#ifndef TESTCHESSBOARD_HPP_
#define TESTCHESSBOARD_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include "../src/ChessBoard.hpp"
#include "SlachTypes.hpp"

/**
 * Test suite to test the chessboard
 */

class TestChessBoard : public CxxTest::TestSuite
{
private:

    /**
     * helper method to check the initial chess position
     */
    void CheckInitialPosition(const std::vector<slach::Square* >& rSquares)
    {
        for (unsigned i = 0; i < rSquares.size(); ++i)
        {
            //first rank
            if ((rSquares[i]->GetFile()=='a')&&(rSquares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::WHITE_ROOK);
            }
            else if ((rSquares[i]->GetFile()=='h')&&(rSquares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::WHITE_ROOK);
            }
            else if ((rSquares[i]->GetFile()=='b')&&(rSquares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::WHITE_KNIGHT);
            }
            else if ((rSquares[i]->GetFile()=='g')&&(rSquares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::WHITE_KNIGHT);
            }
            else if ((rSquares[i]->GetFile()=='c')&&(rSquares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::WHITE_BISHOP);
            }
            else if ((rSquares[i]->GetFile()=='f')&&(rSquares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::WHITE_BISHOP);
            }
            else if ((rSquares[i]->GetFile()=='d')&&(rSquares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::WHITE_QUEEN);
            }
            else if ((rSquares[i]->GetFile()=='e')&&(rSquares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::WHITE_KING);
            }
            //second rank, all white pawns
            else if(rSquares[i]->GetRank()=='2' && rSquares[i]->IsBorderSquare()==false)
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::WHITE_PAWN);
            }
            //seventh rank, all black pawns
            else if (rSquares[i]->GetRank()=='7' && rSquares[i]->IsBorderSquare()==false)
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::BLACK_PAWN);
            }

            //EIGTH rank
            else if ((rSquares[i]->GetFile()=='a')&&(rSquares[i]->GetRank()=='8'))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::BLACK_ROOK);
            }
            else if ((rSquares[i]->GetFile()=='h')&&(rSquares[i]->GetRank()=='8'))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::BLACK_ROOK);
            }
            else if ((rSquares[i]->GetFile()=='b')&&(rSquares[i]->GetRank()=='8'))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::BLACK_KNIGHT);
            }
            else if ((rSquares[i]->GetFile()=='g')&&(rSquares[i]->GetRank()=='8'))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::BLACK_KNIGHT);
            }
            else if ((rSquares[i]->GetFile()=='c')&&(rSquares[i]->GetRank()=='8'))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::BLACK_BISHOP);
            }
            else if ((rSquares[i]->GetFile()=='f')&&(rSquares[i]->GetRank()=='8'))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::BLACK_BISHOP);
            }
            else if ((rSquares[i]->GetFile()=='d')&&(rSquares[i]->GetRank()=='8'))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::BLACK_QUEEN);
            }
            else if ((rSquares[i]->GetFile()=='e')&&(rSquares[i]->GetRank()=='8'))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::BLACK_KING);
            }
            else
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),slach::NO_PIECE);
            }
        }
    }
