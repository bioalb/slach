#ifndef _BOTTOMPANEL_HPP_
#define _BOTTOMPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/button.h>
#include "EngineInterface.hpp"
#include "Colours.hpp"

namespace slach_gui
{

class BottomPanel : public wxPanel
{
protected:

    slach::EngineInterface* mpEngineInterface;
    unsigned mNumberOfEngineLinesShown;
    slach::Position* mpPosition;
    wxButton* mpStartEngineButton;
    wxButton* mpStopEngineButton;
    wxRichTextCtrl* mpEngineTextBox;

    wxTimer mTimer;
    bool mEngineIsRunning;



public:
    BottomPanel(wxFrame* parent, const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);
    ~BottomPanel();

    /*
     * Here we call refresh to tell the panel to draw itself again.
     * So when the user resizes the image panel the image should be resized too.
     */
    void OnSize(wxSizeEvent& event);

    void OnClose(wxCloseEvent& evt);

    /**
     * captures the event and calls DoStartEngine();
     */
    void StartEngine(wxCommandEvent& event);
    void StopEngine(wxCommandEvent& event);
    void SetPositionToAnalyse(slach::Position* pPosition);
    void UpdateEngineOutput(wxTimerEvent& evt);

    void DoStartEngine();
    //public as main frame will call this
    void DoStopEngine();
    wxDECLARE_EVENT_TABLE();
};

} //namespace slach_gui
#endif /* _BOTTOMPANEL_HPP_ */
