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

    void testPieceType()
    {
        TS_ASSERT_EQUALS(slach::IsKnight(slach::BLACK_KING), false);
        TS_ASSERT_EQUALS(slach::IsKnight(slach::BLACK_BISHOP), false);
        TS_ASSERT_EQUALS(slach::IsKnight(slach::BLACK_QUEEN), false);
        TS_ASSERT_EQUALS(slach::IsKnight(slach::BLACK_KNIGHT), true);
        TS_ASSERT_EQUALS(slach::IsKnight(slach::BLACK_PAWN), false);
        TS_ASSERT_EQUALS(slach::IsKnight(slach::BLACK_ROOK), false);
        TS_ASSERT_EQUALS(slach::IsKnight(slach::WHITE_KING), false);
        TS_ASSERT_EQUALS(slach::IsKnight(slach::WHITE_BISHOP), false);
        TS_ASSERT_EQUALS(slach::IsKnight(slach::WHITE_QUEEN), false);
        TS_ASSERT_EQUALS(slach::IsKnight(slach::WHITE_KNIGHT), true);
        TS_ASSERT_EQUALS(slach::IsKnight(slach::WHITE_PAWN), false);
        TS_ASSERT_EQUALS(slach::IsKnight(slach::WHITE_ROOK), false);
        TS_ASSERT_EQUALS(slach::IsKnight(slach::NO_PIECE), false);

        TS_ASSERT_EQUALS(slach::IsPawn(slach::BLACK_KING), false);
        TS_ASSERT_EQUALS(slach::IsPawn(slach::BLACK_BISHOP), false);
        TS_ASSERT_EQUALS(slach::IsPawn(slach::BLACK_QUEEN), false);
        TS_ASSERT_EQUALS(slach::IsPawn(slach::BLACK_KNIGHT), false);
        TS_ASSERT_EQUALS(slach::IsPawn(slach::BLACK_PAWN), true);
        TS_ASSERT_EQUALS(slach::IsPawn(slach::BLACK_ROOK), false);
        TS_ASSERT_EQUALS(slach::IsPawn(slach::WHITE_KING), false);
        TS_ASSERT_EQUALS(slach::IsPawn(slach::WHITE_BISHOP), false);
        TS_ASSERT_EQUALS(slach::IsPawn(slach::WHITE_QUEEN), false);
        TS_ASSERT_EQUALS(slach::IsPawn(slach::WHITE_KNIGHT), false);
        TS_ASSERT_EQUALS(slach::IsPawn(slach::WHITE_PAWN), true);
        TS_ASSERT_EQUALS(slach::IsPawn(slach::WHITE_ROOK), false);
        TS_ASSERT_EQUALS(slach::IsPawn(slach::NO_PIECE), false);

        TS_ASSERT_EQUALS(slach::IsBishop(slach::BLACK_KING), false);
        TS_ASSERT_EQUALS(slach::IsBishop(slach::BLACK_BISHOP), true);
        TS_ASSERT_EQUALS(slach::IsBishop(slach::BLACK_QUEEN), false);
        TS_ASSERT_EQUALS(slach::IsBishop(slach::BLACK_KNIGHT), false);
        TS_ASSERT_EQUALS(slach::IsBishop(slach::BLACK_PAWN), false);
        TS_ASSERT_EQUALS(slach::IsBishop(slach::BLACK_ROOK), false);
        TS_ASSERT_EQUALS(slach::IsBishop(slach::WHITE_KING), false);
        TS_ASSERT_EQUALS(slach::IsBishop(slach::WHITE_BISHOP), true);
        TS_ASSERT_EQUALS(slach::IsBishop(slach::WHITE_QUEEN), false);
        TS_ASSERT_EQUALS(slach::IsBishop(slach::WHITE_KNIGHT), false);
        TS_ASSERT_EQUALS(slach::IsBishop(slach::WHITE_PAWN), false);
        TS_ASSERT_EQUALS(slach::IsBishop(slach::WHITE_ROOK), false);
        TS_ASSERT_EQUALS(slach::IsBishop(slach::NO_PIECE), false);

        TS_ASSERT_EQUALS(slach::IsRook(slach::BLACK_KING), false);
        TS_ASSERT_EQUALS(slach::IsRook(slach::BLACK_BISHOP), false);
        TS_ASSERT_EQUALS(slach::IsRook(slach::BLACK_QUEEN), false);
        TS_ASSERT_EQUALS(slach::IsRook(slach::BLACK_KNIGHT), false);
        TS_ASSERT_EQUALS(slach::IsRook(slach::BLACK_PAWN), false);
        TS_ASSERT_EQUALS(slach::IsRook(slach::BLACK_ROOK), true);
        TS_ASSERT_EQUALS(slach::IsRook(slach::WHITE_KING), false);
        TS_ASSERT_EQUALS(slach::IsRook(slach::WHITE_BISHOP), false);
        TS_ASSERT_EQUALS(slach::IsRook(slach::WHITE_QUEEN), false);
        TS_ASSERT_EQUALS(slach::IsRook(slach::WHITE_KNIGHT), false);
        TS_ASSERT_EQUALS(slach::IsRook(slach::WHITE_PAWN), false);
        TS_ASSERT_EQUALS(slach::IsRook(slach::WHITE_ROOK), true);
        TS_ASSERT_EQUALS(slach::IsRook(slach::NO_PIECE), false);

        TS_ASSERT_EQUALS(slach::IsQueen(slach::BLACK_KING), false);
        TS_ASSERT_EQUALS(slach::IsQueen(slach::BLACK_BISHOP), false);
        TS_ASSERT_EQUALS(slach::IsQueen(slach::BLACK_QUEEN), true);
        TS_ASSERT_EQUALS(slach::IsQueen(slach::BLACK_KNIGHT), false);
        TS_ASSERT_EQUALS(slach::IsQueen(slach::BLACK_PAWN), false);
        TS_ASSERT_EQUALS(slach::IsQueen(slach::BLACK_ROOK), false);
        TS_ASSERT_EQUALS(slach::IsQueen(slach::WHITE_KING), false);
        TS_ASSERT_EQUALS(slach::IsQueen(slach::WHITE_BISHOP), false);
        TS_ASSERT_EQUALS(slach::IsQueen(slach::WHITE_QUEEN), true);
        TS_ASSERT_EQUALS(slach::IsQueen(slach::WHITE_KNIGHT), false);
        TS_ASSERT_EQUALS(slach::IsQueen(slach::WHITE_PAWN), false);
        TS_ASSERT_EQUALS(slach::IsQueen(slach::WHITE_ROOK), false);
        TS_ASSERT_EQUALS(slach::IsQueen(slach::NO_PIECE), false);

        TS_ASSERT_EQUALS(slach::IsKing(slach::BLACK_KING), true);
        TS_ASSERT_EQUALS(slach::IsKing(slach::BLACK_BISHOP), false);
        TS_ASSERT_EQUALS(slach::IsKing(slach::BLACK_QUEEN), false);
        TS_ASSERT_EQUALS(slach::IsKing(slach::BLACK_KNIGHT), false);
        TS_ASSERT_EQUALS(slach::IsKing(slach::BLACK_PAWN), false);
        TS_ASSERT_EQUALS(slach::IsKing(slach::BLACK_ROOK), false);
        TS_ASSERT_EQUALS(slach::IsKing(slach::WHITE_KING), true);
        TS_ASSERT_EQUALS(slach::IsKing(slach::WHITE_BISHOP), false);
        TS_ASSERT_EQUALS(slach::IsKing(slach::WHITE_QUEEN), false);
        TS_ASSERT_EQUALS(slach::IsKing(slach::WHITE_KNIGHT), false);
        TS_ASSERT_EQUALS(slach::IsKing(slach::WHITE_PAWN), false);
        TS_ASSERT_EQUALS(slach::IsKing(slach::WHITE_ROOK), false);
        TS_ASSERT_EQUALS(slach::IsKing(slach::NO_PIECE), false);
    }
};
#endif
