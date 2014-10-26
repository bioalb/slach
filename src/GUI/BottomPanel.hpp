#ifndef _BOTTOMPANEL_HPP_
#define _BOTTOMPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/button.h>
#include <memory>
#include "UCIEngineInterface.hpp"
#include "Colours.hpp"

namespace slach_gui
{

class BottomPanel : public wxPanel
{
protected:

    std::shared_ptr<slach::UCIEngineInterface> mpEngineInterface;
    unsigned mNumberOfEngineLinesShown;
    slach::Position* mpPosition;
    wxButton* mpStartEngineButton;
    wxButton* mpStopEngineButton;
    wxRichTextCtrl* mpEngineTextBox;

    wxTimer mTimer;
    bool mEngineIsRunning;

    /**Cache for engine information*/
    std::vector<std::string> mPrettyLines;
    double mScore;
    int mDepth;
    std::string mBestMove;



public:
    BottomPanel(wxFrame* parent, const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);
    ~BottomPanel();

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
};

} //namespace slach_gui
#endif /* _BOTTOMPANEL_HPP_ */
