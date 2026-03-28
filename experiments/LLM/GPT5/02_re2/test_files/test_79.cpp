// File: sparse_array_get_existing_test_79.cc
#include <gtest/gtest.h>
#include "re2/sparse_array.h"

namespace re2 {

class SparseArrayGetExistingTest_79 : public ::testing::Test {
protected:
  // Use a simple value type to observe behavior via public API.
  using SA = SparseArray<int>;
};

TEST_F(SparseArrayGetExistingTest_79, ReturnsStoredValue_79) {
  SA sa(/*max_size=*/8);
  const int idx = 3;
  const int val = 42;

  // Precondition setup via public API only.
  sa.set(idx, val);
  ASSERT_TRUE(sa.has_index(idx));

  // get_existing should return the stored value.
  int& ref = sa.get_existing(idx);
  EXPECT_EQ(ref, val);

  // And it should be a reference to the stored element (mutations reflect).
  ref = 99;
  EXPECT_EQ(sa.get_existing(idx), 99);
}

TEST_F(SparseArrayGetExistingTest_79, WorksWithMultipleIndices_79) {
  SA sa(/*max_size=*/10);
  sa.set(1, 10);
  sa.set(5, 50);
  sa.set(7, 70);

  ASSERT_TRUE(sa.has_index(1));
  ASSERT_TRUE(sa.has_index(5));
  ASSERT_TRUE(sa.has_index(7));

  EXPECT_EQ(sa.get_existing(1), 10);
  EXPECT_EQ(sa.get_existing(5), 50);
  EXPECT_EQ(sa.get_existing(7), 70);
}

TEST_F(SparseArrayGetExistingTest_79, BoundaryIndices_79) {
  const int max_size = 6;
  SA sa(max_size);

  // Lowest valid index
  sa.set(0, 111);
  ASSERT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 111);

  // Highest valid index (max_size - 1)
  sa.set(max_size - 1, 222);
  ASSERT_TRUE(sa.has_index(max_size - 1));
  EXPECT_EQ(sa.get_existing(max_size - 1), 222);
}

TEST_F(SparseArrayGetExistingTest_79, ReflectsUpdatesFromSetExisting_79) {
  SA sa(/*max_size=*/5);
  const int idx = 2;

  sa.set_new(idx, 5);
  ASSERT_TRUE(sa.has_index(idx));
  EXPECT_EQ(sa.get_existing(idx), 5);

  // Update the same index using the "existing" updater.
  sa.set_existing(idx, 77);
  EXPECT_EQ(sa.get_existing(idx), 77);
}

#ifndef NDEBUG
// get_existing asserts that the index exists; verify the observable failure in debug builds.
TEST_F(SparseArrayGetExistingTest_79, DeathWhenIndexMissing_79) {
  SA sa(/*max_size=*/4);

  // No set() performed; has_index should be false.
  EXPECT_FALSE(sa.has_index(1));

  // Expect process to die due to assertion failure.
  // The exact message is implementation-defined; just check that it crashes.
  ASSERT_DEATH({ (void)sa.get_existing(1); }, ".*");
}
#endif  // NDEBUG

}  // namespace re2
