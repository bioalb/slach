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


SquarePanel::SquarePanel(ActualBoardPanel* parent, Square* pSquare, const wxColour& colour, const wxPoint& pos, const wxSize& size, long style )
    : wxPanel(parent,wxID_ANY, pos,size, style),
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

    PaintBackground();
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

Square* SquarePanel::GetSquare()
{
    return mpSquare;
}

void SquarePanel::PaintBackground()
{
    std::vector<wxSVGDocument*> svgdocs = mpParent->GetPiecesSvgDocs();
    if ( (mpSquare->IsDarkSquare() == true) && (mpSquare->IsBorderSquare() == false))
    {
        this->SetBackgroundColour(wxColour(32,107,129));
        mBackgroundOnThisSquare = svgdocs[13]->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
    }
    if ( (mpSquare->IsLightSquare() == true) && (mpSquare->IsBorderSquare() == false))
    {
        this->SetBackgroundColour(wxColour(235,241,246));
        mBackgroundOnThisSquare = svgdocs[14]->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
    }
    if (mpSquare->IsBorderSquare())
    {
        //mBackgroundOnThisSquare = svgdocs[15]->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
        this->SetBackgroundColour(wxColour(35,87,102));
    }


    //now really draw the rendered image
    wxPaintDC dc(this);
    dc.DrawBitmap( mBackgroundOnThisSquare, 0, 0, false );
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
    std::vector<wxSVGDocument*> svgdocs = mpParent->GetPiecesSvgDocs();

    switch(piece)
    {
        case WHITE_KING:
            //last true is for transparency!
            mImageOfPieceOnThisSquare = svgdocs[0]->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
            break;
        case BLACK_KING:
            mImageOfPieceOnThisSquare = svgdocs[1]->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
            break;
        case WHITE_QUEEN:
            mImageOfPieceOnThisSquare = svgdocs[2]->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
            break;
        case BLACK_QUEEN:
            mImageOfPieceOnThisSquare = svgdocs[3]->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
            break;
        case WHITE_ROOK:
            mImageOfPieceOnThisSquare = svgdocs[4]->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
            break;
        case BLACK_ROOK:
            mImageOfPieceOnThisSquare = svgdocs[5]->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
            break;
        case WHITE_BISHOP:
            mImageOfPieceOnThisSquare = svgdocs[6]->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
            break;
        case BLACK_BISHOP:
            mImageOfPieceOnThisSquare = svgdocs[7]->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
            break;
        case WHITE_KNIGHT:
            mImageOfPieceOnThisSquare = svgdocs[8]->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
            break;
        case BLACK_KNIGHT:
            mImageOfPieceOnThisSquare = svgdocs[9]->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
            break;
        case WHITE_PAWN:
            mImageOfPieceOnThisSquare = svgdocs[10]->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
            break;
        case BLACK_PAWN:
            mImageOfPieceOnThisSquare = svgdocs[11]->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
            break;
        case NO_PIECE:
            mImageOfPieceOnThisSquare = svgdocs[12]->Render(mCurrentWidth,mCurrentHeight,NULL,true,true);
            break;
        default:
            //NEVER_REACHED;
            break;
    }

    //now really draw the rendered image
    wxPaintDC dc(this);
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
        PaintBackground();
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
    //first record source coordinates
    mpParent->SetOriginSquare(this);
    wxBitmapDataObject piece_to_be_moved(mImageOfPieceOnThisSquare);
    wxDropSource dragSource( this );
    dragSource.SetData( piece_to_be_moved );
    wxDragResult result = dragSource.DoDragDrop( TRUE );

    switch (result)
    {
        case wxDragCopy: break;
        case wxDragMove:  break;
        case wxDragCancel: break;
        default: break;
    }
}

bool SquarePanel::OnDrop(wxCoord x, wxCoord y, std::string file, std::string rank)
{
    mpParent->SetDestinationSquare(this);
    return true;
}


BEGIN_EVENT_TABLE(SquarePanel, wxPanel)
    EVT_SIZE(SquarePanel::OnSize)
    EVT_RIGHT_DOWN(SquarePanel::rightClick)
    EVT_PAINT(SquarePanel::RenderOnChessBoard)
    EVT_LEFT_DOWN(SquarePanel::LeftMouseClick)
END_EVENT_TABLE()
