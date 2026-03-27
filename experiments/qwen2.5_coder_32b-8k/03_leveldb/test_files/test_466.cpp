#include <gtest/gtest.h>

#include "leveldb/env.h"



using namespace leveldb;



class EnvTest_466 : public ::testing::Test {

protected:

    Env* env;



    void SetUp() override {

        env = Env::Default();

    }



    void TearDown() override {

        // No need to delete the default environment

    }

};



TEST_F(EnvTest_466, DeleteFile_NormalOperation_466) {

    std::string testFilePath = "testfile.txt";

    Status status = env->DeleteFile(testFilePath);

    EXPECT_TRUE(status.ok());

}



TEST_F(EnvTest_466, DeleteFile_FileDoesNotExist_466) {

    std::string nonExistentFilePath = "nonexistentfile.txt";

    Status status = env->DeleteFile(nonExistentFilePath);

    EXPECT_FALSE(status.ok());

}



TEST_F(EnvTest_466, DeleteFile_EmptyFileName_466) {

    std::string emptyFilePath = "";

    Status status = env->DeleteFile(emptyFilePath);

    EXPECT_FALSE(status.ok());

}
