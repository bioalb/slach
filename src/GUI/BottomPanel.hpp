#ifndef _BOTTOMPANEL_HPP_
#define _BOTTOMPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>

class BottomPanel : public wxPanel
{

public:
    BottomPanel(wxFrame* parent, const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);
    ~BottomPanel();

    /*
     * Here we call refresh to tell the panel to draw itself again.
     * So when the user resizes the image panel the image should be resized too.
     */
    void OnSize(wxSizeEvent& event);

    DECLARE_EVENT_TABLE()
};

#endif /* _BOTTOMPANEL_HPP_ */
