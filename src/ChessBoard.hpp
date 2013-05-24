#ifndef _CHESSBOARD_HPP_
#define _CHESSBOARD_HPP_

#include <vector>
#include <string>
#include "Square.hpp"
#include "Game.hpp"
#include "FenHandler.hpp"

/**
 *
 * The class represents a chessboard. The data structure is one
 * standard vector of squares objects.
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

static const unsigned CHESSBOARD_SIZE_WB = 100u;
static const unsigned CHESSBOARD_SIZE = 64u;
static const unsigned BOARD_ROW_SIZE = 8u;
static const unsigned BOARD_COLUMN_SIZE = 8u;



class ChessBoard
{

    friend class TestChessBoard; //for testing

private:

    /**
     * All the squares on this chessboard. This is core variable of this class.
     * Note that each square contains information about the piece it is occupied by
     * Hence, this vector has all the info to assess a position.
     * */
    std::vector<Square* > mSquares;

    /**The files (columns) on this chessboard*/
    std::vector<std::string> mFiles;
    /**The ranks (rows) on this chessboard*/
    std::vector<std::string> mRanks;

    /** Stores whether it is white's or balck's turn*/
    TurnToMove mTurnToMove;

    FenHandler* mpFenHandler;

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

    void SetupInitialChessPosition();

    /**
     * Returns a vector of (pointers to) squares for this chessboard
     * It is an access method for the variable mSquares
     */
    std::vector<Square* > GetSquares() const;

    bool IsLegalMove();

    /**
     * Updates the current position (vector mSquares) with the move that is passed in.
     * Does NOT check for legality of the move.
     *
     * @param rMove reference to the move we wish to make
     */
    void MakeThisMove(const Move& rMove);

    /**
     * Modifies the pieces position on the chessboard according to the given FEN position.
     * It does nothing if the fen string is invalid
     *
     * @param &rFenPosition the position we want on this chessboard
     *
     * @return 0 if the fen string is valid, 1 if it is not a valid one
     */
    int ArrangePiecesFromFEN(const std::string &rFenPosition);

    /**
     * Access method for the member variable mTurnToMove
     *
     * @return BLACK if it's black's turn, WHITE otherwise
     */
    TurnToMove WhosTurnIsIt() const;


};

#endif /* _CHESSBOARD_HPP_ */
