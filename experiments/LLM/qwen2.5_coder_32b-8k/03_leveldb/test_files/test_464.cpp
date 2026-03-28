#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "leveldb/env.h"

#include "leveldb/status.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class EnvTest : public ::testing::Test {

protected:

    Env* env_;



    void SetUp() override {

        env_ = Env::Default();

    }



    void TearDown() override {

        // No specific cleanup needed for the default environment

    }

};



TEST_F(EnvTest_464, DeleteDir_NormalOperation_464) {

    std::string dirname = "test_dir";

    EXPECT_CALL(*env_, RemoveDir(dirname)).WillOnce(Return(Status::OK()));

    Status status = env_->DeleteDir(dirname);

    EXPECT_TRUE(status.ok());

}



TEST_F(EnvTest_464, DeleteDir_DirectoryDoesNotExist_464) {

    std::string dirname = "nonexistent_dir";

    EXPECT_CALL(*env_, RemoveDir(dirname)).WillOnce(Return(Status::NotFound()));

    Status status = env_->DeleteDir(dirname);

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(EnvTest_464, DeleteDir_PermissionDenied_464) {

    std::string dirname = "protected_dir";

    EXPECT_CALL(*env_, RemoveDir(dirname)).WillOnce(Return(Status::PermissionDenied()));

    Status status = env_->DeleteDir(dirname);

    EXPECT_TRUE(status.IsPermissionDenied());

}



TEST_F(EnvTest_464, DeleteDir_IOError_464) {

    std::string dirname = "io_error_dir";

    EXPECT_CALL(*env_, RemoveDir(dirname)).WillOnce(Return(Status::IOError()));

    Status status = env_->DeleteDir(dirname);

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(EnvTest_464, DeleteDir_EmptyDirectoryName_464) {

    std::string dirname = "";

    EXPECT_CALL(*env_, RemoveDir(dirname)).WillOnce(Return(Status::InvalidArgument()));

    Status status = env_->DeleteDir(dirname);

    EXPECT_TRUE(status.IsInvalidArgument());

}
