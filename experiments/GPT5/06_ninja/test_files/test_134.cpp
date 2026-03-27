// File: ./TestProjects/ninja/tests/util_ispathseparator_test_134.cc

#include "gtest/gtest.h"

// Include the implementation to access the internal static function.
#include "src/util.cc"

// Test suite for IsPathSeparator (TEST_ID = 134)

TEST(UtilIsPathSeparatorTest_134, SlashIsAlwaysSeparator_134) {
  // '/' must be treated as a path separator on all platforms.
  EXPECT_TRUE(IsPathSeparator('/'));
}

TEST(UtilIsPathSeparatorTest_134, BackslashPlatformSpecificBehavior_134) {
  // On Windows, both '/' and '\\' are path separators.
  // On non-Windows, only '/' is a path separator, so '\\' must not be.
#ifdef _WIN32
  EXPECT_TRUE(IsPathSeparator('\\'));
#else
  EXPECT_FALSE(IsPathSeparator('\\'));
#endif
}

TEST(UtilIsPathSeparatorTest_134, NonSeparatorCharacters_134) {
  // Typical non-separator characters should return false.
  EXPECT_FALSE(IsPathSeparator('a'));
  EXPECT_FALSE(IsPathSeparator('Z'));
  EXPECT_FALSE(IsPathSeparator(' '));
  EXPECT_FALSE(IsPathSeparator('\0'));
}

TEST(UtilIsPathSeparatorTest_134, DigitAndPunctuationAreNotSeparators_134) {
  EXPECT_FALSE(IsPathSeparator('0'));
  EXPECT_FALSE(IsPathSeparator('9'));
  EXPECT_FALSE(IsPathSeparator('.'));
  EXPECT_FALSE(IsPathSeparator('_'));
}
