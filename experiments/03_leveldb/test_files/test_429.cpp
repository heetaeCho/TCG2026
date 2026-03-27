#include <gtest/gtest.h>

#include "leveldb/env.h"

#include "util/env_posix.cc"



using namespace leveldb;



class EnvTest_429 : public ::testing::Test {

protected:

    Env* env;



    void SetUp() override {

        env = Env::Default();

    }



    void TearDown() override {

        // No need to delete the environment as it's a singleton

    }

};



TEST_F(EnvTest_429, DefaultReturnsNonNull_429) {

    EXPECT_NE(env, nullptr);

}



TEST_F(EnvTest_429, NewSequentialFile_ReturnsOkForExistingFile_429) {

    SequentialFile* file = nullptr;

    Status status = env->NewSequentialFile("/proc/self/exe", &file); // Assuming /proc/self/exe always exists

    EXPECT_TRUE(status.ok());

    delete file;

}



TEST_F(EnvTest_429, NewSequentialFile_ReturnsNotFoundForNonExistingFile_429) {

    SequentialFile* file = nullptr;

    Status status = env->NewSequentialFile("/nonexistent_file", &file);

    EXPECT_TRUE(status.IsNotFound());

    EXPECT_EQ(file, nullptr);

}



TEST_F(EnvTest_429, NewRandomAccessFile_ReturnsOkForExistingFile_429) {

    RandomAccessFile* file = nullptr;

    Status status = env->NewRandomAccessFile("/proc/self/exe", &file); // Assuming /proc/self/exe always exists

    EXPECT_TRUE(status.ok());

    delete file;

}



TEST_F(EnvTest_429, NewRandomAccessFile_ReturnsNotFoundForNonExistingFile_429) {

    RandomAccessFile* file = nullptr;

    Status status = env->NewRandomAccessFile("/nonexistent_file", &file);

    EXPECT_TRUE(status.IsNotFound());

    EXPECT_EQ(file, nullptr);

}



TEST_F(EnvTest_429, NewWritableFile_ReturnsOkForValidPath_429) {

    WritableFile* file = nullptr;

    Status status = env->NewWritableFile("/tmp/test_writable_file_429", &file);

    EXPECT_TRUE(status.ok());

    delete file;

    env->DeleteFile("/tmp/test_writable_file_429");

}



TEST_F(EnvTest_429, NewAppendableFile_ReturnsOkForValidPath_429) {

    WritableFile* file = nullptr;

    Status status = env->NewAppendableFile("/tmp/test_appendable_file_429", &file);

    EXPECT_TRUE(status.ok());

    delete file;

    env->DeleteFile("/tmp/test_appendable_file_429");

}



TEST_F(EnvTest_429, FileExists_ReturnsTrueForExistingFile_429) {

    bool exists = env->FileExists("/proc/self/exe"); // Assuming /proc/self/exe always exists

    EXPECT_TRUE(exists);

}



TEST_F(EnvTest_429, FileExists_ReturnsFalseForNonExistingFile_429) {

    bool exists = env->FileExists("/nonexistent_file");

    EXPECT_FALSE(exists);

}



TEST_F(EnvTest_429, GetChildren_ReturnsOkAndPopulatesResultForExistingDirectory_429) {

    std::vector<std::string> result;

    Status status = env->GetChildren("/", &result);

    EXPECT_TRUE(status.ok());

    EXPECT_FALSE(result.empty());

}



TEST_F(EnvTest_429, RemoveFile_ReturnsOkForExistingFile_429) {

    WritableFile* file = nullptr;

    env->NewWritableFile("/tmp/test_remove_file_429", &file);

    delete file;



    Status status = env->RemoveFile("/tmp/test_remove_file_429");

    EXPECT_TRUE(status.ok());

}



TEST_F(EnvTest_429, DeleteFile_ReturnsOkForExistingFile_429) {

    WritableFile* file = nullptr;

    env->NewWritableFile("/tmp/test_delete_file_429", &file);

    delete file;



    Status status = env->DeleteFile("/tmp/test_delete_file_429");

    EXPECT_TRUE(status.ok());

}



