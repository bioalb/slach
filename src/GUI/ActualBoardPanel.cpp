#include <algorithm>
#include <iostream>
#include <cassert>
#include "../PieceType.hpp"
#include "ActualBoardPanel.hpp"
#include "DropTargetPanel.hpp"
#include "ActualBoardPanel.hpp"

ActualBoardPanel::ActualBoardPanel(wxPanel* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size),
      mpParent(parent),
      mpOriginSquarePanel(NULL),
      mpDestinationSquarePanel(NULL)
{
    mSvgPieceDirectory = "../../src/GUI/bitmaps/pieces/svg/";
    mSvgBackgroundDirectory = "../../src/GUI/bitmaps/squares/svg/";

    mSquarePanels.resize(CHESSBOARD_SIZE_WB);
    mpChessBoardWithBorders = new ChessBoardWithBorders();


    //now the grid sizer.
    int square_to_border_prop = 3;//proportion between border and square
    mpGridSizer = new wxFlexGridSizer(BOARD_ROW_SIZE+2,BOARD_COLUMN_SIZE+2,0,0);
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

ActualBoardPanel::~ActualBoardPanel()
{
    for (unsigned i = 0; i < CHESSBOARD_SIZE_WB; ++i)
    {
        delete mSquarePanels[i];
    }
    delete mpChessBoard;
}

void ActualBoardPanel::LoadSvgPieces()
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

std::vector<SquarePanel* > ActualBoardPanel::GetSquarePanels()
{
    return mSquarePanels;
}

std::vector<wxSVGDocument* > ActualBoardPanel::GetPiecesSvgDocs()
{
    return mPiecesSvgDocs;
}

void ActualBoardPanel::SetupChessboard()
{
    std::vector<Square* > squares = mpChessBoardWithBorders->GetSquares();
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

void ActualBoardPanel::SetDestinationSquare(SquarePanel* pDestinationPanel)
{
    mpDestinationSquarePanel = pDestinationPanel;

    mpOriginSquarePanel->PaintBackground();
    mpDestinationSquarePanel->PaintBackground();
    if (mpChessBoard->/*GetPosition()->*/IsLegalMove()==true)
    {
        PieceType origin_piece  = mpOriginSquarePanel->GetSquare()->GetPieceOnThisSquare();
        mpDestinationSquarePanel->GetSquare()->SetPieceOnThisSquare(origin_piece);
        mpDestinationSquarePanel->PaintPiece();

    }
    else
    {
        mpOriginSquarePanel->PaintPiece();
    }
}
void ActualBoardPanel::SetOriginSquare(SquarePanel* pOriginPanel)
{
    mpOriginSquarePanel = pOriginPanel;
}

SquarePanel* ActualBoardPanel::GetDestinationSquare()
{
    return mpDestinationSquarePanel;

}
SquarePanel* ActualBoardPanel::GetOriginSquare()
{
    return mpOriginSquarePanel;
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

