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


slach::EngineInterface::EngineInterface()
  : mFenString(""),
    mLatestOutput(""),
    mpStockfishPosition (new stockfish::Position())
{
    stockfish::UCI::init(stockfish::Options);
    stockfish::Bitboards::init();
    stockfish::Zobrist::init();
    stockfish::Bitbases::init_kpk();
    stockfish::Search::init();
    stockfish::Eval::init();
    stockfish::Threads.init();
    stockfish::TT.set_size(stockfish::Options["Hash"]);
}

slach::EngineInterface::~EngineInterface()
{
    //stockfish::Threads.exit();
    delete mpStockfishPosition;
}

void slach::EngineInterface::StartAnalsyingPosition(Position* pPosition, double seconds)
{
    assert(pPosition != NULL);
    stockfish::Search::init();
    stockfish::Threads.init();

    stockfish::Search::Signals.stop = false;
    stockfish::Search::LimitsType limits;

    std::vector< stockfish::Move > searchMoves;
    mpStockfishPosition->set(pPosition->GetPositionAsFen(), false /*not chess960*/, stockfish::Threads.main_thread());

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


std::string slach::EngineInterface::GetLatestEngineOutput()
{
    std::string raw_string = stockfish::global_stream.str();
    if (raw_string.compare(mLatestOutput) > 0) //raw_string is longer
    {
        //std::size_t end_of_shorter_string = raw_string.find(mLatestOutput);


        raw_string = raw_string.substr(mLatestOutput.length());
        mLatestOutput = raw_string;
    }
    else
    {
        raw_string = "";
    }
	return raw_string;
}

stockfish::Square slach::EngineInterface::ConvertSquareToStockfish(const Square* pSquare) const
{
    if (pSquare == NULL)
    {
        EXCEPTION("This is: slach::EngineInterface::ConvertSquareToStockfish. You have passed in a NULL pointer");
    }
    else
    {
        unsigned index = pSquare->GetIndexFromA1();
        switch ( index ) {
          case 0 : return stockfish::SQ_A1;
          case 1 : return stockfish::SQ_B1;
          case 2 : return stockfish::SQ_C1;
          case 3 : return stockfish::SQ_D1;
          case 4 : return stockfish::SQ_E1;
          case 5 : return stockfish::SQ_F1;
          case 6 : return stockfish::SQ_G1;
          case 7 : return stockfish::SQ_H1;
          case 8 : return stockfish::SQ_A2;
          case 9 : return stockfish::SQ_B2;
          case 10 : return stockfish::SQ_C2;
          case 11 : return stockfish::SQ_D2;
          case 12 : return stockfish::SQ_E2;
          case 13 : return stockfish::SQ_F2;
          case 14 : return stockfish::SQ_G2;
          case 15 : return stockfish::SQ_H2;
          case 16 : return stockfish::SQ_A3;
          case 17 : return stockfish::SQ_B3;
          case 18 : return stockfish::SQ_C3;
          case 19 : return stockfish::SQ_D3;
          case 20 : return stockfish::SQ_E3;
          case 21 : return stockfish::SQ_F3;
          case 22 : return stockfish::SQ_G3;
          case 23 : return stockfish::SQ_H3;
          case 24 : return stockfish::SQ_A4;
          case 25 : return stockfish::SQ_B4;
          case 26 : return stockfish::SQ_C4;
          case 27 : return stockfish::SQ_D4;
          case 28 : return stockfish::SQ_E4;
          case 29 : return stockfish::SQ_F4;
          case 30 : return stockfish::SQ_G4;
          case 31 : return stockfish::SQ_H4;
          case 32 : return stockfish::SQ_A5;
          case 33 : return stockfish::SQ_B5;
          case 34 : return stockfish::SQ_C5;
          case 35 : return stockfish::SQ_D5;
          case 36 : return stockfish::SQ_E5;
          case 37 : return stockfish::SQ_F5;
          case 38 : return stockfish::SQ_G5;
          case 39 : return stockfish::SQ_H5;
          case 40 : return stockfish::SQ_A6;
          case 41 : return stockfish::SQ_B6;
          case 42 : return stockfish::SQ_C6;
          case 43 : return stockfish::SQ_D6;
          case 44 : return stockfish::SQ_E6;
          case 45 : return stockfish::SQ_F6;
          case 46 : return stockfish::SQ_G6;
          case 47 : return stockfish::SQ_H6;
          case 48 : return stockfish::SQ_A7;
          case 49 : return stockfish::SQ_B7;
          case 50 : return stockfish::SQ_C7;
          case 51 : return stockfish::SQ_D7;
          case 52 : return stockfish::SQ_E7;
          case 53 : return stockfish::SQ_F7;
          case 54 : return stockfish::SQ_G7;
          case 55 : return stockfish::SQ_H7;
          case 56 : return stockfish::SQ_A8;
          case 57 : return stockfish::SQ_B8;
          case 58 : return stockfish::SQ_C8;
          case 59 : return stockfish::SQ_D8;
          case 60 : return stockfish::SQ_E8;
          case 61 : return stockfish::SQ_F8;
          case 62 : return stockfish::SQ_G8;
          case 63 : return stockfish::SQ_H8;
          default : return stockfish::SQ_NONE;
        }
    }
}
