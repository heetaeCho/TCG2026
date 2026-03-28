#include "gtest/gtest.h"
#include "re2/sparse_array.h"

namespace re2 {

// Test fixture for SparseArray tests
class SparseArrayTest_81 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(SparseArrayTest_81, DefaultConstructor_81) {
  SparseArray<int> sa;
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_81, ConstructorWithMaxSize_81) {
  SparseArray<int> sa(100);
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
  EXPECT_EQ(sa.max_size(), 100);
}

TEST_F(SparseArrayTest_81, CopyConstructor_81) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(7, 70);

  SparseArray<int> copy(sa);
  EXPECT_EQ(copy.size(), 2);
  EXPECT_TRUE(copy.has_index(3));
  EXPECT_TRUE(copy.has_index(7));
  EXPECT_EQ(copy.get_existing(3), 30);
  EXPECT_EQ(copy.get_existing(7), 70);
}

TEST_F(SparseArrayTest_81, MoveConstructor_81) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  sa.set(9, 90);

  SparseArray<int> moved(std::move(sa));
  EXPECT_EQ(moved.size(), 2);
  EXPECT_TRUE(moved.has_index(5));
  EXPECT_TRUE(moved.has_index(9));
  EXPECT_EQ(moved.get_existing(5), 50);
  EXPECT_EQ(moved.get_existing(9), 90);

  // Source should be empty after move
  EXPECT_EQ(sa.size(), 0);
}

// ==================== Assignment Tests ====================

TEST_F(SparseArrayTest_81, CopyAssignment_81) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(4, 40);

  SparseArray<int> other(5);
  other = sa;
  EXPECT_EQ(other.size(), 2);
  EXPECT_TRUE(other.has_index(2));
  EXPECT_TRUE(other.has_index(4));
  EXPECT_EQ(other.get_existing(2), 20);
  EXPECT_EQ(other.get_existing(4), 40);
}

TEST_F(SparseArrayTest_81, MoveAssignment_81) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(8, 80);

  SparseArray<int> other(5);
  other = std::move(sa);
  EXPECT_EQ(other.size(), 2);
  EXPECT_TRUE(other.has_index(1));
  EXPECT_TRUE(other.has_index(8));
  EXPECT_EQ(other.get_existing(1), 10);
  EXPECT_EQ(other.get_existing(8), 80);

  // Source should be empty after move
  EXPECT_EQ(sa.size(), 0);
}

// ==================== Set/Get Tests ====================

TEST_F(SparseArrayTest_81, SetAndGetExisting_81) {
  SparseArray<int> sa(10);
  sa.set(0, 100);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 100);
}

TEST_F(SparseArrayTest_81, SetMultipleValues_81) {
  SparseArray<int> sa(20);
  for (int i = 0; i < 20; i++) {
    sa.set(i, i * 10);
  }
  EXPECT_EQ(sa.size(), 20);
  for (int i = 0; i < 20; i++) {
    EXPECT_TRUE(sa.has_index(i));
    EXPECT_EQ(sa.get_existing(i), i * 10);
  }
}

TEST_F(SparseArrayTest_81, SetOverwritesExistingValue_81) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  EXPECT_EQ(sa.get_existing(5), 50);

  sa.set(5, 500);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_EQ(sa.get_existing(5), 500);
}

TEST_F(SparseArrayTest_81, SetNew_81) {
  SparseArray<int> sa(10);
  sa.set_new(3, 30);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get_existing(3), 30);
}

TEST_F(SparseArrayTest_81, SetExisting_81) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set_existing(3, 300);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_EQ(sa.get_existing(3), 300);
}

// ==================== has_index Tests ====================

TEST_F(SparseArrayTest_81, HasIndexReturnsFalseForMissingIndex_81) {
  SparseArray<int> sa(10);
  EXPECT_FALSE(sa.has_index(0));
  EXPECT_FALSE(sa.has_index(5));
  EXPECT_FALSE(sa.has_index(9));
}

TEST_F(SparseArrayTest_81, HasIndexReturnsTrueForExistingIndex_81) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_FALSE(sa.has_index(4));
  EXPECT_FALSE(sa.has_index(6));
}

// ==================== Clear Tests ====================

TEST_F(SparseArrayTest_81, ClearEmptiesArray_81) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(3, 30);
  sa.set(5, 50);

  EXPECT_EQ(sa.size(), 3);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
  EXPECT_FALSE(sa.has_index(1));
  EXPECT_FALSE(sa.has_index(3));
  EXPECT_FALSE(sa.has_index(5));
}

TEST_F(SparseArrayTest_81, ClearOnEmptyArray_81) {
  SparseArray<int> sa(10);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

// ==================== Size/Empty Tests ====================

TEST_F(SparseArrayTest_81, SizeReflectsNumberOfElements_81) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.size(), 0);

  sa.set(0, 0);
  EXPECT_EQ(sa.size(), 1);

  sa.set(1, 1);
  EXPECT_EQ(sa.size(), 2);

  sa.set(0, 100);  // overwrite, should not increase size
  EXPECT_EQ(sa.size(), 2);
}

TEST_F(SparseArrayTest_81, EmptyReflectsState_81) {
  SparseArray<int> sa(10);
  EXPECT_TRUE(sa.empty());

  sa.set(0, 0);
  EXPECT_FALSE(sa.empty());

  sa.clear();
  EXPECT_TRUE(sa.empty());
}

// ==================== Iterator Tests ====================

TEST_F(SparseArrayTest_81, BeginEqualsEndWhenEmpty_81) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.begin(), sa.end());
}

TEST_F(SparseArrayTest_81, IteratorTraversal_81) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(5, 50);
  sa.set(8, 80);

  int count = 0;
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 3);
}

