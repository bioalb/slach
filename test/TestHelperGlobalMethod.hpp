#ifndef TESTHELPERGLOBALMETHOD_HPP_
#define TESTHELPERGLOBALMETHOD_HPP_

#include <cxxtest/TestSuite.h>
#include "SlachTypes.hpp"

class TestHelperGlobalMethod : public CxxTest::TestSuite
{
public:

    void testPiecesColour()
    {
        TS_ASSERT_EQUALS(slach::IsBlackPiece(slach::BLACK_KING), true);
        TS_ASSERT_EQUALS(slach::IsBlackPiece(slach::BLACK_BISHOP), true);
        TS_ASSERT_EQUALS(slach::IsBlackPiece(slach::BLACK_QUEEN), true);
        TS_ASSERT_EQUALS(slach::IsBlackPiece(slach::BLACK_KNIGHT), true);
        TS_ASSERT_EQUALS(slach::IsBlackPiece(slach::BLACK_PAWN), true);
        TS_ASSERT_EQUALS(slach::IsBlackPiece(slach::BLACK_ROOK), true);
        TS_ASSERT_EQUALS(slach::IsBlackPiece(slach::WHITE_KING), false);
        TS_ASSERT_EQUALS(slach::IsBlackPiece(slach::WHITE_BISHOP), false);
        TS_ASSERT_EQUALS(slach::IsBlackPiece(slach::WHITE_QUEEN), false);
        TS_ASSERT_EQUALS(slach::IsBlackPiece(slach::WHITE_KNIGHT), false);
        TS_ASSERT_EQUALS(slach::IsBlackPiece(slach::WHITE_PAWN), false);
        TS_ASSERT_EQUALS(slach::IsBlackPiece(slach::WHITE_ROOK), false);
        TS_ASSERT_EQUALS(slach::IsBlackPiece(slach::NO_PIECE), false);

        TS_ASSERT_EQUALS(slach::IsWhitePiece(slach::BLACK_KING), false);
        TS_ASSERT_EQUALS(slach::IsWhitePiece(slach::BLACK_BISHOP), false);
        TS_ASSERT_EQUALS(slach::IsWhitePiece(slach::BLACK_QUEEN), false);
        TS_ASSERT_EQUALS(slach::IsWhitePiece(slach::BLACK_KNIGHT), false);
        TS_ASSERT_EQUALS(slach::IsWhitePiece(slach::BLACK_PAWN), false);
        TS_ASSERT_EQUALS(slach::IsWhitePiece(slach::BLACK_ROOK), false);
        TS_ASSERT_EQUALS(slach::IsWhitePiece(slach::WHITE_KING), true);
        TS_ASSERT_EQUALS(slach::IsWhitePiece(slach::WHITE_BISHOP), true);
        TS_ASSERT_EQUALS(slach::IsWhitePiece(slach::WHITE_QUEEN), true);
        TS_ASSERT_EQUALS(slach::IsWhitePiece(slach::WHITE_KNIGHT), true);
        TS_ASSERT_EQUALS(slach::IsWhitePiece(slach::WHITE_PAWN), true);
        TS_ASSERT_EQUALS(slach::IsWhitePiece(slach::WHITE_ROOK), true);
        TS_ASSERT_EQUALS(slach::IsWhitePiece(slach::NO_PIECE), false);

    }
};
#endif
