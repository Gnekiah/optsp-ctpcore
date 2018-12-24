#include "platctp.h"
#include <boost/filesystem.hpp>
#include "arch.h"


PlatCtp::PlatCtp(Config * config, Logger * logger, quote_callback_fn qfn, trade_callback_fn tfn, cmd_callback_fn pfn)
	: config(config), logger(logger), quote_callback(qfn), trade_callback(tfn), cmd_callback(pfn)
{
	std::stringstream log;
	cmdfn = this;
	cmdQueue = new boost::lockfree::queue<PlatCmdField>(64);

	quoteSpi = new QuoteSpi(logger, quote_callback, CmdCallBack);
	tradeSpi = new TradeSpi(logger, trade_callback, CmdCallBack);
	
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
	PlatCmdField cmd = { 0 };
	cmd.Type = rqtype;
	cmd.Id = rqid;
	cmd.Flag = true;
	switch (rqtype) {
	case CMD_TRADE_QRY_INSTRUMENT:
		arch_Memcpy(&cmd.Instrument, ptr, sizeof(cmd.Instrument));
		break;
	}

	lock.lock();
	cmdQueue->push(cmd);
	lock.unlock();
}


void PlatCtp::InsertCommand(int cmdtype, int cmdid, bool flag, void* ptr)
{
	PlatCmdField cmd = { 0 };
	cmd.Type = cmdtype;
	cmd.Id = cmdid;
	cmd.Flag = flag;
	if (flag) {
		///Do copy from ptr to cmd.data
		///ptr is always empty in current version
		switch (cmdtype) {

		}
	}

	lock.lock();
	cmdQueue->push(cmd);
	lock.unlock();
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


void CmdCallBack(int cmdtype, int cmdid, bool flag, void* ptr)
{
	PlatCtp *plat = (PlatCtp*)cmdfn;
	plat->InsertCommand(cmdtype, cmdid, flag, ptr);
}