#ifndef OPTSP_CTPCORE_QUOTESTRUCT_HPP_
#define OPTSP_CTPCORE_QUOTESTRUCT_HPP_

#include "indexstruct.hpp"
#include "datatype.hpp"

typedef struct CbQuoteFrontConnectedField {
} CbQuoteFrontConnectedField;

typedef struct CbQuoteFrontDisconnectedField {
} CbQuoteFrontDisconnectedField;

typedef struct CbQuoteRspUserLoginField {
    uint64_t        DateStamp;      ///交易日, 日期戳："yyyy-MM-dd 00:00:00.000"
    uint64_t        LoginTime;      ///登录成功时间, 时间的格式采用时间戳: "yyyy-MM-dd hh:mm:ss.zzz"
    BrokerIDType    BrokerID;       ///经纪公司代码
    UserIDType      UserID;         ///用户代码
    int             FrontID;        ///前置编号
    int             SessionID;      ///会话编号
    uint64_t        MaxOrderRef;    ///最大报单引用
    uint64_t        SHFETime;       ///上期所时间
    uint64_t        DCETime;        ///大商所时间
    uint64_t        CZCETime;       ///郑商所时间
    uint64_t        FFEXTime;       ///中金所时间
    uint64_t        INETime;        ///能源中心时间
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
    uint64_t            DateStamp;          ///交易日, 日期戳："yyyy-MM-dd 00:00:00.000"
    double              PreClose;           ///昨收盘
    double              PreSettlement;      ///昨结算
    uint64_t            PrePosition;        ///昨持仓
    double              CurrOpen;           ///今开盘
    double              CurrHighest;        ///最高价
    double              CurrLowest;         ///最低价
    double              CurrClose;          ///今收盘
    double              CurrSettlement;     ///今结算
    double              UpperLimit;         ///涨停板
    double              LowerLimit;         ///跌停板
    double              PreDelta;           ///昨虚实度
    double              CurrDelta;          ///今虚实度
    double              BidPrice[5];        ///申买价1-5
    uint64_t            BidVolume[5];       ///申买量1-5
    double              AskPrice[5];        ///申卖价1-5
    uint64_t            AskVolume[5];       ///申卖量1-5
    uint64_t            TimeStamp;          ///时间戳, "yyyy-MM-dd hh:mm:ss.zzz"
    double              Price;              ///时间切片的最新价格
    uint64_t            Volume;             ///成交量
    double              Turnover;           ///成交额
    uint64_t            Position;           ///持仓量
    double              Average;            ///当日均价
    InstrumentIDType    InstrumentID;       ///合约编码，p.s. 字节未对齐} HandicapField;
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
