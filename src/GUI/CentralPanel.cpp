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
      mpSizerForArrows ( new wxBoxSizer(wxHORIZONTAL) ),
      mpMoveListSizer ( new wxFlexGridSizer(3) ), //3 columns for move list sizer
      mpPrincipalSizer (new wxBoxSizer(wxHORIZONTAL) ),
      mpRightSideSizer ( new wxBoxSizer(wxVERTICAL) ),
      mpLeftOfChessBoard ( new wxPanel(this, ID_LEFT_OF_BOARD) ),
      mpChessBoardPanel( new ChessBoardPanel(this, ID_ACTUAL_BOARD) ),
      mpRightOfChessBoard( new wxPanel(this, ID_RIGHT_OF_BOARD) ),
      mpParent(parent),
      mWhitePlayerName(wxT("white player")),
      mBlackPlayerName(wxT("black player")),
      mGameIsLoaded(false),
      mIdOfPanelWithLastMove(INT_MAX)
{
    mpChessBoardPanel->SetAsMainBoard(true);
    mpChessBoard = mpChessBoardPanel->GetChessBoard();

    //Arrange the panels
    mpPrincipalSizer->Add(mpLeftOfChessBoard, 1, wxEXPAND | wxALL);
    mpPrincipalSizer->Add(mpChessBoardPanel, 6, wxEXPAND | wxALL);
    mpPrincipalSizer->Add(mpRightOfChessBoard, 2, wxEXPAND | wxALL);
    this->SetSizer(mpPrincipalSizer, false);

    //divide the section on the RHS of the board
    mpGameInfoBox = new wxTextCtrl(mpRightOfChessBoard, ID_OF_GAME_INFO_BOX, wxT(""), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE | wxTE_MULTILINE);
    mpSpaceForMoveList = new wxScrolledWindow(mpRightOfChessBoard, ID_OF_MOVE_LIST_SPACE);//, wxDefaultPosition, wxDefaultSize , wxVSCROLL);

	mpSpaceForMoveList->SetBackgroundColour(*wxWHITE);

    mpRightSideSizer->Add(mpGameInfoBox, 1, wxEXPAND);
    mpRightSideSizer->Add(mpSpaceForMoveList, 7, wxALL|wxGROW);
    mpRightOfChessBoard->SetSizer(mpRightSideSizer, true);

    mpMoveListSizer->AddGrowableCol(0,1);
    mpMoveListSizer->AddGrowableCol(1,3);
    mpMoveListSizer->AddGrowableCol(2,3);
    mpSpaceForMoveList->SetSizer(mpMoveListSizer);

    //Bind the button and paint  events for the left side of the board
    mpLeftOfChessBoard->Bind(wxEVT_PAINT, &CentralPanel::PaintOnSidesOfBoard, this);//with this-> instead of mpLeftOfChessBoard it does not work
    mpRightOfChessBoard->Bind(wxEVT_SIZE, &CentralPanel::OnSize, this);

    wxButton* pgn_button  = new wxButton(mpLeftOfChessBoard, 1, wxT("Pgn..."),wxDefaultPosition, wxDefaultSize);
    pgn_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CentralPanel::LoadPgnFile, this);

    wxButton* flip_view_button  = new wxButton(mpLeftOfChessBoard, 2, wxT("flip..."),wxPoint(0,55), wxDefaultSize);
    flip_view_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CentralPanel::FlipView, this);

    wxButton* fen_button  = new wxButton(mpLeftOfChessBoard, 3, wxT("Fen..."),wxPoint(0,95), wxDefaultSize);
    fen_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CentralPanel::LoadFen, this);

    this->Bind(wxEVT_CHAR_HOOK, &CentralPanel::ArrowKeyMovement, this);//char hook needed for it to work

    mTextAttributesPlayerNames = wxTextAttr(Colours::Instance()->mPlayerName,
    										wxNullColour,
    										wxFont(wxFontInfo(14).FaceName("Helvetica")),
    										wxTEXT_ALIGNMENT_CENTRE);
    mTextAttributesPlayerNames.SetFlags(wxTEXT_ATTR_TEXT_COLOUR);
    mTextAttributesPlayerNames.SetFlags(wxTEXT_ATTR_FONT);
    mTextAttributesPlayerNames.SetFlags(wxTEXT_ATTR_ALIGNMENT);
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

