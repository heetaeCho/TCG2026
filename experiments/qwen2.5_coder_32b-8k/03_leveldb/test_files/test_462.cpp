#include <gtest/gtest.h>

#include "leveldb/env.h"

#include "leveldb/status.h"



using namespace leveldb;



class EnvTest_462 : public ::testing::Test {

protected:

    Env* env_;

    

    void SetUp() override {

        env_ = Env::Default();

    }

};



TEST_F(EnvTest_462, NewAppendableFile_ReturnsNotSupportedStatus_462) {

    WritableFile* file = nullptr;

    Status status = env_->NewAppendableFile("test_file", &file);

    

    EXPECT_TRUE(status.IsNotSupportedError());

    EXPECT_EQ(file, nullptr);

}



TEST_F(EnvTest_462, NewAppendableFile_ReturnsNonOkStatus_462) {

    WritableFile* file = nullptr;

    Status status = env_->NewAppendableFile("", &file);  // Edge case with empty filename

    

    EXPECT_FALSE(status.ok());

    EXPECT_EQ(file, nullptr);

}



TEST_F(EnvTest_462, NewAppendableFile_NullptrResult_ReturnsNonOkStatus_462) {

    Status status = env_->NewAppendableFile("test_file", nullptr);  // Edge case with null result pointer

    

    EXPECT_FALSE(status.ok());

}
