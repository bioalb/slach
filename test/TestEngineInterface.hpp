#ifndef TESTENGINEINTERFACE_HPP_
#define TESTENGINEINTERFACE_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include "EngineInterface.hpp"

/**
 * Test suite to test the engine interface class
 */
class TestEngineInterface : public CxxTest::TestSuite
{
public:

    void TestInterface()
    {
        slach::EngineInterface interface;
        slach::Square* pe2 = new slach::Square();
        pe2->SetFile("e");
        pe2->SetRank("2");
        pe2->SetIndexFromA1(12u);

        slach::Square* pe4 = new slach::Square();
        pe4->SetFile("e");
        pe4->SetRank("4");
        pe4->SetIndexFromA1(28u);

        slach::Square* pe5 = new slach::Square();
        pe5->SetFile("e");
        pe5->SetRank("5");
        pe5->SetIndexFromA1(36u);

        slach::Move e2e4;
        e2e4.first = pe2;
        e2e4.second = pe4;

        std::string initial_position = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        bool valid = interface.IsMoveValidInPosition(initial_position, e2e4);
        TS_ASSERT_EQUALS(valid,true);

        slach::Move e2e5;
        e2e5.first = pe2;
        e2e5.second = pe5;

        valid = interface.IsMoveValidInPosition(initial_position, e2e5);
        TS_ASSERT_EQUALS(valid,false);

        delete pe2;
        delete pe4;
        delete pe5;
    }
};
#endif

