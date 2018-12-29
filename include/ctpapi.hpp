#ifndef OPTSP_CTPCORE_CTPAPI_HPP_
#define OPTSP_CTPCORE_CTPAPI_HPP_

#if defined(__linux__) && defined( __x86_64__)
#include "../ctpapi/linux64/ThostFtdcMdApi.h"
#include "../ctpapi/linux64/ThostFtdcTraderApi.h"
#include "../ctpapi/linux64/ThostFtdcUserApiStruct.h"
#include "../ctpapi/linux64/ThostFtdcUserApiDataType.h"
#elif defined(_WIN64)
#include "../ctpapi/win64/ThostFtdcMdApi.h"
#include "../ctpapi/win64/ThostFtdcTraderApi.h"
#include "../ctpapi/win64/ThostFtdcUserApiStruct.h"
#include "../ctpapi/win64/ThostFtdcUserApiDataType.h"
#endif


#endif // !OPTSP_CTPCORE_CTPAPI_HPP_
