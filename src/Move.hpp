#ifndef _MOVE_HPP_
#define _MOVE_HPP_

#include <string>
#include <vector>
#include "SlachTypes.hpp"
#include "Square.hpp"

namespace slach
{

/**
 * The MOVE class
 */
class Move
{

private :

    Square* mpOrigin;
    Square* mpDestination;

public :

    Move() = default;
    Move(Square* pOrigin, Square* pDestination);

    ~Move();

    Square* GetOrigin() const;
    Square* GetDestination() const;

    /**
     * Returns true if the move indicates that white
     * intends to castle kingside
     */
    bool IsWhiteCastlingKingSide() const;

    /**
     * Returns true if the move indicates that black
     * intends to castle kingside
     */
    bool IsBlackCastlingKingSide() const;

    /**
     * Returns true if the move indicates that white
     * intends to castle queenside
     */
    bool IsWhiteCastlingQueenSide() const;

    /**
     * Returns true if the move indicates that black
     * intends to castle queenside
     */
    bool IsBlackCastlingQueenSide() const;

    /**
     * Returns true if the move is a special move.
     * Special moves are defined by being either castling
     * or promotions
     */
    bool IsSpecialMove() const;

    /**
     * Returns true if the move indicates that white
     * intends to push a pawn to promotion
     */
    bool IsWhitePromoting() const;

    /**
     * Returns true if the move indicates that black
     * intends to push a pawn to promotion
     */
    bool IsBlackPromoting() const;

};
}
#endif //_MOVE_HPP_

