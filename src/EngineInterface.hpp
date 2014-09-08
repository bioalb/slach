#ifndef ENGINEINTERFACE_HPP_
#define ENGINEINTERFACE_HPP_

#include <limits>
#include <thread>
#include <mutex>
#include <atomic>
#include <ios>
#include <fstream>
#include <sstream>
#include <streambuf>

#include "Game.hpp"
#include "ChessBoard.hpp"


class TestEngineInterface;//forward declaration, for testing and accessing protected methods from the test class
class TestEngineStrings;

namespace slach
{

struct InfoInEngineLine
{
public :
	int mDepth;
	double mScore;
	std::string mMoveList;
	std::string mRootMove;
	bool mValid;
	bool mMateLine;
	bool mCheckMate;

	InfoInEngineLine() :
		mDepth(0),
		mScore(0.0),
		mMoveList(""),
		mRootMove(""),
		mValid(false), //defaults to false!
		mMateLine(false),
		mCheckMate(false)
	{}
};

/**
 * A class that serves as a communicator with one or more engines.
 */
class EngineInterface
{
    friend class ::TestEngineInterface;// for testing
    friend class ::TestEngineStrings;// for testing

  private:

    /**this is the number of different lines to be shown. it is MultiPV in stockfish, defaults to 1*/
    unsigned mNumberOfLinesToBeShown;

    std::shared_ptr<std::thread> mpEngineThread;

    std::string mEngineString;

    std::stringbuf *mEngineOutputBuffer;
    std::streambuf *mBackupCoutBuf;


    void IssueCommandtoStockfish(const std::string& command);
    void DoIssueCommand(const std::string& command);
    void InitEngine();

  protected:
    std::string mCachedFenPositiontoBeanalysed;

    /**Cache the latest depths of engine output when we tried to collect it, as big as mNumberOfLinesToBeShown*/
    std::vector<int> mLatestDepths;

    /**Cache the latest scores of engine output when we tried to collect it,as big as mNumberOfLinesToBeShown*/
    std::vector<double> mLatestScores;

    /**Cache the latest suggested lines of engine output when we tried to collect it, as big as mNumberOfLinesToBeShown*/
    std::vector<std::string> mLatestLines;
    std::vector<std::string> mLatestRootMoves;

    /**we create a chessboard as we need squares with pieces to translate engine moves to SAN*/
    ChessBoard* mpChessBoard;

    /**same as chessboard, we store the pointers to squares*/
    std::vector<Square*> mpSquares;

    /**
     * This one parses a single line of the engine output
     *
     * @param stockfishLine (input) the output of the engine we wish to analyze, a single line
     * @return the information contained in this line
     */
    InfoInEngineLine ParseALineofStockfishOutput(const std::string& stockfishLine);

    void ParseWholeEngineOutput(const std::string& rawOutput);

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
     * This method initializes a new thread that will run the engine.
     */
    void LaunchEngine();

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

    void QuitEngine();

    /**
     * When called, this method will parse the engine output and return
     * you a vector of strings, as big as the number of lines to be shown (mNumberOfLinesToBeShown)
     * with a polished version of the lines, if different from the preivous time you called this
     */
    std::vector<std::string> GetLatestEngineOutput();


    /**
     * access to best move, score and depth
     * These variables is assigned meaningful values upon calling GetLatestEngineOutput()
     *
     * @param bestScore (output) will contain the best score
     * @param depth (output) will contain the depth corresponding to the best score
     * @param bestMove (output) will contain the best move
     */
    void GetLatestBestScoreAndDepth(double& bestScore, int& depth, std::string& bestMove) const;

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
