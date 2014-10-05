#include <vector>
#include <string>
#include <limits>
#include <sstream>
#include <thread>
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
	std::stringstream mCinRedirect;
	std::string mLatestEngineOutput;
	UCIStringsManipulator* mpUCIStringManipulator;
	std::shared_ptr<std::thread> mpMainEngineThread;
	std::shared_ptr<std::thread> mpCommandThread;

	void IssueCommandtoStockfish(const std::string& command);

	void InitEngine();
	void DoIssueCommand(const std::string& command);
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

	void StopAnalysis();
	void StartAnalysis(slach::Position* pPosition, double seconds = std::numeric_limits<double>::max());
};

} // neamespace
#endif /* UCIENGINEINTERFACE_HPP_ */
