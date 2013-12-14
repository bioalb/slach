#include <ctime>
#include "BottomPanel.hpp"

slach_gui::BottomPanel::BottomPanel(wxFrame* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,-1, pos,size),
      mpEngineInterface  (new slach::EngineInterface() ),
      mNumberOfEngineLinesShown(1),
      mpPosition ( new slach::Position() ),
      mpStartEngineButton ( new wxButton(this, 1, wxT("Start Engine"),wxDefaultPosition, wxDefaultSize) ),
      mpStopEngineButton ( new wxButton(this, 2, wxT("Stop Engine"),wxDefaultPosition, wxDefaultSize) ),
      mpEngineTextBox ( new wxTextCtrl(this, wxID_ANY, wxT("Engine output"), wxDefaultPosition, wxSize(150,60), wxTE_MULTILINE | wxBORDER_SIMPLE | wxHSCROLL) ),
      mpScoreTextBox ( new wxRichTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxBORDER_NONE) ),
      mTimer(this, 1),
      mEngineIsRunning(false)
{


    this->SetBackgroundColour(Colours::Instance()->mBottomPanelBackground);
    mpEngineTextBox->SetEditable(false);
    mpScoreTextBox->SetEditable(false);
    mpScoreTextBox->SetBackgroundColour(Colours::Instance()->mScoreBoxBackground);
    wxFont font(12, wxROMAN, wxNORMAL, wxNORMAL);
    mpScoreTextBox->SetFont(font);

    wxBoxSizer *button_sizer = new wxBoxSizer( wxHORIZONTAL );
    button_sizer->Add(mpStartEngineButton,
        wxSizerFlags(0).Align(wxALIGN_LEFT).Border(wxALL, 10));

    button_sizer->Add(mpStopEngineButton,
        wxSizerFlags(0).Align(wxALIGN_LEFT).Border(wxALL, 10));

    wxBoxSizer* right_side_sizer = new wxBoxSizer( wxVERTICAL );
    right_side_sizer->Add(mpEngineTextBox,
    wxSizerFlags(7).Align(wxALIGN_CENTER).Expand().Border(wxALL, 10));
    right_side_sizer->Add(button_sizer, wxSizerFlags(1).Left() );

    wxBoxSizer *topsizer = new wxBoxSizer( wxHORIZONTAL );
    topsizer->Add(right_side_sizer,
    wxSizerFlags(6).Align(wxALIGN_CENTER).Expand().Border(wxALL, 10));
    topsizer->Add(mpScoreTextBox, 
    wxSizerFlags(1).Align(wxALIGN_CENTER).Expand());


    this->SetSizer(topsizer, false);
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
	    for (unsigned pv = mNumberOfEngineLinesShown; pv > 0 ; pv--)
	    {
            wxColour backgroundcolour(255 - 20*pv, 255 -  20*pv, 255 - 20*pv);
            mpEngineTextBox->SetDefaultStyle(wxTextAttr(*wxBLACK, backgroundcolour));
	        (*mpEngineTextBox)<<mpEngineInterface->GetLatestEngineOutput()[pv-1];
	    }
		mpScoreTextBox->BeginTextColour(Colours::Instance()->mEngineText);
		mpScoreTextBox->ChangeValue("");
		mpScoreTextBox->BeginAlignment(wxTEXT_ALIGNMENT_LEFT);
		mpScoreTextBox->WriteText( wxT("Depth = "));
		mpScoreTextBox->WriteText( wxString::Format(wxT("%d"), mpEngineInterface->GetLatestBestScoreAndDepth().second) );
        mpScoreTextBox->LineBreak();

		mpScoreTextBox->BeginBold();
		mpScoreTextBox->WriteText( wxT("Score "));
        mpScoreTextBox->LineBreak();
		mpScoreTextBox->BeginFontSize(18);
		mpScoreTextBox->WriteText( wxString::Format(wxT("%.2f"), mpEngineInterface->GetLatestBestScoreAndDepth().first) );
		mpScoreTextBox->EndFontSize();
		mpScoreTextBox->EndAlignment();
        mpScoreTextBox->EndBold();
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
