#ifndef OPTSP_CTPCORE_TRADESTRUCT_HPP_
#define OPTSP_CTPCORE_TRADESTRUCT_HPP_

#include <stdint.h>
#include "datatype.hpp"


#define        POSITION_STATE_NONE                  'N'        ///无持仓
#define        POSITION_STATE_LONG                  'L'        ///持有多单
#define        POSITION_STATE_SHORT                 'S'        ///持有空单
#define        POSITION_STATE_ONOPEN_LONG           'A'        ///已下多单等待成交
#define        POSITION_STATE_ONOPEN_SHORT          'B'        ///已下空单等待成交
#define        POSITION_STATE_ONCLOSE_LONG          'X'        ///已下多单等待平仓
#define        POSITION_STATE_ONCLOSE_SHORT         'Y'        ///已下空单等待平仓

#define        TRADING_DIRECT_NONE                  'N'        ///价格方向无
#define        TRADING_DIRECT_LONG                  'L'        ///价格涨势
#define        TRADING_DIRECT_SHORT                 'S'        ///价格跌势

#define        ORDER_SIDE_BUY                       'B'        ///买入
#define        ORDER_SIDE_SELL                      'S'        ///卖出

#define        ORDER_FLAG_OPEN                      'O'        ///开仓
#define        ORDER_FLAG_CLOSE                     'C'        ///平仓


typedef struct CbTradeFrontConnectedField {
} CbTradeFrontConnectedField;

typedef struct CbTradeFrontDisconnectedField {
} CbTradeFrontDisconnectedField;

typedef struct CbTradeRspAuthenticateField {
    BrokerIDType    BrokerID;           ///经纪公司代码
    UserIDType      UserID;             ///用户代码
    ProductInfoType	UserProductInfo;    ///用户端产品信息
}CbTradeRspAuthenticateField;

typedef struct CbTradeRspUserLoginField {
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
} CbTradeRspUserLoginField;

typedef struct CbTradeRspUserLogoutField {
    BrokerIDType	BrokerID;       ///经纪公司代码
    UserIDType	    UserID;         ///用户代码
} CbTradeRspUserLogoutField;

typedef struct CbTradeRspErrorField {
} CbTradeRspErrorField;

typedef struct CbTradeRspSubForQuoteRspField {
} CbTradeRspSubForQuoteRspField;

/********** 口令与密钥相关 **********/
typedef struct CbTradeRspUserPasswordUpdateField{
    BrokerIDType            BrokerID;       ///经纪公司代码
    UserIDType              UserID;         ///用户代码
    PasswordType            OldPassword;    ///原来的口令
    PasswordType            NewPassword;    ///新的口令
} CbTradeRspUserPasswordUpdateField;

typedef struct CbTradeRspTradingAccountPasswordUpdateField {
    BrokerIDType    BrokerID;       ///经纪公司代码
    AccountIDType   AccountID;      ///投资者帐号
    PasswordType    OldPassword;    ///原来的口令
    PasswordType    NewPassword;    ///新的口令
    CurrencyIDType  CurrencyID;     ///币种代码
} CbTradeRspTradingAccountPasswordUpdateField;

/********** 预埋单 **********/
typedef struct CbTradeRspParkedOrderInsertField {
} CbTradeRspParkedOrderInsertField;

typedef struct CbTradeRspParkedOrderActionField {
} CbTradeRspParkedOrderActionField;

typedef struct CbTradeRspQryParkedOrderField {
} CbTradeRspQryParkedOrderField;

typedef struct CbTradeRspQryParkedOrderActionField {
} CbTradeRspQryParkedOrderActionField;

typedef struct CbTradeRspRemoveParkedOrderField {
} CbTradeRspRemoveParkedOrderField;

typedef struct CbTradeRspRemoveParkedOrderActionField {
} CbTradeRspRemoveParkedOrderActionField;

