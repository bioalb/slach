#ifndef _DROPTARGETPANEL_HPP_
#define _DROPTARGETPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/dnd.h>

namespace slach_gui
{

/**
 * This class is used for drag and drop operations.
 * Each square on the chessboard is also a target, hence
 * it sets a DropTargetPanel.
 *
 * wxWidgets mandates to derive from some wxDropTarget
 * and implements its pure virtual methods.
 *
 * This class holds an index (that can be set) to identify itself
 * (i.e., which square it represents)
 */
class DropTargetPanel : public wxDropTarget
{
private:
	/** cache for the parent window (here a ChessBoard panel)*/
    wxPanel* mpPanel;
    /** cache for an identification index, initialized at 0*/
    unsigned mIndex;
public:

    /**
     * Constructor.
     * It caches the prent window that is passed in and sets the data type
     * for the drag and drop to be of Bitmap type.
     *
     * @param pParent the parent panel (here, a ChessBoard panel)
     */
    DropTargetPanel(wxPanel* pParent);

    /**
     * Destructor
     */
    virtual ~DropTargetPanel();

    /**
     * Upon release of the mouse, this method gets called.
     * Since this is the end of the drag and drop, we now have all info
     * to process the move (origin and destination squares).
     *
     * What it does is to call a specific method in the parent class
     * (the chessboard) that will process the move.
     * To this method it passes in the index (mIndex) of identification so that
     * the destination square can be properly retrieved.
     *
     * @param x (unused)
     * @param y (unused)
     * @param def this is simply returned.
     */
    virtual wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult def);

    /**
     * not implemented yet
     */
    virtual wxDragResult OnDragOver(wxCoord x, wxCoord y, wxDragResult def);

    /**
     * Allow setting of mIndex
     *
     * @param index the index we wish to set. No check is performed.
     */
    void SetIndexOfSquare(unsigned index);
};

} //namespace slach_gui
#endif

