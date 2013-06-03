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
bool suite_TestChessboards_init = false;
#include "/home/alberto/code/slach/test/TestChessboardWithBorders.hpp"

static TestChessboards suite_TestChessboards;

static CxxTest::List Tests_TestChessboards = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestChessboards( "/home/alberto/code/slach/test/TestChessboardWithBorders.hpp", 14, "TestChessboards", suite_TestChessboards, Tests_TestChessboards );

static class TestDescription_suite_TestChessboards_testBorderFlags : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessboards_testBorderFlags() : CxxTest::RealTestDescription( Tests_TestChessboards, suiteDescription_TestChessboards, 18, "testBorderFlags" ) {}
 void runTest() { suite_TestChessboards.testBorderFlags(); }
} testDescription_suite_TestChessboards_testBorderFlags;

static class TestDescription_suite_TestChessboards_testBoardWithBorders : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessboards_testBoardWithBorders() : CxxTest::RealTestDescription( Tests_TestChessboards, suiteDescription_TestChessboards, 47, "testBoardWithBorders" ) {}
 void runTest() { suite_TestChessboards.testBoardWithBorders(); }
} testDescription_suite_TestChessboards_testBoardWithBorders;

#include "/home/alberto/code/slach/test/TestChessBoard.hpp"

static TestChessBoard suite_TestChessBoard;

static CxxTest::List Tests_TestChessBoard = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestChessBoard( "/home/alberto/code/slach/test/TestChessBoard.hpp", 14, "TestChessBoard", suite_TestChessBoard, Tests_TestChessBoard );

static class TestDescription_suite_TestChessBoard_testBasicBoard : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessBoard_testBasicBoard() : CxxTest::RealTestDescription( Tests_TestChessBoard, suiteDescription_TestChessBoard, 110, "testBasicBoard" ) {}
 void runTest() { suite_TestChessBoard.testBasicBoard(); }
} testDescription_suite_TestChessBoard_testBasicBoard;

static class TestDescription_suite_TestChessBoard_testInitialPosition : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessBoard_testInitialPosition() : CxxTest::RealTestDescription( Tests_TestChessBoard, suiteDescription_TestChessBoard, 304, "testInitialPosition" ) {}
 void runTest() { suite_TestChessBoard.testInitialPosition(); }
} testDescription_suite_TestChessBoard_testInitialPosition;

static class TestDescription_suite_TestChessBoard_testMakeAMove : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessBoard_testMakeAMove() : CxxTest::RealTestDescription( Tests_TestChessBoard, suiteDescription_TestChessBoard, 314, "testMakeAMove" ) {}
 void runTest() { suite_TestChessBoard.testMakeAMove(); }
} testDescription_suite_TestChessBoard_testMakeAMove;

static class TestDescription_suite_TestChessBoard_testSetFenPosition : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessBoard_testSetFenPosition() : CxxTest::RealTestDescription( Tests_TestChessBoard, suiteDescription_TestChessBoard, 369, "testSetFenPosition" ) {}
 void runTest() { suite_TestChessBoard.testSetFenPosition(); }
} testDescription_suite_TestChessBoard_testSetFenPosition;

static class TestDescription_suite_TestChessBoard_testAnotherFen : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessBoard_testAnotherFen() : CxxTest::RealTestDescription( Tests_TestChessBoard, suiteDescription_TestChessBoard, 498, "testAnotherFen" ) {}
 void runTest() { suite_TestChessBoard.testAnotherFen(); }
} testDescription_suite_TestChessBoard_testAnotherFen;

static class TestDescription_suite_TestChessBoard_testCheckingValidityAndMakingAMove : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessBoard_testCheckingValidityAndMakingAMove() : CxxTest::RealTestDescription( Tests_TestChessBoard, suiteDescription_TestChessBoard, 535, "testCheckingValidityAndMakingAMove" ) {}
 void runTest() { suite_TestChessBoard.testCheckingValidityAndMakingAMove(); }
} testDescription_suite_TestChessBoard_testCheckingValidityAndMakingAMove;

static class TestDescription_suite_TestChessBoard_testThatInvalidFenChangesNothing : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestChessBoard_testThatInvalidFenChangesNothing() : CxxTest::RealTestDescription( Tests_TestChessBoard, suiteDescription_TestChessBoard, 560, "testThatInvalidFenChangesNothing" ) {}
 void runTest() { suite_TestChessBoard.testThatInvalidFenChangesNothing(); }
} testDescription_suite_TestChessBoard_testThatInvalidFenChangesNothing;

#include "/home/alberto/code/slach/test/TestSquare.hpp"

static TestSquare suite_TestSquare;

