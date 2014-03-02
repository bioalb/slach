#include "Colours.hpp"

slach_gui::Colours* slach_gui::Colours::mpInstance = NULL;

slach_gui::Colours* slach_gui::Colours::Instance()
{
    if (!mpInstance) mpInstance = new Colours;//only one allowed

    return mpInstance;
}

slach_gui::Colours::Colours()
{
    SetDefaultColours();
}
slach_gui::Colours::~Colours()
{
}

slach_gui::Colours::Colours(Colours const&)
{
}

void slach_gui::Colours::SetDefaultColours()
{
   mLightSquare = wxColour(235,241,246);
   mDarkSquare = wxColour(32,107,129);
   mChessboardBorder = wxColour(35,87,102);
   mBoardCoordinate = wxColour (200, 220, 220);
   mArrowBackground = wxColour(35,87,102);
   mArrowButton = wxColour(207,239,235);
   mArrowBackgroundMouseOn = wxColour(35,1,1);
   mPlayerName = wxColour(32,7,129);
   mHighlightedMove = wxColour(204,229,255);
   mEngineText = wxColour(0, 0, 0);
   mBottomPanelBackground = wxColour(35,87,102);//same as borders...
   mScoreBoxBackground = wxColour(35,87,102);

   mFlipViewBoxBackground = wxColour (200, 220, 220) ;
   mFlipViewArrows = wxColour(35,87,102);


}
