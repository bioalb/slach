#include <algorithm>
#include <iostream>
#include <cassert>
#include "ChessboardPanel.hpp"

ChessboardPanel::ChessboardPanel(wxFrame* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,-1, pos,size)
{
    this->SetBackgroundColour(wxT("yellow"));

    mSquares.resize(CHESSBOARD_SIZE);
    mBorderSquares.resize(FILE_SIZE + 2  + RANK_SIZE + 2 + FILE_SIZE + RANK_SIZE);
    mFiles.resize(FILE_SIZE);
    mRanks.resize(RANK_SIZE);

    mFiles[0] = wxT("A");
    mFiles[1] = wxT("B");
    mFiles[2] = wxT("C");
    mFiles[3] = wxT("D");
    mFiles[4] = wxT("E");
    mFiles[5] = wxT("F");
    mFiles[6] = wxT("G");
    mFiles[7] = wxT("H");

    mRanks[0] = wxT("1");
    mRanks[1] = wxT("2");
    mRanks[2] = wxT("3");
    mRanks[3] = wxT("4");
    mRanks[4] = wxT("5");
    mRanks[5] = wxT("6");
    mRanks[6] = wxT("7");
    mRanks[7] = wxT("8");

    mpActualChessboard = new wxPanel(this, wxID_ANY,wxDefaultPosition);

    //now the grid sizer.
    int square_to_border_prop = 3;//proportion between border and square
    mpGridSizer = new wxFlexGridSizer(FILE_SIZE+2,RANK_SIZE+2,0,0);
    mpGridSizer->AddGrowableCol(0,1);//border
    mpGridSizer->AddGrowableCol(1,square_to_border_prop);
    mpGridSizer->AddGrowableCol(2,square_to_border_prop);
    mpGridSizer->AddGrowableCol(3,square_to_border_prop);
    mpGridSizer->AddGrowableCol(4,square_to_border_prop);
    mpGridSizer->AddGrowableCol(5,square_to_border_prop);
    mpGridSizer->AddGrowableCol(6,square_to_border_prop);
    mpGridSizer->AddGrowableCol(7,square_to_border_prop);
    mpGridSizer->AddGrowableCol(8,square_to_border_prop);
    mpGridSizer->AddGrowableCol(9,1);//border

    mpGridSizer->AddGrowableRow(0,1);//border
    mpGridSizer->AddGrowableRow(1,square_to_border_prop);
    mpGridSizer->AddGrowableRow(2,square_to_border_prop);
    mpGridSizer->AddGrowableRow(3,square_to_border_prop);
    mpGridSizer->AddGrowableRow(4,square_to_border_prop);
    mpGridSizer->AddGrowableRow(5,square_to_border_prop);
    mpGridSizer->AddGrowableRow(6,square_to_border_prop);
    mpGridSizer->AddGrowableRow(7,square_to_border_prop);
    mpGridSizer->AddGrowableRow(8,square_to_border_prop);
    mpGridSizer->AddGrowableRow(9,1);//border

    SetupChessboard();
}

