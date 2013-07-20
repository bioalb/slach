#include "BottomPanel.hpp"

slach_gui::BottomPanel::BottomPanel(wxPanel* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,-1, pos,size)
{
    this->SetBackgroundColour(wxT("green"));
    ShowText();
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

void slach_gui::BottomPanel::ShowText()
{
    wxTextCtrl* text = new wxTextCtrl(this, wxID_ANY, wxT("HELLO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
    text->SetEditable(false);
}
BEGIN_EVENT_TABLE(slach_gui::BottomPanel, wxPanel)
    EVT_SIZE(slach_gui::BottomPanel::OnSize)
END_EVENT_TABLE()
