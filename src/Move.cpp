#include <iostream>
#include <cassert>
#include <stdio.h>
#include <ctype.h>
#include "Move.hpp"
#include "LegalMoveChecker.hpp"
#include "HelperGlobalFunctions.hpp"

slach::Move::Move()
    : mpOrigin(NULL),
      mpDestination(NULL),
      mGivesCheck(false),
      mAmbiguityPrefix(""),
      mPromotionPieceCode("Q")
{
}

slach::Move::Move(Square* pOrigin, Square* pDestination)
    : mpOrigin(pOrigin),
      mpDestination(pDestination),
      mGivesCheck(false),
      mAmbiguityPrefix(""),
      mPromotionPieceCode("Q")
{
}

slach::Move::Move (const Move& move)
  :mpOrigin (move.GetOrigin()),
   mpDestination (move.GetDestination() ),
   mGivesCheck(move.DoesMoveGiceCheck()),
   mAmbiguityPrefix(move.GetAmbiguityPrefix()),
   mPromotionPieceCode(move.GetPromotionPieceCode())
{
}

slach::Move::Move(const std::string& SanMove, std::vector<Square* > pSquares, Colour movingColour)
  : mpOrigin(NULL),
    mpDestination(NULL),
    mGivesCheck(false),
    mAmbiguityPrefix(""),
    mPromotionPieceCode("Q")
{

    if (SanMove == "O-O")
    {
        if (movingColour==WHITE)
        {
            for (unsigned i = 0; i < pSquares.size(); ++i)
            {
                if ( pSquares[i]->GetFile() == 'e' && pSquares[i]->GetRank() == '1' )
                {
                    mpOrigin = pSquares[i];
                    break;
                }
            }
            for (unsigned i = 0; i < pSquares.size(); ++i)
            {
                if ( pSquares[i]->GetFile() == 'g' && pSquares[i]->GetRank() == '1' )
                {
                    mpDestination = pSquares[i];
                    break;
                }
            }
        }
        else//black
        {
            for (unsigned i = 0; i < pSquares.size(); ++i)
            {
                if ( pSquares[i]->GetFile() == 'e' && pSquares[i]->GetRank() == '8' )
                {
                    mpOrigin = pSquares[i];
                    break;
                }
            }
            for (unsigned i = 0; i < pSquares.size(); ++i)
            {
                if ( pSquares[i]->GetFile() == 'g' && pSquares[i]->GetRank() == '8' )
                {
                    mpDestination = pSquares[i];
                    break;
                }
            }
        }
    }
    else if (SanMove == "O-O-O")
    {
        if (movingColour==WHITE)
        {
            for (unsigned i = 0; i < pSquares.size(); ++i)
            {
                if ( pSquares[i]->GetFile() == 'e' && pSquares[i]->GetRank() == '1' )
                {
                    mpOrigin = pSquares[i];
                    break;
                }
            }
            for (unsigned i = 0; i < pSquares.size(); ++i)
            {
                if ( pSquares[i]->GetFile() == 'c' && pSquares[i]->GetRank() == '1' )
                {
                    mpDestination = pSquares[i];
                    break;
                }
            }
        }
        else//black
        {
            for (unsigned i = 0; i < pSquares.size(); ++i)
            {
                if ( pSquares[i]->GetFile() == 'e' && pSquares[i]->GetRank() == '8' )
                {
                    mpOrigin = pSquares[i];
                    break;
                }
            }
            for (unsigned i = 0; i < pSquares.size(); ++i)
            {
                if ( pSquares[i]->GetFile() == 'c' && pSquares[i]->GetRank() == '8' )
                {
                    mpDestination = pSquares[i];
                    break;
                }
            }
        }
    }
    else //not a castling
    {
        std::size_t pos = SanMove.find_first_of("NBRKQ");
        std::size_t pos_of_equal = SanMove.find_first_of("=");
        if ( (pos != std::string::npos) &&  (pos_of_equal == std::string::npos))//knight, bishop, rook or  queen move (and not a promotion)
        {
            if (SanMove.length() == pos-1) return;//nothing after N, Q, etc, out of here!

            unsigned amb_offset = 0;//offset for disambiguation
            bool amb_is_letter = false;//ambiguity code is a letter;
            bool amb_is_number = false;//ambiguity code is a number;
            if ( isdigit( SanMove[pos+1] ) )
            {
                amb_offset++;
                mAmbiguityPrefix = SanMove[pos+1];
                amb_is_number = true;
            }
            else if ( islower( SanMove[pos+1] ) && islower(SanMove[pos+2]) &&  SanMove[pos+1] != 'x' )
            {
                amb_offset++;
                mAmbiguityPrefix = SanMove[pos+1];
                amb_is_letter = true;
            }

            unsigned offset = 0;
            if (SanMove[pos+amb_offset+1] == 'x')
            {
                offset ++;//make the following lines ignore the "x"
            }

            if (SanMove.length() <= pos+2+offset) return;//only one thing after N,Q,etc (and maybe the x, if any), out of here!

            char dest_file = SanMove[pos + 1 + amb_offset + offset];
            char dest_rank = SanMove[pos + 2 + amb_offset + offset];

            for (unsigned i = 0; i < pSquares.size(); ++i)
            {
                if ( (dest_file == pSquares[i]->GetFile()) && (dest_rank == pSquares[i]->GetRank() ) )
                {
                    mpDestination = pSquares[i];
                    break;
                }
            }

            if (mpDestination == NULL) return;//destination not found, invalid SAN, out of here, both pointers still NULL

            assert(mpDestination != NULL);//if we are here, it means we found the destination. We will be using this pointer

            PieceType moving_piece  = GetPieceFromCode(SanMove[pos], movingColour);

            LegalMoveChecker move_checker;

            for (unsigned i = 0; i < pSquares.size(); ++i)
            {
                if (pSquares[i]->GetPieceOnThisSquare() == moving_piece) //found the same piece...
                {

                    //... can it go to destination? i.e., is this the one that should move?
                    std::vector<unsigned> pseudo_valid_destinations = move_checker.GetAttackedSquaresFromOrigin(pSquares[i], pSquares);
                    bool found = false;
                    for (unsigned j = 0; j < pseudo_valid_destinations.size(); ++j)
                    {
                        //std::cout<<pseudo_valid_destinations[j]<<"***"<<mpDestination->GetIndexFromA1()<<"***"<<pSquares[i]->GetIndexFromA1()<<"***"<<amb_offset<<std::endl;
                        if (pseudo_valid_destinations[j] == mpDestination->GetIndexFromA1())
                        {
                            mpOrigin = pSquares[i];
                            found = true;
                            break;
                        }
                    }
                    if ( ( amb_offset == 0 || //no ambiguity or...
                         ( mAmbiguityPrefix == pSquares[i]->GetFileAsString()  && amb_is_letter == true )||
                         ( mAmbiguityPrefix == pSquares[i]->GetRankAsString() && amb_is_number ==  true) ) && found == true)
                    {
                        break;
                    }
                }
            }
        }
        else //pawn move
        {
            if (SanMove.length() < 2) return;//only one thing

            ///Settle promotion case
            std::size_t pos_of_equal = SanMove.find_first_of("=");
            if (pos_of_equal != std::string::npos) //promotion
            {
                if (pos_of_equal < ( SanMove.length() - 1))
                {
                    mPromotionPieceCode = SanMove[pos_of_equal+1];
                }
            }

            if (SanMove[1] == 'x') //pawn capture
            {
                if (SanMove.length() < 4) return;//not long enough for a pawn capture
                char dest_file = SanMove[2];
                char dest_rank = SanMove[3];
                for (unsigned i = 0; i < pSquares.size(); ++i)
                {
                    if ( (dest_file == pSquares[i]->GetFile()) && (dest_rank == pSquares[i]->GetRank() ) )
                    {
                        mpDestination = pSquares[i];
                        break;
                    }
                }
                if (mpDestination == NULL) return;//destination not found, invalid SAN, out of here, both pointers still NULL
                assert(mpDestination != NULL);//if we are here, it means we found the destination. We will be using this pointer

                char origin_file = SanMove[0];
                LegalMoveChecker move_checker;

                for (unsigned i = 0; i < pSquares.size(); ++i)
                {
                    if ((pSquares[i]->GetFile() == origin_file) &&
                         IsPawn(pSquares[i]->GetPieceOnThisSquare()) &&
                         IsPieceSameAsTurn(pSquares[i]->GetPieceOnThisSquare(),movingColour))
                    {
                        std::vector<unsigned> pseudo_valid_destinations = move_checker.GetAttackedSquaresFromOrigin(pSquares[i], pSquares);
                        for (unsigned j = 0; j < pseudo_valid_destinations.size(); ++j)
                        {
                            if (pseudo_valid_destinations[j] == mpDestination->GetIndexFromA1())
                            {
                                mpOrigin = pSquares[i];
                                break;
                            }
                        }
                    }
                }
            }
            else //regular pawn move
            {
                char dest_file = SanMove[0];
                char dest_rank = SanMove[1];
                for (unsigned i = 0; i < pSquares.size(); ++i)
                {
                    if ( (dest_file == pSquares[i]->GetFile()) && (dest_rank == pSquares[i]->GetRank() ) )
                    {
                        mpDestination = pSquares[i];
                        break;
                    }
                }

                if (mpDestination == NULL) return;//destination not found, invalid SAN, out of here, both pointers still NULL
                assert(mpDestination != NULL);//if we are here, it means we found the destination. We will be using this pointer

                unsigned  poss_origin_1 = 0;
                unsigned  poss_origin_2 = 0;
                if (movingColour == WHITE)
                {
                    if ( (mpDestination->GetIndexFromA1() < 16) )
                    {
                        mpDestination = NULL;
                        return; //destination at least third row
                    }
                    poss_origin_1 = mpDestination->GetIndexFromA1() - 8;
                    poss_origin_2 = mpDestination->GetIndexFromA1() - 16;
                }
                else
                {
                    if ( (mpDestination->GetIndexFromA1() > 47) )
                    {
                        mpDestination = NULL;
                        return; //destination at least 6th row
                    }
                    poss_origin_1 = mpDestination->GetIndexFromA1() + 8;
                    poss_origin_2 = mpDestination->GetIndexFromA1() + 16;
                }

                if ( IsPawn( pSquares[poss_origin_1]->GetPieceOnThisSquare() ) &&
                     IsPieceSameAsTurn (pSquares[poss_origin_1]->GetPieceOnThisSquare(), movingColour) )
                {
                    mpOrigin = pSquares[poss_origin_1];
                    return;
                }
                if ( IsPawn( pSquares[poss_origin_2]->GetPieceOnThisSquare() ) &&
                     IsPieceSameAsTurn (pSquares[poss_origin_2]->GetPieceOnThisSquare(), movingColour) )
                {
                    mpOrigin = pSquares[poss_origin_2];
                    return;
                }
            }//end of regular pawn move (not capture)
        }//end of pawn move


        //if we have not found the origin piece, it means something is amiss, put everything back to NULL to signal that
        //the move was not created
        if (mpOrigin == NULL)
        {
            mpDestination = NULL;
        }
    }//end of the else for "not castling move
}

