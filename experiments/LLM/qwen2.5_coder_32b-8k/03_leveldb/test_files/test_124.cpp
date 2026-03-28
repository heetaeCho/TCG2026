#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD1(NewSequentialFile, Status(const std::string&, SequentialFile**));

    MOCK_METHOD1(NewRandomAccessFile, Status(const std::string&, RandomAccessFile**));

    MOCK_METHOD1(NewWritableFile, Status(const std::string&, WritableFile**));

    MOCK_METHOD1(NewAppendableFile, Status(const std::string&, WritableFile**));

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



TEST_F(EnvWrapperTest_SleepForMicroseconds_124, SleepForPositiveMicroseconds_124) {

    EXPECT_CALL(mock_env, SleepForMicroseconds(100)).Times(1);

    env_wrapper.SleepForMicroseconds(100);

}



TEST_F(EnvWrapperTest_SleepForMicroseconds_124, SleepForZeroMicroseconds_124) {

    EXPECT_CALL(mock_env, SleepForMicroseconds(0)).Times(1);

    env_wrapper.SleepForMicroseconds(0);

}



TEST_F(EnvWrapperTest_NewSequentialFile_124, NewSequentialFile_Success_124) {

    SequentialFile* file = nullptr;

    Status status = Status::OK();

    EXPECT_CALL(mock_env, NewSequentialFile("testfile", _)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(file), Return(status)));

    env_wrapper.NewSequentialFile("testfile", &file);

    ASSERT_EQ(file, nullptr); // Assuming file creation doesn't return a pointer in this mock setup

}



TEST_F(EnvWrapperTest_NewSequentialFile_124, NewSequentialFile_Failure_124) {

    SequentialFile* file = nullptr;

    Status status = Status::IOError();

    EXPECT_CALL(mock_env, NewSequentialFile("testfile", _)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(file), Return(status)));

    env_wrapper.NewSequentialFile("testfile", &file);

    ASSERT_EQ(file, nullptr); // Assuming file creation doesn't return a pointer in this mock setup

}



TEST_F(EnvWrapperTest_FileExists_124, FileExists_ReturnsTrue_124) {

    EXPECT_CALL(mock_env, FileExists("existingfile")).WillOnce(Return(true));

    bool exists = env_wrapper.FileExists("existingfile");

    ASSERT_TRUE(exists);

}



TEST_F(EnvWrapperTest_FileExists_124, FileExists_ReturnsFalse_124) {

    EXPECT_CALL(mock_env, FileExists("nonexistentfile")).WillOnce(Return(false));

    bool exists = env_wrapper.FileExists("nonexistentfile");

    ASSERT_FALSE(exists);

}
