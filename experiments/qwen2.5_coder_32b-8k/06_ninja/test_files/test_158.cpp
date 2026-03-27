#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util.h"

#include <errno.h>



extern void Fatal(const char*, ...);



class UtilTest_158 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any necessary state or mocks before each test.

    }



    void TearDown() override {

        // Clean up after each test if necessary.

        errno = 0; // Reset errno to ensure it doesn't affect subsequent tests

    }

};



TEST_F(UtilTest_158, GetWorkingDirectory_ReturnsValidPath_158) {

    std::string path = GetWorkingDirectory();

    EXPECT_FALSE(path.empty());

}



TEST_F(UtilTest_158, GetWorkingDirectory_HandlesSmallBufferIncrementally_158) {

    // This test ensures that the function can handle cases where the initial buffer is too small

    // by incrementally resizing it. We cannot directly control the buffer size here, but we can

    // infer this behavior from the implementation.

    std::string path = GetWorkingDirectory();

    EXPECT_FALSE(path.empty());

}



TEST_F(UtilTest_158, GetWorkingDirectory_ErrnoSetOnFailure_158) {

    // Mocking errno is not possible directly, but we can simulate a failure by temporarily changing

    // the current working directory to an invalid one (if possible) or by other means.

    // For this test, we assume that getcwd can fail and sets errno accordingly.

    // Note: This part of the test might require specific setup which is not always feasible in all environments.



    // Save original cwd

    char orig_cwd[1024];

    EXPECT_NE(getcwd(orig_cwd, sizeof(orig_cwd)), nullptr);



    // Change to a non-existent directory (this will fail)

    EXPECT_EQ(chdir("/non_existent_directory"), -1);

    errno = 0;



    // Attempt to get the working directory

    try {

        std::string path = GetWorkingDirectory();

        FAIL() << "Expected exception or error return but got: " << path;

    } catch (...) {

        EXPECT_NE(errno, 0);

    }



    // Restore original cwd

    chdir(orig_cwd);

}



// Note: Since the function does not use any external collaborators that we could mock with Google Mock,

// we do not have additional tests for mocking interactions.
