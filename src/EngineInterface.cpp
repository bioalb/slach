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
    mLatestDepths(mNumberOfLinesToBeShown, std::numeric_limits<int>::max()),
    mLatestScores(mNumberOfLinesToBeShown, std::numeric_limits<double>::max()),
    mLatestLines(mNumberOfLinesToBeShown, ""),
    mLatestRootMoves (mNumberOfLinesToBeShown, ""),
    mpChessBoard( new slach::ChessBoard() )
{
    mpChessBoard->SetupChessBoard();

    GlobalCommandFromGUI = "readyok";
    GuiIssuedNewCommand = false;
}

void slach::EngineInterface::LaunchEngine()
{
    mpEngineThread =  std::make_shared<std::thread>(&slach::EngineInterface::InitEngine, this);
}

void slach::EngineInterface::InitEngine()
{
#ifndef SLACH_TESTING
	slach_mutex.lock();
	std::cout.rdbuf(mEngineOutputBuffer);
	slach_mutex.unlock();
#endif
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
    mLatestDepths.resize(mNumberOfLinesToBeShown);
    mLatestScores.resize(mNumberOfLinesToBeShown);
    mLatestLines.resize(mNumberOfLinesToBeShown);
    mLatestRootMoves.resize(mNumberOfLinesToBeShown);
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
		IssueCommandtoStockfish("go movetime 5000");
	}
	else
	{
		IssueCommandtoStockfish("go infinite");
    }
}

void slach::EngineInterface::IssueCommandtoStockfish(const std::string& command)
{
	std::shared_ptr<std::thread> command_thread = std::make_shared<std::thread>(&slach::EngineInterface::DoIssueCommand, this, command);
	command_thread->join();
}
void slach::EngineInterface::DoIssueCommand(const std::string& command)
{
	std::unique_lock<std::mutex> lck(global_mutex_send);
	GuiIssuedNewCommand = true;
	GlobalCommandFromGUI = command;
	global_cv_send.notify_all();
}

void slach::EngineInterface::StopEngine()
{
	IssueCommandtoStockfish("stop");
	slach_mutex.lock();
	mEngineOutputBuffer->str("");
	slach_mutex.unlock();
}

void slach::EngineInterface::QuitEngine()
{
	IssueCommandtoStockfish("quit");
}


std::vector<std::string> slach::EngineInterface::GetLatestEngineOutput()
{
    std::vector<std::string> pv_lines;
    pv_lines.resize(mNumberOfLinesToBeShown);
    std::string raw_string = mEngineOutputBuffer->str();
    ParseWholeEngineOutput(raw_string);
    for (unsigned pv = 0; pv <  pv_lines.size(); pv++)
    {
        std::stringstream ss;
        ss.setf( std::ios::fixed, std::ios::floatfield );//for the score
        ss.precision(2);//for the score
        ss<<"Depth = " << mLatestDepths[pv] << "; score = " << mLatestScores[pv] << "; " << mLatestLines[pv] << std::endl;
        pv_lines[pv] = ss.str();
    }
	return pv_lines;
}

void slach::EngineInterface::SetPositionToInternalChessBoard(const std::string& fenPosition)
{
    mCachedFenPositiontoBeanalysed = fenPosition;
    mpChessBoard->SetFenPosition(mCachedFenPositiontoBeanalysed);
}

