#include "tradespi.h"
#include <stdio.h>
#include "../include/arch.h"
#include "../include/tradestruct.hpp"


TradeSpi::TradeSpi(Logger * logger, ctpspi_callback_fn tfn)
    : logger(logger), trade_callback(tfn)
{
    std::stringstream log;
    spiData = new CbTradeField;
    log << "TradeSpi Inited";
    LOGINFO(logger, log);
}


///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void TradeSpi::OnFrontConnected()
{
    std::stringstream log;
    (*trade_callback)(CB_TRADE_FRONT_CONNECTED, nullptr);
    log << "Connected with Trade Front Server";
    LOGINFO(logger, log);
}


///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
void TradeSpi::OnFrontDisconnected(int nReason)
{
    std::stringstream log;
    (*trade_callback)(CB_TRADE_FRONT_DISCONNECTED, nullptr);
    log << "nReason=" << nReason;
    LOGERR(logger, log);
}


///客户端认证响应
void TradeSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pRspAuthenticateField) {
        CbTradeRspAuthenticateField *data = &spiData->RspAuthenticate;
        arch_Strcpy(data->BrokerID, pRspAuthenticateField->BrokerID, sizeof(data->BrokerID));
        arch_Strcpy(data->UserID, pRspAuthenticateField->UserID, sizeof(data->UserID));
        arch_Strcpy(data->UserProductInfo, pRspAuthenticateField->UserProductInfo, sizeof(data->UserProductInfo));
        spiData->IsLast = bIsLast;
        (*trade_callback)(CB_TRADE_RSP_AUTHENTICATE, spiData);
        log << "Success to Authenticate, BrokerID=" << pRspAuthenticateField->BrokerID
            << ", UserID=" << pRspAuthenticateField->UserID
            << ", UserProductInfo=" << pRspAuthenticateField->UserProductInfo;
        LOGINFO(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_RSP_AUTHENTICATE, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Failed to Authenticate");
    }
}


///登录请求响应
void TradeSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pRspUserLogin) {
        CbTradeRspUserLoginField *data = &spiData->RspUserLogin;
        arch_Strcpy(data->BrokerID, pRspUserLogin->BrokerID, sizeof(data->BrokerID));
        arch_Strcpy(data->TradingDay, pRspUserLogin->TradingDay, sizeof(data->TradingDay));
        arch_Strcpy(data->LoginTime, pRspUserLogin->LoginTime, sizeof(data->LoginTime));
        arch_Strcpy(data->UserID, pRspUserLogin->UserID, sizeof(data->UserID));
        arch_Strcpy(data->SHFETime, pRspUserLogin->SHFETime, sizeof(data->SHFETime));
        arch_Strcpy(data->DCETime, pRspUserLogin->DCETime, sizeof(data->DCETime));
        arch_Strcpy(data->CZCETime, pRspUserLogin->CZCETime, sizeof(data->CZCETime));
        arch_Strcpy(data->FFEXTime, pRspUserLogin->FFEXTime, sizeof(data->FFEXTime));
        arch_Strcpy(data->INETime, pRspUserLogin->INETime, sizeof(data->INETime));
        data->FrontID = pRspUserLogin->FrontID;
        data->SessionID = pRspUserLogin->SessionID;
        data->MaxOrderRef = arch_Str2Int64(pRspUserLogin->MaxOrderRef);
        spiData->IsLast = bIsLast;
        (*trade_callback)(CB_TRADE_RSP_USER_LOGIN, spiData);

        uint64_t maxOrderRef = arch_Str2Int64(pRspUserLogin->MaxOrderRef);
        log << "Login on Trade Front Server, TradingDay=" << pRspUserLogin->TradingDay
            << ", LoginTime=" << pRspUserLogin->LoginTime
            << ", BrokerID=" << pRspUserLogin->BrokerID
            << ", UserID=" << pRspUserLogin->UserID;
        LOGINFO(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_RSP_USER_LOGIN, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Failed to Login Trade Front Server");
    }
}


///登出请求响应
void TradeSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pUserLogout) {
        CbTradeRspUserLogoutField *data = &spiData->RspUserLogout;
        arch_Strcpy(data->UserID, pUserLogout->UserID, sizeof(data->UserID));
        arch_Strcpy(data->BrokerID, pUserLogout->BrokerID, sizeof(data->BrokerID));
        spiData->IsLast = bIsLast;
        (*trade_callback)(CB_TRADE_RSP_USER_LOGOUT, spiData);
        log << "Success to Logout";
        LOGINFO(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_RSP_USER_LOGOUT, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Failed to Logout");
    }
}


