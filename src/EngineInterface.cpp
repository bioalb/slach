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


slach::EngineInterface::EngineInterface()
  : mFenString(""),
    mpStockfishPosition (new Position())
{
    UCI::init(Options);
    Bitboards::init();
    Zobrist::init();
    Bitbases::init_kpk();
    Search::init();
    Eval::init();
    Threads.init();
    TT.set_size(Options["Hash"]);
}

slach::EngineInterface::~EngineInterface()
{
    delete mpStockfishPosition;
    //Threads.exit();
}

::Square slach::EngineInterface::ConvertSquareToStockfish(const Square* pSquare) const
{
    if (pSquare == NULL)
    {
        EXCEPTION("This is: slach::EngineInterface::ConvertSquareToStockfish. You have passed in a NULL pointer");
    }
    else
    {
        unsigned index = pSquare->GetIndexFromA1();
        switch ( index ) {
          case 0 : return SQ_A1;
          case 1 : return SQ_B1;
          case 2 : return SQ_C1;
          case 3 : return SQ_D1;
          case 4 : return SQ_E1;
          case 5 : return SQ_F1;
          case 6 : return SQ_G1;
          case 7 : return SQ_H1;
          case 8 : return SQ_A2;
          case 9 : return SQ_B2;
          case 10 : return SQ_C2;
          case 11 : return SQ_D2;
          case 12 : return SQ_E2;
          case 13 : return SQ_F2;
          case 14 : return SQ_G2;
          case 15 : return SQ_H2;
          case 16 : return SQ_A3;
          case 17 : return SQ_B3;
          case 18 : return SQ_C3;
          case 19 : return SQ_D3;
          case 20 : return SQ_E3;
          case 21 : return SQ_F3;
          case 22 : return SQ_G3;
          case 23 : return SQ_H3;
          case 24 : return SQ_A4;
          case 25 : return SQ_B4;
          case 26 : return SQ_C4;
          case 27 : return SQ_D4;
          case 28 : return SQ_E4;
          case 29 : return SQ_F4;
          case 30 : return SQ_G4;
          case 31 : return SQ_H4;
          case 32 : return SQ_A5;
          case 33 : return SQ_B5;
          case 34 : return SQ_C5;
          case 35 : return SQ_D5;
          case 36 : return SQ_E5;
          case 37 : return SQ_F5;
          case 38 : return SQ_G5;
          case 39 : return SQ_H5;
          case 40 : return SQ_A6;
          case 41 : return SQ_B6;
          case 42 : return SQ_C6;
          case 43 : return SQ_D6;
          case 44 : return SQ_E6;
          case 45 : return SQ_F6;
          case 46 : return SQ_G6;
          case 47 : return SQ_H6;
          case 48 : return SQ_A7;
          case 49 : return SQ_B7;
          case 50 : return SQ_C7;
          case 51 : return SQ_D7;
          case 52 : return SQ_E7;
          case 53 : return SQ_F7;
          case 54 : return SQ_G7;
          case 55 : return SQ_H7;
          case 56 : return SQ_A8;
          case 57 : return SQ_B8;
          case 58 : return SQ_C8;
          case 59 : return SQ_D8;
          case 60 : return SQ_E8;
          case 61 : return SQ_F8;
          case 62 : return SQ_G8;
          case 63 : return SQ_H8;
          default : return SQ_NONE;
        }
    }
}
