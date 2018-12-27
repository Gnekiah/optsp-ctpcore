#include "platctp.h"
#include <boost/filesystem.hpp>
#include "arch.h"


PlatCtp::PlatCtp(Config * config, Logger * logger, quote_callback_fn qfn, trade_callback_fn tfn, plat_callback_fn pfn)
	: config(config), logger(logger), quote_callback(qfn), trade_callback(tfn), plat_callback(pfn)
{
	std::stringstream log;
	cmdfn = this;

	quoteState = QUOTE_STATE_NONE;
	tradeState = TRADE_STATE_NONE;
	nInstrumentID = 0;
	cmdQueue = new boost::lockfree::queue<PlatCmdField>(64);

	quoteSpi = new QuoteSpi(logger, quote_callback, CmdCallBack);
	tradeSpi = new TradeSpi(logger, trade_callback, CmdCallBack);
	
	quoteApi = CThostFtdcMdApi::CreateFtdcMdApi(config->homepath.string().c_str());
	quoteApi->RegisterSpi(quoteSpi);
	quoteApi->RegisterFront(config->quoteFrontAddr);

	tradeApi = CThostFtdcTraderApi::CreateFtdcTraderApi(config->homepath.string().c_str());
	tradeApi->RegisterSpi(tradeSpi);
	tradeApi->SubscribePublicTopic(THOST_TERT_RESTART);
	tradeApi->SubscribePrivateTopic(THOST_TERT_RESTART);
	tradeApi->RegisterFront(config->tradeFrontAddr);

	log << "CTP Registered";
	LOGINFO(logger, log);
}


void PlatCtp::InsertCommand(int cmdtype, int cmdid, bool flag, void* ptr)
{
	PlatCmdField cmd = { 0 };
	cmd.Type = cmdtype;
	cmd.Id = cmdid;
	cmd.Flag = flag;
	switch (cmdtype) {
	/* QuoteSpi Callback */
	case CB_CMD_QUOTE_LOGIN:						///QuoteSpi发来的请求登录通知
		quoteState = QUOTE_STATE_CONNECTED;
		break;
	case CB_CMD_QUOTE_SUBSCRIBE:					///QuoteSpi发来的请求订阅通知，订阅操作要等tradeReady之后才进行
		quoteState = QUOTE_STATE_LOGINED;
		break;

	/* TradeSpi Callback */
	case CB_CMD_TRADE_AUTHENTICATE:					///TradeSpi发来的请求验证通知
		tradeState = TRADE_STATE_CONNECTED;
		break;
	case CB_CMD_TRADE_LOGIN:						///TradeSpi发来的请求登录通知
		tradeState = TRADE_STATE_AUTHENED;
		break;
	case CB_CMD_TRADE_SETTLEMENT_CONFIRM:			///TradeSpi发来的请求结算确认通知
		tradeState = TRADE_STATE_LOGINED;
		break;
	case CB_CMD_TRADE_QRY_INSTRUMENT:				///TradeSpi发来的请求查询合约通知
		tradeState = TRADE_STATE_SETTLEMENT_CONFIRMED;
		break;
	case CB_CMD_TRADE_RSP_QRY_INSTRUMENT:			///TradeSpi发来的合约编号数据，只用于控制quoteApi执行订阅
		arch_Memcpy(instrumentIDs[nInstrumentID], ptr, sizeof(InstrumentField));
		nInstrumentID++;
		return;
	case CB_CMD_TRADE_QRY_INSTRUMENT_COMPLETED:		///TradeSpi发来的合约列表获取完毕的通知，获取该通知后，直接修改tradeReady，不插入命令队列
		tradeState = TRADE_STATE_INSTRUMENT_QUERIED;
		return;

	/* STGroup Command */

	default:
		return;
	}
	cmdQueue->push(cmd);
}


void PlatCtp::run()
{
	int ret = 0;
	std::stringstream log;
	PlatCmdField cmd = { 0 };

	while (!config->ready)
		arch_Sleep(100);

	quoteApi->Init();
	tradeApi->Init();

	log << config->brokerID << ";" << config->userID << ";" << config->investorID << ";" << config->password << ";" << config->quoteFrontAddr << ";" << config->tradeFrontAddr;
	LOGINFO(logger, log);

	log << "Looping...";
	LOGINFO(logger, log);

	while (true) {
		while (cmdQueue->empty())
			arch_Sleep(10);
		cmdQueue->pop(cmd);

		switch (cmd.Type) {
		/* QuoteSpi Command */
		case CB_CMD_QUOTE_LOGIN:
			ret = DoQuoteLogin(cmd);
			break;
		case CB_CMD_QUOTE_SUBSCRIBE:
			ret = DoQuoteSubscribe(cmd);
			break;
		/* TradeSpi Command */
		case CB_CMD_TRADE_AUTHENTICATE:
			ret = DoTradeAuthenticate(cmd);
			break;
		case CB_CMD_TRADE_LOGIN:
			ret = DoTradeLogin(cmd);
			break;
		case CB_CMD_TRADE_SETTLEMENT_CONFIRM:
			ret = DoTradeSettlementConfirm(cmd);
			break;
		case CB_CMD_TRADE_QRY_INSTRUMENT:
			ret = DoTradeQryInstrument(cmd);
			break;
		/* StGroup Command */

		default:
			ret = 0;
			break;
		}
		
		if (cmd.Id != CMDID_QUOTE && cmd.Id != CMDID_TRADE) {
			(*plat_callback)(cmd.Type, cmd.Id, (ret == 0 ? true : false), nullptr);
		}
		arch_Sleep(500);
	}
	
	quoteApi->Join();
	tradeApi->Join();
	delete quoteSpi;
	delete tradeSpi;
	quoteApi->Release();
	tradeApi->Release();
}



