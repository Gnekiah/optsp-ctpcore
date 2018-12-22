#include "test_log.h"
#include "test_arch.h"
#include "test_config.h"
#include <gtest/gtest.h>


TEST(test_arch, test_arch_case_1) {
	ASSERT_TRUE(test_arch_GetHomePath());
	ASSERT_TRUE(test_arch_Sleep());
	ASSERT_TRUE(test_arch_GetTimeStamp());
	ASSERT_TRUE(test_arch_Str2TimeStamp());
	ASSERT_TRUE(test_arch_TimeStamp2Str());
}

TEST(test_log, test_log_case_1) {
	ASSERT_TRUE(test_Log());
}

TEST(test_config, test_config_case_1) {
	ASSERT_TRUE(test_Config());
}

int main(int argc, char**argv) {
	testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	getchar();
	return ret;
}