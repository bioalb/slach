#ifndef TESTENGINEINTERFACE_HPP_
#define TESTENGINEINTERFACE_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include "evaluate.h"
#include "thread.h"
#include "EngineInterface.hpp"
#include "ChessBoard.hpp"


/**
 * Test suite to test the engine interface class
 */
class TestEngineInterface : public CxxTest::TestSuite
{
public:

    void TestStartAndStopAfterthreeseconds()
    {
        slach::ChessBoard* p_board = new slach::ChessBoard();
        p_board->SetupChessBoard();
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        slach::Position* p_position = new slach::Position();
        std::vector<slach::Square* > squares = p_board->GetSquares();
        p_position->SetFromFen(test_position, squares);

        slach::EngineInterface interface;
        std::cout<<std::endl<<"*******"<<"Starting analysis. I will analyse for 3 seconds"<<"*******"<<std::endl;
        interface.StartAnalsyingPosition(p_position, 3.0);
        std::cout<<std::endl<<"Done analysing for 3 seconds, engine output follows"<<std::endl;
        std::cout<<interface.GetLatestEngineOutput()[0]<<std::endl;
        delete p_board;
        delete p_position;
    }

    void TestStartInfiniteAndStop()
    {
        slach::ChessBoard* p_board = new slach::ChessBoard();
        p_board->SetupChessBoard();
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        slach::Position* p_position = new slach::Position();
        std::vector<slach::Square* > squares = p_board->GetSquares();
        p_position->SetFromFen(test_position, squares);

        slach::EngineInterface interface;
        //coverage
        TS_ASSERT_EQUALS(interface.GetLatestBestScoreAndDepth().second, INT_MAX);
        TS_ASSERT_EQUALS(interface.GetLatestBestScoreAndDepth().first, DBL_MAX);

        std::cout<<std::endl<<"*******"<<"Starting analysis. I will start with infinite analysis"<<"*******"<<std::endl;
        interface.StartAnalsyingPosition(p_position);

		std::time_t time_now = 0;
		std::time_t start_time = 0;
		std::time(&start_time);

		while (std::difftime(time_now,start_time) < 5.0)
		{
			std::time(&time_now);
		}
        interface.StopEngine();
        std::cout<<interface.GetLatestEngineOutput()[0]<<std::endl;
        delete p_board;
        delete p_position;
    }

    void TestStopMakeAMoveAndRestart()
    {
        slach::ChessBoard* p_board = new slach::ChessBoard();
        p_board->SetupChessBoard();
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        slach::Position* p_position = new slach::Position();
        std::vector<slach::Square* > squares = p_board->GetSquares();
        p_position->SetFromFen(test_position, squares);

        slach::EngineInterface interface;

        std::cout<<std::endl<<"*******"<<"Starting analysis for 3 seconds"<<"*******"<<std::endl;
        interface.StartAnalsyingPosition(p_position, 3.0);
        std::cout<<std::endl<<"Done analysing for 3 seconds, now making a move"<<std::endl;
        slach::Move test_move("f5d3",p_board->GetSquares() );
        assert(test_move.GetOrigin() != NULL);
        assert(test_move.GetDestination() != NULL);
        p_board->MakeThisMove(test_move);

        std::cout<<std::endl<<"*******"<<"Starting analysis after Bxd3"<<"*******"<<std::endl;
        interface.StartAnalsyingPosition(p_position, 3.0);
        std::cout<<interface.GetLatestEngineOutput()[0]<<std::endl;
        delete p_board;
        delete p_position;
    }

