
#include <cassert>
#include <cstdio>
#include <iostream>

#include "ChessBoardWithBorders.hpp"

ChessBoardWithBorders::ChessBoardWithBorders()
{
    mChessBoardSizeWithBorders = 100u;//with border
    std::vector<std::string > files = {"0" , "A", "B", "C", "D", "E","F", "G",  "H", "0"};
    std::vector<std::string > ranks = {"0" , "1", "2", "3", "4", "5","6", "7",  "8", "0"};
    unsigned file_size = files.size();
    unsigned rank_size = ranks.size();

    //create the 64 squares playable chessboard
    mpChessBoard = new ChessBoard();
    mpChessBoard->SetupChessBoard();

    //allocate memory for the vectors
    mSquares.resize(CHESSBOARD_SIZE_WB);
    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        mSquares[i] = new Square();
    }

    //fill in the vector of squares appropriately
    mpChessBoard->SetupChessBoard();
    mPlayableSquares = mpChessBoard->GetSquares();

    unsigned row=rank_size-1;//row counter, start from the max as the loop starts from top left
    unsigned column=0;//column counter
    unsigned playable_sq_counter = 63 - file_size - 2;
    for (unsigned index = 0; index < mChessBoardSizeWithBorders; ++index)
    {
        assert(row<ranks.size());
        assert(column<files.size());
        mSquares[index]->SetFile(files[column]);
        mSquares[index]->SetRank(ranks[row]);
        column++;

        if ( (column%file_size==0) )
        {
            row--;
            column=0;
            playable_sq_counter = 63 - (file_size - 2)*(9-row) + 1;
        }

        //first row at the top, a border
        if (index < file_size)
        {
            if (index==0 || index == file_size-1)
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
        else if (index < (CHESSBOARD_SIZE_WB - (rank_size)))
        {
            //left border
            if ( (index%(rank_size)==0)  )
            {
                mSquares[index]->SetAsBorderSquare(true);
                mSquares[index]->SetAsPrintableCoordinates(true);
            }
            //right borders
            else if ( (index+1)%(rank_size)==0 )
            {
                mSquares[index]->SetAsBorderSquare(true);
                mSquares[index]->SetAsPrintableCoordinates(false);
            }
            else //playable square
            {
                assert(playable_sq_counter<mPlayableSquares.size());
                // delete the object we had created, here we will assign the value of pointer from
                // the underlying playable chessboard
                delete mSquares[index];
                mSquares[index] = mPlayableSquares[playable_sq_counter];
                playable_sq_counter++;
            }

        }
        //last row at the bottom, a border
        else
        {
            if (index==mChessBoardSizeWithBorders-rank_size || index == mChessBoardSizeWithBorders-1)
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
                mSquares[index]->SetAsPrintableCoordinates(true);
            }
        }
    }
}

ChessBoardWithBorders::~ChessBoardWithBorders()
{

    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        if (mSquares[i]->IsBorderSquare()==true)
        {
            delete mSquares[i];
        }
    }
    delete mpChessBoard;
}

std::vector<Square* > ChessBoardWithBorders::GetSquares()
{
    return mSquares;
}

ChessBoard* ChessBoardWithBorders::GetPlayableChessBoard() const
{
    return mpChessBoard;
}
