#ifndef _FENHANDLER_HPP_
#define _FENHANDLER_HPP_

#include <vector>
#include <string>
#include "Square.hpp"
#include "SlachTypes.hpp"


//Forward declaration for testing
class TestFenHandler;

namespace slach
{

/**
 * A class to handle Forsyth Edwards Notation (FEN) strings.
 *
 * Reference for http://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
 */
class FenHandler
{
  friend class ::TestFenHandler;//for testing

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

    /**
     * Helper method.
     * Given a piece, it returns the corresponding letter.
     *
     * @oaram piece the input piece
     * @return a string of one character containing the corresponding letter.
     */
    std::string GetLetterFromPiece(PieceType piece) const;

  protected:
    /**
     * Helper method that checks whether the string is a valid FEN string or not.
     * Returns true of the string is a valid FEN string, false otherwise (for whatever reason).
     * This functions ignores spaces in between parts of the string...
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
     * It checks whether the string is valid. To be valid the FEN string should
     * comply with the criteria listed at
     *
     * http://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
     *
     * If not valid , this method does nothing and returns 1.
     * If it is a valid string, it will arrange the vector of squares so as to have the correct position
     * of pieces. This method ONLY changes the piece that is set on the square, not any other feature of the square.
     * (See documentation of the Square class for more info).
     * The vector of squares is intended as from a1 (first element) to h8 (last element).
     * It must have 64 non-nullptr pointer as its elements. If one of these two conditions is not met,
     * this method will return one and do nothing.
     * No re-sizing of vector or creating of objects is done in this method. It's either 64 pointers to Square objects
     * (already "newed") or this method will just do nothing and return 1.
     *
     * @param rFenString (input) the input FEN string
     * @param rSquares (output) the vector of squares that will contain the correct position of pieces.
     * @param positionFeatures (output) the features of the position
     * @return 0 if the fen string is valid and the re-arrangement of pieces was carried out successfully.
     *         1 otherwise.
     */
    int SetPositionFromFen(const std::string &rFenString, std::vector<Square* > &rSquares, FenPositionFeatures& positionFeatures);

    /**
     * Returns the Fen string corresponding to the vector of squares that is passed in
     *
     * @param pEnPassantSquare the en-passant square. Pass nullptr (default) if there is none (- will be printed)
     */
    std::string GetFenFromPosition(const std::vector<Square* > &rSquares, const FenPositionFeatures& positionFeatures) const;

    /**
     * Given a fen string, returns the position features. Used for testing
     *
     * @return the position features
     */
    FenPositionFeatures GetPositionFeaturesFromFen (const std::string & rInputfen);

};

}//namespace slach

#endif
