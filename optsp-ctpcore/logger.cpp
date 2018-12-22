#include "logger.h"
#include <boost/function.hpp>
#include "arch.h"

Logger::Logger(std::string logpath, int loglevel)
	: logpath(logpath), loglevel(loglevel)
{
	logQueue = new boost::lockfree::queue<LogCellField>(64);
}


void Logger::logging(std::string &log, const char* caller, int level)
{
	if (this->loglevel < level)
		return;
	LogCellField logcell;
	logcell.timestamp = arch_GetTimeStamp();
	logcell.level = level;
	arch_Strcpy(logcell.log, log.c_str(), sizeof(logcell.log));
	arch_Strcpy(logcell.caller, caller, sizeof(logcell.caller));
	logQueue->push(logcell);
}


void Logger::logging(std::stringstream &log, const char* caller, int level)
{
	std::string _log = log.str();
	logging(_log, caller, level);
	log.str("");
}


void Logger::run()
{
	while (true) {
		LogCellField logcell;
		while (logQueue->empty())
			arch_Sleep(2);
		logQueue->pop(logcell);

	}
}


