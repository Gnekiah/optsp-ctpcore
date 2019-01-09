#ifndef OPTSP_CTPCORE_DATATYPE_HPP_
#define OPTSP_CTPCORE_DATATYPE_HPP_

#include "ctpapi.hpp"


#define MAFIELD_MACNT_MAX                       5           ///MA指标的最大数量
#define LOGGER_FLUSH_INTERVAL                   5000        ///日志刷入间隔，单位毫秒
#define PLATCTP_INSTRUMENT_MAX                  1024        ///用于保存合约的数组最大长度



#define CB_QUOTE_TYPE_START         0x00000000
#define CB_TRADE_TYPE_START         0x10000000

/********** Quote回调类型 **********/
#define CB_QUOTE_FRONT_CONNECTED                                    0x00000001  ///客户端与交易后台建立起通信连接
#define CB_QUOTE_FRONT_DISCONNECTED                                 0x00000002  ///客户端与交易后台通信连接断开，API会自动重新连接，客户端可不做处理
#define CB_QUOTE_RSP_USER_LOGIN                                     0x00000003  ///登录请求响应
#define CB_QUOTE_RSP_USER_LOGOUT                                    0x00000004  ///登出请求响应
#define CB_QUOTE_RSP_ERROR                                          0x00000005  ///错误应答
#define CB_QUOTE_HEART_BEAT_WARNING                                 0x00000006  ///心跳超时警告
#define CB_QUOTE_RSP_SUB_MARKET_DATA                                0x00010001  ///订阅行情应答
#define CB_QUOTE_RSP_UNSUB_MARKET_DATA                              0x00010002  ///取消订阅行情应答
#define CB_QUOTE_RSP_SUB_FOR_QUOTE_RSP                              0x00010003  ///订阅询价应答
#define CB_QUOTE_RSP_UNSUB_FOR_QUOTE_RSP                            0x00010004  ///取消订阅询价应答
#define CB_QUOTE_RTN_DEPTH_MARKET_DATA                              0x00010101  ///深度行情通知
#define CB_QUOTE_RTN_FOR_QUOTE_RSP                                  0x00010102  ///询价通知

