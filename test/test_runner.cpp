/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
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
bool suite_TestChessboards_init = false;
#include "/home/alberto/code/slach/test/TestChessboardWithBorders.hpp"

static TestChessboards suite_TestChessboards;

static CxxTest::List Tests_TestChessboards = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestChessboards( "/home/alberto/code/slach/test/TestChessboardWithBorders.hpp", 13, "TestChessboards", suite_TestChessboards, Tests_TestChessboards );

static class TestDescription_suite_TestChessboards_testBorderFlags : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessboards_testBorderFlags() : CxxTest::RealTestDescription( Tests_TestChessboards, suiteDescription_TestChessboards, 17, "testBorderFlags" ) {}
 void runTest() { suite_TestChessboards.testBorderFlags(); }
} testDescription_suite_TestChessboards_testBorderFlags;

static class TestDescription_suite_TestChessboards_testBoardWithBorders : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessboards_testBoardWithBorders() : CxxTest::RealTestDescription( Tests_TestChessboards, suiteDescription_TestChessboards, 46, "testBoardWithBorders" ) {}
 void runTest() { suite_TestChessboards.testBoardWithBorders(); }
} testDescription_suite_TestChessboards_testBoardWithBorders;

#include "/home/alberto/code/slach/test/TestChessBoard.hpp"

static TestChessBoard suite_TestChessBoard;

static CxxTest::List Tests_TestChessBoard = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestChessBoard( "/home/alberto/code/slach/test/TestChessBoard.hpp", 13, "TestChessBoard", suite_TestChessBoard, Tests_TestChessBoard );

static class TestDescription_suite_TestChessBoard_testBasicBoard : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessBoard_testBasicBoard() : CxxTest::RealTestDescription( Tests_TestChessBoard, suiteDescription_TestChessBoard, 109, "testBasicBoard" ) {}
 void runTest() { suite_TestChessBoard.testBasicBoard(); }
} testDescription_suite_TestChessBoard_testBasicBoard;

static class TestDescription_suite_TestChessBoard_testInitialPosition : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessBoard_testInitialPosition() : CxxTest::RealTestDescription( Tests_TestChessBoard, suiteDescription_TestChessBoard, 297, "testInitialPosition" ) {}
 void runTest() { suite_TestChessBoard.testInitialPosition(); }
} testDescription_suite_TestChessBoard_testInitialPosition;

static class TestDescription_suite_TestChessBoard_testMakeAMove : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessBoard_testMakeAMove() : CxxTest::RealTestDescription( Tests_TestChessBoard, suiteDescription_TestChessBoard, 307, "testMakeAMove" ) {}
 void runTest() { suite_TestChessBoard.testMakeAMove(); }
} testDescription_suite_TestChessBoard_testMakeAMove;

static class TestDescription_suite_TestChessBoard_testArrangePiecesFromFEN : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessBoard_testArrangePiecesFromFEN() : CxxTest::RealTestDescription( Tests_TestChessBoard, suiteDescription_TestChessBoard, 362, "testArrangePiecesFromFEN" ) {}
 void runTest() { suite_TestChessBoard.testArrangePiecesFromFEN(); }
} testDescription_suite_TestChessBoard_testArrangePiecesFromFEN;

static class TestDescription_suite_TestChessBoard_testAnotherFen : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessBoard_testAnotherFen() : CxxTest::RealTestDescription( Tests_TestChessBoard, suiteDescription_TestChessBoard, 490, "testAnotherFen" ) {}
 void runTest() { suite_TestChessBoard.testAnotherFen(); }
} testDescription_suite_TestChessBoard_testAnotherFen;

static class TestDescription_suite_TestChessBoard_testInvalidFen : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessBoard_testInvalidFen() : CxxTest::RealTestDescription( Tests_TestChessBoard, suiteDescription_TestChessBoard, 526, "testInvalidFen" ) {}
 void runTest() { suite_TestChessBoard.testInvalidFen(); }
} testDescription_suite_TestChessBoard_testInvalidFen;

