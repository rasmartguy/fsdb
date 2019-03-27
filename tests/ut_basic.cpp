#include "gtest/gtest.h"
#include <fsdb.h>

TEST(FsdbInit, ReturnsFalseIfNotInitialized) {
	Fsdb fsdb;
	EXPECT_FALSE(fsdb.initialized());
}

TEST(VoidTestGroup, ReturnsTrueIfInitialized) {
	Fsdb fsdb;
	fsdb.init();
	EXPECT_TRUE(fsdb.initialized());
}
