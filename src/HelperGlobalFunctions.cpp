#include "HelperGlobalFunctions.hpp"



void slach::DeleteCastlingRights(const CastlingRights& toBeDeleted, std::vector<CastlingRights>& rCastlingRights)
{
    for (unsigned i = 0; i < rCastlingRights.size(); ++i)
    {
        if (rCastlingRights[i] == toBeDeleted)
        {
            rCastlingRights.erase(rCastlingRights.begin()+i);
            break;
        }
    }
}

unsigned slach::GetIndexFromCoordinates(const char &rFile, const char &rRank)
{
    unsigned global_counter = 0u;
    for (unsigned rank_index  = 0; rank_index < gChessboardFiles.size(); ++rank_index)
    {
        for (unsigned file_index = 0; file_index <  gChessboardRanks.size(); ++file_index)
        {
            if ((gChessboardRanks[rank_index] == rRank) && (gChessboardFiles[file_index] == rFile))
            {
                return global_counter;
            }
            global_counter++;
        }
    }
    return 64u;
}

std::string slach::GetPieceCodeOfThisPiece (const PieceType& piece)
{
    std::string ret("");

    if (IsQueen(piece))
    {
        ret = "Q";
    }
    if (IsRook(piece))
    {
        ret = "R";
    }
    if (IsBishop(piece))
    {
        ret = "B";
    }
    if (IsKnight(piece))
    {
        ret = "N";
    }
    if (IsKing(piece))
    {
        ret = "K";
    }

    return ret;
}

slach::PieceType slach::GetPieceFromCode (const char code, Colour col)
{
    if (code == 'N')
    {
        if ( col == WHITE )
        {
            return WHITE_KNIGHT;
        }
        else
        {
            return BLACK_KNIGHT;
        }
    }
    else if (code == 'R')
    {
        if ( col == WHITE )
        {
            return WHITE_ROOK;
        }
        else
        {
            return BLACK_ROOK;
        }
    }
    else if (code == 'Q')
    {
        if ( col == WHITE )
        {
            return WHITE_QUEEN;
        }
        else
        {
            return BLACK_QUEEN;
        }
    }
    else if (code == 'K')
    {
        if ( col == WHITE )
        {
            return WHITE_KING;
        }
        else
        {
            return BLACK_KING;
        }
    }
    else if (code == 'B')
    {
        if ( col == WHITE )
        {
            return WHITE_BISHOP;
        }
        else
        {
            return BLACK_BISHOP;
        }
    }
    else
    {
        return NO_PIECE;
    }
}