static class TestDescription_suite_TestChessBoard_testMoreInvalidFens : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessBoard_testMoreInvalidFens() : CxxTest::RealTestDescription( Tests_TestChessBoard, suiteDescription_TestChessBoard, 652, "testMoreInvalidFens" ) {}
 void runTest() { suite_TestChessBoard.testMoreInvalidFens(); }
} testDescription_suite_TestChessBoard_testMoreInvalidFens;

#include "/home/alberto/code/slach/test/TestSquare.hpp"

static TestSquare suite_TestSquare;

static CxxTest::List Tests_TestSquare = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestSquare( "/home/alberto/code/slach/test/TestSquare.hpp", 12, "TestSquare", suite_TestSquare, Tests_TestSquare );

static class TestDescription_suite_TestSquare_testGetAndSetMethos : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestSquare_testGetAndSetMethos() : CxxTest::RealTestDescription( Tests_TestSquare, suiteDescription_TestSquare, 16, "testGetAndSetMethos" ) {}
 void runTest() { suite_TestSquare.testGetAndSetMethos(); }
} testDescription_suite_TestSquare_testGetAndSetMethos;

static class TestDescription_suite_TestSquare_testSameSquare : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestSquare_testSameSquare() : CxxTest::RealTestDescription( Tests_TestSquare, suiteDescription_TestSquare, 58, "testSameSquare" ) {}
 void runTest() { suite_TestSquare.testSameSquare(); }
} testDescription_suite_TestSquare_testSameSquare;

#include "/home/alberto/code/slach/test/TestGame.hpp"

static TestGame suite_TestGame;

static CxxTest::List Tests_TestGame = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestGame( "/home/alberto/code/slach/test/TestGame.hpp", 12, "TestGame", suite_TestGame, Tests_TestGame );

static class TestDescription_suite_TestGame_testBasicMove : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestGame_testBasicMove() : CxxTest::RealTestDescription( Tests_TestGame, suiteDescription_TestGame, 17, "testBasicMove" ) {}
 void runTest() { suite_TestGame.testBasicMove(); }
} testDescription_suite_TestGame_testBasicMove;

static class TestDescription_suite_TestGame_testPawnMove : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestGame_testPawnMove() : CxxTest::RealTestDescription( Tests_TestGame, suiteDescription_TestGame, 48, "testPawnMove" ) {}
 void runTest() { suite_TestGame.testPawnMove(); }
} testDescription_suite_TestGame_testPawnMove;

static class TestDescription_suite_TestGame_testCapture : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestGame_testCapture() : CxxTest::RealTestDescription( Tests_TestGame, suiteDescription_TestGame, 79, "testCapture" ) {}
 void runTest() { suite_TestGame.testCapture(); }
} testDescription_suite_TestGame_testCapture;

static class TestDescription_suite_TestGame_testPawnCapture : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestGame_testPawnCapture() : CxxTest::RealTestDescription( Tests_TestGame, suiteDescription_TestGame, 111, "testPawnCapture" ) {}
 void runTest() { suite_TestGame.testPawnCapture(); }
} testDescription_suite_TestGame_testPawnCapture;

static class TestDescription_suite_TestGame_testCastleKingSide : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestGame_testCastleKingSide() : CxxTest::RealTestDescription( Tests_TestGame, suiteDescription_TestGame, 142, "testCastleKingSide" ) {}
 void runTest() { suite_TestGame.testCastleKingSide(); }
} testDescription_suite_TestGame_testCastleKingSide;

static class TestDescription_suite_TestGame_testCastleQueenSide : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestGame_testCastleQueenSide() : CxxTest::RealTestDescription( Tests_TestGame, suiteDescription_TestGame, 218, "testCastleQueenSide" ) {}
 void runTest() { suite_TestGame.testCastleQueenSide(); }
} testDescription_suite_TestGame_testCastleQueenSide;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
