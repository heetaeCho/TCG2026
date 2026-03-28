#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;

using ::testing::NotNull;



class MockEnv : public Env {

public:

    MOCK_METHOD(Status, NewSequentialFile, (const std::string& f, SequentialFile** r), (override));

    MOCK_METHOD(Status, NewRandomAccessFile, (const std::string& f, RandomAccessFile** r), (override));

    MOCK_METHOD(Status, NewWritableFile, (const std::string& f, WritableFile** r), (override));

    MOCK_METHOD(Status, NewAppendableFile, (const std::string& f, WritableFile** r), (override));

    MOCK_METHOD(bool, FileExists, (const std::string& f), (override));

    MOCK_METHOD(Status, GetChildren, (const std::string& dir, std::vector<std::string>* r), (override));

    MOCK_METHOD(Status, RemoveFile, (const std::string& f), (override));

    MOCK_METHOD(Status, CreateDir, (const std::string& d), (override));

    MOCK_METHOD(Status, RemoveDir, (const std::string& d), (override));

    MOCK_METHOD(Status, GetFileSize, (const std::string& f, uint64_t* s), (override));

    MOCK_METHOD(Status, RenameFile, (const std::string& s, const std::string& t), (override));

    MOCK_METHOD(Status, LockFile, (const std::string& f, FileLock** l), (override));

    MOCK_METHOD(Status, UnlockFile, (FileLock* l), (override));

    MOCK_METHOD(void, Schedule, (void (*f)(void*), void* a), (override));

    MOCK_METHOD(void, StartThread, (void (*f)(void*), void* a), (override));

    MOCK_METHOD(Status, GetTestDirectory, (std::string* path), (override));

    MOCK_METHOD(Status, NewLogger, (const std::string& fname, Logger** result), (override));

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



TEST_F(EnvWrapperTest_FileExists_105, FileExists_DelegatesToTarget_105) {

    EXPECT_CALL(*mock_env_, FileExists("testfile")).WillOnce(Return(true));

    EXPECT_TRUE(env_wrapper_->FileExists("testfile"));

}



TEST_F(EnvWrapperTest_NewSequentialFile_105, NewSequentialFile_DelegatesToTarget_105) {

    SequentialFile* seq_file = nullptr;

    Status status;

    EXPECT_CALL(*mock_env_, NewSequentialFile("testfile", NotNull()))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(seq_file), Return(Status::OK())));

    status = env_wrapper_->NewSequentialFile("testfile", &seq_file);

    EXPECT_EQ(status, Status::OK());

}



TEST_F(EnvWrapperTest_NewRandomAccessFile_105, NewRandomAccessFile_DelegatesToTarget_105) {

    RandomAccessFile* rand_access_file = nullptr;

    Status status;

    EXPECT_CALL(*mock_env_, NewRandomAccessFile("testfile", NotNull()))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(rand_access_file), Return(Status::OK())));

    status = env_wrapper_->NewRandomAccessFile("testfile", &rand_access_file);

    EXPECT_EQ(status, Status::OK());

}



TEST_F(EnvWrapperTest_NewWritableFile_105, NewWritableFile_DelegatesToTarget_105) {

    WritableFile* writable_file = nullptr;

    Status status;

    EXPECT_CALL(*mock_env_, NewWritableFile("testfile", NotNull()))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(writable_file), Return(Status::OK())));

    status = env_wrapper_->NewWritableFile("testfile", &writable_file);

    EXPECT_EQ(status, Status::OK());

}



TEST_F(EnvWrapperTest_NewAppendableFile_105, NewAppendableFile_DelegatesToTarget_105) {

    WritableFile* appendable_file = nullptr;

    Status status;

    EXPECT_CALL(*mock_env_, NewAppendableFile("testfile", NotNull()))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(appendable_file), Return(Status::OK())));

    status = env_wrapper_->NewAppendableFile("testfile", &appendable_file);

    EXPECT_EQ(status, Status::OK());

}



TEST_F(EnvWrapperTest_GetChildren_105, GetChildren_DelegatesToTarget_105) {

    std::vector<std::string> children;

    Status status;

    EXPECT_CALL(*mock_env_, GetChildren("testdir", NotNull()))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(children), Return(Status::OK())));

    status = env_wrapper_->GetChildren("testdir", &children);

    EXPECT_EQ(status, Status::OK());

}



