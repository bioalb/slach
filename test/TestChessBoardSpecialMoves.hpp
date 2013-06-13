#ifndef TESTCHESSBOARDSPECIALMOVES_HPP_
#define TESTCHESSBOARDSPECIALMOVES_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include "../src/ChessBoard.hpp"
#include "SlachTypes.hpp"

/**
 * Test suite to test the chessboard (Sepcial moves)
 */

class TestChessBoardSpecialMoves : public CxxTest::TestSuite
{
  public :

    void testCastlingQueenSide(void)
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        std::vector<slach::Square* > squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(squares.size(), 64u);

        std::string all_castle_allowed = "r3k2r/pppbqppp/2np1n2/2b1p3/2B1P3/2NP1N2/PPPBQPPP/R3K2R w KQkq - 4 8";
        my_cb.SetFenPosition(all_castle_allowed);

        slach::Move white_castle_queenside;
        white_castle_queenside.first = squares[4];//e1
        white_castle_queenside.second = squares[2];//c1

        slach::Move white_castle_kingside;
        white_castle_kingside.first = squares[4];//e1
        white_castle_kingside.second = squares[6];//g1

        TS_ASSERT_EQUALS(my_cb.IsLegalMove(white_castle_queenside), true);
        TS_ASSERT_EQUALS(my_cb.IsLegalMove(white_castle_kingside), true);

        //make the move
        my_cb.MakeThisMove(white_castle_queenside);

        //check piece position
        TS_ASSERT_EQUALS(squares[0]->GetPieceOnThisSquare(), slach::NO_PIECE);//a1
        TS_ASSERT_EQUALS(squares[1]->GetPieceOnThisSquare(), slach::NO_PIECE);//b1
        TS_ASSERT_EQUALS(squares[2]->GetPieceOnThisSquare(), slach::WHITE_KING);//c1
        TS_ASSERT_EQUALS(squares[3]->GetPieceOnThisSquare(), slach::WHITE_ROOK);//d1
        TS_ASSERT_EQUALS(squares[4]->GetPieceOnThisSquare(), slach::NO_PIECE);//e1
        TS_ASSERT_EQUALS(squares[5]->GetPieceOnThisSquare(), slach::NO_PIECE);//f1
        TS_ASSERT_EQUALS(squares[6]->GetPieceOnThisSquare(), slach::NO_PIECE);//g1
        TS_ASSERT_EQUALS(squares[7]->GetPieceOnThisSquare(), slach::WHITE_ROOK);//h1

        TS_ASSERT_EQUALS (my_cb.GetCurrentFenPosition(), "r3k2r/pppbqppp/2np1n2/2b1p3/2B1P3/2NP1N2/PPPBQPPP/2KR3R b kq - 5 8");

        slach::Move black_castle_queenside;
        black_castle_queenside.first = squares[60];//e8
        black_castle_queenside.second = squares[58];//c8

        slach::Move black_castle_kingside;
        black_castle_kingside.first = squares[60];//e8
        black_castle_kingside.second = squares[62];//g8

        TS_ASSERT_EQUALS(my_cb.IsLegalMove(black_castle_queenside), true);
        TS_ASSERT_EQUALS(my_cb.IsLegalMove(black_castle_kingside), true);

        //make the move
        my_cb.MakeThisMove(black_castle_queenside);

        //check piece position
        TS_ASSERT_EQUALS(squares[56]->GetPieceOnThisSquare(), slach::NO_PIECE);//a8
        TS_ASSERT_EQUALS(squares[57]->GetPieceOnThisSquare(), slach::NO_PIECE);//b8
        TS_ASSERT_EQUALS(squares[58]->GetPieceOnThisSquare(), slach::BLACK_KING);//c8
        TS_ASSERT_EQUALS(squares[59]->GetPieceOnThisSquare(), slach::BLACK_ROOK);//d8
        TS_ASSERT_EQUALS(squares[60]->GetPieceOnThisSquare(), slach::NO_PIECE);//e8
        TS_ASSERT_EQUALS(squares[61]->GetPieceOnThisSquare(), slach::NO_PIECE);//f8
        TS_ASSERT_EQUALS(squares[62]->GetPieceOnThisSquare(), slach::NO_PIECE);//g8
        TS_ASSERT_EQUALS(squares[63]->GetPieceOnThisSquare(), slach::BLACK_ROOK);//h8

