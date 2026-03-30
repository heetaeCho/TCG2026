#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD(Status, UnlockFile, (FileLock* l), (override));

};



class EnvWrapperTest_118 : public ::testing::Test {

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



TEST_F(EnvWrapperTest_118, UnlockFile_NormalOperation_118) {

    FileLock* file_lock = new FileLock();

    EXPECT_CALL(*mock_env, UnlockFile(file_lock)).WillOnce(Return(Status::OK()));

    Status status = env_wrapper->UnlockFile(file_lock);

    EXPECT_TRUE(status.ok());

    delete file_lock;

}



TEST_F(EnvWrapperTest_118, UnlockFile_ExceptionalCase_118) {

    FileLock* file_lock = new FileLock();

    EXPECT_CALL(*mock_env, UnlockFile(file_lock)).WillOnce(Return(Status::IOError()));

    Status status = env_wrapper->UnlockFile(file_lock);

    EXPECT_FALSE(status.ok());

    delete file_lock;

}



TEST_F(EnvWrapperTest_118, UnlockFile_BoundaryCondition_NullPointer_118) {

    FileLock* file_lock = nullptr;

    EXPECT_CALL(*mock_env, UnlockFile(file_lock)).Times(0);

    Status status = env_wrapper->UnlockFile(file_lock);

    // Assuming the implementation handles null pointer gracefully

    EXPECT_FALSE(status.ok());

}
