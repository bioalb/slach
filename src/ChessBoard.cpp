#include <cassert>
#include <cstdio>
#include <iostream>

#include "ChessBoard.hpp"
#include "Exception.hpp"

slach::ChessBoard::ChessBoard()
  : mpPosition(new Position()),
    mpGame(new Game())

{
    //allocate memory for the vectors
    mSquares.resize(gChessBoardSize);

    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        mSquares[i] = new Square();
    }
}

slach::ChessBoard::~ChessBoard()
{
    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        delete mSquares[i];
    }
    delete mpGame;
    delete mpPosition;
}

std::vector<slach::Square* > slach::ChessBoard::GetSquares() const
{
    return mSquares;
}

void slach::ChessBoard::ResetToMoveNumber(int moveNumber, slach::Colour colour)
{
    mpPosition->SetFromFen(mpGame->FetchFromFenList(moveNumber, colour) , mSquares);
}

void slach::ChessBoard::SetupInitialChessPosition()
{
    std::string initial = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    mpPosition->SetFromFen(initial, mSquares);
    mpGame->AddPosition(initial);
}

slach::PgnValidity slach::ChessBoard::LoadGameFromPgn(const std::string& gameString)
{
    return mpGame->LoadFromPgnString(gameString,mSquares);
}

void slach::ChessBoard::SetupChessBoard()
{
    unsigned row=0;//row counter
    unsigned column=0;//column counter
    unsigned bw_counter = 0; //at zero, it will start with black (square A1).

    //will create the squares row by row, starting from bottom left (A1)
    for (unsigned index = 0; index < gChessBoardSize; ++index)
    {
        assert(row<gChessboardRanks.size());
        assert(column<gChessboardFiles.size());
        mSquares[index]->SetFile(gChessboardFiles[column]);
        mSquares[index]->SetRank(gChessboardRanks[row]);
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

        if ( (column%(gBoardRowSize)==0) )
        {
            bw_counter++;//trick the counter, end of a row and beginning of new one have same colour
            row++;
            column=0;
        }
    }
}

bool slach::ChessBoard::IsLegalMove(Move& rMove)
{
    return mpPosition->IsMoveLegal(rMove, mSquares);
}

slach::Game* slach::ChessBoard::GetGame() const
{
	return mpGame;
}

void slach::ChessBoard::MakeThisMove(Move& rMove)
{
    mpGame->AddMove(rMove);
    mpPosition->UpdatePositionWithMove(rMove,mSquares);
    mpGame->AddPosition(mpPosition->GetPositionAsFen());
}


int slach::ChessBoard::SetFenPosition(const std::string &rFenPosition)
{
    return mpPosition->SetFromFen(rFenPosition, mSquares);
}

std::string slach::ChessBoard::GetCurrentFenPosition() const
{
    return mpPosition->GetPositionAsFen();
}

slach::Position* slach::ChessBoard::GetCurrentPosition() const
{
    return mpPosition;
}

slach::Colour slach::ChessBoard::WhosTurnIsIt() const
{
    return mpPosition->GetTurnToMove();
}

unsigned slach::ChessBoard::GetCurrentMoveNumber() const
{
    return mpPosition->GetPositionFeatures().mMoveCounter;
}

void slach::ChessBoard::SetPromotionPiece(slach::PieceType piece)
{
	mpPosition->SetPromotionPiece(piece);
}
