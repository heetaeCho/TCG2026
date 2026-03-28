#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD(Status, NewSequentialFile, (const std::string &, SequentialFile **), (override));

    MOCK_METHOD(Status, NewRandomAccessFile, (const std::string &, RandomAccessFile **), (override));

    MOCK_METHOD(Status, NewWritableFile, (const std::string &, WritableFile **), (override));

    MOCK_METHOD(Status, NewAppendableFile, (const std::string &, WritableFile **), (override));

    MOCK_METHOD(bool, FileExists, (const std::string &), (override));

    MOCK_METHOD(Status, GetChildren, (const std::string &, std::vector<std::string> *), (override));

    MOCK_METHOD(Status, RemoveFile, (const std::string &), (override));

    MOCK_METHOD(Status, DeleteFile, (const std::string &), (override));

    MOCK_METHOD(Status, CreateDir, (const std::string &), (override));

    MOCK_METHOD(Status, RemoveDir, (const std::string &), (override));

    MOCK_METHOD(Status, GetFileSize, (const std::string &, uint64_t *), (override));

    MOCK_METHOD(Status, RenameFile, (const std::string &, const std::string &), (override));

    MOCK_METHOD(Status, LockFile, (const std::string &, FileLock **), (override));

    MOCK_METHOD(Status, UnlockFile, (FileLock *), (override));

    MOCK_METHOD(void, Schedule, (void (*)(void *), void *), (override));

    MOCK_METHOD(void, StartThread, (void (*)(void *), void *), (override));

    MOCK_METHOD(Status, GetTestDirectory, (std::string *), (override));

    MOCK_METHOD(Status, NewLogger, (const std::string &, Logger **), (override));

    MOCK_METHOD(uint64_t, NowMicros, (), (override));

    MOCK_METHOD(void, SleepForMicroseconds, (int), (override));

};



class EnvWrapperTest_119 : public ::testing::Test {

protected:

    MockEnv mock_env;

    EnvWrapper env_wrapper{&mock_env};

};



TEST_F(EnvWrapperTest_119, ScheduleFunctionCall_119) {

    void (*test_func)(void*) = [](void*){};

    void* test_arg = nullptr;



    EXPECT_CALL(mock_env, Schedule(test_func, test_arg)).Times(1);



    env_wrapper.Schedule(test_func, test_arg);

}



TEST_F(EnvWrapperTest_119, NewSequentialFile_NormalOperation_119) {

    std::string filename = "test_file";

    SequentialFile* file = nullptr;

    Status status;



    EXPECT_CALL(mock_env, NewSequentialFile(filename, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(file), Return(Status::OK())));



    status = env_wrapper.NewSequentialFile(filename, &file);

    

    ASSERT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_119, NewSequentialFile_FileNotFound_119) {

    std::string filename = "nonexistent_file";

    SequentialFile* file = nullptr;

    Status status;



    EXPECT_CALL(mock_env, NewSequentialFile(filename, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(file), Return(Status::NotFound("File not found"))));



    status = env_wrapper.NewSequentialFile(filename, &file);

    

    ASSERT_TRUE(status.IsNotFound());

}



TEST_F(EnvWrapperTest_119, NewRandomAccessFile_NormalOperation_119) {

    std::string filename = "test_file";

    RandomAccessFile* file = nullptr;

    Status status;



    EXPECT_CALL(mock_env, NewRandomAccessFile(filename, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(file), Return(Status::OK())));



    status = env_wrapper.NewRandomAccessFile(filename, &file);

    

    ASSERT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_119, NewRandomAccessFile_FileNotFound_119) {

    std::string filename = "nonexistent_file";

    RandomAccessFile* file = nullptr;

    Status status;



    EXPECT_CALL(mock_env, NewRandomAccessFile(filename, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(file), Return(Status::NotFound("File not found"))));



    status = env_wrapper.NewRandomAccessFile(filename, &file);

    

    ASSERT_TRUE(status.IsNotFound());

}



