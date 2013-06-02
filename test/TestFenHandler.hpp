#ifndef TESTFENHANDLER_HPP_
#define TESTFENHANDLER_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include "FenHandler.hpp"

/**
 * Test suite to test the fen handler class
 */


class TestFenHandler : public CxxTest::TestSuite
{
public:

    void testFenValidity()
    {
        slach::FenHandler handler;

        /////////////////////////////
        //WRONG STRINGS
        /////////////////////////////

        //rubbish
        std::string test_fen = "rubbish";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        //empty
        test_fen = "";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        //spaces only
        test_fen = "       ";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        //weird
        test_fen = " w   e  / i/ r / d    ";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        //weird 2
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP blah blah    ";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        //9 pieces in first file
        test_fen = "rnbqkbnrr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        //this one has one too many indications on the 5th rank
        test_fen = "rnbqkbnr/pp1ppppp/8/2p9/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        //this one has one too consecutive numbers
        test_fen = "rnbqkbnr/pp1ppppp/8/2p15/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        //this one has a letter that does not exists (l)
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBlKB1R b KQkq - 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        //this one has one too consecutive numbers, but they add up to less than 8
        test_fen = "rnbqkbnr/pp1ppppp/8/2p11/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        //this one has one too consecutive slashes
        test_fen = "rnbqkbnr/pp1ppppp//8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        //this one has a 9 instead of a 8
        test_fen = "rnbqkbnr/pp1ppppp/9/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        //space in between is not allowed
        test_fen = "rnbqkbnr/p   p1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R o KQkq - 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        //wrong letter to move (o, should be w or b)
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R o KQkq - 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        //wrong castling rights
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w Krkq - 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        //too long castling rights
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkqKQKQ - 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        // castling rights with numbers
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQ3q - 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        // wrong en-passant
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQKq u8 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        // wrong en-passant again, two letters
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQKq ff 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        // wrong en-passant again, 3 elements
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQKq f6a 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        // wrong en-passant again, only one letter
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQKq f 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        // no en-passant
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQKq  1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        // wrong en-passant again, two numbers
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQKq 44 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        //three dashes (two would be OK)
        test_fen = "8/8/8/8/8/5k2/6p1/5K2 w --- 0 68";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        // half move number as letter
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQKq a3 r 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        // wrong full move  number as letter
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQKq a3 1 u";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        // wrong full move  numbers (no space)
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQKq a3 15";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        // no move  numbers
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQKq a3";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);

        // only one move  numbers (should be two)
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQKq a3 1";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), false);


        /////////////////////////////
        //CORRECT STRINGS
        /////////////////////////////

        test_fen = "r4rk1/1p2p1bp/pq1p2p1/2pNPp2/2Pn4/3P4/PP1Q1PPP/R2BK2R w KQ f6 0 16";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), true);

        //extra space in between sections should not be a problem
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w    KQkq - 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), true);

        // right en-passant
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQKq a3 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), true);

        // extra spaces in between sections should be no problem
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQKq       a3 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), true);

        // another right enpassant
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQKq  - 1 2";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), true);

        // correct move and half move (two digits)
        test_fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQKq a3 0 21";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), true);

        //two dashes, no space
        test_fen = "8/8/8/8/8/5k2/6p1/5K2 w -- 0 68";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), true);

        //two dashes, with space
        test_fen = "8/8/8/8/8/5k2/6p1/5K2 w - - 0 68";
        TS_ASSERT_EQUALS(handler.IsFenValid(test_fen), true);
    }

    void testAssignFen()
    {
        slach::FenHandler handler;

        //black king on f3, black pawn on g2 and white king on f1
        std::string endgame = "8/8/8/8/8/5k2/6p1/5K2 w - - 0 68";
        TS_ASSERT_EQUALS(handler.IsFenValid(endgame), true);

        //create a vector of squares for testing purposes
        std::vector<slach::Square* > squares;
        squares.resize(64u);
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            squares[i] = new slach::Square();
            squares[i]->SetPieceOnThisSquare(slach::BLACK_BISHOP);//for testing, we start with all bishops!!
        }

        int rc = handler.SetPositionFromFen(endgame, squares);
        TS_ASSERT_EQUALS(rc,0);

        //check the vector of squares one by one
        for (unsigned i = 0; i < squares.size(); ++i)
        {

            if (i==5u)//f1
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::WHITE_KING);
            }
            else if (i==21u)//f3
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_KING);
            }
            else if (i==14u)//g2
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_PAWN);
            }
            else
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::NO_PIECE);
            }
        }
        TS_ASSERT_EQUALS(handler.WhosTurnIsIt(), slach::WHITE);

        //clear up memory
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            delete squares[i];
        }
    }

    void testAnotherValidFen()
    {
        slach::FenHandler handler;

        //white king on e2, black king on c3, black rook on f4 white pawn on h4 and g5, black pawn on h5, g56 and c7
        std::string endgame = "8/2p5/6p1/6Pp/5r1P/2k5/4K3/8 b - - 1 47";
        TS_ASSERT_EQUALS(handler.IsFenValid(endgame), true);

        //create a vector of squares for testing purposes
        std::vector<slach::Square* > squares;
        squares.resize(64u);
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            squares[i] = new slach::Square();
            squares[i]->SetPieceOnThisSquare(slach::BLACK_BISHOP);//for testing, we start with all bishops!!
        }

        int rc = handler.SetPositionFromFen(endgame, squares);
        TS_ASSERT_EQUALS(rc,0);

        //check the vector of squares one by one
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            if (i==12u)//e2
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::WHITE_KING);
            }
            else if (i==18u)//c3
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_KING);
            }
            else if (i==29u)//f4
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_ROOK);
            }
            else if ( (i==31u) || (i==38) )//h4 or g5
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::WHITE_PAWN);
            }
            else if ( (i==39u) || (i==46) || (i==50) )//h5 or g6 or c7
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_PAWN);
            }
            else
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::NO_PIECE);
            }
        }
        TS_ASSERT_EQUALS(handler.WhosTurnIsIt(), slach::BLACK);

        //clear up memory
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            delete squares[i];
        }
    }

    void testAssignFenStrangeCases()
    {
        slach::FenHandler handler;
        //some valid fen
        std::string endgame = "8/8/8/8/8/5k2/6p1/5K2 w - - 0 68";
        TS_ASSERT_EQUALS(handler.IsFenValid(endgame), true);

        //create a vector of squares for testing purposes...
        std::vector<slach::Square* > squares;
        //but one element short
        squares.resize(63u);
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            squares[i] = new slach::Square();
            squares[i]->SetPieceOnThisSquare(slach::BLACK_BISHOP);//for testing, we start with all bishops!!
        }

        //check that the method returns 1 as error code...
        int rc = handler.SetPositionFromFen(endgame, squares);
        TS_ASSERT_EQUALS(rc,1);

        //..and that it didn't touch anything else
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            TS_ASSERT_EQUALS( squares[i]->GetPieceOnThisSquare(), slach::BLACK_BISHOP);
        }

        //now check the case of a vector of NULL pointers (should not segfault, it should simply return 1)

        //create a vector of squares for testing purposes...
        std::vector<slach::Square* > null_squares;
        null_squares.resize(64u);

        //check that the method returns 1 as error code as the pointers point to NULL...
        rc = handler.SetPositionFromFen(endgame, null_squares);
        TS_ASSERT_EQUALS(rc,1);


        // now check that an invalid fen does not change anything

        //some invalid fen
        std::string invalid_endgame = "8/8/9/8/8/5k2/6p1/5K2 w - - 0 68";
        TS_ASSERT_EQUALS(handler.IsFenValid(invalid_endgame), false);

        //create a vector of valid squares for testing purposes...
        std::vector<slach::Square* > ok_squares;
        ok_squares.resize(64u);
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            ok_squares[i] = new slach::Square();
            ok_squares[i]->SetPieceOnThisSquare(slach::BLACK_BISHOP);//for testing, we start with all bishops!!
        }

        //check that the method returns 1 as error code...
        rc = handler.SetPositionFromFen(invalid_endgame, ok_squares);
        TS_ASSERT_EQUALS(rc,1);

        //..and that it didn't touch anything else
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            TS_ASSERT_EQUALS( ok_squares[i]->GetPieceOnThisSquare(), slach::BLACK_BISHOP);
        }

        //clear up memory
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            delete squares[i];
            delete ok_squares[i];
        }
    }

    void TestGetFenOrdinaryMove()
    {
        //create a vector of squares for testing purposes
        std::vector<slach::Square* > squares;
        squares.resize(64u);
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            squares[i] = new slach::Square();
        }

        //fill in the vector of squares with a known position
        //this is a position from one of chessworld games (8750737)
        // a picture is stored in test/data/test_position_2.png for reference
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            if (i==12u)//e2
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_KING);
            }
            else if (i==55u)//h7
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_KING);
            }
            else if ( (i==8u) || (i==9u) || (i==10u) || (i==20u) || (i==36u) || (i==38u) || (i==39u))//a2, b2, c2 , e3, e5, g5, h5
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_PAWN);
            }
            else if ( (i==48u) || (i==41u) || (i==35u) || (i==37u) )//a7, b6, d5, f5
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_PAWN);
            }
            else if (i==44u)//e6
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_BISHOP);
            }
            else
            {
                squares[i]->SetPieceOnThisSquare(slach::NO_PIECE);
            }
        }

        std::vector<slach::CastlingRights> empty_vec;

        slach::FenHandler handler;
        std::string calculated_fen = handler.GetFenFromPosition(squares,slach::BLACK,empty_vec,NULL,4,40);
        std::string valid_fen = "8/p6k/1p2b3/3pPpPP/8/4P3/PPP1K3/8 b - - 4 40";

        TS_ASSERT_EQUALS(calculated_fen, valid_fen);

        //clear up memory
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            delete squares[i];
        }
    }

    void TestGetFenWithEnpassant()
    {
        //create a vector of squares for testing purposes
        std::vector<slach::Square* > squares;
        squares.resize(64u);
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            squares[i] = new slach::Square();
        }

        //fill in the vector of squares with a known position
        //initial position after 1.e4
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            if (i==0u || i==7u)//a1 and h1
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_ROOK);
            }
            else if (i==1u || i==6u)//b1 and g1
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_KNIGHT);
            }
            else if (i==2u || i==5u)//c1 and f1
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_BISHOP);
            }
            else if (i==3u)//d1
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_QUEEN);
            }
            else if (i==4u)//e1
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_KING);
            }
            else if ( ( i>7u && i<16u && i!=12u) || i==28u)//12 is e2, pawn was moved to e4 (28)
            {
                squares[i]->SetPieceOnThisSquare(slach::WHITE_PAWN);
            }
            //black pieces
            else if (i==56u || i==63u)//a8 and h8
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_ROOK);
            }
            else if (i==57u || i==62u)//b8 and g8
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_KNIGHT);
            }
            else if (i==58u || i==61u)//c8 and f8
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_BISHOP);
            }
            else if (i==59u)//d8
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_QUEEN);
            }
            else if (i==60u)//e8
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_KING);
            }
            else if ( i>47u && i<56u )
            {
                squares[i]->SetPieceOnThisSquare(slach::BLACK_PAWN);
            }
            else
            {
                squares[i]->SetPieceOnThisSquare(slach::NO_PIECE);
            }
        }

        slach::FenHandler handler;
        std::vector<slach::CastlingRights> cr = {slach::WHITE_KINGSIDE, slach::WHITE_QUEENSIDE, slach::BLACK_KINGSIDE, slach::BLACK_QUEENSIDE};

        slach::Square* p_enpassantsquare = new slach::Square();
        p_enpassantsquare->SetFile("e");
        p_enpassantsquare->SetRank("3");
        std::string calculated_fen = handler.GetFenFromPosition(squares,slach::BLACK,cr,p_enpassantsquare,0,1);
        //initial position after 1. e4 (from wikipedia)
        std::string valid_fen = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";

        TS_ASSERT_EQUALS(calculated_fen, valid_fen);

        //clear up memory
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            delete squares[i];
        }
        delete p_enpassantsquare;

    }


};
#endif