/********** 下单 **********/
typedef struct CbTradeRspOrderInsertField {
    uint64_t                ExpireTime;             ///有效时间（时间戳）
    BrokerIDType            BrokerID;               ///经纪公司代码
    InvestorIDType          InvestorID;             ///资金账号
    AccountIDType           AccountID;              ///资金账号
    InstrumentIDType        InstrumentID;           ///合约编号
    UserIDType              UserID;                 ///用户代码
    uint64_t                OrderRef;               ///报单引用
    double                  OrderPrice;             ///委托价格
    double                  StopPrice;              ///止损价
    int                     OrderQty;               ///委托数量
    int                     OrderMinQty;            ///最小成交量
    int                     RequestID;              ///请求编号
    char                    OrderSide;              ///买入 / 卖出
    char                    OrderFlag;              ///开仓 / 平仓
    char                    OrderPriceType;         ///报单价格条件
    char                    TimeCondition;          ///有效期类型
    char                    VolumeCondition;        ///成交量类型
    char                    ContingentCondition;    ///触发条件
    char                    ForceCloseReason;       ///强平原因
    bool                    UserForceClose;         ///用户强评标志
    IPAddressType           IPAddress;              ///IP地址
    MacAddressType          MacAddress;             ///Mac地址
} CbTradeRspOrderInsertField;

typedef struct CbTradeRspOrderActionField {
    BrokerIDType            BrokerID;               ///经纪公司代码
    UserIDType              UserID;                 ///用户代码
    InvestorIDType          InvestorID;             ///资金账号
    InstrumentIDType        InstrumentID;           ///合约编号
    uint64_t                OrderRef;               ///报单引用
    double                  OrderPrice;             ///委托价格
    int                     OrderActionRef;         ///报单操作引用
    int                     RequestID;              ///请求编号
    int                     FrontID;                ///前置编号
    int                     SessionID;              ///会话编号
    int                     QtyChange;              ///数量变化
    IPAddressType           IPAddress;              ///IP地址
    MacAddressType          MacAddress;             ///Mac地址
    OrderSysIDType          OrderSysID;             ///报单编号
    char                    ActionFlag;             ///操作标志
} CbTradeRspOrderActionField;

typedef struct CbTradeRspQryOrderField {

    BrokerIDType            BrokerID;               ///经纪公司代码
    InvestorIDType          InvestorID;             ///资金账号
    AccountIDType           AccountID;              ///资金账号
    InstrumentIDType        InstrumentID;           ///合约编号
    UserIDType              UserID;                 ///用户代码
    uint64_t                OrderRef;               ///报单引用
    double                  OrderPrice;             ///委托价格
    double                  StopPrice;              ///止损价
    int                     OrderQty;               ///委托数量
    int                     OrderMinQty;            ///最小成交量
    int                     RequestID;              ///请求编号
    int                     FrontID;                ///前置编号
    int                     SessionID;              ///会话编号
    int                     NotifySequence;         ///报单提示序号
    char                    OrderSide;              ///买入 / 卖出
    char                    OrderFlag;              ///开仓 / 平仓
    char                    OrderPriceType;         ///报单价格条件
    char                    TimeCondition;          ///有效期类型
    char                    VolumeCondition;        ///成交量类型
    char                    ContingentCondition;    ///触发条件
    char                    ForceCloseReason;       ///强平原因
    bool                    UserForceClose;         ///用户强评标志
    IPAddressType           IPAddress;              ///IP地址
    MacAddressType          MacAddress;             ///Mac地址
    OrderLocalIDType        OrderLocalID;           ///本地报单编号

    char                    OrderSubmitStatus;      ///报单提交状态


    ///交易日
    TThostFtdcDateType	TradingDay;
    ///结算编号
    TThostFtdcSettlementIDType	SettlementID;
    ///报单编号
    TThostFtdcOrderSysIDType	OrderSysID;
    ///报单来源
    TThostFtdcOrderSourceType	OrderSource;
    ///报单状态
    TThostFtdcOrderStatusType	OrderStatus;
    ///报单类型
    TThostFtdcOrderTypeType	OrderType;
    ///今成交数量
    TThostFtdcVolumeType	VolumeTraded;
    ///剩余数量
    TThostFtdcVolumeType	VolumeTotal;
    ///报单日期
    TThostFtdcDateType	InsertDate;
    ///委托时间
    TThostFtdcTimeType	InsertTime;
    ///激活时间
    TThostFtdcTimeType	ActiveTime;
    ///挂起时间
    TThostFtdcTimeType	SuspendTime;
    ///最后修改时间
    TThostFtdcTimeType	UpdateTime;
    ///撤销时间
    TThostFtdcTimeType	CancelTime;
    ///最后修改交易所交易员代码
    TThostFtdcTraderIDType	ActiveTraderID;
    ///结算会员编号
    TThostFtdcParticipantIDType	ClearingPartID;
    ///序号
    TThostFtdcSequenceNoType	SequenceNo;





} CbTradeRspQryOrderField;