TEST_F(EnvWrapperTest_119, NewWritableFile_NormalOperation_119) {

    std::string filename = "test_file";

    WritableFile* file = nullptr;

    Status status;



    EXPECT_CALL(mock_env, NewWritableFile(filename, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(file), Return(Status::OK())));



    status = env_wrapper.NewWritableFile(filename, &file);

    

    ASSERT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_119, NewAppendableFile_NormalOperation_119) {

    std::string filename = "test_file";

    WritableFile* file = nullptr;

    Status status;



    EXPECT_CALL(mock_env, NewAppendableFile(filename, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(file), Return(Status::OK())));



    status = env_wrapper.NewAppendableFile(filename, &file);

    

    ASSERT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_119, FileExists_ReturnsTrue_119) {

    std::string filename = "existing_file";



    EXPECT_CALL(mock_env, FileExists(filename)).WillOnce(Return(true));



    bool exists = env_wrapper.FileExists(filename);



    ASSERT_TRUE(exists);

}



TEST_F(EnvWrapperTest_119, FileExists_ReturnsFalse_119) {

    std::string filename = "nonexistent_file";



    EXPECT_CALL(mock_env, FileExists(filename)).WillOnce(Return(false));



    bool exists = env_wrapper.FileExists(filename);



    ASSERT_FALSE(exists);

}



TEST_F(EnvWrapperTest_119, GetChildren_NormalOperation_119) {

    std::string dir = ".";

    std::vector<std::string> children;



    EXPECT_CALL(mock_env, GetChildren(dir, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(children), Return(Status::OK())));



    Status status = env_wrapper.GetChildren(dir, &children);

    

    ASSERT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_119, RemoveFile_NormalOperation_119) {

    std::string filename = "test_file";



    EXPECT_CALL(mock_env, RemoveFile(filename)).WillOnce(Return(Status::OK()));



    Status status = env_wrapper.RemoveFile(filename);

    

    ASSERT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_119, CreateDir_NormalOperation_119) {

    std::string dir = "new_dir";



    EXPECT_CALL(mock_env, CreateDir(dir)).WillOnce(Return(Status::OK()));



    Status status = env_wrapper.CreateDir(dir);

    

    ASSERT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_119, GetFileSize_NormalOperation_119) {

    std::string filename = "test_file";

    uint64_t file_size;



    EXPECT_CALL(mock_env, GetFileSize(filename, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(file_size), Return(Status::OK())));



    Status status = env_wrapper.GetFileSize(filename, &file_size);

    

    ASSERT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_119, RenameFile_NormalOperation_119) {

    std::string src = "old_name";

    std::string target = "new_name";



    EXPECT_CALL(mock_env, RenameFile(src, target)).WillOnce(Return(Status::OK()));



    Status status = env_wrapper.RenameFile(src, target);

    

    ASSERT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_119, LockFile_NormalOperation_119) {

    std::string filename = "test_file";

    FileLock* lock = nullptr;



    EXPECT_CALL(mock_env, LockFile(filename, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(lock), Return(Status::OK())));



    Status status = env_wrapper.LockFile(filename, &lock);

    

    ASSERT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_119, UnlockFile_NormalOperation_119) {

    FileLock* lock = new FileLock();



    EXPECT_CALL(mock_env, UnlockFile(lock)).WillOnce(Return(Status::OK()));



    Status status = env_wrapper.UnlockFile(lock);

    

    ASSERT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_119, GetTestDirectory_NormalOperation_119) {

    std::string path;



    EXPECT_CALL(mock_env, GetTestDirectory(_))

        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(path), Return(Status::OK())));



    Status status = env_wrapper.GetTestDirectory(&path);

    

    ASSERT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_119, NewLogger_NormalOperation_119) {

    std::string filename = "test_log";

    Logger* logger = nullptr;



    EXPECT_CALL(mock_env, NewLogger(filename, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(logger), Return(Status::OK())));



    Status status = env_wrapper.NewLogger(filename, &logger);

    

    ASSERT_TRUE(status.ok());

}



TEST_F(EnvWrapperTest_119, NowMicros_NormalOperation_119) {

    uint64_t time;



    EXPECT_CALL(mock_env, NowMicros()).WillOnce(Return(time));



    time = env_wrapper.NowMicros();

}



TEST_F(EnvWrapperTest_119, SleepForMicroseconds_NormalOperation_119) {

    int micros = 1000;



    EXPECT_CALL(mock_env, SleepForMicroseconds(micros)).Times(1);



    env_wrapper.SleepForMicroseconds(micros);

}