    void TestStartInfiniteMultiplePV()
    {
        slach::ChessBoard* p_board = new slach::ChessBoard();
        p_board->SetupChessBoard();
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        slach::Position* p_position = new slach::Position();
        std::vector<slach::Square* > squares = p_board->GetSquares();
        p_position->SetFromFen(test_position, squares);

        slach::EngineInterface interface;
        //coverage
        TS_ASSERT_EQUALS(interface.GetLatestBestScoreAndDepth().second, INT_MAX);
        TS_ASSERT_EQUALS(interface.GetLatestBestScoreAndDepth().first, DBL_MAX);
        interface.SetNumberOfLinesToBeShown(4);
        std::cout<<std::endl<<"*******"<<"Starting analysis, multiple output"<<"*******"<<std::endl;
        interface.StartAnalsyingPosition(p_position);

        std::time_t time_now = 0;
        std::time_t start_time = 0;
        std::time(&start_time);

        while (std::difftime(time_now,start_time) < 5.0)
        {
            std::time(&time_now);
        }
        interface.StopEngine();
        std::cout<<interface.GetLatestEngineOutput()[0]<<std::endl;
        std::cout<<interface.GetLatestEngineOutput()[1]<<std::endl;
        std::cout<<interface.GetLatestEngineOutput()[2]<<std::endl;
        std::cout<<interface.GetLatestEngineOutput()[3]<<std::endl;
        delete p_board;
        delete p_position;

    }

    void TestMateInOneThreePlysOutput()
    {
        slach::ChessBoard* p_board = new slach::ChessBoard();
        p_board->SetupChessBoard();
        std::string fools_mate_in_one = "rnbqkbnr/ppppp2p/8/5pp1/4P3/3P4/PPP2PPP/RNBQKBNR w KQkq g6 0 3";
        slach::Position* p_position = new slach::Position();
        std::vector<slach::Square* > squares = p_board->GetSquares();
        p_position->SetFromFen(fools_mate_in_one, squares);

        slach::EngineInterface interface;
        interface.SetNumberOfLinesToBeShown(3);
        std::cout<<std::endl<<"*******"<<"Starting analysis of Mate in one"<<"*******"<<std::endl;
        interface.StartAnalsyingPosition(p_position, 3.0);
        std::cout<<std::endl<<"Done analysing for 3 seconds the fools mate, engine output follows"<<std::endl;
        std::cout<<interface.GetLatestEngineOutput()[0]<<std::endl;
        std::cout<<interface.GetLatestEngineOutput()[1]<<std::endl;
        std::cout<<interface.GetLatestEngineOutput()[2]<<std::endl;
        delete p_board;
        delete p_position;
    }

    void TestCheckMate()
    {
        slach::ChessBoard* p_board = new slach::ChessBoard();
        p_board->SetupChessBoard();
        std::string fools_mate = "rnbqkbnr/ppppp2p/8/5ppQ/4P3/3P4/PPP2PPP/RNB1KBNR b KQkq - 1 3";
        slach::Position* p_position = new slach::Position();
        std::vector<slach::Square* > squares = p_board->GetSquares();
        p_position->SetFromFen(fools_mate, squares);

        slach::EngineInterface interface;
        std::cout<<std::endl<<"*******"<<"Starting analysis of fools mate"<<"*******"<<std::endl;
        interface.StartAnalsyingPosition(p_position, 3.0);
        std::cout<<std::endl<<"Done analysing for 3 seconds the fools mate, engine output follows"<<std::endl;
        std::cout<<interface.GetLatestEngineOutput()[0]<<std::endl;
        delete p_board;
        delete p_position;
    }

    void TestParseStockfishMoveList()
    {
        std::string test_string = "depth 5 Score cp -4 line: f5d3 d2d3 c6b4 d3d2 e7e6";

        slach::EngineInterface interface;
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        interface.SetPositionToInternalChessBoard(test_position);

        int depth = 0;
        double score = 0.0;
        std::string move_list = "";
        std::string root_move = "";
        interface.ParseALineofStockfishOutput(test_string, depth, score, move_list,root_move);
        TS_ASSERT_EQUALS(move_list, "Bxd3 Qxd3 Nb4 Qd2 e6 ");
        TS_ASSERT_EQUALS(root_move, "Bxd3");
        TS_ASSERT_EQUALS(depth, 5);
        TS_ASSERT_DELTA(score, 0.04, 1e-3);
    }

    void TestParseStockfishMoveListWithEndline()
    {
        std::string test_string = "depth 5 Score cp -4 line: f5d3 d2d3 c6b4 d3d2 e7e6\n";

        slach::EngineInterface interface;
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        interface.SetPositionToInternalChessBoard(test_position);

        int depth = 0;
        double score = 0.0;
        std::string move_list = "";
        std::string root_move = "";
        interface.ParseALineofStockfishOutput(test_string, depth, score, move_list, root_move);
        TS_ASSERT_EQUALS(move_list, "Bxd3 Qxd3 Nb4 Qd2 e6 ");
        TS_ASSERT_EQUALS(root_move, "Bxd3");
        TS_ASSERT_EQUALS(depth, 5);
        TS_ASSERT_DELTA(score, 0.04, 1e-3);
    }

