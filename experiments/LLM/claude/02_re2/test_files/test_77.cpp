#include "gtest/gtest.h"
#include "re2/sparse_array.h"

namespace re2 {

// Test fixture for SparseArray tests
class SparseArrayTest_77 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// --- Construction Tests ---

TEST_F(SparseArrayTest_77, DefaultConstructor_77) {
  SparseArray<int> sa;
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_77, ConstructorWithMaxSize_77) {
  SparseArray<int> sa(100);
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
  EXPECT_EQ(sa.max_size(), 100);
}

TEST_F(SparseArrayTest_77, CopyConstructor_77) {
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

TEST_F(SparseArrayTest_77, MoveConstructor_77) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  sa.set(9, 90);

  SparseArray<int> moved(std::move(sa));
  EXPECT_EQ(moved.size(), 2);
  EXPECT_TRUE(moved.has_index(5));
  EXPECT_TRUE(moved.has_index(9));
  EXPECT_EQ(moved.get_existing(5), 50);
  EXPECT_EQ(moved.get_existing(9), 90);
}

// --- Assignment Tests ---

TEST_F(SparseArrayTest_77, CopyAssignment_77) {
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

TEST_F(SparseArrayTest_77, MoveAssignment_77) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(6, 60);

  SparseArray<int> other(5);
  other = std::move(sa);
  EXPECT_EQ(other.size(), 2);
  EXPECT_TRUE(other.has_index(1));
  EXPECT_TRUE(other.has_index(6));
  EXPECT_EQ(other.get_existing(1), 10);
  EXPECT_EQ(other.get_existing(6), 60);
}

// --- set() Tests ---

TEST_F(SparseArrayTest_77, SetNewElement_77) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get_existing(3), 30);
}

TEST_F(SparseArrayTest_77, SetExistingElement_77) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(3, 300);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get_existing(3), 300);
}

TEST_F(SparseArrayTest_77, SetMultipleElements_77) {
  SparseArray<int> sa(10);
  sa.set(0, 0);
  sa.set(5, 50);
  sa.set(9, 90);
  EXPECT_EQ(sa.size(), 3);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_TRUE(sa.has_index(9));
}

// --- set_new() Tests ---

TEST_F(SparseArrayTest_77, SetNew_77) {
  SparseArray<int> sa(10);
  sa.set_new(4, 40);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(4));
  EXPECT_EQ(sa.get_existing(4), 40);
}

TEST_F(SparseArrayTest_77, SetNewMultipleDistinctIndices_77) {
  SparseArray<int> sa(10);
  sa.set_new(0, 100);
  sa.set_new(1, 200);
  sa.set_new(2, 300);
  EXPECT_EQ(sa.size(), 3);
  EXPECT_EQ(sa.get_existing(0), 100);
  EXPECT_EQ(sa.get_existing(1), 200);
  EXPECT_EQ(sa.get_existing(2), 300);
}

// --- set_existing() Tests ---

TEST_F(SparseArrayTest_77, SetExisting_77) {
  SparseArray<int> sa(10);
  sa.set(7, 70);
  sa.set_existing(7, 700);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_EQ(sa.get_existing(7), 700);
}

// --- get_existing() Tests ---

TEST_F(SparseArrayTest_77, GetExistingReturnsCorrectValue_77) {
  SparseArray<int> sa(10);
  sa.set(2, 42);
  EXPECT_EQ(sa.get_existing(2), 42);
}

TEST_F(SparseArrayTest_77, GetExistingReturnsMutableReference_77) {
  SparseArray<int> sa(10);
  sa.set(2, 42);
  sa.get_existing(2) = 99;
  EXPECT_EQ(sa.get_existing(2), 99);
}

// --- has_index() Tests ---

TEST_F(SparseArrayTest_77, HasIndexReturnsFalseForEmpty_77) {
  SparseArray<int> sa(10);
  EXPECT_FALSE(sa.has_index(0));
  EXPECT_FALSE(sa.has_index(5));
  EXPECT_FALSE(sa.has_index(9));
}

TEST_F(SparseArrayTest_77, HasIndexReturnsTrueAfterSet_77) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  EXPECT_TRUE(sa.has_index(3));
}

TEST_F(SparseArrayTest_77, HasIndexReturnsFalseAfterClear_77) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.clear();
  EXPECT_FALSE(sa.has_index(3));
}

// --- clear() Tests ---

TEST_F(SparseArrayTest_77, ClearEmptiesArray_77) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(2, 20);
  sa.set(3, 30);
  EXPECT_EQ(sa.size(), 3);

  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_77, ClearOnEmptyArray_77) {
  SparseArray<int> sa(10);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

// --- size() and empty() Tests ---

TEST_F(SparseArrayTest_77, SizeAfterInsertions_77) {
  SparseArray<int> sa(20);
  EXPECT_EQ(sa.size(), 0);
  sa.set(0, 0);
  EXPECT_EQ(sa.size(), 1);
  sa.set(10, 10);
  EXPECT_EQ(sa.size(), 2);
  sa.set(19, 19);
  EXPECT_EQ(sa.size(), 3);
}

TEST_F(SparseArrayTest_77, EmptyOnNewArray_77) {
  SparseArray<int> sa(10);
  EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_77, NotEmptyAfterSet_77) {
  SparseArray<int> sa(10);
  sa.set(0, 0);
  EXPECT_FALSE(sa.empty());
}

// --- max_size() Tests ---

TEST_F(SparseArrayTest_77, MaxSizeReturnsCorrectValue_77) {
  SparseArray<int> sa(50);
  EXPECT_EQ(sa.max_size(), 50);
}

// --- resize() Tests ---

TEST_F(SparseArrayTest_77, ResizeIncreasesMaxSize_77) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.resize(20);
  EXPECT_EQ(sa.max_size(), 20);
  // Existing elements should still be accessible
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get_existing(3), 30);
}

