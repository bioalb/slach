#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <string>
#include <vector>
#include <iostream>
#include "SlachTypes.hpp"
#include "Move.hpp"
#include "Square.hpp"

namespace slach
{



struct SevenTagRoster
{
    GameResult mResult;

    std::vector<std::string> mLabels;
    std::vector<std::string> mData;

    SevenTagRoster()
       : mLabels{"Event","Site","Date","Round","White", "Black", "Result"},
         mData{"","","","","", "", ""}
    {}
};

enum PgnValidity
{
    VALID_PGN,
    INVALID_PGN
};

/**
 * The game class
 */
class Game
{
private:

    /**
     * Stores the list of moves
     */
    std::vector<Move> mMoveListMainLine;

    /**
     * Stores the list of in algebraic format (for easy pgn output)
     */
    std::vector<std::string> mMoveListMainLineAlgFormat;

    /**
     * Stores the list of positions in this game
     */
    std::vector<std::string> mListOfFenPositionsMainLine;

    /**
     * Structure to store the information of the seven tag roster
     */
    SevenTagRoster mSTR;

    std::vector<Square* > mSquares;

    /**stores the reuslt of the game. Initialize to **/
    std::string mGameResult;

    /**
     * Helper method to clear all move and position lists.
     */
    void ClearAllLists();

    /**
     * Helper method that returns true if the string passed in cprresponds to one of
     * the possible game results (1-0,0-1,1/2-1/2,*)
     * In such case, it also changes the variable mGameResult accordingly.
     *
     * @param toBeChecked the string to be checked
     * @return true if toBeChecked is one of the possible results.
     */
    bool IsThisTheGameResult(const std::string& toBeChecked);

public:
    /**
     * Constructor
     */
    Game();

    /**
     * Destructor
     */
    ~Game();

    /**
     * Access method for the variable containing the move list
     */
    std::vector<slach::Move> GetMoveList() const;

    /**
     * Access method for the variable containing the move list in algebraic format
     * (mMoveListMainLineAlgFormat)
     */
    std::vector<std::string> GetMoveListAlgebraicFormat() const;

    /**
     * Adds a move to the move list (mMoveListMainLine)
     * and also to the move list in algebraic format
     * (e.g., Ne2 for knight to e2).
     *
     * It does nothing if the move originates from an empty square.
     *
     * @param move: the move to be added to the list
     */
    void AddMove(const Move& rMove);

    void AddPosition(std::string fenPosition);

    /**
     * Returns a fen string form the list of strings. It does not throw any exceptions
     *
     * IF the fen list is empty, it returns an empty string, whatever you pass in.
     * If the fen list has one element only, it returns that one, no matter what you pass in.
     * If you pass in a move number that hasn't been played yet, it returns the last fen of the colour to move that is in the list.
     *
     * In all other cases, it returns the fen string correspnding to the move number you pass in and
     * the colour to move.
     *
     * @param moveNumber the move number corresponding to the position. It returns the last position if moveNumber
     *                   is greater than the size of the move list
     * @param toMove the colour to move
     */
    std::string FetchFromFenList(int moveNumber, Colour toMove);

    PgnValidity LoadFromPgnString(const std::string& rGameString, std::vector<Square* > squares);

    /**
     * Access method to the variable mSTR
     */
    slach::SevenTagRoster GetSevenTagRoster() const;

    /**
     * Access the list of fens
     */
    std::vector<std::string> GetFenList() const;

    /**
     * Queries the seven tag roster to find the name of the white player
     *
     * @return the name of the white player
     */
    std::string GetNameOfWhitePlayer() const;

    /**
     * Queries the seven tag roster to find the name of the black player
     *
     * @return the name of the black player
     */
    std::string GetNameOfBlackPlayer() const;

    /**
     * Accesses the variable mGameResult thats tores the result of the game
     *  - * if in progress
     *  - 1-0 if white wins
     *  - 0-1 if black wins
     *  - 1/2-1/2 if it is a draw
     *
     */
    std::string GetGameResult() const;
};

}//namespace slach
#endif
