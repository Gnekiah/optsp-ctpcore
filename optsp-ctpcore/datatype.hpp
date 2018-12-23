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



#define	MAFIELD_MACNT_MAX					5		///MA指标的最大数量
#define	LOGGER_FLUSH_INTERVAL				5000	///日志刷入间隔，单位毫秒


///日志处理的回调函数指针
///int loglevel - 日志记录等级
///const char* ptr - 单条日志缓冲区的首地址指针
typedef void(*log_callback_fn) (int, const char*);
///策略组实时状态回调函数指针
///int cbtype - CB_STGROUP的回调类型
///void* ptr - 回调返回的数据区域的首地址指针
typedef void(*stgroup_callback_fn) (int, void*);
///行情接口的回调函数指针
///int cbtype - CB_QUOTE的回调类型
///bool flag - 标记回调数据是否有效
///void* ptr - 指向回调的数据区域的首地址指针
typedef void(*quote_callback_fn) (int, bool, void*);
///交易接口的回调函数指针
///int cbtype - CB_TRADE的回调类型
///bool flag - 标记回调数据是否有效
///void* ptr - 指向回调的数据区域的首地址指针
typedef void(*trade_callback_fn) (int, bool, void*);
///ST下发的交易命令的回调函数指针
///int cbtype - CB_TRADE_CMD的回调类型
///int cmdid - 用于ST_GROUP唯一确定一个下发命令的ID, 由下发命令时分配
///bool flag - 标记回调数据是否有效
///void* ptr - 指向回调的数据区域的首地址指针
typedef void(*platcmd_callback_fn) (int, int, bool, void*);


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

