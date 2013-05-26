#include "ChessBoard.hpp"
#include "Exception.hpp"
#include <cassert>
#include <cstdio>
#include <iostream>

slach::ChessBoard::ChessBoard()
{
    //allocate memory for the vectors
    mSquares.resize(CHESSBOARD_SIZE);

    mFiles = {"a", "b", "c", "d", "e","f", "g",  "h"};
    mRanks = {"1", "2", "3", "4", "5","6", "7",  "8"};

    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        mSquares[i] = new Square();
    }

    mTurnToMove = WHITE;

    mpFenHandler = new FenHandler();
}

slach::ChessBoard::~ChessBoard()
{
    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        delete mSquares[i];
    }
    delete mpFenHandler;
}

std::vector<slach::Square* > slach::ChessBoard::GetSquares() const
{
    return mSquares;
}

void slach::ChessBoard::SetupInitialChessPosition()
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

void slach::ChessBoard::SetupChessBoard()
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

bool slach::ChessBoard::IsLegalMove()
{
    return true;
}

void slach::ChessBoard::MakeThisMove(const Move& rMove)
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


int slach::ChessBoard::ArrangePiecesFromFEN(const std::string &rFenPosition)
{
     int rc = mpFenHandler->SetPositionFromFen(rFenPosition, mSquares);
     if (rc ==0)
     {
         mTurnToMove = mpFenHandler->WhosTurnIsIt();
     }
     return rc;
}

slach::TurnToMove slach::ChessBoard::WhosTurnIsIt() const
{
    return mTurnToMove;
}
