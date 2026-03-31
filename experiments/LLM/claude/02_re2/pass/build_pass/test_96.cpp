#include "gtest/gtest.h"
#include "re2/sparse_set.h"

namespace re2 {

// Test fixture for SparseSet tests
class SparseSetTest_96 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor
TEST_F(SparseSetTest_96, DefaultConstructor_96) {
  SparseSet s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test constructor with max_size
TEST_F(SparseSetTest_96, ConstructorWithMaxSize_96) {
  SparseSet s(100);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.max_size(), 100);
}

// Test constructor with zero max_size
TEST_F(SparseSetTest_96, ConstructorWithZeroMaxSize_96) {
  SparseSet s(0);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.max_size(), 0);
}

// Test insert and contains
TEST_F(SparseSetTest_96, InsertAndContains_96) {
  SparseSet s(10);
  s.insert(5);
  EXPECT_TRUE(s.contains(5));
  EXPECT_EQ(s.size(), 1);
  EXPECT_FALSE(s.empty());
}

// Test insert multiple elements
TEST_F(SparseSetTest_96, InsertMultipleElements_96) {
  SparseSet s(10);
  s.insert(0);
  s.insert(3);
  s.insert(7);
  EXPECT_TRUE(s.contains(0));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(7));
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(5));
  EXPECT_EQ(s.size(), 3);
}

// Test insert duplicate element
TEST_F(SparseSetTest_96, InsertDuplicateElement_96) {
  SparseSet s(10);
  s.insert(5);
  s.insert(5);
  EXPECT_TRUE(s.contains(5));
  EXPECT_EQ(s.size(), 1);
}

// Test insert_new for new element
TEST_F(SparseSetTest_96, InsertNewElement_96) {
  SparseSet s(10);
  s.insert_new(3);
  EXPECT_TRUE(s.contains(3));
  EXPECT_EQ(s.size(), 1);
}

// Test contains returns false for non-existent element
TEST_F(SparseSetTest_96, ContainsReturnsFalseForNonExistent_96) {
  SparseSet s(10);
  EXPECT_FALSE(s.contains(0));
  EXPECT_FALSE(s.contains(5));
  EXPECT_FALSE(s.contains(9));
}

