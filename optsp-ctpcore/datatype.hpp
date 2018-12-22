#ifndef OPTSP_CTPCORE_DATATYPE_HPP_
#define OPTSP_CTPCORE_DATATYPE_HPP_

#include "ctpapi/ThostFtdcUserApiDataType.h"


#define CB_QUOTE_CONNECTED								0x00000001
#define	CB_QUOTE_DISCONNECTED							0x00000002
#define CB_QUOTE_RSP_USER_LOGIN							0x00000003
#define CB_QUOTE_RSP_USER_LOGOUT						0x00000004
#define CB_QUOTE_RSP_SUB_MARKET_DATA					0x00000005
#define	CB_QUOTE_RSP_UNSUB_MARKET_DATA					0x00000006
#define CB_QUOTE_RTN_DEPTH_MARKET_DATA					0x00000007


#define CB_TRADE_CONNECTED								0x10000001
#define	CB_TRADE_DISCONNECTED							0x10000002
#define CB_TRADE_RSP_AUTHENTICATE						0x10000003
#define CB_TRADE_RSP_USER_LOGIN							0x10000004
#define CB_TRADE_RSP_USER_LOGOUT						0x10000005
#define CB_TRADE_RSP_USER_PASSWD_UPDATE					0x10000006
#define CB_TRADE_RSP_TRADING_ACCOUNT_PASSWD_UPDATE		0x10000007
#define CB_TRADE_RSP_QRY_SETTLEMENT_INFO				0x10001001
#define CB_TRADE_RSP_QRY_SETTLEMENT_INFO_CONFIRM		0x10001002
#define CB_TRADE_RSP_SETTLEMENT_INFO_CONFIRM			0x10001003
#define CB_TRADE_RSP_QRY_INVESTOR_POSITION				0x10002001
#define CB_TRADE_RSP_QRY_INSTRUMENT						0x10002002
#define CB_TRADE_RSP_QRY_TRADING_ACCOUNT				0x10002003
#define CB_TRADE_RSP_QRY_INVESTOR						0x10002004
#define CB_TRADE_RSP_ORDER_INSERT						0x10003001
#define CB_TRADE_RSP_ORDER_ACTION						0x10003002
#define CB_TRADE_RTN_ORDER								0x10003003
#define CB_TRADE_RTN_TRADE								0x10003004
#define CB_TRADE_ERR_RTN_ORDER_INSERT					0x10003005
#define	CB_TRADE_ERR_RTN_ORDER_ACTION					0x10003006



#define	MAFIELD_MACNT_MAX		5


typedef void(*quote_callback_fn) (int, bool, void*);
typedef void(*trade_callback_fn) (int, bool, void*);
typedef void(*stgroup_callback_fn) (int, bool, void*);


typedef char MdCsvFormatType[128];									///行情CSV保存格式类型
typedef char FrontAddrType[64];										///前置地址类型
typedef char DateTimeType[24];										///时间字符串类型, yyyy-MM-dd hh:mm:ss.zzz
typedef TThostFtdcBrokerIDType BrokerIDType;						///经纪公司代码类型
typedef TThostFtdcUserIDType UserIDType;							///用户代码类型
typedef TThostFtdcInvestorIDType InvestorIDType;					///投资者代码类型
typedef TThostFtdcInstrumentIDType InstrumentIDType;				///合约代码类型
typedef TThostFtdcPasswordType PasswordType;						///口令类型
typedef TThostFtdcExchangeIDType ExchangeIDType;					///交易所代码类型
typedef TThostFtdcInstrumentNameType InstrumentNameType;			///合约名称类型
typedef TThostFtdcExchangeInstIDType ExchangeInstIDType;			///合约在交易所的代码类型
typedef TThostFtdcCurrencyIDType CurrencyIDType;					///币种代码类型

#endif // !OPTSP_CTPCORE_DATATYPE_HPP_

