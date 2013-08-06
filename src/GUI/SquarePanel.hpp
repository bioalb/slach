#ifndef _SQAUREPANEL_HPP_
#define _SQAUREPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/dnd.h>
#include "Square.hpp"

namespace slach_gui
{

class ActualBoardPanel;//forward declaration of the parent

class SquarePanel : public wxPanel
{

private:

    ActualBoardPanel* mpParent;

    std::string mFile;
    std::string mRank;

    /**True if the square belongs to the border. False by  default*/
    bool mIsBorderSquarePanel;

    bool mIsCornerSquarePanel;

    bool mIsSquarePanelPrintable;

    slach::Square* mpSquare;

    wxBitmap mResized;

    int mCurrentWidth;
    int mCurrentHeight;

    void PaintOnBorder(wxPaintDC& dc);
    void PaintPiece(wxPaintDC& dc);
    void PaintBackground(wxPaintDC& dc);

    void DetermineCoordinateToPrint();

    wxImage mPrintedCoord;
    wxImage mImageOfPieceOnThisSquare;
    wxImage mBackgroundOnThisSquare;
    wxIcon mIconNearTheMouse;

    bool mDrawPiece;
    bool mDeletePiece;

public:
    SquarePanel(ActualBoardPanel* parent, slach::Square* pSquare,const wxColour& colour = wxT("red"), const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize, long style =  wxBORDER_NONE);
    ~SquarePanel();

    /*
     * Here we call refresh to tell the panel to draw itself again.
     * So when the user resizes the image panel the image should be resized too.
     */
    void OnSize(wxSizeEvent& event);

    void RenderOnChessBoard(wxPaintEvent & evt);

    void rightClick(wxMouseEvent& event);
    void LeftMouseClick(wxMouseEvent& event);
    virtual bool OnDrop(wxCoord x, wxCoord y, std::string file, std::string rank);

    wxImage GetImageOfPieceOnThisSquare();

    slach::Square* GetSquare();

    void SetToDrawPiece(bool drawPiece = true);
    void SetToDeletePiece(bool deletePiece = true);

    wxDECLARE_EVENT_TABLE();
};

}//namespace slach_gui
#endif /* _SQUARE_HPP_ */
