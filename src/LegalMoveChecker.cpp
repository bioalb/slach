#include <cassert>
#include <algorithm>
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
}

slach::LegalMoveChecker::~LegalMoveChecker()
{

}

std::vector<unsigned> slach::LegalMoveChecker::GetTargetSquaresFromOrigin(Square* pOriginSquare, const std::vector<Square*>& rSquares, const std::vector<CastlingRights>& rCastlingRights, unsigned enPassantIndex)
{
    std::vector<unsigned> pseudo_legal_destinations = {};

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
        return pseudo_legal_destinations;
    }

    if (piece_index == 5)//pawn
    {
        //single step forward
        int x88_target_index = pOriginSquare->Getx88Index() + ((IsWhitePiece(pOriginSquare->GetPieceOnThisSquare()) == true) ? 16 : -16);

        //if not obstructed....
        unsigned index_from_a1 = GetA1IndexFromx88(x88_target_index);
        if (rSquares [ index_from_a1 ]->GetPieceOnThisSquare() == NO_PIECE)
        {
            pseudo_legal_destinations.push_back(index_from_a1);

            //double step forward, only if not blocked in front and only if second or seventh rank.
            if ( (pOriginSquare->IsSecondRank() && IsWhitePiece( pOriginSquare->GetPieceOnThisSquare() ) ) ||
                 (pOriginSquare->IsSeventhRank() && IsBlackPiece( pOriginSquare->GetPieceOnThisSquare() ) )  )
            {
                x88_target_index = pOriginSquare->Getx88Index() + ((IsWhitePiece(pOriginSquare->GetPieceOnThisSquare()) == true) ? 32 : -32);
                //if not obstructed....
                index_from_a1 = GetA1IndexFromx88(x88_target_index);
                if (rSquares [ index_from_a1 ]->GetPieceOnThisSquare() == NO_PIECE)
                {
                   pseudo_legal_destinations.push_back(index_from_a1);
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
                pseudo_legal_destinations.push_back(index_from_a1);
            }
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
                    pseudo_legal_destinations.push_back(target_index_from_a1);
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

        //white castles
        if ( (pOriginSquare->GetPieceOnThisSquare() == WHITE_KING) && (pOriginSquare->GetIndexFromA1() == 4u)/*e1*/ )
        {
            //castling kingside not obstructed, 5 is f1 and 6 is g1
            if ( (rSquares[5u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 (rSquares[6u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 (rSquares[7u]->GetPieceOnThisSquare() == WHITE_ROOK) &&
                  IsWithinCastlingRights(WHITE_KINGSIDE,rCastlingRights))
            {
                pseudo_legal_destinations.push_back(6u);//g1
            }
            //castling queenside check rook and empty squares in the middle
            if ( (rSquares[0u]->GetPieceOnThisSquare() == WHITE_ROOK) &&
                 (rSquares[1u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 (rSquares[2u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 (rSquares[3u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 IsWithinCastlingRights(WHITE_QUEENSIDE, rCastlingRights))
            {
                pseudo_legal_destinations.push_back(2u);//c1
            }
        }
        //black castles
        if ( (pOriginSquare->GetPieceOnThisSquare() == BLACK_KING) && (pOriginSquare->GetIndexFromA1() ==60u)/*e8*/ )
        {
            //castling kingside not obstructed, 61 is f8 and 62 is g8
            if ( (rSquares[61u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 (rSquares[62u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 (rSquares[63u]->GetPieceOnThisSquare() == BLACK_ROOK) &&
                 IsWithinCastlingRights(BLACK_KINGSIDE, rCastlingRights))
            {
                pseudo_legal_destinations.push_back(62u);//g8
            }
            //castling queenside check rook and empty squares in the middle
            if ( (rSquares[56u]->GetPieceOnThisSquare() == BLACK_ROOK) &&
                 (rSquares[57u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 (rSquares[58u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 (rSquares[59u]->GetPieceOnThisSquare() == NO_PIECE) &&
                 IsWithinCastlingRights(BLACK_QUEENSIDE, rCastlingRights))
            {
                pseudo_legal_destinations.push_back(58u);//c8
            }
        }

    }//end of the "not a pawn" case
    return pseudo_legal_destinations;
}

bool slach::LegalMoveChecker::IsMoveLegalInPosition(const std::vector<Square*>& rSquares,
            const Move& rMove, TurnToMove turn, std::vector<CastlingRights> castlingRights, unsigned enpassantIindex)
{

    std::vector<unsigned> pseudo_destinations = GetTargetSquaresFromOrigin(rMove.first, rSquares, castlingRights,enpassantIindex);
    std::sort (pseudo_destinations.begin(), pseudo_destinations.end());
    if (std::binary_search (pseudo_destinations.begin(), pseudo_destinations.end(), rMove.second->GetIndexFromA1()) == true)
    {
        for (unsigned i = 0; i < rSquares.size(); ++i)
        {

        }
        return true;
    }
    else//move is not even pseudo-legal as defined here
    {
        return false;
    }
}

bool slach::LegalMoveChecker::IsWithinCastlingRights(const CastlingRights& test, const std::vector<CastlingRights>& castlingRights)
{
    for (unsigned i = 0; i < castlingRights.size(); ++i)
    {
        if (castlingRights[i] == test)
        {
            return true;
        }
    }
    return false;
}
