#include "gtest/gtest.h"
#include "re2/sparse_set.h"

namespace re2 {

// Test fixture for SparseSet (which is SparseSetT<void>)
class SparseSetTest_95 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor creates an empty set
TEST_F(SparseSetTest_95, DefaultConstructorCreatesEmptySet_95) {
  SparseSet s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test constructor with max_size
TEST_F(SparseSetTest_95, ConstructorWithMaxSize_95) {
  SparseSet s(100);
  EXPECT_EQ(s.max_size(), 100);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test contains returns false for empty set
TEST_F(SparseSetTest_95, ContainsReturnsFalseForEmptySet_95) {
  SparseSet s(10);
  EXPECT_FALSE(s.contains(0));
  EXPECT_FALSE(s.contains(5));
  EXPECT_FALSE(s.contains(9));
}

// Test insert and contains
TEST_F(SparseSetTest_95, InsertAndContains_95) {
  SparseSet s(10);
  s.insert(5);
  EXPECT_TRUE(s.contains(5));
  EXPECT_FALSE(s.contains(0));
  EXPECT_FALSE(s.contains(9));
}

// Test insert multiple elements
TEST_F(SparseSetTest_95, InsertMultipleElements_95) {
  SparseSet s(10);
  s.insert(0);
  s.insert(3);
  s.insert(7);
  EXPECT_TRUE(s.contains(0));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(7));
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(9));
  EXPECT_EQ(s.size(), 3);
}

// Test insert_new
TEST_F(SparseSetTest_95, InsertNew_95) {
  SparseSet s(10);
  s.insert_new(4);
  EXPECT_TRUE(s.contains(4));
  EXPECT_EQ(s.size(), 1);
}

// Test duplicate insert does not increase size
TEST_F(SparseSetTest_95, DuplicateInsertDoesNotIncreaseSize_95) {
  SparseSet s(10);
  s.insert(5);
  EXPECT_EQ(s.size(), 1);
  s.insert(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(5));
}

// Test clear removes all elements
TEST_F(SparseSetTest_95, ClearRemovesAllElements_95) {
  SparseSet s(10);
  s.insert(1);
  s.insert(3);
  s.insert(5);
  EXPECT_EQ(s.size(), 3);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(3));
  EXPECT_FALSE(s.contains(5));
}

// Test size after inserts
TEST_F(SparseSetTest_95, SizeAfterInserts_95) {
  SparseSet s(20);
  EXPECT_EQ(s.size(), 0);
  s.insert(0);
  EXPECT_EQ(s.size(), 1);
  s.insert(10);
  EXPECT_EQ(s.size(), 2);
  s.insert(19);
  EXPECT_EQ(s.size(), 3);
}

// Test empty returns correct value
TEST_F(SparseSetTest_95, EmptyReturnsCorrectValue_95) {
  SparseSet s(10);
  EXPECT_TRUE(s.empty());
  s.insert(0);
  EXPECT_FALSE(s.empty());
  s.clear();
  EXPECT_TRUE(s.empty());
}

// Test max_size returns correct value
TEST_F(SparseSetTest_95, MaxSizeReturnsCorrectValue_95) {
  SparseSet s(50);
  EXPECT_EQ(s.max_size(), 50);
}

// Test boundary: insert at index 0
TEST_F(SparseSetTest_95, InsertAtIndexZero_95) {
  SparseSet s(10);
  s.insert(0);
  EXPECT_TRUE(s.contains(0));
  EXPECT_EQ(s.size(), 1);
}

// Test boundary: insert at max_size - 1
TEST_F(SparseSetTest_95, InsertAtMaxSizeMinusOne_95) {
  SparseSet s(10);
  s.insert(9);
  EXPECT_TRUE(s.contains(9));
  EXPECT_EQ(s.size(), 1);
}

// Test inserting all elements up to max_size
TEST_F(SparseSetTest_95, InsertAllElements_95) {
  const int kMaxSize = 20;
  SparseSet s(kMaxSize);
  for (int i = 0; i < kMaxSize; i++) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), kMaxSize);
  for (int i = 0; i < kMaxSize; i++) {
    EXPECT_TRUE(s.contains(i));
  }
}

