#include <climits>
#include <cassert>
#include <iostream>
#include <sstream>
#include "FenHandler.hpp"

FenHandler::FenHandler()
{

}

FenHandler::~FenHandler()
{

}

bool FenHandler::IsFenValid(const std::string &rFenString) const
{
    bool ret = true;
    unsigned slash_counter = 0u;
    unsigned counter_between_slashes = 0u;
    unsigned end_of_piece_position = UINT_MAX;

    for (unsigned i = 0; i < rFenString.length(); ++i)
    {
        if (rFenString[i] == '/')
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
        if ( (slash_counter == 7u) && (rFenString[i] == ' ') )
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
        if ( isdigit (rFenString[i]))//if it is a number
        {
            int empty_squares = atoi (&rFenString[i]);//an integer now
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
        else if (isalpha (rFenString[i]))
        {
            counter_between_slashes++;
            if (counter_between_slashes > 8u)
            {
                ret = false;
                break;
            }
            PieceType piece_to_be_assigned;
            //check the code of the piece (returns 1 if the letter is invalid)
            int valid_piece = AssignPieceFromLetter(piece_to_be_assigned, rFenString[i]);
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
    if (rFenString.length() == 0u)
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

        assert(end_of_piece_position < rFenString.length());
        for (unsigned i = end_of_piece_position; i < rFenString.length(); ++i)
        {
            if (colour_assigned ==false)
            {
                if (rFenString[i] == ' ')//ignore spaces
                {
                    continue;
                }

                if ( rFenString[i] == 'b' || rFenString[i] == 'w' )
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
                if (rFenString[i] == ' ' && castling_rights_started == false)
                {
                    continue;//ignore spaces before we start
                }
                if ( rFenString[i] == '-'  || (rFenString[i] == ' ' && castling_rights_started == true) )
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
                else if( rFenString[i] == 'K' || rFenString[i] == 'k'  || rFenString[i] == 'Q' || rFenString[i] == 'q')
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
                if (rFenString[i] == ' ' && enpassant_started == false)
                {
                    continue;//ignore spaces before we start
                }
                if ( rFenString[i] == '-'  || (rFenString[i] == ' ' && enpassant_started == true) )
                {
                    if (enpassant_counter != 2) //two options here, either it was just a - or something is wrong
                    {
                        if (rFenString[i] == '-')
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
                    if ( rFenString[i] == 'a' || rFenString[i] == 'b'  || rFenString[i] == 'c' || rFenString[i] == 'd' ||
                         rFenString[i] == 'e' || rFenString[i] == 'f'  || rFenString[i] == 'g' || rFenString[i] == 'h')
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
                    if ( rFenString[i] == '1' || rFenString[i] == '2'  || rFenString[i] == '3' || rFenString[i] == '4' ||
                         rFenString[i] == '5' || rFenString[i] == '6'  || rFenString[i] == '7' || rFenString[i] == '8')
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
                if (rFenString[i] == ' ' && half_move_started == true)
                {
                    continue;//ignore spaces before we start
                }
                if ( !isdigit (rFenString[i]) && rFenString[i] != ' ')//if it is not a number or a space
                {
                    ret = false;
                    break;
                }
                else if ( ( isdigit (rFenString[i]) && first_half_move_checked == false ) || rFenString[i] == ' ')
                {
                    first_half_move_checked = true;
                    continue;
                }
                else if ( isdigit (rFenString[i]) && first_half_move_checked == true)
                {
                    if (rFenString[i-1] == ' ')
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


int FenHandler::AssignPieceFromLetter(PieceType& piece, const char &character) const
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


int FenHandler::SetPositionFromFen(const std::string &rFenString, std::vector<Square* > &rSquares)
{
    int rc = 0;//return code, initialise at 0

    //check the vector of squares is properly initialised (no NULL pointers allowed)
    bool null_pointer = false;
    for (unsigned i = 0; i < rSquares.size(); ++i)
    {
        if (rSquares[i] == NULL)
        {
            null_pointer = true;
            break;
        }
    }

    if ( (IsFenValid(rFenString) == false) || (rSquares.size() != 64u) || null_pointer == true)
    {
        rc = 1;
    }
    else//it is  valid string, we operate on the member variable
    {
        unsigned rank_index= 7u;//fen starts by 8th rank
        unsigned file_index = 0u;
        unsigned square_index = 64u - 8u ;//56, index of a8
        unsigned slash_counter = 0u;
        unsigned counter_between_slashes = 0u;
        unsigned end_of_pos = 0;

        //parse the string character by character
        for (unsigned i = 0; i < rFenString.length(); ++i)
        {
            if (rFenString[i] == '/')
            {
                assert(counter_between_slashes == 8u); //assume valid fen string
                counter_between_slashes = 0u;
                slash_counter++;
                assert(slash_counter<=7u); //assume valid fen string
                rank_index--;
                file_index = 0;//new rank, start from file a
                square_index = square_index - 2*8u;
                continue;//this one is a slash, no need to do anything, go to next loop.
            }

            assert(counter_between_slashes <= 8u); //assume valid fen string
            if ( (slash_counter == 7u) && (rFenString[i] == ' ') )
            {
                assert(counter_between_slashes==8u);//assume valid fen string
                end_of_pos = i;
                break;
            }

            if ( isdigit (rFenString[i]))//if it is a number
            {
                int empty_squares = atoi (&rFenString[i]);//an integer now
                assert(counter_between_slashes + empty_squares <= 8u);//assume valid fen string
                for (unsigned n = 0; n < (unsigned) empty_squares; ++n)
                {
                    assert(square_index < 64u);
                    rSquares[square_index]->SetPieceOnThisSquare(NO_PIECE);
                    file_index++;
                    square_index++;
                    counter_between_slashes++;
                }
            }
            else if (isalpha (rFenString[i]))
            {
                counter_between_slashes++;
                assert(counter_between_slashes <= 8u);//assume valid fen string
                PieceType piece_to_be_assigned;
                //assign a piece (returns 1 if the letter is invalid)
                int valid_piece = AssignPieceFromLetter(piece_to_be_assigned, rFenString[i]);
                assert(valid_piece == 0);//assume valid fen string (all valid pieces)
                assert(square_index < 64u);
                rSquares[square_index]->SetPieceOnThisSquare(piece_to_be_assigned);
                file_index++;
                square_index++;
            }
        }

        //assume valid fen
        assert(end_of_pos > 0);
        assert(end_of_pos < rFenString.length());
        for (unsigned i = end_of_pos; i < rFenString.length(); ++i)
        {
            if (rFenString[i]==' ')
            {
                continue;
            }
            else
            {
                assert(rFenString[i]=='b' || rFenString[i]=='w');
                if (rFenString[i]=='b')
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

std::string FenHandler::GetFenFromPosition(const std::vector<Square* > &rSquares,
        TurnToMove turnToMove,
        std::vector<CastlingRights> castlingRights,
        Square* pEnPassantSquare,
        unsigned halfMoveClock,
        unsigned fullMoveNumber) const
{
    unsigned sq_counter = 63u - 8u + 1u;//56-->a8
    unsigned empty_sq_counter = 0u;
    std::string ret = "";
    for (unsigned i =0; i < rSquares.size(); ++i)
    {
        std::cout<<sq_counter<<std::endl;

        if (rSquares[i]->GetPieceOnThisSquare() == NO_PIECE)
        {
            empty_sq_counter++;
        }
        else
        {

        }
        if ((sq_counter+1)%8==0)
        {
            std::stringstream ss;
            ss << empty_sq_counter;
            ret.append(ss.str());
            ret.append("/");
            sq_counter = sq_counter - 16;
            empty_sq_counter = 0u;
        }
        sq_counter++;

    }
    return ret;
}

TurnToMove FenHandler::WhosTurnIsIt() const
{
    return mTurnToMove;
}
