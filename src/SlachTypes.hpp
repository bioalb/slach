#ifndef _PIECETYPE_HPP_
#define _PIECETYPE_HPP_

#include <vector>

namespace slach
{

static const unsigned gChessBoardSizeWB = 100u;
static const unsigned gChessBoardSize = 64u;
static const unsigned gBoardRowSize = 8u;
static const unsigned gBoardColumnSize = 8u;

const std::vector<char> gChessboardFiles = {'a','b','c','d','e','f','g','h'};
const std::vector<char> gChessboardRanks = {'1','2','3','4','5','6','7','8'};

enum SpecialMoveType
{
    WHITE_CASTLE_KINGSIDE = 0,
    BLACK_CASTLE_KINGSIDE,
    WHITE_CASTLE_QUEENSIDE,
    BLACK_CASTLE_QUEENSIDE,
    WHITEPAWN_PROMOTES_QUEEN,
    BLACKPAWN_PROMOTES_QUEEN,
    WHITEPAWN_PROMOTES_KNIGHT,
    BLACKPAWN_PROMOTES_KNIGHT,
    ORDINARY_MOVE
};

/**
 * Type for a piece on the chessboard
 */
enum PieceType
{
    WHITE_KING=0,
    BLACK_KING,
    WHITE_QUEEN,
    BLACK_QUEEN,
    WHITE_ROOK,
    BLACK_ROOK,
    WHITE_BISHOP,
    BLACK_BISHOP,
    WHITE_KNIGHT,
    BLACK_KNIGHT,
    WHITE_PAWN,
    BLACK_PAWN,
    NO_PIECE
};

enum TurnToMove
{
    WHITE = 0,
    BLACK
};

inline TurnToMove OppositeColour(TurnToMove col)
{
	if (col ==WHITE)
	{
		return BLACK;
	}
	else
	{
		return WHITE;
	}
}
inline int GetA1IndexFromx88(int x88index)
{
    int file = x88index & 7;
    int rank = x88index >> 4; // indexFromA1 / 16

    return (8*rank + file);
}

inline bool IsWhitePiece(const PieceType& piece)
{
    if (piece == WHITE_KING ||
        piece == WHITE_QUEEN ||
        piece == WHITE_ROOK ||
        piece == WHITE_BISHOP ||
        piece == WHITE_KNIGHT ||
        piece == WHITE_PAWN)
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline bool IsBlackPiece(const PieceType& piece)
{
    if (piece == BLACK_KING ||
        piece == BLACK_QUEEN ||
        piece == BLACK_ROOK ||
        piece == BLACK_BISHOP ||
        piece == BLACK_KNIGHT ||
        piece == BLACK_PAWN)
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline bool IsPieceSameAsTurn(const PieceType& piece, const TurnToMove turn)
{
    if ( (IsBlackPiece(piece) == true && turn == BLACK) ||
         (IsWhitePiece(piece) == true && turn == WHITE) )
    {
        return true;
    }
    else
    {
        return false;
    }
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

enum CastlingRights
{
    WHITE_KINGSIDE = 0,
    WHITE_QUEENSIDE,
    BLACK_KINGSIDE,
    BLACK_QUEENSIDE
};

}//namespace slach
#endif
