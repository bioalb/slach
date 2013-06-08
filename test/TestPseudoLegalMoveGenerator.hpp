#ifndef TESTPSEUDOLEGALMOVEGENERATOR_HPP_
#define TESTPSEUDOLEGALMOVEGENERAOTR_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include "PseudoLegalMoveGenerator.hpp"
#include "Square.hpp"

class TestPseudoLegalMoveGenerator : public CxxTest::TestSuite
{
public:

    void testKnightMoves(void)
    {
        std::vector<slach::Square* > squares;
        squares.resize(64u);
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            squares[i] = new slach::Square();
            squares[i]->SetIndexFromA1(i);
            //put a knight on e5
            if (i==36u)
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_KNIGHT);
            }
            else
            {
                squares[i]->SetPieceOnThisSquare(slach::NO_PIECE);
            }
        }

        slach::PseudoLegalMoveGenerator generator;
        generator.SetSquaresInPosition(squares);
        std::vector<unsigned> pseudo_valid_destinations = generator.GetPseudoValidDestinations(squares[36]);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 8u);

    }
};
#endif
