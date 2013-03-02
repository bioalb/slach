#include <wx/mstream.h>
#include <algorithm>
#include "SquarePanel.hpp"
#include "bitmaps/letters/png/A.png.h"

SquarePanel::SquarePanel(wxPanel* parent, Square* pSquare, const wxColour& colour, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size),
      mpSquare(pSquare)
{
    mFile = pSquare->GetFile();
    mRank = pSquare->GetRank();
    mIsBorderSquarePanel = pSquare->IsBorderSquare();
    mIsCornerSquarePanel = pSquare->IsCornerSquare();
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
        this->SetBackgroundColour(wxT("red"));
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

void SquarePanel::PaintOnBorder()
{
    if ((mIsBorderSquarePanel==true)&&(mIsCornerSquarePanel==false))
    {
        //wxBitmap bmp(wxBITMAP(A));
        //wxImage image = bmp.ConvertToImage();
        wxPaintDC dc(this);

        int neww, newh;
        this->GetSize( &neww, &newh );

        if( neww != mCurrentWidth || newh != mCurrentHeight )
        {
            wxMemoryInputStream istream(A_img, sizeof A_img);
            wxImage letter(istream, wxBITMAP_TYPE_PNG);

            int letter_width = letter.GetWidth();
            int letter_height = letter.GetHeight();
            double scale_factor = 1.0;
            double fractional_occupancy_of_space= 0.8;

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
                dim =  mCurrentWidth*fractional_occupancy_of_space;
                xcoord = mCurrentWidth*(1-fractional_occupancy_of_space)/2.0;
                ycoord = (mCurrentHeight-dim)/2;
            }
            else
            {
                dim = mCurrentHeight*fractional_occupancy_of_space;
                xcoord = (mCurrentWidth-dim)/2;
                ycoord = mCurrentHeight*(1-fractional_occupancy_of_space)/2.0;
            }
            wxBitmap resized = wxBitmap( letter.Scale(scale_factor*dim, scale_factor*dim /*, wxIMAGE_QUALITY_HIGH*/ ) );
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
