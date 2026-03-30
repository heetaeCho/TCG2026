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



TEST_F(EnvWrapperTest_GetChildren_111, NormalOperationWithNonEmptyDirectory_111) {

    std::vector<std::string> children = {"file1", "file2"};

    EXPECT_CALL(mock_env, GetChildren("test_dir", _)).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<1>(children),

        Return(Status::OK())

    ));



    std::vector<std::string> result;

    Status status = env_wrapper.GetChildren("test_dir", &result);



    EXPECT_EQ(status.ok(), true);

    EXPECT_EQ(result, children);

}



TEST_F(EnvWrapperTest_GetChildren_111, NormalOperationWithEmptyDirectory_111) {

    std::vector<std::string> children;

    EXPECT_CALL(mock_env, GetChildren("test_dir", _)).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<1>(children),

        Return(Status::OK())

    ));



    std::vector<std::string> result;

    Status status = env_wrapper.GetChildren("test_dir", &result);



    EXPECT_EQ(status.ok(), true);

    EXPECT_EQ(result, children);

}



TEST_F(EnvWrapperTest_GetChildren_111, ErrorCaseWithNonExistentDirectory_111) {

    EXPECT_CALL(mock_env, GetChildren("non_existent_dir", _)).WillOnce(Return(Status::IOError()));



    std::vector<std::string> result;

    Status status = env_wrapper.GetChildren("non_existent_dir", &result);



    EXPECT_EQ(status.ok(), false);

}



TEST_F(EnvWrapperTest_GetChildren_111, BoundaryCaseWithEmptyStringDirectory_111) {

    std::vector<std::string> children;

    EXPECT_CALL(mock_env, GetChildren("", _)).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<1>(children),

        Return(Status::OK())

    ));



    std::vector<std::string> result;

    Status status = env_wrapper.GetChildren("", &result);



    EXPECT_EQ(status.ok(), true);

    EXPECT_EQ(result, children);

}
