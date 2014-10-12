#ifndef TESTUCIENGINEINTERFACE_HPP_
#define TESTUCIENGINEINTERFACE_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cassert>
#include "UCIEngineInterface.hpp"
#include "ChessBoard.hpp"

/**
 * Test suite to test some methods of the engine interface class
 */
class TestUCIEngineInterface : public CxxTest::TestSuite
{
public:

	void TestInfiniteAndStopImmediately()
	{
		slach::UCIEngineInterface interface;
		interface.IssueCommandtoStockfish("go infinite");
	}
};
#endif
