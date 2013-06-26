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

	Position();
	~Position();

	int SetFromFen(const std::string& fenPosition, std::vector<Square*>& rSquares);

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
};


}

#endif //  _POSITION_HPP_