TEST_F(SparseArrayTest_77, ResizeDecreasesMaxSize_77) {
  SparseArray<int> sa(20);
  sa.set(3, 30);
  sa.set(15, 150);
  sa.resize(10);
  EXPECT_EQ(sa.max_size(), 10);
  // Element within range should still be there
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get_existing(3), 30);
}

// --- Iterator Tests ---

TEST_F(SparseArrayTest_77, BeginEqualsEndWhenEmpty_77) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.begin(), sa.end());
}

TEST_F(SparseArrayTest_77, IteratorCoversAllElements_77) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(5, 50);
  sa.set(8, 80);

  int count = 0;
  int sum_values = 0;
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    count++;
    sum_values += it->value();
  }
  EXPECT_EQ(count, 3);
  EXPECT_EQ(sum_values, 150);
}

TEST_F(SparseArrayTest_77, IteratorAfterClear_77) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(2, 20);
  sa.clear();
  EXPECT_EQ(sa.begin(), sa.end());
}

// --- less() Tests ---

TEST_F(SparseArrayTest_77, LessComparison_77) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(7, 70);

  // Get iterators to elements
  auto it1 = sa.begin();
  auto it2 = sa.begin() + 1;

  // less compares by index
  if (it1->index() < it2->index()) {
    EXPECT_TRUE(SparseArray<int>::less(*it1, *it2));
    EXPECT_FALSE(SparseArray<int>::less(*it2, *it1));
  } else {
    EXPECT_TRUE(SparseArray<int>::less(*it2, *it1));
    EXPECT_FALSE(SparseArray<int>::less(*it1, *it2));
  }
}

// --- Boundary Tests ---

TEST_F(SparseArrayTest_77, SetAtIndexZero_77) {
  SparseArray<int> sa(5);
  sa.set(0, 100);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 100);
}

TEST_F(SparseArrayTest_77, SetAtMaxIndex_77) {
  SparseArray<int> sa(5);
  sa.set(4, 400);
  EXPECT_TRUE(sa.has_index(4));
  EXPECT_EQ(sa.get_existing(4), 400);
}

TEST_F(SparseArrayTest_77, FillAllIndices_77) {
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

TEST_F(SparseArrayTest_77, ClearAndReuse_77) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(2, 20);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);

  sa.set(3, 30);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_FALSE(sa.has_index(1));
  EXPECT_FALSE(sa.has_index(2));
}

// --- String Value Type Tests ---

TEST_F(SparseArrayTest_77, StringValueType_77) {
  SparseArray<std::string> sa(10);
  sa.set(0, "hello");
  sa.set(5, "world");
  EXPECT_EQ(sa.size(), 2);
  EXPECT_EQ(sa.get_existing(0), "hello");
  EXPECT_EQ(sa.get_existing(5), "world");
}

// --- Large Array Test ---

TEST_F(SparseArrayTest_77, LargeSparseArray_77) {
  const int max_size = 10000;
  SparseArray<int> sa(max_size);

  // Set every 100th index
  for (int i = 0; i < max_size; i += 100) {
    sa.set(i, i);
  }

  EXPECT_EQ(sa.size(), 100);
  for (int i = 0; i < max_size; i += 100) {
    EXPECT_TRUE(sa.has_index(i));
    EXPECT_EQ(sa.get_existing(i), i);
  }
  // Check that some unset indices are not present
  EXPECT_FALSE(sa.has_index(1));
  EXPECT_FALSE(sa.has_index(50));
  EXPECT_FALSE(sa.has_index(99));
}

// --- Set returns iterator test ---

TEST_F(SparseArrayTest_77, SetReturnsValidIterator_77) {
  SparseArray<int> sa(10);
  auto it = sa.set(3, 30);
  EXPECT_EQ(it->index(), 3);
  EXPECT_EQ(it->value(), 30);
}

TEST_F(SparseArrayTest_77, SetNewReturnsValidIterator_77) {
  SparseArray<int> sa(10);
  auto it = sa.set_new(5, 50);
  EXPECT_EQ(it->index(), 5);
  EXPECT_EQ(it->value(), 50);
}

TEST_F(SparseArrayTest_77, SetExistingReturnsValidIterator_77) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  auto it = sa.set_existing(5, 500);
  EXPECT_EQ(it->index(), 5);
  EXPECT_EQ(it->value(), 500);
}

// --- Overwrite does not change size ---

TEST_F(SparseArrayTest_77, OverwriteDoesNotChangeSize_77) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(3, 300);
  sa.set(3, 3000);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_EQ(sa.get_existing(3), 3000);
}

// --- Resize to smaller removes out-of-range elements ---

TEST_F(SparseArrayTest_77, ResizeSmallerRemovesOutOfRange_77) {
  SparseArray<int> sa(10);
  sa.set(0, 0);
  sa.set(5, 50);
  sa.set(9, 90);
  
  sa.resize(6);
  EXPECT_EQ(sa.max_size(), 6);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_TRUE(sa.has_index(5));
  // Index 9 is out of new max_size range
}

// --- MaxSize of 1 ---

TEST_F(SparseArrayTest_77, MaxSizeOne_77) {
  SparseArray<int> sa(1);
  EXPECT_EQ(sa.max_size(), 1);
  EXPECT_EQ(sa.size(), 0);

  sa.set(0, 42);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 42);

  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_FALSE(sa.has_index(0));
}

}  // namespace re2
