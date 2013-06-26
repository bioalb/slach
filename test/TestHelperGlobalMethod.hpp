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

        TS_ASSERT_EQUALS(slach::GetA1IndexFromx88(49), 25);
        TS_ASSERT_EQUALS(slach::GetA1IndexFromx88(48), 24);

        TS_ASSERT_EQUALS( slach::IsPieceSameAsTurn(slach::BLACK_KING, slach::BLACK), true);

        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::BLACK_KING, slach::WHITE), false);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::BLACK_BISHOP, slach::WHITE), false);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::BLACK_QUEEN, slach::WHITE), false);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::BLACK_KNIGHT, slach::WHITE), false);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::BLACK_PAWN, slach::WHITE), false);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::BLACK_ROOK, slach::WHITE), false);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::WHITE_KING, slach::WHITE), true);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::WHITE_BISHOP, slach::WHITE), true);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::WHITE_QUEEN, slach::WHITE), true);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::WHITE_KNIGHT, slach::WHITE), true);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::WHITE_PAWN, slach::WHITE), true);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::WHITE_ROOK, slach::WHITE), true);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::NO_PIECE, slach::WHITE), false);

        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::BLACK_KING, slach::BLACK), true);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::BLACK_BISHOP, slach::BLACK), true);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::BLACK_QUEEN, slach::BLACK), true);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::BLACK_KNIGHT, slach::BLACK), true);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::BLACK_PAWN, slach::BLACK), true);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::BLACK_ROOK, slach::BLACK), true);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::WHITE_KING, slach::BLACK), false);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::WHITE_BISHOP, slach::BLACK), false);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::WHITE_QUEEN, slach::BLACK), false);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::WHITE_KNIGHT, slach::BLACK), false);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::WHITE_PAWN, slach::BLACK), false);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::WHITE_ROOK, slach::BLACK), false);
        TS_ASSERT_EQUALS(slach::IsPieceSameAsTurn(slach::NO_PIECE, slach::BLACK), false);

        TS_ASSERT_EQUALS(slach::OppositeColour(slach::BLACK), slach::WHITE);
        TS_ASSERT_EQUALS(slach::OppositeColour(slach::WHITE), slach::BLACK);

        std::vector<slach::CastlingRights> rights = {slach::WHITE_KINGSIDE, slach::WHITE_QUEENSIDE, slach::BLACK_KINGSIDE, slach::BLACK_QUEENSIDE};
        TS_ASSERT_EQUALS(true, slach::IsWithinCastlingRights(slach::WHITE_KINGSIDE, rights));
        TS_ASSERT_EQUALS(true, slach::IsWithinCastlingRights(slach::WHITE_QUEENSIDE, rights));
        TS_ASSERT_EQUALS(true, slach::IsWithinCastlingRights(slach::BLACK_KINGSIDE, rights));
        TS_ASSERT_EQUALS(true, slach::IsWithinCastlingRights(slach::BLACK_QUEENSIDE, rights));

        std::vector<slach::CastlingRights> rights_2 = {slach::WHITE_QUEENSIDE, slach::BLACK_KINGSIDE, slach::BLACK_QUEENSIDE};
        TS_ASSERT_EQUALS(false, slach::IsWithinCastlingRights(slach::WHITE_KINGSIDE, rights_2));
        TS_ASSERT_EQUALS(true, slach::IsWithinCastlingRights(slach::WHITE_QUEENSIDE, rights_2));
        TS_ASSERT_EQUALS(true, slach::IsWithinCastlingRights(slach::BLACK_KINGSIDE, rights_2));
        TS_ASSERT_EQUALS(true, slach::IsWithinCastlingRights(slach::BLACK_QUEENSIDE, rights_2));

        DeleteCastlingRights(slach::BLACK_KINGSIDE, rights);
        TS_ASSERT_EQUALS(3u, rights.size());
        TS_ASSERT_EQUALS(slach::WHITE_KINGSIDE, rights[0]);
        TS_ASSERT_EQUALS(slach::WHITE_QUEENSIDE, rights[1]);
        TS_ASSERT_EQUALS(slach::BLACK_QUEENSIDE, rights[2]);

        TS_ASSERT_EQUALS(true, slach::IsWithinCastlingRights(slach::WHITE_KINGSIDE, rights));
        TS_ASSERT_EQUALS(true, slach::IsWithinCastlingRights(slach::WHITE_QUEENSIDE, rights));
        TS_ASSERT_EQUALS(false, slach::IsWithinCastlingRights(slach::BLACK_KINGSIDE, rights));
        TS_ASSERT_EQUALS(true, slach::IsWithinCastlingRights(slach::BLACK_QUEENSIDE, rights));

        DeleteCastlingRights(slach::WHITE_QUEENSIDE, rights);
        TS_ASSERT_EQUALS(2u, rights.size());
        TS_ASSERT_EQUALS(slach::WHITE_KINGSIDE, rights[0]);
        TS_ASSERT_EQUALS(slach::BLACK_QUEENSIDE, rights[1]);

        TS_ASSERT_EQUALS(true, slach::IsWithinCastlingRights(slach::WHITE_KINGSIDE, rights));
        TS_ASSERT_EQUALS(false, slach::IsWithinCastlingRights(slach::WHITE_QUEENSIDE, rights));
        TS_ASSERT_EQUALS(false, slach::IsWithinCastlingRights(slach::BLACK_KINGSIDE, rights));
        TS_ASSERT_EQUALS(true, slach::IsWithinCastlingRights(slach::BLACK_QUEENSIDE, rights));

        DeleteCastlingRights(slach::WHITE_KINGSIDE, rights);
        TS_ASSERT_EQUALS(1u, rights.size());
        TS_ASSERT_EQUALS(slach::BLACK_QUEENSIDE, rights[0]);

        TS_ASSERT_EQUALS(false, slach::IsWithinCastlingRights(slach::WHITE_KINGSIDE, rights));
        TS_ASSERT_EQUALS(false, slach::IsWithinCastlingRights(slach::WHITE_QUEENSIDE, rights));
        TS_ASSERT_EQUALS(false, slach::IsWithinCastlingRights(slach::BLACK_KINGSIDE, rights));
        TS_ASSERT_EQUALS(true, slach::IsWithinCastlingRights(slach::BLACK_QUEENSIDE, rights));

        //try deleting something is not there and check everything is still the same
        DeleteCastlingRights(slach::WHITE_KINGSIDE, rights);
        TS_ASSERT_EQUALS(1u, rights.size());
        TS_ASSERT_EQUALS(slach::BLACK_QUEENSIDE, rights[0]);

        TS_ASSERT_EQUALS(false, slach::IsWithinCastlingRights(slach::WHITE_KINGSIDE, rights));
        TS_ASSERT_EQUALS(false, slach::IsWithinCastlingRights(slach::WHITE_QUEENSIDE, rights));
        TS_ASSERT_EQUALS(false, slach::IsWithinCastlingRights(slach::BLACK_KINGSIDE, rights));
        TS_ASSERT_EQUALS(true, slach::IsWithinCastlingRights(slach::BLACK_QUEENSIDE, rights));
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

    void TestIndexFromChars()
    {
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('a','1'),0u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('b','1'),1u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('c','1'),2u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('d','1'),3u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('e','1'),4u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('f','1'),5u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('g','1'),6u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('h','1'),7u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('a','2'),8u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('b','2'),9u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('c','2'),10u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('d','2'),11u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('e','2'),12u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('f','2'),13u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('g','2'),14u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('h','2'),15u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('a','3'),16u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('b','3'),17u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('c','3'),18u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('d','3'),19u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('e','3'),20u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('f','3'),21u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('g','3'),22u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('h','3'),23u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('a','4'),24u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('b','4'),25u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('c','4'),26u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('d','4'),27u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('e','4'),28u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('f','4'),29u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('g','4'),30u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('h','4'),31u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('a','5'),32u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('b','5'),33u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('c','5'),34u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('d','5'),35u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('e','5'),36u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('f','5'),37u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('g','5'),38u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('h','5'),39u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('a','6'),40u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('b','6'),41u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('c','6'),42u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('d','6'),43u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('e','6'),44u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('f','6'),45u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('g','6'),46u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('h','6'),47u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('a','7'),48u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('b','7'),49u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('c','7'),50u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('d','7'),51u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('e','7'),52u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('f','7'),53u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('g','7'),54u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('h','7'),55u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('a','8'),56u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('b','8'),57u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('c','8'),58u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('d','8'),59u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('e','8'),60u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('f','8'),61u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('g','8'),62u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('h','8'),63u);

        //coverage
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('k', '2'), 64u);
        TS_ASSERT_EQUALS(slach::GetIndexFromCoordinates('a', '9'), 64u);
    }
};
#endif
