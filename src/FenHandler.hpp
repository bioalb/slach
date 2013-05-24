#ifndef _FENHANDLER_HPP_
#define _FENHANDLER_HPP_

#include <vector>
#include <string>
#include "Square.hpp"

/**
 * A class to handle FEN strings
 */
class FenHandler
{
  friend class TestFenHandler;//for testing

  private:
    /**
    * Helper method that assigns a piece from a character.
    *
    * R: white rook
    * r: black rook
    * P: white pawn
    * p: black pawn
    * Q: white queen
    * q: black queen
    * B: white bishop
    * b: black bishop
    * K: white king
    * k: black king
    * N: white knight
    * n: black knight
    *
    * Any other character is invalid
    *
    * @param piece (output) will be filled with the appropriate piece
    * @param character (input) the character that we want to tranform into a piece
    *
    * @return 0 if the character is valid, 1 otherwise.
    */
    int AssignPieceFromLetter(PieceType& piece, const char &character) const;

    TurnToMove mTurnToMove;

  protected:

    /**
     * Helper method that checks whether the string is a valid FEN string or not.
     * Returns true of the string is a valid FEN string, false otherwise (for whatever reason).
     *
     * @param rFenString the string to be analysed
     */
    bool IsFenValid(const std::string &rFenString) const;

  public:

    /**
     * Constructor
     */
    FenHandler();

    /**
     * Destructor
     */
    ~FenHandler();

    /**
     * This method takes in a string representing the FEN position on the chessboard.
     * It checks whether the string is valid. If not, it does nothing and returns 1.
     * If it is a valid string, it will arrange the vector of squares so as to have the correct position
     * of pieces. This method ONLY changes the piece that is set on the square, not any other feature of the square.
     * (See documentation of the Square class for more info).
     * The vector of squares is intended as from a1 (first element) to h8 (last element).
     * It must have 64 non-NULL pointer as its elements. If one of these two conditions is not met,
     * this method will return one and do nothing.
     *
     * @param rFenString (input) the input FEN string
     * @param rSquares (output) the vector of squares that will contain the correct position of pieces.
     * @return 0 if the fen string is valid and the re-arrangement of pieces was carried out successfully.
     *         1 otherwise.
     */
    int SetPositionFromFen(const std::string &rFenString, std::vector<Square* > &rSquares);

    TurnToMove WhosTurnIsIt() const;
};



#endif
