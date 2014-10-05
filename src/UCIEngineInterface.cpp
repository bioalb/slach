
#include <sstream>
#include <mutex>
#include <atomic>
#include "UCIEngineInterface.hpp"
#include "main_stockfish.h"

std::mutex slach_mutex;
extern std::string GlobalCommandFromGui;
extern std::atomic<bool> GlobalCommandFromGuiWasIssued;

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
	::main_stockfish(1,nullptr);
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

void slach::UCIEngineInterface::StopAnalysis()
{
	IssueCommandtoStockfish("stop");
}

void slach::UCIEngineInterface::StartAnalysis(slach::Position* pPosition, double seconds)
{
    SetFenPosition(pPosition->GetPositionAsFen());
    std::string position_command = "position fen" + pPosition->GetPositionAsFen();
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
	slach_mutex.lock();
//	std::streambuf *backup = std::cin.rdbuf(); // back up cin's streambuf
//	std::streambuf *psbuf = mCinRedirect.rdbuf();
//	std::cin.rdbuf(psbuf);
//	mCinRedirect<<command<<std::endl;
//	std::cin.sync();
//	std::cin.rdbuf(backup); // Restore old situation
	GlobalCommandFromGui = command;
	slach_mutex.unlock();
	GlobalCommandFromGuiWasIssued.store(true);

}

void slach::UCIEngineInterface::IssueCommandtoStockfish(const std::string& command)
{
	mpCommandThread =   std::make_shared<std::thread>(&slach::UCIEngineInterface::DoIssueCommand, this, command);
	mpCommandThread->join();
}
