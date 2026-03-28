#include "gtest/gtest.h"
#include "re2/sparse_array.h"

namespace re2 {

// Test fixture for SparseArray tests
class SparseArrayTest_78 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(SparseArrayTest_78, DefaultConstructor_78) {
  SparseArray<int> sa;
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_78, ConstructorWithMaxSize_78) {
  SparseArray<int> sa(100);
  EXPECT_EQ(sa.size(), 0);
  EXPECT_EQ(sa.max_size(), 100);
  EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_78, CopyConstructor_78) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(7, 70);

  SparseArray<int> copy(sa);
  EXPECT_EQ(copy.size(), 2);
  EXPECT_EQ(copy.max_size(), 10);
  EXPECT_TRUE(copy.has_index(3));
  EXPECT_TRUE(copy.has_index(7));
  EXPECT_EQ(copy.get_existing(3), 30);
  EXPECT_EQ(copy.get_existing(7), 70);
}

TEST_F(SparseArrayTest_78, MoveConstructor_78) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(7, 70);

  SparseArray<int> moved(std::move(sa));
  EXPECT_EQ(moved.size(), 2);
  EXPECT_TRUE(moved.has_index(3));
  EXPECT_TRUE(moved.has_index(7));
  EXPECT_EQ(moved.get_existing(3), 30);
  EXPECT_EQ(moved.get_existing(7), 70);
}

// ==================== Assignment Operator Tests ====================

TEST_F(SparseArrayTest_78, CopyAssignment_78) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(5, 50);

  SparseArray<int> other(5);
  other = sa;
  EXPECT_EQ(other.size(), 2);
  EXPECT_TRUE(other.has_index(2));
  EXPECT_TRUE(other.has_index(5));
  EXPECT_EQ(other.get_existing(2), 20);
  EXPECT_EQ(other.get_existing(5), 50);
}

TEST_F(SparseArrayTest_78, MoveAssignment_78) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(5, 50);

  SparseArray<int> other(5);
  other = std::move(sa);
  EXPECT_EQ(other.size(), 2);
  EXPECT_TRUE(other.has_index(2));
  EXPECT_TRUE(other.has_index(5));
  EXPECT_EQ(other.get_existing(2), 20);
  EXPECT_EQ(other.get_existing(5), 50);
}

// ==================== set() Tests ====================

TEST_F(SparseArrayTest_78, SetNewElement_78) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get_existing(3), 30);
}

TEST_F(SparseArrayTest_78, SetExistingElement_78) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(3, 300);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get_existing(3), 300);
}

TEST_F(SparseArrayTest_78, SetMultipleElements_78) {
  SparseArray<int> sa(10);
  sa.set(0, 0);
  sa.set(5, 50);
  sa.set(9, 90);
  EXPECT_EQ(sa.size(), 3);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_TRUE(sa.has_index(9));
  EXPECT_EQ(sa.get_existing(0), 0);
  EXPECT_EQ(sa.get_existing(5), 50);
  EXPECT_EQ(sa.get_existing(9), 90);
}

// ==================== set_new() Tests ====================

TEST_F(SparseArrayTest_78, SetNew_78) {
  SparseArray<int> sa(10);
  sa.set_new(4, 40);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(4));
  EXPECT_EQ(sa.get_existing(4), 40);
}

TEST_F(SparseArrayTest_78, SetNewMultiple_78) {
  SparseArray<int> sa(10);
  sa.set_new(1, 10);
  sa.set_new(3, 30);
  sa.set_new(5, 50);
  EXPECT_EQ(sa.size(), 3);
  EXPECT_TRUE(sa.has_index(1));
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_TRUE(sa.has_index(5));
}

// ==================== set_existing() Tests ====================

TEST_F(SparseArrayTest_78, SetExistingUpdatesValue_78) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  sa.set_existing(5, 500);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_EQ(sa.get_existing(5), 500);
}

TEST_F(SparseArrayTest_78, SetExistingReturnsIterator_78) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  auto it = sa.set_existing(5, 500);
  EXPECT_EQ(it->value(), 500);
}

// ==================== get_existing() Tests ====================

