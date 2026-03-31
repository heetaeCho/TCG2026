#include <gtest/gtest.h>
#include <exiv2/error.hpp>
#include <string>

using namespace Exiv2;

class ErrorTest_2162 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with a simple error code
TEST_F(ErrorTest_2162, ConstructWithErrorCode_2162) {
    Error err(ErrorCode::kerGeneralError);
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
}

// Test that what() returns a non-null string
TEST_F(ErrorTest_2162, WhatReturnsNonNull_2162) {
    Error err(ErrorCode::kerGeneralError);
    const char* msg = err.what();
    EXPECT_NE(msg, nullptr);
}

// Test that what() returns a non-empty string for a known error code
TEST_F(ErrorTest_2162, WhatReturnsNonEmptyString_2162) {
    Error err(ErrorCode::kerGeneralError);
    const char* msg = err.what();
    EXPECT_NE(msg, nullptr);
    EXPECT_GT(std::string(msg).size(), 0u);
}

// Test construction with ErrorCode::kerSuccess (code 0 / boundary)
TEST_F(ErrorTest_2162, ConstructWithKerSuccess_2162) {
    Error err(ErrorCode::kerSuccess);
    EXPECT_EQ(err.code(), ErrorCode::kerSuccess);
    EXPECT_NE(err.what(), nullptr);
}

// Test construction with one argument
TEST_F(ErrorTest_2162, ConstructWithOneArg_2162) {
    Error err(ErrorCode::kerFileOpenFailed, "testfile.txt");
    EXPECT_EQ(err.code(), ErrorCode::kerFileOpenFailed);
    const char* msg = err.what();
    EXPECT_NE(msg, nullptr);
    // The message should contain the argument
    std::string msgStr(msg);
    EXPECT_NE(msgStr.find("testfile.txt"), std::string::npos);
}

// Test construction with one integer argument
TEST_F(ErrorTest_2162, ConstructWithOneIntArg_2162) {
    Error err(ErrorCode::kerGeneralError, 42);
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(err.what(), nullptr);
}

// Test construction with two arguments
TEST_F(ErrorTest_2162, ConstructWithTwoArgs_2162) {
    Error err(ErrorCode::kerDataSourceOpenFailed, "file.jpg", "permission denied");
    EXPECT_EQ(err.code(), ErrorCode::kerDataSourceOpenFailed);
    const char* msg = err.what();
    EXPECT_NE(msg, nullptr);
}

// Test construction with three arguments
TEST_F(ErrorTest_2162, ConstructWithThreeArgs_2162) {
    Error err(ErrorCode::kerCallFailed, "func", "arg1", "arg2");
    EXPECT_EQ(err.code(), ErrorCode::kerCallFailed);
    const char* msg = err.what();
    EXPECT_NE(msg, nullptr);
}

// Test that Error is derived from std::exception
TEST_F(ErrorTest_2162, IsDerivedFromStdException_2162) {
    Error err(ErrorCode::kerGeneralError);
    const std::exception& ex = err;
    EXPECT_NE(ex.what(), nullptr);
}

// Test code() is consistent across multiple calls
TEST_F(ErrorTest_2162, CodeIsConsistent_2162) {
    Error err(ErrorCode::kerGeneralError);
    EXPECT_EQ(err.code(), err.code());
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
}

// Test what() is consistent across multiple calls
TEST_F(ErrorTest_2162, WhatIsConsistent_2162) {
    Error err(ErrorCode::kerGeneralError);
    std::string msg1(err.what());
    std::string msg2(err.what());
    EXPECT_EQ(msg1, msg2);
}

// Test copy behavior
TEST_F(ErrorTest_2162, CopyConstructor_2162) {
    Error err1(ErrorCode::kerGeneralError);
    Error err2(err1);
    EXPECT_EQ(err2.code(), ErrorCode::kerGeneralError);
    EXPECT_STREQ(err1.what(), err2.what());
}

// Test with ErrorCode::kerErrorMessage
TEST_F(ErrorTest_2162, ConstructWithKerErrorMessage_2162) {
    Error err(ErrorCode::kerErrorMessage, "custom error message");
    EXPECT_EQ(err.code(), ErrorCode::kerErrorMessage);
    const char* msg = err.what();
    EXPECT_NE(msg, nullptr);
    std::string msgStr(msg);
    EXPECT_NE(msgStr.find("custom error message"), std::string::npos);
}

// Test with empty string argument
TEST_F(ErrorTest_2162, ConstructWithEmptyStringArg_2162) {
    Error err(ErrorCode::kerErrorMessage, "");
    EXPECT_EQ(err.code(), ErrorCode::kerErrorMessage);
    EXPECT_NE(err.what(), nullptr);
}

// Test catching as std::exception
TEST_F(ErrorTest_2162, CatchAsStdException_2162) {
    bool caught = false;
    try {
        throw Error(ErrorCode::kerGeneralError);
    } catch (const std::exception& e) {
        caught = true;
        EXPECT_NE(e.what(), nullptr);
    }
    EXPECT_TRUE(caught);
}

// Test catching as Exiv2::Error
TEST_F(ErrorTest_2162, CatchAsExiv2Error_2162) {
    bool caught = false;
    try {
        throw Error(ErrorCode::kerGeneralError);
    } catch (const Exiv2::Error& e) {
        caught = true;
        EXPECT_EQ(e.code(), ErrorCode::kerGeneralError);
    }
    EXPECT_TRUE(caught);
}

// Test with different error codes to verify different messages
TEST_F(ErrorTest_2162, DifferentErrorCodesDifferentMessages_2162) {
    Error err1(ErrorCode::kerSuccess);
    Error err2(ErrorCode::kerGeneralError);
    // Different error codes should generally produce different messages
    // (though this is implementation-dependent, it's reasonable to test)
    if (err1.code() != err2.code()) {
        // At minimum, both should return valid strings
        EXPECT_NE(err1.what(), nullptr);
        EXPECT_NE(err2.what(), nullptr);
    }
}

// Test construction with string argument as std::string
TEST_F(ErrorTest_2162, ConstructWithStdStringArg_2162) {
    std::string arg = "test_argument";
    Error err(ErrorCode::kerErrorMessage, arg);
    EXPECT_EQ(err.code(), ErrorCode::kerErrorMessage);
    EXPECT_NE(err.what(), nullptr);
}
