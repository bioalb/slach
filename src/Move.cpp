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
