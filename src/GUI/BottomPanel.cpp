#include <ctime>
#include <cfloat>
#include "BottomPanel.hpp"

slach_gui::BottomPanel::BottomPanel(wxFrame* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,-1, pos,size),
      mpEngineInterface  (std::make_shared<slach::UCIEngineInterface>() ),
      mNumberOfEngineLinesShown(1),
      mpPosition ( new slach::Position() ),
      mpStartEngineButton ( new wxButton(this, 1, wxT("Start Engine"),wxDefaultPosition, wxDefaultSize) ),
      mpStopEngineButton ( new wxButton(this, 2, wxT("Stop Engine"),wxDefaultPosition, wxDefaultSize) ),
      mpEngineTextBox ( new wxRichTextCtrl(this, wxID_ANY, wxT("Engine output"), wxDefaultPosition, wxSize(150,60), wxTE_MULTILINE | wxBORDER_SIMPLE | wxHSCROLL) ),
      mTimer(this, 1),
      mEngineIsRunning(false),
      mPrettyLines({}),
      mScore(0.0),
      mDepth(0),
      mBestMove("")
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


    mNumberOfEngineLinesShown = 3;
    mpEngineInterface->SetNumberOfLinesToBeShown(mNumberOfEngineLinesShown);

    this->Bind(wxEVT_CLOSE_WINDOW, &BottomPanel::OnClose, this);

    mpStartEngineButton->Bind(wxEVT_BUTTON, &BottomPanel::StartEngine, this);
    mpStopEngineButton->Bind(wxEVT_BUTTON, &BottomPanel::StopEngine, this);
    this->Connect(mTimer.GetId(),wxEVT_TIMER,wxTimerEventHandler( BottomPanel::UpdateEngineOutput ), NULL, this );
    mTimer.Start(1500);//every 1500 ms
}

slach_gui::BottomPanel::~BottomPanel()
{
}

void slach_gui::BottomPanel::SetPositionToAnalyse(slach::Position* pPosition)
{
    assert(pPosition != nullptr);
    mpPosition = pPosition;
    mpEngineInterface->SetFenPosition(mpPosition->GetPositionAsFen());
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
	mpEngineInterface->StopAnalysis();
	mEngineIsRunning = false;
}

void slach_gui::BottomPanel::DoStartEngine()
{
	mEngineIsRunning = true;
	assert(mpPosition!=nullptr);
	mpEngineInterface->StartAnalysis(mpPosition);
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
		//obtain info from the interface
        mpEngineInterface->GetEngineInfo(mPrettyLines, mScore, mDepth, mBestMove);

	    mpEngineTextBox->Clear();//clear the box
		//wxStreamToTextRedirector redirect(mpEngineTextBox); //not working
        mpEngineTextBox->BeginTextColour(Colours::Instance()->mBottomPanelBackground);
        mpEngineTextBox->BeginBold();
        mpEngineTextBox->BeginFontSize(18);
        mpEngineTextBox->ChangeValue("");
        mpEngineTextBox->BeginAlignment(wxTEXT_ALIGNMENT_LEFT);
        mpEngineTextBox->WriteText( wxT("Best Move: "));
        mpEngineTextBox->WriteText( mBestMove );
        mpEngineTextBox->WriteText( wxT(" ("));
        if (mScore < DBL_MAX) mpEngineTextBox->WriteText( wxString::Format(wxT("%.2f"), mScore) );
        mpEngineTextBox->WriteText( wxT(") Depth: "));
        if (mDepth < INT_MAX) mpEngineTextBox->WriteText( wxString::Format(wxT("%d"), mDepth) );

        mpEngineTextBox->LineBreak();
        mpEngineTextBox->EndFontSize();
        mpEngineTextBox->EndBold();
        mpEngineTextBox->EndTextColour();
        mpEngineTextBox->BeginTextColour(Colours::Instance()->mEngineText);
        mpEngineTextBox->BeginFontSize(13);
	    for (unsigned pv = 0; pv < mPrettyLines.size(); pv++)
	    {
            mpEngineTextBox->WriteText( mPrettyLines[pv] );
            mpEngineTextBox->LineBreak();
	    }
        mpEngineTextBox->EndAlignment();
        mpEngineTextBox->EndFontSize();
        mpEngineTextBox->EndTextColour();
	}
	evt.Skip();
}
