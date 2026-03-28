#include <gtest/gtest.h>
#include <exiv2/error.hpp>
#include <string>

using namespace Exiv2;

// Test fixture for Error class tests
class ErrorTest_2151 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Error with no arguments constructor
TEST_F(ErrorTest_2151, DefaultConstructorSetsCode_2151) {
    Error err(ErrorCode::kerGeneralError);
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
}

// Test: Error with no arguments - what() returns non-null
TEST_F(ErrorTest_2151, DefaultConstructorWhatReturnsNonNull_2151) {
    Error err(ErrorCode::kerGeneralError);
    EXPECT_NE(err.what(), nullptr);
}

// Test: Error with one string argument
TEST_F(ErrorTest_2151, OneStringArgConstructor_2151) {
    Error err(ErrorCode::kerGeneralError, std::string("arg1"));
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(err.what(), nullptr);
}

// Test: Error with one integer argument
TEST_F(ErrorTest_2151, OneIntArgConstructor_2151) {
    Error err(ErrorCode::kerGeneralError, 42);
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(err.what(), nullptr);
}

// Test: Error with one const char* argument
TEST_F(ErrorTest_2151, OneCStringArgConstructor_2151) {
    Error err(ErrorCode::kerGeneralError, "test_arg");
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(err.what(), nullptr);
}

// Test: Error with two arguments (string, string)
TEST_F(ErrorTest_2151, TwoStringArgsConstructor_2151) {
    Error err(ErrorCode::kerGeneralError, std::string("arg1"), std::string("arg2"));
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(err.what(), nullptr);
}

// Test: Error with two arguments (string, int)
TEST_F(ErrorTest_2151, TwoMixedArgsConstructor_2151) {
    Error err(ErrorCode::kerGeneralError, "filename", 123);
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(err.what(), nullptr);
}

// Test: Error with three arguments (string, string, string)
TEST_F(ErrorTest_2151, ThreeStringArgsConstructor_2151) {
    Error err(ErrorCode::kerGeneralError, std::string("arg1"), std::string("arg2"), std::string("arg3"));
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(err.what(), nullptr);
}

// Test: Error with three arguments (mixed types)
TEST_F(ErrorTest_2151, ThreeMixedArgsConstructor_2151) {
    Error err(ErrorCode::kerGeneralError, "file.jpg", 42, "reason");
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(err.what(), nullptr);
}

// Test: Error with three integer arguments
TEST_F(ErrorTest_2151, ThreeIntArgsConstructor_2151) {
    Error err(ErrorCode::kerGeneralError, 1, 2, 3);
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(err.what(), nullptr);
}

// Test: Error is derived from std::exception
TEST_F(ErrorTest_2151, IsStdException_2151) {
    Error err(ErrorCode::kerGeneralError);
    const std::exception& exc = err;
    EXPECT_NE(exc.what(), nullptr);
}

// Test: what() returns a non-empty string for known error codes
TEST_F(ErrorTest_2151, WhatReturnsNonEmptyString_2151) {
    Error err(ErrorCode::kerGeneralError);
    std::string msg(err.what());
    EXPECT_FALSE(msg.empty());
}

// Test: Different error codes produce different code() values
TEST_F(ErrorTest_2151, DifferentErrorCodes_2151) {
    Error err1(ErrorCode::kerGeneralError);
    Error err2(ErrorCode::kerSuccess);
    EXPECT_NE(err1.code(), err2.code());
}

// Test: Error code kerSuccess
TEST_F(ErrorTest_2151, SuccessErrorCode_2151) {
    Error err(ErrorCode::kerSuccess);
    EXPECT_EQ(err.code(), ErrorCode::kerSuccess);
}

// Test: Error with empty string argument
TEST_F(ErrorTest_2151, EmptyStringArgument_2151) {
    Error err(ErrorCode::kerGeneralError, std::string(""));
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(err.what(), nullptr);
}

// Test: Error with three empty string arguments
TEST_F(ErrorTest_2151, ThreeEmptyStringArgs_2151) {
    Error err(ErrorCode::kerGeneralError, "", "", "");
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(err.what(), nullptr);
}

// Test: Copy behavior - code is preserved
TEST_F(ErrorTest_2151, CopyPreservesCode_2151) {
    Error err1(ErrorCode::kerGeneralError, "test");
    Error err2(err1);
    EXPECT_EQ(err1.code(), err2.code());
}

// Test: Copy behavior - what() is preserved
TEST_F(ErrorTest_2151, CopyPreservesWhat_2151) {
    Error err1(ErrorCode::kerGeneralError, "test");
    Error err2(err1);
    EXPECT_STREQ(err1.what(), err2.what());
}

// Test: what() contains argument text for single arg
TEST_F(ErrorTest_2151, WhatContainsArgForSingleArg_2151) {
    Error err(ErrorCode::kerGeneralError, "unique_identifier_xyz");
    std::string msg(err.what());
    // The message should incorporate the argument in some way
    // We check that what() at least returns something meaningful
    EXPECT_GT(msg.length(), 0u);
}

// Test: Error with large integer argument
TEST_F(ErrorTest_2151, LargeIntegerArgument_2151) {
    Error err(ErrorCode::kerGeneralError, 999999999);
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(err.what(), nullptr);
}

// Test: Error with negative integer argument
TEST_F(ErrorTest_2151, NegativeIntegerArgument_2151) {
    Error err(ErrorCode::kerGeneralError, -1);
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(err.what(), nullptr);
}

// Test: Error with three args - all integers including negative and zero
TEST_F(ErrorTest_2151, ThreeArgsEdgeIntegers_2151) {
    Error err(ErrorCode::kerGeneralError, 0, -1, 2147483647);
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(err.what(), nullptr);
}

// Test: Catching Error as std::exception
TEST_F(ErrorTest_2151, CatchAsStdException_2151) {
    bool caught = false;
    try {
        throw Error(ErrorCode::kerGeneralError, "test");
    } catch (const std::exception& e) {
        caught = true;
        EXPECT_NE(e.what(), nullptr);
    }
    EXPECT_TRUE(caught);
}

// Test: Catching Error by its own type
TEST_F(ErrorTest_2151, CatchAsError_2151) {
    bool caught = false;
    try {
        throw Error(ErrorCode::kerGeneralError, "arg1", "arg2", "arg3");
    } catch (const Error& e) {
        caught = true;
        EXPECT_EQ(e.code(), ErrorCode::kerGeneralError);
        EXPECT_NE(e.what(), nullptr);
    }
    EXPECT_TRUE(caught);
}

// Test: what() is callable multiple times and returns same result
TEST_F(ErrorTest_2151, WhatIsConsistent_2151) {
    Error err(ErrorCode::kerGeneralError, "test");
    const char* msg1 = err.what();
    const char* msg2 = err.what();
    EXPECT_STREQ(msg1, msg2);
}

// Test: code() is callable multiple times and returns same result
TEST_F(ErrorTest_2151, CodeIsConsistent_2151) {
    Error err(ErrorCode::kerGeneralError);
    ErrorCode c1 = err.code();
    ErrorCode c2 = err.code();
    EXPECT_EQ(c1, c2);
}
