#ifndef _SQUARE_HPP_
#define _SQUARE_HPP_

#include <string>

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

    bool IsBorderSquare();

    bool IsCornerSquare();

    bool IsLightSquare();

    bool IsDarkSquare();

};

#endif /* _SQUARE_HPP_ */
