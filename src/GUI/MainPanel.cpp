#include "MainPanel.hpp"

slach_gui::MainPanel::MainPanel(wxFrame* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,-1, pos,size)
{

    this->SetBackgroundColour(wxT("white"));
    wxBoxSizer* v_sizer = new wxBoxSizer(wxVERTICAL);
    mpChessboardPanel = new ChessboardPanel(this);
    mpBottomPanel = new BottomPanel(this);

    v_sizer->Add(mpChessboardPanel, 4.0, wxGROW);
    v_sizer->Add(mpBottomPanel, 1.0, wxGROW);

    this->SetSizer(v_sizer);
}
slach_gui::MainPanel::~MainPanel()
{
}

void slach_gui::MainPanel::OnSize(wxSizeEvent& event){
    Refresh();
    //skip the event.
    event.Skip();
}

BEGIN_EVENT_TABLE(slach_gui::MainPanel, wxPanel)
    EVT_SIZE(slach_gui::MainPanel::OnSize)
END_EVENT_TABLE()
