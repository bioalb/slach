#ifndef _SQAUREPANEL_HPP_
#define _SQAUREPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/dnd.h>
#include "../Square.hpp"
#include "ActualBoardPanel.hpp"

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

    Square* mpSquare;

    wxBitmap mResized;

    int mCurrentWidth;
    int mCurrentHeight;

    void PaintOnBorder();
    void PaintPiece();
    void DetermineCoordinateToPrint();
    wxImage* mpPrintedCoord;
    wxImage mImageOfPieceOnThisSquare;

public:
    SquarePanel(ActualBoardPanel* parent, Square* pSquare,const wxColour& colour = wxT("red"), const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);
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

    Square* GetSquare();

    DECLARE_EVENT_TABLE()
};

#endif /* _SQUARE_HPP_ */
