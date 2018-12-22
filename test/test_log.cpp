#include "test_log.h"
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

bool test_Log() {
	Log log("what the fuck", 13);
	boost::thread thrd(boost::bind(&Log::run, &log));
	thrd.join();
	return true;
}