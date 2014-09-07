#ifndef GUITHREADVARS_H_INCLUDED
#define GUITHREADVARS_H_INCLUDED

#include <string>
#include <condition_variable>
#include <mutex>

extern std::string GlobalCommandFromGUI;
volatile extern bool GuiIssuedNewCommand;

extern std::mutex global_mutex_send;
extern std::mutex global_mutex_receive;
extern std::condition_variable global_cv_send;


#endif
