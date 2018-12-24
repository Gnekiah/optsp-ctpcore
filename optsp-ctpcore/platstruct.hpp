#ifndef OPTSP_CTPCORE_PLATSTRUCT_HPP_
#define OPTSP_CTPCORE_PLATSTRUCT_HPP_

#include <atomic>
#include "datatype.hpp"
#include "quotestruct.hpp"
#include "tradestruct.hpp"


#define RSPINFO_ERROR(log, rsp, msg) do { \
	log << msg; \
	if (rsp) \
		log << ", ErrorID=" << rsp->ErrorID << ", ErrorMsg=" << rsp->ErrorMsg; \
	else \
		log << ", pRspInfo == NULL"; \
	LOGERR(logger, log); \
} while(0)


/*	shadowed

#define		PLTSYNC_INIT					0x00

#define		PLTSYNC_QUOTE_CONNECTED			0x11
#define		PLTSYNC_QUOTE_LOGINED			0x12

#define		PLTSYNC_TRADE_CONNECTED			0x21
#define		PLTSYNC_TRADE_AUTHENTICATED		0x22
#define		PLTSYNC_TRADE_LOGINED			0x23

typedef struct QuoteSyncField {
	std::atomic_bool		QuoteActive;
	std::atomic_int			QuoteState;
} QuoteSyncField;


typedef struct TradeSyncField {
	std::atomic_bool		TradeActive;
	std::atomic_int			TradeState;
} TradeSyncField;
*/


typedef struct PlatCmdField {
	 union {
		InstrumentField			Instrument;
		OrderField				Order;
		CapitalField			Capital;
		MatchField				Match;
		PositionField			Position;
	};
	 int Type;										///命令类型
	 int Id;										///命令的ID；来自lower层的命令的ID为负，分别为-1和-2
	 bool Flag;										///标记该cmd的union区域是否有有效数据
} PlatCmdField;

#endif // !OPTSP_CTPCORE_PLATSTRUCT_HPP_

