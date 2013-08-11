#include <wx/mstream.h>
#include <wx/dataobj.h>
#include <algorithm>
#include "SquarePanel.hpp"
#include "DropTargetPanel.hpp"
#include "Exception.hpp"
#include "SlachTypes.hpp"
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

slach_gui::SquarePanel::SquarePanel(wxPanel* parent, slach::Square* pSquare, const wxColour& colour, const wxPoint& pos, const wxSize& size, long style )
    : wxPanel(parent,wxID_ANY, pos,size, style),
      mpParent(parent),
      mpSquare(pSquare),
      mDrawPiece(true)
{
    mFile = pSquare->GetFile();
    mRank = pSquare->GetRank();
    mIsBorderSquarePanel = pSquare->IsBorderSquare();
    mIsCornerSquarePanel = pSquare->IsCornerSquare();
    mIsSquarePanelPrintable = pSquare->IsCoordinatePrintable();
    mCurrentWidth = -1;
    mCurrentHeight = -1;
    DetermineCoordinateToPrint();//this gets the right mPrintedCoord
    this->SetDropTarget(new DropTargetPanel(this));
}

slach_gui::SquarePanel::~SquarePanel()
{

}

void slach_gui::SquarePanel::OnSize(wxSizeEvent& event)
{
    int neww, newh;
    this->GetSize( &neww, &newh );

    if( neww != mCurrentWidth || newh != mCurrentHeight )
    {
        mCurrentWidth = neww;
        mCurrentHeight = newh;
    }
    //skip the event.
    event.Skip();
}

slach::Square* slach_gui::SquarePanel::GetSquare()
{
    return mpSquare;
}

void slach_gui::SquarePanel::PaintBackground(wxPaintDC& dc)
{
    assert(mPngImages.size() == 16u);
    if ( (mpSquare->IsDarkSquare() == true) && (mpSquare->IsBorderSquare() == false))
    {
        mBackgroundOnThisSquare = mPngImages[13];//rgb 32,107,129
    }
    if ( (mpSquare->IsLightSquare() == true) && (mpSquare->IsBorderSquare() == false))
    {
        mBackgroundOnThisSquare = mPngImages[14];//rgb 235,241,246
    }
    if (mpSquare->IsBorderSquare())
    {
        mBackgroundOnThisSquare = mPngImages[15];
    }

    mBackgroundOnThisSquare.Rescale(mCurrentWidth, mCurrentHeight);
    //now really draw the rendered image
    dc.DrawBitmap( mBackgroundOnThisSquare, 0, 0, true );
}

