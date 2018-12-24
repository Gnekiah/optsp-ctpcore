#ifndef OPTSP_CTPCORE_PLATCTP_H_
#define OPTSP_CTPCORE_PLATCTP_H_

#include "ctpapi/ThostFtdcMdApi.h"
#include "ctpapi/ThostFtdcTraderApi.h"
#include "ctpapi/ThostFtdcUserApiDataType.h"
#include "ctpapi/ThostFtdcUserApiStruct.h"
#pragma comment (lib, "ctpapi/thostmduserapi.lib")
#pragma comment (lib, "ctpapi/thosttraderapi.lib")

#include <mutex>
#include <boost/lockfree/queue.hpp>
#include "quotespi.h"
#include "tradespi.h"
#include "config.h"
#include "platstruct.hpp"
#include "datatype.hpp"


static void* cmdfn = nullptr;
void CmdCallBack(int cmdtype, int cmdid, bool flag, void* ptr);


class PlatCtp
{
private:
	Config * config = nullptr;
	Logger * logger = nullptr;

	quote_callback_fn quote_callback = nullptr;
	trade_callback_fn trade_callback = nullptr;
	cmd_callback_fn cmd_callback = nullptr;

	QuoteSpi * quoteSpi = nullptr;
	TradeSpi * tradeSpi = nullptr;
	CThostFtdcMdApi * quoteApi = nullptr;
	CThostFtdcTraderApi * tradeApi = nullptr;

	std::mutex lock;
	boost::lockfree::queue<PlatCmdField> *cmdQueue = nullptr;

public:
	PlatCtp(Config * config, Logger * logger, quote_callback_fn qfn, trade_callback_fn tfn, cmd_callback_fn pfn);
	void InsertCommand(int rqtype, int rqid, void* ptr);					///Insert cmd. by upper ST. Group
	void InsertCommand(int cmdtype, int cmdid, bool flag, void* ptr);		///Insert cmd. from lower plat.
	void run();

private:
	///Quote cmd.
	int DoQuoteLogin();
	int DoQuoteSubscribe();
	int DoQuoteSubscribeAll();

	///Trade cmd.
	int DoTradeAuthenticate();
	int DoTradeLogin();
	int DoTradeSettlementInfoConfirm();
	int DoTradeQryInstrument();
};

#endif // !OPTSP_CTPCORE_PLATCTP_H_

