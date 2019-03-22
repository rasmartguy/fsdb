#include "gtest/gtest.h"
#include <fsdb.h>

TEST(VoidTestGroup, VoidTest) {
	Fsdb fsdb;
	EXPECT_FALSE(fsdb.initialized());
}
