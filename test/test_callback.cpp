#include "test_callback.h"
#include "../include/arch.h"
#include "../include/config.h"

static int gcnt = 0;

_Logger2::_Logger2(Logger * logger, int cnt)
	: logger(logger), cnt(cnt)
{
}


void _Logger2::run() {
	srand((int)time(0));
	for (int i = 0; i < cnt; i++) {
		std::stringstream log;
		log << i;
		logger->logging(log, __FUNCTION__, rand() % 5 + 1);
	}
}


TestClass::TestClass(int id) 
	: id(id)
{
	pfn = this;
	queue = new boost::lockfree::queue<BuffField>(256);
}


void TestClass::run() {
	while (true) {
		while (queue->empty())
			arch_Sleep(2);
		BuffField buf;
		queue->pop(buf);
		gcnt++;
	}
}


void TestClass::callback(int level, const char *ptr) {
	BuffField buf;
	arch_Strcpy(buf.data, ptr, 1024);
	queue->push(buf);
}


void callback(int level, const char* buff) {
	TestClass *x = (TestClass*)pfn;
	x->callback(level, buff);
}


int test_Callback(int cnt) {
	TestClass *tc = new TestClass(1);
	boost::thread thrd0(boost::bind(&TestClass::run, tc));

	Config *config = new Config();
	std::string logpath = (config->homepath / "running-debug.log").string();

	Logger * logger = new Logger(logpath, LOG_LEVEL_TRACE, callback);
	boost::thread thrd1(boost::bind(&Logger::run, logger));

	_Logger2 * _logger = new _Logger2(logger, cnt);
	boost::thread thrd2(boost::bind(&_Logger2::run, _logger));

	arch_Sleep(cnt);
	thrd0.interrupt();
	thrd1.interrupt();
	thrd2.interrupt();
	thrd0.join();
	thrd1.join();
	thrd2.join();
	return gcnt;
}