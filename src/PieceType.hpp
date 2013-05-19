#ifndef _PIECETYPE_HPP_
#define _PIECETYPE_HPP_

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


#endif
