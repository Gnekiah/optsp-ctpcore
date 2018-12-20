#ifndef OPTSP_CTPCORE_CONFIG_H_
#define OPTSP_CTPCORE_CONFIG_H_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

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
	Config();

};

#endif // !OPTSP_CTPCORE_CONFIG_H_
