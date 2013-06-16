#ifndef _MOVE_HPP_
#define _MOVE_HPP_

#include <string>
#include <vector>
#include "SlachTypes.hpp"
#include "Square.hpp"

namespace slach
{

/**
 * The MOVE class. This class holds two pointers to teh roigin and destination squares of this move.
 * It makes available some utility methods to figure out the nature of the move
 * (e.g., castling, promotion, etc).
 */
class Move
{

private :

    /**Cache for the pointer too the origin square*/
    Square* mpOrigin;
    /**Cache for the pointer too the destination square*/
    Square* mpDestination;

public :

    /** Default constructor*/
    Move() = default;

    /**
     * Constructor
     *
     * @param pOrigin pointer to the origin square
     * @param pDestination pointer to the destinations quare
     */
    Move(Square* pOrigin, Square* pDestination);

    /**
     * Destructor
     *
     */
    ~Move();

    /**
     * Access method for the origin square
     */
    Square* GetOrigin() const;

    /**
     * Access method for the destination square
     */
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

    /**
     * Returns true if the move indicates that white
     * intends to move the rook on h1
     */
    bool IsKingSideWhiteRookMoving() const;

    /**
     * Returns true if the move indicates that white
     * intends to move the rook on a1
     */
    bool IsQueenSideWhiteRookMoving() const;

    /**
     * Returns true if the move indicates that black
     * intends to move the rook on h8
     */
    bool IsKingSideBlackRookMoving() const;

    /**
     * Returns true if the move indicates that black
     * intends to move the rook on a8
     */
    bool IsQueenSideBlackRookMoving() const;


};
}//namespace slach
#endif //_MOVE_HPP_