///用户口令更新请求响应
void TradeSpi::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pUserPasswordUpdate) {
        CbTradeRspUserPasswordUpdateField *data = &spiData->RspUserPasswordUpdate;
        arch_Strcpy(data->BrokerID, pUserPasswordUpdate->BrokerID, sizeof(data->BrokerID));
        arch_Strcpy(data->UserID, pUserPasswordUpdate->UserID, sizeof(data->UserID));
        arch_Strcpy(data->OldPassword, pUserPasswordUpdate->OldPassword, sizeof(data->OldPassword));
        arch_Strcpy(data->NewPassword, pUserPasswordUpdate->NewPassword, sizeof(data->NewPassword));
        spiData->IsLast = bIsLast;
        (*trade_callback)(CB_TRADE_RSP_USER_PASSWORD_UPDATE, spiData);
        log << "Success to Update User Password, BrokerID=" << pUserPasswordUpdate->BrokerID
            << ", UserID=" << pUserPasswordUpdate->UserID;
        LOGINFO(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_RSP_USER_PASSWORD_UPDATE, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Failed to Update User Password");
    }
}


///资金账户口令更新请求响应
void TradeSpi::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pTradingAccountPasswordUpdate) {
        CbTradeRspTradingAccountPasswordUpdateField *data = &spiData->RspTradingAccountPasswordUpdate;
        arch_Strcpy(data->AccountID, pTradingAccountPasswordUpdate->AccountID, sizeof(data->AccountID));
        arch_Strcpy(data->BrokerID, pTradingAccountPasswordUpdate->BrokerID, sizeof(data->BrokerID));
        arch_Strcpy(data->CurrencyID, pTradingAccountPasswordUpdate->CurrencyID, sizeof(data->CurrencyID));
        arch_Strcpy(data->OldPassword, pTradingAccountPasswordUpdate->OldPassword, sizeof(data->OldPassword));
        arch_Strcpy(data->NewPassword, pTradingAccountPasswordUpdate->NewPassword, sizeof(data->NewPassword));
        spiData->IsLast = bIsLast;
        (*trade_callback)(CB_TRADE_RSP_TRADING_ACCOUNT_PASSWORD_UPDATE, spiData);
        log << "Success to Update Trading Account Password, BrokerID=" << pTradingAccountPasswordUpdate->BrokerID
            << ", UserID=" << pTradingAccountPasswordUpdate->AccountID;
        LOGINFO(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_RSP_TRADING_ACCOUNT_PASSWORD_UPDATE, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Failed to Update Trading Account Password");
    }
}


///请求查询结算信息确认响应
void TradeSpi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pSettlementInfoConfirm) {
        CbTradeRspQrySettlementInfoConfirmField *data = &spiData->RspQrySettlementInfoConfirm;
        arch_Strcpy(data->AccountID, pSettlementInfoConfirm->AccountID, sizeof(data->AccountID));
        arch_Strcpy(data->BrokerID, pSettlementInfoConfirm->BrokerID, sizeof(data->BrokerID));
        arch_Strcpy(data->InvestorID, pSettlementInfoConfirm->InvestorID, sizeof(data->InvestorID));
        arch_Strcpy(data->ConfirmDate, pSettlementInfoConfirm->ConfirmDate, sizeof(data->ConfirmDate));
        arch_Strcpy(data->ConfirmTime, pSettlementInfoConfirm->ConfirmTime, sizeof(data->ConfirmTime));
        arch_Strcpy(data->AccountID, pSettlementInfoConfirm->AccountID, sizeof(data->AccountID));
        arch_Strcpy(data->CurrencyID, pSettlementInfoConfirm->CurrencyID, sizeof(data->CurrencyID));
        data->SettlementID = pSettlementInfoConfirm->SettlementID;
        spiData->IsLast = bIsLast;
        (*trade_callback)(CB_TRADE_RSP_QRY_SETTLEMENT_INFO_CONFIRM, spiData);
        log << "Success to Query Settlement Info Confirm";
        LOGINFO(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_RSP_QRY_SETTLEMENT_INFO_CONFIRM, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Failed to Query Settlement Info Confirm");
    }
}


