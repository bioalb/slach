#include <wx/mstream.h>
#include <wx/dataobj.h>
#include <SVGDocument.h>
#include <algorithm>
#include "SquarePanel.hpp"
#include "DropTargetPanel.hpp"
#include "../Exception.hpp"
#include "../PieceType.hpp"
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


SquarePanel::SquarePanel(wxPanel* parent, Square* pSquare, const wxColour& colour, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size),
      mpParent(parent),
      mpSquare(pSquare)
{
    mFile = pSquare->GetFile();
    mRank = pSquare->GetRank();
    mIsBorderSquarePanel = pSquare->IsBorderSquare();
    mIsCornerSquarePanel = pSquare->IsCornerSquare();
    mIsSquarePanelPrintable = pSquare->IsCoordinatePrintable();
    mCurrentWidth = -1;
    mCurrentHeight = -1;

    if ( (pSquare->IsDarkSquare() == true) && (pSquare->IsBorderSquare() == false))
    {
        this->SetBackgroundColour(wxColour(32,107,129));
    }
    if ( (pSquare->IsLightSquare() == true) && (pSquare->IsBorderSquare() == false))
    {
        this->SetBackgroundColour(wxColour(235,241,246));
    }
    if (pSquare->IsBorderSquare())
    {
        this->SetBackgroundColour(wxColour(35,87,102));
    }

    this->SetDropTarget(new DropTargetPanel(this));

}

SquarePanel::~SquarePanel()
{

}

void SquarePanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    //skip the event.
    event.Skip();
}

