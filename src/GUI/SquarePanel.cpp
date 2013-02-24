#include "SquarePanel.hpp"
#include "bitmaps/A.xpm"

SquarePanel::SquarePanel(wxPanel* parent, const wxColour& colour, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size)
{
    this->SetBackgroundColour(colour);
    mFile = wxT("UNDEFINED_FILE");
    mRank = wxT("UNDEFINED_RANK");
    mIsBorderSquarePanel = false;

}

SquarePanel::~SquarePanel()
{
}

void SquarePanel::SetAsBorderSquare(bool border)
{
    mIsBorderSquarePanel = border;
}

void SquarePanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    //skip the event.
    event.Skip();
}

void SquarePanel::SetFile(wxString file)
{
    mFile = file;
}

void SquarePanel::SetRank(wxString rank)
{
    mRank = rank;
}

wxString SquarePanel::GetFile()
{
    return mFile;
}

wxString SquarePanel::GetRank()
{
    return mRank;
}

void SquarePanel::PaintLetterOnBorder(wxPaintEvent & evt)
{
    if (mIsBorderSquarePanel==true)
    {
        wxBitmap bmp(wxBITMAP(A));
        wxPaintDC dc(this);
        dc.DrawBitmap(bmp,0,0,false);
    }
}

void SquarePanel::rightClick(wxMouseEvent& event)
{
    //wxString coord = mFile.Append(mRank);
    std::cout<<mFile.mb_str()<<mRank.mb_str()<<std::endl;

}
BEGIN_EVENT_TABLE(SquarePanel, wxPanel)
    EVT_SIZE(SquarePanel::OnSize)
    EVT_RIGHT_DOWN(SquarePanel::rightClick)
    EVT_PAINT(SquarePanel::PaintLetterOnBorder)
END_EVENT_TABLE()
