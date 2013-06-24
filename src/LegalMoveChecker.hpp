#ifndef _PSEUDOLEGALMOVEGENERATOR_HPP_
#define _PSEUDOLEGALMOVEGENERATOR_HPP_

#include <string>
#include <vector>
#include "SlachTypes.hpp"
#include "Game.hpp"
#include "Square.hpp"

//Forward declaration for testing
class TestLegalMoveChecker;

namespace slach
{
/**
 * This class implements a legality move checker.
 * It makes available the method
 *
 * IsMoveLegalInPosition
 *
 * that can be used to check whether a move is legal or not.
 */
class LegalMoveChecker
{
	friend class ::TestLegalMoveChecker;//for testing

private :

    /**
     * Cache for the offsets of the various pieces.
     */
    std::vector<std::vector<int> > mOffsets;

    /**
     * Cache for the offsets of the pawn captures
     */
    std::vector<int> mPawnCaptureOffsets;

	/**
	 * This is a second chessboard that is created in the constructor
	 * as empty. When checking for discovered checks,
	 * this is used to simulate the move and check whether the king
	 * is in check AFTER the move. We need this because
	 * we can''t "take back" the move if it is not legal
	 * as it would look ugly in the GUI.
	 */
    std::vector<Square*> mTempSquares;

protected :

    /**
     * Computes all the possible pseudo valid moves from an origin square
     *
     * @param pOriginSquare the square we want to pseudo-moves from
     * @param rSquares the squares with pieces on the position we wish to check
     * @param rCastlingRights the castling rights in the position (empty by default)
     * @param enPassantIndex the square index (starting from A1) where an en-passant capture may occur
     * @return a vector with the indices (starting from A1) that the piece on the origin square is pseudo-allowed to go.
     */
    std::vector<unsigned> GetPseudoLegalMovesSquaresFromOrigin(Square* pOriginSquare,
    		const std::vector<Square*>& rSquares,
    		const std::vector<CastlingRights>& rCastlingRights = std::vector<CastlingRights>(), unsigned enPassantIndex = 64u);

    /**
     * Computes the squares that are attacked by a piece from a square.
     * This is similar to GetPseudoLegalMovesSquaresFromOrigin, but differs for the pawn (which capture differently from movement)
     *
     * @param pOriginSquare the square from which we want to determine the attacked squares
     * @param rSquares the squares with pieces on the position we wish to check
     * @return a vector with the indices (starting from A1) that the piece on the origin square is attacking
     */
    std::vector<unsigned> GetAttackedSquaresFromOrigin(Square* pOriginSquare, const std::vector<Square*>& rSquares);

    /**
     * Computes the squares that have pieces on which are attacking a given square.
     *
     * @param attacked the square that we want to determine the attackers of
     * @param  rSquares the squares with pieces on the position we wish to check
     * @param attackingColour the enemy colour that we want to check we are attacked from
     * @return a vector with the indices (starting from A1) of the squares with enemy pieces attacking the square "attacked".
     */
    std::vector<unsigned> GetAttackers(Square* attacked, const std::vector<Square*>& rSquares, Colour attackingColour);

public :
    /**
     * Constructor
     */
    LegalMoveChecker();

    /**
     * Destructor
     */
    ~LegalMoveChecker();

    /**
     * Main method of this class. It check whether a move is legal in a given position.
     * The check is complete: it takes care of turn to move (can't move a white piece when it is
     * black's turn), castling legality, checks, double checks and discovered checks.
     *
     * @param rSquares the squares with pieces on the position we wish to check
     * @param rMove the move we wish to check whether it is legal or not
     * @param turn the turn to move : SLACH::WHITE or SLACH::BLACK.
     * @param castlingRights a vector with the castling rights
     * @param enpassantIindex any index of square where there is an en-passant capture possibility.
     * @param givesCheck (output) this will contain true or false whether the moves gives check or not.
     * @return true if the move is legal, false otherwise.
     */
    bool IsMoveLegalInPosition(const std::vector<Square*>& rSquares,
            const Move& rMove, Colour turn, std::vector<CastlingRights> castlingRights, unsigned enpassantIindex, bool& givesCheck);


};

}//NAMESPACE SLACH

#endif //_PSEUDOLEGALMOVEGENERATOR_HPP_
