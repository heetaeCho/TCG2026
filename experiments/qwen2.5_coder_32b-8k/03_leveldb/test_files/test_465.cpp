#include <gtest/gtest.h>

#include "leveldb/env.h"

#include "leveldb/status.h"



using namespace leveldb;



class EnvTest_465 : public ::testing::Test {

protected:

    Env* env_;



    void SetUp() override {

        env_ = Env::Default();

    }



    void TearDown() override {

        // No need to clean up the default environment

    }

};



TEST_F(EnvTest_465, RemoveFile_NonExistentFile_465) {

    Status status = env_->RemoveFile("non_existent_file.txt");

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(EnvTest_465, RemoveFile_SuccessfulDeletion_465) {

    // Assuming a file is created beforehand for this test

    std::string test_filename = "test_remove_file_success_465.txt";

    ASSERT_OK(env_->NewWritableFile(test_filename, nullptr));

    Status status = env_->RemoveFile(test_filename);

    EXPECT_OK(status);

}



TEST_F(EnvTest_465, RemoveFile_EmptyFileName_465) {

    Status status = env_->RemoveFile("");

    EXPECT_TRUE(status.IsInvalidArgument());

}



TEST_F(EnvTest_465, RemoveFile_BoundaryConditionFileName_465) {

    // Test with a very long filename

    std::string long_filename(260, 'a'); // Example of a boundary condition for some file systems

    Status status = env_->RemoveFile(long_filename);

    EXPECT_TRUE(status.IsNotFound() || status.IsInvalidArgument());

}
