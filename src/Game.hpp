#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <string>
#include <vector>
#include "SlachTypes.hpp"
#include "Move.hpp"
#include "Square.hpp"

namespace slach
{

/**
 * The game class
 */
class Game
{
private:

    /**
     * Stores the list of moves
     */
    std::vector<Move*> mMoveList;

    /**
     * Stores the list of in algebraic format (for easy pgn output)
     */
    std::vector<std::string> mMoveListAlgFormat;

    /**
     * Stores the list of positions in this game
     */
    std::vector<std::string> mListOfFenPositions;

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
    std::vector<slach::Move*> GetMoveList() const;

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
     * @param suffix will go after all, can be used, for example for the check sign (+) or the mate (++).
     */
    void AddMove(Move* move, std::string ambiguityPrefix = "", std::string suffix = "");

    void AddPosition(std::string fenPosition);

    /**
     * Returns a fen string form the list of strings.
     *
     * @param moveNumber the move number corresponding to the position. It returns the last position if moveNumber
     *                   is greater than the size of the move list
     * @param colour the colour to move
     */
    std::string FetchFromFenList(unsigned moveNumber, Colour colour);
};

}//namespace slach
#endif
