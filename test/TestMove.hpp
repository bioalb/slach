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
        TS_ASSERT_EQUALS(b1_c3.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(b1_c3.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(b1_c3.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(b1_c3.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(b1_c3.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(b1_c3.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(b1_c3.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(b1_c3.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(b1_c3.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(b1_c3.GetMoveInAlgebraicFormat(), "Nc3");

        //cover the default constructor
        slach::Move def_constr;
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
        TS_ASSERT_EQUALS(white_castle_kingside.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(white_castle_kingside.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(white_castle_kingside.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(white_castle_kingside.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(white_castle_kingside.IsWhiteKingMoving(), true);
        TS_ASSERT_EQUALS(white_castle_kingside.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(white_castle_kingside.DoesMoveRequireSpecialGuiHandling(), true);
        TS_ASSERT_EQUALS(white_castle_kingside.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(white_castle_kingside.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(white_castle_kingside.GetMoveInAlgebraicFormat(), "O-O");

        TS_ASSERT_EQUALS(white_castle_queenside.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(white_castle_queenside.IsWhiteCastlingQueenSide(), true);
        TS_ASSERT_EQUALS(white_castle_queenside.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(white_castle_queenside.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(white_castle_queenside.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(white_castle_queenside.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(white_castle_queenside.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(white_castle_queenside.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(white_castle_queenside.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(white_castle_queenside.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(white_castle_queenside.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(white_castle_queenside.IsWhiteKingMoving(), true);
        TS_ASSERT_EQUALS(white_castle_queenside.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(white_castle_queenside.DoesMoveRequireSpecialGuiHandling(), true);
        TS_ASSERT_EQUALS(white_castle_queenside.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(white_castle_queenside.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(white_castle_queenside.GetMoveInAlgebraicFormat(), "O-O-O");

        TS_ASSERT_EQUALS(black_castle_kingside.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_castle_kingside.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_castle_kingside.IsBlackCastlingKingSide(), true);
        TS_ASSERT_EQUALS(black_castle_kingside.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_castle_kingside.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(black_castle_kingside.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(black_castle_kingside.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(black_castle_kingside.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(black_castle_kingside.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(black_castle_kingside.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(black_castle_kingside.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(black_castle_kingside.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(black_castle_kingside.IsBlackKingMoving(), true);
        TS_ASSERT_EQUALS(black_castle_kingside.DoesMoveRequireSpecialGuiHandling(), true);
        TS_ASSERT_EQUALS(black_castle_kingside.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(black_castle_kingside.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(black_castle_kingside.GetMoveInAlgebraicFormat(), "O-O");

        TS_ASSERT_EQUALS(black_castle_queenside.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_castle_queenside.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_castle_queenside.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_castle_queenside.IsBlackCastlingQueenSide(), true);
        TS_ASSERT_EQUALS(black_castle_queenside.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(black_castle_queenside.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(black_castle_queenside.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(black_castle_queenside.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(black_castle_queenside.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(black_castle_queenside.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(black_castle_queenside.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(black_castle_queenside.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(black_castle_queenside.IsBlackKingMoving(), true);
        TS_ASSERT_EQUALS(black_castle_queenside.DoesMoveRequireSpecialGuiHandling(), true);
        TS_ASSERT_EQUALS(black_castle_queenside.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(black_castle_queenside.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(black_castle_queenside.GetMoveInAlgebraicFormat(), "O-O-O");
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
        TS_ASSERT_EQUALS(fake_white_castle_kingside.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(fake_white_castle_kingside.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(fake_white_castle_kingside.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(fake_white_castle_kingside.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(fake_white_castle_kingside.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(fake_white_castle_kingside.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(fake_white_castle_kingside.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(fake_white_castle_kingside.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(fake_white_castle_kingside.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(fake_white_castle_kingside.GetMoveInAlgebraicFormat(), "Rg1");

        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(fake_white_castle_queenside.GetMoveInAlgebraicFormat(), "Rc1");

        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(fake_black_castle_kingside.GetMoveInAlgebraicFormat(), "Rg8");

        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(fake_black_castle_queenside.GetMoveInAlgebraicFormat(), "Rc8");
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

        slach::Move white_promotes(squares[48],squares[56]);//a7-a8
        TS_ASSERT_EQUALS(white_promotes.GetPromotionPieceCode(), "Q");//default value
        slach::Move white_pawn_move(squares[8], squares[16]);//a2-a3
        slach::Move black_promotes(squares[9u], squares[1u]);//b2-b1
        black_promotes.SetPromotionPiece(slach::BLACK_KNIGHT);
        TS_ASSERT_EQUALS(black_promotes.GetPromotionPieceCode(), "N");
        slach::Move black_pawn_moves(squares[49], squares[41]);//b7-b6

        TS_ASSERT_EQUALS(white_promotes.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(white_promotes.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(white_promotes.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(white_promotes.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(white_promotes.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(white_promotes.IsWhitePromoting(), true);
        TS_ASSERT_EQUALS(white_promotes.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(white_promotes.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(white_promotes.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(white_promotes.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(white_promotes.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(white_promotes.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(white_promotes.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(white_promotes.DoesMoveRequireSpecialGuiHandling(), true);
        TS_ASSERT_EQUALS(white_promotes.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(white_promotes.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(white_promotes.GetMoveInAlgebraicFormat(), "a8=Q");

        TS_ASSERT_EQUALS(white_pawn_move.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(white_pawn_move.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(white_pawn_move.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(white_pawn_move.GetMoveInAlgebraicFormat(), "a3");

        TS_ASSERT_EQUALS(black_promotes.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_promotes.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_promotes.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_promotes.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_promotes.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(black_promotes.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(black_promotes.IsBlackPromoting(), true);
        TS_ASSERT_EQUALS(black_promotes.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(black_promotes.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(black_promotes.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(black_promotes.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(black_promotes.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(black_promotes.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(black_promotes.DoesMoveRequireSpecialGuiHandling(), true);
        TS_ASSERT_EQUALS(black_promotes.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(black_promotes.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(black_promotes.GetMoveInAlgebraicFormat(), "b1=N");

        TS_ASSERT_EQUALS(black_pawn_moves.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(black_pawn_moves.GetMoveInAlgebraicFormat(), "b6");
    }

    void TestPseudoPromotions()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        for (unsigned i = 0; i < squares.size(); ++i)
        {
            if (i==9u)//black ROOK on b2, about to "promote" (no promotion actually, it's a rook!)
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_ROOK);
            }
            else if (i==48u)//white pawn on a7, about to "promote" (no promotion actually, it's a rook!)
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
        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(white_pseudo_promotes_a7_a8.GetMoveInAlgebraicFormat(), "Ra8");


        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(black_pseudo_promotes_b2_b1.GetMoveInAlgebraicFormat(), "Rb1");
    }

    void TestCornerRookMoves()
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

        slach::Move a1_a2(squares[0],squares[8]);
        slach::Move h1_h2(squares[7], squares[15]);
        slach::Move a8_a7(squares[56], squares[48]);
        slach::Move h8_g8(squares[63], squares[62]);
        slach::Move a8_a1(squares[56], squares[0]);
        slach::Move a1_a8(squares[0], squares[56]);

        TS_ASSERT_EQUALS(a1_a2.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(a1_a2.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(a1_a2.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(a1_a2.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(a1_a2.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(a1_a2.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(a1_a2.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(a1_a2.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(a1_a2.IsQueenSideWhiteRookMoving(), true);
        TS_ASSERT_EQUALS(a1_a2.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(a1_a2.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(a1_a2.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(a1_a2.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(a1_a2.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(a1_a2.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(a1_a2.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(a1_a2.GetMoveInAlgebraicFormat(), "Ra2");

        TS_ASSERT_EQUALS(h1_h2.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(h1_h2.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(h1_h2.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(h1_h2.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(h1_h2.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(h1_h2.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(h1_h2.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(h1_h2.IsKingSideWhiteRookMoving(), true);
        TS_ASSERT_EQUALS(h1_h2.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(h1_h2.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(h1_h2.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(h1_h2.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(h1_h2.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(h1_h2.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(h1_h2.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(h1_h2.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(h1_h2.GetMoveInAlgebraicFormat(), "Rh2");

        TS_ASSERT_EQUALS(a8_a7.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(a8_a7.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(a8_a7.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(a8_a7.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(a8_a7.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(a8_a7.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(a8_a7.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(a8_a7.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(a8_a7.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(a8_a7.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(a8_a7.IsQueenSideBlackRookMoving(), true);
        TS_ASSERT_EQUALS(a8_a7.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(a8_a7.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(a8_a7.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(a8_a7.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(a8_a7.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(a8_a7.GetMoveInAlgebraicFormat(), "Ra7");

        TS_ASSERT_EQUALS(h8_g8.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(h8_g8.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(h8_g8.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(h8_g8.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(h8_g8.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(h8_g8.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(h8_g8.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(h8_g8.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(h8_g8.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(h8_g8.IsKingSideBlackRookMoving(), true);
        TS_ASSERT_EQUALS(h8_g8.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(h8_g8.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(h8_g8.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(h8_g8.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(h8_g8.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(h8_g8.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(h8_g8.GetMoveInAlgebraicFormat(), "Rg8");

        TS_ASSERT_EQUALS(a8_a1.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(a8_a1.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(a8_a1.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(a8_a1.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(a8_a1.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(a8_a1.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(a8_a1.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(a8_a1.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(a8_a1.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(a8_a1.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(a8_a1.IsQueenSideBlackRookMoving(), true);
        TS_ASSERT_EQUALS(a8_a1.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(a8_a1.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(a8_a1.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(a8_a1.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(a8_a1.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(a8_a1.GetMoveInAlgebraicFormat(), "Rxa1");

        TS_ASSERT_EQUALS(a1_a8.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(a1_a8.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(a1_a8.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(a1_a8.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(a1_a8.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(a1_a8.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(a1_a8.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(a1_a8.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(a1_a8.IsQueenSideWhiteRookMoving(), true);
        TS_ASSERT_EQUALS(a1_a8.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(a1_a8.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(a1_a8.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(a1_a8.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(a1_a8.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(a1_a8.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(a1_a8.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(a1_a8.GetMoveInAlgebraicFormat(), "Rxa8");
    }

    void TestCornerRookMovesWithAmbiguity()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        for (unsigned i = 0; i < squares.size(); ++i)
        {
            if ((i==0u) || (i==7u) || (i==24u))//white rooks, a1, h1 and a5
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_ROOK);
            }
            else if ((i==56u) || (i==63u))//black rooks
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_ROOK);
            }
            else if (i==12u)//white king, e2
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_KING);
            }
            else if (i==54u)//black king, g7
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_KING);
            }
            else
            {
                squares[i]->SetPieceOnThisSquare(slach::NO_PIECE);
            }
        }

        slach::Move a1_b1(squares[0],squares[1]);//a1-b1, both white rooks can go to b1
        a1_b1.SetAmbiguityPrefix("a");
        slach::Move h1_b1(squares[7], squares[1]); // h1-b1  both white rooks can go to b1
        h1_b1.SetAmbiguityPrefix("h");
        slach::Move a5_a2(squares[24], squares[8]);// a5-a2 both rooks can go to a2
        a5_a2.SetAmbiguityPrefix("5");

        TS_ASSERT_EQUALS(a1_b1.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(a1_b1.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(a1_b1.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(a1_b1.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(a1_b1.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(a1_b1.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(a1_b1.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(a1_b1.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(a1_b1.IsQueenSideWhiteRookMoving(), true);
        TS_ASSERT_EQUALS(a1_b1.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(a1_b1.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(a1_b1.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(a1_b1.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(a1_b1.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(a1_b1.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(a1_b1.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(a1_b1.GetAmbiguityPrefix(), "a");
        TS_ASSERT_EQUALS(a1_b1.GetMoveInAlgebraicFormat(), "Rab1");

        TS_ASSERT_EQUALS(h1_b1.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(h1_b1.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(h1_b1.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(h1_b1.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(h1_b1.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(h1_b1.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(h1_b1.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(h1_b1.IsKingSideWhiteRookMoving(), true);
        TS_ASSERT_EQUALS(h1_b1.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(h1_b1.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(h1_b1.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(h1_b1.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(h1_b1.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(h1_b1.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(h1_b1.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(h1_b1.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(h1_b1.GetMoveInAlgebraicFormat(), "Rhb1");

        TS_ASSERT_EQUALS(a5_a2.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(a5_a2.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(a5_a2.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(a5_a2.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(a5_a2.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(a5_a2.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(a5_a2.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(a5_a2.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(a5_a2.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(a5_a2.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(a5_a2.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(a5_a2.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(a5_a2.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(a5_a2.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(a5_a2.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(a5_a2.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(a5_a2.GetMoveInAlgebraicFormat(), "R5a2");
    }

    void TestPseudoCornerRookMoves()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        for (unsigned i = 0; i < squares.size(); ++i)
        {
            if ((i==0u) || (i==7u))//white queen, so we make sure the method flags only rooks
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_QUEEN);
            }
            else if ((i==56u) || (i==63u))//black queens so we make sure the method flags only rooks
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_QUEEN);
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

        slach::Move a1_a2(squares[0],squares[8]);
        slach::Move h1_h2(squares[7], squares[15]);
        slach::Move a8_a7(squares[56], squares[48]);
        slach::Move h8_g8(squares[63], squares[62]);
        slach::Move e1_e2(squares[4], squares[12]);
        slach::Move e8_f8(squares[60], squares[61]);

        TS_ASSERT_EQUALS(a1_a2.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(a1_a2.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(a1_a2.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(a1_a2.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(a1_a2.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(a1_a2.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(a1_a2.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(a1_a2.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(a1_a2.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(a1_a2.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(a1_a2.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(a1_a2.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(a1_a2.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(a1_a2.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(a1_a2.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(a1_a2.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(a1_a2.GetMoveInAlgebraicFormat(), "Qa2");

        TS_ASSERT_EQUALS(h1_h2.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(h1_h2.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(h1_h2.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(h1_h2.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(h1_h2.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(h1_h2.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(h1_h2.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(h1_h2.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(h1_h2.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(h1_h2.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(h1_h2.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(h1_h2.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(h1_h2.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(h1_h2.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(h1_h2.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(h1_h2.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(h1_h2.GetMoveInAlgebraicFormat(), "Qh2");

        TS_ASSERT_EQUALS(a8_a7.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(a8_a7.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(a8_a7.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(a8_a7.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(a8_a7.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(a8_a7.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(a8_a7.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(a8_a7.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(a8_a7.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(a8_a7.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(a8_a7.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(a8_a7.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(a8_a7.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(a8_a7.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(a8_a7.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(a8_a7.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(a8_a7.GetMoveInAlgebraicFormat(), "Qa7");

        TS_ASSERT_EQUALS(h8_g8.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(h8_g8.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(h8_g8.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(h8_g8.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(h8_g8.IsSpecialMove(), false);
        TS_ASSERT_EQUALS(h8_g8.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(h8_g8.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(h8_g8.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(h8_g8.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(h8_g8.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(h8_g8.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(h8_g8.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(h8_g8.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(h8_g8.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(h8_g8.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(h8_g8.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(h8_g8.GetMoveInAlgebraicFormat(), "Qg8");

        TS_ASSERT_EQUALS(e8_f8.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(e8_f8.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(e8_f8.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(e8_f8.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(e8_f8.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(e8_f8.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(e8_f8.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(e8_f8.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(e8_f8.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(e8_f8.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(e8_f8.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(e8_f8.IsWhiteKingMoving(), false);
        TS_ASSERT_EQUALS(e8_f8.IsBlackKingMoving(), true);
        TS_ASSERT_EQUALS(e8_f8.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(e8_f8.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(e8_f8.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(e8_f8.GetMoveInAlgebraicFormat(), "Kf8");

        TS_ASSERT_EQUALS(e1_e2.IsWhiteCastlingKingSide(), false);
        TS_ASSERT_EQUALS(e1_e2.IsWhiteCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(e1_e2.IsBlackCastlingKingSide(), false);
        TS_ASSERT_EQUALS(e1_e2.IsBlackCastlingQueenSide(), false);
        TS_ASSERT_EQUALS(e1_e2.IsSpecialMove(), true);
        TS_ASSERT_EQUALS(e1_e2.IsWhitePromoting(), false);
        TS_ASSERT_EQUALS(e1_e2.IsBlackPromoting(), false);
        TS_ASSERT_EQUALS(e1_e2.IsKingSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(e1_e2.IsQueenSideWhiteRookMoving(), false);
        TS_ASSERT_EQUALS(e1_e2.IsKingSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(e1_e2.IsQueenSideBlackRookMoving(), false);
        TS_ASSERT_EQUALS(e1_e2.IsWhiteKingMoving(), true);
        TS_ASSERT_EQUALS(e1_e2.IsBlackKingMoving(), false);
        TS_ASSERT_EQUALS(e1_e2.DoesMoveRequireSpecialGuiHandling(), false);
        TS_ASSERT_EQUALS(e1_e2.IsBlackCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(e1_e2.IsWhiteCapturingEnPassant(), false);
        TS_ASSERT_EQUALS(e1_e2.GetMoveInAlgebraicFormat(), "Ke2");
    }


    void TestEnPassant()
	{
		slach::ChessBoard my_cb;
		my_cb.SetupChessBoard();
		std::vector<slach::Square* > squares = my_cb.GetSquares();

		for (unsigned i = 0; i < squares.size(); ++i)
		{
			if (i==32u)//white pawn on a5 - ready to capture en passant on b6
			{
				squares[i]->SetPieceOnThisSquare(slach::WHITE_PAWN);
			}
			else if (i==33u)//black pawn on b5 (say, just moved from b7)
			{
				squares[i]->SetPieceOnThisSquare(slach::BLACK_PAWN);
			}
			else if (i==28u)//white pawn on e4 (say, just moved from e2)
			{
				squares[i]->SetPieceOnThisSquare(slach::WHITE_PAWN);
			}
			else if (i==29u)//black pawn on f4 - ready to capture enpassant on e3
			{
				squares[i]->SetPieceOnThisSquare(slach::BLACK_PAWN);
			}
			else if (i==22u)//white queen on g3 - ready to be captured by black pawn on f4
			{
				squares[i]->SetPieceOnThisSquare(slach::WHITE_QUEEN);
			}
			else if (i==46u)//white pawn on g6 (for normal capture)
			{
				squares[i]->SetPieceOnThisSquare(slach::WHITE_PAWN);
			}
			else if (i==53)//black bishop on f7 - ready to be captured by white pawn on g6
			{
				squares[i]->SetPieceOnThisSquare(slach::BLACK_BISHOP);
			}


			else
			{
				squares[i]->SetPieceOnThisSquare(slach::NO_PIECE);
			}
		}

		slach::Move white_captures_enpassant(squares[32],squares[41]);//a5-b6 (enpassant)
		slach::Move black_captures_enpassant(squares[29], squares[20]);//f4-e3 (enpassant)

		slach::Move white_regular_capture(squares[46],squares[53]);//g6-f7
		slach::Move black_regular_capture(squares[29], squares[22]);//f4-g3

		TS_ASSERT_EQUALS(white_captures_enpassant.IsWhiteCastlingKingSide(), false);
		TS_ASSERT_EQUALS(white_captures_enpassant.IsWhiteCastlingQueenSide(), false);
		TS_ASSERT_EQUALS(white_captures_enpassant.IsBlackCastlingKingSide(), false);
		TS_ASSERT_EQUALS(white_captures_enpassant.IsBlackCastlingQueenSide(), false);
		TS_ASSERT_EQUALS(white_captures_enpassant.IsSpecialMove(), false);
		TS_ASSERT_EQUALS(white_captures_enpassant.IsWhitePromoting(), false);
		TS_ASSERT_EQUALS(white_captures_enpassant.IsBlackPromoting(), false);
		TS_ASSERT_EQUALS(white_captures_enpassant.IsKingSideWhiteRookMoving(), false);
		TS_ASSERT_EQUALS(white_captures_enpassant.IsQueenSideWhiteRookMoving(), false);
		TS_ASSERT_EQUALS(white_captures_enpassant.IsKingSideBlackRookMoving(), false);
		TS_ASSERT_EQUALS(white_captures_enpassant.IsQueenSideBlackRookMoving(), false);
		TS_ASSERT_EQUALS(white_captures_enpassant.IsWhiteKingMoving(), false);
		TS_ASSERT_EQUALS(white_captures_enpassant.IsBlackKingMoving(), false);
		TS_ASSERT_EQUALS(white_captures_enpassant.DoesMoveRequireSpecialGuiHandling(), true);
		TS_ASSERT_EQUALS(white_captures_enpassant.IsBlackCapturingEnPassant(), false);
		TS_ASSERT_EQUALS(white_captures_enpassant.IsWhiteCapturingEnPassant(), true);
		TS_ASSERT_EQUALS(white_captures_enpassant.GetMoveInAlgebraicFormat(), "axb6");

		TS_ASSERT_EQUALS(black_captures_enpassant.IsWhiteCastlingKingSide(), false);
		TS_ASSERT_EQUALS(black_captures_enpassant.IsWhiteCastlingQueenSide(), false);
		TS_ASSERT_EQUALS(black_captures_enpassant.IsBlackCastlingKingSide(), false);
		TS_ASSERT_EQUALS(black_captures_enpassant.IsBlackCastlingQueenSide(), false);
		TS_ASSERT_EQUALS(black_captures_enpassant.IsSpecialMove(), false);
		TS_ASSERT_EQUALS(black_captures_enpassant.IsWhitePromoting(), false);
		TS_ASSERT_EQUALS(black_captures_enpassant.IsBlackPromoting(), false);
		TS_ASSERT_EQUALS(black_captures_enpassant.IsKingSideWhiteRookMoving(), false);
		TS_ASSERT_EQUALS(black_captures_enpassant.IsQueenSideWhiteRookMoving(), false);
		TS_ASSERT_EQUALS(black_captures_enpassant.IsKingSideBlackRookMoving(), false);
		TS_ASSERT_EQUALS(black_captures_enpassant.IsQueenSideBlackRookMoving(), false);
		TS_ASSERT_EQUALS(black_captures_enpassant.IsWhiteKingMoving(), false);
		TS_ASSERT_EQUALS(black_captures_enpassant.IsBlackKingMoving(), false);
		TS_ASSERT_EQUALS(black_captures_enpassant.DoesMoveRequireSpecialGuiHandling(), true);
		TS_ASSERT_EQUALS(black_captures_enpassant.IsBlackCapturingEnPassant(), true);
		TS_ASSERT_EQUALS(black_captures_enpassant.IsWhiteCapturingEnPassant(), false);
		TS_ASSERT_EQUALS(black_captures_enpassant.GetMoveInAlgebraicFormat(), "fxe3");

		TS_ASSERT_EQUALS(white_regular_capture.IsWhiteCastlingKingSide(), false);
		TS_ASSERT_EQUALS(white_regular_capture.IsWhiteCastlingQueenSide(), false);
		TS_ASSERT_EQUALS(white_regular_capture.IsBlackCastlingKingSide(), false);
		TS_ASSERT_EQUALS(white_regular_capture.IsBlackCastlingQueenSide(), false);
		TS_ASSERT_EQUALS(white_regular_capture.IsSpecialMove(), false);
		TS_ASSERT_EQUALS(white_regular_capture.IsWhitePromoting(), false);
		TS_ASSERT_EQUALS(white_regular_capture.IsBlackPromoting(), false);
		TS_ASSERT_EQUALS(white_regular_capture.IsKingSideWhiteRookMoving(), false);
		TS_ASSERT_EQUALS(white_regular_capture.IsQueenSideWhiteRookMoving(), false);
		TS_ASSERT_EQUALS(white_regular_capture.IsKingSideBlackRookMoving(), false);
		TS_ASSERT_EQUALS(white_regular_capture.IsQueenSideBlackRookMoving(), false);
		TS_ASSERT_EQUALS(white_regular_capture.IsWhiteKingMoving(), false);
		TS_ASSERT_EQUALS(white_regular_capture.IsBlackKingMoving(), false);
		TS_ASSERT_EQUALS(white_regular_capture.DoesMoveRequireSpecialGuiHandling(), false);
		TS_ASSERT_EQUALS(white_regular_capture.IsBlackCapturingEnPassant(), false);
		TS_ASSERT_EQUALS(white_regular_capture.IsWhiteCapturingEnPassant(), false);
		TS_ASSERT_EQUALS(white_regular_capture.GetMoveInAlgebraicFormat(), "gxf7");

		TS_ASSERT_EQUALS(black_regular_capture.IsWhiteCastlingKingSide(), false);
		TS_ASSERT_EQUALS(black_regular_capture.IsWhiteCastlingQueenSide(), false);
		TS_ASSERT_EQUALS(black_regular_capture.IsBlackCastlingKingSide(), false);
		TS_ASSERT_EQUALS(black_regular_capture.IsBlackCastlingQueenSide(), false);
		TS_ASSERT_EQUALS(black_regular_capture.IsSpecialMove(), false);
		TS_ASSERT_EQUALS(black_regular_capture.IsWhitePromoting(), false);
		TS_ASSERT_EQUALS(black_regular_capture.IsBlackPromoting(), false);
		TS_ASSERT_EQUALS(black_regular_capture.IsKingSideWhiteRookMoving(), false);
		TS_ASSERT_EQUALS(black_regular_capture.IsQueenSideWhiteRookMoving(), false);
		TS_ASSERT_EQUALS(black_regular_capture.IsKingSideBlackRookMoving(), false);
		TS_ASSERT_EQUALS(black_regular_capture.IsQueenSideBlackRookMoving(), false);
		TS_ASSERT_EQUALS(black_regular_capture.IsWhiteKingMoving(), false);
		TS_ASSERT_EQUALS(black_regular_capture.IsBlackKingMoving(), false);
		TS_ASSERT_EQUALS(black_regular_capture.DoesMoveRequireSpecialGuiHandling(), false);
		TS_ASSERT_EQUALS(black_regular_capture.IsBlackCapturingEnPassant(), false);
		TS_ASSERT_EQUALS(black_regular_capture.IsWhiteCapturingEnPassant(), false);
		TS_ASSERT_EQUALS(black_regular_capture.GetMoveInAlgebraicFormat(), "fxg3");
	}

    void TestRegularknightMoveFromSan()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        slach::Move knightf3("Nf3", squares, slach::WHITE);

        TS_ASSERT_EQUALS(knightf3.GetOrigin()->GetFile(), 'g');
        TS_ASSERT_EQUALS(knightf3.GetOrigin()->GetRank(), '1');
        TS_ASSERT_EQUALS(knightf3.GetDestination()->GetFile(), 'f');
        TS_ASSERT_EQUALS(knightf3.GetDestination()->GetRank(), '3');
    }

    void TestMovesFromSanWhite()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        //this position is stored in test/data/test_position_4.png for reference
        std::string test_pos_4 = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K2R w KQkq - 6 8";
        my_cb.SetFenPosition(test_pos_4);
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        slach::Move ds_bishop_h4("Bh4", squares, slach::WHITE);

        TS_ASSERT_EQUALS(ds_bishop_h4.GetOrigin()->GetFile(), 'g');
        TS_ASSERT_EQUALS(ds_bishop_h4.GetOrigin()->GetRank(), '5');
        TS_ASSERT_EQUALS(ds_bishop_h4.GetDestination()->GetFile(), 'h');
        TS_ASSERT_EQUALS(ds_bishop_h4.GetDestination()->GetRank(), '4');

        slach::Move ls_bishop_b3("Bb3", squares, slach::WHITE);

        TS_ASSERT_EQUALS(ls_bishop_b3.GetOrigin()->GetFile(), 'c');
        TS_ASSERT_EQUALS(ls_bishop_b3.GetOrigin()->GetRank(), '4');
        TS_ASSERT_EQUALS(ls_bishop_b3.GetDestination()->GetFile(), 'b');
        TS_ASSERT_EQUALS(ls_bishop_b3.GetDestination()->GetRank(), '3');

        slach::Move Queen_e2("Qe2", squares, slach::WHITE);

        TS_ASSERT_EQUALS(Queen_e2.GetOrigin()->GetFile(), 'd');
        TS_ASSERT_EQUALS(Queen_e2.GetOrigin()->GetRank(), '2');
        TS_ASSERT_EQUALS(Queen_e2.GetDestination()->GetFile(), 'e');
        TS_ASSERT_EQUALS(Queen_e2.GetDestination()->GetRank(), '2');

        slach::Move rook_g1("Rg1", squares, slach::WHITE);

        TS_ASSERT_EQUALS(rook_g1.GetOrigin()->GetFile(), 'h');
        TS_ASSERT_EQUALS(rook_g1.GetOrigin()->GetRank(), '1');
        TS_ASSERT_EQUALS(rook_g1.GetDestination()->GetFile(), 'g');
        TS_ASSERT_EQUALS(rook_g1.GetDestination()->GetRank(), '1');

        slach::Move king_d1("Kd1", squares, slach::WHITE);

        TS_ASSERT_EQUALS(king_d1.GetOrigin()->GetFile(), 'e');
        TS_ASSERT_EQUALS(king_d1.GetOrigin()->GetRank(), '1');
        TS_ASSERT_EQUALS(king_d1.GetDestination()->GetFile(), 'd');
        TS_ASSERT_EQUALS(king_d1.GetDestination()->GetRank(), '1');

        slach::Move bishop_takes_f6("Bxf6", squares, slach::WHITE);

        TS_ASSERT_EQUALS(bishop_takes_f6.GetOrigin()->GetFile(), 'g');
        TS_ASSERT_EQUALS(bishop_takes_f6.GetOrigin()->GetRank(), '5');
        TS_ASSERT_EQUALS(bishop_takes_f6.GetDestination()->GetFile(), 'f');
        TS_ASSERT_EQUALS(bishop_takes_f6.GetDestination()->GetRank(), '6');

        slach::Move castle("O-O", squares, slach::WHITE);

         TS_ASSERT_EQUALS(castle.GetOrigin()->GetFile(), 'e');
         TS_ASSERT_EQUALS(castle.GetOrigin()->GetRank(), '1');
         TS_ASSERT_EQUALS(castle.GetDestination()->GetFile(), 'g');
         TS_ASSERT_EQUALS(castle.GetDestination()->GetRank(), '1');
         TS_ASSERT_EQUALS(castle.DoesMoveRequireSpecialGuiHandling(), true);
         TS_ASSERT_EQUALS(castle.IsWhiteCastlingKingSide(), true);

         slach::Move castle_q("O-O-O", squares, slach::WHITE);

          TS_ASSERT_EQUALS(castle_q.GetOrigin()->GetFile(), 'e');
          TS_ASSERT_EQUALS(castle_q.GetOrigin()->GetRank(), '1');
          TS_ASSERT_EQUALS(castle_q.GetDestination()->GetFile(), 'c');
          TS_ASSERT_EQUALS(castle_q.GetDestination()->GetRank(), '1');
          TS_ASSERT_EQUALS(castle_q.DoesMoveRequireSpecialGuiHandling(), true);
          TS_ASSERT_EQUALS(castle_q.IsWhiteCastlingQueenSide(), true);
    }

    void TestPawnMovesFromSanWhite()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        //this position is stored in test/data/test_position_4.png for reference
        std::string test_pos_4 = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K2R w KQkq - 6 8";
        my_cb.SetFenPosition(test_pos_4);
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        slach::Move h4("h4", squares, slach::WHITE);

        TS_ASSERT_EQUALS(h4.GetOrigin()->GetFile(), 'h');
        TS_ASSERT_EQUALS(h4.GetOrigin()->GetRank(), '2');
        TS_ASSERT_EQUALS(h4.GetDestination()->GetFile(), 'h');
        TS_ASSERT_EQUALS(h4.GetDestination()->GetRank(), '4');

        slach::Move h3("h3", squares, slach::WHITE);

        TS_ASSERT_EQUALS(h3.GetOrigin()->GetFile(), 'h');
        TS_ASSERT_EQUALS(h3.GetOrigin()->GetRank(), '2');
        TS_ASSERT_EQUALS(h3.GetDestination()->GetFile(), 'h');
        TS_ASSERT_EQUALS(h3.GetDestination()->GetRank(), '3');

        slach::Move d4("d4", squares, slach::WHITE);

        TS_ASSERT_EQUALS(d4.GetOrigin()->GetFile(), 'd');
        TS_ASSERT_EQUALS(d4.GetOrigin()->GetRank(), '3');
        TS_ASSERT_EQUALS(d4.GetDestination()->GetFile(), 'd');
        TS_ASSERT_EQUALS(d4.GetDestination()->GetRank(), '4');
    }

    void TestMovesFromSanBlack()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        //this position is stored in test/data/test_position_4.png, but white has just moved a1-b1
        std::string test_pos_4_after_a1_b1 = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/1R2K2R b Kkq - 7 8";
        my_cb.SetFenPosition(test_pos_4_after_a1_b1);
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        slach::Move king_e7("Ke7", squares,slach::BLACK);
        TS_ASSERT_EQUALS(king_e7.GetOrigin()->GetFile(), 'e');
        TS_ASSERT_EQUALS(king_e7.GetOrigin()->GetRank(), '8');
        TS_ASSERT_EQUALS(king_e7.GetDestination()->GetFile(), 'e');
        TS_ASSERT_EQUALS(king_e7.GetDestination()->GetRank(), '7');

        slach::Move castle("O-O", squares, slach::BLACK);

        TS_ASSERT_EQUALS(castle.GetOrigin()->GetFile(), 'e');
        TS_ASSERT_EQUALS(castle.GetOrigin()->GetRank(), '8');
        TS_ASSERT_EQUALS(castle.GetDestination()->GetFile(), 'g');
        TS_ASSERT_EQUALS(castle.GetDestination()->GetRank(), '8');
        TS_ASSERT_EQUALS(castle.DoesMoveRequireSpecialGuiHandling(), true);
        TS_ASSERT_EQUALS(castle.IsBlackCastlingKingSide(), true);

        slach::Move castle_q("O-O-O", squares, slach::BLACK);

        TS_ASSERT_EQUALS(castle_q.GetOrigin()->GetFile(), 'e');
        TS_ASSERT_EQUALS(castle_q.GetOrigin()->GetRank(), '8');
        TS_ASSERT_EQUALS(castle_q.GetDestination()->GetFile(), 'c');
        TS_ASSERT_EQUALS(castle_q.GetDestination()->GetRank(), '8');
        TS_ASSERT_EQUALS(castle_q.DoesMoveRequireSpecialGuiHandling(), true);
        TS_ASSERT_EQUALS(castle_q.IsBlackCastlingQueenSide(), true);
    }

    void TestPawnMovesFromSanBlack()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        //this position is stored in test/data/test_position_4.png, but white has just moved a1-b1
        std::string test_pos_4_after_a1_b1 = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/1R2K2R b Kkq - 7 8";
        my_cb.SetFenPosition(test_pos_4_after_a1_b1);
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        slach::Move a5("a5", squares, slach::BLACK);

        TS_ASSERT_EQUALS(a5.GetOrigin()->GetFile(), 'a');
        TS_ASSERT_EQUALS(a5.GetOrigin()->GetRank(), '7');
        TS_ASSERT_EQUALS(a5.GetDestination()->GetFile(), 'a');
        TS_ASSERT_EQUALS(a5.GetDestination()->GetRank(), '5');

        slach::Move a6("a6", squares, slach::BLACK);

        TS_ASSERT_EQUALS(a6.GetOrigin()->GetFile(), 'a');
        TS_ASSERT_EQUALS(a6.GetOrigin()->GetRank(), '7');
        TS_ASSERT_EQUALS(a6.GetDestination()->GetFile(), 'a');
        TS_ASSERT_EQUALS(a6.GetDestination()->GetRank(), '6');

        slach::Move d5("d5", squares, slach::BLACK);

        TS_ASSERT_EQUALS(d5.GetOrigin()->GetFile(), 'd');
        TS_ASSERT_EQUALS(d5.GetOrigin()->GetRank(), '6');
        TS_ASSERT_EQUALS(d5.GetDestination()->GetFile(), 'd');
        TS_ASSERT_EQUALS(d5.GetDestination()->GetRank(), '5');
    }

    void TestPawnCapturesFromSAN()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        //saved in tets/data/test_position_7.png for reference
        std::string fen_poistion = "r5k1/1p1b2pp/2n1pp2/2np4/1PP5/r3P1B1/2QK1PPP/R4B1R b - - 4 19";
        my_cb.SetFenPosition(fen_poistion);
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        slach::Move d_takes_c4("dxc4", squares, slach::BLACK);

        TS_ASSERT_EQUALS(d_takes_c4.GetOrigin()->GetFile(), 'd');
        TS_ASSERT_EQUALS(d_takes_c4.GetOrigin()->GetRank(), '5');
        TS_ASSERT_EQUALS(d_takes_c4.GetDestination()->GetFile(), 'c');
        TS_ASSERT_EQUALS(d_takes_c4.GetDestination()->GetRank(), '4');
    }

    void TestPromotionFromSanBlack()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        //saved in tets/data/test_position_5.png for reference
        std::string fen_poistion = "4k3/2P1P1P1/3K3P/p4b2/8/P7/1p6/8 b - - 0 59";
        my_cb.SetFenPosition(fen_poistion);
        std::vector<slach::Square* > squares = my_cb.GetSquares();
        //black's turn move is b2-b1 (promotes queen)
        slach::Move b_promotes_queen("b1=Q", squares, slach::BLACK);

        TS_ASSERT_EQUALS(b_promotes_queen.GetOrigin()->GetFile(), 'b');
        TS_ASSERT_EQUALS(b_promotes_queen.GetOrigin()->GetRank(), '2');
        TS_ASSERT_EQUALS(b_promotes_queen.GetDestination()->GetFile(), 'b');
        TS_ASSERT_EQUALS(b_promotes_queen.GetDestination()->GetRank(), '1');
        TS_ASSERT_EQUALS(b_promotes_queen.IsBlackPromoting(), true);
    }

    void TestPromotionFromSanWhite()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        //saved in tets/data/test_position_5.png for reference but after black promoted
        std::string fen_poistion = "4k3/2P1P1P1/3K3P/p4b2/8/P7/8/1q6 w - - 0 60";
        my_cb.SetFenPosition(fen_poistion);
        std::vector<slach::Square* > squares = my_cb.GetSquares();
        //black's turn move is c7-c8 (promotes, choose a knight)
        slach::Move c_promotes_knight("c8=N", squares, slach::WHITE);

        TS_ASSERT_EQUALS(c_promotes_knight.GetOrigin()->GetFile(), 'c');
        TS_ASSERT_EQUALS(c_promotes_knight.GetOrigin()->GetRank(), '7');
        TS_ASSERT_EQUALS(c_promotes_knight.GetDestination()->GetFile(), 'c');
        TS_ASSERT_EQUALS(c_promotes_knight.GetDestination()->GetRank(), '8');
        TS_ASSERT_EQUALS(c_promotes_knight.IsWhitePromoting(), true);
    }

    void TestInvalidSans()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        //this position is stored in test/data/test_position_4.png for reference
        std::string test_pos_4 = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K2R w KQkq - 6 8";
        my_cb.SetFenPosition(test_pos_4);
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        slach::Move rubbish_bishop_move("BT4", squares, slach::WHITE);

        //TS_ASSERT_EQUALS(rubbish_bishop_move.GetDestination(), NULL); this doesn't compile
        if (rubbish_bishop_move.GetOrigin() == NULL)
        {
            TS_ASSERT_EQUALS(1,1);//pass
        }
        else
        {
            TS_ASSERT_EQUALS(0,1);//fail
        }
        if (rubbish_bishop_move.GetDestination() == NULL)
        {
            TS_ASSERT_EQUALS(1,1);//pass
        }
        else
        {
            TS_ASSERT_EQUALS(0,1);//fail
        }

        //correct syntax, but no white bishop can go there to h8
        slach::Move invalid_bishop_move("Bh8", squares, slach::WHITE);

        //TS_ASSERT_EQUALS(invalid_bishop_move.GetDestination(), NULL); this doesn't compile
        if (invalid_bishop_move.GetOrigin() == NULL)
        {
            TS_ASSERT_EQUALS(1,1);//pass
        }
        else
        {
            TS_ASSERT_EQUALS(0,1);//fail
        }
        if (invalid_bishop_move.GetDestination() == NULL)
        {
            TS_ASSERT_EQUALS(1,1);//pass
        }
        else
        {
            TS_ASSERT_EQUALS(0,1);//fail
        }

        slach::Move short_san("B", squares, slach::WHITE);
        if (short_san.GetOrigin() == NULL)
        {
            TS_ASSERT_EQUALS(1,1);//pass
        }
        else
        {
            TS_ASSERT_EQUALS(0,1);//fail
        }
        if (short_san.GetDestination() == NULL)
        {
            TS_ASSERT_EQUALS(1,1);//pass
        }
        else
        {
            TS_ASSERT_EQUALS(0,1);//fail
        }

        slach::Move short_san_2("Bd", squares, slach::WHITE);
        if (short_san_2.GetOrigin() == NULL)
        {
            TS_ASSERT_EQUALS(1,1);//pass
        }
        else
        {
            TS_ASSERT_EQUALS(0,1);//fail
        }
        if (short_san_2.GetDestination() == NULL)
        {
            TS_ASSERT_EQUALS(1,1);//pass
        }
        else
        {
            TS_ASSERT_EQUALS(0,1);//fail
        }

        slach::Move short_san_3("Bxd", squares, slach::WHITE);
        if (short_san_3.GetOrigin() == NULL)
        {
            TS_ASSERT_EQUALS(1,1);//pass
        }
        else
        {
            TS_ASSERT_EQUALS(0,1);//fail
        }
        if (short_san_3.GetDestination() == NULL)
        {
            TS_ASSERT_EQUALS(1,1);//pass
        }
        else
        {
            TS_ASSERT_EQUALS(0,1);//fail
        }

        slach::Move wrong_pawn("a2", squares, slach::WHITE);
        if (wrong_pawn.GetOrigin() == NULL)
        {
            TS_ASSERT_EQUALS(1,1);//pass
        }
        else
        {
            TS_ASSERT_EQUALS(0,1);//fail
        }
        if (wrong_pawn.GetDestination() == NULL)
        {
            TS_ASSERT_EQUALS(1,1);//pass
        }
        else
        {
            TS_ASSERT_EQUALS(0,1);//fail
        }

        slach::Move wrong_pawn_black("a7", squares, slach::BLACK);
        if (wrong_pawn_black.GetOrigin() == NULL)
        {
            TS_ASSERT_EQUALS(1,1);//pass
        }
        else
        {
            TS_ASSERT_EQUALS(0,1);//fail
        }
        if (wrong_pawn_black.GetDestination() == NULL)
        {
            TS_ASSERT_EQUALS(1,1);//pass
        }
        else
        {
            TS_ASSERT_EQUALS(0,1);//fail
        }
    }

};
#endif //TESTMOVE_HPP_
