#include <gtest/gtest.h>
#include <exiv2/error.hpp>
#include <string>

using namespace Exiv2;

// Test basic construction with error code only
TEST(ErrorTest_726, ConstructWithErrorCode_726) {
  Error error(ErrorCode::kerGeneralError);
  EXPECT_EQ(error.code(), ErrorCode::kerGeneralError);
}

// Test that what() returns a non-null string
TEST(ErrorTest_726, WhatReturnsNonNull_726) {
  Error error(ErrorCode::kerGeneralError);
  const char* msg = error.what();
  EXPECT_NE(msg, nullptr);
}

// Test that what() returns a non-empty string for a known error
TEST(ErrorTest_726, WhatReturnsNonEmptyString_726) {
  Error error(ErrorCode::kerGeneralError);
  const char* msg = error.what();
  EXPECT_NE(msg, nullptr);
  EXPECT_GT(std::string(msg).size(), 0u);
}

// Test Error is derived from std::exception
TEST(ErrorTest_726, ErrorIsDerivedFromStdException_726) {
  Error error(ErrorCode::kerGeneralError);
  const std::exception& exc = error;
  EXPECT_NE(exc.what(), nullptr);
}

// Test construction with one argument
TEST(ErrorTest_726, ConstructWithOneArg_726) {
  Error error(ErrorCode::kerFileOpenFailed, "test_file.txt");
  EXPECT_EQ(error.code(), ErrorCode::kerFileOpenFailed);
  const char* msg = error.what();
  EXPECT_NE(msg, nullptr);
  // The message should contain the argument
  std::string msgStr(msg);
  EXPECT_NE(msgStr.find("test_file.txt"), std::string::npos);
}

// Test construction with two arguments
TEST(ErrorTest_726, ConstructWithTwoArgs_726) {
  Error error(ErrorCode::kerCallFailed, "path/to/file", "some_detail");
  EXPECT_NE(error.what(), nullptr);
}

// Test construction with three arguments
TEST(ErrorTest_726, ConstructWithThreeArgs_726) {
  Error error(ErrorCode::kerCallFailed, "arg1", "arg2", "arg3");
  EXPECT_NE(error.what(), nullptr);
}

// Test construction with integer argument
TEST(ErrorTest_726, ConstructWithIntArg_726) {
  Error error(ErrorCode::kerCallFailed, 42);
  EXPECT_NE(error.what(), nullptr);
}

// Test code() returns the correct error code
TEST(ErrorTest_726, CodeReturnsCorrectCode_726) {
  Error error1(ErrorCode::kerSuccess);
  EXPECT_EQ(error1.code(), ErrorCode::kerSuccess);

  Error error2(ErrorCode::kerGeneralError);
  EXPECT_EQ(error2.code(), ErrorCode::kerGeneralError);

  Error error3(ErrorCode::kerFileOpenFailed);
  EXPECT_EQ(error3.code(), ErrorCode::kerFileOpenFailed);
}

// Test copy construction
TEST(ErrorTest_726, CopyConstruction_726) {
  Error original(ErrorCode::kerGeneralError);
  Error copy(original);
  EXPECT_EQ(copy.code(), original.code());
  EXPECT_STREQ(copy.what(), original.what());
}

// Test that error can be caught as std::exception
TEST(ErrorTest_726, CatchAsStdException_726) {
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
TEST(ErrorTest_726, CatchAsExiv2Error_726) {
  bool caught = false;
  try {
    throw Error(ErrorCode::kerGeneralError);
  } catch (const Error& e) {
    caught = true;
    EXPECT_EQ(e.code(), ErrorCode::kerGeneralError);
    EXPECT_NE(e.what(), nullptr);
  }
  EXPECT_TRUE(caught);
}

// Test different error codes produce different messages
TEST(ErrorTest_726, DifferentCodesProduceDifferentMessages_726) {
  Error error1(ErrorCode::kerGeneralError);
  Error error2(ErrorCode::kerFileOpenFailed, "file.txt");
  // Different error codes should generally produce different messages
  std::string msg1(error1.what());
  std::string msg2(error2.what());
  EXPECT_NE(msg1, msg2);
}

// Test what() is noexcept
TEST(ErrorTest_726, WhatIsNoexcept_726) {
  Error error(ErrorCode::kerGeneralError);
  EXPECT_TRUE(noexcept(error.what()));
}

// Test code() is noexcept
TEST(ErrorTest_726, CodeIsNoexcept_726) {
  Error error(ErrorCode::kerGeneralError);
  EXPECT_TRUE(noexcept(error.code()));
}

// Test with empty string argument
TEST(ErrorTest_726, ConstructWithEmptyStringArg_726) {
  Error error(ErrorCode::kerFileOpenFailed, "");
  EXPECT_EQ(error.code(), ErrorCode::kerFileOpenFailed);
  EXPECT_NE(error.what(), nullptr);
}

// Test with long string argument
TEST(ErrorTest_726, ConstructWithLongStringArg_726) {
  std::string longStr(1000, 'x');
  Error error(ErrorCode::kerFileOpenFailed, longStr);
  EXPECT_EQ(error.code(), ErrorCode::kerFileOpenFailed);
  EXPECT_NE(error.what(), nullptr);
}

// Test success error code
TEST(ErrorTest_726, SuccessErrorCode_726) {
  Error error(ErrorCode::kerSuccess);
  EXPECT_EQ(error.code(), ErrorCode::kerSuccess);
  EXPECT_NE(error.what(), nullptr);
}

// Test multiple calls to what() return consistent result
TEST(ErrorTest_726, WhatIsConsistent_726) {
  Error error(ErrorCode::kerGeneralError);
  const char* msg1 = error.what();
  const char* msg2 = error.what();
  EXPECT_STREQ(msg1, msg2);
}
