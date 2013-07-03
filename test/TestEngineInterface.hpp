#ifndef TESTENGINEINTERFACE_HPP_
#define TESTENGINEINTERFACE_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include "evaluate.h"
#include "thread.h"
#include "EngineInterface.hpp"
#include "ChessBoard.hpp"


/**
 * Test suite to test the engine interface class
 */
class TestEngineInterface : public CxxTest::TestSuite
{
public:

    void TestConversionFromSalchToStockfish()
    {
        slach::EngineInterface interface;
        slach::Square* pe2 = NULL;
        ::Square sf_square;
        //coverage
        TS_ASSERT_THROWS_THIS(sf_square = interface.ConvertSquareToStockfish(pe2),
                "This is: slach::EngineInterface::ConvertSquareToStockfish. You have passed in a NULL pointer");

        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        std::vector<slach::Square*> squares =  my_cb.GetSquares();//already numbered and well defined.

        //coped and pasted from stockfish file types.h
        std::vector< ::Square > stockfish_squares {SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
        SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
        SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
        SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
        SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
        SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
        SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
        SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,
        SQ_NONE};

        for (unsigned i = 0; i < squares.size(); ++i)
        {
            TS_ASSERT_EQUALS(stockfish_squares[i], interface.ConvertSquareToStockfish(squares[i]));
        }
        TS_ASSERT_EQUALS(squares.size()+1u, stockfish_squares.size());

        pe2 = new slach::Square();
        pe2->SetIndexFromA1(152);
        sf_square = SQ_NONE;//avoids silly warning
        TS_ASSERT_EQUALS(stockfish_squares[squares.size()], sf_square);
        TS_ASSERT_EQUALS(stockfish_squares[squares.size()], interface.ConvertSquareToStockfish(pe2));
        delete pe2;
    }

    void TestPosition()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        std::vector<slach::Square*> squares =  my_cb.GetSquares();//already numbered and well defined.
        my_cb.SetupInitialChessPosition();
        std::string test_position_3 = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";

        std::string fen_pos = my_cb.GetCurrentFenPosition();

        Position stockfish_position;
        Search::LimitsType limits;
        limits.movetime = 1000*7;//think for 7 seconds...
        std::vector< ::Move > searchMoves;

        stockfish_position.set(test_position_3, false, ::Threads.main_thread());
        std::cout<<std::endl;
        std::cout<<::Eval::trace(stockfish_position)<<std::endl;

        Threads.start_thinking(stockfish_position, limits, searchMoves, Search::SetupStates);
        Threads.wait_for_think_finished();

    }

};
#endif

