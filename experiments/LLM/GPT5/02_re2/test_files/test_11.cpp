// File: re2_number_of_capturing_groups_test.cc

#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

class RE2NumberOfCapturingGroupsTest_11 : public ::testing::Test {};

// --- Normal operation ---

TEST_F(RE2NumberOfCapturingGroupsTest_11, ZeroForPlainTextPattern_11) {
  RE2 re("abc");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(RE2NumberOfCapturingGroupsTest_11, OneSimpleCapturingGroup_11) {
  RE2 re("(abc)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST_F(RE2NumberOfCapturingGroupsTest_11, MultipleSequentialGroups_11) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(RE2NumberOfCapturingGroupsTest_11, NestedAndSequentialGroups_11) {
  // ((a)b)(c) has three capturing groups: outer ((a)b), inner (a), and (c).
  RE2 re("((a)b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(RE2NumberOfCapturingGroupsTest_11, AlternationWithGroupsCountsAll_11) {
  // (a)|(b) contributes two capturing groups.
  RE2 re("(a)|(b)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 2);
}

// --- Boundary conditions ---

TEST_F(RE2NumberOfCapturingGroupsTest_11, EmptyPatternHasZeroGroups_11) {
  RE2 re("");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(RE2NumberOfCapturingGroupsTest_11, NonCapturingGroupsAreNotCounted_11) {
  // Only (b) is a capturing group; (?:a) is non-capturing.
  RE2 re("(?:a)(b)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST_F(RE2NumberOfCapturingGroupsTest_11, EscapedParenthesesDoNotCapture_11) {
  // Pattern matches literal "(a)"; no capturing groups.
  RE2 re("\\(a\\)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(RE2NumberOfCapturingGroupsTest_11, LargerButReasonableCount_11) {
  RE2 re("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 10);
}

// --- Named capturing groups (still capturing) ---

TEST_F(RE2NumberOfCapturingGroupsTest_11, NamedCapturingGroupsAreCounted_11) {
  // Named groups should still be counted as capturing groups.
  RE2 re("(?P<foo>a)(?P<bar>b)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 2);
}
