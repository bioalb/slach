#include "RightPanel.hpp"

slach_gui::RightPanel::RightPanel(wxFrame* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,-1, pos,size)
{
    this->SetBackgroundColour(wxT("blue"));
}

slach_gui::RightPanel::~RightPanel()
{
}

void slach_gui::RightPanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    //skip the event.
    event.Skip();
}

wxBEGIN_EVENT_TABLE(slach_gui::RightPanel, wxPanel)
    EVT_SIZE(slach_gui::RightPanel::OnSize)
wxEND_EVENT_TABLE()
