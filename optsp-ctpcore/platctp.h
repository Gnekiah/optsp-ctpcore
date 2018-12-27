#ifndef OPTSP_CTPCORE_PLATCTP_H_
#define OPTSP_CTPCORE_PLATCTP_H_

#include "ctpapi/ThostFtdcMdApi.h"
#include "ctpapi/ThostFtdcTraderApi.h"
#include "ctpapi/ThostFtdcUserApiDataType.h"
#include "ctpapi/ThostFtdcUserApiStruct.h"
//#pragma comment (lib, "ctpapi/thostmduserapi.lib")
//#pragma comment (lib, "ctpapi/thosttraderapi.lib")

#include <mutex>
#include <atomic>
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
	///called by spi
	quote_callback_fn quote_callback = nullptr;
	trade_callback_fn trade_callback = nullptr;
	///called by current instance
	plat_callback_fn plat_callback = nullptr;

	QuoteSpi * quoteSpi = nullptr;
	TradeSpi * tradeSpi = nullptr;
	CThostFtdcMdApi * quoteApi = nullptr;
	CThostFtdcTraderApi * tradeApi = nullptr;

	int nInstrumentID;
	char *instrumentIDs[PLATCTP_INSTRUMENT_MAX];
	boost::lockfree::queue<PlatCmdField> *cmdQueue = nullptr;

public:
	std::atomic_int quoteState;		///���QuoteApi��״̬
	std::atomic_int tradeState;		///���TradeApi��״̬

public:
	PlatCtp(Config * config, Logger * logger, quote_callback_fn qfn, trade_callback_fn tfn, plat_callback_fn pfn);
	///Insert cmd. into plat.
	///int cmdtype - CMD������
	///int cmdid - �����ID, ���·�����ʱ����
	///bool flag - ��������Ƿ���Ч
	///void* ptr - ָ������������׵�ַָ��
	void InsertCommand(int cmdtype, int cmdid, bool flag, void* ptr);
	void run();

private:
	///Quote cmd.
	int DoQuoteLogin(PlatCmdField &);
	int DoQuoteSubscribe(PlatCmdField &);

	///Trade cmd.
	int DoTradeAuthenticate(PlatCmdField &);
	int DoTradeLogin(PlatCmdField &);
	int DoTradeSettlementConfirm(PlatCmdField &);
	int DoTradeQryInstrument(PlatCmdField &);
};

#endif // !OPTSP_CTPCORE_PLATCTP_H_

