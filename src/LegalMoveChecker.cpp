#include <cassert>
#include <algorithm>
#include "Exception.hpp"
#include "LegalMoveChecker.hpp"


slach::LegalMoveChecker::LegalMoveChecker()
{
	mOffsets = {
	{  -33, -31, -18, -14, 14, 18, 31, 33, 0 }, // Knight
	{ -17, -15, 15, 17, 0 },                    // Bishop
	{ -16, -1, 1, 16, 0 },                      // Rook
	{ -17, -16, -15, -1, 1, 15, 16, 17, 0 },    // Queen
	{ -17, -16, -15, -1, 1, 15, 16, 17, 0 }     // King
	};

	mPawnCaptureOffsets = { 15, 17 };

	mTempSquares.resize(64u);
	for (unsigned i = 0; i < mTempSquares.size(); ++i)
	{
		mTempSquares[i] = new slach::Square();
		mTempSquares[i]->SetIndexFromA1(i);
		mTempSquares[i]->SetPieceOnThisSquare(slach::NO_PIECE);
	}
}

slach::LegalMoveChecker::~LegalMoveChecker()
{
	for (unsigned i = 0; i < mTempSquares.size(); ++i)
	{
		delete mTempSquares[i];
	}
}
std::vector<unsigned> slach::LegalMoveChecker::GetPseudoLegalMovesSquaresFromOrigin(Square* pOriginSquare, const std::vector<Square*>& rSquares, const std::vector<CastlingRights>& rCastlingRights, unsigned enPassantIndex)
{
    std::vector<unsigned> pseudo_legal_moves;

    if (IsPawn(pOriginSquare->GetPieceOnThisSquare()))
    {
        //single step forward
        int x88_target_index = pOriginSquare->Getx88Index() + ((IsWhitePiece(pOriginSquare->GetPieceOnThisSquare()) == true) ? 16 : -16);

        //if not obstructed....
        unsigned index_from_a1 = GetA1IndexFromx88(x88_target_index);
        if (rSquares [ index_from_a1 ]->GetPieceOnThisSquare() == NO_PIECE)
        {
            pseudo_legal_moves.push_back(index_from_a1);

            //double step forward, only if not blocked in front and only if second or seventh rank.
            if ( (pOriginSquare->IsSecondRank() && IsWhitePiece( pOriginSquare->GetPieceOnThisSquare() ) ) ||
                 (pOriginSquare->IsSeventhRank() && IsBlackPiece( pOriginSquare->GetPieceOnThisSquare() ) )  )
            {
                x88_target_index = pOriginSquare->Getx88Index() + ((IsWhitePiece(pOriginSquare->GetPieceOnThisSquare()) == true) ? 32 : -32);
                //if not obstructed....
                index_from_a1 = GetA1IndexFromx88(x88_target_index);
                if (rSquares [ index_from_a1 ]->GetPieceOnThisSquare() == NO_PIECE)
                {
                    pseudo_legal_moves.push_back(index_from_a1);
                }
            }
        }//end of check for obstruction in front of the pawn

        for (unsigned i = 0; i < mPawnCaptureOffsets.size(); ++i)
        {
            // Ensure the target square is on the board.
            int offset = (IsWhitePiece(pOriginSquare->GetPieceOnThisSquare()) == true) ? mPawnCaptureOffsets[i] : - mPawnCaptureOffsets[i];
            x88_target_index = pOriginSquare->Getx88Index() + offset;
            //crucial 0x88 trick, see http://chessprogramming.wikispaces.com/0x88
            if (x88_target_index & 0x88)//if off the board, check the other square...
            {
                continue;
            }
            index_from_a1 = GetA1IndexFromx88(x88_target_index);
            PieceType target_piece = rSquares[index_from_a1]->GetPieceOnThisSquare();
            //check there is something of opposite colours on the target square
            if ( ( IsWhitePiece(target_piece) && IsBlackPiece( pOriginSquare->GetPieceOnThisSquare() ) ) ||
               (   IsBlackPiece(target_piece) && IsWhitePiece( pOriginSquare->GetPieceOnThisSquare() ) ) ||
                   enPassantIndex == index_from_a1 )
            {
                // Normal capture.
                pseudo_legal_moves.push_back(index_from_a1);
            }
        }
    }//end of pawn handling
    else if (IsKing(pOriginSquare->GetPieceOnThisSquare())) //case of the king
    {
        pseudo_legal_moves = GetAttackedSquaresFromOrigin(pOriginSquare, rSquares);
        //white castles
        if ( (pOriginSquare->GetPieceOnThisSquare() == WHITE_KING) && (pOriginSquare->GetIndexFromA1() == 4u)/*e1*/ )
        {
            std::vector<unsigned> f1_attackers = GetAttackers(rSquares[5u], rSquares, BLACK);
            std::vector<unsigned> e1_attackers = GetAttackers(rSquares[4u], rSquares, BLACK);
            std::vector<unsigned> d1_attackers = GetAttackers(rSquares[3u], rSquares, BLACK);
            //castling kingside not obstructed, 5 is f1 and 6 is g1
            if ( (rSquares[5u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 (rSquares[6u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 (rSquares[7u]->GetPieceOnThisSquare() == WHITE_ROOK) &&
                  IsWithinCastlingRights(WHITE_KINGSIDE,rCastlingRights)&&
                  f1_attackers.size() == 0 && e1_attackers.size() == 0)
            {
                pseudo_legal_moves.push_back(6u);//g1
            }
            //castling queenside check rook and empty squares in the middle
            if ( (rSquares[0u]->GetPieceOnThisSquare() == WHITE_ROOK) &&
                 (rSquares[1u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 (rSquares[2u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 (rSquares[3u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 IsWithinCastlingRights(WHITE_QUEENSIDE, rCastlingRights)&&
                 d1_attackers.size() == 0 && e1_attackers.size() == 0)
            {
                pseudo_legal_moves.push_back(2u);//c1
            }
        }
        //black castles
        if ( (pOriginSquare->GetPieceOnThisSquare() == BLACK_KING) && (pOriginSquare->GetIndexFromA1() ==60u)/*e8*/ )
        {
            std::vector<unsigned> f8_attackers = GetAttackers(rSquares[61u], rSquares, WHITE);
            std::vector<unsigned> e8_attackers = GetAttackers(rSquares[60u], rSquares, WHITE);
            std::vector<unsigned> d8_attackers = GetAttackers(rSquares[59u], rSquares, WHITE);
            //castling kingside not obstructed, 61 is f8 and 62 is g8
            if ( (rSquares[61u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 (rSquares[62u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 (rSquares[63u]->GetPieceOnThisSquare() == BLACK_ROOK) &&
                 IsWithinCastlingRights(BLACK_KINGSIDE, rCastlingRights) &&
                 f8_attackers.size()==0 && e8_attackers.size() == 0)
            {
                pseudo_legal_moves.push_back(62u);//g8
            }
            //castling queenside check rook and empty squares in the middle
            if ( (rSquares[56u]->GetPieceOnThisSquare() == BLACK_ROOK) &&
                 (rSquares[57u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 (rSquares[58u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 (rSquares[59u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 IsWithinCastlingRights(BLACK_QUEENSIDE, rCastlingRights)&&
                 d8_attackers.size()==0 && e8_attackers.size() == 0)
            {
                pseudo_legal_moves.push_back(58u);//c8
            }
        }
    }
    else //sliding pieces
    {
        pseudo_legal_moves = GetAttackedSquaresFromOrigin(pOriginSquare, rSquares);
    }
    return pseudo_legal_moves;
}

std::vector<unsigned> slach::LegalMoveChecker::GetAttackedSquaresFromOrigin(Square* pOriginSquare, const std::vector<Square*>& rSquares)
{
    std::vector<unsigned> attacked_squares = {};

    int piece_index = -1;
    if (IsKnight( pOriginSquare->GetPieceOnThisSquare() )== true)
    {
       piece_index = 0;
    }
    else if (IsBishop( pOriginSquare->GetPieceOnThisSquare() )== true)
    {
       piece_index = 1;
    }
    else if (IsRook( pOriginSquare->GetPieceOnThisSquare() )== true)
    {
      piece_index = 2;
    }
    else if (IsQueen( pOriginSquare->GetPieceOnThisSquare() )== true)
    {
       piece_index = 3;
    }
    else if (IsKing( pOriginSquare->GetPieceOnThisSquare() )== true)
    {
      piece_index = 4;
    }
    else if (IsPawn( pOriginSquare->GetPieceOnThisSquare() )== true)
    {
      piece_index = 5;
    }
    else
    {
        //empty square
        return attacked_squares;
    }

    if (piece_index == 5)//pawn
    {
        for (unsigned i = 0; i < mPawnCaptureOffsets.size(); ++i)
        {
            // Ensure the target square is on the board.
            int offset = (IsWhitePiece(pOriginSquare->GetPieceOnThisSquare()) == true) ? mPawnCaptureOffsets[i] : - mPawnCaptureOffsets[i];
            int x88_target_index = pOriginSquare->Getx88Index() + offset;
            //crucial 0x88 trick, see http://chessprogramming.wikispaces.com/0x88
            if (x88_target_index & 0x88)//if off the board, check the other square...
            {
                continue;
            }
            unsigned index_from_a1 = GetA1IndexFromx88(x88_target_index);
            // Normal capture.
            attacked_squares.push_back(index_from_a1);
        }
    }//end of pawn handling
    else//not a pawn
    {
        assert(piece_index > -1);
        assert(piece_index < 5);
        // loop over the mOffsets
        for (int i = 0; mOffsets[piece_index][i] != 0; i++)
        {
            int x88_target_index = pOriginSquare->Getx88Index();
            while (true)
            {
                x88_target_index += mOffsets[piece_index][i];
                //crucial 0x88 trick, see http://chessprogramming.wikispaces.com/0x88
                if (x88_target_index & 0x88) //bitwise AND, out of the board if non-zero
                {
                    break;
                }

                int target_index_from_a1 = GetA1IndexFromx88(x88_target_index);
                PieceType target_piece = rSquares[target_index_from_a1]->GetPieceOnThisSquare();

                if ( target_piece == NO_PIECE ||
                   ( IsWhitePiece(target_piece) && IsBlackPiece( pOriginSquare->GetPieceOnThisSquare() ) ) ||
                   ( IsBlackPiece(target_piece) && IsWhitePiece( pOriginSquare->GetPieceOnThisSquare() ) ) )
                {
                    attacked_squares.push_back(target_index_from_a1);
                    if (target_piece != NO_PIECE)//enemy piece, we can move there, i.e., capture, but no further
                    {
                        break;
                    }
                }
                else //your own piece, no further
                {
                    break;
                }
                // Knight and king do not go multiple times in their direction.
                if (IsKnight( pOriginSquare->GetPieceOnThisSquare() ) || IsKing( pOriginSquare->GetPieceOnThisSquare() ))
                {
                    break;
                }
            }
        }
    }//end of the "not a pawn" case
    return attacked_squares;
}

std::vector<unsigned> slach::LegalMoveChecker::GetAttackers(Square* attacked, const std::vector<Square*>& rSquares, Colour attackingColour)
{
    std::vector<unsigned> attacking_squares = {};
    for (unsigned i = 0; i < rSquares.size(); ++i)
    {
    	if ( IsPieceSameAsTurn(rSquares[i]->GetPieceOnThisSquare(), attackingColour) == true)
    	{
    		std::vector<unsigned> att = GetAttackedSquaresFromOrigin(rSquares[i], rSquares);
    		std::sort (att.begin(), att.end());
    	    if (std::binary_search (att.begin(), att.end(), attacked->GetIndexFromA1()) == true)
    	    {
    	    	attacking_squares.push_back(i);
    	    }
    	}
    }
    return attacking_squares;
}

bool slach::LegalMoveChecker::IsMoveLegalInPosition(const std::vector<Square*>& rSquares,
            const Move& rMove, Colour turn, std::vector<CastlingRights> castlingRights, unsigned enpassantIindex)
{
    PieceType origin_piece = rMove.first->GetPieceOnThisSquare();
    //NOT YOUR TURN!
    if (IsPieceSameAsTurn(origin_piece, turn) == false)
    {
        return false;
    }

    std::vector<unsigned> pseudo_destinations = GetPseudoLegalMovesSquaresFromOrigin(rMove.first, rSquares, castlingRights,enpassantIindex);
    std::sort (pseudo_destinations.begin(), pseudo_destinations.end());
    if (std::binary_search (pseudo_destinations.begin(), pseudo_destinations.end(), rMove.second->GetIndexFromA1()) == true)
    {
    	// sync tempSquares board with what we want to check
    	for (unsigned  i = 0; i < rSquares.size(); ++i)
    	{
    		mTempSquares[i]->SetPieceOnThisSquare( rSquares[i]->GetPieceOnThisSquare() );
    	}
    	unsigned origin_index = rMove.first->GetIndexFromA1();
    	unsigned dest_index = rMove.second->GetIndexFromA1();
    	//make the move on temp squares
    	mTempSquares[origin_index]->SetPieceOnThisSquare(NO_PIECE);
    	mTempSquares[dest_index]->SetPieceOnThisSquare(rMove.first->GetPieceOnThisSquare());


    	//look for the king
    	unsigned king_location = 64;
    	for (unsigned  i = 0; i < mTempSquares.size(); ++i)
    	{
    		if ( IsKing (mTempSquares[i]->GetPieceOnThisSquare() ) &&
    		     IsPieceSameAsTurn(mTempSquares[i]->GetPieceOnThisSquare(), turn) )
    		{
    			king_location = i;
    			break;
    		}
    	}
    	if (king_location==64)
    	{
    		return true;//only for testing... case where there is no king on the board
    	}
    	else if (GetAttackers(mTempSquares[king_location], mTempSquares, OppositeColour(turn)).size() > 0)
    	{
    		return false;//king under check after the move, not legal!
    	}
    	else
    	{
    		return true;
    	}
    }
    else//move is not even pseudo-legal as defined here
    {
        return false;
    }
}
