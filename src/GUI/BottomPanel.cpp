#include "BottomPanel.hpp"

slach_gui::BottomPanel::BottomPanel(wxPanel* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,-1, pos,size)
{
    this->SetBackgroundColour(wxT("green"));
}

slach_gui::BottomPanel::~BottomPanel()
{
}

void slach_gui::BottomPanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    //skip the event.
    event.Skip();
}

BEGIN_EVENT_TABLE(slach_gui::BottomPanel, wxPanel)
    EVT_SIZE(slach_gui::BottomPanel::OnSize)
END_EVENT_TABLE()