///请求查询投资者结算结果响应
void TradeSpi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pSettlementInfo) {
        CbTradeRspQrySettlementInfoField *data = &spiData->RspQrySettlementInfo;
        arch_Strcpy(data->AccountID, pSettlementInfo->AccountID, sizeof(data->AccountID));
        arch_Strcpy(data->BrokerID, pSettlementInfo->BrokerID, sizeof(data->BrokerID));
        arch_Strcpy(data->Content, pSettlementInfo->Content, sizeof(data->Content));
        arch_Strcpy(data->CurrencyID, pSettlementInfo->CurrencyID, sizeof(data->CurrencyID));
        arch_Strcpy(data->InvestorID, pSettlementInfo->InvestorID, sizeof(data->InvestorID));
        arch_Strcpy(data->TradingDay, pSettlementInfo->TradingDay, sizeof(data->TradingDay));
        data->SequenceNo = pSettlementInfo->SequenceNo;
        data->SettlementID = pSettlementInfo->SettlementID;
        spiData->IsLast = bIsLast;
        (*trade_callback)(CB_TRADE_RSP_QRY_SETTLEMENT_INFO, spiData);
        log << "Success to Query Settlement Info";
        LOGINFO(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_RSP_QRY_SETTLEMENT_INFO, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Failed to Query Settlement Info");
    }
}


///投资者结算结果确认响应
void TradeSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pSettlementInfoConfirm) {
        CbTradeRspSettlementInfoConfirmField *data = &spiData->RspSettlementInfoConfirm;
        arch_Strcpy(data->AccountID, pSettlementInfoConfirm->AccountID, sizeof(data->AccountID));
        arch_Strcpy(data->BrokerID, pSettlementInfoConfirm->BrokerID, sizeof(data->BrokerID));
        arch_Strcpy(data->InvestorID, pSettlementInfoConfirm->InvestorID, sizeof(data->InvestorID));
        arch_Strcpy(data->ConfirmDate, pSettlementInfoConfirm->ConfirmDate, sizeof(data->ConfirmDate));
        arch_Strcpy(data->ConfirmTime, pSettlementInfoConfirm->ConfirmTime, sizeof(data->ConfirmTime));
        arch_Strcpy(data->AccountID, pSettlementInfoConfirm->AccountID, sizeof(data->AccountID));
        arch_Strcpy(data->CurrencyID, pSettlementInfoConfirm->CurrencyID, sizeof(data->CurrencyID));
        data->SettlementID = pSettlementInfoConfirm->SettlementID;
        spiData->IsLast = bIsLast;
        (*trade_callback)(CB_TRADE_RSP_SETTLEMENT_INFO_CONFIRM, spiData);
        log << "Success to Response Settlement Info Confirm, " 
            << pSettlementInfoConfirm->AccountID << ", " << pSettlementInfoConfirm->BrokerID << ", "
            << pSettlementInfoConfirm->ConfirmDate << ", " << pSettlementInfoConfirm->ConfirmTime << ", "
            << pSettlementInfoConfirm->CurrencyID << ", " << pSettlementInfoConfirm->InvestorID << ", "
            << pSettlementInfoConfirm->SettlementID;
        LOGDBG(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_RSP_SETTLEMENT_INFO_CONFIRM, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Failed to Response Settlement Info Confirm");
    }
}


///请求查询投资者持仓响应
void TradeSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pInvestorPosition) {
        CbTradeRspQryInvestorPositionField *data = &spiData->RspQryInvestorPosition;
        arch_Strcpy(data->TradingDay, pInvestorPosition->TradingDay, sizeof(data->TradingDay));
        arch_Strcpy(data->InvestorID, pInvestorPosition->InvestorID, sizeof(data->InvestorID));
        arch_Strcpy(data->InstrumentID, pInvestorPosition->InstrumentID, sizeof(data->InstrumentID));
        data->OpenAmount = pInvestorPosition->OpenAmount;
        data->CloseAmount = pInvestorPosition->CloseAmount;
        data->Commission = pInvestorPosition->Commission;
        data->CloseProfit = pInvestorPosition->CloseProfit;
        data->PositionProfit = pInvestorPosition->PositionProfit;
        data->OpenCost = pInvestorPosition->OpenCost;
        data->UseMargin = pInvestorPosition->UseMargin;
        data->PositionCost = pInvestorPosition->PositionCost;
        data->YdPosition = pInvestorPosition->YdPosition;
        data->Position = pInvestorPosition->Position;
        data->TodayPosition = pInvestorPosition->TodayPosition;
        data->OpenVolume = pInvestorPosition->OpenVolume;
        data->CloseVolume = pInvestorPosition->CloseVolume;
        data->SettlementID = pInvestorPosition->SettlementID;
        data->PosiDirection = pInvestorPosition->PosiDirection;
        data->PositionDate = pInvestorPosition->PositionDate;
        spiData->IsLast = bIsLast;
        (*trade_callback)(CB_TRADE_RSP_QRY_INVESTOR_POSITION, spiData);
        log << "Success to Query Investor Position";
        LOGDBG(logger , log);
    }
    else {
        (*trade_callback)(CB_TRADE_RSP_QRY_INVESTOR_POSITION, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Failed to Query Investor Position");
    }
}


