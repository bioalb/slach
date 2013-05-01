#ifndef TESTCHESSBOARDWITHBORDERS_HPP_
#define TESTCHESSBOARDWITHBORDERS_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include "../src/ChessBoardWithBorders.hpp"
#include "../src/PieceType.hpp"

/**
 * Test suite to test the chessboard and the chessboard with border class.
 */
class TestChessboards : public CxxTest::TestSuite
{
public:

    void testBorderFlags(void)
    {
        ChessBoardWithBorders my_cb;

        std::vector<Square* > squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(squares.size(), CHESSBOARD_SIZE_WB);

        std::vector<unsigned> border_indices_no_corners =
             {1,2,3,4,5,6,7,8,10,19,20,29,30,39,40,49,50,59,60,69,70,79,80,89};

        std::vector<unsigned> corner_indices = {0,9,90,99};

        //check all borders
        for (unsigned  i = 0; i < border_indices_no_corners.size(); ++i)
        {
            unsigned index = border_indices_no_corners[i];
            TS_ASSERT_EQUALS(squares[index]->IsBorderSquare(), true);
            TS_ASSERT_EQUALS(squares[index]->IsCornerSquare(), false);
        }
        //check corners
        for (unsigned  i = 0; i < corner_indices.size(); ++i)
        {
            unsigned index = corner_indices[i];
            TS_ASSERT_EQUALS(squares[index]->IsBorderSquare(), true);
            TS_ASSERT_EQUALS(squares[index]->IsCornerSquare(), true);
        }

    }

