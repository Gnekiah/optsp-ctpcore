#ifndef OPTSP_CTPCORE_DATATYPE_HPP_
#define OPTSP_CTPCORE_DATATYPE_HPP_

#include "ctpapi/ThostFtdcUserApiDataType.h"



#define	MAFIELD_MACNT_MAX					5		///MAָ����������
#define	LOGGER_FLUSH_INTERVAL				5000	///��־ˢ��������λ����
#define PLATCTP_INSTRUMENT_MAX				10240	///���ڱ����Լ��������󳤶�


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

///��Plat.��������ʱ��Ҫָ�������ΨһID����nRequestID
///�ϲ��·�������ID��ST. group����
///�²�ص���ID�ֱ�Ϊ-1��-2
#define	CMDID_QUOTE		-1
#define	CMDID_TRADE		-2

///callback label: QuoteSpi to Plat.
///֪ͨ���͵Ļص�
///���� -> ��¼ -> �ȴ�TradeReady���� -> Ready
#define CB_CMD_QUOTE_LOGIN								0x20000001
#define	CB_CMD_QUOTE_SUBSCRIBE							0x20000002

///callback label: TradeSpi to Plat.
///֪ͨ���͵Ļص�
///���� -> ��֤ -> ��¼ -> ����ȷ�� -> ��ѯ��Լ -> Ready
///����ȷ�Ϲ���: ReqQrySettlementInfoConfirm -> ReqQrySettlementInfo -> ReqSettlementInfoConfirm
#define CB_CMD_TRADE_AUTHENTICATE						0x30000001
#define	CB_CMD_TRADE_LOGIN								0x30000002
#define	CB_CMD_TRADE_SETTLEMENT_CONFIRM					0x30000003

#define CB_CMD_TRADE_QRY_EXCHANGE						0x30001001
#define CB_CMD_TRADE_QRY_EXCHANGE_COMPLETED				0x30001002
#define CB_CMD_TRADE_QRY_PRODUCT						0x30001003
#define CB_CMD_TRADE_QRY_PRODUCT_COMPLETED				0x30001004
#define CB_CMD_TRADE_QRY_INSTRUMENT						0x30001005
#define CB_CMD_TRADE_QRY_INSTRUMENT_COMPLETED			0x30001006
///��֪ͨ���͵Ļص�
#define CB_CMD_TRADE_RSP_QRY_INSTRUMENT					0x30001001


///command label: StGroup to Plat.
//TODO: #define	CMD_STG_......	0x40000001
//#define CMD_STG_TRADE_QRY_INSTRUMENT						0x30000004

///command label: Front to StGroup
//TODO: #define CMD_FRONT_.....	0x50000001

///callback label: StGroup to front
//TODO: #define CB_STG_.....	0x60000001



/* log_callback		��logger��front������־�Ļص�
* stgroup_callback	��stgroup��front���ݲ�����ʵʱ״̬�Ļص�
* quote_callback	��plat/quoteSpi�ص���stgroup�����������ݵĻص�
* trade_callback	��plat/tradeSpi�ص���stgroup���ݽ��׽���Ļص�
* plat_callback	��plat��stgroup���ݷ��ͽ�������ɹ�/ʧ�ܵĻص�
*					�Լ���plat/*Spi�ص���plat���ݳ�ʼ������Ļص�
*/
///��־����Ļص�����ָ��
///int loglevel - ��־��¼�ȼ�
///const char* ptr - ������־���������׵�ַָ��
typedef void(*log_callback_fn) (int, const char*);
///������ʵʱ״̬�ص�����ָ��
///int cbtype - CB_STGROUP�Ļص�����
///void* ptr - �ص����ص�����������׵�ַָ��
typedef void(*stgroup_callback_fn) (int, void*);
///����ӿڵĻص�����ָ��
///int cbtype - CB_QUOTE�Ļص�����
///bool flag - ��ǻص������Ƿ���Ч
///void* ptr - ָ��ص�������������׵�ַָ��
typedef void(*quote_callback_fn) (int, bool, void*);
///���׽ӿڵĻص�����ָ��
///int cbtype - CB_TRADE�Ļص�����
///bool flag - ��ǻص������Ƿ���Ч
///void* ptr - ָ��ص�������������׵�ַָ��
typedef void(*trade_callback_fn) (int, bool, void*);
///����Ļص�����ָ��
///int cbtype - CMD�Ļص�����
///int cmdid - �����ID, ���·�����ʱ���䣬��ӦAPI��SPI��nRequestID
///bool flag - ��ǻص������Ƿ���Ч
///void* ptr - ָ��ص�������������׵�ַָ��
typedef void(*plat_callback_fn) (int, int, bool, void*);




typedef char MdCsvFormatType[128];									///����CSV�����ʽ����
typedef char FrontAddrType[64];										///ǰ�õ�ַ����
typedef char DateTimeType[24];										///ʱ���ַ�������, yyyy-MM-dd hh:mm:ss.zzz
typedef char ProductNameType[24];									///��Ʒ���� - ����TradeApi����֤
typedef char AuthenticateCodeType[32];								///��֤���� - ����TradeApi����֤
typedef TThostFtdcBrokerIDType BrokerIDType;						///���͹�˾��������
typedef TThostFtdcUserIDType UserIDType;							///�û���������
typedef TThostFtdcInvestorIDType InvestorIDType;					///Ͷ���ߴ�������
typedef TThostFtdcInstrumentIDType InstrumentIDType;				///��Լ��������
typedef TThostFtdcPasswordType PasswordType;						///��������
typedef TThostFtdcExchangeIDType ExchangeIDType;					///��������������
typedef TThostFtdcInstrumentNameType InstrumentNameType;			///��Լ��������
typedef TThostFtdcExchangeInstIDType ExchangeInstIDType;			///��Լ�ڽ������Ĵ�������
typedef TThostFtdcCurrencyIDType CurrencyIDType;					///���ִ�������

#endif // !OPTSP_CTPCORE_DATATYPE_HPP_