///请求查询交易所响应
void TradeSpi::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pExchange) {
        CbTradeRspQryExchangeField *data = &spiData->RspQryExchange;
        arch_Strcpy(data->ExchangeID, pExchange->ExchangeID, sizeof(data->ExchangeID));
        arch_Strcpy(data->ExchangeName, pExchange->ExchangeName, sizeof(data->ExchangeName));
        data->ExchangeProperty = pExchange->ExchangeProperty;
        spiData->IsLast = bIsLast;
        (*trade_callback)(CB_TRADE_RSP_QRY_EXCHANGE, spiData);
        log << "Success to Query Exchange";
        LOGDBG(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_RSP_QRY_EXCHANGE, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Failed to Query Exchange");
    }
}


///请求查询产品响应
void TradeSpi::OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pProduct) {
        CbTradeRspQryProductField *data = &spiData->RspQryProduct;
        arch_Strcpy(data->ProductID, pProduct->ProductID, sizeof(data->ProductID));
        arch_Strcpy(data->ExchangeProductID, pProduct->ExchangeProductID, sizeof(data->ExchangeProductID));
        arch_Strcpy(data->ProductName, pProduct->ProductName, sizeof(data->ProductName));
        arch_Strcpy(data->ExchangeID, pProduct->ExchangeID, sizeof(data->ExchangeID));
        arch_Strcpy(data->TradeCurrencyID, pProduct->TradeCurrencyID, sizeof(data->TradeCurrencyID));
        data->PriceTick = pProduct->PriceTick;
        data->UnderlyingMultiple = pProduct->UnderlyingMultiple;
        data->VolumeMultiple = pProduct->VolumeMultiple;
        data->ProductClass = pProduct->ProductClass;
        data->PositionType = pProduct->PositionType;
        data->PositionDateType = pProduct->PositionDateType;
        data->CloseDealType = pProduct->CloseDealType;
        spiData->IsLast = bIsLast;
        (*trade_callback)(CB_TRADE_RSP_QRY_PRODUCT, spiData);
        log << "Success to Query Product";
        LOGDBG(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_RSP_QRY_PRODUCT, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Failed to Query Product");
    }
}


///请求查询合约响应
void TradeSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pInstrument) {
        CbTradeRspQryInstrumentField *data = &spiData->RspQryInstrument;
        arch_Strcpy(data->InstrumentID, pInstrument->InstrumentID, sizeof(data->InstrumentID));
        arch_Strcpy(data->ExchangeID, pInstrument->ExchangeID, sizeof(data->ExchangeID));
        arch_Strcpy(data->InstrumentName, pInstrument->InstrumentName, sizeof(data->InstrumentName));
        arch_Strcpy(data->ExchangeInstID, pInstrument->ExchangeInstID, sizeof(data->ExchangeInstID));
        data->LongMarginRatio = pInstrument->LongMarginRatio;
        data->ShortMarginRatio = pInstrument->ShortMarginRatio;
        data->UnderlyingMultiple = pInstrument->UnderlyingMultiple;
        data->VolumeMultiple = pInstrument->VolumeMultiple;
        data->InstLifePhase = pInstrument->InstLifePhase;
        data->IsTrading = pInstrument->IsTrading;
        spiData->IsLast = bIsLast;
        (*trade_callback)(CB_TRADE_RSP_QRY_INSTRUMENT, spiData);
        log << "Success to Query Instrument";
        LOGDBG(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_RSP_QRY_INSTRUMENT, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Failed to Query Instrument");
    }
}


