#include "gtest/gtest.h"
#include "re2/sparse_array.h"

namespace re2 {

// Test fixture for SparseArray tests
class SparseArrayTest_72 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// === Construction Tests ===

TEST_F(SparseArrayTest_72, DefaultConstructor_72) {
  SparseArray<int> arr;
  EXPECT_EQ(arr.size(), 0);
  EXPECT_TRUE(arr.empty());
}

TEST_F(SparseArrayTest_72, ConstructorWithMaxSize_72) {
  SparseArray<int> arr(100);
  EXPECT_EQ(arr.size(), 0);
  EXPECT_EQ(arr.max_size(), 100);
  EXPECT_TRUE(arr.empty());
}

TEST_F(SparseArrayTest_72, ConstructorWithZeroMaxSize_72) {
  SparseArray<int> arr(0);
  EXPECT_EQ(arr.size(), 0);
  EXPECT_EQ(arr.max_size(), 0);
  EXPECT_TRUE(arr.empty());
}

TEST_F(SparseArrayTest_72, CopyConstructor_72) {
  SparseArray<int> arr(10);
  arr.set(3, 30);
  arr.set(7, 70);

  SparseArray<int> copy(arr);
  EXPECT_EQ(copy.size(), 2);
  EXPECT_EQ(copy.max_size(), 10);
  EXPECT_TRUE(copy.has_index(3));
  EXPECT_TRUE(copy.has_index(7));
  EXPECT_EQ(copy.get_existing(3), 30);
  EXPECT_EQ(copy.get_existing(7), 70);
}

TEST_F(SparseArrayTest_72, MoveConstructor_72) {
  SparseArray<int> arr(10);
  arr.set(3, 30);
  arr.set(7, 70);

  SparseArray<int> moved(std::move(arr));
  EXPECT_EQ(moved.size(), 2);
  EXPECT_TRUE(moved.has_index(3));
  EXPECT_TRUE(moved.has_index(7));
  EXPECT_EQ(moved.get_existing(3), 30);
  EXPECT_EQ(moved.get_existing(7), 70);
}

// === Assignment Tests ===

TEST_F(SparseArrayTest_72, CopyAssignment_72) {
  SparseArray<int> arr(10);
  arr.set(5, 50);

  SparseArray<int> other(20);
  other.set(1, 10);
  other = arr;

  EXPECT_EQ(other.size(), 1);
  EXPECT_TRUE(other.has_index(5));
  EXPECT_EQ(other.get_existing(5), 50);
}

TEST_F(SparseArrayTest_72, MoveAssignment_72) {
  SparseArray<int> arr(10);
  arr.set(5, 50);

  SparseArray<int> other(20);
  other = std::move(arr);

  EXPECT_EQ(other.size(), 1);
  EXPECT_TRUE(other.has_index(5));
  EXPECT_EQ(other.get_existing(5), 50);
}

// === Set/Get Tests ===

TEST_F(SparseArrayTest_72, SetAndGetExisting_72) {
  SparseArray<int> arr(10);
  arr.set(0, 100);
  EXPECT_EQ(arr.size(), 1);
  EXPECT_TRUE(arr.has_index(0));
  EXPECT_EQ(arr.get_existing(0), 100);
}

TEST_F(SparseArrayTest_72, SetMultipleValues_72) {
  SparseArray<int> arr(10);
  arr.set(0, 0);
  arr.set(5, 50);
  arr.set(9, 90);

  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr.get_existing(0), 0);
  EXPECT_EQ(arr.get_existing(5), 50);
  EXPECT_EQ(arr.get_existing(9), 90);
}

TEST_F(SparseArrayTest_72, SetOverwritesExistingValue_72) {
  SparseArray<int> arr(10);
  arr.set(3, 30);
  EXPECT_EQ(arr.get_existing(3), 30);

  arr.set(3, 300);
  EXPECT_EQ(arr.size(), 1);
  EXPECT_EQ(arr.get_existing(3), 300);
}

TEST_F(SparseArrayTest_72, SetNew_72) {
  SparseArray<int> arr(10);
  arr.set_new(3, 30);
  EXPECT_EQ(arr.size(), 1);
  EXPECT_TRUE(arr.has_index(3));
  EXPECT_EQ(arr.get_existing(3), 30);
}

TEST_F(SparseArrayTest_72, SetExisting_72) {
  SparseArray<int> arr(10);
  arr.set(3, 30);
  arr.set_existing(3, 300);
  EXPECT_EQ(arr.size(), 1);
  EXPECT_EQ(arr.get_existing(3), 300);
}

// === has_index Tests ===

