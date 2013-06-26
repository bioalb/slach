#include <cassert>
#include "Exception.hpp"
#include "Position.hpp"

slach::Position::Position()
   : mToMove(WHITE),
     mMoveNumber(1),
     mpFenHandler(new FenHandler() ),
     mpLegalMoveChecker (new LegalMoveChecker() ),
     mWhitePromotionPiece(WHITE_QUEEN),
     mBlackPromotionPiece(BLACK_QUEEN)
{

}

slach::Position::~Position()
{

}

int slach::Position::SetFromFen(const std::string& rFenPosition, std::vector<Square*>& rSquares)
{
    //if the fen is valid, this changes rSquares.
     int rc = mpFenHandler->SetPositionFromFen(rFenPosition, rSquares);
     if (rc == 0)//only if fen is valid
     {
         mCurrentFenPosition = rFenPosition;
         mCastlingRights = mpFenHandler->GetLatestCastlingRights();
         mMoveNumber = mpFenHandler->GetFullMoveClock();
         mHalfMovesSinceLastPawnMove = mpFenHandler->GetHalfMoveClock();
         mToMove = mpFenHandler->WhosTurnIsIt();
     }
     return rc;
}

bool slach::Position::IsMoveLegal(Move& rMove, std::vector<Square*>& rSquares)
{
    bool ret =  mpLegalMoveChecker->IsMoveLegalInPosition(rSquares,
														  rMove,
														  mpFenHandler->WhosTurnIsIt(),
														  mpFenHandler->GetLatestCastlingRights(),
														  mpFenHandler->GetEnPassantSquareIndex(),
														  mMoveGivesCheck);
    if (mMoveGivesCheck == true)
    {
        rMove.GivesCheck(true);
    }

    return ret;
}

void slach::Position::UpdatePositionWithMove(slach::Move& rMove, std::vector<Square*>& rSquares)
{
    unsigned origin_index = rMove.GetOrigin()->GetIndexFromA1();
    unsigned destination_index = rMove.GetDestination()->GetIndexFromA1();

    Square* p_en_passant_square = NULL;

    assert(origin_index<rSquares.size());//segfault guard
    assert(destination_index<rSquares.size());//segfault guard

    //check for pawn move to adjust the clock and enpassant tag
    if (IsPawn(rSquares[origin_index]->GetPieceOnThisSquare() ) )
    {
        if (abs(origin_index - destination_index) == 16)
        {
            if (origin_index < 16)//white pawn
            {
            	p_en_passant_square = rSquares[origin_index + 8u];
            }
            else
            {
            	p_en_passant_square = rSquares[origin_index - 8u];
            }
        }
        mHalfMovesSinceLastPawnMove = 0u;
    }
    else//not a pawn move, increase the clock
    {
    	mHalfMovesSinceLastPawnMove++;
    }

    if (rMove.IsSpecialMove() == true)
    {
        ProcessSpecialMove(rMove, rSquares);
    }
    else
    {
        //Now move the pieces
        MoveThePieces(rMove, rSquares);
    } //otherwise the special move method above  would have processed it

    //update turn to move and move counter
    if (mToMove == slach::BLACK)
    {
    	mToMove = slach::WHITE;//black has moved, white's turn
    	mMoveNumber++;//black has moved, increment move clock
    }
    else //it was white's turn
    {
    	mToMove = slach::BLACK;//white has moved, black's turn
    }

    //get a valid fen for the new position and update the member variable
    mCurrentFenPosition = mpFenHandler->GetFenFromPosition(rSquares, mToMove,
    		mCastlingRights,
    		p_en_passant_square,
    		mHalfMovesSinceLastPawnMove,
    		mMoveNumber);

    //this line will update squares and all other details within the fen handler
    mpFenHandler->SetPositionFromFen(mCurrentFenPosition, rSquares);
}

slach::Colour slach::Position::GetTurnToMove() const
{
	return mToMove;
}

std::string slach::Position::GetPositionAsFen() const
{
	return mCurrentFenPosition;
}

