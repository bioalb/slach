#include <algorithm>
#include <iostream>
#include <cassert>
#include <wx/mstream.h>
#include "SlachTypes.hpp"
#include "ChessBoardPanel.hpp"
#include "DropTargetPanel.hpp"
#include "MainFrame.hpp"
#include "bitmaps/letters/png/a.png.h"
#include "bitmaps/letters/png/b.png.h"
#include "bitmaps/letters/png/c.png.h"
#include "bitmaps/letters/png/d.png.h"
#include "bitmaps/letters/png/e.png.h"
#include "bitmaps/letters/png/f.png.h"
#include "bitmaps/letters/png/g.png.h"
#include "bitmaps/letters/png/h.png.h"

#include "bitmaps/numbers/png/one.png.h"
#include "bitmaps/numbers/png/two.png.h"
#include "bitmaps/numbers/png/three.png.h"
#include "bitmaps/numbers/png/four.png.h"
#include "bitmaps/numbers/png/five.png.h"
#include "bitmaps/numbers/png/six.png.h"
#include "bitmaps/numbers/png/seven.png.h"
#include "bitmaps/numbers/png/eight.png.h"

#include "bitmaps/pieces/xpm/black_rook.xpm"
#include "bitmaps/pieces/xpm/black_king.xpm"
#include "bitmaps/pieces/xpm/black_queen.xpm"
#include "bitmaps/pieces/xpm/black_bishop.xpm"
#include "bitmaps/pieces/xpm/black_knight.xpm"
#include "bitmaps/pieces/xpm/black_pawn.xpm"
#include "bitmaps/pieces/xpm/white_pawn.xpm"
#include "bitmaps/pieces/xpm/white_knight.xpm"
#include "bitmaps/pieces/xpm/white_bishop.xpm"
#include "bitmaps/pieces/xpm/white_rook.xpm"
#include "bitmaps/pieces/xpm/white_queen.xpm"
#include "bitmaps/pieces/xpm/white_king.xpm"
#include "bitmaps/pieces/xpm/no_piece.xpm"

slach_gui::ChessBoardPanel::ChessBoardPanel(wxFrame* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size),
      mPngPieceDirectory("../../src/GUI/bitmaps/pieces/png/"),
      mPngBackgroundDirectory("../../src/GUI/bitmaps/squares/png/"),
      mpChessBoardWithBorders ( new slach::ChessBoardWithBorders() ),
      mpChessBoard(NULL),
      mpGridSizer ( new wxFlexGridSizer(slach::gBoardRowSize+2,slach::gBoardColumnSize+2,0,0) ),
      mpParent(parent),
      mDrawPiece(true),
      mSourceIndex(0u)
{

    mSquarePanels.resize(slach::gChessBoardSizeWB);

    //now the grid sizer.
    int square_to_border_prop = 3;//proportion between border and square
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

    LoadBoardImages();

    mpChessBoard = mpChessBoardWithBorders->GetPlayableChessBoard();
    mpChessBoard->SetupInitialChessPosition();
    (static_cast<MainFrame*> (mpParent))->UpdateChessPositionForEngine(mpChessBoard->GetCurrentPosition());
    mpAllSquares = mpChessBoardWithBorders->GetSquares();

    assert(mpAllSquares.size() == mSquarePanels.size());
    for (unsigned i = 0; i < mpAllSquares.size(); ++i)
    {
        mSquarePanels[i] = new wxPanel( this, /*ID*/ (int) i );
        mpGridSizer->Add(mSquarePanels[i], 0, wxEXPAND);
        //bind the paint event
        mSquarePanels[i]->Bind(wxEVT_PAINT, &ChessBoardPanel::PaintOnSquare, this);
        if (mpAllSquares[i]->IsBorderSquare() == false)
        {
        	mSquarePanels[i]->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::LeftMouseClick, this);
        	DropTargetPanel* p_target_panel = new DropTargetPanel(this);
        	p_target_panel->SetIndexOfSquare(i);
        	mSquarePanels[i]->SetDropTarget(p_target_panel);
        }
    }
    this->SetSizer(mpGridSizer, false);
}