    void TestParseStockfishMoveListWithSpaces()
    {
        std::string test_string = "        depth 5 Score cp -4 line: f5d3 d2d3 c6b4 d3d2 e7e6  ";

        slach::EngineInterface interface;
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        interface.SetPositionToInternalChessBoard(test_position);

        int depth = 0;
        double score = 0.0;
        std::string move_list = "";
        std::string root_move = "";
        interface.ParseALineofStockfishOutput(test_string, depth, score, move_list, root_move);
        TS_ASSERT_EQUALS(move_list, "Bxd3 Qxd3 Nb4 Qd2 e6 ");
        TS_ASSERT_EQUALS(root_move, "Bxd3");
        TS_ASSERT_EQUALS(depth, 5);
        TS_ASSERT_DELTA(score, 0.04, 1e-3);
    }

    void TestParseStockfishMoveListWithSpaces2()
    {
        std::string test_string = "            depth 5 Score cp -4 line: f5d3 d2d3 c6b4 d3d2 e7e6  \n";

        slach::EngineInterface interface;
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        interface.SetPositionToInternalChessBoard(test_position);

        int depth = 0;
        double score = 0.0;
        std::string move_list = "";
        std::string root_move = "";
        interface.ParseALineofStockfishOutput(test_string, depth, score, move_list,root_move);
        TS_ASSERT_EQUALS(move_list, "Bxd3 Qxd3 Nb4 Qd2 e6 ");
        TS_ASSERT_EQUALS(root_move, "Bxd3");
        TS_ASSERT_EQUALS(depth, 5);
        TS_ASSERT_DELTA(score, 0.04, 1e-3);
    }

    void TestParseEngineOutputSingleLine()
    {
        std::string test_string =   std::string("depth 1 Score cp -24 line: f6e4 c3e4 d5e4") +
                                    "\ndepth 2 Score cp -24 line: f6e4 c3e4 d5e4" +
                                    "\ndepth 3 Score cp -8 line: f5d3 d2d3 e7e6" +
                                    "\ndepth 4 Score cp -12 line: f6e4 c3e4 d5e4 g2g4" +
                                    "\ndepth 5 Score cp -4 line: f5d3 d2d3 c6b4 d3d2 e7e6\n";

        slach::EngineInterface interface;
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        interface.SetPositionToInternalChessBoard(test_position);

        interface.ParseWholeEngineOutput(test_string);

        TS_ASSERT_EQUALS(interface.mLatestDepths.size(), 1u);
        TS_ASSERT_EQUALS(interface.mLatestDepths[0], 5u);

        TS_ASSERT_EQUALS(interface.mLatestRootMoves.size(), 1u);
        TS_ASSERT_EQUALS(interface.mLatestRootMoves[0], "Bxd3");

        TS_ASSERT_EQUALS(interface.mLatestScores.size(), 1u);
        TS_ASSERT_DELTA(interface.mLatestScores[0], 0.04, 1e-3);

        TS_ASSERT_EQUALS(interface.mLatestLines.size(), 1u);
        TS_ASSERT_EQUALS(interface.mLatestLines[0], "Bxd3 Qxd3 Nb4 Qd2 e6 ");
    }

