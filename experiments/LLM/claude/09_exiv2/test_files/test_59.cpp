#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "exiv2/error.hpp"

using namespace Exiv2;

// Test construction with ErrorCode only
TEST(ErrorTest_59, ConstructWithErrorCodeOnly_59) {
  Error error(ErrorCode::kerGeneralError);
  EXPECT_EQ(error.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(error.what(), nullptr);
}

// Test construction with one argument
TEST(ErrorTest_59, ConstructWithOneArg_59) {
  Error error(ErrorCode::kerGeneralError, "arg1");
  EXPECT_EQ(error.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(error.what(), nullptr);
}

// Test construction with two arguments
TEST(ErrorTest_59, ConstructWithTwoArgs_59) {
  Error error(ErrorCode::kerGeneralError, "arg1", "arg2");
  EXPECT_EQ(error.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(error.what(), nullptr);
}

// Test construction with three arguments
TEST(ErrorTest_59, ConstructWithThreeArgs_59) {
  Error error(ErrorCode::kerGeneralError, "arg1", "arg2", "arg3");
  EXPECT_EQ(error.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(error.what(), nullptr);
}

// Test that Error is derived from std::exception
TEST(ErrorTest_59, InheritsFromStdException_59) {
  Error error(ErrorCode::kerGeneralError);
  const std::exception& ex = error;
  EXPECT_NE(ex.what(), nullptr);
}

// Test what() returns a non-empty string
TEST(ErrorTest_59, WhatReturnsNonEmptyString_59) {
  Error error(ErrorCode::kerGeneralError);
  std::string msg = error.what();
  EXPECT_FALSE(msg.empty());
}

// Test operator<< outputs what()
TEST(ErrorTest_59, StreamOperatorOutputsWhat_59) {
  Error error(ErrorCode::kerGeneralError);
  std::ostringstream oss;
  oss << error;
  std::string output = oss.str();
  std::string whatStr = error.what();
  EXPECT_EQ(output, whatStr);
}

// Test construction with integer argument
TEST(ErrorTest_59, ConstructWithIntArg_59) {
  Error error(ErrorCode::kerGeneralError, 42);
  EXPECT_EQ(error.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(error.what(), nullptr);
}

// Test construction with mixed argument types
TEST(ErrorTest_59, ConstructWithMixedArgTypes_59) {
  Error error(ErrorCode::kerGeneralError, 42, "string_arg");
  EXPECT_EQ(error.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(error.what(), nullptr);
}

// Test construction with three mixed argument types
TEST(ErrorTest_59, ConstructWithThreeMixedArgTypes_59) {
  Error error(ErrorCode::kerGeneralError, 1, "two", 3);
  EXPECT_EQ(error.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(error.what(), nullptr);
}

// Test different error codes
TEST(ErrorTest_59, DifferentErrorCodes_59) {
  Error error1(ErrorCode::kerSuccess);
  EXPECT_EQ(error1.code(), ErrorCode::kerSuccess);

  Error error2(ErrorCode::kerErrorMessage);
  EXPECT_EQ(error2.code(), ErrorCode::kerErrorMessage);
}

// Test that code() is noexcept
TEST(ErrorTest_59, CodeIsNoexcept_59) {
  Error error(ErrorCode::kerGeneralError);
  EXPECT_TRUE(noexcept(error.code()));
}

// Test that what() is noexcept
TEST(ErrorTest_59, WhatIsNoexcept_59) {
  Error error(ErrorCode::kerGeneralError);
  EXPECT_TRUE(noexcept(error.what()));
}

// Test error can be caught as std::exception
TEST(ErrorTest_59, CatchAsStdException_59) {
  bool caught = false;
  try {
    throw Error(ErrorCode::kerGeneralError);
  } catch (const std::exception& ex) {
    caught = true;
    EXPECT_NE(ex.what(), nullptr);
  }
  EXPECT_TRUE(caught);
}

// Test error can be caught as Error
TEST(ErrorTest_59, CatchAsError_59) {
  bool caught = false;
  try {
    throw Error(ErrorCode::kerGeneralError, "test_message");
  } catch (const Error& err) {
    caught = true;
    EXPECT_EQ(err.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(err.what(), nullptr);
  }
  EXPECT_TRUE(caught);
}

// Test copy semantics
TEST(ErrorTest_59, CopyError_59) {
  Error original(ErrorCode::kerGeneralError, "test");
  Error copy(original);
  EXPECT_EQ(copy.code(), original.code());
  EXPECT_STREQ(copy.what(), original.what());
}

// Test stream operator with empty-ish error
TEST(ErrorTest_59, StreamOperatorConsistency_59) {
  Error error(ErrorCode::kerSuccess);
  std::ostringstream oss;
  oss << error;
  EXPECT_EQ(oss.str(), std::string(error.what()));
}

// Test construction with string argument containing special characters
TEST(ErrorTest_59, SpecialCharacterArgs_59) {
  Error error(ErrorCode::kerGeneralError, "path/to/file.ext", "special chars: !@#$%");
  EXPECT_EQ(error.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(error.what(), nullptr);
}

// Test construction with empty string argument
TEST(ErrorTest_59, EmptyStringArg_59) {
  Error error(ErrorCode::kerGeneralError, "");
  EXPECT_EQ(error.code(), ErrorCode::kerGeneralError);
  EXPECT_NE(error.what(), nullptr);
}

// Test kerFileOpenFailed error code with filename arg
TEST(ErrorTest_59, FileOpenFailedError_59) {
  Error error(ErrorCode::kerFileOpenFailed, "/nonexistent/file.jpg", "r");
  EXPECT_EQ(error.code(), ErrorCode::kerFileOpenFailed);
  EXPECT_NE(error.what(), nullptr);
  std::string msg = error.what();
  EXPECT_FALSE(msg.empty());
}

// Test multiple stream operations
TEST(ErrorTest_59, MultipleStreamOperations_59) {
  Error error(ErrorCode::kerGeneralError, "test");
  std::ostringstream oss1, oss2;
  oss1 << error;
  oss2 << error;
  EXPECT_EQ(oss1.str(), oss2.str());
}

// Test what() called multiple times returns same result
TEST(ErrorTest_59, WhatConsistentAcrossCalls_59) {
  Error error(ErrorCode::kerGeneralError, "consistent");
  std::string first = error.what();
  std::string second = error.what();
  EXPECT_EQ(first, second);
}
