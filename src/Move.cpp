#include "Move.hpp"

slach::Move::Move(Square* pOrigin, Square* pDestination)
    : mpOrigin(pOrigin),
      mpDestination(pDestination),
      mAmbiguityPrefix(""),
      mSuffix("")
{
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
            IsQueenSideBlackRookMoving()
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

std::string slach::Move::GetMoveInAlgebraicFormat()
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
       if (mpDestination->GetPieceOnThisSquare()!=NO_PIECE)
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
       return (piece_code + mAmbiguityPrefix + capture_symbol + mpDestination->GetFile() + mpDestination->GetRank() + promotion_suffix + mSuffix);
    }
}
