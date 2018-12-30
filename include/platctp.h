#ifndef OPTSP_CTPCORE_PLATCTP_H_
#define OPTSP_CTPCORE_PLATCTP_H_

#include "ctpapi.hpp"

#include <mutex>
#include <atomic>
#include <boost/lockfree/queue.hpp>
#include "../platctp/quotespi.h"
#include "../platctp/tradespi.h"
#include "config.h"
#include "platstruct.hpp"
#include "datatype.hpp"


static void* cbfn = nullptr;
void CtpspiCallBack(int cbtype, void* ptr);


class PlatCtp
{
private:
    Config * config = nullptr;
    Logger * logger = nullptr;
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
    std::atomic_int quoteState;        ///标记QuoteApi的状态
    std::atomic_int tradeState;        ///标记TradeApi的状态

public:
    PlatCtp(Config * config, Logger * logger, plat_callback_fn pfn);
    ///Insert cmd. into plat.
    ///int cmdtype - CMD的类型
    ///int cmdid - 命令的ID, 由下发命令时分配
    ///void* ptr - 指向数据区域的首地址指针
    void InsertCommand(int cmdtype, int cmdid, void* ptr);
    void run();

private:
    ///Quote cmd.
    int DoQuoteLogin(PlatCmdField &);
    int DoQuoteSubscribe(PlatCmdField &);

    ///Trade cmd.
    int DoTradeAuthenticate(PlatCmdField &);
    int DoTradeLogin(PlatCmdField &);
    int DoTradeSettlementConfirm(PlatCmdField &);
    int DoTradeQryExchange(PlatCmdField &);
    int DoTradeQryProduct(PlatCmdField &);
    int DoTradeQryInstrument(PlatCmdField &);
};

#endif // !OPTSP_CTPCORE_PLATCTP_H_

