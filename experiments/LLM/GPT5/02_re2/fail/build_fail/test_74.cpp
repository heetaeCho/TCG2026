// File: sparse_array_max_size_test_74.cc
#include "gtest/gtest.h"
#include "re2/sparse_array.h"

using re2::SparseArray;

class SparseArrayMaxSizeTest_74 : public ::testing::Test {};

// Default-constructed array should report 0 max size (no backing storage yet).
TEST_F(SparseArrayMaxSizeTest_74, DefaultIsZero_74) {
  SparseArray a;
  EXPECT_EQ(0, a.max_size());
}

// Growing via resize should update max_size to the new maximum.
TEST_F(SparseArrayMaxSizeTest_74, ResizeGrowUpdatesMaxSize_74) {
  SparseArray a;
  a.resize(10);
  EXPECT_EQ(10, a.max_size());
}

// Shrinking via resize should update max_size accordingly.
TEST_F(SparseArrayMaxSizeTest_74, ResizeShrinkUpdatesMaxSize_74) {
  SparseArray a;
  a.resize(10);
  ASSERT_EQ(10, a.max_size());  // precondition (observable)
  a.resize(4);
  EXPECT_EQ(4, a.max_size());
}

// Resizing to zero should result in max_size() == 0.
TEST_F(SparseArrayMaxSizeTest_74, ResizeToZero_74) {
  SparseArray a;
  a.resize(8);
  ASSERT_EQ(8, a.max_size());  // precondition
  a.resize(0);
  EXPECT_EQ(0, a.max_size());
}

// Copy construction should preserve the observable maximum size.
TEST_F(SparseArrayMaxSizeTest_74, CopyConstructorPreservesMaxSize_74) {
  SparseArray src;
  src.resize(7);
  ASSERT_EQ(7, src.max_size());

  SparseArray copy(src);
  EXPECT_EQ(7, copy.max_size());
  // Source should remain unchanged in observable behavior.
  EXPECT_EQ(7, src.max_size());
}

// Copy assignment should preserve the observable maximum size.
TEST_F(SparseArrayMaxSizeTest_74, CopyAssignmentPreservesMaxSize_74) {
  SparseArray src;
  src.resize(12);
  SparseArray dst;
  dst.resize(3);

  ASSERT_EQ(12, src.max_size());
  ASSERT_EQ(3, dst.max_size());

  dst = src;
  EXPECT_EQ(12, dst.max_size());
  // Source remains unchanged from an observable perspective.
  EXPECT_EQ(12, src.max_size());
}

// Multiple resizes should always reflect the latest requested maximum size.
TEST_F(SparseArrayMaxSizeTest_74, MultipleResizesReflectLatest_74) {
  SparseArray a;
  a.resize(5);
  EXPECT_EQ(5, a.max_size());
  a.resize(15);
  EXPECT_EQ(15, a.max_size());
  a.resize(1);
  EXPECT_EQ(1, a.max_size());
}
