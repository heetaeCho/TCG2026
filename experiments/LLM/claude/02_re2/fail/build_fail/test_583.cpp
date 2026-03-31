#include "gtest/gtest.h"
#include "re2/sparse_array.h"

namespace re2 {

// Test fixture for SparseArray tests
class SparseArrayTest_583 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(SparseArrayTest_583, DefaultConstructor_583) {
  SparseArray<int> sa;
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_583, ConstructorWithMaxSize_583) {
  SparseArray<int> sa(100);
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
  EXPECT_EQ(sa.max_size(), 100);
}

TEST_F(SparseArrayTest_583, CopyConstructor_583) {
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

TEST_F(SparseArrayTest_583, MoveConstructor_583) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(7, 70);

  SparseArray<int> moved(std::move(sa));
  EXPECT_EQ(moved.size(), 2);
  EXPECT_TRUE(moved.has_index(3));
  EXPECT_TRUE(moved.has_index(7));
  EXPECT_EQ(moved.get_existing(3), 30);
  EXPECT_EQ(moved.get_existing(7), 70);

  // Source should be empty after move
  EXPECT_EQ(sa.size(), 0);
}

// ==================== Assignment Tests ====================

TEST_F(SparseArrayTest_583, CopyAssignment_583) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(5, 50);

  SparseArray<int> other(10);
  other = sa;

  EXPECT_EQ(other.size(), 2);
  EXPECT_TRUE(other.has_index(2));
  EXPECT_TRUE(other.has_index(5));
  EXPECT_EQ(other.get_existing(2), 20);
  EXPECT_EQ(other.get_existing(5), 50);
}

TEST_F(SparseArrayTest_583, MoveAssignment_583) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(5, 50);

  SparseArray<int> other(10);
  other = std::move(sa);

  EXPECT_EQ(other.size(), 2);
  EXPECT_TRUE(other.has_index(2));
  EXPECT_TRUE(other.has_index(5));
  EXPECT_EQ(other.get_existing(2), 20);
  EXPECT_EQ(other.get_existing(5), 50);

  EXPECT_EQ(sa.size(), 0);
}

// ==================== set / get / has_index Tests ====================

TEST_F(SparseArrayTest_583, SetAndGetExisting_583) {
  SparseArray<int> sa(10);
  sa.set(0, 100);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 100);
}

TEST_F(SparseArrayTest_583, SetOverwritesExistingValue_583) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  EXPECT_EQ(sa.get_existing(3), 30);

  sa.set(3, 300);
  EXPECT_EQ(sa.get_existing(3), 300);
  EXPECT_EQ(sa.size(), 1);  // Size should not increase
}

TEST_F(SparseArrayTest_583, SetNewAddsNewElement_583) {
  SparseArray<int> sa(10);
  sa.set_new(4, 40);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(4));
  EXPECT_EQ(sa.get_existing(4), 40);
}

TEST_F(SparseArrayTest_583, SetExistingModifiesValue_583) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  sa.set_existing(5, 500);
  EXPECT_EQ(sa.get_existing(5), 500);
  EXPECT_EQ(sa.size(), 1);
}

TEST_F(SparseArrayTest_583, HasIndexReturnsFalseForMissing_583) {
  SparseArray<int> sa(10);
  EXPECT_FALSE(sa.has_index(0));
  EXPECT_FALSE(sa.has_index(5));
  EXPECT_FALSE(sa.has_index(9));
}

TEST_F(SparseArrayTest_583, HasIndexReturnsTrueForExisting_583) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_FALSE(sa.has_index(4));
}

// ==================== Size and Empty Tests ====================

TEST_F(SparseArrayTest_583, SizeIncreasesWithNewElements_583) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.size(), 0);

  sa.set(0, 10);
  EXPECT_EQ(sa.size(), 1);

  sa.set(1, 20);
  EXPECT_EQ(sa.size(), 2);

  sa.set(2, 30);
  EXPECT_EQ(sa.size(), 3);
}