void SquarePanel::DetermineCoordinateToPrint()
{
    assert(mIsSquarePanelPrintable);
    assert(mIsBorderSquarePanel);
    if (mFile=="A")
    {
        wxMemoryInputStream istream(a_img, sizeof a_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mFile=="B")
    {
        wxMemoryInputStream istream(b_img, sizeof b_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mFile=="C")
    {
        wxMemoryInputStream istream(c_img, sizeof c_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mFile=="D")
    {
        wxMemoryInputStream istream(d_img, sizeof d_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mFile=="E")
    {
        wxMemoryInputStream istream(e_img, sizeof e_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mFile=="F")
    {
        wxMemoryInputStream istream(f_img, sizeof f_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mFile=="G")
    {
        wxMemoryInputStream istream(g_img, sizeof g_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mFile=="H")
    {
        wxMemoryInputStream istream(h_img, sizeof h_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }

    else if (mRank=="1")
    {
        wxMemoryInputStream istream(one_img, sizeof one_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mRank=="2")
    {
        wxMemoryInputStream istream(two_img, sizeof two_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mRank=="3")
    {
        wxMemoryInputStream istream(three_img, sizeof three_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mRank=="4")
    {
        wxMemoryInputStream istream(four_img, sizeof four_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mRank=="5")
    {
        wxMemoryInputStream istream(five_img, sizeof five_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mRank=="6")
    {
        wxMemoryInputStream istream(six_img, sizeof six_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mRank=="7")
    {
        wxMemoryInputStream istream(seven_img, sizeof seven_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mRank=="8")
    {
        wxMemoryInputStream istream(eight_img, sizeof eight_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    else
    {
        //we should never be here
    }
}

void SquarePanel::PaintOnBorder()
{
    if ( (mIsBorderSquarePanel==true &&
          mIsCornerSquarePanel==false &&
          mIsSquarePanelPrintable==true))
    {
        wxPaintDC dc(this);
        DetermineCoordinateToPrint();//this gets the right mpPrintedCoord
        assert(mpPrintedCoord!=NULL);
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

        wxBitmap resized = wxBitmap( mpPrintedCoord->Scale(dim, dim) );
        dc.DrawBitmap( resized, xcoord, ycoord, false );
    }
}

void SquarePanel::PaintPiece()
{
    PieceType piece = mpSquare->GetPieceOnThisSquare();

    wxPaintDC dc(this);
    wxSVGDocument* svgDoc = new wxSVGDocument;

    switch(piece)
    {
        case WHITE_KING:
            svgDoc->Load(wxT("../src/GUI/bitmaps/pieces/svg/white_king.svg"));
            break;
        case BLACK_KING:
            svgDoc->Load(wxT("../src/GUI/bitmaps/pieces/svg/black_king.svg"));
            break;
        case WHITE_QUEEN:
            svgDoc->Load(wxT("../src/GUI/bitmaps/pieces/svg/white_queen.svg"));
            break;
        case BLACK_QUEEN:
            svgDoc->Load(wxT("../src/GUI/bitmaps/pieces/svg/black_queen.svg"));
            break;
        case WHITE_ROOK:
            svgDoc->Load(wxT("../src/GUI/bitmaps/pieces/svg/white_rook.svg"));
            break;
        case BLACK_ROOK:
            svgDoc->Load(wxT("../src/GUI/bitmaps/pieces/svg/black_rook.svg"));
            break;
        case WHITE_BISHOP:
            svgDoc->Load(wxT("../src/GUI/bitmaps/pieces/svg/white_bishop.svg"));
            break;
        case BLACK_BISHOP:
            svgDoc->Load(wxT("../src/GUI/bitmaps/pieces/svg/black_bishop.svg"));
            break;
        case WHITE_KNIGHT:
            svgDoc->Load(wxT("../src/GUI/bitmaps/pieces/svg/white_knight.svg"));
            break;
        case BLACK_KNIGHT:
            svgDoc->Load(wxT("../src/GUI/bitmaps/pieces/svg/black_knight.svg"));
            break;
        case WHITE_PAWN:
            svgDoc->Load(wxT("../src/GUI/bitmaps/pieces/svg/white_pawn.svg"));
            break;
        case BLACK_PAWN:
            svgDoc->Load(wxT("../src/GUI/bitmaps/pieces/svg/black_pawn.svg"));
            break;
        default:
            //NEVER_REACHED;
            break;
    }
    //last true is for transparency!
    mImageOfPieceOnThisSquare = svgDoc->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
    dc.DrawBitmap( mImageOfPieceOnThisSquare, 0, 0, false );
}

void SquarePanel::RenderOnChessBoard(wxPaintEvent & evt)
{
    int neww, newh;
    this->GetSize( &neww, &newh );

    if( neww != mCurrentWidth || newh != mCurrentHeight )
    {
        mCurrentWidth = neww;
        mCurrentHeight = newh;
        PaintOnBorder();
        PaintPiece();
    }
}


void SquarePanel::rightClick(wxMouseEvent& event)
{
    std::cout<<mFile<<mRank<<std::endl;
}

wxImage SquarePanel::GetImageOfPieceOnThisSquare()
{
    return mImageOfPieceOnThisSquare;
}


void SquarePanel::LeftMouseClick(wxMouseEvent& event)
{
    wxBitmapDataObject piece_to_be_moved(mImageOfPieceOnThisSquare);
    wxDropSource dragSource( this );
    dragSource.SetData( piece_to_be_moved );
    wxDragResult result = dragSource.DoDragDrop( TRUE );

    switch (result)
    {
        case wxDragCopy: std::cout<<"copy"<<std::endl; break;
        case wxDragMove: std::cout<<"move"<<std::endl; break;
        case wxDragCancel: std::cout<<"cancel"<<std::endl; break;
        default: std::cout<<"no move, no copy"<<std::endl;/* do nothing */ break;
    }

}

bool SquarePanel::OnDrop(wxCoord x, wxCoord y, wxBitmapDataObject* pObject)
{
    std::cout<<"On drop"<<std::endl;
    return true;
}


BEGIN_EVENT_TABLE(SquarePanel, wxPanel)
    EVT_SIZE(SquarePanel::OnSize)
    EVT_RIGHT_DOWN(SquarePanel::rightClick)
    EVT_PAINT(SquarePanel::RenderOnChessBoard)
    EVT_LEFT_DOWN(SquarePanel::LeftMouseClick)
END_EVENT_TABLE()
