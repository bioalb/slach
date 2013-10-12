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

enum GameResult
{
    WHITE_WIN = 0,
    BLACK_WIN,
    DRAW,
    UNKNOWN //game still in progress, game abandoned, or result otherwise unknown
};
enum SpecialMoveType
{
    WHITE_CASTLE_KINGSIDE = 0,
    BLACK_CASTLE_KINGSIDE,
    WHITE_CASTLE_QUEENSIDE,
    BLACK_CASTLE_QUEENSIDE,
    WHITEPAWN_PROMOTES,
    BLACKPAWN_PROMOTES,
    ORDINARY_MOVE
};

enum CastlingRights
{
    WHITE_KINGSIDE = 0,
    WHITE_QUEENSIDE,
    BLACK_KINGSIDE,
    BLACK_QUEENSIDE
};

enum Colour
{
    WHITE = 0,
    BLACK
};

struct FenPositionFeatures
{
	unsigned mMoveCounter;
	unsigned mHalfMoveClockSinceLastPawnMove;
	unsigned mIndexOfEnpassant;
	std::vector<CastlingRights> mCastlingRights;
	Colour mTurnToMove;

	FenPositionFeatures()
	   : mMoveCounter(1),
	     mHalfMoveClockSinceLastPawnMove(0),
	     mIndexOfEnpassant(64),
	     mCastlingRights{WHITE_KINGSIDE,WHITE_QUEENSIDE, BLACK_KINGSIDE, BLACK_QUEENSIDE },
	     mTurnToMove(WHITE)
	{}
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

}//namespace slach
#endif
