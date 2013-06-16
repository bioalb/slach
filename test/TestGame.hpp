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
        slach::Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        slach::Square sq1;
        sq1.SetFile('a');
        sq1.SetRank('1');
        sq1.SetIndexFromA1(0u);
        sq1.SetPieceOnThisSquare(slach::BLACK_BISHOP);

        slach::Square sq2;
        sq2.SetFile('e');
        sq2.SetRank('4');
        sq2.SetIndexFromA1(28u);
        sq2.SetPieceOnThisSquare(slach::NO_PIECE);

        slach::Move bishop_e4_move(&sq1, &sq2);

        gm.AddMove(&bishop_e4_move);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetOrigin()->GetFile(),'a');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetOrigin()->GetRank(),'1');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetDestination()->GetFile(),'e');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetDestination()->GetRank(),'4');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "Be4");
    }

    void testPawnMove()
    {
        slach::Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        slach::Square sq1;
        sq1.SetFile('a');
        sq1.SetRank('2');
        sq1.SetIndexFromA1(8u);
        sq1.SetPieceOnThisSquare(slach::WHITE_PAWN);

        slach::Square sq2;
        sq2.SetFile('a');
        sq2.SetRank('4');
        sq2.SetIndexFromA1(24u);
        sq2.SetPieceOnThisSquare(slach::NO_PIECE);

        slach::Move a4_move(&sq1, &sq2);

        gm.AddMove(&a4_move);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetOrigin()->GetFile(),'a');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetOrigin()->GetRank(),'2');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetDestination()->GetFile(),'a');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetDestination()->GetRank(),'4');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "a4");
    }

    void testCapture()
    {
        slach::Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        slach::Square sq1;
        sq1.SetFile('a');
        sq1.SetRank('2');
        sq1.SetIndexFromA1(8u);
        sq1.SetPieceOnThisSquare(slach::BLACK_QUEEN);

        slach::Square sq2;
        sq2.SetFile('a');
        sq2.SetRank('4');
        sq2.SetIndexFromA1(24u);
        sq2.SetPieceOnThisSquare(slach::WHITE_BISHOP);

        slach::Move queen_takes_bishop(&sq1, &sq2);

        gm.AddMove(&queen_takes_bishop);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetOrigin()->GetFile(),'a');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetOrigin()->GetRank(),'2');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetDestination()->GetFile(),'a');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetDestination()->GetRank(),'4');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "Qxa4");
    }

    void testPawnCapture()
    {
        slach::Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        slach::Square sq1;
        sq1.SetFile('a');
        sq1.SetRank('2');
        sq1.SetIndexFromA1(8u);
        sq1.SetIndexFromA1(8u);
        sq1.SetPieceOnThisSquare(slach::WHITE_PAWN);

        slach::Square sq2;
        sq2.SetFile('b');
        sq2.SetRank('3');
        sq2.SetIndexFromA1(17u);
        sq2.SetPieceOnThisSquare(slach::WHITE_BISHOP);

        slach::Move pawn_takes_bishop(&sq1,&sq2);

        gm.AddMove(&pawn_takes_bishop);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetOrigin()->GetFile(),'a');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetOrigin()->GetRank(),'2');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetDestination()->GetFile(),'b');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetDestination()->GetRank(),'3');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "axb3");
    }

    void testCastleKingSide()
    {
        slach::Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        slach::Square sq1;
        sq1.SetFile('e');
        sq1.SetRank('1');
        sq1.SetIndexFromA1(4u);
        sq1.SetPieceOnThisSquare(slach::WHITE_KING);

        slach::Square sq2;
        sq2.SetFile('g');
        sq2.SetRank('1');
        sq2.SetIndexFromA1(6u);
        sq2.SetPieceOnThisSquare(slach::NO_PIECE);

        slach::Move castle_white(&sq1,&sq2);

        gm.AddMove(&castle_white);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetOrigin()->GetFile(),'e');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetOrigin()->GetRank(),'1');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetDestination()->GetFile(),'g');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetDestination()->GetRank(),'1');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "O-O");

        slach::Square sq3;
        sq3.SetFile('e');
        sq3.SetRank('8');
        sq3.SetIndexFromA1(60u);
        sq3.SetPieceOnThisSquare(slach::BLACK_KING);

        slach::Square sq4;
        sq4.SetFile('g');
        sq4.SetRank('8');
        sq4.SetIndexFromA1(62u);
        sq4.SetPieceOnThisSquare(slach::NO_PIECE);

        slach::Move castle_black(&sq3, &sq4);

        gm.AddMove(&castle_black);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 2u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[1]->GetOrigin()->GetFile(),'e');
        TS_ASSERT_EQUALS(gm.GetMoveList()[1]->GetOrigin()->GetRank(),'8');
        TS_ASSERT_EQUALS(gm.GetMoveList()[1]->GetDestination()->GetFile(),'g');
        TS_ASSERT_EQUALS(gm.GetMoveList()[1]->GetDestination()->GetRank(),'8');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 2u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[1], "O-O");

        //now add another move (the same as before)
        gm.AddMove(&castle_white);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 3u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[2]->GetOrigin()->GetFile(),'e');
        TS_ASSERT_EQUALS(gm.GetMoveList()[2]->GetOrigin()->GetRank(),'1');
        TS_ASSERT_EQUALS(gm.GetMoveList()[2]->GetDestination()->GetFile(),'g');
        TS_ASSERT_EQUALS(gm.GetMoveList()[2]->GetDestination()->GetRank(),'1');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 3u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[2], "O-O");

    }

    void testCastleQueenSide()
    {
        slach::Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        slach::Square sq1;
        sq1.SetFile('e');
        sq1.SetRank('1');
        sq1.SetIndexFromA1(4u);
        sq1.SetPieceOnThisSquare(slach::WHITE_KING);

        slach::Square sq2;
        sq2.SetFile('c');
        sq2.SetRank('1');
        sq2.SetIndexFromA1(2u);
        sq2.SetPieceOnThisSquare(slach::NO_PIECE);

        slach::Move castle_white(&sq1, &sq2);

        gm.AddMove(&castle_white);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetOrigin()->GetFile(),'e');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetOrigin()->GetRank(),'1');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetDestination()->GetFile(),'c');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0]->GetDestination()->GetRank(),'1');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "O-O-O");

        slach::Square sq3;
        sq3.SetFile('e');
        sq3.SetRank('8');
        sq3.SetIndexFromA1(60u);
        sq3.SetPieceOnThisSquare(slach::BLACK_KING);

        slach::Square sq4;
        sq4.SetFile('c');
        sq4.SetRank('8');
        sq4.SetIndexFromA1(58u);
        sq4.SetPieceOnThisSquare(slach::NO_PIECE);

        slach::Move castle_black(&sq3,&sq4);

        gm.AddMove(&castle_black);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 2u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[1]->GetOrigin()->GetFile(),'e');
        TS_ASSERT_EQUALS(gm.GetMoveList()[1]->GetOrigin()->GetRank(),'8');
        TS_ASSERT_EQUALS(gm.GetMoveList()[1]->GetDestination()->GetFile(),'c');
        TS_ASSERT_EQUALS(gm.GetMoveList()[1]->GetDestination()->GetRank(),'8');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 2u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[1], "O-O-O");
    }
};
#endif
