#include "Move.hpp"

slach::Move::Move(Square* pOrigin, Square* pDestination)
    : mpOrigin(pOrigin),
      mpDestination(pDestination)
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
            IsBlackPromoting());
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
