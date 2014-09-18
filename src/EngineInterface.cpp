#include <algorithm>
#include <limits>
#include <cassert>
#include <sstream>
#include "EngineInterface.hpp"
#include "guithreadvars.h"
#include "main_stockfish.hpp"
std::mutex slach_mutex;

slach::EngineInterface::EngineInterface()
  : mNumberOfLinesToBeShown(1u),
    mEngineOutputBuffer(new std::stringbuf(" ")),
    mCachedFenPositiontoBeanalysed(""),
    mpChessBoard( new slach::ChessBoard() ),
	mpHelperFenHandler( new slach::FenHandler() )
{
    mpChessBoard->SetupChessBoard();
    mLatestEngineLines.resize(mNumberOfLinesToBeShown);
    GlobalCommandFromGUI = "readyok";
    GuiIssuedNewCommand = false;
}

void slach::EngineInterface::LaunchEngine()
{
    mpEngineThread =  std::make_shared<std::thread>(&slach::EngineInterface::InitEngine, this);
}

void slach::EngineInterface::InitEngine()
{
	slach_mutex.lock();
	mBackupCoutBuf = std::cout.rdbuf();
	std::cout.rdbuf(mEngineOutputBuffer);
	slach_mutex.unlock();

	::main_stockfish(1,nullptr);
}

slach::EngineInterface::~EngineInterface()
{
	if (mpEngineThread)
	{
		QuitEngine();
		mpEngineThread->join();
	}
    delete mpChessBoard;
}

void slach::EngineInterface::SetNumberOfLinesToBeShown(unsigned num)
{
    mNumberOfLinesToBeShown = num;
    mLatestEngineLines.resize(num);
    if (mpEngineThread)
    {
    	std::stringstream multipv_command;
    	multipv_command << "setoption name MultiPV value "<<mNumberOfLinesToBeShown;
    	IssueCommandtoStockfish(multipv_command.str());
    }
}

void slach::EngineInterface::StartAnalsyingPosition(slach::Position* pPosition, double seconds)
{
    std::string fen_position = pPosition->GetPositionAsFen();
    mpChessBoard->SetFenPosition(fen_position); //set the helper board with this position
    mCachedFenPositiontoBeanalysed = fen_position;
    std::string position_command = "position fen "+fen_position;
    IssueCommandtoStockfish(position_command);

	if (seconds < (std::numeric_limits<double>::max() - 1e-1)) // magic number! just want to be sure ...
	{
		std::stringstream time_limit_command;
		int milliseconds = static_cast<int> (seconds * 1000);
		time_limit_command << "go movetime "<<milliseconds;
		IssueCommandtoStockfish(time_limit_command.str());
	}
	else
	{
		IssueCommandtoStockfish("go infinite");
    }
}

void slach::EngineInterface::IssueCommandtoStockfish(const std::string& command)
{
	while (EngineReadyToReceiveNewCommand.load() == false) {} //wait here

	std::shared_ptr<std::thread> command_thread = std::make_shared<std::thread>(&slach::EngineInterface::DoIssueCommand, this, command);
	command_thread->join();
	GuiIssuedNewCommand.store(false);
}
void slach::EngineInterface::DoIssueCommand(const std::string& command)
{
	std::unique_lock<std::mutex> lck(GUICmmandMutex);
	GuiIssuedNewCommand = true;
	GlobalCommandFromGUI = command;
	GUICmmandCondition.notify_all();
}

void slach::EngineInterface::StopEngine()
{
	IssueCommandtoStockfish("stop");
}

void slach::EngineInterface::QuitEngine()
{
	IssueCommandtoStockfish("quit");
	slach_mutex.lock();
	if (mBackupCoutBuf) std::cout.rdbuf(mBackupCoutBuf);//restore std::cout
	slach_mutex.unlock();
}

std::vector<std::string> slach::EngineInterface::GetLatestEngineOutput()
{
	std::string raw_string = mEngineOutputBuffer->str();
	mLatestEngineLines = ParseWholeEngineOutput(raw_string);
	if (mLatestEngineLines.size() < mNumberOfLinesToBeShown)
	{
		mLatestEngineLines.resize(mNumberOfLinesToBeShown);
	}

	std::sort(mLatestEngineLines.begin(), mLatestEngineLines.end());
	if (mpHelperFenHandler->GetPositionFeaturesFromFen(mCachedFenPositiontoBeanalysed).mTurnToMove == WHITE)
	{
		std::reverse(mLatestEngineLines.begin(), mLatestEngineLines.end());
	}

	std::vector<std::string> pv_lines;
    pv_lines.resize(mLatestEngineLines.size());
    for (unsigned pv = 0; pv <  pv_lines.size(); pv++)
    {
        std::stringstream ss;
        ss.setf( std::ios::fixed, std::ios::floatfield );//for the score
        ss.precision(2);//for the score
        ss<<"Depth = " << mLatestEngineLines[pv].mDepth << "; score = " << mLatestEngineLines[pv].mScore << "; " << mLatestEngineLines[pv].mMoveList << std::endl;
        pv_lines[pv] = ss.str();
    }
	return pv_lines;
}