slach_gui::ChessBoardPanel::~ChessBoardPanel()
{
    delete mpChessBoardWithBorders;
}

void slach_gui::ChessBoardPanel::LeftMouseClick(wxMouseEvent& event)
{
	int square_index_int = (static_cast<wxWindow*> (event.GetEventObject()))->GetId();
	mSourceIndex = (unsigned) square_index_int;

    wxBitmapDataObject piece_to_be_moved(GetImageFromPiece(mpAllSquares[mSourceIndex]->GetPieceOnThisSquare()));
    wxCursor cursor(mpAllSquares[mSourceIndex]->GetPieceOnThisSquare());
    wxDropSource drop_source(mSquarePanels[mSourceIndex], mIconNearTheMouse, mIconNearTheMouse);

    drop_source.SetCursor(wxDragMove, cursor);
    drop_source.SetData( piece_to_be_moved );

    mDrawPiece = false;
    mSquarePanels[mSourceIndex]->Refresh();///remove the source piece while dragging...

    wxDragResult result = drop_source.DoDragDrop( wxDragMove );

    mDrawPiece = true;
    switch (result)
    {
        case wxDragCopy: break;
        case wxDragMove: break;
        case wxDragCancel:
            mDrawPiece = true;
            //need to re-paint the piece as it was deleted upon initiation of dragging
            mSquarePanels[mSourceIndex]->Refresh();
            break;
        default: break;
    }
}

void slach_gui::ChessBoardPanel::LeftMouseRelease(unsigned destinationIndex)
{
	assert(mSourceIndex<mpAllSquares.size());
	assert(destinationIndex<mpAllSquares.size());
    slach::Move candidate_move(mpAllSquares[mSourceIndex], mpAllSquares[destinationIndex]);

    ProcessMoveInGui(candidate_move);
}

