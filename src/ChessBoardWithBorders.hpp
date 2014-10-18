#ifndef _CHESSBOARDWITHBORDERS_HPP_
#define _CHESSBOARDWITHBORDERS_HPP_

#include <vector>
#include <string>
#include <memory>
#include "Square.hpp"
#include "ChessBoard.hpp"

/**
 *
 * The class represents a chessboard with all the borders around it and an additional row at the bottom (intended for arrows).
 * The purpose of this class is to arrange squares and borders ready to be pushed into
 * gridsizers in the GUI.
 *
 * The data structure is one standard vector of squares objects.
 *
 * The indices go from 0 to 109. (64 playable squares plus 16 of borders plus 10 at the bottom for arrows).
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
 * 100  101 102 103 104 105 106 107 108 109
 *
 * with corresponding coordinates of squares (from white perspective):
 *
 * 00   A0  B0  C0  D0  E0  F0  G0  H0  00
 * 08   A8  B8  C8  D8  E8  F8  G8  H8  08
 * 07   A7  B7  C7  D7  E7  F7  G7  H7  07
 * 06   A6  B6  C6  D6  E6  F6  G6  H6  06
 * 05   A5  B5  C5  D5  E5  F5  G5  H5  05
 * 04   A4  B4  C4  D4  E4  F4  G4  H4  04
 * 03   A3  B3  C3  D3  E3  F3  G3  H3  03
 * 02   A2  B2  C2  D2  E2  F2  G2  H2  02
 * 01   A1  B1  C1  D1  E1  F1  G1  H1  01
 * 00   A0  B0  C0  D0  E0  F0  G0  H0  00
 * rr   Ar  Br  Cr  Dr  Er  Fr  Gr  Hr  rr
 *
 * From black Perspective, everything is reversed except for the arrows.
 *
 * where the coordinates are given as FILERANK and  r is for arrows.
 * Note that the border squares have a "0" coordinate for their "meaningless"
 * coordinate, i.e, for the left and right borders, the file is meaningless
 * (it's out of the chessboard) but the rank is meaningful. Conversely,
 * for top and bottom borders, the rank is meaningless (0) but the file is meaningful.
 * For the arrows, the file may be meaningful (r is meaningless).
 *
 */

namespace slach
{

class ChessBoardWithBorders
{

private:

    unsigned mChessBoardSizeWithBorders;

    /**All the squares on this chessboard with the borders*/
    std::vector<Square* > mSquares;

    /**All the squares on this chessboard with the borders, ordered from top left (h1) to bottom right (a8)*/
    std::vector<Square* > mSquaresFromBlackPerspective;

    std::vector<Square* > mPlayableSquares;

    /**the underlying playable chassboard (64 squares, no borders)*/
    std::shared_ptr<ChessBoard> mpChessBoard;

public:

    /**
     * Constructor
     *
     * In the constructor, the vector mSquares is filled appropriately
     * as described in the class documentation.
     * This is done by creating and underlying ChessBoard object and initializing it.
     * Then the playable squares are taken from there.
     */
    ChessBoardWithBorders();

    /**
     * Destructor
     *
     * The pointers to the squares we created are cleared here
     */
    ~ChessBoardWithBorders();

    /**
     * Access method for the vector of squares (mSquares)
     */
    std::vector<slach::Square* > GetSquares() const;

    /**
     * Access method for the vector of squares (mSquaresFromBlackPerspective)
     * from the black perspective
     */
    std::vector<slach::Square* > GetSquaresBlackPerspective() const;


    /**
     * Access method for the underlying playable (no border) square
     * (mpChessBoard)
     */
    std::shared_ptr<ChessBoard> GetPlayableChessBoard() const;


};

}//namespace slach
#endif /* _CHESSBOARDWITHBORDERS_HPP_ */