///报单录入请求响应
void TradeSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pInputOrder) {
        CbTradeRspOrderInsertField *data = &spiData->RspOrderInsert;
        arch_Strcpy(data->AccountID, pInputOrder->AccountID, sizeof(data->AccountID));
        arch_Strcpy(data->BrokerID, pInputOrder->BrokerID, sizeof(data->BrokerID));
        arch_Strcpy(data->InvestorID, pInputOrder->InvestorID, sizeof(data->InvestorID));
        arch_Strcpy(data->InstrumentID, pInputOrder->InstrumentID, sizeof(data->InstrumentID));
        arch_Strcpy(data->UserID, pInputOrder->UserID, sizeof(data->UserID));
        arch_Strcpy(data->IPAddress, pInputOrder->IPAddress, sizeof(data->IPAddress));
        arch_Strcpy(data->MacAddress, pInputOrder->MacAddress, sizeof(data->MacAddress));
        arch_Strcpy(data->GTDDate, pInputOrder->GTDDate, sizeof(data->GTDDate));
        data->OrderRef = arch_Str2Int64(pInputOrder->OrderRef);
        data->LimitPrice = pInputOrder->LimitPrice;
        data->StopPrice = pInputOrder->StopPrice;
        data->VolumeTotalOriginal = pInputOrder->VolumeTotalOriginal;
        data->MinVolume = pInputOrder->MinVolume;
        data->RequestID = pInputOrder->RequestID;
        data->Direction = pInputOrder->Direction;
        data->OrderPriceType = pInputOrder->OrderPriceType;
        data->TimeCondition = pInputOrder->TimeCondition;
        data->VolumeCondition = pInputOrder->VolumeCondition;
        data->ContingentCondition = pInputOrder->ContingentCondition;
        data->ForceCloseReason = pInputOrder->ForceCloseReason;
        data->UserForceClose = pInputOrder->UserForceClose;
        spiData->IsLast = bIsLast;
        (*trade_callback)(CB_TRADE_RSP_ORDER_INSERT, spiData);
        log << "Success to Insert Order";
        LOGDBG(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_RSP_ORDER_INSERT, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Failed to Insert Order");
    }
}


///报单操作请求响应
void TradeSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pInputOrderAction) {
        CbTradeRspOrderActionField *data = &spiData->RspOrderAction;
        arch_Strcpy(data->BrokerID, pInputOrderAction->BrokerID, sizeof(data->BrokerID));
        arch_Strcpy(data->UserID, pInputOrderAction->UserID, sizeof(data->UserID));
        arch_Strcpy(data->InvestorID, pInputOrderAction->InvestorID, sizeof(data->InvestorID));
        arch_Strcpy(data->ExchangeID, pInputOrderAction->ExchangeID, sizeof(data->ExchangeID));
        arch_Strcpy(data->InstrumentID, pInputOrderAction->InstrumentID, sizeof(data->InstrumentID));
        arch_Strcpy(data->OrderSysID, pInputOrderAction->OrderSysID, sizeof(data->OrderSysID));
        arch_Strcpy(data->IPAddress, pInputOrderAction->IPAddress, sizeof(data->IPAddress));
        arch_Strcpy(data->MacAddress, pInputOrderAction->MacAddress, sizeof(data->MacAddress));
        data->OrderRef = arch_Str2Int64(pInputOrderAction->OrderRef);
        data->LimitPrice = pInputOrderAction->LimitPrice;
        data->OrderActionRef = pInputOrderAction->OrderActionRef;
        data->RequestID = pInputOrderAction->RequestID;
        data->FrontID = pInputOrderAction->FrontID;
        data->SessionID = pInputOrderAction->SessionID;
        data->VolumeChange = pInputOrderAction->VolumeChange;
        data->ActionFlag = pInputOrderAction->ActionFlag;
        spiData->IsLast = bIsLast;
        (*trade_callback)(CB_TRADE_RSP_ORDER_ACTION, spiData);
        log << "Success to Response Order Action";
        LOGDBG(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_RSP_ORDER_ACTION, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Failed to Response Order Action");
    }
}


