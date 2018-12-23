#ifndef OPTSP_CTPCORE_TEST_LOG_H_
#define OPTSP_CTPCORE_TEST_LOG_H_

#include "../optsp-ctpcore/logger.h"

class _Logger
{
private:
	Logger * logger = nullptr;
	int level;
	int n;

public:
	_Logger(Logger * logger, int level, int n);
	void run();
	void run_stress();
	static void logger_callback0(int loglevel, const char* buff);
	static void logger_callback1(int loglevel, const char* buff);
	static void logger_callback2(int loglevel, const char* buff);
	static void logger_callback3(int loglevel, const char* buff);
	static void logger_callback4(int loglevel, const char* buff);
	static void logger_callback5(int loglevel, const char* buff);
	static void logger_callback6(int loglevel, const char* buff);
};


int test_Logger_level_off();
int test_Logger_level_error(int cnt);
int test_Logger_level_warning(int cnt);
int test_Logger_level_info(int cnt);
int test_Logger_level_debug(int cnt);
int test_Logger_level_trace(int cnt);
int test_Logger_stress_test(int cnt);


#endif // !OPTSP_CTPCORE_TEST_LOG_H_


