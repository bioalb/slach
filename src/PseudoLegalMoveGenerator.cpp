#include "PseudoLegalMoveGenerator.hpp"

slach::PseudoLegalMoveGenerator::PseudoLegalMoveGenerator()
{

}

slach::PseudoLegalMoveGenerator::~PseudoLegalMoveGenerator()
{

}
void slach::PseudoLegalMoveGenerator::SetSquaresInPosition(std::vector<Square*> pSquares)
{
    mSquares = pSquares;
}

std::vector<unsigned> slach::PseudoLegalMoveGenerator::GetPseudoValidDestinations(Square* pOriginSquare)
{
    std::vector<unsigned> pseudo_legal_destinations = {};
    const int offsets[5][9] = {
        {  -33, -31, -18, -14, 14, 18, 31, 33, 0 }, // Knight
        { -17, -15, 15, 17, 0 }, // Bishop
        { -16, 1, 16, -1, 0 }, // Rook
        { -17, -16, -15, 1, 17, 16, 15, -1, 0 }, // Queen
        { -17, -16, -15, 1, 17, 16, 15, -1, 0 } }; // King

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

    // loop over the offsets
    for (int i = 0; offsets[piece_index][i] != 0; i++)
    {
        int x88_target_index = pOriginSquare->Getx88Index();
        while (true)
        {
            x88_target_index += offsets[piece_index][i];
            //key x88 trick, see http://chessprogramming.wikispaces.com/0x88
            if (x88_target_index & 0x88) //out of the board
            {
                break;
            }

            int target_index_from_a1 = mSquares[0]->GetA1IndexFromx88(x88_target_index);
            PieceType target_piece = mSquares[target_index_from_a1]->GetPieceOnThisSquare();

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
    return pseudo_legal_destinations;
}

