#include "slach.hpp"


bool slach::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler);
    MainFrame *frame = new MainFrame( wxT("slach"),
                                      wxPoint(250, 50),
                                      wxSize(650, 440) );


    frame->Show( true );
    return true;
}

