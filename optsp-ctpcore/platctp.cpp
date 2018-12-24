#include "platctp.h"
#include <boost/filesystem.hpp>
#include "arch.h"


PlatCtp::PlatCtp(Config * config, Logger * logger, quote_callback_fn qfn, trade_callback_fn tfn, platcmd_callback_fn pfn)
	: config(config), logger(logger), quote_callback(qfn), trade_callback(tfn), platcmd_callback(pfn)
{
	std::stringstream log;
	quoteSync = new QuoteSyncField;
	tradeSync = new TradeSyncField;
	quoteSpi = new QuoteSpi(logger, quoteSync, quote_callback);
	tradeSpi = new TradeSpi(logger, tradeSync, trade_callback);
	
	quoteApi = CThostFtdcMdApi::CreateFtdcMdApi(config->homepath.string().c_str());
	quoteApi->RegisterSpi(quoteSpi);
	quoteApi->RegisterFront(config->quoteFrontAddr);

	tradeApi = CThostFtdcTraderApi::CreateFtdcTraderApi(config->homepath.string().c_str());
	tradeApi->RegisterSpi(tradeSpi);
	tradeApi->SubscribePublicTopic(THOST_TERT_RESTART);
	tradeApi->SubscribePrivateTopic(THOST_TERT_RESTART);
	tradeApi->RegisterFront(config->tradeFrontAddr);

	log << "CTP Registered";
	LOGINFO(logger, log);
}


void PlatCtp::InsertCommand(int rqtype, int rqid, void* ptr)
{

}


void PlatCtp::run()
{
	int ret = 0;
	std::stringstream log;
	quoteApi->Init();
	tradeApi->Init();

	log << "Looping...";
	LOGINFO(logger, log);

	while (true) {
		arch_Sleep(500);


	}

	///TODO: looping

	quoteApi->Join();
	tradeApi->Join();
	delete quoteSpi;
	delete tradeSpi;
	quoteApi->Release();
	tradeApi->Release();
}