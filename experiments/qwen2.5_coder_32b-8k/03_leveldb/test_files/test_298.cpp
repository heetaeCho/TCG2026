#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/db_impl.cc"

#include "leveldb/status.h"

#include "leveldb/options.h"

#include "db/dbformat.h"

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD(Status, CreateDir, (const std::string& dirname), (override));

    MOCK_METHOD(Status, RenameFile, (const std::string& src, const std::string& target), (override));

    MOCK_METHOD(Status, NewLogger, (const std::string& fname, Logger** result), (override));

};



class SanitizeOptionsTest_298 : public ::testing::Test {

protected:

    Options default_options;

    MockEnv mock_env;



    InternalKeyComparator icmp = InternalKeyComparator(BytewiseComparator());

    InternalFilterPolicy ipolicy = InternalFilterPolicy(nullptr);



    void SetUp() override {

        default_options.env = &mock_env;

    }

};



TEST_F(SanitizeOptionsTest_298, ComparatorSetCorrectly_298) {

    Options result = SanitizeOptions("testdb", &icmp, &ipolicy, default_options);

    EXPECT_EQ(result.comparator, &icmp);

}



TEST_F(SanitizeOptionsTest_298, FilterPolicySetCorrectlyWhenSourceIsNull_298) {

    default_options.filter_policy = nullptr;

    Options result = SanitizeOptions("testdb", &icmp, &ipolicy, default_options);

    EXPECT_EQ(result.filter_policy, static_cast<const FilterPolicy*>(nullptr));

}



TEST_F(SanitizeOptionsTest_298, FilterPolicySetCorrectlyWhenSourceIsNotNull_298) {

    const FilterPolicy* mock_filter_policy = new MockFilterPolicy();

    default_options.filter_policy = mock_filter_policy;

    Options result = SanitizeOptions("testdb", &icmp, &ipolicy, default_options);

    EXPECT_EQ(result.filter_policy, static_cast<const FilterPolicy*>(mock_filter_policy));

}



TEST_F(SanitizeOptionsTest_298, MaxOpenFilesClippedCorrectlyLowerBound_298) {

    default_options.max_open_files = 63;

    Options result = SanitizeOptions("testdb", &icmp, &ipolicy, default_options);

    EXPECT_EQ(result.max_open_files, kNumNonTableCacheFiles + 64);

}



TEST_F(SanitizeOptionsTest_298, MaxOpenFilesClippedCorrectlyUpperBound_298) {

    default_options.max_open_files = 50001;

    Options result = SanitizeOptions("testdb", &icmp, &ipolicy, default_options);

    EXPECT_EQ(result.max_open_files, 50000);

}



TEST_F(SanitizeOptionsTest_298, WriteBufferSizeClippedCorrectlyLowerBound_298) {

    default_options.write_buffer_size = (64 << 10) - 1;

    Options result = SanitizeOptions("testdb", &icmp, &ipolicy, default_options);

    EXPECT_EQ(result.write_buffer_size, (64 << 10));

}



TEST_F(SanitizeOptionsTest_298, WriteBufferSizeClippedCorrectlyUpperBound_298) {

    default_options.write_buffer_size = (1 << 30) + 1;

    Options result = SanitizeOptions("testdb", &icmp, &ipolicy, default_options);

    EXPECT_EQ(result.write_buffer_size, (1 << 30));

}



TEST_F(SanitizeOptionsTest_298, MaxFileSizeClippedCorrectlyLowerBound_298) {

    default_options.max_file_size = (1 << 20) - 1;

    Options result = SanitizeOptions("testdb", &icmp, &ipolicy, default_options);

    EXPECT_EQ(result.max_file_size, (1 << 20));

}



TEST_F(SanitizeOptionsTest_298, MaxFileSizeClippedCorrectlyUpperBound_298) {

    default_options.max_file_size = (1 << 30) + 1;

    Options result = SanitizeOptions("testdb", &icmp, &ipolicy, default_options);

    EXPECT_EQ(result.max_file_size, (1 << 30));

}



TEST_F(SanitizeOptionsTest_298, BlockSizeClippedCorrectlyLowerBound_298) {

    default_options.block_size = (1 << 10) - 1;

    Options result = SanitizeOptions("testdb", &icmp, &ipolicy, default_options);

    EXPECT_EQ(result.block_size, (1 << 10));

}



TEST_F(SanitizeOptionsTest_298, BlockSizeClippedCorrectlyUpperBound_298) {

    default_options.block_size = (4 << 20) + 1;

    Options result = SanitizeOptions("testdb", &icmp, &ipolicy, default_options);

    EXPECT_EQ(result.block_size, (4 << 20));

}



TEST_F(SanitizeOptionsTest_298, InfoLogCreatedSuccessfully_298) {

    Logger* mock_logger = new MockLogger();

    Status status = Status::OK();

    EXPECT_CALL(mock_env, CreateDir("testdb")).WillOnce(Return(status));

    EXPECT_CALL(mock_env, RenameFile(InfoLogFileName("testdb"), OldInfoLogFileName("testdb"))).WillOnce(Return(status));

    EXPECT_CALL(mock_env, NewLogger(InfoLogFileName("testdb"), testing::_)).WillOnce(testing::DoAll(testing::SetArgReferee<1>(mock_logger), Return(status)));



    Options result = SanitizeOptions("testdb", &icmp, &ipolicy, default_options);

    EXPECT_NE(result.info_log, nullptr);



    delete mock_logger;

}



TEST_F(SanitizeOptionsTest_298, InfoLogNotCreatedWhenNewLoggerFails_298) {

    Status status = Status::IOError("Failed to create logger");

    EXPECT_CALL(mock_env, CreateDir("testdb")).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, RenameFile(InfoLogFileName("testdb"), OldInfoLogFileName("testdb"))).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, NewLogger(InfoLogFileName("testdb"), testing::_)).WillOnce(testing::DoAll(testing::SetArgReferee<1>(nullptr), Return(status)));



    Options result = SanitizeOptions("testdb", &icmp, &ipolicy, default_options);

    EXPECT_EQ(result.info_log, nullptr);

}



TEST_F(SanitizeOptionsTest_298, BlockCacheCreatedWhenNull_298) {

    default_options.block_cache = nullptr;

    Options result = SanitizeOptions("testdb", &icmp, &ipolicy, default_options);

    EXPECT_NE(result.block_cache, nullptr);



    delete result.block_cache;

}



TEST_F(SanitizeOptionsTest_298, BlockCacheNotCreatedWhenNotNull_298) {

    Cache* mock_block_cache = new MockLRUCache(1 << 20);

    default_options.block_cache = mock_block_cache;



    Options result = SanitizeOptions("testdb", &icmp, &ipolicy, default_options);

    EXPECT_EQ(result.block_cache, mock_block_cache);



    delete mock_block_cache;

}
