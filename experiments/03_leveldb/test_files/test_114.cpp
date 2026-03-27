#include <gtest/gtest.h>

#include "leveldb/env.h"

#include <gmock/gmock.h>



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD1(RemoveDir, Status(const std::string& d));

};



class EnvWrapperTest_114 : public ::testing::Test {

protected:

    MockEnv mock_env;

    EnvWrapper env_wrapper{ &mock_env };

};



TEST_F(EnvWrapperTest_114, RemoveDir_Success_114) {

    EXPECT_CALL(mock_env, RemoveDir("test_dir"))

        .WillOnce(Return(Status::OK()));

    

    Status status = env_wrapper.RemoveDir("test_dir");

    EXPECT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_114, RemoveDir_Error_114) {

    EXPECT_CALL(mock_env, RemoveDir("nonexistent_dir"))

        .WillOnce(Return(Status::IOError()));



    Status status = env_wrapper.RemoveDir("nonexistent_dir");

    EXPECT_TRUE(!status.ok());

}



TEST_F(EnvWrapperTest_114, RemoveDir_EmptyString_114) {

    EXPECT_CALL(mock_env, RemoveDir(""))

        .WillOnce(Return(Status::InvalidArgument()));



    Status status = env_wrapper.RemoveDir("");

    EXPECT_TRUE(!status.ok());

}