typedef struct CbTradeRspQryTradeField {

} CbTradeRspQryTradeField;

typedef struct CbTradeRtnOrderField {




    

};

typedef struct CbTradeRtnTradeField {

};

typedef struct CbTradeErrRtnOrderInsertField {

};

typedef struct CbTradeErrRtnOrderActionField {

};
















typedef struct InstrumentField {
    InstrumentIDType    InstrumentID;            ///合约代码
    ExchangeIDType        ExchangeID;                ///交易所代码
    InstrumentNameType    InstrumentName;            ///合约名称
    ExchangeInstIDType    ExchangeInstID;            ///合约在交易所的代码
    double                LongMarginRatio;        ///多头保证金率
    double                ShortMarginRatio;        ///空头保证金率
    double                UnderlyingMultiple;        ///合约基础商品乘数
    int                    VolumeMultiple;            ///合约数量乘数
    char                InstLifePhase;            ///合约生命周期状态
    bool                IsTrading;                ///当前是否交易
} InstrumentField;


typedef struct OrderField {
    
} OrderField;


typedef struct CapitalField {
    InvestorIDType    InvestorID;            ///投资者帐号
    BrokerIDType    BrokerID;            ///经纪公司代码
    CurrencyIDType    CurrencyID;            ///币种代码
    double            FrozenMargin;        ///冻结的保证金
    double            FrozenCash;            ///冻结的资金
    double            FrozenCommission;    ///冻结的手续费
    double            CurrMargin;            ///当前保证金总额
    double            CashIn;                ///资金差额
    double            Commission;            ///手续费
    double            CloseProfit;        ///平仓盈亏
    double            PositionProfit;        ///持仓盈亏
    double            Balance;            ///期货结算准备金
    double            Available;            ///可用资金
    double            Reserve;            ///基本准备金
    double            ExchangeMargin;        ///交易所保证金
    double            ReserveBalance;        ///保底期货结算准备金
} CapitalField;


typedef struct MatchField {
    uint64_t            MatchDateTime;        ///成交时间（时间戳）
    InvestorIDType        InvestorID;            ///资金账号
    InstrumentIDType    InstrumentID;        ///合约编号
    double                MatchPrice;            ///成交价
    double                Fee;                ///手续费
    int                    MatchQty;            ///成交量
    char                MatchSide;            ///买入 / 卖出
    char                MatchFlag;            ///开仓 / 平仓
} MatchField;


typedef struct PositionField {
    InvestorIDType        InvestorID;            ///资金账号
    InstrumentIDType    InstrumentID;        ///合约编号
    double                OpenCost;            ///开仓成本
    double                PositionCost;        ///持仓成本
    double                PositionProfit;        ///持仓盈亏
    double                CloseProfit;        ///平仓盈亏
    double                Fee;                ///手续费
    double                UseMargin;            ///占用的保证金                                                    
    int                    SettlementID;        ///结算编号
    int                    OpenVolume;            ///开仓量
    int                    CloseVolume;        ///平仓量
    int                    PositionQty;        ///今日持仓
    char                PositionSide;        ///买入 / 卖出
} PositionField;


#endif // !OPTSP_CTPCORE_TRADESTRUCT_HPP_
