#ifndef _ACTUALBOARDPANEL_HPP_
#define _ACTUALBOARDPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <SVGDocument.h>
#include <vector>
#include "SquarePanel.hpp"
#include "../ChessBoardWithBorders.hpp"

namespace slach_gui
{

class ActualBoardPanel : public wxPanel
{

private:
    std::string mDestinationFile;
    std::string mDestinationRank;
    std::string mOriginFile;
    std::string mOriginRank;

    std::string mSvgPieceDirectory;
    std::string mSvgBackgroundDirectory;

    /**
     * Stores pointers of svgdocs corresponding to
     * the pieces
     */
    std::vector<wxSVGDocument*> mPiecesSvgDocs;
    std::vector<SquarePanel* > mSquarePanels;
    wxFlexGridSizer* mpGridSizer;
    slach::ChessBoardWithBorders* mpChessBoardWithBorders;
    slach::ChessBoard* mpChessBoard;
    wxPanel* mpParent;
    SquarePanel* mpOriginSquarePanel;
    SquarePanel* mpDestinationSquarePanel;
    /**
     * Helper method to load all the svg pieces
     * this one fills up the member variable vector of mPiecesSvgDocs
     * which contains pointers to wxSVGDocument
     */
    void LoadSvgPieces();
public:
    ActualBoardPanel(wxPanel* parent,  wxWindowID id = wxID_ANY, const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);
    ~ActualBoardPanel();
    void SetDestinationSquare(SquarePanel* pDestinationSquare);
    void SetOriginSquare(SquarePanel* pOrignSquare);
    SquarePanel* GetDestinationSquare();
    SquarePanel* GetOriginSquare();

    void SetupChessboard();

    std::vector<SquarePanel* > GetSquarePanels();
    std::vector<wxSVGDocument* > GetPiecesSvgDocs();
    void OnSize(wxSizeEvent& event);

    DECLARE_EVENT_TABLE()
};

}//namespace slach_gui
#endif /* _ACTUALBOARDPANEL_HPP_ */
