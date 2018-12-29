#ifndef OPTSP_CTPCORE_TRADESPI_H_
#define OPTSP_CTPCORE_TRADESPI_H_

#include "../include/ctpapi.hpp"

#include "../include/platstruct.hpp"
#include "../include/logger.h"
#include "../include/datatype.hpp"

class TradeSpi : public CThostFtdcTraderSpi
{
private:
	Logger * logger = nullptr;
	trade_callback_fn trade_callback = nullptr;
	plat_callback_fn cmd_callback = nullptr;

public:
	TradeSpi(Logger * logger, trade_callback_fn tfn, plat_callback_fn pfn);

	/////////////////////////////////////////
	/********** ͨ����������֤��� **********/
	/////////////////////////////////////////
public:
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	void OnFrontConnected();
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	void OnFrontDisconnected(int nReason);
	///�ͻ�����֤��Ӧ
	void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///��¼������Ӧ
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///�ǳ�������Ӧ
	void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/////////////////////////////////////
	/********** ��������Կ��� **********/
	/////////////////////////////////////
public:
	///�û��������������Ӧ
	void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///�ʽ��˻��������������Ӧ
	void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);


	///��ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ��Ӧ
	void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

	////////////////////////////////
	/********** ������� **********/
	////////////////////////////////
public:
	///Ԥ��¼��������Ӧ
	void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///Ԥ�񳷵�¼��������Ӧ
	void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///ɾ��Ԥ����Ӧ
	void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///ɾ��Ԥ�񳷵���Ӧ
	void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

public:
	///ѯ��¼��������Ӧ
	void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///����¼��������Ӧ
	void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯѯ����Ӧ
	void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///ѯ��֪ͨ
	void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {}

public:
	///ִ������¼��������Ӧ
	void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///ִ���������������Ӧ
	void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///ִ������֪ͨ
	void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder) {}
	///ִ������¼�����ر�
	void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo) {}
	///ִ�������������ر�
	void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo) {}

public:
	///�����ѯͶ���ֲ߳���Ӧ
	void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///�����ѯ��Լ��Ӧ
	void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///�����ѯͶ���߽�������Ӧ
	void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///�����ѯ������Ϣȷ����Ӧ
	void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);


	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ��Լ��֤������Ӧ
	void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ��Լ����������Ӧ
	void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ��������Ӧ
	void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///�����ѯ��Ʒ��Ӧ
	void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///�����ѯ������Ӧ
	void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ�ɽ���Ӧ
	void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ�ͻ�֪ͨ��Ӧ
	void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ������Ӧ
	void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ�ֵ��۵���Ϣ��Ӧ
	void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤����Ӧ
	void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ��������֤������Ӧ
	void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ������������֤������Ӧ
	void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ��Ʒ���ۻ���
	void OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ������������Ӧ
	void OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯִ��������Ӧ
	void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ������Ӧ
	void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

public:
	///����¼��������Ӧ
	void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///��������������Ӧ
	void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///Ͷ���߽�����ȷ����Ӧ
	void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///����֪ͨ
	void OnRtnOrder(CThostFtdcOrderField *pOrder);
	///�ɽ�֪ͨ
	void OnRtnTrade(CThostFtdcTradeField *pTrade);
	///����¼�����ر�
	void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
	///������������ر�
	void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);
	///��Լ����״̬֪ͨ
	void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);
	///����֪ͨ
	void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo);


	///��ѯ��󱨵�������Ӧ
	void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///����������֪ͨ
	void OnRtnBulletin(CThostFtdcBulletinField *pBulletin) {}
	///���۲���������Ӧ
	void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///������������������Ӧ
	void OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///��ʾ������У�����
	void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) {}
	///ѯ��¼�����ر�
	void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo) {}
	///����֪ͨ
	void OnRtnQuote(CThostFtdcQuoteField *pQuote) {}
	///����¼�����ر�
	void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo) {}
	///���۲�������ر�
	void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo) {}
	///����������������ر�
	void OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo) {}

public:
	///�����ѯ����֪ͨ��Ӧ
	void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯԤ����Ӧ
	void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯԤ�񳷵���Ӧ
	void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

	//////////////////////////////////
	/********** �ǽ������ **********/
	//////////////////////////////////
