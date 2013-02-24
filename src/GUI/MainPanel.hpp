/*
 * MainPanel.hpp
 *
 *  Created on: Feb 11, 2013
 *      Author: alberto
 */

#ifndef MainPanel_HPP_
#define MainPanel_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include "ChessboardPanel.hpp"
#include "BottomPanel.hpp"

class MainPanel : public wxPanel
{
    ChessboardPanel* mpChessboardPanel;
    BottomPanel* mpBottomPanel;
public:
    MainPanel(wxFrame* parent, const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);
    ~MainPanel();

    /*
     * Here we call refresh to tell the panel to draw itself again.
     * So when the user resizes the image panel the image should be resized too.
     */
    void OnSize(wxSizeEvent& event);

    DECLARE_EVENT_TABLE()
};

#endif /* MainPanel_HPP_ */
