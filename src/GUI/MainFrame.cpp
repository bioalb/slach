#include <wx/sizer.h>
#include "MainFrame.hpp"


MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
  : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    //the File menu
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(1, wxT("&Hello...\tCtrl-H"),
    wxT("Help string shown in status bar for this menu item"));
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    //the help menu
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, wxT("&File") );
    menuBar->Append( menuHelp, wxT("&Help") );
    //creates the menu bar
    SetMenuBar( menuBar );
    //creates status bar
    CreateStatusBar();
    SetStatusText( wxT("Welcome to SLACH!") );

    this->SetBackgroundColour(wxT("red"));

    //creates the two main panels
    wxBoxSizer* h_sizer = new wxBoxSizer(wxHORIZONTAL);
    // then simply create like this
    right_panel = new RightPanel(this);
    main_panel = new MainPanel(this);

    h_sizer->Add(main_panel, 2.8, wxEXPAND);
    h_sizer->Add(right_panel, 1.0, wxEXPAND);

    this->SetSizer(h_sizer);
}

MainFrame::~MainFrame()
{
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void MainFrame::OnAbout(wxCommandEvent& event)
{
    //first is content of the window, second string is title of the window.
    wxMessageBox( wxT("This is Alberto testing the widgets"),
    wxT("About Slach"), wxOK | wxICON_INFORMATION );
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(wxID_EXIT,  MainFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
END_EVENT_TABLE()
