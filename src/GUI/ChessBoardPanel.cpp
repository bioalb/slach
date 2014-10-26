#include <algorithm>
#include <iostream>
#include <cassert>
#include <wx/mstream.h>
#include <wx/wfstream.h>
#include <wx/filedlg.h>
#include <wx/txtstrm.h>
#include "SlachTypes.hpp"
#include "Colours.hpp"
#include "HelperGlobalFunctions.hpp"
#include "ChessBoardPanel.hpp"
#include "MainFrame.hpp"


slach_gui::ChessBoardPanel::ChessBoardPanel(wxPanel* parent, wxWindowID WXUNUSED(id), const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size),
      mpParent(parent),
      mIamTheMainBoard(true),
      mPngPieceDirectory("src/GUI/bitmaps/pieces/png/"),
      mpChessBoardWithBorders ( std::make_shared<slach::ChessBoardWithBorders>() ),
      mpChessBoard(nullptr),
      mpBoardContainer(new wxPanel(this,wxID_ANY)),
      mNumberOfMovesFastForward(5u),
      mpBoardGridSizer ( new wxFlexGridSizer(slach::gBoardRowSize+3,slach::gBoardColumnSize+2,0,0) ),
      mDrawPiece(true),
      mGameIsLoaded(false),
      mPerspectiveIsFromWhite(true),
      mSourceIndex(0u),
      mDestinationIndex(0u)
{
    this->SetBackgroundColour(*wxWHITE);

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
    mpBoardGridSizer->AddGrowableRow(10,1);//arrows

    LoadBoardImages();

    mpChessBoard = mpChessBoardWithBorders->GetPlayableChessBoard();
    mpChessBoard->SetupInitialChessPosition();
    DoCommunicateTheCurrentPositionForEngine();
    mpAllSquares = mpChessBoardWithBorders->GetSquares();

    assert(mpAllSquares.size() == mSquarePanels.size());

    for (unsigned i = 0; i < mpAllSquares.size(); ++i)
    {
        mSquarePanels[i] = new wxPanel( mpBoardContainer, /*ID*/ (int) i );
        mpBoardGridSizer->Add(mSquarePanels[i], 0, wxEXPAND);

        if (mpAllSquares[i]->IsSquareForArrows() == false)
        {
			//bind the paint event
			mSquarePanels[i]->Bind(wxEVT_PAINT, &ChessBoardPanel::PaintOnSquare, this);
			if (mpAllSquares[i]->IsPlayableSquare() == true)
			{
				mSquarePanels[i]->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::LeftMouseClick, this);
				mSquarePanels[i]->Bind(wxEVT_MOTION, &ChessBoardPanel::LeftMouseClick, this);
				mSquarePanels[i]->Bind(wxEVT_LEFT_UP, &ChessBoardPanel::LeftMouseRelease, this);
			}
			if (mpAllSquares[i]->IstheBottomRightCorner())
			{
				mSquarePanels[i]->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::FlipView, this);
				mSquarePanels[i] -> SetBackgroundColour(Colours::Instance()->mFlipViewBoxBackground);
			}
        }
        else //arrows
        {
        	mSquarePanels[i]->Bind(wxEVT_PAINT,&ChessBoardPanel::PaintArrows, this);
        	mSquarePanels[i]->Bind(wxEVT_LEFT_DOWN, &ChessBoardPanel::ArrowButtonMovement, this);
            //Bind the colouring of the arrows as mouse enters or leave
        	mSquarePanels[i]->Bind(wxEVT_ENTER_WINDOW, &ChessBoardPanel::OnMouseEnteringArrowPanel, this);
        	mSquarePanels[i]->Bind(wxEVT_LEAVE_WINDOW, &ChessBoardPanel::OnMouseLeavingArrowPanel, this);
        	mSquarePanels[i]->SetBackgroundColour (Colours::Instance()->mArrowBackground);
        }
    }
    mpBoardContainer->SetSizer(mpBoardGridSizer);
    this->Bind(wxEVT_SIZE, &ChessBoardPanel::OnSize, this);
}

slach_gui::ChessBoardPanel::~ChessBoardPanel()
{

}

void slach_gui::ChessBoardPanel::SetAsMainBoard(bool flag)
{
    mIamTheMainBoard = flag;
}

