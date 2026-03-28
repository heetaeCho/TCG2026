#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD2(NewSequentialFile, Status(const std::string&, SequentialFile**));

    MOCK_METHOD2(NewRandomAccessFile, Status(const std::string&, RandomAccessFile**));

    MOCK_METHOD2(NewWritableFile, Status(const std::string&, WritableFile**));

    MOCK_METHOD2(NewAppendableFile, Status(const std::string&, WritableFile**));

    MOCK_METHOD1(FileExists, bool(const std::string&));

    MOCK_METHOD2(GetChildren, Status(const std::string&, std::vector<std::string>*));

    MOCK_METHOD1(RemoveFile, Status(const std::string&));

    MOCK_METHOD1(CreateDir, Status(const std::string&));

    MOCK_METHOD1(RemoveDir, Status(const std::string&));

    MOCK_METHOD2(GetFileSize, Status(const std::string&, uint64_t*));

    MOCK_METHOD2(RenameFile, Status(const std::string&, const std::string&));

    MOCK_METHOD2(LockFile, Status(const std::string&, FileLock**));

    MOCK_METHOD1(UnlockFile, Status(FileLock*));

    MOCK_METHOD2(Schedule, void(void (*)(void*), void*));

    MOCK_METHOD2(StartThread, void(void (*)(void*), void*));

    MOCK_METHOD1(GetTestDirectory, Status(std::string*));

    MOCK_METHOD2(NewLogger, Status(const std::string&, Logger**));

    MOCK_METHOD0(NowMicros, uint64_t());

    MOCK_METHOD1(SleepForMicroseconds, void(int));

};



class EnvWrapperTest : public ::testing::Test {

protected:

    MockEnv mock_env;

    EnvWrapper env_wrapper{&mock_env};

};



TEST_F(EnvWrapperTest_NewSequentialFile_106, NormalOperation_106) {

    SequentialFile* seq_file = nullptr;

    EXPECT_CALL(mock_env, NewSequentialFile("testfile", _))

        .WillOnce(Return(Status::OK()));

    auto status = env_wrapper.NewSequentialFile("testfile", &seq_file);

    EXPECT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_NewSequentialFile_106, FileNotFound_106) {

    SequentialFile* seq_file = nullptr;

    EXPECT_CALL(mock_env, NewSequentialFile("nonexistentfile", _))

        .WillOnce(Return(Status::NotFound("")));

    auto status = env_wrapper.NewSequentialFile("nonexistentfile", &seq_file);

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(EnvWrapperTest_NewSequentialFile_106, NullPointerResult_106) {

    SequentialFile* seq_file = nullptr;

    EXPECT_CALL(mock_env, NewSequentialFile(_, _))

        .WillOnce(Return(Status::OK()));

    auto status = env_wrapper.NewSequentialFile("testfile", nullptr);

    EXPECT_TRUE(status.IsInvalidArgument());

}



TEST_F(EnvWrapperTest_NewSequentialFile_106, EmptyFileName_106) {

    SequentialFile* seq_file = nullptr;

    EXPECT_CALL(mock_env, NewSequentialFile("", _))

        .WillOnce(Return(Status::InvalidArgument("")));

    auto status = env_wrapper.NewSequentialFile("", &seq_file);

    EXPECT_TRUE(status.IsInvalidArgument());

}
