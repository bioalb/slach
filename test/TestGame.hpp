#ifndef TESTGAME_HPP_
#define TESTGAME_HPP_

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Game.hpp"
#include "ChessBoard.hpp"

/**
 * Test suite to test the game class
 */

class TestGame : public CxxTest::TestSuite
{
public:


    void testBasicMove()
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

    void testPawnMove()
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

    void testCapture()
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

    void testPawnCapture()
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

    void testCastleKingSide()
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

    void testCastleQueenSide()
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

    }
};
#endif
