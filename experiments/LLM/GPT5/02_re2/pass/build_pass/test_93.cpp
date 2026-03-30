// File: sparse_set_insert_new_test_93.cc

#include <gtest/gtest.h>
#include "re2/sparse_set.h"

namespace re2 {

class SparseSetInsertNewTest_93 : public ::testing::Test {
protected:
  // Helper to count how many times a value appears by iterating [begin, end)
  template <typename SetT>
  int CountInIteration(const SetT& s, int value) {
    int count = 0;
    for (auto it = const_cast<SetT&>(s).begin(); it != const_cast<SetT&>(s).end(); ++it) {
      // We cannot assume element layout; compare by dereferencing iterator
      if (*it == value) ++count;
    }
    return count;
  }
};

// Normal operation: inserting a single value makes it present, increases size,
// and returns a valid iterator (not equal to end()).
TEST_F(SparseSetInsertNewTest_93, InsertNew_BasicPresenceAndIteratorValidity_93) {
  // Construct with a modest capacity to keep bounds meaningful.
  // Treating the implementation as a black box; we only rely on public API.
  SparseSetT<int> s(10);

  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());

  auto it = s.insert_new(3);

  // Returned iterator should be valid and within [begin, end)
  EXPECT_NE(it, s.end());

  // Observable effects
  EXPECT_EQ(s.size(), 1);
  EXPECT_FALSE(s.empty());
  EXPECT_TRUE(s.contains(3));

  // Value should be discoverable by iterating
  EXPECT_EQ(CountInIteration(s, 3), 1);
}

// Boundary conditions: insert lowest and highest valid indices.
TEST_F(SparseSetInsertNewTest_93, InsertNew_ZeroAndMaxMinusOne_93) {
  const int kMax = 5;
  SparseSetT<int> s(kMax);

  auto it0 = s.insert_new(0);
  EXPECT_NE(it0, s.end());
  EXPECT_TRUE(s.contains(0));

  auto it4 = s.insert_new(kMax - 1);
  EXPECT_NE(it4, s.end());
  EXPECT_TRUE(s.contains(kMax - 1));

  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(CountInIteration(s, 0), 1);
  EXPECT_EQ(CountInIteration(s, kMax - 1), 1);
}

// Normal operation with multiple distinct inserts: all become present,
// size matches number of unique inserted values, and iteration can see them.
TEST_F(SparseSetInsertNewTest_93, InsertNew_MultipleDistinctValues_93) {
  SparseSetT<int> s(16);

  (void)s.insert_new(1);
  (void)s.insert_new(3);
  (void)s.insert_new(2);

  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));

  EXPECT_EQ(CountInIteration(s, 1), 1);
  EXPECT_EQ(CountInIteration(s, 2), 1);
  EXPECT_EQ(CountInIteration(s, 3), 1);
}

// Interaction with other public APIs: clear() removes contents;
// inserting the same value again via insert_new should succeed as a fresh insert.
TEST_F(SparseSetInsertNewTest_93, InsertNew_AfterClear_93) {
  SparseSetT<int> s(10);

  (void)s.insert_new(7);
  EXPECT_TRUE(s.contains(7));
  EXPECT_EQ(s.size(), 1);

  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_FALSE(s.contains(7));

  auto it = s.insert_new(7);
  EXPECT_NE(it, s.end());
  EXPECT_TRUE(s.contains(7));
  EXPECT_EQ(s.size(), 1);
}

// Capacity-related boundary: after growing the set with resize(),
// inserting a value at the new upper range is observable via public API.
TEST_F(SparseSetInsertNewTest_93, InsertNew_AfterGrowResize_93) {
  SparseSetT<int> s(4);

  // Grow capacity; behavior verified only through successful insertion/contains.
  s.resize(8);

  auto it = s.insert_new(7);  // new upper range
  EXPECT_NE(it, s.end());
  EXPECT_TRUE(s.contains(7));
  EXPECT_EQ(s.size(), 1);
}

}  // namespace re2
