#include <vector>
#include <string>
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
};

} // neamespace
#endif /* UCIENGINEINTERFACE_HPP_ */