TEST_F(SparseArrayTest_72, HasIndexReturnsFalseForUnsetIndex_72) {
  SparseArray<int> arr(10);
  EXPECT_FALSE(arr.has_index(0));
  EXPECT_FALSE(arr.has_index(5));
  EXPECT_FALSE(arr.has_index(9));
}

TEST_F(SparseArrayTest_72, HasIndexReturnsTrueForSetIndex_72) {
  SparseArray<int> arr(10);
  arr.set(5, 50);
  EXPECT_TRUE(arr.has_index(5));
}

// === Size / Empty Tests ===

TEST_F(SparseArrayTest_72, SizeIncreasesOnSet_72) {
  SparseArray<int> arr(10);
  EXPECT_EQ(arr.size(), 0);
  arr.set(0, 0);
  EXPECT_EQ(arr.size(), 1);
  arr.set(1, 1);
  EXPECT_EQ(arr.size(), 2);
}

TEST_F(SparseArrayTest_72, SizeDoesNotIncreaseOnOverwrite_72) {
  SparseArray<int> arr(10);
  arr.set(3, 30);
  EXPECT_EQ(arr.size(), 1);
  arr.set(3, 300);
  EXPECT_EQ(arr.size(), 1);
}

TEST_F(SparseArrayTest_72, EmptyAfterConstruction_72) {
  SparseArray<int> arr(10);
  EXPECT_TRUE(arr.empty());
}

TEST_F(SparseArrayTest_72, NotEmptyAfterSet_72) {
  SparseArray<int> arr(10);
  arr.set(0, 0);
  EXPECT_FALSE(arr.empty());
}

// === Clear Tests ===

TEST_F(SparseArrayTest_72, ClearRemovesAllElements_72) {
  SparseArray<int> arr(10);
  arr.set(0, 0);
  arr.set(5, 50);
  arr.set(9, 90);

  arr.clear();
  EXPECT_EQ(arr.size(), 0);
  EXPECT_TRUE(arr.empty());
  EXPECT_FALSE(arr.has_index(0));
  EXPECT_FALSE(arr.has_index(5));
  EXPECT_FALSE(arr.has_index(9));
}

TEST_F(SparseArrayTest_72, ClearOnEmptyArray_72) {
  SparseArray<int> arr(10);
  arr.clear();
  EXPECT_EQ(arr.size(), 0);
  EXPECT_TRUE(arr.empty());
}

TEST_F(SparseArrayTest_72, SetAfterClear_72) {
  SparseArray<int> arr(10);
  arr.set(3, 30);
  arr.clear();
  arr.set(3, 300);
  EXPECT_EQ(arr.size(), 1);
  EXPECT_EQ(arr.get_existing(3), 300);
}

// === Resize Tests ===

TEST_F(SparseArrayTest_72, ResizeIncreasesMaxSize_72) {
  SparseArray<int> arr(10);
  arr.set(5, 50);
  arr.resize(20);
  EXPECT_EQ(arr.max_size(), 20);
  // Existing elements should be preserved after resize
  EXPECT_TRUE(arr.has_index(5));
  EXPECT_EQ(arr.get_existing(5), 50);
}

TEST_F(SparseArrayTest_72, ResizeAllowsNewIndices_72) {
  SparseArray<int> arr(10);
  arr.resize(20);
  arr.set(15, 150);
  EXPECT_TRUE(arr.has_index(15));
  EXPECT_EQ(arr.get_existing(15), 150);
}

// === Iterator Tests ===

TEST_F(SparseArrayTest_72, BeginEqualsEndWhenEmpty_72) {
  SparseArray<int> arr(10);
  EXPECT_EQ(arr.begin(), arr.end());
}

TEST_F(SparseArrayTest_72, IteratorRangeMatchesSize_72) {
  SparseArray<int> arr(10);
  arr.set(0, 0);
  arr.set(5, 50);
  arr.set(9, 90);

  int count = 0;
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 3);
}

TEST_F(SparseArrayTest_72, IteratorContainsSetValues_72) {
  SparseArray<int> arr(10);
  arr.set(2, 20);
  arr.set(7, 70);

  std::set<int> indices;
  std::set<int> values;
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    indices.insert(it->index());
    values.insert(it->value());
  }
  EXPECT_TRUE(indices.count(2));
  EXPECT_TRUE(indices.count(7));
  EXPECT_TRUE(values.count(20));
  EXPECT_TRUE(values.count(70));
}

// === max_size Tests ===

TEST_F(SparseArrayTest_72, MaxSizeReturnsCorrectValue_72) {
  SparseArray<int> arr(42);
  EXPECT_EQ(arr.max_size(), 42);
}

// === less static function test ===

