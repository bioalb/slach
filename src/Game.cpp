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

std::vector<slach::Move> slach::Game::GetMoveList() const
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

void slach::Game::AddMove(const Move& rMove, std::string ambiguityPrefix, std::string suffix)
{
    mMoveList.push_back(rMove);
    mMoveListAlgFormat.push_back(rMove.GetMoveInAlgebraicFormat(ambiguityPrefix, suffix));
}

std::string slach::Game::FetchFromFenList(int moveNumber, Colour toMove)
{
	if (mListOfFenPositions.size() == 0u)
	{
		return "";//empty string
	}
	else if (mListOfFenPositions.size() == 1u)
	{
		return mListOfFenPositions[0];
	}
	else
	{
		if (moveNumber<=0)//weird case, it should never happen, moveNumber should start from one
		{
			if (toMove == WHITE)
			{
				return mListOfFenPositions[0];
			}
			else
			{
				return mListOfFenPositions[1];
			}
		}

		unsigned index = moveNumber*2;

		if (toMove == WHITE)
		{
			if ((index - 2)>=mListOfFenPositions.size())
			{
				if (mListOfFenPositions.size()%2==0)
				{
					return mListOfFenPositions[mListOfFenPositions.size()-2];
				}
				else
				{
					return mListOfFenPositions.back();
				}
			}
			else
			{
				return mListOfFenPositions[index - 2];
			}
		}
		else
		{
			if ((index - 1)>=mListOfFenPositions.size())
			{
			    if (mListOfFenPositions.size()%2==0)
			    {
				    return mListOfFenPositions.back();
			    }
			    else
			    {
				    return mListOfFenPositions[mListOfFenPositions.size()-2];
			    }
			}
			else
			{
				return mListOfFenPositions[index-1];
			}
		}
	}
}

