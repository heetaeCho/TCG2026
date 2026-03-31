#include <gtest/gtest.h>
#include <exiv2/error.hpp>
#include <string>

using namespace Exiv2;

class ErrorTest_2150 : public ::testing::Test {
protected:
};

// Test construction with two string arguments
TEST_F(ErrorTest_2150, ConstructWithTwoStringArgs_2150) {
  Error err(ErrorCode::kerGeneralError, std::string("arg1"), std::string("arg2"));
  EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(err.what(), nullptr);
}

// Test construction with two C-string arguments
TEST_F(ErrorTest_2150, ConstructWithTwoCStringArgs_2150) {
  Error err(ErrorCode::kerGeneralError, "first", "second");
  EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(err.what(), nullptr);
}

// Test construction with mixed argument types (string and int)
TEST_F(ErrorTest_2150, ConstructWithStringAndIntArgs_2150) {
  Error err(ErrorCode::kerGeneralError, "filename", 42);
  EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(err.what(), nullptr);
}

// Test construction with two integer arguments
TEST_F(ErrorTest_2150, ConstructWithTwoIntArgs_2150) {
  Error err(ErrorCode::kerGeneralError, 100, 200);
  EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(err.what(), nullptr);
}

// Test that what() returns a non-empty string
TEST_F(ErrorTest_2150, WhatReturnsNonEmptyString_2150) {
  Error err(ErrorCode::kerGeneralError, "arg1", "arg2");
  const char* msg = err.what();
  EXPECT_NE(msg, nullptr);
  EXPECT_GT(std::strlen(msg), 0u);
}

// Test that Error is derived from std::exception
TEST_F(ErrorTest_2150, ErrorIsDerivedFromStdException_2150) {
  Error err(ErrorCode::kerGeneralError, "test", "args");
  const std::exception& ex = err;
  EXPECT_NE(ex.what(), nullptr);
}

// Test with single argument constructor
TEST_F(ErrorTest_2150, ConstructWithSingleArg_2150) {
  Error err(ErrorCode::kerGeneralError);
  EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(err.what(), nullptr);
}

// Test with single template argument constructor
TEST_F(ErrorTest_2150, ConstructWithOneTemplateArg_2150) {
  Error err(ErrorCode::kerGeneralError, "single_arg");
  EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(err.what(), nullptr);
}

// Test with three template arguments
TEST_F(ErrorTest_2150, ConstructWithThreeArgs_2150) {
  Error err(ErrorCode::kerGeneralError, "a1", "a2", "a3");
  EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(err.what(), nullptr);
}

// Test code() is noexcept
TEST_F(ErrorTest_2150, CodeIsNoexcept_2150) {
  Error err(ErrorCode::kerGeneralError, "x", "y");
  EXPECT_TRUE(noexcept(err.code()));
}

// Test what() is noexcept
TEST_F(ErrorTest_2150, WhatIsNoexcept_2150) {
  Error err(ErrorCode::kerGeneralError, "x", "y");
  EXPECT_TRUE(noexcept(err.what()));
}

// Test with empty string arguments
TEST_F(ErrorTest_2150, ConstructWithEmptyStringArgs_2150) {
  Error err(ErrorCode::kerGeneralError, "", "");
  EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(err.what(), nullptr);
}

// Test with different error codes
TEST_F(ErrorTest_2150, DifferentErrorCodes_2150) {
  Error err1(ErrorCode::kerSuccess, "a", "b");
  EXPECT_EQ(err1.code(), ErrorCode::kerSuccess);

  Error err2(ErrorCode::kerErrorMessage, "a", "b");
  EXPECT_EQ(err2.code(), ErrorCode::kerErrorMessage);
}

// Test that what() message contains argument information for two-arg constructor
TEST_F(ErrorTest_2150, WhatMessageContentTwoArgs_2150) {
  Error err(ErrorCode::kerGeneralError, "testfile.jpg", "permission denied");
  const char* msg = err.what();
  EXPECT_NE(msg, nullptr);
  // The message should be meaningful and non-empty
  EXPECT_GT(std::strlen(msg), 0u);
}

// Test copy behavior
TEST_F(ErrorTest_2150, CopyConstructor_2150) {
  Error err1(ErrorCode::kerGeneralError, "arg1", "arg2");
  Error err2(err1);
  EXPECT_EQ(err1.code(), err2.code());
  EXPECT_STREQ(err1.what(), err2.what());
}

// Test with int and string mixed arguments
TEST_F(ErrorTest_2150, ConstructWithIntAndString_2150) {
  Error err(ErrorCode::kerGeneralError, 123, "error_detail");
  EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(err.what(), nullptr);
}

// Test throwing and catching as std::exception
TEST_F(ErrorTest_2150, ThrowAndCatchAsException_2150) {
  bool caught = false;
  try {
    throw Error(ErrorCode::kerGeneralError, "file", "reason");
  } catch (const std::exception& e) {
    caught = true;
    EXPECT_NE(e.what(), nullptr);
  }
  EXPECT_TRUE(caught);
}

// Test throwing and catching as Error
TEST_F(ErrorTest_2150, ThrowAndCatchAsError_2150) {
  bool caught = false;
  try {
    throw Error(ErrorCode::kerGeneralError, "file", "reason");
  } catch (const Error& e) {
    caught = true;
    EXPECT_EQ(e.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(e.what(), nullptr);
  }
  EXPECT_TRUE(caught);
}

// Test with large string arguments
TEST_F(ErrorTest_2150, ConstructWithLargeStringArgs_2150) {
  std::string largeStr1(10000, 'A');
  std::string largeStr2(10000, 'B');
  Error err(ErrorCode::kerGeneralError, largeStr1, largeStr2);
  EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(err.what(), nullptr);
}
