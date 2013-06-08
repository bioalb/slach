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
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 19 );//d3
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 21);//f3
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 26);//c4
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 30);//g4
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 42);//c6
        TS_ASSERT_EQUALS(pseudo_valid_destinations[5], 46);//g6
        TS_ASSERT_EQUALS(pseudo_valid_destinations[6], 51);//d7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[7], 53);//f7

        //put a white piece on a possible destination square (test the block by your own)
        squares[51]->SetPieceOnThisSquare(slach::WHITE_BISHOP);//d7
        pseudo_valid_destinations = generator.GetPseudoValidDestinations(squares[36]);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 7u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 19 );//d3
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 21);//f3
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 26);//c4
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 30);//g4
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 42);//c6
        TS_ASSERT_EQUALS(pseudo_valid_destinations[5], 46);//g6
        TS_ASSERT_EQUALS(pseudo_valid_destinations[6], 53);//f7...instead of d7

        //put a black piece on a possible destination square
        squares[21]->SetPieceOnThisSquare(slach::BLACK_BISHOP);//f3
        pseudo_valid_destinations = generator.GetPseudoValidDestinations(squares[36]);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 7u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 19 );//d3
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 21);//f3, still here, knight captures bishop
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 26);//c4
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 30);//g4
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 42);//c6
        TS_ASSERT_EQUALS(pseudo_valid_destinations[5], 46);//g6
        TS_ASSERT_EQUALS(pseudo_valid_destinations[6], 53);//f7...instead of d7
    }

    void testKnightMovesFromCorner(void)
    {
        std::vector<slach::Square* > squares;
        squares.resize(64u);
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            squares[i] = new slach::Square();
            squares[i]->SetIndexFromA1(i);
            //put a black knight on h1
            if (i==7u)
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_KNIGHT);
            }
            else
            {
                squares[i]->SetPieceOnThisSquare(slach::NO_PIECE);
            }
        }

        slach::PseudoLegalMoveGenerator generator;
        generator.SetSquaresInPosition(squares);
        std::vector<unsigned> pseudo_valid_destinations = generator.GetPseudoValidDestinations(squares[7]);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 2u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 13);//f2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 22);//g3

        //put a black piece on a possible destination square (test the block by your own)
        squares[22]->SetPieceOnThisSquare(slach::BLACK_ROOK);//g3
        pseudo_valid_destinations = generator.GetPseudoValidDestinations(squares[7]);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 1u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 13 );//f2

        //put a white piece on a possible destination square (can capture)
        squares[22]->SetPieceOnThisSquare(slach::WHITE_ROOK);//g3
        pseudo_valid_destinations = generator.GetPseudoValidDestinations(squares[7]);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 2u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 13 );//f2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 22);//capture the rook on g3
    }

    void testBishopMoves(void)
    {
        std::vector<slach::Square* > squares;
        squares.resize(64u);
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            squares[i] = new slach::Square();
            squares[i]->SetIndexFromA1(i);
            //put a bishop on d5
            if (i==35u)//d5
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_BISHOP);
            }
            else
            {
                squares[i]->SetPieceOnThisSquare(slach::NO_PIECE);
            }
        }

        slach::PseudoLegalMoveGenerator generator;
        generator.SetSquaresInPosition(squares);
        std::vector<unsigned> pseudo_valid_destinations = generator.GetPseudoValidDestinations(squares[35]);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 13u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 26);//c4
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 17);//b3
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 8 );//a2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 28);//e4
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 21);//f3
        TS_ASSERT_EQUALS(pseudo_valid_destinations[5], 14 );//g2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[6], 7 );//h1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[7], 42);//c6
        TS_ASSERT_EQUALS(pseudo_valid_destinations[8], 49);//b7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[9], 56);//a8
        TS_ASSERT_EQUALS(pseudo_valid_destinations[10], 44);//e6
        TS_ASSERT_EQUALS(pseudo_valid_destinations[11], 53);//f7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[12], 62);//g8

        //put a blockage on c6 by own colour (white pawn)
        squares[42]->SetPieceOnThisSquare(slach::WHITE_PAWN);
        //now c6, b7 and a8 are not reachable
        pseudo_valid_destinations = generator.GetPseudoValidDestinations(squares[35]);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 10u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 26);//c4
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 17);//b3
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 8 );//a2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 28);//e4
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 21);//f3
        TS_ASSERT_EQUALS(pseudo_valid_destinations[5], 14 );//g2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[6], 7 );//h1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[7], 44);//e6
        TS_ASSERT_EQUALS(pseudo_valid_destinations[8], 53);//f7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[9], 62);//g8

        //put a blockage on e6 by enemy colour (black pawn)
        squares[44]->SetPieceOnThisSquare(slach::BLACK_PAWN);

        //now c6, b7 and a8 are not reachable AND f7 and g8 are not reachable either. e6 is (capture)
        pseudo_valid_destinations = generator.GetPseudoValidDestinations(squares[35]);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 8u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 26);//c4
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 17);//b3
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 8 );//a2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 28);//e4
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 21);//f3
        TS_ASSERT_EQUALS(pseudo_valid_destinations[5], 14 );//g2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[6], 7 );//h1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[7], 44);//e6

        //from empty square
        pseudo_valid_destinations = generator.GetPseudoValidDestinations(squares[0]);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 0u);
    }
};
#endif
