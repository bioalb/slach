#include "DropTargetPanel.hpp"

slach_gui::DropTargetPanel::DropTargetPanel(SquarePanel* pParent)
    : mpPanel(pParent)
{
    this->SetDataObject(new wxBitmapDataObject());
}
slach_gui::DropTargetPanel::~DropTargetPanel()
{ }

wxDragResult slach_gui::DropTargetPanel::OnData(wxCoord x, wxCoord y, wxDragResult def)
{
    std::string drop_rank = mpPanel->GetSquare()->GetRankAsString();
    std::string drop_file = mpPanel->GetSquare()->GetFileAsString();
    mpPanel->OnDrop(x,y, drop_file, drop_rank);

    return def;
}
wxDragResult slach_gui::DropTargetPanel::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
    //will implement this later
    return def;
}
