#ifndef _ChessBoardPANEL_HPP_
#define _ChessBoardPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/vscroll.h>
#include <wx/textctrl.h>
#include <wx/richtext/richtextctrl.h>
#include <vector>
#include "ChessBoardWithBorders.hpp"

namespace slach_gui
{

/**
 * Major GUI class that holds the chessboard
 */

static const int ID_LEFT_OF_BOARD = 50;
static const int ID_ACTUAL_BOARD = 51;
static const int ID_RIGHT_OF_BOARD = 52;
static const int ID_OF_ARROW_SPACE = 53;
static const int ID_FORWARD_BUTTON = 55;
static const int ID_BACKWARD_BUTTON = 56;
static const int ID_FORWARD_MORE_BUTTON = 57;
static const int ID_BACKWARD_MORE_BUTTON = 58;
static const int ID_FORWARD_END_BUTTON = 59;
static const int ID_BACKWARD_END_BUTTON = 60;
static const int ID_OF_UPPER_PLAYER_NAME = 61;
static const int ID_OF_BOTTOM_PLAYER_NAME = 62;
static const int ID_OF_MOVE_LIST_SPACE = 63;
static const int ID_WHITE_PLAYER_BOX = 64;
static const int ID_BLACK_PLAYER_BOX = 65;
static const int ID_ABOVE_WHITE_PLAYER_NAME = 66;
static const int ID_BELOW_WHITE_PLAYER_NAME = 67;
static const int ID_ABOVE_BLACK_PLAYER_NAME = 68;
static const int ID_BELOW_BLACK_PLAYER_NAME = 69;
static const int OFFSET_OF_MOVE_LIST_ID = 1100;
static const int OFFSET_OF_MOVE_NUMBER_ID = 1300;

static const int MAX_NUMBER_OF_VISIBLE_MOVES = 20;//in the movelist window, this is the max number visible (no-scroll)


class ChessBoardPanel : public wxPanel
{

private:

	/** Directory where png of the pieces are*/
    std::string mPngPieceDirectory;
    /** Directory where png of the backgrounds are*/
    std::string mPngBackgroundDirectory;
    /** Directory where the png of the arrows are*/
    std::string mPngArrowsDirectory;

    /** Stores pointers of the images of the pieces */
    std::vector<wxImage> mPieceImages;
    /** Stores pointers of the images of the arrows */
    std::vector<wxImage> mArrowImages;

    /** Stores the panels that make up the chessboard*/
    std::vector<wxPanel* > mSquarePanels;
    /** Stores the square objects of the chessboard*/
    std::vector<slach::Square* > mpAllSquares;
    /** stores the underlying chessbpard */
    slach::ChessBoardWithBorders* mpChessBoardWithBorders;
    /** Stores the playable part of the underlying chessboard */
    slach::ChessBoard* mpChessBoard;
    /** cache of the gridsizer that organizes the board*/
    wxFlexGridSizer* mpBoardGridSizer;
    /** cache for the sizer of the arrows buttons*/
    wxBoxSizer* mpSizerForArrows;
    /**cahce for the sizer of the space containing the move list*/
    wxFlexGridSizer* mpMoveListSizer;
    /**The main sizer that decides where the board is*/
    wxBoxSizer* mpPrincipalSizer;
    wxBoxSizer* mpRightSideSizer;

    /** Stores the panels that show the move list*/
    std::vector<wxTextCtrl* > mMoveListPanels;

    /** The space on the left of the board*/
    wxPanel* mpLeftOfChessBoard;
    /** A panel that will contain the board*/
    wxPanel* mpMidPanelOfChessBoard;
    /** The space on the right of the board*/
    wxPanel* mpRightOfChessBoard;

    /**Panels fon the RHS of the board*/
    wxPanel* mpSpaceForArrows;
    wxPanel* mpNameOfPlayerTop;
    wxPanel* mpNameOfPlayerBottom ;
    wxScrolledWindow* mpSpaceForMoveList;

