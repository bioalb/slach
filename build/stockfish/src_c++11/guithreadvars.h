#ifndef GUITHREADVARS_H_INCLUDED
#define GUITHREADVARS_H_INCLUDED

#include <string>
#include <condition_variable>
#include <mutex>
#include <atomic>

extern std::string GlobalCommandFromGUI;
extern std::atomic<bool> GuiIssuedNewCommand;
extern std::atomic<bool> EngineReadyToReceiveNewCommand;
extern std::mutex GUICmmandMutex;
extern std::condition_variable GUICmmandCondition;


#endif
