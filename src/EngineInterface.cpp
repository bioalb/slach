#include "EngineInterface.hpp"

slach::EngineInterface::EngineInterface()
{
    mpStockfishPosition = new Position();
}

slach::EngineInterface::~EngineInterface()
{
    delete mpStockfishPosition;
}

bool slach::EngineInterface::IsMoveValidInPosition(const std::string &rFenPosition, const slach::Move &rMove) const
{
    mpStockfishPosition->set(rFenPosition, false, NULL);
    return true;
}