    void testBoardWithBorders(void)
    {

        ChessBoardWithBorders my_cb;

        std::vector<Square* > squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(squares.size(), CHESSBOARD_SIZE_WB);

        //check top left corner
        TS_ASSERT_EQUALS(squares.size(), CHESSBOARD_SIZE_WB);
        TS_ASSERT_EQUALS(squares[0]->IsCornerSquare(), true);
        TS_ASSERT_EQUALS(squares[0]->IsBorderSquare(), true);
        TS_ASSERT_EQUALS(squares[0]->GetFile(), "0");
        TS_ASSERT_EQUALS(squares[0]->GetRank(), "0");
        TS_ASSERT_EQUALS(squares[0]->IsCoordinatePrintable(), false);

        //check the top border
        std::vector<std::string > files = {"0" , "A", "B", "C", "D", "E","F", "G",  "H", "0"};
        std::vector<std::string > ranks = {"0" , "1", "2", "3", "4", "5","6", "7",  "8", "0"};
        for (unsigned i=1; i < 9; ++i)
        {
            TS_ASSERT_EQUALS(squares[i]->IsCornerSquare(), false);
            TS_ASSERT_EQUALS(squares[i]->IsBorderSquare(), true);
            TS_ASSERT_EQUALS(squares[i]->GetFile(),files[i]);
            TS_ASSERT_EQUALS(squares[i]->GetRank(), "0");
            TS_ASSERT_EQUALS(squares[i]->IsCoordinatePrintable(), false);
        }

        //check the top right corner
        TS_ASSERT_EQUALS(squares[9]->IsCornerSquare(), true);
        TS_ASSERT_EQUALS(squares[9]->IsBorderSquare(), true);
        TS_ASSERT_EQUALS(squares[9]->GetFile(), "0");
        TS_ASSERT_EQUALS(squares[9]->GetRank(), "0");
        TS_ASSERT_EQUALS(squares[9]->IsCoordinatePrintable(), false);

        //////
        // 8th rank
        //////

        //border first
        TS_ASSERT_EQUALS(squares[10]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[10]->IsBorderSquare(), true);
        TS_ASSERT_EQUALS(squares[10]->GetFile(), "0");
        TS_ASSERT_EQUALS(squares[10]->GetRank(), "8");
        TS_ASSERT_EQUALS(squares[10]->IsCoordinatePrintable(), true);

        //a8
        TS_ASSERT_EQUALS(squares[11]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[11]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[11]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[11]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[11]->GetFile(), "A");
        TS_ASSERT_EQUALS(squares[11]->GetRank(), "8");
        TS_ASSERT_EQUALS(squares[11]->IsCoordinatePrintable(), false);

        //b8
        TS_ASSERT_EQUALS(squares[12]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[12]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[12]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[12]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[12]->GetFile(), "B");
        TS_ASSERT_EQUALS(squares[12]->GetRank(), "8");

        //c8
        TS_ASSERT_EQUALS(squares[13]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[13]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[13]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[13]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[13]->GetFile(), "C");
        TS_ASSERT_EQUALS(squares[13]->GetRank(), "8");

        //d8
        TS_ASSERT_EQUALS(squares[14]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[14]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[14]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[14]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[14]->GetFile(), "D");
        TS_ASSERT_EQUALS(squares[14]->GetRank(), "8");

        //e8
        TS_ASSERT_EQUALS(squares[15]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[15]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[15]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[15]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[15]->GetFile(), "E");
        TS_ASSERT_EQUALS(squares[15]->GetRank(), "8");

        //f8
        TS_ASSERT_EQUALS(squares[16]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[16]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[16]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[16]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[16]->GetFile(), "F");
        TS_ASSERT_EQUALS(squares[16]->GetRank(), "8");

        //g8
        TS_ASSERT_EQUALS(squares[17]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[17]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[17]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[17]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[17]->GetFile(), "G");
        TS_ASSERT_EQUALS(squares[17]->GetRank(), "8");

        //h8
        TS_ASSERT_EQUALS(squares[18]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[18]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[18]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[18]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[18]->GetFile(), "H");
        TS_ASSERT_EQUALS(squares[18]->GetRank(), "8");

        //border square next to h8
        TS_ASSERT_EQUALS(squares[19]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[19]->IsBorderSquare(), true);
        TS_ASSERT_EQUALS(squares[19]->GetFile(), "0");
        TS_ASSERT_EQUALS(squares[19]->GetRank(), "8");
        TS_ASSERT_EQUALS(squares[19]->IsCoordinatePrintable(), false);

        //////
        // 7th rank
        //////

        //border first
        TS_ASSERT_EQUALS(squares[20]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[20]->IsBorderSquare(), true);
        TS_ASSERT_EQUALS(squares[20]->GetFile(), "0");
        TS_ASSERT_EQUALS(squares[20]->GetRank(), "7");
        TS_ASSERT_EQUALS(squares[20]->IsCoordinatePrintable(), true);

        //a7
        TS_ASSERT_EQUALS(squares[21]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[21]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[21]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[21]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[21]->GetFile(), "A");
        TS_ASSERT_EQUALS(squares[21]->GetRank(), "7");

        //b7
        TS_ASSERT_EQUALS(squares[22]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[22]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[22]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[22]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[22]->GetFile(), "B");
        TS_ASSERT_EQUALS(squares[22]->GetRank(), "7");

        //c7
        TS_ASSERT_EQUALS(squares[23]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[23]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[23]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[23]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[23]->GetFile(), "C");
        TS_ASSERT_EQUALS(squares[23]->GetRank(), "7");

        //d7
        TS_ASSERT_EQUALS(squares[24]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[24]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[24]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[24]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[24]->GetFile(), "D");
        TS_ASSERT_EQUALS(squares[24]->GetRank(), "7");

        //e7
        TS_ASSERT_EQUALS(squares[25]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[25]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[25]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[25]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[25]->GetFile(), "E");
        TS_ASSERT_EQUALS(squares[25]->GetRank(), "7");

        //f7
        TS_ASSERT_EQUALS(squares[26]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[26]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[26]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[26]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[26]->GetFile(), "F");
        TS_ASSERT_EQUALS(squares[26]->GetRank(), "7");

        //g7
        TS_ASSERT_EQUALS(squares[27]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[27]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[27]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[27]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[27]->GetFile(), "G");
        TS_ASSERT_EQUALS(squares[27]->GetRank(), "7");

        //h7
        TS_ASSERT_EQUALS(squares[28]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[28]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[28]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[28]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[28]->GetFile(), "H");
        TS_ASSERT_EQUALS(squares[28]->GetRank(), "7");

        //border square next to h7
        TS_ASSERT_EQUALS(squares[29]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[29]->IsBorderSquare(), true);
        TS_ASSERT_EQUALS(squares[29]->GetFile(), "0");
        TS_ASSERT_EQUALS(squares[29]->GetRank(), "7");
        TS_ASSERT_EQUALS(squares[29]->IsCoordinatePrintable(), false);

        //////
        // 1st rank
        //////

        //border first
        TS_ASSERT_EQUALS(squares[80]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[80]->IsBorderSquare(), true);
        TS_ASSERT_EQUALS(squares[80]->GetFile(), "0");
        TS_ASSERT_EQUALS(squares[80]->GetRank(), "1");
        TS_ASSERT_EQUALS(squares[80]->IsCoordinatePrintable(), true);

        //a1
        TS_ASSERT_EQUALS(squares[81]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[81]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[81]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[81]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[81]->GetFile(), "A");
        TS_ASSERT_EQUALS(squares[81]->GetRank(), "1");

        //a1
        TS_ASSERT_EQUALS(squares[82]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[82]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[82]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[82]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[82]->GetFile(), "B");
        TS_ASSERT_EQUALS(squares[82]->GetRank(), "1");

        //c1
        TS_ASSERT_EQUALS(squares[83]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[83]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[83]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[83]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[83]->GetFile(), "C");
        TS_ASSERT_EQUALS(squares[83]->GetRank(), "1");

        //d1
        TS_ASSERT_EQUALS(squares[84]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[84]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[84]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[84]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[84]->GetFile(), "D");
        TS_ASSERT_EQUALS(squares[84]->GetRank(), "1");

        //e1
        TS_ASSERT_EQUALS(squares[85]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[85]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[85]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[85]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[85]->GetFile(), "E");
        TS_ASSERT_EQUALS(squares[85]->GetRank(), "1");

        //f1
        TS_ASSERT_EQUALS(squares[86]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[86]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[86]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[86]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[86]->GetFile(), "F");
        TS_ASSERT_EQUALS(squares[86]->GetRank(), "1");

        //g1
        TS_ASSERT_EQUALS(squares[87]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[87]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[87]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[87]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[87]->GetFile(), "G");
        TS_ASSERT_EQUALS(squares[87]->GetRank(), "1");

        //h1
        TS_ASSERT_EQUALS(squares[88]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[88]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[88]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[88]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[88]->GetFile(), "H");
        TS_ASSERT_EQUALS(squares[88]->GetRank(), "1");

        //border square next to h1
        TS_ASSERT_EQUALS(squares[89]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[89]->IsBorderSquare(), true);
        TS_ASSERT_EQUALS(squares[89]->GetFile(), "0");
        TS_ASSERT_EQUALS(squares[89]->GetRank(), "1");
        TS_ASSERT_EQUALS(squares[89]->IsCoordinatePrintable(), false);

        /////
        //Bottom border
        /////

        //check bottom left corner
        TS_ASSERT_EQUALS(squares[90]->IsCornerSquare(), true);
        TS_ASSERT_EQUALS(squares[90]->IsBorderSquare(), true);
        TS_ASSERT_EQUALS(squares[90]->GetFile(), "0");
        TS_ASSERT_EQUALS(squares[90]->GetRank(), "0");
        TS_ASSERT_EQUALS(squares[90]->IsCoordinatePrintable(), false);

        //check the bottom border
        unsigned file_index = 1;
        for (unsigned i=91; i < 99; ++i)
        {

            TS_ASSERT_EQUALS(squares[i]->IsCornerSquare(), false);
            TS_ASSERT_EQUALS(squares[i]->IsBorderSquare(), true);
            TS_ASSERT_EQUALS(squares[i]->GetFile(),files[file_index]);
            TS_ASSERT_EQUALS(squares[i]->GetRank(), "0");
            TS_ASSERT_EQUALS(squares[i]->IsCoordinatePrintable(), true);
            file_index++;
        }

        //check the bottom right corner
        TS_ASSERT_EQUALS(squares[99]->IsCornerSquare(), true);
        TS_ASSERT_EQUALS(squares[99]->IsBorderSquare(), true);
        TS_ASSERT_EQUALS(squares[99]->GetFile(), "0");
        TS_ASSERT_EQUALS(squares[99]->GetRank(), "0");
        TS_ASSERT_EQUALS(squares[99]->IsCoordinatePrintable(), false);
    }



};
#endif
