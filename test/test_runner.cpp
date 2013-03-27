/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    status = CxxTest::Main<CxxTest::ErrorPrinter>( tmp, argc, argv );
    return status;
}
bool suite_TestChessboard_init = false;
#include "TestChessboard.hpp"

static TestChessboard suite_TestChessboard;

static CxxTest::List Tests_TestChessboard = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestChessboard( "TestChessboard.hpp", 10, "TestChessboard", suite_TestChessboard, Tests_TestChessboard );

static class TestDescription_suite_TestChessboard_testBorderFlags : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessboard_testBorderFlags() : CxxTest::RealTestDescription( Tests_TestChessboard, suiteDescription_TestChessboard, 14, "testBorderFlags" ) {}
 void runTest() { suite_TestChessboard.testBorderFlags(); }
} testDescription_suite_TestChessboard_testBorderFlags;

static class TestDescription_suite_TestChessboard_testBoard : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessboard_testBoard() : CxxTest::RealTestDescription( Tests_TestChessboard, suiteDescription_TestChessboard, 41, "testBoard" ) {}
 void runTest() { suite_TestChessboard.testBoard(); }
} testDescription_suite_TestChessboard_testBoard;

static class TestDescription_suite_TestChessboard_testInitialPosition : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessboard_testInitialPosition() : CxxTest::RealTestDescription( Tests_TestChessboard, suiteDescription_TestChessboard, 353, "testInitialPosition" ) {}
 void runTest() { suite_TestChessboard.testInitialPosition(); }
} testDescription_suite_TestChessboard_testInitialPosition;

#include "TestPosition.hpp"

static TestPosition suite_TestPosition;

static CxxTest::List Tests_TestPosition = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestPosition( "TestPosition.hpp", 10, "TestPosition", suite_TestPosition, Tests_TestPosition );

static class TestDescription_suite_TestPosition_testInitialPosition : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestPosition_testInitialPosition() : CxxTest::RealTestDescription( Tests_TestPosition, suiteDescription_TestPosition, 14, "testInitialPosition" ) {}
 void runTest() { suite_TestPosition.testInitialPosition(); }
} testDescription_suite_TestPosition_testInitialPosition;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
