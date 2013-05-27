#include "EngineInterface.hpp"
#include "platform.h"
#include "bitboard.h"
#include "evaluate.h"
#include "position.h"
#include "search.h"
#include "thread.h"
#include "tt.h"
#include "ucioption.h"


slach::EngineInterface::EngineInterface()
{
    UCI::init(Options);
    Bitboards::init();
    Zobrist::init();
    Bitbases::init_kpk();
    Search::init();
    Eval::init();
    Threads.init();
    TT.set_size(Options["Hash"]);
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
