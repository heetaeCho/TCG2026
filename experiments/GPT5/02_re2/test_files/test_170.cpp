// File: re2_regexp_parseflags_and_test.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

using re2::Regexp;

class RegexpParseFlagsAndTest_170 : public ::testing::Test {};

// Same flag AND itself yields the same flag.
TEST_F(RegexpParseFlagsAndTest_170, SameFlagReturnsSelf_170) {
  auto r = (Regexp::FoldCase & Regexp::FoldCase);
  EXPECT_EQ(r, Regexp::FoldCase);
}

// Disjoint single-bit flags yield NoParseFlags (0).
TEST_F(RegexpParseFlagsAndTest_170, DisjointFlagsYieldZero_170) {
  auto r = (Regexp::FoldCase & Regexp::Literal);
  EXPECT_EQ(r, Regexp::NoParseFlags);
}

// Composite vs component: MatchNL includes ClassNL.
TEST_F(RegexpParseFlagsAndTest_170, MatchNLAndClassNL_170) {
  auto r = (Regexp::MatchNL & Regexp::ClassNL);
  EXPECT_EQ(r, Regexp::ClassNL);
}

// Composite vs component: MatchNL includes DotNL.
TEST_F(RegexpParseFlagsAndTest_170, MatchNLAndDotNL_170) {
  auto r = (Regexp::MatchNL & Regexp::DotNL);
  EXPECT_EQ(r, Regexp::DotNL);
}

// Composite vs composite with partial overlap: LikePerl shares ClassNL with MatchNL (but not DotNL).
TEST_F(RegexpParseFlagsAndTest_170, LikePerlAndMatchNL_ReturnsCommonBits_170) {
  auto r = (Regexp::LikePerl & Regexp::MatchNL);
  EXPECT_EQ(r, Regexp::ClassNL);  // Only the common bit(s) remain
}

// Zero mask behavior.
TEST_F(RegexpParseFlagsAndTest_170, NoParseFlagsAndAnythingIsZero_170) {
  auto r1 = (Regexp::NoParseFlags & Regexp::FoldCase);
  auto r2 = (Regexp::NoParseFlags & Regexp::MatchNL);
  EXPECT_EQ(r1, Regexp::NoParseFlags);
  EXPECT_EQ(r2, Regexp::NoParseFlags);
}

// All mask behavior with a single-bit flag.
TEST_F(RegexpParseFlagsAndTest_170, AllParseFlagsAndSingleBit_170) {
  auto r = (Regexp::AllParseFlags & Regexp::Latin1);
  EXPECT_EQ(r, Regexp::Latin1);
}

// All mask behavior with a composite flag.
TEST_F(RegexpParseFlagsAndTest_170, AllParseFlagsAndComposite_170) {
  auto r = (Regexp::AllParseFlags & Regexp::LikePerl);
  EXPECT_EQ(r, Regexp::LikePerl);
}

// Internal-only flag WasDollar: still behaves as a normal bit in AND.
TEST_F(RegexpParseFlagsAndTest_170, WasDollarAndAllParseFlags_170) {
  auto r = (Regexp::WasDollar & Regexp::AllParseFlags);
  EXPECT_EQ(r, Regexp::WasDollar);
}

// Internal-only vs unrelated single-bit: no overlap -> zero.
TEST_F(RegexpParseFlagsAndTest_170, WasDollarAndFoldCase_Zero_170) {
  auto r = (Regexp::WasDollar & Regexp::FoldCase);
  EXPECT_EQ(r, Regexp::NoParseFlags);
}
