#ifndef OPTSP_CTPCORE_QUOTESPI_H_
#define OPTSP_CTPCORE_QUOTESPI_H_

#include "ctpapi/ThostFtdcMdApi.h"
#include "ctpapi/ThostFtdcUserApiDataType.h"
#include "ctpapi/ThostFtdcUserApiStruct.h"
#pragma comment (lib, "ctpapi/thostmduserapi.lib")

class QuoteSpi : public CThostFtdcMdSpi
{
private:
	DMT * dmt = nullptr;
	PltSyncField * pltSync = nullptr;
	int cntSubSucceed = 0;
	int cntSubFailed = 0;

	void inline updatePltSync(int);

public:
	///���ع��캯��
	QuoteSpi(DMT *dmt, PltSyncField * pltSync);
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	void OnFrontConnected();
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ���������
	void OnFrontDisconnected(int nReason);
	///��¼������Ӧ
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///�ǳ�������Ӧ
	void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///����Ӧ��
	void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///��������Ӧ��
	void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///ȡ����������Ӧ��
	void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///�������֪ͨ
	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);


	////////////////////////////////
	/********** NOT USED **********/
	////////////////////////////////
public:
	///����ѯ��Ӧ��
	void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///ȡ������ѯ��Ӧ��
	void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///ѯ��֪ͨ
	void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {}
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	void OnHeartBeatWarning(int nTimeLapse) {}
};

#endif // !OPTSP_CTPCORE_QUOTESPI_H_