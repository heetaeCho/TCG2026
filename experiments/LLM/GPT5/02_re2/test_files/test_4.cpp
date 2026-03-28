// File: re2_error_code_test_4.cc

#include <gtest/gtest.h>
#include <string>
#include "TestProjects/re2/re2/re2.h"

using re2::RE2;

//
// Test fixture (keeps things tidy for future extensions)
//
class RE2ErrorCodeTest_4 : public ::testing::Test {};

// [Normal operation] A valid pattern should compile and expose NoError via error_code().
TEST_F(RE2ErrorCodeTest_4, ValidPattern_ReturnsNoError_4) {
  RE2 re("ab+");
  // Observable behavior: ok() should be true for a valid pattern.
  EXPECT_TRUE(re.ok());
  // Observable behavior: error_code() should indicate no error for a valid pattern.
  EXPECT_EQ(re.error_code(), RE2::NoError);
}

// [Boundary] Empty pattern is a valid regex that matches the empty string.
// It should compile with no error.
TEST_F(RE2ErrorCodeTest_4, EmptyPattern_NoError_4) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.error_code(), RE2::NoError);
}

// [Exceptional / error case] An invalid pattern should fail to compile and set a non-NoError code.
// We don't assert a specific error enum beyond "not NoError" to avoid inferring internal mapping.
TEST_F(RE2ErrorCodeTest_4, InvalidPattern_SetsNonNoError_4) {
  RE2 re("(");  // Unbalanced parenthesis: clearly invalid and externally observable via ok() == false.
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error_code(), RE2::NoError);
}

// [Const-correctness / accessor behavior] error_code() is const and should be callable on a const object.
TEST_F(RE2ErrorCodeTest_4, ErrorCode_AccessibleFromConstObject_4) {
  const RE2 re("a|b");
  // No assumptions beyond callability and stability under const access.
  auto code = re.error_code();
  // If the pattern is valid, it's reasonable and observable to expect NoError.
  EXPECT_EQ(code, RE2::NoError);
}
