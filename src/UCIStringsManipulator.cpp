#include <algorithm>
#include <limits>
#include <iostream>
#include <sstream>
#include <streambuf>

#include "UCIStringsManipulator.hpp"


slach::UCIStringsManipulator::UCIStringsManipulator()
  : mNumberOfLinesToBeShown(1u),
    mpChessBoard( new slach::ChessBoard() ),
	mpHelperFenHandler( new slach::FenHandler() )
{
    mpChessBoard->SetupChessBoard();
    mLatestEngineLines.resize(mNumberOfLinesToBeShown);
}

slach::UCIStringsManipulator::~UCIStringsManipulator()
{
    delete mpChessBoard;
    delete mpHelperFenHandler;
}

void slach::UCIStringsManipulator::SetNumberOfLinesToBeShown(unsigned num)
{
    mNumberOfLinesToBeShown = num;
}


void slach::UCIStringsManipulator::GetInfoFromUCIOutput(const std::string& uciOutput, std::vector<std::string>& prettyEngineLines,
		 double& score, int& depth, std::string& bestMove)
{
	mLatestEngineLines = ParseWholeEngineOutput(uciOutput);
	// in case the parser didn't find enough good ones...
	if (mLatestEngineLines.size() < mNumberOfLinesToBeShown) mLatestEngineLines.resize(mNumberOfLinesToBeShown);

	//sort them
	std::sort(mLatestEngineLines.begin(), mLatestEngineLines.end());
	if (mpHelperFenHandler->GetPositionFeaturesFromFen(mCachedFenPositiontoBeanalysed).mTurnToMove == WHITE)
	{
		std::reverse(mLatestEngineLines.begin(), mLatestEngineLines.end());
	}

	prettyEngineLines.resize( (mLatestEngineLines.size()) );
    for (unsigned pv = 0; pv <  prettyEngineLines.size(); pv++)
    {
        std::stringstream ss;
        ss.setf( std::ios::fixed, std::ios::floatfield );//for the score
        ss.precision(2);//for the score
        ss<<"Depth = " << mLatestEngineLines[pv].mDepth << "; score = " << mLatestEngineLines[pv].mScore << "; " << mLatestEngineLines[pv].mMoveList;
        prettyEngineLines[pv] = ss.str();
    }

	score = mLatestEngineLines[0].mScore;
	depth = mLatestEngineLines[0].mDepth;
	bestMove = mLatestEngineLines[0].mRootMove;
}

void slach::UCIStringsManipulator::SetPositionToInternalChessBoard(const std::string& fenPosition)
{
    mCachedFenPositiontoBeanalysed = fenPosition;
    mpChessBoard->SetFenPosition(mCachedFenPositiontoBeanalysed); // note that this does nothing if fen is invalid.
}

std::vector<slach::InfoInEngineLine> slach::UCIStringsManipulator::ParseWholeEngineOutput(const std::string& rawOutput)
{
	std::vector<InfoInEngineLine> ret;
    unsigned diverse_lines = 0;
    size_t line_begins = std::string::npos-1;

    while (diverse_lines < mNumberOfLinesToBeShown && line_begins != std::string::npos)
    {
    	line_begins = rawOutput.rfind("info", line_begins-1);
        size_t line_end = rawOutput.find("\n", line_begins);

        if (line_begins != std::string::npos && line_end != std::string::npos)
        {
        	std::string to_be_parsed = rawOutput.substr(line_begins, line_end - line_begins);
        	auto info = ParseALineofStockfishOutput(to_be_parsed);
            if ( std::find (ret.begin(), ret.end(), info) == ret.end()  && info.mValid == true)  //if not found
			{
            	ret.push_back(info);
            	diverse_lines++;
			}
        }
    }

    return ret;
}

