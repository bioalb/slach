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
        EngineInterface interface;
        TS_ASSERT_EQUALS(1+1,3);
    }
};
#endif

