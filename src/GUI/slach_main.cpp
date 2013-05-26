#include "slach_main.hpp"


bool slach_main::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler);
    slach_gui::MainFrame *frame = new slach_gui::MainFrame( wxT("slach"),
                                      wxPoint(250, 50),
                                      wxSize(650, 440) );


    frame->Show( true );
    return true;
}