/********** Trade回调类型 **********/
#define CB_TRADE_FRONT_CONNECTED                                    0x10000001  ///客户端与交易后台建立起通信连接
#define CB_TRADE_FRONT_DISCONNECTED                                 0x10000002  ///客户端与交易后台通信连接断开，API会自动重新连接，客户端可不做处理
#define CB_TRADE_RSP_AUTHENTICATE                                   0x10000003  ///客户端认证响应
#define CB_TRADE_RSP_USER_LOGIN                                     0x10000004  ///登录请求响应
#define CB_TRADE_RSP_USER_LOGOUT                                    0x10000005  ///登出请求响应
#define CB_TRADE_RSP_ERROR                                          0x10000006  ///错误应答
#define CB_TRADE_HEART_BEAT_WARNING                                 0x10000007  ///心跳超时警告
/********** 口令与密钥相关 **********/
#define CB_TRADE_RSP_USER_PASSWORD_UPDATE                           0x10010001  ///用户口令更新请求响应
#define CB_TRADE_RSP_TRADING_ACCOUNT_PASSWORD_UPDATE                0x10010002  ///资金账户口令更新请求响应
/********** 预埋单 **********/
#define CB_TRADE_RSP_PARKED_ORDER_INSERT                            0x10020001  ///预埋单录入请求响应
#define CB_TRADE_RSP_PARKED_ORDER_ACTION                            0x10020002  ///预埋撤单录入请求响应
#define CB_TRADE_RSP_QRY_PARKED_ORDER                               0x10020101  ///请求查询预埋单响应
#define CB_TRADE_RSP_QRY_PARKED_ORDER_ACTION                        0x10020102  ///请求查询预埋撤单响应
#define CB_TRADE_RSP_REMOVE_PARKED_ORDER                            0x10020201  ///删除预埋单响应
#define CB_TRADE_RSP_REMOVE_PARKED_ORDER_ACTION                     0x10020202  ///删除预埋撤单响应
/********** 下单 **********/
#define CB_TRADE_RSP_ORDER_INSERT                                   0x10030001  ///报单录入请求响应
#define CB_TRADE_RSP_ORDER_ACTION                                   0x10030002  ///报单操作请求响应
#define CB_TRADE_RSP_QRY_ORDER                                      0x10030101  ///请求查询报单响应
#define CB_TRADE_RSP_QRY_TRADE                                      0x10030102  ///请求查询成交响应
#define CB_TRADE_RTN_ORDER                                          0x10030201  ///报单通知
#define CB_TRADE_RTN_TRADE                                          0x10030202  ///成交通知
#define CB_TRADE_ERR_RTN_ORDER_INSERT                               0x10030301  ///报单录入错误回报
#define CB_TRADE_ERR_RTN_ORDER_ACTION                               0x10030302  ///报单操作错误回报
/********** 报价 **********/
#define CB_TRADE_RSP_FOR_QUOTE_INSERT                               0x10040001  ///询价录入请求响应
#define CB_TRADE_RSP_QUOTE_INSERT                                   0x10040002  ///报价录入请求响应
#define CB_TRADE_RSP_QUOTE_ACTION                                   0x10040003  ///报价操作请求响应
#define CB_TRADE_RSP_BATCH_ORDER_ACTION                             0x10040004  ///批量报单操作请求响应
#define CB_TRADE_RSP_QRY_FOR_QUOTE                                  0x10040101  ///请求查询询价响应
#define CB_TRADE_RSP_QRY_QUOTE                                      0x10040102  ///请求查询报价响应
#define CB_TRADE_RTN_FOR_QUOTE_RSP                                  0x10040201  ///询价通知
#define CB_TRADE_RTN_QUOTE                                          0x10040202  ///报价通知
#define CB_TRADE_ERR_RTN_FOR_QUOTE_INSERT                           0x10040301  ///询价录入错误回报
#define CB_TRADE_ERR_RTN_QUOTE_INSERT                               0x10040302  ///报价录入错误回报
#define CB_TRADE_ERR_RTN_QUOTE_ACTION                               0x10040303  ///报价操作错误回报
#define CB_TRADE_ERR_RTN_BATCH_ORDER_ACTION                         0x10040304  ///批量报单操作错误回报
/********** 执行宣告 **********/
#define CB_TRADE_RSP_EXEC_ORDER_INSERT                              0x10050001  ///执行宣告录入请求响应
#define CB_TRADE_RSP_EXEC_ORDER_ACTION                              0x10050002  ///执行宣告操作请求响应
#define CB_TRADE_RSP_QRY_EXEC_ORDER                                 0x10050101  ///请求查询执行宣告响应
#define CB_TRADE_RTN_EXEC_ORDER                                     0x10050201  ///执行宣告通知
#define CB_TRADE_ERR_RTN_EXEC_ORDER_INSERT                          0x10050301  ///执行宣告录入错误回报
#define CB_TRADE_ERR_RTN_EXEC_ORDER_ACTION                          0x10050302  ///执行宣告操作错误回报
/********** 组合相关 **********/
#define CB_TRADE_RSP_COMB_ACTION_INSERT                             0x10060001  ///申请组合录入请求响应
#define CB_TRADE_RSP_QRY_COMB_ACTION                                0x10060101  ///请求查询申请组合响应
#define CB_TRADE_RSP_QRY_INVEST_UNIT                                0x10060102  ///请求查询投资单元响应
#define CB_TRADE_RSP_QRY_PRODUCT_GROUP                              0x10060103  ///请求查询产品组
#define CB_TRADE_RSP_QRY_COMB_INSTRUMENT_GUARD                      0x10060104  ///请求查询组合合约安全系数响应
#define CB_TRADE_RTN_COMB_ACTION                                    0x10060201  ///申请组合通知
#define CB_TRADE_ERR_RTN_COMB_ACTION_INSERT                         0x10060301  ///申请组合录入错误回报
/********** 期权相关 **********/
#define CB_TRADE_RSP_OPTION_SELF_CLOSE_INSERT                       0x10070001  ///期权自对冲录入请求响应
#define CB_TRADE_RSP_OPTION_SELF_CLOSE_ACTION                       0x10070002  ///期权自对冲操作请求响应
#define CB_TRADE_RSP_QRY_OPTION_SELF_CLOSE                          0x10070101  ///请求查询期权自对冲响应
#define CB_TRADE_RSP_QRY_OPTION_INSTR_COMM_RATE                     0x10070102  ///请求查询期权合约手续费响应
#define CB_TRADE_RSP_QRY_OPTION_INSTR_TRADE_COST                    0x10070103  ///请求查询期权交易成本响应
#define CB_TRADE_RTN_OPTION_SELF_CLOSE                              0x10070201  ///期权自对冲通知
#define CB_TRADE_ERR_RTN_OPTION_SELF_CLOSE_INSERT                   0x10070301  ///期权自对冲录入错误回报
#define CB_TRADE_ERR_RTN_OPTION_SELF_CLOSE_ACTION                   0x10070302  ///期权自对冲操作错误回报
/********** 投资者结算结果 **********/
#define CB_TRADE_RSP_SETTLEMENT_INFO_CONFIRM                        0x10080001  ///投资者结算结果确认响应
#define CB_TRADE_RSP_QRY_SETTLEMENT_INFO                            0x10080101  ///请求查询投资者结算结果响应
#define CB_TRADE_RSP_QRY_SETTLEMENT_INFO_CONFIRM                    0x10080102  ///请求查询结算信息确认响应
/********** 银行发起操作的通知 **********/
#define CB_TRADE_RTN_FROM_BANK_TO_FUTURE_BY_BANK                    0x10090001  ///银行发起银行资金转期货通知
#define CB_TRADE_RTN_FROM_FUTURE_TO_BANK_BY_BANK                    0x10090002  ///银行发起期货资金转银行通知
#define CB_TRADE_RTN_REPEAL_FROM_BANK_TO_FUTURE_BY_BANK             0x10090003  ///银行发起冲正银行转期货通知
#define CB_TRADE_RTN_REPEAL_FROM_FUTURE_TO_BANK_BY_BANK             0x10090004  ///银行发起冲正期货转银行通知
#define CB_TRADE_RTN_OPEN_ACCOUNT_BY_BANK                           0x10090005  ///银行发起银期开户通知
#define CB_TRADE_RTN_CHANGE_ACCOUNT_BY_BANK                         0x10090006  ///银行发起变更银行账号通知
#define CB_TRADE_RTN_CANCEL_ACCOUNT_BY_BANK                         0x10090007  ///银行发起银期销户通知
/********** 期货发起操作 **********/
#define CB_TRADE_RSP_FROM_BANK_TO_FUTURE_BY_FUTURE                  0x100a0001  ///期货发起银行资金转期货应答
#define CB_TRADE_RSP_FROM_FUTURE_TO_BANK_BY_FUTURE                  0x100a0002  ///期货发起期货资金转银行应答
#define CB_TRADE_RSP_QRY_BANK_ACCOUNT_MONEY_BY_FUTURE               0x100a0101  ///期货发起查询银行余额应答
#define CB_TRADE_RTN_QRY_BANK_BALANCE_BY_FUTURE                     0x100a0102  ///期货发起查询银行余额通知
#define CB_TRADE_RTN_FROM_BANK_TO_FUTURE_BY_FUTURE                  0x100a0201  ///期货发起银行资金转期货通知
#define CB_TRADE_RTN_FROM_FUTURE_TO_BANK_BY_FUTURE                  0x100a0202  ///期货发起期货资金转银行通知
#define CB_TRADE_RTN_REPEAL_FROM_BANK_TO_FUTURE_BY_FUTURE           0x100a0301  ///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
#define CB_TRADE_RTN_REPEAL_FROM_FUTURE_TO_BANK_BY_FUTURE           0x100a0302  ///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
#define CB_TRADE_ERR_RTN_BANK_TO_FUTURE_BY_FUTURE                   0x100a0401  ///期货发起银行资金转期货错误回报
#define CB_TRADE_ERR_RTN_FUTURE_TO_BANK_BY_FUTURE                   0x100a0402  ///期货发起期货资金转银行错误回报
#define CB_TRADE_ERR_RTN_QRY_BANK_BALANCE_BY_FUTURE                 0x100a0403  ///期货发起查询银行余额错误回报
/********** 手工发起冲正 **********/
#define CB_TRADE_RTN_REPEAL_FROM_BANK_TO_FUTURE_BY_FUTURE_MANUAL    0x100b0001  ///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
#define CB_TRADE_RTN_REPEAL_FROM_FUTURE_TO_BANK_BY_FUTURE_MANUAL    0x100b0002  ///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
#define CB_TRADE_ERR_RTN_REPEAL_BANK_TO_FUTURE_BY_FUTURE_MANUAL     0x100b0101  ///系统运行时期货端手工发起冲正银行转期货错误回报
#define CB_TRADE_ERR_RTN_REPEAL_FUTURE_TO_BANK_BY_FUTURE_MANUAL     0x100b0102  ///系统运行时期货端手工发起冲正期货转银行错误回报
/********** 查询通知 **********/
#define CB_TRADE_RSP_QRY_NOTICE                                     0x100c0001  ///请求查询客户通知响应
#define CB_TRADE_RSP_QRY_TRADING_NOTICE                             0x100c0002  ///请求查询交易通知响应
#define CB_TRADE_RTN_TRADING_NOTICE                                 0x100c0101  ///交易通知
#define CB_TRADE_RTN_BULLETIN                                       0x100c0102  ///交易所公告通知
/********** 查询交易所与合约 **********/
#define CB_TRADE_RSP_QRY_EXCHANGE                                   0x100d0001  ///请求查询交易所响应
#define CB_TRADE_RSP_QRY_EXCHANGE_RATE                              0x100d0002  ///请求查询汇率响应
#define CB_TRADE_RSP_QRY_EXCHANGE_MARGIN_RATE                       0x100d0003  ///请求查询交易所保证金率响应
#define CB_TRADE_RSP_QRY_EXCHANGE_MARGIN_RATE_ADJUST                0x100d0004  ///请求查询交易所调整保证金率响应
#define CB_TRADE_RSP_QRY_PRODUCT                                    0x100d0101  ///请求查询产品响应
#define CB_TRADE_RSP_QRY_PRODUCT_EXCH_RATE                          0x100d0102  ///请求查询产品报价汇率
#define CB_TRADE_RSP_QRY_INSTRUMENT                                 0x100d0201  ///请求查询合约响应
#define CB_TRADE_RSP_QRY_INSTRUMENT_MARGIN_RATE                     0x100d0202  ///请求查询合约保证金率响应
#define CB_TRADE_RSP_QRY_INSTRUMENT_COMMISSION_RATE                 0x100d0203  ///请求查询合约手续费率响应
#define CB_TRADE_RSP_QRY_INSTRUMENT_ORDER_COMM_RATE                 0x100d0204  ///请求查询报单手续费响应
#define CB_TRADE_RTN_INSTRUMENT_STATUS                              0x100d0301  ///合约交易状态通知
/********** 查询投资者 **********/
#define CB_TRADE_RSP_QRY_INVESTOR                                   0x100e0001  ///请求查询投资者响应
#define CB_TRADE_RSP_QRY_INVESTOR_POSITION                          0x100e0002  ///请求查询投资者持仓响应
#define CB_TRADE_RSP_QRY_INVESTOR_POSITION_DETAIL                   0x100e0003  ///请求查询投资者持仓明细响应
#define CB_TRADE_RSP_QRY_INVESTOR_POSITION_COMBINE_DETAIL           0x100e0004  ///请求查询投资者持仓明细响应
#define CB_TRADE_RSP_QRY_INVESTOR_PRODUCT_GROUP_MARGIN              0x100e0005  ///请求查询投资者品种/跨品种保证金响应
#define CB_TRADE_RSP_QRY_TRADING_CODE                               0x100e0101  ///请求查询交易编码响应
#define CB_TRADE_RSP_QRY_TRADING_ACCOUNT                            0x100e0102  ///请求查询资金账户响应
/********** 查询银期等 **********/
#define CB_TRADE_RSP_QRY_TRANSFER_SERIAL                            0x100f0001  ///请求查询转帐流水响应
#define CB_TRADE_RSP_QRY_CONTRACT_BANK                              0x100f0002  ///请求查询签约银行响应
#define CB_TRADE_RSP_QRY_TRANSFER_BANK                              0x100f0003  ///请求查询转帐银行响应
#define CB_TRADE_RSP_QRY_ACCOUNT_REGISTER                           0x100f0004  ///请求查询银期签约关系响应
/********** 查询经纪公司 **********/
#define CB_TRADE_RSP_QRY_BROKER_TRADING_PARAMS                      0x10100001  ///请求查询经纪公司交易参数响应
#define CB_TRADE_RSP_QRY_BROKER_TRADING_ALGOS                       0x10100002  ///请求查询经纪公司交易算法响应
/********** 查询二级代理 **********/
#define CB_TRADE_RSP_QRY_SEC_AGENT_ACID_MAP                         0x10110001  ///请求查询二级代理操作员银期权限响应
#define CB_TRADE_RSP_QRY_SEC_AGENT_CHECK_MODE                       0x10110002  ///请求查询二级代理商资金校验模式响应
#define CB_TRADE_RSP_QRY_SEC_AGENT_TRADING_ACCOUNT                  0x10110003  ///请求查询资金账户响应
/********** 查询做市商 **********/
#define CB_TRADE_RSP_QRY_MM_INSTRUMENT_COMMISSION_RATE              0x10120001  ///请求查询做市商合约手续费率响应
#define CB_TRADE_RSP_QRY_MM_OPTION_INSTR_COMM_RATE                  0x10120002  ///请求查询做市商期权合约手续费响应
/********** 查询保证金监控中心 **********/
#define CB_TRADE_RSP_QRY_CFMMC_TRADING_ACCOUNT_TOKEN                0x10130001  ///请求查询监控中心用户令牌响应
#define CB_TRADE_RSP_QRY_CFMMC_TRADING_ACCOUNT_KEY                  0x10130002  ///查询保证金监管系统经纪公司资金账户密钥响应
#define CB_TRADE_RTN_CFMMC_TRADING_ACCOUNT_TOKEN                    0x10130101  ///保证金监控中心用户令牌
/********** 其他查询 **********/
#define CB_TRADE_RSP_QRY_DEPTH_MARKET_DATA                          0x10140001  ///请求查询行情响应
#define CB_TRADE_RSP_QRY_MAX_ORDER_VOLUME                           0x10140002  ///查询最大报单数量响应
#define CB_TRADE_RSP_QRY_EWARRANT_OFFSET                            0x10140003  ///请求查询仓单折抵信息响应
#define CB_TRADE_RTN_ERROR_CONDITIONAL_ORDER                        0x10140101  ///提示条件单校验错误


