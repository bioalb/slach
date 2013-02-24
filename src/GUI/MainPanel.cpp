#include "MainPanel.hpp"

MainPanel::MainPanel(wxFrame* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,-1, pos,size)
{

    this->SetBackgroundColour(wxT("white"));
    wxBoxSizer* v_sizer = new wxBoxSizer(wxVERTICAL);
    mpChessboardPanel = new ChessboardPanel(parent);
    mpBottomPanel = new BottomPanel(parent);

    v_sizer->Add(mpChessboardPanel, 4.0, wxGROW);
    v_sizer->Add(mpBottomPanel, 1.0, wxGROW);

    this->SetSizer(v_sizer);
}
MainPanel::~MainPanel()
{
}

void MainPanel::OnSize(wxSizeEvent& event){
    Refresh();
    //skip the event.
    event.Skip();
}

BEGIN_EVENT_TABLE(MainPanel, wxPanel)
    EVT_SIZE(MainPanel::OnSize)
END_EVENT_TABLE()
