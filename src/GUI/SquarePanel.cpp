#include "SquarePanel.hpp"
#include "bitmaps/letters/A.xpm"

SquarePanel::SquarePanel(wxPanel* parent, Square* pSquare, const wxColour& colour, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size),
      mpSquare(pSquare)
{
    mFile = pSquare->GetFile();
    mRank = pSquare->GetRank();
    mIsBorderSquarePanel = pSquare->IsBorderSquare();
    mIsCornerSquarePanel = pSquare->IsCornerSquare();

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
    wxStaticText textOn (this, wxID_ANY, wxT("A"), wxDefaultPosition,wxSize(65, 44));

}

SquarePanel::~SquarePanel()
{

}

void SquarePanel::WriteLetter()
{

}

void SquarePanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    //skip the event.
    event.Skip();
}

void SquarePanel::PaintLetterOnBorder(wxPaintEvent & evt)
{
    if ((mIsBorderSquarePanel==true)&&(mIsCornerSquarePanel==false))
    {
        //wxBitmap bmp(wxBITMAP(A));
        //wxPaintDC dc(this);
        //dc.DrawBitmap(bmp,0,0,false);
    }
//    wxBitmap bmp(wxBITMAP(dark_wood_ac));
//    wxPaintDC dc(this);
//    dc.DrawBitmap(bmp,0,0,false);


}


void SquarePanel::rightClick(wxMouseEvent& event)
{
    std::cout<<mFile<<mRank<<std::endl;
}
BEGIN_EVENT_TABLE(SquarePanel, wxPanel)
    EVT_SIZE(SquarePanel::OnSize)
    EVT_RIGHT_DOWN(SquarePanel::rightClick)
    EVT_PAINT(SquarePanel::PaintLetterOnBorder)
END_EVENT_TABLE()
