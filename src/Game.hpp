#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <string>
#include <vector>
#include "SlachTypes.hpp"
#include "Square.hpp"


class TestGame;//forward declaration, for testing and accessing protected methods

namespace slach
{

/**
 * Typedef for a move as a pair of square objects
 * the first is the origin square, the second is the destination square
 */
typedef std::pair<Square*,Square*> Move;

/**
 * The game class
 */
class Game
{
    friend class ::TestGame; //for testing
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
     * Stores the fact that a move is a special move, initialised to ORDINARY_MOVE in conmstructor
     */
    SpecialMoveType mSpecialMove;

protected:

    /**
     * Helper method that figures out the type of special move we are dealing with.
     *  It will assign the proper value to mSpecialMove
     *
     * @param rMove the move we wish to analyze
     */
    void DetermineSpecialMove(const Move& rMove);

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
     * @param suffix will go after all, can be used, for example for the check sign (+) or the mate (++).
     */
    void AddMove(const Move& move, std::string ambiguityPrefix = "", std::string suffix = "");

    slach::SpecialMoveType GetSpecialMoveType() const;

};

}//namespace slach
#endif
