#include <gtest/gtest.h>

#include "leveldb/env.h"

#include "gmock/gmock.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD2(NewSequentialFile, Status(const std::string &, SequentialFile **));

    MOCK_METHOD2(NewRandomAccessFile, Status(const std::string &, RandomAccessFile **));

    MOCK_METHOD2(NewWritableFile, Status(const std::string &, WritableFile **));

    MOCK_METHOD2(NewAppendableFile, Status(const std::string &, WritableFile **));

    MOCK_METHOD1(FileExists, bool(const std::string &));

    MOCK_METHOD2(GetChildren, Status(const std::string &, std::vector<std::string> *));

    MOCK_METHOD1(RemoveFile, Status(const std::string &));

    MOCK_METHOD1(CreateDir, Status(const std::string &));

    MOCK_METHOD1(RemoveDir, Status(const std::string &));

    MOCK_METHOD2(GetFileSize, Status(const std::string &, uint64_t *));

    MOCK_METHOD2(RenameFile, Status(const std::string &, const std::string &));

    MOCK_METHOD2(LockFile, Status(const std::string &, FileLock **));

    MOCK_METHOD1(UnlockFile, Status(FileLock *));

    MOCK_METHOD2(Schedule, void(void (*)(void *), void *));

    MOCK_METHOD2(StartThread, void(void (*)(void *), void *));

    MOCK_METHOD1(GetTestDirectory, Status(std::string *));

    MOCK_METHOD2(NewLogger, Status(const std::string &, Logger **));

    MOCK_METHOD0(NowMicros, uint64_t());

    MOCK_METHOD1(SleepForMicroseconds, void(int));

};



class EnvWrapperTest_116 : public ::testing::Test {

protected:

    MockEnv mock_env;

    EnvWrapper env_wrapper{&mock_env};

};



TEST_F(EnvWrapperTest_116, RenameFile_Success_116) {

    EXPECT_CALL(mock_env, RenameFile("source.txt", "target.txt")).WillOnce(Return(Status::OK()));

    Status status = env_wrapper.RenameFile("source.txt", "target.txt");

    EXPECT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_116, RenameFile_SourceDoesNotExist_116) {

    EXPECT_CALL(mock_env, RenameFile("nonexistent_source.txt", "target.txt"))

        .WillOnce(Return(Status::NotFound("Source file not found")));

    Status status = env_wrapper.RenameFile("nonexistent_source.txt", "target.txt");

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(EnvWrapperTest_116, RenameFile_TargetAlreadyExists_116) {

    EXPECT_CALL(mock_env, RenameFile("source.txt", "existing_target.txt"))

        .WillOnce(Return(Status::IOError("Target file already exists")));

    Status status = env_wrapper.RenameFile("source.txt", "existing_target.txt");

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(EnvWrapperTest_116, RenameFile_EmptySourceName_116) {

    EXPECT_CALL(mock_env, RenameFile("", "target.txt"))

        .WillOnce(Return(Status::InvalidArgument("Source file name is empty")));

    Status status = env_wrapper.RenameFile("", "target.txt");

    EXPECT_TRUE(status.IsInvalidArgument());

}



TEST_F(EnvWrapperTest_116, RenameFile_EmptyTargetName_116) {

    EXPECT_CALL(mock_env, RenameFile("source.txt", ""))

        .WillOnce(Return(Status::InvalidArgument("Target file name is empty")));

    Status status = env_wrapper.RenameFile("source.txt", "");

    EXPECT_TRUE(status.IsInvalidArgument());

}
