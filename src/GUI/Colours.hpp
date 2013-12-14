#ifndef _COLOURS_HPP_
#define _COLOURS_HPP_
#include <wx/wx.h>

namespace slach_gui
{

/**
 * A singleton class to store all the colours information
 * It makes available one instance of itself and all the colours.
 */
class Colours
{

public :

    /**
     * The instance to be used toa ccess the class
     */
    static Colours* Instance();
    /**Background colour of the light squares*/
    wxColour mLightSquare;
    /**Background colour of the dark squares*/
    wxColour mDarkSquare;
    /**Background colour of the border squares*/
    wxColour mChessboardBorder;
    /**Background colour of the arrows*/
    wxColour mArrowBackground;
    /**colour of the text for the palyer names*/
    wxColour mPlayerName;

    /**Sets the default colours*/
    void SetDefaultColours();

private :

    /**Private default constructor. It calls SetDefaultColours()*/
    Colours();
    /**Private default destructor*/
    ~Colours();
    /**Private copy constructor, does nothing*/
    Colours(Colours const&);

    /**cache for the instancxe to this class*/
    static Colours* mpInstance;
};
}//namespace slach_gui
#endif
