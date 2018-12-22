#include "arch.h"

#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


#if defined(__linux__) && defined( __x86_64__)
#elif defined(_WIN64)
#include <Windows.h>
#endif

void arch_Sleep(uint64_t msec) {
	boost::this_thread::sleep(boost::posix_time::milliseconds(msec));
}


uint64_t arch_GetTimeStamp() {
	boost::posix_time::ptime origin_time(boost::gregorian::date(1970, 1, 1));
	boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration diff = now - origin_time;
	return diff.total_milliseconds() - 28800000;
}


uint64_t arch_Str2TimeStamp(char* timestr) {
	boost::posix_time::ptime origin_time(boost::gregorian::date(1970, 1, 1));
	boost::posix_time::ptime pt = boost::posix_time::time_from_string(timestr);
	boost::posix_time::time_duration diff = pt - origin_time;
	return diff.total_milliseconds() - 28800000;
}


uint64_t arch_Str2TimeStamp(char* date, char* time, int ms) {
	boost::posix_time::ptime origin_time(boost::gregorian::date(1970, 1, 1));
	boost::posix_time::ptime pt(boost::gregorian::date_from_iso_string(date), boost::posix_time::duration_from_string(time));
	boost::posix_time::time_duration diff = pt - origin_time;
	return diff.total_seconds() * 1000 + ms - 28800000;
}


bool arch_TimeStamp2Str(char* buff, uint64_t ts) {
	ts += 28800000;
	int ms = ts % 1000;
	ts = ts / 1000;
	try {
		boost::posix_time::ptime pt(boost::posix_time::from_time_t(ts));
		std::string timestr = boost::posix_time::to_iso_extended_string(pt);
		arch_Memcpy(buff, timestr.c_str(), 19);
		buff[10] = ' ';
		buff[19] = '.';
		buff[20] = ms / 100 + '0';
		buff[21] = (ms / 10) % 10 + '0';
		buff[22] = ms % 10 + '0';
	}
	catch (std::exception&) {
		return false;
	}
	return true;
}



#if defined(__linux__) && defined( __x86_64__)
#elif defined(_WIN64)

bool arch_GetHomePath(char* homePath) {
	int ret = GetEnvironmentVariableA("USERPROFILE", homePath, 1024);
	return (ret == 0 || ret > 1024) ? false : true;
}





#endif
