#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <string>
#include <vector>
#include "PieceType.hpp"
#include "Square.hpp"

/**
 * The game class
 */

/**
 * Typedef for a move as a pair of square objects
 * the first is the origin square, the second is the destination square
 */
typedef std::pair<Square*,Square*> Move;

class Game
{
private:

    /**
     * Stores the list of moves
     */
    std::vector<Move> mMoveList;

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
    std::vector<Move> GetMoveList() const;

};
#endif
