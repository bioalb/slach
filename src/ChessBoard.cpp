#include "ChessBoard.hpp"
#include "Exception.hpp"
#include <cassert>
#include <cstdio>
#include <iostream>

ChessBoard::ChessBoard()
{
    //allocate memory for the vectors
    mSquares.resize(CHESSBOARD_SIZE);

    mFiles = {"a", "b", "c", "d", "e","f", "g",  "h"};
    mRanks = {"1", "2", "3", "4", "5","6", "7",  "8"};

    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        mSquares[i] = new Square();
    }

    mTurnToMove = WHITE;
}

ChessBoard::~ChessBoard()
{
    for (unsigned i = 0; i <mSquares.size(); ++i )
    {
        delete mSquares[i];
    }
}

std::vector<Square* > ChessBoard::GetSquares() const
{
    return mSquares;
}

void ChessBoard::SetupInitialChessPosition()
{
    for (unsigned i = 0; i < mSquares.size(); ++i)
    {
        //first rank
        if ((mSquares[i]->GetFile()==mFiles[0])&&(mSquares[i]->GetRank()==mRanks[0]))
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_ROOK);
        }
        else if ((mSquares[i]->GetFile()==mFiles[7])&&(mSquares[i]->GetRank()==mRanks[0]))
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_ROOK);
        }
        else if ((mSquares[i]->GetFile()==mFiles[1])&&(mSquares[i]->GetRank()==mRanks[0]))
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_KNIGHT);
        }
        else if ((mSquares[i]->GetFile()==mFiles[6])&&(mSquares[i]->GetRank()==mRanks[0]))
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_KNIGHT);
        }
        else if ((mSquares[i]->GetFile()==mFiles[2])&&(mSquares[i]->GetRank()==mRanks[0]))
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_BISHOP);
        }
        else if ((mSquares[i]->GetFile()==mFiles[5])&&(mSquares[i]->GetRank()==mRanks[0]))
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_BISHOP);
        }
        else if ((mSquares[i]->GetFile()==mFiles[3])&&(mSquares[i]->GetRank()==mRanks[0]))
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_QUEEN);
        }
        else if ((mSquares[i]->GetFile()==mFiles[4])&&(mSquares[i]->GetRank()==mRanks[0]))
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_KING);
        }
        //second rank, all white pawns
        else if ((mSquares[i]->GetRank()==mRanks[1])&&mSquares[i]->IsBorderSquare()==false)
        {
            mSquares[i]->SetPieceOnThisSquare(WHITE_PAWN);
        }
        //seventh rank, all black pawns
        else if(mSquares[i]->GetRank()==mRanks[6]&&mSquares[i]->IsBorderSquare()==false)
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_PAWN);
        }

        //EIGTH rank
        else if ((mSquares[i]->GetFile()==mFiles[0])&&(mSquares[i]->GetRank()==mRanks[7]))
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_ROOK);
        }
        else if ((mSquares[i]->GetFile()==mFiles[7])&&(mSquares[i]->GetRank()==mRanks[7]))
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_ROOK);
        }
        else if ((mSquares[i]->GetFile()==mFiles[1])&&(mSquares[i]->GetRank()==mRanks[7]))
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_KNIGHT);
        }
        else if ((mSquares[i]->GetFile()==mFiles[6])&&(mSquares[i]->GetRank()==mRanks[7]))
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_KNIGHT);
        }
        else if ((mSquares[i]->GetFile()==mFiles[2])&&(mSquares[i]->GetRank()==mRanks[7]))
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_BISHOP);
        }
        else if ((mSquares[i]->GetFile()==mFiles[5])&&(mSquares[i]->GetRank()==mRanks[7]))
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_BISHOP);
        }
        else if ((mSquares[i]->GetFile()==mFiles[3])&&(mSquares[i]->GetRank()==mRanks[7]))
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_QUEEN);
        }
        else if ((mSquares[i]->GetFile()==mFiles[4])&&(mSquares[i]->GetRank()==mRanks[7]))
        {
            mSquares[i]->SetPieceOnThisSquare(BLACK_KING);
        }
        else
        {
            mSquares[i]->SetPieceOnThisSquare(NO_PIECE);
        }
    }
}

