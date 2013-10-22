#ifndef _CHESSBOARD_HPP_
#define _CHESSBOARD_HPP_

#include <vector>
#include <string>
#include "Square.hpp"
#include "Game.hpp"
#include "Position.hpp"

/**
 *
 * The class represents a chessboard.
 * The data structure is one standard vector of squares objects.
 *
 * The indices go from 0 to 63. (64 playable squares).
 * A visual representation of the indices is as follows
 *
 * 0    1    2    3   4   5   6   7
 * 8    9   10   11  12  13  14  15
 * 16   17  18   19  20  21  22  23
 * 24   25  26   27  28  29  30  31
 * 32   33  34   35  36  37  38  39
 * 40   41  42   43  44  45  46  47
 * 48   49  50   51  52  53  54  55
 * 56   57  58   59  60  61  62  63

 * with corresponding coordinates of squares:
 *
 *  A1  B1  C1  D1  E1  F1  G1  H1
 *  A2  B2  C2  D2  E2  F2  G2  H2
 *  A3  B3  C3  D3  E3  F3  G3  H3
 *  A4  B4  C4  D4  E4  F4  G4  H4
 *  A5  B5  C5  D5  E5  F5  G5  H5
 *  A6  B6  C6  D6  E6  F6  G6  H6
 *  A7  B7  C7  D7  E7  F7  G7  H7
 *  A8  B8  C8  D8  E8  F8  G8  H8
 *
 */

namespace slach
{

class ChessBoard
{

private:

    /**
     * All the squares on this chessboard. This is the core variable of this class.
     * Note that each square contains information about the piece it is occupied by
     * Hence, this vector has all the info to assess a position.
     */
    std::vector<Square* > mSquares;

    Position* mpPosition;

    /**A pointer to the game object being played on this board*/
    Game* mpGame;


public:

    /**
     * Constructor
     * It allocates memory for the vector of pointers to the squares (mSquares).
     */
    ChessBoard();

    /**
     * Destructor.
     * Clears up the pointers we newed here.
     */
    ~ChessBoard();

    /**
     * This method essentially sets up the squares in the chessboard.
     * It assigns coordinate to each square according to class documentation
     */
    void SetupChessBoard();

    /**
     * This method does the following things:
     *
     * 1) set the current FEN position (mCurrentFenPosition) to be the initial chess position
     * 2) Uses the FEN handler to arrange the pieces on the borda by modifying mSquares.
     */
    void SetupInitialChessPosition();

    /**
     * Returns a vector of (pointers to) squares for this chessboard
     * It is an access method for the variable mSquares
     */
    std::vector<slach::Square* > GetSquares() const;

    bool IsLegalMove(Move& rMove);

    /**
     * Updates the current position (vector mSquares) with the move that is passed in.
     * Does NOT check for legality of the move.
     *
     * @param rMove reference to the move we wish to make
     */
    void MakeThisMove(Move& rMove);

    /**
     * Modifies the pieces position on the chessboard according to the given FEN position.
     * It does nothing if the fen string is invalid
     *
     * @param &rFenPosition the position we want on this chessboard
     *
     * @return 0 if the fen string is valid, 1 if it is not a valid one
     */
    int SetFenPosition(const std::string &rFenPosition);

    /**
     * Access method for the member variable mTurnToMove
     *
     * @return BLACK if it's black's turn, WHITE otherwise
     */
    slach::Colour WhosTurnIsIt() const;

    /**
     * this one queries the position object and gives the current move number
     *
     * @return the current move number
     */
    unsigned GetCurrentMoveNumber() const;

    /**
     * Access method for the variable mCurrentFenPosition
     *
     * @return a string containing the current FEN position.
     *         the string is guaranteed to be a valid FEN.
     */
    std::string GetCurrentFenPosition() const;


    /**
     * Resets the chessboard to the move number moveNumber
     *
     * @param moveNumber the move number we want to go back to.
     *          This is intended to be 1 at the start of the game. If a number greater than the current move numbe ris supplied,
     *          than the latest position is set (i.e., no effect).
     * @param colour the colour to move
     */
    void ResetToMoveNumber(int moveNumber, slach::Colour colour);

    /**
     * Access method for the variable storing the info on the
     * game being played on this board.
     *
     * @return a pointer to the game.
     */
    Game* GetGame() const;

    PgnValidity LoadGameFromPgn(const std::string& gameString);

    /**
     * Allows ot set a promotion piece different from the queen.
     * It throws an exception if you set a pawn
     *
     * @param piece the promotion piece. Colour will be assigned automatically
     */
    void SetPromotionPiece(slach::PieceType piece);

    Position* GetCurrentPosition() const;

    /**
     * Moves back one move. If no previous move exists, it will return the first position
     */
    void ResetToPreviousMove();

    /**
     * Moves one move forward. If no move exists, it will return the last position
     */
    void ResetToNextMove();
};

}//namespace slach
#endif /* _CHESSBOARD_HPP_ */
