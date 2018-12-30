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
    show(config->APP_NAME);
    show(config->APP_TITLE);
    show(config->HOME_FILE);
    show(config->CONFIG_FILE);
    show(config->RUNNING_LOG_FILE);
    show(config->MATCH_LOG_FILE);
    show(config->POSITION_LOG_FILE);
    show(config->STATE_LOG_FILE);
    show(config->INSTRUMENT_FILE);
    show(config->MD_CSV_FORMAT);
    show(config->homepath.string());
    show(config->datapath.string());
    show(config->loglevel);
    show(config->brokerID);
    show(config->userID);
    show(config->investorID);
    show(config->password);
    show(config->quoteFrontAddr);
    show(config->tradeFrontAddr);
    
    arch_Strcpy(config->brokerID, "test-broke", sizeof(config->brokerID));
    arch_Strcpy(config->investorID, "test-inves", sizeof(config->investorID));
    arch_Strcpy(config->userID, "test-user", sizeof(config->userID));
    arch_Strcpy(config->password, "test-password", sizeof(config->password));
    arch_Strcpy(config->quoteFrontAddr, "test-quotefront-addr", sizeof(config->quoteFrontAddr));
    arch_Strcpy(config->tradeFrontAddr, "test-tradefront-addr", sizeof(config->tradeFrontAddr));
    
    show(config->brokerID);
    show(config->userID);
    show(config->investorID);
    show(config->password);
    show(config->quoteFrontAddr);
    show(config->tradeFrontAddr);

    //config->SaveConfig();
    return true;
}