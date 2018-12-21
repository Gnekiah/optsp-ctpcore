#ifndef OPTSP_CTPCORE_ARCH_H_
#define OPTSP_CTPCORE_ARCH_H_

#include <boost/date_time/posix_time/posix_time.hpp>


///Get Home Path
///parameter:	homePath - char* to save home path
///return:		true - success; false - error
bool arch_GetHomePath(char*);
///Sleep for Milliseconds
///parameter:	milliseconds
void arch_Sleep(uint64_t);

uint64_t arch_GetTimeStamp();





#endif // ! OPTSP_CTPCORE_ARCH_H_
