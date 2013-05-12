#include "ChessBoard.hpp"
#include "Exception.hpp"
#include <cassert>
#include <cstdio>
#include <iostream>

ChessBoard::ChessBoard()
{
    //allocate memory for the vectors
    mSquares.resize(CHESSBOARD_SIZE);

    mFiles = {"a", "b", "c", "d", "e","f", "g",  "h"};
    mRanks = {"1", "2", "3", "4", "5","6", "7",  "8"};

    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        mSquares[i] = new Square();
    }
}

ChessBoard::~ChessBoard()
{
    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        delete mSquares[i];
    }
}

std::vector<Square* > ChessBoard::GetSquares() const
{
    return mSquares;
}

void ChessBoard::SetupInitialChessPosition()
{
    for (unsigned i = 0; i < mSquares.size(); ++i)
    {
        //first rank
        if ((mSquares[i]->GetFile()==mFiles[0])&&(mSquares[i]->GetRank()==mRanks[0]))
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_ROOK);
        }
        else if ((mSquares[i]->GetFile()==mFiles[7])&&(mSquares[i]->GetRank()==mRanks[0]))
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_ROOK);
        }
        else if ((mSquares[i]->GetFile()==mFiles[1])&&(mSquares[i]->GetRank()==mRanks[0]))
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_KNIGHT);
        }
        else if ((mSquares[i]->GetFile()==mFiles[6])&&(mSquares[i]->GetRank()==mRanks[0]))
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_KNIGHT);
        }
        else if ((mSquares[i]->GetFile()==mFiles[2])&&(mSquares[i]->GetRank()==mRanks[0]))
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_BISHOP);
        }
        else if ((mSquares[i]->GetFile()==mFiles[5])&&(mSquares[i]->GetRank()==mRanks[0]))
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_BISHOP);
        }
        else if ((mSquares[i]->GetFile()==mFiles[3])&&(mSquares[i]->GetRank()==mRanks[0]))
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_QUEEN);
        }
        else if ((mSquares[i]->GetFile()==mFiles[4])&&(mSquares[i]->GetRank()==mRanks[0]))
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_KING);
        }
        //second rank, all white pawns
        else if ((mSquares[i]->GetRank()==mRanks[1])&&mSquares[i]->IsBorderSquare()==false)
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_PAWN);
        }
        //seventh rank, all black pawns
        else if(mSquares[i]->GetRank()==mRanks[6]&&mSquares[i]->IsBorderSquare()==false)
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_PAWN);
        }

        //EIGTH rank
        else if ((mSquares[i]->GetFile()==mFiles[0])&&(mSquares[i]->GetRank()==mRanks[7]))
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_ROOK);
        }
        else if ((mSquares[i]->GetFile()==mFiles[7])&&(mSquares[i]->GetRank()==mRanks[7]))
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_ROOK);
        }
        else if ((mSquares[i]->GetFile()==mFiles[1])&&(mSquares[i]->GetRank()==mRanks[7]))
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_KNIGHT);
        }
        else if ((mSquares[i]->GetFile()==mFiles[6])&&(mSquares[i]->GetRank()==mRanks[7]))
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_KNIGHT);
        }
        else if ((mSquares[i]->GetFile()==mFiles[2])&&(mSquares[i]->GetRank()==mRanks[7]))
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_BISHOP);
        }
        else if ((mSquares[i]->GetFile()==mFiles[5])&&(mSquares[i]->GetRank()==mRanks[7]))
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_BISHOP);
        }
        else if ((mSquares[i]->GetFile()==mFiles[3])&&(mSquares[i]->GetRank()==mRanks[7]))
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_QUEEN);
        }
        else if ((mSquares[i]->GetFile()==mFiles[4])&&(mSquares[i]->GetRank()==mRanks[7]))
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_KING);
        }
        else
        {
            mSquares[i]->SetPieceOnThisSquare(NO_PIECE);
        }
    }
}

void ChessBoard::SetupChessBoard()
{
    unsigned row=0;//row counter
    unsigned column=0;//column counter
    unsigned bw_counter = 0; //at zero, it will start with black (square A1).

    //will create the squares row by row, starting from bottom left (A1)
    for (unsigned index = 0; index < CHESSBOARD_SIZE; ++index)
    {
        assert(row<mRanks.size());
        assert(column<mFiles.size());
        mSquares[index]->SetFile(mFiles[column]);
        mSquares[index]->SetRank(mRanks[row]);

        if (bw_counter%2==0)
        {
            mSquares[index]->SetAsDarkSquare();
        }
        else
        {
            mSquares[index]->SetAsLightSquare();
        }
        column++;
        bw_counter++;

        if ( (column%(BOARD_ROW_SIZE)==0) )
        {
            bw_counter++;//trick the counter, end of a row and beginning of new one have same colour
            row++;
            column=0;
        }
    }
}

bool ChessBoard::IsLegalMove()
{
    return true;
}

