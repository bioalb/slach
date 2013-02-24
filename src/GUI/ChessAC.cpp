#include "slac.hpp"


bool slac::OnInit()
{
    MainFrame *frame = new MainFrame( wxT("slac"),
                                      wxPoint(250, 50),
                                      wxSize(650, 440) );

    frame->Show( true );
    return true;
}

