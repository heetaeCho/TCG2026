#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Eq;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD(Status, NewSequentialFile, (const std::string &fname, SequentialFile **result), (override));

    MOCK_METHOD(Status, NewRandomAccessFile, (const std::string &fname, RandomAccessFile **result), (override));

    MOCK_METHOD(Status, NewWritableFile, (const std::string &fname, WritableFile **result), (override));

    MOCK_METHOD(Status, NewAppendableFile, (const std::string &fname, WritableFile **result), (override));

    MOCK_METHOD(bool, FileExists, (const std::string &fname), (override));

    MOCK_METHOD(Status, GetChildren, (const std::string &dir, std::vector<std::string> *result), (override));

    MOCK_METHOD(Status, RemoveFile, (const std::string &fname), (override));

    MOCK_METHOD(Status, CreateDir, (const std::string &dirname), (override));

    MOCK_METHOD(Status, RemoveDir, (const std::string &dirname), (override));

    MOCK_METHOD(Status, GetFileSize, (const std::string &fname, uint64_t *file_size), (override));

    MOCK_METHOD(Status, RenameFile, (const std::string &src, const std::string &target), (override));

    MOCK_METHOD(Status, LockFile, (const std::string &fname, FileLock **lock), (override));

    MOCK_METHOD(Status, UnlockFile, (FileLock *lock), (override));

    MOCK_METHOD(void, Schedule, (void (*function)(void *), void *arg), (override));

    MOCK_METHOD(void, StartThread, (void (*function)(void *), void *arg), (override));

    MOCK_METHOD(Status, GetTestDirectory, (std::string *path), (override));

    MOCK_METHOD(Status, NewLogger, (const std::string &fname, Logger **result), (override));

    MOCK_METHOD(uint64_t, NowMicros, (), (override));

    MOCK_METHOD(void, SleepForMicroseconds, (int micros), (override));

};



class EnvWrapperTest : public ::testing::Test {

protected:

    MockEnv* mock_env_;

    EnvWrapper* env_wrapper_;



    void SetUp() override {

        mock_env_ = new MockEnv();

        env_wrapper_ = new EnvWrapper(mock_env_);

    }



    void TearDown() override {

        delete env_wrapper_;

        delete mock_env_;

    }

};



TEST_F(EnvWrapperTest, NowMicros_ReturnsTargetNowMicros_123) {

    uint64_t expected_time = 123456789;

    EXPECT_CALL(*mock_env_, NowMicros()).WillOnce(Return(expected_time));



    uint64_t actual_time = env_wrapper_->NowMicros();

    EXPECT_EQ(actual_time, expected_time);

}



TEST_F(EnvWrapperTest, NewSequentialFile_DelegatesToTarget_123) {

    const std::string fname = "testfile";

    SequentialFile* result = nullptr;

    Status status = Status::OK();



    EXPECT_CALL(*mock_env_, NewSequentialFile(Eq(fname), _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(result), Return(status)));



    env_wrapper_->NewSequentialFile(fname, &result);

}



TEST_F(EnvWrapperTest, FileExists_DelegatesToTarget_123) {

    const std::string fname = "testfile";

    bool expected_exists = true;



    EXPECT_CALL(*mock_env_, FileExists(Eq(fname)))

        .WillOnce(Return(expected_exists));



    bool actual_exists = env_wrapper_->FileExists(fname);

    EXPECT_EQ(actual_exists, expected_exists);

}



TEST_F(EnvWrapperTest, GetChildren_DelegatesToTarget_123) {

    const std::string dir = "testdir";

    std::vector<std::string> result;

    Status status = Status::OK();



    EXPECT_CALL(*mock_env_, GetChildren(Eq(dir), _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(result), Return(status)));



    env_wrapper_->GetChildren(dir, &result);

}



