#ifndef TESTENGINECOMMANDS_HPP_
#define TESTENGINECOMMANDS_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cassert>
#include "EngineInterface.hpp"
#include "ChessBoard.hpp"


/**
 * Test suite to test the engine interface class
 */
class TestEngineCommands : public CxxTest::TestSuite
{
public:

    void TestSetPosition()
    {
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        slach::EngineInterface interface;
        interface.LaunchEngine();

        interface.IssueCommandtoStockfish("position fen" + test_position);
    }
};
#endif
