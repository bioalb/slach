#include "Game.hpp"
#include "Exception.hpp"

Game::Game()
{
    mMoveList.resize(0u);
    mMoveListAlgFormat.resize(0u);
    mSpecialMove = ORDINARY_MOVE;
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

void Game::DetermineSpecialMove(const Move& rMove)
{
    Square* p_origin = rMove.first;
    Square* p_destination = rMove.second;

    if ( (p_origin->GetFile()=="e" && p_origin->GetRank()=="1") &&
         (p_destination->GetFile()=="g" && p_destination->GetRank()=="1"))
    {
        mSpecialMove = WHITE_CASTLE_KINGSIDE;
    }
    if ( (p_origin->GetFile()=="e" && p_origin->GetRank()=="1") &&
         (p_destination->GetFile()=="c" && p_destination->GetRank()=="1"))
    {
        mSpecialMove = WHITE_CASTLE_QUEENSIDE;
    }
    if ( (p_origin->GetFile()=="e" && p_origin->GetRank()=="8") &&
         (p_destination->GetFile()=="c" && p_destination->GetRank()=="8"))
    {
        mSpecialMove = BLACK_CASTLE_QUEENSIDE;
    }
    if ( (p_origin->GetFile()=="e" && p_origin->GetRank()=="8") &&
         (p_destination->GetFile()=="g" && p_destination->GetRank()=="8"))
    {
        mSpecialMove = BLACK_CASTLE_KINGSIDE;
    }
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

        DetermineSpecialMove(move);

        if ((mSpecialMove == WHITE_CASTLE_KINGSIDE) || (mSpecialMove == BLACK_CASTLE_KINGSIDE))
        {
            mMoveListAlgFormat.push_back("O-O");
        }
        else if ((mSpecialMove == WHITE_CASTLE_QUEENSIDE) || (mSpecialMove == BLACK_CASTLE_QUEENSIDE))
        {
            mMoveListAlgFormat.push_back("O-O-O");
        }
        else//normal move
        {
            //work out the presence of the capture symbol
            std::string capture_symbol = "";
            if (p_destination->GetPieceOnThisSquare()!=NO_PIECE)
            {
                capture_symbol = "x";
                //if a pawn is capturing, the origin file must be included
                if ( (origin_piece == BLACK_PAWN) || (origin_piece == WHITE_PAWN) )
                {
                    piece_code = p_origin->GetFile();
                }
            }
            std::string alg_notation = piece_code + ambiguityPrefix + capture_symbol + p_destination->GetFile() + p_destination->GetRank() + suffix;
            mMoveListAlgFormat.push_back(alg_notation);
        }
    }
}

SpecialMoveType Game::GetSpecialMoveType() const
{
    return mSpecialMove;
}

