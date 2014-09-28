#include <vector>
#include <string>
#include <limits>
#include "UCIStringsManipulator.hpp"

#ifndef UCIENGINEINTERFACE_HPP_
#define UCIENGINEINTERFACE_HPP_

namespace slach
{
/*
 * Class that manages communications with the UCI engine
 */
class UCIEngineInterface {

private:

	std::string mLatestEngineOutput;
	UCIStringsManipulator* mpUCIStringManipulator;

	void IssueCommandtoStockfish(const std::string& command);

public:
	UCIEngineInterface();
	~UCIEngineInterface();

	void SetNumberOfLinesToBeShown(unsigned num);

	/**
	 * Sets the position to be analysed. Passes this information on to the internal string manipulator.
	 *
	 */
	void SetFenPosition(const std::string& fenPosition);

	void GetEngineInfo(std::vector<std::string>& prettyEngineLines,
			 double& score, int& depth, std::string& bestMove);

	void StartAnalysis(slach::Position* pPosition, double seconds = std::numeric_limits<double>::max());
};

} // neamespace
#endif /* UCIENGINEINTERFACE_HPP_ */
