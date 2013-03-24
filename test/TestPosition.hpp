#ifndef TESTPOSITION_HPP_
#define TESTPOSITION_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include "../src/ChessBoard.hpp"
#include "../src/PieceType.hpp"

class TestPosition : public CxxTest::TestSuite
{
public:

    void testInitialPosition(void)
    {
        ChessBoard cb;
        cb.SetupChessBoard();
        cb.SetupInitialChessPosition();
        TS_ASSERT_EQUALS(cb.GetCurrentPosition().size(), 32u);
    }
};
#endif
