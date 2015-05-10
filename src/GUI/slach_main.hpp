
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/app.h>
#include "MainFrame.hpp"


class slach_main : public wxApp
{
public:
    virtual bool OnInit();
};

wxDECLARE_APP(slach_main);



