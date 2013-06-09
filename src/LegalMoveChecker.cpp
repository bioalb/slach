#include <cassert>
#include <algorithm>
#include "LegalMoveChecker.hpp"


slach::LegalMoveChecker::LegalMoveChecker()
{
        mOffsets = {
        {  -33, -31, -18, -14, 14, 18, 31, 33, 0 }, // Knight
        { -17, -15, 15, 17, 0 },                    // Bishop
        { -16, 1, 16, -1, 0 },                      // Rook
        { -17, -16, -15, 1, 17, 16, 15, -1, 0 },    // Queen
        { -17, -16, -15, 1, 17, 16, 15, -1, 0 }     // King
        };

        mPawnCaptureOffsets = { 15, 17 };
}

slach::LegalMoveChecker::~LegalMoveChecker()
{

}

std::vector<unsigned> slach::LegalMoveChecker::GetPseudoValidDestinations(Square* pOriginSquare, const std::vector<Square*>& rSquares)
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

            if ( (pOriginSquare->IsSecondRank() && IsWhitePiece( pOriginSquare->GetPieceOnThisSquare() ) ) ||
                 (pOriginSquare->IsSeventhRank() && IsBlackPiece( pOriginSquare->GetPieceOnThisSquare() ) )  )
            {
                //double step forward
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
            //0x88 trick again to check we are on the board
            if (x88_target_index & 0x88) {
            continue;
            }
            index_from_a1 = GetA1IndexFromx88(x88_target_index);
            PieceType target_piece = rSquares[index_from_a1]->GetPieceOnThisSquare();
            //check there is something of opposite colours on the target square
            if ( ( IsWhitePiece(target_piece) && IsBlackPiece( pOriginSquare->GetPieceOnThisSquare() ) ) ||
               (   IsBlackPiece(target_piece) && IsWhitePiece( pOriginSquare->GetPieceOnThisSquare() ) ) )
            {
                // Normal capture.
                pseudo_legal_destinations.push_back(index_from_a1);
            }
        }
    }
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
    }
    return pseudo_legal_destinations;
}

bool slach::LegalMoveChecker::IsMoveValidInPosition(const std::vector<Square*>& rSquares,
            const Move& rMove, TurnToMove turn, std::vector<CastlingRights> castlingRights, unsigned enpassantIindex)
{
    std::vector<unsigned> pseudo_destinations = GetPseudoValidDestinations(rMove.first, rSquares);
    std::sort (pseudo_destinations.begin(), pseudo_destinations.end());
    return std::binary_search (pseudo_destinations.begin(), pseudo_destinations.end(), rMove.second->GetIndexFromA1());
}
