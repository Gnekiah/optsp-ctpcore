#ifndef OPTSP_CTPCORE_INDEXSTRUCT_HPP_
#define OPTSP_CTPCORE_INDEXSTRUCT_HPP_

#include <stdint.h>
#include "datatype.hpp"


typedef struct TickField {
	uint64_t			TimeStamp;			///ʱ���, "yyyy-MM-dd hh:mm:ss.zzz"
	double				Price;				///ʱ����Ƭ�����¼۸�
	uint64_t			Volume;				///�ɽ���
	double				Turnover;			///�ɽ���
	uint64_t			Position;			///�ֲ���
	double				Average;			///���վ���
	InstrumentIDType	InstrumentID;		///��Լ���룬p.s. �ֽ�δ����
} TickField;


typedef struct HandicapField {
	uint64_t	DateStamp;			///������, ���ڴ���"yyyy-MM-dd 00:00:00.000"
	double		PreClose;			///������
	double		PreSettlement;		///�����
	uint64_t	PrePosition;		///��ֲ�
	double		CurrOpen;			///����
	double		CurrHighest;		///��߼�
	double		CurrLowest;			///��ͼ�
	double		CurrClose;			///������
	double		CurrSettlement;		///�����
	double		UpperLimit;			///��ͣ��
	double		LowerLimit;			///��ͣ��
	double		PreDelta;			///����ʵ��
	double		CurrDelta;			///����ʵ��
	double		BidPrice[5];		///�����1-5
	uint64_t	BidVolume[5];		///������1-5
	double		AskPrice[5];		///������1-5
	uint64_t	AskVolume[5];		///������1-5
	TickField	Tick;				///���µ�Tick����
} HandicapField;


typedef struct KLineField {
	uint64_t	TimeStamp;			///ʱ���, "yyyy-MM-dd hh:mm:ss.zzz"
	uint64_t	TicksCnt;			///������ticks����
	double		Open;				///��
	double		High;				///��
	double		Low;				///��
	double		Close;				///��
} KLineField;


typedef struct MAField {
	double		MA[MAFIELD_MACNT_MAX];	///���5������ָ��
	uint8_t		MACnt;					///��ǵ�ǰ�ж��ٸ�����ָ������Ч�ģ�p.s. �ֽ�δ����
} MAField;


typedef struct MACDField {
	double		Ema1;				///EMA1, e.g. 12
	double		Ema2;				///EMA2, e.g. 26
	double		Dea;				///DEA
	double		Diff;				///DIF
	double		Macd;				///MACD
} MACDField;


#endif // !OPTSP_CTPCORE_INDEXSTRUCT_HPP_

