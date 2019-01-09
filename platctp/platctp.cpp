#include "../include/platctp.h"
#include <boost/filesystem.hpp>
#include "../include/arch.h"
#include "../include/magic.hpp"


PlatCtp::PlatCtp(Config * config, Logger * logger, plat_callback_fn pfn)
    : config(config), logger(logger), plat_callback(pfn)
{
    std::stringstream log;
    cbfn = this;

    quoteState = QUOTE_STATE_NONE;
    tradeState = TRADE_STATE_NONE;
    nInstrumentID = 0;
    cmdQueue = new boost::lockfree::queue<PlatCmdField>(64);

    quoteSpi = new QuoteSpi(logger, CtpspiCallBack);
    tradeSpi = new TradeSpi(logger, CtpspiCallBack);
    
    quoteApi = CThostFtdcMdApi::CreateFtdcMdApi(config->GetHomePath().string().c_str());
    quoteApi->RegisterSpi(quoteSpi);
    FrontAddrType quoteAddr = { 0 };
    arch_Strcpy(quoteAddr, config->GetQuoteFrontAddr().c_str(), sizeof(quoteAddr));
    quoteApi->RegisterFront(quoteAddr);

    tradeApi = CThostFtdcTraderApi::CreateFtdcTraderApi(config->GetHomePath().string().c_str());
    tradeApi->RegisterSpi(tradeSpi);
    tradeApi->SubscribePublicTopic(THOST_TERT_RESTART);
    tradeApi->SubscribePrivateTopic(THOST_TERT_RESTART);
    FrontAddrType tradeAddr = { 0 };
    arch_Strcpy(tradeAddr, config->GetTradeFrontAddr().c_str(), sizeof(tradeAddr));
    tradeApi->RegisterFront(tradeAddr);

    log << "CTP Registered";
    LOGINFO(logger, log);
}


