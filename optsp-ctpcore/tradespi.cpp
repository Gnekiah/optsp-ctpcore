#include "tradespi.h"
#include <stdio.h>
#include "arch.h"
#include "tradestruct.hpp"


TradeSpi::TradeSpi(Logger * logger, TradeSyncField * tradeSync, trade_callback_fn* fn)
	: logger(logger), tradeSync(tradeSync), trade_callback(fn)
{
	std::stringstream log;
	log << "TradeSpi Inited";
	LOGINFO(logger, log);
}


///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void TradeSpi::OnFrontConnected()
{
	std::stringstream log;
	tradeSync->TradeState = PLTSYNC_TRADE_CONNECTED;
	tradeSync->TradeActive = true;
	(*trade_callback)(CB_TRADE_CONNECTED, true, nullptr);
	log << "Connected with Trade Front Server";
	LOGINFO(logger, log);
}


///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
void TradeSpi::OnFrontDisconnected(int nReason)
{
	std::stringstream log;
	(*trade_callback)(CB_TRADE_DISCONNECTED, true, nullptr);
	log << "nReason=" << nReason;
	LOGERR(logger, log);
}


///客户端认证响应
void TradeSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pRspAuthenticateField) {
		tradeSync->TradeState = PLTSYNC_TRADE_AUTHENTICATED;
		tradeSync->TradeActive = true;
		(*trade_callback)(CB_TRADE_RSP_AUTHENTICATE, true, nullptr);
		log << "Success to Authenticate, BrokerID=" << pRspAuthenticateField->BrokerID
			<< ", UserID=" << pRspAuthenticateField->UserID
			<< ", UserProductInfo=" << pRspAuthenticateField->UserProductInfo;
		LOGINFO(logger, log);
	}
	else {
		(*trade_callback)(CB_TRADE_RSP_AUTHENTICATE, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Authenticate");
	}
}


///登录请求响应
void TradeSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pRspUserLogin) {
		tradeSync->TradeState = PLTSYNC_TRADE_LOGINED;
		tradeSync->TradeActive = true;
		(*trade_callback)(CB_TRADE_RSP_USER_LOGIN, true, nullptr);
		maxOrderRef = strtoull(pRspUserLogin->MaxOrderRef, 0, 10);
		log << "Login on Trade Front Server, TradingDay=" << pRspUserLogin->TradingDay
			<< ", LoginTime=" << pRspUserLogin->LoginTime
			<< ", BrokerID=" << pRspUserLogin->BrokerID
			<< ", UserID=" << pRspUserLogin->UserID;
		LOGINFO(logger, log);
	}
	else {
		(*trade_callback)(CB_TRADE_RSP_USER_LOGIN, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Login Trade Front Server");
	}
}


///登出请求响应
void TradeSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pUserLogout) {
		(*trade_callback)(CB_TRADE_RSP_USER_LOGOUT, true, nullptr);
		log << "Success to Logout";
		LOGINFO(logger, log);
	}
	else {
		(*trade_callback)(CB_TRADE_RSP_USER_LOGOUT, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Logout");
	}
}


///用户口令更新请求响应
void TradeSpi::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pUserPasswordUpdate) {
		(*trade_callback)(CB_TRADE_RSP_USER_PASSWD_UPDATE, true, nullptr);
		log << "Success to Update User Password, BrokerID=" << pUserPasswordUpdate->BrokerID
			<< ", UserID=" << pUserPasswordUpdate->UserID;
		LOGINFO(logger, log);
	}
	else {
		(*trade_callback)(CB_TRADE_RSP_USER_PASSWD_UPDATE, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Update User Password");
	}
}


///资金账户口令更新请求响应
void TradeSpi::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pTradingAccountPasswordUpdate) {
		(*trade_callback)(CB_TRADE_RSP_TRADING_ACCOUNT_PASSWD_UPDATE, true, nullptr);
		log << "Success to Update Trading Account Password, BrokerID=" << pTradingAccountPasswordUpdate->BrokerID
			<< ", UserID=" << pTradingAccountPasswordUpdate->AccountID;
		LOGINFO(logger, log);
	}
	else {
		(*trade_callback)(CB_TRADE_RSP_TRADING_ACCOUNT_PASSWD_UPDATE, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Update Trading Account Password");
	}
}


