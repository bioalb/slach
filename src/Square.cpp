#include <climits>
#include <cstdlib> //std div
#include "Square.hpp"
#include "Exception.hpp"

slach::Square::Square()
{
    mIsBorderSquare = false;
    mIsCornerSquare = false;
    mIsLightSquare = false;
    mIsDarkSquare = false;
    mIsCoordinatePrintable = false;
    mFile = '0';
    mRank = '0';
    mPieceOnThisSquare = NO_PIECE;
    mIndexFromA1 = UINT_MAX;
}

slach::Square::~Square()
{

}

void slach::Square::SetAsBorderSquare(bool border)
{
    mIsBorderSquare = border;
}

void slach::Square::SetAsCornerSquare(bool corner)
{
    mIsCornerSquare = corner;
}

bool slach::Square::IsBorderSquare() const
{
    return mIsBorderSquare;
}

bool slach::Square::IsCornerSquare() const
{
    return mIsCornerSquare;
}

void slach::Square::SetAsLightSquare(bool light)
{
    mIsLightSquare = light;
    mIsDarkSquare = !light;
}

void slach::Square::SetAsDarkSquare(bool dark)
{
    mIsDarkSquare = dark;
    mIsLightSquare = !dark;
}

bool slach::Square::IsLightSquare() const
{
    return mIsLightSquare;
}

bool slach::Square::IsDarkSquare() const
{
    return mIsDarkSquare;
}

void slach::Square::SetFile(char file)
{
    if ( (file < 'a' || file >'h') && !(file=='0'))
    {
        EXCEPTION("slach::Square::SetFile: you must set one of a,b,c,d,e,f,g,h or 0 as character");
    }

    mFile = file;
}

void slach::Square::SetRank(char rank)
{

    if ( (rank < '1' || rank >'8') && !(rank=='0'))
    {
        EXCEPTION("slach::Square::SetRank: you must set one of 1,2,3,4,5,6,7,8 or 0 as character");
    }
    mRank = rank;
}

void slach::Square::SetAsPrintableCoordinates(bool print)
{
    mIsCoordinatePrintable = print;
}

bool slach::Square::IsCoordinatePrintable() const
{
    return mIsCoordinatePrintable;
}

char slach::Square::GetFile() const
{
    return mFile;
}

char slach::Square::GetRank() const
{
    return mRank;
}

int slach::Square::GetFileAsInt() const
{
    if (mIndexFromA1 > 63)
    {
        EXCEPTION("slach::Square::GetFileAsInt the square index must be initialised before calling this method");
    }
    std::div_t divresult = std::div( (int) mIndexFromA1,8);
    return divresult.rem;
}

int slach::Square::GetRankAsInt() const
{
    if (mIndexFromA1 > 63)
    {
        EXCEPTION("slach::Square::GetRankAsInt the square index must be initialised before calling this method");
    }
    std::div_t divresult = std::div( (int) mIndexFromA1,8);
    return divresult.quot;
}

std::string slach::Square::GetFileAsString() const
{
    std::string ret(1,mFile);
    return ret;
}
std::string slach::Square::GetRankAsString() const
{
    std::string ret(1,mRank);
    return ret;
}

void slach::Square::SetPieceOnThisSquare(PieceType piece)
{
    mPieceOnThisSquare = piece;
}

slach::PieceType slach::Square::GetPieceOnThisSquare() const
{
    return mPieceOnThisSquare;
}

bool slach::Square::IsSameSquare(const Square &rSquare) const
{
    if (mRank == rSquare.GetRank() && mFile == rSquare.GetFile())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void slach::Square::SetIndexFromA1(unsigned index)
{
    mIndexFromA1 = index;
}

unsigned slach::Square::GetIndexFromA1() const
{
    return mIndexFromA1;
}

int slach::Square::Getx88Index() const
{
    return 16*GetRankAsInt() + GetFileAsInt();
}

bool slach::Square::IsSecondRank() const
{
    if ( (mIndexFromA1 >7) &&  (mIndexFromA1 < 16) )
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool slach::Square::IsSeventhRank() const
{
    if ( (mIndexFromA1 >47) &&  (mIndexFromA1 < 56) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool slach::Square::IsThirdRank() const
{
    if ( (mIndexFromA1 >15) &&  (mIndexFromA1 < 24) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool slach::Square::IsSixthRank() const
{
    if ( (mIndexFromA1 >39) &&  (mIndexFromA1 < 48) )
    {
        return true;
    }
    else
    {
        return false;
    }
}
