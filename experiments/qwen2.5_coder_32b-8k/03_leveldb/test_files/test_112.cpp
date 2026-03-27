#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD1(RemoveFile, Status(const std::string& f));

};



class EnvWrapperTest_112 : public ::testing::Test {

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



TEST_F(EnvWrapperTest_112, RemoveFile_NormalOperation_112) {

    EXPECT_CALL(*mock_env, RemoveFile("testfile.txt")).WillOnce(Return(Status::OK()));

    Status status = env_wrapper->RemoveFile("testfile.txt");

    EXPECT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_112, RemoveFile_FileNotFound_112) {

    EXPECT_CALL(*mock_env, RemoveFile("nonexistentfile.txt"))

        .WillOnce(Return(Status::NotFound("File not found")));

    Status status = env_wrapper->RemoveFile("nonexistentfile.txt");

    EXPECT_EQ(status.code(), Status::kNotFound);

}



TEST_F(EnvWrapperTest_112, RemoveFile_IOError_112) {

    EXPECT_CALL(*mock_env, RemoveFile("ioerrorfile.txt"))

        .WillOnce(Return(Status::IOError("I/O error")));

    Status status = env_wrapper->RemoveFile("ioerrorfile.txt");

    EXPECT_EQ(status.code(), Status::kIOError);

}



TEST_F(EnvWrapperTest_112, RemoveFile_EmptyFileName_112) {

    EXPECT_CALL(*mock_env, RemoveFile(""))

        .WillOnce(Return(Status::InvalidArgument("Invalid argument")));

    Status status = env_wrapper->RemoveFile("");

    EXPECT_EQ(status.code(), Status::kInvalidArgument);

}