///向Plat.插入命令时，要指定命令的唯一ID，即nRequestID
///stgroup下发的命令ID由stgroup分配
///ctpspi回调的ID分别为-1和-2
#define CMDID_QUOTE        -1
#define CMDID_TRADE        -2
///command label: StGroup to Plat.
#define CMD_PLAT_QUOTE_REQ_USER_LOGIN                               0x20000001
#define CMD_PLAT_QUOTE_REQ_USER_LOGOUT                              0x20000002
#define CMD_PLAT_QUOTE_SUBSCRIBE_MARKET_DATA                        0x20010001
#define CMD_PLAT_TRADE_REQ_USER_LOGIN                               0x30000001
#define CMD_PLAT_TRADE_REQ_USER_LOGOUT                              0x30000002
#define CMD_PLAT_TRADE_REQ_AUTHENTICATE                             0x30000003
#define CMD_PLAT_TRADE_REQ_QRY_SETTLEMENT_INFO_CONFIRM              0x30010001
#define CMD_PLAT_TRADE_REQ_QRY_SETTLEMENT_INFO                      0x30010002
#define CMD_PLAT_TRADE_REQ_SETTLEMENT_INFO_CONFIRM                  0x30010003
#define CMD_PLAT_TRADE_REQ_QRY_EXCHANGE                             0x30020001
#define CMD_PLAT_TRADE_REQ_QRY_PRODUCT                              0x30020002
#define CMD_PLAT_TRADE_REQ_QRY_INSTRUMENT                           0x30020003

