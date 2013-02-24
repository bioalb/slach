#include "ChessBoard.hpp"
#include <cassert>
#include <cstdio>
#include <iostream>

ChessBoard::ChessBoard()
{
    //allocate memory for the vectors
    mSquares.resize(CHESSBOARD_SIZE_WB);
    mFiles.resize(FILE_SIZE);
    mRanks.resize(RANK_SIZE);

    mFiles[0] = "0";
    mFiles[1] = "A";
    mFiles[2] = "B";
    mFiles[3] = "C";
    mFiles[4] = "D";
    mFiles[5] = "E";
    mFiles[6] = "F";
    mFiles[7] = "G";
    mFiles[8] = "H";
    mFiles[9] = "0";

    mRanks[0] = "0";
    mRanks[1] = "1";
    mRanks[2] = "2";
    mRanks[3] = "3";
    mRanks[4] = "4";
    mRanks[5] = "5";
    mRanks[6] = "6";
    mRanks[7] = "7";
    mRanks[8] = "8";
    mRanks[9] = "0";

    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        mSquares[i] = new Square();
    }
}

ChessBoard::~ChessBoard()
{

}

std::vector<Square* > ChessBoard::GetSquares()
{
    return mSquares;
}

std::vector<std::string> ChessBoard::GetFiles()
{
    return mFiles;
}

std::vector<std::string> ChessBoard::GetRanks()
{
    return mRanks;
}

void ChessBoard::SetupChessBoard()
{
    unsigned row=RANK_SIZE-1;//row counter, start from the max as the loop starts from top left
    unsigned column=0;//column counter
    unsigned bw_counter = 0; //at zero, it will start with white (square A8).

    //will create the squares row by row, starting from top left
    for (unsigned index = 0; index < CHESSBOARD_SIZE_WB; ++index)
    {
        assert(row<mRanks.size());
        assert(column<mFiles.size());
        mSquares[index]->SetFile(mFiles[column]);
        mSquares[index]->SetRank(mRanks[row]);

        column++;
        bw_counter++;

        if ( (column%FILE_SIZE==0) )
        {
            bw_counter++;//trick the counter, end of a row and beginning of new one have same colour
            row--;
            column=0;
        }

        if (bw_counter%2==0)
        {
            mSquares[index]->SetAsDarkSquare();
        }
        else
        {
            mSquares[index]->SetAsLightSquare();
        }

        //first row at the top, a border
        if (index < FILE_SIZE)
        {
            if (index==0 || index == FILE_SIZE-1)
            {
                //corner square
                mSquares[index]->SetAsCornerSquare(true);
                mSquares[index]->SetAsBorderSquare(true);
            }
            else
            {
                //top row, put markers
                mSquares[index]->SetAsBorderSquare(true);
                mSquares[index]->SetAsCornerSquare(false);
            }
        }
        //all the other rows (ranks) before we hit to bottom border
        else if (index < (CHESSBOARD_SIZE_WB - (RANK_SIZE)))
        {
            //left border and right borders
            if ( (index%(RANK_SIZE)==0) || ((index+1)%(RANK_SIZE)==0) )
            {
                mSquares[index]->SetAsBorderSquare(true);
            }
        }
        //last row at the bottom, a border
        else
        {
            if (index==CHESSBOARD_SIZE_WB-RANK_SIZE || index == CHESSBOARD_SIZE_WB-1)
            {
                //corner square
                mSquares[index]->SetAsCornerSquare(true);
                mSquares[index]->SetAsBorderSquare(true);
            }
            else
            {
                //bottom row, put markers
                mSquares[index]->SetAsBorderSquare(true);
                mSquares[index]->SetAsCornerSquare(false);
            }
        }
    }
}
