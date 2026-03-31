#include "re2/sparse_array.h"
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

namespace re2 {
namespace {

// Test fixture for SparseArray tests
class SparseArrayTest_75 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor
TEST_F(SparseArrayTest_75, DefaultConstructor_75) {
  SparseArray<int> sa;
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

// Test constructor with max_size
TEST_F(SparseArrayTest_75, ConstructorWithMaxSize_75) {
  SparseArray<int> sa(100);
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
  EXPECT_EQ(sa.max_size(), 100);
}

// Test clear on empty array
TEST_F(SparseArrayTest_75, ClearEmpty_75) {
  SparseArray<int> sa(10);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

// Test clear after inserting elements
TEST_F(SparseArrayTest_75, ClearAfterInsert_75) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(5, 50);
  EXPECT_EQ(sa.size(), 2);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

// Test set and has_index
TEST_F(SparseArrayTest_75, SetAndHasIndex_75) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_FALSE(sa.has_index(4));
}

// Test set overwrites existing value
TEST_F(SparseArrayTest_75, SetOverwritesExisting_75) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(3, 99);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get_existing(3), 99);
}

// Test set_new for new index
TEST_F(SparseArrayTest_75, SetNew_75) {
  SparseArray<int> sa(10);
  sa.set_new(5, 50);
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_EQ(sa.size(), 1);
  EXPECT_EQ(sa.get_existing(5), 50);
}

// Test set_existing for existing index
TEST_F(SparseArrayTest_75, SetExisting_75) {
  SparseArray<int> sa(10);
  sa.set(7, 70);
  sa.set_existing(7, 77);
  EXPECT_EQ(sa.get_existing(7), 77);
  EXPECT_EQ(sa.size(), 1);
}

// Test get_existing returns correct value
TEST_F(SparseArrayTest_75, GetExisting_75) {
  SparseArray<int> sa(10);
  sa.set(2, 200);
  EXPECT_EQ(sa.get_existing(2), 200);
}

// Test size increases with new elements
TEST_F(SparseArrayTest_75, SizeIncreasesWithNewElements_75) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.size(), 0);
  sa.set(0, 10);
  EXPECT_EQ(sa.size(), 1);
  sa.set(1, 20);
  EXPECT_EQ(sa.size(), 2);
  sa.set(2, 30);
  EXPECT_EQ(sa.size(), 3);
}

// Test empty returns true when no elements
TEST_F(SparseArrayTest_75, EmptyWhenNoElements_75) {
  SparseArray<int> sa(10);
  EXPECT_TRUE(sa.empty());
}

// Test empty returns false when elements exist
TEST_F(SparseArrayTest_75, NotEmptyWhenElementsExist_75) {
  SparseArray<int> sa(10);
  sa.set(0, 1);
  EXPECT_FALSE(sa.empty());
}

// Test begin and end iterators on empty array
TEST_F(SparseArrayTest_75, BeginEndEmpty_75) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.begin(), sa.end());
}

// Test iteration over elements
TEST_F(SparseArrayTest_75, IterateOverElements_75) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(7, 70);
  sa.set(1, 10);
  
  int count = 0;
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 3);
}

// Test max_size
TEST_F(SparseArrayTest_75, MaxSize_75) {
  SparseArray<int> sa(42);
  EXPECT_EQ(sa.max_size(), 42);
}

// Test has_index returns false for indices not set
TEST_F(SparseArrayTest_75, HasIndexFalseForUnset_75) {
  SparseArray<int> sa(10);
  for (int i = 0; i < 10; i++) {
    EXPECT_FALSE(sa.has_index(i));
  }
}

// Test copy constructor
TEST_F(SparseArrayTest_75, CopyConstructor_75) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(5, 50);

  SparseArray<int> copy(sa);
  EXPECT_EQ(copy.size(), 2);
  EXPECT_TRUE(copy.has_index(3));
  EXPECT_TRUE(copy.has_index(5));
  EXPECT_EQ(copy.get_existing(3), 30);
  EXPECT_EQ(copy.get_existing(5), 50);
}

// Test move constructor
TEST_F(SparseArrayTest_75, MoveConstructor_75) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(5, 50);

  SparseArray<int> moved(std::move(sa));
  EXPECT_EQ(moved.size(), 2);
  EXPECT_TRUE(moved.has_index(3));
  EXPECT_TRUE(moved.has_index(5));
  EXPECT_EQ(moved.get_existing(3), 30);
  EXPECT_EQ(moved.get_existing(5), 50);
}

// Test copy assignment operator
TEST_F(SparseArrayTest_75, CopyAssignment_75) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(5, 50);

  SparseArray<int> other(20);
  other = sa;
  EXPECT_EQ(other.size(), 2);
  EXPECT_TRUE(other.has_index(3));
  EXPECT_TRUE(other.has_index(5));
  EXPECT_EQ(other.get_existing(3), 30);
  EXPECT_EQ(other.get_existing(5), 50);
}

// Test move assignment operator
TEST_F(SparseArrayTest_75, MoveAssignment_75) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(5, 50);

  SparseArray<int> other(20);
  other = std::move(sa);
  EXPECT_EQ(other.size(), 2);
  EXPECT_TRUE(other.has_index(3));
  EXPECT_TRUE(other.has_index(5));
  EXPECT_EQ(other.get_existing(3), 30);
  EXPECT_EQ(other.get_existing(5), 50);
}