void ChessboardPanel::SetupChessboard()
{
    unsigned row=RANK_SIZE;//row counter, start from the max as the loop starts from top left
    unsigned column=0;//column counter
    unsigned square_counter = 0;//counter for the actual squares
    unsigned border_square_counter = 0;//counter for the border squares
    unsigned bw_counter = 0; //at zero, it will start with white (square A8).

    //will create the squares row by row, starting from top left on the screen
    for (unsigned index = 0; index < CHESSBOARD_SIZE_WB; ++index)
    {
        //first row at the top, a border
        if (index < FILE_SIZE+2)
        {
            mBorderSquares[border_square_counter] = new SquarePanel( mpActualChessboard, wxT("red") );
            mBorderSquares[border_square_counter]->SetFile(wxT("BORDER"));
            mBorderSquares[border_square_counter]->SetRank(wxT("BORDER"));
            if (index==0 || index == FILE_SIZE+1)
            {
                //corner squares, no marks on them
                mBorderSquares[border_square_counter]->SetAsBorderSquare(false);
            }
            else
            {
                //top row, put markers
                mBorderSquares[border_square_counter]->SetAsBorderSquare(true);
            }
            mpGridSizer->Add(mBorderSquares[border_square_counter], 0, wxEXPAND);
            border_square_counter++;
        }
        //all the other rows (ranks) before we hit to bottom border
        else if (index < (CHESSBOARD_SIZE_WB - (RANK_SIZE+2)))
        {
            //left border and right borders
            if ( (index%(RANK_SIZE+2)==0) || ((index+1)%(RANK_SIZE+2)==0) )
            {
                mBorderSquares[border_square_counter] = new SquarePanel( mpActualChessboard, wxT("red") );
                mBorderSquares[border_square_counter]->SetFile(wxT("BORDER"));
                mBorderSquares[border_square_counter]->SetRank(wxT("BORDER"));
                mBorderSquares[border_square_counter]->SetAsBorderSquare(true);
                mpGridSizer->Add(mBorderSquares[border_square_counter], 0, wxEXPAND);
                border_square_counter++;
            }
            //the actual chessboard
            else
            {
                assert(square_counter<CHESSBOARD_SIZE);
                if (square_counter%RANK_SIZE==0)
                {
                    bw_counter++;//trick the counter, end of a row and beginning of new one have same colour
                    row--;
                    column=0;
                }
                if (bw_counter%2==0)
                {
                    mSquares[square_counter] = new SquarePanel( mpActualChessboard, wxT("black") );
                }
                else
                {
                    mSquares[square_counter] = new SquarePanel( mpActualChessboard, wxT("white") );
                }
                assert(column<8);
                assert(row<8);
                mSquares[square_counter]->SetFile(mFiles[column]);
                mSquares[square_counter]->SetRank(mRanks[row]);
                mSquares[square_counter]->Show();

                mpGridSizer->Add(mSquares[square_counter], 0, wxEXPAND);

                square_counter++;
                column++;
                bw_counter++;
            }
        }
        //last row at the bottom, a border
        else
        {
            mBorderSquares[border_square_counter] = new SquarePanel( mpActualChessboard, wxT("red") );
            mBorderSquares[border_square_counter]->SetFile(wxT("BORDER"));
            mBorderSquares[border_square_counter]->SetRank(wxT("BORDER"));
            mBorderSquares[border_square_counter]->SetAsBorderSquare(true);
            mpGridSizer->Add(mBorderSquares[border_square_counter], 0, wxEXPAND);
            border_square_counter++;
        }
    }
    mpActualChessboard->SetSizer(mpGridSizer, false);

}

ChessboardPanel::~ChessboardPanel()
{
    for (unsigned i = 0; i < 64; ++i)
    {
        delete mSquares[i];
    }
    delete mpActualChessboard;
}

void ChessboardPanel::OnSize(wxSizeEvent& event)
{
    Refresh();

    //figure out the new dimensions
    wxSize chessboard_panel_size = this->GetSize();
    int panel_x = chessboard_panel_size.GetWidth();
    int panel_y = chessboard_panel_size.GetHeight();
    int min_size;

    //which side is longer...
    wxPoint central_point;
    if (panel_x > panel_y)
    {
        min_size=panel_y;
        central_point.x = (panel_x-min_size)/2;
        central_point.y = 0;
    }
    else
    {
        min_size=panel_x;
        central_point.x = 0;
        central_point.y = (panel_y-min_size)/2;
    }
    //...now resize the chess board accordingly
    wxSize chessboard_size(min_size,min_size);
    mpActualChessboard->SetSize(chessboard_size);
    //and center it
    mpActualChessboard->SetPosition(central_point);
    mpGridSizer->SetMinSize(chessboard_size);

    //skip the event.
    event.Skip();
}

BEGIN_EVENT_TABLE(ChessboardPanel, wxPanel)
    EVT_SIZE(ChessboardPanel::OnSize)
END_EVENT_TABLE()
