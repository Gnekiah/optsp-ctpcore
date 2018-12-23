#include "logger.h"
#include <boost/function.hpp>
#include <fstream>
#include "arch.h"


Logger::Logger(std::string logpath, int loglevel, log_callback_fn fn)
	: logpath(logpath), loglevel(loglevel), log_callback(fn)
{
	logQueue = new boost::lockfree::queue<LogCellField>(256);
}


void Logger::_logging(std::string &log, const char* caller, int level)
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
	_logging(_log, caller, level);
	log.str("");
}


void Logger::run()
{
	DateTimeType time;
	std::stringstream log;
	LogCellField logcell;
	std::ofstream out;
	out.open(logpath, std::ios::app);
	uint64_t currpos = arch_GetTimeStamp();
	uint64_t lastpos = currpos;

	while (true) {
		while (logQueue->empty()) {
			currpos = arch_GetTimeStamp();
			if (currpos - lastpos > LOGGER_FLUSH_INTERVAL) {
				out.close();
				out.open(logpath, std::ios::app);
				lastpos = currpos;
			}
			arch_Sleep(2);
		}
		logQueue->pop(logcell);
		
		log.str("");
		arch_TimeStamp2Str(time, logcell.timestamp);
		log << time;
		switch (logcell.level) {
		case LOG_LEVEL_ERROR:
			log << " [ERROR] <"; break;
		case LOG_LEVEL_WARN:
			log << " [WARN]  <"; break;
		case LOG_LEVEL_INFO:
			log << " [INFO]  <"; break;
		case LOG_LEVEL_DEBUG:
			log << " [DEBUG] <"; break;
		case LOG_LEVEL_TRACE:
			log << " [TRACE] <"; break;
		default:
			continue;
		}
		log << logcell.caller << "> " << logcell.log << std::endl;
		out << log.str().c_str();
		(*log_callback) (logcell.level, log.str().c_str());
	}
	out.close();
}