    /**Panels for each arrows*/
    wxPanel* mpForwardArrowPanel;
    wxPanel* mpForwardArrowPanelMore;
    wxPanel* mpForwardArrowPanelEnd;
    wxPanel* mpBackwardArrowPanel;
    wxPanel* mpBackwardArrowPanelMore;
    wxPanel* mpBackwardArrowPanelEnd;

    /**Text control for the players' names*/
    wxTextCtrl * mpWhitePlayerBox;
    wxTextCtrl * mpBlackPlayerBox;

    wxTextAttr mTextAttributesPlayerNames;

    /** stores the parent frame*/
    wxFrame* mpParent;

    /** cache for the icon near the mouse for drag and drop*/
    wxIcon mIconNearTheMouse;

    wxString mWhitePlayerName;
    wxString mBlackPlayerName;

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
     * Upon initiation of drag and drop,
     * the index of the square where it starts is stored here
     */
    unsigned mSourceIndex;

    /**
     * HElper method that goes into the text control of the white and black player
     * Delete the content and write the names according to mWhitePlayerName and mBlackPlayerName
     * The text attributes are the ones set by mTextAttributesPlayerNames
     */
    void WritePlayerNames();

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

    /**
     * Same as GetImageFromPiece but gets you the icon corresponding to the piece.
     * Uses wxICON macro to create what is returned
     */
    wxIcon GetIconFromPiece(slach::PieceType piece);

    /**
     * Helper method that paints a vertical gradient on the panel
     *
     * @param dc thed evice context
     * @param  pPanel the panel we wish to paint on
     */
    void DoPaintVerticalGradient(wxPaintDC& dc, wxPanel* pPanel);

    /**
     * Helper method to draw an image on a panel. The image is resized to fit into the panel.
     *
     * @param dc thed evice context (paint device context)
     * @param pPanel the panel we want to draw upon
     * @param Image the image we wish to draw
     */
    void DoPaintImageOnPanel(wxPaintDC& dc, wxPanel* pPanel, wxImage& Image);

    /**
     * Highlights the move in the move list with the specified ID.
     * All the other moves are set with white background
     */
    void HighlightMoveListPanelWithThisID(int ID);

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
    ChessBoardPanel(wxFrame* parent,  wxWindowID id = wxID_ANY, const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);

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
     * Paints background gradient and various things near the board.
     * It takes care of:
     *   - gradient backgrounds
     *   - arrows
     *
     * @param event the paint event
     */
    void PaintOnSidesOfBoard(wxPaintEvent& event);

    /**
     * This method captures the initiation of the drag and drop between squares.
     * The children panel of this class (the squares) connects their mouse event to this method.
     *
     * @param event the mouse click event
     */
    void LeftMouseClick(wxMouseEvent& event);

    void OnMouseEnteringSingleMoveArea(wxMouseEvent& event);
    void OnMouseLeavingSingleMoveArea(wxMouseEvent& event);

    void ResetToInitialPosition(wxCommandEvent& event);

    void LoadPgnFile(wxCommandEvent& event);

    /**
     * this method is activated when user clicks on one of the arrows.
     * It figures out which arrow the use clicked and behaves accordingly.
     *
     * @param event the generating event
     */
    void ArrowButtonMovement(wxMouseEvent& event);

    /**
     * this method is activated when user clicks on one of the moves in the move list.
     * It figures out which move and set the chessboard accordingly.
     *
     * @param event the generating event
     */
    void OnClickOnMoveList(wxMouseEvent& event);

    void DrawAndSetFenPositionOnBoard(const std::string& rFenPosition);

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
    void LeftMouseRelease(unsigned destinationIndex);

    void ProcessMoveInGui(slach::Move & move);



    /**
     * Resizing method. It figures out the new size and resize everything accordingly.
     *
     * @param event the size event
     */
    void OnSize(wxSizeEvent& event);

};

}//namespace slach_gui
#endif /* _ChessBoardPANEL_HPP_ */
