#include "gtest/gtest.h"
#include "re2/sparse_array.h"

namespace re2 {

// Test fixture for SparseArray tests
class SparseArrayTest_79 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor creates empty array
TEST_F(SparseArrayTest_79, DefaultConstructor_79) {
  SparseArray<int> sa;
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

// Test constructor with max_size
TEST_F(SparseArrayTest_79, ConstructorWithMaxSize_79) {
  SparseArray<int> sa(100);
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
  EXPECT_EQ(sa.max_size(), 100);
}

// Test set and has_index
TEST_F(SparseArrayTest_79, SetAndHasIndex_79) {
  SparseArray<int> sa(10);
  sa.set(5, 42);
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_FALSE(sa.has_index(3));
  EXPECT_EQ(sa.size(), 1);
}

// Test set multiple values
TEST_F(SparseArrayTest_79, SetMultipleValues_79) {
  SparseArray<int> sa(10);
  sa.set(0, 10);
  sa.set(3, 30);
  sa.set(7, 70);
  EXPECT_EQ(sa.size(), 3);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_TRUE(sa.has_index(7));
  EXPECT_FALSE(sa.has_index(1));
  EXPECT_FALSE(sa.has_index(9));
}

// Test get_existing returns correct value
TEST_F(SparseArrayTest_79, GetExistingReturnsCorrectValue_79) {
  SparseArray<int> sa(10);
  sa.set(5, 42);
  EXPECT_EQ(sa.get_existing(5), 42);
}

// Test set overwrites existing value
TEST_F(SparseArrayTest_79, SetOverwritesExistingValue_79) {
  SparseArray<int> sa(10);
  sa.set(5, 42);
  sa.set(5, 99);
  EXPECT_EQ(sa.get_existing(5), 99);
  EXPECT_EQ(sa.size(), 1);
}

// Test set_new for new index
TEST_F(SparseArrayTest_79, SetNewForNewIndex_79) {
  SparseArray<int> sa(10);
  sa.set_new(3, 33);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get_existing(3), 33);
  EXPECT_EQ(sa.size(), 1);
}

// Test set_existing for existing index
TEST_F(SparseArrayTest_79, SetExistingUpdatesValue_79) {
  SparseArray<int> sa(10);
  sa.set(4, 40);
  sa.set_existing(4, 400);
  EXPECT_EQ(sa.get_existing(4), 400);
  EXPECT_EQ(sa.size(), 1);
}

// Test clear empties the array
TEST_F(SparseArrayTest_79, ClearEmptiesArray_79) {
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

// Test empty on non-empty array
TEST_F(SparseArrayTest_79, EmptyReturnsFalseWhenNotEmpty_79) {
  SparseArray<int> sa(10);
  sa.set(0, 1);
  EXPECT_FALSE(sa.empty());
}

// Test begin and end iterators
TEST_F(SparseArrayTest_79, BeginEndIterators_79) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.begin(), sa.end());
  sa.set(2, 20);
  EXPECT_NE(sa.begin(), sa.end());
}

// Test iteration over elements
TEST_F(SparseArrayTest_79, IterationOverElements_79) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(5, 50);
  sa.set(8, 80);
  int count = 0;
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 3);
}

// Test copy constructor
TEST_F(SparseArrayTest_79, CopyConstructor_79) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(7, 70);
  SparseArray<int> copy(sa);
  EXPECT_EQ(copy.size(), 2);
  EXPECT_TRUE(copy.has_index(2));
  EXPECT_TRUE(copy.has_index(7));
  EXPECT_EQ(copy.get_existing(2), 20);
  EXPECT_EQ(copy.get_existing(7), 70);
}

// Test copy assignment
TEST_F(SparseArrayTest_79, CopyAssignment_79) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  SparseArray<int> other(5);
  other = sa;
  EXPECT_EQ(other.size(), 1);
  EXPECT_TRUE(other.has_index(3));
  EXPECT_EQ(other.get_existing(3), 30);
}

// Test move constructor
TEST_F(SparseArrayTest_79, MoveConstructor_79) {
  SparseArray<int> sa(10);
  sa.set(4, 40);
  sa.set(6, 60);
  SparseArray<int> moved(std::move(sa));
  EXPECT_EQ(moved.size(), 2);
  EXPECT_TRUE(moved.has_index(4));
  EXPECT_TRUE(moved.has_index(6));
  EXPECT_EQ(moved.get_existing(4), 40);
  EXPECT_EQ(moved.get_existing(6), 60);
}

// Test move assignment
TEST_F(SparseArrayTest_79, MoveAssignment_79) {
  SparseArray<int> sa(10);
  sa.set(1, 100);
  SparseArray<int> other(5);
  other = std::move(sa);
  EXPECT_EQ(other.size(), 1);
  EXPECT_TRUE(other.has_index(1));
  EXPECT_EQ(other.get_existing(1), 100);
}

// Test resize
TEST_F(SparseArrayTest_79, ResizeIncreasesMaxSize_79) {
  SparseArray<int> sa(5);
  sa.set(2, 20);
  sa.resize(20);
  EXPECT_EQ(sa.max_size(), 20);
  // Existing elements should still be there
  EXPECT_TRUE(sa.has_index(2));
  EXPECT_EQ(sa.get_existing(2), 20);
}

// Test resize allows setting indices in new range
TEST_F(SparseArrayTest_79, ResizeAllowsNewIndices_79) {
  SparseArray<int> sa(5);
  sa.resize(15);
  sa.set(10, 100);
  EXPECT_TRUE(sa.has_index(10));
  EXPECT_EQ(sa.get_existing(10), 100);
}

