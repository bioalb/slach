#ifndef _TESTPOSITION_HPP_
#define _TESTPOSITION_HPP_

#include <cxxtest/TestSuite.h>
#include "Square.hpp"
#include "Position.hpp"
#include "ChessBoard.hpp"

/**
 * Test suite to test the Position class
 */

class TestPosition : public CxxTest::TestSuite
{

public:

	void testNormalMove(void)
	{
		slach::ChessBoard my_cb;
		my_cb.SetupChessBoard();
		my_cb.SetupInitialChessPosition();
		std::vector<slach::Square*> squares = my_cb.GetSquares();
		TS_ASSERT_EQUALS(squares.size(), 64u);

		std::string initial = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
		slach::Position pos;
		pos.SetFromFen(initial, squares);

		slach::FenPositionFeatures feat = pos.GetPositionFeatures();
		TS_ASSERT_EQUALS(feat.mCastlingRights.size(), 4u);
		TS_ASSERT_EQUALS(feat.mCastlingRights[0], slach::WHITE_KINGSIDE);
		TS_ASSERT_EQUALS(feat.mCastlingRights[1], slach::WHITE_QUEENSIDE);
		TS_ASSERT_EQUALS(feat.mCastlingRights[2], slach::BLACK_KINGSIDE);
		TS_ASSERT_EQUALS(feat.mCastlingRights[3], slach::BLACK_QUEENSIDE);
		TS_ASSERT_EQUALS(feat.mTurnToMove, slach::WHITE);
		TS_ASSERT_EQUALS(feat.mMoveCounter, 1);
		TS_ASSERT_EQUALS(feat.mHalfMoveClockSinceLastPawnMove, 0);
		TS_ASSERT_EQUALS(feat.mIndexOfEnpassant, 64);//no en-passant

		slach::Move e2_e4 (squares[12],squares[28]);//e2-e4

		TS_ASSERT_EQUALS(pos.IsMoveLegal(e2_e4, squares), true);

		//make the move
		pos.UpdatePositionWithMove(e2_e4, squares);

		//check piece position
		TS_ASSERT_EQUALS(squares[12]->GetPieceOnThisSquare(), slach::NO_PIECE);//e2
		TS_ASSERT_EQUALS(squares[28]->GetPieceOnThisSquare(), slach::WHITE_PAWN);//e4

		TS_ASSERT_EQUALS (pos.GetPositionAsFen(), "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
		feat = pos.GetPositionFeatures();
		TS_ASSERT_EQUALS(feat.mCastlingRights.size(), 4u);
		TS_ASSERT_EQUALS(feat.mCastlingRights[0], slach::WHITE_KINGSIDE);
		TS_ASSERT_EQUALS(feat.mCastlingRights[1], slach::WHITE_QUEENSIDE);
		TS_ASSERT_EQUALS(feat.mCastlingRights[2], slach::BLACK_KINGSIDE);
		TS_ASSERT_EQUALS(feat.mCastlingRights[3], slach::BLACK_QUEENSIDE);
		TS_ASSERT_EQUALS(feat.mTurnToMove, slach::BLACK);
		TS_ASSERT_EQUALS(feat.mMoveCounter, 1);
		TS_ASSERT_EQUALS(feat.mHalfMoveClockSinceLastPawnMove, 0);
		TS_ASSERT_EQUALS(feat.mIndexOfEnpassant, 20);//e3
	}

	void testCastlingQueenSide(void)
	{
		slach::ChessBoard my_cb;
		my_cb.SetupChessBoard();
		my_cb.SetupInitialChessPosition();
		std::vector<slach::Square*> squares = my_cb.GetSquares();
		TS_ASSERT_EQUALS(squares.size(), 64u);

		std::string all_castle_allowed = "r3k2r/pppbqppp/2np1n2/2b1p3/2B1P3/2NP1N2/PPPBQPPP/R3K2R w KQkq - 4 8";
		slach::Position pos;
		pos.SetFromFen(all_castle_allowed, squares);
		TS_ASSERT_EQUALS(squares[4]->GetPieceOnThisSquare(), slach::WHITE_KING);//e1
		slach::Move white_castle_queenside (squares[4],squares[2]);//e1c1
		slach::Move white_castle_kingside( squares[4],squares[6]);//e1-g1

		TS_ASSERT_EQUALS(pos.IsMoveLegal(white_castle_queenside, squares), true);
		TS_ASSERT_EQUALS(pos.IsMoveLegal(white_castle_kingside, squares), true);

		//make the move
		pos.UpdatePositionWithMove(white_castle_queenside, squares);

		//check piece position
		TS_ASSERT_EQUALS(squares[0]->GetPieceOnThisSquare(), slach::NO_PIECE);//a1
		TS_ASSERT_EQUALS(squares[1]->GetPieceOnThisSquare(), slach::NO_PIECE);//b1
		TS_ASSERT_EQUALS(squares[2]->GetPieceOnThisSquare(), slach::WHITE_KING);//c1
		TS_ASSERT_EQUALS(squares[3]->GetPieceOnThisSquare(), slach::WHITE_ROOK);//d1
		TS_ASSERT_EQUALS(squares[4]->GetPieceOnThisSquare(), slach::NO_PIECE);//e1
		TS_ASSERT_EQUALS(squares[5]->GetPieceOnThisSquare(), slach::NO_PIECE);//f1
		TS_ASSERT_EQUALS(squares[6]->GetPieceOnThisSquare(), slach::NO_PIECE);//g1
		TS_ASSERT_EQUALS(squares[7]->GetPieceOnThisSquare(), slach::WHITE_ROOK);//h1

		TS_ASSERT_EQUALS (pos.GetPositionAsFen(), "r3k2r/pppbqppp/2np1n2/2b1p3/2B1P3/2NP1N2/PPPBQPPP/2KR3R b kq - 5 8");

		slach::FenPositionFeatures feat = pos.GetPositionFeatures();
		TS_ASSERT_EQUALS(feat.mCastlingRights.size(), 2u);
		TS_ASSERT_EQUALS(feat.mCastlingRights[0], slach::BLACK_KINGSIDE);
		TS_ASSERT_EQUALS(feat.mCastlingRights[1], slach::BLACK_QUEENSIDE);
		TS_ASSERT_EQUALS(feat.mTurnToMove, slach::BLACK);
		TS_ASSERT_EQUALS(feat.mMoveCounter, 8);
		TS_ASSERT_EQUALS(feat.mHalfMoveClockSinceLastPawnMove, 5);
		TS_ASSERT_EQUALS(feat.mIndexOfEnpassant, 64);//no en-passant

		slach::Move black_castle_queenside( squares[60], squares[58]);//e8-c8

		slach::Move black_castle_kingside( squares[60],squares[62]);//e8-g8

		TS_ASSERT_EQUALS(pos.IsMoveLegal(black_castle_queenside, squares), true);
		TS_ASSERT_EQUALS(pos.IsMoveLegal(black_castle_kingside, squares), true);

		//make the move
		pos.UpdatePositionWithMove(black_castle_queenside, squares);

		//check piece position
		TS_ASSERT_EQUALS(squares[56]->GetPieceOnThisSquare(), slach::NO_PIECE);//a8
		TS_ASSERT_EQUALS(squares[57]->GetPieceOnThisSquare(), slach::NO_PIECE);//b8
		TS_ASSERT_EQUALS(squares[58]->GetPieceOnThisSquare(), slach::BLACK_KING);//c8
		TS_ASSERT_EQUALS(squares[59]->GetPieceOnThisSquare(), slach::BLACK_ROOK);//d8
		TS_ASSERT_EQUALS(squares[60]->GetPieceOnThisSquare(), slach::NO_PIECE);//e8
		TS_ASSERT_EQUALS(squares[61]->GetPieceOnThisSquare(), slach::NO_PIECE);//f8
		TS_ASSERT_EQUALS(squares[62]->GetPieceOnThisSquare(), slach::NO_PIECE);//g8
		TS_ASSERT_EQUALS(squares[63]->GetPieceOnThisSquare(), slach::BLACK_ROOK);//h8

		TS_ASSERT_EQUALS (pos.GetPositionAsFen(), "2kr3r/pppbqppp/2np1n2/2b1p3/2B1P3/2NP1N2/PPPBQPPP/2KR3R w - - 6 9");

		feat = pos.GetPositionFeatures();
		TS_ASSERT_EQUALS(feat.mCastlingRights.size(), 0u);
		TS_ASSERT_EQUALS(feat.mTurnToMove, slach::WHITE);
		TS_ASSERT_EQUALS(feat.mMoveCounter, 9);
		TS_ASSERT_EQUALS(feat.mHalfMoveClockSinceLastPawnMove, 6);
		TS_ASSERT_EQUALS(feat.mIndexOfEnpassant, 64);//no en-passant
	}

	void testCastlingKingSide(void)
	{
		slach::ChessBoard my_cb;
		my_cb.SetupChessBoard();
		my_cb.SetupInitialChessPosition();
		std::vector<slach::Square*> squares = my_cb.GetSquares();
		TS_ASSERT_EQUALS(squares.size(), 64u);

		std::string all_castle_allowed = "r3k2r/pppbqppp/2np1n2/2b1p3/2B1P3/2NP1N2/PPPBQPPP/R3K2R w KQkq - 4 8";
		slach::Position pos;
		pos.SetFromFen(all_castle_allowed, squares);

		slach::Move white_castle_queenside(squares[4],squares[2]);//e1-c1
		slach::Move white_castle_kingside(squares[4], squares[6]);//e1-g1

		TS_ASSERT_EQUALS(pos.IsMoveLegal(white_castle_queenside, squares), true);
		TS_ASSERT_EQUALS(pos.IsMoveLegal(white_castle_kingside, squares), true);

		//make the move
		pos.UpdatePositionWithMove(white_castle_kingside, squares);

		//check piece position
		TS_ASSERT_EQUALS(squares[0]->GetPieceOnThisSquare(), slach::WHITE_ROOK);//a1
		TS_ASSERT_EQUALS(squares[1]->GetPieceOnThisSquare(), slach::NO_PIECE);//b1
		TS_ASSERT_EQUALS(squares[2]->GetPieceOnThisSquare(), slach::NO_PIECE);//c1
		TS_ASSERT_EQUALS(squares[3]->GetPieceOnThisSquare(), slach::NO_PIECE);//d1
		TS_ASSERT_EQUALS(squares[4]->GetPieceOnThisSquare(), slach::NO_PIECE);//e1
		TS_ASSERT_EQUALS(squares[5]->GetPieceOnThisSquare(), slach::WHITE_ROOK);//f1
		TS_ASSERT_EQUALS(squares[6]->GetPieceOnThisSquare(), slach::WHITE_KING);//g1
		TS_ASSERT_EQUALS(squares[7]->GetPieceOnThisSquare(), slach::NO_PIECE);//h1

		TS_ASSERT_EQUALS (pos.GetPositionAsFen(), "r3k2r/pppbqppp/2np1n2/2b1p3/2B1P3/2NP1N2/PPPBQPPP/R4RK1 b kq - 5 8");

		slach::FenPositionFeatures feat = pos.GetPositionFeatures();
		TS_ASSERT_EQUALS(feat.mCastlingRights.size(), 2u);
		TS_ASSERT_EQUALS(feat.mCastlingRights[0], slach::BLACK_KINGSIDE);
		TS_ASSERT_EQUALS(feat.mCastlingRights[1], slach::BLACK_QUEENSIDE);
		TS_ASSERT_EQUALS(feat.mTurnToMove, slach::BLACK);
		TS_ASSERT_EQUALS(feat.mMoveCounter, 8);
		TS_ASSERT_EQUALS(feat.mHalfMoveClockSinceLastPawnMove, 5);
		TS_ASSERT_EQUALS(feat.mIndexOfEnpassant, 64);//no en-passant

		slach::Move black_castle_queenside(squares[60], squares[58]);//e8c8

		slach::Move black_castle_kingside(squares[60], squares[62]);//e8-g8

		TS_ASSERT_EQUALS(pos.IsMoveLegal(black_castle_queenside, squares), true);
		TS_ASSERT_EQUALS(pos.IsMoveLegal(black_castle_kingside, squares), true);

		//make the move
		pos.UpdatePositionWithMove(black_castle_kingside, squares);

		//check piece position
		TS_ASSERT_EQUALS(squares[56]->GetPieceOnThisSquare(), slach::BLACK_ROOK);//a8
		TS_ASSERT_EQUALS(squares[57]->GetPieceOnThisSquare(), slach::NO_PIECE);//b8
		TS_ASSERT_EQUALS(squares[58]->GetPieceOnThisSquare(), slach::NO_PIECE);//c8
		TS_ASSERT_EQUALS(squares[59]->GetPieceOnThisSquare(), slach::NO_PIECE);//d8
		TS_ASSERT_EQUALS(squares[60]->GetPieceOnThisSquare(), slach::NO_PIECE);//e8
		TS_ASSERT_EQUALS(squares[61]->GetPieceOnThisSquare(), slach::BLACK_ROOK);//f8
		TS_ASSERT_EQUALS(squares[62]->GetPieceOnThisSquare(), slach::BLACK_KING);//g8
		TS_ASSERT_EQUALS(squares[63]->GetPieceOnThisSquare(), slach::NO_PIECE);//h8

		TS_ASSERT_EQUALS (pos.GetPositionAsFen(), "r4rk1/pppbqppp/2np1n2/2b1p3/2B1P3/2NP1N2/PPPBQPPP/R4RK1 w - - 6 9");
	}


	 //This test starts from a position where, after some moves played, both sides could castle.
	 //Both sides then move their rooks back and forth thus progressively loosing castling rights
	void testCastlingRightsLosses(void)
	{
		slach::ChessBoard my_cb;
		my_cb.SetupChessBoard();
		my_cb.SetupInitialChessPosition();
		std::vector<slach::Square*> squares = my_cb.GetSquares();
		TS_ASSERT_EQUALS(squares.size(), 64u);

		//some useful moves first
		slach::Move white_castle_kingside(squares[4],squares[6]);//e1-g1
		slach::Move white_castle_queenside(squares[4], squares[2]);//e1-c1
		slach::Move black_castle_kingside(squares[60], squares[62]);//e8-g8
		slach::Move black_castle_queenside(squares[60], squares[58]);//e8-c8

		//this position is stored in test/data/test_position_4.png for reference
		std::string all_castle_allowed = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K2R w KQkq - 6 8";
		slach::Position pos;
		pos.SetFromFen(all_castle_allowed, squares);

		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(white_castle_kingside, squares));
		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(white_castle_queenside, squares));
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(black_castle_kingside, squares));//could, but not his turn
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(black_castle_queenside, squares));//could, but not his turn

		slach::Move q_rook_move_white(squares[0],squares[1] );//a1-b1oss of castling rights queenside

		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(q_rook_move_white, squares));
		pos.UpdatePositionWithMove(q_rook_move_white, squares);

		std::string after_q_rook_move = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/1R2K2R b Kkq - 7 8";
		TS_ASSERT_EQUALS (pos.GetPositionAsFen(),after_q_rook_move);

		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(white_castle_kingside, squares));//not his turn
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(white_castle_queenside, squares));//not his turn
		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(black_castle_kingside, squares));
		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(black_castle_queenside, squares));

		//Black's turn, moves a8-b8
		slach::Move q_rook_move_black(squares[56],squares[57] );//a8-b8 loss of castling rights queenside

		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(q_rook_move_black, squares));
		pos.UpdatePositionWithMove(q_rook_move_black, squares);

		after_q_rook_move = "1r2k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/1R2K2R w Kk - 8 9";
		TS_ASSERT_EQUALS (pos.GetPositionAsFen(),after_q_rook_move);

		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(white_castle_kingside, squares));
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(white_castle_queenside, squares));//rook not in place
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(black_castle_kingside, squares));//not his turn
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(black_castle_queenside, squares));//not his turn

		//white's turn, moves rook back to a1
		slach::Move rook_back_to_a1(squares[1], squares[0]);//b1-a1

		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(rook_back_to_a1, squares));
		pos.UpdatePositionWithMove(rook_back_to_a1, squares);

		std::string after_rook_back_to_a1 = "1r2k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K2R b Kk - 9 9";
		TS_ASSERT_EQUALS (pos.GetPositionAsFen(),after_rook_back_to_a1);

		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(white_castle_kingside, squares));//not his turn
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(white_castle_queenside, squares));//not his turn
		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(black_castle_kingside, squares));
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(black_castle_queenside, squares));//rook not in place

		//black's move rook back to a8
		slach::Move rook_back_to_a8(squares[57], squares[56]);//b8-a8

		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(rook_back_to_a8, squares));
		pos.UpdatePositionWithMove(rook_back_to_a8, squares);

		std::string after_rook_back_to_a8 = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K2R w Kk - 10 10";
		TS_ASSERT_EQUALS (pos.GetPositionAsFen(),after_rook_back_to_a8);

		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(white_castle_kingside, squares));
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(white_castle_queenside, squares));//rook in place but lost rights
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(black_castle_kingside, squares));//not his turn
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(black_castle_queenside, squares));//not his turn

		//white's move the kingside rook
		slach::Move k_rook_move_white(squares[7], squares[6]);//h1-g1 loss of castling rights kingside

		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(k_rook_move_white, squares));
		pos.UpdatePositionWithMove(k_rook_move_white, squares);

		std::string after_rook_g1 = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K1R1 b k - 11 10";
		TS_ASSERT_EQUALS (pos.GetPositionAsFen(),after_rook_g1);

		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(white_castle_kingside, squares));//not his turn
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(white_castle_queenside, squares));//not his turn
		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(black_castle_kingside, squares));
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(black_castle_queenside, squares));//rook in place but no rights

		//black's move his kingside rook
		slach::Move k_rook_move_black(squares[63], squares[62]);//h8-g8 loss of castling rights kingside

		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(k_rook_move_black, squares));
		pos.UpdatePositionWithMove(k_rook_move_black, squares);

		std::string after_rook_g8 = "r3k1r1/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K1R1 w - - 12 11";
		TS_ASSERT_EQUALS (pos.GetPositionAsFen(),after_rook_g8);

		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(white_castle_kingside, squares));//rook not in place
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(white_castle_queenside, squares));//rook in place but lost rights
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(black_castle_kingside, squares));//not his turn
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(black_castle_queenside, squares));//not his turn

		//white's move the kingside rook BACK to h1
		slach::Move k_rook_move_white_back_to_h1( squares[6],squares[7]);//g1-h1

		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(k_rook_move_white_back_to_h1, squares));
		pos.UpdatePositionWithMove(k_rook_move_white_back_to_h1, squares);

		std::string after_rook_back_to_h1 = "r3k1r1/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K2R b - - 13 11";
		TS_ASSERT_EQUALS (pos.GetPositionAsFen(),after_rook_back_to_h1);

		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(white_castle_kingside, squares));//not his turn
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(white_castle_queenside, squares));//not his turn
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(black_castle_kingside, squares));//rook not in place
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(black_castle_queenside, squares));//rook in place but no rights

		//black's move his kingside rook BACK to h8
		slach::Move k_rook_move_black_back_to_h8(squares[62],squares[63]);//g8-h8

		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(k_rook_move_black_back_to_h8, squares));
		pos.UpdatePositionWithMove(k_rook_move_black_back_to_h8, squares);

		std::string after_rook_back_to_h8 = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K2R w - - 14 12";
		TS_ASSERT_EQUALS (pos.GetPositionAsFen(),after_rook_back_to_h8);

		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(white_castle_kingside, squares));//rook in place but lost rights
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(white_castle_queenside, squares));//rook in place but lost rights
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(black_castle_kingside, squares));//not his turn
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(black_castle_queenside, squares));//not his turn

		//some move by white
		slach::Move a2_a3(squares[8], squares[16]);//a2-a3

		TS_ASSERT_EQUALS(true, pos.IsMoveLegal(a2_a3, squares));
		pos.UpdatePositionWithMove(a2_a3, squares);

		std::string after_a2_a3 = "r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PPQ1PPP/R3K2R b - - 0 12";
		TS_ASSERT_EQUALS (pos.GetPositionAsFen(),after_a2_a3);

		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(white_castle_kingside, squares));//not his turn
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(white_castle_queenside, squares));//not his turn
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(black_castle_kingside, squares));//rook in place but no rights
		TS_ASSERT_EQUALS(false, pos.IsMoveLegal(black_castle_queenside, squares));//rook in place but no rights
	}

	//This test starts from a position where, after some moves played, both sides could castle.
	//Both sides then move their rooks back and forth thus progressively loosing castling rights
   void testPromotions(void)
   {
       slach::ChessBoard my_cb;
       my_cb.SetupChessBoard();
       my_cb.SetupInitialChessPosition();
       std::vector<slach::Square* > squares = my_cb.GetSquares();
       TS_ASSERT_EQUALS(squares.size(), 64u);

       //saved in tets/data/test_position_5.png for reference
       std::string fen_poistion = "4k3/2P1P1P1/3K3P/p4b2/8/P7/1p6/8 b - - 0 59";
	   slach::Position pos;
	   pos.SetFromFen(fen_poistion, squares);
       //black's turn move is b2-b1 (promotes queen)
       slach::Move b2_b1(squares[9],squares[1]);//b2-b1

       TS_ASSERT_EQUALS(pos.IsMoveLegal(b2_b1, squares), true);
       pos.UpdatePositionWithMove(b2_b1, squares);
       pos.SetPromotionPiece(slach::BLACK_QUEEN);//the default anyway
       TS_ASSERT_EQUALS(squares[1]->GetPieceOnThisSquare(), slach::BLACK_QUEEN);
       TS_ASSERT_EQUALS(squares[9]->GetPieceOnThisSquare(), slach::NO_PIECE);

       std::string after_black_promotion = "4k3/2P1P1P1/3K3P/p4b2/8/P7/8/1q6 w - - 0 60";
       TS_ASSERT_EQUALS(after_black_promotion, pos.GetPositionAsFen());

       //white's turn, also promotes with c7-c8 /// NOTE FOR LATER:g7 g8 here is checkmate
       slach::Move c7_c8( squares[50],squares[58]);//c7-c8

       TS_ASSERT_EQUALS(pos.IsMoveLegal(c7_c8, squares), true);
       pos.UpdatePositionWithMove(c7_c8, squares);

       TS_ASSERT_EQUALS(squares[58]->GetPieceOnThisSquare(), slach::WHITE_QUEEN);
       TS_ASSERT_EQUALS(squares[50]->GetPieceOnThisSquare(), slach::NO_PIECE);

       std::string after_white_promotion = "2Q1k3/4P1P1/3K3P/p4b2/8/P7/8/1q6 b - - 0 60";
       TS_ASSERT_EQUALS(after_white_promotion, pos.GetPositionAsFen());

       //black's turn, bishop captures queen f5-c8
       slach::Move f5_c8(squares[37], squares[58]);//f5-c8

       TS_ASSERT_EQUALS(pos.IsMoveLegal(f5_c8, squares), true);
       pos.UpdatePositionWithMove(f5_c8, squares);

       TS_ASSERT_EQUALS(squares[58]->GetPieceOnThisSquare(), slach::BLACK_BISHOP);
       TS_ASSERT_EQUALS(squares[37]->GetPieceOnThisSquare(), slach::NO_PIECE);

       std::string after_bishop_capture = "2b1k3/4P1P1/3K3P/p7/8/P7/8/1q6 w - - 1 61";
       TS_ASSERT_EQUALS(after_bishop_capture,  pos.GetPositionAsFen());

       //white's turn--> promotes on g8 but get a knight!
       slach::Move g7_g8( squares[54],squares[62]);//g7-g8

       pos.SetPromotionPiece(slach::WHITE_KNIGHT);
       TS_ASSERT_EQUALS(pos.IsMoveLegal(g7_g8, squares), true);
       pos.UpdatePositionWithMove(g7_g8, squares);

       TS_ASSERT_EQUALS(squares[62]->GetPieceOnThisSquare(), slach::WHITE_KNIGHT);
       TS_ASSERT_EQUALS(squares[54]->GetPieceOnThisSquare(), slach::NO_PIECE);
       //coverage
       TS_ASSERT_THROWS_THIS(pos.SetPromotionPiece(slach::WHITE_PAWN), "slach::Position::SetPromotionPiece: you can't set a pawn to be a promotion piece");
       TS_ASSERT_THROWS_THIS(pos.SetPromotionPiece(slach::BLACK_PAWN), "slach::Position::SetPromotionPiece: you can't set a pawn to be a promotion piece");
   }
};
#endif
