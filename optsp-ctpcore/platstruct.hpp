#ifndef OPTSP_CTPCORE_PLATSTRUCT_HPP_
#define OPTSP_CTPCORE_PLATSTRUCT_HPP_

#include <atomic>
#include "datatype.hpp"
#include "quotestruct.hpp"
#include "tradestruct.hpp"


#define		PLTSYNC_INIT					0x00

#define		PLTSYNC_QUOTE_CONNECTED			0x11
#define		PLTSYNC_QUOTE_LOGINED			0x12

#define		PLTSYNC_TRADE_CONNECTED			0x21
#define		PLTSYNC_TRADE_AUTHENTICATED		0x22
#define		PLTSYNC_TRADE_LOGINED			0x23


#define RSPINFO_ERROR(log, rsp, msg) do { \
	log << msg; \
	if (rsp) \
		log << ", ErrorID=" << rsp->ErrorID << ", ErrorMsg=" << rsp->ErrorMsg; \
	else \
		log << ", pRspInfo == NULL"; \
	LOGERR(logger, log); \
} while(0)


typedef struct QuoteSyncField {
	std::atomic_bool		QuoteActive;
	std::atomic_int			QuoteState;
} QuoteSyncField;


typedef struct TradeSyncField {
	std::atomic_bool		TradeActive;
	std::atomic_int			TradeState;
} TradeSyncField;


typedef union TradeCmdField {
	InstrumentField			Instrument;
	OrderField				Order;
	CapitalField			Capital;
	MatchField				Match;
	PositionField			Position;
} TradeCmdField;

#endif // !OPTSP_CTPCORE_PLATSTRUCT_HPP_

