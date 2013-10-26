#include <cassert>
#include "Game.hpp"
#include "Position.hpp"
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

void slach::Game::ClearAllLists()
{
    mListOfFenPositions.clear();
    mMoveList.clear();
    mMoveListAlgFormat.clear();
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

    ClearAllLists();
    Position position;
    position.SetFromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", squares);
    mListOfFenPositions.push_back(position.GetPositionAsFen());

    //from last_tag onward
    size_t dot = rGameString.find('.', last_tag);
    while (dot != std::string::npos)
    {

        unsigned beginning = rGameString.find_first_not_of(" \n\r\t\v\f", dot+1);
        unsigned end = rGameString.find_first_of(" \n\r\t\v\f", beginning+1);

        unsigned beginning_black_move = rGameString.find_first_not_of(" \n\r\t\v\f", end+1);
        unsigned end_black_move = rGameString.find_first_of(" \n\r\t\v\f", beginning_black_move+1);

        std::string move_san = rGameString.substr(beginning, end -beginning);
        std::string move_san_black = rGameString.substr(beginning_black_move, end_black_move -beginning_black_move);
        //std::cout<<std::endl<<dot<<" white move  "<<move_san<<" ("<<move_san.length()<<")"<< "black move  "<<move_san_black<<" ("<<move_san_black.length()<<")"<< std::endl;

        if ( (move_san.find("1-0") != std::string::npos) ||
             (move_san.find("0-1") != std::string::npos) ||
             (move_san.find("1/2-1/2") != std::string::npos) ||
             (move_san.find("*") != std::string::npos) )
        {
            break;
        }
        mMoveListAlgFormat.push_back(move_san);
        Move white_move(move_san, squares, WHITE);
        if ( (white_move.GetOrigin()==NULL) || (white_move.GetDestination() == NULL) )
        {
            ClearAllLists();
            return INVALID_PGN;
        }

        mMoveList.push_back(white_move);
        position.UpdatePositionWithMove(white_move, squares);
        mListOfFenPositions.push_back(position.GetPositionAsFen());

        if ( (move_san_black.find("1-0") != std::string::npos) ||
             (move_san_black.find("0-1") != std::string::npos) ||
             (move_san_black.find("1/2-1/2") != std::string::npos) ||
             (move_san_black.find("*") != std::string::npos) )
        {
            break;
        }

        mMoveListAlgFormat.push_back(move_san_black);
        Move black_move(move_san_black, squares, BLACK);
        if ( (black_move.GetOrigin()==NULL) || (black_move.GetDestination() == NULL) )
        {
            ClearAllLists();
            return INVALID_PGN;
        }

        mMoveList.push_back(black_move);
        position.UpdatePositionWithMove(black_move, squares);
        mListOfFenPositions.push_back(position.GetPositionAsFen());

        last_tag = end_black_move;
        dot = rGameString.find('.', last_tag);
    }

    return VALID_PGN;
}

std::vector<std::string> slach::Game::GetFenList() const
{
	return mListOfFenPositions;
}

slach::SevenTagRoster slach::Game::GetSevenTagRoster() const
{
    return mSTR;
}

std::string slach::Game::GetNameOfWhitePlayer() const
{
    for (unsigned i = 0; i < mSTR.mLabels.size(); ++i)
    {
        if (mSTR.mLabels[i] == "White")
        {
            return mSTR.mData[i];
        }
    }
}

std::string slach::Game::GetNameOfBlackPlayer() const
{
    for (unsigned i = 0; i < mSTR.mLabels.size(); ++i)
    {
        if (mSTR.mLabels[i] == "Black")
        {
            return mSTR.mData[i];
        }
    }
}

