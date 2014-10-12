#include <climits>
#include <cassert>
#include <iostream>
#include <sstream>
#include <cmath>
#include "Exception.hpp"
#include "HelperGlobalFunctions.hpp"
#include "FenHandler.hpp"

slach::FenHandler::FenHandler()
{
}

slach::FenHandler::~FenHandler()
{
}

bool slach::FenHandler::IsFenValid(const std::string &rFenString) const
{
    std::vector<std::size_t> row_delimiter_positions = {0};
    size_t prev_slash = 0;
    size_t next_slash = 0;
    while (next_slash != std::string::npos)
    {
        next_slash = rFenString.find('/', prev_slash+1);
        if (next_slash != std::string::npos)
        {
            row_delimiter_positions.push_back(next_slash);
            prev_slash = next_slash;
        }
    }

    //wrong number of slashes, out of here...
    if (row_delimiter_positions.size() != 8) return false;
    //add the position of the space after the last slash...
    row_delimiter_positions.push_back(rFenString.find(' ', prev_slash));

    unsigned mult = 1;
    for (unsigned i = 0; i < row_delimiter_positions.size()-1; ++i)
    {
        if (i==0) mult =0; else mult =1 ;
        std::string row = rFenString.substr(row_delimiter_positions[i] + 1*mult, row_delimiter_positions[i+1] - row_delimiter_positions[i] - 1*mult);
        unsigned counter_between_slashes = 0;
        for (unsigned j = 0; j < row.length(); ++j)
        {
            if ( isdigit (row[j]))//if it is a number
            {
                counter_between_slashes += atoi (&row[j]);
            }
            else if (isalpha (row[j]))
            {
                counter_between_slashes++;
                PieceType piece_to_be_assigned;
                //check the code of the piece (returns 1 if the letter is invalid)
                int valid_piece = AssignPieceFromLetter(piece_to_be_assigned, row[j]);
                if (valid_piece != 0) return false;
            }
            //if (isspace(row[j])) return false;//uncomment this to forbid spaces in between letters and numbers.
        }
        if (counter_between_slashes != 8) return false;
    }

    size_t start_of_to_move = rFenString.find_first_not_of(' ', row_delimiter_positions.back()+1);
    size_t end_of_to_move = rFenString.find(' ', start_of_to_move);
    std::string to_move = rFenString.substr(start_of_to_move, end_of_to_move - start_of_to_move);
    if (to_move.find_first_of("wb") == std::string::npos) return false;
    if (to_move.length() > 1) return false;

    size_t start_of_castling_rights = rFenString.find_first_not_of(' ', end_of_to_move+1);
    size_t end_of_castling_rights = rFenString.find(' ', start_of_castling_rights);
    std::string castling_rights = rFenString.substr(start_of_castling_rights, end_of_castling_rights - start_of_castling_rights);
    if (castling_rights.length() > 4) return false;

    bool no_enpassant = false;
    if (castling_rights != "-")
    {
        if (castling_rights != "--")
        {
            for (unsigned i = 0; i < castling_rights.length(); ++i)
            {

                if (castling_rights[i] != 'K' && castling_rights[i] != 'k'  && castling_rights[i] != 'Q' && castling_rights[i] != 'q')
                {
                    return false;
                }
            }
        }
        else
        {
            no_enpassant = true;
        }
    }

    size_t start_of_enpassant = rFenString.find_first_not_of(' ', end_of_castling_rights+1);
    size_t end_of_enpassant = rFenString.find(' ', start_of_enpassant);
    std::string enpassant_string = rFenString.substr(start_of_enpassant, end_of_enpassant - start_of_enpassant);
    if (enpassant_string.length()>2) return false;
    if (no_enpassant == false)
    {
            if (enpassant_string.find('-') == std::string::npos)
            {
                if (  enpassant_string.length() != 2 )
                {
                    return false;
                }
                else
                {
                    if (enpassant_string.find_first_of("abcdefgh") == std::string::npos) return false;
                    if (enpassant_string.find_first_of("36", 1) == std::string::npos) return false;
                }
            }
    }
    else //this is the case of "--" for castling rights and enpassant
    {
        end_of_enpassant = end_of_castling_rights;
    }
    size_t start_of_half_move_counter = rFenString.find_first_not_of(' ', end_of_enpassant+1);
    size_t end_of_half_mnove_counter = rFenString.find(' ', start_of_half_move_counter);
    std::string half_move_counter = rFenString.substr(start_of_half_move_counter, end_of_half_mnove_counter - start_of_half_move_counter);
    for (unsigned i=0; i < half_move_counter.length(); ++i)
    {
        if (!(isdigit (half_move_counter[i]))) return false;
    }
    size_t start_of_full_move_counter = rFenString.find_first_not_of(' ', end_of_half_mnove_counter+1);
    size_t end_of_full_mnove_counter = rFenString.find(' ', start_of_full_move_counter);
    std::string full_move_counter = rFenString.substr(start_of_full_move_counter, end_of_full_mnove_counter - start_of_full_move_counter);
    for (unsigned i=0; i < full_move_counter.length(); ++i)
    {
        if (!(isdigit (full_move_counter[i]))) return false;
    }

    return true;
}


