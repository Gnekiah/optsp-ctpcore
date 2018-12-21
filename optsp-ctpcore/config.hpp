#ifndef OPTSP_CTPCORE_CONFIG_HPP_
#define OPTSP_CTPCORE_CONFIG_HPP_

#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "datatype.hpp"

class Config
{
private:
	boost::property_tree::ptree pt;

public:
	const int VERSION = 0;
	const int SUBVERSION = 1;
	const int EXTRAVERSION = 0;
	const char* APP_TITLE = "OPTSP：程序化交易 CTP 仿真测试";
	const char *APP_NAME = "optsp";
	const char *AUTH_CODE = "optsp";
	const char* CONFIG_PATH = "config.ini";

public:
	std::string homepath;							///主目录
	std::string datapath;							///数据目录
	MdCsvFormatType mdCsvFormat;					///数据保存格式
	int loglevel;									///日志过滤等级

public:
	BrokerIDType brokerID;							///经纪公司代码
	UserIDType userID;								///用户账号
	InvestorIDType investorID;						///投资者账号
	PasswordType password;							///口令


public:
	Config()
	{
		std::stringstream log;
	}

};

#endif // !OPTSP_CTPCORE_CONFIG_HPP_
