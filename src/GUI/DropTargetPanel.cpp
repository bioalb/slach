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
    std::cout<<"I want to see this printed on screen!"<<std::endl;
    mpPanel->OnDrop(x,y,((wxBitmapDataObject*)GetDataObject()));
    return def;
}
wxDragResult DropTargetPanel::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
    //will implement this later
    return def;
}