slach::Move::Move (const std::string& originDestMove, std::vector<Square* > pSquares)
    : mpOrigin(NULL),
     mpDestination(NULL),
     mGivesCheck(false),
     mAmbiguityPrefix(""),
     mPromotionPieceCode("Q")
{
    //too short
    if (originDestMove.length() < 4) return;

    char origin_file = originDestMove[0];
    char origin_rank = originDestMove[1];
    char destiantion_file = originDestMove[2];
    char destiantion_rank = originDestMove[3];

    for (unsigned i = 0; i < pSquares.size(); ++i)
    {
        assert(pSquares[i] != NULL);
        if ( (pSquares[i]->GetFile() == origin_file) && (pSquares[i]->GetRank() == origin_rank))
        {
            mpOrigin = pSquares[i];
        }
        if ( (pSquares[i]->GetFile() == destiantion_file) && (pSquares[i]->GetRank() == destiantion_rank))
        {
            mpDestination = pSquares[i];
        }
    }
}
slach::Move& slach::Move::operator=(const Move& from)
{
    if (this != &from)
    {
       mpOrigin = from.GetOrigin();
       mpDestination = from.GetDestination();
       mGivesCheck = from.DoesMoveGiceCheck();
       mAmbiguityPrefix = from.GetAmbiguityPrefix();
       mPromotionPieceCode = from.GetPromotionPieceCode();
    }

    return *this;
}

