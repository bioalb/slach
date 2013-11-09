#ifndef TESTGAME_HPP_
#define TESTGAME_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Game.hpp"
#include "ChessBoard.hpp"

/**
 * Test suite to Test the game class
 */

class TestGame : public CxxTest::TestSuite
{
public:


    void TestBasicMove()
    {
        slach::Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        slach::Square sq1;
        sq1.SetFile('a');
        sq1.SetRank('1');
        sq1.SetIndexFromA1(0u);
        sq1.SetPieceOnThisSquare(slach::BLACK_BISHOP);

        slach::Square sq2;
        sq2.SetFile('e');
        sq2.SetRank('4');
        sq2.SetIndexFromA1(28u);
        sq2.SetPieceOnThisSquare(slach::NO_PIECE);

        slach::Move bishop_e4_move(&sq1, &sq2);

        gm.AddMove(bishop_e4_move);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetOrigin()->GetFile(),'a');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetOrigin()->GetRank(),'1');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetDestination()->GetFile(),'e');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetDestination()->GetRank(),'4');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "Be4");
    }

    void TestPawnMove()
    {
        slach::Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        slach::Square sq1;
        sq1.SetFile('a');
        sq1.SetRank('2');
        sq1.SetIndexFromA1(8u);
        sq1.SetPieceOnThisSquare(slach::WHITE_PAWN);

        slach::Square sq2;
        sq2.SetFile('a');
        sq2.SetRank('4');
        sq2.SetIndexFromA1(24u);
        sq2.SetPieceOnThisSquare(slach::NO_PIECE);

        slach::Move a4_move(&sq1, &sq2);

        gm.AddMove(a4_move);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetOrigin()->GetFile(),'a');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetOrigin()->GetRank(),'2');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetDestination()->GetFile(),'a');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetDestination()->GetRank(),'4');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "a4");
    }

    void TestCapture()
    {
        slach::Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        slach::Square sq1;
        sq1.SetFile('a');
        sq1.SetRank('2');
        sq1.SetIndexFromA1(8u);
        sq1.SetPieceOnThisSquare(slach::BLACK_QUEEN);

        slach::Square sq2;
        sq2.SetFile('a');
        sq2.SetRank('4');
        sq2.SetIndexFromA1(24u);
        sq2.SetPieceOnThisSquare(slach::WHITE_BISHOP);

        slach::Move queen_takes_bishop(&sq1, &sq2);

        gm.AddMove(queen_takes_bishop);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetOrigin()->GetFile(),'a');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetOrigin()->GetRank(),'2');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetDestination()->GetFile(),'a');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetDestination()->GetRank(),'4');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "Qxa4");
    }

    void TestPawnCapture()
    {
        slach::Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        slach::Square sq1;
        sq1.SetFile('a');
        sq1.SetRank('2');
        sq1.SetIndexFromA1(8u);
        sq1.SetIndexFromA1(8u);
        sq1.SetPieceOnThisSquare(slach::WHITE_PAWN);

        slach::Square sq2;
        sq2.SetFile('b');
        sq2.SetRank('3');
        sq2.SetIndexFromA1(17u);
        sq2.SetPieceOnThisSquare(slach::WHITE_BISHOP);

        slach::Move pawn_takes_bishop(&sq1,&sq2);

        gm.AddMove(pawn_takes_bishop);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetOrigin()->GetFile(),'a');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetOrigin()->GetRank(),'2');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetDestination()->GetFile(),'b');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetDestination()->GetRank(),'3');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "axb3");
    }

    void TestCastleKingSide()
    {
        slach::Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        slach::Square sq1;
        sq1.SetFile('e');
        sq1.SetRank('1');
        sq1.SetIndexFromA1(4u);
        sq1.SetPieceOnThisSquare(slach::WHITE_KING);

        slach::Square sq2;
        sq2.SetFile('g');
        sq2.SetRank('1');
        sq2.SetIndexFromA1(6u);
        sq2.SetPieceOnThisSquare(slach::NO_PIECE);

        slach::Move castle_white(&sq1,&sq2);

        gm.AddMove(castle_white);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetOrigin()->GetFile(),'e');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetOrigin()->GetRank(),'1');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetDestination()->GetFile(),'g');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetDestination()->GetRank(),'1');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "O-O");

        slach::Square sq3;
        sq3.SetFile('e');
        sq3.SetRank('8');
        sq3.SetIndexFromA1(60u);
        sq3.SetPieceOnThisSquare(slach::BLACK_KING);

        slach::Square sq4;
        sq4.SetFile('g');
        sq4.SetRank('8');
        sq4.SetIndexFromA1(62u);
        sq4.SetPieceOnThisSquare(slach::NO_PIECE);

        slach::Move castle_black(&sq3, &sq4);

        gm.AddMove(castle_black);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 2u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[1].GetOrigin()->GetFile(),'e');
        TS_ASSERT_EQUALS(gm.GetMoveList()[1].GetOrigin()->GetRank(),'8');
        TS_ASSERT_EQUALS(gm.GetMoveList()[1].GetDestination()->GetFile(),'g');
        TS_ASSERT_EQUALS(gm.GetMoveList()[1].GetDestination()->GetRank(),'8');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 2u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[1], "O-O");

        //now add another move (the same as before)
        gm.AddMove(castle_white);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 3u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[2].GetOrigin()->GetFile(),'e');
        TS_ASSERT_EQUALS(gm.GetMoveList()[2].GetOrigin()->GetRank(),'1');
        TS_ASSERT_EQUALS(gm.GetMoveList()[2].GetDestination()->GetFile(),'g');
        TS_ASSERT_EQUALS(gm.GetMoveList()[2].GetDestination()->GetRank(),'1');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 3u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[2], "O-O");

    }

    void TestCastleQueenSide()
    {
        slach::Game gm;
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 0u);

        slach::Square sq1;
        sq1.SetFile('e');
        sq1.SetRank('1');
        sq1.SetIndexFromA1(4u);
        sq1.SetPieceOnThisSquare(slach::WHITE_KING);

        slach::Square sq2;
        sq2.SetFile('c');
        sq2.SetRank('1');
        sq2.SetIndexFromA1(2u);
        sq2.SetPieceOnThisSquare(slach::NO_PIECE);

        slach::Move castle_white(&sq1, &sq2);

        gm.AddMove(castle_white);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetOrigin()->GetFile(),'e');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetOrigin()->GetRank(),'1');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetDestination()->GetFile(),'c');
        TS_ASSERT_EQUALS(gm.GetMoveList()[0].GetDestination()->GetRank(),'1');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 1u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[0], "O-O-O");

        slach::Square sq3;
        sq3.SetFile('e');
        sq3.SetRank('8');
        sq3.SetIndexFromA1(60u);
        sq3.SetPieceOnThisSquare(slach::BLACK_KING);

        slach::Square sq4;
        sq4.SetFile('c');
        sq4.SetRank('8');
        sq4.SetIndexFromA1(58u);
        sq4.SetPieceOnThisSquare(slach::NO_PIECE);

        slach::Move castle_black(&sq3,&sq4);

        gm.AddMove(castle_black);
        TS_ASSERT_EQUALS(gm.GetMoveList().size(), 2u);
        TS_ASSERT_EQUALS(gm.GetMoveList()[1].GetOrigin()->GetFile(),'e');
        TS_ASSERT_EQUALS(gm.GetMoveList()[1].GetOrigin()->GetRank(),'8');
        TS_ASSERT_EQUALS(gm.GetMoveList()[1].GetDestination()->GetFile(),'c');
        TS_ASSERT_EQUALS(gm.GetMoveList()[1].GetDestination()->GetRank(),'8');

        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat().size(), 2u);
        TS_ASSERT_EQUALS(gm.GetMoveListAlgebraicFormat()[1], "O-O-O");
    }

    void TestFetchFromlist()
    {
        std::string initial = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        std::string after_d2_d4 = "rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq d3 0 1";
        std::string after_e7_e5 = "rnbqkbnr/pppp1ppp/8/4p3/3P4/8/PPP1PPPP/RNBQKBNR w KQkq e6 0 2";
        std::string after_d4_takes_e5 = "rnbqkbnr/pppp1ppp/8/4P3/8/8/PPP1PPPP/RNBQKBNR b KQkq - 0 2";
        std::string after_bishop_b4_check = "rnbqk1nr/pppp1ppp/8/4P3/1b6/8/PPP1PPPP/RNBQKBNR w KQkq - 1 3";
        std::string after_c2c3 =  "rnbqk1nr/pppp1ppp/8/4P3/1b6/2P5/PP2PPPP/RNBQKBNR b KQkq - 0 3";

        slach::Game my_game;

        //fen list is of zero length. Check that we return an empty string
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(4u,slach::WHITE), "");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(4u,slach::BLACK), "");

        my_game.AddPosition(initial);

        //fen list is of length 1. Check that we return the only string, no matter what
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(1u,slach::WHITE), initial);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(1u,slach::BLACK), initial);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(2u,slach::WHITE), initial);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(2u,slach::BLACK), initial);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(22u,slach::WHITE), initial);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(22u,slach::BLACK), initial);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(-22,slach::WHITE), initial);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(-22,slach::BLACK), initial);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(0,slach::WHITE), initial);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(0,slach::BLACK), initial);

        my_game.AddPosition(after_d2_d4);
        my_game.AddPosition(after_e7_e5);
        my_game.AddPosition(after_d4_takes_e5);
        my_game.AddPosition(after_bishop_b4_check);

        //over the size
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(4u,slach::WHITE), after_bishop_b4_check);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(4u,slach::BLACK), after_bishop_b4_check);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(24u,slach::WHITE), after_bishop_b4_check);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(24u,slach::BLACK), after_bishop_b4_check);


        my_game.AddPosition(after_c2c3);

        //cover the weird case when you pas sin 0...behaves like a one.
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(0u,slach::WHITE), initial);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(0u,slach::BLACK), initial);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(1u,slach::WHITE), initial);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(1u,slach::BLACK), after_d2_d4);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(2u,slach::WHITE), after_e7_e5);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(2u,slach::BLACK), after_d4_takes_e5);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(3u,slach::WHITE), after_bishop_b4_check);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(3u,slach::BLACK), after_c2c3);

        //over the size last was black to move
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(4u,slach::WHITE), after_c2c3);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(4u,slach::BLACK), after_c2c3);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(24u,slach::WHITE), after_c2c3);
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(24u,slach::BLACK), after_c2c3);
    }

    void TestReadFromPgnOneGame()
    {
        //read the whole file into string
        std::ifstream in("test/data/pgn/one_game_ok_draw.pgn");
        std::string game_string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        slach::Game my_game;
        slach::PgnValidity valid = my_game.LoadFromPgnString(game_string, squares);

        TS_ASSERT_EQUALS(valid, slach::VALID_PGN);
        TS_ASSERT_EQUALS(my_game.GetSevenTagRoster().mData[0], "7th Kings Tournament");
        TS_ASSERT_EQUALS(my_game.GetSevenTagRoster().mData[1], "Bucharest ROU");
        TS_ASSERT_EQUALS(my_game.GetSevenTagRoster().mData[2], "2013.10.07");
        TS_ASSERT_EQUALS(my_game.GetSevenTagRoster().mData[3], "1.1");
        TS_ASSERT_EQUALS(my_game.GetSevenTagRoster().mData[4], "Radjabov, Teimour");
        TS_ASSERT_EQUALS(my_game.GetSevenTagRoster().mData[5], "Ponomariov, Ruslan");
        TS_ASSERT_EQUALS(my_game.GetSevenTagRoster().mData[6], "1/2-1/2");

        std::vector<slach::Move> move_list = my_game.GetMoveList();
        std::vector<std::string> move_list_san = my_game.GetMoveListAlgebraicFormat();
        TS_ASSERT_EQUALS(move_list.size(), 61u);
        TS_ASSERT_EQUALS(move_list_san.size(), 61u);

        TS_ASSERT_EQUALS(move_list[0].GetOrigin()->GetFile(), 'd');
        TS_ASSERT_EQUALS(move_list[0].GetOrigin()->GetIndexFromA1(), 11u);
        TS_ASSERT_EQUALS(move_list[0].GetOrigin()->GetRank(), '2');
        TS_ASSERT_EQUALS(move_list[0].GetDestination()->GetFile(), 'd');
        TS_ASSERT_EQUALS(move_list[0].GetDestination()->GetRank(), '4');

        TS_ASSERT_EQUALS(move_list[1].GetOrigin()->GetFile(), 'd');
        TS_ASSERT_EQUALS(move_list[1].GetOrigin()->GetRank(), '7');
        TS_ASSERT_EQUALS(move_list[1].GetDestination()->GetFile(), 'd');
        TS_ASSERT_EQUALS(move_list[1].GetDestination()->GetRank(), '5');

        TS_ASSERT_EQUALS(move_list[2].GetOrigin()->GetFile(), 'c');
        TS_ASSERT_EQUALS(move_list[2].GetOrigin()->GetRank(), '2');
        TS_ASSERT_EQUALS(move_list[2].GetDestination()->GetFile(), 'c');
        TS_ASSERT_EQUALS(move_list[2].GetDestination()->GetRank(), '4');

        TS_ASSERT_EQUALS(move_list[3].GetOrigin()->GetFile(), 'c');
        TS_ASSERT_EQUALS(move_list[3].GetOrigin()->GetRank(), '7');
        TS_ASSERT_EQUALS(move_list[3].GetDestination()->GetFile(), 'c');
        TS_ASSERT_EQUALS(move_list[3].GetDestination()->GetRank(), '6');

        TS_ASSERT_EQUALS(move_list[60].GetOrigin()->GetFile(), 'g');
        TS_ASSERT_EQUALS(move_list[60].GetOrigin()->GetRank(), '3');
        TS_ASSERT_EQUALS(move_list[60].GetDestination()->GetFile(), 'f');
        TS_ASSERT_EQUALS(move_list[60].GetDestination()->GetRank(), '4');

        TS_ASSERT_EQUALS(my_game.FetchFromFenList(1, slach::WHITE), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(1, slach::BLACK), "rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq d3 0 1");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(2, slach::WHITE), "rnbqkbnr/ppp1pppp/8/3p4/3P4/8/PPP1PPPP/RNBQKBNR w KQkq d6 0 2");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(2, slach::BLACK), "rnbqkbnr/ppp1pppp/8/3p4/2PP4/8/PP2PPPP/RNBQKBNR b KQkq c3 0 2");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(3, slach::WHITE), "rnbqkbnr/pp2pppp/2p5/3p4/2PP4/8/PP2PPPP/RNBQKBNR w KQkq - 0 3");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(3, slach::BLACK), "rnbqkbnr/pp2pppp/2p5/3p4/2PP4/5N2/PP2PPPP/RNBQKB1R b KQkq - 1 3");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(4, slach::WHITE), "rnbqkb1r/pp2pppp/2p2n2/3p4/2PP4/5N2/PP2PPPP/RNBQKB1R w KQkq - 2 4");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(4, slach::BLACK), "rnbqkb1r/pp2pppp/2p2n2/3p4/2PP4/2N2N2/PP2PPPP/R1BQKB1R b KQkq - 3 4");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(5, slach::WHITE), "rnbqkb1r/pp3ppp/2p1pn2/3p4/2PP4/2N2N2/PP2PPPP/R1BQKB1R w KQkq - 0 5");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(5, slach::BLACK), "rnbqkb1r/pp3ppp/2p1pn2/3p2B1/2PP4/2N2N2/PP2PPPP/R2QKB1R b KQkq - 1 5");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(6, slach::WHITE), "r1bqkb1r/pp1n1ppp/2p1pn2/3p2B1/2PP4/2N2N2/PP2PPPP/R2QKB1R w KQkq - 2 6");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(6, slach::BLACK), "r1bqkb1r/pp1n1ppp/2p1pn2/3P2B1/3P4/2N2N2/PP2PPPP/R2QKB1R b KQkq - 0 6");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(7, slach::WHITE), "r1bqkb1r/pp1n1ppp/2p2n2/3p2B1/3P4/2N2N2/PP2PPPP/R2QKB1R w KQkq - 0 7");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(7, slach::BLACK), "r1bqkb1r/pp1n1ppp/2p2n2/3p2B1/3P4/2N1PN2/PP3PPP/R2QKB1R b KQkq - 0 7");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(8, slach::WHITE), "r1bqk2r/pp1nbppp/2p2n2/3p2B1/3P4/2N1PN2/PP3PPP/R2QKB1R w KQkq - 1 8");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(8, slach::BLACK), "r1bqk2r/pp1nbppp/2p2n2/3p2B1/3P4/2N1PN2/PPQ2PPP/R3KB1R b KQkq - 2 8");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(9, slach::WHITE), "r1bqk2r/pp1nbppp/2p5/3p2Bn/3P4/2N1PN2/PPQ2PPP/R3KB1R w KQkq - 3 9");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(9, slach::BLACK), "r1bqk2r/pp1nBppp/2p5/3p3n/3P4/2N1PN2/PPQ2PPP/R3KB1R b KQkq - 0 9");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(10, slach::WHITE), "r1b1k2r/pp1nqppp/2p5/3p3n/3P4/2N1PN2/PPQ2PPP/R3KB1R w KQkq - 0 10");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(10, slach::BLACK), "r1b1k2r/pp1nqppp/2p5/3p3n/3P4/2N1PN2/PPQ1BPPP/R3K2R b KQkq - 1 10");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(11, slach::WHITE), "r1b1k2r/pp1nqp1p/2p3p1/3p3n/3P4/2N1PN2/PPQ1BPPP/R3K2R w KQkq - 0 11");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(11, slach::BLACK), "r1b1k2r/pp1nqp1p/2p3p1/3p3n/3P4/2N1PN2/PPQ1BPPP/R4RK1 b kq - 1 11");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(12, slach::WHITE), "r1b2rk1/pp1nqp1p/2p3p1/3p3n/3P4/2N1PN2/PPQ1BPPP/R4RK1 w - - 2 12");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(12, slach::BLACK), "r1b2rk1/pp1nqp1p/2p3p1/3p3n/3P4/2N1PN2/PPQ1BPPP/RR4K1 b - - 3 12");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(13, slach::WHITE), "r1b2rk1/pp2qp1p/1np3p1/3p3n/3P4/2N1PN2/PPQ1BPPP/RR4K1 w - - 4 13");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(13, slach::BLACK), "r1b2rk1/pp2qp1p/1np3p1/3p3n/3P4/1QN1PN2/PP2BPPP/RR4K1 b - - 5 13");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(14, slach::WHITE), "r4rk1/pp2qp1p/1np3p1/3p1b1n/3P4/1QN1PN2/PP2BPPP/RR4K1 w - - 6 14");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(14, slach::BLACK), "r4rk1/pp2qp1p/1np3p1/3p1b1n/3P4/1QN1PN2/PP2BPPP/R1R3K1 b - - 7 14");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(15, slach::WHITE), "r4rk1/pp2qp1p/1np2np1/3p1b2/3P4/1QN1PN2/PP2BPPP/R1R3K1 w - - 8 15");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(15, slach::BLACK), "r4rk1/pp2qp1p/1np2np1/3p1b2/P2P4/1QN1PN2/1P2BPPP/R1R3K1 b - a3 0 15");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(16, slach::WHITE), "r1n2rk1/pp2qp1p/2p2np1/3p1b2/P2P4/1QN1PN2/1P2BPPP/R1R3K1 w - - 1 16");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(16, slach::BLACK), "r1n2rk1/pp2qp1p/2p2np1/3p1b2/P2P4/Q1N1PN2/1P2BPPP/R1R3K1 b - - 2 16");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(17, slach::WHITE), "r1n2rk1/1p2qp1p/2p2np1/p2p1b2/P2P4/Q1N1PN2/1P2BPPP/R1R3K1 w - a6 0 17");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(17, slach::BLACK), "r1n2rk1/1p2Qp1p/2p2np1/p2p1b2/P2P4/2N1PN2/1P2BPPP/R1R3K1 b - - 0 17");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(18, slach::WHITE), "r4rk1/1p2np1p/2p2np1/p2p1b2/P2P4/2N1PN2/1P2BPPP/R1R3K1 w - - 0 18");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(18, slach::BLACK), "r4rk1/1p2np1p/2p2np1/p2p1b2/P2P4/1PN1PN2/4BPPP/R1R3K1 b - - 0 18");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(19, slach::WHITE), "r1n2rk1/1p3p1p/2p2np1/p2p1b2/P2P4/1PN1PN2/4BPPP/R1R3K1 w - - 1 19");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(19, slach::BLACK), "r1n2rk1/1p3p1p/2p2np1/p2pNb2/P2P4/1PN1P3/4BPPP/R1R3K1 b - - 2 19");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(20, slach::WHITE), "r1n2rk1/1p1n1p1p/2p3p1/p2pNb2/P2P4/1PN1P3/4BPPP/R1R3K1 w - - 3 20");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(20, slach::BLACK), "r1n2rk1/1p1N1p1p/2p3p1/p2p1b2/P2P4/1PN1P3/4BPPP/R1R3K1 b - - 0 20");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(21, slach::WHITE), "r1n2rk1/1p1b1p1p/2p3p1/p2p4/P2P4/1PN1P3/4BPPP/R1R3K1 w - - 0 21");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(21, slach::BLACK), "r1n2rk1/1p1b1p1p/2p3p1/p2p4/P2P4/1PN1P3/4BPPP/1RR3K1 b - - 1 21");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(22, slach::WHITE), "r4rk1/1p1b1p1p/2pn2p1/p2p4/P2P4/1PN1P3/4BPPP/1RR3K1 w - - 2 22");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(22, slach::BLACK), "r4rk1/1p1b1p1p/2pn2p1/p2p4/PP1P4/2N1P3/4BPPP/1RR3K1 b - - 0 22");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(23, slach::WHITE), "r4rk1/1p1b1p1p/2pn2p1/3p4/Pp1P4/2N1P3/4BPPP/1RR3K1 w - - 0 23");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(23, slach::BLACK), "r4rk1/1p1b1p1p/2pn2p1/3p4/PR1P4/2N1P3/4BPPP/2R3K1 b - - 0 23");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(24, slach::WHITE), "5rk1/1p1b1p1p/2pn2p1/r2p4/PR1P4/2N1P3/4BPPP/2R3K1 w - - 1 24");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(24, slach::BLACK), "5rk1/1p1b1p1p/1Rpn2p1/r2p4/P2P4/2N1P3/4BPPP/2R3K1 b - - 2 24");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(25, slach::WHITE), "r5k1/1p1b1p1p/1Rpn2p1/r2p4/P2P4/2N1P3/4BPPP/2R3K1 w - - 3 25");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(25, slach::BLACK), "r5k1/1p1b1p1p/1Rpn2p1/r2p4/P2P4/2N1PP2/4B1PP/2R3K1 b - - 0 25");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(26, slach::WHITE), "r5k1/1p1b3p/1Rpn2p1/r2p1p2/P2P4/2N1PP2/4B1PP/2R3K1 w - f6 0 26");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(26, slach::BLACK), "r5k1/1p1b3p/1Rpn2p1/r2p1p2/P2P4/2N1PP2/4BKPP/2R5 b - - 1 26");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(27, slach::WHITE), "r7/1p1b1k1p/1Rpn2p1/r2p1p2/P2P4/2N1PP2/4BKPP/2R5 w - - 2 27");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(27, slach::BLACK), "r7/1p1b1k1p/1Rpn2p1/r2p1p2/P2P4/2NBPP2/5KPP/2R5 b - - 3 27");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(28, slach::WHITE), "r7/1p1bk2p/1Rpn2p1/r2p1p2/P2P4/2NBPP2/5KPP/2R5 w - - 4 28");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(28, slach::BLACK), "r7/1p1bk2p/1Rpn2p1/r2p1p2/P2P3P/2NBPP2/5KP1/2R5 b - h3 0 28");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(29, slach::WHITE), "r7/1p2k2p/1Rpnb1p1/r2p1p2/P2P3P/2NBPP2/5KP1/2R5 w - - 1 29");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(29, slach::BLACK), "r7/1p2k2p/1Rpnb1p1/r2p1p2/P2P3P/2NBPP2/5KP1/1R6 b - - 2 29");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(30, slach::WHITE), "8/rp2k2p/1Rpnb1p1/r2p1p2/P2P3P/2NBPP2/5KP1/1R6 w - - 3 30");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(30, slach::BLACK), "8/rp2k2p/1Rpnb1p1/r2p1p2/P2P3P/2NBPPK1/6P1/1R6 b - - 4 30");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(31, slach::WHITE), "8/rp2k3/1Rpnb1pp/r2p1p2/P2P3P/2NBPPK1/6P1/1R6 w - - 0 31");
        TS_ASSERT_EQUALS(my_game.FetchFromFenList(31, slach::BLACK), "8/rp2k3/1Rpnb1pp/r2p1p2/P2P1K1P/2NBPP2/6P1/1R6 b - - 1 31");

        TS_ASSERT_EQUALS(my_game.GetFenList().size(), 62);
        TS_ASSERT_EQUALS(my_game.GetFenList()[0], "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        TS_ASSERT_EQUALS(my_game.GetFenList()[1], "rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq d3 0 1");
        TS_ASSERT_EQUALS(my_game.GetFenList()[2], "rnbqkbnr/ppp1pppp/8/3p4/3P4/8/PPP1PPPP/RNBQKBNR w KQkq d6 0 2");
        TS_ASSERT_EQUALS(my_game.GetFenList()[3], "rnbqkbnr/ppp1pppp/8/3p4/2PP4/8/PP2PPPP/RNBQKBNR b KQkq c3 0 2");
        TS_ASSERT_EQUALS(my_game.GetFenList()[4], "rnbqkbnr/pp2pppp/2p5/3p4/2PP4/8/PP2PPPP/RNBQKBNR w KQkq - 0 3");
        TS_ASSERT_EQUALS(my_game.GetFenList()[5], "rnbqkbnr/pp2pppp/2p5/3p4/2PP4/5N2/PP2PPPP/RNBQKB1R b KQkq - 1 3");
        TS_ASSERT_EQUALS(my_game.GetFenList()[6], "rnbqkb1r/pp2pppp/2p2n2/3p4/2PP4/5N2/PP2PPPP/RNBQKB1R w KQkq - 2 4");
        TS_ASSERT_EQUALS(my_game.GetFenList()[7], "rnbqkb1r/pp2pppp/2p2n2/3p4/2PP4/2N2N2/PP2PPPP/R1BQKB1R b KQkq - 3 4");
        TS_ASSERT_EQUALS(my_game.GetFenList()[8], "rnbqkb1r/pp3ppp/2p1pn2/3p4/2PP4/2N2N2/PP2PPPP/R1BQKB1R w KQkq - 0 5");
        TS_ASSERT_EQUALS(my_game.GetFenList()[9], "rnbqkb1r/pp3ppp/2p1pn2/3p2B1/2PP4/2N2N2/PP2PPPP/R2QKB1R b KQkq - 1 5");
        TS_ASSERT_EQUALS(my_game.GetFenList()[10], "r1bqkb1r/pp1n1ppp/2p1pn2/3p2B1/2PP4/2N2N2/PP2PPPP/R2QKB1R w KQkq - 2 6");
        TS_ASSERT_EQUALS(my_game.GetFenList()[11], "r1bqkb1r/pp1n1ppp/2p1pn2/3P2B1/3P4/2N2N2/PP2PPPP/R2QKB1R b KQkq - 0 6");
        TS_ASSERT_EQUALS(my_game.GetFenList()[12], "r1bqkb1r/pp1n1ppp/2p2n2/3p2B1/3P4/2N2N2/PP2PPPP/R2QKB1R w KQkq - 0 7");
        TS_ASSERT_EQUALS(my_game.GetFenList()[13], "r1bqkb1r/pp1n1ppp/2p2n2/3p2B1/3P4/2N1PN2/PP3PPP/R2QKB1R b KQkq - 0 7");
        TS_ASSERT_EQUALS(my_game.GetFenList()[14], "r1bqk2r/pp1nbppp/2p2n2/3p2B1/3P4/2N1PN2/PP3PPP/R2QKB1R w KQkq - 1 8");
        TS_ASSERT_EQUALS(my_game.GetFenList()[15], "r1bqk2r/pp1nbppp/2p2n2/3p2B1/3P4/2N1PN2/PPQ2PPP/R3KB1R b KQkq - 2 8");
        TS_ASSERT_EQUALS(my_game.GetFenList()[16], "r1bqk2r/pp1nbppp/2p5/3p2Bn/3P4/2N1PN2/PPQ2PPP/R3KB1R w KQkq - 3 9");
        TS_ASSERT_EQUALS(my_game.GetFenList()[17], "r1bqk2r/pp1nBppp/2p5/3p3n/3P4/2N1PN2/PPQ2PPP/R3KB1R b KQkq - 0 9");
        TS_ASSERT_EQUALS(my_game.GetFenList()[18], "r1b1k2r/pp1nqppp/2p5/3p3n/3P4/2N1PN2/PPQ2PPP/R3KB1R w KQkq - 0 10");
        TS_ASSERT_EQUALS(my_game.GetFenList()[19], "r1b1k2r/pp1nqppp/2p5/3p3n/3P4/2N1PN2/PPQ1BPPP/R3K2R b KQkq - 1 10");
        TS_ASSERT_EQUALS(my_game.GetFenList()[20], "r1b1k2r/pp1nqp1p/2p3p1/3p3n/3P4/2N1PN2/PPQ1BPPP/R3K2R w KQkq - 0 11");
        TS_ASSERT_EQUALS(my_game.GetFenList()[21], "r1b1k2r/pp1nqp1p/2p3p1/3p3n/3P4/2N1PN2/PPQ1BPPP/R4RK1 b kq - 1 11");
        TS_ASSERT_EQUALS(my_game.GetFenList()[22], "r1b2rk1/pp1nqp1p/2p3p1/3p3n/3P4/2N1PN2/PPQ1BPPP/R4RK1 w - - 2 12");
        TS_ASSERT_EQUALS(my_game.GetFenList()[23], "r1b2rk1/pp1nqp1p/2p3p1/3p3n/3P4/2N1PN2/PPQ1BPPP/RR4K1 b - - 3 12");
        TS_ASSERT_EQUALS(my_game.GetFenList()[24], "r1b2rk1/pp2qp1p/1np3p1/3p3n/3P4/2N1PN2/PPQ1BPPP/RR4K1 w - - 4 13");
        TS_ASSERT_EQUALS(my_game.GetFenList()[25], "r1b2rk1/pp2qp1p/1np3p1/3p3n/3P4/1QN1PN2/PP2BPPP/RR4K1 b - - 5 13");
        TS_ASSERT_EQUALS(my_game.GetFenList()[26], "r4rk1/pp2qp1p/1np3p1/3p1b1n/3P4/1QN1PN2/PP2BPPP/RR4K1 w - - 6 14");
        TS_ASSERT_EQUALS(my_game.GetFenList()[27], "r4rk1/pp2qp1p/1np3p1/3p1b1n/3P4/1QN1PN2/PP2BPPP/R1R3K1 b - - 7 14");
        TS_ASSERT_EQUALS(my_game.GetFenList()[28], "r4rk1/pp2qp1p/1np2np1/3p1b2/3P4/1QN1PN2/PP2BPPP/R1R3K1 w - - 8 15");
        TS_ASSERT_EQUALS(my_game.GetFenList()[29], "r4rk1/pp2qp1p/1np2np1/3p1b2/P2P4/1QN1PN2/1P2BPPP/R1R3K1 b - a3 0 15");
        TS_ASSERT_EQUALS(my_game.GetFenList()[30], "r1n2rk1/pp2qp1p/2p2np1/3p1b2/P2P4/1QN1PN2/1P2BPPP/R1R3K1 w - - 1 16");
        TS_ASSERT_EQUALS(my_game.GetFenList()[31], "r1n2rk1/pp2qp1p/2p2np1/3p1b2/P2P4/Q1N1PN2/1P2BPPP/R1R3K1 b - - 2 16");
        TS_ASSERT_EQUALS(my_game.GetFenList()[32], "r1n2rk1/1p2qp1p/2p2np1/p2p1b2/P2P4/Q1N1PN2/1P2BPPP/R1R3K1 w - a6 0 17");
        TS_ASSERT_EQUALS(my_game.GetFenList()[33], "r1n2rk1/1p2Qp1p/2p2np1/p2p1b2/P2P4/2N1PN2/1P2BPPP/R1R3K1 b - - 0 17");
        TS_ASSERT_EQUALS(my_game.GetFenList()[34], "r4rk1/1p2np1p/2p2np1/p2p1b2/P2P4/2N1PN2/1P2BPPP/R1R3K1 w - - 0 18");
        TS_ASSERT_EQUALS(my_game.GetFenList()[35], "r4rk1/1p2np1p/2p2np1/p2p1b2/P2P4/1PN1PN2/4BPPP/R1R3K1 b - - 0 18");
        TS_ASSERT_EQUALS(my_game.GetFenList()[36], "r1n2rk1/1p3p1p/2p2np1/p2p1b2/P2P4/1PN1PN2/4BPPP/R1R3K1 w - - 1 19");
        TS_ASSERT_EQUALS(my_game.GetFenList()[37], "r1n2rk1/1p3p1p/2p2np1/p2pNb2/P2P4/1PN1P3/4BPPP/R1R3K1 b - - 2 19");
        TS_ASSERT_EQUALS(my_game.GetFenList()[38], "r1n2rk1/1p1n1p1p/2p3p1/p2pNb2/P2P4/1PN1P3/4BPPP/R1R3K1 w - - 3 20");
        TS_ASSERT_EQUALS(my_game.GetFenList()[39], "r1n2rk1/1p1N1p1p/2p3p1/p2p1b2/P2P4/1PN1P3/4BPPP/R1R3K1 b - - 0 20");
        TS_ASSERT_EQUALS(my_game.GetFenList()[40], "r1n2rk1/1p1b1p1p/2p3p1/p2p4/P2P4/1PN1P3/4BPPP/R1R3K1 w - - 0 21");
        TS_ASSERT_EQUALS(my_game.GetFenList()[41], "r1n2rk1/1p1b1p1p/2p3p1/p2p4/P2P4/1PN1P3/4BPPP/1RR3K1 b - - 1 21");
        TS_ASSERT_EQUALS(my_game.GetFenList()[42], "r4rk1/1p1b1p1p/2pn2p1/p2p4/P2P4/1PN1P3/4BPPP/1RR3K1 w - - 2 22");
        TS_ASSERT_EQUALS(my_game.GetFenList()[43], "r4rk1/1p1b1p1p/2pn2p1/p2p4/PP1P4/2N1P3/4BPPP/1RR3K1 b - - 0 22");
        TS_ASSERT_EQUALS(my_game.GetFenList()[44], "r4rk1/1p1b1p1p/2pn2p1/3p4/Pp1P4/2N1P3/4BPPP/1RR3K1 w - - 0 23");
        TS_ASSERT_EQUALS(my_game.GetFenList()[45], "r4rk1/1p1b1p1p/2pn2p1/3p4/PR1P4/2N1P3/4BPPP/2R3K1 b - - 0 23");
        TS_ASSERT_EQUALS(my_game.GetFenList()[46], "5rk1/1p1b1p1p/2pn2p1/r2p4/PR1P4/2N1P3/4BPPP/2R3K1 w - - 1 24");
        TS_ASSERT_EQUALS(my_game.GetFenList()[47], "5rk1/1p1b1p1p/1Rpn2p1/r2p4/P2P4/2N1P3/4BPPP/2R3K1 b - - 2 24");
        TS_ASSERT_EQUALS(my_game.GetFenList()[48], "r5k1/1p1b1p1p/1Rpn2p1/r2p4/P2P4/2N1P3/4BPPP/2R3K1 w - - 3 25");
        TS_ASSERT_EQUALS(my_game.GetFenList()[49], "r5k1/1p1b1p1p/1Rpn2p1/r2p4/P2P4/2N1PP2/4B1PP/2R3K1 b - - 0 25");
        TS_ASSERT_EQUALS(my_game.GetFenList()[50], "r5k1/1p1b3p/1Rpn2p1/r2p1p2/P2P4/2N1PP2/4B1PP/2R3K1 w - f6 0 26");
        TS_ASSERT_EQUALS(my_game.GetFenList()[51], "r5k1/1p1b3p/1Rpn2p1/r2p1p2/P2P4/2N1PP2/4BKPP/2R5 b - - 1 26");
        TS_ASSERT_EQUALS(my_game.GetFenList()[52], "r7/1p1b1k1p/1Rpn2p1/r2p1p2/P2P4/2N1PP2/4BKPP/2R5 w - - 2 27");
        TS_ASSERT_EQUALS(my_game.GetFenList()[53], "r7/1p1b1k1p/1Rpn2p1/r2p1p2/P2P4/2NBPP2/5KPP/2R5 b - - 3 27");
        TS_ASSERT_EQUALS(my_game.GetFenList()[54], "r7/1p1bk2p/1Rpn2p1/r2p1p2/P2P4/2NBPP2/5KPP/2R5 w - - 4 28");
        TS_ASSERT_EQUALS(my_game.GetFenList()[55], "r7/1p1bk2p/1Rpn2p1/r2p1p2/P2P3P/2NBPP2/5KP1/2R5 b - h3 0 28");
        TS_ASSERT_EQUALS(my_game.GetFenList()[56], "r7/1p2k2p/1Rpnb1p1/r2p1p2/P2P3P/2NBPP2/5KP1/2R5 w - - 1 29");
        TS_ASSERT_EQUALS(my_game.GetFenList()[57], "r7/1p2k2p/1Rpnb1p1/r2p1p2/P2P3P/2NBPP2/5KP1/1R6 b - - 2 29");
        TS_ASSERT_EQUALS(my_game.GetFenList()[58], "8/rp2k2p/1Rpnb1p1/r2p1p2/P2P3P/2NBPP2/5KP1/1R6 w - - 3 30");
        TS_ASSERT_EQUALS(my_game.GetFenList()[59], "8/rp2k2p/1Rpnb1p1/r2p1p2/P2P3P/2NBPPK1/6P1/1R6 b - - 4 30");
        TS_ASSERT_EQUALS(my_game.GetFenList()[60], "8/rp2k3/1Rpnb1pp/r2p1p2/P2P3P/2NBPPK1/6P1/1R6 w - - 0 31");
        TS_ASSERT_EQUALS(my_game.GetFenList()[61], "8/rp2k3/1Rpnb1pp/r2p1p2/P2P1K1P/2NBPP2/6P1/1R6 b - - 1 31");

        TS_ASSERT_EQUALS(my_game.GetGameResult(), "1/2-1/2");
    }

    void TestReadFromPgn2()
    {
        //read the whole file into string
        std::ifstream in("test/data/pgn/one_game_ok_black_win.pgn");
        std::string game_string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        TS_ASSERT_LESS_THAN(1, game_string.length());

        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        slach::Game my_game;
        slach::PgnValidity valid = my_game.LoadFromPgnString(game_string, squares);

        TS_ASSERT_EQUALS(valid, slach::VALID_PGN);
        TS_ASSERT_EQUALS(my_game.GetMoveList().size(), 114u);
        TS_ASSERT_EQUALS(my_game.GetMoveListAlgebraicFormat().size(), 114u);
        TS_ASSERT_EQUALS(my_game.GetGameResult(), "0-1");
    }

    void TestReadFromPgn3()
    {
        //read the whole file into string
        std::ifstream in("test/data/pgn/one_game_ok_white_win.pgn");
        std::string game_string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        TS_ASSERT_LESS_THAN(1, game_string.length());

        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        slach::Game my_game;
        TS_ASSERT_EQUALS(my_game.GetGameResult(), "*");
        TS_ASSERT_EQUALS(my_game.GetNameOfWhitePlayer(), "");
        TS_ASSERT_EQUALS(my_game.GetNameOfBlackPlayer(), "");

        slach::PgnValidity valid = my_game.LoadFromPgnString(game_string, squares);

        TS_ASSERT_EQUALS(valid, slach::VALID_PGN);
        TS_ASSERT_EQUALS(my_game.GetMoveList().size(), 59u);
        TS_ASSERT_EQUALS(my_game.GetMoveListAlgebraicFormat().size(), 59u);
        TS_ASSERT_EQUALS(my_game.GetNameOfWhitePlayer(), "Caruana, Fabiano");
        TS_ASSERT_EQUALS(my_game.GetNameOfBlackPlayer(), "Radjabov, Teimour");
        TS_ASSERT_EQUALS(my_game.GetGameResult(), "1-0");
    }

    void TestReadFromPgnInvalid()
    {
        //read the whole file into string
        std::ifstream in("test/data/pgn/one_game_wrong_move_letter_move_24.pgn");
        std::string game_string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        slach::Game my_game;
        slach::PgnValidity valid = my_game.LoadFromPgnString(game_string, squares);

        TS_ASSERT_EQUALS(valid, slach::INVALID_PGN);
        TS_ASSERT_EQUALS(my_game.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(my_game.GetMoveListAlgebraicFormat().size(), 0u);
    }

    void TestReadFromPgnInvalidBlack()
    {
        //read the whole file into string
        std::ifstream in("test/data/pgn/one_game_wrong_move_13_black.pgn");
        std::string game_string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        TS_ASSERT_LESS_THAN(1, game_string.length());

        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        slach::Game my_game;
        slach::PgnValidity valid = my_game.LoadFromPgnString(game_string, squares);

        TS_ASSERT_EQUALS(valid, slach::INVALID_PGN);
        TS_ASSERT_EQUALS(my_game.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(my_game.GetMoveListAlgebraicFormat().size(), 0u);
    }

    void TestMismatched()
    {
        //read the whole file into string
        std::ifstream in("test/data/pgn/one_game_unmatched_brackets.pgn");
        std::string game_string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        TS_ASSERT_LESS_THAN(1, game_string.length());

        slach::ChessBoard my_cb;
        my_cb.SetupChessBoard();
        my_cb.SetupInitialChessPosition();
        std::vector<slach::Square* > squares = my_cb.GetSquares();

        slach::Game my_game;
        slach::PgnValidity valid = my_game.LoadFromPgnString(game_string, squares);

        TS_ASSERT_EQUALS(valid, slach::INVALID_PGN);
        TS_ASSERT_EQUALS(my_game.GetMoveList().size(), 0u);
        TS_ASSERT_EQUALS(my_game.GetMoveListAlgebraicFormat().size(), 0u);
    }

};
#endif
