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


     //This test starts from a position where, after some moves played, both sides could castle.
     //Both sides then move their rooks back and forth thus progressively loosing castling rights
    void testCastlingRightsLosses(void)
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        std::vector<slach::Square* > squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(squares.size(), 64u);

        //some useful moves first
        slach::Move white_castle_kingside;
        white_castle_kingside.first = squares[4];//e1
        white_castle_kingside.second = squares[6];//g1

        slach::Move white_castle_queenside;
        white_castle_queenside.first = squares[4];//e1
        white_castle_queenside.second = squares[2];//c1

        slach::Move black_castle_kingside;
        black_castle_kingside.first = squares[60];//e8
        black_castle_kingside.second = squares[62];//g1

        slach::Move black_castle_queenside;
        black_castle_queenside.first = squares[60];//e8
        black_castle_queenside.second = squares[58];//c8

        //this position is stored in test/data/test_position_4.png for reference
        std::string all_castle_allowed = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K2R w KQkq - 6 8";
        my_cb.SetFenPosition(all_castle_allowed);

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(white_castle_kingside));
        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(white_castle_queenside));
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(black_castle_kingside));//could, but not his turn
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(black_castle_queenside));//could, but not his turn

        slach::Move q_rook_move_white;//loss of castling rights queenside
        q_rook_move_white.first = squares[0];//a1
        q_rook_move_white.second = squares[1];//b1

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(q_rook_move_white));
		my_cb.MakeThisMove(q_rook_move_white);

        std::string after_q_rook_move = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/1R2K2R b Kkq - 7 8";
        TS_ASSERT_EQUALS (my_cb.GetCurrentFenPosition(),after_q_rook_move);

        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(white_castle_kingside));//not his turn
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(white_castle_queenside));//not his turn
        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(black_castle_kingside));
        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(black_castle_queenside));

        //Black's turn, moves a8-b8
        slach::Move q_rook_move_black;//loss of castling rights queenside
        q_rook_move_black.first = squares[56];//a8
        q_rook_move_black.second = squares[57];//b8

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(q_rook_move_black));
		my_cb.MakeThisMove(q_rook_move_black);

        after_q_rook_move = "1r2k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/1R2K2R w Kk - 8 9";
        TS_ASSERT_EQUALS (my_cb.GetCurrentFenPosition(),after_q_rook_move);

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(white_castle_kingside));
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(white_castle_queenside));//rook not in place
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(black_castle_kingside));//not his turn
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(black_castle_queenside));//not his turn

        //white's turn, moves rook back to a1
        slach::Move rook_back_to_a1;
        rook_back_to_a1.first = squares[1];//b1
        rook_back_to_a1.second = squares[0];//a1

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(rook_back_to_a1));
		my_cb.MakeThisMove(rook_back_to_a1);

        std::string after_rook_back_to_a1 = "1r2k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K2R b Kk - 9 9";
        TS_ASSERT_EQUALS (my_cb.GetCurrentFenPosition(),after_rook_back_to_a1);

        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(white_castle_kingside));//not his turn
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(white_castle_queenside));//not his turn
        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(black_castle_kingside));
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(black_castle_queenside));//rook not in place

        //black's move rook back to a8
        slach::Move rook_back_to_a8;
        rook_back_to_a8.first = squares[57];//b8
        rook_back_to_a8.second = squares[56];//a8

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(rook_back_to_a8));
		my_cb.MakeThisMove(rook_back_to_a8);

		std::string after_rook_back_to_a8 = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K2R w Kk - 10 10";
        TS_ASSERT_EQUALS (my_cb.GetCurrentFenPosition(),after_rook_back_to_a8);

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(white_castle_kingside));
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(white_castle_queenside));//rook in place but lost rights
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(black_castle_kingside));//not his turn
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(black_castle_queenside));//not his turn

        //white's move the kingside rook
        slach::Move k_rook_move_white;//loss of castling rights kingside
        k_rook_move_white.first = squares[7];//h1
        k_rook_move_white.second = squares[6];//g1

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(k_rook_move_white));
		my_cb.MakeThisMove(k_rook_move_white);

		std::string after_rook_g1 = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K1R1 b k - 11 10";
        TS_ASSERT_EQUALS (my_cb.GetCurrentFenPosition(),after_rook_g1);

        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(white_castle_kingside));//not his turn
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(white_castle_queenside));//not his turn
        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(black_castle_kingside));
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(black_castle_queenside));//rook in place but no rights

        //black's move his kingside rook
        slach::Move k_rook_move_black;//loss of castling rights kingside
        k_rook_move_black.first = squares[63];//h8
        k_rook_move_black.second = squares[62];//g8

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(k_rook_move_black));
		my_cb.MakeThisMove(k_rook_move_black);

		std::string after_rook_g8 = "r3k1r1/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K1R1 w - - 12 11";
        TS_ASSERT_EQUALS (my_cb.GetCurrentFenPosition(),after_rook_g8);

        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(white_castle_kingside));//rook not in place
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(white_castle_queenside));//rook in place but lost rights
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(black_castle_kingside));//not his turn
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(black_castle_queenside));//not his turn

        //white's move the kingside rook BACK to h1
        slach::Move k_rook_move_white_back_to_h1;
        k_rook_move_white_back_to_h1.first = squares[6];//g1
        k_rook_move_white_back_to_h1.second = squares[7];//h1

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(k_rook_move_white_back_to_h1));
		my_cb.MakeThisMove(k_rook_move_white_back_to_h1);

		std::string after_rook_back_to_h1 = "r3k1r1/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K2R b - - 13 11";
        TS_ASSERT_EQUALS (my_cb.GetCurrentFenPosition(),after_rook_back_to_h1);

        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(white_castle_kingside));//not his turn
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(white_castle_queenside));//not his turn
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(black_castle_kingside));//rook not in place
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(black_castle_queenside));//rook in place but no rights

        //black's move his kingside rook BACK to h8
        slach::Move k_rook_move_black_back_to_h8;
        k_rook_move_black_back_to_h8.first = squares[62];//g8
        k_rook_move_black_back_to_h8.second = squares[63];//h8

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(k_rook_move_black_back_to_h8));
		my_cb.MakeThisMove(k_rook_move_black_back_to_h8);

		std::string after_rook_back_to_h8 = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K2R w - - 14 12";
        TS_ASSERT_EQUALS (my_cb.GetCurrentFenPosition(),after_rook_back_to_h8);

        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(white_castle_kingside));//rook in place but lost rights
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(white_castle_queenside));//rook in place but lost rights
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(black_castle_kingside));//not his turn
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(black_castle_queenside));//not his turn

        //some move by white
        slach::Move a2_a3;
        a2_a3.first = squares[8];//a2
        a2_a3.second = squares[16];//a3

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(a2_a3));
		my_cb.MakeThisMove(a2_a3);

		std::string after_a2_a3 = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PPQ1PPP/R3K2R b - - 0 12";
        TS_ASSERT_EQUALS (my_cb.GetCurrentFenPosition(),after_a2_a3);

        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(white_castle_kingside));//not his turn
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(white_castle_queenside));//not his turn
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(black_castle_kingside));//rook in place but no rights
        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(black_castle_queenside));//rook in place but no rights

    }
};

#endif