// Test resize to larger size
TEST_F(SparseArrayTest_75, ResizeLarger_75) {
  SparseArray<int> sa(5);
  sa.set(2, 20);
  sa.set(4, 40);
  sa.resize(20);
  EXPECT_EQ(sa.max_size(), 20);
  // After resize, existing elements should be cleared
  // (based on typical SparseArray behavior - resize clears)
  // Actually, let's just check max_size changed
  EXPECT_GE(sa.max_size(), 20);
}

// Test resize to smaller size
TEST_F(SparseArrayTest_75, ResizeSmaller_75) {
  SparseArray<int> sa(20);
  sa.set(2, 20);
  sa.resize(5);
  EXPECT_EQ(sa.max_size(), 5);
}

// Test setting index 0 (boundary)
TEST_F(SparseArrayTest_75, SetIndexZero_75) {
  SparseArray<int> sa(10);
  sa.set(0, 100);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 100);
  EXPECT_EQ(sa.size(), 1);
}

// Test setting last valid index (boundary)
TEST_F(SparseArrayTest_75, SetLastValidIndex_75) {
  SparseArray<int> sa(10);
  sa.set(9, 90);
  EXPECT_TRUE(sa.has_index(9));
  EXPECT_EQ(sa.get_existing(9), 90);
}

// Test multiple sets and clears
TEST_F(SparseArrayTest_75, MultipleSetsAndClears_75) {
  SparseArray<int> sa(10);
  for (int i = 0; i < 10; i++) {
    sa.set(i, i * 10);
  }
  EXPECT_EQ(sa.size(), 10);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());

  // Re-add elements after clear
  sa.set(5, 500);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_EQ(sa.get_existing(5), 500);
}

// Test with string values
TEST_F(SparseArrayTest_75, StringValues_75) {
  SparseArray<std::string> sa(10);
  sa.set(3, "hello");
  sa.set(7, "world");
  EXPECT_EQ(sa.size(), 2);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_TRUE(sa.has_index(7));
  EXPECT_EQ(sa.get_existing(3), "hello");
  EXPECT_EQ(sa.get_existing(7), "world");
}

// Test less static method
TEST_F(SparseArrayTest_75, LessComparison_75) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(7, 70);
  
  // Use the iterator-based approach to verify less
  auto it1 = sa.begin();
  auto it2 = sa.begin() + 1;
  
  // less should compare based on index
  if (it1->index() < it2->index()) {
    EXPECT_TRUE(SparseArray<int>::less(*it1, *it2));
    EXPECT_FALSE(SparseArray<int>::less(*it2, *it1));
  } else {
    EXPECT_TRUE(SparseArray<int>::less(*it2, *it1));
    EXPECT_FALSE(SparseArray<int>::less(*it1, *it2));
  }
}

// Test that has_index returns false after clear
TEST_F(SparseArrayTest_75, HasIndexAfterClear_75) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  EXPECT_TRUE(sa.has_index(5));
  sa.clear();
  EXPECT_FALSE(sa.has_index(5));
}

// Test fill all indices
TEST_F(SparseArrayTest_75, FillAllIndices_75) {
  const int max_sz = 50;
  SparseArray<int> sa(max_sz);
  for (int i = 0; i < max_sz; i++) {
    sa.set(i, i * 2);
  }
  EXPECT_EQ(sa.size(), max_sz);
  for (int i = 0; i < max_sz; i++) {
    EXPECT_TRUE(sa.has_index(i));
    EXPECT_EQ(sa.get_existing(i), i * 2);
  }
}

// Test single element array
TEST_F(SparseArrayTest_75, SingleElementMaxSize_75) {
  SparseArray<int> sa(1);
  EXPECT_EQ(sa.max_size(), 1);
  sa.set(0, 42);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 42);
}

// Test set returns iterator
TEST_F(SparseArrayTest_75, SetReturnsIterator_75) {
  SparseArray<int> sa(10);
  auto it = sa.set(3, 30);
  EXPECT_EQ(it->index(), 3);
  EXPECT_EQ(it->value(), 30);
}

// Test set_new returns iterator
TEST_F(SparseArrayTest_75, SetNewReturnsIterator_75) {
  SparseArray<int> sa(10);
  auto it = sa.set_new(5, 50);
  EXPECT_EQ(it->index(), 5);
  EXPECT_EQ(it->value(), 50);
}

// Test set_existing returns iterator
TEST_F(SparseArrayTest_75, SetExistingReturnsIterator_75) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  auto it = sa.set_existing(5, 55);
  EXPECT_EQ(it->index(), 5);
  EXPECT_EQ(it->value(), 55);
}

// Test copy is independent (deep copy)
TEST_F(SparseArrayTest_75, CopyIsIndependent_75) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  
  SparseArray<int> copy(sa);
  copy.set(3, 99);
  
  // Original should be unchanged
  EXPECT_EQ(sa.get_existing(3), 30);
  EXPECT_EQ(copy.get_existing(3), 99);
}

// Test clear preserves max_size
TEST_F(SparseArrayTest_75, ClearPreservesMaxSize_75) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  sa.clear();
  EXPECT_EQ(sa.max_size(), 10);
}

// Test iterator distance matches size
TEST_F(SparseArrayTest_75, IteratorDistanceMatchesSize_75) {
  SparseArray<int> sa(20);
  sa.set(3, 30);
  sa.set(7, 70);
  sa.set(15, 150);
  
  int dist = static_cast<int>(sa.end() - sa.begin());
  EXPECT_EQ(dist, sa.size());
  EXPECT_EQ(dist, 3);
}

}  // namespace
}  // namespace re2
