#include <wx/mstream.h>
#include <algorithm>
#include "SquarePanel.hpp"
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
      mpSquare(pSquare)
{
    mFile = pSquare->GetFile();
    mRank = pSquare->GetRank();
    mIsBorderSquarePanel = pSquare->IsBorderSquare();
    mIsCornerSquarePanel = pSquare->IsCornerSquare();
    mIsSquarePanelPrintable = pSquare->IsCoordinatePrintable();
    mCurrentWidth = -1;
    mCurrentHeight = -1;

    //this->SetBackgroundColour(colour);

    if ( (pSquare->IsDarkSquare() == true) && (pSquare->IsBorderSquare() == false))
    {
        this->SetBackgroundColour(wxT("black"));
    }
    if ( (pSquare->IsLightSquare() == true) && (pSquare->IsBorderSquare() == false))
    {
        this->SetBackgroundColour(wxT("white"));
    }
    if (pSquare->IsBorderSquare())
    {
        this->SetBackgroundColour(wxT("brown"));
    }
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
    if (mFile=="B")
    {
        wxMemoryInputStream istream(b_img, sizeof b_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    if (mFile=="C")
    {
        wxMemoryInputStream istream(c_img, sizeof c_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    if (mFile=="D")
    {
        wxMemoryInputStream istream(d_img, sizeof d_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    if (mFile=="E")
    {
        wxMemoryInputStream istream(e_img, sizeof e_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    if (mFile=="F")
    {
        wxMemoryInputStream istream(f_img, sizeof f_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    if (mFile=="G")
    {
        wxMemoryInputStream istream(g_img, sizeof g_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    if (mFile=="H")
    {
        wxMemoryInputStream istream(h_img, sizeof h_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }

    if (mRank=="1")
    {
        wxMemoryInputStream istream(one_img, sizeof one_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    if (mRank=="2")
    {
        wxMemoryInputStream istream(two_img, sizeof two_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    if (mRank=="3")
    {
        wxMemoryInputStream istream(three_img, sizeof three_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    if (mRank=="4")
    {
        wxMemoryInputStream istream(four_img, sizeof four_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    if (mRank=="5")
    {
        wxMemoryInputStream istream(five_img, sizeof five_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    if (mRank=="6")
    {
        wxMemoryInputStream istream(six_img, sizeof six_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    if (mRank=="7")
    {
        wxMemoryInputStream istream(seven_img, sizeof seven_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
    if (mRank=="8")
    {
        wxMemoryInputStream istream(eight_img, sizeof eight_img);
        mpPrintedCoord = new wxImage(istream, wxBITMAP_TYPE_PNG);
    }
}

void SquarePanel::PaintOnBorder()
{
    if ( (mIsBorderSquarePanel==true &&
          mIsCornerSquarePanel==false &&
          mIsSquarePanelPrintable==true))
    {
        DetermineCoordinateToPrint();//this gets the right mpPrintedCoord

        wxPaintDC dc(this);

        int neww, newh;
        this->GetSize( &neww, &newh );

        if( neww != mCurrentWidth || newh != mCurrentHeight )
        {
            assert(mpPrintedCoord!=NULL);
            int letter_width = mpPrintedCoord->GetWidth();
            int letter_height = mpPrintedCoord->GetHeight();
            double scale_factor = 1.0;
            double fractional_occupancy_of_space= 0.7;

            //apply a scale factor if the square is too small
            if (letter_width>neww || letter_height>newh)
            {
                scale_factor = double( std::min(neww,newh) )/ double(std::max((letter_width), (letter_height)));
            }

            mCurrentWidth = neww;
            mCurrentHeight = newh;
            int dim = 0;
            int xcoord = 0;
            int ycoord = 0;
            if (mCurrentWidth<=mCurrentHeight)
            {
                dim =  mCurrentWidth*fractional_occupancy_of_space*scale_factor;
                xcoord = mCurrentWidth*(1-fractional_occupancy_of_space)/2.0;
                ycoord = (mCurrentHeight-dim)/2;
            }
            else
            {
                dim = mCurrentHeight*fractional_occupancy_of_space*scale_factor;
                xcoord = (mCurrentWidth-dim)/2;
                ycoord = mCurrentHeight*(1-fractional_occupancy_of_space)/2.0;
            }
            wxBitmap resized = wxBitmap( mpPrintedCoord->Scale(dim, dim) );
            dc.DrawBitmap( resized, xcoord, ycoord, false );
        }
    }
}
void SquarePanel::RenderOnChessBoard(wxPaintEvent & evt)
{
    PaintOnBorder();
}


void SquarePanel::rightClick(wxMouseEvent& event)
{
    std::cout<<mFile<<mRank<<std::endl;
}
BEGIN_EVENT_TABLE(SquarePanel, wxPanel)
    EVT_SIZE(SquarePanel::OnSize)
    EVT_RIGHT_DOWN(SquarePanel::rightClick)
    EVT_PAINT(SquarePanel::RenderOnChessBoard)
END_EVENT_TABLE()
