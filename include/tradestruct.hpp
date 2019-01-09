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
} CbTradeRspAuthenticateField;

typedef struct CbTradeRspUserLoginField {
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
typedef struct CbTradeRspUserPasswordUpdateField {
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
    BrokerIDType            BrokerID;               ///经纪公司代码
    InvestorIDType          InvestorID;             ///资金账号
    AccountIDType           AccountID;              ///资金账号
    InstrumentIDType        InstrumentID;           ///合约编号
    UserIDType              UserID;                 ///用户代码
    DateType                GTDDate;                ///GTD日期
    IPAddressType           IPAddress;              ///IP地址
    MacAddressType          MacAddress;             ///Mac地址
    uint64_t                OrderRef;               ///报单引用
    double                  LimitPrice;             ///委托价格
    double                  StopPrice;              ///止损价
    int                     VolumeTotalOriginal;    ///委托数量
    int                     MinVolume;              ///最小成交量
    int                     RequestID;              ///请求编号
    char                    Direction;              ///买入 / 卖出
    char                    OrderPriceType;         ///报单价格条件
    char                    TimeCondition;          ///有效期类型
    char                    VolumeCondition;        ///成交量类型
    char                    ContingentCondition;    ///触发条件
    char                    ForceCloseReason;       ///强平原因
    bool                    UserForceClose;         ///用户强评标志
} CbTradeRspOrderInsertField;

typedef struct CbTradeRspOrderActionField {
    BrokerIDType            BrokerID;               ///经纪公司代码
    UserIDType              UserID;                 ///用户代码
    InvestorIDType          InvestorID;             ///资金账号
    ExchangeIDType	        ExchangeID;             ///交易所代码
    InstrumentIDType        InstrumentID;           ///合约编号
    OrderSysIDType          OrderSysID;             ///报单编号
    IPAddressType           IPAddress;              ///IP地址
    MacAddressType          MacAddress;             ///Mac地址
    uint64_t                OrderRef;               ///报单引用
    double                  LimitPrice;             ///委托价格
    int                     OrderActionRef;         ///报单操作引用
    int                     RequestID;              ///请求编号
    int                     FrontID;                ///前置编号
    int                     SessionID;              ///会话编号
    int                     VolumeChange;           ///数量变化
    char                    ActionFlag;             ///操作标志
} CbTradeRspOrderActionField;

typedef struct CbTradeRspQryOrderField {
    BrokerIDType            BrokerID;               ///经纪公司代码
    InvestorIDType          InvestorID;             ///资金账号
    AccountIDType           AccountID;              ///资金账号
    InstrumentIDType        InstrumentID;           ///合约编号
    UserIDType              UserID;                 ///用户代码
    IPAddressType           IPAddress;              ///IP地址
    MacAddressType          MacAddress;             ///Mac地址
    OrderLocalIDType        OrderLocalID;           ///本地报单编号
    OrderSysIDType          OrderSysID;             ///报单编号
    DateType                InsertDate;             ///报单日期
    TimeType                InsertTime;             ///委托时间
    TimeType                ActiveTime;             ///激活时间
    TimeType                SuspendTime;            ///挂起时间
    TimeType                UpdateTime;             ///最后修改时间
    TimeType                CancelTime;             ///撤销时间
    uint64_t                OrderRef;               ///报单引用
    double                  LimitPrice;             ///委托价格
    double                  StopPrice;              ///止损价
    int                     VolumeTotalOriginal;    ///委托数量
    int                     MinVolume;              ///最小成交量
    int                     RequestID;              ///请求编号
    int                     FrontID;                ///前置编号
    int                     SessionID;              ///会话编号
    int                     NotifySequence;         ///报单提示序号
    int                     VolumeTraded;           ///今成交数量
    int                     VolumeTotal;            ///剩余数量
    int                     SequenceNo;             ///序号
    int                     SettlementID;           ///结算编号
    char                    Direction;              ///买入 / 卖出
    char                    OrderPriceType;         ///报单价格条件
    char                    TimeCondition;          ///有效期类型
    char                    VolumeCondition;        ///成交量类型
    char                    ContingentCondition;    ///触发条件
    char                    ForceCloseReason;       ///强平原因
    char                    OrderSubmitStatus;      ///报单提交状态
    char                    OrderStatus;            ///报单状态
    char                    OrderSource;            ///报单来源
    char                    OrderType;              ///报单类型
    bool                    UserForceClose;         ///用户强评标志
} CbTradeRspQryOrderField;

typedef struct CbTradeRspQryTradeField {
    BrokerIDType            BrokerID;               ///经纪公司代码
    InvestorIDType          InvestorID;             ///资金账号
    InstrumentIDType        InstrumentID;           ///合约编号
    UserIDType              UserID;                 ///用户代码
    OrderSysIDType          OrderSysID;             ///报单编号
    OrderLocalIDType        OrderLocalID;           ///本地报单编号
    DateType	            TradeDate;              ///成交时期
    TimeType	            TradeTime;              ///成交时间
    uint64_t                OrderRef;               ///报单引用
    double                  Price;                  ///价格
    int                     SettlementID;           ///结算编号
    int                     Volume;                 ///数量
    char                    Direction;              ///买卖方向
} CbTradeRspQryTradeField;

typedef struct CbTradeRtnOrderField {
    BrokerIDType            BrokerID;               ///经纪公司代码
    InvestorIDType          InvestorID;             ///资金账号
    AccountIDType           AccountID;              ///资金账号
    InstrumentIDType        InstrumentID;           ///合约编号
    UserIDType              UserID;                 ///用户代码
    IPAddressType           IPAddress;              ///IP地址
    MacAddressType          MacAddress;             ///Mac地址
    OrderLocalIDType        OrderLocalID;           ///本地报单编号
    OrderSysIDType          OrderSysID;             ///报单编号
    DateType                InsertDate;             ///报单日期
    TimeType                InsertTime;             ///委托时间
    TimeType                ActiveTime;             ///激活时间
    TimeType                SuspendTime;            ///挂起时间
    TimeType                UpdateTime;             ///最后修改时间
    TimeType                CancelTime;             ///撤销时间
    uint64_t                OrderRef;               ///报单引用
    double                  LimitPrice;             ///委托价格
    double                  StopPrice;              ///止损价
    int                     VolumeTotalOriginal;    ///委托数量
    int                     MinVolume;              ///最小成交量
    int                     RequestID;              ///请求编号
    int                     FrontID;                ///前置编号
    int                     SessionID;              ///会话编号
    int                     NotifySequence;         ///报单提示序号
    int                     VolumeTraded;           ///今成交数量
    int                     VolumeTotal;            ///剩余数量
    int                     SequenceNo;             ///序号
    int                     SettlementID;           ///结算编号
    char                    Direction;              ///买入 / 卖出
    char                    OrderPriceType;         ///报单价格条件
    char                    TimeCondition;          ///有效期类型
    char                    VolumeCondition;        ///成交量类型
    char                    ContingentCondition;    ///触发条件
    char                    ForceCloseReason;       ///强平原因
    char                    OrderSubmitStatus;      ///报单提交状态
    char                    OrderStatus;            ///报单状态
    char                    OrderSource;            ///报单来源
    char                    OrderType;              ///报单类型
    bool                    UserForceClose;         ///用户强评标志
} CbTradeRtnOrderField;

typedef struct CbTradeRtnTradeField {
    BrokerIDType            BrokerID;               ///经纪公司代码
    InvestorIDType          InvestorID;             ///资金账号
    InstrumentIDType        InstrumentID;           ///合约编号
    UserIDType              UserID;                 ///用户代码
    OrderSysIDType          OrderSysID;             ///报单编号
    OrderLocalIDType        OrderLocalID;           ///本地报单编号
    DateType	            TradeDate;              ///成交时期
    TimeType	            TradeTime;              ///成交时间
    uint64_t                OrderRef;               ///报单引用
    double                  Price;                  ///价格
    int                     SettlementID;           ///结算编号
    int                     Volume;                 ///数量
    char                    Direction;              ///买卖方向
} CbTradeRtnTradeField;

typedef struct CbTradeErrRtnOrderInsertField {
    BrokerIDType            BrokerID;               ///经纪公司代码
    InvestorIDType          InvestorID;             ///资金账号
    AccountIDType           AccountID;              ///资金账号
    InstrumentIDType        InstrumentID;           ///合约编号
    UserIDType              UserID;                 ///用户代码
    DateType                GTDDate;                ///GTD日期
    IPAddressType           IPAddress;              ///IP地址
    MacAddressType          MacAddress;             ///Mac地址
    uint64_t                OrderRef;               ///报单引用
    double                  LimitPrice;             ///委托价格
    double                  StopPrice;              ///止损价
    int                     VolumeTotalOriginal;    ///委托数量
    int                     MinVolume;              ///最小成交量
    int                     RequestID;              ///请求编号
    char                    Direction;              ///买入 / 卖出
    char                    OrderPriceType;         ///报单价格条件
    char                    TimeCondition;          ///有效期类型
    char                    VolumeCondition;        ///成交量类型
    char                    ContingentCondition;    ///触发条件
    char                    ForceCloseReason;       ///强平原因
    bool                    UserForceClose;         ///用户强评标志
} CbTradeErrRtnOrderInsertField;

typedef struct CbTradeErrRtnOrderActionField {
    BrokerIDType            BrokerID;               ///经纪公司代码
    UserIDType              UserID;                 ///用户代码
    InvestorIDType          InvestorID;             ///资金账号
    ExchangeIDType	        ExchangeID;             ///交易所代码
    InstrumentIDType        InstrumentID;           ///合约编号
    OrderSysIDType          OrderSysID;             ///报单编号
    IPAddressType           IPAddress;              ///IP地址
    MacAddressType          MacAddress;             ///Mac地址
    uint64_t                OrderRef;               ///报单引用
    double                  LimitPrice;             ///委托价格
    int                     OrderActionRef;         ///报单操作引用
    int                     RequestID;              ///请求编号
    int                     FrontID;                ///前置编号
    int                     SessionID;              ///会话编号
    int                     VolumeChange;           ///数量变化
    char                    ActionFlag;             ///操作标志
} CbTradeErrRtnOrderActionField;

/********** 报价 **********/
typedef struct CbTradeRspForQuoteInsertField {

} CbTradeRspForQuoteInsertField;

typedef struct CbTradeRspQuoteInsertField {

} CbTradeRspQuoteInsertField;

typedef struct CbTradeRspQuoteActionField {

} CbTradeRspQuoteActionField;

typedef struct CbTradeRspBatchOrderActionField {

} CbTradeRspBatchOrderActionField;

typedef struct CbTradeRspQryForQuoteField {

} CbTradeRspQryForQuoteField;

typedef struct CbTradeRspQryQuoteField {

} CbTradeRspQryQuoteField;

typedef struct CbTradeRtnForQuoteRspField {

} CbTradeRtnForQuoteRspField;

typedef struct CbTradeRtnQuoteField {

} CbTradeRtnQuoteField;

typedef struct CbTradeErrRtnForQuoteInsertField {

} CbTradeErrRtnForQuoteInsertField;

typedef struct CbTradeErrRtnQuoteInsertField {

} CbTradeErrRtnQuoteInsertField;

typedef struct CbTradeErrRtnQuoteActionField {

} CbTradeErrRtnQuoteActionField;

typedef struct CbTradeErrRtnBatchOrderActionField {

} CbTradeErrRtnBatchOrderActionField;

/********** 执行宣告 **********/
typedef struct CbTradeRspExecOrderInsertField {

} CbTradeRspExecOrderInsertField;

typedef struct CbTradeRspExecOrderActionField {

} CbTradeRspExecOrderActionField;

typedef struct CbTradeRspQryExecOrderField {

} CbTradeRspQryExecOrderField;

typedef struct CbTradeRtnExecOrderField {

} CbTradeRtnExecOrderField;

typedef struct CbTradeErrRtnExecOrderInsertField {

} CbTradeErrRtnExecOrderInsertField;

typedef struct CbTradeErrRtnExecOrderActionField {

} CbTradeErrRtnExecOrderActionField;

/********** 组合相关 **********/
typedef struct CbTradeRspCombActionInsertField {

} CbTradeRspCombActionInsertField;

typedef struct CbTradeRspQryCombActionField {

} CbTradeRspQryCombActionField;

typedef struct CbTradeRspQryInvestUnitField {

} CbTradeRspQryInvestUnitField;

typedef struct CbTradeRspQryProductGroupField {

} CbTradeRspQryProductGroupField;

typedef struct CbTradeRspQryCombInstrumentGuardField {

} CbTradeRspQryCombInstrumentGuardField;

typedef struct CbTradeRtnCombActionField {

} CbTradeRtnCombActionField;

typedef struct CbTradeErrRtnCombActionInsertField {

} CbTradeErrRtnCombActionInsertField;

/********** 期权相关 **********/
typedef struct CbTradeRspOptionSelfCloseInsertField {

} CbTradeRspOptionSelfCloseInsertField;

typedef struct CbTradeRspOptionSelfCloseActionField {

} CbTradeRspOptionSelfCloseActionField;

typedef struct CbTradeRspQryOptionSelfCloseField {

} CbTradeRspQryOptionSelfCloseField;

typedef struct CbTradeRspQryOptionInstrCommRateField {

} CbTradeRspQryOptionInstrCommRateField;

typedef struct CbTradeRspQryOptionInstrTradeCostField {

} CbTradeRspQryOptionInstrTradeCostField;

typedef struct CbTradeRtnOptionSelfCloseField {

} CbTradeRtnOptionSelfCloseField;

typedef struct CbTradeErrRtnOptionSelfCloseInsertField {

} CbTradeErrRtnOptionSelfCloseInsertField;

typedef struct CbTradeErrRtnOptionSelfCloseActionField {

} CbTradeErrRtnOptionSelfCloseActionField;

/********** 投资者结算结果 **********/
typedef struct CbTradeRspSettlementInfoConfirmField {
    BrokerIDType                BrokerID;       ///经纪公司代码
    InvestorIDType              InvestorID;     ///投资者代码
    DateType                    ConfirmDate;    ///确认日期
    TimeType                    ConfirmTime;    ///确认时间
    AccountIDType               AccountID;      ///投资者帐号
    CurrencyIDType              CurrencyID;     ///币种代码
    int                         SettlementID;   ///结算编号
} CbTradeRspSettlementInfoConfirmField;

typedef struct CbTradeRspQrySettlementInfoField {
    DateType                    TradingDay;     ///交易日
    BrokerIDType                BrokerID;       ///经纪公司代码
    InvestorIDType              InvestorID;     ///投资者代码
    AccountIDType               AccountID;      ///投资者帐号
    CurrencyIDType              CurrencyID;     ///币种代码
    ContentType                 Content;        ///消息正文
    int                         SettlementID;   ///结算编号
    int                         SequenceNo;     ///序号
} CbTradeRspQrySettlementInfoField;

typedef struct CbTradeRspQrySettlementInfoConfirmField {
    BrokerIDType                BrokerID;       ///经纪公司代码
    InvestorIDType              InvestorID;     ///投资者代码
    DateType                    ConfirmDate;    ///确认日期
    TimeType                    ConfirmTime;    ///确认时间
    AccountIDType               AccountID;      ///投资者帐号
    CurrencyIDType              CurrencyID;     ///币种代码
    int                         SettlementID;   ///结算编号
} CbTradeRspQrySettlementInfoConfirmField;

/********** 银行发起操作的通知 **********/
typedef struct CbTradeRtnFromBankToFutureByBankField {

} CbTradeRtnFromBankToFutureByBankField;

typedef struct CbTradeRtnFromFutureToBankByBankField {

} CbTradeRtnFromFutureToBankByBankField;

typedef struct CbTradeRtnRepealFromBankToFutureByBankField {

} CbTradeRtnRepealFromBankToFutureByBankField;

typedef struct CbTradeRtnRepealFromFutureToBankByBankField {

} CbTradeRtnRepealFromFutureToBankByBankField;

typedef struct CbTradeRtnOpenAccountByBankField {

} CbTradeRtnOpenAccountByBankField;

typedef struct CbTradeRtnChangeAccountByBankField {

} CbTradeRtnChangeAccountByBankField;

typedef struct CbTradeRtnCancelAccountByBankField {

} CbTradeRtnCancelAccountByBankField;

/********** 期货发起操作 **********/
typedef struct CbTradeRspFromBankToFutureByFutureField {

} CbTradeRspFromBankToFutureByFutureField;

typedef struct CbTradeRspFromFutureToBankByFutureField {

} CbTradeRspFromFutureToBankByFutureField;

typedef struct CbTradeRspQryBankAccountMoneyByFutureField {

} CbTradeRspQryBankAccountMoneyByFutureField;

typedef struct CbTradeRtnQryBankBalanceByFutureField {

} CbTradeRtnQryBankBalanceByFutureField;

typedef struct CbTradeRtnFromBankToFutureByFutureField {

} CbTradeRtnFromBankToFutureByFutureField;

typedef struct CbTradeRtnFromFutureToBankByFutureField {

} CbTradeRtnFromFutureToBankByFutureField;

typedef struct CbTradeRtnRepealFromBankToFutureByFutureField {

} CbTradeRtnRepealFromBankToFutureByFutureField;

typedef struct CbTradeRtnRepealFromFutureToBankByFutureField {

} CbTradeRtnRepealFromFutureToBankByFutureField;

typedef struct CbTradeErrRtnBankToFutureByFutureField {

} CbTradeErrRtnBankToFutureByFutureField;

typedef struct CbTradeErrRtnFutureToBankByFutureField {

} CbTradeErrRtnFutureToBankByFutureField;

typedef struct CbTradeErrRtnQryBankBalanceByFutureField {

} CbTradeErrRtnQryBankBalanceByFutureField;

/********** 手工发起冲正 **********/
typedef struct CbTradeRtnRepealFromBankToFutureByFutureManualField {

} CbTradeRtnRepealFromBankToFutureByFutureManualField;

typedef struct CbTradeRtnRepealFromFutureToBankByFutureManualField {

} CbTradeRtnRepealFromFutureToBankByFutureManualField;

typedef struct CbTradeErrRtnRepealBankToFutureByFutureManualField {

} CbTradeErrRtnRepealBankToFutureByFutureManualField;

typedef struct CbTradeErrRtnRepealFutureToBankByFutureManualField {

} CbTradeErrRtnRepealFutureToBankByFutureManualField;

/********** 查询通知 **********/
typedef struct CbTradeRspQryNoticeField {

} CbTradeRspQryNoticeField;

typedef struct CbTradeRspQryTradingNoticeField {

} CbTradeRspQryTradingNoticeField;

typedef struct CbTradeRtnTradingNoticeField {
    BrokerIDType        BrokerID;           ///经纪公司代码
    InvestorIDType      InvestorID;         ///投资者代码
    TimeType            SendTime;           ///发送时间
    ContentType         FieldContent;       ///消息正文
    int                 SequenceSeries;     ///序列系列号
    int                 SequenceNo;         ///序列号
} CbTradeRtnTradingNoticeField;

typedef struct CbTradeRtnBulletinField {

} CbTradeRtnBulletinField;

/********** 查询交易所与合约 **********/
typedef struct CbTradeRspQryExchangeField {
    ExchangeIDType      ExchangeID;                     ///交易所代码
    ExchangeNameType    ExchangeName;                   ///交易所名称
    char                ExchangeProperty;               ///交易所属性
} CbTradeRspQryExchangeField;

typedef struct CbTradeRspQryExchangeRateField {

} CbTradeRspQryExchangeRateField;

typedef struct CbTradeRspQryExchangeMarginRateField {

} CbTradeRspQryExchangeMarginRateField;

typedef struct CbTradeRspQryExchangeMarginRateAdjustField {

} CbTradeRspQryExchangeMarginRateAdjustField;

typedef struct CbTradeRspQryProductField {
    InstrumentIDType            ProductID;              ///产品代码
    InstrumentIDType            ExchangeProductID;      ///交易所产品代码
    ProductNameType             ProductName;            ///产品名称
    ExchangeIDType              ExchangeID;             ///交易所代码
    CurrencyIDType              TradeCurrencyID;        ///交易币种类型
    double                      PriceTick;              ///最小变动价位
    double                      UnderlyingMultiple;     ///合约基础商品乘数
    int                         VolumeMultiple;         ///合约数量乘数
    char                        ProductClass;           ///产品类型
    char                        PositionType;           ///持仓类型
    char                        PositionDateType;       ///持仓日期类型
    char                        CloseDealType;          ///平仓处理类型
} CbTradeRspQryProductField;

typedef struct CbTradeRspQryProductExchRateField {

} CbTradeRspQryProductExchRateField;

typedef struct CbTradeRspQryInstrumentField {
    InstrumentIDType        InstrumentID;               ///合约代码
    ExchangeIDType          ExchangeID;                 ///交易所代码
    InstrumentNameType      InstrumentName;             ///合约名称
    ExchangeInstIDType      ExchangeInstID;             ///合约在交易所的代码
    double                  LongMarginRatio;            ///多头保证金率
    double                  ShortMarginRatio;           ///空头保证金率
    double                  UnderlyingMultiple;         ///合约基础商品乘数
    int                     VolumeMultiple;             ///合约数量乘数
    char                    InstLifePhase;              ///合约生命周期状态
    bool                    IsTrading;                  ///当前是否交易
} CbTradeRspQryInstrumentField;

typedef struct CbTradeRspQryInstrumentMarginRateField {

} CbTradeRspQryInstrumentMarginRateField;

typedef struct CbTradeRspQryInstrumentCommissionRateField {

} CbTradeRspQryInstrumentCommissionRateField;

typedef struct CbTradeRspQryInstrumentOrderCommRateField {

} CbTradeRspQryInstrumentOrderCommRateField;

typedef struct CbTradeRtnInstrumentStatusField {
    ExchangeIDType                  ExchangeID;             ///交易所代码
    ExchangeInstIDType              ExchangeInstID;         ///合约在交易所的代码
    InstrumentIDType                InstrumentID;           ///合约代码
    TimeType                        EnterTime;              ///进入本状态时间
    char                            InstrumentStatus;       ///合约交易状态
    char                            EnterReason;            ///进入本状态原因
} CbTradeRtnInstrumentStatusField;

/********** 查询投资者 **********/
typedef struct CbTradeRspQryInvestorField {
    InvestorIDType          InvestorID;         ///投资者代码
    BrokerIDType            BrokerID;           ///经纪公司代码
    InvestorIDType          InvestorGroupID;    ///投资者分组代码
    PartyNameType           InvestorName;       ///投资者名称
    IdentifiedCardNoType    IdentifiedCardNo;   ///证件号码
    TelephoneType           Telephone;          ///联系电话
    AddressType             Address;            ///通讯地址
    DateType                OpenDate;           ///开户日期
    MobileType              Mobile;             ///手机
    char                    IdentifiedCardType; ///证件类型
    bool                    IsActive;           ///是否活跃
} CbTradeRspQryInvestorField;

typedef struct CbTradeRspQryInvestorPositionField {
    DateType                TradingDay;             ///交易日
    InvestorIDType          InvestorID;             ///资金账号
    InstrumentIDType        InstrumentID;           ///合约编号
    double                  OpenAmount;             ///开仓金额    
    double                  CloseAmount;            ///平仓金额
    double                  Commission;             ///手续费
    double                  CloseProfit;            ///平仓盈亏
    double                  PositionProfit;         ///持仓盈亏
    double                  OpenCost;               ///开仓成本
    double                  UseMargin;              ///占用的保证金
    double                  PositionCost;           ///持仓成本
    int                     YdPosition;             ///上日持仓
    int                     Position;               ///今日持仓
    int                     TodayPosition;          ///今日持仓
    int                     OpenVolume;             ///开仓量
    int                     CloseVolume;            ///平仓量
    int                     SettlementID;           ///结算编号
    char                    PosiDirection;          ///持仓多空方向
    char                    PositionDate;           ///持仓日期
} CbTradeRspQryInvestorPositionField;

typedef struct CbTradeRspQryInvestorPositionDetailField {

} CbTradeRspQryInvestorPositionDetailField;

typedef struct CbTradeRspQryInvestorPositionCombineDetailField {

} CbTradeRspQryInvestorPositionCombineDetailField;

typedef struct CbTradeRspQryInvestorProductGroupMarginField {

} CbTradeRspQryInvestorProductGroupMarginField;

typedef struct CbTradeRspQryTradingCodeField {

} CbTradeRspQryTradingCodeField;

typedef struct CbTradeRspQryTradingAccountField {
    DateType            TradingDay;             ///交易日
    BrokerIDType        BrokerID;               ///经纪公司代码
    CurrencyIDType      CurrencyID;             ///币种代码
    double              FrozenMargin;           ///冻结的保证金
    double              FrozenCash;             ///冻结的资金
    double              FrozenCommission;       ///冻结的手续费
    double              CurrMargin;             ///当前保证金总额
    double              CashIn;                 ///资金差额
    double              Commission;             ///手续费
    double              CloseProfit;            ///平仓盈亏
    double              PositionProfit;         ///持仓盈亏
    double              Balance;                ///期货结算准备金
    double              Available;              ///可用资金
    double              Reserve;                ///基本准备金
    double              ExchangeMargin;         ///交易所保证金
    double              ReserveBalance;         ///保底期货结算准备金
} CbTradeRspQryTradingAccountField;

/********** 查询银期等 **********/
typedef struct CbTradeRspQryTransferSerialField {

} CbTradeRspQryTransferSerialField;

typedef struct CbTradeRspQryContractBankField {

} CbTradeRspQryContractBankField;

typedef struct CbTradeRspQryTransferBankField {

} CbTradeRspQryTransferBankField;

typedef struct CbTradeRspQryAccountRegisterField {

} CbTradeRspQryAccountRegisterField;

/********** 查询经纪公司 **********/
typedef struct CbTradeRspQryBrokerTradingParamsField {

} CbTradeRspQryBrokerTradingParamsField;

typedef struct CbTradeRspQryBrokerTradingAlgosField {

} CbTradeRspQryBrokerTradingAlgosField;

/********** 查询二级代理 **********/
typedef struct CbTradeRspQrySecAgentAcidMapField {

} CbTradeRspQrySecAgentAcidMapField;

typedef struct CbTradeRspQrySecAgentCheckModeField {

} CbTradeRspQrySecAgentCheckModeField;

typedef struct CbTradeRspQrySecAgentTradingAccountField {

} CbTradeRspQrySecAgentTradingAccountField;

/********** 查询做市商 **********/
typedef struct CbTradeRspQryMmInstrumentCommissionRateField {

} CbTradeRspQryMmInstrumentCommissionRateField;

typedef struct CbTradeRspQryMmOptionInstrCommRateField {

} CbTradeRspQryMmOptionInstrCommRateField;

/********** 查询保证金监控中心 **********/
typedef struct CbTradeRspQryCfmmcTradingAccountTokenField {

} CbTradeRspQryCfmmcTradingAccountTokenField;

typedef struct CbTradeRspQryCfmmcTradingAccountKeyField {

} CbTradeRspQryCfmmcTradingAccountKeyField;

typedef struct CbTradeRtnCfmmcTradingAccountTokenField {

} CbTradeRtnCfmmcTradingAccountTokenField;

/********** 其他查询 **********/
typedef struct CbTradeRspQryDepthMarketDataField {

} CbTradeRspQryDepthMarketDataField;

typedef struct CbTradeRspQryMaxOrderVolumeField {

} CbTradeRspQryMaxOrderVolumeField;

typedef struct CbTradeRspQryEwarrantOffsetField {

} CbTradeRspQryEwarrantOffsetField;

typedef struct CbTradeRtnErrorConditionalOrderField {

} CbTradeRtnErrorConditionalOrderField;


typedef struct CbTradeField {
    union {
        CbTradeFrontConnectedField                          FrontConnected;
        CbTradeFrontDisconnectedField                       FrontDisconnected;
        CbTradeRspAuthenticateField                         RspAuthenticate;
        CbTradeRspUserLoginField                            RspUserLogin;
        CbTradeRspUserLogoutField                           RspUserLogout;
        CbTradeRspErrorField                                RspError;
        CbTradeRspSubForQuoteRspField                       RspSubForQuoteRsp;
        CbTradeRspUserPasswordUpdateField                   RspUserPasswordUpdate;
        CbTradeRspTradingAccountPasswordUpdateField         RspTradingAccountPasswordUpdate;
        CbTradeRspParkedOrderInsertField                    RspParkedOrderInsert;
        CbTradeRspParkedOrderActionField                    RspParkedOrderAction;
        CbTradeRspQryParkedOrderField                       RspQryParkedOrder;
        CbTradeRspQryParkedOrderActionField                 RspQryParkedOrderAction;
        CbTradeRspRemoveParkedOrderField                    RspRemoveParkedOrder;
        CbTradeRspRemoveParkedOrderActionField              RspRemoveParkedOrderAction;
        CbTradeRspOrderInsertField                          RspOrderInsert;
        CbTradeRspOrderActionField                          RspOrderAction;
        CbTradeRspQryOrderField                             RspQryOrder;
        CbTradeRspQryTradeField                             RspQryTrade;
        CbTradeRtnOrderField                                RtnOrder;
        CbTradeRtnTradeField                                RtnTrade;
        CbTradeErrRtnOrderInsertField                       ErrRtnOrderInsert;
        CbTradeErrRtnOrderActionField                       ErrRtnOrderAction;
        CbTradeRspForQuoteInsertField                       RspForQuoteInsert;
        CbTradeRspQuoteInsertField                          RspQuoteInsert;
        CbTradeRspQuoteActionField                          RspQuoteAction;
        CbTradeRspBatchOrderActionField                     RspBatchOrderAction;
        CbTradeRspQryForQuoteField                          RspQryForQuote;
        CbTradeRspQryQuoteField                             RspQryQuote;
        CbTradeRtnForQuoteRspField                          RtnForQuoteRsp;
        CbTradeRtnQuoteField                                RtnQuote;
        CbTradeErrRtnForQuoteInsertField                    ErrRtnForQuoteInsert;
        CbTradeErrRtnQuoteInsertField                       ErrRtnQuoteInsert;
        CbTradeErrRtnQuoteActionField                       ErrRtnQuoteAction;
        CbTradeErrRtnBatchOrderActionField                  ErrRtnBatchOrderAction;
        CbTradeRspExecOrderInsertField                      RspExecOrderInsert;
        CbTradeRspExecOrderActionField                      RspExecOrderAction;
        CbTradeRspQryExecOrderField                         RspQryExecOrder;
        CbTradeRtnExecOrderField                            RtnExecOrder;
        CbTradeErrRtnExecOrderInsertField                   ErrRtnExecOrderInsert;
        CbTradeErrRtnExecOrderActionField                   ErrRtnExecOrderAction;
        CbTradeRspCombActionInsertField                     RspCombActionInsert;
        CbTradeRspQryCombActionField                        RspQryCombAction;
        CbTradeRspQryInvestUnitField                        RspQryInvestUnit;
        CbTradeRspQryProductGroupField                      RspQryProductGroup;
        CbTradeRspQryCombInstrumentGuardField               RspQryCombInstrumentGuard;
        CbTradeRtnCombActionField                           RtnCombAction;
        CbTradeErrRtnCombActionInsertField                  ErrRtnCombActionInsert;
        CbTradeRspOptionSelfCloseInsertField                RspOptionSelfCloseInsert;
        CbTradeRspOptionSelfCloseActionField                RspOptionSelfCloseAction;
        CbTradeRspQryOptionSelfCloseField                   RspQryOptionSelfClose;
        CbTradeRspQryOptionInstrCommRateField               RspQryOptionInstrCommRate;
        CbTradeRspQryOptionInstrTradeCostField              RspQryOptionInstrTradeCost;
        CbTradeRtnOptionSelfCloseField                      RtnOptionSelfClose;
        CbTradeErrRtnOptionSelfCloseInsertField             ErrRtnOptionSelfCloseInsert;
        CbTradeErrRtnOptionSelfCloseActionField             ErrRtnOptionSelfCloseAction;
        CbTradeRspSettlementInfoConfirmField                RspSettlementInfoConfirm;
        CbTradeRspQrySettlementInfoField                    RspQrySettlementInfo;
        CbTradeRspQrySettlementInfoConfirmField             RspQrySettlementInfoConfirm;
        CbTradeRtnFromBankToFutureByBankField               RtnFromBankToFutureByBank;
        CbTradeRtnFromFutureToBankByBankField               RtnFromFutureToBankByBank;
        CbTradeRtnRepealFromBankToFutureByBankField         RtnRepealFromBankToFutureByBank;
        CbTradeRtnRepealFromFutureToBankByBankField         RtnRepealFromFutureToBankByBank;
        CbTradeRtnOpenAccountByBankField                    RtnOpenAccountByBank;
        CbTradeRtnChangeAccountByBankField                  RtnChangeAccountByBank;
        CbTradeRtnCancelAccountByBankField                  RtnCancelAccountByBank;
        CbTradeRspFromBankToFutureByFutureField             RspFromBankToFutureByFuture;
        CbTradeRspFromFutureToBankByFutureField             RspFromFutureToBankByFuture;
        CbTradeRspQryBankAccountMoneyByFutureField          RspQryBankAccountMoneyByFuture;
        CbTradeRtnQryBankBalanceByFutureField               RtnQryBankBalanceByFuture;
        CbTradeRtnFromBankToFutureByFutureField             RtnFromBankToFutureByFuture;
        CbTradeRtnFromFutureToBankByFutureField             RtnFromFutureToBankByFuture;
        CbTradeRtnRepealFromBankToFutureByFutureField       RtnRepealFromBankToFutureByFuture;
        CbTradeRtnRepealFromFutureToBankByFutureField       RtnRepealFromFutureToBankByFuture;
        CbTradeErrRtnBankToFutureByFutureField              ErrRtnBankToFutureByFuture;
        CbTradeErrRtnFutureToBankByFutureField              ErrRtnFutureToBankByFuture;
        CbTradeErrRtnQryBankBalanceByFutureField            ErrRtnQryBankBalanceByFuture;
        CbTradeRtnRepealFromBankToFutureByFutureManualField RtnRepealFromBankToFutureByFutureManual;
        CbTradeRtnRepealFromFutureToBankByFutureManualField RtnRepealFromFutureToBankByFutureManual;
        CbTradeErrRtnRepealBankToFutureByFutureManualField  ErrRtnRepealBankToFutureByFutureManual;
        CbTradeErrRtnRepealFutureToBankByFutureManualField  ErrRtnRepealFutureToBankByFutureManual;
        CbTradeRspQryNoticeField                            RspQryNotice;
        CbTradeRspQryTradingNoticeField                     RspQryTradingNotice;
        CbTradeRtnTradingNoticeField                        RtnTradingNotice;
        CbTradeRtnBulletinField                             RtnBulletin;
        CbTradeRspQryExchangeField                          RspQryExchange;
        CbTradeRspQryExchangeRateField                      RspQryExchangeRate;
        CbTradeRspQryExchangeMarginRateField                RspQryExchangeMarginRate;
        CbTradeRspQryExchangeMarginRateAdjustField          RspQryExchangeMarginRateAdjust;
        CbTradeRspQryProductField                           RspQryProduct;
        CbTradeRspQryProductExchRateField                   RspQryProductExchRate;
        CbTradeRspQryInstrumentField                        RspQryInstrument;
        CbTradeRspQryInstrumentMarginRateField              RspQryInstrumentMarginRate;
        CbTradeRspQryInstrumentCommissionRateField          RspQryInstrumentCommissionRate;
        CbTradeRspQryInstrumentOrderCommRateField           RspQryInstrumentOrderCommRate;
        CbTradeRtnInstrumentStatusField                     RtnInstrumentStatus;
        CbTradeRspQryInvestorField                          RspQryInvestor;
        CbTradeRspQryInvestorPositionField                  RspQryInvestorPosition;
        CbTradeRspQryInvestorPositionDetailField            RspQryInvestorPositionDetail;
        CbTradeRspQryInvestorPositionCombineDetailField     RspQryInvestorPositionCombineDetail;
        CbTradeRspQryInvestorProductGroupMarginField        RspQryInvestorProductGroupMargin;
        CbTradeRspQryTradingCodeField                       RspQryTradingCode;
        CbTradeRspQryTradingAccountField                    RspQryTradingAccount;
        CbTradeRspQryTransferSerialField                    RspQryTransferSerial;
        CbTradeRspQryContractBankField                      RspQryContractBank;
        CbTradeRspQryTransferBankField                      RspQryTransferBank;
        CbTradeRspQryAccountRegisterField                   RspQryAccountRegister;
        CbTradeRspQryBrokerTradingParamsField               RspQryBrokerTradingParams;
        CbTradeRspQryBrokerTradingAlgosField                RspQryBrokerTradingAlgos;
        CbTradeRspQrySecAgentAcidMapField                   RspQrySecAgentAcidMap;
        CbTradeRspQrySecAgentCheckModeField                 RspQrySecAgentCheckMode;
        CbTradeRspQrySecAgentTradingAccountField            RspQrySecAgentTradingAccount;
        CbTradeRspQryMmInstrumentCommissionRateField        RspQryMmInstrumentCommissionRate;
        CbTradeRspQryMmOptionInstrCommRateField             RspQryMmOptionInstrCommRate;
        CbTradeRspQryCfmmcTradingAccountTokenField          RspQryCfmmcTradingAccountToken;
        CbTradeRspQryCfmmcTradingAccountKeyField            RspQryCfmmcTradingAccountKey;
        CbTradeRtnCfmmcTradingAccountTokenField             RtnCfmmcTradingAccountToken;
        CbTradeRspQryDepthMarketDataField                   RspQryDepthMarketData;
        CbTradeRspQryMaxOrderVolumeField                    RspQryMaxOrderVolume;
        CbTradeRspQryEwarrantOffsetField                    RspQryEwarrantOffset;
        CbTradeRtnErrorConditionalOrderField                RtnErrorConditionalOrder;
    };
    bool IsLast;
} CbTradeField;


#endif // !OPTSP_CTPCORE_TRADESTRUCT_HPP_
