#ifndef OPTSP_CTPCORE_QUOTESTRUCT_HPP_
#define OPTSP_CTPCORE_QUOTESTRUCT_HPP_

#include "indexstruct.hpp"
#include "datatype.hpp"

typedef struct CbQuoteFrontConnectedField {
} CbQuoteFrontConnectedField;

typedef struct CbQuoteFrontDisconnectedField {
} CbQuoteFrontDisconnectedField;

typedef struct CbQuoteRspUserLoginField {
    DateType        TradingDay;     ///交易日
    TimeType        LoginTime;      ///登录成功时间
    BrokerIDType    BrokerID;       ///经纪公司代码
    UserIDType      UserID;         ///用户代码
    TimeType        SHFETime;       ///上期所时间
    TimeType        DCETime;        ///大商所时间
    TimeType        CZCETime;       ///郑商所时间
    TimeType        FFEXTime;       ///中金所时间
    TimeType        INETime;        ///能源中心时间
    int             FrontID;        ///前置编号
    int             SessionID;      ///会话编号
    uint64_t        MaxOrderRef;    ///最大报单引用
} CbQuoteRspUserLoginField;

typedef struct CbQuoteRspUserLogoutField {
    BrokerIDType	BrokerID;       ///经纪公司代码
    UserIDType	    UserID;         ///用户代码
} CbQuoteRspUserLogoutField;

typedef struct CbQuoteRspSubMarketDataField {
    InstrumentIDType    InstrumentID;   ///合约代码
} CbQuoteRspSubMarketDataField;

typedef struct CbQuoteRspUnsubMarketDataField {
    InstrumentIDType    InstrumentID;   ///合约代码
} CbQuoteRspUnsubMarketDataField;

typedef struct CbQuoteRspSubForQuoteRspField {
} CbQuoteRspSubForQuoteRspField;

typedef struct CbQuoteRspErrorField {
} CbQuoteRspErrorField;

typedef struct CbQuoteHeartBeatWarningField {
} CbQuoteHeartBeatWarningField;

typedef struct CbQuoteRspUnsubForQuoteRspField {
} CbQuoteRspUnsubForQuoteRspField;

typedef struct CbQuoteRtnDepthMarketDataField {
    DateType            TradingDay;             ///交易日
    InstrumentIDType    InstrumentID;           ///合约编码，p.s. 字节未对齐} HandicapField;
    ExchangeIDType      ExchangeID;             ///交易所代码
    ExchangeInstIDType  ExchangeInstID;         ///合约在交易所的代码
    double              PreClosePrice;          ///昨收盘
    double              PreSettlementPrice;     ///昨结算
    uint64_t            PreOpenInterest;        ///昨持仓
    double              OpenPrice;              ///今开盘
    double              HighestPrice;           ///最高价
    double              LowestPrice;            ///最低价
    double              ClosePrice;             ///今收盘
    double              SettlementPrice;        ///今结算
    double              UpperLimitPrice;        ///涨停板
    double              LowerLimitPrice;        ///跌停板
    double              PreDelta;               ///昨虚实度
    double              CurrDelta;              ///今虚实度
    double              BidPrice[5];            ///申买价1-5
    uint64_t            BidVolume[5];           ///申买量1-5
    double              AskPrice[5];            ///申卖价1-5
    uint64_t            AskVolume[5];           ///申卖量1-5
    uint64_t            TimeStamp;              ///时间戳, "yyyy-MM-dd hh:mm:ss.zzz"
    double              LastPrice;              ///时间切片的最新价格
    uint64_t            Volume;                 ///成交量
    double              Turnover;               ///成交额
    uint64_t            OpenInterest;           ///持仓量
    double              AveragePrice;           ///当日均价
} CbQuoteRtnDepthMarketDataField;

typedef struct CbQuoteRtnForQuoteRspField {
} CbQuoteRtnForQuoteRspField;


typedef union CbQuoteField {
    CbQuoteFrontConnectedField          FrontConnected;
    CbQuoteFrontDisconnectedField       FrontDisconnected;
    CbQuoteRspUserLoginField            RspUserLogin;
    CbQuoteRspUserLogoutField           RspUserLogout;
    CbQuoteRspSubMarketDataField        RspSubMarketData;
    CbQuoteRspUnsubMarketDataField      RspUnsubMarketData;
    CbQuoteRspSubForQuoteRspField       RspSubForQuoteRsp;
    CbQuoteRspErrorField                RspError;
    CbQuoteRtnForQuoteRspField          RtnForQuoteRsp;
    CbQuoteHeartBeatWarningField        HeartBeatWarning;
    CbQuoteRspUnsubForQuoteRspField     RspUnsubForQuoteRsp;
    CbQuoteRtnDepthMarketDataField      RtnDepthMarketData;
} CbQuoteField;

#endif // !OPTSP_CTPCORE_QUOTESTRUCT_HPP_
