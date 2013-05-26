#include <algorithm>
#include <iostream>
#include <cassert>
#include "ChessboardPanel.hpp"
#include "DropTargetPanel.hpp"


slach_gui::ChessboardPanel::ChessboardPanel(wxPanel* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size)
{
    this->SetBackgroundColour(wxT("yellow"));
    mpActualChessboard = new ActualBoardPanel(this, wxID_ANY,wxDefaultPosition);
}


slach_gui::ChessboardPanel::~ChessboardPanel()
{
    delete mpActualChessboard;
}

void slach_gui::ChessboardPanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    mpActualChessboard->OnSize(event);
    //skip the event.
    event.Skip();
}


BEGIN_EVENT_TABLE(slach_gui::ChessboardPanel, wxPanel)
    EVT_SIZE(slach_gui::ChessboardPanel::OnSize)
END_EVENT_TABLE()
