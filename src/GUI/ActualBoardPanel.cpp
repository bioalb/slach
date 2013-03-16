#include <algorithm>
#include <iostream>
#include <cassert>
#include "ActualBoardPanel.hpp"
#include "DropTargetPanel.hpp"
#include "ActualBoardPanel.hpp"

ActualBoardPanel::ActualBoardPanel(wxPanel* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size),
      mpParent(parent)

{
    mSquarePanels.resize(CHESSBOARD_SIZE_WB);
    mpChessBoard = new ChessBoard();
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

ActualBoardPanel::~ActualBoardPanel()
{
    for (unsigned i = 0; i < CHESSBOARD_SIZE_WB; ++i)
    {
        delete mSquarePanels[i];
    }
    delete mpChessBoard;
}

std::vector<SquarePanel* > ActualBoardPanel::GetSquarePanels()
{
    return mSquarePanels;
}

void ActualBoardPanel::SetupChessboard()
{
    mpChessBoard->SetupChessBoard();
    std::vector<Square* > squares = mpChessBoard->GetSquares();
    assert(squares.size() == mSquarePanels.size());
    for (unsigned i = 0; i < squares.size(); ++i)
    {
        mSquarePanels[i] = new SquarePanel( this, squares[i] );
        mpGridSizer->Add(mSquarePanels[i], 0, wxEXPAND);
    }
    this->SetSizer(mpGridSizer, false);
}

void ActualBoardPanel::SetDestinationSquare(std::string file, std::string rank)
{
    mDestinationFile = file;
    mDestinationRank = rank;
}
void ActualBoardPanel::SetOriginSquare(std::string file, std::string rank)
{
    mOriginFile = file;
    mOriginRank = rank;
}

std::pair<std::string, std::string> ActualBoardPanel::GetDestinationSquare()
{
    return std::make_pair(mDestinationFile,mDestinationRank);

}
std::pair<std::string, std::string> ActualBoardPanel::GetOriginSquare()
{
    return std::make_pair(mOriginFile,mOriginRank);
}

void ActualBoardPanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    //figure out the new dimensions
    wxSize chessboard_panel_size = mpParent->GetSize();
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
    this->SetSize(chessboard_size);
    //and center it
    this->SetPosition(central_point);
    mpGridSizer->SetMinSize(chessboard_size);

    //skip the event.
    event.Skip();
}


BEGIN_EVENT_TABLE(ActualBoardPanel, wxPanel)
EVT_SIZE(ActualBoardPanel::OnSize)
END_EVENT_TABLE()

