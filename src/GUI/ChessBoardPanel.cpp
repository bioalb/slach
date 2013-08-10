#include <algorithm>
#include <iostream>
#include <cassert>
#include "SlachTypes.hpp"
#include "ChessBoardPanel.hpp"
#include "DropTargetPanel.hpp"
#include "ChessBoardPanel.hpp"

slach_gui::ChessBoardPanel::ChessBoardPanel(wxFrame* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size),
      mpParent(parent),
      mpOriginSquarePanel(NULL),
      mpDestinationSquarePanel(NULL)
{
    mPngPieceDirectory = "../../src/GUI/bitmaps/pieces/png/";
    mPngBackgroundDirectory = "../../src/GUI/bitmaps/squares/png/";

    mSquarePanels.resize(slach::gChessBoardSizeWB);
    mpChessBoardWithBorders = new slach::ChessBoardWithBorders();


    //now the grid sizer.
    int square_to_border_prop = 3;//proportion between border and square
    mpGridSizer = new wxFlexGridSizer(slach::gBoardRowSize+2,slach::gBoardColumnSize+2,0,0);
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

slach_gui::ChessBoardPanel::~ChessBoardPanel()
{
    for (unsigned i = 0; i < slach::gChessBoardSizeWB; ++i)
    {
        delete mSquarePanels[i];
    }
    delete mpChessBoardWithBorders;
}

void slach_gui::ChessBoardPanel::LoadSvgPieces()
{
	mPieceImages.resize(16u);

    mPieceImages[0].LoadFile(wxString((mPngPieceDirectory+"white_king.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[1].LoadFile(wxString((mPngPieceDirectory+"black_king.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[2].LoadFile(wxString((mPngPieceDirectory+"white_queen.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[3].LoadFile(wxString((mPngPieceDirectory+"black_queen.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[4].LoadFile(wxString((mPngPieceDirectory+"white_rook.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[5].LoadFile(wxString((mPngPieceDirectory+"black_rook.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[6].LoadFile(wxString((mPngPieceDirectory+"white_bishop.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[7].LoadFile(wxString((mPngPieceDirectory+"black_bishop.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[8].LoadFile(wxString((mPngPieceDirectory+"white_knight.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[9].LoadFile(wxString((mPngPieceDirectory+"black_knight.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[10].LoadFile(wxString((mPngPieceDirectory+"white_pawn.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[11].LoadFile(wxString((mPngPieceDirectory+"black_pawn.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[12].LoadFile(wxString((mPngPieceDirectory+"no_piece.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[13].LoadFile(wxString((mPngBackgroundDirectory+"dark_square.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[14].LoadFile(wxString((mPngBackgroundDirectory+"light_square.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[15].LoadFile(wxString((mPngBackgroundDirectory+"border_square.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );

}

std::vector<slach_gui::SquarePanel* > slach_gui::ChessBoardPanel::GetSquarePanels()
{
    return mSquarePanels;
}

std::vector<wxImage > slach_gui::ChessBoardPanel::GetPiecesPgns()
{
    return mPieceImages;
}

void slach_gui::ChessBoardPanel::SetupChessboard()
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

void slach_gui::ChessBoardPanel::SetDestinationSquare(SquarePanel* pDestinationPanel)
{
    mpDestinationSquarePanel = pDestinationPanel;

    slach::Move candidate_move(mpOriginSquarePanel->GetSquare(), mpDestinationSquarePanel->GetSquare());
    if (mpChessBoard->IsLegalMove(candidate_move)==true)
    {
        if (candidate_move.DoesMoveRequireSpecialGuiHandling())
        {
            mpChessBoard->MakeThisMove(candidate_move);

            //delete piece on origin
            mpOriginSquarePanel->SetToDrawPiece (false);
            mpOriginSquarePanel->Refresh();
            mpOriginSquarePanel->SetToDrawPiece (true);

            //paint piece on destination
            mpDestinationSquarePanel->SetToDrawPiece (true);
            mpDestinationSquarePanel->Refresh();


			for (unsigned i = 0; i  < mSquarePanels.size(); ++i)
			{
				if (! ( mpChessBoardWithBorders->GetSquares()[i]->IsBorderSquare()))
				{
					mSquarePanels[i]->SetToDrawPiece (true);
					mSquarePanels[i]->Refresh();
				}
			}
        }
        else
        {
            mpChessBoard->MakeThisMove(candidate_move);
            //delete piece on origin
            mpOriginSquarePanel->SetToDrawPiece (false);
            mpOriginSquarePanel->Refresh();
            mpOriginSquarePanel->SetToDrawPiece (true);

            //paint piece on destination
            mpDestinationSquarePanel->SetToDrawPiece (true);
            mpDestinationSquarePanel->Refresh();
        }
    }
    else
    {
    	//not legal, re-draw piece on origin
    	mpOriginSquarePanel->SetToDrawPiece (true);
    	mpOriginSquarePanel->Refresh();
    }
}
void slach_gui::ChessBoardPanel::SetOriginSquare(SquarePanel* pOriginPanel)
{
    mpOriginSquarePanel = pOriginPanel;
}

slach_gui::SquarePanel* slach_gui::ChessBoardPanel::GetDestinationSquare()
{
    return mpDestinationSquarePanel;

}

slach_gui::SquarePanel* slach_gui::ChessBoardPanel::GetOriginSquare()
{
    return mpOriginSquarePanel;
}

void slach_gui::ChessBoardPanel::OnSize(wxSizeEvent& event)
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
    this->SetSize(chessboard_size);
    //and center it
    this->SetPosition(central_point);
    mpGridSizer->SetMinSize(chessboard_size);

    //skip the event.
    event.Skip();
}

slach::ChessBoard* slach_gui::ChessBoardPanel::GetChessBoard() const
{
    return mpChessBoard;
}

wxBEGIN_EVENT_TABLE(slach_gui::ChessBoardPanel, wxPanel)
    EVT_SIZE(slach_gui::ChessBoardPanel::OnSize)
wxEND_EVENT_TABLE()

