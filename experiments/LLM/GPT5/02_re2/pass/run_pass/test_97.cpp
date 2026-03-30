// File: sparse_set_less_test_97.cc
#include <gtest/gtest.h>
#include <climits>
#include "re2/sparse_set.h"

using re2::SparseSetT;
using re2::SparseSet;  // typedef SparseSetT<void>

//
// Basic correctness
//
TEST(SparseSetLessTest_97, ReturnsTrueWhenALessThanB_97) {
  EXPECT_TRUE(SparseSetT<void>::less(1, 2));
  EXPECT_TRUE(SparseSet::less(-10, -5));
  EXPECT_TRUE(SparseSet::less(-1, 0));
}

TEST(SparseSetLessTest_97, ReturnsFalseWhenAEqualsB_97) {
  EXPECT_FALSE(SparseSetT<void>::less(0, 0));
  EXPECT_FALSE(SparseSet::less(42, 42));
  EXPECT_FALSE(SparseSetT<void>::less(-7, -7));
}

TEST(SparseSetLessTest_97, ReturnsFalseWhenAGreaterThanB_97) {
  EXPECT_FALSE(SparseSetT<void>::less(2, 1));
  EXPECT_FALSE(SparseSet::less(0, -1));
  EXPECT_FALSE(SparseSetT<void>::less(-3, -4));
}

//
// Boundary values
//
TEST(SparseSetLessTest_97, HandlesIntMinAndMax_97) {
  // INT_MIN is less than everything else
  EXPECT_TRUE(SparseSet::less(INT_MIN, INT_MIN + 1));
  EXPECT_TRUE(SparseSetT<void>::less(INT_MIN, 0));
  EXPECT_TRUE(SparseSet::less(INT_MIN, INT_MAX));

  // INT_MAX comparisons
  EXPECT_FALSE(SparseSetT<void>::less(INT_MAX, INT_MAX));
  EXPECT_FALSE(SparseSet::less(INT_MAX, INT_MIN));
  EXPECT_FALSE(SparseSetT<void>::less(INT_MAX, INT_MAX - 1));
}

TEST(SparseSetLessTest_97, HandlesMixedSigns_97) {
  EXPECT_TRUE(SparseSet::less(-100, 100));
  EXPECT_FALSE(SparseSetT<void>::less(100, -100));
}

//
// Comparator properties (observable via interface)
//
TEST(SparseSetLessTest_97, IsIrreflexive_97) {
  // For several representative values, a is never less than a
  const int samples[] = {INT_MIN, -123, -1, 0, 1, 123, INT_MAX};
  for (int v : samples) {
    EXPECT_FALSE(SparseSet::less(v, v)) << "v=" << v;
  }
}

TEST(SparseSetLessTest_97, IsAsymmetric_97) {
  // If a < b then !(b < a)
  const std::pair<int,int> pairs[] = {
    {INT_MIN, -1}, {-5, -4}, {-1, 0}, {0, 1}, {1, 2}, {INT_MAX - 1, INT_MAX}
  };
  for (auto [a, b] : pairs) {
    ASSERT_TRUE(SparseSet::less(a, b)) << a << " !< " << b;
    EXPECT_FALSE(SparseSetT<void>::less(b, a)) << b << " < " << a;
  }
}
