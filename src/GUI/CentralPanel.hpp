#ifndef _CentralPanel_HPP_
#define _CentralPanel_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/vscroll.h>
#include <wx/textctrl.h>
#include <wx/richtext/richtextctrl.h>
#include <vector>
#include "IDContainer.hpp"
#include "ChessBoardPanel.hpp"
#include "ChessBoard.hpp"

namespace slach_gui
{

/**
 * Major GUI class that holds the chessboard
 */




class CentralPanel : public wxPanel
{

private:

    /** Stores pointers of the images of the arrows */
    std::vector<wxImage> mArrowImages;

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
    ChessBoardPanel* mpChessBoardPanel;
    /** The space on the right of the board*/
    wxPanel* mpRightOfChessBoard;


    slach::ChessBoard* mpChessBoard;

    /**Panels fon the RHS of the board*/
    wxPanel* mpNameOfPlayerTop;
    wxPanel* mpNameOfPlayerBottom ;
    wxScrolledWindow* mpSpaceForMoveList;
    wxPanel* mAboveBotoomPlayerName;
    wxPanel* mBelowBotoomPlayerName;
    wxPanel* mAboveTopPlayerName;
    wxPanel* mBelowTopPlayerName;

    /**Text control for the players' names*/
    wxTextCtrl * mpBottomPlayerBox;
    wxTextCtrl * mpTopPlayerBox;
    wxTextCtrl * mpAboveBottomPlayerBox;
    wxTextCtrl * mpAboveTopPlayerBox;

    wxTextAttr mTextAttributesPlayerNames;
    wxTextAttr mTextAttributesGameResultBox;

    /** stores the parent frame*/
    wxFrame* mpParent;

    wxString mWhitePlayerName;
    wxString mBlackPlayerName;


    /**
     * A flag to signal when a game is loaded from pgn
     */
    bool mGameIsLoaded;


    /**
     * HElper method that goes into the text control of the white and black player
     * Delete the content and write the names according to mWhitePlayerName and mBlackPlayerName
     * The text attributes are the ones set by mTextAttributesPlayerNames
     */
    void WritePlayerNames();


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
    CentralPanel(wxFrame* parent,  wxWindowID id = wxID_ANY, const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);

    /**
     * Destructor
     */
    ~CentralPanel();


    /**
     * Paints background gradient and various things near the board.
     * It takes care of:
     *   - gradient backgrounds
     *   - arrows
     *
     * @param event the paint event
     */
    void PaintOnSidesOfBoard(wxPaintEvent& event);

    void ArrowKeyMovement(wxKeyEvent& event);

    void OnMouseEnteringSingleMoveArea(wxMouseEvent& event);
    void OnMouseLeavingSingleMoveArea(wxMouseEvent& event);

    void LoadPgnFile(wxCommandEvent& event);

    void FlipView (wxCommandEvent& WXUNUSED(event));

    /**
     * this method is activated when user clicks on one of the moves in the move list.
     * It figures out which move and set the chessboard accordingly.
     *
     * @param event the generating event
     */
    void OnClickOnMoveList(wxMouseEvent& event);

    /**
     * Resizing method. It figures out the new size and resize everything accordingly.
     *
     * @param event the size event
     */
    void OnSize(wxSizeEvent& event);

    /**
     * Highlights the move in the move list with the specified ID.
     * All the other moves are set with white background
     */
    void HighlightMoveListPanelWithThisID(int ID);

    int GetCurrentlyHighlightedMove();

    /**
     * access method to the variable mMoveListPanels;
     * Used by chessboard child.
     */
    std::vector<wxTextCtrl* > GetMoveListPanels();

};

}//namespace slach_gui
#endif /* _CentralPanel_HPP_ */