void ChessBoard::MakeThisMove(const Move& rMove)
{
    Square* origin = rMove.first;
    Square* destination = rMove.second;

    for (unsigned i = 0; i < mSquares.size(); ++i)
    {
        if (origin->IsSameSquare((*mSquares[i])))//if we found the origin square
        {
            PieceType origin_piece = mSquares[i]->GetPieceOnThisSquare();
            mSquares[i]->SetPieceOnThisSquare(NO_PIECE);//no more piece here
            //look for the destination
            for (unsigned j = 0; j < mSquares.size(); ++j)
            {
                if (destination->IsSameSquare((*mSquares[j])))//if we found the destination square
                {
                    mSquares[j]->SetPieceOnThisSquare(origin_piece);
                    break;
                }
            }
            break;
        }
    }

}

int ChessBoard::AssignPieceFromLetter(PieceType& piece, const char &character)
{
    int rc = 0;
    if (character == 'R')
    {
        rc =1;
        piece = WHITE_ROOK;
    }
    else if (character == 'r')
    {
        rc =1;
        piece = BLACK_ROOK;
    }
    else if (character == 'P')
    {
        rc =1;
        piece = WHITE_PAWN;
    }
    else if (character == 'p')
    {
        rc =1;
        piece = BLACK_PAWN;
    }
    else if (character == 'Q')
    {
        rc =1;
        piece = WHITE_QUEEN;
    }
    else if (character == 'q')
    {
        rc =1;
        piece = BLACK_QUEEN;
    }
    else if (character == 'B')
    {
        rc =1;
        piece = WHITE_BISHOP;
    }
    else if (character == 'b')
    {
        rc =1;
        piece = BLACK_BISHOP;
    }
    else if (character == 'K')
    {
        rc =1;
        piece = WHITE_KING;
    }
    else if (character == 'k')
    {
        rc =1;
        piece = BLACK_KING;
    }
    else if (character == 'N')
    {
        rc =1;
        piece = WHITE_KNIGHT;
    }
    else if (character == 'n')
    {
        rc =1;
        piece = BLACK_KNIGHT;
    }
    return rc;
}

int ChessBoard::ArrangePiecesFromFEN(const std::string &rFenPosition)
{
    int rc = 1;//return code, initialise at 1

    unsigned rank_index= 7u;//fen starts by 8th rank
    unsigned file_index = 0u;
    unsigned square_index = CHESSBOARD_SIZE - mFiles.size() ;//56, index of a8
    unsigned slash_counter = 0u;
    unsigned counter_between_slashes = 0u;

    std::vector<Square* > temp_squares;
    temp_squares.resize(CHESSBOARD_SIZE);
    for (unsigned i = 0; i <temp_squares.size(); ++i )
    {
        temp_squares[i] = new Square();
    }

    //parse the string character by character
    for (unsigned i = 0; i < rFenPosition.length(); ++i)
    {
        if (rFenPosition[i] == '/')
        {
            if (counter_between_slashes != 8u)
            {
                rc = 0;
                break;
            }
            counter_between_slashes = 0u;
            slash_counter++;
            if (slash_counter > 7u)
            {
                rc = 0;
                break;
            }
            rank_index--;
            file_index = 0;//new rank, start from file a
            square_index = square_index - 2*mFiles.size();
            continue;//this one is a slash, no need to do anything, go to next loop.
        }
        if (counter_between_slashes > 8u)
        {
            rc = 0;
            break;
        }
        if ( (slash_counter == 7u) && (rFenPosition[i] == ' ') )
        {
            if (counter_between_slashes==8u)
            {
                break;
            }
            else
            {
                rc = 0;
                break;
            }
        }

        if ( isdigit (rFenPosition[i]))//if it is a number
        {
            int empty_squares = atoi (&rFenPosition[i]);//an integer now
            if ((counter_between_slashes + empty_squares) > 8)
            {
                rc = 0;
                break;
            }
            for (unsigned n = 0; n < (unsigned) empty_squares; ++n)
            {
                assert(square_index < CHESSBOARD_SIZE);
                temp_squares[square_index]->SetPieceOnThisSquare(NO_PIECE);
                file_index++;
                square_index++;
                counter_between_slashes++;
            }
        }
        else if (isalpha (rFenPosition[i]))
        {
            counter_between_slashes++;
            if (counter_between_slashes > 8u)
            {
                rc = 0;
                break;
            }

            PieceType piece_to_be_assigned;
            //assign a piece (returns 0 if the letter is invalid
            int valid_piece = AssignPieceFromLetter(piece_to_be_assigned, rFenPosition[i]);
            assert(square_index < CHESSBOARD_SIZE);
            temp_squares[square_index]->SetPieceOnThisSquare(piece_to_be_assigned);
            if (valid_piece != 1)
            {
                rc = 0;
                break;
            }
            file_index++;
            square_index++;
        }
    }

    //if there were too many slashes
    if ( (slash_counter != 7u))
    {
        rc = 0;
    }

    //take care of the nasty case of an empty string.
    if (rFenPosition.length() == 0u)
    {
        rc = 0;
    }

    //actually assign the pieces to the data structure
    for (unsigned i = 0; i <temp_squares.size(); ++i )
    {
        //...only if the fen was valid...
        if (rc != 0)
        {
            mSquares[i]->SetPieceOnThisSquare( temp_squares[i]->GetPieceOnThisSquare() );
        }
        delete temp_squares[i];
    }
    return rc;
}
