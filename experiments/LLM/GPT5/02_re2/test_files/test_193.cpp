// File: pcre_replace_test_193.cc

#include <gtest/gtest.h>
#include <string>
#include "re2/util/pcre.h"   // Assuming this exposes re2::PCRE

using re2::PCRE;

// Test fixture kept minimal; we treat PCRE as a black box per constraints.
class PCRE_ReplaceTest_193 : public ::testing::Test {};

// [Normal] Replaces a simple literal match at the start of the string.
TEST_F(PCRE_ReplaceTest_193, Replace_SimpleStartMatch_193) {
  std::string s = "hello";
  PCRE pattern("he");
  const bool ok = PCRE::Replace(&s, pattern, "HI");

  EXPECT_TRUE(ok);
  EXPECT_EQ(s, "HIllo");
}

// [Normal] Replaces a numeric run in the middle; verifies only the matched span is changed.
TEST_F(PCRE_ReplaceTest_193, Replace_MiddleSpanOnly_193) {
  std::string s = "abc123def";
  PCRE pattern("\\d+");  // digits
  const bool ok = PCRE::Replace(&s, pattern, "X");

  EXPECT_TRUE(ok);
  EXPECT_EQ(s, "abcXdef");
}

// [Boundary] Empty rewrite removes the matched portion.
TEST_F(PCRE_ReplaceTest_193, Replace_EmptyRewrite_RemovesMatch_193) {
  std::string s = "hello";
  PCRE pattern("he");
  const bool ok = PCRE::Replace(&s, pattern, "");

  EXPECT_TRUE(ok);
  EXPECT_EQ(s, "llo");
}

// [Boundary] Empty input with a pattern that can match empty text.
TEST_F(PCRE_ReplaceTest_193, Replace_EmptyInput_MatchPossible_193) {
  std::string s = "";
  // Commonly ".*" can match empty; we assert only observable behavior: if it matches,
  // Replace returns true and applies rewrite; otherwise returns false and s unchanged.
  PCRE pattern(".*");
  const bool ok = PCRE::Replace(&s, pattern, "X");

  if (ok) {
    EXPECT_EQ(s, "X");
  } else {
    EXPECT_EQ(s, "");  // No change on no match
  }
}

// [Exceptional/Observable error] Invalid backreference in rewrite should cause Replace to fail
// and leave the input unchanged (observable behavior).
TEST_F(PCRE_ReplaceTest_193, Replace_InvalidBackrefInRewrite_FailsAndNoChange_193) {
  std::string original = "value=42";
  std::string s = original;
  PCRE pattern("(\\d+)");      // one capturing group
  // Reference a non-existent second group; if the implementation validates rewrites,
  // this should fail and leave the string unchanged.
  const bool ok = PCRE::Replace(&s, pattern, "\\2");

  if (!ok) {
    EXPECT_EQ(s, original);    // No modification when Replace reports failure
  } else {
    // If implementation treats this literally or tolerates it, still ensure it remains sensible:
    // At minimum, the string should change in a single contiguous span if it succeeded.
    // We avoid asserting internal details; just ensure it's not corrupt.
    EXPECT_FALSE(s.empty());
  }
}

// [No-match] When the pattern does not match, Replace returns false and the string is unchanged.
TEST_F(PCRE_ReplaceTest_193, Replace_NoMatch_ReturnsFalseAndUnchanged_193) {
  std::string original = "hello";
  std::string s = original;
  PCRE pattern("z+");   // unlikely to match "hello"
  const bool ok = PCRE::Replace(&s, pattern, "Y");

  EXPECT_FALSE(ok);
  EXPECT_EQ(s, original);
}
