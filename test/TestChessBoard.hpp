#ifndef TESTCHESSBOARD_HPP_
#define TESTCHESSBOARD_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include "../src/ChessBoard.hpp"
#include "../src/PieceType.hpp"

/**
 * Test suite to test the chessboard
 */
class TestChessBoard : public CxxTest::TestSuite
{
private:

    /**
     * helper method to check the initial chess position
     */
    void CheckInitialPosition(const std::vector<Square* >& rSquares)
    {
        for (unsigned i = 0; i < rSquares.size(); ++i)
        {
            //first rank
            if ((rSquares[i]->GetFile()=="a")&&(rSquares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),WHITE_ROOK);
            }
            else if ((rSquares[i]->GetFile()=="h")&&(rSquares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),WHITE_ROOK);
            }
            else if ((rSquares[i]->GetFile()=="b")&&(rSquares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),WHITE_KNIGHT);
            }
            else if ((rSquares[i]->GetFile()=="g")&&(rSquares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),WHITE_KNIGHT);
            }
            else if ((rSquares[i]->GetFile()=="c")&&(rSquares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),WHITE_BISHOP);
            }
            else if ((rSquares[i]->GetFile()=="f")&&(rSquares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),WHITE_BISHOP);
            }
            else if ((rSquares[i]->GetFile()=="d")&&(rSquares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),WHITE_QUEEN);
            }
            else if ((rSquares[i]->GetFile()=="e")&&(rSquares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),WHITE_KING);
            }
            //second rank, all white pawns
            else if(rSquares[i]->GetRank()=="2" && rSquares[i]->IsBorderSquare()==false)
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),WHITE_PAWN);
            }
            //seventh rank, all black pawns
            else if (rSquares[i]->GetRank()=="7" && rSquares[i]->IsBorderSquare()==false)
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),BLACK_PAWN);
            }

            //EIGTH rank
            else if ((rSquares[i]->GetFile()=="a")&&(rSquares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),BLACK_ROOK);
            }
            else if ((rSquares[i]->GetFile()=="h")&&(rSquares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),BLACK_ROOK);
            }
            else if ((rSquares[i]->GetFile()=="b")&&(rSquares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),BLACK_KNIGHT);
            }
            else if ((rSquares[i]->GetFile()=="g")&&(rSquares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),BLACK_KNIGHT);
            }
            else if ((rSquares[i]->GetFile()=="c")&&(rSquares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),BLACK_BISHOP);
            }
            else if ((rSquares[i]->GetFile()=="f")&&(rSquares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),BLACK_BISHOP);
            }
            else if ((rSquares[i]->GetFile()=="d")&&(rSquares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),BLACK_QUEEN);
            }
            else if ((rSquares[i]->GetFile()=="e")&&(rSquares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),BLACK_KING);
            }
            else
            {
                TS_ASSERT_EQUALS(rSquares[i]->GetPieceOnThisSquare(),NO_PIECE);
            }
        }
    }
