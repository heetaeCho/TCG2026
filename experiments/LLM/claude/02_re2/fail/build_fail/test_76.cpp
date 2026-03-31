#include "gtest/gtest.h"
#include "re2/sparse_array.h"

namespace re2 {

// Test fixture for SparseArray tests
class SparseArrayTest_76 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// --- Construction Tests ---

TEST_F(SparseArrayTest_76, DefaultConstructor_76) {
  SparseArray<int> sa;
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_76, ConstructWithMaxSize_76) {
  SparseArray<int> sa(100);
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
  EXPECT_EQ(sa.max_size(), 100);
}

TEST_F(SparseArrayTest_76, CopyConstructor_76) {
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

TEST_F(SparseArrayTest_76, MoveConstructor_76) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  sa.set(2, 20);

  SparseArray<int> moved(std::move(sa));
  EXPECT_EQ(moved.size(), 2);
  EXPECT_TRUE(moved.has_index(5));
  EXPECT_TRUE(moved.has_index(2));
  EXPECT_EQ(moved.get_existing(5), 50);
  EXPECT_EQ(moved.get_existing(2), 20);
}

// --- Assignment Tests ---

TEST_F(SparseArrayTest_76, CopyAssignment_76) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(4, 40);

  SparseArray<int> other(5);
  other = sa;
  EXPECT_EQ(other.size(), 2);
  EXPECT_TRUE(other.has_index(1));
  EXPECT_TRUE(other.has_index(4));
  EXPECT_EQ(other.get_existing(1), 10);
  EXPECT_EQ(other.get_existing(4), 40);
}

TEST_F(SparseArrayTest_76, MoveAssignment_76) {
  SparseArray<int> sa(10);
  sa.set(6, 60);

  SparseArray<int> other(5);
  other = std::move(sa);
  EXPECT_EQ(other.size(), 1);
  EXPECT_TRUE(other.has_index(6));
  EXPECT_EQ(other.get_existing(6), 60);
}

// --- set() Tests ---

TEST_F(SparseArrayTest_76, SetNewElement_76) {
  SparseArray<int> sa(10);
  sa.set(3, 42);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get_existing(3), 42);
}

TEST_F(SparseArrayTest_76, SetOverwriteExistingElement_76) {
  SparseArray<int> sa(10);
  sa.set(3, 42);
  sa.set(3, 99);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get_existing(3), 99);
}

TEST_F(SparseArrayTest_76, SetMultipleElements_76) {
  SparseArray<int> sa(10);
  sa.set(0, 100);
  sa.set(5, 500);
  sa.set(9, 900);
  EXPECT_EQ(sa.size(), 3);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_TRUE(sa.has_index(9));
  EXPECT_EQ(sa.get_existing(0), 100);
  EXPECT_EQ(sa.get_existing(5), 500);
  EXPECT_EQ(sa.get_existing(9), 900);
}

TEST_F(SparseArrayTest_76, SetReturnsIterator_76) {
  SparseArray<int> sa(10);
  auto it = sa.set(3, 42);
  EXPECT_EQ(it->value(), 42);
  EXPECT_EQ(it->index(), 3);
}

// --- set_new() Tests ---

TEST_F(SparseArrayTest_76, SetNewOnNewIndex_76) {
  SparseArray<int> sa(10);
  sa.set_new(4, 44);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(4));
  EXPECT_EQ(sa.get_existing(4), 44);
}

// --- set_existing() Tests ---

TEST_F(SparseArrayTest_76, SetExistingUpdatesValue_76) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set_existing(2, 200);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_EQ(sa.get_existing(2), 200);
}

// --- has_index() Tests ---

TEST_F(SparseArrayTest_76, HasIndexReturnsFalseForMissing_76) {
  SparseArray<int> sa(10);
  EXPECT_FALSE(sa.has_index(0));
  EXPECT_FALSE(sa.has_index(5));
  EXPECT_FALSE(sa.has_index(9));
}

TEST_F(SparseArrayTest_76, HasIndexReturnsTrueForPresent_76) {
  SparseArray<int> sa(10);
  sa.set(7, 77);
  EXPECT_TRUE(sa.has_index(7));
  EXPECT_FALSE(sa.has_index(6));
}

