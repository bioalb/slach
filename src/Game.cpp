#include "Game.hpp"
#include "Exception.hpp"

Game::Game()
{
    mMoveList.resize(0u);
    mMoveListAlgFormat.resize(0u);
}
Game::~Game()
{

}

std::vector<Move> Game::GetMoveList() const
{
    return mMoveList;
}

std::vector<std::string> Game::GetMoveListAlgebraicFormat() const
{
    return mMoveListAlgFormat;
}

void Game::AddMove(const Move& move, std::string ambiguityPrefix, std::string suffix)
{

    Square* p_origin = move.first;
    Square* p_destination = move.second;

    PieceType origin_piece = p_origin->GetPieceOnThisSquare();
    bool empty_origin_square = false;
    std::string piece_code = "";
    switch (origin_piece)
    {
        case (BLACK_BISHOP) :
            piece_code="B";
            break;
        case (WHITE_BISHOP) :
            piece_code="B";
            break;
        case (BLACK_QUEEN) :
            piece_code="Q";
            break;
        case (WHITE_QUEEN) :
            piece_code="Q";
            break;
        case (BLACK_KING) :
            piece_code="K";
            break;
        case (WHITE_KING) :
            piece_code="K";
            break;
        case (BLACK_KNIGHT) :
            piece_code="N";
            break;
        case (WHITE_KNIGHT) :
            piece_code="N";
            break;
        case (BLACK_ROOK) :
            piece_code="R";
            break;
        case (WHITE_ROOK) :
            piece_code="R";
            break;
        case (BLACK_PAWN) :
            piece_code="";
            break;
        case (WHITE_PAWN) :
            piece_code="";
            break;
        default:
            empty_origin_square = true;
            break;
    }
    if (empty_origin_square==false)
    {
        mMoveList.push_back(move);
        std::string alg_notation = piece_code + ambiguityPrefix + p_destination->GetFile() + p_destination->GetRank() + suffix;
        mMoveListAlgFormat.push_back(alg_notation);
    }
}

