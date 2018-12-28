#ifndef OPTSP_CTPCORE_CONFIG_H_
#define OPTSP_CTPCORE_CONFIG_H_

#include <sstream>
#include <mutex>
#include <atomic>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>
#include "datatype.hpp"


class Config
{
private:
	boost::property_tree::ptree pt;

public:
	///访问类的public属性时，要加锁
	std::mutex lock;
	std::atomic_bool ready;

public:
	const int VERSION = 0;
	const int SUBVERSION = 1;
	const int EXTRAVERSION = 0;
	const char* APP_TITLE = "OPTSP：程序化交易 CTP 仿真测试";

	const char* HOME_FILE = ".optsp";					///程序主目录
	const char* CONFIG_FILE = "config.ini";				///配置文件
	const char* RUNNING_LOG_FILE = "running.log";		///程序运行日志
	const char* MATCH_LOG_FILE = "match.csv";			///成交信息保存文件
	const char* POSITION_LOG_FILE = "position.csv";		///持仓信息保存文件
	const char* STATE_LOG_FILE = "state.csv";			///状态信息保存文件
	const char* INSTRUMENT_FILE = "instrument.csv";		///合约列表保存文件
	const char* MD_CSV_FORMAT = "md-%s-tick.csv";		///数据保存的文件格式
	
public:
	boost::filesystem::path homepath;				///主目录
	boost::filesystem::path datapath;				///数据目录
	int loglevel;									///日志过滤等级

public:
	ProductNameType productName = { 0 };			///产品名称
	AuthenticateCodeType authCode = { 0 };			///验证编码
	BrokerIDType brokerID = { 0 };					///经纪公司代码
	UserIDType userID = { 0 };						///用户账号
	InvestorIDType investorID = { 0 };				///投资者账号
	PasswordType password = { 0 };					///口令
	FrontAddrType quoteFrontAddr = { 0 };			///行情API前置地址
	FrontAddrType tradeFrontAddr = { 0 };			///交易API前置地址

public:
	Config();
	void SaveConfig();
	bool CheckConfig();
};

#endif // !OPTSP_CTPCORE_CONFIG_H_
