
#include <cassert>
#include <cstdio>
#include <iostream>

#include "ChessBoardWithBorders.hpp"

slach::ChessBoardWithBorders::ChessBoardWithBorders()
	: mpChessBoard(std::make_shared<ChessBoard>())
{
    mChessBoardSizeWithBorders = gChessBoardSizeWB;//with border
    std::vector<char> files = {'0' , 'a', 'b', 'c', 'd', 'e','f', 'g',  'h', '0'};
    std::vector<char> ranks = {'0' , '8', '7', '6', '5', '4', '3', '2', '1', '0'};
    unsigned file_size = files.size();
    unsigned rank_size = ranks.size();

    //create the 64 squares playable chessboard
    mpChessBoard->SetupChessBoard();

    //allocate memory for the vectors
    mSquares.resize(gChessBoardSizeWB);
    mSquaresFromBlackPerspective.resize(gChessBoardSizeWB);

    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        mSquares[i] = new Square();
    }

    //fill in the vector of squares appropriately
    mpChessBoard->SetupChessBoard();
    mPlayableSquares = mpChessBoard->GetSquares();

    unsigned playable_sq_counter = 56;//A8
    for (unsigned index = 0; index < mChessBoardSizeWithBorders; ++index)
    {
    	std::div_t result = std::div(index,10);
    	int col_index =  result.rem;
    	int row_index = result.quot;
    	//std::cout<<row_index<<std::endl;
    	bool right_border = false;
    	if (col_index > 8)
    	{
    		col_index = 0;
    		right_border = true;
    	}

    	if (index < 10u) //top border
    	{
            mSquares[index]->SetFile(files[col_index]);
            mSquares[index]->SetRank(ranks.back());
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
    	else  if (index < 90u)//main board
    	{
    		mSquares[index]->SetFile(files[col_index]);
    		mSquares[index]->SetRank(ranks[row_index]);
            //borders
            if ( col_index == 0)
            {
                mSquares[index]->SetAsBorderSquare(true);
                mSquares[index]->SetAsPrintableCoordinates(true);
				//right borders
				if ( right_border ) mSquares[index]->SetAsPrintableCoordinates(false);
            }
            else //playable square
            {
                assert(playable_sq_counter<mPlayableSquares.size());
                // delete the object we had created, here we will assign the value of pointer from
                // the underlying playable chessboard
                delete mSquares[index];
                mSquares[index] = mPlayableSquares[playable_sq_counter];
                playable_sq_counter++;
                if (std::div(playable_sq_counter,8).rem == 0)  playable_sq_counter -= 16;
            }
    	}
    	else if(index < 100) //bottom border
    	{
            mSquares[index]->SetFile(files[col_index]);
            mSquares[index]->SetRank(ranks.back());
            if (index==90u || index == 99u)
            {
                //corner square
                mSquares[index]->SetAsCornerSquare(true);
                mSquares[index]->SetAsBorderSquare(true);
                if (index == 99u) mSquares[index]->SetAsBottomRightCorner(true);
            }
            else
            {
                //bottom row, put markers
                mSquares[index]->SetAsBorderSquare(true);
                mSquares[index]->SetAsCornerSquare(false);
                mSquares[index]->SetAsPrintableCoordinates(true);
            }
    	}
    	else //bottom row with arrows
    	{
            mSquares[index]->SetFile(files[col_index]);
            if ((index == 100) || (index == 109)) mSquares[index]->SetFile('r');
            mSquares[index]->SetRank('r');
            mSquares[index]->SetAsSquareForArrows(true);
    	}
    }


    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        mSquares[i]->SetIndexFromTopLeft(i);
        mSquares[i]->SetIndexFromBottomRight(mSquares.size() - 1 - i);
    }

    unsigned index_from_white = 99u;
    for (unsigned i = 0; i < 100; ++i)
    {
        assert(index_from_white <  mSquares.size());
        mSquaresFromBlackPerspective[i] = mSquares[index_from_white];
        index_from_white--;
    }
    for (unsigned i = 100; i < 110; ++i)
    {
    	mSquaresFromBlackPerspective[i] = mSquares[i];
    }
}

slach::ChessBoardWithBorders::~ChessBoardWithBorders()
{
    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        if ((mSquares[i]->IsBorderSquare()==true) || mSquares[i]->IsSquareForArrows() == true)
        {
            delete mSquares[i];
        }
    }
}

std::vector<slach::Square* > slach::ChessBoardWithBorders::GetSquares() const
{
	mSquares[0]->SetAsBottomRightCorner(false);
	mSquares[99]->SetAsBottomRightCorner(true);
    return mSquares;
}

std::vector<slach::Square* > slach::ChessBoardWithBorders::GetSquaresBlackPerspective() const
{
	mSquaresFromBlackPerspective[0]->SetAsBottomRightCorner(false);
	mSquaresFromBlackPerspective[99]->SetAsBottomRightCorner(true);
    return mSquaresFromBlackPerspective;
}

std::shared_ptr<slach::ChessBoard> slach::ChessBoardWithBorders::GetPlayableChessBoard() const
{
    return mpChessBoard;
}