///请求查询投资者结算结果响应
void TradeSpi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pSettlementInfo) {
		(*trade_callback)(CB_TRADE_RSP_QRY_SETTLEMENT_INFO, true, nullptr);
		log << "Success to Query Settlement Info";
		LOGINFO(logger, log);
	}
	else {
		(*trade_callback)(CB_TRADE_RSP_QRY_SETTLEMENT_INFO, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Query Settlement Info");
	}
}


///请求查询结算信息确认响应
void TradeSpi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pSettlementInfoConfirm) {
		(*trade_callback)(CB_TRADE_RSP_QRY_SETTLEMENT_INFO_CONFIRM, true, nullptr);
		log << "Success to Query Settlement Info Confirm";
		LOGINFO(logger, log);
	}
	else {
		(*trade_callback)(CB_TRADE_RSP_QRY_SETTLEMENT_INFO_CONFIRM, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Query Settlement Info Confirm");
	}
}



///投资者结算结果确认响应
void TradeSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pSettlementInfoConfirm) {
		(*trade_callback)(CB_TRADE_RSP_SETTLEMENT_INFO_CONFIRM, true, nullptr);
		log << "Success to Response Settlement Info Confirm";
		LOGDBG(logger, log);
	}
	else {
		(*trade_callback)(CB_TRADE_RSP_SETTLEMENT_INFO_CONFIRM, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Response Settlement Info Confirm");
	}
}


///请求查询投资者持仓响应
void TradeSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pInvestorPosition) {
		PositionField position;
		arch_Strcpy(position.InvestorID, pInvestorPosition->InvestorID, sizeof(position.InvestorID));
		arch_Strcpy(position.InstrumentID, pInvestorPosition->InstrumentID, sizeof(position.InstrumentID));
		position.PositionSide = pInvestorPosition->PosiDirection;
		position.SettlementID = pInvestorPosition->SettlementID;
		position.OpenVolume = pInvestorPosition->OpenVolume;
		position.CloseVolume = pInvestorPosition->CloseVolume;
		position.PositionQty = pInvestorPosition->Position;
		position.OpenCost = pInvestorPosition->OpenCost;
		position.PositionCost = pInvestorPosition->PositionCost;
		position.PositionProfit = pInvestorPosition->PositionProfit;
		position.CloseProfit = pInvestorPosition->CloseProfit;
		position.Fee = pInvestorPosition->Commission;
		position.UseMargin = pInvestorPosition->UseMargin;
		(*trade_callback)(CB_TRADE_RSP_QRY_INVESTOR_POSITION, true, &position);
		log << "Success to Query Investor Position";
		LOGDBG(logger , log);
	}
	else {
		(*trade_callback)(CB_TRADE_RSP_QRY_INVESTOR_POSITION, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Query Investor Position");
	}
}


///请求查询合约响应
void TradeSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pInstrument) {
		InstrumentField instrument;
		arch_Strcpy(instrument.InstrumentID, pInstrument->InstrumentID, sizeof(instrument.InstrumentID));
		arch_Strcpy(instrument.ExchangeID, pInstrument->ExchangeID, sizeof(instrument.ExchangeID));
		arch_Strcpy(instrument.InstrumentName, pInstrument->InstrumentName, sizeof(instrument.InstrumentName));
		arch_Strcpy(instrument.ExchangeInstID, pInstrument->ExchangeInstID, sizeof(instrument.ExchangeInstID));
		instrument.InstLifePhase = pInstrument->InstLifePhase;
		instrument.IsTrading = pInstrument->IsTrading;
		instrument.LongMarginRatio = pInstrument->LongMarginRatio;
		instrument.ShortMarginRatio = pInstrument->ShortMarginRatio;
		instrument.UnderlyingMultiple = pInstrument->UnderlyingMultiple;
		instrument.VolumeMultiple = pInstrument->VolumeMultiple;
		(*trade_callback)(CB_TRADE_RSP_QRY_INSTRUMENT, true, &instrument);
		log << "Success to Query Instrument";
		LOGDBG(logger, log);
	}
	else {
		(*trade_callback)(CB_TRADE_RSP_QRY_INSTRUMENT, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Query Instrument");
	}
}


///报单录入请求响应
void TradeSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pInputOrder) {
		(*trade_callback)(CB_TRADE_RSP_ORDER_INSERT, true, nullptr);
		log << "Success to Insert Order";
		LOGDBG(logger, log);
	}
	else {
		(*trade_callback)(CB_TRADE_RSP_ORDER_INSERT, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Insert Order");
	}
}


