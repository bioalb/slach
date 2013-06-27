#ifndef _POSITION_HPP_
#define _POSITION_HPP_

#include <string>
#include <vector>
#include "SlachTypes.hpp"
#include "Square.hpp"
#include "FenHandler.hpp"
#include "LegalMoveChecker.hpp"

namespace slach
{
class Position
{

private :

    /**Cache for the features of a fen position other than the pieces*/
	FenPositionFeatures mPositionFeatures;

	/**Cache for the fen string corresponding to this position*/
	std::string mCurrentFenPosition;

    /**A pointer to a FenHandler object. Initialised in constructor*/
    FenHandler* mpFenHandler;

    /**A pointer to an EngineInterface object. Initialised in constructor*/
    LegalMoveChecker* mpLegalMoveChecker;

    /**Needed for storing whether a move gives check or not from this position*/
    bool  mMoveGivesCheck;
    slach::PieceType mWhitePromotionPiece;
    slach::PieceType mBlackPromotionPiece;
    /**
     * Helper method that does the following:
     * - it re-arranges the squares according to the special move.
     * - updates castling rights accordingly
     *
     * @param rMove (input) the move to be processed
     * @param rSquares (will change) the representation of the chessboard
     */
    void ProcessSpecialMove(const Move& rMove, std::vector<Square*>& rSquares);

    /**
     * Helper method that actually moves the pieces according to rMove.
     * No check is performed. Special Moves are taken care of by another method (ProcessSpecialMove)
     *
     * @param rMove the move to be performed
     * @param rSquares (will change) the representation of the chessboard
     */
    void MoveThePieces(const Move& rMove, std::vector<Square*>& rSquares);

public :

    /**
     * Constructor
     */
	Position();

	/**
	 * Destructor
	 */
	~Position();

	/**
	 * Sets the position according to fenPosition. When you call this method,
	 * the member variable that stores the features of the position. Also, the picees
	 * are arranged on the squares pointed by the vector in rSquares
	 *
	 * @param  fenPosition (input) the FEN position we wish to set.
	 * @param rSquares (output) vector of pointers to square. The squares will be occupied by the correct pieces
	 * @return 0 if the fen is valid and the pieces have been moved, non-zero otherwise.
	 */
	int SetFromFen(const std::string& fenPosition, std::vector<Square*>& rSquares);

	/**
	 * Returns true of the move is legal in the current position.
	 * The move object itself is changed if this method figures that the move is giving check.
	 *
	 * @param rMove the move we wish to check.
	 * @param rSquares the squares that describe the position.
	 */
	bool IsMoveLegal(Move& rMove, std::vector<Square*>& rSquares);

	void UpdatePositionWithMove(Move& rMove, std::vector<Square*>& rSquares);

	Colour GetTurnToMove() const;

    /**
     * Allows ot set a promotion piece different from the queen.
     * It throws an exception if you set a pawn
     *
     * @param piece the promotion piece. Colour will be assigned automatically
     */
    void SetPromotionPiece(slach::PieceType piece);

    std::string GetPositionAsFen() const;

    slach::FenPositionFeatures GetPositionFeatures() const;
};


}

#endif //  _POSITION_HPP_

