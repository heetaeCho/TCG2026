// File: regexp_newliteral_test_346.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

using re2::Regexp;
using re2::kRegexpLiteral;

namespace {

// Basic creation: non-null, correct op, rune, and flags.
TEST(RegexpNewLiteralTest_346, CreatesLiteralWithGivenRune_346) {
  // Use small, safe flag values; we don't assume any particular semantics.
  auto flags = static_cast<Regexp::ParseFlags>(0);
  Regexp* re = Regexp::NewLiteral('A', flags);

  ASSERT_NE(re, nullptr) << "NewLiteral should return a non-null Regexp*";
  EXPECT_EQ(re->op(), kRegexpLiteral) << "op() should be kRegexpLiteral";
  EXPECT_EQ(re->rune(), static_cast<int>('A')) << "rune() should match the input rune";
  EXPECT_EQ(re->parse_flags(), flags) << "parse_flags() should reflect the flags passed in";

  re->Decref();  // Release per the public interface.
}

// Flags propagation: whatever flag value we pass should be observable via parse_flags().
TEST(RegexpNewLiteralTest_346, PreservesParseFlags_346) {
  auto flags = static_cast<Regexp::ParseFlags>(1);
  Regexp* re = Regexp::NewLiteral('B', flags);

  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->parse_flags(), flags);

  re->Decref();
}

// Distinct objects: separate calls should yield separate instances with independent state.
TEST(RegexpNewLiteralTest_346, DistinctInstancesForEachCall_346) {
  auto flags = static_cast<Regexp::ParseFlags>(0);
  Regexp* re1 = Regexp::NewLiteral('X', flags);
  Regexp* re2 = Regexp::NewLiteral('Y', flags);

  ASSERT_NE(re1, nullptr);
  ASSERT_NE(re2, nullptr);
  EXPECT_NE(re1, re2) << "Two NewLiteral calls should not return the same instance";

  EXPECT_EQ(re1->op(), kRegexpLiteral);
  EXPECT_EQ(re2->op(), kRegexpLiteral);

  EXPECT_EQ(re1->rune(), static_cast<int>('X'));
  EXPECT_EQ(re2->rune(), static_cast<int>('Y'));

  re1->Decref();
  re2->Decref();
}

// Boundary: zero rune value should be stored as-is.
TEST(RegexpNewLiteralTest_346, ZeroRune_346) {
  auto flags = static_cast<Regexp::ParseFlags>(0);
  Regexp* re = Regexp::NewLiteral(0, flags);

  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 0);

  re->Decref();
}

// Boundary: a high Unicode code point (0x10FFFF) should be stored as-is.
// (We don't assume validation; we only verify observable storage via rune()).
TEST(RegexpNewLiteralTest_346, MaxUnicodeRune_346) {
  const int kMaxRune = 0x10FFFF;
  auto flags = static_cast<Regexp::ParseFlags>(0);
  Regexp* re = Regexp::NewLiteral(kMaxRune, flags);

  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), kMaxRune);

  re->Decref();
}

}  // namespace
