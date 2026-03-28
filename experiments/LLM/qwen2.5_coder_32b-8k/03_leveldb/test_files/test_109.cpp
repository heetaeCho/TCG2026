#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::Return;

using ::testing::_;



class MockEnv : public Env {

public:

    MOCK_METHOD(Status, NewAppendableFile, (const std::string &fname, WritableFile **result), (override));

};



class EnvWrapperTest_109 : public ::testing::Test {

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



TEST_F(EnvWrapperTest_109, NewAppendableFile_SuccessfulCreation_109) {

    auto mock_writable_file = new WritableFile();

    EXPECT_CALL(*mock_env, NewAppendableFile("testfile", _))

        .WillOnce(Return(Status::OK()));

    WritableFile* result;

    Status status = env_wrapper->NewAppendableFile("testfile", &result);

    EXPECT_EQ(status.ok(), true);

}



TEST_F(EnvWrapperTest_109, NewAppendableFile_FailureCreation_109) {

    EXPECT_CALL(*mock_env, NewAppendableFile("nonexistentfile", _))

        .WillOnce(Return(Status::IOError()));

    WritableFile* result;

    Status status = env_wrapper->NewAppendableFile("nonexistentfile", &result);

    EXPECT_EQ(status.ok(), false);

}



TEST_F(EnvWrapperTest_109, NewAppendableFile_NullWritableFilePointer_109) {

    EXPECT_CALL(*mock_env, NewAppendableFile("testfile", _))

        .WillOnce(Return(Status::OK()));

    WritableFile* result = nullptr;

    Status status = env_wrapper->NewAppendableFile("testfile", &result);

    EXPECT_EQ(status.ok(), true);

}



TEST_F(EnvWrapperTest_109, NewAppendableFile_EmptyFileName_109) {

    EXPECT_CALL(*mock_env, NewAppendableFile("", _))

        .WillOnce(Return(Status::InvalidArgument()));

    WritableFile* result;

    Status status = env_wrapper->NewAppendableFile("", &result);

    EXPECT_EQ(status.ok(), false);

}
