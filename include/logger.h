#ifndef OPTSP_CTPCORE_LOG_H_
#define OPTSP_CTPCORE_LOG_H_

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/lockfree/queue.hpp>
#include "datatype.hpp"


typedef struct LogCellField {
    uint64_t timestamp;
    int level;
    char log[1024];
    char caller[128];
} LogField;


#define LOG_LEVEL_OFF           0
#define LOG_LEVEL_ERROR         1
#define LOG_LEVEL_WARN          2
#define LOG_LEVEL_INFO          3
#define LOG_LEVEL_DEBUG         4
#define LOG_LEVEL_TRACE         5


#define LOGERR(handle, stream)      handle->logging(stream, __FUNCTION__, LOG_LEVEL_ERROR)
#define LOGWARN(handle, stream)     handle->logging(stream, __FUNCTION__, LOG_LEVEL_WARN)
#define LOGINFO(handle, stream)     handle->logging(stream, __FUNCTION__, LOG_LEVEL_INFO)
#define LOGDBG(handle, stream)      handle->logging(stream, __FUNCTION__, LOG_LEVEL_DEBUG)
#define LOGTRACE(handle, stream)    handle->logging(stream, __FUNCTION__, LOG_LEVEL_TRACE)


class Logger 
{
private:
    int loglevel;
    std::string logpath;
    boost::lockfree::queue<LogCellField> *logQueue = nullptr;
    log_callback_fn log_callback = nullptr;

public:
    Logger(std::string logpath, int loglevel, log_callback_fn fn);
    void logging(std::stringstream &log, const char* caller, int level);
    void _logging(std::string &log, const char* caller, int level);
    void run();
};

#endif // !OPTSP_CTPCORE_LOG_H_

