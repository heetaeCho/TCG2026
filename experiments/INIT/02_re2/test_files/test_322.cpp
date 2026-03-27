// File: is_anchor_start_test_322.cc
#include <gtest/gtest.h>

#include "re2/regexp.h"

// Pull in the function under test (file-scope static inside namespace re2).
// This lets us call re2::IsAnchorStart without re-implementing it.
#include "re2/compile.cc"

using re2::Regexp;
using re2::kRegexpBeginText;
using re2::kRegexpLiteralString;
using re2::kRegexpConcat;
using re2::kRegexpCapture;

namespace {

// Small helper to parse a pattern and return a Regexp* or nullptr.
// Flags = 0 to avoid depending on specific flag bits.
static Regexp* ParseOrNull(const std::string& pattern) {
  re2::RegexpStatus status;
  return Regexp::Parse(pattern, static_cast<Regexp::ParseFlags>(0), &status);
}

class IsAnchorStartTest_322 : public ::testing::Test {
protected:
  // Utility: Decref-and-null to avoid leaks in the tests.
  static void SafeDecref(Regexp*& re) {
    if (re) {
      re->Decref();
      re = nullptr;
    }
  }
};

}  // namespace

// 1) Null input: returns false and leaves pointer unchanged.
TEST_F(IsAnchorStartTest_322, NullInputReturnsFalse_322) {
  Regexp* re = nullptr;
  EXPECT_FALSE(re2::IsAnchorStart(&re, /*depth=*/0));
  EXPECT_EQ(re, nullptr);
}

// 2) Depth limit: depth >= 4 short-circuits and does nothing.
TEST_F(IsAnchorStartTest_322, DepthLimitShortCircuits_322) {
  Regexp* re = ParseOrNull("\\A");  // BeginText
  ASSERT_NE(re, nullptr);

  Regexp* before = re;
  EXPECT_FALSE(re2::IsAnchorStart(&re, /*depth=*/4));
  // No rewrite occurred.
  EXPECT_EQ(re, before);
  // Sanity: original node is BeginText.
  EXPECT_EQ(re->op(), kRegexpBeginText);

  SafeDecref(re);
}

// 3) Direct BeginText is rewritten to empty LiteralString.
TEST_F(IsAnchorStartTest_322, BeginTextBecomesEmptyLiteralString_322) {
  Regexp* re = ParseOrNull("\\A");
  ASSERT_NE(re, nullptr);

  EXPECT_TRUE(re2::IsAnchorStart(&re, /*depth=*/0));
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  // Empty string literal has 0 runes.
  EXPECT_EQ(re->nrunes(), 0);

  SafeDecref(re);
}

// 4) Capture(BeginText) rewrites inner to empty LiteralString and preserves capture.
TEST_F(IsAnchorStartTest_322, CaptureAroundBeginTextRewritten_322) {
  Regexp* re = ParseOrNull("(\\A)");
  ASSERT_NE(re, nullptr);

  EXPECT_TRUE(re2::IsAnchorStart(&re, /*depth=*/0));
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  ASSERT_EQ(re->nsub(), 1);
  Regexp* sub = re->sub()[0];
  ASSERT_NE(sub, nullptr);
  EXPECT_EQ(sub->op(), kRegexpLiteralString);
  EXPECT_EQ(sub->nrunes(), 0);

  SafeDecref(re);
}

// 5) Concat(BeginText, "abc") rewrites first piece to empty LiteralString.
TEST_F(IsAnchorStartTest_322, ConcatFrontBeginTextRewritten_322) {
  Regexp* re = ParseOrNull("\\Aabc");
  ASSERT_NE(re, nullptr);

  EXPECT_TRUE(re2::IsAnchorStart(&re, /*depth=*/0));
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  ASSERT_GE(re->nsub(), 1);
  Regexp* first = re->sub()[0];
  ASSERT_NE(first, nullptr);
  EXPECT_EQ(first->op(), kRegexpLiteralString);
  EXPECT_EQ(first->nrunes(), 0);

  SafeDecref(re);
}

// 6) Concat(Capture(BeginText), "x") handles nested recursion across both cases.
TEST_F(IsAnchorStartTest_322, ConcatThenCaptureThenBeginText_322) {
  Regexp* re = ParseOrNull("(\\A)x");
  ASSERT_NE(re, nullptr);

  EXPECT_TRUE(re2::IsAnchorStart(&re, /*depth=*/0));
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  ASSERT_GE(re->nsub(), 1);
  Regexp* first = re->sub()[0];
  ASSERT_NE(first, nullptr);
  EXPECT_EQ(first->op(), kRegexpCapture);
  ASSERT_EQ(first->nsub(), 1);
  Regexp* inner = first->sub()[0];
  ASSERT_NE(inner, nullptr);
  EXPECT_EQ(inner->op(), kRegexpLiteralString);
  EXPECT_EQ(inner->nrunes(), 0);

  SafeDecref(re);
}

// 7) Concat where the first child is NOT an anchor: no change.
TEST_F(IsAnchorStartTest_322, ConcatNonFrontAnchorNoChange_322) {
  // Anchor appears later, not as first element of concat.
  Regexp* re = ParseOrNull("a\\Ab");
  ASSERT_NE(re, nullptr);

  Regexp* before = re;
  EXPECT_FALSE(re2::IsAnchorStart(&re, /*depth=*/0));
  EXPECT_EQ(re, before);  // unchanged

  SafeDecref(re);
}

// 8) Depth cut-off with nested captures: 4 nested captures around \A => no rewrite.
TEST_F(IsAnchorStartTest_322, FourNestedCapturesHitDepthLimit_322) {
  Regexp* re = ParseOrNull("((((\\A))))");
  ASSERT_NE(re, nullptr);

  // At top depth=0; after 4 nested captures, the recursive call would be depth=4.
  EXPECT_FALSE(re2::IsAnchorStart(&re, /*depth=*/0));
  // Because no rewrite, pointer remains the same (implementation returns false without mutation).
  // (If the implementation ever changes to allow mutation on false, this can be relaxed.)
  SafeDecref(re);
}

// 9) Non-anchor input (e.g., "abc") => returns false and unchanged.
TEST_F(IsAnchorStartTest_322, NonAnchorNoChange_322) {
  Regexp* re = ParseOrNull("abc");
  ASSERT_NE(re, nullptr);

  Regexp* before = re;
  EXPECT_FALSE(re2::IsAnchorStart(&re, /*depth=*/0));
  EXPECT_EQ(re, before);

  SafeDecref(re);
}
