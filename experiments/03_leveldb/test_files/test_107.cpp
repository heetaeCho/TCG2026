#include <gtest/gtest.h>

#include "leveldb/env.h"

#include "leveldb/status.h"



using namespace leveldb;



class EnvWrapperTest : public ::testing::Test {

protected:

    Env* mock_target_env;

    EnvWrapper* env_wrapper;



    void SetUp() override {

        mock_target_env = new Env();

        env_wrapper = new EnvWrapper(mock_target_env);

    }



    void TearDown() override {

        delete env_wrapper;

        delete mock_target_env;

    }

};



TEST_F(EnvWrapperTest, NewRandomAccessFile_Success_107) {

    RandomAccessFile* random_access_file = nullptr;

    Status status = env_wrapper->NewRandomAccessFile("testfile", &random_access_file);

    EXPECT_TRUE(status.ok());

    // Assuming the mock_target_env returns a non-null pointer on success

    EXPECT_NE(random_access_file, nullptr);

}



TEST_F(EnvWrapperTest, NewRandomAccessFile_FileNotFound_107) {

    RandomAccessFile* random_access_file = nullptr;

    Status status = env_wrapper->NewRandomAccessFile("nonexistentfile", &random_access_file);

    EXPECT_TRUE(!status.ok());

    EXPECT_EQ(random_access_file, nullptr);

}



TEST_F(EnvWrapperTest, NewRandomAccessFile_NullPointer_107) {

    RandomAccessFile* random_access_file = nullptr;

    Status status = env_wrapper->NewRandomAccessFile("testfile", nullptr);

    EXPECT_TRUE(!status.ok());

    // Assuming the mock_target_env returns an error when passed a null pointer

}



TEST_F(EnvWrapperTest, NewRandomAccessFile_EmptyFileName_107) {

    RandomAccessFile* random_access_file = nullptr;

    Status status = env_wrapper->NewRandomAccessFile("", &random_access_file);

    EXPECT_TRUE(!status.ok());

    EXPECT_EQ(random_access_file, nullptr);

}
