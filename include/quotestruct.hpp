#ifndef OPTSP_CTPCORE_QUOTESTRUCT_HPP_
#define OPTSP_CTPCORE_QUOTESTRUCT_HPP_

#include "indexstruct.hpp"
#include "datatype.hpp"


typedef struct CbSubMarketDataField {
	InstrumentIDType InstrumentID;
} CbSubMarketDataField;


typedef struct CbUnsubMarketDataField {
	InstrumentIDType InstrumentID;
} CbUnsubMarketDataField;


#endif // !OPTSP_CTPCORE_QUOTESTRUCT_HPP_
