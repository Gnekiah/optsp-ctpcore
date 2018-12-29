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
	///�������public����ʱ��Ҫ����
	std::mutex lock;
	std::atomic_bool ready;

public:
	const int VERSION = 0;
	const int SUBVERSION = 1;
	const int EXTRAVERSION = 0;
	const char* APP_TITLE = "OPTSP�����򻯽��� CTP �������";

	const char* HOME_FILE = ".optsp";					///������Ŀ¼
	const char* CONFIG_FILE = "config.ini";				///�����ļ�
	const char* RUNNING_LOG_FILE = "running.log";		///����������־
	const char* MATCH_LOG_FILE = "match.csv";			///�ɽ���Ϣ�����ļ�
	const char* POSITION_LOG_FILE = "position.csv";		///�ֲ���Ϣ�����ļ�
	const char* STATE_LOG_FILE = "state.csv";			///״̬��Ϣ�����ļ�
	const char* INSTRUMENT_FILE = "instrument.csv";		///��Լ�б����ļ�
	const char* MD_CSV_FORMAT = "md-%s-tick.csv";		///���ݱ�����ļ���ʽ
	
public:
	boost::filesystem::path homepath;				///��Ŀ¼
	boost::filesystem::path datapath;				///����Ŀ¼
	int loglevel;									///��־���˵ȼ�

public:
	ProductNameType productName = { 0 };			///��Ʒ����
	AuthenticateCodeType authCode = { 0 };			///��֤����
	BrokerIDType brokerID = { 0 };					///���͹�˾����
	UserIDType userID = { 0 };						///�û��˺�
	InvestorIDType investorID = { 0 };				///Ͷ�����˺�
	PasswordType password = { 0 };					///����
	FrontAddrType quoteFrontAddr = { 0 };			///����APIǰ�õ�ַ
	FrontAddrType tradeFrontAddr = { 0 };			///����APIǰ�õ�ַ

public:
	Config();
	void SaveConfig();
	bool CheckConfig();
};

#endif // !OPTSP_CTPCORE_CONFIG_H_
