#include <climits>
#include "Square.hpp"
#include "Exception.hpp"

slach::Square::Square()
{
    mIsBorderSquare = false;
    mIsCornerSquare = false;
    mIsLightSquare = false;
    mIsDarkSquare = false;
    mIsCoordinatePrintable = false;
    mFile = "UNDEFINED";
    mRank = "UNDEFINED";
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

void slach::Square::SetFile(std::string file)
{
    mFile = file;
}

void slach::Square::SetRank(std::string rank)
{
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

std::string slach::Square::GetFile() const
{
    return mFile;
}

std::string slach::Square::GetRank() const
{
    return mRank;
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
