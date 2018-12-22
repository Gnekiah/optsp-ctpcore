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


///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
void TradeSpi::OnFrontConnected()
{
	std::stringstream log;
	tradeSync->TradeState = PLTSYNC_TRADE_CONNECTED;
	tradeSync->TradeActive = true;
	(*trade_callback)(CB_TRADE_CONNECTED, true, nullptr);
	log << "Connected with Trade Front Server";
	LOGINFO(logger, log);
}


///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
void TradeSpi::OnFrontDisconnected(int nReason)
{
	std::stringstream log;
	(*trade_callback)(CB_TRADE_DISCONNECTED, true, nullptr);
	log << "nReason=" << nReason;
	LOGERR(logger, log);
}


///�ͻ�����֤��Ӧ
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


///��¼������Ӧ
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


///�ǳ�������Ӧ
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


///�û��������������Ӧ
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


///�ʽ��˻��������������Ӧ
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


///�����ѯͶ���߽�������Ӧ
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


///�����ѯ������Ϣȷ����Ӧ
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



///Ͷ���߽�����ȷ����Ӧ
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


///�����ѯͶ���ֲ߳���Ӧ
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


///�����ѯ��Լ��Ӧ
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


///����¼��������Ӧ
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


///��������������Ӧ
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


///����֪ͨ
void TradeSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	std::stringstream log;
	(*trade_callback)(CB_TRADE_RTN_ORDER, true, nullptr);
	log << "Rtn Order";
	LOGTRACE(logger, log);
}


///�ɽ�֪ͨ
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


///����¼�����ر�
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


///������������ر�
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


///��Լ����״̬֪ͨ
void TradeSpi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{
	std::stringstream log;
	log << pInstrumentStatus->EnterReason << "," << pInstrumentStatus->EnterTime << ","
		<< pInstrumentStatus->ExchangeID << "," << pInstrumentStatus->ExchangeInstID << ","
		<< pInstrumentStatus->InstrumentID << "," << pInstrumentStatus->InstrumentStatus << ","
		<< pInstrumentStatus->SettlementGroupID << "," << pInstrumentStatus->TradingSegmentSN;
	LOGTRACE(logger, log);
}


///����֪ͨ
void TradeSpi::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo)
{
	std::stringstream log;
	log << pTradingNoticeInfo->BrokerID << "," << pTradingNoticeInfo->FieldContent << ","
		<< pTradingNoticeInfo->InvestorID << "," << pTradingNoticeInfo->InvestUnitID << ","
		<< pTradingNoticeInfo->SendTime << "," << pTradingNoticeInfo->SequenceNo << ","
		<< pTradingNoticeInfo->SequenceSeries;
	LOGINFO(logger, log);
}


///�����ѯ�ʽ��˻���Ӧ
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


///�����ѯͶ������Ӧ
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