///command label: Front to StGroup
//TODO: #define CMD_FRONT_.....     0x50000001
///callback label: StGroup to front
//TODO: #define CB_STG_.....        0x60000001


///定义回调函数的参数
///log_callback         由logger向front传递日志的回调
///ctpspi_callback      由ctpspi向plat传递ctpapi回调结果的回调
///quote_callback       由stgroup向front传递行情数据的回调
///trade_callback       由stgroup向front传递交易结果的回调
///plat_callback        由plat向stgroup传递ctpapi回调结果的回调
///stgroup_callback     由stgroup向front传递策略组实时状态的回调
typedef void(*base_callback_fn) (int, void*);
///日志处理的回调函数指针
///int loglevel     日志记录等级
///char *ptr        单条日志缓冲区的首地址指针
typedef base_callback_fn log_callback_fn;
///CTP接口回调类的回调函数指针
///int cbtype       CTPSPI回调类型
///void *ptr        指向回调的数据区域的首地址指针
typedef base_callback_fn ctpspi_callback_fn;
///行情接口的回调函数指针
///int cbtype       CB_QUOTE的回调类型
///void *ptr        指向回调的数据区域的首地址指针
typedef base_callback_fn quote_callback_fn;
///交易接口的回调函数指针
///int cbtype       CB_TRADE的回调类型
///void *ptr        指向回调的数据区域的首地址指针
typedef base_callback_fn trade_callback_fn;
///Platform的回调函数指针
///int cbtype       PLAT的回调类型
///void *ptr        指向回调的数据区域的首地址指针
typedef base_callback_fn plat_callback_fn;
///策略组实时状态回调函数指针
///int cbtype       CB_STGROUP的回调类型
///void *ptr        回调返回的数据区域的首地址指针
typedef base_callback_fn stgroup_callback_fn;


