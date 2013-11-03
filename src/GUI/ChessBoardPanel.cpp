#include <algorithm>
#include <iostream>
#include <cassert>
#include <wx/mstream.h>
#include <wx/wfstream.h>
#include <wx/filedlg.h>
#include <wx/txtstrm.h>
#include "SlachTypes.hpp"
#include "HelperGlobalFunctions.hpp"
#include "ChessBoardPanel.hpp"
#include "DropTargetPanel.hpp"
#include "MainFrame.hpp"
#include "bitmaps/letters/png/a.png.h"
#include "bitmaps/letters/png/b.png.h"
#include "bitmaps/letters/png/c.png.h"
#include "bitmaps/letters/png/d.png.h"
#include "bitmaps/letters/png/e.png.h"
#include "bitmaps/letters/png/f.png.h"
#include "bitmaps/letters/png/g.png.h"
#include "bitmaps/letters/png/h.png.h"

#include "bitmaps/numbers/png/one.png.h"
#include "bitmaps/numbers/png/two.png.h"
#include "bitmaps/numbers/png/three.png.h"
#include "bitmaps/numbers/png/four.png.h"
#include "bitmaps/numbers/png/five.png.h"
#include "bitmaps/numbers/png/six.png.h"
#include "bitmaps/numbers/png/seven.png.h"
#include "bitmaps/numbers/png/eight.png.h"

#include "bitmaps/pieces/xpm/black_rook.xpm"
#include "bitmaps/pieces/xpm/black_king.xpm"
#include "bitmaps/pieces/xpm/black_queen.xpm"
#include "bitmaps/pieces/xpm/black_bishop.xpm"
#include "bitmaps/pieces/xpm/black_knight.xpm"
#include "bitmaps/pieces/xpm/black_pawn.xpm"
#include "bitmaps/pieces/xpm/white_pawn.xpm"
#include "bitmaps/pieces/xpm/white_knight.xpm"
#include "bitmaps/pieces/xpm/white_bishop.xpm"
#include "bitmaps/pieces/xpm/white_rook.xpm"
#include "bitmaps/pieces/xpm/white_queen.xpm"
#include "bitmaps/pieces/xpm/white_king.xpm"
#include "bitmaps/pieces/xpm/no_piece.xpm"