TEST_F(SparseArrayTest_78, GetExistingReturnsCorrectValue_78) {
  SparseArray<int> sa(10);
  sa.set(7, 77);
  EXPECT_EQ(sa.get_existing(7), 77);
}

TEST_F(SparseArrayTest_78, GetExistingIsModifiable_78) {
  SparseArray<int> sa(10);
  sa.set(7, 77);
  sa.get_existing(7) = 777;
  EXPECT_EQ(sa.get_existing(7), 777);
}

// ==================== has_index() Tests ====================

TEST_F(SparseArrayTest_78, HasIndexReturnsFalseForEmpty_78) {
  SparseArray<int> sa(10);
  EXPECT_FALSE(sa.has_index(0));
  EXPECT_FALSE(sa.has_index(5));
  EXPECT_FALSE(sa.has_index(9));
}

TEST_F(SparseArrayTest_78, HasIndexReturnsTrueAfterSet_78) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_FALSE(sa.has_index(4));
}

TEST_F(SparseArrayTest_78, HasIndexReturnsFalseAfterClear_78) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.clear();
  EXPECT_FALSE(sa.has_index(3));
}

// ==================== size() and empty() Tests ====================

TEST_F(SparseArrayTest_78, SizeIncreasesWithSet_78) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.size(), 0);
  sa.set(0, 0);
  EXPECT_EQ(sa.size(), 1);
  sa.set(1, 1);
  EXPECT_EQ(sa.size(), 2);
}

TEST_F(SparseArrayTest_78, SizeDoesNotIncreaseOnOverwrite_78) {
  SparseArray<int> sa(10);
  sa.set(0, 0);
  sa.set(0, 1);
  EXPECT_EQ(sa.size(), 1);
}

TEST_F(SparseArrayTest_78, EmptyReturnsTrueWhenEmpty_78) {
  SparseArray<int> sa(10);
  EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_78, EmptyReturnsFalseWhenNotEmpty_78) {
  SparseArray<int> sa(10);
  sa.set(0, 0);
  EXPECT_FALSE(sa.empty());
}

// ==================== clear() Tests ====================

TEST_F(SparseArrayTest_78, ClearMakesEmpty_78) {
  SparseArray<int> sa(10);
  sa.set(0, 0);
  sa.set(1, 1);
  sa.set(2, 2);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_78, ClearDoesNotChangeMaxSize_78) {
  SparseArray<int> sa(10);
  sa.set(0, 0);
  sa.clear();
  EXPECT_EQ(sa.max_size(), 10);
}

TEST_F(SparseArrayTest_78, ClearThenReuse_78) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.clear();
  EXPECT_FALSE(sa.has_index(3));
  sa.set(3, 300);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get_existing(3), 300);
}

// ==================== max_size() Tests ====================

TEST_F(SparseArrayTest_78, MaxSizeReturnsCorrectValue_78) {
  SparseArray<int> sa(50);
  EXPECT_EQ(sa.max_size(), 50);
}

// ==================== resize() Tests ====================

TEST_F(SparseArrayTest_78, ResizeIncreasesMaxSize_78) {
  SparseArray<int> sa(10);
  sa.resize(20);
  EXPECT_EQ(sa.max_size(), 20);
}

TEST_F(SparseArrayTest_78, ResizePreservesExistingElements_78) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(7, 70);
  sa.resize(20);
  EXPECT_EQ(sa.size(), 2);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_TRUE(sa.has_index(7));
  EXPECT_EQ(sa.get_existing(3), 30);
  EXPECT_EQ(sa.get_existing(7), 70);
}

TEST_F(SparseArrayTest_78, ResizeAllowsNewIndices_78) {
  SparseArray<int> sa(10);
  sa.resize(20);
  sa.set(15, 150);
  EXPECT_TRUE(sa.has_index(15));
  EXPECT_EQ(sa.get_existing(15), 150);
}

// ==================== Iterator Tests ====================

TEST_F(SparseArrayTest_78, BeginEqualsEndWhenEmpty_78) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.begin(), sa.end());
}

