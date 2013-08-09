#include <ctime>
#include "BottomPanel.hpp"

slach_gui::BottomPanel::BottomPanel(wxPanel* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,-1, pos,size),
      mpEngineInterface( new slach::EngineInterface() ),
      mpStartEngineButton ( new wxButton(this, 1, wxT("Start Engine"),wxDefaultPosition, wxDefaultSize) ),
      mpStopEngineButton ( new wxButton(this, 2, wxT("Stop Engine"),wxDefaultPosition, wxDefaultSize) ),
      mpEngineTextBox ( new wxTextCtrl(this, wxID_ANY, wxT("Engine output"), wxDefaultPosition, wxSize(150,60), wxTE_MULTILINE) ),
      mTimer(this, 1),
      mEngineIsRunning(false)
{
    this->SetBackgroundColour(wxT("green"));
    mpEngineTextBox->SetEditable(false);
    wxBoxSizer *topsizer = new wxBoxSizer( wxVERTICAL );
    topsizer->Add(mpEngineTextBox,
        wxSizerFlags(1).Align(wxALIGN_CENTER).Expand().Border(wxALL, 10));

    wxBoxSizer *button_sizer = new wxBoxSizer( wxHORIZONTAL );
    button_sizer->Add(mpStartEngineButton,
        wxSizerFlags(0).Align(wxALIGN_LEFT).Border(wxALL, 10));

    button_sizer->Add(mpStopEngineButton,
        wxSizerFlags(0).Align(wxALIGN_LEFT).Border(wxALL, 10));

    topsizer->Add(button_sizer, wxSizerFlags(0).Left() );

    this->SetSizer(topsizer, false);
    mTimer.Start(1500);//every 500 ms

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
}

void slach_gui::BottomPanel::StopEngine(wxCommandEvent& event)
{
	mEngineIsRunning = false;
	//mpEngineInterface->StopEngine(); not working, it's in the thread!
}

void slach_gui::BottomPanel::StartEngine(wxCommandEvent& event)
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

	event.Skip();
}

wxThread::ExitCode slach_gui::BottomPanel::Entry()
{
    // IMPORTANT:
    // this function gets executed in the secondary thread context!

    // here we do our long task, periodically calling TestDestroy():
    while (!GetThread()->TestDestroy())
    {
        // since this Entry() is implemented in MyFrame context we don't
        // need any pointer to access the m_data, m_processedData, m_dataCS
        // variables... very nice!
        wxCriticalSectionLocker lock(mCritSect);
        mpEngineInterface->StartAnalsyingPosition(mpPosition); //infinite
        // VERY IMPORTANT: do not call any GUI function inside this
        //                 function; rather use wxQueueEvent():
        //wxQueueEvent(this, new wxThreadEvent(myEVT_THREAD_UPDATE));
            // we used pointer 'this' assuming it's safe; see OnClose()
    }
    // TestDestroy() returned true (which means the main thread asked us
    // to terminate as soon as possible) or we ended the long task...
    return (wxThread::ExitCode)0;
}

void slach_gui::BottomPanel::OnClose(wxCloseEvent&)
{
	mpEngineInterface->StopEngine();
    // important: before terminating, we _must_ wait for our joinable
    // thread to end, if it's running; in fact it uses variables of this
    // instance and posts events to *this event handler
    if (GetThread() &&      // DoStartALongTask() may have not been called
        GetThread()->IsRunning())
    {
        GetThread()->Kill();
    }
    Destroy();
}

void slach_gui::BottomPanel::OnThreadUpdate(wxThreadEvent& evt)
{

	evt.Skip();
}

void slach_gui::BottomPanel::UpdateEngineOutput(wxTimerEvent& evt)
{
	if (mEngineIsRunning == true)
	{
		//wxStreamToTextRedirector redirect(mpEngineTextBox); not working
		(*mpEngineTextBox)<<mpEngineInterface->GetLatestEngineOutput();
	}
	evt.Skip();
}

wxDEFINE_EVENT(myEVT_THREAD_UPDATE, wxThreadEvent);
wxBEGIN_EVENT_TABLE(slach_gui::BottomPanel, wxPanel)
    EVT_THREAD(myEVT_THREAD_UPDATE, slach_gui::BottomPanel::OnThreadUpdate)
    EVT_CLOSE(slach_gui::BottomPanel::OnClose)
    EVT_SIZE(slach_gui::BottomPanel::OnSize)
    EVT_BUTTON(1, slach_gui::BottomPanel::StartEngine)
    EVT_BUTTON(2, slach_gui::BottomPanel::StopEngine)
    EVT_TIMER(1, slach_gui::BottomPanel::UpdateEngineOutput)
wxEND_EVENT_TABLE()