slach::Move slach::UCIStringsManipulator::FindEngineFinalMove(const std::string& rawOutput)
{
	mpChessBoard->SetFenPosition(mCachedFenPositiontoBeanalysed);
	std::vector<Square*> p_squares = mpChessBoard->GetSquares();
	std::string orig_dest;
	Move invalid_dummy;//origin and dest are nullptr.
	std::size_t position = rawOutput.rfind("bestmove");
	if (position == std::string::npos) return invalid_dummy;
	std::size_t end_of_bestmove = rawOutput.find_first_of(" ", position);
	if (end_of_bestmove == std::string::npos) return invalid_dummy;
	std::size_t real_start_of_move = rawOutput.find_first_not_of(" ", end_of_bestmove);
	if (rawOutput.length() < (real_start_of_move + 4)) return invalid_dummy; // too short
	orig_dest = rawOutput.substr(real_start_of_move, 4);
	Move ret(orig_dest,p_squares);
	return ret;
}

slach::InfoInEngineLine slach::UCIStringsManipulator::ParseALineofStockfishOutput(const std::string& stockfishLine)
{
	InfoInEngineLine info;

    //depth
    size_t pos = stockfishLine.find("info depth");
    if (pos == std::string::npos) return info; //with valid as false....
    pos = stockfishLine.find_first_not_of(" ", pos+10); //10 is the length of "info depth" itself...
    info.mDepth = atoi(&(stockfishLine[pos]));

    //mate line or checkmate?
    pos = stockfishLine.find("mate");
    if (pos != std::string::npos)
    {
    	pos = stockfishLine.find_first_not_of(' ', pos+4);
    	info.mDepth = atoi(&(stockfishLine[pos]));
    	if (info.mDepth == 0)
    	{
    		info.mCheckMate = true;
    		info.mRootMove = "checkmate";
    		info.mValid = true;
    		return info;
    	}
    	info.mMateLine = true;
    }

    //score
    pos = stockfishLine.rfind("cp");
    if ( (pos == std::string::npos) && info.mMateLine == false ) return info;  //with valid as false....
    pos = stockfishLine.find_first_of(' ', pos);
    double score = atof(&(stockfishLine[pos]))/100.0;
    if (info.mMateLine == true) score = 100;
    //fix the score to be positive for white and negative for black
    if (mpHelperFenHandler->GetPositionFeaturesFromFen(mCachedFenPositiontoBeanalysed).mTurnToMove == BLACK) score = (- score);
    info.mScore = score;

    //line
    std::size_t start_of_move_list = stockfishLine.find(" pv");
    //only checkmate lines do not have pv...
    if ( (start_of_move_list == std::string::npos) && info.mCheckMate == false ) return info;  //with valid as false....
    size_t start_of_move = stockfishLine.find_first_not_of(" ", start_of_move_list+2);
    std::string pretty_line = "";
    int i = 0;
    mpChessBoard->SetFenPosition(mCachedFenPositiontoBeanalysed);
    while (start_of_move != std::string::npos)
    {
        std::size_t end_of_move = stockfishLine.find(' ', start_of_move+1);

        std::string move_string = stockfishLine.substr(start_of_move, end_of_move - start_of_move );
        Move verbose_move(move_string, mpChessBoard->GetSquares());
        if ( (verbose_move.GetOrigin() != nullptr) && (verbose_move.GetDestination() != nullptr) )
        {
            if (! mpChessBoard->IsLegalMove(verbose_move) ) return info; //with valid still as false

            std::string pretty_move = verbose_move.GetMoveInAlgebraicFormat();
            pretty_line = pretty_line + pretty_move + " ";
            if (i == 0)
            {
                info.mRootMove = pretty_move;
                i++;
            }
            mpChessBoard->MakeThisMove(verbose_move);
        }
        start_of_move = stockfishLine.find_first_not_of(" \n", end_of_move);
    }

    if (pretty_line.length() > 0)
    {
        info.mMoveList = pretty_line;

        if (info.mMateLine == true) info.mMoveList += "mate";
    }

    info.mValid  = true;
    return info;
}

