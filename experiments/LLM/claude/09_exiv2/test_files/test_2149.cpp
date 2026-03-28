#include <gtest/gtest.h>
#include <exiv2/error.hpp>
#include <string>
#include <stdexcept>

using namespace Exiv2;

// Test fixture for Error class tests
class ErrorTest_2149 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with just an error code
TEST_F(ErrorTest_2149, ConstructWithErrorCodeOnly_2149) {
    Error err(ErrorCode::kerGeneralError);
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
}

// Test that what() returns a non-null string
TEST_F(ErrorTest_2149, WhatReturnsNonNull_2149) {
    Error err(ErrorCode::kerGeneralError);
    const char* msg = err.what();
    EXPECT_NE(msg, nullptr);
}

// Test construction with one string argument
TEST_F(ErrorTest_2149, ConstructWithOneStringArg_2149) {
    Error err(ErrorCode::kerFileOpenFailed, std::string("testfile.txt"));
    EXPECT_EQ(err.code(), ErrorCode::kerFileOpenFailed);
    EXPECT_NE(err.what(), nullptr);
}

// Test construction with one const char* argument
TEST_F(ErrorTest_2149, ConstructWithOneConstCharArg_2149) {
    Error err(ErrorCode::kerFileOpenFailed, "testfile.txt");
    EXPECT_EQ(err.code(), ErrorCode::kerFileOpenFailed);
    EXPECT_NE(err.what(), nullptr);
}

// Test construction with one integer argument
TEST_F(ErrorTest_2149, ConstructWithOneIntArg_2149) {
    Error err(ErrorCode::kerCallFailed, 42);
    EXPECT_EQ(err.code(), ErrorCode::kerCallFailed);
    EXPECT_NE(err.what(), nullptr);
}

// Test construction with two arguments
TEST_F(ErrorTest_2149, ConstructWithTwoArgs_2149) {
    Error err(ErrorCode::kerDataSourceOpenFailed, "file.jpg", "permission denied");
    EXPECT_EQ(err.code(), ErrorCode::kerDataSourceOpenFailed);
    EXPECT_NE(err.what(), nullptr);
}

// Test construction with three arguments
TEST_F(ErrorTest_2149, ConstructWithThreeArgs_2149) {
    Error err(ErrorCode::kerInvalidMalloc, "arg1", "arg2", "arg3");
    EXPECT_EQ(err.code(), ErrorCode::kerInvalidMalloc);
    EXPECT_NE(err.what(), nullptr);
}

// Test that Error is derived from std::exception
TEST_F(ErrorTest_2149, ErrorIsDerivedFromStdException_2149) {
    Error err(ErrorCode::kerGeneralError);
    const std::exception& ex = err;
    EXPECT_NE(ex.what(), nullptr);
}

// Test that what() message is non-empty for known error codes
TEST_F(ErrorTest_2149, WhatMessageNonEmpty_2149) {
    Error err(ErrorCode::kerGeneralError);
    std::string msg(err.what());
    EXPECT_FALSE(msg.empty());
}

// Test that code() returns the correct code for different error codes
TEST_F(ErrorTest_2149, CodeReturnsCorrectValueForDifferentCodes_2149) {
    {
        Error err(ErrorCode::kerSuccess);
        EXPECT_EQ(err.code(), ErrorCode::kerSuccess);
    }
    {
        Error err(ErrorCode::kerGeneralError);
        EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
    }
    {
        Error err(ErrorCode::kerErrorMessage, "some message");
        EXPECT_EQ(err.code(), ErrorCode::kerErrorMessage);
    }
}

// Test that the what() message contains the argument when applicable
TEST_F(ErrorTest_2149, WhatContainsArgument_2149) {
    Error err(ErrorCode::kerErrorMessage, "specific_error_text");
    std::string msg(err.what());
    // The error message should contain the argument passed
    EXPECT_NE(msg.find("specific_error_text"), std::string::npos);
}

// Test that Error can be caught as std::exception
TEST_F(ErrorTest_2149, CanBeCaughtAsStdException_2149) {
    bool caught = false;
    try {
        throw Error(ErrorCode::kerGeneralError);
    } catch (const std::exception& ex) {
        caught = true;
        EXPECT_NE(ex.what(), nullptr);
    }
    EXPECT_TRUE(caught);
}

// Test that Error can be caught as Exiv2::Error
TEST_F(ErrorTest_2149, CanBeCaughtAsExiv2Error_2149) {
    bool caught = false;
    try {
        throw Error(ErrorCode::kerFileOpenFailed, "myfile.jpg");
    } catch (const Error& err) {
        caught = true;
        EXPECT_EQ(err.code(), ErrorCode::kerFileOpenFailed);
    }
    EXPECT_TRUE(caught);
}

// Test copy behavior
TEST_F(ErrorTest_2149, CopyPreservesCodeAndMessage_2149) {
    Error err1(ErrorCode::kerErrorMessage, "copy test");
    Error err2(err1);
    EXPECT_EQ(err1.code(), err2.code());
    EXPECT_STREQ(err1.what(), err2.what());
}

// Test with empty string argument
TEST_F(ErrorTest_2149, ConstructWithEmptyStringArg_2149) {
    Error err(ErrorCode::kerErrorMessage, "");
    EXPECT_EQ(err.code(), ErrorCode::kerErrorMessage);
    EXPECT_NE(err.what(), nullptr);
}

// Test with numeric argument types
TEST_F(ErrorTest_2149, ConstructWithLongArg_2149) {
    Error err(ErrorCode::kerCallFailed, 123456789L);
    EXPECT_EQ(err.code(), ErrorCode::kerCallFailed);
    EXPECT_NE(err.what(), nullptr);
}

// Test code() is noexcept
TEST_F(ErrorTest_2149, CodeIsNoexcept_2149) {
    Error err(ErrorCode::kerGeneralError);
    EXPECT_TRUE(noexcept(err.code()));
}

// Test what() is noexcept
TEST_F(ErrorTest_2149, WhatIsNoexcept_2149) {
    Error err(ErrorCode::kerGeneralError);
    EXPECT_TRUE(noexcept(err.what()));
}

// Test with two string arguments
TEST_F(ErrorTest_2149, ConstructWithTwoStringArgs_2149) {
    Error err(ErrorCode::kerDataSourceOpenFailed, std::string("file"), std::string("reason"));
    EXPECT_EQ(err.code(), ErrorCode::kerDataSourceOpenFailed);
    EXPECT_NE(err.what(), nullptr);
}

// Test with mixed argument types
TEST_F(ErrorTest_2149, ConstructWithMixedArgTypes_2149) {
    Error err(ErrorCode::kerDataSourceOpenFailed, "filename", 404);
    EXPECT_EQ(err.code(), ErrorCode::kerDataSourceOpenFailed);
    EXPECT_NE(err.what(), nullptr);
}
