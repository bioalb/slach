#include "UCIEngineInterface.hpp"

slach::UCIEngineInterface::UCIEngineInterface()
	: mLatestEngineOutput(""),
	  mpUCIStringManipulator(new UCIStringsManipulator())
{

}

slach::UCIEngineInterface::~UCIEngineInterface()
{
	delete mpUCIStringManipulator;
}

void slach::UCIEngineInterface::GetEngineInfo(std::vector<std::string>& prettyEngineLines,
		 double& score, int& depth, std::string& bestMove)
{
	mpUCIStringManipulator->GetInfoFromUCIOutput(mLatestEngineOutput, prettyEngineLines, score, depth, bestMove);
}

void slach::UCIEngineInterface::SetNumberOfLinesToBeShown(unsigned num)
{
	mpUCIStringManipulator->SetNumberOfLinesToBeShown(num);
}

void slach::UCIEngineInterface::SetFenPosition(const std::string& fenPosition)
{
	mpUCIStringManipulator->SetPositionToInternalChessBoard(fenPosition);
}
