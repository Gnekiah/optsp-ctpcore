#ifndef OPTSP_CTPCORE_TRADESTRUCT_HPP_
#define OPTSP_CTPCORE_TRADESTRUCT_HPP_

#include <stdint.h>
#include "datatype.hpp"


#define		POSITION_STATE_NONE				'N'		///无持仓
#define		POSITION_STATE_LONG				'L'		///持有多单
#define		POSITION_STATE_SHORT			'S'		///持有空单
#define		POSITION_STATE_ONOPEN_LONG		'A'		///已下多单等待成交
#define		POSITION_STATE_ONOPEN_SHORT		'B'		///已下空单等待成交
#define		POSITION_STATE_ONCLOSE_LONG		'X'		///已下多单等待平仓
#define		POSITION_STATE_ONCLOSE_SHORT	'Y'		///已下空单等待平仓

#define		TRADING_DIRECT_NONE				'N'		///价格方向无
#define		TRADING_DIRECT_LONG				'L'		///价格涨势
#define		TRADING_DIRECT_SHORT			'S'		///价格跌势

#define		ORDER_SIDE_BUY					'B'		///买入
#define		ORDER_SIDE_SELL					'S'		///卖出

#define		ORDER_FLAG_OPEN					'O'		///开仓
#define		ORDER_FLAG_CLOSE				'C'		///平仓


typedef struct InstrumentField {
	InstrumentIDType	InstrumentID;			///合约代码
	ExchangeIDType		ExchangeID;				///交易所代码
	InstrumentNameType	InstrumentName;			///合约名称
	ExchangeInstIDType	ExchangeInstID;			///合约在交易所的代码
	double				LongMarginRatio;		///多头保证金率
	double				ShortMarginRatio;		///空头保证金率
	double				UnderlyingMultiple;		///合约基础商品乘数
	int					VolumeMultiple;			///合约数量乘数
	char				InstLifePhase;			///合约生命周期状态
	bool				IsTrading;				///当前是否交易
} InstrumentField;


typedef struct OrderField {
	uint64_t			ExpireTime;			///有效时间（时间戳）
	InvestorIDType		InvestorID;			///资金账号
	InstrumentIDType	InstrumentID;		///合约编号
	double				OrderPrice;			///委托价格
	int					OrderQty;			///委托数量
	int					OrderMinQty;		///最小成交量
	char				OrderSide;			///买入 / 卖出
	char				OrderFlag;			///开仓 / 平仓
} OrderField;


typedef struct CapitalField {
	InvestorIDType	InvestorID;			///投资者帐号
	BrokerIDType	BrokerID;			///经纪公司代码
	CurrencyIDType	CurrencyID;			///币种代码
	double			FrozenMargin;		///冻结的保证金
	double			FrozenCash;			///冻结的资金
	double			FrozenCommission;	///冻结的手续费
	double			CurrMargin;			///当前保证金总额
	double			CashIn;				///资金差额
	double			Commission;			///手续费
	double			CloseProfit;		///平仓盈亏
	double			PositionProfit;		///持仓盈亏
	double			Balance;			///期货结算准备金
	double			Available;			///可用资金
	double			Reserve;			///基本准备金
	double			ExchangeMargin;		///交易所保证金
	double			ReserveBalance;		///保底期货结算准备金
} CapitalField;


typedef struct MatchField {
	uint64_t			MatchDateTime;		///成交时间（时间戳）
	InvestorIDType		InvestorID;			///资金账号
	InstrumentIDType	InstrumentID;		///合约编号
	double				MatchPrice;			///成交价
	double				Fee;				///手续费
	int					MatchQty;			///成交量
	char				MatchSide;			///买入 / 卖出
	char				MatchFlag;			///开仓 / 平仓
} MatchField;


typedef struct PositionField {
	InvestorIDType		InvestorID;			///资金账号
	InstrumentIDType	InstrumentID;		///合约编号
	double				OpenCost;			///开仓成本
	double				PositionCost;		///持仓成本
	double				PositionProfit;		///持仓盈亏
	double				CloseProfit;		///平仓盈亏
	double				Fee;				///手续费
	double				UseMargin;			///占用的保证金													
	int					SettlementID;		///结算编号
	int					OpenVolume;			///开仓量
	int					CloseVolume;		///平仓量
	int					PositionQty;		///今日持仓
	char				PositionSide;		///买入 / 卖出
} PositionField;


#endif // !OPTSP_CTPCORE_TRADESTRUCT_HPP_