public:
	///�����ѯ�ʽ��˻���Ӧ
	void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///�����ѯͶ������Ӧ
	void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);


	///�����ѯ���ױ�����Ӧ
	void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯǩԼ������Ӧ
	void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯת��������Ӧ
	void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ���͹�˾���ײ�����Ӧ
	void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ���͹�˾�����㷨��Ӧ
	void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ��������û�������Ӧ
	void OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ������Ӧ
	void OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ�����������Ա����Ȩ����Ӧ
	void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯת����ˮ��Ӧ
	void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ����ǩԼ��ϵ��Ӧ
	void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ�ʽ��˻���Ӧ
	void OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ�����������ʽ�У��ģʽ��Ӧ
	void OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ�����̺�Լ����������Ӧ
	void OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ��������Ȩ��Լ��������Ӧ
	void OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///��֤���������û�����
	void OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken) {}

	////////////////////////////////
	/********** ������ **********/
	////////////////////////////////
public:
	///�������֪ͨ
	void OnRtnCombAction(CThostFtdcCombActionField *pCombAction) {}
	///�������¼�����ر�
	void OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo) {}
	///�������¼��������Ӧ
	void OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯͶ�ʵ�Ԫ��Ӧ
	void OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ��Ϻ�Լ��ȫϵ����Ӧ
	void OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ���������Ӧ
	void OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ��Ʒ��
	void OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

	////////////////////////////////
	/********** ��Ȩ��� **********/
	////////////////////////////////
public:
	///��Ȩ�ԶԳ�¼��������Ӧ
	void OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///��Ȩ�ԶԳ����������Ӧ
	void OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ��Ȩ���׳ɱ���Ӧ
	void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ��Ȩ��Լ��������Ӧ
	void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�����ѯ��Ȩ�ԶԳ���Ӧ
	void OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///��Ȩ�ԶԳ�֪ͨ
	void OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose) {}
	///��Ȩ�ԶԳ�¼�����ر�
	void OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo) {}
	///��Ȩ�ԶԳ��������ر�
	void OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo) {}

	/////////////////////////////////////////////
	/********** �������ڻ����������� **********/
	/////////////////////////////////////////////
public:
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	void OnHeartBeatWarning(int nTimeLapse) {}
	///����Ӧ��
	void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

	/* ���з��������֪ͨ */
public:
	///���з��������ʽ�ת�ڻ�֪ͨ
	void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) {}
	///���з����ڻ��ʽ�ת����֪ͨ
	void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) {}
	///���з����������ת�ڻ�֪ͨ
	void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) {}
	///���з�������ڻ�ת����֪ͨ
	void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) {}
	///���з������ڿ���֪ͨ
	void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) {}
	///���з�����������֪ͨ
	void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) {}
	///���з����������˺�֪ͨ
	void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) {}

	/* �ڻ����������֪ͨ */
public:
	///�ڻ������ѯ�������֪ͨ
	void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) {}
	///�ڻ����������ʽ�ת�ڻ�֪ͨ
	void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) {}
	///�ڻ������ڻ��ʽ�ת����֪ͨ
	void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) {}
	///�ڻ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
	void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) {}
	///�ڻ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
	void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) {}

	/* �ڻ����������Ӧ�� */
public:
	///�ڻ����������ʽ�ת�ڻ�Ӧ��
	void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�ڻ������ڻ��ʽ�ת����Ӧ��
	void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}
	///�ڻ������ѯ�������Ӧ��
	void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

	/* �ڻ���������Ĵ���ر� */
public:
	///�ڻ������ѯ����������ر�
	void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo) {}
	///�ڻ����������ʽ�ת�ڻ�����ر�
	void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {}
	///�ڻ������ڻ��ʽ�ת���д���ر�
	void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {}

	/* ϵͳ����ʱ�ڻ����ֹ����������֪ͨ */
public:
	///ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
	void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {}
	///ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
	void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {}

	/* ϵͳ����ʱ�ڻ����ֹ���������Ĵ���ر� */
public:
	///ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ�����ر�
	void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {}
	///ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת���д���ر�
	void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {}
};



#endif // !OPTSP_CTPCORE_TRADESPI_H_
