#ifndef _ChessBoardPANEL_HPP_
#define _ChessBoardPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <vector>
#include "ChessBoardWithBorders.hpp"

namespace slach_gui
{

/**
 * Major GUI class that holds the chessboard
 */
class ChessBoardPanel : public wxPanel
{

private:

	/** Directory where png of the pieces are*/
    std::string mPngPieceDirectory;
    /** Directory where png of the backgrounds are*/
    std::string mPngBackgroundDirectory;

    /** Stores pointers of the images of the pieces */
    std::vector<wxImage> mPieceImages;
    /** Stores the panels that make up the chessboard*/
    std::vector<wxPanel* > mSquarePanels;
    /** Stores the square objects of the chessboard*/
    std::vector<slach::Square* > mpAllSquares;
    /** stores the underlying chessbpard */
    slach::ChessBoardWithBorders* mpChessBoardWithBorders;
    /** Stores the playable part of the underlying chessboard */
    slach::ChessBoard* mpChessBoard;
    /** cache of the gridsizer that organizes the board*/
    wxFlexGridSizer* mpGridSizer;

    /** stores the parent frame*/
    wxFrame* mpParent;

    /** cache for the icon near the mouse for drag and drop*/
    wxIcon mIconNearTheMouse;

    /**
     * when refreshing a square of the board, sometimes you need to draw the piece
     * sometimes not. This boolean regulates the behaviour
     */
    bool mDrawPiece;

    /**
     * Upon initiation of drag and drop,
     * the index of the square where it starts is stored here
     */
    unsigned mSourceIndex;

    /**
     * Helper method to load all the images (backgrounds, pieces and coordinates)
     * this one fills up the member variable vector mPieceImages
     */
    void LoadBoardImages();

    /**
     * Helper method to paint on the border of the chessboard.
     * A check is performed whether the square corresponding to
     * squareIndex is, in fact, on the border.
     * If not, nothing is done.
     * If yes, the border is painted appropriately.
     *
     * Called by PaintOnSquare
     *
     * @param dc the device context used for drawing
     * @param squareIndex the index of the square where to paint
     */
    void PaintOnBorder(wxPaintDC& dc, unsigned squareIndex);

    /**
     * Helper method to paint a piece on the chessboard.
     * the piece to be painted is retrieved from teh square
     * corresponding to squareIndex.
     *
     * The appropriate piece is then drawn.
     * Called by PaintOnSquare.
     *
     * @param dc the device context used for drawing
     * @param squareIndex the index of the square where to paint
     */
    void PaintPiece(wxPaintDC& dc, unsigned squareIndex);

    /**
     * Helper method to paint the background of the squares of the chessboard.
     *
     * Called by PaintOnSquare.
     *
     * @param dc the device context used for drawing
     * @param squareIndex the index of the square where to paint
     */
    void PaintBackground(wxPaintDC& dc, unsigned squareIndex);

    /**
     * Helper method to figure out the image
     * of the coordinate to print on the border.
     * Called by PaintOnBorder.
     *
     * @param squareIndex the index of the square where to paint
     * @return the image of the coordinate to be printed.
     */
    wxImage DetermineCoordinateToPrint(unsigned squareIndex);

    /**
     * Helper method to figure out the image
     * of a piece given the piece itself.
     *
     * Called by PaintPiece.
     *
     * @param squareIndex the index of the square where to paint
     * @return the image of the piece to be printed.
     */
    wxImage GetImageFromPiece(slach::PieceType piece);

public:

    ChessBoardPanel(wxFrame* parent,  wxWindowID id = wxID_ANY, const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);
    ~ChessBoardPanel();

    void PaintOnSquare(wxPaintEvent& event);
    void LeftMouseClick(wxMouseEvent& event);
    void LeftMouseRelease(unsigned destinationIndex);
    void OnSize(wxSizeEvent& event);


    wxDECLARE_EVENT_TABLE();
};

}//namespace slach_gui
#endif /* _ChessBoardPANEL_HPP_ */
