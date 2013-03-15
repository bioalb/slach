#ifndef _CHESSBOARDPANEL_HPP_
#define _CHESSBOARDPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <vector>
#include "SquarePanel.hpp"
#include "../ChessBoard.hpp"

class ChessboardPanel : public wxPanel
{

private:

    std::vector<SquarePanel* > mSquarePanels;
    //std::vector<SquarePanelDropTarget* > mpDropTargets;
    wxFlexGridSizer* mpGridSizer;

    ChessBoard* mpChessBoard;
    /**panel with the actual chessboard (borders included)*/
    wxPanel* mpActualChessboard;

public:
    ChessboardPanel(wxPanel* parent, const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);
    ~ChessboardPanel();

    /**
     * Contains what to do when the user resizes the window
     * It works out the new dimension, resize the chessboard and place it in the
     * middle of the bigger dimension
     */
    void OnSize(wxSizeEvent& event);

    void SetupChessboard();

    std::vector<SquarePanel* > GetSquarePanels();

    DECLARE_EVENT_TABLE()
};

#endif /* _CHESSBOARDPANEL_HPP_ */
