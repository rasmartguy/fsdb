#include "gmock/gmock.h"
#include <filesystem>
#include <fsdb/fsdb.hpp>

TEST(FsdbInit, ReturnsFalseIfNotInitialized) {
	Fsdb fsdb;
	bool result = fsdb.initialized();
	EXPECT_FALSE(result);
}

TEST(FsdbInit, ReturnsTrueIfInitialized) {
	Fsdb fsdb;
	fsdb.init();
	bool result = fsdb.initialized();
	EXPECT_TRUE(result);
}

TEST(FsdbInit, InitReturnsSameAsInitialized) {
	Fsdb fsdb;
	bool result = fsdb.init();
	bool expected = fsdb.initialized();
	EXPECT_EQ(result, expected);
}

class MockFsdb : public Fsdb {
public:
    MOCK_METHOD0(init, void());
    MOCK_METHOD0(deinit, void());
};

TEST(FsdbInit, InitShouldBeCalled) {
    auto fsdb = std::make_shared<MockFsdb>();
    EXPECT_CALL(*fsdb, init())
        .WillOnce(::testing::Invoke([&fsdb]() {
            fsdb->Fsdb::init();
        }));
    fsdb->init();
}

TEST(FsdbInit, InitSetsDefaultName) {
    Fsdb fsdb;
    fsdb.init();
    EXPECT_STREQ(fsdb.get_name().c_str(), "default");
}

TEST(FsdbInit, InitDbCreatesDirectory) {
    Fsdb fsdb;
    auto db_name = fsdb.get_name();
    if (std::filesystem::exists(db_name)) {
        std::filesystem::remove(db_name); //< preparing for test
    }
    EXPECT_FALSE(std::filesystem::exists(db_name));
    fsdb.init();
    EXPECT_TRUE(std::filesystem::exists(db_name));
}
