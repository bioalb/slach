#ifndef _CHESSBOARDPANEL_HPP_
#define _CHESSBOARDPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <vector>
#include "ActualBoardPanel.hpp"

class ChessboardPanel : public wxPanel
{

private:
    /**panel with the actual chessboard (borders included)*/
    ActualBoardPanel* mpActualChessboard;

public:
    ChessboardPanel(wxPanel* parent, const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);
    ~ChessboardPanel();

    /**
     * Contains what to do when the user resizes the window
     * It works out the new dimension, resize the chessboard and place it in the
     * middle of the bigger dimension
     */
    void OnSize(wxSizeEvent& event);

    DECLARE_EVENT_TABLE()
};

#endif /* _CHESSBOARDPANEL_HPP_ */
