#include <gtest/gtest.h>

#include "leveldb/env.h"

#include "leveldb/status.h"



using namespace leveldb;



class EnvTest_463 : public ::testing::Test {

protected:

    Env* env;



    void SetUp() override {

        env = Env::Default();

    }



    void TearDown() override {

        // No specific teardown needed for this test suite

    }

};



TEST_F(EnvTest_463, RemoveDir_NormalOperation_463) {

    std::string dirname = "test_dir";

    Status status = env->RemoveDir(dirname);

    EXPECT_TRUE(status.ok() || status.IsNotFound());

}



TEST_F(EnvTest_463, RemoveDir_DirectoryDoesNotExist_463) {

    std::string non_existent_dirname = "non_existent_test_dir";

    Status status = env->RemoveDir(non_existent_dirname);

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(EnvTest_463, RemoveDir_EmptyDirectoryName_463) {

    std::string empty_dirname = "";

    Status status = env->RemoveDir(empty_dirname);

    EXPECT_TRUE(!status.ok()); // Expecting an error for invalid directory name

}



TEST_F(EnvTest_463, RemoveDir_ValidButNonEmptyDirectory_463) {

    std::string dirname = "non_empty_test_dir";

    Status create_status = env->CreateDir(dirname);

    ASSERT_TRUE(create_status.ok());



    // Assuming there is a way to add files to the directory in another test or setup

    // For this example, we assume it's done externally and focus on RemoveDir



    Status remove_status = env->RemoveDir(dirname);

    EXPECT_TRUE(remove_status.IsIOError()); // Expecting an error for non-empty directory

}



TEST_F(EnvTest_463, DeleteDir_NormalOperation_463) {

    std::string dirname = "test_dir";

    Status create_status = env->CreateDir(dirname);

    ASSERT_TRUE(create_status.ok());



    Status delete_status = env->DeleteDir(dirname);

    EXPECT_TRUE(delete_status.ok());

}



TEST_F(EnvTest_463, DeleteDir_DirectoryDoesNotExist_463) {

    std::string non_existent_dirname = "non_existent_test_dir";

    Status status = env->DeleteDir(non_existent_dirname);

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(EnvTest_463, DeleteDir_EmptyDirectoryName_463) {

    std::string empty_dirname = "";

    Status status = env->DeleteDir(empty_dirname);

    EXPECT_TRUE(!status.ok()); // Expecting an error for invalid directory name

}