    void TestParseEngineOutputWithBestMoveNote()
    {
        std::string test_string = std::string( " depth 1 Score cp -24 Line: f6e4 c3e4 d5e4 ") +
         "\ndepth 2 Score cp -24 line: f6e4 c3e4 d5e4" +
         "\ndepth 3 Score cp -8 line: f5d3 d2d3 e7e6" +
         "\ndepth 4 Score cp -12 line: f6e4 c3e4 d5e4 g2g4" +
         "\ndepth 5 Score cp -4 line: f5d3 d2d3 c6b4 d3d2 e7e6" +
         "\ndepth 6 Score cp -24 line: f5d3 d2d3 e7e6 e1c1 f8d6 f4d6 c7d6" +
         "\ndepth 7 Score cp -12 line: f5d3 d2d3 e7e6 e1c1 f8d6 f4d6 c7d6 h2h3 h7h6" +
         "\ndepth 8 Score cp -4 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 h5f4 e3f4 f8c5" +
         "\ndepth 9 Score cp -4 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 h5f4 e3f4 f8e7 c1b1 e8g8" +
         "\ndepth 10 Score cp 0 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 h5f4 e3f4 f8e7 c1b1 e8g8 g2g4" +
         "\ndepth 11 Score cp -4 line: f5d3 c2d3 e7e6 g2g4 d7d8 f3e5 c6e5 f4e5 f8d6 e5f6 g7f6 h2h4 c7c6" +
         "\ndepth 12 Score cp -8 line: f5d3 c2d3 e7e6 g2g4 d7d8 e1c1 f8d6 e3e4 d6b4 g4g5 f6h5 c1b1 h5f4 d2f4 e8g8 h2h4 b4d6" +
         "\ndepth 13 Score cp -4 line: f5d3 c2d3 e7e6 g2g4 d7d8 e1c1 f8d6 e3e4 d6b4 g4g5 f6h5 c1b1 e8g8 h2h4 f7f5 e4d5 b4c3 b2c3 d8d5" +
         "\ndepth 14 Score cp -4 line: f5d3 c2d3 e7e6 g2g4 d7d8 e1c1 f8d6 e3e4 d6b4 g4g5 f6h5 c1b1 e8g8 h2h4 f7f5 e4d5 b4c3 b2c3 d8d5" +
         "\ndepth 15 Score cp -4 line: f5d3 c2d3 e7e6 g2g4 d7d8 e1c1 f8d6 e3e4 d6b4 g4g5 f6h5 c1b1 e8g8 h2h4 f7f5 e4d5 b4c3 b2c3 d8d5" +
         "\ndepth 16 Score cp -4 line: f5d3 c2d3 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 d5d4 c3e2 f7f6 g2g4 f6g5 g4h5 d4e3 f2e3 f8e7 e2d4 e8g8 a1c1" +
         "\ndepth 17 Score cp -4 line: f5d3 c2d3 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 d5d4 c3e2 f7f6 g2g4 f6g5 g4h5 d4e3 f2e3 f8e7 e2d4 e8g8 a1c1" +
         "bestmove f5d3 ponder c2d3";


        slach::EngineInterface interface;
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        interface.SetPositionToInternalChessBoard(test_position);

        interface.ParseWholeEngineOutput(test_string);

        TS_ASSERT_EQUALS(interface.mLatestDepths.size(), 1u);
        TS_ASSERT_EQUALS(interface.mLatestDepths[0], 17u);

        TS_ASSERT_EQUALS(interface.mLatestRootMoves.size(), 1u);
        TS_ASSERT_EQUALS(interface.mLatestRootMoves[0], "Bxd3");

        TS_ASSERT_EQUALS(interface.mLatestScores.size(), 1u);
        TS_ASSERT_DELTA(interface.mLatestScores[0], 0.04, 1e-3);

        TS_ASSERT_EQUALS(interface.mLatestLines.size(), 1u);
        TS_ASSERT_EQUALS(interface.mLatestLines[0], "Bxd3 cxd3 e6 Ne5 Nxe5 dxe5 Nh5 Bg5 d4 Ne2 f6 g4 fxg5 gxh5 dxe3 fxe3 Be7 Nd4 O-O Rc1 ");
    }
    void TestParseEngineOutputMultipleLines()
    {

        std::string test_string = std::string("depth 1 Score cp -24 line: f6e4 c3e4 d5e4")
        + "\ndepth 1 Score cp -24 line: h7h6 d3f5 d7f5"
        + "\ndepth 1 Score cp -36 line: e7e6 d3f5 e6f5"
        + "\ndepth 1 Score cp -48 line: f5d3 d2d3"
        + "\ndepth 2 Score cp -24 line: f6e4 c3e4 d5e4"
        + "\ndepth 2 Score cp -48 line: f5d3 d2d3"
        + "\ndepth 2 Score cp -56 line: e7e6 e1c1 f5d3 d2d3"
        + "\ndepth 2 Score cp -64 line: f6g4 h2h3"
        + "\ndepth 3 Score cp -8 line: f5d3 d2d3 e7e6"
        + "\ndepth 3 Score cp -24 line: f6e4 c3e4 d5e4"
        + "\ndepth 3 Score cp -48 line: c6b4 d3f5 d7f5"
        + "\ndepth 3 Score cp -56 line: e7e6 e1c1 f5d3 d2d3"
        + "\ndepth 4 Score cp -12 line: f6e4 c3e4 d5e4 g2g4"
        + "\ndepth 4 Score cp -40 line: f5d3 d2d3 c6b4 d3d2"
        + "\ndepth 4 Score cp -40 line: c6b4 d3f5 d7f5 e1c1 e7e6"
        + "\ndepth 4 Score cp -44 line: e7e6 e1c1 f5d3 d2d3 f8d6"
        + "\ndepth 5 Score cp -4 line: f5d3 d2d3 c6b4 d3d2 e7e6"
        + "\ndepth 5 Score cp -44 line: e7e6 e1c1 f5d3 d2d3 f8d6 c1b1 d6f4 e3f4"
        + "\ndepth 5 Score cp -68 line: f5g6 e1c1 g6d3 c2d3 e7e6 c1b1"
        + "\ndepth 5 Score cp -68 line: f5e4 e1c1 e4d3 c2d3 e7e6 c1b1"
        + "\ndepth 6 Score cp -24 line: f5d3 d2d3 e7e6 e1c1 f8d6 f4d6 c7d6"
        + "\ndepth 6 Score cp -32 line: e7e6 d3f5 e6f5 f3e5 c6e5 d4e5"
        + "\ndepth 6 Score cp -52 line: f5g6 e1c1 g6d3 c2d3 e7e6 c1b1 f8d6"
        + "\ndepth 6 Score cp -64 line: f5e4 d3e4 f6e4 c3e4 d5e4 f3e5 c6e5 f4e5"
        + "\ndepth 7 Score cp -28 line: f5d3 d2d3 e7e6 e1c1 f8d6 f3e5 d6e5 f4e5 c6e5 d4e5"
        + "\ndepth 7 Score cp -60 line: f6e4 d3e4 f5e4 e1c1 e4g6 f3e5 c6e5 f4e5"
        + "\ndepth 7 Score cp -64 line: e7e6 d3f5 e6f5 f3e5 c6e5 d4e5 f6e4 d2d5 e4c3 d5d7 e8d7 b2c3"
        + "\ndepth 7 Score cp -64 line: f5g6 e1c1 e7e6 c1b1 f8e7 f3e5 c6e5 f4e5 g6d3 d2d3"
        + "\ndepth 8 Score cp -16 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 f8c5 f4g5"
        + "\ndepth 8 Score cp -28 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7d6"
        + "\ndepth 8 Score cp -48 line: e7e6 d3f5 e6f5 f3e5 d7e6 e5c6 e6c6 e1c1 f8e7 c1b1 e8g8"
        + "\ndepth 8 Score cp -56 line: f6e4 d3e4 f5e4 c3e4 d5e4 f3e5 c6e5 f4e5 f7f6"
        + "\ndepth 9 Score cp -4 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 f8e7 c1b1 h5f4 e3f4 e8g8"
        + "\ndepth 9 Score cp -28 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7d6"
        + "\ndepth 9 Score cp -48 line: e7e6 d3f5 e6f5 f3e5 d7e6 e5c6 e6c6 e1c1 f8e7 c1b1 e8g8"
        + "\ndepth 9 Score cp -48 line: h7h6 h2h3 f6e4 d3e4 d5e4 f3h4 e7e5 f4e5 c6e5 d4e5"
        + "\ndepth 10 Score cp -24 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7b4 f3g5 f8g8 d2d3 b4d6"
        + "\ndepth 9 Score cp -4 line: f5d3 c2d3 e7e6 g2g4 h7h6 f3e5"
        + "\ndepth 9 Score cp -48 line: e7e6 d3f5 e6f5 f3e5 d7e6 e5c6 e6c6 e1c1 f8e7 c1b1 e8g8"
        + "\ndepth 9 Score cp -48 line: h7h6 h2h3 f6e4 d3e4 d5e4 f3h4 e7e5 f4e5 c6e5 d4e5"
        + "\ndepth 10 Score cp -24 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7b4 f3g5 f8g8 d2d3 b4d6"
        + "\ndepth 10 Score cp -12 line: f5d3 c2d3 e7e6 g2g4 h7h6 f3e5"
        + "\ndepth 9 Score cp -48 line: e7e6 d3f5 e6f5 f3e5 d7e6 e5c6 e6c6 e1c1 f8e7 c1b1 e8g8"
        + "\ndepth 9 Score cp -48 line: h7h6 h2h3 f6e4 d3e4 d5e4 f3h4 e7e5 f4e5 c6e5 d4e5"
        + "\ndepth 10 Score cp -24 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7b4 f3g5 f8g8 d2d3 b4d6"
        + "\ndepth 10 Score cp -20 line: f5d3 c2d3 e7e6 g2g4 h7h6 f3e5"
        + "\ndepth 9 Score cp -48 line: e7e6 d3f5 e6f5 f3e5 d7e6 e5c6 e6c6 e1c1 f8e7 c1b1 e8g8"
        + "\ndepth 9 Score cp -48 line: h7h6 h2h3 f6e4 d3e4 d5e4 f3h4 e7e5 f4e5 c6e5 d4e5"
        + "\ndepth 10 Score cp -24 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7b4 f3g5 f8g8 d2d3 b4d6"
        + "\ndepth 10 Score cp -32 line: f5d3 c2d3 e7e6 g2g4 h7h6 f3e5"
        + "\ndepth 9 Score cp -48 line: e7e6 d3f5 e6f5 f3e5 d7e6 e5c6 e6c6 e1c1 f8e7 c1b1 e8g8"
        + "\ndepth 9 Score cp -48 line: h7h6 h2h3 f6e4 d3e4 d5e4 f3h4 e7e5 f4e5 c6e5 d4e5"
        + "\ndepth 10 Score cp -4 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 f8e7 c1b1 h5f4 e3f4 e8g8 g2g4 e7c5 c3e4 c5b6"
        + "\ndepth 10 Score cp -24 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7b4 f3g5 f8g8 d2d3 b4d6"
        + "\ndepth 9 Score cp -48 line: e7e6 d3f5 e6f5 f3e5 d7e6 e5c6 e6c6 e1c1 f8e7 c1b1 e8g8"
        + "\ndepth 9 Score cp -48 line: h7h6 h2h3 f6e4 d3e4 d5e4 f3h4 e7e5 f4e5 c6e5 d4e5"
        + "\ndepth 10 Score cp -4 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 f8e7 c1b1 h5f4 e3f4 e8g8 g2g4 e7c5 c3e4 c5b6"
        + "\ndepth 10 Score cp -24 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7b4 f3g5 f8g8 d2d3 b4d6"
        + "\ndepth 10 Score cp -40 line: e7e6 d3f5 e6f5 f3e5 d7e6 e5c6 e6c6 e1c1 f8e7 c1b1 e8g8"
        + "\ndepth 9 Score cp -48 line: h7h6 h2h3 f6e4 d3e4 d5e4 f3h4 e7e5 f4e5 c6e5 d4e5"
        + "\ndepth 10 Score cp -4 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 f8e7 c1b1 h5f4 e3f4 e8g8 g2g4 e7c5 c3e4 c5b6"
        + "\ndepth 10 Score cp -24 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7b4 f3g5 f8g8 d2d3 b4d6"
        + "\ndepth 10 Score cp -32 line: e7e6 d3f5 e6f5 f3e5 d7e6 e5c6 e6c6 e1c1 f8e7 c1b1 e8g8"
        + "\ndepth 9 Score cp -48 line: h7h6 h2h3 f6e4 d3e4 d5e4 f3h4 e7e5 f4e5 c6e5 d4e5"
        + "\ndepth 10 Score cp -4 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 f8e7 c1b1 h5f4 e3f4 e8g8 g2g4 e7c5 c3e4 c5b6"
        + "\ndepth 10 Score cp -24 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7b4 f3g5 f8g8 d2d3 b4d6"
        + "\ndepth 10 Score cp -36 line: e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8e7 f2f3 e8g8 c1b1 f8e8 e5c6 e6c6 h2h4"
        + "\ndepth 9 Score cp -48 line: h7h6 h2h3 f6e4 d3e4 d5e4 f3h4 e7e5 f4e5 c6e5 d4e5"
        + "\ndepth 10 Score cp -4 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 f8e7 c1b1 h5f4 e3f4 e8g8 g2g4 e7c5 c3e4 c5b6"
        + "\ndepth 10 Score cp -24 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7b4 f3g5 f8g8 d2d3 b4d6"
        + "\ndepth 10 Score cp -36 line: e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8e7 f2f3 e8g8 c1b1 f8e8 e5c6 e6c6 h2h4"
        + "\ndepth 10 Score cp -40 line: h7h6 e1c1 f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 c1b1 h5f4 e3f4 f8c5"
        + "\ndepth 10 Score cp -4 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 f8e7 c1b1 h5f4 e3f4 e8g8 g2g4 e7c5 c3e4 c5b6"
        + "\ndepth 10 Score cp -24 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7b4 f3g5 f8g8 d2d3 b4d6"
        + "\ndepth 10 Score cp -36 line: e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8e7 f2f3 e8g8 c1b1 f8e8 e5c6 e6c6 h2h4"
        + "\ndepth 10 Score cp -56 line: h7h6 f3e5 c6e5 d4e5 f6e4 d3e4 f5e4 c3e4 d5e4 e1c1"
        + "\ndepth 10 Score cp -4 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 f8e7 c1b1 h5f4 e3f4 e8g8 g2g4 e7c5 c3e4 c5b6"
        + "\ndepth 10 Score cp -24 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7b4 f3g5 f8g8 d2d3 b4d6"
        + "\ndepth 10 Score cp -36 line: e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8e7 f2f3 e8g8 c1b1 f8e8 e5c6 e6c6 h2h4"
        + "\ndepth 10 Score cp -68 line: h7h6 f3e5 c6e5 d4e5 f6e4 d3e4 f5e4 c3e4 d5e4 d2d7 e8d7 e1c1"
        + "\ndepth 10 Score cp -4 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 f8e7 c1b1 h5f4 e3f4 e8g8 g2g4 e7c5 c3e4 c5b6"
        + "\ndepth 10 Score cp -24 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7b4 f3g5 f8g8 d2d3 b4d6"
        + "\ndepth 10 Score cp -36 line: e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8e7 f2f3 e8g8 c1b1 f8e8 e5c6 e6c6 h2h4"
        + "\ndepth 10 Score cp -48 line: h7h6 f3e5 c6e5 d4e5 f6e4 d3e4 d5e4 e1c1 d7d2 d1d2 g7g5 f4g3 f8g7 g1d1"
        + "\ndepth 11 Score cp -4 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 f8e7 c1b1 h5f4 e3f4 e8g8 g2g4 e7c5 c3e4 c5b6"
        + "\ndepth 10 Score cp -24 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7b4 f3g5 f8g8 d2d3 b4d6"
        + "\ndepth 10 Score cp -36 line: e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8e7 f2f3 e8g8 c1b1 f8e8 e5c6 e6c6 h2h4"
        + "\ndepth 10 Score cp -48 line: h7h6 f3e5 c6e5 d4e5 f6e4 d3e4 d5e4 e1c1 d7d2 d1d2 g7g5 f4g3 f8g7 g1d1"
        + "\ndepth 11 Score cp -4 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 f8e7 c1b1 h5f4 e3f4 e8g8 g2g4 e7c5 c3e4 c5b6"
        + "\ndepth 11 Score cp -24 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7b4 f3g5 f8g8 d2d3 b4d6"
        + "\ndepth 10 Score cp -36 line: e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8e7 f2f3 e8g8 c1b1 f8e8 e5c6 e6c6 h2h4"
        + "\ndepth 10 Score cp -48 line: h7h6 f3e5 c6e5 d4e5 f6e4 d3e4 d5e4 e1c1 d7d2 d1d2 g7g5 f4g3 f8g7 g1d1"
        + "\ndepth 11 Score cp -4 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 f8e7 c1b1 h5f4 e3f4 e8g8 g2g4 e7c5 c3e4 c5b6"
        + "\ndepth 11 Score cp -24 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7b4 f3g5 f8g8 d2d3 b4d6"
        + "\ndepth 11 Score cp -36 line: e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8e7 f2f3 e8g8 c1b1 f8e8 e5c6 e6c6 h2h4"
        + "\ndepth 10 Score cp -48 line: h7h6 f3e5 c6e5 d4e5 f6e4 d3e4 d5e4 e1c1 d7d2 d1d2 g7g5 f4g3 f8g7 g1d1"
        + "\ndepth 11 Score cp -4 line: f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 f8e7 c1b1 h5f4 e3f4 e8g8 g2g4 e7c5 c3e4 c5b6"
        + "\ndepth 11 Score cp -24 line: f5g6 e1c1 e7e6 c1b1 f8e7 d3g6 h7g6 h2h3 e8f8 g1e1 e7b4 f3g5 f8g8 d2d3 b4d6"
        + "\ndepth 11 Score cp -36 line: e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8e7 f2f3 e8g8 c1b1 f8e8 e5c6 e6c6 h2h4"
        + "\ndepth 11 Score cp -48 line: h7h6 f3e5 c6e5 d4e5 f6e4 d3e4 d5e4 e1c1 d7d2 d1d2 g7g5 f4g3 f8g7 g1d1";

        slach::EngineInterface interface;
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        interface.SetPositionToInternalChessBoard(test_position);

        interface.SetNumberOfLinesToBeShown(4u);//asking stockfish to display 4 lines
        interface.ParseWholeEngineOutput(test_string);
        TS_ASSERT_EQUALS(interface.mLatestDepths.size(), 4u);
        TS_ASSERT_EQUALS(interface.mLatestDepths[3], 11u);
        TS_ASSERT_EQUALS(interface.mLatestDepths[2], 11u);
        TS_ASSERT_EQUALS(interface.mLatestDepths[1], 11u);
        TS_ASSERT_EQUALS(interface.mLatestDepths[0], 11u);

        TS_ASSERT_EQUALS(interface.mLatestRootMoves.size(), 4u);
        TS_ASSERT_EQUALS(interface.mLatestRootMoves[3], "Bxd3");
        TS_ASSERT_EQUALS(interface.mLatestRootMoves[2], "Bg6");
        TS_ASSERT_EQUALS(interface.mLatestRootMoves[1], "e6");
        TS_ASSERT_EQUALS(interface.mLatestRootMoves[0], "h6");

        TS_ASSERT_EQUALS(interface.mLatestScores.size(), 4u);
        TS_ASSERT_DELTA(interface.mLatestScores[3], 0.04, 1e-3);
        TS_ASSERT_DELTA(interface.mLatestScores[2], 0.24,1e-3);
        TS_ASSERT_DELTA(interface.mLatestScores[1], 0.36, 1e-3);
        TS_ASSERT_DELTA(interface.mLatestScores[0], 0.48, 1e-3);

        TS_ASSERT_EQUALS(interface.mLatestLines.size(), 4u);
        TS_ASSERT_EQUALS(interface.mLatestLines[3], "Bxd3 Qxd3 e6 Ne5 Nxe5 dxe5 Nh5 O-O-O Be7 Kb1 Nxf4 exf4 O-O g4 Bc5 Ne4 Bb6 ");
        TS_ASSERT_EQUALS(interface.mLatestLines[2], "Bg6 O-O-O e6 Kb1 Be7 Bxg6 hxg6 h3 Kf8 Rge1 Bb4 Ng5 Kg8 Qd3 Bd6 ");
        TS_ASSERT_EQUALS(interface.mLatestLines[1], "e6 Bxf5 exf5 Ne5 Qe6 O-O-O Be7 f3 O-O Kb1 Rfe8 Nxc6 Qxc6 h4 ");
        TS_ASSERT_EQUALS(interface.mLatestLines[0], "h6 Ne5 Nxe5 dxe5 Ne4 Bxe4 dxe4 O-O-O Qxd2+ Rxd2 g5 Bg3 Bg7 Rgd1 ");
    }


};
#endif

