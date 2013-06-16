#ifndef TESTMOVE_HPP_
#define TESTMOVE_HPP_

#include <cxxtest/TestSuite.h>
#include "Move.hpp"
#include "Square.hpp"
#include "SlachTypes.hpp"

/**
 * Test suite to test the move class
 */

class TestMove : public CxxTest::TestSuite
{
  public :

    void TestBAsicMove()
    {
        TS_ASSERT_EQUALS(1+1, 3);
    }
};
#endif //TESTMOVE_HPP_