slach_gui::ChessBoardPanel::ChessBoardPanel(wxFrame* parent, wxWindowID WXUNUSED(id), const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size),
      mPngPieceDirectory("../../src/GUI/bitmaps/pieces/png/"),
      mPngBackgroundDirectory("../../src/GUI/bitmaps/squares/png/"),
      mPngArrowsDirectory("../../src/GUI/bitmaps/arrows/png/"),
      mpChessBoardWithBorders ( new slach::ChessBoardWithBorders() ),
      mpChessBoard(NULL),
      mpBoardGridSizer ( new wxFlexGridSizer(slach::gBoardRowSize+2,slach::gBoardColumnSize+2,0,0) ),
      mpSizerForArrows ( new wxBoxSizer(wxHORIZONTAL) ),
      mpMoveListSizer ( new wxFlexGridSizer(3) ), //3 columns for move list sizer
      mpPrincipalSizer (new wxBoxSizer(wxHORIZONTAL) ),
      mpRightSideSizer ( new wxBoxSizer(wxVERTICAL) ),
      mpLeftOfChessBoard ( new wxPanel(this, ID_LEFT_OF_BOARD) ),
      mpMidPanelOfChessBoard( new wxPanel(this, ID_ACTUAL_BOARD) ),
      mpRightOfChessBoard( new wxPanel(this, ID_RIGHT_OF_BOARD) ),
      mpParent(parent),
      mWhitePlayerName(wxT("white player")),
      mBlackPlayerName(wxT("black player")),
      mDrawPiece(true),
      mSourceIndex(0u)
{

    mSquarePanels.resize(slach::gChessBoardSizeWB);

    //now the grid sizer.
    int square_to_border_prop = 3;//proportion between border and square
    mpBoardGridSizer->AddGrowableCol(0,1);//border
    mpBoardGridSizer->AddGrowableCol(1,square_to_border_prop);
    mpBoardGridSizer->AddGrowableCol(2,square_to_border_prop);
    mpBoardGridSizer->AddGrowableCol(3,square_to_border_prop);
    mpBoardGridSizer->AddGrowableCol(4,square_to_border_prop);
    mpBoardGridSizer->AddGrowableCol(5,square_to_border_prop);
    mpBoardGridSizer->AddGrowableCol(6,square_to_border_prop);
    mpBoardGridSizer->AddGrowableCol(7,square_to_border_prop);
    mpBoardGridSizer->AddGrowableCol(8,square_to_border_prop);
    mpBoardGridSizer->AddGrowableCol(9,1);//border

    mpBoardGridSizer->AddGrowableRow(0,1);//border
    mpBoardGridSizer->AddGrowableRow(1,square_to_border_prop);
    mpBoardGridSizer->AddGrowableRow(2,square_to_border_prop);
    mpBoardGridSizer->AddGrowableRow(3,square_to_border_prop);
    mpBoardGridSizer->AddGrowableRow(4,square_to_border_prop);
    mpBoardGridSizer->AddGrowableRow(5,square_to_border_prop);
    mpBoardGridSizer->AddGrowableRow(6,square_to_border_prop);
    mpBoardGridSizer->AddGrowableRow(7,square_to_border_prop);
    mpBoardGridSizer->AddGrowableRow(8,square_to_border_prop);
    mpBoardGridSizer->AddGrowableRow(9,1);//border

    LoadBoardImages();

    mpChessBoard = mpChessBoardWithBorders->GetPlayableChessBoard();
    mpChessBoard->SetupInitialChessPosition();
    (static_cast<MainFrame*> (mpParent))->UpdateChessPositionForEngine(mpChessBoard->GetCurrentPosition());
    mpAllSquares = mpChessBoardWithBorders->GetSquares();

    assert(mpAllSquares.size() == mSquarePanels.size());
    for (unsigned i = 0; i < mpAllSquares.size(); ++i)
    {
        mSquarePanels[i] = new wxPanel( mpMidPanelOfChessBoard, /*ID*/ (int) i );
        mpBoardGridSizer->Add(mSquarePanels[i], 0, wxEXPAND | wxALL);
        //bind the paint event
        mSquarePanels[i]->Bind(wxEVT_PAINT, &ChessBoardPanel::PaintOnSquare, this);
        if (mpAllSquares[i]->IsBorderSquare() == false)
        {
        	mSquarePanels[i]->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::LeftMouseClick, this);
        	DropTargetPanel* p_target_panel = new DropTargetPanel(this);
        	p_target_panel->SetIndexOfSquare(i);
        	mSquarePanels[i]->SetDropTarget(p_target_panel);
        }
    }

    //Arrange the panels
    mpPrincipalSizer->Add(mpLeftOfChessBoard, 1, wxEXPAND | wxALL);
    mpPrincipalSizer->Add(mpMidPanelOfChessBoard, 6, wxEXPAND | wxALL);
    mpPrincipalSizer->Add(mpRightOfChessBoard, 2, wxEXPAND | wxALL);
    this->SetSizer(mpPrincipalSizer, false);

    //divide the section on the RHS of the board
    mpNameOfPlayerTop = new wxPanel(mpRightOfChessBoard, ID_OF_UPPER_PLAYER_NAME);
    mpNameOfPlayerBottom = new wxPanel(mpRightOfChessBoard, ID_OF_BOTTOM_PLAYER_NAME);
    mpSpaceForMoveList = new wxScrolledWindow(mpRightOfChessBoard, ID_OF_MOVE_LIST_SPACE);//, wxDefaultPosition, wxDefaultSize , wxVSCROLL);
	mpSpaceForArrows =  new wxPanel(mpRightOfChessBoard, ID_OF_ARROW_SPACE);

    mpRightSideSizer->Add(mpNameOfPlayerTop, 1, wxEXPAND);
    mpRightSideSizer->Add(mpSpaceForMoveList, 7, wxALL|wxGROW);
    mpRightSideSizer->Add(mpSpaceForArrows, 1, wxEXPAND);
    mpRightSideSizer->Add(mpNameOfPlayerBottom, 1, wxEXPAND);
    mpRightOfChessBoard->SetSizer(mpRightSideSizer, true);

    mpMoveListSizer->AddGrowableCol(0,1);
    mpMoveListSizer->AddGrowableCol(1,3);
    mpMoveListSizer->AddGrowableCol(2,3);
    mpSpaceForMoveList->SetSizer(mpMoveListSizer);

    mpForwardArrowPanel  = new wxPanel(mpSpaceForArrows, ID_FORWARD_BUTTON);
    mpForwardArrowPanelMore  = new wxPanel(mpSpaceForArrows, ID_FORWARD_MORE_BUTTON);
    mpForwardArrowPanelEnd  = new wxPanel(mpSpaceForArrows, ID_FORWARD_END_BUTTON);
    mpBackwardArrowPanel  = new wxPanel(mpSpaceForArrows, ID_BACKWARD_BUTTON);
    mpBackwardArrowPanelMore  = new wxPanel(mpSpaceForArrows, ID_BACKWARD_MORE_BUTTON);
    mpBackwardArrowPanelEnd  = new wxPanel(mpSpaceForArrows, ID_BACKWARD_END_BUTTON);


    mpSizerForArrows->Add(mpBackwardArrowPanelEnd,1.0, wxEXPAND | wxALL);
    mpSizerForArrows->Add(mpBackwardArrowPanelMore,1.0, wxEXPAND | wxALL);
    mpSizerForArrows->Add(mpBackwardArrowPanel,1.0, wxEXPAND | wxALL);
    mpSizerForArrows->Add(mpForwardArrowPanel,1.0, wxEXPAND | wxALL);
    mpSizerForArrows->Add(mpForwardArrowPanelMore,1.0, wxEXPAND | wxALL);
    mpSizerForArrows->Add(mpForwardArrowPanelEnd,1.0, wxEXPAND | wxALL);
    mpSpaceForArrows->SetSizer(mpSizerForArrows, false);


    //Bind the button and paint  events for the left side of the board
    mpLeftOfChessBoard->Bind(wxEVT_PAINT, &ChessBoardPanel::PaintOnSidesOfBoard, this);//with this-> instead of mpLeftOfChessBoard it does not work
    mpRightOfChessBoard->Bind(wxEVT_SIZE, &ChessBoardPanel::OnSize, this);

    //BIND THE CLICKS ON THE ARROWS
    mpForwardArrowPanel->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::ArrowButtonMovement, this);
    mpForwardArrowPanelMore->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::ArrowButtonMovement, this);
    mpForwardArrowPanelEnd->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::ArrowButtonMovement, this);
    mpBackwardArrowPanel->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::ArrowButtonMovement, this);
    mpBackwardArrowPanelMore->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::ArrowButtonMovement, this);
    mpBackwardArrowPanelEnd->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::ArrowButtonMovement, this);


    wxButton* rest_button  = new wxButton(mpLeftOfChessBoard, 1, wxT("Pgn..."),wxDefaultPosition, wxDefaultSize);
    rest_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ChessBoardPanel::LoadPgnFile, this);

    mpWhitePlayerBox = new wxTextCtrl (mpNameOfPlayerBottom, ID_WHITE_PLAYER_BOX, wxT(""), wxDefaultPosition,
    								  wxDefaultSize, wxTE_LEFT | wxTE_RICH | wxTE_MULTILINE | wxTE_DONTWRAP | wxBORDER_NONE);
    mpBlackPlayerBox = new wxTextCtrl (mpNameOfPlayerTop, ID_BLACK_PLAYER_BOX, wxT(""), wxDefaultPosition,
    								  wxDefaultSize, wxTE_LEFT | wxTE_RICH | wxTE_MULTILINE | wxTE_DONTWRAP | wxBORDER_NONE);

    //Make the white player box fill in the entire space
    wxPanel* above_white_player_name  = new wxPanel(mpNameOfPlayerBottom, ID_ABOVE_WHITE_PLAYER_NAME);
    wxPanel* below_white_player_name  = new wxPanel(mpNameOfPlayerBottom, ID_BELOW_WHITE_PLAYER_NAME);
    above_white_player_name->SetMinSize(wxSize(0,0));
    below_white_player_name->SetMinSize(wxSize(0,0));
    above_white_player_name->SetBackgroundColour(wxT("white"));
    below_white_player_name->SetBackgroundColour(wxT("white"));
    wxBoxSizer* white_player_box_sizer =  new wxBoxSizer(wxVERTICAL);
    white_player_box_sizer->Add(above_white_player_name,1, wxEXPAND | wxALL);
    white_player_box_sizer->Add(mpWhitePlayerBox,2, wxEXPAND | wxALL);
    white_player_box_sizer->Add(below_white_player_name,1, wxEXPAND | wxALL);
    mpNameOfPlayerBottom->SetSizer(white_player_box_sizer, false);

    //Make the black player box fill in the entire space
    wxPanel* above_black_player_name  = new wxPanel(mpNameOfPlayerTop, ID_ABOVE_BLACK_PLAYER_NAME);
    wxPanel* below_black_player_name  = new wxPanel(mpNameOfPlayerTop, ID_BELOW_BLACK_PLAYER_NAME);
    above_black_player_name->SetMinSize(wxSize(0,0));
    below_black_player_name->SetMinSize(wxSize(0,0));
    above_black_player_name->SetBackgroundColour(wxT("white"));
    below_black_player_name->SetBackgroundColour(wxT("white"));
    wxBoxSizer* black_player_box_sizer =  new wxBoxSizer(wxVERTICAL);
    black_player_box_sizer->Add(above_black_player_name,1, wxEXPAND | wxALL);
    black_player_box_sizer->Add(mpBlackPlayerBox,2, wxEXPAND | wxALL);
    black_player_box_sizer->Add(below_black_player_name,1, wxEXPAND | wxALL);
    mpNameOfPlayerTop->SetSizer(black_player_box_sizer, false);


    mTextAttributesPlayerNames = wxTextAttr(wxColour(32,7,129),
    										wxNullColour,
    										wxFont(wxFontInfo(14).FaceName("Helvetica")),
    										wxTEXT_ALIGNMENT_CENTRE);
    mTextAttributesPlayerNames.SetFlags(wxTEXT_ATTR_TEXT_COLOUR);
    mTextAttributesPlayerNames.SetFlags(wxTEXT_ATTR_FONT);
    mTextAttributesPlayerNames.SetFlags(wxTEXT_ATTR_ALIGNMENT);

    WritePlayerNames();
}

