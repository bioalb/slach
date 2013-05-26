#ifndef ENGINEINTERFACE_HPP_
#define ENGINEINTERFACE_HPP_

#include "position.h"//within stockfish
#include "Game.hpp"

namespace slach
{

class EngineInterface
{
private:

    std::string mFenString;

    Position* mpStockfishPosition;

public:

    EngineInterface();
    ~EngineInterface();

    bool IsMoveValidInPosition(const std::string &rFenPosition, const slach::Move &rMove) const;


};

}//namespace slach
#endif
