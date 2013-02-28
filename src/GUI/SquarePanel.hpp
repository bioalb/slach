#ifndef _SQAUREPANEL_HPP_
#define _SQAUREPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include "../Square.hpp"

class SquarePanel : public wxPanel
{

private:
    std::string mFile;
    std::string mRank;

    /**True if the square belongs to the border. False by  default*/
    bool mIsBorderSquarePanel;

    bool mIsCornerSquarePanel;

    Square* mpSquare;

    wxBitmap mResized;


public:
    SquarePanel(wxPanel* parent, Square* pSquare,const wxColour& colour = wxT("red"), const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);
    ~SquarePanel();

    /*
     * Here we call refresh to tell the panel to draw itself again.
     * So when the user resizes the image panel the image should be resized too.
     */
    void OnSize(wxSizeEvent& event);

    void PaintLetterOnBorder(wxPaintEvent & evt);

    void rightClick(wxMouseEvent& event);
    DECLARE_EVENT_TABLE()
};

#endif /* _SQUARE_HPP_ */
