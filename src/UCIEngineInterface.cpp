
#include <sstream>
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

void slach::UCIEngineInterface::StartAnalysis(slach::Position* pPosition, double seconds)
{
    SetFenPosition(pPosition->GetPositionAsFen());

	if (seconds < (std::numeric_limits<double>::max() - 1e-1)) // magic number! just want to be sure ...
	{
			std::stringstream time_limit_command;
			int milliseconds = static_cast<int> (seconds * 1000);
			time_limit_command << "go movetime "<<milliseconds;
			IssueCommandtoStockfish(time_limit_command.str());
	}
	else
	{
			IssueCommandtoStockfish("go infinite");
    }
}

void slach::UCIEngineInterface::IssueCommandtoStockfish(const std::string& command)
{

}
