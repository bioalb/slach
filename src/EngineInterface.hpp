#ifndef ENGINEINTERFACE_HPP_
#define ENGINEINTERFACE_HPP_

#include <limits>
#include "position.h"//within stockfish
#include "Game.hpp"
#include "Position.hpp"
#include "ChessBoard.hpp"

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

    /**this is the number of different lines to be shown. it is MultiPV in stockfish, defaults to 1*/
    unsigned mNumberOfLinesToBeShown;

  protected:
    std::string mCachedFenPositiontoBeanalysed;

    /**Cache the latest depths of engine output when we tried to collect it, as big as mNumberOfLinesToBeShown*/
    std::vector<int> mLatestDepths;

    /**Cache the latest scores of engine output when we tried to collect it,as big as mNumberOfLinesToBeShown*/
    std::vector<double> mLatestScores;

    /**Cache the latest suggested lines of engine output when we tried to collect it, as big as mNumberOfLinesToBeShown*/
    std::vector<std::string> mLatestLines;
    std::vector<std::string> mLatestRootMoves;
    /**pointer to a position object within the stockfish engine*/
    ::Position* mpStockfishPosition;

    /**we create a chessboard as we need squares with pieces to translate engine moves to SAN*/
    ChessBoard* mpChessBoard;

    /**same as chessboard, we store the pointers to squares*/
    std::vector<Square*> mpSquares;

    /**
     * This one parses a single line of the engine output
     *
     * @param stockfishLine (input) the output of the engine we wish to analyze
     * @param depth (output) will contain the  depth analyzed by the engine
     * @param score (output)  will contain the score analyzed by the engine
     * @param move_list (output) will contain the computer suggested line as a string
     * @param rootMove teh first move of the suggested move list
     */
    void ParseALineofStockfishOutput(const std::string& stockfishLine, int & depth, double & score, std::string &  move_list, std::string& rootMove);

    void ParseWholeEngineOutput(const std::string& rawOutput);

    void InitialiseEngine();

  public :
    /**
     * Helper method only used for testing private methods.
     */
    void SetPositionToInternalChessBoard(const std::string& fenPosition);

    /**
     * Constructor
     *
     * @param pChessBoard the chessboard object we wish the engine to interact with.
     */
    EngineInterface();
    ~EngineInterface();

    /**
     * This method triggers the engine to analyse the position and outputs to std::output the engine analysis.
     * It thinks for the number of seconds specified by the parameter "seconds"
     *
     * @param pPosition the position to analyse
     * @param seconds the number of seconds we want the engine to analyse the position for. Iif no parameter is specified,
     *        the engine will think for an infinite time
     */
    void StartAnalsyingPosition(slach::Position* pPosition, double seconds = std::numeric_limits<double>::max());

    void StopEngine();

    /**
     * When called, this method will parse the engine output and return
     * you a vector of strings, as big as the number of lines to be shown (mNumberOfLinesToBeShown)
     * with a polished version of the lines, if different from the preivous time you called this
     */
    std::vector<std::string> GetLatestEngineOutput();


    /**
     * Returns the best score and its corresponding depth in a pair.
     * This variable is assigned meaningful values upon calling GetLatestEngineOutput()
     */
    std::pair<double, int> GetLatestBestScoreAndDepth() const;

    /**
     * Sets the number of line to be shown. It sets the member variable here
     * and also prepares the stockfish option
     *
     * @param num the number of lines to be shown
     */
    void SetNumberOfLinesToBeShown(unsigned num);

    ChessBoard* GetChessBoard()
    {
        return mpChessBoard;
    }

};

}//namespace slach
#endif
