#ifndef _SQUARE_HPP_
#define _SQUARE_HPP_

#include <string>
#include "SlachTypes.hpp"

namespace slach
{

/**
 * Class that encapsulates a square on the chessboard
 * It can be on the playing board or one of the border squares
 */
class Square
{

private:
    /**
     * The file ("column") of this square. Initialised to '0'
     */
    char mFile;

    /**
     * The rank ("row") of this square. Initialised to '0'
     */
    char mRank;

    /**True if the square belongs to the border. False by  default*/
    bool mIsBorderSquare;

    /**True if it is a square in the corner. False by default*/
    bool mIsCornerSquare;

    /**True if it is a light square*/
    bool mIsLightSquare;

    /**True if it is a dark square*/
    bool mIsDarkSquare;

    /**True if it is a light square*/
    bool mIsCoordinatePrintable;

    /**The piece that occupies this square. Initialized to NO_PIECE*/
    PieceType mPieceOnThisSquare;

    /**
     * The index of this square on a chessboard counting from square A1 (index=0) to H8 (index = 63)
     * it is initialised to UINT_MAX in the constructor
     */
    unsigned mIndexFromA1;
    /**
     * The index of this square on a chessboard counting from top left of the board
     * INCLUDING borders.
     * Meaning that this index is zero in the border square top left of A8
     *
     * it is initialised to UINT_MAX in the constructor
     */
    unsigned mIndexFromTopLeft;

public:
    /**Constructor*/
    Square();
    /**Destructor*/
    ~Square();

    /**
     * Sets the file of the square (mFile)
     * One of a,b,c,d,e,f,g,h or 0 are allowed (case sensitive).
     * If none of the above is passed in, an exception is thrown
     *
     * @param file the char containing the file ('a' to 'h' or '0')
     */
    void SetFile(char file);

    /**
     * Sets the file of the square (mRank)
     * One of 1,2,3,4,5,6,7,8 or 0 are allowed (as characters, not numbers).
     * If none of the above is passed in, an exception is thrown
     *
     * @param rank the char containing the file ('1' to '8' or '0')
     */
    void SetRank(char rank);

    /**
     * Access the file (column on the chessboard) of this square
     *
     * @return the file as a string
     */
    char GetFile() const;

    /**
     * Access the rank (row on the chessboard) of this square
     *
     * @return the rank as a string
     */
    char GetRank() const;

    /**
     * Return the file (column on the chessboard) of this square as integer
     * (A file = 0, H file = 7).
     * It does so by examining mIndexFromA1, rather than the chracters mFile and mRank
     *
     * @return the file as an integer
     */
    int GetFileAsInt() const;

    /**
     * Return the rank (row on the chessboard) of this square as integer
     * (0 to 7)
     * It does so by examining mIndexFromA1, rather than the chracters mFile and mRank
     *
     * @return the rank as an integer
     */
    int GetRankAsInt() const;


    /**
     * Access the file (column on the chessboard) of this square and returns it as a std::string.
     * A simple convenience method
     *
     * @return a string with one character representing the file of the square
     */
    std::string GetFileAsString() const;

    /**
     * Access the rank (row on the chessboard)  of this square and returns it as a std::string.
     * A simple convenience method
     *
     * @return a string with one character representing the rank of the square
     */
    std::string GetRankAsString() const;

    /**
     * Sets this square as light (also puts the flag for dark square to false)
     *
     * @param light true if you want this square to be a light square
     */
    void SetAsLightSquare(bool light = true);

    /**
     * Sets this square as dark (also puts the flag for light square to false)
     *
     * @param dark true if you want this square to be a dark square
     */
    void SetAsDarkSquare(bool dark = true);

    /**
     * Sets this square as a border square
     *
     * @param border true if you want this square to be a border square
     */
    void SetAsBorderSquare(bool border=true);

    /**
     * Sets this square as a corner square
     *
     * @param border true if you want this square to be a corner square
     */
    void SetAsCornerSquare(bool border=true);

    /**
     * This method has  effects only on border squares.
     * Only 2 of the 4 borders of the chessboard have printed coordinates
     * @param print true if you want the coordinate to be printed.
     */
    void SetAsPrintableCoordinates(bool print = true);

    /**
     * Sets the piece that occupies this square
     *
     * @param piece the piece that you want to occupy this square.
     *        It overrides any previous piece that was there before.
     */
    void SetPieceOnThisSquare(PieceType piece);

    /**
     * Access method for the variable mIsBorderSquare
     *
     * @return true if the square is a border square
     */
    bool IsBorderSquare() const;

    /**
     * Access method for the variable mIsCornerSquare
     *
     * @return true if the square is a corner square
     */
    bool IsCornerSquare() const;

    /**
     * Access method for the variable mIsLightSquare
     *
     * @return true if the square is a light square
     */
    bool IsLightSquare() const;

    /**
     * Access method for the variable mIsDarkSquare
     *
     * @return true if the square is a dark square
     */
    bool IsDarkSquare() const;

    /**
     * Access method for the variable mIsCoordinatePrintable
     *
     * @return true if the square is flagged to have printable coordinates
     */
    bool IsCoordinatePrintable() const;

    /**
     * Access method for the variable mPieceOnThisSquare
     *
     * @return the piece that currently occupies this square
     */
    PieceType GetPieceOnThisSquare() const;

    /**
     * Return true if this square is the same as rSquare.
     * Two squares are the same if they have the same coordinates.
     *
     * @param rSquare the square we want to compare with.
     */
    bool IsSameSquare(const Square &rSquare) const;

    /**
     * Access the member variable mIndexFromA1.
     * @return the index index of this square on a chessboard counting from square A1 (index=0) to H8 (index = 63)
     */
    unsigned GetIndexFromA1() const;

    /**
     * Set the index of this square.
     * This method PERFORMS NO CHECKS. whatever is passed in, gets assigned to the mIndexFromA1
     * member variable.
     *
     * @param index the index we wish to set.
     */
    void SetIndexFromA1(unsigned index);

    /**
     * Sets the index of this square
     * counting from top left (near a8) AND including borders
     * This method PERFORMS NO CHECKS. whatever is passed in, gets assigned to the mIndexFromTopLeft
     * member variable.
     *
     * @param index the index we wish to set
     */
    void SetIndexFromTopLeft(unsigned index);

    /**
     * Gets the index of this square
     * counting from top left (near a8) AND including borders
     */
    unsigned GetIndexFromTopLeft() const;

    int Getx88Index() const;

    /**
     * Determines if the square is on the seventh rank
     * it does so by examining the Index from A1, NOT the variable mRank
     *
     * @return true if the square is on the seventh rank
     */
    bool IsSeventhRank() const;

    /**
     * Determines if the square is on the second rank
     * it does so by examining the Index from A1, NOT the variable mRank
     *
     * @return true if the square is on the second rank
     */
    bool IsSecondRank() const;

    /**
     * Determines if the square is on the third rank
     * it does so by examining the Index from A1, NOT the variable mRank
     *
     * @return true if the square is on the third rank
     */
    bool IsThirdRank() const;

    /**
     * Determines if the square is on the sixth rank
     * it does so by examining the Index from A1, NOT the variable mRank
     *
     * @return true if the square is on the sixth rank
     */
    bool IsSixthRank() const;
};

}//namespace slach
#endif /* _SQUARE_HPP_ */
