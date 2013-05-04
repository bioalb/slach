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

    void testBasic()
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
};
#endif
