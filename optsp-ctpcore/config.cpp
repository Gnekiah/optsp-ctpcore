#include "config.h"
#include <iostream>
#include "arch.h"


Config::Config()
{
	char _home[64];
	arch_GetHomePath(_home);
	homepath = boost::filesystem::path(_home)/HOME_FILE;
	std::string _config_path = (homepath / CONFIG_FILE).string();

	if (!boost::filesystem::exists(homepath) || !boost::filesystem::is_directory(homepath))
		boost::filesystem::create_directories(homepath);

	std::ifstream fin(_config_path);
	if (!fin)
	{
		pt.put<std::string>("Logger.LogLevel", "4");
		pt.put<std::string>("Logger.DataPath", "./data/");
		pt.put<std::string>("Trader.BrokerID", "");
		pt.put<std::string>("Trader.UserID", "");
		pt.put<std::string>("Trader.InvestorID", "");
		pt.put<std::string>("Trader.QuoteFrontAddr", "");
		pt.put<std::string>("Trader.TradeFrontAddr", "");
		write_ini(_config_path, pt);
	}
	else {
		boost::property_tree::ini_parser::read_ini(_config_path, pt);
		this->loglevel = pt.get<int>("Logger.LogLevel", 4);
		this->datapath = boost::filesystem::path(pt.get<std::string>("Logger.DataPath", "./data/"));
		arch_Strcpy(this->brokerID, pt.get<std::string>("Trader.BrokerID", "").c_str(), sizeof(this->brokerID));
		arch_Strcpy(this->userID, pt.get<std::string>("Trader.UserID", "").c_str(), sizeof(this->userID));
		arch_Strcpy(this->investorID, pt.get<std::string>("Trader.InvestorID", "").c_str(), sizeof(this->investorID));
		arch_Strcpy(this->quoteFrontAddr, pt.get<std::string>("Trader.QuoteFrontAddr", "").c_str(), sizeof(this->quoteFrontAddr));
		arch_Strcpy(this->tradeFrontAddr, pt.get<std::string>("Trader.TradeFrontAddr", "").c_str(), sizeof(this->tradeFrontAddr));

		if (!boost::filesystem::exists(datapath) || !boost::filesystem::is_directory(datapath))
			boost::filesystem::create_directories(datapath);
	}
}