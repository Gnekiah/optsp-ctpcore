#ifndef OPTSP_CTPCORE_PLATSTRUCT_HPP_
#define OPTSP_CTPCORE_PLATSTRUCT_HPP_

#include <atomic>

#define		PLTSYNC_INITED					0x00
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

#endif // !OPTSP_CTPCORE_PLATSTRUCT_HPP_

