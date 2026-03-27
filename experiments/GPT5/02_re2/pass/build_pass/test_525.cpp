// File: add_ugroup_test_525.cc

#include "gtest/gtest.h"

// Pull in the implementation so we can call the internal static function.
#include "./TestProjects/re2/re2/parse.cc"

// Headers for types used in the interface
#include "./TestProjects/re2/re2/regexp.h"
#include "./TestProjects/re2/re2/unicode_groups.h"
#include "./TestProjects/re2/util/utf.h"

using namespace re2;

namespace {

// [Normal operation] sign=+1 should include exactly the provided ranges.
TEST(AddUGroupTest_525, AddPositiveRanges_BasicMembership_525) {
  URange16 r16[] = { {1, 3}, {10, 12} };
  UGroup g{ "basic", +1, r16, 2, nullptr, 0 };

  CharClassBuilder cc;
  AddUGroup(&cc, &g, +1, Regexp::NoParseFlags);

  EXPECT_TRUE(cc.Contains(1));
  EXPECT_TRUE(cc.Contains(2));
  EXPECT_TRUE(cc.Contains(3));
  EXPECT_TRUE(cc.Contains(10));
  EXPECT_TRUE(cc.Contains(12));

  EXPECT_FALSE(cc.Contains(0));
  EXPECT_FALSE(cc.Contains(4));
  EXPECT_FALSE(cc.Contains(13));
}

// [Boundary/normal] sign=-1 without FoldCase: complement of provided ranges
TEST(AddUGroupTest_525, AddNegativeNoFold_ComplementMembership_525) {
  URange16 r16[] = { {1, 3}, {10, 12} };
  UGroup g{ "neg-no-fold", -1, r16, 2, nullptr, 0 };

  CharClassBuilder cc;
  AddUGroup(&cc, &g, -1, Regexp::NoParseFlags);

  EXPECT_TRUE(cc.Contains(0));      // outside ranges => included
  EXPECT_FALSE(cc.Contains(2));     // inside [1,3]   => excluded
  EXPECT_TRUE(cc.Contains(5));      // gap            => included
  EXPECT_FALSE(cc.Contains(11));    // inside [10,12] => excluded
  EXPECT_TRUE(cc.Contains(Runemax)); // top end outside => included
}

// [FoldCase path] When ClassNL is NOT set, newline should be cut out
// of the negated class (observable via Contains('\n') == false).
TEST(AddUGroupTest_525, NegativeFoldCase_CutsNewlineWhenClassNLUnset_525) {
  URange16 r16[] = { {20, 25} };
  UGroup g{ "fold-cut-nl", -1, r16, 1, nullptr, 0 };

  CharClassBuilder cc;
  AddUGroup(&cc, &g, -1, Regexp::FoldCase);

  EXPECT_FALSE(cc.Contains('\n'));  // newline excluded by cut
  EXPECT_FALSE(cc.Contains(22));    // inside original => excluded
  EXPECT_TRUE(cc.Contains(26));     // outside original => included
}

// [FoldCase path] When ClassNL IS set (and NeverNL is not), newline is NOT cut.
TEST(AddUGroupTest_525, NegativeFoldCase_RespectsClassNL_AllowsNewline_525) {
  URange16 r16[] = { {30, 35} };
  UGroup g{ "fold-keep-nl", -1, r16, 1, nullptr, 0 };

  CharClassBuilder cc;
  AddUGroup(&cc, &g, -1,
            static_cast<Regexp::ParseFlags>(Regexp::FoldCase | Regexp::ClassNL));

  EXPECT_TRUE(cc.Contains('\n'));   // newline included (not cut)
  EXPECT_FALSE(cc.Contains(33));    // inside original => excluded
  EXPECT_TRUE(cc.Contains(1000));   // outside original => included
}

// [FoldCase path] Even if ClassNL is set, NeverNL forces newline to be cut.
TEST(AddUGroupTest_525, NegativeFoldCase_NeverNL_StillCutsNewline_525) {
  URange16 r16[] = { {40, 41} };
  UGroup g{ "fold-never-nl", -1, r16, 1, nullptr, 0 };

  CharClassBuilder cc;
  AddUGroup(&cc, &g, -1,
            static_cast<Regexp::ParseFlags>(Regexp::FoldCase |
                                            Regexp::ClassNL |
                                            Regexp::NeverNL));

  EXPECT_FALSE(cc.Contains('\n'));  // forced cut
  EXPECT_FALSE(cc.Contains(40));    // inside original => excluded
  EXPECT_TRUE(cc.Contains(100));    // outside original => included
}

// [Boundary] Empty group with sign=+1 adds nothing.
TEST(AddUGroupTest_525, EmptyGroup_PositiveAddsNothing_525) {
  UGroup g{ "empty-pos", +1, nullptr, 0, nullptr, 0 };

  CharClassBuilder cc;
  AddUGroup(&cc, &g, +1, Regexp::NoParseFlags);

  EXPECT_FALSE(cc.Contains(0));
  EXPECT_FALSE(cc.Contains('A'));
  EXPECT_FALSE(cc.Contains('\n'));
}

// [Boundary] Empty group with sign=-1 without FoldCase yields full universe.
TEST(AddUGroupTest_525, EmptyGroup_NegativeNoFold_ComplementAll_525) {
  UGroup g{ "empty-neg", -1, nullptr, 0, nullptr, 0 };

  CharClassBuilder cc;
  AddUGroup(&cc, &g, -1, Regexp::NoParseFlags);

  EXPECT_TRUE(cc.Contains(0));
  EXPECT_TRUE(cc.Contains('A'));
  EXPECT_TRUE(cc.Contains('\n'));
  EXPECT_TRUE(cc.Contains(Runemax));
}

// [Boundary] Range touching 0 behaves correctly for both signs.
TEST(AddUGroupTest_525, BoundaryAtZero_525) {
  URange16 r16[] = { {0, 0} };      // minimal boundary
  UGroup gpos{ "zero-pos", +1, r16, 1, nullptr, 0 };
  UGroup gneg{ "zero-neg", -1, r16, 1, nullptr, 0 };

  CharClassBuilder cc_pos;
  AddUGroup(&cc_pos, &gpos, +1, Regexp::NoParseFlags);
  EXPECT_TRUE(cc_pos.Contains(0));
  EXPECT_FALSE(cc_pos.Contains(1));

  CharClassBuilder cc_neg;
  AddUGroup(&cc_neg, &gneg, -1, Regexp::NoParseFlags);
  EXPECT_FALSE(cc_neg.Contains(0));
  EXPECT_TRUE(cc_neg.Contains(1));
  EXPECT_TRUE(cc_neg.Contains(Runemax));
}

} // namespace
