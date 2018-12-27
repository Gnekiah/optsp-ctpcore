#include "test_platctp.h"
#include <boost/thread.hpp>
#include "../optsp-ctpcore/tradespi.h"
#include "../optsp-ctpcore/quotespi.h"
#include "../optsp-ctpcore/platctp.h"
#include "../optsp-ctpcore/logger.h"
#include "../optsp-ctpcore/config.h"
#include "../optsp-ctpcore/datatype.hpp"
#include "../optsp-ctpcore/ctpapi/ThostFtdcMdApi.h"
#include "../optsp-ctpcore/ctpapi/ThostFtdcTraderApi.h"
#include "../optsp-ctpcore/ctpapi/ThostFtdcUserApiDataType.h"
#include "../optsp-ctpcore/ctpapi/ThostFtdcUserApiStruct.h"
//#pragma comment (lib, "../optsp-ctpcore/ctpapi/thostmduserapi.lib")
//#pragma comment (lib, "../optsp-ctpcore/ctpapi/thosttraderapi.lib")


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