static CxxTest::List Tests_TestSquare = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestSquare( "/home/alberto/code/slach/test/TestSquare.hpp", 13, "TestSquare", suite_TestSquare, Tests_TestSquare );

static class TestDescription_suite_TestSquare_testGetAndSetMethos : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestSquare_testGetAndSetMethos() : CxxTest::RealTestDescription( Tests_TestSquare, suiteDescription_TestSquare, 17, "testGetAndSetMethos" ) {}
 void runTest() { suite_TestSquare.testGetAndSetMethos(); }
} testDescription_suite_TestSquare_testGetAndSetMethos;

static class TestDescription_suite_TestSquare_testSameSquare : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestSquare_testSameSquare() : CxxTest::RealTestDescription( Tests_TestSquare, suiteDescription_TestSquare, 67, "testSameSquare" ) {}
 void runTest() { suite_TestSquare.testSameSquare(); }
} testDescription_suite_TestSquare_testSameSquare;

#include "/home/alberto/code/slach/test/TestFenHandler.hpp"

static TestFenHandler suite_TestFenHandler;

static CxxTest::List Tests_TestFenHandler = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestFenHandler( "/home/alberto/code/slach/test/TestFenHandler.hpp", 14, "TestFenHandler", suite_TestFenHandler, Tests_TestFenHandler );

static class TestDescription_suite_TestFenHandler_testFenValidity : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestFenHandler_testFenValidity() : CxxTest::RealTestDescription( Tests_TestFenHandler, suiteDescription_TestFenHandler, 18, "testFenValidity" ) {}
 void runTest() { suite_TestFenHandler.testFenValidity(); }
} testDescription_suite_TestFenHandler_testFenValidity;

static class TestDescription_suite_TestFenHandler_TestIndexFromChars : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestFenHandler_TestIndexFromChars() : CxxTest::RealTestDescription( Tests_TestFenHandler, suiteDescription_TestFenHandler, 179, "TestIndexFromChars" ) {}
 void runTest() { suite_TestFenHandler.TestIndexFromChars(); }
} testDescription_suite_TestFenHandler_TestIndexFromChars;

static class TestDescription_suite_TestFenHandler_testAssignFenInitialAftere2e4 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestFenHandler_testAssignFenInitialAftere2e4() : CxxTest::RealTestDescription( Tests_TestFenHandler, suiteDescription_TestFenHandler, 253, "testAssignFenInitialAftere2e4" ) {}
 void runTest() { suite_TestFenHandler.testAssignFenInitialAftere2e4(); }
} testDescription_suite_TestFenHandler_testAssignFenInitialAftere2e4;

static class TestDescription_suite_TestFenHandler_testAssignFen : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestFenHandler_testAssignFen() : CxxTest::RealTestDescription( Tests_TestFenHandler, suiteDescription_TestFenHandler, 350, "testAssignFen" ) {}
 void runTest() { suite_TestFenHandler.testAssignFen(); }
} testDescription_suite_TestFenHandler_testAssignFen;

static class TestDescription_suite_TestFenHandler_testAnotherValidFen : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestFenHandler_testAnotherValidFen() : CxxTest::RealTestDescription( Tests_TestFenHandler, suiteDescription_TestFenHandler, 404, "testAnotherValidFen" ) {}
 void runTest() { suite_TestFenHandler.testAnotherValidFen(); }
} testDescription_suite_TestFenHandler_testAnotherValidFen;

static class TestDescription_suite_TestFenHandler_testMixedCastlingRights : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestFenHandler_testMixedCastlingRights() : CxxTest::RealTestDescription( Tests_TestFenHandler, suiteDescription_TestFenHandler, 465, "testMixedCastlingRights" ) {}
 void runTest() { suite_TestFenHandler.testMixedCastlingRights(); }
} testDescription_suite_TestFenHandler_testMixedCastlingRights;

static class TestDescription_suite_TestFenHandler_testAssignFenStrangeCases : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestFenHandler_testAssignFenStrangeCases() : CxxTest::RealTestDescription( Tests_TestFenHandler, suiteDescription_TestFenHandler, 503, "testAssignFenStrangeCases" ) {}
 void runTest() { suite_TestFenHandler.testAssignFenStrangeCases(); }
} testDescription_suite_TestFenHandler_testAssignFenStrangeCases;

static class TestDescription_suite_TestFenHandler_TestGetFenOrdinaryMove : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestFenHandler_TestGetFenOrdinaryMove() : CxxTest::RealTestDescription( Tests_TestFenHandler, suiteDescription_TestFenHandler, 574, "TestGetFenOrdinaryMove" ) {}
 void runTest() { suite_TestFenHandler.TestGetFenOrdinaryMove(); }
} testDescription_suite_TestFenHandler_TestGetFenOrdinaryMove;