int PlatCtp::DoQuoteLogin(PlatCmdField &cmd)
{
	int ret = 0;
	std::stringstream log;

	CThostFtdcReqUserLoginField req = { 0 };
	arch_Strcpy(req.UserID, config->userID, sizeof(req.UserID));
	arch_Strcpy(req.BrokerID, config->brokerID, sizeof(req.BrokerID));
	arch_Strcpy(req.Password, config->password, sizeof(req.Password));
	ret = quoteApi->ReqUserLogin(&req, cmd.Id);
	if (ret) {
		log << "Failed to login quote front server, nRequest=" << cmd.Id;
		LOGERR(logger, log);
	}
	return ret;
}


int PlatCtp::DoQuoteSubscribe(PlatCmdField &cmd)
{
	int ret = 0;
	std::stringstream log;

	if (tradeState < TRADE_STATE_INSTRUMENT_QUERIED) {
		InsertCommand(CB_CMD_QUOTE_SUBSCRIBE, CMDID_QUOTE, false, nullptr);
		return -1;
	}
	ret = quoteApi->SubscribeMarketData(instrumentIDs, nInstrumentID);
	if (ret) {
		log << "Failed to subscribe market data, nRequest=" << cmd.Id;
		LOGERR(logger, log);
	}
	return ret;
}


int PlatCtp::DoTradeAuthenticate(PlatCmdField &cmd)
{
	int ret = 0;
	std::stringstream log;
	
	CThostFtdcReqAuthenticateField req = { 0 };
	arch_Strcpy(req.AuthCode, config->AUTH_CODE, sizeof(req.AuthCode));
	arch_Strcpy(req.UserProductInfo, config->APP_NAME, sizeof(req.UserProductInfo));
	arch_Strcpy(req.BrokerID, config->brokerID, sizeof(req.BrokerID));
	arch_Strcpy(req.UserID, config->userID, sizeof(req.UserID));
	ret = tradeApi->ReqAuthenticate(&req, cmd.Id);
	if (ret) {
		log << "Failed to do trade authenticate, nRequestID=" << cmd.Id;
		LOGERR(logger, log);
	}
	return ret;
}


int PlatCtp::DoTradeLogin(PlatCmdField &cmd)
{
	int ret = 0;
	std::stringstream log;

	CThostFtdcReqUserLoginField req = { 0 };
	arch_Strcpy(req.UserID, config->userID, sizeof(req.UserID));
	arch_Strcpy(req.BrokerID, config->brokerID, sizeof(req.BrokerID));
	arch_Strcpy(req.Password, config->password, sizeof(req.Password));
	ret = tradeApi->ReqUserLogin(&req, cmd.Id);
	if (ret) {
		log << "Failed to login trade front server, nRequestID=" << cmd.Id;
		LOGERR(logger, log);
	}
	return ret;
}


int PlatCtp::DoTradeSettlementConfirm(PlatCmdField &cmd)
{
	int ret = 0;
	std::stringstream log;

	CThostFtdcQrySettlementInfoConfirmField req1 = { 0 };
	arch_Strcpy(req1.BrokerID, config->brokerID, sizeof(req1.BrokerID));
	arch_Strcpy(req1.InvestorID, config->investorID, sizeof(req1.InvestorID));
	ret = tradeApi->ReqQrySettlementInfoConfirm(&req1, cmd.Id);
	if (ret) {
		log << "Failed to query settlement info confirm";
		LOGERR(logger, log);
	}
	arch_Sleep(500);
	CThostFtdcQrySettlementInfoField req2 = { 0 };
	arch_Strcpy(req2.BrokerID, config->brokerID, sizeof(req2.BrokerID));
	arch_Strcpy(req2.InvestorID, config->investorID, sizeof(req2.InvestorID));
	ret = tradeApi->ReqQrySettlementInfo(&req2, cmd.Id);
	if (ret) {
		log << "Failed to query settlement info";
		LOGERR(logger, log);
	}
	arch_Sleep(500);
	CThostFtdcSettlementInfoConfirmField req3 = { 0 };
	arch_Strcpy(req3.BrokerID, config->brokerID, sizeof(req3.BrokerID));
	arch_Strcpy(req3.InvestorID, config->investorID, sizeof(req3.InvestorID));
	ret = tradeApi->ReqSettlementInfoConfirm(&req3, cmd.Id);
	if (ret) {
		log << "Failed to do settlement info confirm";
		LOGERR(logger, log);
	}
	return ret;
}


int PlatCtp::DoTradeQryInstrument(PlatCmdField &cmd)
{
	int ret = 0;
	std::stringstream log;

	CThostFtdcQryInstrumentField req = { 0 };
	ret = tradeApi->ReqQryInstrument(&req, cmd.Id);
	if (ret) {
		log << "Failed to query instrument";
		LOGWARN(logger, log);
	}
	return ret;
}




///for callback
void CmdCallBack(int cmdtype, int cmdid, bool flag, void* ptr)
{
	PlatCtp *plat = (PlatCtp*)cmdfn;
	plat->InsertCommand(cmdtype, cmdid, flag, ptr);
}