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

    bool mGivesCheck;

    std::string mAmbiguityPrefix;

    std::string mPromotionPieceCode;

public :

    /**
     * Default constructor. Initializes
     * the two pointers to NULL
     */
    Move();

    /**
     * Copy constructor. It simply assigns
     * the pointers to origin and destination.
     *
     * @param move: the move to be copied.
     */
    Move (const Move& move);

    /**
     * Constructor that takes in the move in SAN form. Because SAN form does not specify origin,
     * we need the squares and the turn to move.
     *
     * Behaviour:
     *
     * It tries to locate a destination square by analysing the SAN string.
     * If it can't be found (i.e., invalid SAN), the internal variable mpOrigin and mpDestination
     * will remain NULL. Hence this can be tested for SAN validity as well.
     *
     * If the destination is found, a search for the origin piece is performed:
     * - for pieces (Q,N,K,R,B): the LegalMoveChecker is used. If a PSEUSO-legal move is found, then the origin square is found.
     *   Note that no other legality check is performed.
     * - for pawns: the one-step movement is sought first, if no pawn is found, then two-step move is considered.
     *
     * If no suitable source is found,the SAN is considered invalid, and the move will have both pointers set tto NULL.
     *
     * Special cases of castling (O-O and O-O-O) are handled.
     *
     *
     * @param SanMove the move in SAN format
     * @param pSquares the squares that form the board. All must be well formed and with pieces assigned.
     * @param movingColour the colour that is making this move
     */
    Move (const std::string& SanMove, std::vector<Square* > pSquares, Colour movingColour);


    /**
     * Overload  = operator. It assigns
     * the pointers to origin and destination.
     *
     * @param from the move we want to be assigned from.
     */
    Move& operator=(const Move& from);

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
     * or promotions or moves that affects castling rights
     * (e.g., king moving, rook moving from initial position).
     */
    bool IsSpecialMove() const;

    /**
     * Returns true if the move requires special handling by the GUI.
     * This means that it is not a simple move where
     * you shift a piece from a square (origin) to a destination.
     *
     * Moves that require special handling involve other squares as well.
     * This includes:
     *
     *  - castling (need to move the rook as well)
     *  - promotion (need to change nature of moving piece)
     *  - en-passant capture (need to remove the capture pawn which is not on the destination square)
     */
    bool DoesMoveRequireSpecialGuiHandling() const;

    /**
     * Returns true if white his move black is trying
     * to capture en-passant.
     *
     * No legality (not even pseudo-legality) check is made here.
     */
    bool IsWhiteCapturingEnPassant() const;

    /**
     * Returns true if black his move black is trying
     * to capture en-passant.
     *
     * No legality (not even pseudo-legality) check is made here.
     */
    bool IsBlackCapturingEnPassant() const;

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

    /**
     * Returns true if the move indicates that the white king is about to move
     * Returns true if the white king is about to move, anywhere
     */
    bool IsWhiteKingMoving() const;

    /**
     * Returns true if the move indicates that the black king is about to move
     * Returns true if the black king is about to move, anywhere
     */
    bool IsBlackKingMoving() const;

    /**
     * Returns the algebraic format of this move
     */
    std::string GetMoveInAlgebraicFormat() const;

    void GivesCheck(bool gives = true);

    bool DoesMoveGiceCheck() const;

    std::string GetAmbiguityPrefix() const;

    void SetAmbiguityPrefix(std::string prefix);

    std::string GetPromotionPieceCode() const;

    void SetPromotionPiece(const slach::PieceType& piece);


};
}//namespace slach
#endif //_MOVE_HPP_

