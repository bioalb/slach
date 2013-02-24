#include "Square.hpp"

Square::Square()
{
    mIsBorderSquare = false;
    mIsCornerSquare = false;
    mIsLightSquare = false;
    mIsDarkSquare = false;
    mFile = "UNDEFINED";
    mRank = "UNDEFINED";
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

bool Square::IsBorderSquare()
{
    return mIsBorderSquare;
}

bool Square::IsCornerSquare()
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

bool Square::IsLightSquare()
{
    return mIsLightSquare;
}

bool Square::IsDarkSquare()
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

std::string Square::GetFile()
{
    return mFile;
}

std::string Square::GetRank()
{
    return mRank;
}
