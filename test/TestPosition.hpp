#ifndef TESTPOSITION_HPP_
#define TESTPOSITION_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>

#include "ChessBoard.hpp"
#include "PieceType.hpp"



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
            std::stringstream ss;
            ss << i;
            std::string rank_string = ss.str();
            std::vector<Square* > rank = cb.GetOneRank(i);
            TS_ASSERT_EQUALS(rank[i]->GetRank(),rank_string);
            std::vector<Square* > file = cb.GetOneFile(i);
            std::string file_string;
            switch (i)
            {
                case 1:
                    file_string =  "A";
                    break;
                case 2:
                    file_string =  "B";
                    break;
                case 3:
                    file_string =  "C";
                    break;
                case 4:
                    file_string =  "D";
                    break;
                case 5:
                    file_string =  "E";
                    break;
                case 6:
                    file_string =  "F";
                    break;
                case 7:
                    file_string =  "G";
                    break;
                case 8:
                    file_string =  "H";
                    break;
            }
            TS_ASSERT_EQUALS(file[i]->GetFile(),file_string);
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
