#include <algorithm>
#include <iostream>
#include <cassert>
#include <wx/mstream.h>
#include <wx/wfstream.h>
#include <wx/filedlg.h>
#include <wx/txtstrm.h>
#include "SlachTypes.hpp"
#include "HelperGlobalFunctions.hpp"
#include "CentralPanel.hpp"
#include "MainFrame.hpp"


slach_gui::CentralPanel::CentralPanel(wxFrame* parent, wxWindowID WXUNUSED(id), const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size),
      mpPrincipalSizer (new wxBoxSizer(wxHORIZONTAL) ),
      mpRightSideSizer ( new wxBoxSizer(wxVERTICAL) ),
      mpChessBoardPanel( new ChessBoardPanel(this, ID_ACTUAL_BOARD) ),
      mpRightOfChessBoard( new wxPanel(this, ID_RIGHT_OF_BOARD) ),
      mpSpaceForMoveList ( new wxRichTextCtrl(mpRightOfChessBoard, ID_OF_MOVE_LIST_SPACE) ),
      mMoveListRanges ({}),
      mIndexOfHighlightedMove(-1),
      mpParent(parent),
      mWhitePlayerName(wxT("white player")),
      mBlackPlayerName(wxT("black player")),
      mGameIsLoaded(false),
      mIdOfPanelWithLastMove(INT_MAX)
{
    mpChessBoardPanel->SetAsMainBoard(true);
    mpChessBoard = mpChessBoardPanel->GetChessBoard();

    //Arrange the panels
    mpPrincipalSizer->Add(mpChessBoardPanel, 4, wxEXPAND | wxALL);
    mpPrincipalSizer->Add(mpRightOfChessBoard, 1, wxEXPAND | wxALL);
    this->SetSizer(mpPrincipalSizer, false);

    //divide the section on the RHS of the board
    mpGameInfoBox = new wxTextCtrl(mpRightOfChessBoard, ID_OF_GAME_INFO_BOX, wxT(""), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE | wxTE_MULTILINE);
    mpButtonsBelowMoveList =  new wxPanel(mpRightOfChessBoard, ID_RIGHT_OF_BOARD_BUTTONS);
	mpSpaceForMoveList->SetBackgroundColour(*wxWHITE);

    mpRightSideSizer->Add(mpGameInfoBox, 1, wxEXPAND);
    mpRightSideSizer->Add(mpSpaceForMoveList, 7, wxALL|wxGROW);
    mpRightSideSizer->Add(mpButtonsBelowMoveList,1,wxEXPAND);
    mpRightOfChessBoard->SetSizer(mpRightSideSizer, true);

    //Bind the size event
    mpRightOfChessBoard->Bind(wxEVT_SIZE, &CentralPanel::OnSize, this);
    //bind teh functionalities in the move list area
    mpSpaceForMoveList->Bind(wxEVT_RICHTEXT_LEFT_CLICK, &CentralPanel::OnClickOnMoveList, this);

    wxButton* pgn_button  = new wxButton(mpButtonsBelowMoveList, 1, wxT("Pgn..."),wxDefaultPosition, wxDefaultSize);
    pgn_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CentralPanel::LoadPgnFile, this);
    wxButton* fen_button  = new wxButton(mpButtonsBelowMoveList, 3, wxT("Fen..."),wxDefaultPosition, wxDefaultSize);
    fen_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CentralPanel::LoadFen, this);
    wxBoxSizer* sizer_for_buttons = new wxBoxSizer(wxHORIZONTAL);
    sizer_for_buttons->Add(pgn_button, 1, wxEXPAND);
    sizer_for_buttons->Add(fen_button, 1, wxEXPAND);
    mpButtonsBelowMoveList->SetSizer(sizer_for_buttons);


    this->Bind(wxEVT_CHAR_HOOK, &CentralPanel::ArrowKeyMovement, this);//char hook needed for it to work

    mTextAttributesPlayerNames = wxTextAttr(Colours::Instance()->mPlayerName,
    										wxNullColour,
    										wxFont(wxFontInfo(14).FaceName("Helvetica")),
    										wxTEXT_ALIGNMENT_CENTRE);
    mTextAttributesMoveList = wxTextAttr(Colours::Instance()->mPlayerName,
                                         wxNullColour,
                                         wxFont(wxFontInfo(14).FaceName("Helvetica")));
    mTextAttributesMoveListHighlighted = wxTextAttr(Colours::Instance()->mPlayerName,
                                          Colours::Instance()->mHighlightedMove,
                                          wxFont(wxFontInfo(14).FaceName("Helvetica")));

    mpSpaceForMoveList->SetEditable(false);
    mpSpaceForMoveList->SetDefaultStyle(mTextAttributesMoveList);
    mpSpaceForMoveList->SetTextCursor(*wxSTANDARD_CURSOR);
}

