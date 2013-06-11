#ifndef _PSEUDOLEGALMOVEGENERATOR_HPP_
#define _PSEUDOLEGALMOVEGENERATOR_HPP_

#include <string>
#include <vector>
#include "SlachTypes.hpp"
#include "Game.hpp"
#include "Square.hpp"

namespace slach
{

class LegalMoveChecker
{
private :

    std::vector<Square*> mTempSquares;

    std::vector<std::vector<int> > mOffsets;

    std::vector<int> mPawnCaptureOffsets;

    bool IsWithinCastlingRights(const CastlingRights& test, const std::vector<CastlingRights>& castlingRights);


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
     * Computes all the possible pseudo valid moves from an origin square
     *
     * @param pOriginSquare the square we want to pseudo-moves from
     * @return a vector with the indices (starting from A1) that the piece on the origin square is pseudo-allowed to go.
     */
    std::vector<unsigned> GetPseudoLegalMovesSquaresFromOrigin(Square* pOriginSquare, const std::vector<Square*>& rSquares, const std::vector<CastlingRights>& rCastlingRights = std::vector<CastlingRights>(), unsigned enPassantIndex = 64u);

    std::vector<unsigned> GetAttackedSquaresFromOrigin(Square* pOriginSquare, const std::vector<Square*>& rSquares);

    bool IsMoveLegalInPosition(const std::vector<Square*>& rSquares,
            const Move& rMove, TurnToMove turn, std::vector<CastlingRights> castlingRights, unsigned enpassantIindex);

    std::vector<unsigned> GetAttackers(Square* attacked, const std::vector<Square*>& rSquares, TurnToMove attackingColour);

    bool IsSquareAttacked(Square * pSquare, const std::vector<Square*>& rSquares,TurnToMove turn);
};

}//NAMESPACE SLACH

#endif //_PSEUDOLEGALMOVEGENERATOR_HPP_
