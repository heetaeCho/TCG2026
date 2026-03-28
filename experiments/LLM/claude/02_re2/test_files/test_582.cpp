#include "gtest/gtest.h"
#include "re2/sparse_array.h"

using re2::SparseArray;

// Test default constructor
TEST(SparseArrayTest_582, DefaultConstructor_582) {
  SparseArray<int> sa;
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

// Test constructor with max_size
TEST(SparseArrayTest_582, ConstructorWithMaxSize_582) {
  SparseArray<int> sa(100);
  EXPECT_EQ(sa.size(), 0);
  EXPECT_EQ(sa.max_size(), 100);
  EXPECT_TRUE(sa.empty());
}

// Test set and size
TEST(SparseArrayTest_582, SetIncreasesSize_582) {
  SparseArray<int> sa(10);
  sa.set(3, 42);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_FALSE(sa.empty());
}

// Test has_index
TEST(SparseArrayTest_582, HasIndex_582) {
  SparseArray<int> sa(10);
  EXPECT_FALSE(sa.has_index(3));
  sa.set(3, 42);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_FALSE(sa.has_index(5));
}

// Test get_existing
TEST(SparseArrayTest_582, GetExisting_582) {
  SparseArray<int> sa(10);
  sa.set(3, 42);
  EXPECT_EQ(sa.get_existing(3), 42);
}

// Test set overwrites existing value
TEST(SparseArrayTest_582, SetOverwritesExistingValue_582) {
  SparseArray<int> sa(10);
  sa.set(3, 42);
  sa.set(3, 99);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_EQ(sa.get_existing(3), 99);
}

// Test set_new
TEST(SparseArrayTest_582, SetNew_582) {
  SparseArray<int> sa(10);
  sa.set_new(5, 100);
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_EQ(sa.get_existing(5), 100);
  EXPECT_EQ(sa.size(), 1);
}

// Test set_existing
TEST(SparseArrayTest_582, SetExisting_582) {
  SparseArray<int> sa(10);
  sa.set(5, 100);
  sa.set_existing(5, 200);
  EXPECT_EQ(sa.get_existing(5), 200);
  EXPECT_EQ(sa.size(), 1);
}

// Test clear
TEST(SparseArrayTest_582, Clear_582) {
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

// Test iterators
TEST(SparseArrayTest_582, Iterators_582) {
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

// Test copy constructor
TEST(SparseArrayTest_582, CopyConstructor_582) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(3, 30);
  sa.set(5, 50);

  SparseArray<int> copy(sa);
  EXPECT_EQ(copy.size(), 3);
  EXPECT_EQ(copy.max_size(), 10);
  EXPECT_TRUE(copy.has_index(1));
  EXPECT_TRUE(copy.has_index(3));
  EXPECT_TRUE(copy.has_index(5));
  EXPECT_EQ(copy.get_existing(1), 10);
  EXPECT_EQ(copy.get_existing(3), 30);
  EXPECT_EQ(copy.get_existing(5), 50);
}

// Test copy constructor independence
TEST(SparseArrayTest_582, CopyConstructorIndependence_582) {
  SparseArray<int> sa(10);
  sa.set(1, 10);

  SparseArray<int> copy(sa);
  copy.set(1, 999);
  EXPECT_EQ(sa.get_existing(1), 10);
  EXPECT_EQ(copy.get_existing(1), 999);
}

// Test move constructor
TEST(SparseArrayTest_582, MoveConstructor_582) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(3, 30);

  SparseArray<int> moved(std::move(sa));
  EXPECT_EQ(moved.size(), 2);
  EXPECT_TRUE(moved.has_index(1));
  EXPECT_TRUE(moved.has_index(3));
  EXPECT_EQ(moved.get_existing(1), 10);
  EXPECT_EQ(moved.get_existing(3), 30);
}

// Test copy assignment operator
TEST(SparseArrayTest_582, CopyAssignment_582) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(3, 30);

  SparseArray<int> other(5);
  other = sa;
  EXPECT_EQ(other.size(), 2);
  EXPECT_EQ(other.max_size(), 10);
  EXPECT_TRUE(other.has_index(1));
  EXPECT_TRUE(other.has_index(3));
  EXPECT_EQ(other.get_existing(1), 10);
  EXPECT_EQ(other.get_existing(3), 30);
}

// Test move assignment operator
TEST(SparseArrayTest_582, MoveAssignment_582) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(3, 30);

  SparseArray<int> other(5);
  other = std::move(sa);
  EXPECT_EQ(other.size(), 2);
  EXPECT_TRUE(other.has_index(1));
  EXPECT_TRUE(other.has_index(3));
  EXPECT_EQ(other.get_existing(1), 10);
  EXPECT_EQ(other.get_existing(3), 30);
}

// Test resize
TEST(SparseArrayTest_582, Resize_582) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(3, 30);

  sa.resize(20);
  EXPECT_EQ(sa.max_size(), 20);
  // After resize, previously set elements should still be accessible
  EXPECT_TRUE(sa.has_index(1));
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get_existing(1), 10);
  EXPECT_EQ(sa.get_existing(3), 30);
}