///报单通知
void TradeSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
    std::stringstream log;
    CbTradeRtnOrderField *data = &spiData->RtnOrder;
    arch_Strcpy(data->BrokerID, pOrder->BrokerID, sizeof(data->BrokerID));
    arch_Strcpy(data->InvestorID, pOrder->InvestorID, sizeof(data->InvestorID));
    arch_Strcpy(data->AccountID, pOrder->AccountID, sizeof(data->AccountID));
    arch_Strcpy(data->InstrumentID, pOrder->InstrumentID, sizeof(data->InstrumentID));
    arch_Strcpy(data->UserID, pOrder->UserID, sizeof(data->UserID));
    arch_Strcpy(data->IPAddress, pOrder->IPAddress, sizeof(data->IPAddress));
    arch_Strcpy(data->MacAddress, pOrder->MacAddress, sizeof(data->MacAddress));
    arch_Strcpy(data->OrderLocalID, pOrder->OrderLocalID, sizeof(data->OrderLocalID));
    arch_Strcpy(data->OrderSysID, pOrder->OrderSysID, sizeof(data->OrderSysID));
    arch_Strcpy(data->InsertDate, pOrder->InsertDate, sizeof(data->InsertDate));
    arch_Strcpy(data->InsertTime, pOrder->InsertTime, sizeof(data->InsertTime));
    arch_Strcpy(data->ActiveTime, pOrder->ActiveTime, sizeof(data->ActiveTime));
    arch_Strcpy(data->SuspendTime, pOrder->SuspendTime, sizeof(data->SuspendTime));
    arch_Strcpy(data->UpdateTime, pOrder->UpdateTime, sizeof(data->UpdateTime));
    arch_Strcpy(data->CancelTime, pOrder->CancelTime, sizeof(data->CancelTime));
    data->OrderRef = arch_Str2Int64(pOrder->OrderRef);
    data->LimitPrice = pOrder->LimitPrice;
    data->StopPrice = pOrder->StopPrice;
    data->VolumeTotalOriginal = pOrder->VolumeTotalOriginal;
    data->MinVolume = pOrder->MinVolume;
    data->RequestID = pOrder->RequestID;
    data->FrontID = pOrder->FrontID;
    data->SessionID = pOrder->SessionID;
    data->NotifySequence = pOrder->NotifySequence;
    data->VolumeTraded = pOrder->VolumeTraded;
    data->VolumeTotal = pOrder->VolumeTotal;
    data->SequenceNo = pOrder->SequenceNo;
    data->SettlementID = pOrder->SettlementID;
    data->Direction = pOrder->Direction;
    data->OrderPriceType = pOrder->OrderPriceType;
    data->TimeCondition = pOrder->TimeCondition;
    data->VolumeCondition = pOrder->VolumeCondition;
    data->ContingentCondition = pOrder->ContingentCondition;
    data->ForceCloseReason = pOrder->ForceCloseReason;
    data->OrderSubmitStatus = pOrder->OrderSubmitStatus;
    data->OrderStatus = pOrder->OrderStatus;
    data->OrderSource = pOrder->OrderSource;
    data->OrderType = pOrder->OrderType;
    data->UserForceClose = pOrder->UserForceClose;
    (*trade_callback)(CB_TRADE_RTN_ORDER, spiData);
    log << "Rtn Order";
    LOGTRACE(logger, log);
}


///成交通知
void TradeSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
    std::stringstream log;
    CbTradeRtnTradeField *data = &spiData->RtnTrade;
    arch_Strcpy(data->BrokerID, pTrade->BrokerID, sizeof(data->BrokerID));
    arch_Strcpy(data->InvestorID, pTrade->InvestorID, sizeof(data->InvestorID));
    arch_Strcpy(data->InstrumentID, pTrade->InstrumentID, sizeof(data->InstrumentID));
    arch_Strcpy(data->UserID, pTrade->UserID, sizeof(data->UserID));
    arch_Strcpy(data->OrderSysID, pTrade->OrderSysID, sizeof(data->OrderSysID));
    arch_Strcpy(data->OrderLocalID, pTrade->OrderLocalID, sizeof(data->OrderLocalID));
    arch_Strcpy(data->TradeDate, pTrade->TradeDate, sizeof(data->TradeDate));
    arch_Strcpy(data->TradeTime, pTrade->TradeTime, sizeof(data->TradeTime));
    data->OrderRef = arch_Str2Int64(pTrade->OrderRef);
    data->Price = pTrade->Price;
    data->SettlementID = pTrade->SettlementID;
    data->Volume = pTrade->Volume;
    data->Direction = pTrade->Direction;
    (*trade_callback)(CB_TRADE_RTN_TRADE, spiData);
    log << "Rtn Trade";
    LOGTRACE(logger, log);
}


///报单录入错误回报
void TradeSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pInputOrder) {
        CbTradeErrRtnOrderInsertField *data = &spiData->ErrRtnOrderInsert;
        arch_Strcpy(data->AccountID, pInputOrder->AccountID, sizeof(data->AccountID));
        arch_Strcpy(data->BrokerID, pInputOrder->BrokerID, sizeof(data->BrokerID));
        arch_Strcpy(data->InvestorID, pInputOrder->InvestorID, sizeof(data->InvestorID));
        arch_Strcpy(data->InstrumentID, pInputOrder->InstrumentID, sizeof(data->InstrumentID));
        arch_Strcpy(data->UserID, pInputOrder->UserID, sizeof(data->UserID));
        arch_Strcpy(data->IPAddress, pInputOrder->IPAddress, sizeof(data->IPAddress));
        arch_Strcpy(data->MacAddress, pInputOrder->MacAddress, sizeof(data->MacAddress));
        arch_Strcpy(data->GTDDate, pInputOrder->GTDDate, sizeof(data->GTDDate));
        data->OrderRef = arch_Str2Int64(pInputOrder->OrderRef);
        data->LimitPrice = pInputOrder->LimitPrice;
        data->StopPrice = pInputOrder->StopPrice;
        data->VolumeTotalOriginal = pInputOrder->VolumeTotalOriginal;
        data->MinVolume = pInputOrder->MinVolume;
        data->RequestID = pInputOrder->RequestID;
        data->Direction = pInputOrder->Direction;
        data->OrderPriceType = pInputOrder->OrderPriceType;
        data->TimeCondition = pInputOrder->TimeCondition;
        data->VolumeCondition = pInputOrder->VolumeCondition;
        data->ContingentCondition = pInputOrder->ContingentCondition;
        data->ForceCloseReason = pInputOrder->ForceCloseReason;
        data->UserForceClose = pInputOrder->UserForceClose;
        (*trade_callback)(CB_TRADE_ERR_RTN_ORDER_INSERT, spiData);
        log << "Error on Order Insert";
        LOGERR(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_ERR_RTN_ORDER_INSERT, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Error on Order Insert");
    }
}


