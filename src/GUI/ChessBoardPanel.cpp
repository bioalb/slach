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
#include "MainFrame.hpp"


slach_gui::ChessBoardPanel::ChessBoardPanel(wxPanel* parent, wxWindowID WXUNUSED(id), const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size),
      mpParent(parent),
      mIamTheMainBoard(true),
      mPngPieceDirectory("../../src/GUI/bitmaps/pieces/png/"),
      mPngBackgroundDirectory("../../src/GUI/bitmaps/squares/png/"),
      mpChessBoardWithBorders ( new slach::ChessBoardWithBorders() ),
      mpChessBoard(NULL),
      mpBoardGridSizer ( new wxFlexGridSizer(slach::gBoardRowSize+2,slach::gBoardColumnSize+2,0,0) ),
      mpPrincipalSizer ( new wxBoxSizer(wxVERTICAL) ),
      mpSizerForArrows ( new wxBoxSizer(wxHORIZONTAL) ),
      mpSpaceForArrows ( new wxPanel(this, ID_OF_ARROW_SPACE) ),
      mpSpaceForActualBoard (  new wxPanel(this, ID_OF_BOARD_SPACE) ),
      mDrawPiece(true),
      mGameIsLoaded(false),
      mPerspectiveIsFromWhite(true),
      mSourceIndex(0u),
      mDestinationIndex(0u),
      mCachedArrowsStartPoint (wxPoint(0,0)),
      mCachedArrowSpace (wxSize(10,10))
{
    mpSpaceForActualBoard->SetBackgroundColour(*wxWHITE);
    mpSpaceForArrows->SetBackgroundColour(*wxWHITE);
    mpPrincipalSizer->Add(mpSpaceForActualBoard,15, wxGROW | wxALL);
    mpPrincipalSizer->Add(mpSpaceForArrows, 1, wxGROW | wxALL);
    this->SetSizer(mpPrincipalSizer);

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
    DoCommunicateTheCurrentPositionForEngine();
    mpAllSquares = mpChessBoardWithBorders->GetSquares();

    assert(mpAllSquares.size() == mSquarePanels.size());
    for (unsigned i = 0; i < mpAllSquares.size(); ++i)
    {
        mSquarePanels[i] = new wxPanel( mpSpaceForActualBoard, /*ID*/ (int) i );
        mpBoardGridSizer->Add(mSquarePanels[i], 0, wxEXPAND | wxALL);
        //bind the paint event
        mSquarePanels[i]->Bind(wxEVT_PAINT, &ChessBoardPanel::PaintOnSquare, this);
        if (mpAllSquares[i]->IsBorderSquare() == false)
        {
        	mSquarePanels[i]->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::LeftMouseClick, this);
        	mSquarePanels[i]->Bind(wxEVT_MOTION, &ChessBoardPanel::LeftMouseClick, this);
        	mSquarePanels[i]->Bind(wxEVT_LEFT_UP, &ChessBoardPanel::LeftMouseRelease, this);
        }
    }
    mpSpaceForActualBoard->SetSizer(mpBoardGridSizer);

    mpForwardArrowPanel  = new wxPanel(mpSpaceForArrows, ID_FORWARD_BUTTON);
    mpForwardArrowPanelMore  = new wxPanel(mpSpaceForArrows, ID_FORWARD_MORE_BUTTON);
    mpForwardArrowPanelEnd  = new wxPanel(mpSpaceForArrows, ID_FORWARD_END_BUTTON);
    mpBackwardArrowPanel  = new wxPanel(mpSpaceForArrows, ID_BACKWARD_BUTTON);
    mpBackwardArrowPanelMore  = new wxPanel(mpSpaceForArrows, ID_BACKWARD_MORE_BUTTON);
    mpBackwardArrowPanelEnd  = new wxPanel(mpSpaceForArrows, ID_BACKWARD_END_BUTTON);
    mpDummyPanelAfterLastArrow = new wxPanel(mpSpaceForArrows, ID_DUMMY_AFTER_LAST_ARROW);
    mpDummyPanelAfterLastArrow->SetBackgroundColour(*wxWHITE);
    mpSizerForArrows->Add(mpBackwardArrowPanelEnd,1.0, wxEXPAND | wxALL);
    mpSizerForArrows->Add(mpBackwardArrowPanelMore,1.0, wxEXPAND | wxALL);
    mpSizerForArrows->Add(mpBackwardArrowPanel,1.0, wxEXPAND | wxALL);
    mpSizerForArrows->Add(mpForwardArrowPanel,1.0, wxEXPAND | wxALL);
    mpSizerForArrows->Add(mpForwardArrowPanelMore,1.0, wxEXPAND | wxALL);
    mpSizerForArrows->Add(mpForwardArrowPanelEnd,1.0, wxEXPAND | wxALL);
    mpSizerForArrows->Add(mpDummyPanelAfterLastArrow,4.0, wxEXPAND | wxALL);
    mpSpaceForArrows->SetSizer(mpSizerForArrows);

    //BIND THE CLICKS ON THE ARROWS and the keys
    mpForwardArrowPanel->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::ArrowButtonMovement, this);
    mpForwardArrowPanelMore->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::ArrowButtonMovement, this);
    mpForwardArrowPanelEnd->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::ArrowButtonMovement, this);
    mpBackwardArrowPanel->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::ArrowButtonMovement, this);
    mpBackwardArrowPanelMore->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::ArrowButtonMovement, this);
    mpBackwardArrowPanelEnd->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::ArrowButtonMovement, this);

    mpSpaceForActualBoard->Bind(wxEVT_SIZE, &ChessBoardPanel::OnSize, this);
    mpSpaceForArrows->Bind(wxEVT_SIZE, &ChessBoardPanel::OnSize, this);
    mpForwardArrowPanel->Bind(wxEVT_PAINT, &ChessBoardPanel::PaintArrows, this);
    mpForwardArrowPanelMore->Bind(wxEVT_PAINT, &ChessBoardPanel::PaintArrows, this);
    mpForwardArrowPanelEnd->Bind(wxEVT_PAINT, &ChessBoardPanel::PaintArrows, this);
    mpBackwardArrowPanel->Bind(wxEVT_PAINT, &ChessBoardPanel::PaintArrows, this);
    mpBackwardArrowPanelMore->Bind(wxEVT_PAINT, &ChessBoardPanel::PaintArrows, this);
    mpBackwardArrowPanelEnd->Bind(wxEVT_PAINT, &ChessBoardPanel::PaintArrows, this);
}

