#include "Game.hpp"
#include "Exception.hpp"

slach::Game::Game()
  : mMoveList {},
    mMoveListAlgFormat {},
    mListOfFenPositions {},
    mSTR()
{
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

void slach::Game::AddMove(const Move& rMove)
{
    mMoveList.push_back(rMove);
    mMoveListAlgFormat.push_back(rMove.GetMoveInAlgebraicFormat());
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
		if (moveNumber<=0)
		{
			return mListOfFenPositions[0];
		}

		unsigned index = moveNumber*2;

		if (toMove == WHITE)
		{
			if ((index - 2)>=mListOfFenPositions.size())
			{
				return mListOfFenPositions.back();
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
				return mListOfFenPositions.back();
			}
			else
			{
				return mListOfFenPositions[index-1];
			}
		}
	}
}

slach::PgnValidity slach::Game::LoadFromPgnString(const std::string& rGameString)
{
    //Find end of tag pairs
    unsigned last_tag = rGameString.rfind(']');
    unsigned closed_bracket = 0;
    unsigned old_closed_bracket = 0;
    do
    {
        unsigned open_bracket = rGameString.find ('[',old_closed_bracket);
        closed_bracket = rGameString.find(']', open_bracket);
        std::string whole_tag = rGameString.substr(open_bracket, closed_bracket - open_bracket);

        //find, within the tag, the label (from start until either space or ")
        unsigned end_of_label = whole_tag.find_first_of(" \"");
        std::string label =  whole_tag.substr(1, end_of_label-1);

        unsigned first_inverted_commas = whole_tag.find('"');
        unsigned last_inverted_commas = whole_tag.rfind('"');
        std::string data = whole_tag.substr(first_inverted_commas+1, last_inverted_commas - first_inverted_commas - 1);
        for (unsigned i = 0; i < mSTR.mLabels.size(); ++i)
        {
            if (label == mSTR.mLabels[i])
            {
                mSTR.mData[i] = data;
            }
        }

        old_closed_bracket = closed_bracket;
    }
    while ( (closed_bracket != last_tag) &&  (closed_bracket != std::string::npos) );

    //from last_tag onward
    unsigned dot = rGameString.find('.', last_tag);
    unsigned beginning = rGameString.find_first_not_of(' ', dot+1);
    unsigned end = rGameString.find(' ', beginning+1);

    unsigned beginning_black_move = rGameString.find_first_not_of(' ', end+1);
    unsigned end_black_move = rGameString.find(' ', beginning_black_move+1);

    std::string move_san = rGameString.substr(beginning, end -beginning);
    std::string move_san_black = rGameString.substr(beginning_black_move, end_black_move -beginning_black_move);
    std::cout<<std::endl<<"*******"<<move_san<<"****"<<move_san_black<<std::endl;

    return VALID_PGN;
}

slach::SevenTagRoster slach::Game::GetSevenTagRoster() const
{
    return mSTR;
}
