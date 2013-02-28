#include "slach.hpp"


bool slach::OnInit()
{
    MainFrame *frame = new MainFrame( wxT("slach"),
                                      wxPoint(250, 50),
                                      wxSize(650, 440) );

    frame->Show( true );
    return true;
}