TEST_F(SparseArrayTest_583, EmptyReturnsTrueWhenNoElements_583) {
  SparseArray<int> sa(10);
  EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_583, EmptyReturnsFalseWhenElementsExist_583) {
  SparseArray<int> sa(10);
  sa.set(0, 10);
  EXPECT_FALSE(sa.empty());
}

// ==================== Clear Tests ====================

TEST_F(SparseArrayTest_583, ClearRemovesAllElements_583) {
  SparseArray<int> sa(10);
  sa.set(0, 10);
  sa.set(3, 30);
  sa.set(7, 70);

  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
  EXPECT_FALSE(sa.has_index(0));
  EXPECT_FALSE(sa.has_index(3));
  EXPECT_FALSE(sa.has_index(7));
}

TEST_F(SparseArrayTest_583, ClearOnEmptyArray_583) {
  SparseArray<int> sa(10);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

// ==================== Resize Tests ====================

TEST_F(SparseArrayTest_583, ResizeIncreasesMaxSize_583) {
  SparseArray<int> sa(5);
  EXPECT_EQ(sa.max_size(), 5);

  sa.resize(20);
  EXPECT_EQ(sa.max_size(), 20);
}

TEST_F(SparseArrayTest_583, ResizePreservesExistingElements_583) {
  SparseArray<int> sa(5);
  sa.set(0, 10);
  sa.set(2, 30);

  sa.resize(20);
  EXPECT_EQ(sa.size(), 2);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_TRUE(sa.has_index(2));
  EXPECT_EQ(sa.get_existing(0), 10);
  EXPECT_EQ(sa.get_existing(2), 30);
}

TEST_F(SparseArrayTest_583, ResizeAllowsNewLargerIndices_583) {
  SparseArray<int> sa(5);
  sa.resize(20);

  sa.set(15, 150);
  EXPECT_TRUE(sa.has_index(15));
  EXPECT_EQ(sa.get_existing(15), 150);
}

// ==================== Iterator Tests ====================

TEST_F(SparseArrayTest_583, BeginEqualsEndWhenEmpty_583) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.begin(), sa.end());
}

TEST_F(SparseArrayTest_583, IteratorTraversesAllElements_583) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(3, 30);
  sa.set(5, 50);

  int count = 0;
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 3);
}

TEST_F(SparseArrayTest_583, IteratorAccessesIndexAndValue_583) {
  SparseArray<int> sa(10);
  sa.set(4, 40);

  auto it = sa.begin();
  EXPECT_NE(it, sa.end());
  EXPECT_EQ(it->index(), 4);
  EXPECT_EQ(it->value(), 40);
}

// ==================== Boundary Condition Tests ====================

TEST_F(SparseArrayTest_583, SetAtMaxSizeMinusOne_583) {
  SparseArray<int> sa(10);
  sa.set(9, 90);
  EXPECT_TRUE(sa.has_index(9));
  EXPECT_EQ(sa.get_existing(9), 90);
}

TEST_F(SparseArrayTest_583, SetAtIndexZero_583) {
  SparseArray<int> sa(10);
  sa.set(0, 0);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 0);
}

TEST_F(SparseArrayTest_583, FillAllIndices_583) {
  const int max_size = 10;
  SparseArray<int> sa(max_size);
  for (int i = 0; i < max_size; i++) {
    sa.set(i, i * 10);
  }
  EXPECT_EQ(sa.size(), max_size);
  for (int i = 0; i < max_size; i++) {
    EXPECT_TRUE(sa.has_index(i));
    EXPECT_EQ(sa.get_existing(i), i * 10);
  }
}

TEST_F(SparseArrayTest_583, MaxSizeOneElement_583) {
  SparseArray<int> sa(1);
  EXPECT_EQ(sa.max_size(), 1);
  sa.set(0, 42);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 42);
}

// ==================== Less Comparator Test ====================

