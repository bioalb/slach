
#include <sstream>
#include <mutex>
#include <atomic>
#include "UCIEngineInterface.hpp"
#include "main_stockfish.h"

std::mutex command_mutex;
std::mutex cout_mutex;

extern std::string GlobalCommandFromGui;
extern std::atomic<bool> GlobalCommandFromGuiWasIssued;
extern std::atomic<bool> GlobalEngineReadyToRecievCommand;

slach::UCIEngineInterface::UCIEngineInterface()
	: mLatestEngineOutput(""),
	  mpUCIStringManipulator(new UCIStringsManipulator())
{
	mpMainEngineThread =  std::make_shared<std::thread>(&slach::UCIEngineInterface::InitEngine, this);
}

slach::UCIEngineInterface::~UCIEngineInterface()
{
	delete mpUCIStringManipulator;
}

void slach::UCIEngineInterface::InitEngine()
{
	cout_mutex.lock();
	std::cout.rdbuf(mCoutRedirect.rdbuf());
	cout_mutex.unlock();
	::main_stockfish(1,nullptr);
}

void slach::UCIEngineInterface::GetEngineInfo(std::vector<std::string>& prettyEngineLines,
		 double& score, int& depth, std::string& bestMove)
{
	mLatestEngineOutput = mCoutRedirect.str();
	mpUCIStringManipulator->GetInfoFromUCIOutput(mLatestEngineOutput, prettyEngineLines, score, depth, bestMove);
}

void slach::UCIEngineInterface::SetNumberOfLinesToBeShown(unsigned num)
{
	std::stringstream multi_pv_vommand;
	multi_pv_vommand << "setoption name MultiPV value "<<num;
	IssueCommandtoStockfish(multi_pv_vommand.str());

	mpUCIStringManipulator->SetNumberOfLinesToBeShown(num);
}

void slach::UCIEngineInterface::SetFenPosition(const std::string& fenPosition)
{
	mpUCIStringManipulator->SetPositionToInternalChessBoard(fenPosition);
}

void slach::UCIEngineInterface::StopAnalysis()
{
	IssueCommandtoStockfish("stop");
}

void slach::UCIEngineInterface::StartAnalysis(slach::Position* pPosition, double seconds)
{
    SetFenPosition(pPosition->GetPositionAsFen());
    std::string position_command = "position fen " + pPosition->GetPositionAsFen();
    IssueCommandtoStockfish(position_command);
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

void slach::UCIEngineInterface::DoIssueCommand(const std::string& command)
{
	while(GlobalEngineReadyToRecievCommand.load() == false)
	{}//wait for engine to be ready.
	command_mutex.lock();
	GlobalCommandFromGui = command; // issue command
	command_mutex.unlock();
	GlobalCommandFromGuiWasIssued.store(true);//tell engine command was issued

}

void slach::UCIEngineInterface::IssueCommandtoStockfish(const std::string& command)
{
	mpCommandThread =   std::make_shared<std::thread>(&slach::UCIEngineInterface::DoIssueCommand, this, command);
	mpCommandThread->join();
}
