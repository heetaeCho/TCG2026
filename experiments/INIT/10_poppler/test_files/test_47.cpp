// SPDX-License-Identifier: MIT
// File: test_cmpTrueTypeLocaIdxFunctor_47.cc
//
// Unit tests for:
//   - TrueTypeLoca
//   - cmpTrueTypeLocaIdxFunctor::operator()
//
// Constraints honored:
//   - Treat implementation as black box (we only assert observable return value behavior).
//   - No private/internal state access (none exists here).
//   - Boundary + normal + exceptional-ish (robustness) cases via interface observations.

#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <vector>

// Include the production header if available in your build.
// If FoFiTrueType.cc is not exposed via a header in this test project,
// adjust the include path to wherever TrueTypeLoca/cmpTrueTypeLocaIdxFunctor are declared.
#include "FoFiTrueType.h"  // <-- If this doesn't exist, replace with the correct header for your build.

// If your project does not provide a header and instead expects the test to see the declarations
// via some other include, you should update the include above accordingly.
// Do NOT re-define the structs here.

namespace {

// TEST_ID = 47
class cmpTrueTypeLocaIdxFunctorTest_47 : public ::testing::Test {};

TEST_F(cmpTrueTypeLocaIdxFunctorTest_47, ReturnsTrueWhenFirstIdxLessThanSecond_47) {
  cmpTrueTypeLocaIdxFunctor cmp;

  TrueTypeLoca a;
  a.idx = 1;
  a.newOffset = 999;

  TrueTypeLoca b;
  b.idx = 2;
  b.newOffset = -123;

  EXPECT_TRUE(cmp(a, b));
  EXPECT_FALSE(cmp(b, a));
}

TEST_F(cmpTrueTypeLocaIdxFunctorTest_47, ReturnsFalseWhenIdxEqualRegardlessOfNewOffset_47) {
  cmpTrueTypeLocaIdxFunctor cmp;

  TrueTypeLoca a;
  a.idx = 7;
  a.newOffset = 0;

  TrueTypeLoca b;
  b.idx = 7;
  b.newOffset = 123456;  // should not matter for idx-only comparison

  EXPECT_FALSE(cmp(a, b));
  EXPECT_FALSE(cmp(b, a));
}

TEST_F(cmpTrueTypeLocaIdxFunctorTest_47, HandlesNegativeIdxValues_47) {
  cmpTrueTypeLocaIdxFunctor cmp;

  TrueTypeLoca a;
  a.idx = -10;
  a.newOffset = 1;

  TrueTypeLoca b;
  b.idx = -1;
  b.newOffset = 2;

  EXPECT_TRUE(cmp(a, b));
  EXPECT_FALSE(cmp(b, a));
}

TEST_F(cmpTrueTypeLocaIdxFunctorTest_47, HandlesIntMinAndIntMax_47) {
  cmpTrueTypeLocaIdxFunctor cmp;

  TrueTypeLoca minLoca;
  minLoca.idx = std::numeric_limits<int>::min();
  minLoca.newOffset = 111;

  TrueTypeLoca maxLoca;
  maxLoca.idx = std::numeric_limits<int>::max();
  maxLoca.newOffset = 222;

  EXPECT_TRUE(cmp(minLoca, maxLoca));
  EXPECT_FALSE(cmp(maxLoca, minLoca));
}

TEST_F(cmpTrueTypeLocaIdxFunctorTest_47, CanBeUsedToSortByIdxAscending_47) {
  cmpTrueTypeLocaIdxFunctor cmp;

  TrueTypeLoca l1;
  l1.idx = 3;
  l1.newOffset = 30;

  TrueTypeLoca l2;
  l2.idx = 1;
  l2.newOffset = 10;

  TrueTypeLoca l3;
  l3.idx = 2;
  l3.newOffset = 20;

  std::vector<TrueTypeLoca> v{l1, l2, l3};

  std::sort(v.begin(), v.end(), cmp);

  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0].idx, 1);
  EXPECT_EQ(v[1].idx, 2);
  EXPECT_EQ(v[2].idx, 3);
}

TEST_F(cmpTrueTypeLocaIdxFunctorTest_47, SortingWithDuplicateIdxKeepsAllElementsAndSortedByIdx_47) {
  cmpTrueTypeLocaIdxFunctor cmp;

  TrueTypeLoca a;
  a.idx = 2;
  a.newOffset = 200;

  TrueTypeLoca b;
  b.idx = 2;
  b.newOffset = 201;

  TrueTypeLoca c;
  c.idx = 1;
  c.newOffset = 100;

  std::vector<TrueTypeLoca> v{a, b, c};

  std::sort(v.begin(), v.end(), cmp);

  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0].idx, 1);
  EXPECT_EQ(v[1].idx, 2);
  EXPECT_EQ(v[2].idx, 2);

  // For equal idx values, comparator should not claim either is "less".
  EXPECT_FALSE(cmp(v[1], v[2]));
  EXPECT_FALSE(cmp(v[2], v[1]));
}

TEST_F(cmpTrueTypeLocaIdxFunctorTest_47, ComparatorIsIrreflexive_47) {
  cmpTrueTypeLocaIdxFunctor cmp;

  TrueTypeLoca a;
  a.idx = 42;
  a.newOffset = -999;

  EXPECT_FALSE(cmp(a, a));
}

TEST_F(cmpTrueTypeLocaIdxFunctorTest_47, ComparatorIsTransitiveForOrderedTriplet_47) {
  cmpTrueTypeLocaIdxFunctor cmp;

  TrueTypeLoca a;
  a.idx = 1;
  a.newOffset = 0;

  TrueTypeLoca b;
  b.idx = 2;
  b.newOffset = 0;

  TrueTypeLoca c;
  c.idx = 3;
  c.newOffset = 0;

  // If a < b and b < c then a < c.
  ASSERT_TRUE(cmp(a, b));
  ASSERT_TRUE(cmp(b, c));
  EXPECT_TRUE(cmp(a, c));
}

}  // namespace