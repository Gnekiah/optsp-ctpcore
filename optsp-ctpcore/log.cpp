#include "log.h"
#include <boost/function.hpp>
#include "arch.h"

Log::Log(std::string logpath, int loglevel)
	: logpath(logpath), loglevel(loglevel)
{
	logQueue = new boost::lockfree::queue<LogCellField>(64);
}


void Log::logging(std::string log, char* caller, int level)
{
	LogCellField logcell;
	logcell.timestamp = arch_GetTimeStamp();
	logcell.level = level;
	arch_Strcpy(logcell.log, log.c_str(), sizeof(logcell.log));
	arch_Strcpy(logcell.caller, caller, sizeof(logcell.caller));
	logQueue->push(logcell);
}


void Log::run()
{
	while (true) {
		LogCellField logcell;
		while (logQueue->empty())
			arch_Sleep(2);
		logQueue->pop(logcell);

	}
}


