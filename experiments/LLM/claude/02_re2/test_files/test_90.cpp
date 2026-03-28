#include "gtest/gtest.h"
#include "re2/sparse_set.h"

namespace re2 {

// Test fixture for SparseSet tests
class SparseSetTest_90 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor creates empty set with max_size 0
TEST_F(SparseSetTest_90, DefaultConstructorCreatesEmptySet_90) {
  SparseSet s;
  EXPECT_EQ(s.max_size(), 0);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test constructor with max_size parameter
TEST_F(SparseSetTest_90, ParameterizedConstructorSetsMaxSize_90) {
  SparseSet s(100);
  EXPECT_EQ(s.max_size(), 100);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test constructor with max_size of 1
TEST_F(SparseSetTest_90, ConstructorWithMaxSizeOne_90) {
  SparseSet s(1);
  EXPECT_EQ(s.max_size(), 1);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test insert adds element to set
TEST_F(SparseSetTest_90, InsertAddsElement_90) {
  SparseSet s(10);
  s.insert(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_FALSE(s.empty());
  EXPECT_TRUE(s.contains(5));
}

// Test insert multiple elements
TEST_F(SparseSetTest_90, InsertMultipleElements_90) {
  SparseSet s(10);
  s.insert(1);
  s.insert(3);
  s.insert(7);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(7));
}

// Test insert duplicate element doesn't increase size
TEST_F(SparseSetTest_90, InsertDuplicateDoesNotIncreaseSize_90) {
  SparseSet s(10);
  s.insert(5);
  s.insert(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(5));
}

// Test insert_new adds element
TEST_F(SparseSetTest_90, InsertNewAddsElement_90) {
  SparseSet s(10);
  s.insert_new(3);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(3));
}

// Test contains returns false for element not in set
TEST_F(SparseSetTest_90, ContainsReturnsFalseForMissingElement_90) {
  SparseSet s(10);
  EXPECT_FALSE(s.contains(5));
}

// Test contains returns true for inserted element
TEST_F(SparseSetTest_90, ContainsReturnsTrueForInsertedElement_90) {
  SparseSet s(10);
  s.insert(5);
  EXPECT_TRUE(s.contains(5));
}

// Test clear removes all elements
TEST_F(SparseSetTest_90, ClearRemovesAllElements_90) {
  SparseSet s(10);
  s.insert(1);
  s.insert(3);
  s.insert(7);
  EXPECT_EQ(s.size(), 3);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(3));
  EXPECT_FALSE(s.contains(7));
}

// Test clear on empty set
TEST_F(SparseSetTest_90, ClearOnEmptySet_90) {
  SparseSet s(10);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test empty returns true for empty set
TEST_F(SparseSetTest_90, EmptyReturnsTrueForEmptySet_90) {
  SparseSet s(10);
  EXPECT_TRUE(s.empty());
}

// Test empty returns false for non-empty set
TEST_F(SparseSetTest_90, EmptyReturnsFalseForNonEmptySet_90) {
  SparseSet s(10);
  s.insert(0);
  EXPECT_FALSE(s.empty());
}

// Test begin and end iterators on empty set
TEST_F(SparseSetTest_90, BeginEqualsEndForEmptySet_90) {
  SparseSet s(10);
  EXPECT_EQ(s.begin(), s.end());
}

// Test iteration over elements
TEST_F(SparseSetTest_90, IterationOverElements_90) {
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

// Test insert element at boundary (0)
TEST_F(SparseSetTest_90, InsertElementAtZero_90) {
  SparseSet s(10);
  s.insert(0);
  EXPECT_TRUE(s.contains(0));
  EXPECT_EQ(s.size(), 1);
}

// Test insert element at boundary (max_size - 1)
TEST_F(SparseSetTest_90, InsertElementAtMaxSizeMinusOne_90) {
  SparseSet s(10);
  s.insert(9);
  EXPECT_TRUE(s.contains(9));
  EXPECT_EQ(s.size(), 1);
}

// Test fill set to capacity
TEST_F(SparseSetTest_90, FillSetToCapacity_90) {
  SparseSet s(5);
  for (int i = 0; i < 5; i++) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), 5);
  for (int i = 0; i < 5; i++) {
    EXPECT_TRUE(s.contains(i));
  }
}

// Test resize increases max_size
TEST_F(SparseSetTest_90, ResizeIncreasesMaxSize_90) {
  SparseSet s(5);
  s.insert(2);
  s.insert(4);
  s.resize(20);
  EXPECT_EQ(s.max_size(), 20);
  // After resize, previously inserted elements should still be present
  // (depending on implementation, resize may or may not preserve elements)
}

// Test resize from default-constructed set
TEST_F(SparseSetTest_90, ResizeFromDefaultConstructed_90) {
  SparseSet s;
  s.resize(10);
  EXPECT_EQ(s.max_size(), 10);
  EXPECT_EQ(s.size(), 0);
  s.insert(5);
  EXPECT_TRUE(s.contains(5));
}

// Test less static function
TEST_F(SparseSetTest_90, LessComparesCorrectly_90) {
  EXPECT_TRUE(SparseSet::less(1, 2));
  EXPECT_FALSE(SparseSet::less(2, 1));
  EXPECT_FALSE(SparseSet::less(1, 1));
}

// Test less with negative numbers
TEST_F(SparseSetTest_90, LessWithNegativeNumbers_90) {
  EXPECT_TRUE(SparseSet::less(-1, 0));
  EXPECT_TRUE(SparseSet::less(-2, -1));
  EXPECT_FALSE(SparseSet::less(0, -1));
}

// Test insert and clear cycle
TEST_F(SparseSetTest_90, InsertClearCycle_90) {
  SparseSet s(10);
  s.insert(3);
  s.insert(7);
  EXPECT_EQ(s.size(), 2);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_FALSE(s.contains(3));
  EXPECT_FALSE(s.contains(7));
  s.insert(3);
  s.insert(7);
  EXPECT_EQ(s.size(), 2);
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(7));
}

// Test large set
TEST_F(SparseSetTest_90, LargeSet_90) {
  const int kSize = 10000;
  SparseSet s(kSize);
  for (int i = 0; i < kSize; i += 2) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), kSize / 2);
  for (int i = 0; i < kSize; i++) {
    if (i % 2 == 0) {
      EXPECT_TRUE(s.contains(i));
    } else {
      EXPECT_FALSE(s.contains(i));
    }
  }
}

