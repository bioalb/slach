#include "BottomPanel.hpp"

BottomPanel::BottomPanel(wxPanel* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,-1, pos,size)
{
    this->SetBackgroundColour(wxT("green"));
}

BottomPanel::~BottomPanel()
{
}

void BottomPanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    //skip the event.
    event.Skip();
}

BEGIN_EVENT_TABLE(BottomPanel, wxPanel)
    EVT_SIZE(BottomPanel::OnSize)
END_EVENT_TABLE()