int slach::FenHandler::AssignPieceFromLetter(PieceType& piece, const char &character) const
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

int slach::FenHandler::SetPositionFromFen(const std::string &rFenString, std::vector<Square* > &rSquares,FenPositionFeatures& positionFeatures)
{
    int rc = 0;//return code, initialise at 0

    //check the vector of squares is properly initialised (no nullptr pointers allowed)
    bool null_pointer = false;
    for (unsigned i = 0; i < rSquares.size(); ++i)
    {
        if (rSquares[i] == nullptr)
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
        unsigned end_of_colour = end_of_pos;
        for (unsigned i = end_of_pos; i < rFenString.length(); ++i)
        {
            if (rFenString[i]==' ')
            {
                continue;
            }
            else
            {
                assert(rFenString[i]=='b' || rFenString[i]=='w');//assume valid fen
                if (rFenString[i]=='b')
                {
                	positionFeatures.mTurnToMove = BLACK;
                    end_of_colour = i;
                    break;
                }
                else
                {
                	positionFeatures.mTurnToMove = WHITE;
                    end_of_colour = i;
                    break;
                }
            }
        }

        //castling rights
        positionFeatures.mCastlingRights = {};
        unsigned end_of_castling_rights = end_of_colour;
        bool castling_rights_started = false;
        for (unsigned i = end_of_colour+1; i < rFenString.length(); ++i)
        {
            if ((rFenString[i]==' ') && castling_rights_started == false)
            {
                continue;
            }
            else
            {
                castling_rights_started = true;
                if (rFenString[i]=='-')
                {
                	positionFeatures.mCastlingRights = {};
                    end_of_castling_rights = i;
                    break;
                }
                else if (rFenString[i]=='K')
                {
                	positionFeatures.mCastlingRights.push_back(WHITE_KINGSIDE);
                }
                else if (rFenString[i]=='k')
                {
                	positionFeatures.mCastlingRights.push_back(BLACK_KINGSIDE);
                }
                else if (rFenString[i]=='Q')
                {
                	positionFeatures.mCastlingRights.push_back(WHITE_QUEENSIDE);
                }
                else if (rFenString[i]=='q')
                {
                	positionFeatures.mCastlingRights.push_back(BLACK_QUEENSIDE);
                }
                else if (rFenString[i]==' ')
                {
                    end_of_castling_rights = i;
                    break;
                }
            }
        }//castling rights for loop

        unsigned end_of_enpassant = end_of_castling_rights;
        char file;
        char rank;
        bool no_enpassant = false;
        for (unsigned i = end_of_castling_rights+1; i < rFenString.length(); ++i)
        {
            if (rFenString[i]==' ')
            {
                continue;
            }
            else
            {
                if (rFenString[i]=='-')
                {
                	positionFeatures.mIndexOfEnpassant = 64u;
                    end_of_enpassant = i;
                    no_enpassant = true;
                    break;
                }
                else
                {
                    if (isalpha (rFenString[i]))
                    {
                        file = rFenString[i];
                    }
                    else if (isdigit (rFenString[i]))
                    {
                        rank =  rFenString[i];
                        end_of_enpassant = i;
                        break;//assume valid fen, after the number, it is over
                    }
                    else
                    {
                        NEVER_REACHED;//assume valid fen
                    }
                }
            }
        }
        if (no_enpassant == false)
        {
        	positionFeatures.mIndexOfEnpassant = GetIndexFromCoordinates(file, rank);
        }

        //clocks, half move and full move
        unsigned end_of_half_move = 0u;
        for (unsigned i = end_of_enpassant+1; i < rFenString.length(); ++i)
        {
            if ( isdigit (rFenString[i]) )
            {
            	positionFeatures.mHalfMoveClockSinceLastPawnMove =   atoi (&rFenString[i]);
                end_of_half_move = i;
                break;
            }
            else
            {
            	continue;//white space
            }
        }

        //after this, if the half move clock has 2 digits, the next time it will read the second digit.
        //so we wait for a space before starting the full move clock read
		unsigned start_of_full_clock = 0;
        for (unsigned i =end_of_half_move; i < rFenString.length(); ++i )
        {
			if(isspace(rFenString[i]))
			{
				start_of_full_clock = i;
				break;
			}
        }
        for (unsigned i =start_of_full_clock; i < rFenString.length(); ++i )
        {
            if ( isdigit (rFenString[i]) )
            {
            	positionFeatures.mMoveCounter = atoi (&rFenString[i]);
                break;
            }
            else
            {
                continue;//white space
            }
        }
    }
    return rc;
}

