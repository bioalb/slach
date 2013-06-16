#include "Game.hpp"
#include "Exception.hpp"

slach::Game::Game()
{
    mMoveList.resize(0u);
    mMoveListAlgFormat.resize(0u);
}
slach::Game::~Game()
{

}

std::vector<slach::Move*> slach::Game::GetMoveList() const
{
    return mMoveList;
}

std::vector<std::string> slach::Game::GetMoveListAlgebraicFormat() const
{
    return mMoveListAlgFormat;
}

void slach::Game::AddMove(Move* move, std::string ambiguityPrefix, std::string suffix)
{
    mMoveList.push_back(move);
    mMoveListAlgFormat.push_back(move->GetMoveInAlgebraicFormat());
}

