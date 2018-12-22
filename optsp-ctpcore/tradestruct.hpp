#ifndef OPTSP_CTPCORE_TRADESTRUCT_HPP_
#define OPTSP_CTPCORE_TRADESTRUCT_HPP_

#include <stdint.h>
#include "datatype.hpp"


#define		POSITION_STATE_NONE				'N'		///�޳ֲ�
#define		POSITION_STATE_LONG				'L'		///���ж൥
#define		POSITION_STATE_SHORT			'S'		///���пյ�
#define		POSITION_STATE_ONOPEN_LONG		'A'		///���¶൥�ȴ��ɽ�
#define		POSITION_STATE_ONOPEN_SHORT		'B'		///���¿յ��ȴ��ɽ�
#define		POSITION_STATE_ONCLOSE_LONG		'X'		///���¶൥�ȴ�ƽ��
#define		POSITION_STATE_ONCLOSE_SHORT	'Y'		///���¿յ��ȴ�ƽ��

#define		TRADING_DIRECT_NONE				'N'		///�۸�����
#define		TRADING_DIRECT_LONG				'L'		///�۸�����
#define		TRADING_DIRECT_SHORT			'S'		///�۸����

#define		ORDER_SIDE_BUY					'B'		///����
#define		ORDER_SIDE_SELL					'S'		///����

#define		ORDER_FLAG_OPEN					'O'		///����
#define		ORDER_FLAG_CLOSE				'C'		///ƽ��


typedef struct InstrumentField {
	InstrumentIDType	InstrumentID;			///��Լ����
	ExchangeIDType		ExchangeID;				///����������
	InstrumentNameType	InstrumentName;			///��Լ����
	ExchangeInstIDType	ExchangeInstID;			///��Լ�ڽ������Ĵ���
	double				LongMarginRatio;		///��ͷ��֤����
	double				ShortMarginRatio;		///��ͷ��֤����
	double				UnderlyingMultiple;		///��Լ������Ʒ����
	int					VolumeMultiple;			///��Լ��������
	char				InstLifePhase;			///��Լ��������״̬
	bool				IsTrading;				///��ǰ�Ƿ���
} InstrumentField;


typedef struct OrderField {
	uint64_t			ExpireTime;			///��Чʱ�䣨ʱ�����
	InvestorIDType		InvestorID;			///�ʽ��˺�
	InstrumentIDType	InstrumentID;		///��Լ���
	double				OrderPrice;			///ί�м۸�
	int					OrderQty;			///ί������
	int					OrderMinQty;		///��С�ɽ���
	char				OrderSide;			///���� / ����
	char				OrderFlag;			///���� / ƽ��
} OrderField;


typedef struct CapitalField {
	InvestorIDType	InvestorID;			///Ͷ�����ʺ�
	BrokerIDType	BrokerID;			///���͹�˾����
	CurrencyIDType	CurrencyID;			///���ִ���
	double			FrozenMargin;		///����ı�֤��
	double			FrozenCash;			///������ʽ�
	double			FrozenCommission;	///�����������
	double			CurrMargin;			///��ǰ��֤���ܶ�
	double			CashIn;				///�ʽ���
	double			Commission;			///������
	double			CloseProfit;		///ƽ��ӯ��
	double			PositionProfit;		///�ֲ�ӯ��
	double			Balance;			///�ڻ�����׼����
	double			Available;			///�����ʽ�
	double			Reserve;			///����׼����
	double			ExchangeMargin;		///��������֤��
	double			ReserveBalance;		///�����ڻ�����׼����
} CapitalField;


typedef struct MatchField {
	uint64_t			MatchDateTime;		///�ɽ�ʱ�䣨ʱ�����
	InvestorIDType		InvestorID;			///�ʽ��˺�
	InstrumentIDType	InstrumentID;		///��Լ���
	double				MatchPrice;			///�ɽ���
	double				Fee;				///������
	int					MatchQty;			///�ɽ���
	char				MatchSide;			///���� / ����
	char				MatchFlag;			///���� / ƽ��
} MatchField;


typedef struct PositionField {
	InvestorIDType		InvestorID;			///�ʽ��˺�
	InstrumentIDType	InstrumentID;		///��Լ���
	double				OpenCost;			///���ֳɱ�
	double				PositionCost;		///�ֲֳɱ�
	double				PositionProfit;		///�ֲ�ӯ��
	double				CloseProfit;		///ƽ��ӯ��
	double				Fee;				///������
	double				UseMargin;			///ռ�õı�֤��													
	int					SettlementID;		///������
	int					OpenVolume;			///������
	int					CloseVolume;		///ƽ����
	int					PositionQty;		///���ճֲ�
	char				PositionSide;		///���� / ����
} PositionField;


#endif // !OPTSP_CTPCORE_TRADESTRUCT_HPP_
