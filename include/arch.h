#ifndef OPTSP_CTPCORE_ARCH_H_
#define OPTSP_CTPCORE_ARCH_H_

#include <stdint.h>
#include <cstring>
#include <stdlib.h>

#define arch_Str2Int64(s)          atoll(s)

#if defined(__linux__) && defined( __x86_64__)
#define arch_Strcpy(dst, src, n)    strncpy(dst, src, n)
#define arch_Memcpy(dst, src, n)    memcpy(dst, src, n)
#elif defined(_WIN64)
#define arch_Strcpy(dst, src, n)    strcpy_s(dst, n, src)
#define arch_Memcpy(dst, src, n)    memcpy_s(dst, n, src, n)
#endif


///Get Home Path
///parameter:   homePath - char* to save home path
///return:      true - success; false - error
bool arch_GetHomePath(char* homePath);
///Sleep for Milliseconds
///parameter:   msec - milliseconds
void arch_Sleep(uint64_t msec);
///Get Time Stamp
///return:      timestamp
uint64_t arch_GetTimeStamp();
///Get Date Stamp
///return:      datestamp
uint64_t arch_GetDateStamp();
///String to Timestamp
///parameter:   timestr - datetime string as: yyyy-MM-dd hh:mm:ss.zzz
///return:      timestamp
uint64_t arch_Str2TimeStamp(const char* timestr);
///String to Timestamp
///parameter:   date - yyyyMMdd
///             time - hh:mm:ss
///             ms - zzz
///return:      timestamp
uint64_t arch_Str2TimeStamp(const char* date, const char* time, int ms);
///Timestamp to String
///parameter:   buff - buffer to save string
///             ts - timestamp
///return:      true - success; false - error
bool arch_TimeStamp2Str(char* buff, uint64_t ts);





#endif // ! OPTSP_CTPCORE_ARCH_H_
