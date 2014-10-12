#include <cassert>
#include "Game.hpp"
#include "Position.hpp"
#include "Exception.hpp"

slach::Game::Game()
  : mMoveListMainLine {},
    mMoveListMainLineAlgFormat {},
    mListOfFenPositionsMainLine {},
    mSTR(),
    mOTR(),
    mGameResult("*")
{
}
slach::Game::~Game()
{

}

std::vector<slach::Move> slach::Game::GetMoveList() const
{
    return mMoveListMainLine;
}

std::vector<std::string> slach::Game::GetMoveListAlgebraicFormat() const
{
    return mMoveListMainLineAlgFormat;
}

void slach::Game::AddPosition(std::string fenPosition)
{
    mListOfFenPositionsMainLine.push_back(fenPosition);
}

std::string slach::Game::GetGameResult() const
{
    return mGameResult;
}

void slach::Game::AddMove(const Move& rMove)
{
    mMoveListMainLine.push_back(rMove);
    mMoveListMainLineAlgFormat.push_back(rMove.GetMoveInAlgebraicFormat());
}

void slach::Game::ClearAllLists()
{
    mListOfFenPositionsMainLine.clear();
    mMoveListMainLine.clear();
    mMoveListMainLineAlgFormat.clear();
}

std::string slach::Game::FetchFromFenList(int moveNumber, Colour toMove)
{
	if (mListOfFenPositionsMainLine.size() == 0u)
	{
		return "";//empty string
	}
	else if (mListOfFenPositionsMainLine.size() == 1u)
	{
		return mListOfFenPositionsMainLine[0];
	}
	else
	{
		if (moveNumber<=0)
		{
			return mListOfFenPositionsMainLine[0];
		}

		unsigned index = moveNumber*2;

		if (toMove == WHITE)
		{
			if ((index - 2)>=mListOfFenPositionsMainLine.size())
			{
				return mListOfFenPositionsMainLine.back();
			}
			else
			{
			    return mListOfFenPositionsMainLine[index - 2];
			}
		}
		else
		{
			if ((index - 1)>=mListOfFenPositionsMainLine.size())
			{
				return mListOfFenPositionsMainLine.back();
			}
			else
			{
				return mListOfFenPositionsMainLine[index-1];
			}
		}
	}
}

