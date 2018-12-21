#ifndef OPTSP_CTPCORE_TEST_ARCH_HPP_
#define OPTSP_CTPCORE_TEST_ARCH_HPP_

#include <string>
#include <sstream>
#include "../optsp-ctpcore/arch.h"

bool test_arch_GetHomePath() {
	char home[100] = { 0 };
	int ret = arch_GetHomePath(home);
	std::cout << __FUNCTION__ << ": " << home << std::endl;
	return ret;
}


bool test_arch_Sleep() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 100; j++) 
			arch_Sleep(10);
		const boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
		const boost::posix_time::time_duration td = now.time_of_day();
		int hh = td.hours();
		int mm = td.minutes();
		int ss = td.seconds();
		int ms = td.total_milliseconds() - ((hh * 3600 + mm * 60 + ss) * 1000);
		std::cout << ms << std::endl;
	}
	return true;
}


bool test_arch_GetTimeStamp() {
	std::cout << arch_GetTimeStamp() << std::endl;
	return true;
}


#endif // !OPTSP_CTPCORE_TEST_ARCH_HPP_

