// File: charclassbuilder_addrangeflags_520_test.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

using re2::CharClassBuilder;
using re2::Regexp;

namespace {

class CharClassBuilderAddRangeFlagsTest_520 : public ::testing::Test {
protected:
  static constexpr int kLF = '\n';
};

TEST_F(CharClassBuilderAddRangeFlagsTest_520, ExcludesNewline_WhenClassNLNotSet_520) {
  CharClassBuilder cc;
  // Range straddling '\n' should be split and exclude '\n' when ClassNL is NOT set.
  cc.AddRangeFlags(kLF - 1, kLF + 1, Regexp::NoParseFlags);

  EXPECT_TRUE(cc.Contains(kLF - 1));
  EXPECT_FALSE(cc.Contains(kLF));      // newline excluded
  EXPECT_TRUE(cc.Contains(kLF + 1));
}

TEST_F(CharClassBuilderAddRangeFlagsTest_520, ExcludesNewline_WhenNeverNLSet_EvenIfClassNL_520) {
  CharClassBuilder cc;
  // NeverNL overrides ClassNL; newline must be excluded.
  cc.AddRangeFlags(kLF - 1, kLF + 1, static_cast<Regexp::ParseFlags>(Regexp::ClassNL | Regexp::NeverNL));

  EXPECT_TRUE(cc.Contains(kLF - 1));
  EXPECT_FALSE(cc.Contains(kLF));      // newline excluded
  EXPECT_TRUE(cc.Contains(kLF + 1));
}

TEST_F(CharClassBuilderAddRangeFlagsTest_520, IncludesNewline_WhenClassNLSet_520) {
  CharClassBuilder cc;
  // When ClassNL is set (and NeverNL is not), a range containing only '\n' should include it.
  cc.AddRangeFlags(kLF, kLF, Regexp::ClassNL);

  EXPECT_TRUE(cc.Contains(kLF));       // newline included
  // Sanity check: neighbors are not implicitly included by this specific call.
  EXPECT_FALSE(cc.Contains(kLF - 1));
  EXPECT_FALSE(cc.Contains(kLF + 1));
}

TEST_F(CharClassBuilderAddRangeFlagsTest_520, OnlyNewlineWithCutnl_LeavesClassEmpty_520) {
  CharClassBuilder cc;
  // With cutnl in effect (default: ClassNL not set), adding only '\n' should add nothing.
  cc.AddRangeFlags(kLF, kLF, Regexp::NoParseFlags);

  EXPECT_FALSE(cc.Contains(kLF));
  EXPECT_EQ(cc.size(), 0);  // observable empty result
}

TEST_F(CharClassBuilderAddRangeFlagsTest_520, FoldCase_DoesNotReintroduceNewline_WhenExcluded_520) {
  CharClassBuilder cc;
  // FoldCase path is taken internally, but the provided code removes '\n' BEFORE folding.
  cc.AddRangeFlags(kLF - 1, kLF + 1, Regexp::FoldCase);

  EXPECT_TRUE(cc.Contains(kLF - 1));
  EXPECT_FALSE(cc.Contains(kLF));      // still excluded
  EXPECT_TRUE(cc.Contains(kLF + 1));
}

TEST_F(CharClassBuilderAddRangeFlagsTest_520, FoldCaseWithClassNL_IncludesNewline_520) {
  CharClassBuilder cc;
  // With ClassNL allowed, even in FoldCase mode, '\n' remains included.
  cc.AddRangeFlags(kLF, kLF, static_cast<Regexp::ParseFlags>(Regexp::FoldCase | Regexp::ClassNL));

  EXPECT_TRUE(cc.Contains(kLF));
}

TEST_F(CharClassBuilderAddRangeFlagsTest_520, Latin1FoldCase_NewlineStillExcluded_WhenClassNLNotSet_520) {
  CharClassBuilder cc;
  // Latin1+FoldCase still must not include '\n' when ClassNL is not set.
  cc.AddRangeFlags(kLF - 1, kLF + 1, static_cast<Regexp::ParseFlags>(Regexp::FoldCase | Regexp::Latin1));

  EXPECT_TRUE(cc.Contains(kLF - 1));
  EXPECT_FALSE(cc.Contains(kLF));      // excluded
  EXPECT_TRUE(cc.Contains(kLF + 1));
}

TEST_F(CharClassBuilderAddRangeFlagsTest_520, RangeWithoutNewline_UnaffectedByNLFlags_520) {
  CharClassBuilder cc;
  // A range that does not cross '\n' should be added normally regardless of NL-related flags.
  cc.AddRangeFlags('a', 'c', Regexp::NoParseFlags);

  EXPECT_TRUE(cc.Contains('a'));
  EXPECT_TRUE(cc.Contains('b'));
  EXPECT_TRUE(cc.Contains('c'));
  EXPECT_FALSE(cc.Contains(kLF));
}

}  // namespace
