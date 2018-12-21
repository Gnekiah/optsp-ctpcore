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
	const char* APP_TITLE = "OPTSP�����򻯽��� CTP �������";
	const char *APP_NAME = "optsp";
	const char *AUTH_CODE = "optsp";
	const char* CONFIG_PATH = "config.ini";

public:
	std::string homepath;							///��Ŀ¼
	std::string datapath;							///����Ŀ¼
	MdCsvFormatType mdCsvFormat;					///���ݱ����ʽ
	int loglevel;									///��־���˵ȼ�

public:
	BrokerIDType brokerID;							///���͹�˾����
	UserIDType userID;								///�û��˺�
	InvestorIDType investorID;						///Ͷ�����˺�
	PasswordType password;							///����


public:
	Config()
	{
		std::stringstream log;
	}

};

#endif // !OPTSP_CTPCORE_CONFIG_HPP_
