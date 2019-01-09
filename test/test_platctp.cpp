#include "test_platctp.h"
#include <boost/thread.hpp>
#include "../platctp/tradespi.h"
#include "../platctp/quotespi.h"
#include "../include/platctp.h"
#include "../include/logger.h"
#include "../include/config.h"
#include "../include/datatype.hpp"
#include "../include/ctpapi.hpp"

//#define show(x)    do { std::cerr << x << std::endl; } while(0)
#define show(x)    do { ; } while(0)


void log_callback(int loglevel, void* buff) { 
    std::cerr << (char*)buff;
}

void plat_callback(int cbtype, void *ptr) {
    //std::cerr << "plat callback" << std::endl;
}

bool test_PlatCtp() {
    Config *config = new Config();
    Logger *logger = new Logger((config->GetHomePath() / "logging-debug-quotespi.log").string(), LOG_LEVEL_TRACE, log_callback);
    PlatCtp *platctp = new PlatCtp(config, logger, plat_callback);

    show(config->VERSION);
    show(config->SUBVERSION);
    show(config->EXTRAVERSION);
    show(config->GetProductName());
    show(config->APP_TITLE);
    show(config->HOME_FILE);
    show(config->CONFIG_FILE);
    show(config->RUNNING_LOG_FILE);
    show(config->MATCH_LOG_FILE);
    show(config->POSITION_LOG_FILE);
    show(config->STATE_LOG_FILE);
    show(config->INSTRUMENT_FILE);
    show(config->MD_CSV_FORMAT);
    show(config->GetHomePath().string());
    show(config->GetDataPath().string());
    show(config->GetLogLevel());
    show(config->GetBrokerID());
    show(config->GetUserID());
    show(config->GetInvestorID());
    show(config->GetPassword());
    show(config->GetQuoteFrontAddr());
    show(config->GetTradeFrontAddr());

    boost::thread thrd1(boost::bind(&Logger::run, logger));
    boost::thread thrd2(boost::bind(&PlatCtp::run, platctp));
    thrd1.join();
    thrd2.join();
    return true;
}