void slach_gui::CentralPanel::FlipView (wxCommandEvent& WXUNUSED(event))
{
    mpChessBoardPanel->DoFlipView();
    mpChessBoardPanel->Refresh();
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
            wxSize window_size = mpSpaceForMoveList->GetSize();
            int size_of_one_move  = window_size.y/MAX_NUMBER_OF_VISIBLE_MOVES;
            int virtual_size_y = size_of_one_move * (static_cast<int> ( move_list.size()/2 + 2));//plus two for safety

            mpSpaceForMoveList->SetVirtualSize(window_size.x, virtual_size_y);
            unsigned number_of_panels_to_add = move_list.size() + static_cast<unsigned> (std::div(move_list.size(),2).quot + std::div(move_list.size(),2).rem);
            for (unsigned i = 0; i < mMoveListPanels.size(); ++i)
            {
                mMoveListPanels[i]->Destroy();
            }
            mMoveListPanels.clear();
            unsigned move_index = 0;
            for (unsigned i = 0; i < number_of_panels_to_add; ++i)
            {
                mMoveListPanels.push_back( new wxTextCtrl( mpSpaceForMoveList, /*ID*/ OFFSET_OF_MOVE_LIST_ID + (int) i,
                                               wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTRE | wxBORDER_NONE) );
                mMoveListPanels[i]->SetMinSize(wxSize(0,size_of_one_move));
                mpMoveListSizer->Add(mMoveListPanels[i], 0, wxEXPAND | wxALL);
                mMoveListPanels[i]->SetBackgroundColour(*wxWHITE);
                if (i%3 == 0)
                {
                    int move_number  = (int) i/3 + 1;
                    wxString move_number_string = wxString::Format(wxT("%i"),move_number);
                    mMoveListPanels[i]->WriteText(move_number_string);
                }
                else
                {
                    if (move_index < move_list.size())
                    {
                        wxString san_move(move_list_san[move_index]);
                        mMoveListPanels[i]->WriteText(san_move);
                        //Bind to the event both the text box and the panel, so the user can click anywhere
                        mMoveListPanels[i]->Bind(wxEVT_LEFT_DOWN, &CentralPanel::OnClickOnMoveList, this);
                        mMoveListPanels[i]->Bind(wxEVT_ENTER_WINDOW, &CentralPanel::OnMouseEnteringSingleMoveArea, this);
                        mMoveListPanels[i]->Bind(wxEVT_LEAVE_WINDOW, &CentralPanel::OnMouseLeavingSingleMoveArea, this);
                        move_index++;
                        //store the index of the panel with the move. At the end of the loop, this wil be the last...
                        mIdOfPanelWithLastMove = mMoveListPanels[i]->GetId();
                    }
                }
            }
            //push back the result
            //if the last move was black's...shift by one panel
            if (std::div(number_of_panels_to_add,3).rem == 0)
            {
                mMoveListPanels.push_back( new wxTextCtrl( mpSpaceForMoveList, /*ID*/ ID_OF_GAME_RESULT,
                                               wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTRE | wxBORDER_NONE) );
                mMoveListPanels.back()->SetMinSize(wxSize(0,size_of_one_move));
                mpMoveListSizer->Add(mMoveListPanels.back(), 0, wxEXPAND | wxALL);
            }

            mMoveListPanels.push_back( new wxTextCtrl( mpSpaceForMoveList, /*ID*/ ID_OF_GAME_RESULT+1,
                                           wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTRE | wxBORDER_NONE) );
            mMoveListPanels.back()->SetBackgroundColour(*wxLIGHT_GREY);
            mMoveListPanels.back()->SetMinSize(wxSize(0,size_of_one_move));
            mpMoveListSizer->Add(mMoveListPanels.back(), 0, wxEXPAND | wxALL);
            wxString result(mpChessBoard->GetGame()->GetGameResult() );
            mMoveListPanels.back()->WriteText(result);

            mpSpaceForMoveList->Layout();
            //mpSpaceForMoveList->SetScrollbar(wxVERTICAL, 0, 8*window_size.y,500*(virtual_size_y+window_size.y) ); not needed
            mpSpaceForMoveList->SetScrollRate(0, 5);
            mpMoveListSizer->Layout();//force to layout, otherwise it is only done on resize...
            mGameIsLoaded = true;
        }
        mpChessBoard->ResetToMoveNumber(1,slach::WHITE);//otherwise, on an immediate resize, it will skip to the last move
        mpChessBoardPanel->DoGoBackToBeginning();//make sure all goes to beginning when loading a game
    }
}


void slach_gui::CentralPanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    //wxSize box_size = mpTopPlayerBox->GetClientSize();
    //mTextAttributesPlayerNames.SetFontPixelSize((int) box_size.y - (int)box_size.y/10);

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
void slach_gui::CentralPanel::OnClickOnMoveList(wxMouseEvent& event)
{
    int index_in_vector = ((wxTextCtrl*) event.GetEventObject())->GetId() - OFFSET_OF_MOVE_LIST_ID;
    unsigned move_index = index_in_vector - std::div(index_in_vector,3).quot - 1;
    std::string fen_to_set;
    if (move_index >= (mpChessBoard->GetGame()->GetFenList().size() - 1))
    {
        fen_to_set = mpChessBoard->GetGame()->GetFenList()[move_index];
    }
    else
    {
        fen_to_set = mpChessBoard->GetGame()->GetFenList()[move_index+1];
    }
    mpChessBoardPanel->DrawAndSetFenPositionOnBoard(fen_to_set);
    HighlightMoveListPanelWithThisID(((wxTextCtrl*) event.GetEventObject())->GetId());
}

