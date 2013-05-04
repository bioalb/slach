#ifndef TESTSQUARE_HPP_
#define TESTSQUARE_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include "Square.hpp"

/**
 * Test suite to test the SQUARE
 */
class TestSquare : public CxxTest::TestSuite
{
public:

    void testGetAndSetMethos(void)
    {
        Square sq1;
        //check default values
        TS_ASSERT_EQUALS(sq1.GetRank(), "UNDEFINED");
        TS_ASSERT_EQUALS(sq1.GetFile(), "UNDEFINED");
        TS_ASSERT_EQUALS(sq1.IsBorderSquare(), false);
        TS_ASSERT_EQUALS(sq1.IsCornerSquare(), false);
        TS_ASSERT_EQUALS(sq1.IsCoordinatePrintable(), false);
        TS_ASSERT_EQUALS(sq1.IsCornerSquare(), false);
        TS_ASSERT_EQUALS(sq1.GetPieceOnThisSquare(),NO_PIECE);
        TS_ASSERT_EQUALS(sq1.IsDarkSquare(), false);
        TS_ASSERT_EQUALS(sq1.IsLightSquare(), false);

        sq1.SetFile("A");
        sq1.SetRank("4");
        TS_ASSERT_EQUALS(sq1.GetRank(), "4");
        TS_ASSERT_EQUALS(sq1.GetFile(), "A");

        sq1.SetAsLightSquare();
        TS_ASSERT_EQUALS(sq1.IsLightSquare(), true);
        TS_ASSERT_EQUALS(sq1.IsDarkSquare(), false);

        sq1.SetAsDarkSquare();
        TS_ASSERT_EQUALS(sq1.IsLightSquare(), false);
        TS_ASSERT_EQUALS(sq1.IsDarkSquare(), true);

        sq1.SetPieceOnThisSquare(BLACK_KING);
        TS_ASSERT_EQUALS(sq1.GetPieceOnThisSquare(),BLACK_KING);

        sq1.SetPieceOnThisSquare(WHITE_PAWN);
        TS_ASSERT_EQUALS(sq1.GetPieceOnThisSquare(),WHITE_PAWN);

        //set some features and check
        sq1.SetAsBorderSquare();
        TS_ASSERT_EQUALS(sq1.IsBorderSquare(), true);
        sq1.SetAsCornerSquare(true);
        TS_ASSERT_EQUALS(sq1.IsCornerSquare(), true);
        sq1.SetAsPrintableCoordinates();
        TS_ASSERT_EQUALS(sq1.IsCoordinatePrintable(), true);
    }

    void testSameSquare(void)
    {
        Square sq1;
        Square sq2;

        TS_ASSERT_EQUALS(sq1.IsSameSquare(sq2), true);
        TS_ASSERT_EQUALS(sq2.IsSameSquare(sq1), true);

        sq1.SetFile("A");
        sq2.SetFile("B");

        TS_ASSERT_EQUALS(sq1.IsSameSquare(sq2), false);
        TS_ASSERT_EQUALS(sq2.IsSameSquare(sq1), false);

        sq2.SetFile("A");

        TS_ASSERT_EQUALS(sq1.IsSameSquare(sq2), true);
        TS_ASSERT_EQUALS(sq2.IsSameSquare(sq1), true);

        sq2.SetRank("2");

        TS_ASSERT_EQUALS(sq1.IsSameSquare(sq2), false);
        TS_ASSERT_EQUALS(sq2.IsSameSquare(sq1), false);

        sq1.SetRank("2");

        TS_ASSERT_EQUALS(sq1.IsSameSquare(sq2), true);
        TS_ASSERT_EQUALS(sq2.IsSameSquare(sq1), true);
    }
};
#endif