slach::Move::~Move()
{
}

slach::Square* slach::Move::GetOrigin() const
{
    return mpOrigin;
}

slach::Square* slach::Move::GetDestination() const
{
    return mpDestination;
}

bool slach::Move::IsWhiteKingMoving() const
{
    if (mpOrigin->GetPieceOnThisSquare()==WHITE_KING)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool slach::Move::IsBlackKingMoving() const
{
    if (mpOrigin->GetPieceOnThisSquare()==BLACK_KING)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool slach::Move::IsWhiteCastlingKingSide() const
{
    if ((mpOrigin->GetIndexFromA1()==4u) &&
        (mpOrigin->GetPieceOnThisSquare()==WHITE_KING) &&
         mpDestination->GetIndexFromA1()==6u)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool slach::Move::IsBlackCastlingKingSide() const
{
    if ((mpOrigin->GetIndexFromA1()==60u) &&
        (mpOrigin->GetPieceOnThisSquare()==BLACK_KING) &&
         mpDestination->GetIndexFromA1()==62u)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool slach::Move::IsWhiteCastlingQueenSide() const
{
    if ((mpOrigin->GetIndexFromA1()==4u) &&
        (mpOrigin->GetPieceOnThisSquare()==WHITE_KING) &&
         mpDestination->GetIndexFromA1()==2u)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool slach::Move::IsBlackCastlingQueenSide() const
{
    if ((mpOrigin->GetIndexFromA1()==60u) &&
        (mpOrigin->GetPieceOnThisSquare()==BLACK_KING) &&
         mpDestination->GetIndexFromA1()==58u)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool slach::Move::IsSpecialMove() const
{
    return (IsWhiteCastlingKingSide() ||
            IsBlackCastlingKingSide() ||
            IsWhiteCastlingQueenSide() ||
            IsBlackCastlingQueenSide() ||
            IsWhitePromoting() ||
            IsBlackPromoting() ||
            IsKingSideWhiteRookMoving() ||
            IsQueenSideWhiteRookMoving() ||
            IsKingSideBlackRookMoving() ||
            IsQueenSideBlackRookMoving() ||
            IsBlackKingMoving() ||
            IsWhiteKingMoving()
            );
}
bool slach::Move::IsWhitePromoting() const
{
    if ((mpOrigin->GetPieceOnThisSquare()==WHITE_PAWN)&&
        (mpOrigin->IsSeventhRank()))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool slach::Move::IsBlackPromoting() const
{
    if ((mpOrigin->GetPieceOnThisSquare()==BLACK_PAWN)&&
        (mpOrigin->IsSecondRank()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool slach::Move::IsKingSideWhiteRookMoving() const
{
    if ((mpOrigin->GetPieceOnThisSquare()==WHITE_ROOK)&&
        (mpOrigin->GetIndexFromA1()==7u))//h1
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool slach::Move::IsQueenSideWhiteRookMoving() const
{
    if ((mpOrigin->GetPieceOnThisSquare()==WHITE_ROOK)&&
        (mpOrigin->GetIndexFromA1()==0u))//a1
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool slach::Move::IsKingSideBlackRookMoving() const
{
    if ((mpOrigin->GetPieceOnThisSquare()==BLACK_ROOK)&&
        (mpOrigin->GetIndexFromA1()==63u))//h8
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool slach::Move::IsQueenSideBlackRookMoving() const
{
    if ((mpOrigin->GetPieceOnThisSquare()==BLACK_ROOK)&&
        (mpOrigin->GetIndexFromA1()==56u))//h1
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool slach::Move::DoesMoveRequireSpecialGuiHandling() const
{
    return (IsWhiteCastlingKingSide() ||
            IsBlackCastlingKingSide() ||
            IsWhiteCastlingQueenSide() ||
            IsBlackCastlingQueenSide() ||
            IsWhitePromoting() ||
            IsBlackPromoting() ||
            IsWhiteCapturingEnPassant() ||
            IsBlackCapturingEnPassant()
            );
}

bool slach::Move::IsWhiteCapturingEnPassant() const
{
	if (mpOrigin->GetPieceOnThisSquare() == WHITE_PAWN &&
		mpDestination->GetPieceOnThisSquare() == NO_PIECE &&
		mpDestination->IsSixthRank() &&
		(abs(mpDestination->GetIndexFromA1() - mpOrigin->GetIndexFromA1()) == 7 ||
		 abs(mpDestination->GetIndexFromA1() - mpOrigin->GetIndexFromA1()) == 9)  )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool slach::Move::IsBlackCapturingEnPassant() const
{
	if (mpOrigin->GetPieceOnThisSquare() == BLACK_PAWN &&
		mpDestination->GetPieceOnThisSquare() == NO_PIECE &&
		mpDestination->IsThirdRank() &&
		(abs(mpDestination->GetIndexFromA1() - mpOrigin->GetIndexFromA1()) == 7 ||
		 abs(mpDestination->GetIndexFromA1() - mpOrigin->GetIndexFromA1()) == 9)  )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool slach::Move::DoesMoveGiceCheck() const
{
	return mGivesCheck;
}

void slach::Move::GivesCheck(bool gives)
{
	mGivesCheck = gives;
}

std::string slach::Move::GetAmbiguityPrefix() const
{
    return mAmbiguityPrefix;
}

void slach::Move::SetAmbiguityPrefix(std::string prefix)
{
    mAmbiguityPrefix = prefix;
}

std::string slach::Move::GetPromotionPieceCode() const
{
    return mPromotionPieceCode;
}

void slach::Move::SetPromotionPiece(const slach::PieceType& piece)
{
    if (IsQueen(piece))
    {
        mPromotionPieceCode = "Q";
    }
    if (IsRook(piece))
    {
        mPromotionPieceCode = "R";
    }
    if (IsBishop(piece))
    {
        mPromotionPieceCode = "B";
    }
    if (IsKnight(piece))
    {
        mPromotionPieceCode = "N";
    }
}


std::string slach::Move::GetMoveInAlgebraicFormat() const
{
    if (IsBlackCastlingKingSide() || IsWhiteCastlingKingSide())
    {
        return "O-O";
    }
    else if (IsBlackCastlingQueenSide() || IsWhiteCastlingQueenSide())
    {
        return "O-O-O";
    }
    else//normal move
    {
        slach::PieceType origin_piece = mpOrigin->GetPieceOnThisSquare();
        std::string piece_code = "";

        if (IsBishop(origin_piece))
        {
            piece_code="B";
        }
        else if (IsQueen(origin_piece))
        {
            piece_code = "Q";
        }
        else if (IsKing(origin_piece))
        {
            piece_code = "K";
        }
        else if(IsKnight(origin_piece))
        {
            piece_code = "N";
        }
        else if(IsRook(origin_piece))
        {
            piece_code = "R";
        }
        else if (IsPawn(origin_piece))
        {
            piece_code = "";
        }

       //work out the presence of the capture symbol
       std::string capture_symbol = "";
       if (!(mpDestination->GetPieceOnThisSquare()==NO_PIECE) ||
		   IsBlackCapturingEnPassant() ||
		   IsWhiteCapturingEnPassant() )
       {
           capture_symbol = "x";
           //if a pawn is capturing, the origin file must be included
           if ( (origin_piece == BLACK_PAWN) || (origin_piece == WHITE_PAWN) )
           {
               piece_code = mpOrigin->GetFile();
           }
       }

       std::string promotion_suffix = "";
       if (IsBlackPromoting() || IsWhitePromoting())
       {
           promotion_suffix = std::string("=") + mPromotionPieceCode;
       }

       std::string suffix;
       if (mGivesCheck == true)
       {
    	   suffix = "+";
       }
       return (piece_code + mAmbiguityPrefix + capture_symbol + mpDestination->GetFile() + mpDestination->GetRank() + promotion_suffix + suffix);
    }
}
