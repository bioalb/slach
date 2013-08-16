#ifndef _ChessBoardPANEL_HPP_
#define _ChessBoardPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <vector>
#include "ChessBoardWithBorders.hpp"

namespace slach_gui
{

class ChessBoardPanel : public wxPanel
{

private:

    void PaintOnBorder(wxPaintDC& dc, unsigned squareIndex);
    void PaintPiece(wxPaintDC& dc, unsigned squareIndex);
    void PaintBackground(wxPaintDC& dc, unsigned squareIndex);

    std::string mDestinationFile;
    std::string mDestinationRank;
    std::string mOriginFile;
    std::string mOriginRank;

    std::string mPngPieceDirectory;
    std::string mPngBackgroundDirectory;

    /**
     * Stores pointers of svgdocs corresponding to
     * the pieces
     */
    std::vector<wxImage> mPieceImages;
    std::vector<wxPanel* > mSquarePanels;
    wxFlexGridSizer* mpGridSizer;
    slach::ChessBoardWithBorders* mpChessBoardWithBorders;
    slach::ChessBoard* mpChessBoard;
    wxFrame* mpParent;

    wxIcon mIconNearTheMouse;
    std::vector<slach::Square* > mpSquares;

    bool mDrawPiece;
    /**
     * Helper method to load all the svg pieces
     * this one fills up the member variable vector of mPiecesSvgDocs
     * which contains pointers to wxSVGDocument
     */
    void LoadSvgPieces();


    wxImage DetermineCoordinateToPrint(unsigned squareIndex);

    unsigned mSourceIndex;
public:
    ChessBoardPanel(wxFrame* parent,  wxWindowID id = wxID_ANY, const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);
    ~ChessBoardPanel();

    void PaintOnSquare(wxPaintEvent& event);
    void LeftMouseClick(wxMouseEvent& event);
    void LeftMouseRelease(wxMouseEvent& event);
    std::vector<wxImage > GetPiecesPgns();
    void OnSize(wxSizeEvent& event);

    slach::ChessBoard* GetChessBoard() const;

    wxDECLARE_EVENT_TABLE();
};

}//namespace slach_gui
#endif /* _ChessBoardPANEL_HPP_ */