// --- get_existing() Tests ---

TEST_F(SparseArrayTest_76, GetExistingReturnsCorrectValue_76) {
  SparseArray<int> sa(10);
  sa.set(8, 888);
  EXPECT_EQ(sa.get_existing(8), 888);
}

TEST_F(SparseArrayTest_76, GetExistingReturnsReference_76) {
  SparseArray<int> sa(10);
  sa.set(3, 33);
  int& ref = sa.get_existing(3);
  ref = 333;
  EXPECT_EQ(sa.get_existing(3), 333);
}

// --- clear() Tests ---

TEST_F(SparseArrayTest_76, ClearEmptiesArray_76) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(2, 20);
  sa.set(3, 30);
  EXPECT_EQ(sa.size(), 3);

  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
  EXPECT_FALSE(sa.has_index(1));
  EXPECT_FALSE(sa.has_index(2));
  EXPECT_FALSE(sa.has_index(3));
}

TEST_F(SparseArrayTest_76, ClearOnEmptyArray_76) {
  SparseArray<int> sa(10);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

// --- size() and empty() Tests ---

TEST_F(SparseArrayTest_76, SizeIncreasesWithSet_76) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.size(), 0);
  sa.set(0, 1);
  EXPECT_EQ(sa.size(), 1);
  sa.set(1, 2);
  EXPECT_EQ(sa.size(), 2);
}

TEST_F(SparseArrayTest_76, SizeDoesNotIncreaseOnOverwrite_76) {
  SparseArray<int> sa(10);
  sa.set(0, 1);
  sa.set(0, 2);
  EXPECT_EQ(sa.size(), 1);
}

TEST_F(SparseArrayTest_76, EmptyReturnsTrueWhenEmpty_76) {
  SparseArray<int> sa(10);
  EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_76, EmptyReturnsFalseWhenNotEmpty_76) {
  SparseArray<int> sa(10);
  sa.set(0, 1);
  EXPECT_FALSE(sa.empty());
}

// --- max_size() Tests ---

TEST_F(SparseArrayTest_76, MaxSizeMatchesConstructorArg_76) {
  SparseArray<int> sa(50);
  EXPECT_EQ(sa.max_size(), 50);
}

// --- begin() and end() / Iterator Tests ---

TEST_F(SparseArrayTest_76, BeginEqualsEndWhenEmpty_76) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.begin(), sa.end());
}

TEST_F(SparseArrayTest_76, IteratorTraversesAllElements_76) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(5, 50);
  sa.set(8, 80);

  int count = 0;
  int sum_values = 0;
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    sum_values += it->value();
    count++;
  }
  EXPECT_EQ(count, 3);
  EXPECT_EQ(sum_values, 150);
}

TEST_F(SparseArrayTest_76, IteratorDistanceMatchesSize_76) {
  SparseArray<int> sa(10);
  sa.set(0, 0);
  sa.set(3, 3);
  sa.set(9, 9);
  EXPECT_EQ(sa.end() - sa.begin(), sa.size());
}

// --- resize() Tests ---

TEST_F(SparseArrayTest_76, ResizeIncreasesMaxSize_76) {
  SparseArray<int> sa(5);
  sa.resize(20);
  EXPECT_EQ(sa.max_size(), 20);
}

TEST_F(SparseArrayTest_76, ResizePreservesExistingElements_76) {
  SparseArray<int> sa(10);
  sa.set(2, 22);
  sa.set(4, 44);
  sa.resize(20);
  EXPECT_EQ(sa.size(), 2);
  EXPECT_TRUE(sa.has_index(2));
  EXPECT_TRUE(sa.has_index(4));
  EXPECT_EQ(sa.get_existing(2), 22);
  EXPECT_EQ(sa.get_existing(4), 44);
}

TEST_F(SparseArrayTest_76, ResizeAllowsSettingNewIndices_76) {
  SparseArray<int> sa(5);
  sa.resize(15);
  sa.set(10, 100);
  EXPECT_TRUE(sa.has_index(10));
  EXPECT_EQ(sa.get_existing(10), 100);
}

// --- Boundary Conditions ---

TEST_F(SparseArrayTest_76, SetAtIndexZero_76) {
  SparseArray<int> sa(10);
  sa.set(0, 999);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 999);
}

