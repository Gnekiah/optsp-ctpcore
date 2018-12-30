#ifndef OPTSP_CTPCORE_TEST_CALLBACK_H_
#define OPTSP_CTPCORE_TEST_CALLBACK_H_

#include <boost/thread/thread.hpp>
#include <boost/lockfree/queue.hpp>
#include "../include/logger.h"

static void* pfn = nullptr;

typedef struct BuffField {
    char data[1024];
} BuffField;

class TestClass 
{
private:
    int id;
    boost::lockfree::queue<BuffField> *queue = nullptr;

public:
    TestClass(int id);
    void run();
    void callback(int level, const char *ptr);
};


class _Logger2
{
private:
    Logger * logger = nullptr;
    int cnt;
public:
    _Logger2(Logger * logger, int cnt);
    void run();
};

int test_Callback(int cnt);

#endif // !OPTSP_CTPCORE_TEST_CALLBACK_H_