void slach_gui::SquarePanel::DetermineCoordinateToPrint()
{
    if (mFile=="a")
    {
        wxMemoryInputStream istream(a_img, sizeof a_img);
        mPrintedCoord.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mFile=="b")
    {
        wxMemoryInputStream istream(b_img, sizeof b_img);
        mPrintedCoord.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mFile=="c")
    {
        wxMemoryInputStream istream(c_img, sizeof c_img);
        mPrintedCoord.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mFile=="d")
    {
        wxMemoryInputStream istream(d_img, sizeof d_img);
        mPrintedCoord.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mFile=="e")
    {
        wxMemoryInputStream istream(e_img, sizeof e_img);
        mPrintedCoord.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mFile=="f")
    {
        wxMemoryInputStream istream(f_img, sizeof f_img);
        mPrintedCoord.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mFile=="g")
    {
        wxMemoryInputStream istream(g_img, sizeof g_img);
        mPrintedCoord.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mFile=="h")
    {
        wxMemoryInputStream istream(h_img, sizeof h_img);
        mPrintedCoord.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }

    else if (mRank=="1")
    {
        wxMemoryInputStream istream(one_img, sizeof one_img);
        mPrintedCoord.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mRank=="2")
    {
        wxMemoryInputStream istream(two_img, sizeof two_img);
        mPrintedCoord.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mRank=="3")
    {
        wxMemoryInputStream istream(three_img, sizeof three_img);
        mPrintedCoord.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mRank=="4")
    {
        wxMemoryInputStream istream(four_img, sizeof four_img);
        mPrintedCoord.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mRank=="5")
    {
        wxMemoryInputStream istream(five_img, sizeof five_img);
        mPrintedCoord.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mRank=="6")
    {
        wxMemoryInputStream istream(six_img, sizeof six_img);
        mPrintedCoord.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mRank=="7")
    {
        wxMemoryInputStream istream(seven_img, sizeof seven_img);
        mPrintedCoord.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mRank=="8")
    {
        wxMemoryInputStream istream(eight_img, sizeof eight_img);
        mPrintedCoord.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else
    {
        //we should never be here
    }
}

void slach_gui::SquarePanel::PaintOnBorder(wxPaintDC& dc)
{
    if ( (mIsBorderSquarePanel==true &&
          mIsCornerSquarePanel==false &&
          mIsSquarePanelPrintable==true))
    {
        double fractional_occupancy_of_space= 0.7;
        int dim = 0;
        int xcoord = 0;
        int ycoord = 0;
        if (mCurrentWidth<=mCurrentHeight)
        {
            dim =  mCurrentWidth*fractional_occupancy_of_space;
            xcoord = 0.0;//for some reason it does not want to center itself when it is small
            ycoord = (mCurrentHeight-dim)/2;
        }
        else
        {
            dim = mCurrentHeight*fractional_occupancy_of_space;
            xcoord = (mCurrentWidth-dim)/2;
            ycoord = (mCurrentHeight-dim)/2;;
        }

        mPrintedCoord.Rescale(dim, dim);
        dc.DrawBitmap(mPrintedCoord, xcoord, ycoord, true );
    }
}
void slach_gui::SquarePanel::SetPngImages(std::vector<wxImage>& pngImages)
{
    pngImages = mPngImages;
}

void slach_gui::SquarePanel::PaintPiece(wxPaintDC& dc)
{
    slach::PieceType piece = mpSquare->GetPieceOnThisSquare();
    assert(mPngImages.size() == 16u);
    switch(piece)
    {
        case slach::WHITE_KING:
            mImageOfPieceOnThisSquare = mPngImages[0];
            mIconNearTheMouse = wxDROP_ICON(white_king);
            break;
        case slach::BLACK_KING:
            mImageOfPieceOnThisSquare = mPngImages[1];
            mIconNearTheMouse = wxDROP_ICON(black_king);
            break;
        case slach::WHITE_QUEEN:
            mImageOfPieceOnThisSquare = mPngImages[2];
            mIconNearTheMouse = wxDROP_ICON(white_queen);
            break;
        case slach::BLACK_QUEEN:
            mImageOfPieceOnThisSquare = mPngImages[3];
            mIconNearTheMouse = wxDROP_ICON(black_queen);
            break;
        case slach::WHITE_ROOK:
            mImageOfPieceOnThisSquare = mPngImages[4];
            mIconNearTheMouse = wxDROP_ICON(white_rook);
            break;
        case slach::BLACK_ROOK:
            mImageOfPieceOnThisSquare = mPngImages[5];
            mIconNearTheMouse = wxDROP_ICON(black_rook);
            break;
        case slach::WHITE_BISHOP:
            mImageOfPieceOnThisSquare = mPngImages[6];
            mIconNearTheMouse = wxDROP_ICON(white_bishop);
            break;
        case slach::BLACK_BISHOP:
            mImageOfPieceOnThisSquare = mPngImages[7];
            mIconNearTheMouse = wxDROP_ICON(black_bishop);
            break;
        case slach::WHITE_KNIGHT:
            mImageOfPieceOnThisSquare = mPngImages[8];
            mIconNearTheMouse = wxDROP_ICON(white_knight);
            break;
        case slach::BLACK_KNIGHT:
            mImageOfPieceOnThisSquare = mPngImages[9];
            mIconNearTheMouse = wxDROP_ICON(black_knight);
            break;
        case slach::WHITE_PAWN:
            mImageOfPieceOnThisSquare = mPngImages[10];
            mIconNearTheMouse = wxDROP_ICON(white_pawn);
            break;
        case slach::BLACK_PAWN:
            mImageOfPieceOnThisSquare = mPngImages[11];
            mIconNearTheMouse = wxDROP_ICON(black_pawn);
            break;
        case slach::NO_PIECE:
            mImageOfPieceOnThisSquare = mPngImages[12];
            mIconNearTheMouse = wxDROP_ICON(no_piece);
            break;
        default:
            //NEVER_REACHED;
            break;
    }

    mImageOfPieceOnThisSquare.Rescale(mCurrentWidth, mCurrentHeight);
    //now really draw the rendered image;
    dc.DrawBitmap( mImageOfPieceOnThisSquare, 0, 0, true );
}

void slach_gui::SquarePanel::RenderOnChessBoard(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	if (mpSquare->IsBorderSquare())
	{
		PaintBackground(dc);
		PaintOnBorder(dc);
	}
	else
	{
		PaintBackground(dc);
		if (mDrawPiece == true)
		{
			PaintPiece(dc);
		}
	}
    evt.Skip();
}


void slach_gui::SquarePanel::rightClick(wxMouseEvent& event)
{
    std::cout<<mFile<<mRank<<std::endl;
}

wxImage slach_gui::SquarePanel::GetImageOfPieceOnThisSquare()
{
    return mImageOfPieceOnThisSquare;
}


void slach_gui::SquarePanel::LeftMouseClick(wxMouseEvent& event)
{
    //first record source coordinates
    mpParent->SetOriginSquare(this);

    wxBitmapDataObject piece_to_be_moved(mImageOfPieceOnThisSquare);
    wxCursor cursor(mImageOfPieceOnThisSquare);
    wxDropSource drop_source( this, mIconNearTheMouse, mIconNearTheMouse);

    drop_source.SetCursor(wxDragMove, cursor);
    drop_source.SetData( piece_to_be_moved );

    mDrawPiece = false;
    this->Refresh();///remove the source piece while dragging...

    wxDragResult result = drop_source.DoDragDrop( wxDragMove );

    mDrawPiece = true;
    switch (result)
    {
        case wxDragCopy: break;
        case wxDragMove: break;
        case wxDragCancel:
            mDrawPiece = true;
            //need to re-paint the piece as it was deleted upon initiation of dragging
            this->Refresh();
            break;
        default: break;
    }
}

bool slach_gui::SquarePanel::OnDrop(wxCoord x, wxCoord y, std::string file, std::string rank)
{
    mpParent->SetDestinationSquare(this);
    return true;
}

void slach_gui::SquarePanel::SetToDrawPiece(bool drawPiece)
{
	mDrawPiece = drawPiece;
}



wxBEGIN_EVENT_TABLE(slach_gui::SquarePanel, wxPanel)
    EVT_SIZE(slach_gui::SquarePanel::OnSize)
    EVT_RIGHT_DOWN(slach_gui::SquarePanel::rightClick)
    EVT_PAINT(slach_gui::SquarePanel::RenderOnChessBoard)
    EVT_LEFT_DOWN(slach_gui::SquarePanel::LeftMouseClick)
wxEND_EVENT_TABLE()