TEST_F(SparseArrayTest_76, SetAtMaxIndexMinusOne_76) {
  SparseArray<int> sa(10);
  sa.set(9, 999);
  EXPECT_TRUE(sa.has_index(9));
  EXPECT_EQ(sa.get_existing(9), 999);
}

TEST_F(SparseArrayTest_76, FillEntireArray_76) {
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

TEST_F(SparseArrayTest_76, ClearAndRefill_76) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(2, 20);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);

  sa.set(3, 30);
  sa.set(4, 40);
  EXPECT_EQ(sa.size(), 2);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_TRUE(sa.has_index(4));
  EXPECT_FALSE(sa.has_index(1));
  EXPECT_FALSE(sa.has_index(2));
}

// --- less() static method test ---

TEST_F(SparseArrayTest_76, LessComparesIndices_76) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(7, 70);

  // Get iterators to the elements
  auto it_begin = sa.begin();
  auto it_next = it_begin + 1;
  
  // less() should compare by index
  // We check that the static less function works consistently
  bool result1 = SparseArray<int>::less(*it_begin, *it_next);
  bool result2 = SparseArray<int>::less(*it_next, *it_begin);
  // One should be true, the other false (they have different indices)
  EXPECT_NE(result1, result2);
}

// --- String Value Type ---

TEST_F(SparseArrayTest_76, WorksWithStringValues_76) {
  SparseArray<std::string> sa(10);
  sa.set(2, "hello");
  sa.set(5, "world");
  EXPECT_EQ(sa.size(), 2);
  EXPECT_EQ(sa.get_existing(2), "hello");
  EXPECT_EQ(sa.get_existing(5), "world");
}

TEST_F(SparseArrayTest_76, OverwriteStringValue_76) {
  SparseArray<std::string> sa(10);
  sa.set(3, "foo");
  sa.set(3, "bar");
  EXPECT_EQ(sa.size(), 1);
  EXPECT_EQ(sa.get_existing(3), "bar");
}

// --- MaxSize of 1 (edge case) ---

TEST_F(SparseArrayTest_76, MaxSizeOne_76) {
  SparseArray<int> sa(1);
  EXPECT_EQ(sa.max_size(), 1);
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());

  sa.set(0, 42);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_FALSE(sa.empty());
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 42);

  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

// --- Double value type ---

TEST_F(SparseArrayTest_76, WorksWithDoubleValues_76) {
  SparseArray<double> sa(5);
  sa.set(0, 3.14);
  sa.set(4, 2.72);
  EXPECT_EQ(sa.size(), 2);
  EXPECT_DOUBLE_EQ(sa.get_existing(0), 3.14);
  EXPECT_DOUBLE_EQ(sa.get_existing(4), 2.72);
}

// --- set_new multiple times ---

TEST_F(SparseArrayTest_76, SetNewMultipleDistinctIndices_76) {
  SparseArray<int> sa(10);
  sa.set_new(0, 0);
  sa.set_new(1, 10);
  sa.set_new(2, 20);
  EXPECT_EQ(sa.size(), 3);
  EXPECT_EQ(sa.get_existing(0), 0);
  EXPECT_EQ(sa.get_existing(1), 10);
  EXPECT_EQ(sa.get_existing(2), 20);
}

// --- Resize to smaller removes elements beyond new max ---

TEST_F(SparseArrayTest_76, ResizeToSmallerSize_76) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(8, 80);
  sa.resize(5);
  EXPECT_EQ(sa.max_size(), 5);
  // Index 2 should still be accessible, index 8 may be removed
  EXPECT_TRUE(sa.has_index(2));
  EXPECT_EQ(sa.get_existing(2), 20);
}

// --- Copy preserves independence ---

TEST_F(SparseArrayTest_76, CopyIsIndependent_76) {
  SparseArray<int> sa(10);
  sa.set(3, 30);

  SparseArray<int> copy(sa);
  copy.set(3, 300);
  copy.set(5, 500);

  // Original should be unaffected
  EXPECT_EQ(sa.size(), 1);
  EXPECT_EQ(sa.get_existing(3), 30);
  EXPECT_FALSE(sa.has_index(5));
}

}  // namespace re2