void slach_gui::CentralPanel::HighlightMoveListPanelWithThisID(int ID)
{
    for (unsigned i =0; i < mMoveListPanels.size(); ++i)
    {
        mMoveListPanels[i]->SetBackgroundColour(wxT("white"));
        if ( (int) i == ( ID -  OFFSET_OF_MOVE_LIST_ID) )
        {
            mMoveListPanels[i]->SetBackgroundColour(*wxYELLOW);
        }
    }
    if (mGameIsLoaded == true)
    {
        mMoveListPanels.back()->SetBackgroundColour(*wxLIGHT_GREY);
    }

}
void slach_gui::CentralPanel::OnMouseEnteringSingleMoveArea(wxMouseEvent& event)
{
    int generating_index = ((wxTextCtrl*) event.GetEventObject())->GetId() - OFFSET_OF_MOVE_LIST_ID;
    if (mMoveListPanels[generating_index]->GetBackgroundColour() != *wxYELLOW)
    {
        mMoveListPanels[generating_index]->SetBackgroundColour(*wxLIGHT_GREY);
    }
}

void slach_gui::CentralPanel::OnMouseLeavingSingleMoveArea(wxMouseEvent& event)
{
    int generating_index = ((wxTextCtrl*) event.GetEventObject())->GetId() - OFFSET_OF_MOVE_LIST_ID;
    if (mMoveListPanels[generating_index]->GetBackgroundColour() != *wxYELLOW)
    {
        mMoveListPanels[generating_index]->SetBackgroundColour(*wxWHITE);
    }
}

int slach_gui::CentralPanel::GetCurrentlyHighlightedMove()
{
    int index_of_currently_highlighted_move = 0;
    for (unsigned i = 0; i  < mMoveListPanels.size(); ++i )
    {
        if (mMoveListPanels[i]->GetBackgroundColour() == (*wxYELLOW))
        {
            return (int) i;
        }
    }
    return index_of_currently_highlighted_move;
}

void slach_gui::CentralPanel::HighlightNextMove()
{
    int highlighted_move = GetCurrentlyHighlightedMove();
    //skip the move numbers...
    if ( (std::div(highlighted_move,3).rem == 2))
    {
        highlighted_move++;
    }
    //prevent de-highlighting of last move
    if ((unsigned) highlighted_move < mMoveListPanels.size())
    {
        if (mMoveListPanels[highlighted_move]->GetId() >= mIdOfPanelWithLastMove)
        {
            HighlightMoveListPanelWithThisID(mIdOfPanelWithLastMove);
        }
        else
        {
            HighlightMoveListPanelWithThisID(highlighted_move +   OFFSET_OF_MOVE_LIST_ID + 1);
        }
    }
}

void slach_gui::CentralPanel::HighlightSeveralMovesAhead()
{
    int index_of_currently_highlighted_move = GetCurrentlyHighlightedMove();
    //skip the move numbers...
    if (std::div(index_of_currently_highlighted_move,3).rem == 2)
    {
        index_of_currently_highlighted_move++;
    }

    if ((unsigned) index_of_currently_highlighted_move < mMoveListPanels.size())
    {
        //prevent de-highlighting of last move
        if ( mMoveListPanels[index_of_currently_highlighted_move]->GetId() >= (mIdOfPanelWithLastMove - 8))
        {
            HighlightMoveListPanelWithThisID(mIdOfPanelWithLastMove);
        }
        else
        {
            HighlightMoveListPanelWithThisID(index_of_currently_highlighted_move +   OFFSET_OF_MOVE_LIST_ID + 7);
        }
    }
}

void slach_gui::CentralPanel::HighlightLastMove()
{
	HighlightMoveListPanelWithThisID(mIdOfPanelWithLastMove);
}

void slach_gui::CentralPanel::HighlightPreviousMove()
{
    int index_of_currently_highlighted_move = GetCurrentlyHighlightedMove();
    //skip the move numbers...
    if (std::div(index_of_currently_highlighted_move,3).rem == 1)
    {
        index_of_currently_highlighted_move--;
    }
    HighlightMoveListPanelWithThisID(index_of_currently_highlighted_move +   OFFSET_OF_MOVE_LIST_ID - 1);
}

void slach_gui::CentralPanel::HighlightSeveralMovesBack()
{
    int index_of_currently_highlighted_move = GetCurrentlyHighlightedMove();
    //skip the move numbers...
    if (std::div(index_of_currently_highlighted_move,3).rem == 1)
    {
        index_of_currently_highlighted_move--;
    }
    HighlightMoveListPanelWithThisID(index_of_currently_highlighted_move +   OFFSET_OF_MOVE_LIST_ID - 7);
}

void slach_gui::CentralPanel::HighlightBeforeFirstMove()
{
    HighlightMoveListPanelWithThisID(-1);//do not colour anything
}


std::vector<wxTextCtrl* > slach_gui::CentralPanel::GetMoveListPanels()
{
    return  mMoveListPanels;
}

void slach_gui::CentralPanel::PaintOnSidesOfBoard(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(mpLeftOfChessBoard);
    DoPaintVerticalGradient(dc, mpLeftOfChessBoard);

    wxPaintDC dc1(mpChessBoardPanel);
    DoPaintVerticalGradient(dc1,mpChessBoardPanel);

    wxPaintDC dc2(mpRightOfChessBoard);
    DoPaintVerticalGradient(dc2, mpRightOfChessBoard);
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


