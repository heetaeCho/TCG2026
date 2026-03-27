#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD(Status, NewWritableFile, (const std::string&, WritableFile**), (override));

};



class EnvWrapperTest_108 : public ::testing::Test {

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



TEST_F(EnvWrapperTest_108, NewWritableFile_SuccessfulCreation_108) {

    std::string file_name = "test_file";

    WritableFile* writable_file = nullptr;

    EXPECT_CALL(*mock_env, NewWritableFile(file_name, _))

        .WillOnce(Return(Status::OK()));



    Status status = env_wrapper->NewWritableFile(file_name, &writable_file);

    EXPECT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_108, NewWritableFile_FileExistsError_108) {

    std::string file_name = "test_file";

    WritableFile* writable_file = nullptr;

    EXPECT_CALL(*mock_env, NewWritableFile(file_name, _))

        .WillOnce(Return(Status::IOError()));



    Status status = env_wrapper->NewWritableFile(file_name, &writable_file);

    EXPECT_TRUE(!status.ok());

}



TEST_F(EnvWrapperTest_108, NewWritableFile_NullFileName_108) {

    std::string file_name = "";

    WritableFile* writable_file = nullptr;

    EXPECT_CALL(*mock_env, NewWritableFile(file_name, _))

        .WillOnce(Return(Status::InvalidArgument()));



    Status status = env_wrapper->NewWritableFile(file_name, &writable_file);

    EXPECT_TRUE(!status.ok());

}



TEST_F(EnvWrapperTest_108, NewWritableFile_NullWritableFilePointer_108) {

    std::string file_name = "test_file";

    WritableFile* writable_file = nullptr;

    EXPECT_CALL(*mock_env, NewWritableFile(file_name, _))

        .WillOnce(Return(Status::InvalidArgument()));



    Status status = env_wrapper->NewWritableFile(file_name, nullptr);

    EXPECT_TRUE(!status.ok());

}
