#include "gtest/gtest.h"
#include "re2/sparse_set.h"

namespace re2 {

// Test fixture for SparseSet tests
class SparseSetTest_88 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor creates empty set
TEST_F(SparseSetTest_88, DefaultConstructor_88) {
  SparseSet s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test constructor with max_size
TEST_F(SparseSetTest_88, ConstructorWithMaxSize_88) {
  SparseSet s(100);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.max_size(), 100);
}

// Test insert increases size
TEST_F(SparseSetTest_88, InsertIncreasesSize_88) {
  SparseSet s(10);
  s.insert(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_FALSE(s.empty());
}

// Test insert multiple elements
TEST_F(SparseSetTest_88, InsertMultipleElements_88) {
  SparseSet s(10);
  s.insert(1);
  s.insert(3);
  s.insert(7);
  EXPECT_EQ(s.size(), 3);
}

// Test insert duplicate element does not increase size
TEST_F(SparseSetTest_88, InsertDuplicateElement_88) {
  SparseSet s(10);
  s.insert(5);
  s.insert(5);
  EXPECT_EQ(s.size(), 1);
}

// Test contains after insert
TEST_F(SparseSetTest_88, ContainsAfterInsert_88) {
  SparseSet s(10);
  EXPECT_FALSE(s.contains(5));
  s.insert(5);
  EXPECT_TRUE(s.contains(5));
}

// Test contains returns false for non-inserted element
TEST_F(SparseSetTest_88, ContainsReturnsFalseForNonInserted_88) {
  SparseSet s(10);
  s.insert(3);
  EXPECT_FALSE(s.contains(7));
}

// Test clear empties the set
TEST_F(SparseSetTest_88, ClearEmptiesSet_88) {
  SparseSet s(10);
  s.insert(1);
  s.insert(2);
  s.insert(3);
  EXPECT_EQ(s.size(), 3);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test contains returns false after clear
TEST_F(SparseSetTest_88, ContainsReturnsFalseAfterClear_88) {
  SparseSet s(10);
  s.insert(5);
  EXPECT_TRUE(s.contains(5));
  s.clear();
  EXPECT_FALSE(s.contains(5));
}

// Test empty on empty set
TEST_F(SparseSetTest_88, EmptyOnEmptySet_88) {
  SparseSet s(10);
  EXPECT_TRUE(s.empty());
}

// Test empty on non-empty set
TEST_F(SparseSetTest_88, EmptyOnNonEmptySet_88) {
  SparseSet s(10);
  s.insert(0);
  EXPECT_FALSE(s.empty());
}

// Test max_size returns correct value
TEST_F(SparseSetTest_88, MaxSizeReturnsCorrectValue_88) {
  SparseSet s(50);
  EXPECT_EQ(s.max_size(), 50);
}

// Test begin and end iterators on empty set
TEST_F(SparseSetTest_88, BeginEndOnEmptySet_88) {
  SparseSet s(10);
  EXPECT_EQ(s.begin(), s.end());
}

// Test begin and end iterators reflect size
TEST_F(SparseSetTest_88, IteratorRangeMatchesSize_88) {
  SparseSet s(10);
  s.insert(1);
  s.insert(3);
  s.insert(5);
  int count = 0;
  for (auto it = s.begin(); it != s.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 3);
}

// Test iterating over elements finds inserted values
TEST_F(SparseSetTest_88, IteratingFindsInsertedValues_88) {
  SparseSet s(10);
  s.insert(2);
  s.insert(4);
  s.insert(6);
  
  bool found2 = false, found4 = false, found6 = false;
  for (auto it = s.begin(); it != s.end(); ++it) {
    if (*it == 2) found2 = true;
    if (*it == 4) found4 = true;
    if (*it == 6) found6 = true;
  }
  EXPECT_TRUE(found2);
  EXPECT_TRUE(found4);
  EXPECT_TRUE(found6);
}

// Test insert_new with new element
TEST_F(SparseSetTest_88, InsertNewWithNewElement_88) {
  SparseSet s(10);
  s.insert_new(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(5));
}

// Test insert element at boundary index 0
TEST_F(SparseSetTest_88, InsertElementAtIndexZero_88) {
  SparseSet s(10);
  s.insert(0);
  EXPECT_TRUE(s.contains(0));
  EXPECT_EQ(s.size(), 1);
}

// Test insert element at max boundary
TEST_F(SparseSetTest_88, InsertElementAtMaxBoundary_88) {
  SparseSet s(10);
  s.insert(9);
  EXPECT_TRUE(s.contains(9));
  EXPECT_EQ(s.size(), 1);
}

// Test resize increases max_size
TEST_F(SparseSetTest_88, ResizeIncreasesMaxSize_88) {
  SparseSet s(10);
  s.resize(20);
  EXPECT_EQ(s.max_size(), 20);
}

// Test resize preserves emptiness
TEST_F(SparseSetTest_88, ResizeOnEmptySet_88) {
  SparseSet s(10);
  s.resize(20);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test insert after resize with larger index
TEST_F(SparseSetTest_88, InsertAfterResize_88) {
  SparseSet s(10);
  s.resize(20);
  s.insert(15);
  EXPECT_TRUE(s.contains(15));
  EXPECT_EQ(s.size(), 1);
}

// Test inserting all elements up to max_size
TEST_F(SparseSetTest_88, InsertAllElements_88) {
  int max = 10;
  SparseSet s(max);
  for (int i = 0; i < max; i++) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), max);
  for (int i = 0; i < max; i++) {
    EXPECT_TRUE(s.contains(i));
  }
}

// Test clear followed by re-insert
TEST_F(SparseSetTest_88, ClearThenReinsert_88) {
  SparseSet s(10);
  s.insert(3);
  s.insert(7);
  s.clear();
  s.insert(3);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(3));
  EXPECT_FALSE(s.contains(7));
}

// Test less static function
TEST_F(SparseSetTest_88, LessFunction_88) {
  EXPECT_TRUE(SparseSet::less(1, 2));
  EXPECT_FALSE(SparseSet::less(2, 1));
  EXPECT_FALSE(SparseSet::less(1, 1));
}

// Test less with negative values
TEST_F(SparseSetTest_88, LessWithNegativeValues_88) {
  EXPECT_TRUE(SparseSet::less(-1, 0));
  EXPECT_FALSE(SparseSet::less(0, -1));
}

// Test constructor with max_size of 1
TEST_F(SparseSetTest_88, ConstructorWithMaxSizeOne_88) {
  SparseSet s(1);
  EXPECT_EQ(s.max_size(), 1);
  s.insert(0);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(0));
}

// Test multiple clears
TEST_F(SparseSetTest_88, MultipleClears_88) {
  SparseSet s(10);
  s.insert(1);
  s.clear();
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test size consistency with insert and clear cycles
TEST_F(SparseSetTest_88, InsertClearCycles_88) {
  SparseSet s(10);
  for (int cycle = 0; cycle < 5; cycle++) {
    for (int i = 0; i < 10; i++) {
      s.insert(i);
    }
    EXPECT_EQ(s.size(), 10);
    s.clear();
    EXPECT_EQ(s.size(), 0);
  }
}

}  // namespace re2