static class TestDescription_suite_TestFenHandler_TestGetFenWithEnpassant : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestFenHandler_TestGetFenWithEnpassant() : CxxTest::RealTestDescription( Tests_TestFenHandler, suiteDescription_TestFenHandler, 630, "TestGetFenWithEnpassant" ) {}
 void runTest() { suite_TestFenHandler.TestGetFenWithEnpassant(); }
} testDescription_suite_TestFenHandler_TestGetFenWithEnpassant;

#include "/home/alberto/code/slach/test/TestGame.hpp"

static TestGame suite_TestGame;

static CxxTest::List Tests_TestGame = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestGame( "/home/alberto/code/slach/test/TestGame.hpp", 13, "TestGame", suite_TestGame, Tests_TestGame );

static class TestDescription_suite_TestGame_testBasicMove : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestGame_testBasicMove() : CxxTest::RealTestDescription( Tests_TestGame, suiteDescription_TestGame, 18, "testBasicMove" ) {}
 void runTest() { suite_TestGame.testBasicMove(); }
} testDescription_suite_TestGame_testBasicMove;

static class TestDescription_suite_TestGame_testPawnMove : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestGame_testPawnMove() : CxxTest::RealTestDescription( Tests_TestGame, suiteDescription_TestGame, 49, "testPawnMove" ) {}
 void runTest() { suite_TestGame.testPawnMove(); }
} testDescription_suite_TestGame_testPawnMove;

static class TestDescription_suite_TestGame_testCapture : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestGame_testCapture() : CxxTest::RealTestDescription( Tests_TestGame, suiteDescription_TestGame, 80, "testCapture" ) {}
 void runTest() { suite_TestGame.testCapture(); }
} testDescription_suite_TestGame_testCapture;

static class TestDescription_suite_TestGame_testPawnCapture : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestGame_testPawnCapture() : CxxTest::RealTestDescription( Tests_TestGame, suiteDescription_TestGame, 112, "testPawnCapture" ) {}
 void runTest() { suite_TestGame.testPawnCapture(); }
} testDescription_suite_TestGame_testPawnCapture;

static class TestDescription_suite_TestGame_testCastleKingSide : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestGame_testCastleKingSide() : CxxTest::RealTestDescription( Tests_TestGame, suiteDescription_TestGame, 143, "testCastleKingSide" ) {}
 void runTest() { suite_TestGame.testCastleKingSide(); }
} testDescription_suite_TestGame_testCastleKingSide;

static class TestDescription_suite_TestGame_testCastleQueenSide : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestGame_testCastleQueenSide() : CxxTest::RealTestDescription( Tests_TestGame, suiteDescription_TestGame, 219, "testCastleQueenSide" ) {}
 void runTest() { suite_TestGame.testCastleQueenSide(); }
} testDescription_suite_TestGame_testCastleQueenSide;

#include "/home/alberto/code/slach/test/TestEngineInterface.hpp"

static TestEngineInterface suite_TestEngineInterface;

static CxxTest::List Tests_TestEngineInterface = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestEngineInterface( "/home/alberto/code/slach/test/TestEngineInterface.hpp", 14, "TestEngineInterface", suite_TestEngineInterface, Tests_TestEngineInterface );

static class TestDescription_suite_TestEngineInterface_TestInterface : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestEngineInterface_TestInterface() : CxxTest::RealTestDescription( Tests_TestEngineInterface, suiteDescription_TestEngineInterface, 18, "TestInterface" ) {}
 void runTest() { suite_TestEngineInterface.TestInterface(); }
} testDescription_suite_TestEngineInterface_TestInterface;

static class TestDescription_suite_TestEngineInterface_TestLegalMoves : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestEngineInterface_TestLegalMoves() : CxxTest::RealTestDescription( Tests_TestEngineInterface, suiteDescription_TestEngineInterface, 56, "TestLegalMoves" ) {}
 void runTest() { suite_TestEngineInterface.TestLegalMoves(); }
} testDescription_suite_TestEngineInterface_TestLegalMoves;

static class TestDescription_suite_TestEngineInterface_TestConversionFromSalchToStockfish : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestEngineInterface_TestConversionFromSalchToStockfish() : CxxTest::RealTestDescription( Tests_TestEngineInterface, suiteDescription_TestEngineInterface, 104, "TestConversionFromSalchToStockfish" ) {}
 void runTest() { suite_TestEngineInterface.TestConversionFromSalchToStockfish(); }
} testDescription_suite_TestEngineInterface_TestConversionFromSalchToStockfish;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
