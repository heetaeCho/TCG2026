// File: re2_globalreplace_test_257.cc
#include <gtest/gtest.h>
#include <string>
#include "re2/re2.h"

using re2::RE2;

class RE2_GlobalReplaceTest_257 : public ::testing::Test {
protected:
  void TearDown() override {
    // Ensure any cap set in a test is cleared for subsequent tests.
    RE2::FUZZING_ONLY_set_maximum_global_replace_count(-1);
  }
};

// [Normal] Replaces all digit runs with their whole-match capture ($0).
TEST_F(RE2_GlobalReplaceTest_257, ReplacesDigitsWithCapture_257) {
  std::string s = "a1 b22 c333";
  RE2 re("(\\d+)");
  // Any instance can call the member; the method uses the 're' parameter.
  RE2 caller(".*");

  int n = caller.GlobalReplace(&s, re, "<$0>");
  EXPECT_EQ(n, 3);
  EXPECT_EQ(s, "a<1> b<22> c<333>");
}

// [No-match] Returns 0 and leaves the string unchanged.
TEST_F(RE2_GlobalReplaceTest_257, NoMatchReturnsZeroAndUnchanged_257) {
  std::string original = "abc def";
  std::string s = original;
  RE2 re("\\d+");
  RE2 caller(".*");

  int n = caller.GlobalReplace(&s, re, "X");
  EXPECT_EQ(n, 0);
  EXPECT_EQ(s, original);
}

// [Invalid rewrite] Using a capture index higher than the pattern provides
// should return 0 and leave the input unchanged (early failure path).
TEST_F(RE2_GlobalReplaceTest_257, InvalidRewriteCaptureTooHigh_ReturnsZeroNoChange_257) {
  std::string original = "x123y";
  std::string s = original;
  RE2 re("(\\d+)");         // only 1 capturing group
  RE2 caller(".*");

  // Rewrite asks for $2 which doesn't exist for this pattern.
  int n = caller.GlobalReplace(&s, re, "[$2]");
  EXPECT_EQ(n, 0);
  EXPECT_EQ(s, original);
}

// [Zero-width matches] Word-boundary pattern should insert at boundaries,
// and the function must avoid infinite loops on empty matches.
// Expect separators at start, between letters, and at end.
TEST_F(RE2_GlobalReplaceTest_257, ZeroWidthWordBoundary_InsertsAtBoundaries_257) {
  std::string s = "ab";
  RE2 re("\\b");            // zero-width word boundary
  RE2 caller(".*");

  int n = caller.GlobalReplace(&s, re, "|");
  EXPECT_EQ(n, 3);
  EXPECT_EQ(s, "|a|b|");
}

// [Cap on replacements] Honors the global replacement cap.
TEST_F(RE2_GlobalReplaceTest_257, RespectsMaximumGlobalReplaceCount_257) {
  std::string s = "abc";
  RE2 re("\\w");            // every word-char
  RE2 caller(".*");

  RE2::FUZZING_ONLY_set_maximum_global_replace_count(1);
  int n = caller.GlobalReplace(&s, re, "#");

  EXPECT_EQ(n, 1);
  EXPECT_EQ(s, "#bc");      // only first match replaced
}

// [UTF-8 + zero-width] Empty pattern matches at every position. The
// implementation should step by a full UTF-8 rune between identical
// empty matches, so a multi-byte character stays intact.
TEST_F(RE2_GlobalReplaceTest_257, EmptyPatternWithUTF8Rune_SafeAdvance_257) {
  // Single Korean syllable "가" (3-byte UTF-8)
  std::string s = u8"가";
  RE2 re("");               // empty pattern (zero-width everywhere)
  RE2 caller(".*");

  int n = caller.GlobalReplace(&s, re, "|");
  // Expect replacement before and after the rune.
  EXPECT_EQ(n, 2);
  EXPECT_EQ(s, u8"|가|");
}
