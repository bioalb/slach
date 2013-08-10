#ifndef MAINFRAME_HPP_
#define MAINFRAME_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "BottomPanel.hpp"
#include "RightPanel.hpp"
#include "ChessBoardPanel.hpp"

namespace slach_gui
{

class MainFrame: public wxFrame
{
public:
    /**
     * Constructor
     *
     * It creates the menu and the status bar.
     *
     * @param title : the title of the main window
     * @param pos : the position where it pops up (in pixels from top left)
     * @param size :  the size (in pixels)
     */
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    ~MainFrame();

    RightPanel* mpRightPanel;
    BottomPanel* mpBottomPanel;
    ChessBoardPanel* mpBoardPanel;

private:

    /**
     * Standard exit event (Quit)
     *
     */
    void OnExit(wxCommandEvent& event);

    /**
     * Regulates the About button
     * It simply pops up a message box
     */
    void OnAbout(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

}//namespace slach_gui
#endif
