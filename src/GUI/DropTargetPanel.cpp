#include "DropTargetPanel.hpp"

DropTargetPanel::DropTargetPanel(SquarePanel* pParent)
    : mpPanel(pParent)
{
    this->SetDataObject(new wxBitmapDataObject());
}
DropTargetPanel::~DropTargetPanel()
{ }

wxDragResult DropTargetPanel::OnData(wxCoord x, wxCoord y, wxDragResult def)
{
    //std::cout<<mpPanel->GetSquare()->GetFile()<<std::endl;
//    wxBitmap bmp  = ( (wxBitmapDataObject*)GetDataObject() )->GetBitmap();
//    if (bmp.IsOk())
//    {
//        std::cout<<"OK"<<std::endl;
//    }

    std::string drop_rank = mpPanel->GetSquare()->GetRank();
    std::string drop_file = mpPanel->GetSquare()->GetFile();
    mpPanel->OnDrop(x,y, drop_file, drop_rank);

    return def;
}
wxDragResult DropTargetPanel::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
    //will implement this later
    return def;
}
