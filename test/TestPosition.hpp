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

        for (unsigned i = 1; i <9; i++)
        {
            std::vector<Square* > rank = cb.GetOneRank(i);
            std::vector<Square* > file = cb.GetOneFile(i);
            TS_ASSERT_EQUALS(rank.size(),8u);
            TS_ASSERT_EQUALS(file.size(),8u);
        }
        TS_ASSERT_THROWS_THIS(cb.GetOneRank(0u), "Requested rank may go from 1 to 8");
        TS_ASSERT_THROWS_THIS(cb.GetOneRank(9u), "Requested rank may go from 1 to 8");
        TS_ASSERT_THROWS_THIS(cb.GetOneRank(10u), "Requested rank may go from 1 to 8");
        TS_ASSERT_THROWS_THIS(cb.GetOneRank(25u), "Requested rank may go from 1 to 8");

        TS_ASSERT_THROWS_THIS(cb.GetOneFile(0u), "Requested file may go from 1 to 8");
        TS_ASSERT_THROWS_THIS(cb.GetOneFile(9u), "Requested file may go from 1 to 8");
        TS_ASSERT_THROWS_THIS(cb.GetOneFile(10u), "Requested file may go from 1 to 8");
        TS_ASSERT_THROWS_THIS(cb.GetOneFile(25u), "Requested file may go from 1 to 8");
    }
};
#endif