TEST_F(EnvWrapperTest, RemoveFile_DelegatesToTarget_123) {

    const std::string fname = "testfile";

    Status status = Status::OK();



    EXPECT_CALL(*mock_env_, RemoveFile(Eq(fname)))

        .WillOnce(Return(status));



    env_wrapper_->RemoveFile(fname);

}



TEST_F(EnvWrapperTest, CreateDir_DelegatesToTarget_123) {

    const std::string dirname = "testdir";

    Status status = Status::OK();



    EXPECT_CALL(*mock_env_, CreateDir(Eq(dirname)))

        .WillOnce(Return(status));



    env_wrapper_->CreateDir(dirname);

}



TEST_F(EnvWrapperTest, RemoveDir_DelegatesToTarget_123) {

    const std::string dirname = "testdir";

    Status status = Status::OK();



    EXPECT_CALL(*mock_env_, RemoveDir(Eq(dirname)))

        .WillOnce(Return(status));



    env_wrapper_->RemoveDir(dirname);

}



TEST_F(EnvWrapperTest, GetFileSize_DelegatesToTarget_123) {

    const std::string fname = "testfile";

    uint64_t file_size;

    Status status = Status::OK();



    EXPECT_CALL(*mock_env_, GetFileSize(Eq(fname), _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(file_size), Return(status)));



    env_wrapper_->GetFileSize(fname, &file_size);

}



TEST_F(EnvWrapperTest, RenameFile_DelegatesToTarget_123) {

    const std::string src = "srcfile";

    const std::string target = "targetfile";

    Status status = Status::OK();



    EXPECT_CALL(*mock_env_, RenameFile(Eq(src), Eq(target)))

        .WillOnce(Return(status));



    env_wrapper_->RenameFile(src, target);

}



TEST_F(EnvWrapperTest, LockFile_DelegatesToTarget_123) {

    const std::string fname = "testfile";

    FileLock* lock;

    Status status = Status::OK();



    EXPECT_CALL(*mock_env_, LockFile(Eq(fname), _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(lock), Return(status)));



    env_wrapper_->LockFile(fname, &lock);

}



TEST_F(EnvWrapperTest, UnlockFile_DelegatesToTarget_123) {

    FileLock* lock = nullptr;

    Status status = Status::OK();



    EXPECT_CALL(*mock_env_, UnlockFile(Eq(lock)))

        .WillOnce(Return(status));



    env_wrapper_->UnlockFile(lock);

}



TEST_F(EnvWrapperTest, Schedule_DelegatesToTarget_123) {

    void (*function)(void *) = [](void*){};

    void* arg = nullptr;



    EXPECT_CALL(*mock_env_, Schedule(Eq(function), Eq(arg)));



    env_wrapper_->Schedule(function, arg);

}



TEST_F(EnvWrapperTest, StartThread_DelegatesToTarget_123) {

    void (*function)(void *) = [](void*){};

    void* arg = nullptr;



    EXPECT_CALL(*mock_env_, StartThread(Eq(function), Eq(arg)));



    env_wrapper_->StartThread(function, arg);

}



TEST_F(EnvWrapperTest, GetTestDirectory_DelegatesToTarget_123) {

    std::string path;

    Status status = Status::OK();



    EXPECT_CALL(*mock_env_, GetTestDirectory(_))

        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(path), Return(status)));



    env_wrapper_->GetTestDirectory(&path);

}



TEST_F(EnvWrapperTest, NewLogger_DelegatesToTarget_123) {

    const std::string fname = "testfile";

    Logger* result;

    Status status = Status::OK();



    EXPECT_CALL(*mock_env_, NewLogger(Eq(fname), _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(result), Return(status)));



    env_wrapper_->NewLogger(fname, &result);

}



TEST_F(EnvWrapperTest, SleepForMicroseconds_DelegatesToTarget_123) {

    int micros = 100;



    EXPECT_CALL(*mock_env_, SleepForMicroseconds(Eq(micros)));



    env_wrapper_->SleepForMicroseconds(micros);

}
