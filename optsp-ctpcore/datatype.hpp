#ifndef OPTSP_CTPCORE_DATATYPE_HPP_
#define OPTSP_CTPCORE_DATATYPE_HPP_

#include "ctpapi/ThostFtdcUserApiDataType.h"



typedef char MdCsvFormatType[128];									///行情CSV保存格式类型
typedef TThostFtdcBrokerIDType BrokerIDType;						///经纪公司代码类型
typedef TThostFtdcUserIDType UserIDType;							///用户代码类型
typedef TThostFtdcInvestorIDType InvestorIDType;					///投资者代码类型
typedef TThostFtdcInstrumentIDType InstrumentIDType;				///合约代码类型
typedef TThostFtdcPasswordType PasswordType;						///口令类型
typedef char FrontAddrType[64];										///前置地址类型

#endif // !OPTSP_CTPCORE_DATATYPE_HPP_