TEST_F(SparseArrayTest_72, LessComparesIndices_72) {
  SparseArray<int> arr(10);
  arr.set(2, 200);
  arr.set(5, 50);

  // The less function compares by index
  // We can sort the range and verify ordering
  std::vector<SparseArray<int>::IndexValue> vec(arr.begin(), arr.end());
  std::sort(vec.begin(), vec.end(), SparseArray<int>::less);

  EXPECT_EQ(vec[0].index(), 2);
  EXPECT_EQ(vec[1].index(), 5);
}

// === Boundary Tests ===

TEST_F(SparseArrayTest_72, SetAtMaxIndexBoundary_72) {
  SparseArray<int> arr(10);
  arr.set(9, 90);
  EXPECT_TRUE(arr.has_index(9));
  EXPECT_EQ(arr.get_existing(9), 90);
}

TEST_F(SparseArrayTest_72, SetAtIndexZero_72) {
  SparseArray<int> arr(10);
  arr.set(0, 0);
  EXPECT_TRUE(arr.has_index(0));
  EXPECT_EQ(arr.get_existing(0), 0);
}

TEST_F(SparseArrayTest_72, FillAllIndices_72) {
  const int max = 10;
  SparseArray<int> arr(max);
  for (int i = 0; i < max; i++) {
    arr.set(i, i * 10);
  }
  EXPECT_EQ(arr.size(), max);
  for (int i = 0; i < max; i++) {
    EXPECT_TRUE(arr.has_index(i));
    EXPECT_EQ(arr.get_existing(i), i * 10);
  }
}

// === Value type tests with different types ===

TEST_F(SparseArrayTest_72, WorksWithStringValues_72) {
  SparseArray<std::string> arr(10);
  arr.set(3, "hello");
  arr.set(7, "world");

  EXPECT_EQ(arr.size(), 2);
  EXPECT_EQ(arr.get_existing(3), "hello");
  EXPECT_EQ(arr.get_existing(7), "world");
}

TEST_F(SparseArrayTest_72, WorksWithDoubleValues_72) {
  SparseArray<double> arr(10);
  arr.set(0, 3.14);
  arr.set(9, 2.71);

  EXPECT_DOUBLE_EQ(arr.get_existing(0), 3.14);
  EXPECT_DOUBLE_EQ(arr.get_existing(9), 2.71);
}

// === Set returns iterator Tests ===

TEST_F(SparseArrayTest_72, SetReturnsValidIterator_72) {
  SparseArray<int> arr(10);
  auto it = arr.set(5, 50);
  EXPECT_EQ(it->index(), 5);
  EXPECT_EQ(it->value(), 50);
}

TEST_F(SparseArrayTest_72, SetNewReturnsValidIterator_72) {
  SparseArray<int> arr(10);
  auto it = arr.set_new(3, 30);
  EXPECT_EQ(it->index(), 3);
  EXPECT_EQ(it->value(), 30);
}

TEST_F(SparseArrayTest_72, SetExistingReturnsValidIterator_72) {
  SparseArray<int> arr(10);
  arr.set(3, 30);
  auto it = arr.set_existing(3, 300);
  EXPECT_EQ(it->index(), 3);
  EXPECT_EQ(it->value(), 300);
}

// === Stress-like test ===

TEST_F(SparseArrayTest_72, LargeArrayOperations_72) {
  const int max_sz = 10000;
  SparseArray<int> arr(max_sz);

  // Set every other index
  for (int i = 0; i < max_sz; i += 2) {
    arr.set(i, i);
  }
  EXPECT_EQ(arr.size(), max_sz / 2);

  // Verify
  for (int i = 0; i < max_sz; i++) {
    if (i % 2 == 0) {
      EXPECT_TRUE(arr.has_index(i));
      EXPECT_EQ(arr.get_existing(i), i);
    } else {
      EXPECT_FALSE(arr.has_index(i));
    }
  }

  arr.clear();
  EXPECT_EQ(arr.size(), 0);
  EXPECT_TRUE(arr.empty());
}

// === Copy independence test ===

TEST_F(SparseArrayTest_72, CopyIsIndependent_72) {
  SparseArray<int> arr(10);
  arr.set(3, 30);

  SparseArray<int> copy(arr);
  copy.set(3, 300);

  // Original should be unchanged
  EXPECT_EQ(arr.get_existing(3), 30);
  EXPECT_EQ(copy.get_existing(3), 300);
}

TEST_F(SparseArrayTest_72, CopyAssignmentIsIndependent_72) {
  SparseArray<int> arr(10);
  arr.set(3, 30);

  SparseArray<int> other(10);
  other = arr;
  other.set(3, 300);

  EXPECT_EQ(arr.get_existing(3), 30);
  EXPECT_EQ(other.get_existing(3), 300);
}

}  // namespace re2
