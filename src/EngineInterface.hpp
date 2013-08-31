#ifndef ENGINEINTERFACE_HPP_
#define ENGINEINTERFACE_HPP_

#include <limits>
#include "position.h"//within stockfish
#include "Game.hpp"
#include "Position.hpp"

class TestEngineInterface;//forward declaration, for testing and accessing protected methods from the test class

namespace slach
{
/**
 * A class that serves as a communicator with one or more engines.
 */
class EngineInterface
{
    friend class ::TestEngineInterface;// for testing

  private:
    /**Cache for a FEN string*/
    std::string mFenString;

    /**Cache the latest depth of engine output when we tried to collect it*/
    int mLatestDepth;

    /**Cache the latest score of engine output when we tried to collect it*/
    double mLatestScore;

    /**Cache the latest suggested line of engine output when we tried to collect it*/
    std::string mLatestLine;

    /**pointer to a position object within the stockfish engine*/
    stockfish::Position* mpStockfishPosition;

  protected:

    /**
     * Helper method to convert a Square object within slach
     * to one within the stockfish engine
     *
     * @param pSquare a pointer to the square we wish to convert.
     * @return The corresponding square of the correct type defined by stocksfish (enum)
     */
    stockfish::Square ConvertSquareToStockfish(const Square* pSquare) const;

    /**
     * This one parses the engine output looking for the LATEST depth analyzed,
     * the latest score and the latest line.
     *
     * @param engineOutput (input) the output of the engine we wish to analyze
     * @param depth (output) will contain the latest depth analyzed by the engine
     * @param score (output)  will contain the altest score analyzed by the engine
     * @param line (output) will contain the computer suggested line a s a string
     */
    void ParseEngineOutput(const std::string& engineOutput, int& depth, double& score, std::string& line);

  public :

    EngineInterface();
    ~EngineInterface();

    /**
     * This method triggers the engine to analyse the position and outputs to std::output the engine analysis.
     * It thinks for the number of seconds specified by the parameter "seconds"
     *
     * @param pPosition A pointer to the position to analyise
     * @param seconds the number of seconds we want the engine to analyse the position for. Iif no parameter is specified,
     *        the engine will think for an infinite time
     */
    void StartAnalsyingPosition(Position* pPosition, double seconds = std::numeric_limits<double>::max());

    void StopEngine();

    std::string GetLatestEngineOutput();
};

}//namespace slach
#endif
