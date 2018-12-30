#include "test_platctp.h"
#include <boost/thread.hpp>
#include "../platctp/tradespi.h"
#include "../platctp/quotespi.h"
#include "../include/platctp.h"
#include "../include/logger.h"
#include "../include/config.h"
#include "../include/datatype.hpp"
#include "../include/ctpapi.hpp"


void log_callback(int loglevel, const char* buff) { 
    std::cerr << buff;
}

void quote_callback(int cbtype, bool flag, void *ptr) {
    std::cerr << "quote callback" << std::endl;
}

void trade_callback(int cbtype, bool flag, void *ptr) {
    std::cerr << "trade callback" << std::endl;
}

void plat_callback(int cbtype, int cmdid, bool flag, void *ptr) {
    std::cerr << "plat callback" << std::endl;
}

bool test_PlatCtp() {
    Config *config = new Config();
    Logger *logger = new Logger((config->homepath / "logging-debug-quotespi.log").string(), LOG_LEVEL_TRACE, log_callback);
    PlatCtp *platctp = new PlatCtp(config, logger, quote_callback, trade_callback, plat_callback);

    boost::thread thrd1(boost::bind(&Logger::run, logger));
    boost::thread thrd2(boost::bind(&PlatCtp::run, platctp));
    thrd1.join();
    thrd2.join();
    return true;
}