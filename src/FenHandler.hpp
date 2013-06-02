#ifndef _FENHANDLER_HPP_
#define _FENHANDLER_HPP_

#include <vector>
#include <string>
#include "Square.hpp"

/**
 * A class to handle Forsyth Edwards Notation (FEN) strings.
 *
 * Reference for http://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
 */

class TestFenHandler;

namespace slach
{

/**
 * A class to handle FEN strings
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

    /**
     * Stores the turn to move,Set upon calling SetPositionFromFen
     */
    TurnToMove mTurnToMove;

    /**Stores the castling rights. Set upon calling SetPositionFromFen*/
    std::vector<CastlingRights> mCastlingRights;
    /**
     * Stores the index of the en-passant square, if any. Set upon calling SetPositionFromFen.
     * It refers to the index of a square on a chessboard starting from A1 (0->63).
     * If there is no en-passant, its value is 64 (out of the chessboard)
     */
    unsigned mEnPassantSquare;
    /**Stores the half-move clock Set upon calling SetPositionFromFen*/
    unsigned mHalfMoveClock;
    /**Stores the full-move clock Set upon calling SetPositionFromFen*/
    unsigned mFullMoveClock;

  protected:
    /**
     * Helper method that checks whether the string is a valid FEN string or not.
     * Returns true of the string is a valid FEN string, false otherwise (for whatever reason).
     *
     * @param rFenString the string to be analysed
     */
    bool IsFenValid(const std::string &rFenString) const;

    /**
     * Helper method that returns the index (counting on a chessboard from A1 to H8, from 0 to 63)
     * corresponding to the char coordinates
     *
     * @param  rFile the file of the coordinate (column), a to h
     * @param rRank the rank of the coordinate (row) 1 to 8
     * @return the index if rank and files are appropriate, 64 (out of the chessboard) otherwise
     */
    unsigned GetIndexFromCoordinates(const char &rFile, const char &rRank) const;

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
     * It must have 64 non-NULL pointer as its elements. If one of these two conditions is not met,
     * this method will return one and do nothing.
     * No re-sizing of vector or creating of objects is done in this method. It's either 64 pointers to Square objects
     * (already "newed") or this method will just do nothing and return 1.
     *
     * @param rFenString (input) the input FEN string
     * @param rSquares (output) the vector of squares that will contain the correct position of pieces.
     * @return 0 if the fen string is valid and the re-arrangement of pieces was carried out successfully.
     *         1 otherwise.
     */
    int SetPositionFromFen(const std::string &rFenString, std::vector<Square* > &rSquares);

    /**
     * Returns the Fen string corresponding to the vector of squares that is passed in
     *
     * @param pEnPassantSquare the en-passant square. Pass NULL (default) if there is none (- will be printed)
     */
    std::string GetFenFromPosition(const std::vector<Square* > &rSquares,
            TurnToMove turnToMove,
            std::vector<CastlingRights> castlingRights,
            Square* pEnPassantSquare = NULL,
            unsigned halfMoveClock = 0,
            unsigned fullMoveNumber = 0) const;

    /**
     * Access method for the variable mTurnToMove. Refers to the last valid fen that
     * was passed to SetPositionFromFen
     *
     * @return BLACK if it is black's turn to move, WHITE if it is white
     */
    slach::TurnToMove WhosTurnIsIt() const;

    /**
     * Access the member variable mCastlingRights
     *
     * @return a vector containing the castling rights set the last time SetPositionFromFen was called.
     *         if it is empty, it means there are no castling rights
     */
    std::vector<slach::CastlingRights> GetLatestCastlingRights() const;


    /**
     * Access the member variable mEnPassantSquare
     *
     * @return the index of the square available for enpassant (starting from A1 to H8, 0 to 63)
     *         as per the last time SetPositionFromFen was called.
     *         if it returns 64 (out of the chessboard), it means there are no enpassant squares
     */
    unsigned GetEnPassantSquareIndex() const;

    /**
     * Access the member variable mHalfMoveClock
     *
     * @return the number of half moves since the last pawn move
     *         as per the last time SetPositionFromFen was called.
     */
    unsigned GetHalfMoveClock() const;

    /**
     * Access the member variable mFullMoveClock
     *
     * @return the number of moves so far as per the last time SetPositionFromFen was called.
     */
    unsigned GetFullMoveClock() const;


};

}//namespace slach

#endif
