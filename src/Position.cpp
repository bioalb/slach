#include <cassert>
#include "Exception.hpp"
#include "HelperGlobalFunctions.hpp"
#include "Position.hpp"

slach::Position::Position()
   : mpFenHandler(new FenHandler() ),
     mpLegalMoveChecker (new LegalMoveChecker() ),
     mWhitePromotionPiece(WHITE_QUEEN),
     mBlackPromotionPiece(BLACK_QUEEN)
{

}

slach::Position::~Position()
{
    delete mpFenHandler;
    delete mpLegalMoveChecker;
}

int slach::Position::SetFromFen(const std::string& rFenPosition, std::vector<Square*>& rSquares)
{
	FenPositionFeatures temp;
    //if the fen is valid, this changes rSquares.
     int rc = mpFenHandler->SetPositionFromFen(rFenPosition, rSquares,temp);
     if (rc == 0)//only if fen is valid
     {
    	 mCurrentFenPosition = rFenPosition;
    	 mPositionFeatures = temp;
     }
     return rc;
}

bool slach::Position::IsMoveLegal(Move& rMove, std::vector<Square*>& rSquares)
{
    unsigned amb;
    bool ret =  mpLegalMoveChecker->IsMoveLegalInPosition(rSquares,
														  rMove,
														  mPositionFeatures.mTurnToMove,
														  mPositionFeatures.mCastlingRights,
														  mPositionFeatures.mIndexOfEnpassant,
														  mMoveGivesCheck,
														  amb);
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

    assert(origin_index<rSquares.size());//segfault guard
    assert(destination_index<rSquares.size());//segfault guard

    //check for pawn move to adjust the clock and enpassant tag
    mPositionFeatures.mIndexOfEnpassant = 64u;
    if (IsPawn(rSquares[origin_index]->GetPieceOnThisSquare() ) )
    {
        if (abs(origin_index - destination_index) == 16)
        {
            if (origin_index < 16)//white pawn
            {
            	mPositionFeatures.mIndexOfEnpassant = origin_index + 8u;
            }
            else
            {
            	mPositionFeatures.mIndexOfEnpassant = origin_index - 8u;
            }
        }
        mPositionFeatures.mHalfMoveClockSinceLastPawnMove = 0u;
    }
    else//not a pawn move, increase the clock
    {
    	mPositionFeatures.mHalfMoveClockSinceLastPawnMove++;
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
    if (mPositionFeatures.mTurnToMove == slach::BLACK)
    {
    	mPositionFeatures.mTurnToMove = slach::WHITE;//black has moved, white's turn
    	mPositionFeatures.mMoveCounter++;//black has moved, increment move clock
    }
    else //it was white's turn
    {
    	mPositionFeatures.mTurnToMove = slach::BLACK;//white has moved, black's turn
    }

    //get a valid fen for the new position
    mCurrentFenPosition = mpFenHandler->GetFenFromPosition(rSquares,mPositionFeatures);
}

slach::Colour slach::Position::GetTurnToMove() const
{
	return mPositionFeatures.mTurnToMove;
}

std::string slach::Position::GetPositionAsFen() const
{
	return mCurrentFenPosition;
}

slach::FenPositionFeatures slach::Position::GetPositionFeatures() const
{
	return mPositionFeatures;
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
        if (mPositionFeatures.mTurnToMove == WHITE)
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
        DeleteCastlingRights(WHITE_KINGSIDE, mPositionFeatures.mCastlingRights);
        DeleteCastlingRights(WHITE_QUEENSIDE, mPositionFeatures.mCastlingRights);
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
        DeleteCastlingRights(BLACK_KINGSIDE, mPositionFeatures.mCastlingRights);
        DeleteCastlingRights(BLACK_QUEENSIDE, mPositionFeatures.mCastlingRights);
    }
    else if (rMove.IsKingSideWhiteRookMoving())
    {
		DeleteCastlingRights(WHITE_KINGSIDE, mPositionFeatures.mCastlingRights);
		MoveThePieces(rMove, rSquares);
    }
    else if (rMove.IsQueenSideWhiteRookMoving())
    {
		DeleteCastlingRights(WHITE_QUEENSIDE, mPositionFeatures.mCastlingRights);
		MoveThePieces(rMove, rSquares);
    }
    else if (rMove.IsKingSideBlackRookMoving())
    {
		DeleteCastlingRights(BLACK_KINGSIDE, mPositionFeatures.mCastlingRights);
		MoveThePieces(rMove, rSquares);
    }
    else if(rMove.IsQueenSideBlackRookMoving())
    {
		DeleteCastlingRights(BLACK_QUEENSIDE, mPositionFeatures.mCastlingRights);
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
        EXCEPTION("slach::Position::SetPromotionPiece: you can't set a pawn to be a promotion piece");
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
