#include <algorithm>
#include <iostream>
#include <cassert>
#include "SlachTypes.hpp"
#include "ActualBoardPanel.hpp"
#include "DropTargetPanel.hpp"
#include "ActualBoardPanel.hpp"

slach_gui::ActualBoardPanel::ActualBoardPanel(wxPanel* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size),
      mpParent(parent),
      mpOriginSquarePanel(NULL),
      mpDestinationSquarePanel(NULL)
{
    mSvgPieceDirectory = "../../src/GUI/bitmaps/pieces/svg/";
    mSvgBackgroundDirectory = "../../src/GUI/bitmaps/squares/svg/";

    mSquarePanels.resize(slach::CHESSBOARD_SIZE_WB);
    mpChessBoardWithBorders = new slach::ChessBoardWithBorders();


    //now the grid sizer.
    int square_to_border_prop = 3;//proportion between border and square
    mpGridSizer = new wxFlexGridSizer(slach::BOARD_ROW_SIZE+2,slach::BOARD_COLUMN_SIZE+2,0,0);
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

    LoadSvgPieces();
    SetupChessboard();

}

slach_gui::ActualBoardPanel::~ActualBoardPanel()
{
    for (unsigned i = 0; i < slach::CHESSBOARD_SIZE_WB; ++i)
    {
        delete mSquarePanels[i];
    }
    delete mpChessBoard;
}

void slach_gui::ActualBoardPanel::LoadSvgPieces()
{
    mPiecesSvgDocs.resize(16u);
    for (unsigned i = 0; i < mPiecesSvgDocs.size(); ++i)
    {
        mPiecesSvgDocs[i] = new wxSVGDocument;
    }

    mPiecesSvgDocs[0]->Load(wxString((mSvgPieceDirectory+"white_king.svg").c_str(), wxConvUTF8));
    mPiecesSvgDocs[1]->Load(wxString((mSvgPieceDirectory+"black_king.svg").c_str(), wxConvUTF8));
    mPiecesSvgDocs[2]->Load(wxString((mSvgPieceDirectory+"white_queen.svg").c_str(), wxConvUTF8));
    mPiecesSvgDocs[3]->Load(wxString((mSvgPieceDirectory+"black_queen.svg").c_str(), wxConvUTF8));
    mPiecesSvgDocs[4]->Load(wxString((mSvgPieceDirectory+"white_rook.svg").c_str(), wxConvUTF8));
    mPiecesSvgDocs[5]->Load(wxString((mSvgPieceDirectory+"black_rook.svg").c_str(), wxConvUTF8));
    mPiecesSvgDocs[6]->Load(wxString((mSvgPieceDirectory+"white_bishop.svg").c_str(), wxConvUTF8));
    mPiecesSvgDocs[7]->Load(wxString((mSvgPieceDirectory+"black_bishop.svg").c_str(), wxConvUTF8));
    mPiecesSvgDocs[8]->Load(wxString((mSvgPieceDirectory+"white_knight.svg").c_str(), wxConvUTF8));
    mPiecesSvgDocs[9]->Load(wxString((mSvgPieceDirectory+"black_knight.svg").c_str(), wxConvUTF8));
    mPiecesSvgDocs[10]->Load(wxString((mSvgPieceDirectory+"white_pawn.svg").c_str(), wxConvUTF8));
    mPiecesSvgDocs[11]->Load(wxString((mSvgPieceDirectory+"black_pawn.svg").c_str(), wxConvUTF8));
    mPiecesSvgDocs[12]->Load(wxString((mSvgPieceDirectory+"no_piece.svg").c_str(), wxConvUTF8));
    mPiecesSvgDocs[13]->Load(wxString((mSvgBackgroundDirectory+"dark_square.svg").c_str(), wxConvUTF8));
    mPiecesSvgDocs[14]->Load(wxString((mSvgBackgroundDirectory+"light_square.svg").c_str(), wxConvUTF8));
    mPiecesSvgDocs[15]->Load(wxString((mSvgBackgroundDirectory+"border_square.svg").c_str(), wxConvUTF8));

}

std::vector<slach_gui::SquarePanel* > slach_gui::ActualBoardPanel::GetSquarePanels()
{
    return mSquarePanels;
}

std::vector<wxSVGDocument* > slach_gui::ActualBoardPanel::GetPiecesSvgDocs()
{
    return mPiecesSvgDocs;
}

void slach_gui::ActualBoardPanel::SetupChessboard()
{
    std::vector<slach::Square* > squares = mpChessBoardWithBorders->GetSquares();
    assert(squares.size() == mSquarePanels.size());
    for (unsigned i = 0; i < squares.size(); ++i)
    {
        mSquarePanels[i] = new SquarePanel( this, squares[i] );
        mpGridSizer->Add(mSquarePanels[i], 0, wxEXPAND);
    }
    this->SetSizer(mpGridSizer, false);
    mpChessBoard = mpChessBoardWithBorders->GetPlayableChessBoard();
    mpChessBoard->SetupInitialChessPosition();
}

void slach_gui::ActualBoardPanel::SetDestinationSquare(SquarePanel* pDestinationPanel)
{
    mpDestinationSquarePanel = pDestinationPanel;

    slach::Move candidate_move;
    candidate_move.first = mpOriginSquarePanel->GetSquare();
    candidate_move.second = mpDestinationSquarePanel->GetSquare();
    if (mpChessBoard->IsLegalMove(candidate_move)==true)
    {
        mpOriginSquarePanel->PaintBackground();
        mpDestinationSquarePanel->PaintBackground();
        slach::PieceType origin_piece  = mpOriginSquarePanel->GetSquare()->GetPieceOnThisSquare();
        mpDestinationSquarePanel->GetSquare()->SetPieceOnThisSquare(origin_piece);
        mpDestinationSquarePanel->PaintPiece();
        //update underlying chessboard
        mpChessBoard->MakeThisMove(candidate_move);
    }
    else
    {
        mpOriginSquarePanel->PaintPiece();
    }
}
void slach_gui::ActualBoardPanel::SetOriginSquare(SquarePanel* pOriginPanel)
{
    mpOriginSquarePanel = pOriginPanel;
}

slach_gui::SquarePanel* slach_gui::ActualBoardPanel::GetDestinationSquare()
{
    return mpDestinationSquarePanel;

}

slach_gui::SquarePanel* slach_gui::ActualBoardPanel::GetOriginSquare()
{
    return mpOriginSquarePanel;
}

void slach_gui::ActualBoardPanel::OnSize(wxSizeEvent& event)
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


BEGIN_EVENT_TABLE(slach_gui::ActualBoardPanel, wxPanel)
    EVT_SIZE(slach_gui::ActualBoardPanel::OnSize)
END_EVENT_TABLE()

