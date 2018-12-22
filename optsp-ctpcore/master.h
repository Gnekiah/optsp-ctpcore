#ifndef OPTSP_CTPCORE_MASTER_H_
#define OPTSP_CTPCORE_MASTER_H_

#include "arch.h"
#include "logger.h"
#include "config.h"

class Master
{
private:
	Logger * logger = nullptr;
	Config * config = nullptr;

public:
	Master();
	void run();
};

#endif // !OPTSP_CTPCORE_MASTER_H_

