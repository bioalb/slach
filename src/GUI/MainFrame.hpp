#ifndef MAINFRAME_HPP_
#define MAINFRAME_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "BottomPanel.hpp"
#include "CentralPanel.hpp"
#include "Colours.hpp"

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

    BottomPanel* mpBottomPanel;
    CentralPanel* mpCentralPanel;

    /**
     * this methods tells the bottom panel
     * to use the position that is passed in
     *
     * @param pPosition the position we wish to set
     */
    void UpdateChessPositionForEngine(slach::Position* pPosition);
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

};

}//namespace slach_gui
#endif
