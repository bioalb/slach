#include <wx/sizer.h>
#include "MainFrame.hpp"


slach_gui::MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
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

    mpRightPanel = new RightPanel(this);
    mpBottomPanel = new BottomPanel(this);
    mpCentralPanel = new CentralPanel(this);
    mpBottomPanel->SetMinSize(wxSize(50, 20));
    wxBoxSizer* h_sizer = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer* v_sizer = new wxBoxSizer(wxVERTICAL);
    v_sizer->Add(mpCentralPanel, 5, wxEXPAND);
    v_sizer->Add(mpBottomPanel, 1, wxEXPAND);

    h_sizer->Add(v_sizer,4,wxEXPAND);
    h_sizer->Add(mpRightPanel, 1, wxEXPAND);
    this->SetSizer(h_sizer);
}

void slach_gui::MainFrame::UpdateChessPositionForEngine(slach::Position* pPosition)
{
	mpBottomPanel->SetPositionToAnalyse(pPosition);
}

slach_gui::MainFrame::~MainFrame()
{

}

void slach_gui::MainFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
    mpBottomPanel->DoStopEngine();
    Close( true );
}
void slach_gui::MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    //first is content of the window, second string is title of the window.
    wxMessageBox( wxT("This is Alberto testing the widgets"),
    wxT("About Slach"), wxOK | wxICON_INFORMATION );
}

wxBEGIN_EVENT_TABLE(slach_gui::MainFrame, wxFrame)
    EVT_MENU(wxID_EXIT,  slach_gui::MainFrame::OnExit)
    EVT_MENU(wxID_ABOUT, slach_gui::MainFrame::OnAbout)
wxEND_EVENT_TABLE()
