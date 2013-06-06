#include <cassert>
#include <cstdio>
#include <iostream>

#include "ChessBoard.hpp"
#include "Exception.hpp"

slach::ChessBoard::ChessBoard()
{
    //allocate memory for the vectors
    mSquares.resize(gChessBoardSize);

    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        mSquares[i] = new Square();
    }



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

bool slach::ChessBoard::IsLegalMove(const Move& rMove) const
{
    return mpEngineInterface->IsMoveValidInPosition(mCurrentFenPosition, rMove);
}

void slach::ChessBoard::MakeThisMove(const Move& rMove)
{
    unsigned origin_index = rMove.first->GetIndexFromA1();
    unsigned destination_index = rMove.second->GetIndexFromA1();

    std::vector<CastlingRights> castling_rights = mpFenHandler->GetLatestCastlingRights();
    unsigned full_move_clock = mpFenHandler->GetFullMoveClock();
    unsigned half_move_clock = mpFenHandler->GetHalfMoveClock();
    TurnToMove turn_to_move = mpFenHandler->WhosTurnIsIt();
    Square* p_en_passant_square = NULL;

    assert(origin_index<mSquares.size());//segfault guard
    assert(destination_index<mSquares.size());//segfault guard

    //check for pawn move to adjust the clock and enpassant tag
    if ((mSquares[origin_index]->GetPieceOnThisSquare() == WHITE_PAWN) || (mSquares[origin_index]->GetPieceOnThisSquare() == BLACK_PAWN))
    {
        if (abs(origin_index - destination_index) == 16)
        {
            if (origin_index < 16)//white pawn
            {
            	p_en_passant_square = mSquares[origin_index + 8u];
            }
            else
            {
            	p_en_passant_square = mSquares[origin_index - 8u];
            }
        }
        half_move_clock = 0u;
    }
    else//not a pawn move, increase the clock
    {
    	half_move_clock++;
    }

    //update turn to move and move counter
    if (turn_to_move == slach::BLACK)
    {
    	turn_to_move = slach::WHITE;//black has moved, white's turn
    	full_move_clock++;//black has moved, increment move clock
    }
    else //it was white's turn
    {
    	turn_to_move = slach::BLACK;//white has moved, black's turn
    }

    SpecialMoveType special_move_type = ProcessSpecialMove(rMove, castling_rights);;

    if (special_move_type == ORDINARY_MOVE)
    {
		//Now move the pieces
		PieceType origin_piece = mSquares[origin_index]->GetPieceOnThisSquare();
		mSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);//no more piece here
		mSquares[destination_index]->SetPieceOnThisSquare(origin_piece);
    } //otherwise the special move method above  would have processed it


    //get a valid fen for the new position and update the member variable
    mCurrentFenPosition = mpFenHandler->GetFenFromPosition(mSquares, turn_to_move,
    		castling_rights,
    		p_en_passant_square,
            half_move_clock,
            full_move_clock);

    //this line will update squares and all other details within the fen handler
    mpFenHandler->SetPositionFromFen(mCurrentFenPosition, mSquares);
}


int slach::ChessBoard::SetFenPosition(const std::string &rFenPosition)
{
    //if the fen is valid, this changes mSquares.
     int rc = mpFenHandler->SetPositionFromFen(rFenPosition, mSquares);
     if (rc == 0)//only if fen is valid
     {
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
    return mpFenHandler->WhosTurnIsIt();
}

slach::SpecialMoveType slach::ChessBoard::ProcessSpecialMove(const Move& rMove, std::vector<CastlingRights>& rCastlingRights)
{
    unsigned origin_index = rMove.first->GetIndexFromA1();
    unsigned destination_index = rMove.second->GetIndexFromA1();

    SpecialMoveType ret =  ORDINARY_MOVE;

    if (mSquares[origin_index]->GetPieceOnThisSquare() == WHITE_KING)
    {
        //check for e1-g1
        if (origin_index == 4u && destination_index==6u)
        {
            mSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);
            mSquares[destination_index]->SetPieceOnThisSquare(WHITE_KING);
            mSquares[origin_index+1]->SetPieceOnThisSquare(WHITE_ROOK);
            mSquares[7]->SetPieceOnThisSquare(NO_PIECE);//h1
            ret = WHITE_CASTLE_KINGSIDE;
        }
        else if (origin_index == 4u && destination_index==2u) //e1-c1
        {
            mSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);
            mSquares[destination_index]->SetPieceOnThisSquare(WHITE_KING);
            mSquares[origin_index-1]->SetPieceOnThisSquare(WHITE_ROOK);
            mSquares[0]->SetPieceOnThisSquare(NO_PIECE);//a1
            ret = WHITE_CASTLE_QUEENSIDE;
        }

        //white can't castle anymore anyway
        for (unsigned i = 0; i < rCastlingRights.size(); ++i)
        {
            if ((rCastlingRights[i] == WHITE_KINGSIDE) || (rCastlingRights[i] == WHITE_QUEENSIDE))
            {
                rCastlingRights.erase(rCastlingRights.begin()+i);
                i--;//index will be incremented at next loop and must therefore be adjusted by minus 1
            }
        }
    }
    else if (mSquares[origin_index]->GetPieceOnThisSquare() == BLACK_KING)
    {

    }


    return ret;
}
