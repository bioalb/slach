#ifndef _CentralPanel_HPP_
#define _CentralPanel_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/vscroll.h>
#include <wx/textctrl.h>
#include <wx/richtext/richtextctrl.h>
#include <vector>
#include <memory>
#include "IDContainer.hpp"
#include "Colours.hpp"
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

    /**The main sizer that decides where the board is*/
    wxBoxSizer* mpPrincipalSizer;
    wxBoxSizer* mpRightSideSizer;

    /**The chessboard panel*/
    ChessBoardPanel* mpChessBoardPanel;
    /** The space on the right of the board*/
    wxPanel* mpRightOfChessBoard;


    std::shared_ptr<slach::ChessBoard> mpChessBoard;

    /**Panels on the RHS of the board*/
    wxRichTextCtrl* mpSpaceForMoveList;
    /**Each element is a range of a move in the move list*/
    std::vector<wxRichTextRange> mMoveListRanges;
    /**Stores the index of the currently highlighted move. -1 if no move is highlighted*/
    int mIndexOfHighlightedMove;

    wxPanel* mpButtonsBelowMoveList;

    wxRichTextAttr mTextAttributesPlayerNames;
    wxTextAttr mTextAttributesMoveList;
    wxTextAttr mTextAttributeMoveNumber;
    wxTextAttr mTextAttributesMoveListHighlighted;

    /** stores the parent frame*/
    wxFrame* mpParent;

    wxString mWhitePlayerName;
    wxString mBlackPlayerName;


    /**
     * A flag to signal when a game is loaded from pgn
     */
    bool mGameIsLoaded;

    /**
     * This is a cache for the ID
     * of the panel in the move list where the last actual move is stored.
     * Initialized to INT_MAX
     */
    int mIdOfPanelWithLastMove;

    /**
     * HElper method that goes into the text control of the white and black player
     * Delete the content and write the names according to mWhitePlayerName and mBlackPlayerName
     * The text attributes are the ones set by mTextAttributesPlayerNames
     */
//    void WritePlayerNames();


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
     * Handles the event of pressing keys on teh keyboard
     * - arrow up and arrow right: one move forward
     * - arrow down and left: one move backward
     * - home: start of the game
     * - End: end of the game
     * - Page up back 5 half moves
     * - Page down forward 5 half moves
     */
    void ArrowKeyMovement(wxKeyEvent& event);

    void LoadPgnFile(wxCommandEvent& event);

    void LoadFen (wxCommandEvent& WXUNUSED(event));

    /**
     * this method is activated when user clicks on one of the moves in the move list.
     * It figures out which move and set the chessboard accordingly.
     *
     * @param event the generating event
     */
    void OnClickOnMoveList(wxRichTextEvent& event);

    /**
     * Resizing method. It figures out the new size and resize everything accordingly.
     *
     * @param event the size event
     */
    void OnSize(wxSizeEvent& event);

    /**
     * Highlights the move in the move list with the specified index.
     *
     * @param The index referred to the move list ranges stored in mMoveListRanges, i.e.,in the front-end.
     */
    void HighlightMoveListRange(int ID);

    void HighlightNextMove();
    void HighlightSeveralMovesAhead();
    void HighlightLastMove();
    void HighlightPreviousMove();
    void HighlightSeveralMovesBack();
    void HighlightBeforeFirstMove();

};

}//namespace slach_gui
#endif /* _CentralPanel_HPP_ */