///报单操作请求响应
void TradeSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pInputOrderAction) {
		(*trade_callback)(CB_TRADE_RSP_ORDER_ACTION, true, nullptr);
		log << "Success to Response Order Action";
		LOGDBG(logger, log);
	}
	else {
		(*trade_callback)(CB_TRADE_RSP_ORDER_ACTION, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Response Order Action");
	}
}


///报单通知
void TradeSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	std::stringstream log;
	(*trade_callback)(CB_TRADE_RTN_ORDER, true, nullptr);
	log << "Rtn Order";
	LOGTRACE(logger, log);
}


///成交通知
void TradeSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
	std::stringstream log;
	MatchField match;
	match.MatchDateTime = arch_Str2TimeStamp(pTrade->TradeDate, pTrade->TradeTime, 0);
	arch_Strcpy(match.InvestorID, pTrade->InvestorID, sizeof(match.InvestorID));
	arch_Strcpy(match.InstrumentID, pTrade->InstrumentID, sizeof(match.InstrumentID));
	match.MatchPrice = pTrade->Price;
	match.Fee = 0;
	match.MatchQty = pTrade->Volume;
	match.MatchSide = (pTrade->Direction == THOST_FTDC_D_Buy ? ORDER_SIDE_BUY : ORDER_SIDE_SELL);
	match.MatchFlag = (pTrade->OffsetFlag == THOST_FTDC_OF_Open ? ORDER_FLAG_OPEN : ORDER_FLAG_CLOSE);
	(*trade_callback)(CB_TRADE_RTN_TRADE, true, &match);
	log << "Rtn Trade";
	LOGTRACE(logger, log);


}


///报单录入错误回报
void TradeSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pInputOrder) {
		(*trade_callback)(CB_TRADE_ERR_RTN_ORDER_INSERT, true, nullptr);
		log << "Error on Order Insert";
		LOGERR(logger, log);
	}
	else {
		(*trade_callback)(CB_TRADE_ERR_RTN_ORDER_INSERT, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Error on Order Insert");
	}
}


///报单操作错误回报
void TradeSpi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pOrderAction) {
		(*trade_callback)(CB_TRADE_ERR_RTN_ORDER_ACTION, true, nullptr);
		log << "Error on Order Action";
		LOGERR(logger, log);
	}
	else {
		(*trade_callback)(CB_TRADE_ERR_RTN_ORDER_ACTION, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Error on Order Action");
	}
}


///合约交易状态通知
void TradeSpi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{
	std::stringstream log;
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
	if (pRspInfo && pRspInfo->ErrorID == 0 && pTradingAccount) {
		CapitalField capital;
		
		capital.Available = pTradingAccount->Available;
		capital.Balance = pTradingAccount->Balance;
		capital.CashIn = pTradingAccount->CashIn;
		capital.CloseProfit = pTradingAccount->CloseProfit;
		capital.Commission = pTradingAccount->Commission;
		capital.CurrMargin = pTradingAccount->CurrMargin;
		capital.ExchangeMargin = pTradingAccount->ExchangeMargin;
		capital.FrozenCash = pTradingAccount->FrozenCash;
		capital.FrozenCommission = pTradingAccount->FrozenCommission;
		capital.FrozenMargin = pTradingAccount->FrozenMargin;
		capital.PositionProfit = pTradingAccount->PositionProfit;
		capital.Reserve = pTradingAccount->Reserve;
		capital.ReserveBalance = pTradingAccount->ReserveBalance;
		(*trade_callback)(CB_TRADE_RSP_QRY_TRADING_ACCOUNT, true, &capital);
		log << "Success to Query Trading Account";
		LOGINFO(logger, log);
	}
	else {
		(*trade_callback)(CB_TRADE_RSP_QRY_TRADING_ACCOUNT, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Query Trading Account");
	}
}


///请求查询投资者响应
void TradeSpi::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pInvestor) {
		(*trade_callback)(CB_TRADE_RSP_QRY_INVESTOR, true, nullptr);
		log << "Success to Query Investor, " << pInvestor->InvestorID << "," << pInvestor->BrokerID;
		LOGINFO(logger, log);
	}
	else {
		(*trade_callback)(CB_TRADE_RSP_QRY_INVESTOR, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Query Investor");
	}
}