        TS_ASSERT_EQUALS (my_cb.GetCurrentFenPosition(), "2kr3r/pppbqppp/2np1n2/2b1p3/2B1P3/2NP1N2/PPPBQPPP/2KR3R w - - 6 9");
    }

    void testCastlingKingSide(void)
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        std::vector<slach::Square* > squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(squares.size(), 64u);

        std::string all_castle_allowed = "r3k2r/pppbqppp/2np1n2/2b1p3/2B1P3/2NP1N2/PPPBQPPP/R3K2R w KQkq - 4 8";
        my_cb.SetFenPosition(all_castle_allowed);

        slach::Move white_castle_queenside;
        white_castle_queenside.first = squares[4];//e1
        white_castle_queenside.second = squares[2];//c1

        slach::Move white_castle_kingside;
        white_castle_kingside.first = squares[4];//e1
        white_castle_kingside.second = squares[6];//g1

        TS_ASSERT_EQUALS(my_cb.IsLegalMove(white_castle_queenside), true);
        TS_ASSERT_EQUALS(my_cb.IsLegalMove(white_castle_kingside), true);

        //make the move
        my_cb.MakeThisMove(white_castle_kingside);

        //check piece position
        TS_ASSERT_EQUALS(squares[0]->GetPieceOnThisSquare(), slach::WHITE_ROOK);//a1
        TS_ASSERT_EQUALS(squares[1]->GetPieceOnThisSquare(), slach::NO_PIECE);//b1
        TS_ASSERT_EQUALS(squares[2]->GetPieceOnThisSquare(), slach::NO_PIECE);//c1
        TS_ASSERT_EQUALS(squares[3]->GetPieceOnThisSquare(), slach::NO_PIECE);//d1
        TS_ASSERT_EQUALS(squares[4]->GetPieceOnThisSquare(), slach::NO_PIECE);//e1
        TS_ASSERT_EQUALS(squares[5]->GetPieceOnThisSquare(), slach::WHITE_ROOK);//f1
        TS_ASSERT_EQUALS(squares[6]->GetPieceOnThisSquare(), slach::WHITE_KING);//g1
        TS_ASSERT_EQUALS(squares[7]->GetPieceOnThisSquare(), slach::NO_PIECE);//h1

        TS_ASSERT_EQUALS (my_cb.GetCurrentFenPosition(), "r3k2r/pppbqppp/2np1n2/2b1p3/2B1P3/2NP1N2/PPPBQPPP/R4RK1 b kq - 5 8");

        slach::Move black_castle_queenside;
        black_castle_queenside.first = squares[60];//e8
        black_castle_queenside.second = squares[58];//c8

        slach::Move black_castle_kingside;
        black_castle_kingside.first = squares[60];//e8
        black_castle_kingside.second = squares[62];//g8

        TS_ASSERT_EQUALS(my_cb.IsLegalMove(black_castle_queenside), true);
        TS_ASSERT_EQUALS(my_cb.IsLegalMove(black_castle_kingside), true);

        //make the move
        my_cb.MakeThisMove(black_castle_kingside);

        //check piece position
        TS_ASSERT_EQUALS(squares[56]->GetPieceOnThisSquare(), slach::BLACK_ROOK);//a8
        TS_ASSERT_EQUALS(squares[57]->GetPieceOnThisSquare(), slach::NO_PIECE);//b8
        TS_ASSERT_EQUALS(squares[58]->GetPieceOnThisSquare(), slach::NO_PIECE);//c8
        TS_ASSERT_EQUALS(squares[59]->GetPieceOnThisSquare(), slach::NO_PIECE);//d8
        TS_ASSERT_EQUALS(squares[60]->GetPieceOnThisSquare(), slach::NO_PIECE);//e8
        TS_ASSERT_EQUALS(squares[61]->GetPieceOnThisSquare(), slach::BLACK_ROOK);//f8
        TS_ASSERT_EQUALS(squares[62]->GetPieceOnThisSquare(), slach::BLACK_KING);//g8
        TS_ASSERT_EQUALS(squares[63]->GetPieceOnThisSquare(), slach::NO_PIECE);//h8

        TS_ASSERT_EQUALS (my_cb.GetCurrentFenPosition(), "r4rk1/pppbqppp/2np1n2/2b1p3/2B1P3/2NP1N2/PPPBQPPP/R4RK1 w - - 6 9");
    }
};

#endif
