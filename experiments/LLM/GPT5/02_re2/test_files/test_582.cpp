// File: sparse_array_copy_test_582.cc
#include <gtest/gtest.h>
#include <iterator>
#include "re2/sparse_array.h"

using re2::SparseArray;

namespace {

TEST(SparseArrayCopyTest_582, CopyFromEmptyWithCapacity_582) {
  SparseArray<int> a(8);                 // create with capacity, no elements
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.max_size(), 8);

  SparseArray<int> b(a);                 // copy-construct
  EXPECT_EQ(b.max_size(), a.max_size()); // capacity copied
  EXPECT_EQ(b.size(), a.size());         // size copied
  EXPECT_EQ(std::distance(b.begin(), b.end()), 0); // no iteration elements
  EXPECT_FALSE(b.has_index(0));          // no indices present
}

TEST(SparseArrayCopyTest_582, CopyFromDefaultConstructed_582) {
  SparseArray<int> a;                    // default constructor
  SparseArray<int> b(a);                 // copy-construct
  EXPECT_EQ(b.max_size(), a.max_size()); // whatever default is, it should match
  EXPECT_EQ(b.size(), a.size());
  EXPECT_EQ(std::distance(b.begin(), b.end()), 0);
}

TEST(SparseArrayCopyTest_582, CopyPreservesIndicesAndValues_582) {
  SparseArray<int> a(10);
  a.set(0, 1);
  a.set(5, 55);
  a.set(9, 99);

  SparseArray<int> b(a);                 // copy-construct

  // Size and capacity preserved
  EXPECT_EQ(b.max_size(), a.max_size());
  EXPECT_EQ(b.size(), a.size());

  // All copied indices should exist with same values
  ASSERT_TRUE(b.has_index(0));
  ASSERT_TRUE(b.has_index(5));
  ASSERT_TRUE(b.has_index(9));
  EXPECT_EQ(b.get_existing(0), 1);
  EXPECT_EQ(b.get_existing(5), 55);
  EXPECT_EQ(b.get_existing(9), 99);

  // Unset index should not exist
  EXPECT_FALSE(b.has_index(1));
}

TEST(SparseArrayCopyTest_582, CopyIsIndependentOfSource_582) {
  SparseArray<int> a(10);
  a.set(2, 200);
  a.set(7, 700);

  SparseArray<int> b(a);                 // copy-construct

  // Change the source after copying
  a.set(2, 222);
  a.clear();                             // remove everything from source

  // The copy should remain unchanged
  ASSERT_TRUE(b.has_index(2));
  ASSERT_TRUE(b.has_index(7));
  EXPECT_EQ(b.get_existing(2), 200);
  EXPECT_EQ(b.get_existing(7), 700);
  EXPECT_EQ(b.size(), 2);
}

TEST(SparseArrayCopyTest_582, CopyWithBoundaryIndices_582) {
  SparseArray<int> a(2);
  a.set(0, 7);
  a.set(1, 8);                           // highest valid index

  SparseArray<int> b(a);                 // copy-construct

  ASSERT_TRUE(b.has_index(0));
  ASSERT_TRUE(b.has_index(1));
  EXPECT_EQ(b.get_existing(0), 7);
  EXPECT_EQ(b.get_existing(1), 8);
  EXPECT_EQ(b.size(), 2);
  EXPECT_EQ(b.max_size(), 2);
}

}  // namespace
