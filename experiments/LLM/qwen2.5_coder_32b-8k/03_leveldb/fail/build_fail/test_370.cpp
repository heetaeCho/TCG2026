#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"

#include "helpers/memenv/memenv.cc"



using namespace leveldb;

using ::testing::Return;



class MemEnvTest_370 : public ::testing::Test {

protected:

    void SetUp() override {

        base_env = new Env();

        mem_env = dynamic_cast<InMemoryEnv*>(NewMemEnv(base_env));

    }



    void TearDown() override {

        delete mem_env;

        delete base_env;

    }



    Env* base_env;

    InMemoryEnv* mem_env;

};



TEST_F(MemEnvTest_370, NewSequentialFile_NormalOperation_370) {

    SequentialFile* file = nullptr;

    Status status = mem_env->NewSequentialFile("testfile", &file);

    EXPECT_TRUE(status.ok());

    delete file;

}



TEST_F(MemEnvTest_370, NewRandomAccessFile_NormalOperation_370) {

    RandomAccessFile* file = nullptr;

    Status status = mem_env->NewRandomAccessFile("testfile", &file);

    EXPECT_TRUE(status.ok());

    delete file;

}



TEST_F(MemEnvTest_370, NewWritableFile_NormalOperation_370) {

    WritableFile* file = nullptr;

    Status status = mem_env->NewWritableFile("testfile", &file);

    EXPECT_TRUE(status.ok());

    delete file;

}



TEST_F(MemEnvTest_370, NewAppendableFile_NormalOperation_370) {

    WritableFile* file = nullptr;

    Status status = mem_env->NewAppendableFile("testfile", &file);

    EXPECT_TRUE(status.ok());

    delete file;

}



TEST_F(MemEnvTest_370, FileExists_ReturnsFalseForNonExistentFile_370) {

    EXPECT_FALSE(mem_env->FileExists("nonexistentfile"));

}



TEST_F(MemEnvTest_370, GetChildren_EmptyDirectory_370) {

    std::vector<std::string> children;

    Status status = mem_env->GetChildren("/", &children);

    EXPECT_TRUE(status.ok());

    EXPECT_EQ(children.size(), 0);

}



TEST_F(MemEnvTest_370, RemoveFile_FileDoesNotExist_ReturnsError_370) {

    Status status = mem_env->RemoveFile("nonexistentfile");

    EXPECT_FALSE(status.ok());

}



TEST_F(MemEnvTest_370, DeleteFile_FileDoesNotExist_ReturnsError_370) {

    Status status = mem_env->DeleteFile("nonexistentfile");

    EXPECT_FALSE(status.ok());

}



TEST_F(MemEnvTest_370, CreateDir_NormalOperation_370) {

    Status status = mem_env->CreateDir("/testdir");

    EXPECT_TRUE(status.ok());

}



TEST_F(MemEnvTest_370, RemoveDir_DirectoryDoesNotExist_ReturnsError_370) {

    Status status = mem_env->RemoveDir("nonexistentdir");

    EXPECT_FALSE(status.ok());

}



TEST_F(MemEnvTest_370, DeleteDir_DirectoryDoesNotExist_ReturnsError_370) {

    Status status = mem_env->DeleteDir("nonexistentdir");

    EXPECT_FALSE(status.ok());

}



TEST_F(MemEnvTest_370, GetFileSize_FileDoesNotExist_ReturnsError_370) {

    uint64_t file_size;

    Status status = mem_env->GetFileSize("nonexistentfile", &file_size);

    EXPECT_FALSE(status.ok());

}



TEST_F(MemEnvTest_370, RenameFile_SourceFileDoesNotExist_ReturnsError_370) {

    Status status = mem_env->RenameFile("nonexistentfile", "newfile");

    EXPECT_FALSE(status.ok());

}



TEST_F(MemEnvTest_370, LockFile_FileDoesNotExist_ReturnsError_370) {

    FileLock* lock;

    Status status = mem_env->LockFile("nonexistentfile", &lock);

    EXPECT_FALSE(status.ok());

}



TEST_F(MemEnvTest_370, UnlockFile_NullLock_ReturnsError_370) {

    Status status = mem_env->UnlockFile(nullptr);

    EXPECT_FALSE(status.ok());

}
