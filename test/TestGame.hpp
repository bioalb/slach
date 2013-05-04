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
        std::vector<Move> movelist = gm.GetMoveList();
        TS_ASSERT_EQUALS(movelist.size(), 0u);
    }
};
#endif