TEST_F(EnvWrapperTest_RemoveFile_105, RemoveFile_DelegatesToTarget_105) {

    Status status;

    EXPECT_CALL(*mock_env_, RemoveFile("testfile")).WillOnce(Return(Status::OK()));

    status = env_wrapper_->RemoveFile("testfile");

    EXPECT_EQ(status, Status::OK());

}



TEST_F(EnvWrapperTest_CreateDir_105, CreateDir_DelegatesToTarget_105) {

    Status status;

    EXPECT_CALL(*mock_env_, CreateDir("testdir")).WillOnce(Return(Status::OK()));

    status = env_wrapper_->CreateDir("testdir");

    EXPECT_EQ(status, Status::OK());

}



TEST_F(EnvWrapperTest_RemoveDir_105, RemoveDir_DelegatesToTarget_105) {

    Status status;

    EXPECT_CALL(*mock_env_, RemoveDir("testdir")).WillOnce(Return(Status::OK()));

    status = env_wrapper_->RemoveDir("testdir");

    EXPECT_EQ(status, Status::OK());

}



TEST_F(EnvWrapperTest_GetFileSize_105, GetFileSize_DelegatesToTarget_105) {

    uint64_t file_size;

    Status status;

    EXPECT_CALL(*mock_env_, GetFileSize("testfile", NotNull()))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(file_size), Return(Status::OK())));

    status = env_wrapper_->GetFileSize("testfile", &file_size);

    EXPECT_EQ(status, Status::OK());

}



TEST_F(EnvWrapperTest_RenameFile_105, RenameFile_DelegatesToTarget_105) {

    Status status;

    EXPECT_CALL(*mock_env_, RenameFile("oldname", "newname")).WillOnce(Return(Status::OK()));

    status = env_wrapper_->RenameFile("oldname", "newname");

    EXPECT_EQ(status, Status::OK());

}



TEST_F(EnvWrapperTest_LockFile_105, LockFile_DelegatesToTarget_105) {

    FileLock* file_lock = nullptr;

    Status status;

    EXPECT_CALL(*mock_env_, LockFile("testfile", NotNull()))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(file_lock), Return(Status::OK())));

    status = env_wrapper_->LockFile("testfile", &file_lock);

    EXPECT_EQ(status, Status::OK());

}



TEST_F(EnvWrapperTest_UnlockFile_105, UnlockFile_DelegatesToTarget_105) {

    FileLock* file_lock = new FileLock();

    Status status;

    EXPECT_CALL(*mock_env_, UnlockFile(file_lock)).WillOnce(Return(Status::OK()));

    status = env_wrapper_->UnlockFile(file_lock);

    EXPECT_EQ(status, Status::OK());

}



TEST_F(EnvWrapperTest_Schedule_105, Schedule_DelegatesToTarget_105) {

    void (*f)(void*) = [](void* a) {};

    void* arg = nullptr;

    EXPECT_CALL(*mock_env_, Schedule(f, arg));

    env_wrapper_->Schedule(f, arg);

}



TEST_F(EnvWrapperTest_StartThread_105, StartThread_DelegatesToTarget_105) {

    void (*f)(void*) = [](void* a) {};

    void* arg = nullptr;

    EXPECT_CALL(*mock_env_, StartThread(f, arg));

    env_wrapper_->StartThread(f, arg);

}



TEST_F(EnvWrapperTest_GetTestDirectory_105, GetTestDirectory_DelegatesToTarget_105) {

    std::string path;

    Status status;

    EXPECT_CALL(*mock_env_, GetTestDirectory(NotNull()))

        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(path), Return(Status::OK())));

    status = env_wrapper_->GetTestDirectory(&path);

    EXPECT_EQ(status, Status::OK());

}



TEST_F(EnvWrapperTest_NewLogger_105, NewLogger_DelegatesToTarget_105) {

    Logger* logger = nullptr;

    Status status;

    EXPECT_CALL(*mock_env_, NewLogger("testlog", NotNull()))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(logger), Return(Status::OK())));

    status = env_wrapper_->NewLogger("testlog", &logger);

    EXPECT_EQ(status, Status::OK());

}



