#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD(Status, LockFile, (const std::string& f, FileLock** l), (override));

};



class EnvWrapperTest_117 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_env = new MockEnv();

        env_wrapper.reset(new EnvWrapper(mock_env));

    }



    void TearDown() override {

        env_wrapper.reset();

        delete mock_env;

    }



    MockEnv* mock_env;

    std::unique_ptr<EnvWrapper> env_wrapper;

};



TEST_F(EnvWrapperTest_117, LockFile_NormalOperation_117) {

    FileLock* lock = nullptr;

    EXPECT_CALL(*mock_env, LockFile("testfile", _))

        .WillOnce(Return(Status::OK()));



    Status status = env_wrapper->LockFile("testfile", &lock);

    EXPECT_EQ(status.ok(), true);

}



TEST_F(EnvWrapperTest_117, LockFile_BoundaryCondition_EmptyFileName_117) {

    FileLock* lock = nullptr;

    EXPECT_CALL(*mock_env, LockFile("", _))

        .WillOnce(Return(Status::InvalidArgument()));



    Status status = env_wrapper->LockFile("", &lock);

    EXPECT_EQ(status.IsInvalidArgument(), true);

}



TEST_F(EnvWrapperTest_117, LockFile_ExceptionalCase_LockFailure_117) {

    FileLock* lock = nullptr;

    EXPECT_CALL(*mock_env, LockFile("testfile", _))

        .WillOnce(Return(Status::IOError()));



    Status status = env_wrapper->LockFile("testfile", &lock);

    EXPECT_EQ(status.IsIOError(), true);

}



TEST_F(EnvWrapperTest_117, LockFile_VerifyExternalInteraction_117) {

    FileLock* lock = nullptr;

    EXPECT_CALL(*mock_env, LockFile("testfile", _))

        .WillOnce(Return(Status::OK()));



    Status status = env_wrapper->LockFile("testfile", &lock);

    EXPECT_EQ(status.ok(), true);

}
