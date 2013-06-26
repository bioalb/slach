#include <iostream>
#include "Move.hpp"

slach::Move::Move()
    : mpOrigin(NULL),
      mpDestination(NULL),
      mGivesCheck(false)
{
}

slach::Move::Move(Square* pOrigin, Square* pDestination)
    : mpOrigin(pOrigin),
      mpDestination(pDestination),
      mGivesCheck(false)
{
}

slach::Move::Move (const Move& move)
  :mpOrigin (move.GetOrigin()),
   mpDestination (move.GetDestination() ),
   mGivesCheck(move.DoesMoveGiceCheck())
{
}

slach::Move& slach::Move::operator=(const Move& from)
{
    if (this != &from)
    {
       mpOrigin = from.GetOrigin();
       mpDestination = from.GetDestination();
    }

    return *this;
}

slach::Move::~Move()
{
}

slach::Square* slach::Move::GetOrigin() const
{
    return mpOrigin;
}

slach::Square* slach::Move::GetDestination() const
{
    return mpDestination;
}

bool slach::Move::IsWhiteKingMoving() const
{
    if (mpOrigin->GetPieceOnThisSquare()==WHITE_KING)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool slach::Move::IsBlackKingMoving() const
{
    if (mpOrigin->GetPieceOnThisSquare()==BLACK_KING)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool slach::Move::IsWhiteCastlingKingSide() const
{
    if ((mpOrigin->GetIndexFromA1()==4u) &&
        (mpOrigin->GetPieceOnThisSquare()==WHITE_KING) &&
         mpDestination->GetIndexFromA1()==6u)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool slach::Move::IsBlackCastlingKingSide() const
{
    if ((mpOrigin->GetIndexFromA1()==60u) &&
        (mpOrigin->GetPieceOnThisSquare()==BLACK_KING) &&
         mpDestination->GetIndexFromA1()==62u)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool slach::Move::IsWhiteCastlingQueenSide() const
{
    if ((mpOrigin->GetIndexFromA1()==4u) &&
        (mpOrigin->GetPieceOnThisSquare()==WHITE_KING) &&
         mpDestination->GetIndexFromA1()==2u)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool slach::Move::IsBlackCastlingQueenSide() const
{
    if ((mpOrigin->GetIndexFromA1()==60u) &&
        (mpOrigin->GetPieceOnThisSquare()==BLACK_KING) &&
         mpDestination->GetIndexFromA1()==58u)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool slach::Move::IsSpecialMove() const
{
    return (IsWhiteCastlingKingSide() ||
            IsBlackCastlingKingSide() ||
            IsWhiteCastlingQueenSide() ||
            IsBlackCastlingQueenSide() ||
            IsWhitePromoting() ||
            IsBlackPromoting() ||
            IsKingSideWhiteRookMoving() ||
            IsQueenSideWhiteRookMoving() ||
            IsKingSideBlackRookMoving() ||
            IsQueenSideBlackRookMoving() ||
            IsBlackKingMoving() ||
            IsWhiteKingMoving()
            );
}
bool slach::Move::IsWhitePromoting() const
{
    if ((mpOrigin->GetPieceOnThisSquare()==WHITE_PAWN)&&
        (mpOrigin->IsSeventhRank()))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool slach::Move::IsBlackPromoting() const
{
    if ((mpOrigin->GetPieceOnThisSquare()==BLACK_PAWN)&&
        (mpOrigin->IsSecondRank()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool slach::Move::IsKingSideWhiteRookMoving() const
{
    if ((mpOrigin->GetPieceOnThisSquare()==WHITE_ROOK)&&
        (mpOrigin->GetIndexFromA1()==7u))//h1
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool slach::Move::IsQueenSideWhiteRookMoving() const
{
    if ((mpOrigin->GetPieceOnThisSquare()==WHITE_ROOK)&&
        (mpOrigin->GetIndexFromA1()==0u))//a1
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool slach::Move::IsKingSideBlackRookMoving() const
{
    if ((mpOrigin->GetPieceOnThisSquare()==BLACK_ROOK)&&
        (mpOrigin->GetIndexFromA1()==63u))//h8
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool slach::Move::IsQueenSideBlackRookMoving() const
{
    if ((mpOrigin->GetPieceOnThisSquare()==BLACK_ROOK)&&
        (mpOrigin->GetIndexFromA1()==56u))//h1
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool slach::Move::DoesMoveRequireSpecialGuiHandling() const
{
    return (IsWhiteCastlingKingSide() ||
            IsBlackCastlingKingSide() ||
            IsWhiteCastlingQueenSide() ||
            IsBlackCastlingQueenSide() ||
            IsWhitePromoting() ||
            IsBlackPromoting() ||
            IsWhiteCapturingEnPassant() ||
            IsBlackCapturingEnPassant()
            );
}

bool slach::Move::IsWhiteCapturingEnPassant() const
{
	if (mpOrigin->GetPieceOnThisSquare() == WHITE_PAWN &&
		mpDestination->GetPieceOnThisSquare() == NO_PIECE &&
		mpDestination->IsSixthRank() &&
		(abs(mpDestination->GetIndexFromA1() - mpOrigin->GetIndexFromA1()) == 7 ||
		 abs(mpDestination->GetIndexFromA1() - mpOrigin->GetIndexFromA1()) == 9)  )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool slach::Move::IsBlackCapturingEnPassant() const
{
	if (mpOrigin->GetPieceOnThisSquare() == BLACK_PAWN &&
		mpDestination->GetPieceOnThisSquare() == NO_PIECE &&
		mpDestination->IsThirdRank() &&
		(abs(mpDestination->GetIndexFromA1() - mpOrigin->GetIndexFromA1()) == 7 ||
		 abs(mpDestination->GetIndexFromA1() - mpOrigin->GetIndexFromA1()) == 9)  )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool slach::Move::DoesMoveGiceCheck() const
{
	return mGivesCheck;
}

void slach::Move::GivesCheck(bool gives)
{
	mGivesCheck = gives;
}

std::string slach::Move::GetMoveInAlgebraicFormat(std::string ambiguityPrefix) const
{
    if (IsBlackCastlingKingSide() || IsWhiteCastlingKingSide())
    {
        return "O-O";
    }
    else if (IsBlackCastlingQueenSide() || IsWhiteCastlingQueenSide())
    {
        return "O-O-O";
    }
    else//normal move
    {
        slach::PieceType origin_piece = mpOrigin->GetPieceOnThisSquare();
        std::string piece_code = "";

        if (IsBishop(origin_piece))
        {
            piece_code="B";
        }
        else if (IsQueen(origin_piece))
        {
            piece_code = "Q";
        }
        else if (IsKing(origin_piece))
        {
            piece_code = "K";
        }
        else if(IsKnight(origin_piece))
        {
            piece_code = "N";
        }
        else if(IsRook(origin_piece))
        {
            piece_code = "R";
        }
        else if (IsPawn(origin_piece))
        {
            piece_code = "";
        }

       //work out the presence of the capture symbol
       std::string capture_symbol = "";
       if (!(mpDestination->GetPieceOnThisSquare()==NO_PIECE) ||
		   IsBlackCapturingEnPassant() ||
		   IsWhiteCapturingEnPassant() )
       {
           capture_symbol = "x";
           //if a pawn is capturing, the origin file must be included
           if ( (origin_piece == BLACK_PAWN) || (origin_piece == WHITE_PAWN) )
           {
               piece_code = mpOrigin->GetFile();
           }
       }

       std::string promotion_suffix = "";
       if (IsBlackPromoting() || IsWhitePromoting())
       {
           promotion_suffix = "=Q";
       }

       std::string suffix;
       if (mGivesCheck == true)
       {
    	   suffix = "+";
       }
       return (piece_code + ambiguityPrefix + capture_symbol + mpDestination->GetFile() + mpDestination->GetRank() + promotion_suffix + suffix);
    }
}
