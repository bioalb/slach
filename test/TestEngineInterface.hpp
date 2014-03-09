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

    void TestStartInfiniteAndStop()
    {
        slach::ChessBoard* p_board = new slach::ChessBoard();
        p_board->SetupChessBoard();
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        slach::Position* p_position = new slach::Position();
        std::vector<slach::Square* > squares = p_board->GetSquares();
        p_position->SetFromFen(test_position, squares);

        slach::EngineInterface interface;

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
        interface.StopEngine();
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
        std::string mate_line  = interface.GetLatestEngineOutput()[2];
        std::cout<<mate_line<<std::endl;

        TS_ASSERT_EQUALS(mate_line, "Depth = 0; score = 100.00; Qh5+ mate\n");
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

        std::string engine_output = interface.GetLatestEngineOutput()[0];
        TS_ASSERT_EQUALS(engine_output, "Depth = 0; score = 0.00; CHECKMATE\n");
        std::cout<<engine_output<<std::endl;

        delete p_board;
        delete p_position;
    }

    void TestCheckMateMultplepv()
    {
        slach::ChessBoard* p_board = new slach::ChessBoard();
        p_board->SetupChessBoard();
        std::string fools_mate = "rnbqkbnr/ppppp2p/8/5ppQ/4P3/3P4/PPP2PPP/RNB1KBNR b KQkq - 1 3";
        slach::Position* p_position = new slach::Position();
        std::vector<slach::Square* > squares = p_board->GetSquares();
        p_position->SetFromFen(fools_mate, squares);

        slach::EngineInterface interface;
        interface.SetNumberOfLinesToBeShown(3);
        std::cout<<std::endl<<"*******"<<"Starting analysis of fools mate, multiple pv"<<"*******"<<std::endl;
        interface.StartAnalsyingPosition(p_position, 3.0);
        std::cout<<std::endl<<"Done analysing for 3 seconds the fools mate, engine output follows"<<std::endl;

        std::string engine_output = interface.GetLatestEngineOutput()[0];
        TS_ASSERT_EQUALS(engine_output, "Depth = 0; score = 0.00; CHECKMATE\n");
        std::cout<<engine_output<<std::endl;

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

    void TestParseEngineOutputMultipleLines()
    {

        std::string test_string = std::string("info depth 1 seldepth 1 score cp 6 nodes 522 nps 130500 time 4 multipv 1 pv f6e4 c3e4 d5e4")
                                                +"\ninfo depth 1 seldepth 1 score cp -2 nodes 522 nps 130500 time 4 multipv 2 pv h7h6 d3f5 d7f5"
                                                +"\ninfo depth 1 seldepth 1 score cp -6 nodes 522 nps 130500 time 4 multipv 3 pv e7e6 d3f5 e6f5"
                                                +"\ninfo depth 1 seldepth 1 score cp -16 nodes 522 nps 130500 time 4 multipv 4 pv f5d3 c2d3"
                                                +"\ninfo depth 2 seldepth 3 score cp 6 nodes 1373 nps 137300 time 10 multipv 1 pv f6e4 c3e4 d5e4"
                                                +"\ninfo depth 2 seldepth 3 score cp -16 nodes 1373 nps 137300 time 10 multipv 2 pv f5d3 c2d3"
                                                +"\ninfo depth 2 seldepth 3 score cp -28 nodes 1373 nps 137300 time 10 multipv 3 pv c6b4 d3f5 d7f5"
                                                +"\ninfo depth 2 seldepth 3 score cp -40 nodes 1373 nps 137300 time 10 multipv 4 pv e7e6 e1c1 f5d3 d2d3"
                                                +"\ninfo depth 3 seldepth 4 score cp 18 nodes 2519 nps 132578 time 19 multipv 1 pv f5d3 c2d3 e7e6"
                                                +"\ninfo depth 3 seldepth 4 score cp 6 nodes 2519 nps 132578 time 19 multipv 2 pv f6e4 c3e4 d5e4"
                                                +"\ninfo depth 3 seldepth 4 score cp -28 nodes 2519 nps 132578 time 19 multipv 3 pv c6b4 d3f5 d7f5"
                                                +"\ninfo depth 3 seldepth 4 score cp -40 nodes 2519 nps 132578 time 19 multipv 4 pv e7e6 e1c1 f5d3 d2d3"
                                                +"\ninfo depth 4 seldepth 5 score cp -6 nodes 4622 nps 171185 time 27 multipv 1 pv f6e4 c3e4 d5e4 g2g4"
                                                +"\ninfo depth 4 seldepth 5 score cp -10 nodes 4622 nps 171185 time 27 multipv 2 pv f5d3 c2d3 e7e6 e1e2"
                                                +"\ninfo depth 4 seldepth 5 score cp -30 nodes 4622 nps 171185 time 27 multipv 3 pv c6b4 d3f5 d7f5 e1c1 e7e6"
                                                +"\ninfo depth 4 seldepth 5 score cp -50 nodes 4622 nps 171185 time 27 multipv 4 pv e7e6 d3f5 e6f5 e1c1 f6e4"
                                                +"\ninfo depth 5 seldepth 6 score cp 8 nodes 11440 nps 178750 time 64 multipv 1 pv f5d3 c2d3 e7e6 e1c1 f8d6 f4d6 c7d6"
                                                +"\ninfo depth 5 seldepth 6 score cp -14 nodes 11440 nps 178750 time 64 multipv 2 pv f6e4 c3e4 d5e4 g2g4 e4d3 g4f5"
                                                +"\ninfo depth 5 seldepth 6 score cp -50 nodes 11440 nps 178750 time 64 multipv 3 pv e7e6 d3f5 e6f5 e1c1 f6e4 d2e1"
                                                +"\ninfo depth 5 seldepth 6 score cp -68 nodes 11440 nps 178750 time 64 multipv 4 pv h7h6 e1c1 f6e4 d3e4 d5e4 f3e5 c6e5 d4e5 d7d2 c1d2"
                                                +"\ninfo depth 6 seldepth 8 score cp 16 nodes 16330 nps 192117 time 85 multipv 1 pv f5d3 c2d3 e7e6 e1c1 f8e7 f3e5 c6e5 d4e5"
                                                +"\ninfo depth 6 seldepth 8 score cp -36 nodes 16330 nps 192117 time 85 multipv 2 pv e7e6 d3f5 e6f5 e1c1 f6e4 d2e1 f8e7"
                                                +"\ninfo depth 6 seldepth 8 score cp -38 nodes 16330 nps 192117 time 85 multipv 3 pv f6e4 d3e4 d5e4 f3g5 e7e5 f4e5"
                                                +"\ninfo depth 6 seldepth 8 score cp -52 nodes 16330 nps 192117 time 85 multipv 4 pv h7h6 e1c1 f5d3 d2d3 c6b4 d3e2 e7e6"
                                                +"\ninfo depth 7 seldepth 11 score cp -6 nodes 35426 nps 199022 time 178 multipv 1 pv f5d3 c2d3 e7e6 a2a3 h7h6 e1e2 f8e7 h2h3"
                                                +"\ninfo depth 7 seldepth 11 score cp -38 nodes 35426 nps 199022 time 178 multipv 2 pv e7e6 d3f5 e6f5 e1c1 f6e4 c3e4 f5e4 f3e5 c6e5 f4e5"
                                                +"\ninfo depth 7 seldepth 11 score cp -66 nodes 35426 nps 199022 time 178 multipv 3 pv f5g4 e1c1 f6h5 c3e2 h5f4 e2f4 e7e5 d4e5 g4f3 g2f3 c6e5"
                                                +"\ninfo depth 7 seldepth 11 score cp -68 nodes 35426 nps 199022 time 178 multipv 4 pv f6e4 d3e4 d5e4 f3g5 e7e5 d4e5 d7d2 e1d2 c8d8 d2e2"
                                                +"\ninfo depth 8 seldepth 14 score cp -14 nodes 60788 nps 198006 time 307 multipv 1 pv f5d3 c2d3 f6h5 f4g5 e7e6 e1c1 f8d6 g2g4 h5f6 g5f6 g7f6"
                                                +"\ninfo depth 8 seldepth 14 score cp -32 nodes 60788 nps 198006 time 307 multipv 2 pv e7e6 d3f5 e6f5 f3e5 c6e5 d4e5 f6e4 d2d5 e4c3 d5d7 e8d7 b2c3"
                                                +"\ninfo depth 8 seldepth 14 score cp -54 nodes 60788 nps 198006 time 307 multipv 3 pv h7h6 e1c1 f5d3 d2d3 e7e6 c1b1 f8e7 f3e5 c6e5 f4e5"
                                                +"\ninfo depth 8 seldepth 14 score cp -68 nodes 60788 nps 198006 time 307 multipv 4 pv f5g4 e1c1 f6h5 c3e2 h5f4 e2f4 g7g5 f4e2 f8h6 c1b1 e8g8 e2c3 d7e6 h2h3"
                                                +"\ninfo depth 9 seldepth 16 score cp -14 nodes 85697 nps 204040 time 420 multipv 1 pv f5d3 c2d3 f6h5 f4g5 e7e6 e1c1 f8d6 g2g4 h5f6 g5f6 g7f6"
                                                +"\ninfo depth 9 seldepth 16 score cp -28 nodes 85697 nps 204040 time 420 multipv 2 pv f6e4 d3e4 f5e4 e1c1 e4g6 c1b1 e7e6 f3h4 f8d6 h4g6 h7g6 f4d6 c7d6"
                                                +"\ninfo depth 9 seldepth 16 score cp -32 nodes 85697 nps 204040 time 420 multipv 3 pv e7e6 d3f5 e6f5 f3e5 c6e5 d4e5 f6e4 d2d5 e4c3 d5d7 e8d7 b2c3"
                                                +"\ninfo depth 9 seldepth 16 score cp -50 nodes 85697 nps 204040 time 420 multipv 4 pv h7h6 e1c1 f5d3 d2d3 e7e6 c1b1 f8e7 f3e5 c6e5 d4e5 f6g4 f2f3"
                                                +"\ninfo depth 10 seldepth 18 score cp -40 nodes 178497 nps 212496 time 840 multipv 1 pv f5d3 c2d3 f6h5 f4g5 h5f6 e1c1 e7e6 g5f6 g7f6 c1b1 f8e7 e3e4 e8g8 e4d5 e6d5 g1e1"
                                                +"\ninfo depth 10 seldepth 18 score cp -40 nodes 178497 nps 212496 time 840 multipv 2 pv f5g6 e1c1 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 g6d3 d2d3 h7h6 g5h4 f8e7 h4e7 e8e7"
                                                +"\ninfo depth 10 seldepth 18 score cp -46 nodes 178497 nps 212496 time 840 multipv 3 pv f6e4 d3e4 f5e4 c3e4 d5e4 f3e5 c6e5 f4e5 f7f6 e5g3 e8f7 e1c1 c8d8"
                                                +"\ninfo depth 10 seldepth 18 score cp -52 nodes 178497 nps 212496 time 840 multipv 4 pv e7e6 d3f5 e6f5 f3e5 c6e5 d4e5 f6e4 c3e4 f5e4 e1c1 c7c6 f2f3 e4f3 g2f3 d7h3"
                                                +"\ninfo depth 11 seldepth 20 score cp -40 nodes 253005 nps 213326 time 1186 multipv 1 pv f5d3 c2d3 e7e6 g2g4 f8e7 f3e5 c6e5 d4e5 f6g8 g4g5 d5d4 c3e4 d4e3 f2e3"
                                                +"\ninfo depth 11 seldepth 20 score cp -44 nodes 253005 nps 213326 time 1186 multipv 2 pv e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8e7 c1b1 e8g8 e5c6 e6c6 f2f3 c8e8 d2d3 c6d7"
                                                +"\ninfo depth 11 seldepth 20 score cp -46 nodes 253005 nps 213326 time 1186 multipv 3 pv f6e4 d3e4 f5e4 c3e4 d5e4 f3e5 c6e5 f4e5 f7f6 e5g3 e8f7 d2b4 c7c6"
                                                +"\ninfo depth 11 seldepth 20 score cp -52 nodes 253005 nps 213326 time 1186 multipv 4 pv f5g6 e1c1 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 g6d3 d2d3 h7h6 g5h4 f8e7 h4e7 e8e7 g2g4"
                                                +"\ninfo depth 12 seldepth 21 score cp -22 nodes 391446 nps 216149 time 1811 multipv 1 pv f5d3 c2d3 e7e6 g2g4 f8e7 f3e5 c6e5 d4e5 f6g8 e1e2 g7g5 f4g3 g8h6 h2h3 e8g8 f2f4 g8g7 f4g5 e7g5"
                                                +"\ninfo depth 12 seldepth 21 score cp -28 nodes 391446 nps 216149 time 1811 multipv 2 pv e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8b4 f2f3 e8g8 c1b1 f8e8 f4g3 b4d6 g1e1 c6e5 d4e5 d6e5 c3d5 e5g3 h2g3 f6d5 d2d5 e6d5 d1d5"
                                                +"\ninfo depth 12 seldepth 21 score cp -46 nodes 391446 nps 216149 time 1811 multipv 3 pv f6e4 d3e4 f5e4 c3e4 d5e4 f3e5 c6e5 f4e5 f7f6 e5g3 e8f7 d2b4 c7c6 e1c1"
                                                +"\ninfo depth 12 seldepth 21 score cp -52 nodes 391446 nps 216149 time 1811 multipv 4 pv f5g6 e1c1 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 f7f6 e5f6 h5f6 d3g6 h7g6 h2h3 f8d6 d2d3 e8f7 c1b1"
                                                +"\ninfo depth 13 seldepth 22 score cp -20 nodes 616566 nps 218950 time 2816 multipv 1 pv f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 f7f6 g2g4 f6g5 g4h5 f8e7 e1d2"
                                                +"\ninfo depth 13 seldepth 22 score cp -34 nodes 616566 nps 218950 time 2816 multipv 2 pv e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8b4 f2f3 e8g8 c1b1 f8e8 h2h3 b4d6 g1e1 c6e5 d4e5 d6e5 c3d5 e5f4 e3f4"
                                                +"\ninfo depth 13 seldepth 22 score cp -48 nodes 616566 nps 218950 time 2816 multipv 3 pv f6e4 d3e4 f5e4 c3e4 d5e4 f3e5 c6e5 d4e5 d7d2 e1d2 e7e6 g1d1 f8e7 d2e2 g7g5 f4g3 c8d8"
                                                +"\ninfo depth 13 seldepth 22 score cp -52 nodes 616566 nps 218950 time 2816 multipv 4 pv f5g6 e1c1 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 f7f6 e5f6 h5f6 d3g6 h7g6 h2h3 f8d6 d2d3 e8f7 c1b1"
                                                +"\ninfo depth 14 seldepth 22 score cp -12 lowerbound nodes 663085 nps 218048 time 3041 multipv 1 pv f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 f7f6 g2g4 f6g5 g4h5 f8e7 e1d2 c8d8"
                                                +"\ninfo depth 13 seldepth 22 score cp -34 nodes 663085 nps 218048 time 3041 multipv 2 pv e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8b4 f2f3 e8g8 c1b1 f8e8 h2h3 b4d6 g1e1 c6e5 d4e5 d6e5 c3d5 e5f4 e3f4"
                                                +"\ninfo depth 13 seldepth 22 score cp -48 nodes 663085 nps 218048 time 3041 multipv 3 pv f6e4 d3e4 f5e4 c3e4 d5e4 f3e5 c6e5 d4e5 d7d2 e1d2 e7e6 g1d1 f8e7 d2e2 g7g5 f4g3 c8d8"
                                                +"\ninfo depth 13 seldepth 22 score cp -52 nodes 663085 nps 218048 time 3041 multipv 4 pv f5g6 e1c1 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 f7f6 e5f6 h5f6 d3g6 h7g6 h2h3 f8d6 d2d3 e8f7 c1b1"
                                                +"\ninfo depth 14 currmove f5d3 currmovenumber 1"
                                                +"\ninfo depth 14 seldepth 22 score cp -4 lowerbound nodes 693158 nps 218386 time 3174 multipv 1 pv f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 f7f6 g2g4 f6g5 g4h5 d7f7 g1g5 f8e7"
                                                +"\ninfo depth 13 seldepth 22 score cp -34 nodes 693158 nps 218386 time 3174 multipv 2 pv e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8b4 f2f3 e8g8 c1b1 f8e8 h2h3 b4d6 g1e1 c6e5 d4e5 d6e5 c3d5 e5f4 e3f4"
                                                +"\ninfo depth 13 seldepth 22 score cp -48 nodes 693158 nps 218386 time 3174 multipv 3 pv f6e4 d3e4 f5e4 c3e4 d5e4 f3e5 c6e5 d4e5 d7d2 e1d2 e7e6 g1d1 f8e7 d2e2 g7g5 f4g3 c8d8"
                                                +"\ninfo depth 13 seldepth 22 score cp -52 nodes 693158 nps 218386 time 3174 multipv 4 pv f5g6 e1c1 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 f7f6 e5f6 h5f6 d3g6 h7g6 h2h3 f8d6 d2d3 e8f7 c1b1"
                                                +"\ninfo depth 14 currmove f5d3 currmovenumber 1"
                                                +"\ninfo depth 14 seldepth 22 score cp 8 lowerbound nodes 749055 nps 218766 time 3424 multipv 1 pv f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 f7f6 g2g4 f6g5 g4h5 d7f7 g1g5 f8e7"
                                                +"\ninfo depth 13 seldepth 22 score cp -34 nodes 749055 nps 218766 time 3424 multipv 2 pv e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8b4 f2f3 e8g8 c1b1 f8e8 h2h3 b4d6 g1e1 c6e5 d4e5 d6e5 c3d5 e5f4 e3f4"
                                                +"\ninfo depth 13 seldepth 22 score cp -48 nodes 749055 nps 218766 time 3424 multipv 3 pv f6e4 d3e4 f5e4 c3e4 d5e4 f3e5 c6e5 d4e5 d7d2 e1d2 e7e6 g1d1 f8e7 d2e2 g7g5 f4g3 c8d8"
                                                +"\ninfo depth 13 seldepth 22 score cp -52 nodes 749055 nps 218766 time 3424 multipv 4 pv f5g6 e1c1 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 f7f6 e5f6 h5f6 d3g6 h7g6 h2h3 f8d6 d2d3 e8f7 c1b1"
                                                +"\ninfo depth 14 currmove f5d3 currmovenumber 1"
                                                +"\ninfo depth 14 currmove f6e4 currmovenumber 2"
                                                +"\ninfo depth 14 currmove e7e6 currmovenumber 3"
                                                +"\ninfo depth 14 currmove f5g6 currmovenumber 4"
                                                +"\ninfo depth 14 currmove f6g4 currmovenumber 5"
                                                +"\ninfo depth 14 currmove c6b4 currmovenumber 6"
                                                +"\ninfo depth 14 currmove f6h5 currmovenumber 7"
                                                +"\ninfo depth 14 currmove g7g5 currmovenumber 8"
                                                +"\ninfo depth 14 currmove f5g4 currmovenumber 9"
                                                +"\ninfo depth 14 currmove d7e6 currmovenumber 10"
                                                +"\ninfo depth 14 currmove f5h3 currmovenumber 11"
                                                +"\ninfo depth 14 currmove f5e6 currmovenumber 12"
                                                +"\ninfo depth 14 currmove c8d8 currmovenumber 13"
                                                +"\ninfo depth 14 currmove d7d6 currmovenumber 14"
                                                +"\ninfo depth 14 currmove f5e4 currmovenumber 15"
                                                +"\ninfo depth 14 currmove e7e5 currmovenumber 16"
                                                +"\ninfo depth 14 currmove g7g6 currmovenumber 17"
                                                +"\ninfo depth 14 currmove c6d8 currmovenumber 18"
                                                +"\ninfo depth 14 currmove h7h6 currmovenumber 19"
                                                +"\ninfo depth 14 currmove h7h5 currmovenumber 20"
                                                +"\ninfo depth 14 currmove c6b8 currmovenumber 21"
                                                +"\ninfo depth 14 currmove c6e5 currmovenumber 22"
                                                +"\ninfo depth 14 currmove f6g8 currmovenumber 23"
                                                +"\ninfo depth 14 currmove c6a7 currmovenumber 24"
                                                +"\ninfo depth 14 currmove c8a8 currmovenumber 25"
                                                +"\ninfo depth 14 currmove a6a5 currmovenumber 26"
                                                +"\ninfo depth 14 currmove c6a5 currmovenumber 27"
                                                +"\ninfo depth 14 currmove b7b5 currmovenumber 28"
                                                +"\ninfo depth 14 currmove e8d8 currmovenumber 29"
                                                +"\ninfo depth 14 currmove d7d8 currmovenumber 30"
                                                +"\ninfo depth 14 currmove c8b8 currmovenumber 31"
                                                +"\ninfo depth 14 currmove h8g8 currmovenumber 32"
                                                +"\ninfo depth 14 currmove b7b6 currmovenumber 33"
                                                +"\ninfo depth 14 currmove c6d4 currmovenumber 34"
                                                +"\ninfo depth 14 seldepth 24 score cp -2 nodes 843846 nps 218104 time 3869 multipv 1 pv f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 g2g3 f8c5 e1c1 e8g8 c1b1 d7e8 h2h4 c5e7 e3e4 h5f4 g3f4 e7h4 e4d5 h4f2"
                                                +"\ninfo depth 13 seldepth 24 score cp -34 nodes 843846 nps 218104 time 3869 multipv 2 pv e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8b4 f2f3 e8g8 c1b1 f8e8 h2h3 b4d6 g1e1 c6e5 d4e5 d6e5 c3d5 e5f4 e3f4"
                                                +"\ninfo depth 13 seldepth 24 score cp -48 nodes 843846 nps 218104 time 3869 multipv 3 pv f6e4 d3e4 f5e4 c3e4 d5e4 f3e5 c6e5 d4e5 d7d2 e1d2 e7e6 g1d1 f8e7 d2e2 g7g5 f4g3 c8d8"
                                                +"\ninfo depth 13 seldepth 24 score cp -52 nodes 843846 nps 218104 time 3869 multipv 4 pv f5g6 e1c1 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 f7f6 e5f6 h5f6 d3g6 h7g6 h2h3 f8d6 d2d3 e8f7 c1b1"
                                                +"\ninfo depth 14 currmove e7e6 currmovenumber 2"
                                                +"\ninfo depth 14 currmove f6e4 currmovenumber 3"
                                                +"\ninfo depth 14 currmove f6h5 currmovenumber 4"
                                                +"\ninfo depth 14 currmove f6g4 currmovenumber 5"
                                                +"\ninfo depth 14 currmove c6b4 currmovenumber 6"
                                                +"\ninfo depth 14 currmove f5g6 currmovenumber 7"
                                                +"\ninfo depth 14 currmove d7e6 currmovenumber 8"
                                                +"\ninfo depth 14 currmove g7g5 currmovenumber 9"
                                                +"\ninfo depth 14 currmove f5h3 currmovenumber 10"
                                                +"\ninfo depth 14 currmove d7d6 currmovenumber 11"
                                                +"\ninfo depth 14 currmove f5e4 currmovenumber 12"
                                                +"\ninfo depth 14 currmove f5g4 currmovenumber 13"
                                                +"\ninfo depth 14 currmove c8d8 currmovenumber 14"
                                                +"\ninfo depth 14 currmove e7e5 currmovenumber 15"
                                                +"\ninfo depth 14 currmove f5e6 currmovenumber 16"
                                                +"\ninfo depth 14 currmove g7g6 currmovenumber 17"
                                                +"\ninfo depth 14 currmove h7h6 currmovenumber 18"
                                                +"\ninfo depth 14 currmove c6d8 currmovenumber 19"
                                                +"\ninfo depth 14 currmove h7h5 currmovenumber 20"
                                                +"\ninfo depth 14 currmove c6b8 currmovenumber 21"
                                                +"\ninfo depth 14 currmove c6e5 currmovenumber 22"
                                                +"\ninfo depth 14 currmove f6g8 currmovenumber 23"
                                                +"\ninfo depth 14 currmove c6a7 currmovenumber 24"
                                                +"\ninfo depth 14 currmove c8a8 currmovenumber 25"
                                                +"\ninfo depth 14 currmove a6a5 currmovenumber 26"
                                                +"\ninfo depth 14 currmove c6a5 currmovenumber 27"
                                                +"\ninfo depth 14 currmove b7b5 currmovenumber 28"
                                                +"\ninfo depth 14 currmove e8d8 currmovenumber 29"
                                                +"\ninfo depth 14 currmove d7d8 currmovenumber 30"
                                                +"\ninfo depth 14 currmove c8b8 currmovenumber 31"
                                                +"\ninfo depth 14 currmove h8g8 currmovenumber 32"
                                                +"\ninfo depth 14 currmove b7b6 currmovenumber 33"
                                                +"\ninfo depth 14 currmove c6d4 currmovenumber 34"
                                                +"\ninfo depth 14 seldepth 24 score cp -2 nodes 879075 nps 218295 time 4027 multipv 1 pv f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 g2g3 f8c5 e1c1 e8g8 c1b1 d7e8 h2h4 c5e7 e3e4 h5f4 g3f4 e7h4 e4d5 h4f2"
                                                +"\ninfo depth 14 seldepth 24 score cp -34 nodes 879075 nps 218295 time 4027 multipv 2 pv e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8b4 f2f3 e8g8 c1b1 f8e8 h2h3 b4d6 g1e1 c6e5 d4e5 d6e5 c3d5 c7c5"
                                                +"\ninfo depth 13 seldepth 24 score cp -48 nodes 879075 nps 218295 time 4027 multipv 3 pv f6e4 d3e4 f5e4 c3e4 d5e4 f3e5 c6e5 d4e5 d7d2 e1d2 e7e6 g1d1 f8e7 d2e2 g7g5 f4g3 c8d8"
                                                +"\ninfo depth 13 seldepth 24 score cp -52 nodes 879075 nps 218295 time 4027 multipv 4 pv f5g6 e1c1 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 f7f6 e5f6 h5f6 d3g6 h7g6 h2h3 f8d6 d2d3 e8f7 c1b1"
                                                +"\ninfo depth 14 currmove f6e4 currmovenumber 3"
                                                +"\ninfo depth 14 currmove f5g6 currmovenumber 4"
                                                +"\ninfo depth 14 currmove f6g4 currmovenumber 5"
                                                +"\ninfo depth 14 currmove c6b4 currmovenumber 6"
                                                +"\ninfo depth 14 currmove f6h5 currmovenumber 7"
                                                +"\ninfo depth 14 currmove c8d8 currmovenumber 8"
                                                +"\ninfo depth 14 currmove f5g4 currmovenumber 9"
                                                +"\ninfo depth 14 currmove d7e6 currmovenumber 10"
                                                +"\ninfo depth 14 currmove g7g5 currmovenumber 11"
                                                +"\ninfo depth 14 currmove f5h3 currmovenumber 12"
                                                +"\ninfo depth 14 currmove e7e5 currmovenumber 13"
                                                +"\ninfo depth 14 currmove d7d6 currmovenumber 14"
                                                +"\ninfo depth 14 currmove f5e4 currmovenumber 15"
                                                +"\ninfo depth 14 currmove h7h5 currmovenumber 16"
                                                +"\ninfo depth 14 currmove f5e6 currmovenumber 17"
                                                +"\ninfo depth 14 currmove h7h6 currmovenumber 18"
                                                +"\ninfo depth 14 currmove g7g6 currmovenumber 19"
                                                +"\ninfo depth 14 currmove c6b8 currmovenumber 20"
                                                +"\ninfo depth 14 currmove c8a8 currmovenumber 21"
                                                +"\ninfo depth 14 currmove c6e5 currmovenumber 22"
                                                +"\ninfo depth 14 currmove f6g8 currmovenumber 23"
                                                +"\ninfo depth 14 currmove c6d8 currmovenumber 24"
                                                +"\ninfo depth 14 currmove c6a7 currmovenumber 25"
                                                +"\ninfo depth 14 currmove a6a5 currmovenumber 26"
                                                +"\ninfo depth 14 currmove c6a5 currmovenumber 27"
                                                +"\ninfo depth 14 currmove b7b5 currmovenumber 28"
                                                +"\ninfo depth 14 currmove e8d8 currmovenumber 29"
                                                +"\ninfo depth 14 currmove d7d8 currmovenumber 30"
                                                +"\ninfo depth 14 currmove c8b8 currmovenumber 31"
                                                +"\ninfo depth 14 currmove h8g8 currmovenumber 32"
                                                +"\ninfo depth 14 currmove b7b6 currmovenumber 33"
                                                +"\ninfo depth 14 currmove c6d4 currmovenumber 34"
                                                +"\ninfo depth 14 seldepth 24 score cp -2 nodes 950342 nps 222042 time 4280 multipv 1 pv f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 g2g3 f8c5 e1c1 e8g8 c1b1 d7e8 h2h4 c5e7 e3e4 h5f4 g3f4 e7h4 e4d5 h4f2"
                                                +"\ninfo depth 14 seldepth 24 score cp -34 nodes 950342 nps 222042 time 4280 multipv 2 pv e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8b4 f2f3 e8g8 c1b1 f8e8 h2h3 b4d6 g1e1 c6e5 d4e5 d6e5 c3d5 c7c5"
                                                +"\ninfo depth 14 seldepth 24 score cp -52 nodes 950342 nps 222042 time 4280 multipv 3 pv f5g6 e1c1 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 f7f6 e5f6 h5f6 d3g6 h7g6 h2h3 f8d6 d2d3 e8f7 c1b1"
                                                +"\ninfo depth 13 seldepth 24 score cp -48 nodes 950342 nps 222042 time 4280 multipv 4 pv f6e4 d3e4 f5e4 c3e4 d5e4 f3e5 c6e5 d4e5 d7d2 e1d2 e7e6 d2e2 f8e7 a1d1 h7h5 d1d4 c8d8 d4e4"
                                                +"\ninfo depth 14 currmove f6e4 currmovenumber 4"
                                                +"\ninfo depth 14 currmove f6g4 currmovenumber 5"
                                                +"\ninfo depth 14 currmove f6h5 currmovenumber 6"
                                                +"\ninfo depth 14 currmove c6b4 currmovenumber 7"
                                                +"\ninfo depth 14 currmove c8d8 currmovenumber 8"
                                                +"\ninfo depth 14 currmove f5g4 currmovenumber 9"
                                                +"\ninfo depth 14 currmove e7e5 currmovenumber 10"
                                                +"\ninfo depth 14 currmove f5h3 currmovenumber 11"
                                                +"\ninfo depth 14 currmove d7d6 currmovenumber 12"
                                                +"\ninfo depth 14 currmove f5e4 currmovenumber 13"
                                                +"\ninfo depth 14 currmove d7e6 currmovenumber 14"
                                                +"\ninfo depth 14 currmove g7g5 currmovenumber 15"
                                                +"\ninfo depth 14 currmove f5e6 currmovenumber 16"
                                                +"\ninfo depth 14 currmove c8a8 currmovenumber 17"
                                                +"\ninfo depth 14 currmove h7h5 currmovenumber 18"
                                                +"\ninfo depth 14 currmove h7h6 currmovenumber 19"
                                                +"\ninfo depth 14 currmove g7g6 currmovenumber 20"
                                                +"\ninfo depth 14 currmove c6b8 currmovenumber 21"
                                                +"\ninfo depth 14 currmove b7b5 currmovenumber 22"
                                                +"\ninfo depth 14 currmove c6e5 currmovenumber 23"
                                                +"\ninfo depth 14 currmove f6g8 currmovenumber 24"
                                                +"\ninfo depth 14 currmove c6d8 currmovenumber 25"
                                                +"\ninfo depth 14 currmove c6a7 currmovenumber 26"
                                                +"\ninfo depth 14 currmove a6a5 currmovenumber 27"
                                                +"\ninfo depth 14 currmove c6a5 currmovenumber 28"
                                                +"\ninfo depth 14 currmove e8d8 currmovenumber 29"
                                                +"\ninfo depth 14 currmove d7d8 currmovenumber 30"
                                                +"\ninfo depth 14 currmove c8b8 currmovenumber 31"
                                                +"\ninfo depth 14 currmove h8g8 currmovenumber 32"
                                                +"\ninfo depth 14 currmove b7b6 currmovenumber 33"
                                                +"\ninfo depth 14 currmove c6d4 currmovenumber 34"
                                                +"\ninfo depth 14 seldepth 24 score cp -2 nodes 962019 nps 222277 time 4328 multipv 1 pv f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6h5 g2g3 f8c5 e1c1 e8g8 c1b1 d7e8 h2h4 c5e7 e3e4 h5f4 g3f4 e7h4 e4d5 h4f2"
                                                +"\ninfo depth 14 seldepth 24 score cp -34 nodes 962019 nps 222277 time 4328 multipv 2 pv e7e6 d3f5 e6f5 f3e5 d7e6 e1c1 f8b4 f2f3 e8g8 c1b1 f8e8 h2h3 b4d6 g1e1 c6e5 d4e5 d6e5 c3d5 c7c5"
                                                +"\ninfo depth 14 seldepth 24 score cp -52 nodes 962019 nps 222277 time 4328 multipv 3 pv f5g6 e1c1 e7e6 f3e5 c6e5 d4e5 f6h5 f4g5 f7f6 e5f6 h5f6 d3g6 h7g6 h2h3 f8d6 d2d3 e8f7 c1b1"
                                                +"\ninfo depth 14 seldepth 24 score cp -54 nodes 962019 nps 222277 time 4328 multipv 4 pv f6e4 d3e4 f5e4 c3e4 d5e4 f3e5 c6e5 d4e5 d7d2 e1d2 e7e6 d2e2 f8e7 a1d1 h7h5 d1d4 c8d8 d4e4"
                                                +"\ninfo depth 15 currmove f5d3 currmovenumber 1"
                                                +"\ninfo nodes 990650 time 4473"
                                                +"\nbestmove f5d3 ponder d2d3";

        slach::EngineInterface interface;
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8"; //test_position_3
        interface.SetPositionToInternalChessBoard(test_position);

        interface.SetNumberOfLinesToBeShown(4u);//asking stockfish to display 4 lines
        interface.ParseWholeEngineOutput(test_string);
        TS_ASSERT_EQUALS(interface.mLatestDepths.size(), 4u);
        TS_ASSERT_EQUALS(interface.mLatestDepths[3], 14u);
        TS_ASSERT_EQUALS(interface.mLatestDepths[2], 14u);
        TS_ASSERT_EQUALS(interface.mLatestDepths[1], 14u);
        TS_ASSERT_EQUALS(interface.mLatestDepths[0], 14u);

        TS_ASSERT_EQUALS(interface.mLatestRootMoves.size(), 4u);
        TS_ASSERT_EQUALS(interface.mLatestRootMoves[3], "Bxd3");
        TS_ASSERT_EQUALS(interface.mLatestRootMoves[2], "e6");
        TS_ASSERT_EQUALS(interface.mLatestRootMoves[1], "Bg6");
        TS_ASSERT_EQUALS(interface.mLatestRootMoves[0], "Ne4");

        TS_ASSERT_EQUALS(interface.mLatestScores.size(), 4u);
        TS_ASSERT_DELTA(interface.mLatestScores[3], 0.02, 1e-3);
        TS_ASSERT_DELTA(interface.mLatestScores[2], 0.34,1e-3);
        TS_ASSERT_DELTA(interface.mLatestScores[1], 0.52, 1e-3);
        TS_ASSERT_DELTA(interface.mLatestScores[0], 0.54, 1e-3);

        TS_ASSERT_EQUALS(interface.mLatestLines.size(), 4u);
        TS_ASSERT_EQUALS(interface.mLatestLines[3], "Bxd3 Qxd3 e6 Ne5 Nxe5 dxe5 Nh5 g3 Bc5 O-O-O O-O Kb1 Qe8 h4 Be7 e4 Nxf4 gxf4 Bxh4 exd5 Bxf2 ");
        TS_ASSERT_EQUALS(interface.mLatestLines[2], "e6 Bxf5 exf5 Ne5 Qe6 O-O-O Bb4 f3 O-O Kb1 Rfe8 h3 Bd6 Rge1 Nxe5 dxe5 Bxe5 Nxd5 c5 ");
        TS_ASSERT_EQUALS(interface.mLatestLines[1], "Bg6 O-O-O e6 Ne5 Nxe5 dxe5 Nh5 Bg5 f6 exf6 Nxf6 Bxg6+ hxg6 h3 Bd6 Qd3 Kf7 Kb1 ");
        TS_ASSERT_EQUALS(interface.mLatestLines[0], "Ne4 Bxe4 Bxe4 Nxe4 dxe4 Ne5 Nxe5 dxe5 Qxd2+ Kxd2 e6 Ke2 Be7 Rad1 h5 Rd4 Rd8 Rxe4 ");

        int depth;
        double score;
        std::string best_move;
        interface.GetLatestBestScoreAndDepth(score,depth, best_move);
        TS_ASSERT_EQUALS(depth, 14);
        TS_ASSERT_DELTA(score, 0.02, 0.01);
        TS_ASSERT_EQUALS(best_move, "Bxd3");
    }

    void TestParseEngineOutputMultipleLinesWhiteToMove()
    {

        std::string test_string = std::string("info depth 1 seldepth 2 score cp 24 nodes 494 nps 123500 time 4 multipv 2 pv h2h3")
                                            +"\ninfo depth 1 seldepth 2 score cp 12 nodes 494 nps 123500 time 4 multipv 3 pv a2a3"
                                            +"\ninfo depth 1 seldepth 2 score cp 12 nodes 494 nps 123500 time 4 multipv 4 pv d3f5 d7f5"
                                            +"\ninfo depth 2 seldepth 3 score cp 76 nodes 1682 nps 186888 time 9 multipv 1 pv e1c1 f6e4 c3e4 d5e4"
                                            +"\ninfo depth 2 seldepth 3 score cp 14 nodes 1682 nps 186888 time 9 multipv 2 pv h2h3 f6e4 c3e4 d5e4"
                                            +"\ninfo depth 2 seldepth 3 score cp 12 nodes 1682 nps 186888 time 9 multipv 3 pv d3f5 d7f5"
                                            +"\ninfo depth 2 seldepth 3 score cp 4 nodes 1682 nps 186888 time 9 multipv 4 pv h2h4 f6e4 c3e4 d5e4"
                                            +"\ninfo depth 3 seldepth 4 score cp 64 nodes 3187 nps 199187 time 16 multipv 1 pv e1c1 f5d3 d2d3 e7e6"
                                            +"\ninfo depth 3 seldepth 4 score cp 42 nodes 3187 nps 199187 time 16 multipv 2 pv d3f5 d7f5 e1c1 e7e6"
                                            +"\ninfo depth 3 seldepth 4 score cp 14 nodes 3187 nps 199187 time 16 multipv 3 pv h2h3 f6e4 c3e4 d5e4"
                                            +"\ninfo depth 3 seldepth 4 score cp 4 nodes 3187 nps 199187 time 16 multipv 4 pv h2h4 f6e4 c3e4 d5e4"
                                            +"\ninfo depth 4 seldepth 5 score cp 84 nodes 6714 nps 216580 time 31 multipv 1 pv d3f5 d7f5 e1c1 e7e6 c1b1"
                                            +"\ninfo depth 4 seldepth 5 score cp 68 nodes 6714 nps 216580 time 31 multipv 2 pv e1c1 f6e4 d2e1 c6b4 d3e4 d5e4"
                                            +"\ninfo depth 4 seldepth 5 score cp 4 nodes 6714 nps 216580 time 31 multipv 3 pv h2h3 f5d3 c2d3 e7e6"
                                            +"\ninfo depth 4 seldepth 5 score cp -2 nodes 6714 nps 216580 time 31 multipv 4 pv a2a3 f5d3 d2d3 e7e6"
                                            +"\ninfo depth 5 seldepth 6 score cp 74 nodes 9816 nps 245400 time 40 multipv 1 pv d3f5 d7f5 e1c1 e7e6 c1b1 f8e7"
                                            +"\ninfo depth 5 seldepth 6 score cp 62 nodes 9816 nps 245400 time 40 multipv 2 pv e1c1 f5d3 d2d3 c6b4 d3e2 e7e6"
                                            +"\ninfo depth 5 seldepth 6 score cp 18 nodes 9816 nps 245400 time 40 multipv 3 pv a2a3 f6e4 c3e4 d5e4 g2g4"
                                            +"\ninfo depth 5 seldepth 6 score cp 16 nodes 9816 nps 245400 time 40 multipv 4 pv h2h3 f6e4 d3e4 d5e4 f3e5 c6e5 f4e5"
                                            +"\ninfo depth 6 seldepth 7 score cp 82 nodes 14280 nps 259636 time 55 multipv 1 pv e1c1 f5d3 d2d3 e7e6 c1b1 f8d6 c3e2"
                                            +"\ninfo depth 6 seldepth 7 score cp 64 nodes 14280 nps 259636 time 55 multipv 2 pv d3f5 d7f5 e1c1 e7e6 c1b1 f8d6 c3e2"
                                            +"\ninfo depth 6 seldepth 7 score cp 22 nodes 14280 nps 259636 time 55 multipv 3 pv a2a3 f6e4 c3e4 d5e4 g2g4 e4d3 g4f5"
                                            +"\ninfo depth 6 seldepth 7 score cp 22 nodes 14280 nps 259636 time 55 multipv 4 pv h2h3 f5d3 c2d3 e7e6 e1e2 f8e7"
                                            +"\ninfo depth 7 seldepth 12 score cp 64 nodes 31831 nps 256701 time 124 multipv 1 pv e1c1 f5d3 d2d3 e7e6 c1b1 f8d6 f3e5 d6e5 d4e5 f6g4"
                                            +"\ninfo depth 7 seldepth 12 score cp 54 nodes 31831 nps 256701 time 124 multipv 2 pv d3f5 d7f5 e1c1 e7e6 c1b1 f8d6 g2g4 f5g6 g4g5 f6e4 c3e4 g6e4"
                                            +"\ninfo depth 7 seldepth 12 score cp 48 nodes 31831 nps 256701 time 124 multipv 3 pv h2h3 f5d3 d2d3 c6b4 d3d2 e7e6 e1c1 f8e7"
                                            +"\ninfo depth 7 seldepth 12 score cp 18 nodes 31831 nps 256701 time 124 multipv 4 pv a2a3 f5d3 d2d3 e7e6 e1c1 f8e7 f3e5 c6e5 f4e5"
                                            +"\ninfo depth 8 seldepth 15 score cp 82 nodes 60267 nps 265493 time 227 multipv 1 pv e1c1 f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6g4 d3e2 f7f5 c1b1"
                                            +"\ninfo depth 8 seldepth 15 score cp 76 nodes 60267 nps 265493 time 227 multipv 2 pv f3e5 c6e5 d4e5 f6e4 d3e4 d5e4 d2d7 f5d7 e1e2 d7g4 f2f3 e4f3 g2f3"
                                            +"\ninfo depth 8 seldepth 15 score cp 50 nodes 60267 nps 265493 time 227 multipv 3 pv h2h3 e7e6 e1c1 f5d3 d2d3 f8d6 f3e5 c6b4 d3e2 d6e5 f4e5"
                                            +"\ninfo depth 8 seldepth 15 score cp 28 nodes 60267 nps 265493 time 227 multipv 4 pv d3f5 d7f5 e1c1 e7e6 c1b1 f8d6 g2g4 f6g4 h2h3 g4f6 g1g7 d6f4 e3f4 f5h3"
                                            +"\ninfo depth 9 seldepth 16 score cp 72 nodes 114572 nps 280127 time 409 multipv 1 pv f3e5 c6e5 d4e5 f6e4 d3e4 d5e4 d2d7 f5d7 e1c1 d7g4 d1d4 c7c5 d4e4"
                                            +"\ninfo depth 9 seldepth 16 score cp 52 nodes 114572 nps 280127 time 409 multipv 2 pv h2h3 e7e6 d3f5 e6f5 e1c1 f6e4 c3e4 f5e4 f3e5 c6e5 f4e5"
                                            +"\ninfo depth 9 seldepth 16 score cp 46 nodes 114572 nps 280127 time 409 multipv 3 pv d3f5 d7f5 f3e5 g7g5 e5c6 g5f4 c6e5 f4e3 f2e3 e7e6 g2g4"
                                            +"\ninfo depth 9 seldepth 16 score cp 40 nodes 114572 nps 280127 time 409 multipv 4 pv e1c1 f5d3 d2d3 e7e6 g2g4 f8b4 g4g5 b4c3 g5f6 c6b4 d3e2 b4a2 c1b1"
                                            +"\ninfo depth 10 seldepth 19 score cp 92 nodes 183916 nps 279507 time 658 multipv 1 pv f3e5 c6e5 d4e5 f6e4 d3e4 d5e4 d2d7 f5d7 e1c1 d7c6 d1d4 e7e6 c3e4 f8e7 h2h3"
                                            +"\ninfo depth 10 seldepth 19 score cp 62 nodes 183916 nps 279507 time 658 multipv 2 pv e1c1 f5d3 d2d3 e7e6 g2g4 f8d6 f3e5 c6b4 d3e2 d7e7 a2a3 d6e5 f4e5"
                                            +"\ninfo depth 10 seldepth 19 score cp 58 nodes 183916 nps 279507 time 658 multipv 3 pv d3f5 d7f5 h2h3 f6e4 c3e4 d5e4 g2g4 f5d7 f3e5 c6e5 f4e5 e7e6"
                                            +"\ninfo depth 10 seldepth 19 score cp 40 nodes 183916 nps 279507 time 658 multipv 4 pv h2h3 f5d3 c2d3 e7e6 g2g4 f8e7 f3e5 c6e5 d4e5 f6g8 e1e2"
                                            +"\ninfo depth 11 seldepth 19 score cp 92 nodes 334621 nps 256414 time 1305 multipv 1 pv f3e5 c6e5 d4e5 f6e4 d3e4 d5e4 d2d7 f5d7 e1c1 e7e6 c3e4 d7c6 d1d4 f8e7 g1d1 c6d5 c2c4 d5e4 d4e4"
                                            +"\ninfo depth 11 seldepth 19 score cp 52 nodes 334621 nps 256414 time 1305 multipv 2 pv e1c1 f5d3 d2d3 e7e6 g2g4 c6b4 d3f1 c7c5 f3e5 d7d8 a2a3 c5d4 e3d4 b4c6 c1b1 f8d6"
                                            +"\ninfo depth 11 seldepth 19 score cp 52 nodes 334621 nps 256414 time 1305 multipv 3 pv d3f5 d7f5 f3e5 g7g5 e5c6 g5f4 c6e5 f8h6 e1c1 f5g5 d1e1 c7c5 c1b1 e8g8 e5f3 f4e3 e1e3"
                                            +"\ninfo depth 11 seldepth 19 score cp 34 nodes 334621 nps 256414 time 1305 multipv 4 pv h2h3 f5d3 d2d3 e7e6 f3e5 c6e5 f4e5 f8e7 g2g4 h7h6 e1c1 c7c5 e5f6 e7f6"
                                            +"\ninfo depth 12 seldepth 23 score cp 78 nodes 626320 nps 258063 time 2427 multipv 1 pv f3e5 c6e5 d4e5 f6e4 d3e4 d5e4 d2d7 f5d7 e1c1 d7g4 d1d2 g4f5 h2h3 h7h5 g1d1 c7c5 d2d5 f5e6"
                                            +"\ninfo depth 12 seldepth 23 score cp 68 nodes 626320 nps 258063 time 2427 multipv 2 pv e1c1 f5d3 d2d3 f6h5 g2g3 e7e6 f3e5 h5f4 g3f4 c6e5 f4e5 c7c5 c1b1 c5c4"
                                            +"\ninfo depth 12 seldepth 23 score cp 56 nodes 626320 nps 258063 time 2427 multipv 3 pv h2h3 f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6e4 c3e4 d5e4 d3e4 c8d8 e4b7 d7d2 e1f1 d2c2 g2g4"
                                            +"\ninfo depth 12 seldepth 23 score cp 52 nodes 626320 nps 258063 time 2427 multipv 4 pv d3f5 d7f5 f3e5 g7g5 e5c6 g5f4 c6e5 f8h6 e1c1 f5g5 d1e1 c7c5 c1b1 e8g8 e5f3 f4e3 e1e3"
                                            +"\ninfo depth 13 currmove g2g4 currmovenumber 5"
                                            +"\ninfo depth 13 currmove f3g5 currmovenumber 6"
                                            +"\ninfo depth 13 currmove f4e5 currmovenumber 7"
                                            +"\ninfo depth 13 currmove f3h4 currmovenumber 8"
                                            +"\ninfo depth 13 currmove f4g3 currmovenumber 9"
                                            +"\ninfo depth 13 currmove a1d1 currmovenumber 10"
                                            +"\ninfo depth 13 currmove d2e2 currmovenumber 11"
                                            +"\ninfo depth 13 currmove d3c4 currmovenumber 12"
                                            +"\ninfo depth 13 currmove e3e4 currmovenumber 13"
                                            +"\ninfo depth 13 currmove d3b5 currmovenumber 14"
                                            +"\ninfo depth 13 currmove d3e4 currmovenumber 15"
                                            +"\ninfo depth 13 currmove d3e2 currmovenumber 16"
                                            +"\ninfo depth 13 currmove a2a3 currmovenumber 17"
                                            +"\ninfo depth 13 currmove d3f1 currmovenumber 18"
                                            +"\ninfo depth 13 currmove f4d6 currmovenumber 19"
                                            +"\ninfo depth 13 currmove f4g5 currmovenumber 20"
                                            +"\ninfo depth 13 currmove d2c1 currmovenumber 21"
                                            +"\ninfo depth 13 currmove a1c1 currmovenumber 22"
                                            +"\ninfo depth 13 currmove c3a4 currmovenumber 23"
                                            +"\ninfo depth 13 currmove d2d1 currmovenumber 24"
                                            +"\ninfo depth 13 currmove c3e4 currmovenumber 25"
                                            +"\ninfo depth 13 currmove e1f1 currmovenumber 26"
                                            +"\ninfo depth 13 currmove c3b5 currmovenumber 27"
                                            +"\ninfo depth 13 currmove g1h1 currmovenumber 28"
                                            +"\ninfo depth 13 currmove e1d1 currmovenumber 29"
                                            +"\ninfo depth 13 currmove c3d1 currmovenumber 30"
                                            +"\ninfo depth 13 currmove a1b1 currmovenumber 31"
                                            +"\ninfo depth 13 currmove e1e2 currmovenumber 32"
                                            +"\ninfo depth 13 currmove b2b3 currmovenumber 33"
                                            +"\ninfo depth 13 currmove b2b4 currmovenumber 34"
                                            +"\ninfo depth 13 currmove f4h6 currmovenumber 35"
                                            +"\ninfo depth 13 currmove g1f1 currmovenumber 36"
                                            +"\ninfo depth 13 currmove c3b1 currmovenumber 37"
                                            +"\ninfo depth 13 currmove g2g3 currmovenumber 38"
                                            +"\ninfo depth 13 currmove a2a4 currmovenumber 39"
                                            +"\ninfo depth 13 currmove c3e2 currmovenumber 40"
                                            +"\ninfo depth 13 currmove h2h4 currmovenumber 41"
                                            +"\ninfo depth 13 currmove c3d5 currmovenumber 42"
                                            +"\ninfo depth 13 currmove f4c7 currmovenumber 43"
                                            +"\ninfo depth 13 currmove d3a6 currmovenumber 44"
                                            +"\ninfo depth 13 seldepth 23 score cp 88 nodes 785618 nps 257326 time 3053 multipv 1 pv f3e5 c6e5 d4e5 f6e4 d3e4 d5e4 d2d7 f5d7 e1c1 e7e6 c3e4 d7c6 d1d4 f8e7 g1d1 c6d5 h2h3 e8g8 f2f3 f8e8 b2b3 c7c5 d4d5 e6d5 d1d5"
                                            +"\ninfo depth 13 seldepth 23 score cp 66 nodes 785618 nps 257326 time 3053 multipv 2 pv e1c1 f5d3 d2d3 f6h5 f4e5 f7f6 e5g3 e7e6 g3h4 c6b4 d3d2 c7c5 c1b1 f8d6 g2g4 c5d4 f3d4"
                                            +"\ninfo depth 13 seldepth 23 score cp 62 nodes 785618 nps 257326 time 3053 multipv 3 pv h2h3 f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6e4 c3e4 d5e4 d3e4 c8d8 e4b7 h7h6 b7a6"
                                            +"\ninfo depth 13 seldepth 23 score cp 44 upperbound nodes 785618 nps 257326 time 3053 multipv 4 pv d3f5 d7f5 f3e5 c6e5 d4e5 f6e4 c3e4 f5e4 f2f3 e4c4 e1f2 e7e6 d2d3 c4d3 c2d3 f8e7"
                                            +"\ninfo depth 13 currmove d3f5 currmovenumber 4"
                                            +"\ninfo depth 13 currmove g2g4 currmovenumber 5"
                                            +"\ninfo depth 13 currmove f3h4 currmovenumber 6"
                                            +"\ninfo depth 13 currmove f3g5 currmovenumber 7"
                                            +"\ninfo depth 13 currmove f4e5 currmovenumber 8"
                                            +"\ninfo depth 13 currmove a1d1 currmovenumber 9"
                                            +"\ninfo depth 13 currmove f4g3 currmovenumber 10"
                                            +"\ninfo depth 13 currmove d2e2 currmovenumber 11"
                                            +"\ninfo depth 13 currmove d3c4 currmovenumber 12"
                                            +"\ninfo depth 13 currmove d3e4 currmovenumber 13"
                                            +"\ninfo depth 13 currmove d3e2 currmovenumber 14"
                                            +"\ninfo depth 13 currmove e3e4 currmovenumber 15"
                                            +"\ninfo depth 13 currmove d3f1 currmovenumber 16"
                                            +"\ninfo depth 13 currmove d3b5 currmovenumber 17"
                                            +"\ninfo depth 13 currmove f4d6 currmovenumber 18"
                                            +"\ninfo depth 13 currmove a2a3 currmovenumber 19"
                                            +"\ninfo depth 13 currmove a1c1 currmovenumber 20"
                                            +"\ninfo depth 13 currmove f4g5 currmovenumber 21"
                                            +"\ninfo depth 13 currmove c3a4 currmovenumber 22"
                                            +"\ninfo depth 13 currmove d2d1 currmovenumber 23"
                                            +"\ninfo depth 13 currmove c3e4 currmovenumber 24"
                                            +"\ninfo depth 13 currmove e1f1 currmovenumber 25"
                                            +"\ninfo depth 13 currmove c3b5 currmovenumber 26"
                                            +"\ninfo depth 13 currmove d2c1 currmovenumber 27"
                                            +"\ninfo depth 13 currmove e1d1 currmovenumber 28"
                                            +"\ninfo depth 13 currmove c3d1 currmovenumber 29"
                                            +"\ninfo depth 13 currmove e1e2 currmovenumber 30"
                                            +"\ninfo depth 13 currmove b2b3 currmovenumber 31"
                                            +"\ninfo depth 13 currmove g1h1 currmovenumber 32"
                                            +"\ninfo depth 13 currmove a1b1 currmovenumber 33"
                                            +"\ninfo depth 13 currmove b2b4 currmovenumber 34"
                                            +"\ninfo depth 13 currmove f4h6 currmovenumber 35"
                                            +"\ninfo depth 13 currmove g1f1 currmovenumber 36"
                                            +"\ninfo depth 13 currmove c3b1 currmovenumber 37"
                                            +"\ninfo depth 13 currmove g2g3 currmovenumber 38"
                                            +"\ninfo depth 13 currmove a2a4 currmovenumber 39"
                                            +"\ninfo depth 13 currmove c3e2 currmovenumber 40"
                                            +"\ninfo depth 13 currmove h2h4 currmovenumber 41"
                                            +"\ninfo depth 13 currmove c3d5 currmovenumber 42"
                                            +"\ninfo depth 13 currmove f4c7 currmovenumber 43"
                                            +"\ninfo depth 13 currmove d3a6 currmovenumber 44"
                                            +"\ninfo depth 13 seldepth 23 score cp 88 nodes 859452 nps 253900 time 3385 multipv 1 pv f3e5 c6e5 d4e5 f6e4 d3e4 d5e4 d2d7 f5d7 e1c1 e7e6 c3e4 d7c6 d1d4 f8e7 g1d1 c6d5 h2h3 e8g8 f2f3 f8e8 b2b3 c7c5 d4d5 e6d5 d1d5"
                                            +"\ninfo depth 13 seldepth 23 score cp 66 nodes 859452 nps 253900 time 3385 multipv 2 pv e1c1 f5d3 d2d3 f6h5 f4e5 f7f6 e5g3 e7e6 g3h4 c6b4 d3d2 c7c5 c1b1 f8d6 g2g4 c5d4 f3d4"
                                            +"\ninfo depth 13 seldepth 23 score cp 62 nodes 859452 nps 253900 time 3385 multipv 3 pv h2h3 f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6e4 c3e4 d5e4 d3e4 c8d8 e4b7 h7h6 b7a6"
                                            +"\ninfo depth 13 seldepth 23 score cp 36 upperbound nodes 859452 nps 253900 time 3385 multipv 4 pv d3f5 d7f5 f3e5 c6e5 d4e5 f6e4 c3e4 f5e4 f2f3 e4c4 e1f2 e7e6 d2d3 c4d3 c2d3 f8e7"
                                            +"\ninfo depth 13 currmove d3f5 currmovenumber 4"
                                            +"\ninfo depth 13 currmove f3g5 currmovenumber 5"
                                            +"\ninfo depth 13 currmove g2g4 currmovenumber 6"
                                            +"\ninfo depth 13 currmove f3h4 currmovenumber 7"
                                            +"\ninfo depth 13 currmove f4e5 currmovenumber 8"
                                            +"\ninfo depth 13 currmove d3c4 currmovenumber 9"
                                            +"\ninfo depth 13 currmove d3e4 currmovenumber 10"
                                            +"\ninfo depth 13 currmove d3e2 currmovenumber 11"
                                            +"\ninfo depth 13 currmove d3b5 currmovenumber 12"
                                            +"\ninfo depth 13 currmove d3f1 currmovenumber 13"
                                            +"\ninfo depth 13 currmove e3e4 currmovenumber 14"
                                            +"\ninfo depth 13 currmove d2e2 currmovenumber 15"
                                            +"\ninfo depth 13 currmove f4g3 currmovenumber 16"
                                            +"\ninfo depth 13 currmove d2d1 currmovenumber 17"
                                            +"\ninfo depth 13 currmove e1e2 currmovenumber 18"
                                            +"\ninfo depth 13 currmove c3e4 currmovenumber 19"
                                            +"\ninfo depth 13 currmove c3b5 currmovenumber 20"
                                            +"\ninfo depth 13 currmove a1d1 currmovenumber 21"
                                            +"\ninfo depth 13 currmove f4d6 currmovenumber 22"
                                            +"\ninfo depth 13 currmove f4g5 currmovenumber 23"
                                            +"\ninfo depth 13 currmove a2a3 currmovenumber 24"
                                            +"\ninfo depth 13 currmove h2h4 currmovenumber 25"
                                            +"\ninfo depth 13 currmove e1f1 currmovenumber 26"
                                            +"\ninfo depth 13 currmove g1f1 currmovenumber 27"
                                            +"\ninfo depth 13 currmove f4h6 currmovenumber 28"
                                            +"\ninfo depth 13 currmove d2c1 currmovenumber 29"
                                            +"\ninfo depth 13 currmove b2b3 currmovenumber 30"
                                            +"\ninfo depth 13 currmove c3a4 currmovenumber 31"
                                            +"\ninfo depth 13 currmove e1d1 currmovenumber 32"
                                            +"\ninfo depth 13 currmove c3b1 currmovenumber 33"
                                            +"\ninfo depth 13 currmove c3d1 currmovenumber 34"
                                            +"\ninfo depth 13 currmove a1b1 currmovenumber 35"
                                            +"\ninfo depth 13 currmove c3e2 currmovenumber 36"
                                            +"\ninfo depth 13 currmove a1c1 currmovenumber 37"
                                            +"\ninfo depth 13 currmove g1h1 currmovenumber 38"
                                            +"\ninfo depth 13 currmove g2g3 currmovenumber 39"
                                            +"\ninfo depth 13 currmove b2b4 currmovenumber 40"
                                            +"\ninfo depth 13 currmove a2a4 currmovenumber 41"
                                            +"\ninfo depth 13 currmove c3d5 currmovenumber 42"
                                            +"\ninfo depth 13 currmove f4c7 currmovenumber 43"
                                            +"\ninfo depth 13 currmove d3a6 currmovenumber 44"
                                            +"\ninfo depth 13 seldepth 23 score cp 88 nodes 1046616 nps 244080 time 4288 multipv 1 pv f3e5 c6e5 d4e5 f6e4 d3e4 d5e4 d2d7 f5d7 e1c1 e7e6 c3e4 d7c6 d1d4 f8e7 g1d1 c6d5 h2h3 e8g8 f2f3 f8e8 b2b3 c7c5 d4d5 e6d5 d1d5"
                                            +"\ninfo depth 13 seldepth 23 score cp 66 nodes 1046616 nps 244080 time 4288 multipv 2 pv e1c1 f5d3 d2d3 f6h5 f4e5 f7f6 e5g3 e7e6 g3h4 c6b4 d3d2 c7c5 c1b1 f8d6 g2g4 c5d4 f3d4"
                                            +"\ninfo depth 13 seldepth 23 score cp 62 nodes 1046616 nps 244080 time 4288 multipv 3 pv h2h3 f5d3 d2d3 e7e6 f3e5 c6e5 d4e5 f6e4 c3e4 d5e4 d3e4 c8d8 e4b7 h7h6 b7a6"
                                            +"\ninfo depth 13 seldepth 23 score cp 50 nodes 1046616 nps 244080 time 4288 multipv 4 pv a2a3 f5d3 d2d3 e7e6 g2g4 f8d6 f3e5 d6e5 f4e5 c6e5 d4e5 f6g8 e1c1 g8e7"
                                            +"\ninfo depth 14 currmove f3e5 currmovenumber 1v"
                                            +"\ninfo nodes 1098339 time 4509"
                                            +"\nbestmove f3e5 ponder c6e5";
        slach::EngineInterface interface;
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 w Qk - 3 8";//test_position_3 but white to move
        interface.SetPositionToInternalChessBoard(test_position);

        interface.SetNumberOfLinesToBeShown(4u);//asking stockfish to display 4 lines
        interface.ParseWholeEngineOutput(test_string);
        TS_ASSERT_EQUALS(interface.mLatestDepths.size(), 4u);
        TS_ASSERT_EQUALS(interface.mLatestDepths[3], 13u);
        TS_ASSERT_EQUALS(interface.mLatestDepths[2], 13u);
        TS_ASSERT_EQUALS(interface.mLatestDepths[1], 13u);
        TS_ASSERT_EQUALS(interface.mLatestDepths[0], 13u);

        TS_ASSERT_EQUALS(interface.mLatestRootMoves.size(), 4u);
        TS_ASSERT_EQUALS(interface.mLatestRootMoves[3], "Ne5");
        TS_ASSERT_EQUALS(interface.mLatestRootMoves[2], "O-O-O");
        TS_ASSERT_EQUALS(interface.mLatestRootMoves[1], "h3");
        TS_ASSERT_EQUALS(interface.mLatestRootMoves[0], "a3");

        TS_ASSERT_EQUALS(interface.mLatestScores.size(), 4u);
        TS_ASSERT_DELTA(interface.mLatestScores[3], 0.88, 1e-3);
        TS_ASSERT_DELTA(interface.mLatestScores[2], 0.66,1e-3);
        TS_ASSERT_DELTA(interface.mLatestScores[1], 0.62, 1e-3);
        TS_ASSERT_DELTA(interface.mLatestScores[0], 0.50, 1e-3);

        TS_ASSERT_EQUALS(interface.mLatestLines.size(), 4u);
        TS_ASSERT_EQUALS(interface.mLatestLines[3], "Ne5 Nxe5 dxe5 Ne4 Bxe4 dxe4 Qxd7+ Bxd7 O-O-O e6 Nxe4 Bc6 Rd4 Be7 Rgd1 Bd5 h3 O-O f3 Rfe8 b3 c5 Rxd5 exd5 Rxd5 ");
        TS_ASSERT_EQUALS(interface.mLatestLines[2], "O-O-O Bxd3 Qxd3 Nh5 Be5 f6 Bg3 e6 Bh4 Nb4 Qd2 c5 Kb1 Bd6 g4 cxd4 Nxd4 ");
        TS_ASSERT_EQUALS(interface.mLatestLines[1], "h3 Bxd3 Qxd3 e6 Ne5 Nxe5 dxe5 Ne4 Nxe4 dxe4 Qxe4 Rd8 Qxb7 h6 Qxa6 ");
        TS_ASSERT_EQUALS(interface.mLatestLines[0], "a3 Bxd3 Qxd3 e6 g4 Bd6 Ne5 Bxe5 Bxe5 Nxe5 dxe5 Ng8 O-O-O Ne7 ");

        int depth;
        double score;
        std::string best_move;
        interface.GetLatestBestScoreAndDepth(score,depth, best_move);
        TS_ASSERT_EQUALS(depth, 13);
        TS_ASSERT_DELTA(score, 0.88, 0.01);
        TS_ASSERT_EQUALS(best_move, "Ne5");
    }
};
#endif