TEST_F(SparseArrayTest_78, IteratorTraversal_78) {
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

TEST_F(SparseArrayTest_78, IteratorValues_78) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(5, 50);

  // Verify all values are accessible through iteration
  std::set<int> values;
  std::set<int> indices;
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    values.insert(it->value());
    indices.insert(it->index());
  }
  EXPECT_TRUE(values.count(20));
  EXPECT_TRUE(values.count(50));
  EXPECT_TRUE(indices.count(2));
  EXPECT_TRUE(indices.count(5));
}

// ==================== less() Tests ====================

TEST_F(SparseArrayTest_78, LessComparison_78) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(5, 50);

  // The less function compares IndexValue objects by index
  auto it1 = sa.begin();
  auto it2 = sa.begin();
  // We can at least verify that less is callable
  // The exact behavior depends on index comparison
  bool result = SparseArray<int>::less(*sa.begin(), *(sa.begin()));
  EXPECT_FALSE(result); // same element should not be less than itself
}

// ==================== Boundary Tests ====================

TEST_F(SparseArrayTest_78, SetAtIndexZero_78) {
  SparseArray<int> sa(10);
  sa.set(0, 100);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 100);
}

TEST_F(SparseArrayTest_78, SetAtMaxIndex_78) {
  SparseArray<int> sa(10);
  sa.set(9, 90);
  EXPECT_TRUE(sa.has_index(9));
  EXPECT_EQ(sa.get_existing(9), 90);
}

TEST_F(SparseArrayTest_78, FillAllIndices_78) {
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

TEST_F(SparseArrayTest_78, MaxSizeOne_78) {
  SparseArray<int> sa(1);
  EXPECT_EQ(sa.max_size(), 1);
  sa.set(0, 42);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 42);
}

// ==================== String Value Type Tests ====================

TEST_F(SparseArrayTest_78, StringValueType_78) {
  SparseArray<std::string> sa(10);
  sa.set(3, "hello");
  sa.set(7, "world");
  EXPECT_EQ(sa.size(), 2);
  EXPECT_EQ(sa.get_existing(3), "hello");
  EXPECT_EQ(sa.get_existing(7), "world");
}

// ==================== set() Return Value Tests ====================

TEST_F(SparseArrayTest_78, SetReturnsIterator_78) {
  SparseArray<int> sa(10);
  auto it = sa.set(3, 30);
  EXPECT_EQ(it->index(), 3);
  EXPECT_EQ(it->value(), 30);
}

TEST_F(SparseArrayTest_78, SetNewReturnsIterator_78) {
  SparseArray<int> sa(10);
  auto it = sa.set_new(5, 50);
  EXPECT_EQ(it->index(), 5);
  EXPECT_EQ(it->value(), 50);
}

// ==================== Multiple Clear and Reuse Tests ====================

TEST_F(SparseArrayTest_78, MultipleClearAndReuse_78) {
  SparseArray<int> sa(10);
  for (int round = 0; round < 3; round++) {
    for (int i = 0; i < 10; i++) {
      sa.set(i, round * 100 + i);
    }
    EXPECT_EQ(sa.size(), 10);
    for (int i = 0; i < 10; i++) {
      EXPECT_EQ(sa.get_existing(i), round * 100 + i);
    }
    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
  }
}

// ==================== Overwrite All Elements Tests ====================

TEST_F(SparseArrayTest_78, OverwriteAllElements_78) {
  SparseArray<int> sa(10);
  for (int i = 0; i < 10; i++) {
    sa.set(i, i);
  }
  for (int i = 0; i < 10; i++) {
    sa.set(i, i * 100);
  }
  EXPECT_EQ(sa.size(), 10);
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(sa.get_existing(i), i * 100);
  }
}

// ==================== Double Value Type Tests ====================

TEST_F(SparseArrayTest_78, DoubleValueType_78) {
  SparseArray<double> sa(10);
  sa.set(0, 3.14);
  sa.set(9, 2.718);
  EXPECT_DOUBLE_EQ(sa.get_existing(0), 3.14);
  EXPECT_DOUBLE_EQ(sa.get_existing(9), 2.718);
}

}  // namespace re2
