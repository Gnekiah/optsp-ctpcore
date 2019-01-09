#include "../include/config.h"
#include <iostream>
#include <boost/algorithm/string.hpp>  
#include "../include/arch.h"
#include "../include/magic.hpp"


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
        pt.put<std::string>("Trader.ProductName", "");
        pt.put<std::string>("Trader.AuthCode", "");

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
        arch_Strcpy(this->productName, pt.get<std::string>("Trader.ProductName", "").c_str(), sizeof(this->productName));
        arch_Strcpy(this->authCode, pt.get<std::string>("Trader.AuthCode", "").c_str(), sizeof(this->authCode));

#ifdef _OPTSP_CTPCORE_ON_DEBUG_
        arch_Strcpy(this->password, pt.get<std::string>("Trader.passwd", "").c_str(), sizeof(this->password));
#endif // _OPTSP_CTPCORE_ON_DEBUG_

        if (!boost::filesystem::exists(datapath) || !boost::filesystem::is_directory(datapath))
            boost::filesystem::create_directories(datapath);
    }
    CheckConfig();
}


void Config::SaveConfig()
{
    std::string _config_path = (homepath / CONFIG_FILE).string();
    pt.put<int>("Logger.LogLevel", loglevel);                           ///fixed - 2018/12/23 17:47:00
    pt.put<std::string>("Logger.DataPath", datapath.string());
    pt.put<std::string>("Trader.BrokerID", brokerID);
    pt.put<std::string>("Trader.UserID", userID);
    pt.put<std::string>("Trader.InvestorID", investorID);
    pt.put<std::string>("Trader.QuoteFrontAddr", quoteFrontAddr);
    pt.put<std::string>("Trader.TradeFrontAddr", tradeFrontAddr);
    write_ini(_config_path, pt);
}


bool Config::CheckConfig()
{
    do {
        if (strlen(brokerID) < 3)
            break;
        if (strlen(userID) < 3)
            break;
        if (strlen(investorID) < 3)
            break;
        if (strlen(password) < 3)
            break;
        if (strlen(quoteFrontAddr) < 3)
            break;
        if (strlen(tradeFrontAddr) < 3)
            break;
        return true;
    } while (0);
    return false;
}


void Config::SetDataPath(std::string &s)
{
    SetDataPath(s.c_str());
}


void Config::SetDataPath(const char *s)
{
    lock.lock();
    this->datapath = boost::filesystem::path(s);
    lock.unlock();
}


void Config::SetLogLevel(std::string &s)
{
    SetLogLevel(s.c_str());
}


void Config::SetLogLevel(const char *s)
{
    lock.lock();
    using boost::algorithm::iequals;
    if (iequals(s, "off") || iequals(s, "o"))
        this->loglevel = 0;
    else if (iequals(s, "error") || iequals(s, "err") || iequals(s, "e"))
        this->loglevel = 1;
    else if (iequals(s, "warning") || iequals(s, "warn") || iequals(s, "w"))
        this->loglevel = 2;
    else if (iequals(s, "information") || iequals(s, "infor") || iequals(s, "info") || iequals(s, "inf") || iequals(s, "i"))
        this->loglevel = 3;
    else if (iequals(s, "debug") || iequals(s, "dbg") || iequals(s, "d"))
        this->loglevel = 4;
    else if (iequals(s, "trace") || iequals(s, "track") || iequals(s, "tr") || iequals(s, "t"))
        this->loglevel = 5;
    else
        this->loglevel = 0;
    lock.unlock();
}


void Config::SetLogLevel(int s)
{
    lock.lock();
    this->loglevel = s;
    lock.unlock();
}


void Config::SetProductName(std::string &s)
{
    SetProductName(s.c_str());
}


void Config::SetProductName(const char *s)
{
    lock.lock();
    arch_Strcpy(this->productName, s, sizeof(this->productName));
    lock.unlock();
}


void Config::SetAuthCode(std::string &s)
{
    SetAuthCode(s.c_str());
}


void Config::SetAuthCode(const char *s)
{
    lock.lock();
    arch_Strcpy(this->authCode, s, sizeof(this->authCode));
    lock.unlock();
}


void Config::SetBrokerID(std::string &s)
{
    SetBrokerID(s.c_str());
}


void Config::SetBrokerID(const char *s)
{
    lock.lock();
    arch_Strcpy(this->brokerID, s, sizeof(this->brokerID));
    lock.unlock();
}


void Config::SetUserID(std::string &s)
{
    SetUserID(s.c_str());
}


void Config::SetUserID(const char *s)
{
    lock.lock();
    arch_Strcpy(this->userID, s, sizeof(this->userID));
    lock.unlock();
}