void ChessBoard::SetupChessBoard()
{
    unsigned row=0;//row counter
    unsigned column=0;//column counter
    unsigned bw_counter = 0; //at zero, it will start with black (square A1).

    //will create the squares row by row, starting from bottom left (A1)
    for (unsigned index = 0; index < CHESSBOARD_SIZE; ++index)
    {
        assert(row<mRanks.size());
        assert(column<mFiles.size());
        mSquares[index]->SetFile(mFiles[column]);
        mSquares[index]->SetRank(mRanks[row]);

        if (bw_counter%2==0)
        {
            mSquares[index]->SetAsDarkSquare();
        }
        else
        {
            mSquares[index]->SetAsLightSquare();
        }
        column++;
        bw_counter++;

        if ( (column%(BOARD_ROW_SIZE)==0) )
        {
            bw_counter++;//trick the counter, end of a row and beginning of new one have same colour
            row++;
            column=0;
        }
    }
}

bool ChessBoard::IsLegalMove()
{
    return true;
}

void ChessBoard::MakeThisMove(const Move& rMove)
{
    Square* origin = rMove.first;
    Square* destination = rMove.second;

    for (unsigned i = 0; i < mSquares.size(); ++i)
    {
        if (origin->IsSameSquare((*mSquares[i])))//if we found the origin square
        {
            PieceType origin_piece = mSquares[i]->GetPieceOnThisSquare();
            mSquares[i]->SetPieceOnThisSquare(NO_PIECE);//no more piece here
            //look for the destination
            for (unsigned j = 0; j < mSquares.size(); ++j)
            {
                if (destination->IsSameSquare((*mSquares[j])))//if we found the destination square
                {
                    mSquares[j]->SetPieceOnThisSquare(origin_piece);
                    break;
                }
            }
            break;
        }
    }

}

int ChessBoard::AssignPieceFromLetter(PieceType& piece, const char &character) const
{
    int rc = 1;
    if (character == 'R')
    {
        rc =0;
        piece = WHITE_ROOK;
    }
    else if (character == 'r')
    {
        rc =0;
        piece = BLACK_ROOK;
    }
    else if (character == 'P')
    {
        rc =0;
        piece = WHITE_PAWN;
    }
    else if (character == 'p')
    {
        rc =0;
        piece = BLACK_PAWN;
    }
    else if (character == 'Q')
    {
        rc =0;
        piece = WHITE_QUEEN;
    }
    else if (character == 'q')
    {
        rc =0;
        piece = BLACK_QUEEN;
    }
    else if (character == 'B')
    {
        rc =0;
        piece = WHITE_BISHOP;
    }
    else if (character == 'b')
    {
        rc =0;
        piece = BLACK_BISHOP;
    }
    else if (character == 'K')
    {
        rc =0;
        piece = WHITE_KING;
    }
    else if (character == 'k')
    {
        rc =0;
        piece = BLACK_KING;
    }
    else if (character == 'N')
    {
        rc =0;
        piece = WHITE_KNIGHT;
    }
    else if (character == 'n')
    {
        rc =0;
        piece = BLACK_KNIGHT;
    }
    return rc;
}

