#include "gtest/gtest.h"
#include "re2/sparse_set.h"

namespace re2 {

// Test fixture for SparseSet tests
class SparseSetTest_94 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default construction
TEST_F(SparseSetTest_94, DefaultConstruction_94) {
  SparseSet s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Test construction with max_size
TEST_F(SparseSetTest_94, ConstructionWithMaxSize_94) {
  SparseSet s(10);
  EXPECT_EQ(s.size(), 0);
  EXPECT_EQ(s.max_size(), 10);
  EXPECT_TRUE(s.empty());
}

// Test insert and contains
TEST_F(SparseSetTest_94, InsertAndContains_94) {
  SparseSet s(10);
  s.insert(5);
  EXPECT_TRUE(s.contains(5));
  EXPECT_EQ(s.size(), 1);
  EXPECT_FALSE(s.empty());
}

// Test insert_new
TEST_F(SparseSetTest_94, InsertNew_94) {
  SparseSet s(10);
  s.insert_new(3);
  EXPECT_TRUE(s.contains(3));
  EXPECT_EQ(s.size(), 1);
}

// Test inserting duplicate with insert
TEST_F(SparseSetTest_94, InsertDuplicate_94) {
  SparseSet s(10);
  s.insert(5);
  s.insert(5);
  EXPECT_TRUE(s.contains(5));
  EXPECT_EQ(s.size(), 1);
}

// Test multiple inserts
TEST_F(SparseSetTest_94, MultipleInserts_94) {
  SparseSet s(10);
  s.insert(0);
  s.insert(3);
  s.insert(7);
  s.insert(9);
  EXPECT_EQ(s.size(), 4);
  EXPECT_TRUE(s.contains(0));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(7));
  EXPECT_TRUE(s.contains(9));
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(5));
}

// Test clear
TEST_F(SparseSetTest_94, Clear_94) {
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

// Test begin and end iterators on empty set
TEST_F(SparseSetTest_94, EmptyIterators_94) {
  SparseSet s(10);
  EXPECT_EQ(s.begin(), s.end());
}

// Test begin and end iterators with elements
TEST_F(SparseSetTest_94, IteratorsWithElements_94) {
  SparseSet s(10);
  s.insert(2);
  s.insert(5);
  s.insert(8);
  int count = 0;
  for (auto it = s.begin(); it != s.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 3);
}

// Test resize to larger size
TEST_F(SparseSetTest_94, ResizeLarger_94) {
  SparseSet s(5);
  s.insert(0);
  s.insert(2);
  s.insert(4);
  EXPECT_EQ(s.max_size(), 5);
  EXPECT_EQ(s.size(), 3);

  s.resize(10);
  EXPECT_EQ(s.max_size(), 10);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(0));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(4));
}

// Test resize allows inserting elements in new range
TEST_F(SparseSetTest_94, ResizeLargerAllowsNewInserts_94) {
  SparseSet s(5);
  s.insert(3);
  s.resize(10);
  s.insert(7);
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(7));
  EXPECT_EQ(s.size(), 2);
}

// Test resize to same size
TEST_F(SparseSetTest_94, ResizeSameSize_94) {
  SparseSet s(10);
  s.insert(3);
  s.insert(5);
  s.resize(10);
  EXPECT_EQ(s.max_size(), 10);
  EXPECT_EQ(s.size(), 2);
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(5));
}

// Test resize to smaller size that doesn't affect elements
TEST_F(SparseSetTest_94, ResizeSmallerNoElementLoss_94) {
  SparseSet s(10);
  s.insert(0);
  s.insert(1);
  // Resize smaller but size_ (2) <= new_max_size (5)
  s.resize(5);
  // max_size should not decrease (based on the implementation, resize only grows)
  // The implementation only grows sparse_/dense_ if new_max_size > max_size()
  // But it does: if (size_ > new_max_size) size_ = new_max_size;
  // Since max_size is 10 and new_max_size is 5, it won't reallocate
  // but will clamp size_ to min(size_, new_max_size) = min(2, 5) = 2
  EXPECT_EQ(s.size(), 2);
}

