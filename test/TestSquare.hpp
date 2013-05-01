#ifndef TESTSQUARE_HPP_
#define TESTSQUARE_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include "Square.hpp"

/**
 * Test suite to test the SQUARE
 */
class TestSquare : public CxxTest::TestSuite
{
public:

    void testSameSquare(void)
    {
        Square sq1;
        Square sq2;

        TS_ASSERT_EQUALS(sq1.IsSameSquare(sq2), true);
        TS_ASSERT_EQUALS(sq2.IsSameSquare(sq1), true);

        sq1.SetFile("A");
        sq2.SetFile("B");

        TS_ASSERT_EQUALS(sq1.IsSameSquare(sq2), false);
        TS_ASSERT_EQUALS(sq2.IsSameSquare(sq1), false);

        sq2.SetFile("A");

        TS_ASSERT_EQUALS(sq1.IsSameSquare(sq2), true);
        TS_ASSERT_EQUALS(sq2.IsSameSquare(sq1), true);

        sq2.SetRank("2");

        TS_ASSERT_EQUALS(sq1.IsSameSquare(sq2), false);
        TS_ASSERT_EQUALS(sq2.IsSameSquare(sq1), false);

        sq1.SetRank("2");

        TS_ASSERT_EQUALS(sq1.IsSameSquare(sq2), true);
        TS_ASSERT_EQUALS(sq2.IsSameSquare(sq1), true);

    }
};
#endif