///报单操作错误回报
void TradeSpi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pOrderAction) {
        CbTradeErrRtnOrderActionField *data = &spiData->ErrRtnOrderAction;
        arch_Strcpy(data->BrokerID, pOrderAction->BrokerID, sizeof(data->BrokerID));
        arch_Strcpy(data->UserID, pOrderAction->UserID, sizeof(data->UserID));
        arch_Strcpy(data->InvestorID, pOrderAction->InvestorID, sizeof(data->InvestorID));
        arch_Strcpy(data->ExchangeID, pOrderAction->ExchangeID, sizeof(data->ExchangeID));
        arch_Strcpy(data->InstrumentID, pOrderAction->InstrumentID, sizeof(data->InstrumentID));
        arch_Strcpy(data->OrderSysID, pOrderAction->OrderSysID, sizeof(data->OrderSysID));
        arch_Strcpy(data->IPAddress, pOrderAction->IPAddress, sizeof(data->IPAddress));
        arch_Strcpy(data->MacAddress, pOrderAction->MacAddress, sizeof(data->MacAddress));
        data->OrderRef = arch_Str2Int64(pOrderAction->OrderRef);
        data->LimitPrice = pOrderAction->LimitPrice;
        data->OrderActionRef = pOrderAction->OrderActionRef;
        data->RequestID = pOrderAction->RequestID;
        data->FrontID = pOrderAction->FrontID;
        data->SessionID = pOrderAction->SessionID;
        data->VolumeChange = pOrderAction->VolumeChange;
        data->ActionFlag = pOrderAction->ActionFlag;
        (*trade_callback)(CB_TRADE_ERR_RTN_ORDER_ACTION, spiData);
        log << "Error on Order Action";
        LOGERR(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_ERR_RTN_ORDER_ACTION, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Error on Order Action");
    }
}


///合约交易状态通知
void TradeSpi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{
    std::stringstream log;
    CbTradeRtnInstrumentStatusField *data = &spiData->RtnInstrumentStatus;
    arch_Strcpy(data->ExchangeID, pInstrumentStatus->ExchangeID, sizeof(data->ExchangeID));
    arch_Strcpy(data->ExchangeInstID, pInstrumentStatus->ExchangeInstID, sizeof(data->ExchangeInstID));
    arch_Strcpy(data->InstrumentID, pInstrumentStatus->InstrumentID, sizeof(data->InstrumentID));
    arch_Strcpy(data->EnterTime, pInstrumentStatus->EnterTime, sizeof(data->EnterTime));
    data->EnterReason = pInstrumentStatus->EnterReason;
    data->InstrumentStatus = pInstrumentStatus->InstrumentStatus;
    (*trade_callback)(CB_TRADE_RTN_INSTRUMENT_STATUS, spiData);
    log << pInstrumentStatus->EnterReason << "," << pInstrumentStatus->EnterTime << ","
        << pInstrumentStatus->ExchangeID << "," << pInstrumentStatus->ExchangeInstID << ","
        << pInstrumentStatus->InstrumentID << "," << pInstrumentStatus->InstrumentStatus << ","
        << pInstrumentStatus->SettlementGroupID << "," << pInstrumentStatus->TradingSegmentSN;
    LOGTRACE(logger, log);
}