void PlatCtp::InsertCommand(int cmdtype, int cmdid, void* ptr)
{
    PlatCmdField cmd = { 0 };
    cmd.Type = cmdtype;
    cmd.Id = cmdid;
    switch (cmdtype) {
    /* STGroup Command */
    case 1:
        break;
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

    while (!config->CheckConfig())
        arch_Sleep(100);

    quoteApi->Init();
    tradeApi->Init();

    log << "Looping...";
    LOGINFO(logger, log);

    while (true) {
        while (cmdQueue->empty())
            arch_Sleep(10);
        cmdQueue->pop(cmd);

        switch (cmd.Type) {
        /* QuoteSpi Command */
        case CMD_PLAT_QUOTE_REQ_USER_LOGIN:
            ret = quoteApi->ReqUserLogin(&cmd.ReqUserLogin, cmd.Id);
            APIRTN_ERROR(log, cmd.Id, ret, "Failed to login quote front server");
            break;
        case CMD_PLAT_QUOTE_SUBSCRIBE_MARKET_DATA:
            if (!bInstrumentIDReady) {
                cmdQueue->push(cmd);
                ret = 0;
                break;
            }
            ret = quoteApi->SubscribeMarketData(instrumentIDs, nInstrumentID);
            APIRTN_ERROR(log, cmd.Id, ret, "Failed to subscribe market data");
            break;

        /* TradeSpi Command */
        case CMD_PLAT_TRADE_REQ_AUTHENTICATE:
            ret = tradeApi->ReqAuthenticate(&cmd.ReqAuthenticate, cmd.Id);
            APIRTN_ERROR(log, cmd.Id, ret, "Failed to do trade authenticate");
            break;
        case CMD_PLAT_TRADE_REQ_USER_LOGIN:
            ret = tradeApi->ReqUserLogin(&cmd.ReqUserLogin, cmd.Id);
            APIRTN_ERROR(log, cmd.Id, ret, "Failed to login trade front server");
            break;
        case CMD_PLAT_TRADE_REQ_QRY_SETTLEMENT_INFO_CONFIRM:
            ret = tradeApi->ReqQrySettlementInfoConfirm(&cmd.QrySettlementInfoConfirm, cmd.Id);
            APIRTN_ERROR(log, cmd.Id, ret, "Failed to query settlement info confirm");
            break;
        case CMD_PLAT_TRADE_REQ_QRY_SETTLEMENT_INFO:
            ret = tradeApi->ReqQrySettlementInfo(&cmd.QrySettlementInfo, cmd.Id);
            APIRTN_ERROR(log, cmd.Id, ret, "Failed to query settlement info");
            break;
        case CMD_PLAT_TRADE_REQ_SETTLEMENT_INFO_CONFIRM:
            ret = tradeApi->ReqSettlementInfoConfirm(&cmd.SettlementInfoConfirm, cmd.Id);
            APIRTN_ERROR(log, cmd.Id, ret, "Failed to do settlement info confirm");
            break;
        case CMD_PLAT_TRADE_REQ_QRY_EXCHANGE:
            ret = tradeApi->ReqQryExchange(&cmd.QryExchange, cmd.Id);
            APIRTN_ERROR(log, cmd.Id, ret, "Failed to do query exchange");
            break;
        case CMD_PLAT_TRADE_REQ_QRY_PRODUCT:
            ret = tradeApi->ReqQryProduct(&cmd.QryProduct, cmd.Id);
            APIRTN_ERROR(log, cmd.Id, ret, "Failed to do query product");
            break;
        case CMD_PLAT_TRADE_REQ_QRY_INSTRUMENT:
            ret = tradeApi->ReqQryInstrument(&cmd.QryInstrument, cmd.Id);
            APIRTN_ERROR(log, cmd.Id, ret, "Failed to do query instrument");
            break;

        /* StGroup Command */

        default:
            ret = 0;
            break;
        }
        
        if (cmd.Id != CMDID_QUOTE && cmd.Id != CMDID_TRADE) {
            cmd.Ret = ret;
            (*plat_callback)(cmd.Type, &cmd);
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


void PlatCtp::DispatchSpi(int cbtype, void* ptr)
{
    switch (cbtype) {
    case CB_QUOTE_FRONT_CONNECTED: {
        PlatCmdField cmd = { 0 };
        cmd.Id = CMDID_QUOTE;
        cmd.Type = CMD_PLAT_QUOTE_REQ_USER_LOGIN;
        CThostFtdcReqUserLoginField *data = &cmd.ReqUserLogin;
        arch_Strcpy(data->BrokerID, config->GetBrokerID().c_str(), sizeof(data->BrokerID));
        arch_Strcpy(data->UserID, config->GetUserID().c_str(), sizeof(data->UserID));
        arch_Strcpy(data->Password, config->GetPassword().c_str(), sizeof(data->Password));
        cmdQueue->push(cmd);
        break;
    }
    case CB_QUOTE_RSP_USER_LOGIN: {
        PlatCmdField cmd = { 0 };
        cmd.Id = CMDID_QUOTE;
        cmd.Type = CMD_PLAT_QUOTE_SUBSCRIBE_MARKET_DATA;
        cmdQueue->push(cmd);
        break;
    }
    case CB_TRADE_FRONT_CONNECTED: {
        PlatCmdField cmd = { 0 };
        cmd.Id = CMDID_TRADE;
#ifdef _OPTSP_CTPCORE_WITHOUT_AUTHENTICATE_
        cmd.Type = CMD_PLAT_TRADE_REQ_USER_LOGIN;
        CThostFtdcReqUserLoginField *data = &cmd.ReqUserLogin;
        arch_Strcpy(data->BrokerID, config->GetBrokerID().c_str(), sizeof(data->BrokerID));
        arch_Strcpy(data->UserID, config->GetUserID().c_str(), sizeof(data->UserID));
        arch_Strcpy(data->Password, config->GetPassword().c_str(), sizeof(data->Password));
#else
        cmd.Type = CMD_PLAT_TRADE_REQ_AUTHENTICATE;
        CThostFtdcReqAuthenticateField *data = &cmd.Authenticate;
        arch_Strcpy(data->AuthCode, config->GetAuthCode().c_str(), sizeof(data->AuthCode));
        arch_Strcpy(data->UserProductInfo, config->GetProductName().c_str(), sizeof(data->UserProductInfo));
        arch_Strcpy(data->BrokerID, config->GetBrokerID().c_str(), sizeof(data->BrokerID));
        arch_Strcpy(data->UserID, config->GetUserID().c_str(), sizeof(data->UserID));
#endif
        cmdQueue->push(cmd);
        break;
    }
    case CB_TRADE_RSP_AUTHENTICATE: {
        PlatCmdField cmd = { 0 };
        cmd.Id = CMDID_TRADE;
        cmd.Type = CMD_PLAT_TRADE_REQ_USER_LOGIN;
        CThostFtdcReqUserLoginField *data = &cmd.ReqUserLogin;
        arch_Strcpy(data->BrokerID, config->GetBrokerID().c_str(), sizeof(data->BrokerID));
        arch_Strcpy(data->UserID, config->GetUserID().c_str(), sizeof(data->UserID));
        arch_Strcpy(data->Password, config->GetPassword().c_str(), sizeof(data->Password));
        cmdQueue->push(cmd);
        break;
    }
    case CB_TRADE_RSP_USER_LOGIN: {
        PlatCmdField cmd = { 0 };
        cmd.Id = CMDID_TRADE;
        cmd.Type = CMD_PLAT_TRADE_REQ_QRY_SETTLEMENT_INFO_CONFIRM;
        CThostFtdcQrySettlementInfoConfirmField *data1 = &cmd.QrySettlementInfoConfirm;
        arch_Strcpy(data1->BrokerID, config->GetBrokerID().c_str(), sizeof(data1->BrokerID));
        arch_Strcpy(data1->InvestorID, config->GetInvestorID().c_str(), sizeof(data1->InvestorID));
        cmdQueue->push(cmd);

        memset(&cmd, 0, sizeof(cmd));
        cmd.Id = CMDID_TRADE;
        cmd.Type = CMD_PLAT_TRADE_REQ_QRY_SETTLEMENT_INFO;
        CThostFtdcQrySettlementInfoField *data2 = &cmd.QrySettlementInfo;
        arch_Strcpy(data2->BrokerID, config->GetBrokerID().c_str(), sizeof(data2->BrokerID));
        arch_Strcpy(data2->InvestorID, config->GetInvestorID().c_str(), sizeof(data2->InvestorID));
        cmdQueue->push(cmd);

        memset(&cmd, 0, sizeof(cmd));
        cmd.Id = CMDID_TRADE;
        cmd.Type = CMD_PLAT_TRADE_REQ_SETTLEMENT_INFO_CONFIRM;
        CThostFtdcSettlementInfoConfirmField *data3 = &cmd.SettlementInfoConfirm;
        arch_Strcpy(data3->BrokerID, config->GetBrokerID().c_str(), sizeof(data3->BrokerID));
        arch_Strcpy(data3->InvestorID, config->GetInvestorID().c_str(), sizeof(data3->InvestorID));
        cmdQueue->push(cmd);
        break;
    }
    case CB_TRADE_RSP_SETTLEMENT_INFO_CONFIRM: {
        PlatCmdField cmd = { 0 };
        cmd.Id = CMDID_TRADE;
        cmd.Type = CMD_PLAT_TRADE_REQ_QRY_INSTRUMENT;
        CThostFtdcQryInstrumentField *data = &cmd.QryInstrument;
        cmdQueue->push(cmd);
        break;
    }
    case CB_TRADE_RSP_QRY_INSTRUMENT: {
        CbTradeField *cb = (CbTradeField *)ptr;
        CbTradeRspQryInstrumentField *inst = &cb->RspQryInstrument;
        instrumentIDs[nInstrumentID] = new InstrumentIDType;
        arch_Strcpy(instrumentIDs[nInstrumentID], inst->InstrumentID, sizeof(InstrumentIDType));
        nInstrumentID++;
        if (cb->IsLast)
            bInstrumentIDReady = true;
        break;
    }
    default:
        break;
    }
    (*plat_callback)(cbtype, ptr);
}


///for callback
void CtpspiCallBack(int cbtype, void* ptr) {
    PlatCtp *plat = (PlatCtp*)cbfn;
    plat->DispatchSpi(cbtype, ptr);
}

