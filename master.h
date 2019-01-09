#ifndef OPTSP_CTPCORE_MASTER_H_
#define OPTSP_CTPCORE_MASTER_H_

#include "include/arch.h"
#include "include/logger.h"
#include "include/config.h"

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

