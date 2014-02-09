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
        slach::Square sq1;
        //check default values
        TS_ASSERT_EQUALS(sq1.GetRank(), '0');
        TS_ASSERT_EQUALS(sq1.GetFile(), '0');
        TS_ASSERT_EQUALS(sq1.GetRankAsString(), "0");
        TS_ASSERT_EQUALS(sq1.GetFileAsString(), "0");
        TS_ASSERT_EQUALS(sq1.IsBorderSquare(), false);
        TS_ASSERT_EQUALS(sq1.IsCornerSquare(), false);
        TS_ASSERT_EQUALS(sq1.IsCoordinatePrintable(), false);
        TS_ASSERT_EQUALS(sq1.IsCornerSquare(), false);
        TS_ASSERT_EQUALS(sq1.GetPieceOnThisSquare(),slach::NO_PIECE);
        TS_ASSERT_EQUALS(sq1.IsDarkSquare(), false);
        TS_ASSERT_EQUALS(sq1.IsLightSquare(), false);
        TS_ASSERT_EQUALS(sq1.GetIndexFromA1(), UINT_MAX);
        TS_ASSERT_EQUALS(sq1.GetIndexFromTopLeft(), UINT_MAX);
        TS_ASSERT_EQUALS(sq1.IsHighlightable(), false);
        TS_ASSERT_EQUALS(sq1.IstheBottomRightCorner(), false);
        TS_ASSERT_THROWS_THIS(sq1.GetRankAsInt(),
                "slach::Square::GetRankAsInt the square index must be initialised before calling this method");
        TS_ASSERT_THROWS_THIS(sq1.GetFileAsInt(),
                "slach::Square::GetFileAsInt the square index must be initialised before calling this method");


        sq1.SetFile('a');
        sq1.SetRank('4');
        TS_ASSERT_EQUALS(sq1.GetRank(), '4');
        TS_ASSERT_EQUALS(sq1.GetFile(), 'a');
        TS_ASSERT_EQUALS(sq1.GetRankAsString(), "4");
        TS_ASSERT_EQUALS(sq1.GetFileAsString(), "a");
        TS_ASSERT_EQUALS(sq1.GetIndexFromA1(), UINT_MAX);
        TS_ASSERT_EQUALS(sq1.GetIndexFromBottomRight(), UINT_MAX);
        sq1.SetIndexFromA1(24u);
        sq1.SetIndexFromTopLeft(41u);
        sq1.SetIndexFromBottomRight(45u);
        TS_ASSERT_EQUALS(sq1.GetIndexFromA1(), 24u);
        TS_ASSERT_EQUALS(sq1.GetIndexFromTopLeft(), 41u);
        TS_ASSERT_EQUALS(sq1.GetIndexFromBottomRight(), 45u);
        TS_ASSERT_EQUALS(sq1.GetRankAsInt(), 3);
        TS_ASSERT_EQUALS(sq1.GetFileAsInt(), 0);
        TS_ASSERT_EQUALS(sq1.Getx88Index(), 48);
        TS_ASSERT_EQUALS(sq1.IsSecondRank(), false);
        TS_ASSERT_EQUALS(sq1.IsSeventhRank(), false);
        TS_ASSERT_EQUALS(sq1.IsThirdRank(), false);
        TS_ASSERT_EQUALS(sq1.IsSixthRank(), false);
        sq1.SetAsToBeHighlightable(true);
        TS_ASSERT_EQUALS(sq1.IsHighlightable(), true);
        sq1.SetAsToBeHighlightable(false);
        TS_ASSERT_EQUALS(sq1.IsHighlightable(), false);
        sq1.SetAsBottomRightCorner(true);
        TS_ASSERT_EQUALS(sq1.IstheBottomRightCorner(), true);
        sq1.SetAsBottomRightCorner(false);
        TS_ASSERT_EQUALS(sq1.IstheBottomRightCorner(), false);

        sq1.SetIndexFromA1(25u);//b4
        TS_ASSERT_EQUALS(sq1.GetIndexFromA1(), 25u);
        TS_ASSERT_EQUALS(sq1.GetRankAsInt(), 3);
        TS_ASSERT_EQUALS(sq1.GetFileAsInt(), 1);
        TS_ASSERT_EQUALS(sq1.Getx88Index(), 49);

        sq1.SetIndexFromA1(9u);//b2
        TS_ASSERT_EQUALS(sq1.IsSecondRank(), true);
        TS_ASSERT_EQUALS(sq1.IsSeventhRank(), false);
        TS_ASSERT_EQUALS(sq1.IsThirdRank(), false);
        TS_ASSERT_EQUALS(sq1.IsSixthRank(), false);

        sq1.SetIndexFromA1(55u);//h7
        TS_ASSERT_EQUALS(sq1.IsSecondRank(), false);
        TS_ASSERT_EQUALS(sq1.IsSeventhRank(), true);
        TS_ASSERT_EQUALS(sq1.IsThirdRank(), false);
        TS_ASSERT_EQUALS(sq1.IsSixthRank(), false);

        sq1.SetIndexFromA1(23u);//h3
        TS_ASSERT_EQUALS(sq1.IsSecondRank(), false);
        TS_ASSERT_EQUALS(sq1.IsSeventhRank(), false);
        TS_ASSERT_EQUALS(sq1.IsThirdRank(), true);
        TS_ASSERT_EQUALS(sq1.IsSixthRank(), false);

        sq1.SetIndexFromA1(41u);//b6
        TS_ASSERT_EQUALS(sq1.IsSecondRank(), false);
        TS_ASSERT_EQUALS(sq1.IsSeventhRank(), false);
        TS_ASSERT_EQUALS(sq1.IsThirdRank(), false);
        TS_ASSERT_EQUALS(sq1.IsSixthRank(), true);

        sq1.SetAsLightSquare();
        TS_ASSERT_EQUALS(sq1.IsLightSquare(), true);
        TS_ASSERT_EQUALS(sq1.IsDarkSquare(), false);

        sq1.SetAsDarkSquare();
        TS_ASSERT_EQUALS(sq1.IsLightSquare(), false);
        TS_ASSERT_EQUALS(sq1.IsDarkSquare(), true);

        sq1.SetPieceOnThisSquare(slach::BLACK_KING);
        TS_ASSERT_EQUALS(sq1.GetPieceOnThisSquare(),slach::BLACK_KING);

        sq1.SetPieceOnThisSquare(slach::WHITE_PAWN);
        TS_ASSERT_EQUALS(sq1.GetPieceOnThisSquare(),slach::WHITE_PAWN);

        //set some features and check
        sq1.SetAsBorderSquare();
        TS_ASSERT_EQUALS(sq1.IsBorderSquare(), true);
        sq1.SetAsCornerSquare(true);
        TS_ASSERT_EQUALS(sq1.IsCornerSquare(), true);
        sq1.SetAsPrintableCoordinates();
        TS_ASSERT_EQUALS(sq1.IsCoordinatePrintable(), true);

        //coverage
        TS_ASSERT_THROWS_THIS(sq1.SetFile('p'),
                "slach::Square::SetFile: you must set one of a,b,c,d,e,f,g,h or 0 as character");
        TS_ASSERT_THROWS_THIS(sq1.SetFile('A'),
                "slach::Square::SetFile: you must set one of a,b,c,d,e,f,g,h or 0 as character");
        TS_ASSERT_THROWS_THIS(sq1.SetRank('a'),
                "slach::Square::SetRank: you must set one of 1,2,3,4,5,6,7,8 or 0 as character");
        TS_ASSERT_THROWS_THIS(sq1.SetRank('9'),
                "slach::Square::SetRank: you must set one of 1,2,3,4,5,6,7,8 or 0 as character");
        TS_ASSERT_THROWS_NOTHING(sq1.SetRank('0'));
        TS_ASSERT_THROWS_NOTHING(sq1.SetFile('0'));
    }

    void testSameSquare(void)
    {
        slach::Square sq1;
        slach::Square sq2;

        TS_ASSERT_EQUALS(sq1.IsSameSquare(sq2), true);
        TS_ASSERT_EQUALS(sq2.IsSameSquare(sq1), true);

        sq1.SetFile('a');
        sq2.SetFile('b');

        TS_ASSERT_EQUALS(sq1.IsSameSquare(sq2), false);
        TS_ASSERT_EQUALS(sq2.IsSameSquare(sq1), false);

        sq2.SetFile('a');

        TS_ASSERT_EQUALS(sq1.IsSameSquare(sq2), true);
        TS_ASSERT_EQUALS(sq2.IsSameSquare(sq1), true);

        sq2.SetRank('2');

        TS_ASSERT_EQUALS(sq1.IsSameSquare(sq2), false);
        TS_ASSERT_EQUALS(sq2.IsSameSquare(sq1), false);

        sq1.SetRank('2');

        TS_ASSERT_EQUALS(sq1.IsSameSquare(sq2), true);
        TS_ASSERT_EQUALS(sq2.IsSameSquare(sq1), true);
    }
};
#endif
