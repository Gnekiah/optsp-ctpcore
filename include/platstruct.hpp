#ifndef OPTSP_CTPCORE_PLATSTRUCT_HPP_
#define OPTSP_CTPCORE_PLATSTRUCT_HPP_

#include <atomic>
#include "datatype.hpp"
#include "quotestruct.hpp"
#include "tradestruct.hpp"


#define RSPINFO_ERROR(log, rsp, msg) do { \
    log << msg; \
    if (rsp) \
        log << ", ErrorID=" << rsp->ErrorID << ", ErrorMsg=" << rsp->ErrorMsg; \
    else \
        log << ", pRspInfo == NULL"; \
    LOGERR(logger, log); \
} while(0)

#define APIRTN_ERROR(log, cmdid, ret, msg) do { \
    if (ret) { \
        log << msg << ", nRequest=" << cmdid << ", ret=" << ret; \
        LOGERR(logger, log); \
    } \
} while(0)


#define QUOTE_STATE_NONE                            0x00
#define QUOTE_STATE_CONNECTED                       0x01
#define QUOTE_STATE_LOGINED                         0x02

#define TRADE_STATE_NONE                            0x10
#define TRADE_STATE_AUTHENED                        0x11
#define TRADE_STATE_CONNECTED                       0x12
#define TRADE_STATE_LOGINED                         0x13
#define TRADE_STATE_SETTLEMENT_CONFIRMED            0x14

#define TRADE_STATE_EXCHANGE_QUERIED                0x21
#define TRADE_STATE_PRODUCT_QUERIED                 0x22
#define TRADE_STATE_INSTRUMENT_QUERIED              0x23

/*
typedef struct PlatCmdReqUserLoginField {
    BrokerIDType            BrokerID;
    UserIDType              UserID;
    PasswordType            Password;
    ProductInfoType         ProductInfo;
    IPAddressType           ClientIPAddress;
} PlatCmdReqUserLoginField;

typedef struct PlatCmdReqUserLogoutField {
    BrokerIDType            BrokerID;
    UserIDType              UserID;
} PlatCmdReqUserLogoutField;

typedef struct PlatCmdReqUserPasswordUpdateField {
    BrokerIDType            BrokerID;
    UserIDType              UserID;
    PasswordType            OldPassword;
    PasswordType            NewPassword;
} PlatCmdReqUserPasswordUpdateField;

typedef struct PlatCmdReqTradingAccountPasswordUpdateField {
    BrokerIDType            BrokerID;
    AccountIDType           AccountID;
    PasswordType            OldPassword;
    PasswordType            NewPassword;
} PlatCmdReqTradingAccountPasswordUpdateField;

typedef struct PlatCmdReqOrderInsertField {
    BrokerIDType            BrokerID;
    UserIDType              UserID;
    InvestorIDType          InvestorID;
    InstrumentIDType        InstrumentID;
    DateType                GTDDate;
    uint64_t                OrderRef;
    double                  LimitPrice;
    double                  StopPrice;
    int                     VolumeTotalOriginal;
    int                     MinVolume;
    int                     RequestID;
    char                    OrderPriceType;
    char                    Direction;
    char                    TimeCondition;
    char                    VolumeCondition;
    char                    ContingentCondition;
    char                    ForceCloseReason;
    bool                    UserForceClose;
} PlatCmdReqOrderInsertField;

typedef struct PlatCmdReqOrderActionField {
    BrokerIDType            BrokerID;
    InvestorIDType          InvestorID;
    uint64_t                OrderRef;
    int                     OrderActionRef;
    int                     RequestID;
    int                     FrontID;
    int                     SessionID;
    //TODO
} PlatCmdReqOrderActionField;
*/

typedef struct PlatCmdField {
    int Type;           ///命令类型
    int Id;             ///命令的ID；来自lower层的命令的ID为负，分别为-1和-2
    int Ret;            ///执行API的返回值
     union {
         CThostFtdcReqUserLoginField                    ReqUserLogin;
         CThostFtdcUserLogoutField                      UserLogout;
         CThostFtdcReqAuthenticateField                 ReqAuthenticate;
         CThostFtdcUserPasswordUpdateField              UserPasswordUpdate;
         CThostFtdcTradingAccountPasswordUpdateField    TradingAccountPasswordUpdate;
         CThostFtdcInputOrderField                      InputOrder;
         CThostFtdcOrderActionField                     OrderAction;
         CThostFtdcQrySettlementInfoConfirmField        QrySettlementInfoConfirm;
         CThostFtdcQrySettlementInfoField               QrySettlementInfo;
         CThostFtdcSettlementInfoConfirmField           SettlementInfoConfirm;
         CThostFtdcQryExchangeField                     QryExchange;
         CThostFtdcQryProductField                      QryProduct;
         CThostFtdcQryInstrumentField                   QryInstrument;
    };
} PlatCmdField;

#endif // !OPTSP_CTPCORE_PLATSTRUCT_HPP_