// Test resize smaller truncates elements
TEST_F(SparseSetTest_94, ResizeSmallerTruncatesSize_94) {
  SparseSet s(10);
  // Insert many elements
  for (int i = 0; i < 8; i++) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), 8);
  // Resize to 3 - should clamp size_ to 3
  s.resize(3);
  EXPECT_EQ(s.size(), 3);
}

// Test contains returns false for non-existent element
TEST_F(SparseSetTest_94, ContainsReturnsFalseForMissing_94) {
  SparseSet s(10);
  EXPECT_FALSE(s.contains(0));
  EXPECT_FALSE(s.contains(5));
  EXPECT_FALSE(s.contains(9));
}

// Test max_size after construction
TEST_F(SparseSetTest_94, MaxSizeAfterConstruction_94) {
  SparseSet s(100);
  EXPECT_EQ(s.max_size(), 100);
}

// Test inserting at boundary values (0 and max_size-1)
TEST_F(SparseSetTest_94, InsertBoundaryValues_94) {
  SparseSet s(10);
  s.insert(0);
  s.insert(9);
  EXPECT_TRUE(s.contains(0));
  EXPECT_TRUE(s.contains(9));
  EXPECT_EQ(s.size(), 2);
}

// Test clear then re-insert
TEST_F(SparseSetTest_94, ClearThenReinsert_94) {
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

// Test less static method
TEST_F(SparseSetTest_94, LessMethod_94) {
  EXPECT_TRUE(SparseSet::less(1, 2));
  EXPECT_FALSE(SparseSet::less(2, 1));
  EXPECT_FALSE(SparseSet::less(1, 1));
}

// Test resize from zero max_size
TEST_F(SparseSetTest_94, ResizeFromDefault_94) {
  SparseSet s;
  s.resize(10);
  EXPECT_EQ(s.max_size(), 10);
  s.insert(5);
  EXPECT_TRUE(s.contains(5));
  EXPECT_EQ(s.size(), 1);
}

// Test resize multiple times
TEST_F(SparseSetTest_94, ResizeMultipleTimes_94) {
  SparseSet s(5);
  s.insert(2);
  s.resize(10);
  s.insert(7);
  s.resize(20);
  s.insert(15);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(7));
  EXPECT_TRUE(s.contains(15));
}

// Test empty returns correct value
TEST_F(SparseSetTest_94, EmptyMethod_94) {
  SparseSet s(5);
  EXPECT_TRUE(s.empty());
  s.insert(1);
  EXPECT_FALSE(s.empty());
  s.clear();
  EXPECT_TRUE(s.empty());
}

// Test size with max_size of 1
TEST_F(SparseSetTest_94, SingleElementCapacity_94) {
  SparseSet s(1);
  EXPECT_EQ(s.max_size(), 1);
  s.insert(0);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(0));
}

// Test iteration order matches insertion order (dense array)
TEST_F(SparseSetTest_94, IterationContainsAllElements_94) {
  SparseSet s(20);
  s.insert(10);
  s.insert(5);
  s.insert(15);

  std::set<int> found;
  for (auto it = s.begin(); it != s.end(); ++it) {
    found.insert(*it);
  }
  EXPECT_EQ(found.size(), 3u);
  EXPECT_TRUE(found.count(10));
  EXPECT_TRUE(found.count(5));
  EXPECT_TRUE(found.count(15));
}

// Test resize preserves existing elements after growing
TEST_F(SparseSetTest_94, ResizePreservesAllElements_94) {
  SparseSet s(5);
  s.insert(0);
  s.insert(1);
  s.insert(2);
  s.insert(3);
  s.insert(4);
  EXPECT_EQ(s.size(), 5);

  s.resize(20);
  EXPECT_EQ(s.size(), 5);
  for (int i = 0; i < 5; i++) {
    EXPECT_TRUE(s.contains(i));
  }
}

}  // namespace re2
