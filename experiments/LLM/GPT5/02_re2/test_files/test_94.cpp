// File: sparse_set_resize_test_94.cc
#include <gtest/gtest.h>
#include "re2/sparse_set.h"

namespace {

using re2::SparseSetT;

// A simple fixture to create sets with various initial sizes.
class SparseSetResizeTest_94 : public ::testing::Test {
protected:
  // Helper to populate the set with values [0, n)
  void InsertRange(SparseSetT<int>* s, int n) {
    for (int i = 0; i < n; ++i) {
      s->insert(i);
    }
  }
};

TEST_F(SparseSetResizeTest_94, ResizeGrowPreservesElements_94) {
  SparseSetT<int> s(5);
  // Insert a few elements inside the initial max_size.
  s->insert(0);
  s->insert(2);
  s->insert(4);

  ASSERT_EQ(s->max_size(), 5);
  ASSERT_EQ(s->size(), 3);

  // Grow the set; observable expectations:
  // - max_size() reflects the new capacity
  // - size() remains unchanged
  // - previously inserted elements remain present (observable via contains)
  s->resize(10);

  EXPECT_EQ(s->max_size(), 10);
  EXPECT_EQ(s->size(), 3);
  EXPECT_TRUE(s->contains(0));
  EXPECT_TRUE(s->contains(2));
  EXPECT_TRUE(s->contains(4));
  EXPECT_FALSE(s->contains(1));

  // After growing, inserting within the new bounds should work and affect size().
  s->insert(7);
  EXPECT_TRUE(s->contains(7));
  EXPECT_EQ(s->size(), 4);
}

TEST_F(SparseSetResizeTest_94, ResizeShrinkReducesSizeToNewMax_94) {
  SparseSetT<int> s(10);
  // Insert 7 distinct values: [0..6]
  InsertRange(&s, 7);
  ASSERT_EQ(s->size(), 7);
  ASSERT_EQ(s->max_size(), 10);

  // Shrink the set to 5. Observable expectations:
  // - max_size() becomes 5
  // - size() must not exceed new max_size(); the interface makes size() observable
  s->resize(5);

  EXPECT_EQ(s->max_size(), 5);
  EXPECT_EQ(s->size(), 5);

  // Inserting values within [0, new_max_size) should not exceed new_max_size.
  // (We don't assert which specific elements remain — only observable size bound.)
  for (int i = 0; i < s->max_size(); ++i) {
    s->insert(i);
  }
  EXPECT_LE(s->size(), s->max_size());
}

TEST_F(SparseSetResizeTest_94, ResizeToZeroClearsSet_94) {
  SparseSetT<int> s(6);
  InsertRange(&s, 4);  // Insert [0..3]
  ASSERT_EQ(s->size(), 4);
  ASSERT_EQ(s->max_size(), 6);

  // Resize to zero: observable expectations
  // - max_size() == 0
  // - size() == 0
  s->resize(0);
  EXPECT_EQ(s->max_size(), 0);
  EXPECT_EQ(s->size(), 0);

  // Growing again should allow inserts within the new bound.
  s->resize(3);
  EXPECT_EQ(s->max_size(), 3);
  EXPECT_EQ(s->size(), 0);

  s->insert(1);
  EXPECT_TRUE(s->contains(1));
  EXPECT_EQ(s->size(), 1);
}

TEST_F(SparseSetResizeTest_94, ResizeNoOpWhenEqualSize_94) {
  SparseSetT<int> s(4);
  s->insert(0);
  s->insert(3);
  const int size_before = s->size();

  // Resizing to the same max should leave observable state unchanged.
  s->resize(4);
  EXPECT_EQ(s->max_size(), 4);
  EXPECT_EQ(s->size(), size_before);
  EXPECT_TRUE(s->contains(0));
  EXPECT_TRUE(s->contains(3));
  EXPECT_FALSE(s->contains(2));
}

}  // namespace