void slach::EngineInterface::SetPositionToInternalChessBoard(const std::string& fenPosition)
{
    mCachedFenPositiontoBeanalysed = fenPosition;
    mpChessBoard->SetFenPosition(mCachedFenPositiontoBeanalysed);
}

std::vector<slach::InfoInEngineLine> slach::EngineInterface::ParseWholeEngineOutput(const std::string& rawOutput)
{
	std::vector<InfoInEngineLine> ret;
    unsigned diverse_lines = 0;
    size_t line_begins = std::string::npos-1;

    while (diverse_lines < mNumberOfLinesToBeShown && line_begins != std::string::npos)
    {
    	line_begins = rawOutput.rfind("info", line_begins-1);
        size_t line_end = rawOutput.find("\n", line_begins);

        if (line_begins != std::string::npos && line_end != std::string::npos)
        {
        	std::string to_be_parsed = rawOutput.substr(line_begins, line_end - line_begins);
        	auto info = ParseALineofStockfishOutput(to_be_parsed);
            if ( std::find (ret.begin(), ret.end(), info) == ret.end()  && info.mValid == true)  //if not found
			{
            	ret.push_back(info);
            	diverse_lines++;
			}
        }
    }

    return ret;
}
void slach::EngineInterface::GetLatestBestScoreAndDepth(double& bestScore, int& depth, std::string& bestMove)  const
{
	bestScore = mLatestEngineLines[0].mScore;
	depth = mLatestEngineLines[0].mDepth;
	bestMove = mLatestEngineLines[0].mRootMove;
}


slach::InfoInEngineLine slach::EngineInterface::ParseALineofStockfishOutput(const std::string& stockfishLine)
{
	InfoInEngineLine info;

    //depth
    size_t pos = stockfishLine.find("info depth");
    if (pos == std::string::npos) return info; //with valid as false....
    pos = stockfishLine.find_first_not_of(" ", pos+10); //10 is the length of "info depth" itself...
    info.mDepth = atoi(&(stockfishLine[pos]));

    //mate line or checkmate?
    pos = stockfishLine.find("mate");
    if (pos != std::string::npos)
    {
    	pos = stockfishLine.find_first_not_of(' ', pos+4);
    	info.mDepth = atoi(&(stockfishLine[pos]));
    	if (info.mDepth == 0)
    	{
    		info.mCheckMate = true;
    		info.mRootMove = "checkmate";
    		info.mValid = true;
    		return info;
    	}
    	info.mMateLine = true;
    }

    //score
    pos = stockfishLine.rfind("cp");
    if ( (pos == std::string::npos) && info.mMateLine == false ) return info;  //with valid as false....
    pos = stockfishLine.find_first_of(' ', pos);
    double score = atof(&(stockfishLine[pos]))/100.0;
    if (info.mMateLine == true) score = 100;
    //fix the score to be positive for white and negative for black
    if (mpHelperFenHandler->GetPositionFeaturesFromFen(mCachedFenPositiontoBeanalysed).mTurnToMove == BLACK) score = (- score);
    info.mScore = score;

    //line
    std::size_t start_of_move_list = stockfishLine.find(" pv");
    //only checkmate lines do not have pv...
    if ( (start_of_move_list == std::string::npos) && info.mCheckMate == false ) return info;  //with valid as false....
    size_t start_of_move = stockfishLine.find_first_not_of(" ", start_of_move_list+2);
    std::string pretty_line = "";
    int i = 0;
    mpChessBoard->SetFenPosition(mCachedFenPositiontoBeanalysed);
    while (start_of_move != std::string::npos)
    {
        std::size_t end_of_move = stockfishLine.find(' ', start_of_move+1);

        std::string move_string = stockfishLine.substr(start_of_move, end_of_move - start_of_move );
        Move verbose_move(move_string, mpChessBoard->GetSquares());
        if ( (verbose_move.GetOrigin() != NULL) && (verbose_move.GetDestination() != NULL) )
        {
            if (! mpChessBoard->IsLegalMove(verbose_move) ) return info; //with valid still as false

            std::string pretty_move = verbose_move.GetMoveInAlgebraicFormat();
            pretty_line = pretty_line + pretty_move + " ";
            if (i == 0)
            {
                info.mRootMove = pretty_move;
                i++;
            }
            mpChessBoard->MakeThisMove(verbose_move);
        }
        start_of_move = stockfishLine.find_first_not_of(" \n", end_of_move);
    }

    if (pretty_line.length() > 0)
    {
        info.mMoveList = pretty_line;

        if (info.mMateLine == true) info.mMoveList += "mate";
    }

    info.mValid  = true;
    return info;
}

