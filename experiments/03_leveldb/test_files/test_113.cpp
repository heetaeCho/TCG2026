#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD1(CreateDir, Status(const std::string& d));

};



class EnvWrapperTest_113 : public ::testing::Test {

protected:

    std::unique_ptr<MockEnv> mock_env_;

    std::unique_ptr<EnvWrapper> env_wrapper_;



    void SetUp() override {

        mock_env_ = std::make_unique<MockEnv>();

        env_wrapper_ = std::make_unique<EnvWrapper>(mock_env_.get());

    }

};



TEST_F(EnvWrapperTest_113, CreateDir_Success_113) {

    EXPECT_CALL(*mock_env_, CreateDir("test_dir"))

        .WillOnce(Return(Status::OK()));



    Status status = env_wrapper_->CreateDir("test_dir");

    EXPECT_TRUE(status.ok()) << "Expected OK status";

}



TEST_F(EnvWrapperTest_113, CreateDir_Failure_113) {

    EXPECT_CALL(*mock_env_, CreateDir("test_dir"))

        .WillOnce(Return(Status::IOError()));



    Status status = env_wrapper_->CreateDir("test_dir");

    EXPECT_TRUE(!status.ok()) << "Expected non-OK status";

}



TEST_F(EnvWrapperTest_113, CreateDir_EmptyString_113) {

    EXPECT_CALL(*mock_env_, CreateDir(""))

        .WillOnce(Return(Status::InvalidArgument()));



    Status status = env_wrapper_->CreateDir("");

    EXPECT_TRUE(!status.ok()) << "Expected non-OK status for empty string";

}



TEST_F(EnvWrapperTest_113, CreateDir_BoundaryLengthString_113) {

    std::string long_name(1024, 'a'); // Assuming a reasonable max path length

    EXPECT_CALL(*mock_env_, CreateDir(long_name))

        .WillOnce(Return(Status::OK()));



    Status status = env_wrapper_->CreateDir(long_name);

    EXPECT_TRUE(status.ok()) << "Expected OK status for boundary length string";

}
