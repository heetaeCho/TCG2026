#include "gtest/gtest.h"
#include "re2/sparse_set.h"

namespace re2 {

class SparseSetTest_92 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor and basic state
TEST_F(SparseSetTest_92, DefaultConstructor_92) {
  SparseSet s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test parameterized constructor
TEST_F(SparseSetTest_92, ParameterizedConstructor_92) {
  SparseSet s(10);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.max_size(), 10);
}

// Test insert single element
TEST_F(SparseSetTest_92, InsertSingleElement_92) {
  SparseSet s(10);
  s.insert(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_FALSE(s.empty());
  EXPECT_TRUE(s.contains(5));
}

// Test insert multiple elements
TEST_F(SparseSetTest_92, InsertMultipleElements_92) {
  SparseSet s(10);
  s.insert(1);
  s.insert(3);
  s.insert(7);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(7));
  EXPECT_FALSE(s.contains(0));
  EXPECT_FALSE(s.contains(2));
  EXPECT_FALSE(s.contains(9));
}

// Test insert duplicate element
TEST_F(SparseSetTest_92, InsertDuplicateElement_92) {
  SparseSet s(10);
  s.insert(5);
  s.insert(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(5));
}

// Test insert_new for a new element
TEST_F(SparseSetTest_92, InsertNew_92) {
  SparseSet s(10);
  s.insert_new(3);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(3));
}

// Test contains returns false for absent element
TEST_F(SparseSetTest_92, ContainsReturnsFalseForAbsent_92) {
  SparseSet s(10);
  EXPECT_FALSE(s.contains(0));
  EXPECT_FALSE(s.contains(5));
  EXPECT_FALSE(s.contains(9));
}

// Test contains returns true for present element
TEST_F(SparseSetTest_92, ContainsReturnsTrueForPresent_92) {
  SparseSet s(10);
  s.insert(4);
  EXPECT_TRUE(s.contains(4));
}

// Test clear
TEST_F(SparseSetTest_92, ClearEmptiesSet_92) {
  SparseSet s(10);
  s.insert(1);
  s.insert(2);
  s.insert(3);
  EXPECT_EQ(s.size(), 3);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(2));
  EXPECT_FALSE(s.contains(3));
}

// Test clear on already empty set
TEST_F(SparseSetTest_92, ClearOnEmptySet_92) {
  SparseSet s(10);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test size
TEST_F(SparseSetTest_92, SizeReflectsInsertions_92) {
  SparseSet s(20);
  EXPECT_EQ(s.size(), 0);
  s.insert(0);
  EXPECT_EQ(s.size(), 1);
  s.insert(5);
  EXPECT_EQ(s.size(), 2);
  s.insert(10);
  EXPECT_EQ(s.size(), 3);
  // Duplicate should not increase size
  s.insert(5);
  EXPECT_EQ(s.size(), 3);
}

// Test empty
TEST_F(SparseSetTest_92, EmptyReflectsState_92) {
  SparseSet s(10);
  EXPECT_TRUE(s.empty());
  s.insert(0);
  EXPECT_FALSE(s.empty());
  s.clear();
  EXPECT_TRUE(s.empty());
}

// Test max_size
TEST_F(SparseSetTest_92, MaxSizeReturnsConstructorValue_92) {
  SparseSet s(100);
  EXPECT_EQ(s.max_size(), 100);
}

// Test begin and end on empty set
TEST_F(SparseSetTest_92, BeginEqualsEndOnEmpty_92) {
  SparseSet s(10);
  EXPECT_EQ(s.begin(), s.end());
}

// Test iteration over elements
TEST_F(SparseSetTest_92, IterationOverElements_92) {
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
TEST_F(SparseSetTest_92, ResizeIncreasesMaxSize_92) {
  SparseSet s(5);
  EXPECT_EQ(s.max_size(), 5);
  s.resize(20);
  EXPECT_EQ(s.max_size(), 20);
}

// Test resize preserves existing elements (if applicable)
TEST_F(SparseSetTest_92, ResizePreservesElements_92) {
  SparseSet s(10);
  s.insert(3);
  s.insert(7);
  s.resize(20);
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(7));
  EXPECT_EQ(s.size(), 2);
}

// Test inserting element 0 (boundary)
TEST_F(SparseSetTest_92, InsertZero_92) {
  SparseSet s(10);
  s.insert(0);
  EXPECT_TRUE(s.contains(0));
  EXPECT_EQ(s.size(), 1);
}

// Test inserting max_size - 1 (boundary)
TEST_F(SparseSetTest_92, InsertMaxMinusOne_92) {
  SparseSet s(10);
  s.insert(9);
  EXPECT_TRUE(s.contains(9));
  EXPECT_EQ(s.size(), 1);
}

// Test insert all elements up to max_size
TEST_F(SparseSetTest_92, InsertAllElements_92) {
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

// Test clear then reinsert
TEST_F(SparseSetTest_92, ClearThenReinsert_92) {
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

// Test less static method
TEST_F(SparseSetTest_92, LessComparison_92) {
  EXPECT_TRUE(SparseSet::less(1, 2));
  EXPECT_FALSE(SparseSet::less(2, 1));
  EXPECT_FALSE(SparseSet::less(3, 3));
  EXPECT_TRUE(SparseSet::less(-1, 0));
  EXPECT_TRUE(SparseSet::less(0, 1));
}

// Test insert returns iterator pointing to inserted element
TEST_F(SparseSetTest_92, InsertReturnsIterator_92) {
  SparseSet s(10);
  auto it = s.insert(5);
  EXPECT_EQ(*it, 5);
}

// Test insert_new returns iterator pointing to inserted element
TEST_F(SparseSetTest_92, InsertNewReturnsIterator_92) {
  SparseSet s(10);
  auto it = s.insert_new(7);
  EXPECT_EQ(*it, 7);
}

// Test with max_size of 1
TEST_F(SparseSetTest_92, MaxSizeOne_92) {
  SparseSet s(1);
  EXPECT_EQ(s.max_size(), 1);
  EXPECT_EQ(s.size(), 0);
  s.insert(0);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(0));
}

// Test multiple clear operations
TEST_F(SparseSetTest_92, MultipleClearOperations_92) {
  SparseSet s(10);
  s.insert(1);
  s.clear();
  s.insert(2);
  s.clear();
  s.insert(3);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(3));
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(2));
}

// Test large set
TEST_F(SparseSetTest_92, LargeSet_92) {
  const int max = 10000;
  SparseSet s(max);
  for (int i = 0; i < max; i += 2) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), max / 2);
  for (int i = 0; i < max; i++) {
    if (i % 2 == 0) {
      EXPECT_TRUE(s.contains(i));
    } else {
      EXPECT_FALSE(s.contains(i));
    }
  }
}

// Test resize to smaller size (if allowed) - the set might clear
TEST_F(SparseSetTest_92, ResizeToSmallerAndReuse_92) {
  SparseSet s(20);
  s.insert(5);
  s.resize(10);
  EXPECT_EQ(s.max_size(), 10);
  // After resize to smaller, we can still use values within new range
  s.insert(3);
  EXPECT_TRUE(s.contains(3));
}

}  // namespace re2
