#ifndef TESTGAME_HPP_
#define TESTGAME_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include "Game.hpp"

/**
 * Test suite to test the game class
 */
class TestGame : public CxxTest::TestSuite
{
public:


    void testBasicMove()
    {
        Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        Square sq1;
        sq1.SetFile("a");
        sq1.SetRank("1");
        sq1.SetPieceOnThisSquare(BLACK_BISHOP);

        Square sq2;
        sq2.SetFile("e");
        sq2.SetRank("4");
        sq2.SetPieceOnThisSquare(NO_PIECE);

        Move bishop_e4_move;
        bishop_e4_move.first = &sq1;
        bishop_e4_move.second = &sq2;

        gm.AddMove(bishop_e4_move);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].first->GetFile(),"a");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].first->GetRank(),"1");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].second->GetFile(),"e");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].second->GetRank(),"4");

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "Be4");
    }

    void testPawnMove()
    {
        Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        Square sq1;
        sq1.SetFile("a");
        sq1.SetRank("2");
        sq1.SetPieceOnThisSquare(BLACK_PAWN);

        Square sq2;
        sq2.SetFile("a");
        sq2.SetRank("4");
        sq2.SetPieceOnThisSquare(NO_PIECE);

        Move a4_move;
        a4_move.first = &sq1;
        a4_move.second = &sq2;

        gm.AddMove(a4_move);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].first->GetFile(),"a");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].first->GetRank(),"2");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].second->GetFile(),"a");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].second->GetRank(),"4");

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "a4");
    }

    void testCapture()
    {
        Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        Square sq1;
        sq1.SetFile("a");
        sq1.SetRank("2");
        sq1.SetPieceOnThisSquare(BLACK_QUEEN);

        Square sq2;
        sq2.SetFile("a");
        sq2.SetRank("4");
        sq2.SetPieceOnThisSquare(WHITE_BISHOP);

        Move queen_takes_bishop;
        queen_takes_bishop.first = &sq1;
        queen_takes_bishop.second = &sq2;

        gm.AddMove(queen_takes_bishop);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].first->GetFile(),"a");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].first->GetRank(),"2");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].second->GetFile(),"a");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].second->GetRank(),"4");

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "Qxa4");

    }

    void testPawnCapture()
    {
        Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        Square sq1;
        sq1.SetFile("a");
        sq1.SetRank("2");
        sq1.SetPieceOnThisSquare(BLACK_PAWN);

        Square sq2;
        sq2.SetFile("b");
        sq2.SetRank("3");
        sq2.SetPieceOnThisSquare(WHITE_BISHOP);

        Move pawn_takes_bishop;
        pawn_takes_bishop.first = &sq1;
        pawn_takes_bishop.second = &sq2;

        gm.AddMove(pawn_takes_bishop);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].first->GetFile(),"a");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].first->GetRank(),"2");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].second->GetFile(),"b");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].second->GetRank(),"3");

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "axb3");
    }

    void testCastleKingSide()
    {
        Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        Square sq1;
        sq1.SetFile("e");
        sq1.SetRank("1");
        sq1.SetPieceOnThisSquare(WHITE_KING);

        Square sq2;
        sq2.SetFile("g");
        sq2.SetRank("1");
        sq2.SetPieceOnThisSquare(NO_PIECE);

        Move castle_white;
        castle_white.first = &sq1;
        castle_white.second = &sq2;

        gm.DetermineSpecialMove(castle_white);
        SpecialMoveType mt = gm.GetSpecialMoveType();
        TS_ASSERT_EQUALS(mt, WHITE_CASTLE_KINGSIDE);

        gm.AddMove(castle_white);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].first->GetFile(),"e");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].first->GetRank(),"1");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].second->GetFile(),"g");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].second->GetRank(),"1");

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "O-O");

        Square sq3;
        sq3.SetFile("e");
        sq3.SetRank("8");
        sq3.SetPieceOnThisSquare(BLACK_KING);

        Square sq4;
        sq4.SetFile("g");
        sq4.SetRank("8");
        sq4.SetPieceOnThisSquare(NO_PIECE);

        Move castle_black;
        castle_black.first = &sq3;
        castle_black.second = &sq4;

        gm.DetermineSpecialMove(castle_black);
        SpecialMoveType mt2 = gm.GetSpecialMoveType();
        TS_ASSERT_EQUALS(mt2, BLACK_CASTLE_KINGSIDE);

        gm.AddMove(castle_black);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 2u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[1].first->GetFile(),"e");
        TS_ASSERT_EQUALS(gm.GetMoveList()[1].first->GetRank(),"8");
        TS_ASSERT_EQUALS(gm.GetMoveList()[1].second->GetFile(),"g");
        TS_ASSERT_EQUALS(gm.GetMoveList()[1].second->GetRank(),"8");

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 2u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[1], "O-O");

        //now add another move (the same as before) without calling the helper method explicitly.
        // this is because the helper method is called by AddMove internally as well.
        gm.AddMove(castle_white);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 3u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[2].first->GetFile(),"e");
        TS_ASSERT_EQUALS(gm.GetMoveList()[2].first->GetRank(),"1");
        TS_ASSERT_EQUALS(gm.GetMoveList()[2].second->GetFile(),"g");
        TS_ASSERT_EQUALS(gm.GetMoveList()[2].second->GetRank(),"1");

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 3u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[2], "O-O");

    }

    void testCastleQueenSide()
    {
        Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        Square sq1;
        sq1.SetFile("e");
        sq1.SetRank("1");
        sq1.SetPieceOnThisSquare(WHITE_KING);

        Square sq2;
        sq2.SetFile("c");
        sq2.SetRank("1");
        sq2.SetPieceOnThisSquare(NO_PIECE);

        Move castle_white;
        castle_white.first = &sq1;
        castle_white.second = &sq2;

        gm.DetermineSpecialMove(castle_white);
        SpecialMoveType mt = gm.GetSpecialMoveType();
        TS_ASSERT_EQUALS(mt, WHITE_CASTLE_QUEENSIDE);

        gm.AddMove(castle_white);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].first->GetFile(),"e");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].first->GetRank(),"1");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].second->GetFile(),"c");
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].second->GetRank(),"1");

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "O-O-O");

        Square sq3;
        sq3.SetFile("e");
        sq3.SetRank("8");
        sq3.SetPieceOnThisSquare(BLACK_KING);

        Square sq4;
        sq4.SetFile("c");
        sq4.SetRank("8");
        sq4.SetPieceOnThisSquare(NO_PIECE);

        Move castle_black;
        castle_black.first = &sq3;
        castle_black.second = &sq4;

        gm.DetermineSpecialMove(castle_black);
        SpecialMoveType mt2 = gm.GetSpecialMoveType();
        TS_ASSERT_EQUALS(mt2, BLACK_CASTLE_QUEENSIDE);

        gm.AddMove(castle_black);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 2u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[1].first->GetFile(),"e");
        TS_ASSERT_EQUALS(gm.GetMoveList()[1].first->GetRank(),"8");
        TS_ASSERT_EQUALS(gm.GetMoveList()[1].second->GetFile(),"c");
        TS_ASSERT_EQUALS(gm.GetMoveList()[1].second->GetRank(),"8");

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 2u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[1], "O-O-O");
    }
};
#endif
