#ifndef UCIStringsManipulator_HPP_
#define UCIStringsManipulator_HPP_

#include "Game.hpp"
#include "ChessBoard.hpp"


class TestUCIStringsManipulator;//forward declaration, for testing and accessing protected methods from the test class

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

	bool operator== (const InfoInEngineLine & comp)
	{
		return ( mRootMove == comp.mRootMove );
	}

	InfoInEngineLine& operator=(const InfoInEngineLine &rhs)
	{
	    // Only do assignment if RHS is a different object from this.
	    if (this != &rhs)
	    {
	    	mDepth = rhs.mDepth;
	    	mScore = rhs.mScore;
	    	mMoveList = rhs.mMoveList;
	    	mValid = rhs.mValid;
	    	mMateLine = rhs.mMateLine;
	    	mCheckMate = rhs.mCheckMate;
	    	mRootMove = rhs.mRootMove;
	    }
	    return *this;
	  }

    bool operator < (const InfoInEngineLine& rhs) const
    {
       return this->mScore < rhs.mScore;

    }
};

/**
 * A helper class with functionalities to parse a UCI output string
 * and obtain nicely formatted lines, scores and other info.
 */
class UCIStringsManipulator
{
    friend class ::TestUCIStringsManipulator;// for testing

  private:

    /**this is the number of different lines to be shown. it is MultiPV in stockfish, defaults to 1*/
    unsigned mNumberOfLinesToBeShown;

  protected:

    /**Cache the latest engine lines and all associated info*/
    std::vector<InfoInEngineLine> mLatestEngineLines;

    /**we create a chessboard as we need squares with pieces to translate engine moves to SAN*/
    ChessBoard* mpChessBoard;

    /**Cache of the poistion being analysed*/
    std::string mCachedFenPositiontoBeanalysed;

    /**Helper class to handle fen strings*/
    FenHandler* mpHelperFenHandler;

    /**
     * This one parses a single line of the engine output
     *
     * @param stockfishLine (input) the output of the engine we wish to analyze, a single line
     * @return the information contained in this line
     */
    InfoInEngineLine ParseALineofStockfishOutput(const std::string& stockfishLine);

    /**
     * Key helper method that parses the whole output and returns a vector of information for each line
     */
    std::vector<InfoInEngineLine> ParseWholeEngineOutput(const std::string& rawOutput);

  public :


    /**
     * Constructor
     */
    UCIStringsManipulator();

    /**
     * Destructor
     */
    ~UCIStringsManipulator();


    /**
     * When called, this method will parse the UCI engine output and gives you useful info about the output.
     *
     * @param uciOutput (input) string to be parsed
     * @param prettyEngineLines (output)  a vector of engine lines in algebraic notation
     * @param score (output) the score in pawns, positive if favourable to white, negative otherwise, the best possible
     * @param depth (output) the depth of analysis
     * @param bestMove (output) the best move for the colour to move
     */
     void GetInfoFromUCIOutput(const std::string& uciOutput, std::vector<std::string>& prettyEngineLines,
    		 double& score, int& depth, std::string& bestMove);


    /**
     * Sets the number of line to be shown.
     *
     * @param num the number of lines to be shown
     */
    void SetNumberOfLinesToBeShown(unsigned num);

    /**
     * Helper method only used for testing private methods.
     */
    void SetPositionToInternalChessBoard(const std::string& fenPosition);
};

}//namespace slach
#endif
