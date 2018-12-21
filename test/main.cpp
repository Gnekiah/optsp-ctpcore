#include "const.hpp"
#include "log.hpp"
#include "arch.hpp"
#include <gtest/gtest.h>


TEST(test_arch, test_arch_case_1) {
	ASSERT_TRUE(test_arch_GetHomePath());
	ASSERT_TRUE(test_arch_Sleep());
	ASSERT_TRUE(test_arch_GetTimeStamp());
}

int main(int argc, char**argv) {
	testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	getchar();
	return ret;
}