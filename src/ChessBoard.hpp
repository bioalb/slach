#ifndef _CHESSBOARD_HPP_
#define _CHESSBOARD_HPP_

#include <vector>
#include <string>
#include "Square.hpp"

/**
 *
 * The class represents a chessboard. The data structure is one
 * standard vector of squares objects.
 *
 * The indices go from 0 to 99. (64 playable squares plus 16 of borders).
 * A visual representation of the indices is as follows
 *
 * 0    1   2   3   4   5   6   7   8   9
 * 10   11  12  13  14  15  16  17  18  19
 * 20   21  22  23  24  25  26  27  28  29
 * 30   31  32  33  34  35  36  37  38  39
 * 40   41  42  43  44  45  46  47  48  49
 * 50   51  52  53  54  55  56  57  58  59
 * 60   61  62  63  64  65  66  67  68  69
 * 70   71  72  73  74  75  76  77  78  79
 * 80   81  82  83  84  85  86  87  88  89
 * 90   91  92  93  94  95  96  97  98  99
 *
 * with corresponding coordinates of squares (from white perspective):
 *
 * 00   A0  B0  C0  D0  E0  F0  G0  H0  00
 * 08   A8  B8  C8  D8  E8  F8  G8  H8  08
 * 07   A7  B7  C7  D7  E7  F7  G7  H7  07
 * 06   A6  B6  C6  D6  E6  F6  G6  H6  05
 * 05   A5  B5  C5  D5  E5  F5  G5  H5  05
 * 04   A4  B4  C4  D4  E4  F4  G4  H4  04
 * 03   A3  B3  C3  D3  E3  F3  G3  H3  03
 * 02   A2  B2  C2  D2  E2  F2  G2  H2  02
 * 01   A1  B1  C1  D1  E1  F1  G1  H1  01
 * 00   A0  B0  C0  D0  E0  F0  G0  H0  00
 *
 * where the coordinates are given as FILERANK.
 * Note that the border squares have a "0" coordinate for their "meaningless"
 * coordinate, i.e, for the left and right borders, the file is meaningless
 * (it's out of the chessboard) but the rank is meaningful. Conversely,
 * for top and bottom borders, the rank is meaningless (0) but the file is meaningful.
 *
 *
 */


static const unsigned CHESSBOARD_SIZE = 64u;
static const unsigned CHESSBOARD_SIZE_WB = 100u;//with border
static const unsigned FILE_SIZE = 10u;
static const unsigned RANK_SIZE = 10u;

/**
 * Typedef for a move as a pair of square objects
 * the first is the origin square, the second is the destination square
 */
typedef std::pair<Square,Square> Move;

/**
 * Typedef for a position as a vector of (pointers to) square objects
 * this is meant to be the list of squares occupied by any piece
 */
typedef std::vector<Square*> Position;

class ChessBoard
{

private:

    /**All the squares on this chessboard*/
    std::vector<Square* > mSquares;
    /**The current position on this chessboard*/
    Position mCurrentPosition;
    /**The files (columns) on this chessboard*/
    std::vector<std::string> mFiles;
    /**The ranks (rows) on this chessboard*/
    std::vector<std::string> mRanks;

    std::vector<Square* > mFirstRank;
    std::vector<Square* > mSecondRank;
    std::vector<Square* > mThirdRank;
    std::vector<Square* > mFourthRank;
    std::vector<Square* > mFifthRank;
    std::vector<Square* > mSixthRank;
    std::vector<Square* > mSeventhRank;
    std::vector<Square* > mEighthRank;


public:

    /**
     * Constructor
     */
    ChessBoard();

    /**
     * Destructor
     */
    ~ChessBoard();

    void SetupChessBoard();

    void SetupInitialChessPosition();

    std::vector<Square* > GetSquares();

    std::vector<std::string> GetFiles();

    std::vector<std::string> GetRanks();

    Position GetCurrentPosition() const;

    bool IsLegalMove();

    /**
     * Returns all the squares in a given rank
     *
     * @param rank the rank that we want the squares of
     */
    std::vector<Square* > GetOneRank(unsigned rank);
};

#endif /* _CHESSBOARD_HPP_ */
