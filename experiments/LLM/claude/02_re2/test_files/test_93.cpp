#include "gtest/gtest.h"
#include "re2/sparse_set.h"

namespace re2 {

// Test fixture for SparseSet tests
class SparseSetTest_93 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor and basic properties
TEST_F(SparseSetTest_93, DefaultConstructor_93) {
  SparseSet s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test parameterized constructor
TEST_F(SparseSetTest_93, ParameterizedConstructor_93) {
  SparseSet s(10);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.max_size(), 10);
}

// Test insert single element
TEST_F(SparseSetTest_93, InsertSingleElement_93) {
  SparseSet s(10);
  s.insert(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_FALSE(s.empty());
  EXPECT_TRUE(s.contains(5));
}

// Test insert multiple elements
TEST_F(SparseSetTest_93, InsertMultipleElements_93) {
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
TEST_F(SparseSetTest_93, InsertDuplicateElement_93) {
  SparseSet s(10);
  s.insert(5);
  s.insert(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(5));
}

// Test insert_new single element
TEST_F(SparseSetTest_93, InsertNewSingleElement_93) {
  SparseSet s(10);
  s.insert_new(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(5));
}

// Test insert_new multiple unique elements
TEST_F(SparseSetTest_93, InsertNewMultipleUniqueElements_93) {
  SparseSet s(10);
  s.insert_new(0);
  s.insert_new(5);
  s.insert_new(9);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(0));
  EXPECT_TRUE(s.contains(5));
  EXPECT_TRUE(s.contains(9));
}

// Test contains returns false for absent element
TEST_F(SparseSetTest_93, ContainsReturnsFalseForAbsentElement_93) {
  SparseSet s(10);
  EXPECT_FALSE(s.contains(0));
  EXPECT_FALSE(s.contains(5));
  EXPECT_FALSE(s.contains(9));
}

// Test clear empties the set
TEST_F(SparseSetTest_93, ClearEmptiesSet_93) {
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
TEST_F(SparseSetTest_93, ClearOnEmptySet_93) {
  SparseSet s(10);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test begin and end on empty set
TEST_F(SparseSetTest_93, BeginEndEmptySet_93) {
  SparseSet s(10);
  EXPECT_EQ(s.begin(), s.end());
}

// Test iteration over elements
TEST_F(SparseSetTest_93, IterationOverElements_93) {
  SparseSet s(10);
  s.insert(2);
  s.insert(5);
  s.insert(8);

  int count = 0;
  bool found2 = false, found5 = false, found8 = false;
  for (SparseSet::iterator it = s.begin(); it != s.end(); ++it) {
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

// Test max_size returns correct value
TEST_F(SparseSetTest_93, MaxSizeReturnsCorrectValue_93) {
  SparseSet s(100);
  EXPECT_EQ(s.max_size(), 100);
}

// Test resize increases max_size
TEST_F(SparseSetTest_93, ResizeIncreasesMaxSize_93) {
  SparseSet s(10);
  s.insert(5);
  s.resize(20);
  EXPECT_EQ(s.max_size(), 20);
  // Previously inserted element should still be present
  EXPECT_TRUE(s.contains(5));
}

// Test resize allows inserting elements beyond original max_size
TEST_F(SparseSetTest_93, ResizeAllowsInsertBeyondOriginalMax_93) {
  SparseSet s(5);
  s.resize(20);
  s.insert(15);
  EXPECT_TRUE(s.contains(15));
  EXPECT_EQ(s.size(), 1);
}

// Test inserting element at boundary (0 and max_size - 1)
TEST_F(SparseSetTest_93, InsertBoundaryElements_93) {
  SparseSet s(10);
  s.insert(0);
  s.insert(9);
  EXPECT_TRUE(s.contains(0));
  EXPECT_TRUE(s.contains(9));
  EXPECT_EQ(s.size(), 2);
}

// Test insert_new at boundary element 0
TEST_F(SparseSetTest_93, InsertNewBoundaryZero_93) {
  SparseSet s(10);
  s.insert_new(0);
  EXPECT_TRUE(s.contains(0));
  EXPECT_EQ(s.size(), 1);
}

// Test insert_new at boundary element max_size - 1
TEST_F(SparseSetTest_93, InsertNewBoundaryMaxMinusOne_93) {
  SparseSet s(10);
  s.insert_new(9);
  EXPECT_TRUE(s.contains(9));
  EXPECT_EQ(s.size(), 1);
}

// Test filling the entire set
TEST_F(SparseSetTest_93, FillEntireSet_93) {
  const int max = 50;
  SparseSet s(max);
  for (int i = 0; i < max; i++) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), max);
  for (int i = 0; i < max; i++) {
    EXPECT_TRUE(s.contains(i));
  }
}

// Test clear then re-insert
TEST_F(SparseSetTest_93, ClearThenReInsert_93) {
  SparseSet s(10);
  s.insert(3);
  s.insert(7);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_FALSE(s.contains(3));
  EXPECT_FALSE(s.contains(7));

  s.insert(3);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(3));
  EXPECT_FALSE(s.contains(7));
}

// Test less static method
TEST_F(SparseSetTest_93, LessComparison_93) {
  EXPECT_TRUE(SparseSet::less(1, 2));
  EXPECT_FALSE(SparseSet::less(2, 1));
  EXPECT_FALSE(SparseSet::less(2, 2));
}

// Test less with negative numbers
TEST_F(SparseSetTest_93, LessWithNegativeNumbers_93) {
  EXPECT_TRUE(SparseSet::less(-1, 0));
  EXPECT_TRUE(SparseSet::less(-5, -1));
  EXPECT_FALSE(SparseSet::less(0, -1));
}

// Test less with zero
TEST_F(SparseSetTest_93, LessWithZero_93) {
  EXPECT_TRUE(SparseSet::less(0, 1));
  EXPECT_FALSE(SparseSet::less(1, 0));
  EXPECT_FALSE(SparseSet::less(0, 0));
}

// Test empty on non-empty set
TEST_F(SparseSetTest_93, EmptyOnNonEmptySet_93) {
  SparseSet s(10);
  s.insert(5);
  EXPECT_FALSE(s.empty());
}

// Test size with max_size of 1
TEST_F(SparseSetTest_93, MaxSizeOne_93) {
  SparseSet s(1);
  EXPECT_EQ(s.max_size(), 1);
  EXPECT_EQ(s.size(), 0);
  s.insert(0);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(0));
}

// Test insert returns iterator pointing to inserted element
TEST_F(SparseSetTest_93, InsertReturnsIterator_93) {
  SparseSet s(10);
  SparseSet::iterator it = s.insert(5);
  EXPECT_EQ(*it, 5);
}

// Test insert_new returns iterator pointing to inserted element
TEST_F(SparseSetTest_93, InsertNewReturnsIterator_93) {
  SparseSet s(10);
  SparseSet::iterator it = s.insert_new(3);
  EXPECT_EQ(*it, 3);
}

// Test insert duplicate returns iterator to existing element
TEST_F(SparseSetTest_93, InsertDuplicateReturnsIterator_93) {
  SparseSet s(10);
  s.insert(5);
  SparseSet::iterator it = s.insert(5);
  EXPECT_EQ(*it, 5);
  EXPECT_EQ(s.size(), 1);
}

// Test multiple clear operations
TEST_F(SparseSetTest_93, MultipleClearOperations_93) {
  SparseSet s(10);
  s.insert(1);
  s.insert(2);
  s.clear();
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test resize to smaller size (elements within range should still be contained)
TEST_F(SparseSetTest_93, ResizeToSmallerButWithinRange_93) {
  SparseSet s(20);
  s.insert(3);
  s.insert(5);
  s.resize(10);
  EXPECT_EQ(s.max_size(), 10);
  // Elements 3 and 5 are within new range
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(5));
}

// Test large set operations
TEST_F(SparseSetTest_93, LargeSetOperations_93) {
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

}  // namespace re2
