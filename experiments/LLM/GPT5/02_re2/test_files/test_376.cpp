// File: ./TestProjects/re2/re2/tests/charclassbuilder_negate_test.cc
#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "util/utf.h"

using re2::CharClassBuilder;
using re2::Runemax;

//
// Suite name and each test case name include TEST_ID = 376
//
TEST(CharClassBuilderTest_376, Negate_EmptyBecomesFull_376) {
  CharClassBuilder cc;          // starts empty by contract
  EXPECT_TRUE(cc.empty());

  cc.Negate();

  // After negation of empty, the set should be full over [0, Runemax].
  EXPECT_TRUE(cc.full());
  EXPECT_TRUE(cc.Contains(0));
  EXPECT_TRUE(cc.Contains(Runemax));
  // A couple of interior points should also be included.
  EXPECT_TRUE(cc.Contains(1));
  EXPECT_TRUE(cc.Contains(Runemax / 2));
}

TEST(CharClassBuilderTest_376, Negate_FullBecomesEmpty_376) {
  CharClassBuilder cc;
  ASSERT_TRUE(cc.AddRange(0, Runemax));  // make it full through public API
  ASSERT_TRUE(cc.full());

  cc.Negate();

  // Complement of full is empty.
  EXPECT_TRUE(cc.empty());
  EXPECT_FALSE(cc.Contains(0));
  EXPECT_FALSE(cc.Contains(Runemax));
  // Spot-check an interior point.
  EXPECT_FALSE(cc.Contains(Runemax / 2));
}

TEST(CharClassBuilderTest_376, Negate_SingleMiddleRange_ComplementsEndpoints_376) {
  CharClassBuilder cc;
  ASSERT_TRUE(cc.AddRange(10, 20));

  cc.Negate();

  // Points strictly inside original range should now be excluded.
  EXPECT_FALSE(cc.Contains(10));
  EXPECT_FALSE(cc.Contains(15));
  EXPECT_FALSE(cc.Contains(20));

  // Points just outside original range should be included.
  EXPECT_TRUE(cc.Contains(9));
  EXPECT_TRUE(cc.Contains(21));

  // Extremes should be included (since original range was strictly interior).
  EXPECT_TRUE(cc.Contains(0));
  EXPECT_TRUE(cc.Contains(Runemax));
}

TEST(CharClassBuilderTest_376, Negate_RangeStartingAtZero_376) {
  CharClassBuilder cc;
  ASSERT_TRUE(cc.AddRange(0, 5));

  cc.Negate();

  // Original covered prefix [0,5] is excluded after negation.
  for (int r = 0; r <= 5; ++r) {
    EXPECT_FALSE(cc.Contains(r)) << "Unexpected containment at r=" << r;
  }
  // Immediately after the covered prefix should be included.
  EXPECT_TRUE(cc.Contains(6));
  // Far end should be included as well.
  EXPECT_TRUE(cc.Contains(Runemax));
}

TEST(CharClassBuilderTest_376, Negate_RangeEndingAtRunemax_376) {
  CharClassBuilder cc;
  ASSERT_TRUE(cc.AddRange(Runemax - 5, Runemax));

  cc.Negate();

  // Original covered suffix [Runemax-5, Runemax] is excluded after negation.
  for (int r = Runemax - 5; r <= Runemax; ++r) {
    EXPECT_FALSE(cc.Contains(r)) << "Unexpected containment at r=" << r;
  }
  // Just before the excluded suffix should be included.
  EXPECT_TRUE(cc.Contains(Runemax - 6));
  // Zero should be included, since the original range was at the high end.
  EXPECT_TRUE(cc.Contains(0));
}

TEST(CharClassBuilderTest_376, Negate_TwiceRestoresOriginal_376) {
  CharClassBuilder cc;
  ASSERT_TRUE(cc.AddRange(0, 0));         // a single point at 0
  ASSERT_TRUE(cc.AddRange(100, 200));     // and a middle range

  // Snapshot some observable points before negation.
  const bool before_0     = cc.Contains(0);
  const bool before_50    = cc.Contains(50);
  const bool before_150   = cc.Contains(150);
  const bool before_top   = cc.Contains(Runemax);

  // Double negate should be an involution.
  cc.Negate();
  cc.Negate();

  EXPECT_EQ(before_0,   cc.Contains(0));
  EXPECT_EQ(before_50,  cc.Contains(50));
  EXPECT_EQ(before_150, cc.Contains(150));
  EXPECT_EQ(before_top, cc.Contains(Runemax));
}
