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
    const int offsets[5][9] = {
        { -18, -33, -31, -14, 18, 33, 31, 14, 0 }, // Knight
        { -17, -15, 17, 15, 0 }, // Bishop
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
            if (x88_target_index & 0x88)
            {
                break;
            }

            int target_index_from_a1 = mSquares[0]->GetA1IndexFromx88(x88_target_index);
            PieceType target_piece = mSquares[target_index_from_a1]->GetPieceOnThisSquare();
            //          if (target_piece.is_valid()) {
            //              // Captures.
            //              if (target_piece.color() != m_position->turn()) {
            //              m_cache.push(Move(square, target));
            //              }
            //              break;
            //          } else {
            //              m_cache.push(Move(square, target));
            //          }

            if ( target_piece == NO_PIECE ||
             ( IsWhitePiece(target_piece) && IsBlackPiece( pOriginSquare->GetPieceOnThisSquare() ) ) ||
             ( IsBlackPiece(target_piece) && IsWhitePiece( pOriginSquare->GetPieceOnThisSquare() ) ) )
            {
                mPseudoLegalDestinations.push_back(target_index_from_a1);
            }
            // Knight and king do not go multiple times in their direction.
            if (IsKnight( pOriginSquare->GetPieceOnThisSquare() ) || IsKing( pOriginSquare->GetPieceOnThisSquare() ))
            {
                break;
            }
        }
    }
    //std::vector<unsigned> ;

    return mPseudoLegalDestinations;
}

