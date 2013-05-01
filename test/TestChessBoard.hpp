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
        TS_ASSERT_EQUALS(squares[0]->GetFile(), "A");
        TS_ASSERT_EQUALS(squares[0]->GetRank(), "1");
        TS_ASSERT_EQUALS(squares[0]->IsCoordinatePrintable(), false);

        //b1
        TS_ASSERT_EQUALS(squares[1]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[1]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[1]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[1]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[1]->GetFile(), "B");
        TS_ASSERT_EQUALS(squares[1]->GetRank(), "1");

        //c1
        TS_ASSERT_EQUALS(squares[2]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[2]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[2]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[2]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[2]->GetFile(), "C");
        TS_ASSERT_EQUALS(squares[2]->GetRank(), "1");

        //d1
        TS_ASSERT_EQUALS(squares[3]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[3]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[3]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[3]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[3]->GetFile(), "D");
        TS_ASSERT_EQUALS(squares[3]->GetRank(), "1");

        //e1
        TS_ASSERT_EQUALS(squares[4]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[4]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[4]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[4]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[4]->GetFile(), "E");
        TS_ASSERT_EQUALS(squares[4]->GetRank(), "1");

        //f1
        TS_ASSERT_EQUALS(squares[5]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[5]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[5]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[5]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[5]->GetFile(), "F");
        TS_ASSERT_EQUALS(squares[5]->GetRank(), "1");

        //g1
        TS_ASSERT_EQUALS(squares[6]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[6]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[6]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[6]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[6]->GetFile(), "G");
        TS_ASSERT_EQUALS(squares[6]->GetRank(), "1");

        //h1
        TS_ASSERT_EQUALS(squares[7]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[7]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[7]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[7]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[7]->GetFile(), "H");
        TS_ASSERT_EQUALS(squares[7]->GetRank(), "1");


        //a2
        TS_ASSERT_EQUALS(squares[8]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[8]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[8]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[8]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[8]->GetFile(), "A");
        TS_ASSERT_EQUALS(squares[8]->GetRank(), "2");

        //b2
        TS_ASSERT_EQUALS(squares[9]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[9]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[9]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[9]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[9]->GetFile(), "B");
        TS_ASSERT_EQUALS(squares[9]->GetRank(), "2");

        //c2
        TS_ASSERT_EQUALS(squares[10]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[10]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[10]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[10]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[10]->GetFile(), "C");
        TS_ASSERT_EQUALS(squares[10]->GetRank(), "2");

        //d2
        TS_ASSERT_EQUALS(squares[11]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[11]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[11]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[11]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[11]->GetFile(), "D");
        TS_ASSERT_EQUALS(squares[11]->GetRank(), "2");

        //e2
        TS_ASSERT_EQUALS(squares[12]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[12]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[12]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[12]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[12]->GetFile(), "E");
        TS_ASSERT_EQUALS(squares[12]->GetRank(), "2");

        //f2
        TS_ASSERT_EQUALS(squares[13]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[13]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[13]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[13]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[13]->GetFile(), "F");
        TS_ASSERT_EQUALS(squares[13]->GetRank(), "2");

        //g2
        TS_ASSERT_EQUALS(squares[14]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[14]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[14]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[14]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[14]->GetFile(), "G");
        TS_ASSERT_EQUALS(squares[14]->GetRank(), "2");

        //h2
        TS_ASSERT_EQUALS(squares[15]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[15]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[15]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[15]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[15]->GetFile(), "H");
        TS_ASSERT_EQUALS(squares[15]->GetRank(), "2");


        //////
        // 3rd rank (some squares)
        //////

        //a3
        TS_ASSERT_EQUALS(squares[16]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[16]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[16]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[16]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[16]->GetFile(), "A");
        TS_ASSERT_EQUALS(squares[16]->GetRank(), "3");

        //c3
        TS_ASSERT_EQUALS(squares[18]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[18]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[18]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[18]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[18]->GetFile(), "C");
        TS_ASSERT_EQUALS(squares[18]->GetRank(), "3");

        //////
        // 8th rank (some squares)
        //////

        //h8
        TS_ASSERT_EQUALS(squares[63]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[63]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[63]->IsDarkSquare(), true);
        TS_ASSERT_EQUALS(squares[63]->IsLightSquare(), false);
        TS_ASSERT_EQUALS(squares[63]->GetFile(), "H");
        TS_ASSERT_EQUALS(squares[63]->GetRank(), "8");

        //g8
        TS_ASSERT_EQUALS(squares[62]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[62]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[62]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[62]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[62]->GetFile(), "G");
        TS_ASSERT_EQUALS(squares[62]->GetRank(), "8");

        //a8
        TS_ASSERT_EQUALS(squares[56]->IsCornerSquare(), false);
        TS_ASSERT_EQUALS(squares[56]->IsBorderSquare(), false);
        TS_ASSERT_EQUALS(squares[56]->IsDarkSquare(), false);
        TS_ASSERT_EQUALS(squares[56]->IsLightSquare(), true);
        TS_ASSERT_EQUALS(squares[56]->GetFile(), "A");
        TS_ASSERT_EQUALS(squares[56]->GetRank(), "8");

    }

    void testInitialPosition(void)
    {
        ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        TS_ASSERT_EQUALS(my_cb.GetCurrentPosition().size(), 32u);
        std::vector<Square* > squares = my_cb.GetSquares();
        TS_ASSERT_EQUALS(squares.size(), 64u);

        for (unsigned i = 0; i < squares.size(); ++i)
        {
            //first rank
            if ((squares[i]->GetFile()=="A")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_ROOK);
            }
            else if ((squares[i]->GetFile()=="H")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_ROOK);
            }
            else if ((squares[i]->GetFile()=="B")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_KNIGHT);
            }
            else if ((squares[i]->GetFile()=="G")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_KNIGHT);
            }
            else if ((squares[i]->GetFile()=="C")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_BISHOP);
            }
            else if ((squares[i]->GetFile()=="F")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_BISHOP);
            }
            else if ((squares[i]->GetFile()=="D")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_QUEEN);
            }
            else if ((squares[i]->GetFile()=="E")&&(squares[i]->GetRank()=="1"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_KING);
            }
            //second rank, all white pawns
            else if(squares[i]->GetRank()=="2" && squares[i]->IsBorderSquare()==false)
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),WHITE_PAWN);
            }
            //seventh rank, all black pawns
            else if (squares[i]->GetRank()=="7" && squares[i]->IsBorderSquare()==false)
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_PAWN);
            }

            //EIGTH rank
            else if ((squares[i]->GetFile()=="A")&&(squares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_ROOK);
            }
            else if ((squares[i]->GetFile()=="H")&&(squares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_ROOK);
            }
            else if ((squares[i]->GetFile()=="B")&&(squares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_KNIGHT);
            }
            else if ((squares[i]->GetFile()=="G")&&(squares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_KNIGHT);
            }
            else if ((squares[i]->GetFile()=="C")&&(squares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_BISHOP);
            }
            else if ((squares[i]->GetFile()=="F")&&(squares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_BISHOP);
            }
            else if ((squares[i]->GetFile()=="D")&&(squares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_QUEEN);
            }
            else if ((squares[i]->GetFile()=="E")&&(squares[i]->GetRank()=="8"))
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),BLACK_KING);
            }
            else
            {
                TS_ASSERT_EQUALS(squares[i]->GetPieceOnThisSquare(),NO_PIECE);
            }
        }

    }

};
#endif
