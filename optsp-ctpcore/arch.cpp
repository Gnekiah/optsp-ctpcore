#include "arch.h"

#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


void arch_Sleep(uint64_t msec) {
	boost::this_thread::sleep(boost::posix_time::milliseconds(msec));
}


uint64_t arch_GetTimeStamp() {
	boost::posix_time::ptime origin_time(boost::gregorian::date(1970, 1, 1));
	boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration diff = now - origin_time;
	return diff.total_milliseconds();
}



#if defined(__linux__) && defined( __x86_64__)
#elif defined(_WIN64)

#include <Windows.h>
bool arch_GetHomePath(char* homePath) {
	int ret = GetEnvironmentVariable("USERPROFILE", homePath, 1024);
	return (ret == 0 || ret > 1024) ? false : true;
}





#endif