///交易通知
void TradeSpi::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo)
{
    std::stringstream log;
    CbTradeRtnTradingNoticeField *data = &spiData->RtnTradingNotice;
    arch_Strcpy(data->BrokerID, pTradingNoticeInfo->BrokerID, sizeof(data->BrokerID));
    arch_Strcpy(data->InvestorID, pTradingNoticeInfo->InvestorID, sizeof(data->InvestorID));
    arch_Strcpy(data->SendTime, pTradingNoticeInfo->SendTime, sizeof(data->SendTime));
    arch_Strcpy(data->FieldContent, pTradingNoticeInfo->FieldContent, sizeof(data->FieldContent));
    data->SequenceSeries = pTradingNoticeInfo->SequenceSeries;
    data->SequenceNo = pTradingNoticeInfo->SequenceNo;
    (*trade_callback)(CB_TRADE_RTN_TRADING_NOTICE, spiData);
    log << pTradingNoticeInfo->BrokerID << "," << pTradingNoticeInfo->FieldContent << ","
        << pTradingNoticeInfo->InvestorID << "," << pTradingNoticeInfo->InvestUnitID << ","
        << pTradingNoticeInfo->SendTime << "," << pTradingNoticeInfo->SequenceNo << ","
        << pTradingNoticeInfo->SequenceSeries;
    LOGINFO(logger, log);
}


///请求查询资金账户响应
void TradeSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pTradingAccount) {
        CbTradeRspQryTradingAccountField *data = &spiData->RspQryTradingAccount;
        arch_Strcpy(data->TradingDay, pTradingAccount->TradingDay, sizeof(data->TradingDay));
        arch_Strcpy(data->BrokerID, pTradingAccount->BrokerID, sizeof(data->BrokerID));
        arch_Strcpy(data->CurrencyID, pTradingAccount->CurrencyID, sizeof(data->CurrencyID));
        data->FrozenMargin = pTradingAccount->FrozenMargin;
        data->FrozenCash = pTradingAccount->FrozenCash;
        data->FrozenCommission = pTradingAccount->FrozenCommission;
        data->CurrMargin = pTradingAccount->CurrMargin;
        data->CashIn = pTradingAccount->CashIn;
        data->Commission = pTradingAccount->Commission;
        data->CloseProfit = pTradingAccount->CloseProfit;
        data->PositionProfit = pTradingAccount->PositionProfit;
        data->Balance = pTradingAccount->Balance;
        data->Available = pTradingAccount->Available;
        data->Reserve = pTradingAccount->Reserve;
        data->ExchangeMargin = pTradingAccount->ExchangeMargin;
        data->ReserveBalance = pTradingAccount->ReserveBalance;
        spiData->IsLast = bIsLast;
        (*trade_callback)(CB_TRADE_RSP_QRY_TRADING_ACCOUNT, spiData);
        log << "Success to Query Trading Account";
        LOGINFO(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_RSP_QRY_TRADING_ACCOUNT, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Failed to Query Trading Account");
    }
}


///请求查询投资者响应
void TradeSpi::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::stringstream log;
    if (!(pRspInfo && pRspInfo->ErrorID != 0) && pInvestor) {
        CbTradeRspQryInvestorField *data = &spiData->RspQryInvestor;
        arch_Strcpy(data->InvestorID, pInvestor->InvestorID, sizeof(data->InvestorID));
        arch_Strcpy(data->BrokerID, pInvestor->BrokerID, sizeof(data->BrokerID));
        arch_Strcpy(data->InvestorGroupID, pInvestor->InvestorGroupID, sizeof(data->InvestorGroupID));
        arch_Strcpy(data->InvestorName, pInvestor->InvestorName, sizeof(data->InvestorName));
        arch_Strcpy(data->IdentifiedCardNo, pInvestor->IdentifiedCardNo, sizeof(data->IdentifiedCardNo));
        arch_Strcpy(data->Telephone, pInvestor->Telephone, sizeof(data->Telephone));
        arch_Strcpy(data->Address, pInvestor->Address, sizeof(data->Address));
        arch_Strcpy(data->OpenDate, pInvestor->OpenDate, sizeof(data->OpenDate));
        arch_Strcpy(data->Mobile, pInvestor->Mobile, sizeof(data->Mobile));
        data->IdentifiedCardType = pInvestor->IdentifiedCardType;
        data->IsActive = pInvestor->IsActive;
        spiData->IsLast = bIsLast;
        (*trade_callback)(CB_TRADE_RSP_QRY_INVESTOR, spiData);
        log << "Success to Query Investor, " << pInvestor->InvestorID << "," << pInvestor->BrokerID;
        LOGINFO(logger, log);
    }
    else {
        (*trade_callback)(CB_TRADE_RSP_QRY_INVESTOR, nullptr);
        RSPINFO_ERROR(log, pRspInfo, "Failed to Query Investor");
    }
}
