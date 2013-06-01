#ifndef ENGINEINTERFACE_HPP_
#define ENGINEINTERFACE_HPP_

#include "position.h"//within stockfish
#include "Game.hpp"

namespace slach
{
/**
 * A class that serves as a communicator with one or more engines.
 */
class EngineInterface
{
    friend class TestEngineInterface;// for testing

  private:
    /**Cache for a FEN string*/
    std::string mFenString;

    /**pointer to a position object within the stockfish engine*/
    Position* mpStockfishPosition;

  public :
    /**
     * Helper method to convert a Square object within slach
     * to one within the stockfish engine
     *
     * @param pSquare a pointer to the square we wish to convert.
     * @return The corresponding square of the correct type defined by stocksfish (enum)
     */
    ::Square ConvertSquareToStockfish(const Square* pSquare) const;

    EngineInterface();
    ~EngineInterface();

    bool IsMoveValidInPosition(const std::string &rFenPosition, const slach::Move &rMove) const;


};

}//namespace slach
#endif