void slach_gui::ChessBoardPanel::FlipView (wxMouseEvent& event)
{
    DoFlipView();
    event.Skip();
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
    this->Refresh();
}

bool slach_gui::ChessBoardPanel::IsItFromWhitePerspective() const
{
    return mPerspectiveIsFromWhite;
}

void slach_gui::ChessBoardPanel::LeftMouseClick(wxMouseEvent& event)
{
	int square_index_int = (static_cast<wxWindow*> (event.GetEventObject()))->GetId();
	//when one clicks on a square, we assume drag starts
	//here we manually delete the piece from origin and "move" the piece to be the cursor
	if (event.LeftDown())
	{
		//prepare the cursor
		wxImage curs_image = GetImageFromPiece(mpAllSquares[square_index_int]->GetPieceOnThisSquare());
		int width = mSquarePanels[square_index_int]->GetClientSize().GetWidth();
		int height = mSquarePanels[square_index_int]->GetClientSize().GetHeight();
		curs_image.Rescale(width, height);
		curs_image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_X, width/2);
		curs_image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_Y, height/2);
		wxCursor piece_cursor( curs_image );

		wxSetCursor(piece_cursor);
		mSourceIndex = (unsigned) square_index_int;
		//important, remove piece while dragging
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
	this->Refresh();
    wxSize total_panel_size = this->GetSize();
    int panel_x = total_panel_size.GetWidth();
    int panel_y = total_panel_size.GetHeight();

    int final_size_x, final_size_y;
    wxPoint cb_top_left(0,0);
	auto height_of_arrow_row = 0;
    //which side is longer...
    if (panel_x > panel_y)
    {
    	if (!mpBoardGridSizer->GetRowHeights().IsEmpty()) height_of_arrow_row = mpBoardGridSizer->GetRowHeights().Last();
    	final_size_x = panel_y - height_of_arrow_row;
    	final_size_y = panel_y ;
    }
    else //vertical longer than horizontal
    {
    	if (!mpBoardGridSizer->GetRowHeights().IsEmpty())  height_of_arrow_row = mpBoardGridSizer->GetRowHeights().Last();
    	final_size_x = panel_x;
    	final_size_y = panel_x + height_of_arrow_row;
    }

    //...now resize the chess board accordingly
    mpBoardContainer->SetSize(cb_top_left.x,cb_top_left.y, final_size_x, final_size_y);

    event.Skip();
}

void slach_gui::ChessBoardPanel::DoAdvanceOneMove()
{
    if (mpChessBoard->ResetToNextMove())
    {
		std::string fen_to_set = mpChessBoard->GetCurrentFenPosition();
		if (mIamTheMainBoard == true)
		{
			(static_cast<CentralPanel*> (mpParent))->HighlightNextMove();
		}
		DrawAndSetFenPositionOnBoard(fen_to_set);
    }
}

