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

enum CastlingRights
{
    WHITE_KINGSIDE = 0,
    WHITE_QUEENSIDE,
    BLACK_KINGSIDE,
    BLACK_QUEENSIDE
};

}//namespace slach
#endif
