#include <cassert>
#include <cstdio>
#include <iostream>

#include "ChessBoard.hpp"
#include "Exception.hpp"

slach::ChessBoard::ChessBoard()
{
    //allocate memory for the vectors
    mSquares.resize(CHESSBOARD_SIZE);

    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        mSquares[i] = new Square();
    }

    mTurnToMove = WHITE;

    mpFenHandler = new FenHandler();
    mpEngineInterface = new EngineInterface();
}

slach::ChessBoard::~ChessBoard()
{
    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        delete mSquares[i];
    }
    delete mpFenHandler;
    delete mpEngineInterface;
}

std::vector<slach::Square* > slach::ChessBoard::GetSquares() const
{
    return mSquares;
}

void slach::ChessBoard::SetupInitialChessPosition()
{
    mCurrentFenPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    mpFenHandler->SetPositionFromFen(mCurrentFenPosition, mSquares);
    std::vector<CastlingRights> mCastlingRights = {WHITE_KINGSIDE, BLACK_KINGSIDE, WHITE_QUEENSIDE, BLACK_QUEENSIDE};
    mpEnPassantSquare = NULL;
    mHalfMoveClock = 0;
    mFullMoveClock = 1;
}

void slach::ChessBoard::SetupChessBoard()
{
    unsigned row=0;//row counter
    unsigned column=0;//column counter
    unsigned bw_counter = 0; //at zero, it will start with black (square A1).

    //will create the squares row by row, starting from bottom left (A1)
    for (unsigned index = 0; index < CHESSBOARD_SIZE; ++index)
    {
        assert(row<CHESSBOARD_RANKS.size());
        assert(column<CHESSBOARD_FILES.size());
        mSquares[index]->SetFile(CHESSBOARD_FILES[column]);
        mSquares[index]->SetRank(CHESSBOARD_RANKS[row]);
        mSquares[index]->SetIndexFromA1(index);

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

bool slach::ChessBoard::IsLegalMove(const Move& rMove) const
{
    return mpEngineInterface->IsMoveValidInPosition(mCurrentFenPosition, rMove);
}

void slach::ChessBoard::MakeThisMove(const Move& rMove)
{
    Square* origin = rMove.first;
    Square* destination = rMove.second;

    //check for pawn move
    if ((origin->GetPieceOnThisSquare() == WHITE_PAWN) || (origin->GetPieceOnThisSquare() == BLACK_PAWN))
    {
        if (abs(origin->GetIndexFromA1() - destination->GetIndexFromA1()) == 16)
        {
            if (origin->GetIndexFromA1() < 16)//white pawn
            {
                mpEnPassantSquare = mSquares[origin->GetIndexFromA1() + 8u];
            }
            else
            {
                mpEnPassantSquare = mSquares[origin->GetIndexFromA1() - 8u];
            }
        }
        mHalfMoveClock = 0;
    }

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

    mCastlingRights = mpFenHandler->GetLatestCastlingRights();
    mHalfMoveClock = mpFenHandler->GetHalfMoveClock();
    mFullMoveClock = mpFenHandler->GetFullMoveClock();
    mTurnToMove = mpFenHandler->WhosTurnIsIt();
    if (mTurnToMove == slach::BLACK)
    {
        mTurnToMove = slach::WHITE;//black has moved, white's turn
        mFullMoveClock++;//black has moved, increment move clock
    }
    else //it was white's turn
    {
        mTurnToMove = slach::BLACK;//white has moved, black's turn
    }
    mCurrentFenPosition = mpFenHandler->GetFenFromPosition(mSquares, mTurnToMove,
            mCastlingRights,
            mpEnPassantSquare,
            mHalfMoveClock,
            mFullMoveClock);
    mpEnPassantSquare = NULL;
}


int slach::ChessBoard::SetFenPosition(const std::string &rFenPosition)
{
    //if the fen is valid, this changes mSquares.
     int rc = mpFenHandler->SetPositionFromFen(rFenPosition, mSquares);
     if (rc == 0)//only if fen is valid
     {
         mTurnToMove = mpFenHandler->WhosTurnIsIt();
         mCurrentFenPosition = rFenPosition;
     }
     return rc;
}

std::string slach::ChessBoard::GetCurrentFenPosition() const
{
    return mCurrentFenPosition;
}

slach::TurnToMove slach::ChessBoard::WhosTurnIsIt() const
{
    return mTurnToMove;
}
