// File: sparse_set_empty_test_89.cc
#include <gtest/gtest.h>
#include "re2/sparse_set.h"

namespace re2 {

class SparseSetEmptyTest_89 : public ::testing::Test {};

// [Normal] Freshly constructed set is empty.
TEST_F(SparseSetEmptyTest_89, DefaultConstructedIsEmpty_89) {
  SparseSet s; // Alias to SparseSetT<void> in the provided interface notes.
  // empty() is declared to return int in the snippet; treat non-zero as true.
  EXPECT_NE(0, s.empty());
}

// [Normal] After inserting one element, the set is not empty.
TEST_F(SparseSetEmptyTest_89, InsertMakesNonEmpty_89) {
  // Use explicit capacity to avoid relying on unspecified defaults.
  SparseSetT<void> s(/*max_size=*/8);
  s.insert(3);
  EXPECT_EQ(0, s.empty());  // non-empty -> empty() should be 0/false
}

// [Normal] Clearing a non-empty set makes it empty again.
TEST_F(SparseSetEmptyTest_89, ClearRestoresEmpty_89) {
  SparseSetT<void> s(/*max_size=*/8);
  s.insert(1);
  ASSERT_EQ(0, s.empty());  // precondition: became non-empty
  s.clear();
  EXPECT_NE(0, s.empty());
}

// [Boundary] Inserting the lowest valid index transitions from empty to non-empty.
TEST_F(SparseSetEmptyTest_89, InsertMinIndexAffectsEmpty_89) {
  SparseSetT<void> s(/*max_size=*/4);
  EXPECT_NE(0, s.empty());  // starts empty
  s.insert(0);              // boundary: lowest index
  EXPECT_EQ(0, s.empty());  // now non-empty
}

// [Boundary] Inserting the highest valid index transitions from empty to non-empty.
TEST_F(SparseSetEmptyTest_89, InsertMaxIndexAffectsEmpty_89) {
  const int cap = 5;
  SparseSetT<void> s(cap);
  EXPECT_NE(0, s.empty());   // starts empty
  s.insert(cap - 1);         // boundary: highest index within capacity
  EXPECT_EQ(0, s.empty());   // now non-empty
}

}  // namespace re2
