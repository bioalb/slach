#ifndef _ACTUALBOARDPANEL_HPP_
#define _ACTUALBOARDPANEL_HPP_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <vector>
#include "SquarePanel.hpp"
#include "../ChessBoard.hpp"

class ActualBoardPanel : public wxPanel
{

private:
    std::string mDestinationFile;
    std::string mDestinationRank;
    std::string mOriginFile;
    std::string mOriginRank;


    std::vector<SquarePanel* > mSquarePanels;
    //std::vector<SquarePanelDropTarget* > mpDropTargets;
    wxFlexGridSizer* mpGridSizer;

    ChessBoard* mpChessBoard;
    wxPanel* mpParent;


public:
    ActualBoardPanel(wxPanel* parent,  wxWindowID id = wxID_ANY, const wxPoint& pos= wxDefaultPosition, const wxSize& size= wxDefaultSize);
    ~ActualBoardPanel();
    void SetDestinationSquare(std::string file, std::string rank);
    void SetOriginSquare(std::string file, std::string rank);
    std::pair<std::string, std::string> GetDestinationSquare();
    std::pair<std::string, std::string> GetOriginSquare();

    void SetupChessboard();

    std::vector<SquarePanel* > GetSquarePanels();
    void OnSize(wxSizeEvent& event);

    DECLARE_EVENT_TABLE()
};
#endif /* _ACTUALBOARDPANEL_HPP_ */