typedef char MdCsvFormatType[128];                                          ///行情CSV保存格式类型
typedef char FrontAddrType[64];                                             ///前置地址类型
typedef char DateTimeType[24];                                              ///时间字符串类型, yyyy-MM-dd hh:mm:ss.zzz
typedef char ProductNameType[24];                                           ///产品名称 - 用于TradeApi的验证
typedef char AuthenticateCodeType[32];                                      ///验证编码 - 用于TradeApi的验证

typedef TThostFtdcDateType                  DateType;                       ///日期类型，yyyyMMdd
typedef TThostFtdcTimeType                  TimeType;                       ///时间类型，hh:mm:ss
typedef TThostFtdcBrokerIDType              BrokerIDType;                   ///经纪公司代码类型
typedef TThostFtdcUserIDType                UserIDType;                     ///用户代码类型
typedef TThostFtdcInvestorIDType            InvestorIDType;                 ///投资者代码类型
typedef TThostFtdcAccountIDType             AccountIDType;                  ///投资者帐号类型
typedef TThostFtdcInstrumentIDType          InstrumentIDType;               ///合约代码类型
typedef TThostFtdcPasswordType              PasswordType;                   ///口令类型
typedef TThostFtdcExchangeIDType            ExchangeIDType;                 ///交易所代码类型
typedef TThostFtdcInstrumentNameType        InstrumentNameType;             ///合约名称类型
typedef TThostFtdcExchangeInstIDType        ExchangeInstIDType;             ///合约在交易所的代码类型
typedef TThostFtdcCurrencyIDType            CurrencyIDType;                 ///币种代码类型
typedef TThostFtdcProductInfoType           ProductInfoType;                ///产品信息类型
typedef TThostFtdcIPAddressType             IPAddressType;                  ///IP地址
typedef TThostFtdcMacAddressType            MacAddressType;                 ///Mac地址
typedef TThostFtdcOrderSysIDType            OrderSysIDType;                 ///报单编号
typedef TThostFtdcOrderLocalIDType          OrderLocalIDType;               ///本地报单编号
typedef TThostFtdcContentType               ContentType;                    ///消息正文
typedef TThostFtdcExchangeNameType          ExchangeNameType;               ///交易所名称
typedef TThostFtdcPartyNameType             PartyNameType;                  ///投资者名称
typedef TThostFtdcIdentifiedCardNoType      IdentifiedCardNoType;           ///证件号码
typedef TThostFtdcTelephoneType             TelephoneType;                  ///联系电话
typedef TThostFtdcAddressType               AddressType;                    ///通讯地址
typedef TThostFtdcMobileType                MobileType;                     ///手机

#endif // !OPTSP_CTPCORE_DATATYPE_HPP_

