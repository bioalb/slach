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
        stockfish::Square sf_square;
        //coverage
        TS_ASSERT_THROWS_THIS(sf_square = interface.ConvertSquareToStockfish(pe2),
                "This is: slach::EngineInterface::ConvertSquareToStockfish. You have passed in a NULL pointer");

        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        std::vector<slach::Square*> squares =  my_cb.GetSquares();//already numbered and well defined.

        //coped and pasted from stockfish file types.h
        std::vector< stockfish::Square > stockfish_squares {stockfish::SQ_A1, stockfish::SQ_B1, stockfish::SQ_C1, stockfish::SQ_D1, stockfish::SQ_E1, stockfish::SQ_F1, stockfish::SQ_G1, stockfish::SQ_H1,
        stockfish::SQ_A2, stockfish::SQ_B2, stockfish::SQ_C2, stockfish::SQ_D2, stockfish::SQ_E2, stockfish::SQ_F2, stockfish::SQ_G2, stockfish::SQ_H2,
        stockfish::SQ_A3, stockfish::SQ_B3, stockfish::SQ_C3, stockfish::SQ_D3, stockfish::SQ_E3, stockfish::SQ_F3, stockfish::SQ_G3, stockfish::SQ_H3,
        stockfish::SQ_A4, stockfish::SQ_B4, stockfish::SQ_C4, stockfish::SQ_D4, stockfish::SQ_E4, stockfish::SQ_F4, stockfish::SQ_G4, stockfish::SQ_H4,
        stockfish::SQ_A5, stockfish::SQ_B5, stockfish::SQ_C5, stockfish::SQ_D5, stockfish::SQ_E5, stockfish::SQ_F5, stockfish::SQ_G5, stockfish::SQ_H5,
        stockfish::SQ_A6, stockfish::SQ_B6, stockfish::SQ_C6, stockfish::SQ_D6, stockfish::SQ_E6, stockfish::SQ_F6, stockfish::SQ_G6, stockfish::SQ_H6,
        stockfish::SQ_A7, stockfish::SQ_B7, stockfish::SQ_C7, stockfish::SQ_D7, stockfish::SQ_E7, stockfish::SQ_F7, stockfish::SQ_G7, stockfish::SQ_H7,
        stockfish::SQ_A8, stockfish::SQ_B8, stockfish::SQ_C8, stockfish::SQ_D8, stockfish::SQ_E8, stockfish::SQ_F8, stockfish::SQ_G8, stockfish::SQ_H8,
        stockfish::SQ_NONE};

        for (unsigned i = 0; i < squares.size(); ++i)
        {
            TS_ASSERT_EQUALS(stockfish_squares[i], interface.ConvertSquareToStockfish(squares[i]));
        }
        TS_ASSERT_EQUALS(squares.size()+1u, stockfish_squares.size());

        pe2 = new slach::Square();
        pe2->SetIndexFromA1(152);
        sf_square = stockfish::SQ_NONE;//avoids silly warning
        TS_ASSERT_EQUALS(stockfish_squares[squares.size()], sf_square);
        TS_ASSERT_EQUALS(stockfish_squares[squares.size()], interface.ConvertSquareToStockfish(pe2));
        delete pe2;
    }

    void TestStartAndStopAfterthreeseconds()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        std::vector<slach::Square*> squares =  my_cb.GetSquares();//already numbered and well defined.

        slach::EngineInterface interface;
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        slach::Position position;
        position.SetFromFen(test_position, squares);
        std::cout<<std::endl<<"*******"<<"Starting analysis. I will analyse for 3 seconds"<<"*******"<<std::endl;
        interface.StartAnalsyingPosition(&position, 3.0);
        std::cout<<std::endl<<"Done analysing for 3 seconds, engine output follows"<<std::endl;
        std::cout<<interface.GetLatestEngineOutput()<<std::endl;
    }

    void TestStartInfiniteAndStop()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        std::vector<slach::Square*> squares =  my_cb.GetSquares();//already numbered and well defined.

        slach::EngineInterface interface;
        //coverage
        TS_ASSERT_EQUALS(interface.GetLatestDepth(), INT_MAX);
        TS_ASSERT_EQUALS(interface.GetLatestScore(), DBL_MAX);

        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        slach::Position position;
        position.SetFromFen(test_position, squares);
        std::cout<<std::endl<<"*******"<<"Starting analysis. I will start with infinite analysis"<<"*******"<<std::endl;
        interface.StartAnalsyingPosition(&position);

		std::time_t time_now;
		std::time_t start_time;
		std::time(&start_time);

		while (std::difftime(time_now,start_time) < 5.0)
		{
			std::time(&time_now);
		}
        interface.StopEngine();
        std::cout<<interface.GetLatestEngineOutput()<<std::endl;
    }

    void TestParsingEngineOutput()
    {
        slach::EngineInterface interface;
        slach::ChessBoard board;
        board.SetupChessBoard();
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        board.SetFenPosition(test_position);
        interface.mFenString = test_position;
        interface.mpChessBoard = &board;
        interface.mpSquares = interface.mpChessBoard->GetSquares();
        std::string test_string =   std::string("Depth 1 Score cp -24 Line: f6e4 c3e4 d5e4") +
                                    "\nDepth 2 Score cp -24 Line: f6e4 c3e4 d5e4" +
                                    "\nDepth 3 Score cp -8 Line: f5d3 d2d3 e7e6" +
                                    "\nDepth 4 Score cp -12 Line: f6e4 c3e4 d5e4 g2g4" +
                                    "\nDepth 5 Score cp -4 Line: f5d3 d2d3 c6b4 d3d2 e7e6\n";
        int depth;
        double score;
        std::string line;
        interface.ParseEngineOutput(test_string, depth, score, line);

        TS_ASSERT_EQUALS(depth,5);
        TS_ASSERT_DELTA(score, 4.0/100.0, 1e-6);
        TS_ASSERT_EQUALS(line, "Bxd3 Qxd3 Nb4 Qd2 e6 ");

        interface.mpChessBoard = NULL;
    }

};
#endif

