#include "test_logger.h"
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "../optsp-ctpcore/datatype.hpp"
#include "../optsp-ctpcore/arch.h"
#include "../optsp-ctpcore/config.h"
#include<stdlib.h>
#include<time.h>

static int gcnt0 = 0;
static int gcnt1 = 0;
static int gcnt2 = 0;
static int gcnt3 = 0;
static int gcnt4 = 0;
static int gcnt5 = 0;
static int gcnt6 = 0;


_Logger::_Logger(Logger * logger, int level, int n)
	: logger(logger), level(level), n(n)
{
}


void _Logger::run() {
	int j = 0;
	int _level;
	srand((int)time(0));

	for (int i = 0; i < 1000; i++) {
		_level = (level < LOG_LEVEL_TRACE) ? (rand() % (LOG_LEVEL_TRACE - level) + level + 1) : LOG_LEVEL_OFF;
		if (rand() % 2 && j++ < n) 
			_level = (level) ? (rand() % level + 1) : 0;

		std::stringstream log;
		log << "test";
		logger->logging(log, __FUNCTION__, _level);
	}
}


void _Logger::run_stress() {
	srand((int)time(0));
	for (int i = 0; i < n; i++) {
		std::stringstream log;
		log << i;
		logger->logging(log, __FUNCTION__, rand() % 5 + 1);
	}
}


void _Logger::logger_callback0(int loglevel, const char* buff) { gcnt0++; }
void _Logger::logger_callback1(int loglevel, const char* buff) { gcnt1++; }
void _Logger::logger_callback2(int loglevel, const char* buff) { gcnt2++; }
void _Logger::logger_callback3(int loglevel, const char* buff) { gcnt3++; }
void _Logger::logger_callback4(int loglevel, const char* buff) { gcnt4++; }
void _Logger::logger_callback5(int loglevel, const char* buff) { gcnt5++; }
void _Logger::logger_callback6(int loglevel, const char* buff) { gcnt6++; }


int test_Logger(int level, int cnt, void *ptr, int *p) {
	Config *config = new Config();
	std::string logpath = (config->homepath / "running-debug.log").string();
	Logger * logger = new Logger(logpath, level, (log_callback_fn)ptr);
	boost::thread thrd1(boost::bind(&Logger::run, logger));
	_Logger * _logger = new _Logger(logger, level, cnt);
	boost::thread thrd2(boost::bind(&_Logger::run, _logger));
	arch_Sleep(cnt);
	return *p;
}

int test_Logger_level_off() {
	return test_Logger(LOG_LEVEL_OFF, 100, &_Logger::logger_callback0, &gcnt0);
}


int test_Logger_level_error(int cnt) {
	return test_Logger(LOG_LEVEL_ERROR, cnt, &_Logger::logger_callback1, &gcnt1);
}


int test_Logger_level_warning(int cnt) {
	return test_Logger(LOG_LEVEL_WARN, cnt, &_Logger::logger_callback2, &gcnt2);
}


int test_Logger_level_info(int cnt) {
	return test_Logger(LOG_LEVEL_INFO, cnt, &_Logger::logger_callback3, &gcnt3);
}


int test_Logger_level_debug(int cnt) {
	return test_Logger(LOG_LEVEL_DEBUG, cnt, &_Logger::logger_callback4, &gcnt4);
}


int test_Logger_level_trace(int cnt) {
	return test_Logger(LOG_LEVEL_TRACE, cnt, &_Logger::logger_callback5, &gcnt5);
}


int test_Logger_stress_test(int cnt) {
	Config *config = new Config();
	std::string logpath = (config->homepath / "running-debug.log").string();
	Logger * logger = new Logger(logpath, LOG_LEVEL_TRACE, &_Logger::logger_callback6);
	boost::thread thrd1(boost::bind(&Logger::run, logger));
	_Logger * _logger = new _Logger(logger, LOG_LEVEL_TRACE, cnt);
	boost::thread thrd2(boost::bind(&_Logger::run_stress, _logger));
	arch_Sleep(cnt);
	return gcnt6;
}