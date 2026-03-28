#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD(Status, GetFileSize, (const std::string& f, uint64_t* s), (override));

};



class EnvWrapperTest_115 : public ::testing::Test {

protected:

    MockEnv mock_env;

    EnvWrapper env_wrapper{&mock_env};

};



TEST_F(EnvWrapperTest_115, GetFileSize_NormalOperation_115) {

    uint64_t size = 0;

    EXPECT_CALL(mock_env, GetFileSize("test_file", &size)).WillOnce(Return(Status::OK()));

    Status status = env_wrapper.GetFileSize("test_file", &size);

    EXPECT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_115, GetFileSize_FileNotFound_115) {

    uint64_t size = 0;

    EXPECT_CALL(mock_env, GetFileSize("nonexistent_file", &size)).WillOnce(Return(Status::IOError()));

    Status status = env_wrapper.GetFileSize("nonexistent_file", &size);

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(EnvWrapperTest_115, GetFileSize_SizeUpdatedOnSuccess_115) {

    uint64_t size = 0;

    EXPECT_CALL(mock_env, GetFileSize("test_file", _)).WillOnce(DoAll(SetArgReferee<1>(1234), Return(Status::OK())));

    Status status = env_wrapper.GetFileSize("test_file", &size);

    EXPECT_TRUE(status.ok());

    EXPECT_EQ(size, 1234);

}



TEST_F(EnvWrapperTest_115, GetFileSize_SizeUnchangedOnFailure_115) {

    uint64_t size = 0;

    EXPECT_CALL(mock_env, GetFileSize("nonexistent_file", _)).WillOnce(Return(Status::IOError()));

    Status status = env_wrapper.GetFileSize("nonexistent_file", &size);

    EXPECT_TRUE(status.IsIOError());

    EXPECT_EQ(size, 0);

}



TEST_F(EnvWrapperTest_115, GetFileSize_NullPointerFileName_115) {

    uint64_t size = 0;

    Status status = env_wrapper.GetFileSize("", &size);

    // Assuming that an empty filename is treated as invalid input and returns a non-OK status

    EXPECT_FALSE(status.ok());

}



TEST_F(EnvWrapperTest_115, GetFileSize_NullPointerSize_115) {

    EXPECT_CALL(mock_env, GetFileSize("test_file", nullptr)).WillOnce(Return(Status::InvalidArgument()));

    Status status = env_wrapper.GetFileSize("test_file", nullptr);

    EXPECT_TRUE(status.IsInvalidArgument());

}
