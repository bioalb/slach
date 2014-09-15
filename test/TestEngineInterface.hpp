#ifndef TESTENGINEINTERFACE_HPP_
#define TESTENGINEINTERFACE_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cassert>
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
        std::cout<<std::endl<<"*******Starting analysis. I will start with infinite analysis and stop after 5 seconds*******"<<std::endl;
        interface.LaunchEngine();
        interface.StartAnalsyingPosition(p_position);

        std::time_t time_now = 0;
        std::time_t start_time = 0;
        std::time(&start_time);

        while (std::difftime(time_now,start_time) < 5.0)
        {
            std::time(&time_now);
        }
        interface.StopEngine();
        interface.QuitEngine();
        auto output = interface.GetLatestEngineOutput();
        TS_ASSERT_EQUALS(output.size(), 1u);
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
        interface.LaunchEngine();
        interface.StartAnalsyingPosition(p_position, 3.0);

        auto output = interface.GetLatestEngineOutput();
        TS_ASSERT_EQUALS(output.size(), 4u);
        //interface.StopEngine();
        //interface.QuitEngine();
        delete p_board;
        delete p_position;
    }

    void xTestStopMakeAMoveAndRestart()
    {
        slach::ChessBoard* p_board = new slach::ChessBoard();
        p_board->SetupChessBoard();
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        slach::Position* p_position = new slach::Position();
        std::vector<slach::Square* > squares = p_board->GetSquares();
        p_position->SetFromFen(test_position, squares);

        slach::EngineInterface interface;
        interface.LaunchEngine();

        std::cout<<std::endl<<"*******"<<"Starting analysis for 3 seconds, stop make a move and restart"<<"*******"<<std::endl;
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
        auto output = interface.GetLatestEngineOutput();
        TS_ASSERT_EQUALS(output.size(), 4u);
        interface.QuitEngine();
        delete p_board;
        delete p_position;
    }

    void xTestStartInfiniteMultiplePV()
    {
        slach::ChessBoard* p_board = new slach::ChessBoard();
        p_board->SetupChessBoard();
        std::string test_position = "2r1kb1r/1ppqpppp/p1n2n2/3p1b2/3P1B2/2NBPN2/PPPQ1PPP/R3K1R1 b Qk - 3 8";
        slach::Position* p_position = new slach::Position();
        std::vector<slach::Square* > squares = p_board->GetSquares();
        p_position->SetFromFen(test_position, squares);

        slach::EngineInterface interface;
        interface.LaunchEngine();

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
        auto output = interface.GetLatestEngineOutput();
        TS_ASSERT_EQUALS(output.size(), 4u);

        delete p_board;
        delete p_position;

    }

    void xTestMateInOneThreePlysOutput()
    {
        slach::ChessBoard* p_board = new slach::ChessBoard();
        p_board->SetupChessBoard();
        std::string fools_mate_in_one = "rnbqkbnr/ppppp2p/8/5pp1/4P3/3P4/PPP2PPP/RNBQKBNR w KQkq g6 0 3";
        slach::Position* p_position = new slach::Position();
        std::vector<slach::Square* > squares = p_board->GetSquares();
        p_position->SetFromFen(fools_mate_in_one, squares);

        slach::EngineInterface interface;
        interface.LaunchEngine();
        interface.SetNumberOfLinesToBeShown(3);
        std::cout<<std::endl<<"*******"<<"Starting analysis of Mate in one"<<"*******"<<std::endl;
        interface.StartAnalsyingPosition(p_position, 3.0);
        std::cout<<std::endl<<"Done analysing for 3 seconds the fools mate, engine output follows"<<std::endl;
        auto output = interface.GetLatestEngineOutput();
        TS_ASSERT_EQUALS(output.size(), 3u);
        TS_ASSERT_EQUALS(output[0], "Depth = 1; score = 100.00; Qh5+ mate\n");
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
        interface.LaunchEngine();
        std::cout<<std::endl<<"*******"<<"Starting analysis of fools mate"<<"*******"<<std::endl;
        interface.StartAnalsyingPosition(p_position, 3.0);
        std::cout<<std::endl<<"Done analysing for 3 seconds the fools mate, engine output follows"<<std::endl;

        auto output = interface.GetLatestEngineOutput();
        TS_ASSERT_EQUALS(output.size(), 1u);
        TS_ASSERT_EQUALS(output[0], "Depth = 0; score = 0.00;\n");

        delete p_board;
        delete p_position;
    }

    void xTestCheckMateMultplepv()
    {
        slach::ChessBoard* p_board = new slach::ChessBoard();
        p_board->SetupChessBoard();
        std::string fools_mate = "rnbqkbnr/ppppp2p/8/5ppQ/4P3/3P4/PPP2PPP/RNB1KBNR b KQkq - 1 3";
        slach::Position* p_position = new slach::Position();
        std::vector<slach::Square* > squares = p_board->GetSquares();
        p_position->SetFromFen(fools_mate, squares);

        slach::EngineInterface interface;
        interface.LaunchEngine();
        interface.SetNumberOfLinesToBeShown(3);
        std::cout<<std::endl<<"*******"<<"Starting analysis of fools mate, multiple pv"<<"*******"<<std::endl;
        interface.StartAnalsyingPosition(p_position, 3.0);
        std::cout<<std::endl<<"Done analysing for 3 seconds the fools mate, engine output follows"<<std::endl;


        auto output = interface.GetLatestEngineOutput();
        TS_ASSERT_EQUALS(output.size(), 3u);
        TS_ASSERT_EQUALS(output[0], "Depth = 0; score = 0.00;\n");
        TS_ASSERT_EQUALS(output[1], "Depth = 0; score = 0.00;\n");
        TS_ASSERT_EQUALS(output[2], "Depth = 0; score = 0.00;\n");

        delete p_board;
        delete p_position;
    }


};
#endif

