#include "test_platctp.h"
#include "../optsp-ctpcore/tradespi.h"
#include "../optsp-ctpcore/logger.h"
#include "../optsp-ctpcore/config.h"
#include "../optsp-ctpcore/datatype.hpp"
#include "../optsp-ctpcore/ctpapi/ThostFtdcMdApi.h"
#include "../optsp-ctpcore/ctpapi/ThostFtdcTraderApi.h"
#include "../optsp-ctpcore/ctpapi/ThostFtdcUserApiDataType.h"
#include "../optsp-ctpcore/ctpapi/ThostFtdcUserApiStruct.h"



void log_callback(int level, const char* buff) {
	std::cerr << __FUNCTION__ << ": [level]=" << level << " [msg]=" << buff;
}

void quote_callback(int cbtype, bool flag, void* ptr) {
	switch (cbtype) {
	case CB_QUOTE_CONNECTED:
		break;
	case CB_QUOTE_DISCONNECTED:
		break;
	case CB_QUOTE_RSP_USER_LOGIN:
		break;
	case CB_QUOTE_RSP_USER_LOGOUT:
		break;
	case CB_QUOTE_RSP_SUB_MARKET_DATA:
		break;
	case CB_QUOTE_RSP_UNSUB_MARKET_DATA:
		break;
	case CB_QUOTE_RTN_DEPTH_MARKET_DATA:
		break;
	default:
		std::cerr << __FUNCTION__ << ": [ERROR] CB_QUOTE_ out of match" << std::endl;
	}
}

void trade_callback(int cbtype, bool flag, void* ptr) {
	switch (cbtype) {
	case CB_TRADE_CONNECTED:
		break;
	case CB_TRADE_DISCONNECTED:
		break;
	case CB_TRADE_RSP_AUTHENTICATE:
		break;
	case CB_TRADE_RSP_USER_LOGIN:
		break;
	case CB_TRADE_RSP_USER_LOGOUT:
		break;
	case CB_TRADE_RSP_USER_PASSWD_UPDATE:
		break;
	case CB_TRADE_RSP_TRADING_ACCOUNT_PASSWD_UPDATE:
		break;
	case CB_TRADE_RSP_QRY_SETTLEMENT_INFO:
		break;
	case CB_TRADE_RSP_QRY_SETTLEMENT_INFO_CONFIRM:
		break;
	case CB_TRADE_RSP_SETTLEMENT_INFO_CONFIRM:
		break;
	case CB_TRADE_RSP_QRY_INVESTOR_POSITION:
		break;
	case CB_TRADE_RSP_QRY_INSTRUMENT:
		break;
	case CB_TRADE_RSP_QRY_TRADING_ACCOUNT:
		break;
	case CB_TRADE_RSP_QRY_INVESTOR:
		break;
	case CB_TRADE_RSP_ORDER_INSERT:
		break;
	case CB_TRADE_RSP_ORDER_ACTION:
		break;
	case CB_TRADE_RTN_ORDER:
		break;
	case CB_TRADE_RTN_TRADE:
		break;
	case CB_TRADE_ERR_RTN_ORDER_INSERT:
		break;
	case CB_TRADE_ERR_RTN_ORDER_ACTION:
		break;
	default:
		std::cerr << __FUNCTION__ << ": [ERROR] CB_TRADE_ out of match" << std::endl;
	}
}

void platcmd_callback(int cbtype, int cmdid, bool flag, void* ptr) {

}

bool test_PlatCtp() {
	Config *config = new Config();
	Logger *logger = new Logger((config->homepath / "logging-debug-quotespi.log").string(), LOG_LEVEL_TRACE, log_callback);
	QuoteSyncField *quoteSync = new QuoteSyncField;
	QuoteSpi *quoteSpi = new QuoteSpi(logger, quoteSync, quote_callback, platcmd_callback);
	TradeSyncField *tradeSync = new TradeSyncField;
	TradeSpi *tradeSpi = new TradeSpi(logger, tradeSync, trade_callback, platcmd_callback);

	CThostFtdcMdApi *quoteApi = CThostFtdcMdApi::CreateFtdcMdApi(config->homepath.string().c_str());
	quoteApi->RegisterSpi(quoteSpi);
	quoteApi->RegisterFront(config->quoteFrontAddr);

	CThostFtdcTraderApi *tradeApi = CThostFtdcTraderApi::CreateFtdcTraderApi(config->homepath.string().c_str());
	tradeApi->RegisterSpi(tradeSpi);
	tradeApi->SubscribePublicTopic(THOST_TERT_RESTART);
	tradeApi->SubscribePrivateTopic(THOST_TERT_RESTART);
	tradeApi->RegisterFront(config->tradeFrontAddr);

	quoteApi->Join();
	tradeApi->Join();

	///TODO: LOOPING

	delete quoteSpi;
	delete tradeSpi;
	quoteApi->Release();
	tradeApi->Release();
	delete logger;
	delete config;
	return true;
}