#include "gtest/gtest.h"
#include "re2/sparse_set.h"

namespace re2 {

// Test fixture for SparseSet tests
class SparseSetTest_89 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor creates an empty set
TEST_F(SparseSetTest_89, DefaultConstructorCreatesEmptySet_89) {
  SparseSet s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

// Test constructor with max_size creates an empty set
TEST_F(SparseSetTest_89, ParameterizedConstructorCreatesEmptySet_89) {
  SparseSet s(100);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
  EXPECT_EQ(s.max_size(), 100);
}

// Test inserting a single element
TEST_F(SparseSetTest_89, InsertSingleElement_89) {
  SparseSet s(10);
  s.insert(5);
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(5));
}

// Test inserting multiple elements
TEST_F(SparseSetTest_89, InsertMultipleElements_89) {
  SparseSet s(10);
  s.insert(1);
  s.insert(3);
  s.insert(7);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(7));
}

// Test that inserting duplicate element does not increase size
TEST_F(SparseSetTest_89, InsertDuplicateElement_89) {
  SparseSet s(10);
  s.insert(5);
  s.insert(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(5));
}

// Test contains returns false for non-existent element
TEST_F(SparseSetTest_89, ContainsReturnsFalseForMissingElement_89) {
  SparseSet s(10);
  s.insert(3);
  EXPECT_FALSE(s.contains(5));
  EXPECT_FALSE(s.contains(0));
  EXPECT_FALSE(s.contains(9));
}

// Test clear empties the set
TEST_F(SparseSetTest_89, ClearEmptiesTheSet_89) {
  SparseSet s(10);
  s.insert(1);
  s.insert(2);
  s.insert(3);
  EXPECT_EQ(s.size(), 3);
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(2));
  EXPECT_FALSE(s.contains(3));
}

// Test empty on a non-empty set returns false
TEST_F(SparseSetTest_89, EmptyReturnsFalseWhenNonEmpty_89) {
  SparseSet s(10);
  s.insert(0);
  EXPECT_FALSE(s.empty());
}

// Test empty on an empty set returns true
TEST_F(SparseSetTest_89, EmptyReturnsTrueWhenEmpty_89) {
  SparseSet s(10);
  EXPECT_TRUE(s.empty());
}

// Test max_size returns correct value
TEST_F(SparseSetTest_89, MaxSizeReturnsCorrectValue_89) {
  SparseSet s(50);
  EXPECT_EQ(s.max_size(), 50);
}

// Test insert_new for a new element
TEST_F(SparseSetTest_89, InsertNewAddsElement_89) {
  SparseSet s(10);
  s.insert_new(4);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(4));
}

// Test inserting element at boundary (0)
TEST_F(SparseSetTest_89, InsertElementAtZero_89) {
  SparseSet s(10);
  s.insert(0);
  EXPECT_TRUE(s.contains(0));
  EXPECT_EQ(s.size(), 1);
}

// Test inserting element at max boundary (max_size - 1)
TEST_F(SparseSetTest_89, InsertElementAtMaxBoundary_89) {
  SparseSet s(10);
  s.insert(9);
  EXPECT_TRUE(s.contains(9));
  EXPECT_EQ(s.size(), 1);
}

// Test begin and end iterators on empty set
TEST_F(SparseSetTest_89, BeginEqualsEndWhenEmpty_89) {
  SparseSet s(10);
  EXPECT_EQ(s.begin(), s.end());
}

// Test begin and end iterators on non-empty set
TEST_F(SparseSetTest_89, BeginNotEqualsEndWhenNonEmpty_89) {
  SparseSet s(10);
  s.insert(5);
  EXPECT_NE(s.begin(), s.end());
}

// Test iteration over all elements
TEST_F(SparseSetTest_89, IterationOverElements_89) {
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

// Test resize increases max_size
TEST_F(SparseSetTest_89, ResizeIncreasesMaxSize_89) {
  SparseSet s(5);
  EXPECT_EQ(s.max_size(), 5);
  s.resize(20);
  EXPECT_EQ(s.max_size(), 20);
}

// Test resize preserves emptiness when no elements inserted
TEST_F(SparseSetTest_89, ResizeOnEmptySetKeepsEmpty_89) {
  SparseSet s(5);
  s.resize(20);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

// Test inserting after clear
TEST_F(SparseSetTest_89, InsertAfterClear_89) {
  SparseSet s(10);
  s.insert(1);
  s.insert(2);
  s.clear();
  s.insert(3);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(3));
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(2));
}

// Test inserting all elements up to max_size
TEST_F(SparseSetTest_89, InsertAllElements_89) {
  const int max = 10;
  SparseSet s(max);
  for (int i = 0; i < max; i++) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), max);
  for (int i = 0; i < max; i++) {
    EXPECT_TRUE(s.contains(i));
  }
}

// Test size after multiple insertions and clear cycles
TEST_F(SparseSetTest_89, MultipleClearCycles_89) {
  SparseSet s(10);
  s.insert(1);
  s.insert(2);
  EXPECT_EQ(s.size(), 2);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  s.insert(3);
  EXPECT_EQ(s.size(), 1);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test less static function
TEST_F(SparseSetTest_89, LessComparison_89) {
  EXPECT_TRUE(SparseSet::less(1, 2));
  EXPECT_FALSE(SparseSet::less(2, 1));
  EXPECT_FALSE(SparseSet::less(2, 2));
}

// Test with max_size of 1
TEST_F(SparseSetTest_89, MaxSizeOne_89) {
  SparseSet s(1);
  EXPECT_EQ(s.max_size(), 1);
  EXPECT_TRUE(s.empty());
  s.insert(0);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(0));
}

// Test resize to smaller value after clear
TEST_F(SparseSetTest_89, ResizeSmaller_89) {
  SparseSet s(20);
  s.clear();
  s.resize(5);
  EXPECT_EQ(s.max_size(), 5);
  s.insert(3);
  EXPECT_TRUE(s.contains(3));
}

// Test distance between begin and end equals size
TEST_F(SparseSetTest_89, IteratorDistanceEqualsSize_89) {
  SparseSet s(10);
  s.insert(1);
  s.insert(4);
  s.insert(7);
  int count = 0;
  for (auto it = s.begin(); it != s.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, s.size());
}

// Test contains on empty set
TEST_F(SparseSetTest_89, ContainsOnEmptySet_89) {
  SparseSet s(10);
  EXPECT_FALSE(s.contains(0));
  EXPECT_FALSE(s.contains(5));
  EXPECT_FALSE(s.contains(9));
}

}  // namespace re2
