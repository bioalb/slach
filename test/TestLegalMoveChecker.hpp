#ifndef TESTPSEUDOLEGALMOVEGENERATOR_HPP_
#define TESTPSEUDOLEGALMOVEGENERAOTR_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include "LegalMoveChecker.hpp"
#include "Square.hpp"

class TestLegalMoveChecker : public CxxTest::TestSuite
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

        slach::LegalMoveChecker generator;

        std::vector<unsigned> pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[36],squares);
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
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[36],squares);
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
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[36],squares);
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

        slach::LegalMoveChecker generator;
        std::vector<unsigned> pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[7],squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 2u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 13);//f2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 22);//g3

        //put a black piece on a possible destination square (test the block by your own)
        squares[22]->SetPieceOnThisSquare(slach::BLACK_ROOK);//g3
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[7], squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 1u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 13 );//f2

        //put a white piece on a possible destination square (can capture)
        squares[22]->SetPieceOnThisSquare(slach::WHITE_ROOK);//g3
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[7],squares);
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

        slach::LegalMoveChecker generator;

        std::vector<unsigned> pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[35], squares);
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
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[35],squares);
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
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[35],squares);
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
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[0],squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 0u);
    }

    void testPawnMoves(void)
    {
        std::vector<slach::Square* > squares;
        squares.resize(64u);
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            squares[i] = new slach::Square();
            squares[i]->SetIndexFromA1(i);
            //put a pawn on d5
            if (i==35u)//d5
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_PAWN);
            }
            else
            {
                squares[i]->SetPieceOnThisSquare(slach::NO_PIECE);
            }
        }

        slach::LegalMoveChecker generator;

        std::vector<unsigned> pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[35], squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 1u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 43);//d6

        //put a blockage on d6 by own colour (white pawn)
        squares[43]->SetPieceOnThisSquare(slach::WHITE_PAWN);
        //no move available
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[35],squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 0u);

        //pawn on a2
        squares[8]->SetPieceOnThisSquare(slach::WHITE_PAWN);
        //two moves available: a3 and a4
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[8],squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 2u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 16u);//a3
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 24u);//a4

        //pawn capture, there is a black bishop on b3
        squares[17]->SetPieceOnThisSquare(slach::BLACK_BISHOP);
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[8],squares);
        //now the bishop can also be taken
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 3u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 16u);//a3
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 24u);//a4
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 17u);//b3

        //black pawn on a7
        squares[48]->SetPieceOnThisSquare(slach::BLACK_PAWN);
        //two moves available: a6 and a5
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[48],squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 2u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 40u);//a5
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 32u);//a6

        //pawn capture, there is a white queen on b6
        squares[41]->SetPieceOnThisSquare(slach::WHITE_QUEEN);
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[48],squares);
        //now the queen can also be taken
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 3u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 40u);//a5
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 32u);//a6
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 41u);//b6
    }

    void testKingMoves(void)
    {
        std::vector<slach::Square* > squares;
        squares.resize(64u);
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            squares[i] = new slach::Square();
            squares[i]->SetIndexFromA1(i);
            //put the king on e1
            if (i==4u)//e1
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_KING);
            }
            else if (i==60)//e8
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_KING);
            }
            else
            {
                squares[i]->SetPieceOnThisSquare(slach::NO_PIECE);
            }
        }

        slach::LegalMoveChecker generator;

        std::vector<unsigned> pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[4u],squares);
        //first case, there is no rook, can't castle
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 5u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 3u);//d1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 5u);//f1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 11u);//d2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 12u);//e2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 13u);//f2

        //put a rook on a1, then it can castle queenside
        squares[0]->SetPieceOnThisSquare(slach::WHITE_ROOK);
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[4u],squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 6u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 3u);//d1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 5u);//f1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 11u);//d2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 12u);//e2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 13u);//f2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[5], 2u);//c1, the castle queenside

        //put a rook on h1, then it can castle queenside AND KINGSIDE
        squares[7]->SetPieceOnThisSquare(slach::WHITE_ROOK);
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[4u],squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 7u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 3u);//d1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 5u);//f1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 11u);//d2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 12u);//e2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 13u);//f2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[5], 6u);//g1, castle kingside
        TS_ASSERT_EQUALS(pseudo_valid_destinations[6], 2u);//c1, the castle queenside

        //add a bishop on  f1, then it can castle ONLY queenside
        squares[5]->SetPieceOnThisSquare(slach::WHITE_BISHOP);
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[4u],squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 5u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 3u);//d1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 11u);//d2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 12u);//e2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 13u);//f2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 2u);//c1, the castle queenside

        //add a bishop on  c1, no more castles
        squares[2]->SetPieceOnThisSquare(slach::WHITE_BISHOP);
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[4u],squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 4u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 3u);//d1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 11u);//d2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 12u);//e2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 13u);//f2

        /////////////////
        ///BLACK KING MOVES
        /////////////////

        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[60u],squares);
        //first case, there is no rook, can't castle
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 5u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 51u);//d7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 52u);//e7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 53u);//f7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 59u);//d8
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 61u);//f8

        //put a rook on h8, then it can castle kingside
        squares[63]->SetPieceOnThisSquare(slach::BLACK_ROOK);
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[60u],squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 6u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 51u);//d7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 52u);//e7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 53u);//f7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 59u);//d8
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 61u);//f8
        TS_ASSERT_EQUALS(pseudo_valid_destinations[5], 62u);//g8, the castle kingside

        //put a rook on a8, then it can castle queenside AND KINGSIDE
        squares[56]->SetPieceOnThisSquare(slach::BLACK_ROOK);
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[60u],squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 7u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 51u);//d7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 52u);//e7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 53u);//f7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 59u);//d8
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 61u);//f8
        TS_ASSERT_EQUALS(pseudo_valid_destinations[5], 62u);//g8, the castle kingside
        TS_ASSERT_EQUALS(pseudo_valid_destinations[6], 58u);//c8, the castle queenside

        //add a bishop on  f8, then it can castle ONLY queenside
        squares[61]->SetPieceOnThisSquare(slach::BLACK_BISHOP);
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[60u],squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 5u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 51u);//d7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 52u);//e7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 53u);//f7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 59u);//d8
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 58u);//c8, the castle queenside

        //add a bishop on  c8, no more castles
        squares[58]->SetPieceOnThisSquare(slach::BLACK_BISHOP);
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[60u],squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 4u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 51u);//d7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 52u);//e7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 53u);//f7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 59u);//d8
    }

    void testRookMoves(void)
    {
        std::vector<slach::Square* > squares;
        squares.resize(64u);
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            squares[i] = new slach::Square();
            squares[i]->SetIndexFromA1(i);
            //put a rook on a1
            if (i==0u)//a1
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_ROOK);
            }
            else if (i==8)//black rook on a2
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_ROOK);
            }
            else
            {
                squares[i]->SetPieceOnThisSquare(slach::NO_PIECE);
            }
        }
        slach::LegalMoveChecker generator;

        //moves of the white rook
        std::vector<unsigned> pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[0u],squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 8u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 1u);//b1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 2u);//c1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 3u);//d1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 4u);//e1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 5u);//f1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[5], 6u);//g1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[6], 7u);//h1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[7], 8u);//capture the black rook on a2

        //moves of the black rook
        pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[8u],squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 14u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 0u);//capture on a1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 9u);//b2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 10u);//c2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 11u);//d2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 12u);//e2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[5], 13u);//f2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[6], 14u);//g2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[7], 15u);//h2
        TS_ASSERT_EQUALS(pseudo_valid_destinations[8], 16u);//a3
        TS_ASSERT_EQUALS(pseudo_valid_destinations[9], 24u);//a4
        TS_ASSERT_EQUALS(pseudo_valid_destinations[10], 32u);//a5
        TS_ASSERT_EQUALS(pseudo_valid_destinations[11], 40u);//a6
        TS_ASSERT_EQUALS(pseudo_valid_destinations[12], 48u);//a7
        TS_ASSERT_EQUALS(pseudo_valid_destinations[13], 56u);//a8
    }

    void testQueenMoves(void)
    {
        std::vector<slach::Square* > squares;
        squares.resize(64u);
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            squares[i] = new slach::Square();
            squares[i]->SetIndexFromA1(i);
            //put a queen on a1
            if (i==0u)//a1
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_QUEEN);
            }
            else if ( (i==8) || (i==17) || (i==18) )//pawns on a2, b3 and c3
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_PAWN);
            }
            else
            {
                squares[i]->SetPieceOnThisSquare(slach::NO_PIECE);
            }
        }
        slach::LegalMoveChecker generator;

        //moves of the white queen
        std::vector<unsigned> pseudo_valid_destinations = generator.GetTargetSquaresFromOrigin(squares[0u],squares);
        TS_ASSERT_EQUALS(pseudo_valid_destinations.size(), 8u);
        TS_ASSERT_EQUALS(pseudo_valid_destinations[0], 1u);//b1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[1], 2u);//c1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[2], 3u);//d1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[3], 4u);//e1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[4], 5u);//f1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[5], 6u);//g1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[6], 7u);//h1
        TS_ASSERT_EQUALS(pseudo_valid_destinations[7], 9u);//b2
    }
};
#endif