void Config::SetInvestorID(std::string &s)
{
    SetInvestorID(s.c_str());
}


void Config::SetInvestorID(const char *s)
{
    lock.lock();
    arch_Strcpy(this->investorID, s, sizeof(this->investorID));
    lock.unlock();
}


void Config::SetPassword(std::string &s)
{
    SetPassword(s.c_str());
}


void Config::SetPassword(const char *s)
{
    lock.lock();
    arch_Strcpy(this->password, s, sizeof(this->password));
    lock.unlock();
}


void Config::SetQuoteFrontAddr(std::string &s)
{
    SetQuoteFrontAddr(s.c_str());
}


void Config::SetQuoteFrontAddr(const char *s)
{
    lock.lock();
    arch_Strcpy(this->quoteFrontAddr, s, sizeof(this->quoteFrontAddr));
    lock.unlock();
}


void Config::SetTradeFrontAddr(std::string &s)
{
    SetTradeFrontAddr(s.c_str());
}


void Config::SetTradeFrontAddr(const char *s)
{
    lock.lock();
    arch_Strcpy(this->tradeFrontAddr, s, sizeof(this->tradeFrontAddr));
    lock.unlock();
}


boost::filesystem::path Config::GetHomePath()
{
    lock.lock();
    boost::filesystem::path p = this->homepath;
    lock.unlock();
    return p;
}


boost::filesystem::path Config::GetDataPath()
{
    lock.lock();
    boost::filesystem::path p = this->datapath;
    lock.unlock();
    return p;
}


int Config::GetLogLevel()
{
    lock.lock();
    int i = this->loglevel;
    lock.unlock();
    return i;
}


std::string Config::GetProductName()
{
    lock.lock();
    std::string s(this->productName);
    lock.unlock();
    return s;
}


std::string Config::GetAuthCode()
{
    lock.lock();
    std::string s(this->authCode);
    lock.unlock();
    return s;
}


std::string Config::GetBrokerID()
{
    lock.lock();
    std::string s(this->brokerID);
    lock.unlock();
    return s;
}


std::string Config::GetUserID()
{
    lock.lock();
    std::string s(this->userID);
    lock.unlock();
    return s;
}


std::string Config::GetInvestorID()
{
    lock.lock();
    std::string s(this->investorID);
    lock.unlock();
    return s;
}


std::string Config::GetPassword()
{
    lock.lock();
    std::string s(this->password);
    lock.unlock();
    return s;
}


std::string Config::GetQuoteFrontAddr()
{
    lock.lock();
    std::string s(this->quoteFrontAddr);
    lock.unlock();
    return s;
}


std::string Config::GetTradeFrontAddr()
{
    lock.lock();
    std::string s(this->tradeFrontAddr);
    lock.unlock();
    return s;
}


bool Config::GetHomePath(char *s)
{
    lock.lock();
    arch_Strcpy(s, homepath.string().c_str(), sizeof(homepath.string().c_str()));
    lock.unlock();
    return true;
}


bool Config::GetDataPath(char *s)
{
    lock.lock();
    arch_Strcpy(s, datapath.string().c_str(), sizeof(datapath.string().c_str()));
    lock.unlock();
    return true;
}


bool Config::GetProductName(char *s)
{
    lock.lock();
    arch_Strcpy(s, productName, sizeof(productName));
    lock.unlock();
    return true;
}


bool Config::GetAuthCode(char *s)
{
    lock.lock();
    arch_Strcpy(s, authCode, sizeof(authCode));
    lock.unlock();
    return true;
}


bool Config::GetBrokerID(char *s)
{
    lock.lock();
    arch_Strcpy(s, brokerID, sizeof(brokerID));
    lock.unlock();
    return true;
}


bool Config::GetUserID(char *s)
{
    lock.lock();
    arch_Strcpy(s, userID, sizeof(userID));
    lock.unlock();
    return true;
}


bool Config::GetInvestorID(char *s)
{
    lock.lock();
    arch_Strcpy(s, investorID, sizeof(investorID));
    lock.unlock();
    return true;
}


bool Config::GetPassword(char *s)
{
    lock.lock();
    arch_Strcpy(s, password, sizeof(password));
    lock.unlock();
    return true;
}


bool Config::GetQuoteFrontAddr(char *s)
{
    lock.lock();
    arch_Strcpy(s, quoteFrontAddr, sizeof(quoteFrontAddr));
    lock.unlock();
    return true;
}


bool Config::GetTradeFrontAddr(char *s)
{
    lock.lock();
    arch_Strcpy(s, tradeFrontAddr, sizeof(tradeFrontAddr));
    lock.unlock();
    return true;
}