#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD2(NewLogger, Status(const std::string& fname, Logger** result));

};



class EnvWrapperTest_122 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_env = new MockEnv();

        env_wrapper = new EnvWrapper(mock_env);

    }



    void TearDown() override {

        delete env_wrapper;

        delete mock_env;

    }



    MockEnv* mock_env;

    EnvWrapper* env_wrapper;

};



TEST_F(EnvWrapperTest_122, NewLogger_SuccessfulCreation_122) {

    Logger* logger = nullptr;

    EXPECT_CALL(*mock_env, NewLogger("test.log", _))

        .WillOnce(Return(Status::OK()));



    Status status = env_wrapper->NewLogger("test.log", &logger);

    EXPECT_TRUE(status.ok());

    EXPECT_NE(logger, nullptr);



    // Assuming the logger is created and returned

    delete logger;

}



TEST_F(EnvWrapperTest_122, NewLogger_Failure_122) {

    Logger* logger = nullptr;

    EXPECT_CALL(*mock_env, NewLogger("test.log", _))

        .WillOnce(Return(Status::IOError()));



    Status status = env_wrapper->NewLogger("test.log", &logger);

    EXPECT_TRUE(status.IsIOError());

    EXPECT_EQ(logger, nullptr);

}



TEST_F(EnvWrapperTest_122, NewLogger_NullPointerResult_122) {

    Logger* logger = nullptr;

    EXPECT_CALL(*mock_env, NewLogger(_, _))

        .WillOnce(Return(Status::OK()));



    Status status = env_wrapper->NewLogger("test.log", nullptr);

    EXPECT_TRUE(status.IsInvalidArgument());

}



TEST_F(EnvWrapperTest_122, NewLogger_EmptyFileName_122) {

    Logger* logger = nullptr;

    EXPECT_CALL(*mock_env, NewLogger("", _))

        .WillOnce(Return(Status::IOError()));



    Status status = env_wrapper->NewLogger("", &logger);

    EXPECT_TRUE(status.IsIOError());

}
