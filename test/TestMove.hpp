#ifndef TESTMOVE_HPP_
#define TESTMOVE_HPP_

#include <cxxtest/TestSuite.h>
#include "Move.hpp"
#include "Square.hpp"
#include "ChessBoard.hpp"
#include "SlachTypes.hpp"

/**
 * Test suite to test the move class
 */

class TestMove : public CxxTest::TestSuite
{
  public :

    void TestBasicMove()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        std::vector<slach::Square* > squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(squares.size(), 64u);

        slach::Move b1_c3(squares[1],squares[18]);//b1-c3
        TS_ASSERT_EQUALS(b1_c3.GetOrigin()->GetIndexFromA1(), 1u);
        TS_ASSERT_EQUALS(b1_c3.GetDestination()->GetIndexFromA1(), 18u);

        TS_ASSERT_EQUALS(b1_c3.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(b1_c3.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(b1_c3.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(b1_c3.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(b1_c3.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(b1_c3.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(b1_c3.IsBlackPromoting(), false);
    }

    void TestCastling()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        for (unsigned i = 0; i < squares.size(); ++i)
        {
            if ((i==0u) || (i==7u))//white rooks
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_ROOK);
            }
            else if ((i==56u) || (i==63u))//black rooks
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_ROOK);
            }
            else if (i==4u)//white king
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_KING);
            }
            else if (i==60u)//black king
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_KING);
            }
            else
            {
                squares[i]->SetPieceOnThisSquare(slach::NO_PIECE);
            }
        }

        slach::Move white_castle_kingside(squares[4],squares[6]);//e1-g1
        slach::Move white_castle_queenside(squares[4], squares[2]);//e1-c1
        slach::Move black_castle_kingside(squares[60], squares[62]);//e8-g8
        slach::Move black_castle_queenside(squares[60], squares[58]);//e8-c8

        slach::Move white_king_moves(squares[4],squares[5]);//e1-f1
        slach::Move black_king_moves(squares[60], squares[61]);//e8-f8

        TS_ASSERT_EQUALS(white_castle_kingside.IsWhiteCastlingKingSide(), true);
        TS_ASSERT_EQUALS(white_castle_kingside.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(white_castle_kingside.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(white_castle_kingside.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(white_castle_kingside.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(white_castle_kingside.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(white_castle_kingside.IsBlackPromoting(), false);

        TS_ASSERT_EQUALS(white_castle_queenside.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(white_castle_queenside.IsWhiteCastlingQueenSide(), true);
        TS_ASSERT_EQUALS(white_castle_queenside.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(white_castle_queenside.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(white_castle_queenside.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(white_castle_queenside.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(white_castle_queenside.IsBlackPromoting(), false);

        TS_ASSERT_EQUALS(black_castle_kingside.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_castle_kingside.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_castle_kingside.IsBlackCastlingKingSide(), true);
        TS_ASSERT_EQUALS(black_castle_kingside.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_castle_kingside.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(black_castle_kingside.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(black_castle_kingside.IsBlackPromoting(), false);

        TS_ASSERT_EQUALS(black_castle_queenside.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_castle_queenside.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_castle_queenside.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_castle_queenside.IsBlackCastlingQueenSide(), true);
        TS_ASSERT_EQUALS(black_castle_queenside.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(black_castle_queenside.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(black_castle_queenside.IsBlackPromoting(), false);
    }

    void TestPseudoCastling()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        for (unsigned i = 0; i < squares.size(); ++i)
        {
            if (i==4u)//white rook on e1, fake castling
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_ROOK);
            }
            else if (i==60u)//black rook on e8, fake castling
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_ROOK);
            }
            else
            {
                squares[i]->SetPieceOnThisSquare(slach::NO_PIECE);
            }
        }

        slach::Move fake_white_castle_kingside(squares[4],squares[6]);//e1-g1
        slach::Move fake_white_castle_queenside(squares[4], squares[2]);//e1-c1
        slach::Move fake_black_castle_kingside(squares[60], squares[62]);//e8-g8
        slach::Move fake_black_castle_queenside(squares[60], squares[58]);//e8-c8

        TS_ASSERT_EQUALS(fake_white_castle_kingside.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(fake_white_castle_kingside.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(fake_white_castle_kingside.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(fake_white_castle_kingside.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(fake_white_castle_kingside.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(fake_white_castle_kingside.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(fake_white_castle_kingside.IsBlackPromoting(), false);

        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsBlackPromoting(), false);

        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsBlackPromoting(), false);

        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsBlackPromoting(), false);
    }

    void TestPromotions()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        for (unsigned i = 0; i < squares.size(); ++i)
        {
            if (i==8u)//white pawn on a2
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_PAWN);
            }
            else if (i==9u)//black pawn on b2, about to promote
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_PAWN);
            }
            else if (i==48u)//white pawn on a7, about to promote
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_PAWN);
            }
            else if(i==49u)//black pawn on b7
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_PAWN);
            }
            else
            {
                squares[i]->SetPieceOnThisSquare(slach::NO_PIECE);
            }
        }

        slach::Move white_promotes_a7_a8(squares[48],squares[56]);//a7-a8
        slach::Move white_pawn_move(squares[8], squares[16]);//a2-a3
        slach::Move black_pawn_promotes_b2_b1(squares[9u], squares[1u]);//b2-b1
        slach::Move black_pawn_moves(squares[49], squares[41]);//b7-b6

        TS_ASSERT_EQUALS(white_promotes_a7_a8.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(white_promotes_a7_a8.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(white_promotes_a7_a8.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(white_promotes_a7_a8.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(white_promotes_a7_a8.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(white_promotes_a7_a8.IsWhitePromoting(), true);
        TS_ASSERT_EQUALS(white_promotes_a7_a8.IsBlackPromoting(), false);

        TS_ASSERT_EQUALS(white_pawn_move.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsBlackPromoting(), false);

        TS_ASSERT_EQUALS(black_pawn_promotes_b2_b1.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_pawn_promotes_b2_b1.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_pawn_promotes_b2_b1.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_pawn_promotes_b2_b1.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_pawn_promotes_b2_b1.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(black_pawn_promotes_b2_b1.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(black_pawn_promotes_b2_b1.IsBlackPromoting(), true);

        TS_ASSERT_EQUALS(black_pawn_moves.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsBlackPromoting(), false);
    }

    void TestPseudoPromotions()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        for (unsigned i = 0; i < squares.size(); ++i)
        {
            if (i==9u)//black ROOK on b2, about to promote
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_ROOK);
            }
            else if (i==48u)//white pawn on a7, about to promote
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_ROOK);
            }
            else
            {
                squares[i]->SetPieceOnThisSquare(slach::NO_PIECE);
            }
        }

        slach::Move white_pseudo_promotes_a7_a8(squares[48],squares[56]);//a7-a8
        slach::Move black_pseudo_promotes_b2_b1(squares[9u], squares[1u]);//b2-b1

        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.IsBlackPromoting(), false);

        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsBlackPromoting(), false);

    }
};
#endif //TESTMOVE_HPP_
