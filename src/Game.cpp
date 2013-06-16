#include "Game.hpp"
#include "Exception.hpp"

slach::Game::Game()
{
    mMoveList.resize(0u);
    mMoveListAlgFormat.resize(0u);
    mListOfFenPositions.resize(0);
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

void slach::Game::AddPosition(std::string fenPosition)
{
    mListOfFenPositions.push_back(fenPosition);
}

void slach::Game::AddMove(Move* move, std::string ambiguityPrefix, std::string suffix)
{
    mMoveList.push_back(move);
    mMoveListAlgFormat.push_back(move->GetMoveInAlgebraicFormat(ambiguityPrefix, suffix));
}

std::string slach::Game::FetchFromFenList(unsigned moveNumber, Colour colour)
{
    if (moveNumber==0)//weird case, it should never happen, moveNumber should start from one
    {
        if (colour == WHITE)
        {
            return mListOfFenPositions[0];
        }
        else
        {
            return mListOfFenPositions[1];
        }
    }

    unsigned index = moveNumber*2;

    if (colour == WHITE)
    {
        if ((index - 2)>=mListOfFenPositions.size())
        {
            return mListOfFenPositions.back();
        }
        return mListOfFenPositions[index - 2];
    }
    else
    {
        if ((index - 1)>=mListOfFenPositions.size())
        {
            return mListOfFenPositions.back();
        }
        return mListOfFenPositions[index-1];
    }
}

