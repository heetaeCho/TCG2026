#include "re2/sparse_set.h"
#include <gtest/gtest.h>

namespace re2 {

class SparseSetTest_97 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor
TEST_F(SparseSetTest_97, DefaultConstructor_97) {
  SparseSet s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test constructor with max_size
TEST_F(SparseSetTest_97, ConstructorWithMaxSize_97) {
  SparseSet s(100);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.max_size(), 100);
}

// Test constructor with zero max_size
TEST_F(SparseSetTest_97, ConstructorWithZeroMaxSize_97) {
  SparseSet s(0);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.max_size(), 0);
}

// Test insert single element
TEST_F(SparseSetTest_97, InsertSingleElement_97) {
  SparseSet s(10);
  s.insert(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_FALSE(s.empty());
  EXPECT_TRUE(s.contains(5));
}

// Test insert multiple elements
TEST_F(SparseSetTest_97, InsertMultipleElements_97) {
  SparseSet s(10);
  s.insert(0);
  s.insert(3);
  s.insert(7);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(0));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(7));
}

// Test insert duplicate element
TEST_F(SparseSetTest_97, InsertDuplicateElement_97) {
  SparseSet s(10);
  s.insert(5);
  s.insert(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(5));
}

// Test insert_new
TEST_F(SparseSetTest_97, InsertNew_97) {
  SparseSet s(10);
  s.insert_new(3);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(3));
}

// Test contains returns false for non-existent element
TEST_F(SparseSetTest_97, ContainsReturnsFalseForNonExistent_97) {
  SparseSet s(10);
  EXPECT_FALSE(s.contains(0));
  EXPECT_FALSE(s.contains(5));
  EXPECT_FALSE(s.contains(9));
}

// Test contains after insert
TEST_F(SparseSetTest_97, ContainsAfterInsert_97) {
  SparseSet s(10);
  s.insert(4);
  EXPECT_TRUE(s.contains(4));
  EXPECT_FALSE(s.contains(3));
}

// Test clear
TEST_F(SparseSetTest_97, Clear_97) {
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

// Test clear on empty set
TEST_F(SparseSetTest_97, ClearOnEmptySet_97) {
  SparseSet s(10);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test size
TEST_F(SparseSetTest_97, Size_97) {
  SparseSet s(10);
  EXPECT_EQ(s.size(), 0);
  s.insert(1);
  EXPECT_EQ(s.size(), 1);
  s.insert(2);
  EXPECT_EQ(s.size(), 2);
  s.insert(2);
  EXPECT_EQ(s.size(), 2);  // duplicate, no change
}

// Test empty
TEST_F(SparseSetTest_97, Empty_97) {
  SparseSet s(10);
  EXPECT_TRUE(s.empty());
  s.insert(0);
  EXPECT_FALSE(s.empty());
  s.clear();
  EXPECT_TRUE(s.empty());
}

// Test max_size
TEST_F(SparseSetTest_97, MaxSize_97) {
  SparseSet s(50);
  EXPECT_EQ(s.max_size(), 50);
}

// Test begin and end on empty set
TEST_F(SparseSetTest_97, BeginEndEmptySet_97) {
  SparseSet s(10);
  EXPECT_EQ(s.begin(), s.end());
}

// Test iteration over elements
TEST_F(SparseSetTest_97, Iteration_97) {
  SparseSet s(10);
  s.insert(2);
  s.insert(5);
  s.insert(8);

  int count = 0;
  bool found2 = false, found5 = false, found8 = false;
  for (auto it = s.begin(); it != s.end(); ++it) {
    count++;
    if (*it == 2) found2 = true;
    if (*it == 5) found5 = true;
    if (*it == 8) found8 = true;
  }
  EXPECT_EQ(count, 3);
  EXPECT_TRUE(found2);
  EXPECT_TRUE(found5);
  EXPECT_TRUE(found8);
}

// Test less static function
TEST_F(SparseSetTest_97, LessFunction_97) {
  EXPECT_TRUE(SparseSet::less(1, 2));
  EXPECT_FALSE(SparseSet::less(2, 1));
  EXPECT_FALSE(SparseSet::less(2, 2));
  EXPECT_TRUE(SparseSet::less(-1, 0));
  EXPECT_TRUE(SparseSet::less(0, 1));
}

// Test resize
TEST_F(SparseSetTest_97, Resize_97) {
  SparseSet s(10);
  s.insert(3);
  s.insert(5);
  s.resize(20);
  EXPECT_EQ(s.max_size(), 20);
  // After resize, the set should still function
  s.insert(15);
  EXPECT_TRUE(s.contains(15));
}

// Test resize to larger size preserves no elements (behavior may vary)
TEST_F(SparseSetTest_97, ResizeFromSmallToLarger_97) {
  SparseSet s(5);
  s.insert(2);
  s.resize(10);
  EXPECT_EQ(s.max_size(), 10);
}

// Test insert at boundary (max_size - 1)
TEST_F(SparseSetTest_97, InsertAtMaxSizeBoundary_97) {
  SparseSet s(10);
  s.insert(9);
  EXPECT_TRUE(s.contains(9));
  EXPECT_EQ(s.size(), 1);
}

// Test insert element 0
TEST_F(SparseSetTest_97, InsertZero_97) {
  SparseSet s(10);
  s.insert(0);
  EXPECT_TRUE(s.contains(0));
  EXPECT_EQ(s.size(), 1);
}

// Test insert all elements up to max_size
TEST_F(SparseSetTest_97, InsertAllElements_97) {
  const int max_sz = 20;
  SparseSet s(max_sz);
  for (int i = 0; i < max_sz; i++) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), max_sz);
  for (int i = 0; i < max_sz; i++) {
    EXPECT_TRUE(s.contains(i));
  }
}

// Test clear and reinsert
TEST_F(SparseSetTest_97, ClearAndReinsert_97) {
  SparseSet s(10);
  s.insert(1);
  s.insert(2);
  s.clear();
  s.insert(3);
  s.insert(4);
  EXPECT_EQ(s.size(), 2);
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(4));
}

// Test constructor with large max_size
TEST_F(SparseSetTest_97, LargeMaxSize_97) {
  SparseSet s(10000);
  EXPECT_EQ(s.max_size(), 10000);
  s.insert(9999);
  EXPECT_TRUE(s.contains(9999));
  EXPECT_EQ(s.size(), 1);
}

// Test insert returns iterator
TEST_F(SparseSetTest_97, InsertReturnsIterator_97) {
  SparseSet s(10);
  auto it = s.insert(5);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 5);
}

// Test insert_new returns iterator
TEST_F(SparseSetTest_97, InsertNewReturnsIterator_97) {
  SparseSet s(10);
  auto it = s.insert_new(7);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 7);
}

// Test less with equal values
TEST_F(SparseSetTest_97, LessEqualValues_97) {
  EXPECT_FALSE(SparseSet::less(5, 5));
}

// Test less with negative values
TEST_F(SparseSetTest_97, LessNegativeValues_97) {
  EXPECT_TRUE(SparseSet::less(-10, -5));
  EXPECT_FALSE(SparseSet::less(-5, -10));
}

// Test multiple clears
TEST_F(SparseSetTest_97, MultipleClears_97) {
  SparseSet s(10);
  s.insert(1);
  s.clear();
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test resize to 1
TEST_F(SparseSetTest_97, ResizeToOne_97) {
  SparseSet s(10);
  s.resize(1);
  EXPECT_EQ(s.max_size(), 1);
  s.insert(0);
  EXPECT_TRUE(s.contains(0));
  EXPECT_EQ(s.size(), 1);
}

}  // namespace re2
