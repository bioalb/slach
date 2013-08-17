#include "DropTargetPanel.hpp"
#include "ChessBoardPanel.hpp"
slach_gui::DropTargetPanel::DropTargetPanel(wxPanel* pParent)
    : mpPanel(pParent)
{
	mIndex = 0;
    this->SetDataObject(new wxBitmapDataObject());
}
slach_gui::DropTargetPanel::~DropTargetPanel()
{ }

void slach_gui::DropTargetPanel::SetIndexOfSquare(unsigned index)
{
	mIndex = index;
}
wxDragResult slach_gui::DropTargetPanel::OnData(wxCoord x, wxCoord y, wxDragResult def)
{
	(static_cast<ChessBoardPanel*> (mpPanel))->LeftMouseRelease(mIndex);
    return def;
}
wxDragResult slach_gui::DropTargetPanel::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
    //will implement this later
    return def;
}
