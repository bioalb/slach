#include "Square.hpp"
#include "Exception.hpp"

Square::Square()
{
    mIsBorderSquare = false;
    mIsCornerSquare = false;
    mIsLightSquare = false;
    mIsDarkSquare = false;
    mIsCoordinatePrintable = false;
    mFile = "UNDEFINED";
    mRank = "UNDEFINED";
    mPieceOnThisSquare = NO_PIECE;
}

Square::~Square()
{

}

void Square::SetAsBorderSquare(bool border)
{
    mIsBorderSquare = border;
}

void Square::SetAsCornerSquare(bool corner)
{
    mIsCornerSquare = corner;
}

bool Square::IsBorderSquare() const
{
    return mIsBorderSquare;
}

bool Square::IsCornerSquare() const
{
    return mIsCornerSquare;
}

void Square::SetAsLightSquare(bool light)
{
    mIsLightSquare = light;
}

void Square::SetAsDarkSquare(bool dark)
{
    mIsDarkSquare = dark;
}

bool Square::IsLightSquare() const
{
    return mIsLightSquare;
}

bool Square::IsDarkSquare() const
{
    return mIsDarkSquare;
}

void Square::SetFile(std::string file)
{
    mFile = file;
}

void Square::SetRank(std::string rank)
{
    mRank = rank;
}

void Square::SetAsPrintableCoordinates(bool print)
{
    mIsCoordinatePrintable = print;
}

bool Square::IsCoordinatePrintable() const
{
    return mIsCoordinatePrintable;
}

std::string Square::GetFile() const
{
    return mFile;
}

std::string Square::GetRank() const
{
    return mRank;
}

void Square::SetPieceOnThisSquare(PieceType piece)
{
    mPieceOnThisSquare = piece;
}

PieceType Square::GetPieceOnThisSquare() const
{
    return mPieceOnThisSquare;
}

bool Square::IsSameSquare(const Square &rSquare) const
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