slach_gui::ChessBoardPanel::~ChessBoardPanel()
{
    delete mpChessBoardWithBorders;
}

void slach_gui::ChessBoardPanel::SetAsMainBoard(bool flag)
{
    mIamTheMainBoard = flag;
}
void slach_gui::ChessBoardPanel::DoFlipView()
{
    if (mPerspectiveIsFromWhite == true)
    {
        mpAllSquares = mpChessBoardWithBorders->GetSquaresBlackPerspective();
        mPerspectiveIsFromWhite = false;
    }
    else
    {
        mpAllSquares = mpChessBoardWithBorders->GetSquares();
        mPerspectiveIsFromWhite = true;
    }
    mpBoardGridSizer->Layout();
}

bool slach_gui::ChessBoardPanel::IsItFromWhitePerspective() const
{
    return mPerspectiveIsFromWhite;
}

void slach_gui::ChessBoardPanel::LeftMouseClick(wxMouseEvent& event)
{
	int square_index_int = (static_cast<wxWindow*> (event.GetEventObject()))->GetId();

	//prepare the cursor
	wxImage curs_image = GetImageFromPiece(mpAllSquares[square_index_int]->GetPieceOnThisSquare());
    int width = mSquarePanels[square_index_int]->GetClientSize().GetWidth();
    int height = mSquarePanels[square_index_int]->GetClientSize().GetHeight();
    curs_image.Rescale(width, height);
	curs_image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_X, width/2);
	curs_image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_Y, height/2);
	wxCursor piece_cursor( curs_image );
	//set if it is dragging....
	if (event.Dragging())
	{
		wxSetCursor(piece_cursor);
		mSourceIndex = (unsigned) square_index_int;
		mDrawPiece = false;
		mSquarePanels[mSourceIndex]->Refresh();///remove the source piece while dragging...
	}
	event.Skip();
}

