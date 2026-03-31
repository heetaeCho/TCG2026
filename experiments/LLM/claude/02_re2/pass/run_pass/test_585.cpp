#include "gtest/gtest.h"
#include "re2/sparse_set.h"

namespace re2 {

// Test fixture for SparseSet tests
class SparseSetTest_585 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(SparseSetTest_585, DefaultConstruction_585) {
  SparseSet s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

TEST_F(SparseSetTest_585, ConstructWithMaxSize_585) {
  SparseSet s(100);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.max_size(), 100);
}

TEST_F(SparseSetTest_585, ConstructWithZeroMaxSize_585) {
  SparseSet s(0);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.max_size(), 0);
}

TEST_F(SparseSetTest_585, ConstructWithSmallMaxSize_585) {
  SparseSet s(1);
  EXPECT_EQ(s.size(), 0);
  EXPECT_EQ(s.max_size(), 1);
}

// ==================== Insert Tests ====================

TEST_F(SparseSetTest_585, InsertSingleElement_585) {
  SparseSet s(10);
  s.insert(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_FALSE(s.empty());
  EXPECT_TRUE(s.contains(5));
}

TEST_F(SparseSetTest_585, InsertMultipleElements_585) {
  SparseSet s(10);
  s.insert(0);
  s.insert(3);
  s.insert(7);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(0));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(7));
}

TEST_F(SparseSetTest_585, InsertDuplicateElement_585) {
  SparseSet s(10);
  s.insert(5);
  s.insert(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(5));
}

TEST_F(SparseSetTest_585, InsertAtBoundaryZero_585) {
  SparseSet s(10);
  s.insert(0);
  EXPECT_TRUE(s.contains(0));
  EXPECT_EQ(s.size(), 1);
}

TEST_F(SparseSetTest_585, InsertAtBoundaryMaxMinusOne_585) {
  SparseSet s(10);
  s.insert(9);
  EXPECT_TRUE(s.contains(9));
  EXPECT_EQ(s.size(), 1);
}

TEST_F(SparseSetTest_585, InsertAllElements_585) {
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

// ==================== InsertNew Tests ====================

TEST_F(SparseSetTest_585, InsertNewSingleElement_585) {
  SparseSet s(10);
  s.insert_new(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(5));
}

TEST_F(SparseSetTest_585, InsertNewMultipleDistinctElements_585) {
  SparseSet s(10);
  s.insert_new(1);
  s.insert_new(3);
  s.insert_new(5);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(5));
}

// ==================== Contains Tests ====================

TEST_F(SparseSetTest_585, ContainsReturnsFalseForEmptySet_585) {
  SparseSet s(10);
  EXPECT_FALSE(s.contains(0));
  EXPECT_FALSE(s.contains(5));
  EXPECT_FALSE(s.contains(9));
}

TEST_F(SparseSetTest_585, ContainsReturnsTrueForInsertedElement_585) {
  SparseSet s(10);
  s.insert(3);
  EXPECT_TRUE(s.contains(3));
}

TEST_F(SparseSetTest_585, ContainsReturnsFalseForNonInsertedElement_585) {
  SparseSet s(10);
  s.insert(3);
  EXPECT_FALSE(s.contains(4));
  EXPECT_FALSE(s.contains(0));
}

// ==================== Clear Tests ====================

TEST_F(SparseSetTest_585, ClearEmptySet_585) {
  SparseSet s(10);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

TEST_F(SparseSetTest_585, ClearNonEmptySet_585) {
  SparseSet s(10);
  s.insert(1);
  s.insert(5);
  s.insert(9);
  EXPECT_EQ(s.size(), 3);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(5));
  EXPECT_FALSE(s.contains(9));
}

TEST_F(SparseSetTest_585, InsertAfterClear_585) {
  SparseSet s(10);
  s.insert(3);
  s.insert(7);
  s.clear();
  s.insert(5);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(5));
  EXPECT_FALSE(s.contains(3));
  EXPECT_FALSE(s.contains(7));
}

// ==================== Size and Empty Tests ====================

TEST_F(SparseSetTest_585, SizeIncreasesWithInserts_585) {
  SparseSet s(10);
  EXPECT_EQ(s.size(), 0);
  s.insert(1);
  EXPECT_EQ(s.size(), 1);
  s.insert(2);
  EXPECT_EQ(s.size(), 2);
  s.insert(3);
  EXPECT_EQ(s.size(), 3);
}

TEST_F(SparseSetTest_585, EmptyReturnsTrueForNewSet_585) {
  SparseSet s(10);
  EXPECT_TRUE(s.empty());
}

TEST_F(SparseSetTest_585, EmptyReturnsFalseAfterInsert_585) {
  SparseSet s(10);
  s.insert(0);
  EXPECT_FALSE(s.empty());
}

