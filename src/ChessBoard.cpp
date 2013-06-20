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

    mWhitePromotionPiece = WHITE_QUEEN;
    mBlackPromotionPiece = BLACK_QUEEN;
    mMoveGivesCheck = false;
    mpFenHandler = new FenHandler();
    mpLegalMoveChecker = new LegalMoveChecker();
    mpGame = new Game();
}

slach::ChessBoard::~ChessBoard()
{
    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        delete mSquares[i];
    }
    delete mpFenHandler;
    delete mpLegalMoveChecker;
    delete mpGame;
}

std::vector<slach::Square* > slach::ChessBoard::GetSquares() const
{
    return mSquares;
}

void slach::ChessBoard::ResetToMoveNumber(int moveNumber, slach::Colour colour)
{
    mCurrentFenPosition = mpGame->FetchFromFenList(moveNumber, colour);
    mpFenHandler->SetPositionFromFen(mCurrentFenPosition, mSquares);
}

void slach::ChessBoard::SetupInitialChessPosition()
{
    mCurrentFenPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    mpFenHandler->SetPositionFromFen(mCurrentFenPosition, mSquares);
    mpGame->AddPosition(mCurrentFenPosition);
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

bool slach::ChessBoard::IsLegalMove(const Move& rMove)
{
    return mpLegalMoveChecker->IsMoveLegalInPosition(mSquares,
                                                     rMove,
                                                     mpFenHandler->WhosTurnIsIt(),
                                                     mpFenHandler->GetLatestCastlingRights(),
                                                     mpFenHandler->GetEnPassantSquareIndex(),
                                                     mMoveGivesCheck);
}

slach::Game* slach::ChessBoard::GetGame() const
{
	return mpGame;
}

void slach::ChessBoard::MakeThisMove(const Move& rMove)
{
    unsigned origin_index = rMove.GetOrigin()->GetIndexFromA1();
    unsigned destination_index = rMove.GetDestination()->GetIndexFromA1();

    //legal move, add it to the game
    if (mMoveGivesCheck == true)
    {
        mpGame->AddMove(rMove,"","+");
    }
    else
    {
        mpGame->AddMove(rMove);
    }

    std::vector<CastlingRights> castling_rights = mpFenHandler->GetLatestCastlingRights();
    unsigned full_move_clock = mpFenHandler->GetFullMoveClock();
    unsigned half_move_clock = mpFenHandler->GetHalfMoveClock();
    Colour turn_to_move = mpFenHandler->WhosTurnIsIt();
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

    if (rMove.IsSpecialMove() == true)
    {
        ProcessSpecialMove(rMove, castling_rights);
    }
    else
    {
        //Now move the pieces
        MoveThePieces(rMove);
    } //otherwise the special move method above  would have processed it


    //get a valid fen for the new position and update the member variable
    mCurrentFenPosition = mpFenHandler->GetFenFromPosition(mSquares, turn_to_move,
    		castling_rights,
    		p_en_passant_square,
            half_move_clock,
            full_move_clock);

    //this line will update squares and all other details within the fen handler
    mpFenHandler->SetPositionFromFen(mCurrentFenPosition, mSquares);
    mpGame->AddPosition(mCurrentFenPosition);
}

void  slach::ChessBoard::MoveThePieces(const Move& rMove)
{
    unsigned origin_index = rMove.GetOrigin()->GetIndexFromA1();
    unsigned destination_index = rMove.GetDestination()->GetIndexFromA1();

    PieceType origin_piece = mSquares[origin_index]->GetPieceOnThisSquare();
    mSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);//no more piece here
    mSquares[destination_index]->SetPieceOnThisSquare(origin_piece);
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

slach::Colour slach::ChessBoard::WhosTurnIsIt() const
{
    return mpFenHandler->WhosTurnIsIt();
}

void slach::ChessBoard::ProcessSpecialMove(const Move& rMove, std::vector<CastlingRights>& rCastlingRights)
{
    unsigned origin_index = rMove.GetOrigin()->GetIndexFromA1();
    unsigned destination_index = rMove.GetDestination()->GetIndexFromA1();

    if (rMove.IsWhiteCastlingKingSide())
    {
        mSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);
        mSquares[destination_index]->SetPieceOnThisSquare(WHITE_KING);
        mSquares[origin_index+1]->SetPieceOnThisSquare(WHITE_ROOK);
        mSquares[7]->SetPieceOnThisSquare(NO_PIECE);//h1

        //white can't castle anymore anyway
        DeleteCastlingRights(WHITE_KINGSIDE, rCastlingRights);
        DeleteCastlingRights(WHITE_QUEENSIDE, rCastlingRights);
    }
    else if (rMove.IsWhiteCastlingQueenSide())
    {
        mSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);
        mSquares[destination_index]->SetPieceOnThisSquare(WHITE_KING);
        mSquares[origin_index-1]->SetPieceOnThisSquare(WHITE_ROOK);
        mSquares[0]->SetPieceOnThisSquare(NO_PIECE);//a1

        //white can't castle anymore anyway
        DeleteCastlingRights(WHITE_KINGSIDE, rCastlingRights);
        DeleteCastlingRights(WHITE_QUEENSIDE, rCastlingRights);
    }
    else if (rMove.IsBlackCastlingKingSide())
    {
        mSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);
        mSquares[destination_index]->SetPieceOnThisSquare(BLACK_KING);
        mSquares[origin_index+1]->SetPieceOnThisSquare(BLACK_ROOK);
        mSquares[63]->SetPieceOnThisSquare(NO_PIECE);//h8

        //black can't castle anymore anyway
        DeleteCastlingRights(BLACK_KINGSIDE, rCastlingRights);
        DeleteCastlingRights(BLACK_QUEENSIDE, rCastlingRights);
    }
    else if (rMove.IsBlackCastlingQueenSide())
    {
        mSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);
        mSquares[destination_index]->SetPieceOnThisSquare(BLACK_KING);
        mSquares[origin_index-1]->SetPieceOnThisSquare(BLACK_ROOK);
        mSquares[56]->SetPieceOnThisSquare(NO_PIECE);//a8

        //black can't castle anymore anyway
        DeleteCastlingRights(BLACK_KINGSIDE, rCastlingRights);
        DeleteCastlingRights(BLACK_QUEENSIDE, rCastlingRights);
    }
    else if (rMove.IsKingSideWhiteRookMoving())
    {
		DeleteCastlingRights(WHITE_KINGSIDE, rCastlingRights);
		MoveThePieces(rMove);
    }
    else if (rMove.IsQueenSideWhiteRookMoving())
    {
		DeleteCastlingRights(WHITE_QUEENSIDE, rCastlingRights);
		MoveThePieces(rMove);
    }
    else if (rMove.IsKingSideBlackRookMoving())
    {
		DeleteCastlingRights(BLACK_KINGSIDE, rCastlingRights);
		MoveThePieces(rMove);
    }
    else if(rMove.IsQueenSideBlackRookMoving())
    {
		DeleteCastlingRights(BLACK_QUEENSIDE, rCastlingRights);
		MoveThePieces(rMove);
    }
    else if (rMove.IsWhitePromoting())
    {
        mSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);
        mSquares[destination_index]->SetPieceOnThisSquare(mWhitePromotionPiece);
    }
    else if (rMove.IsBlackPromoting())
    {
        mSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);
        mSquares[destination_index]->SetPieceOnThisSquare(mBlackPromotionPiece);
    }
    else
    {
        NEVER_REACHED;
    }
}


void slach::ChessBoard::SetPromotionPiece(slach::PieceType piece)
{
    if (IsPawn(piece))
    {
        EXCEPTION("slach::ChessBoard::SetPromotionPiece: you can't set a pawn to be a promotion piece");
    }
    if (IsWhitePiece(piece))
    {
        mWhitePromotionPiece = piece;
    }
    else//black
    {
        mBlackPromotionPiece = piece;
    }
}
