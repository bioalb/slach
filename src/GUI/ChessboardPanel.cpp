#include <algorithm>
#include <iostream>
#include <cassert>
#include "ChessboardPanel.hpp"
#include "DropTargetPanel.hpp"


ChessboardPanel::ChessboardPanel(wxPanel* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size)
{
    this->SetBackgroundColour(wxT("yellow"));

    mSquarePanels.resize(CHESSBOARD_SIZE_WB);
    //mpDropTargets.resize(CHESSBOARD_SIZE_WB);
    mpChessBoard = new ChessBoard();
    mpActualChessboard = new ActualBoardPanel(this, wxID_ANY,wxDefaultPosition);

    //now the grid sizer.
    int square_to_border_prop = 3;//proportion between border and square
    mpGridSizer = new wxFlexGridSizer(FILE_SIZE,RANK_SIZE,0,0);
    mpGridSizer->AddGrowableCol(0,1);//border
    mpGridSizer->AddGrowableCol(1,square_to_border_prop);
    mpGridSizer->AddGrowableCol(2,square_to_border_prop);
    mpGridSizer->AddGrowableCol(3,square_to_border_prop);
    mpGridSizer->AddGrowableCol(4,square_to_border_prop);
    mpGridSizer->AddGrowableCol(5,square_to_border_prop);
    mpGridSizer->AddGrowableCol(6,square_to_border_prop);
    mpGridSizer->AddGrowableCol(7,square_to_border_prop);
    mpGridSizer->AddGrowableCol(8,square_to_border_prop);
    mpGridSizer->AddGrowableCol(9,1);//border

    mpGridSizer->AddGrowableRow(0,1);//border
    mpGridSizer->AddGrowableRow(1,square_to_border_prop);
    mpGridSizer->AddGrowableRow(2,square_to_border_prop);
    mpGridSizer->AddGrowableRow(3,square_to_border_prop);
    mpGridSizer->AddGrowableRow(4,square_to_border_prop);
    mpGridSizer->AddGrowableRow(5,square_to_border_prop);
    mpGridSizer->AddGrowableRow(6,square_to_border_prop);
    mpGridSizer->AddGrowableRow(7,square_to_border_prop);
    mpGridSizer->AddGrowableRow(8,square_to_border_prop);
    mpGridSizer->AddGrowableRow(9,1);//border

    SetupChessboard();
    mpChessBoard->SetupInitialChessPosition();
}

void ChessboardPanel::SetupChessboard()
{
    mpChessBoard->SetupChessBoard();
    std::vector<Square* > squares = mpChessBoard->GetSquares();
    assert(squares.size() == mSquarePanels.size());
    for (unsigned i = 0; i < squares.size(); ++i)
    {
        mSquarePanels[i] = new SquarePanel( mpActualChessboard, squares[i] );
        mpGridSizer->Add(mSquarePanels[i], 0, wxEXPAND);
    }
    mpActualChessboard->SetSizer(mpGridSizer, false);
}

std::vector<SquarePanel* > ChessboardPanel::GetSquarePanels()
{
    return mSquarePanels;
}

ChessboardPanel::~ChessboardPanel()
{
    for (unsigned i = 0; i < CHESSBOARD_SIZE_WB; ++i)
    {
        delete mSquarePanels[i];
        //delete mpDropTargets[i];
    }
    delete mpActualChessboard;
    delete mpChessBoard;
}

void ChessboardPanel::OnSize(wxSizeEvent& event)
{
    Refresh();

    //figure out the new dimensions
    wxSize chessboard_panel_size = this->GetSize();
    int panel_x = chessboard_panel_size.GetWidth();
    int panel_y = chessboard_panel_size.GetHeight();
    int min_size;

    //which side is longer...
    wxPoint central_point;
    if (panel_x > panel_y)
    {
        min_size=panel_y;
        central_point.x = (panel_x-min_size)/2;
        central_point.y = 0;
    }
    else
    {
        min_size=panel_x;
        central_point.x = 0;
        central_point.y = (panel_y-min_size)/2;
    }
    //...now resize the chess board accordingly
    wxSize chessboard_size(min_size,min_size);
    mpActualChessboard->SetSize(chessboard_size);
    //and center it
    mpActualChessboard->SetPosition(central_point);
    mpGridSizer->SetMinSize(chessboard_size);

    //skip the event.
    event.Skip();
}


BEGIN_EVENT_TABLE(ChessboardPanel, wxPanel)
    EVT_SIZE(ChessboardPanel::OnSize)
END_EVENT_TABLE()
