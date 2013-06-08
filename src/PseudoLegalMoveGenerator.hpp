#ifndef _PSEUDOLEGALMOVEGENERATOR_HPP_
#define _PSEUDOLEGALMOVEGENERATOR_HPP_

#include <string>
#include <vector>
#include "SlachTypes.hpp"
#include "Square.hpp"

namespace slach
{

class PseudoLegalMoveGenerator
{
private :

    std::vector<unsigned> mPseudoLegalDestinations;
    std::vector<Square*> mSquares;

public :
    /**
     * Constructor
     */
    PseudoLegalMoveGenerator();

    /**
     * Destructor
     */
    ~PseudoLegalMoveGenerator();

    /**
     * Computes all the possible pseudo valid moves from an origin square
     *
     * @param pOriginSquare the square we want to pseudo-moves from
     * @return a vector with the indices (starting from A1) that the piece on the origin square is pseudo-allowed to go.
     */
    std::vector<unsigned> GetPseudoValidDestinations(Square* pOriginSquare);

    void SetSquaresInPosition(std::vector<Square*> pSquares);
};

}//NAMESPACE SLACH

#endif //_PSEUDOLEGALMOVEGENERATOR_HPP_
