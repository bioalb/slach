#include <algorithm>
#include <iostream>
#include <cassert>
#include "ChessboardPanel.hpp"
#include "DropTargetPanel.hpp"


ChessboardPanel::ChessboardPanel(wxPanel* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size)
{
    this->SetBackgroundColour(wxT("yellow"));
    mpActualChessboard = new ActualBoardPanel(this, wxID_ANY,wxDefaultPosition);
}


ChessboardPanel::~ChessboardPanel()
{
    delete mpActualChessboard;
}

void ChessboardPanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    mpActualChessboard->OnSize(event);
    //skip the event.
    event.Skip();
}


BEGIN_EVENT_TABLE(ChessboardPanel, wxPanel)
    EVT_SIZE(ChessboardPanel::OnSize)
END_EVENT_TABLE()
