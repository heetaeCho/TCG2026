// File: re2_reverse_program_size_test_245.cc

#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

class RE2ReverseProgramSizeTest_245 : public ::testing::Test {};

// [Normal] Valid simple pattern ⇒ non-negative size and stable across calls.
TEST_F(RE2ReverseProgramSizeTest_245, ValidSimplePattern_NonNegativeAndStable_245) {
  RE2 re("a");
  ASSERT_TRUE(re.ok()) << "Construction should succeed for a simple valid pattern";
  int size1 = re.ReverseProgramSize();
  EXPECT_GE(size1, 0);
  int size2 = re.ReverseProgramSize();
  EXPECT_EQ(size1, size2) << "Result should be deterministic for the same instance";
}

// [Boundary] Empty pattern is valid in RE2 ⇒ non-negative size.
TEST_F(RE2ReverseProgramSizeTest_245, EmptyPattern_NonNegative_245) {
  RE2 re("");
  ASSERT_TRUE(re.ok()) << "Empty pattern should be a valid regex";
  EXPECT_GE(re.ReverseProgramSize(), 0);
}

// [Exceptional] Invalid pattern (unbalanced parenthesis) ⇒ ok()==false and -1 size.
TEST_F(RE2ReverseProgramSizeTest_245, InvalidPattern_ReturnsMinusOne_245) {
  RE2 re("(");  // Unbalanced, expected to be invalid
  ASSERT_FALSE(re.ok()) << "Invalid pattern should be reported via ok()==false";
  EXPECT_EQ(-1, re.ReverseProgramSize());
}

// [Sanity] Different valid patterns ⇒ calls succeed and return non-negative values.
// (No assumptions about relative sizes.)
TEST_F(RE2ReverseProgramSizeTest_245, DifferentValidPatterns_NonNegative_245) {
  RE2 re1("a");
  RE2 re2("a|b");
  ASSERT_TRUE(re1.ok());
  ASSERT_TRUE(re2.ok());

  int s1 = re1.ReverseProgramSize();
  int s2 = re2.ReverseProgramSize();

  EXPECT_GE(s1, 0);
  EXPECT_GE(s2, 0);
  // No assertion about s1 vs s2: we avoid inferring internal logic.
}
