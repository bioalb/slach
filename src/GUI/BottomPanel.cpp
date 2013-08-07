#include "BottomPanel.hpp"

slach_gui::BottomPanel::BottomPanel(wxPanel* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,-1, pos,size),
      mpEngineInterface( new slach::EngineInterface() ),
      mpStartEngineButton ( new wxButton(this, 1, wxT("Start Engine"),wxDefaultPosition, wxDefaultSize) )
{
    this->SetBackgroundColour(wxT("green"));
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

void slach_gui::BottomPanel::StartEngine(wxCommandEvent& event)
{

    wxTextCtrl* text = new wxTextCtrl(this, wxID_ANY, wxT("HELLO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"), wxDefaultPosition, wxSize(350,180), wxTE_MULTILINE);
    //text->SetEditable(false);
    text->Refresh();

    {
        wxStreamToTextRedirector redirect(text);
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

//    //main thread now
//    time_t time_now;
//    time_t previous_time;
//
//    time(&previous_time);
//    while (true)
//    {
//        time(&time_now);
//        text->Refresh();
//        if (difftime(time_now,previous_time) > 3.0)
//        {
//            previous_time = time_now;
//            std::cout << "engine is running...every 3 seconds I write this";
//        }
//    }


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
        wxQueueEvent(this, new wxThreadEvent(myEVT_THREAD_UPDATE));
            // we used pointer 'this' assuming it's safe; see OnClose()
    }
    // TestDestroy() returned true (which means the main thread asked us
    // to terminate as soon as possible) or we ended the long task...
    return (wxThread::ExitCode)0;
}

void slach_gui::BottomPanel::OnClose(wxCloseEvent&)
{
    // important: before terminating, we _must_ wait for our joinable
    // thread to end, if it's running; in fact it uses variables of this
    // instance and posts events to *this event handler
    if (GetThread() &&      // DoStartALongTask() may have not been called
        GetThread()->IsRunning())
    {
    	mpEngineInterface->StopEngine();
        GetThread()->Kill();
    }
    Destroy();
}

void slach_gui::BottomPanel::OnThreadUpdate(wxThreadEvent& evt)
{

}

wxDEFINE_EVENT(myEVT_THREAD_UPDATE, wxThreadEvent);
wxBEGIN_EVENT_TABLE(slach_gui::BottomPanel, wxPanel)
    EVT_THREAD(myEVT_THREAD_UPDATE, slach_gui::BottomPanel::OnThreadUpdate)
    EVT_CLOSE(slach_gui::BottomPanel::OnClose)
    EVT_SIZE(slach_gui::BottomPanel::OnSize)
    EVT_BUTTON(1, slach_gui::BottomPanel::StartEngine)
wxEND_EVENT_TABLE()