std::string slach::FenHandler::GetLetterFromPiece(PieceType piece) const
{
    if (piece == WHITE_KING)
    {
        return "K";
    }
    else if (piece == BLACK_KING)
    {
        return "k";
    }
    else if (piece == WHITE_BISHOP)
    {
        return "B";
    }
    else if (piece == BLACK_BISHOP)
    {
        return "b";
    }
    else if (piece == WHITE_ROOK)
    {
        return "R";
    }
    else if (piece == BLACK_ROOK)
    {
        return "r";
    }
    else if (piece == WHITE_QUEEN)
    {
        return "Q";
    }
    else if (piece == BLACK_QUEEN)
    {
        return "q";
    }
    else if (piece == WHITE_KNIGHT)
    {
        return "N";
    }
    else if (piece == BLACK_KNIGHT)
    {
        return "n";
    }
    else if (piece == WHITE_PAWN)
    {
        return "P";
    }
    else //(piece == BLACK_PAWN)
    {
        return "p";
    }

}
std::string slach::FenHandler::GetFenFromPosition(const std::vector<Square* > &rSquares,const FenPositionFeatures& positionFeatures) const
{
    unsigned sq_counter = 63u - 8u + 1u;//56-->a8
    unsigned empty_sq_counter = 0u;
    std::string ret = "";
    for (unsigned i =0; i < rSquares.size(); ++i)
    {
        if (rSquares[sq_counter]->GetPieceOnThisSquare() == NO_PIECE)
        {
            empty_sq_counter++;
        }
        else
        {
            if (empty_sq_counter > 0)
            {
                std::stringstream ss;
                ss << empty_sq_counter;
                ret.append(ss.str());
                empty_sq_counter = 0u;
            }
            std::string piece_letter = GetLetterFromPiece(rSquares[sq_counter]->GetPieceOnThisSquare());
            ret.append(piece_letter);
        }

        if ((sq_counter+1)%8==0)
        {
            if (empty_sq_counter>0)
            {
                std::stringstream ss;
                ss << empty_sq_counter;
                ret.append(ss.str());
            }
            if (sq_counter > 7)
            {
                ret.append("/");
            }
            sq_counter = sq_counter - 16;
            empty_sq_counter = 0u;
        }
        sq_counter++;
    }

    //Append turn to move
    if (positionFeatures.mTurnToMove==WHITE)
    {
        ret.append(" w ");
    }
    else
    {
        ret.append(" b ");
    }

    //append castling rights no spaces either before or after
    if (positionFeatures.mCastlingRights.size()==0)
    {
        ret.append("-");
    }
    else
    {
        for (unsigned i = 0; i <positionFeatures.mCastlingRights.size(); ++i)
        {
            if (positionFeatures.mCastlingRights[i] == WHITE_KINGSIDE)
            {
                ret.append("K");
            }
            if (positionFeatures.mCastlingRights[i] == BLACK_KINGSIDE)
            {
                ret.append("k");
            }
            if (positionFeatures.mCastlingRights[i] == WHITE_QUEENSIDE)
            {
                ret.append("Q");
            }
            if (positionFeatures.mCastlingRights[i] == BLACK_QUEENSIDE)
            {
                ret.append("q");
            }
        }
    }

    //append en-passant, spaces all around
    if (positionFeatures.mIndexOfEnpassant > 63)
    {
        ret.append(" - ");
    }
    else
    {
        ret.append(" ");
        ret.append(rSquares[positionFeatures.mIndexOfEnpassant]->GetFileAsString());
        ret.append(rSquares[positionFeatures.mIndexOfEnpassant]->GetRankAsString());
        ret.append(" ");
    }

    //append half move counter
    std::stringstream hm_SS;
    hm_SS << positionFeatures.mHalfMoveClockSinceLastPawnMove;
    ret.append(hm_SS.str());

    ret.append(" ");

    std::stringstream fm_SS;
    fm_SS << positionFeatures.mMoveCounter;
    ret.append(fm_SS.str());
    return ret;
}


slach::FenPositionFeatures slach::FenHandler::GetPositionFeaturesFromFen (const std::string & rInputfen)
{
    FenPositionFeatures pos_feat;
    std::vector<Square* > dummy_squares;//unused here
    dummy_squares.resize(64u);
    for (unsigned i = 0; i < dummy_squares.size(); ++i)
    {
        dummy_squares[i] = new Square();
    }

    SetPositionFromFen(rInputfen, dummy_squares, pos_feat);

    for (unsigned i = 0; i < dummy_squares.size(); ++i)
    {
       delete  dummy_squares[i];
    }
    return pos_feat;
}
