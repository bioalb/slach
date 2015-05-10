#include "slach_main.hpp"

wxIMPLEMENT_APP(slach_main);

bool slach_main::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler);
    slach_gui::MainFrame *frame = new slach_gui::MainFrame( wxT("slach"),
                                      wxPoint(100, 50),
                                      wxSize(1500, 1000) );


    frame->Show( true );
    return true;
}