TEST_F(EnvTest_429, CreateDir_ReturnsOkForNonExistingDirectory_429) {

    Status status = env->CreateDir("/tmp/test_create_dir_429");

    EXPECT_TRUE(status.ok());



    env->DeleteDir("/tmp/test_create_dir_429");

}



TEST_F(EnvTest_429, RemoveDir_ReturnsOkForExistingEmptyDirectory_429) {

    Status status = env->CreateDir("/tmp/test_remove_dir_429");

    EXPECT_TRUE(status.ok());



    status = env->RemoveDir("/tmp/test_remove_dir_429");

    EXPECT_TRUE(status.ok());

}



TEST_F(EnvTest_429, DeleteDir_ReturnsOkForExistingEmptyDirectory_429) {

    Status status = env->CreateDir("/tmp/test_delete_dir_429");

    EXPECT_TRUE(status.ok());



    status = env->DeleteDir("/tmp/test_delete_dir_429");

    EXPECT_TRUE(status.ok());

}



TEST_F(EnvTest_429, GetFileSize_ReturnsOkAndSetsFileSizeForExistingFile_429) {

    WritableFile* file = nullptr;

    env->NewWritableFile("/tmp/test_get_file_size_429", &file);

    delete file;



    uint64_t file_size = 0;

    Status status = env->GetFileSize("/tmp/test_get_file_size_429", &file_size);

    EXPECT_TRUE(status.ok());

    EXPECT_EQ(file_size, 0);



    env->DeleteFile("/tmp/test_get_file_size_429");

}



TEST_F(EnvTest_429, RenameFile_ReturnsOkForExistingFile_429) {

    WritableFile* file = nullptr;

    env->NewWritableFile("/tmp/test_rename_file_src_429", &file);

    delete file;



    Status status = env->RenameFile("/tmp/test_rename_file_src_429", "/tmp/test_rename_file_dst_429");

    EXPECT_TRUE(status.ok());



    env->DeleteFile("/tmp/test_rename_file_dst_429");

}



TEST_F(EnvTest_429, LockFile_ReturnsOkForExistingFile_429) {

    WritableFile* file = nullptr;

    env->NewWritableFile("/tmp/test_lock_file_429", &file);

    delete file;



    FileLock* lock = nullptr;

    Status status = env->LockFile("/tmp/test_lock_file_429", &lock);

    EXPECT_TRUE(status.ok());

    env->UnlockFile(lock);



    env->DeleteFile("/tmp/test_lock_file_429");

}



TEST_F(EnvTest_429, Schedule_SchedulesFunction_429) {

    bool function_called = false;

    auto func = [&function_called] (void*) { function_called = true; };



    env->Schedule(func, nullptr);

    env->SleepForMicroseconds(1000); // Give some time for the scheduler to run

    EXPECT_TRUE(function_called);

}



TEST_F(EnvTest_429, StartThread_StartsFunction_429) {

    bool function_called = false;

    auto func = [&function_called] (void*) { function_called = true; };



    env->StartThread(func, nullptr);

    env->SleepForMicroseconds(1000); // Give some time for the thread to run

    EXPECT_TRUE(function_called);

}



TEST_F(EnvTest_429, GetTestDirectory_ReturnsOkAndSetsPath_429) {

    std::string path;

    Status status = env->GetTestDirectory(&path);

    EXPECT_TRUE(status.ok());

    EXPECT_FALSE(path.empty());

}



TEST_F(EnvTest_429, NewLogger_ReturnsOkForValidPath_429) {

    Logger* logger = nullptr;

    Status status = env->NewLogger("/tmp/test_logger_file_429", &logger);

    EXPECT_TRUE(status.ok());

    delete logger;

    env->DeleteFile("/tmp/test_logger_file_429");

}



TEST_F(EnvTest_429, NowMicros_ReturnsNonZero_429) {

    uint64_t time = env->NowMicros();

    EXPECT_NE(time, 0);

}



TEST_F(EnvTest_429, SleepForMicroseconds_SleepsForGivenDuration_429) {

    uint64_t start_time = env->NowMicros();

    env->SleepForMicroseconds(1000); // sleep for 1 ms

    uint64_t end_time = env->NowMicros();



    EXPECT_GE(end_time - start_time, 1000);

}
