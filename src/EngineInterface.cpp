#include <iostream>
#include <streambuf>
#include <pthread.h>
#include "EngineInterface.hpp"
#include "Exception.hpp"
#include "platform.h"
#include "bitboard.h"
#include "evaluate.h"
#include "position.h"
#include "search.h"
#include "thread.h"
#include "tt.h"
#include "ucioption.h"
#include "misc.h"


slach::EngineInterface::EngineInterface()
  : mNumberOfLinesToBeShown(1u),
    mCachedFenPositiontoBeanalysed(""),
    mLatestDepths(mNumberOfLinesToBeShown, INT_MAX),
    mLatestScores(mNumberOfLinesToBeShown, DBL_MAX),
    mLatestLines(mNumberOfLinesToBeShown, ""),
    mLatestRootMoves (mNumberOfLinesToBeShown, ""),
    mpStockfishPosition (new ::Position()),
    mpChessBoard( new slach::ChessBoard() )
{
    mpChessBoard->SetupChessBoard();
    InitialiseEngine();
}

slach::EngineInterface::~EngineInterface()
{
    delete mpStockfishPosition;
    delete mpChessBoard;
}

void slach::EngineInterface::InitialiseEngine()
{
    ::UCI::init(::Options);
    ::Bitboards::init();
    ::Position::init();
    ::Bitbases::init_kpk();
    ::Search::init();
    ::Eval::init();
    ::Threads.init();
    ::TT.set_size(::Options["Hash"]);
    ::Options["MultiPV"] = ::UCI::Option(mNumberOfLinesToBeShown, 1, 500);
}

void slach::EngineInterface::SetNumberOfLinesToBeShown(unsigned num)
{
    mNumberOfLinesToBeShown = num;
    mLatestDepths.resize(mNumberOfLinesToBeShown);
    mLatestScores.resize(mNumberOfLinesToBeShown);
    mLatestLines.resize(mNumberOfLinesToBeShown);
    mLatestRootMoves.resize(mNumberOfLinesToBeShown);
    ::Options["MultiPV"] = ::UCI::Option(mNumberOfLinesToBeShown, 1, 500);
}

void slach::EngineInterface::StartAnalsyingPosition(slach::Position* pPosition, double seconds)
{
    ::Position::init();//this makes tests passing...
    ::Search::Signals.stop = false;
    ::Search::LimitsType limits;
    assert(pPosition != NULL);

    //critically important to clear the stream.
    ::global_stream.str(std::string());
    ::global_stream.clear();

    std::vector< ::Move > searchMoves;
    mpStockfishPosition->set(pPosition->GetPositionAsFen(), false /*not chess960*/, ::Threads.main());
    mpChessBoard->SetFenPosition(pPosition->GetPositionAsFen()); //set the helper board with this position
    mCachedFenPositiontoBeanalysed = pPosition->GetPositionAsFen();

    try
    {
        if (seconds < (std::numeric_limits<double>::max() - 1e-1)) // magic number! just want to be sure ...
        {
            limits.movetime = 1000*seconds;//converts milliseconds to seconds...
            limits.infinite = false;
            ::Threads.start_thinking(*mpStockfishPosition, limits, searchMoves, ::Search::SetupStates);
            ::Threads.wait_for_think_finished();
        }
        else
        {
            limits.infinite = true;
            ::Threads.start_thinking(*mpStockfishPosition, limits, searchMoves, ::Search::SetupStates);
        }
    }
    catch (int e)
    {
        std::cout<<"Exception!!!"<<std::endl;
    }
}

void slach::EngineInterface::StopEngine()
{
	::Search::Signals.stop = true;
	::Threads.main()->notify_one();
	::Threads.wait_for_think_finished();
}


std::vector<std::string> slach::EngineInterface::GetLatestEngineOutput()
{
    std::string raw_string = ::global_stream.str();
    std::vector<std::string> pv_lines;
    pv_lines.resize(mNumberOfLinesToBeShown);
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

        int depth = INT_MAX;
        double score = DBL_MAX;
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
std::pair<double, int>  slach::EngineInterface::GetLatestBestScoreAndDepth() const
{
    std::pair<double, int> ret;
    double max = 0;
    int max_depth = 0;
    for (unsigned sc = 0; sc < mLatestScores.size(); ++sc)
    {
        if (fabs(mLatestScores[sc]) > max)
        {
            max = mLatestScores[sc];
            max_depth = mLatestDepths[sc];
        }
    }
    ret.first = max;
    ret.second = max_depth;
    return ret;
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