bool ChessBoard::IsFenValid(const std::string &rFenPosition) const
{
    bool ret = true;
    unsigned slash_counter = 0u;
    unsigned counter_between_slashes = 0u;
    unsigned end_of_piece_position = UINT_MAX;

    for (unsigned i = 0; i < rFenPosition.length(); ++i)
    {
        if (rFenPosition[i] == '/')
        {
            if (counter_between_slashes != 8u)
            {
                ret = false;
                break;
            }
            counter_between_slashes = 0u;
            slash_counter++;
            if (slash_counter > 7u)
            {
                ret = false;
                break;
            }
            continue;//this one is a slash, no need to do anything, go to next loop.
        }
        if (counter_between_slashes > 8u)
        {
            ret = false;
            break;
        }
        //look for the last space after the position
        if ( (slash_counter == 7u) && (rFenPosition[i] == ' ') )
        {
            if (counter_between_slashes==8u)
            {
                end_of_piece_position = i;
                break;
            }
            else
            {
                ret = false;
                break;
            }
        }
        if ( isdigit (rFenPosition[i]))//if it is a number
        {
            int empty_squares = atoi (&rFenPosition[i]);//an integer now
            if ((counter_between_slashes + empty_squares) > 8)
            {
                ret = false;
                break;
            }
            for (unsigned n = 0; n < (unsigned) empty_squares; ++n)
            {
                counter_between_slashes++;
            }
        }
        else if (isalpha (rFenPosition[i]))
        {
            counter_between_slashes++;
            if (counter_between_slashes > 8u)
            {
                ret = false;
                break;
            }
            PieceType piece_to_be_assigned;
            //check the code of the piece (returns 1 if the letter is invalid)
            int valid_piece = AssignPieceFromLetter(piece_to_be_assigned, rFenPosition[i]);
            if (valid_piece != 0)
            {
                ret = false;
                break;
            }
        }
    }

    //if there were too many slashes or too few
    if ( (slash_counter != 7u))
    {
        ret = false;
    }

    //take care of the nasty case of an empty string.
    if (rFenPosition.length() == 0u)
    {
        ret = false;
    }
    if (ret ==  true) //if the string is still valid, do the last bit
    {
        bool colour_assigned = false;
        bool castling_rights_assigned = false;
        bool castling_rights_started = false;
        unsigned castling_rights_counter = 0u;
        bool enpassant_first_checked = false;
        bool enpassant_second_checked = false;
        bool enpassant_started = false;
        bool enpassant_checked = false;
        unsigned enpassant_counter = 0u;
        bool half_move_checked = false;
        bool half_move_started = false;
        bool first_half_move_checked = false;

        assert(end_of_piece_position < rFenPosition.length());
        for (unsigned i = end_of_piece_position; i < rFenPosition.length(); ++i)
        {
            if (colour_assigned ==false)
            {
                if (rFenPosition[i] == ' ')//ignore spaces
                {
                    continue;
                }

                if ( rFenPosition[i] == 'b' || rFenPosition[i] == 'w' )
                {
                    colour_assigned = true;
                    continue;
                }
                else
                {
                    ret = false;
                    break;
                }
            }
            if ((colour_assigned == true) && (castling_rights_assigned == false))
            {
                if (rFenPosition[i] == ' ' && castling_rights_started == false)
                {
                    continue;//ignore spaces before we start
                }
                if ( rFenPosition[i] == '-'  || (rFenPosition[i] == ' ' && castling_rights_started == true) )
                {
                    if (castling_rights_counter>4)
                    {
                        ret = false;
                        break;
                    }
                    else
                    {
                        castling_rights_assigned = true;
                        continue;
                    }
                }
                else if( rFenPosition[i] == 'K' || rFenPosition[i] == 'k'  || rFenPosition[i] == 'Q' || rFenPosition[i] == 'q')
                {
                    castling_rights_started = true;
                    castling_rights_counter++;
                    continue;
                }
                else
                {
                    ret = false;
                    break;
                }
            }
            if (colour_assigned == true && castling_rights_assigned == true && enpassant_checked == false)
            {
                if (rFenPosition[i] == ' ' && enpassant_started == false)
                {
                    continue;//ignore spaces before we start
                }
                if ( rFenPosition[i] == '-'  || (rFenPosition[i] == ' ' && enpassant_started == true) )
                {
                    if (enpassant_counter != 2) //two options here, either it was just a - or something is wrong
                    {
                        if (rFenPosition[i] == '-')
                        {
                            enpassant_checked = true;
                            continue;
                        }
                        else
                        {
                            ret = false;
                            break;
                        }
                    }
                    else
                    {
                        enpassant_checked = true;
                        continue;
                    }
                }
                else if( enpassant_first_checked == false )
                {
                    if ( rFenPosition[i] == 'a' || rFenPosition[i] == 'b'  || rFenPosition[i] == 'c' || rFenPosition[i] == 'd' ||
                         rFenPosition[i] == 'e' || rFenPosition[i] == 'f'  || rFenPosition[i] == 'g' || rFenPosition[i] == 'h')
                    {
                        enpassant_started = true;
                        enpassant_first_checked = true;
                        enpassant_counter++;
                        continue;
                    }
                    else
                    {
                        ret = false;
                        break;
                    }
                }
                else if( enpassant_second_checked == false )
                {
                    if ( rFenPosition[i] == '1' || rFenPosition[i] == '2'  || rFenPosition[i] == '3' || rFenPosition[i] == '4' ||
                         rFenPosition[i] == '5' || rFenPosition[i] == '6'  || rFenPosition[i] == '7' || rFenPosition[i] == '8')
                    {
                        enpassant_started = true;
                        enpassant_second_checked = true;
                        enpassant_counter++;
                        continue;
                    }
                    else
                    {
                        ret = false;
                        break;
                    }
                }
                else
                {
                    ret = false;
                    break;
                }
            }


            if (colour_assigned == true && castling_rights_assigned == true && enpassant_checked == true && half_move_checked == false)
            {
                if (rFenPosition[i] == ' ' && half_move_started == true)
                {
                    continue;//ignore spaces before we start
                }
                if ( !isdigit (rFenPosition[i]) && rFenPosition[i] != ' ')//if it is not a number or a space
                {
                    ret = false;
                    break;
                }
                else if ( ( isdigit (rFenPosition[i]) && first_half_move_checked == false ) || rFenPosition[i] == ' ')
                {
                    first_half_move_checked = true;
                    continue;
                }
                else if ( isdigit (rFenPosition[i]) && first_half_move_checked == true)
                {
                    if (rFenPosition[i-1] == ' ')
                    {
                        half_move_checked = true;
                        break;//finished reading, all good
                    }
                    else
                    {
                        ret = false;
                        break;
                    }
                }
                else
                {
                    ret = false;
                    break;
                }
            }
        }//end of for loop

        //case where there is absolutely no half or full move numbers
        if (half_move_checked==false)
        {
            ret = false;
        }
    }//end of if statement
    return ret;
}

