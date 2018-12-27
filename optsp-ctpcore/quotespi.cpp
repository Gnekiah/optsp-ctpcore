#include "quotespi.h"
#include <sstream>
#include "quotestruct.hpp"
#include "arch.h"

QuoteSpi::QuoteSpi(Logger * logger, quote_callback_fn qfn, plat_callback_fn pfn)
	: logger(logger), quote_callback(qfn), cmd_callback(pfn)
{
	std::stringstream log;
	handicap = new HandicapField;
	log << "QuoteSpi Inited";
	LOGINFO(logger, log);
}


void QuoteSpi::OnFrontConnected()
{
	std::stringstream log;
	(*cmd_callback)(CB_CMD_QUOTE_LOGIN, CMDID_QUOTE, false, nullptr);
	(*quote_callback)(CB_QUOTE_CONNECTED, true, nullptr);
	log << "Connected with Quote Front Server";
	LOGINFO(logger, log);
}


void QuoteSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pRspUserLogin) {
		(*cmd_callback)(CB_CMD_QUOTE_SUBSCRIBE, CMDID_QUOTE, false, nullptr);
		(*quote_callback)(CB_QUOTE_RSP_USER_LOGIN, true, nullptr);
		log << "Login on Quote Front Server, " << pRspUserLogin->TradingDay << ", " << pRspUserLogin->LoginTime;
		LOGINFO(logger, log);
	}
	else {
		(*quote_callback)(CB_QUOTE_RSP_USER_LOGIN, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Login Quote Front Server");
	}
}


void QuoteSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pSpecificInstrument) {
		CbSubMarketDataField data;
		arch_Strcpy(data.InstrumentID, pSpecificInstrument->InstrumentID, sizeof(data.InstrumentID));
		(*quote_callback)(CB_QUOTE_RSP_SUB_MARKET_DATA, true, &data);
		log << "Success to Subscribe: " << pSpecificInstrument->InstrumentID;
		LOGDBG(logger, log);
	}
	else {
		(*quote_callback)(CB_QUOTE_RSP_SUB_MARKET_DATA, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Subscribe Market Data");
	}
}


void QuoteSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	handicap->DateStamp = arch_Str2TimeStamp((char*)pDepthMarketData->TradingDay, (char*)pDepthMarketData->UpdateTime, pDepthMarketData->UpdateMillisec);
	handicap->PreClose = pDepthMarketData->PreClosePrice;
	handicap->PreSettlement = pDepthMarketData->PreSettlementPrice;
	handicap->PrePosition = (uint64_t)pDepthMarketData->PreOpenInterest;
	handicap->CurrOpen = pDepthMarketData->OpenPrice;
	handicap->CurrHighest = pDepthMarketData->HighestPrice;
	handicap->CurrLowest = pDepthMarketData->LowestPrice;
	handicap->CurrClose = pDepthMarketData->ClosePrice;
	handicap->CurrSettlement = pDepthMarketData->SettlementPrice;
	handicap->UpperLimit = pDepthMarketData->UpperLimitPrice;
	handicap->LowerLimit = pDepthMarketData->LowerLimitPrice;
	handicap->PreDelta = pDepthMarketData->PreDelta;
	handicap->CurrDelta = pDepthMarketData->CurrDelta;
	handicap->BidPrice[0] = pDepthMarketData->BidPrice1;
	handicap->BidVolume[0] = pDepthMarketData->BidVolume1;
	handicap->AskPrice[0] = pDepthMarketData->AskPrice1;
	handicap->AskVolume[0] = pDepthMarketData->AskVolume1;
	arch_Strcpy(handicap->Tick.InstrumentID, pDepthMarketData->InstrumentID, sizeof(handicap->Tick.InstrumentID));
	handicap->Tick.Price = pDepthMarketData->LastPrice;
	handicap->Tick.Volume = pDepthMarketData->Volume;
	handicap->Tick.Position = (long)pDepthMarketData->OpenInterest;
	handicap->Tick.Turnover = pDepthMarketData->Turnover;
	handicap->Tick.Average = pDepthMarketData->AveragePrice;
	(*quote_callback)(CB_QUOTE_RTN_DEPTH_MARKET_DATA, true, handicap);
}


void QuoteSpi::OnFrontDisconnected(int nReason)
{
	std::stringstream log;
	(*quote_callback)(CB_QUOTE_DISCONNECTED, true, nullptr);
	log << "nReason=" << nReason;
	LOGERR(logger, log);
}


void QuoteSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	RSPINFO_ERROR(log, pRspInfo, "Error");
}


void QuoteSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pUserLogout) {
		(*quote_callback)(CB_QUOTE_RSP_USER_LOGOUT, true, nullptr);
		log << "Success to Logout";
		LOGINFO(logger, log);
	}
	else {
		(*quote_callback)(CB_QUOTE_RSP_USER_LOGOUT, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Logout");
	}
}


void QuoteSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::stringstream log;
	if (pRspInfo && pRspInfo->ErrorID == 0 && pSpecificInstrument) {
		CbUnsubMarketDataField data;
		arch_Strcpy(data.InstrumentID, pSpecificInstrument->InstrumentID, sizeof(data.InstrumentID));
		(*quote_callback)(CB_QUOTE_RSP_UNSUB_MARKET_DATA, true, &data);
		log << "Success to Unsubscribe: " << pSpecificInstrument->InstrumentID;
		LOGDBG(logger, log);
	}
	else {
		(*quote_callback)(CB_QUOTE_RSP_UNSUB_MARKET_DATA, false, nullptr);
		RSPINFO_ERROR(log, pRspInfo, "Failed to Unsubscribe Market Data");
	}
}
