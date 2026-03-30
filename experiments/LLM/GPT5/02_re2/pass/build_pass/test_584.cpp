// File: sparse_array_test_584.cc
#include <gtest/gtest.h>
#include "re2/sparse_array.h"

#include <utility>  // for std::move

using re2::SparseArray;

class SparseArrayTest_584 : public ::testing::Test {};

// Construction & basic properties
TEST_F(SparseArrayTest_584, Construct_MaxSizeAndEmpty_584) {
  const int kMax = 5;
  SparseArray<int> sa(kMax);

  EXPECT_EQ(kMax, sa.max_size());
  EXPECT_EQ(0, sa.size());
  EXPECT_NE(nullptr, sa.begin());
  EXPECT_NE(nullptr, sa.end());
  EXPECT_EQ(sa.begin(), sa.end());  // empty => begin==end

  // Indices are initially absent.
  for (int i = 0; i < kMax; ++i) {
    EXPECT_FALSE(sa.has_index(i));
  }
  // Out-of-bounds upper index must not be present.
  EXPECT_FALSE(sa.has_index(kMax));
}

// Setting and querying values
TEST_F(SparseArrayTest_584, Set_AndHasIndex_GetExisting_584) {
  SparseArray<int> sa(3);

  // Set at a valid index
  auto it = sa.set(2, 42);
  (void)it;  // We don't assume anything about iterator contents.

  EXPECT_EQ(1, sa.size());
  EXPECT_TRUE(sa.has_index(2));
  EXPECT_FALSE(sa.has_index(0));
  EXPECT_FALSE(sa.has_index(1));
  EXPECT_NE(sa.begin(), sa.end());

  // Value is retrievable via get_existing
  int& v = sa.get_existing(2);
  EXPECT_EQ(42, v);
}

// Update existing values explicitly
TEST_F(SparseArrayTest_584, SetExisting_UpdatesValue_584) {
  SparseArray<int> sa(4);
  sa.set(1, 7);

  // Update via set_existing should change the stored value
  sa.set_existing(1, 99);
  EXPECT_TRUE(sa.has_index(1));
  EXPECT_EQ(99, sa.get_existing(1));

  // Other indices remain absent
  EXPECT_FALSE(sa.has_index(0));
  EXPECT_FALSE(sa.has_index(2));
  EXPECT_FALSE(sa.has_index(3));
}

// set_new behavior for a fresh index
TEST_F(SparseArrayTest_584, SetNew_SucceedsForFreshIndex_584) {
  SparseArray<int> sa(2);
  sa.set_new(1, 5);

  EXPECT_EQ(1, sa.size());
  EXPECT_TRUE(sa.has_index(1));
  EXPECT_EQ(5, sa.get_existing(1));
}

// Boundary indices (0 and max_size-1)
TEST_F(SparseArrayTest_584, BoundaryIndices_ZeroAndLast_584) {
  const int kMax = 4;
  SparseArray<int> sa(kMax);

  sa.set(0, 10);
  sa.set(kMax - 1, 40);

  EXPECT_TRUE(sa.has_index(0));
  EXPECT_TRUE(sa.has_index(kMax - 1));
  EXPECT_EQ(10, sa.get_existing(0));
  EXPECT_EQ(40, sa.get_existing(kMax - 1));
  EXPECT_EQ(2, sa.size());
}

// Clear empties the container
TEST_F(SparseArrayTest_584, Clear_ResetsToEmpty_584) {
  SparseArray<int> sa(3);
  sa.set(1, 11);
  ASSERT_EQ(1, sa.size());

  sa.clear();
  EXPECT_EQ(0, sa.size());
  EXPECT_EQ(sa.begin(), sa.end());
  EXPECT_FALSE(sa.has_index(1));
}

// Resize increases capacity and keeps existing indices usable
TEST_F(SparseArrayTest_584, Resize_PreservesAndExpands_584) {
  SparseArray<int> sa(2);
  sa.set(1, 123);
  ASSERT_TRUE(sa.has_index(1));
  ASSERT_EQ(123, sa.get_existing(1));

  sa.resize(6);
  EXPECT_EQ(6, sa.max_size());

  // Previously-set entry remains observable
  EXPECT_TRUE(sa.has_index(1));
  EXPECT_EQ(123, sa.get_existing(1));

  // New higher indices are out-of-bounds prior to setting
  EXPECT_FALSE(sa.has_index(5));

  // Setting within new bounds works
  sa.set(5, 555);
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_EQ(555, sa.get_existing(5));
}

// Iterator range covers exactly size() elements
TEST_F(SparseArrayTest_584, Iterate_CountEqualsSize_584) {
  SparseArray<int> sa(10);
  sa.set(0, 1);
  sa.set(3, 2);
  sa.set(9, 3);

  // Count elements via iterator without inspecting internals.
  int count = 0;
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    ++count;  // We do not dereference; we only count elements in range.
  }
  EXPECT_EQ(sa.size(), count);
}

// Copy constructor copies observable contents and is independent
TEST_F(SparseArrayTest_584, CopyConstructor_CopiesIndependently_584) {
  SparseArray<int> a(5);
  a.set(2, 22);
  a.set(4, 44);

  SparseArray<int> b(a);  // copy-construct

  // Both have the same observable entries
  EXPECT_EQ(a.max_size(), b.max_size());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_TRUE(b.has_index(2));
  EXPECT_TRUE(b.has_index(4));
  EXPECT_EQ(22, b.get_existing(2));
  EXPECT_EQ(44, b.get_existing(4));

  // Independence: changing 'a' doesn't affect 'b'
  a.set_existing(2, 222);
  EXPECT_EQ(222, a.get_existing(2));
  EXPECT_EQ(22,  b.get_existing(2));
}

// Move constructor transfers observable contents
TEST_F(SparseArrayTest_584, MoveConstructor_TransfersContent_584) {
  SparseArray<int> src(3);
  src.set(1, 7);

  SparseArray<int> dst(std::move(src));

  // Destination has the observable content
  EXPECT_TRUE(dst.has_index(1));
  EXPECT_EQ(7, dst.get_existing(1));

  // We do not assert specifics about moved-from 'src' beyond validity.
  // It should be in a valid-but-unspecified state per typical C++ move rules.
}

// Copy & move assignment operators
TEST_F(SparseArrayTest_584, AssignmentOperators_CopyAndMove_584) {
  SparseArray<int> a(4);
  a.set(0, 10);
  a.set(3, 30);

  SparseArray<int> b(2);
  b = a;  // copy-assign
  EXPECT_EQ(a.max_size(), b.max_size());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_TRUE(b.has_index(0));
  EXPECT_TRUE(b.has_index(3));
  EXPECT_EQ(10, b.get_existing(0));
  EXPECT_EQ(30, b.get_existing(3));

  SparseArray<int> c(1);
  c = std::move(a);  // move-assign
  EXPECT_TRUE(c.has_index(0));
  EXPECT_TRUE(c.has_index(3));
  EXPECT_EQ(10, c.get_existing(0));
  EXPECT_EQ(30, c.get_existing(3));
  // No assertions about moved-from 'a' state.
}