int ChessBoard::ArrangePiecesFromFEN(const std::string &rFenPosition)
{
    int rc = 0;//return code, initialise at 0
    if (IsFenValid(rFenPosition) == false)
    {
        rc = 1;
    }
    else//it is  valid string, we operate on the member variable
    {
        unsigned rank_index= 7u;//fen starts by 8th rank
        unsigned file_index = 0u;
        unsigned square_index = CHESSBOARD_SIZE - mFiles.size() ;//56, index of a8
        unsigned slash_counter = 0u;
        unsigned counter_between_slashes = 0u;
        unsigned end_of_pos = 0;

        //parse the string character by character
        for (unsigned i = 0; i < rFenPosition.length(); ++i)
        {
            if (rFenPosition[i] == '/')
            {
                assert(counter_between_slashes == 8u); //assume valid fen string
                counter_between_slashes = 0u;
                slash_counter++;
                assert(slash_counter<=7u); //assume valid fen string
                rank_index--;
                file_index = 0;//new rank, start from file a
                square_index = square_index - 2*mFiles.size();
                continue;//this one is a slash, no need to do anything, go to next loop.
            }

            assert(counter_between_slashes <= 8u); //assume valid fen string
            if ( (slash_counter == 7u) && (rFenPosition[i] == ' ') )
            {
                assert(counter_between_slashes==8u);//assume valid fen string
                end_of_pos = i;
                break;
            }

            if ( isdigit (rFenPosition[i]))//if it is a number
            {
                int empty_squares = atoi (&rFenPosition[i]);//an integer now
                assert(counter_between_slashes + empty_squares <= 8u);//assume valid fen string
                for (unsigned n = 0; n < (unsigned) empty_squares; ++n)
                {
                    assert(square_index < CHESSBOARD_SIZE);
                    mSquares[square_index]->SetPieceOnThisSquare(NO_PIECE);
                    file_index++;
                    square_index++;
                    counter_between_slashes++;
                }
            }
            else if (isalpha (rFenPosition[i]))
            {
                counter_between_slashes++;
                assert(counter_between_slashes <= 8u);//assume valid fen string
                PieceType piece_to_be_assigned;
                //assign a piece (returns 1 if the letter is invalid)
                int valid_piece = AssignPieceFromLetter(piece_to_be_assigned, rFenPosition[i]);
                assert(valid_piece == 0);//assume valid fen string (all valid pieces)
                assert(square_index < CHESSBOARD_SIZE);
                mSquares[square_index]->SetPieceOnThisSquare(piece_to_be_assigned);
                file_index++;
                square_index++;
            }
        }

        //assume valid fen
        assert(end_of_pos > 0);
        assert(end_of_pos < rFenPosition.length());
        for (unsigned i = end_of_pos; i < rFenPosition.length(); ++i)
        {
            if (rFenPosition[i]==' ')
            {
                continue;
            }
            else
            {
                assert(rFenPosition[i]=='b' || rFenPosition[i]=='w');
                if (rFenPosition[i]=='b')
                {
                    mTurnToMove = BLACK;
                    break;
                }
                else
                {
                    mTurnToMove = WHITE;
                    break;
                }
            }
        }
    }

    return rc;
}

TurnToMove ChessBoard::WhosTurnIsIt() const
{
    return mTurnToMove;
}
