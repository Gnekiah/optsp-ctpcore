#ifndef OPTSP_CTPCORE_INDEXSTRUCT_HPP_
#define OPTSP_CTPCORE_INDEXSTRUCT_HPP_

#include <stdint.h>
#include "datatype.hpp"


typedef struct TickField {
    uint64_t            TimeStamp;            ///时间戳, "yyyy-MM-dd hh:mm:ss.zzz"
    double                Price;                ///时间切片的最新价格
    uint64_t            Volume;                ///成交量
    double                Turnover;            ///成交额
    uint64_t            Position;            ///持仓量
    double                Average;            ///当日均价
    InstrumentIDType    InstrumentID;        ///合约编码，p.s. 字节未对齐
} TickField;


typedef struct HandicapField {
    uint64_t    DateStamp;            ///交易日, 日期戳："yyyy-MM-dd 00:00:00.000"
    double        PreClose;            ///昨收盘
    double        PreSettlement;        ///昨结算
    uint64_t    PrePosition;        ///昨持仓
    double        CurrOpen;            ///今开盘
    double        CurrHighest;        ///最高价
    double        CurrLowest;            ///最低价
    double        CurrClose;            ///今收盘
    double        CurrSettlement;        ///今结算
    double        UpperLimit;            ///涨停板
    double        LowerLimit;            ///跌停板
    double        PreDelta;            ///昨虚实度
    double        CurrDelta;            ///今虚实度
    double        BidPrice[5];        ///申买价1-5
    uint64_t    BidVolume[5];        ///申买量1-5
    double        AskPrice[5];        ///申卖价1-5
    uint64_t    AskVolume[5];        ///申卖量1-5
    TickField    Tick;                ///最新的Tick数据
} HandicapField;


typedef struct KLineField {
    uint64_t    TimeStamp;            ///时间戳, "yyyy-MM-dd hh:mm:ss.zzz"
    uint64_t    TicksCnt;            ///包含的ticks数量
    double        Open;                ///开
    double        High;                ///高
    double        Low;                ///低
    double        Close;                ///收
} KLineField;


typedef struct MAField {
    double        MA[MAFIELD_MACNT_MAX];    ///最多5个均线指标
    uint8_t        MACnt;                    ///标记当前有多少个均线指标是有效的，p.s. 字节未对齐
} MAField;


typedef struct MACDField {
    double        Ema1;                ///EMA1, e.g. 12
    double        Ema2;                ///EMA2, e.g. 26
    double        Dea;                ///DEA
    double        Diff;                ///DIF
    double        Macd;                ///MACD
} MACDField;


#endif // !OPTSP_CTPCORE_INDEXSTRUCT_HPP_

