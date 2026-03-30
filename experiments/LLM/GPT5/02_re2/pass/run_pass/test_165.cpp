// File: charclassbuilder_size_test_165.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

using re2::CharClassBuilder;

class CharClassBuilderTest_165 : public ::testing::Test {
protected:
  CharClassBuilder cc_;
};

TEST_F(CharClassBuilderTest_165, NewlyConstructedSizeIsZero_165) {
  // Normal: default-constructed object should report no runes.
  EXPECT_EQ(cc_.size(), 0);
}

TEST_F(CharClassBuilderTest_165, AddSingleCharIncreasesSizeByOne_165) {
  // Normal: adding a single-rune range adds exactly one rune.
  ASSERT_TRUE(cc_.AddRange('a', 'a'));
  EXPECT_EQ(cc_.size(), 1);
  // Sanity: Contains should reflect that addition (observable behavior).
  EXPECT_TRUE(cc_.Contains('a'));
  EXPECT_FALSE(cc_.Contains('b'));
}

TEST_F(CharClassBuilderTest_165, AddNonOverlappingRangesCountsAllRunes_165) {
  // Normal: disjoint ranges count all runes in both.
  ASSERT_TRUE(cc_.AddRange('a', 'c'));   // 3 runes: a,b,c
  ASSERT_TRUE(cc_.AddRange('x', 'z'));   // 3 runes: x,y,z
  EXPECT_EQ(cc_.size(), 6);
}

TEST_F(CharClassBuilderTest_165, AddOverlappingRangesDoesNotDoubleCount_165) {
  // Boundary: overlapping ranges should not double count overlapped runes.
  ASSERT_TRUE(cc_.AddRange('a', 'c'));   // a,b,c => 3
  ASSERT_TRUE(cc_.AddRange('b', 'd'));   // b,c,d overlaps; unique => a,b,c,d
  EXPECT_EQ(cc_.size(), 4);
  EXPECT_TRUE(cc_.Contains('a'));
  EXPECT_TRUE(cc_.Contains('d'));
  EXPECT_FALSE(cc_.Contains('e'));
}

TEST_F(CharClassBuilderTest_165, AddRangeInvalidOrderDoesNotChangeSize_165) {
  // Exceptional: lo > hi is invalid; should not modify observable size.
  EXPECT_EQ(cc_.size(), 0);
  EXPECT_FALSE(cc_.AddRange('z', 'a'));
  EXPECT_EQ(cc_.size(), 0);
}

TEST_F(CharClassBuilderTest_165, RemoveAboveTruncatesSize_165) {
  // Boundary: removing runes above a threshold shrinks size appropriately.
  ASSERT_TRUE(cc_.AddRange('0', '9'));  // 10 runes
  EXPECT_EQ(cc_.size(), 10);

  cc_.RemoveAbove('5');                  // keep '0'..'5' inclusive
  EXPECT_EQ(cc_.size(), 6);
  EXPECT_TRUE(cc_.Contains('0'));
  EXPECT_TRUE(cc_.Contains('5'));
  EXPECT_FALSE(cc_.Contains('6'));
}

TEST_F(CharClassBuilderTest_165, AddCharClassMergesWithoutDuplication_165) {
  // Normal + interaction: merging two builders accumulates unique runes.
  CharClassBuilder digits;
  ASSERT_TRUE(digits.AddRange('0', '9'));  // 10

  CharClassBuilder hexlow;
  ASSERT_TRUE(hexlow.AddRange('a', 'f'));  // 6

  // Start empty, then add digits and merge hexlow.
  ASSERT_TRUE(cc_.AddRange('0', '9'));
  EXPECT_EQ(cc_.size(), 10);

  cc_.AddCharClass(&hexlow);
  EXPECT_EQ(cc_.size(), 16);               // 10 + 6 unique runes

  EXPECT_TRUE(cc_.Contains('3'));
  EXPECT_TRUE(cc_.Contains('a'));
  EXPECT_TRUE(cc_.Contains('f'));
  EXPECT_FALSE(cc_.Contains('g'));
}
