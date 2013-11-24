#include <iostream>
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


slach::EngineInterface::EngineInterface(slach::ChessBoard* pChessBoard)
  : mNumberOfLinesToBeShown(1u),
    mLatestDepths(mNumberOfLinesToBeShown, INT_MAX),
    mLatestScores(mNumberOfLinesToBeShown, DBL_MAX),
    mLatestLines(mNumberOfLinesToBeShown, ""),
    mLatestRootMoves (mNumberOfLinesToBeShown, ""),
    mpStockfishPosition (new stockfish::Position()),
    mFenString(""),
    mpChessBoard( pChessBoard )
{
    InitialiseEngine();
}

slach::EngineInterface::~EngineInterface()
{
    //stockfish::Threads.exit();
    delete mpStockfishPosition;
}

void slach::EngineInterface::InitialiseEngine()
{
    stockfish::UCI::init(stockfish::Options);
    stockfish::Bitboards::init();
    stockfish::Zobrist::init();
    stockfish::Bitbases::init_kpk();
    stockfish::Search::init();
    stockfish::Eval::init();
    stockfish::Threads.init();
    stockfish::TT.set_size(stockfish::Options["Hash"]);
    stockfish::Options["MultiPV"] = stockfish::UCI::Option(mNumberOfLinesToBeShown, 1, 500);
}

void slach::EngineInterface::SetNumberOfLinesToBeShown(unsigned num)
{
    mNumberOfLinesToBeShown = num;
    mLatestDepths.resize(mNumberOfLinesToBeShown);
    mLatestScores.resize(mNumberOfLinesToBeShown);
    mLatestLines.resize(mNumberOfLinesToBeShown);
    mLatestRootMoves.resize(mNumberOfLinesToBeShown);
    InitialiseEngine();
    stockfish::Options["MultiPV"] = stockfish::UCI::Option(mNumberOfLinesToBeShown, 1, 500);
}

void slach::EngineInterface::StartAnalsyingPosition(double seconds)
{
    InitialiseEngine();
    stockfish::Search::Signals.stop = false;
    stockfish::Search::LimitsType limits;

    std::vector< stockfish::Move > searchMoves;
    mpStockfishPosition->set(mpChessBoard->GetCurrentFenPosition(), false /*not chess960*/, stockfish::Threads.main_thread());
    mFenString = mpChessBoard->GetCurrentFenPosition();
    if (seconds < (std::numeric_limits<double>::max() - 1e-1)) // magic number! just want to be sure ...
    {
        limits.movetime = 1000*seconds;//converts milliseconds to seconds...
        limits.infinite = false;
        stockfish::Threads.start_thinking(*mpStockfishPosition, limits, searchMoves, stockfish::Search::SetupStates);
        stockfish::Threads.wait_for_think_finished();
    }
    else
    {
        limits.infinite = true;
        stockfish::Threads.start_thinking(*mpStockfishPosition, limits, searchMoves, stockfish::Search::SetupStates);
    }
}

void slach::EngineInterface::StopEngine()
{
	stockfish::Search::Signals.stop = true;
	stockfish::Threads.main_thread()->notify_one();
	stockfish::Threads.wait_for_think_finished();
	//stockfish::Threads.exit();
}


std::vector<std::string> slach::EngineInterface::GetLatestEngineOutput()
{
    std::string raw_string = stockfish::global_stream.str();
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
void slach::EngineInterface::ParseWholeEngineOutput(const std::string& rawOutput)
{
    unsigned diverse_lines = 0;
    size_t previous_begin = rawOutput.rfind("bestmove");
    while (diverse_lines < mNumberOfLinesToBeShown)
    {
        size_t line_begin = rawOutput.rfind("Depth", previous_begin - 4);
        //std::cout<<rawOutput.substr(line_begin, previous_begin - line_begin)<<std::endl;
        std::string to_be_parsed = rawOutput.substr(line_begin, previous_begin - line_begin);
        previous_begin = line_begin;

        int depth = INT_MAX;
        double score = DBL_MAX;
        std::string move_list("");
        std::string root_move("");

        ParseALineofStockfishOutput(to_be_parsed, depth, score, move_list,root_move);
        mpChessBoard->SetFenPosition(mFenString);//reset to initial fen
        if ( (depth !=  mLatestDepths[diverse_lines]) ||
             (root_move != mLatestRootMoves[diverse_lines]) ||
             (fabs(score - mLatestScores[diverse_lines]) > 0.01 ) ||
             (move_list != mLatestLines[diverse_lines] && move_list.length() > mLatestLines[diverse_lines].length() ) )
        {
            mLatestDepths[diverse_lines] = depth;
            mLatestScores[diverse_lines] = score;
            mLatestLines[diverse_lines] = move_list;
            mLatestRootMoves[diverse_lines] = root_move;
            diverse_lines++;
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
    mpChessBoard->SetFenPosition(mFenString);
    //depth
    size_t pos = stockfishLine.find("Depth");
    pos = stockfishLine.find_first_of(' ', pos);
    depth = atoi(&(stockfishLine[pos]));

    //score
    pos = stockfishLine.rfind("cp");
    pos = stockfishLine.find_first_of(' ', pos);
    score = atof(&(stockfishLine[pos]))/100.0;
    //fix the score to be positive for white and negative for black
    Colour to_move = mpChessBoard->WhosTurnIsIt();
    if (to_move == BLACK)
    {
        score = (- score);
    }

    std::size_t start_of_move = stockfishLine.find_first_not_of(' ');
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
            assert(valid);
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
    }
}

