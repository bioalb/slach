#include "BottomPanel.hpp"

slach_gui::BottomPanel::BottomPanel(wxPanel* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,-1, pos,size),
      mpEngineInterface( new slach::EngineInterface() ),
      mpStartEngineButton ( new wxButton(this, 1, wxT("Start Engine"),wxDefaultPosition, wxDefaultSize) )
{
    this->SetBackgroundColour(wxT("green"));
}

slach_gui::BottomPanel::~BottomPanel()
{
    delete mpEngineInterface;
}

void slach_gui::BottomPanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    //skip the event.
    event.Skip();
}

void slach_gui::BottomPanel::SetPositionToAnalyse(slach::Position* pPosition)
{
    mpPosition = pPosition;
}

void slach_gui::BottomPanel::StartEngine(wxCommandEvent& event)
{
    wxTextCtrl* text = new wxTextCtrl(this, wxID_ANY, wxT("HELLO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
    {
        wxStreamToTextRedirector redirect(text);
        text->SetEditable(false);
        mpEngineInterface->StartAnalsyingPosition(mpPosition, 1.0);
    }
}
BEGIN_EVENT_TABLE(slach_gui::BottomPanel, wxPanel)
    EVT_SIZE(slach_gui::BottomPanel::OnSize)
    EVT_BUTTON(1, slach_gui::BottomPanel::StartEngine)
END_EVENT_TABLE()
