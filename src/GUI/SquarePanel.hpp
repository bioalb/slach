#ifndef _SQAUREPANEL_HPP_
#define _SQAUREPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/dnd.h>
#include "Square.hpp"

namespace slach_gui
{

class ChessBoardPanel;//forward declaration of the parent

class SquarePanel : public wxPanel
{

private:

    wxPanel* mpParent;

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

    /**
     * tells whether at the next refresh we need to draw a piece or not
     * True by default, it should be kept true unless we need a deletion.
     * Do remember to switch it back to true after deleting a piece
     */
    bool mDrawPiece;

    std::vector<wxImage> mPngImages;

public:
    SquarePanel(wxPanel* parent, slach::Square* pSquare,const wxColour& colour = wxT("red"), const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize, long style =  wxBORDER_NONE);
    ~SquarePanel();

    /*
     * Here we call refresh to tell the panel to draw itself again.
     * So when the user resizes the image panel the image should be resized too.
     */
    void OnSize(wxSizeEvent& event);

    /**
     * This method handles the rendering of images on this square panel.
     * First, it checks if we are a border square and draw border markers accordingly.
     *
     * If not on the border,it then examines the member variable
     * mDrawPiece. If true, the piece will be drawn.
     * If false, the piece will be deleted from the square.
     * This method is executed during a paint event, hence at every refresh.
     *
     * @param evt the paint event (skipped at the end)
     */
    void RenderOnChessBoard(wxPaintEvent & evt);

    void rightClick(wxMouseEvent& event);
    void LeftMouseClick(wxMouseEvent& event);
    virtual bool OnDrop(wxCoord x, wxCoord y, std::string file, std::string rank);

    wxImage GetImageOfPieceOnThisSquare();

    /**
     * this method gets you a pointer to the underlying Square object.
     *
     * @return a ointer to the underlying slach::Square object
     */
    slach::Square* GetSquare();

    /**
     * Sets whether we wish to draw a piece on this square or not.
     * The drawing will take place at the next Refresh().
     * You can pass false to this method and achieve deletion of a piece
     * at the next Refresh().
     *
     * @param drawPiece true if you want the piece drawn, false if you want just the background
     *                  e.g., for deleting ane xisting piece.
     */
    void SetToDrawPiece(bool drawPiece = true);

    void SetPngImages(std::vector<wxImage>& pngImages);

    wxDECLARE_EVENT_TABLE();
};

}//namespace slach_gui
#endif /* _SQUARE_HPP_ */
