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
    std::vector<Move> mMoveList;

    /**
     * Stores the list of in algebraic format (for easy pgn output)
     */
    std::vector<std::string> mMoveListAlgFormat;

    /**
     * Stores the list of positions in this game
     */
    std::vector<std::string> mListOfFenPositions;

    /**
     * Structure to store the information of the seven tag roster
     */
    SevenTagRoster mSTR;

    std::vector<Square* > mSquares;


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
     * (mMoveListAlgFormat)
     */
    std::vector<std::string> GetMoveListAlgebraicFormat() const;

    /**
     * Adds a move to the move list (mMoveList)
     * and also to the move list in algebraic format
     * (e.g., Ne2 for knight to e2).
     *
     * It does nothing if the move originates from an empty square.
     *
     * @param move: the move to be added to the list
     * @param ambiguityPrefix: to go in algebraic notation between the piece code and the destination
     *                         coordinate (e.g., Rad1, the a rook to d1. Can also be used for the X capture sign)
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
};

}//namespace slach
#endif
