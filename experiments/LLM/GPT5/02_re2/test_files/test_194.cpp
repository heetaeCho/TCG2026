// File: pcre_globalreplace_test_194.cc
#include <gtest/gtest.h>
#include <string>

#include "re2/util/pcre.h"

using re2::PCRE;

class PCRE_GlobalReplaceTest_194 : public ::testing::Test {};

TEST_F(PCRE_GlobalReplaceTest_194, NoMatchReturnsZeroAndLeavesStringUnchanged_194) {
  std::string s = "bbb";          // No 'a' present
  PCRE pattern("a");               // Simple literal
  const int replaced = PCRE::GlobalReplace(&s, pattern, "X");

  EXPECT_EQ(replaced, 0);
  EXPECT_EQ(s, "bbb");             // String should remain unchanged
}

TEST_F(PCRE_GlobalReplaceTest_194, ReplacesAllOccurrencesAndReturnsCount_194) {
  std::string s = "abracadabra";   // Contains five 'a' characters
  PCRE pattern("a");
  const int replaced = PCRE::GlobalReplace(&s, pattern, "X");

  EXPECT_EQ(replaced, 5);          // All matches replaced
  EXPECT_EQ(s, "XbrXcXdXbrX");     // Each 'a' → 'X'
}

TEST_F(PCRE_GlobalReplaceTest_194, AppendsUnmatchedSuffix_194) {
  std::string s = "foo.bar";
  PCRE pattern("\\.");             // Replace the dot between "foo" and "bar"
  const int replaced = PCRE::GlobalReplace(&s, pattern, "-");

  EXPECT_EQ(replaced, 1);
  EXPECT_EQ(s, "foo-bar");         // Confirms unmatched tail "bar" was preserved/appended
}

TEST_F(PCRE_GlobalReplaceTest_194, NonOverlappingMatches_194) {
  std::string s = "aaaa";          // Two non-overlapping "aa" segments
  PCRE pattern("aa");
  const int replaced = PCRE::GlobalReplace(&s, pattern, "b");

  EXPECT_EQ(replaced, 2);          // Should count non-overlapping matches only
  EXPECT_EQ(s, "bb");              // "aa" + "aa" → "b" + "b"
}

TEST_F(PCRE_GlobalReplaceTest_194, DeletionWhenRewriteIsEmpty_194) {
  std::string s = "banana";        // Remove all 'a'
  PCRE pattern("a");
  const int replaced = PCRE::GlobalReplace(&s, pattern, "");

  // "banana" has three 'a' characters
  EXPECT_EQ(replaced, 3);
  EXPECT_EQ(s, "bnn");             // All 'a's deleted
}
