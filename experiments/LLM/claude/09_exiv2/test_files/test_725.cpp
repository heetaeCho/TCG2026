#include <gtest/gtest.h>
#include <exiv2/error.hpp>

using namespace Exiv2;

// Test basic construction with error code only
TEST(ErrorTest_725, ConstructWithErrorCode_725) {
  Error error(ErrorCode::kerGeneralError);
  EXPECT_EQ(error.code(), ErrorCode::kerGeneralError);
}

// Test that code() returns the correct error code for different codes
TEST(ErrorTest_725, CodeReturnsCorrectErrorCode_725) {
  Error error1(ErrorCode::kerSuccess);
  EXPECT_EQ(error1.code(), ErrorCode::kerSuccess);

  Error error2(ErrorCode::kerErrorMessage);
  EXPECT_EQ(error2.code(), ErrorCode::kerErrorMessage);
}

// Test construction with one argument
TEST(ErrorTest_725, ConstructWithOneArg_725) {
  Error error(ErrorCode::kerErrorMessage, "test argument");
  EXPECT_EQ(error.code(), ErrorCode::kerErrorMessage);
  // what() should return a non-null string
  EXPECT_NE(error.what(), nullptr);
}

// Test construction with two arguments
TEST(ErrorTest_725, ConstructWithTwoArgs_725) {
  Error error(ErrorCode::kerErrorMessage, "arg1", "arg2");
  EXPECT_EQ(error.code(), ErrorCode::kerErrorMessage);
  EXPECT_NE(error.what(), nullptr);
}

// Test construction with three arguments
TEST(ErrorTest_725, ConstructWithThreeArgs_725) {
  Error error(ErrorCode::kerErrorMessage, "arg1", "arg2", "arg3");
  EXPECT_EQ(error.code(), ErrorCode::kerErrorMessage);
  EXPECT_NE(error.what(), nullptr);
}

// Test that what() returns a non-null and non-empty string
TEST(ErrorTest_725, WhatReturnsNonNullString_725) {
  Error error(ErrorCode::kerGeneralError);
  const char* msg = error.what();
  EXPECT_NE(msg, nullptr);
  EXPECT_GT(std::strlen(msg), 0u);
}

// Test that Error is derived from std::exception
TEST(ErrorTest_725, ErrorIsDerivedFromException_725) {
  Error error(ErrorCode::kerGeneralError);
  const std::exception& ex = error;
  EXPECT_NE(ex.what(), nullptr);
}

// Test construction with numeric argument
TEST(ErrorTest_725, ConstructWithNumericArg_725) {
  Error error(ErrorCode::kerErrorMessage, 42);
  EXPECT_EQ(error.code(), ErrorCode::kerErrorMessage);
  EXPECT_NE(error.what(), nullptr);
}

// Test that code() is noexcept
TEST(ErrorTest_725, CodeIsNoexcept_725) {
  Error error(ErrorCode::kerGeneralError);
  EXPECT_TRUE(noexcept(error.code()));
}

// Test copy behavior - Error should be copyable as it derives from std::exception
TEST(ErrorTest_725, ErrorIsCopyable_725) {
  Error original(ErrorCode::kerErrorMessage, "copy test");
  Error copy(original);
  EXPECT_EQ(copy.code(), original.code());
  EXPECT_STREQ(copy.what(), original.what());
}

// Test that what() message contains meaningful content for error with argument
TEST(ErrorTest_725, WhatMessageIsConsistent_725) {
  Error error(ErrorCode::kerErrorMessage, "specific_marker");
  const char* msg = error.what();
  EXPECT_NE(msg, nullptr);
  // Calling what() multiple times should return the same string
  EXPECT_STREQ(error.what(), msg);
}

// Test kerSuccess error code
TEST(ErrorTest_725, SuccessErrorCode_725) {
  Error error(ErrorCode::kerSuccess);
  EXPECT_EQ(error.code(), ErrorCode::kerSuccess);
  EXPECT_NE(error.what(), nullptr);
}

// Test that error can be caught as std::exception
TEST(ErrorTest_725, CatchAsStdException_725) {
  bool caught = false;
  try {
    throw Error(ErrorCode::kerGeneralError);
  } catch (const std::exception& e) {
    caught = true;
    EXPECT_NE(e.what(), nullptr);
  }
  EXPECT_TRUE(caught);
}

// Test that error can be caught as Exiv2::Error
TEST(ErrorTest_725, CatchAsExiv2Error_725) {
  bool caught = false;
  try {
    throw Error(ErrorCode::kerGeneralError);
  } catch (const Error& e) {
    caught = true;
    EXPECT_EQ(e.code(), ErrorCode::kerGeneralError);
  }
  EXPECT_TRUE(caught);
}

// Test construction with mixed argument types
TEST(ErrorTest_725, ConstructWithMixedArgTypes_725) {
  Error error(ErrorCode::kerErrorMessage, 123, "string_arg");
  EXPECT_EQ(error.code(), ErrorCode::kerErrorMessage);
  EXPECT_NE(error.what(), nullptr);
}

// Test that what() is const noexcept
TEST(ErrorTest_725, WhatIsConstNoexcept_725) {
  const Error error(ErrorCode::kerGeneralError);
  EXPECT_TRUE(noexcept(error.what()));
  EXPECT_NE(error.what(), nullptr);
}