slach_gui::ChessBoardPanel::~ChessBoardPanel()
{
    delete mpChessBoardWithBorders;
}

void slach_gui::ChessBoardPanel::WritePlayerNames()
{
    mpWhitePlayerBox->ChangeValue("");
    mpWhitePlayerBox->SetDefaultStyle(mTextAttributesPlayerNames);
    mpWhitePlayerBox->WriteText(mWhitePlayerName);
    mpWhitePlayerBox->SetInsertionPoint(0);

    mpBlackPlayerBox->ChangeValue("");
    mpBlackPlayerBox->SetDefaultStyle(mTextAttributesPlayerNames);
    mpBlackPlayerBox->WriteText(mBlackPlayerName);
    mpBlackPlayerBox->SetInsertionPoint(0);
}

void slach_gui::ChessBoardPanel::LoadPgnFile(wxCommandEvent& WXUNUSED(event))
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
            WritePlayerNames();

            std::vector<slach::Move> move_list = mpChessBoard->GetGame()->GetMoveList();
            std::vector<std::string > move_list_san = mpChessBoard->GetGame()->GetMoveListAlgebraicFormat();
            wxSize window_size = mpSpaceForMoveList->GetSize();
            int size_of_one_move  = window_size.y/MAX_NUMBER_OF_VISIBLE_MOVES;
            int virtual_size_y = size_of_one_move * (static_cast<int> ( move_list.size()/2 + 2));//plus two for safety

            mpSpaceForMoveList->SetVirtualSize(window_size.x, virtual_size_y);

            unsigned number_of_panels_to_add = move_list.size() + static_cast<unsigned> (move_list.size()/2 + 1);
            mMoveListPanels.clear();
            unsigned move_index = 0;
            for (unsigned i = 0; i < number_of_panels_to_add; ++i)
            {
                mMoveListPanels.push_back( new wxTextCtrl( mpSpaceForMoveList, /*ID*/ OFFSET_OF_MOVE_LIST_ID + (int) i,
                                               wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTRE) );
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
                        mMoveListPanels[i]->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::OnClickOnMoveList, this);
                        mMoveListPanels[i]->Bind(wxEVT_ENTER_WINDOW, &ChessBoardPanel::OnMouseEnteringSingleMoveArea, this);
                        mMoveListPanels[i]->Bind(wxEVT_LEAVE_WINDOW, &ChessBoardPanel::OnMouseLeavingSingleMoveArea, this);

                        move_index++;
                    }
                }
            }
            mpSpaceForMoveList->Layout();
            //mpSpaceForMoveList->SetScrollbar(wxVERTICAL, 0, 8*window_size.y,500*(virtual_size_y+window_size.y) ); not needed
            mpSpaceForMoveList->SetScrollRate(0, 5);
            mpMoveListSizer->Layout();//force to layout, otherwise it is only done on resize...
        }
        mpChessBoard->ResetToMoveNumber(1,slach::WHITE);//otherwise, on an immediate resize, it will skip to the last move
    }
}

