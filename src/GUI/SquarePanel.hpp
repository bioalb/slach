#ifndef _SQAUREPANEL_HPP_
#define _SQAUREPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>

class SquarePanel : public wxPanel
{

private:
    wxString mFile;
    wxString mRank;

    /**True if the square belongs to the border. False by  default*/
    bool mIsBorderSquarePanel;
public:
    SquarePanel(wxPanel* parent, const wxColour& colour, const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);
    ~SquarePanel();

    /*
     * Here we call refresh to tell the panel to draw itself again.
     * So when the user resizes the image panel the image should be resized too.
     */
    void OnSize(wxSizeEvent& event);

    void SetFile(wxString file);

    void SetRank(wxString rank);

    void SetAsBorderSquare(bool border=true);

    wxString GetFile();

    wxString GetRank();

    void PaintLetterOnBorder(wxPaintEvent & evt);

    void rightClick(wxMouseEvent& event);
    DECLARE_EVENT_TABLE()
};

#endif /* _SQUARE_HPP_ */
