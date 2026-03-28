// File: ./TestProjects/re2/re2/tests/is_anchor_end_test_323.cc

#include "gtest/gtest.h"

// Public interface
#include "re2/regexp.h"

// Pull in the static function under test into this TU.
// (Safe because the function has internal linkage.)
#include "re2/compile.cc"

using namespace re2;

namespace {

// Small helper that checks the observable “empty literal string” case
// using only the public interface (no internal state).
bool IsEmptyLiteralString(Regexp* re) {
  return re != nullptr &&
         re->op() == kRegexpLiteralString &&
         re->nrunes() == 0;
}

// Helper to parse a pattern into a Regexp* using only the public API.
// We pass nullptr for status to avoid depending on RegexpStatus details.
Regexp* ParseRe(const char* pat,
                Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(0)) {
  return Regexp::Parse(pat, flags, /*status=*/nullptr);
}

}  // namespace

// ---------- Tests ----------

TEST(IsAnchorEndTest_323, NullInput_ReturnsFalse_323) {
  Regexp* re = nullptr;
  // Should not crash; should return false; pointer should remain nullptr.
  bool changed = IsAnchorEnd(&re, /*depth=*/0);
  EXPECT_FALSE(changed);
  EXPECT_EQ(re, nullptr);
}

TEST(IsAnchorEndTest_323, EndText_BecomesEmptyLiteral_323) {
  // Base case: kRegexpEndText should be rewritten to an empty literal string.
  Regexp* re = ParseRe("\\z");
  ASSERT_NE(re, nullptr);

  bool changed = IsAnchorEnd(&re, /*depth=*/0);
  EXPECT_TRUE(changed);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(IsEmptyLiteralString(re));

  re->Decref();
}

TEST(IsAnchorEndTest_323, CaptureWrappingEndText_RewritesToCaptureEmptyLiteral_323) {
  // Build: Capture(EndText)
  Regexp* end = ParseRe("\\z");
  ASSERT_NE(end, nullptr);

  // Use a non-zero flags value to verify parse_flags propagation.
  auto flags = static_cast<Regexp::ParseFlags>(0x1234);
  Regexp* cap = Regexp::Capture(end, flags, /*cap id=*/7);
  ASSERT_NE(cap, nullptr);

  bool changed = IsAnchorEnd(&cap, /*depth=*/0);
  EXPECT_TRUE(changed);

  // Verify structure via public API only.
  ASSERT_EQ(cap->op(), kRegexpCapture);
  EXPECT_EQ(cap->parse_flags(), flags);
  EXPECT_EQ(cap->cap(), 7);

  Regexp* inner = cap->sub()[0];
  ASSERT_NE(inner, nullptr);
  EXPECT_TRUE(IsEmptyLiteralString(inner));

  cap->Decref();
}

TEST(IsAnchorEndTest_323, ConcatWithEndTextLast_RewritesLastSubToEmpty_323) {
  // Build: Concat(Literal('a'), EndText)
  auto flags = static_cast<Regexp::ParseFlags>(0x00FF);
  Regexp* lit_a = Regexp::NewLiteral('a', flags);
  ASSERT_NE(lit_a, nullptr);
  Regexp* end = ParseRe("\\z");
  ASSERT_NE(end, nullptr);

  Regexp* subs[2] = {lit_a, end};
  Regexp* concat = Regexp::Concat(subs, 2, flags);
  ASSERT_NE(concat, nullptr);
  ASSERT_EQ(concat->op(), kRegexpConcat);
  ASSERT_EQ(concat->nsub(), 2);

  bool changed = IsAnchorEnd(&concat, /*depth=*/0);
  EXPECT_TRUE(changed);

  // Still a concat with 2 subs; last must now be empty literal string.
  ASSERT_EQ(concat->op(), kRegexpConcat);
  ASSERT_EQ(concat->nsub(), 2);
  EXPECT_EQ(concat->parse_flags(), flags);

  Regexp* last = concat->sub()[1];
  ASSERT_NE(last, nullptr);
  EXPECT_TRUE(IsEmptyLiteralString(last));

  // First sub remains a literal.
  Regexp* first = concat->sub()[0];
  ASSERT_NE(first, nullptr);
  EXPECT_EQ(first->op(), kRegexpLiteral);

  concat->Decref();
}

TEST(IsAnchorEndTest_323, ConcatWithEndTextNotLast_ReturnsFalse_NoChange_323) {
  // Build: Concat(EndText, Literal('a'))  — EndText is not the last element.
  auto flags = static_cast<Regexp::ParseFlags>(0x0A0A);
  Regexp* end = ParseRe("\\z");
  ASSERT_NE(end, nullptr);
  Regexp* lit_a = Regexp::NewLiteral('a', flags);
  ASSERT_NE(lit_a, nullptr);

  Regexp* subs[2] = {end, lit_a};
  Regexp* concat = Regexp::Concat(subs, 2, flags);
  ASSERT_NE(concat, nullptr);
  Regexp* original_ptr = concat;

  bool changed = IsAnchorEnd(&concat, /*depth=*/0);
  EXPECT_FALSE(changed);
  // No rewrite should occur; pointer identity should remain the same.
  EXPECT_EQ(concat, original_ptr);
  ASSERT_EQ(concat->op(), kRegexpConcat);
  ASSERT_EQ(concat->nsub(), 2);

  // The last sub remains the literal 'a'.
  Regexp* last = concat->sub()[1];
  ASSERT_NE(last, nullptr);
  EXPECT_EQ(last->op(), kRegexpLiteral);

  concat->Decref();
}

TEST(IsAnchorEndTest_323, DepthLimitAcrossNestedCaptures_ReturnsFalse_NoChange_323) {
  // Build: Capture(Capture(Capture(Capture(EndText)))))
  // Starting at depth=0, recursion reaches depth==4 at the 5th level and should stop.
  Regexp* re = ParseRe("\\z");
  ASSERT_NE(re, nullptr);

  auto flags = static_cast<Regexp::ParseFlags>(0x0055);
  re = Regexp::Capture(re, flags, 1);
  re = Regexp::Capture(re, flags, 2);
  re = Regexp::Capture(re, flags, 3);
  re = Regexp::Capture(re, flags, 4);
  ASSERT_NE(re, nullptr);

  Regexp* original_ptr = re;
  bool changed = IsAnchorEnd(&re, /*depth=*/0);
  EXPECT_FALSE(changed);
  EXPECT_EQ(re, original_ptr);

  // Verify the nested structure is still intact and bottom is EndText.
  ASSERT_EQ(re->op(), kRegexpCapture);
  Regexp* s0 = re->sub()[0];
  ASSERT_EQ(s0->op(), kRegexpCapture);
  Regexp* s1 = s0->sub()[0];
  ASSERT_EQ(s1->op(), kRegexpCapture);
  Regexp* s2 = s1->sub()[0];
  ASSERT_EQ(s2->op(), kRegexpCapture);
  Regexp* bottom = s2->sub()[0];
  ASSERT_NE(bottom, nullptr);
  EXPECT_EQ(bottom->op(), kRegexpEndText);

  re->Decref();
}

TEST(IsAnchorEndTest_323, DepthAtLimitParameter_ReturnsFalse_323) {
  // If depth >= 4 on entry, should immediately return false.
  Regexp* re = ParseRe("\\z");
  ASSERT_NE(re, nullptr);

  Regexp* original_ptr = re;
  bool changed = IsAnchorEnd(&re, /*depth=*/4);
  EXPECT_FALSE(changed);
  EXPECT_EQ(re, original_ptr);

  re->Decref();
}