void slach_gui::ChessBoardPanel::LeftMouseClick(wxMouseEvent& event)
{
	int square_index_int = (static_cast<wxWindow*> (event.GetEventObject()))->GetId();
	mSourceIndex = (unsigned) square_index_int;

    wxDropSource drop_source(mSquarePanels[mSourceIndex], GetIconFromPiece(mpAllSquares[mSourceIndex]->GetPieceOnThisSquare()),
                                                          GetIconFromPiece(mpAllSquares[mSourceIndex]->GetPieceOnThisSquare()));

    wxBitmapDataObject piece_to_be_moved(GetImageFromPiece(mpAllSquares[mSourceIndex]->GetPieceOnThisSquare()));
    drop_source.SetData( piece_to_be_moved );

    mDrawPiece = false;
    mSquarePanels[mSourceIndex]->Refresh();///remove the source piece while dragging...

    wxDragResult result = drop_source.DoDragDrop( wxDragMove );

    mDrawPiece = true;
    switch (result)
    {
        case wxDragCopy: break;
        case wxDragMove: break;
        case wxDragCancel:
            mDrawPiece = true;
            //need to re-paint the piece as it was deleted upon initiation of dragging
            mSquarePanels[mSourceIndex]->Refresh();
            break;
        default: break;
    }
}

void slach_gui::ChessBoardPanel::LeftMouseRelease(unsigned destinationIndex)
{
	assert(mSourceIndex<mpAllSquares.size());
	assert(destinationIndex<mpAllSquares.size());
    slach::Move candidate_move(mpAllSquares[mSourceIndex], mpAllSquares[destinationIndex]);

    ProcessMoveInGui(candidate_move);
}

