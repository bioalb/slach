#ifndef HELPER_GLOBAL_FUNCTIONS_HPP
#define HELPER_GLOBAL_FUNCTIONS_HPP

#include <string>
#include "SlachTypes.hpp"

namespace slach
{


inline Colour OppositeColour(Colour col)
{
	if (col == WHITE) return BLACK;
	return WHITE;

}
inline int GetA1IndexFromx88(int x88index)
{
    int file = x88index & 7;
    int rank = x88index >> 4; // indexFromA1 / 16

    return (8*rank + file);
}

inline bool IsWhitePiece(const PieceType& piece)
{
    return (piece == WHITE_KING ||
			 piece == WHITE_QUEEN ||
			 piece == WHITE_ROOK ||
			 piece == WHITE_BISHOP ||
			 piece == WHITE_KNIGHT ||
			 piece == WHITE_PAWN);
}

inline bool IsBlackPiece(const PieceType& piece)
{
    return (piece == BLACK_KING ||
             piece == BLACK_QUEEN ||
             piece == BLACK_ROOK ||
             piece == BLACK_BISHOP ||
             piece == BLACK_KNIGHT ||
             piece == BLACK_PAWN);
}

inline bool IsPieceSameAsTurn(const PieceType& piece, const Colour turn)
{
    return ( (IsBlackPiece(piece) == true && turn == BLACK) ||
              (IsWhitePiece(piece) == true && turn == WHITE) );
}
inline bool IsKnight(const PieceType& piece)
{
    return ((piece == WHITE_KNIGHT || piece == BLACK_KNIGHT) ? true : false);
}

inline bool IsRook(const PieceType& piece)
{
    return ((piece == WHITE_ROOK || piece == BLACK_ROOK) ? true : false);
}

inline bool IsBishop(const PieceType& piece)
{
    return ((piece == WHITE_BISHOP || piece == BLACK_BISHOP) ? true : false);
}

inline bool IsQueen(const PieceType& piece)
{
    return ((piece == WHITE_QUEEN || piece == BLACK_QUEEN) ? true : false);
}

inline bool IsKing(const PieceType& piece)
{
    return ((piece == WHITE_KING || piece == BLACK_KING) ? true : false);
}

inline bool IsPawn(const PieceType& piece)
{
    return ((piece == WHITE_PAWN || piece == BLACK_PAWN) ? true : false);
}

inline bool IsWithinCastlingRights(const CastlingRights& test, const std::vector<CastlingRights>& castlingRights)
{
    for (unsigned i = 0; i < castlingRights.size(); ++i)
    {
        if (castlingRights[i] == test) return true;
    }
    return false;
}

void DeleteCastlingRights(const CastlingRights& toBeDeleted, std::vector<CastlingRights>& rCastlingRights);

/**
 * Helper method that returns the index (counting on a chessboard from A1 to H8, from 0 to 63)
 * corresponding to the char coordinates
 *
 * @param  rFile the file of the coordinate (column), a to h
 * @param rRank the rank of the coordinate (row) 1 to 8
 * @return the index if rank and files are appropriate, 64 (out of the chessboard) otherwise
 */
unsigned GetIndexFromCoordinates(const char &rFile, const char &rRank);

/**
 * Helper method that gives you the code of the piece you pass in (Q, B etc)
 */
std::string GetPieceCodeOfThisPiece (const PieceType& piece);

/**
 * Helper method that gives you the piece based on the SAN code and the colour
 */
PieceType GetPieceFromCode (const char code, Colour col);

} // namespace slach

#endif //HELPER_GLOBAL_FUNCTIONS_HPP
