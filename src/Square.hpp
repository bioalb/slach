#ifndef _SQUARE_HPP_
#define _SQUARE_HPP_

#include <string>
#include "PieceType.hpp"

class Square
{

private:
    std::string mFile;
    std::string mRank;

    /**True if the square belongs to the border. False by  default*/
    bool mIsBorderSquare;

    /**True if it is a square in the corner*/
    bool mIsCornerSquare;

    bool mIsLightSquare;

    bool mIsDarkSquare;

    bool mIsCoordinatePrintable;

    PieceType mPieceOnThisSquare;

public:
    Square();
    ~Square();

    void SetFile(std::string file);

    void SetRank(std::string rank);

    std::string GetFile();

    std::string GetRank();

    void SetAsLightSquare(bool light = true);

    void SetAsDarkSquare(bool dark = true);

    void SetAsBorderSquare(bool border=true);

    void SetAsCornerSquare(bool border=true);

    void SetAsPrintableCoordinates(bool print = true);

    bool IsBorderSquare();

    bool IsCornerSquare();

    bool IsLightSquare();

    bool IsDarkSquare();

    bool IsCoordinatePrintable();

    void SetPieceOnThisSquare(PieceType piece);

    PieceType GetPieceOnThisSquare();

};

#endif /* _SQUARE_HPP_ */