void slach_gui::ChessBoardPanel::ProcessMoveInGui(slach::Move & move)
{
	unsigned destination_index = move.GetDestination()->GetIndexFromTopLeft();
	unsigned source_index = move.GetOrigin()->GetIndexFromTopLeft();

    if (mpChessBoard->IsLegalMove(move)==true)
    {
        if (move.DoesMoveRequireSpecialGuiHandling())
        {
            mpChessBoard->MakeThisMove(move);

            //delete piece on origin
            mDrawPiece = false;
            mSquarePanels[source_index]->Refresh();
            mDrawPiece = true;

            //paint piece on destination
            mSquarePanels[destination_index]->Refresh();

			for (unsigned i = 0; i  < mSquarePanels.size(); ++i)
			{
				if (! ( mpChessBoardWithBorders->GetSquares()[i]->IsBorderSquare()))
				{
					mSquarePanels[i]->Refresh();
				}
			}
        }
        else
        {
            mpChessBoard->MakeThisMove(move);
            //delete piece on origin
            mDrawPiece = false;
            mSquarePanels[source_index]->Refresh();
            mDrawPiece = true;

            //paint piece on destination
            mSquarePanels[destination_index]->Refresh();
        }
        (static_cast<MainFrame*> (mpParent))->UpdateChessPositionForEngine(mpChessBoard->GetCurrentPosition());
    }
    else
    {
    	//not legal, re-draw piece on origin
    	mDrawPiece = true;
        mSquarePanels[source_index]->Refresh();
    }
}

void slach_gui::ChessBoardPanel::OnSize(wxSizeEvent& event)
{
    Refresh();

    //figure out the new dimensions
    wxSize chessboard_panel_size = mpPrincipalSizer->GetItem(mpMidPanelOfChessBoard)->GetSize();
    int panel_x = chessboard_panel_size.GetWidth();
    int panel_y = chessboard_panel_size.GetHeight();

    int min_size;

    //which side is longer...
    wxPoint central_point;
    if (panel_x > panel_y)
    {
        min_size=panel_y;
        central_point.x = (panel_x - min_size)/2;
        central_point.y = 0.0;
    }
    else
    {
        min_size=panel_x;
        central_point.x = 0.0;
        central_point.y = (panel_y - min_size)/2;
    }
    //...now resize the chess board accordingly
    wxSize chessboard_size(min_size,min_size);
    mpBoardGridSizer->SetDimension(central_point, chessboard_size);
    //mpBoardGridSizer->Layout();

    wxSize box_size = mpBlackPlayerBox->GetClientSize();
    mTextAttributesPlayerNames.SetFontPixelSize((int) box_size.y - (int)box_size.y/10);
    WritePlayerNames();

    //skip the event. Needed as per wxWdigets documentation
    event.Skip();
}

void slach_gui::ChessBoardPanel::OnClickOnMoveList(wxMouseEvent& event)
{
    int index_in_vector = ((wxPanel*) event.GetEventObject())->GetId() - OFFSET_OF_MOVE_LIST_ID;
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
    DrawAndSetFenPositionOnBoard(fen_to_set);
    for (unsigned i =0; i < mMoveListPanels.size(); ++i)
    {
        mMoveListPanels[i]->SetBackgroundColour(wxT("white"));
    }
    ((wxPanel*) event.GetEventObject())->SetBackgroundColour(*wxYELLOW);
}

void slach_gui::ChessBoardPanel::OnMouseEnteringSingleMoveArea(wxMouseEvent& event)
{
    int generating_index = ((wxPanel*) event.GetEventObject())->GetId() - OFFSET_OF_MOVE_LIST_ID;
    if (mMoveListPanels[generating_index]->GetBackgroundColour() != *wxYELLOW)
    {
        mMoveListPanels[generating_index]->SetBackgroundColour(*wxLIGHT_GREY);
    }
}

void slach_gui::ChessBoardPanel::OnMouseLeavingSingleMoveArea(wxMouseEvent& event)
{
    int generating_index = ((wxPanel*) event.GetEventObject())->GetId() - OFFSET_OF_MOVE_LIST_ID;
    if (mMoveListPanels[generating_index]->GetBackgroundColour() != *wxYELLOW)
    {
        mMoveListPanels[generating_index]->SetBackgroundColour(*wxWHITE);
    }
}

void slach_gui::ChessBoardPanel::ArrowButtonMovement(wxMouseEvent& event)
{
    int generating_id = ((wxPanel*) event.GetEventObject())->GetId();
    slach::Colour current_turn = mpChessBoard->WhosTurnIsIt();
    slach::Colour opp_col = slach::OppositeColour(current_turn);

    std::string fen_to_set;

    if (generating_id == ID_FORWARD_BUTTON)
    {
        mpChessBoard->ResetToNextMove();
        fen_to_set = mpChessBoard->GetCurrentFenPosition();
    }
    else if (generating_id == ID_FORWARD_MORE_BUTTON)
    {
        mpChessBoard->ResetToNextMove();
        mpChessBoard->ResetToNextMove();
        mpChessBoard->ResetToNextMove();
        mpChessBoard->ResetToNextMove();
        mpChessBoard->ResetToNextMove();
        fen_to_set = mpChessBoard->GetCurrentFenPosition();
    }
    else if (generating_id == ID_FORWARD_END_BUTTON)
    {
        fen_to_set = mpChessBoard->GetGame()->FetchFromFenList(100000000, opp_col);
    }
    else if (generating_id == ID_BACKWARD_BUTTON)
    {
        mpChessBoard->ResetToPreviousMove();
        fen_to_set = mpChessBoard->GetCurrentFenPosition();
    }
    else if (generating_id == ID_BACKWARD_MORE_BUTTON)
    {
        mpChessBoard->ResetToPreviousMove();
        mpChessBoard->ResetToPreviousMove();
        mpChessBoard->ResetToPreviousMove();
        mpChessBoard->ResetToPreviousMove();
        mpChessBoard->ResetToPreviousMove();
        fen_to_set = mpChessBoard->GetCurrentFenPosition();
    }
    else if (generating_id == ID_BACKWARD_END_BUTTON)
    {
        fen_to_set = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    }
    DrawAndSetFenPositionOnBoard(fen_to_set);
}

