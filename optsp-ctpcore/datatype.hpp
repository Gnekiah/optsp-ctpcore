#ifndef OPTSP_CTPCORE_DATATYPE_HPP_
#define OPTSP_CTPCORE_DATATYPE_HPP_

#include "ctpapi/ThostFtdcUserApiDataType.h"



#define	MAFIELD_MACNT_MAX					5		///MA指标的最大数量
#define	LOGGER_FLUSH_INTERVAL				5000	///日志刷入间隔，单位毫秒
#define PLATCTP_INSTRUMENT_MAX				10240	///用于保存合约的数组最大长度


///callback label: QuoteSpi to StGroup
#define CB_QUOTE_CONNECTED								0x00000001
#define	CB_QUOTE_DISCONNECTED							0x00000002
#define CB_QUOTE_RSP_USER_LOGIN							0x00000003
#define CB_QUOTE_RSP_USER_LOGOUT						0x00000004
#define CB_QUOTE_RSP_SUB_MARKET_DATA					0x00000005
#define	CB_QUOTE_RSP_UNSUB_MARKET_DATA					0x00000006
#define CB_QUOTE_RTN_DEPTH_MARKET_DATA					0x00000007

///callback label: TradeSpip to StGroup
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
#define CB_TRADE_RSP_QRY_EXCHANGE	0x20000000//TODO
#define	CB_TRADE_RSP_QRY_PRODUCT	0x20000001//TODO
#define CB_TRADE_RSP_QRY_INSTRUMENT						0x10002002
#define CB_TRADE_RSP_QRY_TRADING_ACCOUNT				0x10002003
#define CB_TRADE_RSP_QRY_INVESTOR						0x10002004

#define CB_TRADE_RSP_ORDER_INSERT						0x10003001
#define CB_TRADE_RSP_ORDER_ACTION						0x10003002
#define CB_TRADE_RTN_ORDER								0x10003003
#define CB_TRADE_RTN_TRADE								0x10003004
#define CB_TRADE_ERR_RTN_ORDER_INSERT					0x10003005
#define	CB_TRADE_ERR_RTN_ORDER_ACTION					0x10003006

///向Plat.插入命令时，要指定命令的唯一ID，即nRequestID
///上层下发的命令ID由ST. group分配
///下层回调的ID分别为-1和-2
#define	CMDID_QUOTE		-1
#define	CMDID_TRADE		-2

///callback label: QuoteSpi to Plat.
///通知类型的回调
///连接 -> 登录 -> 等待TradeReady后订阅 -> Ready
#define CB_CMD_QUOTE_LOGIN								0x20000001
#define	CB_CMD_QUOTE_SUBSCRIBE							0x20000002

///callback label: TradeSpi to Plat.
///通知类型的回调
///连接 -> 验证 -> 登录 -> 结算确认 -> 查询合约 -> Ready
///结算确认过程: ReqQrySettlementInfoConfirm -> ReqQrySettlementInfo -> ReqSettlementInfoConfirm
#define CB_CMD_TRADE_AUTHENTICATE						0x30000001
#define	CB_CMD_TRADE_LOGIN								0x30000002
#define	CB_CMD_TRADE_SETTLEMENT_CONFIRM					0x30000003

#define CB_CMD_TRADE_QRY_EXCHANGE						0x30001001
#define CB_CMD_TRADE_QRY_EXCHANGE_COMPLETED				0x30001002
#define CB_CMD_TRADE_QRY_PRODUCT						0x30001003
#define CB_CMD_TRADE_QRY_PRODUCT_COMPLETED				0x30001004
#define CB_CMD_TRADE_QRY_INSTRUMENT						0x30001005
#define CB_CMD_TRADE_QRY_INSTRUMENT_COMPLETED			0x30001006
///非通知类型的回调
#define CB_CMD_TRADE_RSP_QRY_INSTRUMENT					0x30001001


///command label: StGroup to Plat.
//TODO: #define	CMD_STG_......	0x40000001
//#define CMD_STG_TRADE_QRY_INSTRUMENT						0x30000004

///command label: Front to StGroup
//TODO: #define CMD_FRONT_.....	0x50000001

///callback label: StGroup to front
//TODO: #define CB_STG_.....	0x60000001



/* log_callback		由logger向front传递日志的回调
* stgroup_callback	由stgroup向front传递策略组实时状态的回调
* quote_callback	由plat/quoteSpi回调向stgroup传递行情数据的回调
* trade_callback	由plat/tradeSpi回调向stgroup传递交易结果的回调
* plat_callback	由plat向stgroup传递发送交易命令成功/失败的回调
*					以及由plat/*Spi回调向plat传递初始化命令的回调
*/
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
///命令的回调函数指针
///int cbtype - CMD的回调类型
///int cmdid - 命令的ID, 由下发命令时分配，对应API和SPI的nRequestID
///bool flag - 标记回调数据是否有效
///void* ptr - 指向回调的数据区域的首地址指针
typedef void(*plat_callback_fn) (int, int, bool, void*);




typedef char MdCsvFormatType[128];									///行情CSV保存格式类型
typedef char FrontAddrType[64];										///前置地址类型
typedef char DateTimeType[24];										///时间字符串类型, yyyy-MM-dd hh:mm:ss.zzz
typedef char ProductNameType[24];									///产品名称 - 用于TradeApi的验证
typedef char AuthenticateCodeType[32];								///验证编码 - 用于TradeApi的验证
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

