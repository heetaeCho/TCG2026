// File: ./TestProjects/ninja/tests/util_islatinalpha_test_145.cc

#include "gtest/gtest.h"
#include "util.h"  // assumes islatinalpha(int) is declared here

// TEST_ID: 145

// Basic expectation: ASCII Latin alphabet characters (A–Z, a–z) are true,
// everything else is false.

TEST(IsLatinAlphaTest_145, ReturnsTrueForLowercaseLetters_145) {
  EXPECT_TRUE(islatinalpha('a'));
  EXPECT_TRUE(islatinalpha('m'));
  EXPECT_TRUE(islatinalpha('z'));
}

TEST(IsLatinAlphaTest_145, ReturnsTrueForUppercaseLetters_145) {
  EXPECT_TRUE(islatinalpha('A'));
  EXPECT_TRUE(islatinalpha('M'));
  EXPECT_TRUE(islatinalpha('Z'));
}

TEST(IsLatinAlphaTest_145, ReturnsFalseForDigitsAndPunctuation_145) {
  EXPECT_FALSE(islatinalpha('0'));
  EXPECT_FALSE(islatinalpha('9'));
  EXPECT_FALSE(islatinalpha('@'));  // just before 'A'
  EXPECT_FALSE(islatinalpha('['));  // just after 'Z'
  EXPECT_FALSE(islatinalpha('`'));  // just before 'a'
  EXPECT_FALSE(islatinalpha('{'));  // just after 'z'
  EXPECT_FALSE(islatinalpha(' '));
  EXPECT_FALSE(islatinalpha('\n'));
}

TEST(IsLatinAlphaTest_145, BoundaryAroundLowercaseRange_145) {
  // Just before range
  EXPECT_FALSE(islatinalpha('a' - 1));

  // Inside range
  EXPECT_TRUE(islatinalpha('a'));
  EXPECT_TRUE(islatinalpha('z'));

  // Just after range
  EXPECT_FALSE(islatinalpha('z' + 1));
}

TEST(IsLatinAlphaTest_145, BoundaryAroundUppercaseRange_145) {
  // Just before range
  EXPECT_FALSE(islatinalpha('A' - 1));

  // Inside range
  EXPECT_TRUE(islatinalpha('A'));
  EXPECT_TRUE(islatinalpha('Z'));

  // Just after range
  EXPECT_FALSE(islatinalpha('Z' + 1));
}

TEST(IsLatinAlphaTest_145, NonAsciiAndOutOfTypicalCharRange_145) {
  // Values outside standard ASCII letter range should be false.
  EXPECT_FALSE(islatinalpha(-1));
  EXPECT_FALSE(islatinalpha(0));      // NUL
  EXPECT_FALSE(islatinalpha(128));
  EXPECT_FALSE(islatinalpha(255));
  EXPECT_FALSE(islatinalpha(1000));
}
