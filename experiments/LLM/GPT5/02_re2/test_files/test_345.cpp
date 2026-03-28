// File: regexp_repeat_test_345.cc
#include <gtest/gtest.h>
#include <climits>
#include "re2/regexp.h"

namespace {

using re2::Regexp;
using re2::kRegexpRepeat;

// Helper to get a valid (but minimal) flags value without assuming specifics.
static inline auto F0() {
  // Prefer the nested type if available; fall back to plain ParseFlags.
  return static_cast<Regexp::ParseFlags>(0);
}

static inline auto F1() {
  return static_cast<Regexp::ParseFlags>(1);
}

// --- Tests ---

// Verifies that Repeat creates a repeat node with one sub-expression,
// preserves the sub pointer, min/max bounds, and sets the op to kRegexpRepeat.
TEST(RegexpRepeatTest_345, CreatesRepeatNodeWithOneSub_345) {
  Regexp* child = nullptr;
  Regexp* re = Regexp::Repeat(child, F0(), /*min=*/2, /*max=*/5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->nsub(), 1);
  ASSERT_NE(re->sub(), nullptr);
  EXPECT_EQ(re->sub()[0], child);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
}

// Boundary check: zero repetition bounds should be kept as-is.
TEST(RegexpRepeatTest_345, KeepsZeroBounds_345) {
  Regexp* re = Regexp::Repeat(nullptr, F0(), /*min=*/0, /*max=*/0);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 0);
  EXPECT_EQ(re->max(), 0);
}

// Boundary check: negative min and very large max should be preserved
// (no inference about validation—just verifying observable getters).
TEST(RegexpRepeatTest_345, PreservesNegativeMinAndHugeMax_345) {
  Regexp* re = Regexp::Repeat(nullptr, F0(), /*min=*/-7, /*max=*/INT_MAX);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), -7);
  EXPECT_EQ(re->max(), INT_MAX);
}

// Edge case: min > max should be preserved as provided (no normalization assumed).
TEST(RegexpRepeatTest_345, AllowsMinGreaterThanMax_345) {
  Regexp* re = Regexp::Repeat(nullptr, F0(), /*min=*/5, /*max=*/2);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 5);
  EXPECT_EQ(re->max(), 2);
}

// Verifies that a non-null sub-expression pointer is stored verbatim.
TEST(RegexpRepeatTest_345, StoresNonNullSubPointer_345) {
  // Create a simple child via Repeat itself (treating as black box).
  Regexp* child = Regexp::Repeat(nullptr, F0(), 1, 1);
  ASSERT_NE(child, nullptr);

  Regexp* re = Regexp::Repeat(child, F0(), 3, 4);
  ASSERT_NE(re, nullptr);
  ASSERT_NE(re->sub(), nullptr);
  EXPECT_EQ(re->sub()[0], child);
  EXPECT_EQ(re->nsub(), 1);
}

// Verifies that the parse flags provided to Repeat are reflected by parse_flags().
TEST(RegexpRepeatTest_345, PropagatesParseFlags_345) {
  Regexp* re0 = Regexp::Repeat(nullptr, F0(), 1, 2);
  ASSERT_NE(re0, nullptr);
  EXPECT_EQ(re0->parse_flags(), F0());

  Regexp* re1 = Regexp::Repeat(nullptr, F1(), 1, 2);
  ASSERT_NE(re1, nullptr);
  EXPECT_EQ(re1->parse_flags(), F1());
}

}  // namespace