// Test resize to smaller
TEST(SparseArrayTest_582, ResizeSmaller_582) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(3, 30);

  sa.resize(5);
  EXPECT_EQ(sa.max_size(), 5);
}

// Test multiple sets and gets
TEST(SparseArrayTest_582, MultipleSetsAndGets_582) {
  SparseArray<int> sa(100);
  for (int i = 0; i < 100; i++) {
    sa.set(i, i * 10);
  }
  EXPECT_EQ(sa.size(), 100);
  for (int i = 0; i < 100; i++) {
    EXPECT_TRUE(sa.has_index(i));
    EXPECT_EQ(sa.get_existing(i), i * 10);
  }
}

// Test empty after construction
TEST(SparseArrayTest_582, EmptyAfterConstruction_582) {
  SparseArray<int> sa(50);
  EXPECT_TRUE(sa.empty());
  EXPECT_EQ(sa.begin(), sa.end());
}

// Test with string values
TEST(SparseArrayTest_582, StringValues_582) {
  SparseArray<std::string> sa(10);
  sa.set(0, "hello");
  sa.set(5, "world");
  EXPECT_EQ(sa.size(), 2);
  EXPECT_EQ(sa.get_existing(0), "hello");
  EXPECT_EQ(sa.get_existing(5), "world");
}

// Test boundary: index 0
TEST(SparseArrayTest_582, BoundaryIndexZero_582) {
  SparseArray<int> sa(10);
  sa.set(0, 42);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 42);
}

// Test boundary: max index
TEST(SparseArrayTest_582, BoundaryMaxIndex_582) {
  SparseArray<int> sa(10);
  sa.set(9, 99);
  EXPECT_TRUE(sa.has_index(9));
  EXPECT_EQ(sa.get_existing(9), 99);
}

// Test clear and reuse
TEST(SparseArrayTest_582, ClearAndReuse_582) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(2, 20);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_EQ(sa.max_size(), 10);

  sa.set(3, 30);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_FALSE(sa.has_index(1));
  EXPECT_FALSE(sa.has_index(2));
}

// Test less static function
TEST(SparseArrayTest_582, LessFunction_582) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  sa.set(2, 20);

  // The less function compares IndexValue by index
  // We can test it indirectly through the iterator
  auto it1 = sa.begin();
  auto it2 = sa.begin() + 1;
  // One of them should be "less" than the other
  bool result1 = SparseArray<int>::less(*it1, *it2);
  bool result2 = SparseArray<int>::less(*it2, *it1);
  // Exactly one should be true (they have different indices)
  EXPECT_NE(result1, result2);
}

// Test set returns iterator
TEST(SparseArrayTest_582, SetReturnsIterator_582) {
  SparseArray<int> sa(10);
  auto it = sa.set(3, 42);
  EXPECT_NE(it, sa.end());
}

// Test set_new returns iterator
TEST(SparseArrayTest_582, SetNewReturnsIterator_582) {
  SparseArray<int> sa(10);
  auto it = sa.set_new(3, 42);
  EXPECT_NE(it, sa.end());
}

// Test with max_size of 1
TEST(SparseArrayTest_582, MaxSizeOne_582) {
  SparseArray<int> sa(1);
  EXPECT_EQ(sa.max_size(), 1);
  sa.set(0, 100);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 100);
}

// Test copy of empty array
TEST(SparseArrayTest_582, CopyEmptyArray_582) {
  SparseArray<int> sa(10);
  SparseArray<int> copy(sa);
  EXPECT_EQ(copy.size(), 0);
  EXPECT_EQ(copy.max_size(), 10);
  EXPECT_TRUE(copy.empty());
}

// Test move of empty array
TEST(SparseArrayTest_582, MoveEmptyArray_582) {
  SparseArray<int> sa(10);
  SparseArray<int> moved(std::move(sa));
  EXPECT_EQ(moved.size(), 0);
  EXPECT_TRUE(moved.empty());
}

// Test double values
TEST(SparseArrayTest_582, DoubleValues_582) {
  SparseArray<double> sa(10);
  sa.set(0, 3.14);
  sa.set(5, 2.718);
  EXPECT_DOUBLE_EQ(sa.get_existing(0), 3.14);
  EXPECT_DOUBLE_EQ(sa.get_existing(5), 2.718);
}

// Test iterator count matches size
TEST(SparseArrayTest_582, IteratorCountMatchesSize_582) {
  SparseArray<int> sa(20);
  sa.set(1, 10);
  sa.set(5, 50);
  sa.set(15, 150);

  int count = 0;
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, sa.size());
  EXPECT_EQ(count, 3);
}

// Test has_index returns false for unset indices
TEST(SparseArrayTest_582, HasIndexFalseForUnsetIndices_582) {
  SparseArray<int> sa(10);
  for (int i = 0; i < 10; i++) {
    EXPECT_FALSE(sa.has_index(i));
  }
  sa.set(5, 50);
  for (int i = 0; i < 10; i++) {
    if (i == 5)
      EXPECT_TRUE(sa.has_index(i));
    else
      EXPECT_FALSE(sa.has_index(i));
  }
}
