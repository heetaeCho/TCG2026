// File: re2_check_rewrite_string_test_263.cc
#include <gtest/gtest.h>
#include <string>

// Adjust the include path if your project structure differs.
#include "re2/re2.h"

namespace re2 {

class RE2CheckRewriteStringTest_263 : public ::testing::Test {
protected:
  // Utility to call CheckRewriteString and capture error
  bool Check(const RE2& re, absl::string_view rewrite, std::string* error) const {
    return re.CheckRewriteString(rewrite, error);
  }
};

// --- Normal operation ---

TEST_F(RE2CheckRewriteStringTest_263, ReturnsTrueWhenNoBackslashes_263) {
  RE2 re("abc");  // 0 capturing groups
  std::string error = "unchanged";
  EXPECT_TRUE(Check(re, "hello world", &error));
  // On success, the function should not set an error message.
  EXPECT_EQ(error, "unchanged");
}

TEST_F(RE2CheckRewriteStringTest_263, ReturnsTrueForEscapedBackslash_263) {
  RE2 re("(a)");  // 1 capturing group (not relevant for this case)
  std::string error = "keep";
  EXPECT_TRUE(Check(re, "foo\\\\bar", &error));  // rewrite literal: foo\\bar
  EXPECT_EQ(error, "keep");
}

TEST_F(RE2CheckRewriteStringTest_263, ReturnsTrueWhenMaxTokenEqualsGroupCount_263) {
  RE2 re("(a)(b)");  // 2 capturing groups
  std::string error = "keep";
  EXPECT_TRUE(Check(re, "\\2", &error));
  EXPECT_EQ(error, "keep");
}

TEST_F(RE2CheckRewriteStringTest_263, ReturnsTrueForZeroReferenceEvenWithNoGroups_263) {
  RE2 re("abc");  // 0 capturing groups
  std::string error = "keep";
  EXPECT_TRUE(Check(re, "\\0", &error));
  EXPECT_EQ(error, "keep");
}

// --- Boundary / error cases ---

TEST_F(RE2CheckRewriteStringTest_263, FailsWhenTrailingBackslash_263) {
  RE2 re("(x)");  // any pattern
  std::string error;
  EXPECT_FALSE(Check(re, "ends with slash\\", &error));
  EXPECT_EQ(error, "Rewrite schema error: '\\' not allowed at end.");
}

TEST_F(RE2CheckRewriteStringTest_263, FailsWhenBackslashNotFollowedByDigitOrBackslash_263) {
  RE2 re("(x)");
  std::string error;
  EXPECT_FALSE(Check(re, "bad \\x here", &error));
  EXPECT_EQ(error, "Rewrite schema error: '\\' must be followed by a digit or '\\'.");
}

TEST_F(RE2CheckRewriteStringTest_263, FailsWhenReferenceExceedsCapturingGroups_263) {
  RE2 re("(a)");  // 1 capturing group
  std::string error;
  EXPECT_FALSE(Check(re, "\\2", &error));
  // The function formats this exact message with the requested and available counts.
  EXPECT_EQ(
      error,
      "Rewrite schema requests 2 matches, but the regexp only has 1 parenthesized subexpressions.");
}

}  // namespace re2
