#ifndef _DROPTARGETPANEL_HPP_
#define _DROPTARGETPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/dnd.h>

namespace slach_gui
{

class DropTargetPanel : public wxDropTarget
{
private:
    SquarePanel* mpPanel;
public:
    DropTargetPanel(SquarePanel* pParent);
    virtual ~DropTargetPanel();
    virtual wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult def);
    virtual wxDragResult OnDragOver(wxCoord x, wxCoord y, wxDragResult def);
};

} //namespace slach_gui
#endif

