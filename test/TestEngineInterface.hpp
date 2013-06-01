#ifndef TESTENGINEINTERFACE_HPP_
#define TESTENGINEINTERFACE_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include "ChessBoard.hpp"
#include "EngineInterface.hpp"

/**
 * Test suite to test the engine interface class
 */
class TestEngineInterface : public CxxTest::TestSuite
{
public:

    void TestInterface()
    {
        slach::EngineInterface interface;
        slach::Square* pe2 = new slach::Square();
        pe2->SetFile("e");
        pe2->SetRank("2");
        pe2->SetIndexFromA1(12u);

        slach::Square* pe4 = new slach::Square();
        pe4->SetFile("e");
        pe4->SetRank("4");
        pe4->SetIndexFromA1(28u);

        slach::Square* pe5 = new slach::Square();
        pe5->SetFile("e");
        pe5->SetRank("5");
        pe5->SetIndexFromA1(36u);

        slach::Move e2e4;
        e2e4.first = pe2;
        e2e4.second = pe4;

        std::string initial_position = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        bool valid = interface.IsMoveValidInPosition(initial_position, e2e4);
        TS_ASSERT_EQUALS(valid,true);

        slach::Move e2e5;
        e2e5.first = pe2;
        e2e5.second = pe5;

        valid = interface.IsMoveValidInPosition(initial_position, e2e5);
        TS_ASSERT_EQUALS(valid,false);

        delete pe2;
        delete pe4;
        delete pe5;
    }

    void TestLegalMoves()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();

        //from one of my games on chessworld (8771022). Picture stored in test/data/test_position_1 for reference only
        std::string test_position_1 = "r2q1rk1/pp2b1pp/2n2np1/2pp4/3P4/2PB1N2/PP2QPPP/R1B1R1K1 b - - 3 15";
        my_cb.SetFenPosition(test_position_1);
        std::vector<slach::Square*> squares =  my_cb.GetSquares();//already numbered and well defined.

        slach::EngineInterface interface;

        slach::Move illegal_because_it_is_black_turn;//a1-b1
        illegal_because_it_is_black_turn.first = squares[0];
        illegal_because_it_is_black_turn.second = squares[1];
        TS_ASSERT_EQUALS(false, interface.IsMoveValidInPosition(test_position_1, illegal_because_it_is_black_turn));

        slach::Move illegal_because_no_piece_on_origin;//b1-c1
        illegal_because_no_piece_on_origin.first = squares[1];
        illegal_because_no_piece_on_origin.second = squares[2];
        TS_ASSERT_EQUALS(false, interface.IsMoveValidInPosition(test_position_1, illegal_because_no_piece_on_origin));

        slach::Move illegal_move_by_black;//f8-g8
        illegal_move_by_black.first = squares[61];
        illegal_move_by_black.second = squares[62];
        TS_ASSERT_EQUALS(false, interface.IsMoveValidInPosition(test_position_1, illegal_move_by_black));

        slach::Move illegal_move_by_black_2;//d8-e6, queen moving like a knight
        illegal_move_by_black_2.first = squares[59];
        illegal_move_by_black_2.second = squares[44];
        TS_ASSERT_EQUALS(false, interface.IsMoveValidInPosition(test_position_1, illegal_move_by_black_2));

        slach::Move legal_capturte_by_black;//c5-d4
        legal_capturte_by_black.first = squares[34];
        legal_capturte_by_black.second = squares[27];
        TS_ASSERT_EQUALS(true, interface.IsMoveValidInPosition(test_position_1, legal_capturte_by_black));

        slach::Move legal_move_by_black;//g8-h8
        legal_move_by_black.first = squares[62];
        legal_move_by_black.second = squares[63];
        TS_ASSERT_EQUALS(true, interface.IsMoveValidInPosition(test_position_1, legal_move_by_black));

        slach::Move legal_move_by_black_2;//c6-a5 knight move
        legal_move_by_black_2.first = squares[42];
        legal_move_by_black_2.second = squares[32];
        TS_ASSERT_EQUALS(true, interface.IsMoveValidInPosition(test_position_1, legal_move_by_black_2));
    }

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

};
#endif