void slach_gui::ChessBoardPanel::PaintOnSidesOfBoard(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(mpLeftOfChessBoard);
    DoPaintVerticalGradient(dc, mpLeftOfChessBoard);

    wxPaintDC dc1(mpMidPanelOfChessBoard);
    DoPaintVerticalGradient(dc1, mpMidPanelOfChessBoard);

    wxPaintDC dc2(mpRightOfChessBoard);
    DoPaintVerticalGradient(dc2, mpRightOfChessBoard);


    wxPaintDC dcBE(mpBackwardArrowPanelEnd);
    DoPaintImageOnPanel(dcBE, mpBackwardArrowPanelEnd, mArrowImages[5]);

    wxPaintDC dcBM(mpBackwardArrowPanelMore);
    DoPaintImageOnPanel(dcBM, mpBackwardArrowPanelMore, mArrowImages[4]);

    wxPaintDC dcBACK(mpBackwardArrowPanel);
    DoPaintImageOnPanel(dcBACK, mpBackwardArrowPanelMore, mArrowImages[3]);

    wxPaintDC dcFOR(mpForwardArrowPanel);
    DoPaintImageOnPanel(dcFOR, mpForwardArrowPanel, mArrowImages[0]);

    wxPaintDC dcFM(mpForwardArrowPanelMore);
    DoPaintImageOnPanel(dcFM, mpForwardArrowPanelMore, mArrowImages[1]);

    wxPaintDC dcFE(mpForwardArrowPanelEnd);
    DoPaintImageOnPanel(dcFE, mpForwardArrowPanelEnd, mArrowImages[2]);
}

void slach_gui::ChessBoardPanel::DoPaintImageOnPanel(wxPaintDC& dc, wxPanel* pPanel, wxImage& Image)
{
    int width = pPanel->GetClientSize().GetWidth();
    int height = pPanel->GetClientSize().GetHeight();
    Image.Rescale(width, height);
    //now really draw the rendered image;
    dc.DrawBitmap(Image, 0, 0, true );
}

void slach_gui::ChessBoardPanel::DoPaintVerticalGradient(wxPaintDC& dc, wxPanel* pPanel)
{
    wxRect clientRect = pPanel->GetClientRect();
    wxRect gradientRect = clientRect;
    gradientRect.SetHeight(gradientRect.GetHeight());
    dc.GradientFillLinear(gradientRect,
    wxColour(32,107,129), wxColour(235,241,246), wxSOUTH);
}
void slach_gui::ChessBoardPanel::PaintOnSquare(wxPaintEvent& event)
{
	int square_index_int = (static_cast<wxWindow*> (event.GetEventObject()))->GetId();
	unsigned square_index = (unsigned) square_index_int;

	wxPaintDC dc(mSquarePanels[square_index]);
	if (mpAllSquares[square_index]->IsBorderSquare())
	{
		PaintBackground(dc, square_index);
		PaintOnBorder(dc, square_index);
	}
	else
	{
		PaintBackground(dc, square_index);
		if (mDrawPiece == true)
		{
			PaintPiece(dc, square_index);
		}
	}
	//event .Skip();
}

void slach_gui::ChessBoardPanel::DrawAndSetFenPositionOnBoard(const std::string& rFenPosition)
{
    mpChessBoard->SetFenPosition(rFenPosition);
    for (unsigned i = 0; i  < mSquarePanels.size(); ++i)
    {
        if (! ( mpChessBoardWithBorders->GetSquares()[i]->IsBorderSquare()))
        {
            mSquarePanels[i]->Refresh();
        }
    }
    (static_cast<MainFrame*> (mpParent))->UpdateChessPositionForEngine(mpChessBoard->GetCurrentPosition());
}

void slach_gui::ChessBoardPanel::ResetToInitialPosition(wxCommandEvent& event)
{
    DrawAndSetFenPositionOnBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    event.Skip();
}

