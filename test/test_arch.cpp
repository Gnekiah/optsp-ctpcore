#include "test_arch.h"
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>


bool test_arch_GetHomePath() {
    char home[100] = { 0 };
    return arch_GetHomePath(home);
}


bool test_arch_Sleep() {
    boost::posix_time::ptime p1 = boost::posix_time::microsec_clock::local_time();
    for (int j = 0; j < 100; j++)
        arch_Sleep(10);
    boost::posix_time::ptime p2 = boost::posix_time::microsec_clock::local_time();
    boost::posix_time::time_duration td = p2 - p1;
    int diff = td.total_milliseconds();
    return diff < 1500 ? true : false;
}


bool test_arch_GetTimeStamp() {
    return true;
}


bool test_arch_Str2TimeStamp() {
    return true;
}


bool test_arch_TimeStamp2Str() {
    char buff[24] = { 0 };
    uint64_t ts = arch_GetTimeStamp();
    int ret = arch_TimeStamp2Str(buff, ts);
    char date[9] = { 0 };
    char time[9] = { 0 };
    int ms = 0;
    arch_Memcpy(date, buff, 4);
    date[4] = buff[5];
    date[5] = buff[6];
    date[6] = buff[8];
    date[7] = buff[9];
    arch_Memcpy(time, buff+11, 8);
    ms = (buff[20] - '0') * 100 + (buff[21] - '0') * 10 + (buff[22] - '0');
    uint64_t ts1 = arch_Str2TimeStamp(buff);
    uint64_t ts2 = arch_Str2TimeStamp(date, time, ms);
    return (ts1 == ts2 && ts == ts1) ? true : false;
}