TEST_F(SparseArrayTest_583, LessComparison_583) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  sa.set(2, 20);

  // The less function compares IndexValues by index
  // We can at least verify it compiles and is callable
  // by getting iterators and checking order after potential sort
  auto it1 = sa.begin();
  auto it2 = it1 + 1;
  // Just verify both are valid
  EXPECT_NE(it1, sa.end());
  EXPECT_NE(it2, sa.end());
}

// ==================== Value Type Tests ====================

TEST_F(SparseArrayTest_583, StringValueType_583) {
  SparseArray<std::string> sa(10);
  sa.set(3, "hello");
  sa.set(7, "world");

  EXPECT_EQ(sa.size(), 2);
  EXPECT_EQ(sa.get_existing(3), "hello");
  EXPECT_EQ(sa.get_existing(7), "world");
}

TEST_F(SparseArrayTest_583, DoubleValueType_583) {
  SparseArray<double> sa(10);
  sa.set(1, 3.14);
  sa.set(2, 2.71);

  EXPECT_DOUBLE_EQ(sa.get_existing(1), 3.14);
  EXPECT_DOUBLE_EQ(sa.get_existing(2), 2.71);
}

// ==================== Multiple Operations Test ====================

TEST_F(SparseArrayTest_583, SetClearSetAgain_583) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  sa.set(8, 80);
  EXPECT_EQ(sa.size(), 2);

  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_FALSE(sa.has_index(5));
  EXPECT_FALSE(sa.has_index(8));

  sa.set(5, 500);
  sa.set(3, 300);
  EXPECT_EQ(sa.size(), 2);
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get_existing(5), 500);
  EXPECT_EQ(sa.get_existing(3), 300);
}

TEST_F(SparseArrayTest_583, SetReturnedIteratorIsValid_583) {
  SparseArray<int> sa(10);
  auto it = sa.set(3, 30);
  EXPECT_EQ(it->index(), 3);
  EXPECT_EQ(it->value(), 30);
}

TEST_F(SparseArrayTest_583, SetNewReturnedIteratorIsValid_583) {
  SparseArray<int> sa(10);
  auto it = sa.set_new(7, 70);
  EXPECT_EQ(it->index(), 7);
  EXPECT_EQ(it->value(), 70);
}

TEST_F(SparseArrayTest_583, SetExistingReturnedIteratorIsValid_583) {
  SparseArray<int> sa(10);
  sa.set(4, 40);
  auto it = sa.set_existing(4, 400);
  EXPECT_EQ(it->index(), 4);
  EXPECT_EQ(it->value(), 400);
}

TEST_F(SparseArrayTest_583, MoveConstructorLeavesSourceEmpty_583) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(2, 20);
  sa.set(3, 30);

  SparseArray<int> moved(std::move(sa));
  EXPECT_EQ(sa.size(), 0);
  EXPECT_EQ(moved.size(), 3);
}

TEST_F(SparseArrayTest_583, MoveAssignmentLeavesSourceEmpty_583) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(2, 20);

  SparseArray<int> other;
  other = std::move(sa);
  EXPECT_EQ(sa.size(), 0);
  EXPECT_EQ(other.size(), 2);
  EXPECT_TRUE(other.has_index(1));
  EXPECT_TRUE(other.has_index(2));
}

TEST_F(SparseArrayTest_583, CopyDoesNotAffectOriginal_583) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(2, 20);

  SparseArray<int> copy(sa);
  copy.set(3, 30);
  copy.set(1, 100);

  // Original should be unaffected
  EXPECT_EQ(sa.size(), 2);
  EXPECT_EQ(sa.get_existing(1), 10);
  EXPECT_FALSE(sa.has_index(3));
}

TEST_F(SparseArrayTest_583, ResizeSmaller_583) {
  SparseArray<int> sa(20);
  sa.set(0, 10);
  sa.set(1, 20);

  sa.resize(5);
  EXPECT_EQ(sa.max_size(), 5);
  // Elements within range should still be accessible
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_TRUE(sa.has_index(1));
}

}  // namespace re2
