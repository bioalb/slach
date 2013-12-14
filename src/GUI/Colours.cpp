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
   mArrowBackground = wxColour(35,87,102);
   mPlayerName = wxColour(32,7,129);
}