void  slach::Position::MoveThePieces(const Move& rMove, std::vector<Square*>& rSquares)
{
    unsigned origin_index = rMove.GetOrigin()->GetIndexFromA1();
    unsigned destination_index = rMove.GetDestination()->GetIndexFromA1();
    PieceType origin_piece = rSquares[origin_index]->GetPieceOnThisSquare();

    //check if it enpassant
    if (IsPawn(origin_piece) &&
        (abs(destination_index - origin_index) != 8) &&
        (abs(destination_index - origin_index) != 16) &&
        rSquares[destination_index]->GetPieceOnThisSquare() == NO_PIECE)
    {
        if (mToMove == WHITE)
        {
            if (abs(destination_index-origin_index) == 7)//enpassant on the left
            {
            	rSquares[origin_index-1]-> SetPieceOnThisSquare(NO_PIECE);
            }
            else
            {
            	rSquares[origin_index+1]-> SetPieceOnThisSquare(NO_PIECE);
            }
        }
        else //black
        {
            if (abs(destination_index-origin_index) == 9)//enpassant on the left
            {
            	rSquares[origin_index-1]-> SetPieceOnThisSquare(NO_PIECE);
            }
            else
            {
            	rSquares[origin_index+1]-> SetPieceOnThisSquare(NO_PIECE);
            }
        }
    }

    rSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);//no more piece here
    rSquares[destination_index]->SetPieceOnThisSquare(origin_piece);
}

void slach::Position::ProcessSpecialMove(const Move& rMove, std::vector<Square*>& rSquares)
{
    unsigned origin_index = rMove.GetOrigin()->GetIndexFromA1();
    unsigned destination_index = rMove.GetDestination()->GetIndexFromA1();

    if (rMove.IsWhiteKingMoving())
    {
        if (rMove.IsWhiteCastlingKingSide())
        {
        	rSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);
        	rSquares[destination_index]->SetPieceOnThisSquare(WHITE_KING);
        	rSquares[origin_index+1]->SetPieceOnThisSquare(WHITE_ROOK);
        	rSquares[7]->SetPieceOnThisSquare(NO_PIECE);//h1
        }
        else if (rMove.IsWhiteCastlingQueenSide())
        {
        	rSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);
        	rSquares[destination_index]->SetPieceOnThisSquare(WHITE_KING);
        	rSquares[origin_index-1]->SetPieceOnThisSquare(WHITE_ROOK);
        	rSquares[0]->SetPieceOnThisSquare(NO_PIECE);//a1
        }
        else
        {
            MoveThePieces(rMove, rSquares);
        }
        //white can't castle anymore anyway
        DeleteCastlingRights(WHITE_KINGSIDE, mCastlingRights);
        DeleteCastlingRights(WHITE_QUEENSIDE, mCastlingRights);
    }
    else if (rMove.IsBlackKingMoving())
    {
        if (rMove.IsBlackCastlingKingSide())
        {
        	rSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);
        	rSquares[destination_index]->SetPieceOnThisSquare(BLACK_KING);
        	rSquares[origin_index+1]->SetPieceOnThisSquare(BLACK_ROOK);
        	rSquares[63]->SetPieceOnThisSquare(NO_PIECE);//h8
        }
        else if (rMove.IsBlackCastlingQueenSide())
        {
        	rSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);
        	rSquares[destination_index]->SetPieceOnThisSquare(BLACK_KING);
        	rSquares[origin_index-1]->SetPieceOnThisSquare(BLACK_ROOK);
        	rSquares[56]->SetPieceOnThisSquare(NO_PIECE);//a8
        }
        else
        {
            MoveThePieces(rMove, rSquares);
        }
        //black can't castle anymore anyway
        DeleteCastlingRights(BLACK_KINGSIDE, mCastlingRights);
        DeleteCastlingRights(BLACK_QUEENSIDE, mCastlingRights);
    }
    else if (rMove.IsKingSideWhiteRookMoving())
    {
		DeleteCastlingRights(WHITE_KINGSIDE, mCastlingRights);
		MoveThePieces(rMove, rSquares);
    }
    else if (rMove.IsQueenSideWhiteRookMoving())
    {
		DeleteCastlingRights(WHITE_QUEENSIDE, mCastlingRights);
		MoveThePieces(rMove, rSquares);
    }
    else if (rMove.IsKingSideBlackRookMoving())
    {
		DeleteCastlingRights(BLACK_KINGSIDE, mCastlingRights);
		MoveThePieces(rMove, rSquares);
    }
    else if(rMove.IsQueenSideBlackRookMoving())
    {
		DeleteCastlingRights(BLACK_QUEENSIDE, mCastlingRights);
		MoveThePieces(rMove, rSquares);
    }
    else if (rMove.IsWhitePromoting())
    {
        rSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);
        rSquares[destination_index]->SetPieceOnThisSquare(mWhitePromotionPiece);
    }
    else if (rMove.IsBlackPromoting())
    {
        rSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);
        rSquares[destination_index]->SetPieceOnThisSquare(mBlackPromotionPiece);
    }
    else
    {
       // NEVER_REACHED;
    }
}

void slach::Position::SetPromotionPiece(slach::PieceType piece)
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