// Test clear
TEST_F(SparseSetTest_96, Clear_96) {
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

// Test empty on empty set
TEST_F(SparseSetTest_96, EmptyOnEmptySet_96) {
  SparseSet s(10);
  EXPECT_TRUE(s.empty());
}

// Test empty on non-empty set
TEST_F(SparseSetTest_96, EmptyOnNonEmptySet_96) {
  SparseSet s(10);
  s.insert(2);
  EXPECT_FALSE(s.empty());
}

// Test size
TEST_F(SparseSetTest_96, Size_96) {
  SparseSet s(10);
  EXPECT_EQ(s.size(), 0);
  s.insert(1);
  EXPECT_EQ(s.size(), 1);
  s.insert(2);
  EXPECT_EQ(s.size(), 2);
  s.insert(3);
  EXPECT_EQ(s.size(), 3);
}

// Test max_size
TEST_F(SparseSetTest_96, MaxSize_96) {
  SparseSet s(50);
  EXPECT_EQ(s.max_size(), 50);
}

// Test begin and end iterators on empty set
TEST_F(SparseSetTest_96, BeginEndEmpty_96) {
  SparseSet s(10);
  EXPECT_EQ(s.begin(), s.end());
}

// Test begin and end iterators on non-empty set
TEST_F(SparseSetTest_96, BeginEndNonEmpty_96) {
  SparseSet s(10);
  s.insert(3);
  s.insert(7);
  EXPECT_NE(s.begin(), s.end());
  int count = 0;
  for (auto it = s.begin(); it != s.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 2);
}

// Test iteration over elements
TEST_F(SparseSetTest_96, IterateElements_96) {
  SparseSet s(10);
  s.insert(2);
  s.insert(5);
  s.insert(8);
  
  std::set<int> found;
  for (auto it = s.begin(); it != s.end(); ++it) {
    found.insert(*it);
  }
  EXPECT_EQ(found.size(), 3u);
  EXPECT_TRUE(found.count(2));
  EXPECT_TRUE(found.count(5));
  EXPECT_TRUE(found.count(8));
}

// Test resize
TEST_F(SparseSetTest_96, Resize_96) {
  SparseSet s(5);
  EXPECT_EQ(s.max_size(), 5);
  s.resize(20);
  EXPECT_EQ(s.max_size(), 20);
  s.insert(15);
  EXPECT_TRUE(s.contains(15));
}

// Test resize preserves existing elements (if applicable)
TEST_F(SparseSetTest_96, ResizePreservation_96) {
  SparseSet s(10);
  s.insert(3);
  s.insert(7);
  s.resize(20);
  // After resize, the set should be usable; existing elements may or may not be preserved
  // based on implementation, but max_size should be updated
  EXPECT_EQ(s.max_size(), 20);
}

// Test boundary: insert element at index 0
TEST_F(SparseSetTest_96, InsertAtIndexZero_96) {
  SparseSet s(10);
  s.insert(0);
  EXPECT_TRUE(s.contains(0));
  EXPECT_EQ(s.size(), 1);
}

// Test boundary: insert element at max_size - 1
TEST_F(SparseSetTest_96, InsertAtMaxSizeMinusOne_96) {
  SparseSet s(10);
  s.insert(9);
  EXPECT_TRUE(s.contains(9));
  EXPECT_EQ(s.size(), 1);
}

// Test filling the entire set
TEST_F(SparseSetTest_96, FillEntireSet_96) {
  const int max_size = 10;
  SparseSet s(max_size);
  for (int i = 0; i < max_size; i++) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), max_size);
  for (int i = 0; i < max_size; i++) {
    EXPECT_TRUE(s.contains(i));
  }
}

// Test clear and reinsert
TEST_F(SparseSetTest_96, ClearAndReinsert_96) {
  SparseSet s(10);
  s.insert(1);
  s.insert(2);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  s.insert(3);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(3));
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(2));
}

// Test less static function
TEST_F(SparseSetTest_96, LessFunction_96) {
  EXPECT_TRUE(SparseSet::less(1, 2));
  EXPECT_FALSE(SparseSet::less(2, 1));
  EXPECT_FALSE(SparseSet::less(1, 1));
}

// Test less with negative numbers
TEST_F(SparseSetTest_96, LessWithNegativeNumbers_96) {
  EXPECT_TRUE(SparseSet::less(-1, 0));
  EXPECT_TRUE(SparseSet::less(-5, -3));
  EXPECT_FALSE(SparseSet::less(0, -1));
}

// Test large max_size
TEST_F(SparseSetTest_96, LargeMaxSize_96) {
  SparseSet s(10000);
  EXPECT_EQ(s.max_size(), 10000);
  s.insert(9999);
  EXPECT_TRUE(s.contains(9999));
  EXPECT_EQ(s.size(), 1);
}

// Test multiple clears
TEST_F(SparseSetTest_96, MultipleClears_96) {
  SparseSet s(10);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  s.insert(5);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  s.clear();
  EXPECT_EQ(s.size(), 0);
}

// Test insert returns iterator
TEST_F(SparseSetTest_96, InsertReturnsIterator_96) {
  SparseSet s(10);
  auto it = s.insert(5);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 5);
}

// Test insert_new returns iterator
TEST_F(SparseSetTest_96, InsertNewReturnsIterator_96) {
  SparseSet s(10);
  auto it = s.insert_new(7);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 7);
}

// Test max_size with constructor parameter 1
TEST_F(SparseSetTest_96, MaxSizeOne_96) {
  SparseSet s(1);
  EXPECT_EQ(s.max_size(), 1);
  s.insert(0);
  EXPECT_TRUE(s.contains(0));
  EXPECT_EQ(s.size(), 1);
}

}  // namespace re2
