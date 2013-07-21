#ifndef _BOTTOMPANEL_HPP_
#define _BOTTOMPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include "EngineInterface.hpp"

namespace slach_gui
{

class BottomPanel : public wxPanel
{
private:

    slach::EngineInterface* mpEngineInterface;
    wxButton* mpStartEngineButton;
    slach::Position* mpPosition;

public:
    BottomPanel(wxPanel* parent, const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);
    ~BottomPanel();

    /*
     * Here we call refresh to tell the panel to draw itself again.
     * So when the user resizes the image panel the image should be resized too.
     */
    void OnSize(wxSizeEvent& event);
    void StartEngine(wxCommandEvent& event);
    void SetPositionToAnalyse(slach::Position* pPosition);

    DECLARE_EVENT_TABLE()
};

} //namespace slach_gui
#endif /* _BOTTOMPANEL_HPP_ */