slach_gui::CentralPanel::~CentralPanel()
{

}


void slach_gui::CentralPanel::LoadFen (wxCommandEvent& WXUNUSED(event))
{
    wxTextEntryDialog* fen_dialogue =  new wxTextEntryDialog(this, wxT("Enter a position in FEN notation"), wxT("Fen input"),  wxEmptyString);
    if ( fen_dialogue->ShowModal() == wxID_OK )
    {
        mpChessBoardPanel->DrawAndSetFenPositionOnBoard(fen_dialogue->GetValue().ToStdString());
    }
    else
    {
        //else: dialog was cancelled or some another button pressed
        fen_dialogue->Destroy();
    }

}

void slach_gui::CentralPanel::LoadPgnFile(wxCommandEvent& WXUNUSED(event))
{
    wxFileDialog* openFileDialog = new wxFileDialog(this, "Choose a file to open", wxEmptyString, wxEmptyString,
            "PGN files (*.pgn)|*.pgn", wxFD_OPEN);

    if (openFileDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
    {
        wxFile input_file(openFileDialog->GetPath());
        if (!input_file.IsOpened())
        {
            wxLogError("Cannot open file '%s'.", openFileDialog->GetPath());
            return;
        }
        wxString game_string;
        input_file.ReadAll(&game_string);

        slach::PgnValidity valid = mpChessBoard->LoadGameFromPgn(game_string.ToStdString());
        std::string name_of_white_player = mpChessBoard->GetGame()->GetNameOfWhitePlayer();
        std::string name_of_black_player = mpChessBoard->GetGame()->GetNameOfBlackPlayer();

        if (valid == slach::VALID_PGN)
        {
            mMoveListRanges.clear();
            mpSpaceForMoveList->Clear();
            mIndexOfHighlightedMove = -1;
            wxString name_of_white_player_wx(name_of_white_player);
            wxString name_of_black_player_wx(name_of_black_player);
            mWhitePlayerName = name_of_white_player_wx;
            mBlackPlayerName = name_of_black_player_wx;
            mpGameInfoBox->AppendText(wxT("White: "));
            mpGameInfoBox->AppendText(mWhitePlayerName);
            mpGameInfoBox->AppendText(wxT("\nBlack: "));
            mpGameInfoBox->AppendText(mBlackPlayerName);

            std::vector<slach::Move> move_list = mpChessBoard->GetGame()->GetMoveList();
            std::vector<std::string > move_list_san = mpChessBoard->GetGame()->GetMoveListAlgebraicFormat();

            unsigned move_index = 0;
            unsigned  i = 0;
            while (move_index < move_list_san.size())
            {
                if (i%3 == 0)
                {
                    int move_number  = (int) i/3 + 1;
                    wxString move_number_string = wxString::Format(wxT("%i"),move_number);
                    mpSpaceForMoveList->AppendText(move_number_string);
                    mpSpaceForMoveList->AppendText(wxT(". "));
                }
                else
                {
                    wxString san_move(move_list_san[move_index]);
                    long before = mpSpaceForMoveList->GetInsertionPoint();
                    mpSpaceForMoveList->AppendText(san_move);
                    mMoveListRanges.push_back(wxRichTextRange (before, mpSpaceForMoveList->GetInsertionPoint()));
                    mpSpaceForMoveList->AppendText(wxT(" "));

                    move_index++;
                }
                i++;
            }
            //push back the result
            wxString result(mpChessBoard->GetGame()->GetGameResult() );
            mpSpaceForMoveList->AppendText(result);

            mGameIsLoaded = true;
        }
        mpChessBoard->ResetToMoveNumber(1,slach::WHITE);//otherwise, on an immediate resize, it will skip to the last move
        mpChessBoardPanel->DoGoBackToBeginning();//make sure all goes to beginning when loading a game
    }
}


void slach_gui::CentralPanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    //skip the event. Needed as per wxWdigets documentation
    event.Skip();
}

