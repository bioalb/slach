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

	void TestBasic()
	{
		slach::UCIEngineInterface interface;
		interface.SetFenPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		//interface.IssueCommandtoStockfish("quit");
		//assert(0);
	}
};
#endif
