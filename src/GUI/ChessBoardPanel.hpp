#ifndef _ChessBoardPANEL_HPP_
#define _ChessBoardPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/vscroll.h>
#include <wx/textctrl.h>
#include <wx/richtext/richtextctrl.h>
#include <vector>
#include <memory>
#include "IDContainer.hpp"
#include "ChessBoardWithBorders.hpp"

namespace slach_gui
{


class ChessBoardPanel : public wxPanel
{

private:

    wxPanel* mpParent;

    /**tells whether this is the main board or a secondary one, true by default*/
    bool mIamTheMainBoard;

	/** Directory where png of the pieces are*/
    std::string mPngPieceDirectory;

    /** Stores pointers of the images of the pieces */
    std::vector<wxImage> mPieceImages;

    /** Stores the panels that make up the chessboard*/
    std::vector<wxPanel* > mSquarePanels;
    /** Stores the square objects of the chessboard*/
    std::vector<slach::Square* > mpAllSquares;
    /** stores the underlying chessboard */
    std::shared_ptr<slach::ChessBoardWithBorders> mpChessBoardWithBorders;
    /** Stores the playable part of the underlying chessboard */
    std::shared_ptr<slach::ChessBoard> mpChessBoard;
    /**this is the number of half moves that the "fast forward" arrow will move (also fast backward arrow)*/
    unsigned mNumberOfMovesFastForward;
    /** cache of the gridsizer that organizes the board*/
    wxFlexGridSizer* mpBoardGridSizer;


    /**
     * when refreshing a square of the board, sometimes you need to draw the piece
     * sometimes not. This boolean regulates the behaviour
     */
    bool mDrawPiece;

    /**
     * A flag to signal when a game is loaded from pgn
     */
    bool mGameIsLoaded;

    /**
     * A flag to keep track where the perspective is from
     * True by default
     */
    bool mPerspectiveIsFromWhite;

    /**
     * Upon initiation of drag and drop,
     * the index of the square where it starts is stored here
     */
    unsigned mSourceIndex;

    /**
     * Cache for the destination square
     */
    unsigned mDestinationIndex;


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
     * of a piece given the piece itself.
     *
     * Called by PaintPiece.
     *
     * @param squareIndex the index of the square where to paint
     * @return the image of the piece to be printed.
     */
    wxImage GetImageFromPiece(slach::PieceType piece);


    /**
     * Private helper method to encapsulate all the times we need to communicate an update in chess position to the
     * computer, e.g., when drawing a fen, when drag and drop occurs...
     */
    void DoCommunicateTheCurrentPositionForEngine();

    void ClearCurrentHighlighting();

public:

    /**
     * Constructor. Initializes all member variables.
     * Create all teh children panel (the squares) and puts them
     * in the gridsizer.
     * Initialization of the target for the drag and drop also happens here.
     *
     * @param parent the parent frame
     * @param id the window ID (defaults to wx/ID_ANY)
     * @param pos the position of this panel (defaults to wxDefaultPosition)
     * @param size the size of this panel in pixel (wxDefaultSize)
     */
    ChessBoardPanel(wxPanel* parent,  wxWindowID id = wxID_ANY, const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);

    /**
     * Destructor
     */
    ~ChessBoardPanel();

    /**
     * Main method to draw the chessboard and the pieces.
     * Captured as PaintEvent, it figures out which object (square panel)
     * has generated the event and paint on it accordingly.
     * To do so, it examines various member variables including mDrawPiece.
     * The children panel of this class (the squares) connects their paint event to this method.
     * It calls several private helper methods (PaintBackground, PaintPiece and PaintOnBorder)
     *
     * @param event the paint event
     */
    void PaintOnSquare(wxPaintEvent& event);

    /**
     * This method captures the initiation of the drag and drop between squares.
     * The children panel of this class (the squares) connects their mouse event to this method.
     *
     * @param event the mouse click event
     */
    void LeftMouseClick(wxMouseEvent& event);

    /**
     * This method captures the click on the flip view buttoon
     *
     * @param event the mouse click event
     */
    void FlipView (wxMouseEvent& event);


    void ResetToInitialPosition(wxCommandEvent& event);


    void DoFlipView();

    bool IsItFromWhitePerspective() const;

    /**
     * this method is activated when user clicks on one of the arrows.
     * It figures out which arrow the use clicked and behaves accordingly.
     *
     * @param event the generating event
     */
    void ArrowButtonMovement(wxMouseEvent& event);

    void PaintArrows(wxPaintEvent& event);

    void DrawAndSetFenPositionOnBoard(const std::string& rFenPosition);

    void DoAdvanceOneMove();
    void DoAdvanceSeveralMoves();
    void DoAdvanceUntilEnd();
    void DoGoBackOneMove();
    void DoGoBackSeveralMoves();
    void DoGoBackToBeginning();

    /**
     * This method captures the mouse release for drag and drop.
     * It gets called by a DropTargetPanel (where the user released the mouse).
     * Since mSourceIndex was already stored, obtaining the index of the destination
     * square completes the information we need to generate a move.
     *
     * This is done in this method that contains the logic to repaint the necessary pieces
     * according to the move. It also calls the legal move checker to see if it is valid.
     *
     * @param destinationIndex the index of the destination square
     */
    void LeftMouseRelease(wxMouseEvent& event);

    void ProcessMoveInGui(slach::Move & move);

    /**
     * Provide access to the underlying playable chessboard object.
     */
    std::shared_ptr<slach::ChessBoard> GetChessBoard();

    /**
     * Resizing method. It figures out the new size and resize everything accordingly.
     *
     */
    void OnSize(wxSizeEvent& event);

    /**
     * Sets whether this is the main board or not.
     * Changes the variable mIamTheMainBoard
     */
    void SetAsMainBoard(bool flag = true);

    /**
     * Specifies what to do when mouse enters the area of one of the arrows,
     * i.e., change background colour
     *
     * @param event the mouse event
     */
    void OnMouseEnteringArrowPanel(wxMouseEvent& event);

    /**
     * Specifies what to do when mouse leaves the area of one of the arrows
     * i.e., restore background colour
     *
     * @param event the mouse event
     */
    void OnMouseLeavingArrowPanel(wxMouseEvent& event);

};

}//namespace slach_gui
#endif /* _ChessBoardPANEL_HPP_ */