void slach_gui::CentralPanel::ArrowKeyMovement(wxKeyEvent& event)
{
    if (event.GetKeyCode() == WXK_RIGHT) mpChessBoardPanel->DoAdvanceOneMove();
    if (event.GetKeyCode() == WXK_DOWN) mpChessBoardPanel->DoAdvanceOneMove();
    if (event.GetKeyCode() == WXK_UP) mpChessBoardPanel->DoGoBackOneMove();
    if (event.GetKeyCode() == WXK_LEFT) mpChessBoardPanel->DoGoBackOneMove();
    if (event.GetKeyCode() == WXK_PAGEUP) mpChessBoardPanel->DoGoBackSeveralMoves();
    if (event.GetKeyCode() == WXK_PAGEDOWN) mpChessBoardPanel->DoAdvanceSeveralMoves();
    if (event.GetKeyCode() == WXK_HOME) mpChessBoardPanel->DoGoBackToBeginning();
    if (event.GetKeyCode() == WXK_END) mpChessBoardPanel->DoAdvanceUntilEnd();

    event.Skip();
}
void slach_gui::CentralPanel::OnClickOnMoveList(wxRichTextEvent& event)
{
    long click_position = event.GetPosition();
    std::string fen_to_set;
    for (unsigned i = 0; i < mMoveListRanges.size(); ++i)
    {
        if (mMoveListRanges[i].Contains(click_position))
        {
            std::vector<std::string> fen_list = mpChessBoard->GetGame()->GetFenList();
            assert( i <= fen_list.size() );
            fen_to_set = fen_list[i+1];
            //do the highlighting
            HighlightMoveListRange((int) i);
            mIndexOfHighlightedMove = i;//stores index of highlighted move
            break;
        }
    }
    mpChessBoardPanel->DrawAndSetFenPositionOnBoard(fen_to_set);
}

void slach_gui::CentralPanel::HighlightMoveListRange(int ID)
{
    if (ID >= 0 )
    {
        unsigned to_be_highlighted = UINT_MAX;
        if (ID >= (int) mMoveListRanges.size() )
        {
            to_be_highlighted = mMoveListRanges.size() - 1;
        }
        else
        {
            to_be_highlighted = (unsigned) ID;
        }
        mpSpaceForMoveList->SetStyleEx(mMoveListRanges[mIndexOfHighlightedMove], mTextAttributesMoveList,wxRICHTEXT_SETSTYLE_RESET);
        mpSpaceForMoveList->SetStyle(mMoveListRanges[to_be_highlighted], mTextAttributesMoveListHighlighted);
        mIndexOfHighlightedMove = (int) to_be_highlighted;
    }
    else
    {
        mpSpaceForMoveList->SetStyleEx(mMoveListRanges[mIndexOfHighlightedMove], mTextAttributesMoveList,wxRICHTEXT_SETSTYLE_RESET);
        mpSpaceForMoveList->SetStyle(mMoveListRanges[mIndexOfHighlightedMove], mTextAttributesMoveList);
        mIndexOfHighlightedMove = -1;
    }
}

void slach_gui::CentralPanel::HighlightNextMove()
{
    int next_move = mIndexOfHighlightedMove + 1;
    HighlightMoveListRange (next_move);
}

void slach_gui::CentralPanel::HighlightSeveralMovesAhead()
{
    int next_move = mIndexOfHighlightedMove + 5;
    HighlightMoveListRange (next_move);
}

void slach_gui::CentralPanel::HighlightLastMove()
{
    HighlightMoveListRange (mMoveListRanges.size() - 1);
}

void slach_gui::CentralPanel::HighlightPreviousMove()
{
    int prev_move = mIndexOfHighlightedMove - 1;
    HighlightMoveListRange (prev_move);
}

void slach_gui::CentralPanel::HighlightSeveralMovesBack()
{
    int prev_move = mIndexOfHighlightedMove - 5;
    HighlightMoveListRange (prev_move);
}

void slach_gui::CentralPanel::HighlightBeforeFirstMove()
{
    HighlightMoveListRange(-1);//do not colour anything
}


void slach_gui::CentralPanel::DoPaintImageOnPanel(wxPaintDC& dc, wxPanel* pPanel, wxImage& Image)
{
    int width = pPanel->GetClientSize().GetWidth();
    int height = pPanel->GetClientSize().GetHeight();
    Image.Rescale(width, height);
    //now really draw the rendered image;
    dc.DrawBitmap(Image, 0, 0, true );
}

void slach_gui::CentralPanel::DoPaintVerticalGradient(wxPaintDC& dc, wxPanel* pPanel)
{
    wxRect clientRect = pPanel->GetClientRect();
    wxRect gradientRect = clientRect;
    gradientRect.SetHeight(gradientRect.GetHeight());
    dc.GradientFillLinear(gradientRect,
    wxColour(32,107,129), wxColour(235,241,246), wxSOUTH);
}


