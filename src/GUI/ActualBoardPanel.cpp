#include <algorithm>
#include <iostream>
#include <cassert>
#include "ActualBoardPanel.hpp"
#include "DropTargetPanel.hpp"
#include "ActualBoardPanel.hpp"

ActualBoardPanel::ActualBoardPanel(wxPanel* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent,wxID_ANY, pos,size)
{

}



ActualBoardPanel::~ActualBoardPanel()
{

}

void ActualBoardPanel::SetDestinationSquare(std::string file, std::string rank)
{
    mDestinationFile = file;
    mDestinationRank = rank;
}
void ActualBoardPanel::SetOriginSquare(std::string file, std::string rank)
{
    mOriginFile = file;
    mOriginRank = rank;
}

std::pair<std::string, std::string> ActualBoardPanel::GetDestinationSquare()
{
    return std::make_pair(mDestinationFile,mDestinationRank);

}
std::pair<std::string, std::string> ActualBoardPanel::GetOriginSquare()
{
    return std::make_pair(mOriginFile,mOriginRank);
}