// Test insert returns iterator
TEST_F(SparseSetTest_90, InsertReturnsIterator_90) {
  SparseSet s(10);
  auto it = s.insert(5);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 5);
}

// Test insert_new returns iterator
TEST_F(SparseSetTest_90, InsertNewReturnsIterator_90) {
  SparseSet s(10);
  auto it = s.insert_new(5);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 5);
}

// Test size after multiple insertions and clear
TEST_F(SparseSetTest_90, SizeTracksCorrectly_90) {
  SparseSet s(100);
  EXPECT_EQ(s.size(), 0);
  for (int i = 0; i < 50; i++) {
    s.insert(i);
    EXPECT_EQ(s.size(), i + 1);
  }
  s.clear();
  EXPECT_EQ(s.size(), 0);
}

// Test max_size is correct after construction
TEST_F(SparseSetTest_90, MaxSizeCorrectAfterConstruction_90) {
  SparseSet s1(0);
  EXPECT_EQ(s1.max_size(), 0);

  SparseSet s2(1);
  EXPECT_EQ(s2.max_size(), 1);

  SparseSet s3(1000);
  EXPECT_EQ(s3.max_size(), 1000);
}

// Test contains after clear
TEST_F(SparseSetTest_90, ContainsAfterClear_90) {
  SparseSet s(10);
  for (int i = 0; i < 10; i++) {
    s.insert(i);
  }
  s.clear();
  for (int i = 0; i < 10; i++) {
    EXPECT_FALSE(s.contains(i));
  }
}

// Test iterator distance matches size
TEST_F(SparseSetTest_90, IteratorDistanceMatchesSize_90) {
  SparseSet s(20);
  s.insert(3);
  s.insert(7);
  s.insert(15);
  
  int count = 0;
  for (auto it = s.begin(); it != s.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, s.size());
}

}  // namespace re2
