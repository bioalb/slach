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

        p_position->SetFromFen(p_board->GetCurrentFenPosition(), squares);
        std::cout<<std::endl<<"*******"<<"Starting analysis after Bxd3"<<"*******"<<std::endl;
        interface.StartAnalsyingPosition(p_position, 3.0);
        std::cout<<std::endl<<"Done analysing for 3 seconds, after Bxd3 engine output follows"<<std::endl;
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

    void xTestCheckMate()
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
        std::string test_string = "info depth 1 seldepth 1 score cp 6 nodes 251 nps 62750 time 4 multipv 1 pv f6e4 c3e4 d5e4";

        slach::EngineInterface interface;
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        interface.SetPositionToInternalChessBoard(test_position);

        int depth = 0;
        double score = 0.0;
        std::string move_list = "";
        std::string root_move = "";
        interface.ParseALineofStockfishOutput(test_string, depth, score, move_list,root_move);
        TS_ASSERT_EQUALS(move_list, "Ne4 Nxe4 dxe4 ");
        TS_ASSERT_EQUALS(root_move, "Ne4");
        TS_ASSERT_EQUALS(depth, 1);
        TS_ASSERT_DELTA(score, -0.06, 1e-3);
    }

    void TestParseStockfishMoveListWithEndline()
    {
        std::string test_string = "info depth 1 seldepth 1 score cp 6 nodes 251 nps 62750 time 4 multipv 1 pv f6e4 c3e4 d5e4\n";

        slach::EngineInterface interface;
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        interface.SetPositionToInternalChessBoard(test_position);

        int depth = 0;
        double score = 0.0;
        std::string move_list = "";
        std::string root_move = "";
        interface.ParseALineofStockfishOutput(test_string, depth, score, move_list,root_move);
        TS_ASSERT_EQUALS(move_list, "Ne4 Nxe4 dxe4 ");
        TS_ASSERT_EQUALS(root_move, "Ne4");
        TS_ASSERT_EQUALS(depth, 1);
        TS_ASSERT_DELTA(score, -0.06, 1e-3);
    }

    void TestParseStockfishMoveListWithSpaces()
    {
        std::string test_string = "       info depth 1 seldepth 1 score cp 6 nodes 251 nps 62750 time 4 multipv 1 pv f6e4 c3e4 d5e4        ";

        slach::EngineInterface interface;
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        interface.SetPositionToInternalChessBoard(test_position);

        int depth = 0;
        double score = 0.0;
        std::string move_list = "";
        std::string root_move = "";
        interface.ParseALineofStockfishOutput(test_string, depth, score, move_list,root_move);
        TS_ASSERT_EQUALS(move_list, "Ne4 Nxe4 dxe4 ");
        TS_ASSERT_EQUALS(root_move, "Ne4");
        TS_ASSERT_EQUALS(depth, 1);
        TS_ASSERT_DELTA(score, -0.06, 1e-3);
    }

    void TestParseStockfishMoveListWithSpaces2()
    {
        std::string test_string = "   info depth 1 seldepth 1 score cp 6 nodes 251 nps 62750 time 4 multipv 1 pv f6e4 c3e4 d5e4    \n";

        slach::EngineInterface interface;
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        interface.SetPositionToInternalChessBoard(test_position);

        int depth = 0;
        double score = 0.0;
        std::string move_list = "";
        std::string root_move = "";
        interface.ParseALineofStockfishOutput(test_string, depth, score, move_list,root_move);
        TS_ASSERT_EQUALS(move_list, "Ne4 Nxe4 dxe4 ");
        TS_ASSERT_EQUALS(root_move, "Ne4");
        TS_ASSERT_EQUALS(depth, 1);
        TS_ASSERT_DELTA(score, -0.06, 1e-3);
    }

    void TestParseEngineOutputSingleLine()
    {
        std::string test_string =   std::string("info depth 1 seldepth 1 score cp 6 nodes 251 nps 62750 time 4 multipv 1 pv f6e4 c3e4 d5e4") +
												"\ninfo depth 2 seldepth 2 score cp 6 nodes 372 nps 74400 time 5 multipv 1 pv f6e4 c3e4 d5e4"+
												"\ninfo depth 3 seldepth 3 score cp 18 nodes 727 nps 80777 time 9 multipv 1 pv f5d3 c2d3 e7e6"+
												"\ninfo depth 4 seldepth 5 score cp -6 nodes 1761 nps 92684 time 19 multipv 1 pv f6e4 c3e4 d5e4 g2g4"+
												"\ninfo depth 5 seldepth 6 score cp 8 nodes 2676 nps 102923 time 26 multipv 1 pv f5d3 c2d3 e7e6 e1c1 f8d6 f4d6 c7d6"+
												"\ninfo depth 6 seldepth 7 score cp 0 nodes 3778 nps 104944 time 36 multipv 1 pv f5d3 c2d3 e7e6 e1e2 f6g4 h2h3"+
												"\ninfo depth 7 seldepth 11 score cp 2 nodes 6474 nps 102761 time 63 multipv 1 pv f5d3 c2d3 e7e6 e1e2 f8e7 f3e5 c6e5 d4e5 f6g4 h2h3"+
												"\ninfo depth 8 seldepth 16 score cp -22 nodes 21322 nps 120463 time 177 multipv 1 pv f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 f8c5 c3e2 h5f4 e2f4"+
												"\ninfo depth 9 seldepth 16 score cp 0 nodes 31457 nps 129452 time 243 multipv 1 pv f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 h5f4 e3f4 f8c5 c3e4"+
												"\ninfo depth 10 seldepth 18 score cp -2 nodes 48686 nps 139102 time 350 multipv 1 pv f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 h5f4 e3f4 f8c5 c3e4 c5e7 d3b3 d7c6 e4g5 e7g5 f4g5"+
												"\ninfo depth 11 seldepth 21 score cp -2 nodes 71376 nps 145073 time 492 multipv 1 pv f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 h5f4 e3f4 f8c5 c3e4 c5e7 d3b3 d7c6 e4g5 e7g5 f4g5 e8g8"+
												"\ninfo depth 12 seldepth 21 score cp -18 nodes 137610 nps 149089 time 923 multipv 1 pv f5d3 c2d3 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 f7f6 g2g4 f6g5 g4h5 d7f7 d2d1 f8e7 d3d4"+
												"\ninfo depth 13 seldepth 21 score cp -2 nodes 208874 nps 154036 time 1356 multipv 1 pv f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 e1c1 f8e7 c1b1 h5f4 e3f4 e8g8 g2g4 c7c5 a2a3"+
												"\ninfo depth 14 currmove e7e6 currmovenumber 2"+
												"\ninfo depth 14 currmove f5g6 currmovenumber 3"+
												"\ninfo depth 14 currmove c6b4 currmovenumber 4"+
												"\ninfo depth 14 currmove f6e4 currmovenumber 5"+
												"\ninfo depth 14 currmove f6g4 currmovenumber 6"+
												"\ninfo depth 14 currmove f6h5 currmovenumber 7"+
												"\ninfo depth 14 currmove f5e4 currmovenumber 8"+
												"\ninfo depth 14 currmove f5g4 currmovenumber 9"+
												"\ninfo depth 14 currmove f5h3 currmovenumber 10"+
												"\ninfo depth 14 currmove f5e6 currmovenumber 11"+
												"\ninfo depth 14 currmove d7e6 currmovenumber 12"+
												"\ninfo depth 14 currmove d7d6 currmovenumber 13"+
												"\ninfo depth 14 currmove d7d8 currmovenumber 14"+
												"\ninfo depth 14 currmove h8g8 currmovenumber 15"+
												"\ninfo depth 14 currmove b7b5 currmovenumber 16"+
												"\ninfo depth 14 currmove c8a8 currmovenumber 17"+
												"\ninfo depth 14 currmove c8b8 currmovenumber 18"+
												"\ninfo depth 14 currmove f6g8 currmovenumber 19"+
												"\ninfo depth 14 currmove e8d8 currmovenumber 20"+
												"\ninfo depth 14 currmove c6e5 currmovenumber 21"+
												"\ninfo depth 14 currmove e7e5 currmovenumber 22"+
												"\ninfo depth 14 currmove c8d8 currmovenumber 23"+
												"\ninfo depth 14 currmove g7g6 currmovenumber 24"+
												"\ninfo depth 14 currmove h7h6 currmovenumber 25"+
												"\ninfo depth 14 currmove b7b6 currmovenumber 26"+
												"\ninfo depth 14 currmove g7g5 currmovenumber 27"+
												"\ninfo depth 14 currmove c6d8 currmovenumber 28"+
												"\ninfo depth 14 currmove a6a5 currmovenumber 29"+
												"\ninfo depth 14 currmove c6a7 currmovenumber 30"+
												"\ninfo depth 14 currmove c6b8 currmovenumber 31"+
												"\ninfo depth 14 currmove c6a5 currmovenumber 32"+
												"\ninfo depth 14 currmove h7h5 currmovenumber 33"+
												"\ninfo depth 14 currmove c6d4 currmovenumber 34"+
												"\ninfo depth 14 seldepth 22 score cp 2 nodes 584279 nps 155807 time 3750 multipv 1 pv f5d3 d2d3 e7e6 e1c1 f8d6 h2h3 e8g8 a2a3 h7h6 f3e5 d7e8 c1b1 d6e5 f4e5 c6e5 d4e5 f6d7 f2f4"+
												"\ninfo depth 15 currmove f5d3 currmovenumber 1"+
												"\ninfo nodes 740875 time 4736"+
												"\nbestmove f5d3 ponder d2d3";

        slach::EngineInterface interface;
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        interface.SetPositionToInternalChessBoard(test_position);

        interface.ParseWholeEngineOutput(test_string);

        TS_ASSERT_EQUALS(interface.mLatestDepths.size(), 1u);
        TS_ASSERT_EQUALS(interface.mLatestDepths[0], 14u);

        TS_ASSERT_EQUALS(interface.mLatestRootMoves.size(), 1u);
        TS_ASSERT_EQUALS(interface.mLatestRootMoves[0], "Bxd3");

        TS_ASSERT_EQUALS(interface.mLatestScores.size(), 1u);
        TS_ASSERT_DELTA(interface.mLatestScores[0], -0.02, 1e-3);

        TS_ASSERT_EQUALS(interface.mLatestLines.size(), 1u);
        TS_ASSERT_EQUALS(interface.mLatestLines[0], "Bxd3 Qxd3 e6 O-O-O Bd6 h3 O-O a3 h6 Ne5 Qe8 Kb1 Bxe5 Bxe5 Nxe5 dxe5 Nd7 f4 ");
    }

    void xTestParseEngineOutputMultipleLines()
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

