#ifndef OPTSP_CTPCORE_QUOTESPI_H_
#define OPTSP_CTPCORE_QUOTESPI_H_

#include "ctpapi/ThostFtdcMdApi.h"
#include "ctpapi/ThostFtdcUserApiDataType.h"
#include "ctpapi/ThostFtdcUserApiStruct.h"
#pragma comment (lib, "ctpapi/thostmduserapi.lib")

#include "platstruct.hpp"
#include "logger.h"
#include "datatype.hpp"

class QuoteSpi : public CThostFtdcMdSpi
{
private:
	Logger * logger = nullptr;
	QuoteSyncField * quoteSync = nullptr;
	quote_callback_fn * quote_callback = nullptr;
	HandicapField * handicap = nullptr;

public:
	///重载构造函数
	QuoteSpi(Logger * logger, QuoteSyncField * quoteSync, quote_callback_fn* fn);
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	void OnFrontConnected();
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	void OnFrontDisconnected(int nReason);
	///登录请求响应
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///登出请求响应
	void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///错误应答
	void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///订阅行情应答
	void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///取消订阅行情应答
	void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///深度行情通知
	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);


	////////////////////////////////
	/********** NOT USED **********/
	////////////////////////////////
public:
	///订阅询价应答
	void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///取消订阅询价应答
	void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///询价通知
	void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {}
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	void OnHeartBeatWarning(int nTimeLapse) {}
};

#endif // !OPTSP_CTPCORE_QUOTESPI_H_
