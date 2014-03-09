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
    mNumberOfEngineLinesShown = 3;
    mpEngineInterface->SetNumberOfLinesToBeShown(mNumberOfEngineLinesShown);
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
        mpEngineTextBox->BeginTextColour(Colours::Instance()->mEngineText);
        mpEngineTextBox->ChangeValue("");
        mpEngineTextBox->BeginAlignment(wxTEXT_ALIGNMENT_LEFT);
        mpEngineTextBox->WriteText( wxT("Depth = "));
        mpEngineTextBox->WriteText( wxString::Format(wxT("%d"), mpEngineInterface->GetLatestBestScoreAndDepth().second) );

        mpEngineTextBox->BeginBold();
        mpEngineTextBox->BeginFontSize(18);
        mpEngineTextBox->WriteText( wxT("   Score "));
        double score = mpEngineInterface->GetLatestBestScoreAndDepth().first;
        if (score < DBL_MAX)
        {
            mpEngineTextBox->WriteText( wxString::Format(wxT("%.2f"), score) );
        }
        mpEngineTextBox->EndFontSize();
        mpEngineTextBox->EndAlignment();
        mpEngineTextBox->EndBold();
        mpEngineTextBox->EndTextColour();
        mpEngineTextBox->LineBreak();
	    for (unsigned pv = mNumberOfEngineLinesShown; pv > 0 ; pv--)
	    {
            wxColour backgroundcolour(255 - 20*pv, 255 -  20*pv, 255 - 20*pv);
            mpEngineTextBox->SetDefaultStyle(wxTextAttr(*wxBLACK, backgroundcolour));
	        //(*mpEngineTextBox)<<mpEngineInterface->GetLatestEngineOutput()[pv-1];
            mpEngineTextBox->WriteText( mpEngineInterface->GetLatestEngineOutput()[pv-1] );
	    }

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