bool slach::Game::IsThisTheGameResult(const std::string& toBeChecked)
{
    bool ret = false;
    if (toBeChecked == "0-1")
    {
        mGameResult = "0-1";
        ret = true;
    }
    else if(toBeChecked == "1-0")
    {
        mGameResult = "1-0";
        ret = true;
    }
    else if (toBeChecked == "1/2-1/2")
    {
        mGameResult = "1/2-1/2";
        ret = true;
    }
    else if (toBeChecked == "*")
    {
        mGameResult = "*";
        ret = true;
    }
    return ret;
}
slach::PgnValidity slach::Game::LoadFromPgnString(const std::string& rGameString, std::vector<Square* > squares)
{
    //Find end of tag pairs
    unsigned last_tag = rGameString.rfind(']');
    size_t closed_bracket = 0;
    unsigned old_closed_bracket = 0;
    do
    {
        unsigned open_bracket = rGameString.find ('[',old_closed_bracket);
        closed_bracket = rGameString.find(']', open_bracket);
        //check there is not another open bracket before the closed
        if (rGameString.find('[',open_bracket+1) < closed_bracket) return INVALID_PGN;

        std::string whole_tag = rGameString.substr(open_bracket, closed_bracket - open_bracket);

        //find, within the tag, the label (from start until either space or ")
        unsigned end_of_label = whole_tag.find_first_of(" \"");
        std::string label =  whole_tag.substr(1, end_of_label-1);
        unsigned first_inverted_commas = whole_tag.find('"');
        unsigned last_inverted_commas = whole_tag.rfind('"');
        std::string data = whole_tag.substr(first_inverted_commas+1, last_inverted_commas - first_inverted_commas - 1);
        //see if it is one the seven tags
        for (unsigned i = 0; i < mSTR.mLabels.size(); ++i)
        {
            if (label == mSTR.mLabels[i])
            {
                mSTR.mData[i] = data;
            }
        }
        //see if it is one of the additional tags
        for (unsigned i = 0; i < mOTR.mLabels.size(); ++i)
        {
            if (label == mOTR.mLabels[i])
            {
                mOTR.mData[i] = data;
            }
        }

        old_closed_bracket = closed_bracket;
    }
    while ( (closed_bracket != last_tag) &&  (closed_bracket != std::string::npos) );

    ClearAllLists();
    Position position;
    position.SetFromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", squares);
    mListOfFenPositionsMainLine.push_back(position.GetPositionAsFen());

    //from last_tag onward
    size_t dot = rGameString.find('.', last_tag);
    while (dot != std::string::npos)
    {
        size_t beginning = rGameString.find_first_not_of(" \n\r\t\v\f", dot+1);
        size_t end = rGameString.find_first_of(" \n\r\t\v\f", beginning+1);

        size_t beginning_black_move = rGameString.find_first_not_of(" \n\r\t\v\f", end+1);
        size_t end_black_move = rGameString.find_first_of(" \n\r\t\v\f", beginning_black_move+1);

        std::string move_san = rGameString.substr(beginning, end -beginning);
        std::string move_san_black = rGameString.substr(beginning_black_move, end_black_move -beginning_black_move);
        //std::cout<<std::endl<<dot<<" white move  "<<move_san<<" ("<<move_san.length()<<")"<< "black move  "<<move_san_black<<" ("<<move_san_black.length()<<")"<< std::endl;

        //if (IsThisTheGameResult(move_san)) break;

        mMoveListMainLineAlgFormat.push_back(move_san);
        Move white_move(move_san, squares, WHITE);
        if ( (white_move.GetOrigin()==nullptr) || (white_move.GetDestination() == nullptr) )
        {
            ClearAllLists();
            return INVALID_PGN;
        }

        mMoveListMainLine.push_back(white_move);
        position.UpdatePositionWithMove(white_move, squares);
        mListOfFenPositionsMainLine.push_back(position.GetPositionAsFen());

        if (IsThisTheGameResult(move_san_black)) break; //case of result coming after white move (would be move_san_black here)

        mMoveListMainLineAlgFormat.push_back(move_san_black);
        Move black_move(move_san_black, squares, BLACK);
        if ( (black_move.GetOrigin()==nullptr) || (black_move.GetDestination() == nullptr) )
        {
            ClearAllLists();
            return INVALID_PGN;
        }

        mMoveListMainLine.push_back(black_move);
        position.UpdatePositionWithMove(black_move, squares);
        mListOfFenPositionsMainLine.push_back(position.GetPositionAsFen());

        last_tag = end_black_move;
        dot = rGameString.find('.', last_tag);
        //case of result coming after black move, but no more dots after this
        if (dot == std::string::npos)
        {
            size_t start_of_result = rGameString.find_first_not_of(" \n\r\t\v\f", last_tag);
            size_t end_of_result = rGameString.find_first_of(" \n\r\t\v\f", start_of_result+1);
            if (IsThisTheGameResult(rGameString.substr(start_of_result, end_of_result - start_of_result))) break;
        }
    }

    return VALID_PGN;
}

std::vector<std::string> slach::Game::GetFenList() const
{
	return mListOfFenPositionsMainLine;
}

slach::SevenTagRoster slach::Game::GetSevenTagRoster() const
{
    return mSTR;
}

slach::OtherTagsRoster slach::Game::GetOtherTagsRoster() const
{
    return mOTR;
}

std::string slach::Game::GetNameOfWhitePlayer() const
{
    std::string empty_string = "";
    for (unsigned i = 0; i < mSTR.mLabels.size(); ++i)
    {
        if (mSTR.mLabels[i] == "White")
        {
            return mSTR.mData[i];
        }
    }
    return empty_string;
}

std::string slach::Game::GetNameOfBlackPlayer() const
{
    std::string empty_string = "";
    for (unsigned i = 0; i < mSTR.mLabels.size(); ++i)
    {
        if (mSTR.mLabels[i] == "Black")
        {
            return mSTR.mData[i];
        }
    }
    return empty_string;
}

std::string slach::Game::GetEloOfWhitePlayer() const
{
    std::string empty_string = "";
    for (unsigned i = 0; i < mSTR.mLabels.size(); ++i)
    {
        if (mOTR.mLabels[i] == "WhiteElo")
        {
            return mOTR.mData[i];
        }
    }
    return empty_string;
}

std::string slach::Game::GetEloOfBlackPlayer() const
{
    std::string empty_string = "";
    for (unsigned i = 0; i < mOTR.mLabels.size(); ++i)
    {
        if (mOTR.mLabels[i] == "BlackElo")
        {
            return mOTR.mData[i];
        }
    }
    return empty_string;
}

