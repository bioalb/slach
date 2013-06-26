#ifndef _TESTPOSITION_HPP_
#define _TESTPOSITION_HPP_

#include <cxxtest/TestSuite.h>
#include "Square.hpp"
#include "Position.hpp"

/**
 * Test suite to test the Position class
 */

class TestPosition : public CxxTest::TestSuite
{
public:

    void testPositionBasic()
    {
    	slach::Position pos;
		TS_ASSERT_EQUALS(1+1,3)
    }
};
#endif
