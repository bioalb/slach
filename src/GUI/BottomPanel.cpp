#include <ctime>
#include <cfloat>
#include "BottomPanel.hpp"

slach_gui::BottomPanel::BottomPanel(wxFrame* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,-1, pos,size),
      mpEngineInterface  (new slach::EngineInterface() ),
      mNumberOfEngineLinesShown(1),
      mpPosition ( new slach::Position() ),
      mpStartEngineButton ( new wxButton(this, 1, wxT("Start Engine"),wxDefaultPosition, wxDefaultSize) ),
      mpStopEngineButton ( new wxButton(this, 2, wxT("Stop Engine"),wxDefaultPosition, wxDefaultSize) ),
      mpEngineTextBox ( new wxRichTextCtrl(this, wxID_ANY, wxT("Engine output"), wxDefaultPosition, wxSize(150,60), wxTE_MULTILINE | wxBORDER_SIMPLE | wxHSCROLL) ),
      mTimer(this, 1),
      mEngineIsRunning(false)
{
    this->SetBackgroundColour(Colours::Instance()->mBottomPanelBackground);
    mpEngineTextBox->SetEditable(false);
    wxFont font(12, wxROMAN, wxNORMAL, wxNORMAL);

    wxBoxSizer *right_side_sizer = new wxBoxSizer( wxVERTICAL );
    right_side_sizer->Add(mpStartEngineButton,1, wxEXPAND);
    right_side_sizer->Add(mpStopEngineButton,1, wxEXPAND);

    wxBoxSizer* main_sizer = new wxBoxSizer( wxHORIZONTAL );
    main_sizer->Add(mpEngineTextBox, 6, wxEXPAND);
    main_sizer->Add(right_side_sizer, 1, wxEXPAND );

    this->SetSizer(main_sizer, false);
    mTimer.Start(1500);//every 1500 ms

    mpEngineInterface->LaunchEngine();
    mNumberOfEngineLinesShown = 3;
    mpEngineInterface->SetNumberOfLinesToBeShown(mNumberOfEngineLinesShown);
}

slach_gui::BottomPanel::~BottomPanel()
{
	mpEngineInterface->QuitEngine();
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
    assert(pPosition != NULL);
    mpPosition = pPosition;
    mpEngineInterface->SetPositionToInternalChessBoard(mpPosition->GetPositionAsFen());
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
	mpEngineInterface->StopEngine();
}

void slach_gui::BottomPanel::DoStartEngine()
{
	mEngineIsRunning = true;
	assert(mpPosition!=NULL);
    mpEngineInterface->StartAnalsyingPosition(mpPosition); //infinite
}

void slach_gui::BottomPanel::OnClose(wxCloseEvent&)
{
	if (mEngineIsRunning == true)
	{
		DoStopEngine();
	}
}

void slach_gui::BottomPanel::UpdateEngineOutput(wxTimerEvent& evt)
{
	if (mEngineIsRunning == true)
	{
	    mpEngineTextBox->Clear();//clear the box
		//wxStreamToTextRedirector redirect(mpEngineTextBox); //not working
        mpEngineTextBox->BeginTextColour(Colours::Instance()->mBottomPanelBackground);
        mpEngineTextBox->BeginBold();
        mpEngineTextBox->BeginFontSize(18);
        mpEngineTextBox->ChangeValue("");
        mpEngineTextBox->BeginAlignment(wxTEXT_ALIGNMENT_LEFT);
        int depth = 0;
        double score = 0;
        std::string best_move = "";
        mpEngineInterface->GetLatestBestScoreAndDepth(score,depth,best_move);
        mpEngineTextBox->WriteText( wxT("Best Move: "));
        mpEngineTextBox->WriteText( best_move );
        mpEngineTextBox->WriteText( wxT("   Best Score: "));
        if (score < DBL_MAX) mpEngineTextBox->WriteText( wxString::Format(wxT("%.2f"), score) );
        mpEngineTextBox->WriteText( wxT("   Depth: "));
        if (depth < INT_MAX) mpEngineTextBox->WriteText( wxString::Format(wxT("%d"), depth) );

        mpEngineTextBox->LineBreak();
        mpEngineTextBox->EndFontSize();
        mpEngineTextBox->EndBold();
        mpEngineTextBox->EndTextColour();
        mpEngineTextBox->BeginTextColour(Colours::Instance()->mEngineText);
        mpEngineTextBox->BeginFontSize(13);
	    for (unsigned pv = mNumberOfEngineLinesShown; pv > 0 ; pv--)
	    {
            mpEngineTextBox->WriteText( mpEngineInterface->GetLatestEngineOutput()[pv-1] );
	    }
        mpEngineTextBox->EndAlignment();
        mpEngineTextBox->EndFontSize();
        mpEngineTextBox->EndTextColour();
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
