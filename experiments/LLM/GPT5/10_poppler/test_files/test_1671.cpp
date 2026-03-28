// File: test_PSOutputDev_pageDimensionEqual_1671.cc
#include <gtest/gtest.h>

#include <climits>
#include <vector>

// To access the internal-linkage helper in the .cc file, compile this test
// as a single translation unit by including the implementation file.
#include "poppler/PSOutputDev.cc"

class PageDimensionEqualTest_1671 : public ::testing::Test {};

TEST_F(PageDimensionEqualTest_1671, ExactEqualityReturnsTrue_1671) {
  EXPECT_TRUE(pageDimensionEqual(0, 0));
  EXPECT_TRUE(pageDimensionEqual(123, 123));
  EXPECT_TRUE(pageDimensionEqual(-45, -45));
}

TEST_F(PageDimensionEqualTest_1671, SmallDifferencesAreConsideredEqual_1671) {
  EXPECT_TRUE(pageDimensionEqual(100, 101));
  EXPECT_TRUE(pageDimensionEqual(100, 104));
  EXPECT_TRUE(pageDimensionEqual(100, 96));
  EXPECT_TRUE(pageDimensionEqual(-100, -97));
  EXPECT_TRUE(pageDimensionEqual(-100, -104));
}

TEST_F(PageDimensionEqualTest_1671, BoundaryAtFivePixelsIsNotEqual_1671) {
  // Differences strictly less than 5 are treated as equal.
  EXPECT_TRUE(pageDimensionEqual(10, 14));
  EXPECT_TRUE(pageDimensionEqual(14, 10));

  // Difference of exactly 5 should not be considered equal.
  EXPECT_FALSE(pageDimensionEqual(10, 15));
  EXPECT_FALSE(pageDimensionEqual(15, 10));

  // Larger differences should also be not equal.
  EXPECT_FALSE(pageDimensionEqual(10, 16));
  EXPECT_FALSE(pageDimensionEqual(16, 10));
}

TEST_F(PageDimensionEqualTest_1671, WorksWithNegativeAndMixedSignValues_1671) {
  EXPECT_TRUE(pageDimensionEqual(-2, 1));   // diff 3
  EXPECT_FALSE(pageDimensionEqual(-2, 3));  // diff 5

  EXPECT_TRUE(pageDimensionEqual(-1000, -996));   // diff 4
  EXPECT_FALSE(pageDimensionEqual(-1000, -995));  // diff 5
}

TEST_F(PageDimensionEqualTest_1671, SymmetryHoldsForRepresentativePairs_1671) {
  const std::vector<std::pair<int, int>> pairs = {
      {0, 0},
      {1, 4},
      {4, 1},
      {10, 15},
      {-7, -3},
      {-2, 3},
      {INT_MAX, INT_MAX - 4},
      {INT_MIN + 4, INT_MIN},
  };

  for (const auto& p : pairs) {
    EXPECT_EQ(pageDimensionEqual(p.first, p.second), pageDimensionEqual(p.second, p.first))
        << "a=" << p.first << " b=" << p.second;
  }
}

TEST_F(PageDimensionEqualTest_1671, LargeValuesWithoutOverflowBehaveAsExpected_1671) {
  EXPECT_TRUE(pageDimensionEqual(INT_MAX, INT_MAX));
  EXPECT_TRUE(pageDimensionEqual(INT_MAX, INT_MAX - 4));
  EXPECT_FALSE(pageDimensionEqual(INT_MAX, INT_MAX - 5));

  EXPECT_TRUE(pageDimensionEqual(INT_MIN, INT_MIN));
  EXPECT_TRUE(pageDimensionEqual(INT_MIN, INT_MIN + 4));
  EXPECT_FALSE(pageDimensionEqual(INT_MIN, INT_MIN + 5));
}

TEST_F(PageDimensionEqualTest_1671, OverflowInDifferenceResultsInFalse_1671) {
  // These pairs would overflow a signed int subtraction in at least one direction.
  EXPECT_FALSE(pageDimensionEqual(INT_MIN, INT_MAX));
  EXPECT_FALSE(pageDimensionEqual(INT_MAX, INT_MIN));
}