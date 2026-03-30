// File: pcre_checkrewritestr_test.cc

#include <gtest/gtest.h>
#include <string>

#include "re2/util/pcre.h"  // Adjust include path if needed

using re2::PCRE;

class PCRE_CheckRewriteStringTest_200 : public ::testing::Test {};

// -----------------------------
// Normal / happy-path behavior
// -----------------------------

// No escapes or references: should pass.
TEST_F(PCRE_CheckRewriteStringTest_200, PlainText_NoCaptures_ReturnsTrue_200) {
  PCRE re("abc");  // 0 capturing groups
  std::string err;
  EXPECT_TRUE(re.CheckRewriteString("just text", &err));
  EXPECT_TRUE(err.empty());
}

// Escaped backslash is allowed.
TEST_F(PCRE_CheckRewriteStringTest_200, EscapedBackslash_Allowed_200) {
  PCRE re("(a)");  // 1 capturing group
  std::string err;
  EXPECT_TRUE(re.CheckRewriteString("prefix\\\\suffix", &err));  // "\\\\" => literal '\'
  EXPECT_TRUE(err.empty());
}

// Backreferences within the available capture count are allowed.
TEST_F(PCRE_CheckRewriteStringTest_200, Backrefs_WithinRange_ReturnsTrue_200) {
  PCRE re("(a)(b)");  // 2 capturing groups
  std::string err;
  EXPECT_TRUE(re.CheckRewriteString("X\\1Y\\2Z", &err));
  EXPECT_TRUE(err.empty());
}

// Boundary: referencing exactly the highest available group should pass.
TEST_F(PCRE_CheckRewriteStringTest_200, Backref_ExactlyMaxCapture_ReturnsTrue_200) {
  PCRE re("(a)(b)");  // 2 capturing groups
  std::string err;
  EXPECT_TRUE(re.CheckRewriteString("\\2", &err));
  EXPECT_TRUE(err.empty());
}

// Boundary: \0 is considered a digit escape and does not exceed capture count when there are 0 groups.
TEST_F(PCRE_CheckRewriteStringTest_200, Backref_ZeroDigit_WithNoCaptures_ReturnsTrue_200) {
  PCRE re("abc");  // 0 capturing groups
  std::string err;
  EXPECT_TRUE(re.CheckRewriteString("\\0", &err));
  EXPECT_TRUE(err.empty());
}

// -----------------------------
// Error / exceptional behavior
// -----------------------------

// Trailing backslash at end is not allowed.
TEST_F(PCRE_CheckRewriteStringTest_200, TrailingBackslash_ReturnsFalseAndSetsError_200) {
  PCRE re("(a)");  // any pattern; count not relevant for this error
  std::string err;
  EXPECT_FALSE(re.CheckRewriteString("ends-with-backslash\\", &err));
  EXPECT_EQ(err, "Rewrite schema error: '\\' not allowed at end.");
}

// Backslash must be followed by a digit or backslash.
TEST_F(PCRE_CheckRewriteStringTest_200, BackslashFollowedByNonDigitNonBackslash_ReturnsFalse_200) {
  PCRE re("(a)");  // any pattern; count not relevant for this error
  std::string err;
  EXPECT_FALSE(re.CheckRewriteString("\\x", &err));
  EXPECT_EQ(err, "Rewrite schema error: '\\' must be followed by a digit or '\\'.");
}

// Requesting a capture index greater than the number of capturing groups should fail.
TEST_F(PCRE_CheckRewriteStringTest_200, Backref_ExceedsCaptureCount_ReturnsFalseWithCountMessage_200) {
  PCRE re("(a)(b)");  // 2 capturing groups
  std::string err;
  // \3 requests more groups than available (max_token = 3, capture count = 2)
  EXPECT_FALSE(re.CheckRewriteString("\\3", &err));

  // Expected exact message as produced by the implementation
  EXPECT_EQ(
      err,
      "Rewrite schema requests 3 matches, but the regexp only has 2 parenthesized subexpressions.");
}