///////////////////////////////
// Helper private methods
//////////////////////////////
void slach_gui::ChessBoardPanel::LoadBoardImages()
{
	mPieceImages.resize(16u);

    mPieceImages[0].LoadFile(wxString((mPngPieceDirectory+"white_king.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[1].LoadFile(wxString((mPngPieceDirectory+"black_king.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[2].LoadFile(wxString((mPngPieceDirectory+"white_queen.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[3].LoadFile(wxString((mPngPieceDirectory+"black_queen.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[4].LoadFile(wxString((mPngPieceDirectory+"white_rook.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[5].LoadFile(wxString((mPngPieceDirectory+"black_rook.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[6].LoadFile(wxString((mPngPieceDirectory+"white_bishop.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[7].LoadFile(wxString((mPngPieceDirectory+"black_bishop.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[8].LoadFile(wxString((mPngPieceDirectory+"white_knight.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[9].LoadFile(wxString((mPngPieceDirectory+"black_knight.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[10].LoadFile(wxString((mPngPieceDirectory+"white_pawn.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[11].LoadFile(wxString((mPngPieceDirectory+"black_pawn.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[12].LoadFile(wxString((mPngPieceDirectory+"no_piece.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[13].LoadFile(wxString((mPngBackgroundDirectory+"dark_square.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[14].LoadFile(wxString((mPngBackgroundDirectory+"light_square.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mPieceImages[15].LoadFile(wxString((mPngBackgroundDirectory+"border_square.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );

    mArrowImages.resize(6u);
    mArrowImages[0].LoadFile(wxString((mPngArrowsDirectory+"forward.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mArrowImages[1].LoadFile(wxString((mPngArrowsDirectory+"forward_more.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mArrowImages[2].LoadFile(wxString((mPngArrowsDirectory+"forward_end.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mArrowImages[3].LoadFile(wxString((mPngArrowsDirectory+"backward.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mArrowImages[4].LoadFile(wxString((mPngArrowsDirectory+"backward_more.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
    mArrowImages[5].LoadFile(wxString((mPngArrowsDirectory+"backward_end.png").c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG );
}

void slach_gui::ChessBoardPanel::PaintPiece(wxPaintDC& dc, unsigned squareIndex)
{
	assert(mPieceImages.size() == 16u);
    slach::PieceType piece = mpAllSquares[squareIndex]->GetPieceOnThisSquare();
    wxImage piece_image = GetImageFromPiece(piece);

    int width = mSquarePanels[squareIndex]->GetClientSize().GetWidth();
    int height = mSquarePanels[squareIndex]->GetClientSize().GetHeight();
    piece_image.Rescale(width, height);
    //now really draw the rendered image;
    dc.DrawBitmap( piece_image, 0, 0, true );
}

wxIcon slach_gui::ChessBoardPanel::GetIconFromPiece(slach::PieceType piece)
{
    wxIcon piece_icon;
    switch(piece)
    {
        case slach::WHITE_KING:
            piece_icon = wxDROP_ICON(white_king);
            break;
        case slach::BLACK_KING:
            piece_icon = wxDROP_ICON(black_king);
            break;
        case slach::WHITE_QUEEN:
            piece_icon = wxDROP_ICON(white_queen);
            break;
        case slach::BLACK_QUEEN:
            piece_icon = wxDROP_ICON(black_queen);
            break;
        case slach::WHITE_ROOK:
            piece_icon = wxDROP_ICON(white_rook);
            break;
        case slach::BLACK_ROOK:
            piece_icon = wxDROP_ICON(black_rook);
            break;
        case slach::WHITE_BISHOP:
            piece_icon = wxDROP_ICON(white_bishop);
            break;
        case slach::BLACK_BISHOP:
            piece_icon = wxDROP_ICON(black_bishop);
            break;
        case slach::WHITE_KNIGHT:
            piece_icon = wxDROP_ICON(white_knight);
            break;
        case slach::BLACK_KNIGHT:
            piece_icon = wxDROP_ICON(black_knight);
            break;
        case slach::WHITE_PAWN:
            piece_icon = wxDROP_ICON(white_pawn);
            break;
        case slach::BLACK_PAWN:
            piece_icon = wxDROP_ICON(black_pawn);
            break;
        case slach::NO_PIECE:
            piece_icon = wxDROP_ICON(no_piece);
            break;
        default:
            //NEVER_REACHED;
            break;
    }

    return piece_icon;
}
wxImage slach_gui::ChessBoardPanel::GetImageFromPiece(slach::PieceType piece)
{
	wxImage piece_image;
    switch(piece)
    {
        case slach::WHITE_KING:
            piece_image = mPieceImages[0];
            break;
        case slach::BLACK_KING:
            piece_image = mPieceImages[1];
            break;
        case slach::WHITE_QUEEN:
            piece_image = mPieceImages[2];
            break;
        case slach::BLACK_QUEEN:
            piece_image = mPieceImages[3];
            break;
        case slach::WHITE_ROOK:
            piece_image = mPieceImages[4];
            break;
        case slach::BLACK_ROOK:
            piece_image = mPieceImages[5];
            break;
        case slach::WHITE_BISHOP:
            piece_image = mPieceImages[6];
            break;
        case slach::BLACK_BISHOP:
            piece_image = mPieceImages[7];
            break;
        case slach::WHITE_KNIGHT:
            piece_image = mPieceImages[8];
            break;
        case slach::BLACK_KNIGHT:
            piece_image = mPieceImages[9];
            break;
        case slach::WHITE_PAWN:
            piece_image = mPieceImages[10];
            break;
        case slach::BLACK_PAWN:
            piece_image = mPieceImages[11];
            break;
        case slach::NO_PIECE:
            piece_image = mPieceImages[12];
            break;
        default:
            //NEVER_REACHED;
            break;
    }
    return piece_image;
}


void slach_gui::ChessBoardPanel::PaintBackground(wxPaintDC& dc, unsigned squareIndex)
{
    assert(mPieceImages.size() == 16u);
    int width = mSquarePanels[squareIndex]->GetClientSize().GetWidth();
    int height = mSquarePanels[squareIndex]->GetClientSize().GetHeight();

    if ( (mpAllSquares[squareIndex]->IsDarkSquare() == true) && (mpAllSquares[squareIndex]->IsBorderSquare() == false))
    {
        mPieceImages[13].Rescale(width, height);//rgb 32,107,129
        //now really draw the rendered image
        dc.DrawBitmap( mPieceImages[13], 0, 0, true );
    }
    if ( (mpAllSquares[squareIndex]->IsLightSquare() == true) && (mpAllSquares[squareIndex]->IsBorderSquare() == false))
    {
        mPieceImages[14].Rescale(width, height);//rgb 235.241,246
        //now really draw the rendered image
        dc.DrawBitmap( mPieceImages[14], 0, 0, true );
    }
    if (mpAllSquares[squareIndex]->IsBorderSquare())
    {
        mPieceImages[15].Rescale(width, height);//rgb 35,87,102
        //now really draw the rendered image
        dc.DrawBitmap( mPieceImages[15], 0, 0, true );
    }
}

void slach_gui::ChessBoardPanel::PaintOnBorder(wxPaintDC& dc, unsigned squareIndex)
{
    if ( (mpAllSquares[squareIndex]->IsBorderSquare()==true &&
    	  mpAllSquares[squareIndex]->IsCornerSquare()==false &&
    	  mpAllSquares[squareIndex]->IsCoordinatePrintable()))
    {
        double fractional_occupancy_of_space= 0.7;
        int dim = 0;
        int xcoord = 0;
        int ycoord = 0;
        int width = mSquarePanels[squareIndex]->GetClientSize().GetWidth();
        int height = mSquarePanels[squareIndex]->GetClientSize().GetHeight();
        if (width<=height)
        {
            dim =  width*fractional_occupancy_of_space;
            xcoord = 0.0;//for some reason it does not want to center itself when it is small
            ycoord = (height-dim)/2;
        }
        else
        {
            dim = height*fractional_occupancy_of_space;
            xcoord = (width-dim)/2;
            ycoord = (height-dim)/2;;
        }

        wxImage ret = DetermineCoordinateToPrint(squareIndex);
        ret.Rescale(dim, dim);
        dc.DrawBitmap(ret, xcoord, ycoord, true );
    }
}

wxImage slach_gui::ChessBoardPanel::DetermineCoordinateToPrint(unsigned squareIndex)
{
	wxImage ret;
    if (mpAllSquares[squareIndex]->GetFile()=='a')
    {
        wxMemoryInputStream istream(a_img, sizeof a_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetFile()=='b')
    {
        wxMemoryInputStream istream(b_img, sizeof b_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetFile()=='c')
    {
        wxMemoryInputStream istream(c_img, sizeof c_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetFile()=='d')
    {
        wxMemoryInputStream istream(d_img, sizeof d_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetFile()=='e')
    {
        wxMemoryInputStream istream(e_img, sizeof e_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetFile()=='f')
    {
        wxMemoryInputStream istream(f_img, sizeof f_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetFile()=='g')
    {
        wxMemoryInputStream istream(g_img, sizeof g_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetFile()=='h')
    {
        wxMemoryInputStream istream(h_img, sizeof h_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }

    else if (mpAllSquares[squareIndex]->GetRank()=='1')
    {
        wxMemoryInputStream istream(one_img, sizeof one_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetRank()=='2')
    {
        wxMemoryInputStream istream(two_img, sizeof two_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetRank()=='3')
    {
        wxMemoryInputStream istream(three_img, sizeof three_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetRank()=='4')
    {
        wxMemoryInputStream istream(four_img, sizeof four_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetRank()=='5')
    {
        wxMemoryInputStream istream(five_img, sizeof five_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetRank()=='6')
    {
        wxMemoryInputStream istream(six_img, sizeof six_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetRank()=='7')
    {
        wxMemoryInputStream istream(seven_img, sizeof seven_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else if (mpAllSquares[squareIndex]->GetRank()=='8')
    {
        wxMemoryInputStream istream(eight_img, sizeof eight_img);
        ret.LoadFile(istream, wxBITMAP_TYPE_PNG);
    }
    else
    {
        //we should never be here
    }

    return ret;
}


