#include "RightPanel.hpp"

RightPanel::RightPanel(wxFrame* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,-1, pos,size)
{
    this->SetBackgroundColour(wxT("blue"));
}

RightPanel::~RightPanel()
{
}

void RightPanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    //skip the event.
    event.Skip();
}

BEGIN_EVENT_TABLE(RightPanel, wxPanel)
    EVT_SIZE(RightPanel::OnSize)
END_EVENT_TABLE()
