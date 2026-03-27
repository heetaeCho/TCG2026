// File: re2_parseflags_not_operator_test_171.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

using PF = re2::Regexp::ParseFlags;

static int AsInt(PF f) { return static_cast<int>(f); }

TEST(ParseFlagsNotTest_171, NotOnNoParseFlags_ReturnsAll_171) {
  PF result = ~PF::NoParseFlags;
  EXPECT_EQ(AsInt(result), AsInt(PF::AllParseFlags));
}

TEST(ParseFlagsNotTest_171, NotOnAllParseFlags_ReturnsNone_171) {
  PF result = ~PF::AllParseFlags;
  EXPECT_EQ(AsInt(result), AsInt(PF::NoParseFlags));
}

TEST(ParseFlagsNotTest_171, NotOnSingleFlag_ClearsThatFlag_171) {
  PF result = ~PF::FoldCase;
  int expected = AsInt(PF::AllParseFlags) & ~AsInt(PF::FoldCase);
  EXPECT_EQ(AsInt(result), expected);
  // Spot-check: cleared bit must be 0, others remain within mask
  EXPECT_EQ(AsInt(result) & AsInt(PF::FoldCase), 0);
  EXPECT_EQ(AsInt(result) & ~AsInt(PF::AllParseFlags), 0);  // no out-of-range bits
}

TEST(ParseFlagsNotTest_171, NotOnCombinedFlags_ComplementsWithinMask_171) {
  PF combo = static_cast<PF>(AsInt(PF::FoldCase) | AsInt(PF::DotNL) | AsInt(PF::Latin1));
  PF result = ~combo;
  int expected = AsInt(PF::AllParseFlags) & ~AsInt(combo);
  EXPECT_EQ(AsInt(result), expected);
}

TEST(ParseFlagsNotTest_171, NotOnPredefinedCombo_LikePerl_171) {
  PF result = ~PF::LikePerl;
  int expected = AsInt(PF::AllParseFlags) & ~AsInt(PF::LikePerl);
  EXPECT_EQ(AsInt(result), expected);
}

TEST(ParseFlagsNotTest_171, NotMasksOutOfRangeBits_171) {
  // Create a value with a bit outside AllParseFlags (bit 14 set if AllParseFlags=0..13)
  PF invalid = static_cast<PF>(1 << 14);  // 16384
  PF result = ~invalid;
  // Out-of-range bits must be ignored; equivalent to ~NoParseFlags within mask.
  EXPECT_EQ(AsInt(result), AsInt(PF::AllParseFlags));
  EXPECT_EQ(AsInt(result) & ~AsInt(PF::AllParseFlags), 0);
}