public:

    void testBasicBoard(void)
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        std::vector<slach::Square* > squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(squares.size(), 64u);

        //a1
        TS_ASSERT_EQUALS(squares[0]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[0]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[0]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[0]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[0]->GetFile(), 'a');
        TS_ASSERT_EQUALS(squares[0]->GetRank(), '1');
        TS_ASSERT_EQUALS(squares[0]->IsCoordinatePrintable(), false);

        //b1
        TS_ASSERT_EQUALS(squares[1]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[1]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[1]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[1]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[1]->GetFile(), 'b');
        TS_ASSERT_EQUALS(squares[1]->GetRank(), '1');

        //c1
        TS_ASSERT_EQUALS(squares[2]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[2]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[2]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[2]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[2]->GetFile(), 'c');
        TS_ASSERT_EQUALS(squares[2]->GetRank(), '1');

        //d1
        TS_ASSERT_EQUALS(squares[3]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[3]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[3]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[3]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[3]->GetFile(), 'd');
        TS_ASSERT_EQUALS(squares[3]->GetRank(), '1');

        //e1
        TS_ASSERT_EQUALS(squares[4]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[4]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[4]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[4]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[4]->GetFile(), 'e');
        TS_ASSERT_EQUALS(squares[4]->GetRank(), '1');

        //f1
        TS_ASSERT_EQUALS(squares[5]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[5]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[5]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[5]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[5]->GetFile(), 'f');
        TS_ASSERT_EQUALS(squares[5]->GetRank(), '1');

        //g1
        TS_ASSERT_EQUALS(squares[6]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[6]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[6]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[6]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[6]->GetFile(), 'g');
        TS_ASSERT_EQUALS(squares[6]->GetRank(), '1');

        //h1
        TS_ASSERT_EQUALS(squares[7]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[7]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[7]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[7]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[7]->GetFile(), 'h');
        TS_ASSERT_EQUALS(squares[7]->GetRank(), '1');


        //a2
        TS_ASSERT_EQUALS(squares[8]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[8]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[8]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[8]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[8]->GetFile(), 'a');
        TS_ASSERT_EQUALS(squares[8]->GetRank(), '2');

        //b2
        TS_ASSERT_EQUALS(squares[9]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[9]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[9]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[9]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[9]->GetFile(), 'b');
        TS_ASSERT_EQUALS(squares[9]->GetRank(), '2');

        //c2
        TS_ASSERT_EQUALS(squares[10]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[10]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[10]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[10]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[10]->GetFile(), 'c');
        TS_ASSERT_EQUALS(squares[10]->GetRank(), '2');

        //d2
        TS_ASSERT_EQUALS(squares[11]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[11]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[11]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[11]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[11]->GetFile(), 'd');
        TS_ASSERT_EQUALS(squares[11]->GetRank(), '2');

        //e2
        TS_ASSERT_EQUALS(squares[12]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[12]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[12]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[12]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[12]->GetFile(), 'e');
        TS_ASSERT_EQUALS(squares[12]->GetRank(), '2');

        //f2
        TS_ASSERT_EQUALS(squares[13]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[13]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[13]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[13]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[13]->GetFile(), 'f');
        TS_ASSERT_EQUALS(squares[13]->GetRank(), '2');

        //g2
        TS_ASSERT_EQUALS(squares[14]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[14]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[14]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[14]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[14]->GetFile(), 'g');
        TS_ASSERT_EQUALS(squares[14]->GetRank(), '2');

        //h2
        TS_ASSERT_EQUALS(squares[15]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[15]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[15]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[15]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[15]->GetFile(), 'h');
        TS_ASSERT_EQUALS(squares[15]->GetRank(), '2');


        //////
        // 3rd rank (some squares)
        //////

        //a3
        TS_ASSERT_EQUALS(squares[16]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[16]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[16]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[16]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[16]->GetFile(), 'a');
        TS_ASSERT_EQUALS(squares[16]->GetRank(), '3');

        //c3
        TS_ASSERT_EQUALS(squares[18]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[18]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[18]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[18]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[18]->GetFile(), 'c');
        TS_ASSERT_EQUALS(squares[18]->GetRank(), '3');

        //////
        // 8th rank (some squares)
        //////

        //h8
        TS_ASSERT_EQUALS(squares[63]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[63]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[63]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[63]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[63]->GetFile(), 'h');
        TS_ASSERT_EQUALS(squares[63]->GetRank(), '8');

        //g8
        TS_ASSERT_EQUALS(squares[62]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[62]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[62]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[62]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[62]->GetFile(), 'g');
        TS_ASSERT_EQUALS(squares[62]->GetRank(), '8');

        //a8
        TS_ASSERT_EQUALS(squares[56]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[56]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[56]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[56]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[56]->GetFile(), 'a');
        TS_ASSERT_EQUALS(squares[56]->GetRank(), '8');

        //check the index within the Square class
        for (unsigned index = 0; index < squares.size(); ++index)
        {
            TS_ASSERT_EQUALS(squares[index]->GetIndexFromA1(), index);
        }

    }

    void testInitialPosition(void)
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        std::vector<slach::Square* > squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(squares.size(), 64u);
        CheckInitialPosition(squares);
    }

    void testMakeAMove()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();

        //non-capturing move
        std::vector<slach::Square*> squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(squares[12]->GetFile(),'e');
        TS_ASSERT_EQUALS(squares[20]->GetFile(),'e');
        TS_ASSERT_EQUALS(squares[12]->GetRank(),'2');
        TS_ASSERT_EQUALS(squares[20]->GetRank(),'3');

        TS_ASSERT_EQUALS(squares[12]->GetPieceOnThisSquare(),slach::WHITE_PAWN);
        TS_ASSERT_EQUALS(squares[20]->GetPieceOnThisSquare(),slach::NO_PIECE);

        slach::Move non_capturing_move(squares[12], squares[20]);

        //make the move e2-e3
        my_cb.MakeThisMove(non_capturing_move);

        //size is the same
        std::vector<slach::Square*> updated_squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(updated_squares[12]->GetPieceOnThisSquare(),slach::NO_PIECE);//e2 now empty
        TS_ASSERT_EQUALS(updated_squares[20]->GetPieceOnThisSquare(),slach::WHITE_PAWN);//e3 with white pawn

        //make sure we do not screw up the coordinates
        TS_ASSERT_EQUALS(updated_squares[12]->GetFile(),'e');
        TS_ASSERT_EQUALS(updated_squares[20]->GetFile(),'e');
        TS_ASSERT_EQUALS(updated_squares[12]->GetRank(),'2');
        TS_ASSERT_EQUALS(updated_squares[20]->GetRank(),'3');

        //capturing move a2 takes a7 (a fake one, but does not matter here)

        slach::Move capturing_move( squares[8], squares[48]);//a7

        TS_ASSERT_EQUALS(squares[8]->GetPieceOnThisSquare(),slach::WHITE_PAWN);//a2, white pawn
        TS_ASSERT_EQUALS(squares[48]->GetPieceOnThisSquare(),slach::BLACK_PAWN);//a7, black pawn

        TS_ASSERT_EQUALS(squares[8]->GetFile(),'a');
        TS_ASSERT_EQUALS(squares[48]->GetFile(),'a');
        TS_ASSERT_EQUALS(squares[8]->GetRank(),'2');
        TS_ASSERT_EQUALS(squares[48]->GetRank(),'7');

        //make the move e2-e4
        my_cb.MakeThisMove(capturing_move);

        TS_ASSERT_EQUALS(squares[8]->GetPieceOnThisSquare(),slach::NO_PIECE);//e2 now empty
        TS_ASSERT_EQUALS(squares[48]->GetPieceOnThisSquare(),slach::WHITE_PAWN);//e4 with white pawn
    }

    void testSetFenPosition()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();

        std::string fen_after_2Nf3 = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
        int rc = my_cb.SetFenPosition(fen_after_2Nf3);
        TS_ASSERT_EQUALS(rc,0);
        TS_ASSERT_EQUALS(fen_after_2Nf3, my_cb.GetCurrentFenPosition());

        std::vector<slach::Square*> squares = my_cb.GetSquares();
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            //first rank
            if ((squares[i]->GetFile()=='a')&&(squares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::WHITE_ROOK);
            }
            else if ((squares[i]->GetFile()=='h')&&(squares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::WHITE_ROOK);
            }
            else if ((squares[i]->GetFile()=='b')&&(squares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::WHITE_KNIGHT);
            }
            else if ((squares[i]->GetFile()=='g')&&(squares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::NO_PIECE);//knight wne to f3
            }
            else if ((squares[i]->GetFile()=='c')&&(squares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::WHITE_BISHOP);
            }
            else if ((squares[i]->GetFile()=='f')&&(squares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::WHITE_BISHOP);
            }
            else if ((squares[i]->GetFile()=='d')&&(squares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::WHITE_QUEEN);
            }
            else if ((squares[i]->GetFile()=='e')&&(squares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::WHITE_KING);
            }
            //second rank, all white pawns
            else if(squares[i]->GetRank()=='2' && squares[i]->IsBorderSquare()==false)
            {
                if (squares[i]->GetFile()=='e')//pawn went to e4
                {
                    TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::NO_PIECE);
                }
                else
                {
                    TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::WHITE_PAWN);
                }
            }
            //seventh rank, all black pawns
            else if (squares[i]->GetRank()=='7' && squares[i]->IsBorderSquare()==false)
            {
                if (squares[i]->GetFile()=='c')//pawn went to c5
                {
                    TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::NO_PIECE);
                }
                else
                {
                    TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_PAWN);
                }
            }

            //EIGTH rank
            else if ((squares[i]->GetFile()=='a')&&(squares[i]->GetRank()=='8'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_ROOK);
            }
            else if ((squares[i]->GetFile()=='h')&&(squares[i]->GetRank()=='8'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_ROOK);
            }
            else if ((squares[i]->GetFile()=='b')&&(squares[i]->GetRank()=='8'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_KNIGHT);
            }
            else if ((squares[i]->GetFile()=='g')&&(squares[i]->GetRank()=='8'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_KNIGHT);
            }
            else if ((squares[i]->GetFile()=='c')&&(squares[i]->GetRank()=='8'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_BISHOP);
            }
            else if ((squares[i]->GetFile()=='f')&&(squares[i]->GetRank()=='8'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_BISHOP);
            }
            else if ((squares[i]->GetFile()=='d')&&(squares[i]->GetRank()=='8'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_QUEEN);
            }
            else if ((squares[i]->GetFile()=='e')&&(squares[i]->GetRank()=='8'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_KING);
            }
            else
            {
                if (((squares[i]->GetFile()=='f')&&(squares[i]->GetRank()=='3')))
                {
                    TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::WHITE_KNIGHT);
                }
                else if (((squares[i]->GetFile()=='c')&&(squares[i]->GetRank()=='5')))
                {
                    TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_PAWN);
                }
                else if (((squares[i]->GetFile()=='e')&&(squares[i]->GetRank()=='4')))
                {
                    TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::WHITE_PAWN);
                }
                else
                {
                    TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::NO_PIECE);
                }
            }
        }

        //black's turn
        TS_ASSERT_EQUALS(my_cb.WhosTurnIsIt(), slach::BLACK);
    }

    void testAnotherFen()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        //here we test that we are able to change a position from the initial position
        my_cb.SetupInitialChessPosition();
        //black king on f3, black pawn on g2 and white king on f1
        std::string endgame = "8/8/8/8/8/5k2/6p1/5K2 w - - 0 68";
        int rc = my_cb.SetFenPosition(endgame);
        TS_ASSERT_EQUALS(rc,0);
        TS_ASSERT_EQUALS(endgame, my_cb.GetCurrentFenPosition());

        std::vector<slach::Square*> squares = my_cb.GetSquares();
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            //first rank
            if ((squares[i]->GetFile()=='f')&&(squares[i]->GetRank()=='3'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_KING);
            }
            else if ((squares[i]->GetFile()=='f')&&(squares[i]->GetRank()=='1'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::WHITE_KING);
            }
            else if ((squares[i]->GetFile()=='g')&&(squares[i]->GetRank()=='2'))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::BLACK_PAWN);
            }
            else
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::NO_PIECE);
            }
        }

        TS_ASSERT_EQUALS(my_cb.WhosTurnIsIt(), slach::WHITE);
    }

    void testThatInvalidFenChangesNothing()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();

        std::string too_long = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R/8/8/8/8 b KQkq - 1 2";
        int rc = my_cb.SetFenPosition(too_long);
        TS_ASSERT_EQUALS(rc,1);

        std::string too_short = "rnbqkbnr/pp1ppppp/ b KQkq - 1 2";
        rc = my_cb.SetFenPosition(too_short);
        TS_ASSERT_EQUALS(rc,1);
        TS_ASSERT_EQUALS(my_cb.WhosTurnIsIt(), slach::WHITE);//invalid fen not applied, still white's turn

        //invalid fen, check return code and that we don't move anything on the board (all empty squares)
        std::vector<slach::Square*> squares = my_cb.GetSquares();
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),slach::NO_PIECE);
        }

        //invalid fen again, check return code and that we don't move anything on the board (after setting initial position)
        my_cb.SetupInitialChessPosition();
        TS_ASSERT_EQUALS(my_cb.WhosTurnIsIt(), slach::WHITE);
        rc = my_cb.SetFenPosition(too_long);
        TS_ASSERT_EQUALS(my_cb.WhosTurnIsIt(), slach::WHITE);//still white's trun
        squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(rc,1);
        CheckInitialPosition(squares);
        std::string init_pos_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        TS_ASSERT_EQUALS(init_pos_fen, my_cb.GetCurrentFenPosition());
    }

    void testCheckingValidityAndMakingAMove()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        //black king on f3, black pawn on g2 and white king on f1
        std::string endgame = "8/8/8/8/8/5k2/6p1/5K2 w - - 0 68";
        int rc = my_cb.SetFenPosition(endgame);
        TS_ASSERT_EQUALS(rc,0);
        TS_ASSERT_EQUALS(endgame, my_cb.GetCurrentFenPosition());

        std::vector<slach::Square*> squares = my_cb.GetSquares();
        //now make a valid move f1-g1
        slach::Move f1_g1(squares[5], squares[6]);

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(f1_g1));
        my_cb.MakeThisMove(f1_g1);
        TS_ASSERT_EQUALS(squares[5]->GetPieceOnThisSquare(), slach::NO_PIECE);
        TS_ASSERT_EQUALS(squares[6]->GetPieceOnThisSquare(), slach::WHITE_KING);

        std::string updated_endgame = "8/8/8/8/8/5k2/6p1/6K1 b - - 1 68";
        TS_ASSERT_EQUALS(my_cb.GetCurrentFenPosition(), updated_endgame);
    }

    void testMakingSeveralMovesFromStart()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        std::string initial = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        int rc = my_cb.SetFenPosition(initial);

        TS_ASSERT_EQUALS(rc,0);
        TS_ASSERT_EQUALS(initial, my_cb.GetCurrentFenPosition());

        std::vector<slach::Square*> squares = my_cb.GetSquares();
        CheckInitialPosition(squares);

        /////Initial position done, move d2-d4 now
        slach::Move d2_d4(squares[11], squares[27]);//d2-d4

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(d2_d4));
        my_cb.MakeThisMove(d2_d4);
        TS_ASSERT_EQUALS(squares[11]->GetPieceOnThisSquare(), slach::NO_PIECE);
        TS_ASSERT_EQUALS(squares[27]->GetPieceOnThisSquare(), slach::WHITE_PAWN);

        std::string after_d2_d4 = "rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq d3 0 1";
        TS_ASSERT_EQUALS(my_cb.GetCurrentFenPosition(), after_d2_d4);

        //////Black now moves e7-e5
        slach::Move e7_e5(squares[52],squares[36]);//e7-e5

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(e7_e5));
        my_cb.MakeThisMove(e7_e5);
        TS_ASSERT_EQUALS(squares[52]->GetPieceOnThisSquare(), slach::NO_PIECE);
        TS_ASSERT_EQUALS(squares[36]->GetPieceOnThisSquare(), slach::BLACK_PAWN);

        std::string after_e7_e5 = "rnbqkbnr/pppp1ppp/8/4p3/3P4/8/PPP1PPPP/RNBQKBNR w KQkq e6 0 2";
        TS_ASSERT_EQUALS(my_cb.GetCurrentFenPosition(), after_e7_e5);

        ///white captures the pawn on e5
        slach::Move d4_takes_e5(squares[27], squares[36]);//d4-e5

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(d4_takes_e5));
        my_cb.MakeThisMove(d4_takes_e5);
        TS_ASSERT_EQUALS(squares[27]->GetPieceOnThisSquare(), slach::NO_PIECE);
        TS_ASSERT_EQUALS(squares[36]->GetPieceOnThisSquare(), slach::WHITE_PAWN);

        std::string after_d4_takes_e5 = "rnbqkbnr/pppp1ppp/8/4P3/8/8/PPP1PPPP/RNBQKBNR b KQkq - 0 2";
        TS_ASSERT_EQUALS(my_cb.GetCurrentFenPosition(), after_d4_takes_e5);

        ///black plays bishop b4 check
        slach::Move bishop_b4_check(squares[61], squares[25]);//f8-b4

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(bishop_b4_check));
        my_cb.MakeThisMove(bishop_b4_check);
        TS_ASSERT_EQUALS(squares[61]->GetPieceOnThisSquare(), slach::NO_PIECE);
        TS_ASSERT_EQUALS(squares[25]->GetPieceOnThisSquare(), slach::BLACK_BISHOP);

        std::string after_bishop_b4_check = "rnbqk1nr/pppp1ppp/8/4P3/1b6/8/PPP1PPPP/RNBQKBNR w KQkq - 1 3";
        TS_ASSERT_EQUALS(my_cb.GetCurrentFenPosition(), after_bishop_b4_check);

        ///now white tries an illegal move (h2-h4) it's under check and not allowed
        slach::Move illegal_h2_h4( squares[15], squares[31]);//h2-h4

        TS_ASSERT_EQUALS(false, my_cb.IsLegalMove(illegal_h2_h4));

        // a legal move is c2-c3...
        slach::Move c2_c3 (squares[10],squares[18]);//c2-c3

        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(c2_c3));
        my_cb.MakeThisMove(c2_c3);
        TS_ASSERT_EQUALS(squares[10]->GetPieceOnThisSquare(), slach::NO_PIECE);
        TS_ASSERT_EQUALS(squares[18]->GetPieceOnThisSquare(), slach::WHITE_PAWN);

        std::string after_c2c3 =  "rnbqk1nr/pppp1ppp/8/4P3/1b6/2P5/PP2PPPP/RNBQKBNR b KQkq - 0 3";
        TS_ASSERT_EQUALS(my_cb.GetCurrentFenPosition(), after_c2c3);

        slach::Game* p_game =  my_cb.GetGame();
        TS_ASSERT_EQUALS(p_game->GetMoveList().size(), 5u);
        TS_ASSERT_EQUALS(p_game->GetMoveListAlgebraicFormat().size(), 5u);
        TS_ASSERT_EQUALS(p_game->GetMoveListAlgebraicFormat()[0], "d4");
        TS_ASSERT_EQUALS(p_game->GetMoveListAlgebraicFormat()[1], "e5");
        TS_ASSERT_EQUALS(p_game->GetMoveListAlgebraicFormat()[2], "dxe5");
        TS_ASSERT_EQUALS(p_game->GetMoveListAlgebraicFormat()[3], "Bb4+");
        TS_ASSERT_EQUALS(p_game->GetMoveListAlgebraicFormat()[4], "c3");

        TS_ASSERT_EQUALS(p_game->GetMoveList()[0].GetOrigin()->GetFile(), 'd');
        TS_ASSERT_EQUALS(p_game->GetMoveList()[0].GetOrigin()->GetRank(), '2');
        TS_ASSERT_EQUALS(p_game->GetMoveList()[0].GetDestination()->GetFile(), 'd');
        TS_ASSERT_EQUALS(p_game->GetMoveList()[0].GetDestination()->GetRank(), '4');

        ////// Trying to reset to move 2 (white to move).
        my_cb.ResetToMoveNumber(2u, slach::WHITE);
        TS_ASSERT_EQUALS(my_cb.GetCurrentFenPosition(), after_e7_e5);
        TS_ASSERT_EQUALS(squares[52]->GetPieceOnThisSquare(), slach::NO_PIECE);
        TS_ASSERT_EQUALS(squares[36]->GetPieceOnThisSquare(), slach::BLACK_PAWN);
        //bishop b4 not yet played...
        TS_ASSERT_EQUALS(squares[61]->GetPieceOnThisSquare(), slach::BLACK_BISHOP);//58
        TS_ASSERT_EQUALS(squares[25]->GetPieceOnThisSquare(), slach::NO_PIECE);//b4
    }

    void testSettingFenAndCastling()
    {
        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        std::vector<slach::Square*> squares = my_cb.GetSquares();
        CheckInitialPosition(squares);

        //this one is after 1.e4 e5 2.Nf3 Nc6 3.Bc4 Bc5 (Giuoco piano) ... now white can castle kingside, it is white's turn
    	std::string before_castling = "r1bqk1nr/pppp1ppp/2n5/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 4 4";
        int rc = my_cb.SetFenPosition(before_castling);
        TS_ASSERT_EQUALS(rc,0);
        TS_ASSERT_EQUALS(before_castling, my_cb.GetCurrentFenPosition());

        // e1-g1 (castling)
        slach::Move castle_kingside (squares[4],squares[6]);//e1-g1
        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(castle_kingside));
        my_cb.MakeThisMove(castle_kingside);

        TS_ASSERT_EQUALS(squares[4]->GetPieceOnThisSquare(), slach::NO_PIECE);//e1
        TS_ASSERT_EQUALS(squares[5]->GetPieceOnThisSquare(), slach::WHITE_ROOK);//f1 --> rook
        TS_ASSERT_EQUALS(squares[6]->GetPieceOnThisSquare(), slach::WHITE_KING);//g1
        TS_ASSERT_EQUALS(squares[7]->GetPieceOnThisSquare(), slach::NO_PIECE);//h1

        std::string after_castling = "r1bqk1nr/pppp1ppp/2n5/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQ1RK1 b kq - 5 4";
        TS_ASSERT_EQUALS(my_cb.GetCurrentFenPosition(), after_castling);

        ///reset the FEN as before castling...
        //this one is after 1.e4 e5 2.Nf3 Nc6 3.Bc4 Bc5 (Giuoco piano) ... now white can castle kingside, it is white's turn

        rc = my_cb.SetFenPosition(before_castling);
        TS_ASSERT_EQUALS(rc,0);
        TS_ASSERT_EQUALS(before_castling, my_cb.GetCurrentFenPosition());

        // e1-f1 (whote king moves)
        slach::Move e1_f1 (squares[4],squares[5]);//e1-f1
        TS_ASSERT_EQUALS(true, my_cb.IsLegalMove(e1_f1));
        my_cb.MakeThisMove(e1_f1);

        TS_ASSERT_EQUALS(squares[4]->GetPieceOnThisSquare(), slach::NO_PIECE);//e1
        TS_ASSERT_EQUALS(squares[5]->GetPieceOnThisSquare(), slach::WHITE_KING);//f1 --> rook
        TS_ASSERT_EQUALS(squares[6]->GetPieceOnThisSquare(), slach::NO_PIECE);//g1
        TS_ASSERT_EQUALS(squares[7]->GetPieceOnThisSquare(), slach::WHITE_ROOK);//h1

        std::string after_e1_f1 = "r1bqk1nr/pppp1ppp/2n5/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQ1K1R b kq - 5 4";
        TS_ASSERT_EQUALS(my_cb.GetCurrentFenPosition(), after_e1_f1);
    }
};

#endif
