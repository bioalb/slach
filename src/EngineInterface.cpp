#include <algorithm>
#include <limits>
#include <sstream>
#include <streambuf>
#include <cassert>
#include "EngineInterface.hpp"
//following includes are the same as main.cpp in stockfish exe
#include "bitboard.h"
#include "evaluate.h"
#include "position.h"
#include "search.h"
#include "thread.h"
#include "tt.h"
#include "ucioption.h"

slach::EngineInterface::EngineInterface()
  : mNumberOfLinesToBeShown(1u),
    mCachedFenPositiontoBeanalysed(""),
    mLatestDepths(mNumberOfLinesToBeShown, std::numeric_limits<int>::max()),
    mLatestScores(mNumberOfLinesToBeShown, std::numeric_limits<double>::max()),
    mLatestLines(mNumberOfLinesToBeShown, ""),
    mLatestRootMoves (mNumberOfLinesToBeShown, ""),
    mpChessBoard( new slach::ChessBoard() )
{
    mpChessBoard->SetupChessBoard();
    InitEngine();
}

void slach::EngineInterface::InitEngine()
{
	  UCI::init(Options);
	  Bitboards::init();
	  ::Position::init();
	  Bitbases::init_kpk();
	  Search::init();
	  Pawns::init();
	  Eval::init();
	  Threads.init();
	  TT.resize(Options["Hash"]);
}

slach::EngineInterface::~EngineInterface()
{
	//mpEngineThread->join();
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
	if (!mpEngineThread)
	{
	    mpEngineThread =  std::make_shared<std::thread>(&slach::EngineInterface::DoAnalysePosition, this, pPosition, seconds);
	    mpEngineThread->detach();
	}
}

void slach::EngineInterface::IssueCommandtoStockfish(const std::string& command)
{
	  //std::streambuf *backup;
	  //backup = std::cin.rdbuf();     // back up cin's streambuf

	  std::stringbuf  psbuf(command + "\n");
	  std::cin.rdbuf(&psbuf);         // assign psbuf to cin
	  std::cin.sync();
	  //std::cin.rdbuf(backup);        // restore cin's original streambuf
}

void slach::EngineInterface::DoAnalysePosition(slach::Position* pPosition, double seconds)
{
	//if (mEngineIsrunning.load(std::memory_order_relaxed) == false)
	//{
		//InitialiseEngine();
	//}

    std::string fen_position = pPosition->GetPositionAsFen();
    mpChessBoard->SetFenPosition(fen_position); //set the helper board with this position
    mCachedFenPositiontoBeanalysed = fen_position;
    std::string position_command = "position fen "+fen_position+"\n";
    IssueCommandtoStockfish(position_command);

	if (seconds < (std::numeric_limits<double>::max() - 1e-1)) // magic number! just want to be sure ...
	{
		IssueCommandtoStockfish("go movetime 5000");
	}
	else
	{
		IssueCommandtoStockfish("go infinite \n");
    }

}

void slach::EngineInterface::StopEngine()
{
	system("quit");
}


std::vector<std::string> slach::EngineInterface::GetLatestEngineOutput()
{
    std::vector<std::string> pv_lines;
    pv_lines.resize(mNumberOfLinesToBeShown);
    //ParseWholeEngineOutput(raw_string);
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

        int depth = std::numeric_limits<int>::max();
        double score = std::numeric_limits<double>::max();
        std::string move_list("");
        std::string root_move("");

        mpChessBoard->SetFenPosition(mCachedFenPositiontoBeanalysed);
        ParseALineofStockfishOutput(to_be_parsed, depth, score, move_list,root_move);
        if (move_list == "CHECKMATE")
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

            bool found = (std::find(mLatestRootMoves.begin(), mLatestRootMoves.end(), root_move)!=mLatestRootMoves.end());
            if (!found)
            {
                mLatestDepths[diverse_lines] = depth;
                mLatestScores[diverse_lines] = score;
                mLatestLines[diverse_lines] = move_list;
                mLatestRootMoves[diverse_lines] = root_move;
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

void slach::EngineInterface::ParseALineofStockfishOutput(const std::string& stockfishLine, int & depth, double & score, std::string &  move_list, std::string& rootMove)
{
    //depth
    size_t pos = stockfishLine.find("depth");
    pos = stockfishLine.find_first_of(' ', pos);
    depth = atoi(&(stockfishLine[pos]));

    //score
    bool mate_found = false;
    pos = stockfishLine.rfind("cp");
    if (pos == std::string::npos)
    {
        pos = stockfishLine.rfind("mate");
        score = 100;
        mate_found = true;
    }
    else
    {
        pos = stockfishLine.find_first_of(' ', pos);
        score = atof(&(stockfishLine[pos]))/100.0;
    }
    //fix the score to be positive for white and negative for black
    Colour to_move = mpChessBoard->WhosTurnIsIt();
    if (to_move == BLACK)
    {
        score = (- score);
    }

    std::size_t start_of_move_list = stockfishLine.find(" pv");
    if (start_of_move_list == std::string::npos)//e.g., mate
    {
        move_list = "CHECKMATE";
        return;
    }
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
            if (!valid)
            {
                break;//wait to sync engine and output in case they are in two threads...
            }
            //assert(valid);
            std::string pretty_move = verbose_move.GetMoveInAlgebraicFormat();
            pretty_line = pretty_line + pretty_move + " ";
            if (i == 0)
            {
                rootMove = pretty_move;
                i++;
            }
            mpChessBoard->MakeThisMove(verbose_move);
        }
        start_of_move = stockfishLine.find_first_not_of(" \n", end_of_move);
    }

    if (pretty_line.length() > 0)
    {
        move_list = pretty_line;
        if (mate_found)
        {
            depth = 0;
            move_list += "mate";
        }
    }
}