void slach_gui::ChessBoardPanel::LeftMouseRelease(wxMouseEvent& event)
{
	unsigned destination_index = 0;
	for (unsigned i = 0; i < mpAllSquares.size(); ++i)
	{
		if (mSquarePanels[i]->GetClientRect().Contains(mSquarePanels[i]->ScreenToClient( wxGetMousePosition() )))
		{
			destination_index = i;//found it!
			break;
		}
	}
	wxSetCursor(wxNullCursor);
	assert(mSourceIndex<mpAllSquares.size());
	assert(destination_index<mpAllSquares.size());
    slach::Move candidate_move(mpAllSquares[mSourceIndex], mpAllSquares[destination_index]);
    if (destination_index > 0 )
    {
        mDestinationIndex = destination_index;
    }
    ProcessMoveInGui(candidate_move);
    event.Skip();
}

void slach_gui::ChessBoardPanel::ClearCurrentHighlighting()
{
    for (unsigned i = 0; i  < mSquarePanels.size(); ++i)
    {
        if (! ( mpChessBoardWithBorders->GetSquares()[i]->IsBorderSquare()))
        {
            mSquarePanels[i]->Refresh();
        }
    }
}

void slach_gui::ChessBoardPanel::ProcessMoveInGui(slach::Move & move)
{
    unsigned destination_index = 0;
    unsigned source_index = 0;
    if (mPerspectiveIsFromWhite == true)
    {
        destination_index = move.GetDestination()->GetIndexFromTopLeft();
        source_index = move.GetOrigin()->GetIndexFromTopLeft();
    }
    else
    {
        destination_index = move.GetDestination()->GetIndexFromBottomRight();
        source_index = move.GetOrigin()->GetIndexFromBottomRight();
    }

    if (mpChessBoard->IsLegalMove(move)==true)
    {
        ClearCurrentHighlighting();
        if (move.DoesMoveRequireSpecialGuiHandling())
        {
            mpChessBoard->MakeThisMove(move);

            //delete piece on origin
            mDrawPiece = false;
            mpAllSquares[source_index]->SetAsToBeHighlightable(true);//paint event activated at next line
            mSquarePanels[source_index]->Refresh();
            mDrawPiece = true;

            //paint piece on destination
            mpAllSquares[destination_index]->SetAsToBeHighlightable(true);
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
            mpAllSquares[source_index]->SetAsToBeHighlightable(true);
            mSquarePanels[source_index]->Refresh();
            mDrawPiece = true;

            //paint piece on destination
            mpAllSquares[destination_index]->SetAsToBeHighlightable(true);
            mSquarePanels[destination_index]->Refresh();
        }
        DoCommunicateTheCurrentPositionForEngine();
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
    //figure out the new dimensions
    wxSize total_panel_size = this->GetSize();
    int panel_x = total_panel_size.GetWidth();
    int panel_y = total_panel_size.GetHeight();

    wxSize arrow_space_size = mpSpaceForArrows->GetSize();
    //int arrows_x = arrow_space_size.GetWidth();
    int arrows_y = arrow_space_size.GetHeight();

    int min_size;

    //which side is longer...
    wxPoint central_point;
    wxPoint start_of_arrows(0,0);
    if (panel_x > panel_y)
    {
        min_size=panel_y - arrows_y;
        central_point.x = (panel_x - min_size)/2;
        central_point.y = 0.0;

        start_of_arrows.x = central_point.x;
        start_of_arrows.y = 0.0;
        arrow_space_size.x = min_size;
    }
    else
    {
        min_size=panel_x;
        central_point.x = 0.0;
        central_point.y = panel_y - min_size - arrows_y;
    }
    //...now resize the chess board accordingly
    wxSize chessboard_size(min_size,min_size);

    mpBoardGridSizer->SetDimension(central_point, chessboard_size);
    mpSizerForArrows->SetDimension(start_of_arrows, arrow_space_size);

    mCachedArrowsStartPoint = start_of_arrows;
    mCachedArrowSpace = arrow_space_size;
    event.Skip();
}

void slach_gui::ChessBoardPanel::DoAdvanceOneMove()
{
    mpChessBoard->ResetToNextMove();
    std::string fen_to_set = mpChessBoard->GetCurrentFenPosition();
    if (mIamTheMainBoard == true)
    {
        (static_cast<CentralPanel*> (mpParent))->HighlightNextMove();
    }
    DrawAndSetFenPositionOnBoard(fen_to_set);
}

void slach_gui::ChessBoardPanel::DoAdvanceSeveralMoves()
{
    mpChessBoard->ResetToNextMove();
    mpChessBoard->ResetToNextMove();
    mpChessBoard->ResetToNextMove();
    mpChessBoard->ResetToNextMove();
    mpChessBoard->ResetToNextMove();
    std::string fen_to_set = mpChessBoard->GetCurrentFenPosition();
    if (mIamTheMainBoard == true)
    {
        (static_cast<CentralPanel*> (mpParent))->HighlightSeveralMovesAhead();
    }
    DrawAndSetFenPositionOnBoard(fen_to_set);
}

void slach_gui::ChessBoardPanel::DoAdvanceUntilEnd()
{
    slach::Colour current_turn = mpChessBoard->WhosTurnIsIt();
    slach::Colour opp_col = slach::OppositeColour(current_turn);
    std::string fen_to_set = mpChessBoard->GetGame()->FetchFromFenList(100000000, opp_col);
    if (mIamTheMainBoard == true)
    {
        (static_cast<CentralPanel*> (mpParent))->HighlightLastMove();
    }
    DrawAndSetFenPositionOnBoard(fen_to_set);
}
void slach_gui::ChessBoardPanel::DoGoBackOneMove()
{
    mpChessBoard->ResetToPreviousMove();
    std::string fen_to_set = mpChessBoard->GetCurrentFenPosition();
    if (mIamTheMainBoard == true)
    {
        (static_cast<CentralPanel*> (mpParent))->HighlightPreviousMove();
    }
    DrawAndSetFenPositionOnBoard(fen_to_set);
}
void slach_gui::ChessBoardPanel::DoGoBackSeveralMoves()
{
    mpChessBoard->ResetToPreviousMove();
    mpChessBoard->ResetToPreviousMove();
    mpChessBoard->ResetToPreviousMove();
    mpChessBoard->ResetToPreviousMove();
    mpChessBoard->ResetToPreviousMove();
    std::string fen_to_set = mpChessBoard->GetCurrentFenPosition();
    if (mIamTheMainBoard == true)
    {
        (static_cast<CentralPanel*> (mpParent))->HighlightSeveralMovesBack();
    }
    DrawAndSetFenPositionOnBoard(fen_to_set);
}

void slach_gui::ChessBoardPanel::DoGoBackToBeginning()
{
    std::string fen_to_set = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    if (mIamTheMainBoard == true)
    {
        (static_cast<CentralPanel*> (mpParent))->HighlightBeforeFirstMove();
    }
    DrawAndSetFenPositionOnBoard(fen_to_set);
}

void slach_gui::ChessBoardPanel::ArrowButtonMovement(wxMouseEvent& event)
{
    int generating_id = ((wxPanel*) event.GetEventObject())->GetId();

    if (generating_id == ID_FORWARD_BUTTON) DoAdvanceOneMove();
    else if (generating_id == ID_FORWARD_MORE_BUTTON) DoAdvanceSeveralMoves();
    else if (generating_id == ID_FORWARD_END_BUTTON) DoAdvanceUntilEnd();
    else if (generating_id == ID_BACKWARD_BUTTON) DoGoBackOneMove();
    else if (generating_id == ID_BACKWARD_MORE_BUTTON) DoGoBackSeveralMoves();
    else if (generating_id == ID_BACKWARD_END_BUTTON) DoGoBackToBeginning();
}

void slach_gui::ChessBoardPanel::DoPaintImageOnPanel(wxPaintDC& dc, wxPanel* pPanel, wxImage& Image)
{
    int width = pPanel->GetClientSize().GetWidth();
    int height = pPanel->GetClientSize().GetHeight();
    Image.Rescale(width, height);
    //now really draw the rendered image;
    dc.DrawBitmap(Image, 0, 0, true );
}

void slach_gui::ChessBoardPanel::PaintArrows(wxPaintEvent& event)
{
    int generating_id = ((wxPanel*) event.GetEventObject())->GetId();

    mpSizerForArrows->SetDimension(mCachedArrowsStartPoint, mCachedArrowSpace);
    mpSizerForArrows->Layout();

    mpBackwardArrowPanelEnd->SetBackgroundColour (wxColour(35,87,102));
    mpBackwardArrowPanelMore->SetBackgroundColour (wxColour(35,87,102));
    mpBackwardArrowPanel->SetBackgroundColour (wxColour(35,87,102));
    mpForwardArrowPanel->SetBackgroundColour (wxColour(35,87,102));
    mpForwardArrowPanelMore->SetBackgroundColour (wxColour(35,87,102));
    mpForwardArrowPanelEnd->SetBackgroundColour (wxColour(35,87,102));
    double margin_x_dir = 0.3;//fractional margin between arrow and border of panel, x direction
    double margin_y_dir = 0.1;//fractional margin between arrow and border of panel, y direction
    double double_arrow_offset = 0.5;//fractional offset for doublw arrows
    if (generating_id == ID_BACKWARD_END_BUTTON)
    {
        wxPaintDC dcBE(mpBackwardArrowPanelEnd);
        wxSize panel_size = mpSizerForArrows->GetItem(mpBackwardArrowPanelEnd)->GetSize();
        int origin_y = panel_size.y*0.5;
        int origin_x = panel_size.x*margin_x_dir;

        dcBE.SetBrush(wxBrush(wxColour(207,239,235))); // filling,
        dcBE.SetPen( wxNullPen );
        wxPoint point_list [] = {wxPoint(0,0),
                                 wxPoint((1.0 - 2*margin_x_dir)*panel_size.x,-0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                 wxPoint((1.0 - 2*margin_x_dir)*panel_size.x, 0.5*(1.0-2.0*margin_y_dir)*panel_size.y)};
        dcBE.DrawPolygon(3, point_list, origin_x, origin_y);

        dcBE.SetPen( wxPen( wxColor(207,239,235), 2 ) ); // 2-pixels-thick outline
        dcBE.DrawLine(origin_x, margin_y_dir*panel_size.y,
                      origin_x, (1.0-margin_y_dir)*panel_size.y);
    }
    else if (generating_id == ID_BACKWARD_MORE_BUTTON)
    {
        wxPaintDC dcBM(mpBackwardArrowPanelMore);
        wxSize panel_size = mpSizerForArrows->GetItem(mpBackwardArrowPanelMore)->GetSize();
        int origin_y = panel_size.y/2;
        int origin_x = panel_size.x*margin_x_dir;

        dcBM.SetBrush(wxBrush(wxColour(207,239,235))); // filling,
        dcBM.SetPen( wxNullPen );
        wxPoint point_list [] = {wxPoint(0,0),
                                 wxPoint((1.0 - 2*margin_x_dir)*panel_size.x,-0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                 wxPoint((1.0 - 2*margin_x_dir)*panel_size.x, 0.5*(1.0-2.0*margin_y_dir)*panel_size.y)};
        wxPoint point_list_2 [] = {wxPoint( - panel_size.x*margin_x_dir*double_arrow_offset,0),
                                   wxPoint(double_arrow_offset*(1.0 - 2*margin_x_dir)*panel_size.x,-0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                   wxPoint(double_arrow_offset*(1.0 - 2*margin_x_dir)*panel_size.x, 0.5*(1.0-2.0*margin_y_dir)*panel_size.y)};
        dcBM.DrawPolygon(3, point_list, origin_x, origin_y);
        dcBM.DrawPolygon(3, point_list_2, origin_x, origin_y);
    }
    else if (generating_id == ID_BACKWARD_BUTTON)
    {
        wxPaintDC dcBACK(mpBackwardArrowPanel);
        wxSize panel_size = mpSizerForArrows->GetItem(mpBackwardArrowPanel)->GetSize();
        int origin_y = panel_size.y/2;
        int origin_x = panel_size.x*margin_x_dir;

        dcBACK.SetBrush(wxBrush(wxColour(207,239,235))); // filling,
        dcBACK.SetPen( wxNullPen );
        wxPoint point_list [] = {wxPoint(0,0),
                                 wxPoint((1.0 - 2*margin_x_dir)*panel_size.x,-0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                 wxPoint((1.0 - 2*margin_x_dir)*panel_size.x, 0.5*(1.0-2.0*margin_y_dir)*panel_size.y)};
        dcBACK.DrawPolygon(3, point_list, origin_x, origin_y);
    }
    else if (generating_id == ID_FORWARD_BUTTON)
    {
        wxPaintDC dcFOR(mpForwardArrowPanel);
        wxSize panel_size = mpSizerForArrows->GetItem(mpForwardArrowPanel)->GetSize();
        int origin_y = panel_size.y/2;
        int origin_x = panel_size.x*margin_x_dir;

        dcFOR.SetBrush(wxBrush(wxColour(207,239,235))); // filling,
        dcFOR.SetPen( wxNullPen );
        wxPoint point_list [] = {wxPoint(0,0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                 wxPoint(0,-0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                 wxPoint((1.0 - 2*margin_x_dir)*panel_size.x, 0)};
        dcFOR.DrawPolygon(3, point_list, origin_x, origin_y);
    }
    else if (generating_id == ID_FORWARD_MORE_BUTTON)
    {
        wxPaintDC dcFM(mpForwardArrowPanelMore);
        wxSize panel_size = mpSizerForArrows->GetItem(mpForwardArrowPanelMore)->GetSize();
        int origin_y = panel_size.y/2;
        int origin_x = panel_size.x*margin_x_dir;

        dcFM.SetBrush(wxBrush(wxColour(207,239,235))); // filling,
        dcFM.SetPen( wxNullPen );
        wxPoint point_list [] = {wxPoint(0,0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                 wxPoint(0,-0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                 wxPoint((1.0 - 2*margin_x_dir)*panel_size.x, 0)};
        wxPoint point_list_2 [] = {wxPoint(double_arrow_offset*(1.0-2*margin_x_dir)*panel_size.x,0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                   wxPoint(double_arrow_offset*(1.0-2*margin_x_dir)*panel_size.x,-0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                   wxPoint((1.0+double_arrow_offset)*(1.0 - 2*margin_x_dir)*panel_size.x, 0)};
        dcFM.DrawPolygon(3, point_list, origin_x, origin_y);
        dcFM.DrawPolygon(3, point_list_2, origin_x, origin_y);
    }
    else if ( generating_id == ID_FORWARD_END_BUTTON)
    {
        wxPaintDC dcFE(mpForwardArrowPanelEnd);
        wxSize panel_size = mpSizerForArrows->GetItem(mpForwardArrowPanelEnd)->GetSize();
        int origin_y = panel_size.y/2;
        int origin_x = panel_size.x*margin_x_dir;

        dcFE.SetBrush(wxBrush(wxColour(207,239,235))); // filling,
        dcFE.SetPen( wxNullPen );
        wxPoint point_list [] = {wxPoint(0,0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                 wxPoint(0,-0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                 wxPoint((1.0 - 2*margin_x_dir)*panel_size.x, 0)};
        dcFE.DrawPolygon(3, point_list, origin_x, origin_y);

        dcFE.SetPen( wxPen( wxColor(207,239,235), 2 ) ); // 2-pixels-thick outline
        dcFE.DrawLine((1.0 - margin_x_dir)*panel_size.x, margin_y_dir*panel_size.y,
                      (1.0 - margin_x_dir)*panel_size.x, (1.0-margin_y_dir)*panel_size.y);
    }

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

	if (mpAllSquares[square_index]->IsHighlightable() == true)
	{
	    // draw a rectangle
	    dc.SetBrush(wxNullBrush); // no filling
	    dc.SetPen( wxPen( wxColor(155,10,10), 5 ) ); // 5-pixels-thick outline
	    wxSize win_size =  mSquarePanels[square_index]->GetClientSize();
	    dc.DrawRectangle( 0, 0, win_size.x, win_size.y );
	}
    mpAllSquares[square_index]->SetAsToBeHighlightable(false);
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

    //Here we figure out what we need to highlight ON THE BOARD!
    unsigned index_of_last_played_move = mpChessBoard->GetIndexInMoveListOfCurrentMoveJustPlayed();
    if (index_of_last_played_move <= mpChessBoard->GetGame()->GetMoveList().size() &&
        index_of_last_played_move > 0)
    {
        ClearCurrentHighlighting();
        slach::Move last_move_played = mpChessBoard->GetGame()->GetMoveList()[index_of_last_played_move-1];
        assert(last_move_played.GetDestination() != NULL);
        assert(last_move_played.GetOrigin() != NULL);

        unsigned source_index;
        unsigned destination_index;
        if (mPerspectiveIsFromWhite == true)
        {
            destination_index = last_move_played.GetDestination()->GetIndexFromTopLeft();
            source_index = last_move_played.GetOrigin()->GetIndexFromTopLeft();
        }
        else
        {
            destination_index = last_move_played.GetDestination()->GetIndexFromBottomRight();
            source_index = last_move_played.GetOrigin()->GetIndexFromBottomRight();
        }
        mpAllSquares[source_index]->SetAsToBeHighlightable(true);//paint event activated at next line
        mSquarePanels[source_index]->Refresh();
        mpAllSquares[destination_index]->SetAsToBeHighlightable(true);//paint event activated at next line
        mSquarePanels[destination_index]->Refresh();
    }


    DoCommunicateTheCurrentPositionForEngine();
}

void slach_gui::ChessBoardPanel::DoCommunicateTheCurrentPositionForEngine()
{
	//engine is driven only by events on main board
    if ( (mIamTheMainBoard == true) && GetGrandParent() != NULL)
    {
    	(static_cast<MainFrame*> (GetGrandParent()))->UpdateChessPositionForEngine(mpChessBoard->GetCurrentPosition());
    }
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
        wxString file(mpAllSquares[squareIndex]->GetFileAsString());
        wxString rank(mpAllSquares[squareIndex]->GetRankAsString());
        wxString to_print;
        if (file == "0")
        {
            to_print = rank;
        }
        else
        {
            to_print = file;
        }
        dc.SetFont( wxFont(wxFontInfo(15).FaceName("Helvetica").Bold()) );
        dc.SetTextForeground ( wxColour (200, 220, 220) );
        wxSize text_size = dc.GetTextExtent(to_print);

        int width = mSquarePanels[squareIndex]->GetClientSize().GetWidth();
        int height = mSquarePanels[squareIndex]->GetClientSize().GetHeight();
        int xcoord = (width - text_size.x)/2;
        int ycoord = (height - text_size.y)/2;

        dc.DrawText(to_print,xcoord,ycoord);
    }
}

slach::ChessBoard* slach_gui::ChessBoardPanel::GetChessBoard()
{
    return mpChessBoard;
}