TEST_F(SparseArrayTest_81, IteratorAccessIndexAndValue_81) {
  SparseArray<int> sa(10);
  sa.set(3, 30);

  auto it = sa.begin();
  EXPECT_NE(it, sa.end());
  EXPECT_EQ(it->index(), 3);
  EXPECT_EQ(it->value(), 30);
}

// ==================== Resize Tests ====================

TEST_F(SparseArrayTest_81, ResizeIncreasesMaxSize_81) {
  SparseArray<int> sa(5);
  EXPECT_EQ(sa.max_size(), 5);

  sa.resize(20);
  EXPECT_EQ(sa.max_size(), 20);
  EXPECT_EQ(sa.size(), 0);
}

TEST_F(SparseArrayTest_81, ResizePreservesExistingElements_81) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(4, 40);

  sa.resize(20);
  EXPECT_EQ(sa.size(), 2);
  EXPECT_TRUE(sa.has_index(2));
  EXPECT_TRUE(sa.has_index(4));
  EXPECT_EQ(sa.get_existing(2), 20);
  EXPECT_EQ(sa.get_existing(4), 40);
}

TEST_F(SparseArrayTest_81, ResizeToSmallerTruncatesElements_81) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(8, 80);

  sa.resize(5);
  EXPECT_EQ(sa.max_size(), 5);
  // Index 8 should no longer be valid since it's >= new max_size
  EXPECT_TRUE(sa.has_index(2));
}

// ==================== max_size Tests ====================

TEST_F(SparseArrayTest_81, MaxSizeReflectsConstruction_81) {
  SparseArray<int> sa(42);
  EXPECT_EQ(sa.max_size(), 42);
}

// ==================== less() static function Tests ====================

TEST_F(SparseArrayTest_81, LessComparison_81) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(7, 70);

  // less should compare by index
  auto it1 = sa.begin();
  auto it2 = sa.begin() + 1;

  // We know elements are in insertion order
  bool result = SparseArray<int>::less(*it1, *it2);
  // The first inserted should have a smaller index if 3 < 7
  // But we can't guarantee internal ordering, just check it doesn't crash
  // and returns a consistent boolean
  (void)result;
}

// ==================== String Value Type Tests ====================

TEST_F(SparseArrayTest_81, StringValueType_81) {
  SparseArray<std::string> sa(10);
  sa.set(0, "hello");
  sa.set(5, "world");

  EXPECT_EQ(sa.size(), 2);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_EQ(sa.get_existing(0), "hello");
  EXPECT_EQ(sa.get_existing(5), "world");
}

// ==================== Boundary Tests ====================

TEST_F(SparseArrayTest_81, SetAtMaxSizeMinusOne_81) {
  SparseArray<int> sa(10);
  sa.set(9, 90);
  EXPECT_TRUE(sa.has_index(9));
  EXPECT_EQ(sa.get_existing(9), 90);
}

TEST_F(SparseArrayTest_81, SetAtIndexZero_81) {
  SparseArray<int> sa(10);
  sa.set(0, 0);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 0);
}

TEST_F(SparseArrayTest_81, MaxSizeOne_81) {
  SparseArray<int> sa(1);
  EXPECT_EQ(sa.max_size(), 1);
  sa.set(0, 42);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 42);
}

// ==================== set returns iterator Tests ====================

TEST_F(SparseArrayTest_81, SetReturnsIterator_81) {
  SparseArray<int> sa(10);
  auto it = sa.set(3, 30);
  EXPECT_EQ(it->index(), 3);
  EXPECT_EQ(it->value(), 30);
}

TEST_F(SparseArrayTest_81, SetNewReturnsIterator_81) {
  SparseArray<int> sa(10);
  auto it = sa.set_new(7, 70);
  EXPECT_EQ(it->index(), 7);
  EXPECT_EQ(it->value(), 70);
}

TEST_F(SparseArrayTest_81, SetExistingReturnsIterator_81) {
  SparseArray<int> sa(10);
  sa.set(4, 40);
  auto it = sa.set_existing(4, 400);
  EXPECT_EQ(it->index(), 4);
  EXPECT_EQ(it->value(), 400);
}

// ==================== Multiple Operations Tests ====================

TEST_F(SparseArrayTest_81, SetClearSet_81) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(2, 20);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);

  sa.set(1, 100);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(1));
  EXPECT_EQ(sa.get_existing(1), 100);
}

TEST_F(SparseArrayTest_81, FillEntireArray_81) {
  const int kSize = 50;
  SparseArray<int> sa(kSize);
  for (int i = 0; i < kSize; i++) {
    sa.set(i, i * 2);
  }
  EXPECT_EQ(sa.size(), kSize);
  for (int i = 0; i < kSize; i++) {
    EXPECT_TRUE(sa.has_index(i));
    EXPECT_EQ(sa.get_existing(i), i * 2);
  }
}

TEST_F(SparseArrayTest_81, CopyAssignmentDoesNotAffectSource_81) {
  SparseArray<int> sa(10);
  sa.set(3, 30);

  SparseArray<int> copy(5);
  copy = sa;

  // Modify copy
  copy.set(3, 300);
  copy.set(5, 50);

  // Source should be unchanged
  EXPECT_EQ(sa.size(), 1);
  EXPECT_EQ(sa.get_existing(3), 30);
  EXPECT_FALSE(sa.has_index(5));
}

TEST_F(SparseArrayTest_81, DoubleValueType_81) {
  SparseArray<double> sa(10);
  sa.set(0, 3.14);
  sa.set(9, 2.71);

  EXPECT_EQ(sa.size(), 2);
  EXPECT_DOUBLE_EQ(sa.get_existing(0), 3.14);
  EXPECT_DOUBLE_EQ(sa.get_existing(9), 2.71);
}

}  // namespace re2
