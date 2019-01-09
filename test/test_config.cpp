#include "test_config.h"
#include <iostream>
#include "../include/arch.h"

//#define show(x)    do { std::cerr << x << std::endl; } while(0)
#define show(x)    do { ; } while(0)

bool test_Config() {
    Config *config = new Config();
    show(config->VERSION);
    show(config->SUBVERSION);
    show(config->EXTRAVERSION);
    show(config->GetProductName());
    show(config->APP_TITLE);
    show(config->HOME_FILE);
    show(config->CONFIG_FILE);
    show(config->RUNNING_LOG_FILE);
    show(config->MATCH_LOG_FILE);
    show(config->POSITION_LOG_FILE);
    show(config->STATE_LOG_FILE);
    show(config->INSTRUMENT_FILE);
    show(config->MD_CSV_FORMAT);
    show(config->GetHomePath().string());
    show(config->GetDataPath().string());
    show(config->GetLogLevel());
    show(config->GetBrokerID());
    show(config->GetUserID());
    show(config->GetInvestorID());
    show(config->GetPassword());
    show(config->GetQuoteFrontAddr());
    show(config->GetTradeFrontAddr());
    
    config->SetBrokerID("test-broke");
    config->SetInvestorID("test-inves");
    config->SetUserID("test-user");
    config->SetPassword("test-password");
    config->SetQuoteFrontAddr("test-quotefront-addr");
    config->SetTradeFrontAddr("test-tradefront-addr");
    
    show(config->GetBrokerID());
    show(config->GetUserID());
    show(config->GetInvestorID());
    show(config->GetPassword());
    show(config->GetQuoteFrontAddr());
    show(config->GetTradeFrontAddr());

    //config->SaveConfig();
    return true;
}