void slach::EngineInterface::ParseWholeEngineOutput(const std::string& rawOutput)
{
    unsigned diverse_lines = 0;
    size_t previous_mid_of_useful_line = std::string::npos;
    size_t mid_of_useful_line = 0;
    mLatestRootMoves.assign(mNumberOfLinesToBeShown, "");
    while (mid_of_useful_line != std::string::npos)
    {
        mid_of_useful_line = rawOutput.rfind("score cp", previous_mid_of_useful_line);
        size_t line_with_mate =  rawOutput.rfind("score mate", previous_mid_of_useful_line);
        if ( line_with_mate > mid_of_useful_line && line_with_mate != std::string::npos)
        {
            mid_of_useful_line = line_with_mate;
        }
        size_t line_begin = rawOutput.rfind("\n", mid_of_useful_line);
        size_t line_end = rawOutput.find("\n", mid_of_useful_line);
        std::string to_be_parsed = rawOutput.substr(line_begin, line_end - line_begin);
        previous_mid_of_useful_line = mid_of_useful_line - 1;

        mpChessBoard->SetFenPosition(mCachedFenPositiontoBeanalysed);
        InfoInEngineLine info = ParseALineofStockfishOutput(to_be_parsed);
        if (info.mCheckMate == true)
        {
            for (unsigned index = 0; index < mNumberOfLinesToBeShown; ++index)
            {
                mLatestDepths[index] = 0;
                mLatestScores[index] = 0;
                mLatestLines[index] = "CHECKMATE";
                mLatestRootMoves[index] = "";
            }
            break;
        }
        mpChessBoard->SetFenPosition(mCachedFenPositiontoBeanalysed);//reset to initial fen

//        if ( (depth !=  mLatestDepths[diverse_lines] && move_list.length() >= mLatestLines[diverse_lines].length() ) ||
//             (root_move != mLatestRootMoves[diverse_lines] ) ||
//             (fabs(score - mLatestScores[diverse_lines]) > 0.01 ) ||
//             (move_list != mLatestLines[diverse_lines] && move_list.length() >= mLatestLines[diverse_lines].length() ) )
//        {

            bool found = (std::find(mLatestRootMoves.begin(), mLatestRootMoves.end(), info.mRootMove)!=mLatestRootMoves.end());
            if (!found)
            {
                mLatestDepths[diverse_lines] = info.mDepth;
                mLatestScores[diverse_lines] = info.mScore;
                mLatestLines[diverse_lines] = info.mMoveList;
                mLatestRootMoves[diverse_lines] = info.mRootMove;
                diverse_lines++;
            }

            if (diverse_lines >= mNumberOfLinesToBeShown)
            {
                break;
            }

    }
}
void slach::EngineInterface::GetLatestBestScoreAndDepth(double& bestScore, int& depth, std::string& bestMove)  const
{
    double max = -std::numeric_limits<double>::max();
    double min = std::numeric_limits<double>::max();
    int max_depth = 0;
    std::string best_root_move = "";
    assert(mLatestRootMoves.size() == mLatestDepths.size());
    assert(mLatestRootMoves.size() == mLatestRootMoves.size());
    for (unsigned sc = 0; sc < mLatestScores.size(); ++sc)
    {
        if (mpChessBoard->WhosTurnIsIt() == WHITE )
        {
            if (mLatestScores[sc] > max)
            {
                max = mLatestScores[sc];
                max_depth = mLatestDepths[sc];
                best_root_move = mLatestRootMoves[sc];
            }
        }
        else //black to move
        {
            if (mLatestScores[sc] < min)
            {
                min = mLatestScores[sc];
                max_depth = mLatestDepths[sc];
                best_root_move = mLatestRootMoves[sc];
            }
        }
    }
    bestScore = max;
    if (mpChessBoard->WhosTurnIsIt() == BLACK) bestScore = min;
    depth = max_depth;
    bestMove = best_root_move;
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
    //fix the score to be positive for white and negative for black
    Colour to_move = mpChessBoard->WhosTurnIsIt();
    if (to_move == BLACK) score = (- score);
    info.mScore = score;

    //line
    std::size_t start_of_move_list = stockfishLine.find(" pv");
    //only checkmate lines do not have pv...
    if ( (start_of_move_list == std::string::npos) && info.mCheckMate == false ) return info;  //with valid as false....
    size_t start_of_move = stockfishLine.find_first_not_of(" ", start_of_move_list+2);
    std::string pretty_line = "";
    int i = 0;
    while (start_of_move != std::string::npos)
    {
        std::size_t end_of_move = stockfishLine.find(' ', start_of_move+1);

        std::string move_string = stockfishLine.substr(start_of_move, end_of_move - start_of_move );
        Move verbose_move(move_string, mpChessBoard->GetSquares());
        if ( (verbose_move.GetOrigin() != NULL) && (verbose_move.GetDestination() != NULL) )
        {
            bool valid = mpChessBoard->IsLegalMove(verbose_move);
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