void slach_gui::ChessBoardPanel::DoAdvanceSeveralMoves()
{
	bool ok = true;
	for (unsigned i = 0; i < mNumberOfMovesFastForward; ++i)
	{
		ok = mpChessBoard->ResetToNextMove();
		if (ok == false) break;
	}

	if (ok)
	{
		std::string fen_to_set = mpChessBoard->GetCurrentFenPosition();
		if (mIamTheMainBoard == true)
		{
			(static_cast<CentralPanel*> (mpParent))->HighlightSeveralMovesAhead();
		}
		DrawAndSetFenPositionOnBoard(fen_to_set);
	}
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

void slach_gui::ChessBoardPanel::PaintArrows(wxPaintEvent& event)
{
    int generating_id = ((wxPanel*) event.GetEventObject())->GetId();

    double margin_x_dir = 0.3;//fractional margin between arrow and border of panel, x direction
    double margin_y_dir = 0.1;//fractional margin between arrow and border of panel, y direction
    double double_arrow_offset = 0.5;//fractional offset for double arrows
    if (generating_id == ID_BACKWARD_END_BUTTON)
    {
        wxPaintDC dcBE(mSquarePanels[ID_BACKWARD_END_BUTTON]);
        wxSize panel_size = mpBoardGridSizer->GetItem(mSquarePanels[ID_BACKWARD_END_BUTTON])->GetSize();
        int origin_y = panel_size.y*0.5;
        int origin_x = panel_size.x*margin_x_dir;

        dcBE.SetBrush(wxBrush(Colours::Instance()->mArrowButton)); // filling,
        dcBE.SetPen( wxNullPen );
        wxPoint point_list [] = {wxPoint(0,0),
                                 wxPoint((1.0 - 2*margin_x_dir)*panel_size.x,-0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                 wxPoint((1.0 - 2*margin_x_dir)*panel_size.x, 0.5*(1.0-2.0*margin_y_dir)*panel_size.y)};
        dcBE.DrawPolygon(3, point_list, origin_x, origin_y);

        dcBE.SetPen( wxPen( Colours::Instance()->mArrowButton, 2 ) ); // 2-pixels-thick outline
        dcBE.DrawLine(origin_x, margin_y_dir*panel_size.y,
                      origin_x, (1.0-margin_y_dir)*panel_size.y);
    }
    else if (generating_id == ID_BACKWARD_MORE_BUTTON)
    {
        wxPaintDC dcBM(mSquarePanels[ID_BACKWARD_MORE_BUTTON]);
        wxSize panel_size = mpBoardGridSizer->GetItem(mSquarePanels[ID_BACKWARD_MORE_BUTTON])->GetSize();
        int origin_y = panel_size.y/2;
        int origin_x = panel_size.x*margin_x_dir;

        dcBM.SetBrush(wxBrush(Colours::Instance()->mArrowButton)); // filling,
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
        wxPaintDC dcBACK(mSquarePanels[ID_BACKWARD_BUTTON]);
        wxSize panel_size = mpBoardGridSizer->GetItem(mSquarePanels[ID_BACKWARD_BUTTON])->GetSize();
        int origin_y = panel_size.y/2;
        int origin_x = panel_size.x*margin_x_dir;

        dcBACK.SetBrush(wxBrush(Colours::Instance()->mArrowButton)); // filling,
        dcBACK.SetPen( wxNullPen );
        wxPoint point_list [] = {wxPoint(0,0),
                                 wxPoint((1.0 - 2*margin_x_dir)*panel_size.x,-0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                 wxPoint((1.0 - 2*margin_x_dir)*panel_size.x, 0.5*(1.0-2.0*margin_y_dir)*panel_size.y)};
        dcBACK.DrawPolygon(3, point_list, origin_x, origin_y);
    }
    else if (generating_id == ID_FORWARD_BUTTON)
    {
        wxPaintDC dcFOR(mSquarePanels[ID_FORWARD_BUTTON]);
        wxSize panel_size = mpBoardGridSizer->GetItem(mSquarePanels[ID_FORWARD_BUTTON])->GetSize();
        int origin_y = panel_size.y/2;
        int origin_x = panel_size.x*margin_x_dir;

        dcFOR.SetBrush(wxBrush(Colours::Instance()->mArrowButton)); // filling,
        dcFOR.SetPen( wxNullPen );
        wxPoint point_list [] = {wxPoint(0,0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                 wxPoint(0,-0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                 wxPoint((1.0 - 2*margin_x_dir)*panel_size.x, 0)};
        dcFOR.DrawPolygon(3, point_list, origin_x, origin_y);
    }
    else if (generating_id == ID_FORWARD_MORE_BUTTON)
    {
        wxPaintDC dcFM(mSquarePanels[ID_FORWARD_MORE_BUTTON]);
        wxSize panel_size = mpBoardGridSizer->GetItem(mSquarePanels[ID_FORWARD_MORE_BUTTON])->GetSize();
        int origin_y = panel_size.y/2;
        int origin_x = panel_size.x*margin_x_dir;

        dcFM.SetBrush(wxBrush(Colours::Instance()->mArrowButton)); // filling,
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
        wxPaintDC dcFE(mSquarePanels[ID_FORWARD_END_BUTTON]);
        wxSize panel_size = mpBoardGridSizer->GetItem(mSquarePanels[ID_FORWARD_END_BUTTON])->GetSize();
        int origin_y = panel_size.y/2;
        int origin_x = panel_size.x*margin_x_dir;

        dcFE.SetBrush(wxBrush(Colours::Instance()->mArrowButton)); // filling,
        dcFE.SetPen( wxNullPen );
        wxPoint point_list [] = {wxPoint(0,0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                 wxPoint(0,-0.5*(1.0-2.0*margin_y_dir)*panel_size.y),
                                 wxPoint((1.0 - 2*margin_x_dir)*panel_size.x, 0)};
        dcFE.DrawPolygon(3, point_list, origin_x, origin_y);

        dcFE.SetPen( wxPen( Colours::Instance()->mArrowButton, 2 ) ); // 2-pixels-thick outline
        dcFE.DrawLine((1.0 - margin_x_dir)*panel_size.x, margin_y_dir*panel_size.y,
                      (1.0 - margin_x_dir)*panel_size.x, (1.0-margin_y_dir)*panel_size.y);
    }

}

void slach_gui::ChessBoardPanel::OnMouseEnteringArrowPanel(wxMouseEvent& event)
{
    int generating_id = ((wxPanel*) event.GetEventObject())->GetId();
    assert(generating_id < (int) mSquarePanels.size());
    mSquarePanels[generating_id]->SetBackgroundColour (Colours::Instance()->mArrowBackgroundMouseOn);
}
void slach_gui::ChessBoardPanel::OnMouseLeavingArrowPanel(wxMouseEvent& event)
{
    int generating_id = ((wxPanel*) event.GetEventObject())->GetId();
    assert(generating_id< (int) mSquarePanels.size());
    mSquarePanels[generating_id]->SetBackgroundColour (Colours::Instance()->mArrowBackground);
}

void slach_gui::ChessBoardPanel::PaintOnSquare(wxPaintEvent& event)
{
	int square_index_int = (static_cast<wxWindow*> (event.GetEventObject()))->GetId();
	unsigned square_index = (unsigned) square_index_int;

	wxPaintDC dc(mSquarePanels[square_index]);
    PaintBackground(dc, square_index);
    if (mDrawPiece == true)
    {
        PaintPiece(dc, square_index);
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
	event .Skip();
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
        assert(last_move_played.GetDestination() != nullptr);
        assert(last_move_played.GetOrigin() != nullptr);

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
    if ( (mIamTheMainBoard == true) && GetGrandParent() != nullptr)
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
	mPieceImages.resize(13u);

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
}

void slach_gui::ChessBoardPanel::PaintPiece(wxPaintDC& dc, unsigned squareIndex)
{
	assert(mPieceImages.size() == 13u);
    slach::PieceType piece = mpAllSquares[squareIndex]->GetPieceOnThisSquare();
    wxImage piece_image = GetImageFromPiece(piece);

    int width = mSquarePanels[squareIndex]->GetClientSize().GetWidth();
    int height = mSquarePanels[squareIndex]->GetClientSize().GetHeight();
    piece_image.Rescale(width, height);
    //now really draw the rendered image;
    dc.DrawBitmap( piece_image, 0, 0, true );
}

void slach_gui::ChessBoardPanel::PaintBackground(wxPaintDC& dc, unsigned squareIndex)
{
    if ( (mpAllSquares[squareIndex]->IsDarkSquare() == true) && (mpAllSquares[squareIndex]->IsBorderSquare() == false))
    {
        mSquarePanels[squareIndex]->SetBackgroundColour(Colours::Instance()->mDarkSquare);
    }
    if ( (mpAllSquares[squareIndex]->IsLightSquare() == true) && (mpAllSquares[squareIndex]->IsBorderSquare() == false))
    {
        mSquarePanels[squareIndex]->SetBackgroundColour(Colours::Instance()->mLightSquare);
    }
    if (mpAllSquares[squareIndex]->IsBorderSquare())
    {
        if (mpAllSquares[squareIndex]->IstheBottomRightCorner())
        {
            mSquarePanels[squareIndex] -> SetBackgroundColour(Colours::Instance()->mFlipViewBoxBackground);
        }
        else
        {
            mSquarePanels[squareIndex]->SetBackgroundColour(Colours::Instance()->mChessboardBorder);
        }
        PaintOnBorder(dc, squareIndex);
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
        dc.SetTextForeground ( Colours::Instance()->mBoardCoordinate );
        wxSize text_size = dc.GetTextExtent(to_print);

        int width = mSquarePanels[squareIndex]->GetClientSize().GetWidth();
        int height = mSquarePanels[squareIndex]->GetClientSize().GetHeight();
        int xcoord = (width - text_size.x)/2;
        int ycoord = (height - text_size.y)/2;

        dc.DrawText(to_print,xcoord,ycoord);
    }

    if ( mpAllSquares[squareIndex]->IsBorderSquare()== true &&
         mpAllSquares[squareIndex]->IsCornerSquare()== true  &&
         mpAllSquares[squareIndex]->IstheBottomRightCorner() == true)
    {
        int panel_width = mSquarePanels[squareIndex]->GetClientSize().GetWidth();
        int panel_height = mSquarePanels[squareIndex]->GetClientSize().GetHeight();

        int vertex_upper_arrow_x = panel_width*0.95;
        int vertex_upper_arrow_y = panel_height*0.4;

        int base_upper_arrow_below_x = vertex_upper_arrow_x*0.75;
        int base_upper_arrow_below_y = vertex_upper_arrow_y;

        int base_upper_arrow_above_x = vertex_upper_arrow_x;
        int base_upper_arrow_above_y = vertex_upper_arrow_y*0.2;

        dc.SetBrush(wxBrush(Colours::Instance()->mFlipViewArrows)); // filling,
        dc.SetPen( wxNullPen );
        wxPoint point_list [] = {wxPoint(vertex_upper_arrow_x,vertex_upper_arrow_y),
                                 wxPoint(base_upper_arrow_below_x,base_upper_arrow_below_y),
                                 wxPoint(base_upper_arrow_above_x,base_upper_arrow_above_y )};
        dc.DrawPolygon(3, point_list, 0, 0 );

        int end_spline_x = (base_upper_arrow_below_x + base_upper_arrow_above_x)/2;
        int end_spline_y = (base_upper_arrow_below_y + base_upper_arrow_above_y)/2;
        int start_spline_x = panel_width*0.2;
        int start_spline_y = vertex_upper_arrow_y;
        int mid_spline_x = (start_spline_x + end_spline_x) / 2;
        int mid_spline_y = vertex_upper_arrow_y/6;

        dc.SetPen( wxPen( Colours::Instance()->mFlipViewArrows, 2 ) ); // 2-pixels-thick outline
        dc.DrawSpline(start_spline_x, start_spline_y, mid_spline_x, mid_spline_y, end_spline_x, end_spline_y);


        int vertex_lower_arrow_x = panel_width*0.2;
        int vertex_lower_arrow_y = panel_height*0.6;

        int base_lower_arrow_below_x = vertex_lower_arrow_x*1;
        int base_lower_arrow_below_y = vertex_lower_arrow_y*1.5;

        int base_lower_arrow_above_x = vertex_lower_arrow_x*2.2;
        int base_lower_arrow_above_y = vertex_lower_arrow_y*1.1;

        dc.SetBrush(wxBrush(Colours::Instance()->mFlipViewArrows)); // filling,
        dc.SetPen( wxNullPen );
        wxPoint point_list_2 [] = {wxPoint(vertex_lower_arrow_x,vertex_lower_arrow_y),
                                 wxPoint(base_lower_arrow_below_x,base_lower_arrow_below_y),
                                 wxPoint(base_lower_arrow_above_x,base_lower_arrow_above_y )};
        dc.DrawPolygon(3, point_list_2, 0, 0 );


        end_spline_x = (base_lower_arrow_below_x + base_lower_arrow_above_x)/2;
        end_spline_y = (base_lower_arrow_below_y + base_lower_arrow_above_y)/2;
        start_spline_x = vertex_upper_arrow_x;
        start_spline_y = vertex_lower_arrow_y;
        mid_spline_x = (start_spline_x + end_spline_x) / 2;
        mid_spline_y = panel_height - vertex_lower_arrow_y/8;

        dc.SetPen( wxPen( Colours::Instance()->mFlipViewArrows, 2 ) ); // 2-pixels-thick outline
        dc.DrawSpline(start_spline_x, start_spline_y, mid_spline_x, mid_spline_y, end_spline_x, end_spline_y);
    }
}

std::shared_ptr<slach::ChessBoard> slach_gui::ChessBoardPanel::GetChessBoard()
{
    return mpChessBoard;
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