public:

    void testBasicBoard(void)
    {
        ChessBoard my_cb;
        my_cb.SetupChessBoard();
        std::vector<Square* > squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(squares.size(), 64u);

        //a1
        TS_ASSERT_EQUALS(squares[0]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[0]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[0]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[0]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[0]->GetFile(), "a");
        TS_ASSERT_EQUALS(squares[0]->GetRank(), "1");
        TS_ASSERT_EQUALS(squares[0]->IsCoordinatePrintable(), false);

        //b1
        TS_ASSERT_EQUALS(squares[1]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[1]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[1]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[1]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[1]->GetFile(), "b");
        TS_ASSERT_EQUALS(squares[1]->GetRank(), "1");

        //c1
        TS_ASSERT_EQUALS(squares[2]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[2]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[2]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[2]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[2]->GetFile(), "c");
        TS_ASSERT_EQUALS(squares[2]->GetRank(), "1");

        //d1
        TS_ASSERT_EQUALS(squares[3]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[3]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[3]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[3]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[3]->GetFile(), "d");
        TS_ASSERT_EQUALS(squares[3]->GetRank(), "1");

        //e1
        TS_ASSERT_EQUALS(squares[4]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[4]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[4]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[4]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[4]->GetFile(), "e");
        TS_ASSERT_EQUALS(squares[4]->GetRank(), "1");

        //f1
        TS_ASSERT_EQUALS(squares[5]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[5]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[5]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[5]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[5]->GetFile(), "f");
        TS_ASSERT_EQUALS(squares[5]->GetRank(), "1");

        //g1
        TS_ASSERT_EQUALS(squares[6]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[6]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[6]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[6]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[6]->GetFile(), "g");
        TS_ASSERT_EQUALS(squares[6]->GetRank(), "1");

        //h1
        TS_ASSERT_EQUALS(squares[7]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[7]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[7]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[7]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[7]->GetFile(), "h");
        TS_ASSERT_EQUALS(squares[7]->GetRank(), "1");


        //a2
        TS_ASSERT_EQUALS(squares[8]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[8]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[8]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[8]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[8]->GetFile(), "a");
        TS_ASSERT_EQUALS(squares[8]->GetRank(), "2");

        //b2
        TS_ASSERT_EQUALS(squares[9]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[9]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[9]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[9]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[9]->GetFile(), "b");
        TS_ASSERT_EQUALS(squares[9]->GetRank(), "2");

        //c2
        TS_ASSERT_EQUALS(squares[10]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[10]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[10]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[10]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[10]->GetFile(), "c");
        TS_ASSERT_EQUALS(squares[10]->GetRank(), "2");

        //d2
        TS_ASSERT_EQUALS(squares[11]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[11]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[11]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[11]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[11]->GetFile(), "d");
        TS_ASSERT_EQUALS(squares[11]->GetRank(), "2");

        //e2
        TS_ASSERT_EQUALS(squares[12]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[12]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[12]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[12]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[12]->GetFile(), "e");
        TS_ASSERT_EQUALS(squares[12]->GetRank(), "2");

        //f2
        TS_ASSERT_EQUALS(squares[13]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[13]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[13]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[13]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[13]->GetFile(), "f");
        TS_ASSERT_EQUALS(squares[13]->GetRank(), "2");

        //g2
        TS_ASSERT_EQUALS(squares[14]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[14]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[14]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[14]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[14]->GetFile(), "g");
        TS_ASSERT_EQUALS(squares[14]->GetRank(), "2");

        //h2
        TS_ASSERT_EQUALS(squares[15]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[15]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[15]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[15]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[15]->GetFile(), "h");
        TS_ASSERT_EQUALS(squares[15]->GetRank(), "2");


        //////
        // 3rd rank (some squares)
        //////

        //a3
        TS_ASSERT_EQUALS(squares[16]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[16]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[16]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[16]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[16]->GetFile(), "a");
        TS_ASSERT_EQUALS(squares[16]->GetRank(), "3");

        //c3
        TS_ASSERT_EQUALS(squares[18]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[18]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[18]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[18]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[18]->GetFile(), "c");
        TS_ASSERT_EQUALS(squares[18]->GetRank(), "3");

        //////
        // 8th rank (some squares)
        //////

        //h8
        TS_ASSERT_EQUALS(squares[63]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[63]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[63]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[63]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[63]->GetFile(), "h");
        TS_ASSERT_EQUALS(squares[63]->GetRank(), "8");

        //g8
        TS_ASSERT_EQUALS(squares[62]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[62]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[62]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[62]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[62]->GetFile(), "g");
        TS_ASSERT_EQUALS(squares[62]->GetRank(), "8");

        //a8
        TS_ASSERT_EQUALS(squares[56]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[56]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[56]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[56]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[56]->GetFile(), "a");
        TS_ASSERT_EQUALS(squares[56]->GetRank(), "8");

    }

    void testInitialPosition(void)
    {
        ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        std::vector<Square* > squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(squares.size(), 64u);
        CheckInitialPosition(squares);
    }

    void testMakeAMove()
    {
        ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();

        //non-capturing move
        std::vector<Square*> squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(squares[12]->GetFile(),"e");
        TS_ASSERT_EQUALS(squares[20]->GetFile(),"e");
        TS_ASSERT_EQUALS(squares[12]->GetRank(),"2");
        TS_ASSERT_EQUALS(squares[20]->GetRank(),"3");

        TS_ASSERT_EQUALS(squares[12]->GetPieceOnThisSquare(),WHITE_PAWN);
        TS_ASSERT_EQUALS(squares[20]->GetPieceOnThisSquare(),NO_PIECE);

        Move non_capturing_move;
        non_capturing_move.first = squares[12];
        non_capturing_move.second = squares[20];

        //make the move e2-e3
        my_cb.MakeThisMove(non_capturing_move);

        //size is the same
        std::vector<Square*> updated_squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(updated_squares[12]->GetPieceOnThisSquare(),NO_PIECE);//e2 now empty
        TS_ASSERT_EQUALS(updated_squares[20]->GetPieceOnThisSquare(),WHITE_PAWN);//e3 with white pawn

        //make sure we do not screw up the coordinates
        TS_ASSERT_EQUALS(updated_squares[12]->GetFile(),"e");
        TS_ASSERT_EQUALS(updated_squares[20]->GetFile(),"e");
        TS_ASSERT_EQUALS(updated_squares[12]->GetRank(),"2");
        TS_ASSERT_EQUALS(updated_squares[20]->GetRank(),"3");

        //capturing move a2 takes a7 (a fake one, but does not matter here)

        Move capturing_move;
        capturing_move.first = squares[8];//a2
        capturing_move.second = squares[48];//a7

        TS_ASSERT_EQUALS(squares[8]->GetPieceOnThisSquare(),WHITE_PAWN);//a2, white pawn
        TS_ASSERT_EQUALS(squares[48]->GetPieceOnThisSquare(),BLACK_PAWN);//a7, black pawn

        TS_ASSERT_EQUALS(squares[8]->GetFile(),"a");
        TS_ASSERT_EQUALS(squares[48]->GetFile(),"a");
        TS_ASSERT_EQUALS(squares[8]->GetRank(),"2");
        TS_ASSERT_EQUALS(squares[48]->GetRank(),"7");

        //make the move e2-e4
        my_cb.MakeThisMove(capturing_move);

        TS_ASSERT_EQUALS(squares[8]->GetPieceOnThisSquare(),NO_PIECE);//e2 now empty
        TS_ASSERT_EQUALS(squares[48]->GetPieceOnThisSquare(),WHITE_PAWN);//e4 with white pawn
    }

    void testArrangePiecesFromFEN()
    {
        ChessBoard my_cb;
        my_cb.SetupChessBoard();

        std::string fen_after_2Nf3 = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
        int rc = my_cb.ArrangePiecesFromFEN(fen_after_2Nf3);
        TS_ASSERT_EQUALS(rc,0);

        std::vector<Square*> squares = my_cb.GetSquares();
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            //first rank
            if ((squares[i]->GetFile()=="a")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_ROOK);
            }
            else if ((squares[i]->GetFile()=="h")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_ROOK);
            }
            else if ((squares[i]->GetFile()=="b")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_KNIGHT);
            }
            else if ((squares[i]->GetFile()=="g")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),NO_PIECE);//knight wne to f3
            }
            else if ((squares[i]->GetFile()=="c")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_BISHOP);
            }
            else if ((squares[i]->GetFile()=="f")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_BISHOP);
            }
            else if ((squares[i]->GetFile()=="d")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_QUEEN);
            }
            else if ((squares[i]->GetFile()=="e")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_KING);
            }
            //second rank, all white pawns
            else if(squares[i]->GetRank()=="2" && squares[i]->IsBorderSquare()==false)
            {
                if (squares[i]->GetFile()=="e")//pawn went to e4
                {
                    TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),NO_PIECE);
                }
                else
                {
                    TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_PAWN);
                }
            }
            //seventh rank, all black pawns
            else if (squares[i]->GetRank()=="7" && squares[i]->IsBorderSquare()==false)
            {
                if (squares[i]->GetFile()=="c")//pawn went to c5
                {
                    TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),NO_PIECE);
                }
                else
                {
                    TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_PAWN);
                }
            }

            //EIGTH rank
            else if ((squares[i]->GetFile()=="a")&&(squares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_ROOK);
            }
            else if ((squares[i]->GetFile()=="h")&&(squares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_ROOK);
            }
            else if ((squares[i]->GetFile()=="b")&&(squares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_KNIGHT);
            }
            else if ((squares[i]->GetFile()=="g")&&(squares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_KNIGHT);
            }
            else if ((squares[i]->GetFile()=="c")&&(squares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_BISHOP);
            }
            else if ((squares[i]->GetFile()=="f")&&(squares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_BISHOP);
            }
            else if ((squares[i]->GetFile()=="d")&&(squares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_QUEEN);
            }
            else if ((squares[i]->GetFile()=="e")&&(squares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_KING);
            }
            else
            {
                if (((squares[i]->GetFile()=="f")&&(squares[i]->GetRank()=="3")))
                {
                    TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_KNIGHT);
                }
                else if (((squares[i]->GetFile()=="c")&&(squares[i]->GetRank()=="5")))
                {
                    TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_PAWN);
                }
                else if (((squares[i]->GetFile()=="e")&&(squares[i]->GetRank()=="4")))
                {
                    TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_PAWN);
                }
                else
                {
                    TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),NO_PIECE);
                }
            }
        }

        //black's turn
        TS_ASSERT_EQUALS(my_cb.WhosTurnIsIt(), BLACK);
    }

    void testAnotherFen()
    {
        ChessBoard my_cb;
        my_cb.SetupChessBoard();
        //here we test that we are able to change a position from the initial position
        my_cb.SetupInitialChessPosition();
        //black king on f3, black pawn on g2 and white king on f1
        std::string endgame = "8/8/8/8/8/5k2/6p1/5K2 w - - 0 68";
        int rc = my_cb.ArrangePiecesFromFEN(endgame);
        TS_ASSERT_EQUALS(rc,0);
        std::vector<Square*> squares = my_cb.GetSquares();
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            //first rank
            if ((squares[i]->GetFile()=="f")&&(squares[i]->GetRank()=="3"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_KING);
            }
            else if ((squares[i]->GetFile()=="f")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_KING);
            }
            else if ((squares[i]->GetFile()=="g")&&(squares[i]->GetRank()=="2"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_PAWN);
            }
            else
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),NO_PIECE);
            }
        }

        TS_ASSERT_EQUALS(my_cb.WhosTurnIsIt(), WHITE);
    }

    void testThatInvalidFenChangesNothing()
    {
        ChessBoard my_cb;
        my_cb.SetupChessBoard();

        std::string too_long = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R/8/8/8/8 b KQkq - 1 2";
        int rc = my_cb.ArrangePiecesFromFEN(too_long);
        TS_ASSERT_EQUALS(rc,1);

        std::string too_short = "rnbqkbnr/pp1ppppp/ b KQkq - 1 2";
        rc = my_cb.ArrangePiecesFromFEN(too_short);
        TS_ASSERT_EQUALS(rc,1);
        TS_ASSERT_EQUALS(my_cb.WhosTurnIsIt(), WHITE);//invalid fen not applied, still white's turn

        //invalid fen, check return code and that we don't move anything on the board (all empty squares)
        std::vector<Square*> squares = my_cb.GetSquares();
        for (unsigned i = 0; i < squares.size(); ++i)
        {
            TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),NO_PIECE);
        }

        //invalid fen again, check return code and that we don't move anything on the board (after setting initial position)
        my_cb.SetupInitialChessPosition();
        rc = my_cb.ArrangePiecesFromFEN(too_long);
        squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(rc,1);
        CheckInitialPosition(squares);
    }
};
#endif