TEST_F(SparseSetTest_585, EmptyReturnsTrueAfterClear_585) {
  SparseSet s(10);
  s.insert(0);
  s.clear();
  EXPECT_TRUE(s.empty());
}

// ==================== MaxSize Tests ====================

TEST_F(SparseSetTest_585, MaxSizeReturnsCorrectValue_585) {
  SparseSet s(50);
  EXPECT_EQ(s.max_size(), 50);
}

TEST_F(SparseSetTest_585, MaxSizeUnchangedAfterInserts_585) {
  SparseSet s(50);
  s.insert(10);
  s.insert(20);
  EXPECT_EQ(s.max_size(), 50);
}

// ==================== Iterator Tests ====================

TEST_F(SparseSetTest_585, BeginEqualsEndForEmptySet_585) {
  SparseSet s(10);
  EXPECT_EQ(s.begin(), s.end());
}

TEST_F(SparseSetTest_585, IteratorCoversAllElements_585) {
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

TEST_F(SparseSetTest_585, IteratorAfterClear_585) {
  SparseSet s(10);
  s.insert(1);
  s.insert(2);
  s.clear();
  EXPECT_EQ(s.begin(), s.end());
}

// ==================== Resize Tests ====================

TEST_F(SparseSetTest_585, ResizeToLarger_585) {
  SparseSet s(5);
  s.insert(2);
  s.insert(4);
  s.resize(20);
  EXPECT_EQ(s.max_size(), 20);
  // After resize, the set should be cleared or elements may not persist
  // We test max_size is updated
}

TEST_F(SparseSetTest_585, ResizeToSmaller_585) {
  SparseSet s(20);
  s.resize(5);
  EXPECT_EQ(s.max_size(), 5);
}

TEST_F(SparseSetTest_585, ResizeToZero_585) {
  SparseSet s(10);
  s.resize(0);
  EXPECT_EQ(s.max_size(), 0);
  EXPECT_EQ(s.size(), 0);
}

TEST_F(SparseSetTest_585, InsertAfterResizeToLarger_585) {
  SparseSet s(5);
  s.resize(20);
  s.insert(15);
  EXPECT_TRUE(s.contains(15));
  EXPECT_EQ(s.size(), 1);
}

// ==================== Less Tests ====================

TEST_F(SparseSetTest_585, LessComparison_585) {
  EXPECT_TRUE(SparseSet::less(1, 2));
  EXPECT_FALSE(SparseSet::less(2, 1));
  EXPECT_FALSE(SparseSet::less(1, 1));
}

TEST_F(SparseSetTest_585, LessWithNegativeNumbers_585) {
  EXPECT_TRUE(SparseSet::less(-1, 0));
  EXPECT_FALSE(SparseSet::less(0, -1));
}

TEST_F(SparseSetTest_585, LessWithZero_585) {
  EXPECT_TRUE(SparseSet::less(0, 1));
  EXPECT_FALSE(SparseSet::less(1, 0));
}

// ==================== Stress / Larger Set Tests ====================

TEST_F(SparseSetTest_585, LargeSetInsertAndContains_585) {
  const int max_size = 10000;
  SparseSet s(max_size);
  for (int i = 0; i < max_size; i += 2) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), max_size / 2);
  for (int i = 0; i < max_size; i++) {
    if (i % 2 == 0) {
      EXPECT_TRUE(s.contains(i));
    } else {
      EXPECT_FALSE(s.contains(i));
    }
  }
}

TEST_F(SparseSetTest_585, ClearAndReinsert_585) {
  SparseSet s(10);
  for (int i = 0; i < 10; i++) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), 10);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  for (int i = 0; i < 10; i++) {
    EXPECT_FALSE(s.contains(i));
  }
  // Reinsert different subset
  s.insert(1);
  s.insert(3);
  s.insert(5);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(5));
  EXPECT_FALSE(s.contains(0));
  EXPECT_FALSE(s.contains(2));
}

TEST_F(SparseSetTest_585, MultipleClearCycles_585) {
  SparseSet s(10);
  for (int cycle = 0; cycle < 5; cycle++) {
    for (int i = 0; i < 10; i++) {
      s.insert(i);
    }
    EXPECT_EQ(s.size(), 10);
    s.clear();
    EXPECT_EQ(s.size(), 0);
    EXPECT_TRUE(s.empty());
  }
}

TEST_F(SparseSetTest_585, InsertReturnsIterator_585) {
  SparseSet s(10);
  auto it = s.insert(5);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 5);
}

TEST_F(SparseSetTest_585, InsertNewReturnsIterator_585) {
  SparseSet s(10);
  auto it = s.insert_new(7);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 7);
}

TEST_F(SparseSetTest_585, InsertDuplicateReturnsIteratorToExisting_585) {
  SparseSet s(10);
  s.insert(5);
  auto it = s.insert(5);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 5);
  EXPECT_EQ(s.size(), 1);
}

}  // namespace re2
