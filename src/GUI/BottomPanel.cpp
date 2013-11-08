#include <ctime>
#include "BottomPanel.hpp"

slach_gui::BottomPanel::BottomPanel(wxFrame* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,-1, pos,size),
      mpEngineInterface( new slach::EngineInterface() ),
      mpStartEngineButton ( new wxButton(this, 1, wxT("Start Engine"),wxDefaultPosition, wxDefaultSize) ),
      mpStopEngineButton ( new wxButton(this, 2, wxT("Stop Engine"),wxDefaultPosition, wxDefaultSize) ),
      mpEngineTextBox ( new wxTextCtrl(this, wxID_ANY, wxT("Engine output"), wxDefaultPosition, wxSize(150,60), wxTE_MULTILINE | wxBORDER_SIMPLE) ),
      mpScoreTextBox ( new wxRichTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE) ),
      mTimer(this, 1),
      mEngineIsRunning(false)
{
    this->SetBackgroundColour(wxColour(35,87,102));
    mpEngineTextBox->SetEditable(false);
    mpScoreTextBox->SetBackgroundColour(wxColour(35,87,102));
    wxFont font(12, wxROMAN, wxNORMAL, wxNORMAL);
    mpScoreTextBox->SetFont(font);

    wxBoxSizer *topsizer = new wxBoxSizer( wxHORIZONTAL );
    topsizer->Add(mpEngineTextBox,
    wxSizerFlags(6).Align(wxALIGN_CENTER).Expand().Border(wxALL, 10));
    topsizer->Add(mpScoreTextBox, 
    wxSizerFlags(1).Align(wxALIGN_CENTER).Expand());

    wxBoxSizer *button_sizer = new wxBoxSizer( wxHORIZONTAL );
    button_sizer->Add(mpStartEngineButton,
        wxSizerFlags(0).Align(wxALIGN_LEFT).Border(wxALL, 10));

    button_sizer->Add(mpStopEngineButton,
        wxSizerFlags(0).Align(wxALIGN_LEFT).Border(wxALL, 10));

    topsizer->Add(button_sizer, wxSizerFlags(0).Left() );



    this->SetSizer(topsizer, false);
    mTimer.Start(1500);//every 1500 ms

}

slach_gui::BottomPanel::~BottomPanel()
{
    delete mpEngineInterface;
}

void slach_gui::BottomPanel::OnSize(wxSizeEvent& event)
{
    Refresh();

    //skip the event.
    event.Skip();
}

void slach_gui::BottomPanel::SetPositionToAnalyse(slach::Position* pPosition)
{
    mpPosition = pPosition;
    mpEngineTextBox->Clear();//clear the box
    if (mEngineIsRunning == true)
    {
    	DoStopEngine();
    	DoStartEngine();
    }
}

void slach_gui::BottomPanel::StopEngine(wxCommandEvent& event)
{
	DoStopEngine();
	event.Skip();
}

void slach_gui::BottomPanel::StartEngine(wxCommandEvent& event)
{
    mpEngineTextBox->Clear();//clear the box
	DoStartEngine();
	event.Skip();
}

void slach_gui::BottomPanel::DoStopEngine()
{
	mEngineIsRunning = false;
	wxCriticalSectionLocker lock(mCritSect);
	mpEngineInterface->StopEngine();
}

void slach_gui::BottomPanel::DoStartEngine()
{
	mEngineIsRunning = true;
    // we want to start a long task, but we don't want our GUI to block
    // while it's executed, so we use a thread to do it.
	if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR)
	{
		wxLogError("Could not create the worker thread!");
		return;
	}
	// go!
	if (GetThread()->Run() != wxTHREAD_NO_ERROR)
	{
		wxLogError("Could not run the worker thread!");
		return;
	}
}

wxThread::ExitCode slach_gui::BottomPanel::Entry()
{
    // IMPORTANT:this function gets executed in the secondary thread context!
	wxCriticalSectionLocker lock(mCritSect);
	mpEngineInterface->StartAnalsyingPosition(mpPosition); //infinite
    return (wxThread::ExitCode)0;
}

void slach_gui::BottomPanel::OnClose(wxCloseEvent&)
{
	if (mEngineIsRunning == true)
	{
		DoStopEngine();
	}
    // important: before terminating, we _must_ wait for our joinable
    // thread to end, if it's running; in fact it uses variables of this
    // instance and posts events to *this event handler
    if ( GetThread() &&   GetThread()->IsRunning())
    {
    	GetThread()->Wait();
    }
    Destroy();
}

void slach_gui::BottomPanel::UpdateEngineOutput(wxTimerEvent& evt)
{
	if (mEngineIsRunning == true)
	{
		//wxStreamToTextRedirector redirect(mpEngineTextBox); //not working
		(*mpEngineTextBox)<<mpEngineInterface->GetLatestEngineOutput();
		mpScoreTextBox->BeginTextColour(wxColour(255, 255, 255));
		mpScoreTextBox->ChangeValue("");
		mpScoreTextBox->BeginAlignment(wxTEXT_ALIGNMENT_LEFT);
		mpScoreTextBox->WriteText( wxT("Depth: "));
		mpScoreTextBox->WriteText( wxString::Format(wxT("%d"), mpEngineInterface->GetLatestDepth()) );
		mpScoreTextBox->Newline();
		mpScoreTextBox->WriteText( wxT("Score: "));
		mpScoreTextBox->BeginAlignment(wxTEXT_ALIGNMENT_CENTRE);
		mpScoreTextBox->BeginFontSize(18);
		mpScoreTextBox->WriteText( wxString::Format(wxT("%f"), mpEngineInterface->GetLatestScore()) );
		mpScoreTextBox->EndAlignment();
		mpScoreTextBox->EndFontSize();
		mpScoreTextBox->EndTextColour();
	}
	evt.Skip();
}

wxBEGIN_EVENT_TABLE(slach_gui::BottomPanel, wxPanel)
    EVT_CLOSE(slach_gui::BottomPanel::OnClose)
    EVT_SIZE(slach_gui::BottomPanel::OnSize)
    EVT_BUTTON(1, slach_gui::BottomPanel::StartEngine)
    EVT_BUTTON(2, slach_gui::BottomPanel::StopEngine)
    EVT_TIMER(1, slach_gui::BottomPanel::UpdateEngineOutput)
wxEND_EVENT_TABLE()