TEST_F(EnvWrapperTest_NowMicros_105, NowMicros_DelegatesToTarget_105) {

    uint64_t micros;

    EXPECT_CALL(*mock_env_, NowMicros()).WillOnce(Return(micros));

    env_wrapper_->NowMicros();

}



TEST_F(EnvWrapperTest_SleepForMicroseconds_105, SleepForMicroseconds_DelegatesToTarget_105) {

    int microseconds = 100;

    EXPECT_CALL(*mock_env_, SleepForMicroseconds(microseconds));

    env_wrapper_->SleepForMicroseconds(microseconds);

}



TEST_F(EnvWrapperTest_GetChildren_ErrorHandling_105, GetChildren_ReturnsError_105) {

    std::vector<std::string> children;

    Status status;

    EXPECT_CALL(*mock_env_, GetChildren("testdir", NotNull()))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(children), Return(Status::IOError())));

    status = env_wrapper_->GetChildren("testdir", &children);

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(EnvWrapperTest_RemoveFile_ErrorHandling_105, RemoveFile_ReturnsError_105) {

    Status status;

    EXPECT_CALL(*mock_env_, RemoveFile("testfile")).WillOnce(Return(Status::IOError()));

    status = env_wrapper_->RemoveFile("testfile");

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(EnvWrapperTest_CreateDir_ErrorHandling_105, CreateDir_ReturnsError_105) {

    Status status;

    EXPECT_CALL(*mock_env_, CreateDir("testdir")).WillOnce(Return(Status::IOError()));

    status = env_wrapper_->CreateDir("testdir");

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(EnvWrapperTest_RemoveDir_ErrorHandling_105, RemoveDir_ReturnsError_105) {

    Status status;

    EXPECT_CALL(*mock_env_, RemoveDir("testdir")).WillOnce(Return(Status::IOError()));

    status = env_wrapper_->RemoveDir("testdir");

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(EnvWrapperTest_GetFileSize_ErrorHandling_105, GetFileSize_ReturnsError_105) {

    uint64_t file_size;

    Status status;

    EXPECT_CALL(*mock_env_, GetFileSize("testfile", NotNull()))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(file_size), Return(Status::IOError())));

    status = env_wrapper_->GetFileSize("testfile", &file_size);

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(EnvWrapperTest_RenameFile_ErrorHandling_105, RenameFile_ReturnsError_105) {

    Status status;

    EXPECT_CALL(*mock_env_, RenameFile("oldname", "newname")).WillOnce(Return(Status::IOError()));

    status = env_wrapper_->RenameFile("oldname", "newname");

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(EnvWrapperTest_LockFile_ErrorHandling_105, LockFile_ReturnsError_105) {

    FileLock* file_lock = nullptr;

    Status status;

    EXPECT_CALL(*mock_env_, LockFile("testfile", NotNull()))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(file_lock), Return(Status::IOError())));

    status = env_wrapper_->LockFile("testfile", &file_lock);

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(EnvWrapperTest_UnlockFile_ErrorHandling_105, UnlockFile_ReturnsError_105) {

    FileLock* file_lock = new FileLock();

    Status status;

    EXPECT_CALL(*mock_env_, UnlockFile(file_lock)).WillOnce(Return(Status::IOError()));

    status = env_wrapper_->UnlockFile(file_lock);

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(EnvWrapperTest_GetTestDirectory_ErrorHandling_105, GetTestDirectory_ReturnsError_105) {

    std::string path;

    Status status;

    EXPECT_CALL(*mock_env_, GetTestDirectory(NotNull()))

        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(path), Return(Status::IOError())));

    status = env_wrapper_->GetTestDirectory(&path);

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(EnvWrapperTest_NewLogger_ErrorHandling_105, NewLogger_ReturnsError_105) {

    Logger* logger = nullptr;

    Status status;

    EXPECT_CALL(*mock_env_, NewLogger("testlog", NotNull()))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(logger), Return(Status::IOError())));

    status = env_wrapper_->NewLogger("testlog", &logger);

    EXPECT_TRUE(status.IsIOError());

}
