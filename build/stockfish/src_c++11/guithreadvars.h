#ifndef GUITHREADVARS_H_INCLUDED
#define GUITHREADVARS_H_INCLUDED

#include <string>
#include <condition_variable>
#include <mutex>

extern std::string GlobalCommandFromGUI;
volatile extern bool GuiIssuedNewCommand;

extern std::mutex GUICmmandMutex;
extern std::condition_variable GUICmmandCondition;


#endif