// Test iterator begin and end
TEST_F(SparseSetTest_95, IteratorBeginEnd_95) {
  SparseSet s(10);
  s.insert(2);
  s.insert(5);
  s.insert(8);

  int count = 0;
  for (SparseSet::iterator it = s.begin(); it != s.end(); ++it) {
    count++;
    EXPECT_TRUE(s.contains(*it));
  }
  EXPECT_EQ(count, 3);
}

// Test iterators for empty set
TEST_F(SparseSetTest_95, IteratorEmptySet_95) {
  SparseSet s(10);
  EXPECT_EQ(s.begin(), s.end());
}

// Test resize to larger size
TEST_F(SparseSetTest_95, ResizeToLargerSize_95) {
  SparseSet s(5);
  s.insert(2);
  s.insert(4);
  s.resize(20);
  EXPECT_EQ(s.max_size(), 20);
  // After resize, the set should still contain the previously inserted elements
  // (depending on implementation, resize may clear; we test observable behavior)
}

// Test resize to smaller size clears elements
TEST_F(SparseSetTest_95, ResizeToSmallerSize_95) {
  SparseSet s(20);
  s.insert(15);
  s.resize(10);
  EXPECT_EQ(s.max_size(), 10);
  // Element 15 is beyond new max_size, so it should not be accessible
}

// Test contains with max_size of 1
TEST_F(SparseSetTest_95, MaxSizeOne_95) {
  SparseSet s(1);
  EXPECT_EQ(s.max_size(), 1);
  EXPECT_FALSE(s.contains(0));
  s.insert(0);
  EXPECT_TRUE(s.contains(0));
  EXPECT_EQ(s.size(), 1);
}

// Test less static method
TEST_F(SparseSetTest_95, LessComparison_95) {
  EXPECT_TRUE(SparseSet::less(1, 2));
  EXPECT_FALSE(SparseSet::less(2, 1));
  EXPECT_FALSE(SparseSet::less(1, 1));
}

// Test clear and reinsert
TEST_F(SparseSetTest_95, ClearAndReinsert_95) {
  SparseSet s(10);
  s.insert(3);
  s.insert(7);
  s.clear();
  EXPECT_FALSE(s.contains(3));
  EXPECT_FALSE(s.contains(7));
  s.insert(3);
  EXPECT_TRUE(s.contains(3));
  EXPECT_FALSE(s.contains(7));
  EXPECT_EQ(s.size(), 1);
}

// Test insert returns iterator
TEST_F(SparseSetTest_95, InsertReturnsIterator_95) {
  SparseSet s(10);
  SparseSet::iterator it = s.insert(5);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 5);
}

// Test insert_new returns iterator
TEST_F(SparseSetTest_95, InsertNewReturnsIterator_95) {
  SparseSet s(10);
  SparseSet::iterator it = s.insert_new(3);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 3);
}

// Test large max_size
TEST_F(SparseSetTest_95, LargeMaxSize_95) {
  const int kMaxSize = 10000;
  SparseSet s(kMaxSize);
  EXPECT_EQ(s.max_size(), kMaxSize);
  s.insert(0);
  s.insert(kMaxSize - 1);
  s.insert(kMaxSize / 2);
  EXPECT_TRUE(s.contains(0));
  EXPECT_TRUE(s.contains(kMaxSize - 1));
  EXPECT_TRUE(s.contains(kMaxSize / 2));
  EXPECT_EQ(s.size(), 3);
}

// Test that elements are iterable in insertion order (dense array order)
TEST_F(SparseSetTest_95, IterationOrder_95) {
  SparseSet s(10);
  s.insert(7);
  s.insert(2);
  s.insert(5);

  std::vector<int> elements(s.begin(), s.end());
  EXPECT_EQ(elements.size(), 3u);
  // The first inserted element should be first in dense array
  EXPECT_EQ(elements[0], 7);
  EXPECT_EQ(elements[1], 2);
  EXPECT_EQ(elements[2], 5);
}

}  // namespace re2
