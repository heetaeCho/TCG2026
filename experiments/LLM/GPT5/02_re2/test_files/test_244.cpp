// File: re2_programsize_test_244.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

class RE2_ProgramSizeTest_244 : public ::testing::Test {};

// Normal operation: valid pattern should compile; ProgramSize() should be non-negative.
TEST_F(RE2_ProgramSizeTest_244, ValidPattern_ReturnsNonNegative_244) {
  RE2 re("abc");               // simple, valid regex
  EXPECT_TRUE(re.ok()) << "Expected a valid RE2 object for a valid pattern";
  // We intentionally avoid asserting an exact size; only that it's not the sentinel -1.
  EXPECT_GE(re.ProgramSize(), 0) << "ProgramSize() should be non-negative for a valid compiled program";
}

// Error case: clearly invalid pattern should fail; ProgramSize() should return -1.
TEST_F(RE2_ProgramSizeTest_244, InvalidPattern_ReturnsMinusOne_AndNotOk_244) {
  RE2 re("(");                 // unbalanced parenthesis: invalid regex
  EXPECT_FALSE(re.ok()) << "Expected RE2::ok() to be false for an invalid pattern";
  EXPECT_EQ(re.ProgramSize(), -1) << "ProgramSize() should be -1 when no program is available";
}

// Independence: multiple instances with different validity report independently.
TEST_F(RE2_ProgramSizeTest_244, MultipleInstances_ReportIndependently_244) {
  RE2 good("a+");              // valid
  RE2 bad("(");                // invalid

  ASSERT_TRUE(good.ok());
  ASSERT_FALSE(bad.ok());

  EXPECT_GE(good.ProgramSize(), 0) << "Valid instance should have non-negative ProgramSize()";
  EXPECT_EQ(bad.ProgramSize(), -1) << "Invalid instance should report -1 ProgramSize()";
}
