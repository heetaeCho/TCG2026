#include "gtest/gtest.h"
#include "re2/sparse_set.h"

namespace re2 {

// Test fixture for SparseSet tests
class SparseSetTest_91 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor
TEST_F(SparseSetTest_91, DefaultConstructor_91) {
  SparseSet s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test constructor with max_size
TEST_F(SparseSetTest_91, ConstructorWithMaxSize_91) {
  SparseSet s(100);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.max_size(), 100);
}

// Test insert and contains
TEST_F(SparseSetTest_91, InsertAndContains_91) {
  SparseSet s(100);
  s.insert(5);
  EXPECT_TRUE(s.contains(5));
  EXPECT_EQ(s.size(), 1);
  EXPECT_FALSE(s.empty());
}

// Test insert multiple elements
TEST_F(SparseSetTest_91, InsertMultipleElements_91) {
  SparseSet s(100);
  s.insert(5);
  s.insert(10);
  s.insert(50);
  EXPECT_TRUE(s.contains(5));
  EXPECT_TRUE(s.contains(10));
  EXPECT_TRUE(s.contains(50));
  EXPECT_EQ(s.size(), 3);
}

// Test insert duplicate element
TEST_F(SparseSetTest_91, InsertDuplicateElement_91) {
  SparseSet s(100);
  s.insert(5);
  s.insert(5);
  EXPECT_TRUE(s.contains(5));
  EXPECT_EQ(s.size(), 1);
}

// Test insert_new with unique element
TEST_F(SparseSetTest_91, InsertNewUniqueElement_91) {
  SparseSet s(100);
  s.insert_new(5);
  EXPECT_TRUE(s.contains(5));
  EXPECT_EQ(s.size(), 1);
}

// Test contains returns false for non-existent element
TEST_F(SparseSetTest_91, ContainsReturnsFalseForNonExistent_91) {
  SparseSet s(100);
  EXPECT_FALSE(s.contains(5));
  EXPECT_FALSE(s.contains(0));
  EXPECT_FALSE(s.contains(99));
}

// Test clear
TEST_F(SparseSetTest_91, ClearEmptiesSet_91) {
  SparseSet s(100);
  s.insert(5);
  s.insert(10);
  s.insert(50);
  EXPECT_EQ(s.size(), 3);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test clear makes contains return false
TEST_F(SparseSetTest_91, ClearMakesContainsFalse_91) {
  SparseSet s(100);
  s.insert(5);
  s.insert(10);
  EXPECT_TRUE(s.contains(5));
  EXPECT_TRUE(s.contains(10));
  s.clear();
  EXPECT_FALSE(s.contains(5));
  EXPECT_FALSE(s.contains(10));
}

// Test empty on empty set
TEST_F(SparseSetTest_91, EmptyOnEmptySet_91) {
  SparseSet s(100);
  EXPECT_TRUE(s.empty());
}

// Test empty on non-empty set
TEST_F(SparseSetTest_91, EmptyOnNonEmptySet_91) {
  SparseSet s(100);
  s.insert(1);
  EXPECT_FALSE(s.empty());
}

// Test max_size
TEST_F(SparseSetTest_91, MaxSizeReturnsCorrectValue_91) {
  SparseSet s(200);
  EXPECT_EQ(s.max_size(), 200);
}

// Test size
TEST_F(SparseSetTest_91, SizeReturnsCorrectValue_91) {
  SparseSet s(100);
  EXPECT_EQ(s.size(), 0);
  s.insert(1);
  EXPECT_EQ(s.size(), 1);
  s.insert(2);
  EXPECT_EQ(s.size(), 2);
  s.insert(3);
  EXPECT_EQ(s.size(), 3);
}

// Test begin and end iterators on empty set
TEST_F(SparseSetTest_91, BeginEqualsEndOnEmptySet_91) {
  SparseSet s(100);
  EXPECT_EQ(s.begin(), s.end());
}

// Test begin and end iterators with elements
TEST_F(SparseSetTest_91, IteratorsTraverseAllElements_91) {
  SparseSet s(100);
  s.insert(3);
  s.insert(7);
  s.insert(11);

  int count = 0;
  bool found3 = false, found7 = false, found11 = false;
  for (auto it = s.begin(); it != s.end(); ++it) {
    count++;
    if (*it == 3) found3 = true;
    if (*it == 7) found7 = true;
    if (*it == 11) found11 = true;
  }
  EXPECT_EQ(count, 3);
  EXPECT_TRUE(found3);
  EXPECT_TRUE(found7);
  EXPECT_TRUE(found11);
}

// Test resize
TEST_F(SparseSetTest_91, ResizeIncreasesMaxSize_91) {
  SparseSet s(10);
  EXPECT_EQ(s.max_size(), 10);
  s.resize(200);
  EXPECT_EQ(s.max_size(), 200);
}

// Test resize preserves existing elements (if within new range)
TEST_F(SparseSetTest_91, ResizePreservesElements_91) {
  SparseSet s(50);
  s.insert(5);
  s.insert(10);
  s.resize(100);
  EXPECT_TRUE(s.contains(5));
  EXPECT_TRUE(s.contains(10));
  EXPECT_EQ(s.size(), 2);
}

// Test insert at boundary (element 0)
TEST_F(SparseSetTest_91, InsertAtZero_91) {
  SparseSet s(100);
  s.insert(0);
  EXPECT_TRUE(s.contains(0));
  EXPECT_EQ(s.size(), 1);
}

// Test insert at boundary (element max_size - 1)
TEST_F(SparseSetTest_91, InsertAtMaxSizeMinusOne_91) {
  SparseSet s(100);
  s.insert(99);
  EXPECT_TRUE(s.contains(99));
  EXPECT_EQ(s.size(), 1);
}

// Test max_size of 1
TEST_F(SparseSetTest_91, MaxSizeOne_91) {
  SparseSet s(1);
  EXPECT_EQ(s.max_size(), 1);
  s.insert(0);
  EXPECT_TRUE(s.contains(0));
  EXPECT_EQ(s.size(), 1);
}

// Test clear on already empty set
TEST_F(SparseSetTest_91, ClearOnEmptySet_91) {
  SparseSet s(100);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test insert after clear
TEST_F(SparseSetTest_91, InsertAfterClear_91) {
  SparseSet s(100);
  s.insert(5);
  s.insert(10);
  s.clear();
  s.insert(15);
  EXPECT_FALSE(s.contains(5));
  EXPECT_FALSE(s.contains(10));
  EXPECT_TRUE(s.contains(15));
  EXPECT_EQ(s.size(), 1);
}

// Test re-inserting element after clear
TEST_F(SparseSetTest_91, ReinsertAfterClear_91) {
  SparseSet s(100);
  s.insert(5);
  EXPECT_TRUE(s.contains(5));
  s.clear();
  EXPECT_FALSE(s.contains(5));
  s.insert(5);
  EXPECT_TRUE(s.contains(5));
  EXPECT_EQ(s.size(), 1);
}

// Test filling set to capacity
TEST_F(SparseSetTest_91, FillToCapacity_91) {
  const int max_size = 50;
  SparseSet s(max_size);
  for (int i = 0; i < max_size; i++) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), max_size);
  for (int i = 0; i < max_size; i++) {
    EXPECT_TRUE(s.contains(i));
  }
}

// Test less static function
TEST_F(SparseSetTest_91, LessFunction_91) {
  EXPECT_TRUE(SparseSet::less(1, 2));
  EXPECT_FALSE(SparseSet::less(2, 1));
  EXPECT_FALSE(SparseSet::less(1, 1));
}

// Test less with negative values
TEST_F(SparseSetTest_91, LessWithNegativeValues_91) {
  EXPECT_TRUE(SparseSet::less(-1, 0));
  EXPECT_TRUE(SparseSet::less(-5, -2));
  EXPECT_FALSE(SparseSet::less(0, -1));
}

// Test iterator distance matches size
TEST_F(SparseSetTest_91, IteratorDistanceMatchesSize_91) {
  SparseSet s(100);
  s.insert(10);
  s.insert(20);
  s.insert(30);
  s.insert(40);
  s.insert(50);

  int distance = 0;
  for (auto it = s.begin(); it != s.end(); ++it) {
    distance++;
  }
  EXPECT_EQ(distance, s.size());
  EXPECT_EQ(distance, 5);
}

// Test multiple clears
TEST_F(SparseSetTest_91, MultipleClears_91) {
  SparseSet s(100);
  s.insert(1);
  s.clear();
  s.insert(2);
  s.insert(3);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(2));
  EXPECT_FALSE(s.contains(3));
}

// Test resize to smaller size (elements should still be tracked correctly)
TEST_F(SparseSetTest_91, ResizeSmaller_91) {
  SparseSet s(100);
  s.insert(5);
  s.resize(50);
  EXPECT_EQ(s.max_size(), 50);
  // Element 5 is still within range, but behavior after resize may vary
  // At least the set should not crash
}

// Test insert_new multiple unique elements
TEST_F(SparseSetTest_91, InsertNewMultipleUnique_91) {
  SparseSet s(100);
  s.insert_new(1);
  s.insert_new(2);
  s.insert_new(3);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

}  // namespace re2