void slach_gui::ChessBoardPanel::ProcessMoveInGui(slach::Move & move)
{
	unsigned destination_index = move.GetDestination()->GetIndexFromTopLeft();
	unsigned source_index = move.GetOrigin()->GetIndexFromTopLeft();

    if (mpChessBoard->IsLegalMove(move)==true)
    {
        if (move.DoesMoveRequireSpecialGuiHandling())
        {
            mpChessBoard->MakeThisMove(move);

            //delete piece on origin
            mDrawPiece = false;
            mSquarePanels[source_index]->Refresh();
            mDrawPiece = true;

            //paint piece on destination
            mSquarePanels[destination_index]->Refresh();

			for (unsigned i = 0; i  < mSquarePanels.size(); ++i)
			{
				if (! ( mpChessBoardWithBorders->GetSquares()[i]->IsBorderSquare()))
				{
					mSquarePanels[i]->Refresh();
				}
			}
        }
        else
        {
            mpChessBoard->MakeThisMove(move);
            //delete piece on origin
            mDrawPiece = false;
            mSquarePanels[source_index]->Refresh();
            mDrawPiece = true;

            //paint piece on destination
            mSquarePanels[destination_index]->Refresh();
        }
        (static_cast<MainFrame*> (mpParent))->UpdateChessPositionForEngine(mpChessBoard->GetCurrentPosition());
    }
    else
    {
    	//not legal, re-draw piece on origin
    	mDrawPiece = true;
        mSquarePanels[source_index]->Refresh();
    }
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

void slach_gui::ChessBoardPanel::PaintOnSquare(wxPaintEvent& event)
{
	int square_index_int = (static_cast<wxWindow*> (event.GetEventObject()))->GetId();
	unsigned square_index = (unsigned) square_index_int;

	wxPaintDC dc(mSquarePanels[square_index]);
	if (mpAllSquares[square_index]->IsBorderSquare())
	{
		PaintBackground(dc, square_index);
		PaintOnBorder(dc, square_index);
	}
	else
	{
		PaintBackground(dc, square_index);
		if (mDrawPiece == true)
		{
			PaintPiece(dc, square_index);
		}
	}
	event .Skip();
}


///////////////////////////////
// Helper private methods
//////////////////////////////
void slach_gui::ChessBoardPanel::LoadBoardImages()
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

void slach_gui::ChessBoardPanel::PaintPiece(wxPaintDC& dc, unsigned squareIndex)
{
	assert(mPieceImages.size() == 16u);
    slach::PieceType piece = mpAllSquares[squareIndex]->GetPieceOnThisSquare();
    wxImage piece_image = GetImageFromPiece(piece);

    int width = mSquarePanels[squareIndex]->GetClientSize().GetWidth();
    int height = mSquarePanels[squareIndex]->GetClientSize().GetHeight();
    piece_image.Rescale(width, height);
    //now really draw the rendered image;
    dc.DrawBitmap( piece_image, 0, 0, true );
}

wxImage slach_gui::ChessBoardPanel::GetImageFromPiece(slach::PieceType piece)
{
	wxImage piece_image;
    switch(piece)
    {
        case slach::WHITE_KING:
            piece_image = mPieceImages[0];
            mIconNearTheMouse = wxDROP_ICON(white_king);
            break;
        case slach::BLACK_KING:
            piece_image = mPieceImages[1];
            mIconNearTheMouse = wxDROP_ICON(black_king);
            break;
        case slach::WHITE_QUEEN:
            piece_image = mPieceImages[2];
            mIconNearTheMouse = wxDROP_ICON(white_queen);
            break;
        case slach::BLACK_QUEEN:
            piece_image = mPieceImages[3];
            mIconNearTheMouse = wxDROP_ICON(black_queen);
            break;
        case slach::WHITE_ROOK:
            piece_image = mPieceImages[4];
            mIconNearTheMouse = wxDROP_ICON(white_rook);
            break;
        case slach::BLACK_ROOK:
            piece_image = mPieceImages[5];
            mIconNearTheMouse = wxDROP_ICON(black_rook);
            break;
        case slach::WHITE_BISHOP:
            piece_image = mPieceImages[6];
            mIconNearTheMouse = wxDROP_ICON(white_bishop);
            break;
        case slach::BLACK_BISHOP:
            piece_image = mPieceImages[7];
            mIconNearTheMouse = wxDROP_ICON(black_bishop);
            break;
        case slach::WHITE_KNIGHT:
            piece_image = mPieceImages[8];
            mIconNearTheMouse = wxDROP_ICON(white_knight);
            break;
        case slach::BLACK_KNIGHT:
            piece_image = mPieceImages[9];
            mIconNearTheMouse = wxDROP_ICON(black_knight);
            break;
        case slach::WHITE_PAWN:
            piece_image = mPieceImages[10];
            mIconNearTheMouse = wxDROP_ICON(white_pawn);
            break;
        case slach::BLACK_PAWN:
            piece_image = mPieceImages[11];
            mIconNearTheMouse = wxDROP_ICON(black_pawn);
            break;
        case slach::NO_PIECE:
            piece_image = mPieceImages[12];
            mIconNearTheMouse = wxDROP_ICON(no_piece);
            break;
        default:
            //NEVER_REACHED;
            break;
    }
    return piece_image;
}


void slach_gui::ChessBoardPanel::PaintBackground(wxPaintDC& dc, unsigned squareIndex)
{
    assert(mPieceImages.size() == 16u);
    int width = mSquarePanels[squareIndex]->GetClientSize().GetWidth();
    int height = mSquarePanels[squareIndex]->GetClientSize().GetHeight();

    if ( (mpAllSquares[squareIndex]->IsDarkSquare() == true) && (mpAllSquares[squareIndex]->IsBorderSquare() == false))
    {
        mPieceImages[13].Rescale(width, height);//rgb 32,107,129
        //now really draw the rendered image
        dc.DrawBitmap( mPieceImages[13], 0, 0, true );
    }
    if ( (mpAllSquares[squareIndex]->IsLightSquare() == true) && (mpAllSquares[squareIndex]->IsBorderSquare() == false))
    {
        mPieceImages[14].Rescale(width, height);//rgb 235.241,246
        //now really draw the rendered image
        dc.DrawBitmap( mPieceImages[14], 0, 0, true );
    }
    if (mpAllSquares[squareIndex]->IsBorderSquare())
    {
        mPieceImages[15].Rescale(width, height);
        //now really draw the rendered image
        dc.DrawBitmap( mPieceImages[15], 0, 0, true );
    }
}

void slach_gui::ChessBoardPanel::PaintOnBorder(wxPaintDC& dc, unsigned squareIndex)
{
    if ( (mpAllSquares[squareIndex]->IsBorderSquare()==true &&
    	  mpAllSquares[squareIndex]->IsCornerSquare()==false &&
    	  mpAllSquares[squareIndex]->IsCoordinatePrintable()))
    {
        double fractional_occupancy_of_space= 0.7;
        int dim = 0;
        int xcoord = 0;
        int ycoord = 0;
        int width = mSquarePanels[squareIndex]->GetClientSize().GetWidth();
        int height = mSquarePanels[squareIndex]->GetClientSize().GetHeight();
        if (width<=height)
        {
            dim =  width*fractional_occupancy_of_space;
            xcoord = 0.0;//for some reason it does not want to center itself when it is small
            ycoord = (height-dim)/2;
        }
        else
        {
            dim = height*fractional_occupancy_of_space;
            xcoord = (width-dim)/2;
            ycoord = (height-dim)/2;;
        }

        wxImage ret = DetermineCoordinateToPrint(squareIndex);
        ret.Rescale(dim, dim);
        dc.DrawBitmap(ret, xcoord, ycoord, true );
    }
}

wxImage slach_gui::ChessBoardPanel::DetermineCoordinateToPrint(unsigned squareIndex)
{
	wxImage ret;
    if (mpAllSquares[squareIndex]->GetFile()=='a')
    {
        wxMemoryInputStream istream(a_img, sizeof a_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetFile()=='b')
    {
        wxMemoryInputStream istream(b_img, sizeof b_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetFile()=='c')
    {
        wxMemoryInputStream istream(c_img, sizeof c_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetFile()=='d')
    {
        wxMemoryInputStream istream(d_img, sizeof d_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetFile()=='e')
    {
        wxMemoryInputStream istream(e_img, sizeof e_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetFile()=='f')
    {
        wxMemoryInputStream istream(f_img, sizeof f_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetFile()=='g')
    {
        wxMemoryInputStream istream(g_img, sizeof g_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetFile()=='h')
    {
        wxMemoryInputStream istream(h_img, sizeof h_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }

    else if (mpAllSquares[squareIndex]->GetRank()=='1')
    {
        wxMemoryInputStream istream(one_img, sizeof one_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetRank()=='2')
    {
        wxMemoryInputStream istream(two_img, sizeof two_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetRank()=='3')
    {
        wxMemoryInputStream istream(three_img, sizeof three_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetRank()=='4')
    {
        wxMemoryInputStream istream(four_img, sizeof four_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetRank()=='5')
    {
        wxMemoryInputStream istream(five_img, sizeof five_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetRank()=='6')
    {
        wxMemoryInputStream istream(six_img, sizeof six_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetRank()=='7')
    {
        wxMemoryInputStream istream(seven_img, sizeof seven_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetRank()=='8')
    {
        wxMemoryInputStream istream(eight_img, sizeof eight_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else
    {
        //we should never be here
    }

    return ret;
}

wxBEGIN_EVENT_TABLE(slach_gui::ChessBoardPanel, wxPanel)
    EVT_SIZE(slach_gui::ChessBoardPanel::OnSize)
    EVT_PAINT(slach_gui::ChessBoardPanel::PaintOnSquare)
    EVT_LEFT_DOWN(slach_gui::ChessBoardPanel::LeftMouseClick)
wxEND_EVENT_TABLE()