// Test max_size
TEST_F(SparseArrayTest_79, MaxSizeReturnsCorrectValue_79) {
  SparseArray<int> sa(42);
  EXPECT_EQ(sa.max_size(), 42);
}

// Test has_index returns false for out of range index
TEST_F(SparseArrayTest_79, HasIndexReturnsFalseForOutOfRange_79) {
  SparseArray<int> sa(5);
  EXPECT_FALSE(sa.has_index(5));
  EXPECT_FALSE(sa.has_index(10));
  EXPECT_FALSE(sa.has_index(-1));
}

// Test set at index 0 (boundary)
TEST_F(SparseArrayTest_79, SetAtIndexZero_79) {
  SparseArray<int> sa(10);
  sa.set(0, 999);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 999);
}

// Test set at max_size - 1 (boundary)
TEST_F(SparseArrayTest_79, SetAtMaxIndex_79) {
  SparseArray<int> sa(10);
  sa.set(9, 999);
  EXPECT_TRUE(sa.has_index(9));
  EXPECT_EQ(sa.get_existing(9), 999);
}

// Test with string values
TEST_F(SparseArrayTest_79, StringValues_79) {
  SparseArray<std::string> sa(10);
  sa.set(3, "hello");
  sa.set(7, "world");
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_TRUE(sa.has_index(7));
  EXPECT_EQ(sa.get_existing(3), "hello");
  EXPECT_EQ(sa.get_existing(7), "world");
}

// Test clear and reuse
TEST_F(SparseArrayTest_79, ClearAndReuse_79) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(2, 20);
  sa.clear();
  sa.set(1, 100);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(1));
  EXPECT_EQ(sa.get_existing(1), 100);
  EXPECT_FALSE(sa.has_index(2));
}

// Test less comparison
TEST_F(SparseArrayTest_79, LessComparison_79) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  sa.set(2, 20);
  // less should compare by index
  auto it1 = sa.begin();
  auto it2 = sa.begin() + 1;
  // We just verify the static function exists and can be called
  bool result1 = SparseArray<int>::less(*it1, *it2);
  bool result2 = SparseArray<int>::less(*it2, *it1);
  // One should be true and the other false (they can't be equal since different indices)
  EXPECT_NE(result1, result2);
}

// Test copy constructor independence
TEST_F(SparseArrayTest_79, CopyConstructorIndependence_79) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  SparseArray<int> copy(sa);
  sa.set(3, 300);
  // Copy should be independent
  EXPECT_EQ(copy.get_existing(3), 30);
  EXPECT_EQ(sa.get_existing(3), 300);
}

// Test filling all indices
TEST_F(SparseArrayTest_79, FillAllIndices_79) {
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

// Test size of 1
TEST_F(SparseArrayTest_79, SingleElementMaxSize_79) {
  SparseArray<int> sa(1);
  EXPECT_EQ(sa.max_size(), 1);
  sa.set(0, 42);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 42);
}

// Test get_existing returns a mutable reference
TEST_F(SparseArrayTest_79, GetExistingReturnsMutableReference_79) {
  SparseArray<int> sa(10);
  sa.set(5, 42);
  sa.get_existing(5) = 99;
  EXPECT_EQ(sa.get_existing(5), 99);
}

// Test set returns iterator
TEST_F(SparseArrayTest_79, SetReturnsIterator_79) {
  SparseArray<int> sa(10);
  auto it = sa.set(3, 30);
  EXPECT_NE(it, sa.end());
}

// Test set_new returns iterator
TEST_F(SparseArrayTest_79, SetNewReturnsIterator_79) {
  SparseArray<int> sa(10);
  auto it = sa.set_new(3, 30);
  EXPECT_NE(it, sa.end());
}

// Test set_existing returns iterator
TEST_F(SparseArrayTest_79, SetExistingReturnsIterator_79) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  auto it = sa.set_existing(3, 300);
  EXPECT_NE(it, sa.end());
}

// Test resize to smaller size clears elements beyond new size
TEST_F(SparseArrayTest_79, ResizeSmaller_79) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(8, 80);
  sa.resize(5);
  EXPECT_EQ(sa.max_size(), 5);
  // Index 2 should still be accessible if it was within new range
  // Index 8 should no longer be valid
  EXPECT_FALSE(sa.has_index(8));
}

// Test with double values
TEST_F(SparseArrayTest_79, DoubleValues_79) {
  SparseArray<double> sa(10);
  sa.set(0, 3.14);
  sa.set(9, 2.718);
  EXPECT_DOUBLE_EQ(sa.get_existing(0), 3.14);
  EXPECT_DOUBLE_EQ(sa.get_existing(9), 2.718);
}

// Test large sparse array
TEST_F(SparseArrayTest_79, LargeSparseArray_79) {
  const int max_size = 100000;
  SparseArray<int> sa(max_size);
  // Set only a few elements in a large array
  sa.set(0, 0);
  sa.set(50000, 50000);
  sa.set(99999, 99999);
  EXPECT_EQ(sa.size(), 3);
  EXPECT_EQ(sa.get_existing(0), 0);
  EXPECT_EQ(sa.get_existing(50000), 50000);
  EXPECT_EQ(sa.get_existing(99999), 99999);
  EXPECT_FALSE(sa.has_index(1));
  EXPECT_FALSE(sa.has_index(49999));
}

}  // namespace re2
