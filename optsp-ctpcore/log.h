#ifndef OPTSP_CTPCORE_LOG_H_
#define OPTSP_CTPCORE_LOG_H_

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/lockfree/queue.hpp>


typedef struct LogCellField {
	uint64_t timestamp;
	int level;
	char log[1024];
	char caller[128];
} LogField;

class Log 
{
private:
	int loglevel;
	std::string logpath;
	boost::lockfree::queue<LogCellField> *logQueue = nullptr;

public:
	Log(std::string logpath, int loglevel);
	void logging(std::string log, char* caller, int level);
	void run();
};

#endif // !OPTSP_CTPCORE_LOG_H_

