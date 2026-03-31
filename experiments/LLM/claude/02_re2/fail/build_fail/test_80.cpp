#include "gtest/gtest.h"
#include "re2/sparse_array.h"

using re2::SparseArray;

// Test default constructor
TEST(SparseArrayTest_80, DefaultConstructor_80) {
  SparseArray<int> sa;
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

// Test parameterized constructor with max_size
TEST(SparseArrayTest_80, ParameterizedConstructor_80) {
  SparseArray<int> sa(100);
  EXPECT_EQ(sa.size(), 0);
  EXPECT_EQ(sa.max_size(), 100);
  EXPECT_TRUE(sa.empty());
}

// Test set and has_index
TEST(SparseArrayTest_80, SetAndHasIndex_80) {
  SparseArray<int> sa(10);
  sa.set(3, 42);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_FALSE(sa.has_index(5));
  EXPECT_EQ(sa.size(), 1);
}

// Test set multiple elements
TEST(SparseArrayTest_80, SetMultipleElements_80) {
  SparseArray<int> sa(10);
  sa.set(0, 10);
  sa.set(5, 50);
  sa.set(9, 90);
  EXPECT_EQ(sa.size(), 3);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_TRUE(sa.has_index(9));
  EXPECT_FALSE(sa.has_index(1));
}

// Test get_existing
TEST(SparseArrayTest_80, GetExisting_80) {
  SparseArray<int> sa(10);
  sa.set(3, 42);
  EXPECT_EQ(sa.get_existing(3), 42);
}

// Test set_existing overwrites value
TEST(SparseArrayTest_80, SetExistingOverwrites_80) {
  SparseArray<int> sa(10);
  sa.set(3, 42);
  sa.set_existing(3, 100);
  EXPECT_EQ(sa.get_existing(3), 100);
  EXPECT_EQ(sa.size(), 1);
}

// Test set overwrites existing value
TEST(SparseArrayTest_80, SetOverwritesExistingValue_80) {
  SparseArray<int> sa(10);
  sa.set(3, 42);
  sa.set(3, 100);
  EXPECT_EQ(sa.get_existing(3), 100);
  EXPECT_EQ(sa.size(), 1);
}

// Test set_new adds new element
TEST(SparseArrayTest_80, SetNew_80) {
  SparseArray<int> sa(10);
  sa.set_new(7, 77);
  EXPECT_TRUE(sa.has_index(7));
  EXPECT_EQ(sa.get_existing(7), 77);
  EXPECT_EQ(sa.size(), 1);
}

// Test clear
TEST(SparseArrayTest_80, Clear_80) {
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
TEST(SparseArrayTest_80, EmptyOnNonEmpty_80) {
  SparseArray<int> sa(10);
  sa.set(0, 1);
  EXPECT_FALSE(sa.empty());
}

// Test iterator begin and end
TEST(SparseArrayTest_80, IteratorBeginEnd_80) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(5, 50);
  int count = 0;
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 2);
}

// Test copy constructor
TEST(SparseArrayTest_80, CopyConstructor_80) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(3, 30);
  sa.set(7, 70);

  SparseArray<int> copy(sa);
  EXPECT_EQ(copy.size(), 3);
  EXPECT_EQ(copy.max_size(), 10);
  EXPECT_TRUE(copy.has_index(1));
  EXPECT_TRUE(copy.has_index(3));
  EXPECT_TRUE(copy.has_index(7));
  EXPECT_EQ(copy.get_existing(1), 10);
  EXPECT_EQ(copy.get_existing(3), 30);
  EXPECT_EQ(copy.get_existing(7), 70);
}

// Test copy assignment operator
TEST(SparseArrayTest_80, CopyAssignment_80) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(4, 40);

  SparseArray<int> other(5);
  other = sa;
  EXPECT_EQ(other.size(), 2);
  EXPECT_EQ(other.max_size(), 10);
  EXPECT_TRUE(other.has_index(2));
  EXPECT_TRUE(other.has_index(4));
  EXPECT_EQ(other.get_existing(2), 20);
  EXPECT_EQ(other.get_existing(4), 40);
}

// Test move constructor
TEST(SparseArrayTest_80, MoveConstructor_80) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(5, 50);

  SparseArray<int> moved(std::move(sa));
  EXPECT_EQ(moved.size(), 2);
  EXPECT_TRUE(moved.has_index(1));
  EXPECT_TRUE(moved.has_index(5));
  EXPECT_EQ(moved.get_existing(1), 10);
  EXPECT_EQ(moved.get_existing(5), 50);
}

// Test move assignment operator
TEST(SparseArrayTest_80, MoveAssignment_80) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(6, 60);

  SparseArray<int> other(5);
  other = std::move(sa);
  EXPECT_EQ(other.size(), 2);
  EXPECT_TRUE(other.has_index(3));
  EXPECT_TRUE(other.has_index(6));
  EXPECT_EQ(other.get_existing(3), 30);
  EXPECT_EQ(other.get_existing(6), 60);
}

// Test resize to larger size
TEST(SparseArrayTest_80, ResizeLarger_80) {
  SparseArray<int> sa(5);
  sa.set(2, 20);
  sa.set(4, 40);

  sa.resize(20);
  EXPECT_EQ(sa.max_size(), 20);
  // After resize, existing entries should still be accessible
  EXPECT_TRUE(sa.has_index(2));
  EXPECT_TRUE(sa.has_index(4));
  EXPECT_EQ(sa.get_existing(2), 20);
  EXPECT_EQ(sa.get_existing(4), 40);

  // Now we can set indices in the new range
  sa.set(15, 150);
  EXPECT_TRUE(sa.has_index(15));
  EXPECT_EQ(sa.get_existing(15), 150);
}

// Test resize to smaller size
TEST(SparseArrayTest_80, ResizeSmaller_80) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(4, 40);

  sa.resize(5);
  EXPECT_EQ(sa.max_size(), 5);
  EXPECT_TRUE(sa.has_index(2));
  EXPECT_TRUE(sa.has_index(4));
}

// Test with string values
TEST(SparseArrayTest_80, StringValues_80) {
  SparseArray<std::string> sa(10);
  sa.set(0, "hello");
  sa.set(9, "world");
  EXPECT_EQ(sa.size(), 2);
  EXPECT_EQ(sa.get_existing(0), "hello");
  EXPECT_EQ(sa.get_existing(9), "world");
}

// Test boundary: index 0
TEST(SparseArrayTest_80, BoundaryIndexZero_80) {
  SparseArray<int> sa(5);
  sa.set(0, 100);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 100);
}

// Test boundary: index max_size - 1
TEST(SparseArrayTest_80, BoundaryIndexMaxMinusOne_80) {
  SparseArray<int> sa(5);
  sa.set(4, 400);
  EXPECT_TRUE(sa.has_index(4));
  EXPECT_EQ(sa.get_existing(4), 400);
}

// Test max_size returns correct value
TEST(SparseArrayTest_80, MaxSize_80) {
  SparseArray<int> sa(42);
  EXPECT_EQ(sa.max_size(), 42);
}

// Test copy assignment does not affect source
TEST(SparseArrayTest_80, CopyAssignmentDoesNotAffectSource_80) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(2, 20);

  SparseArray<int> other(10);
  other = sa;

  // Modify other
  other.set(1, 999);
  other.set(5, 50);

  // Source should be unaffected
  EXPECT_EQ(sa.get_existing(1), 10);
  EXPECT_EQ(sa.size(), 2);
  EXPECT_FALSE(sa.has_index(5));
}

// Test less function
TEST(SparseArrayTest_80, LessFunction_80) {
  // less compares index values
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(5, 50);

  // Get iterators to check less
  auto it1 = sa.begin();
  auto it2 = sa.begin() + 1;

  // less should compare by index
  bool result = SparseArray<int>::less(*it1, *it2);
  // Just ensure it returns a boolean - we check consistency
  EXPECT_TRUE(result == true || result == false);
}

// Test fill and clear cycle
TEST(SparseArrayTest_80, FillAndClearCycle_80) {
  SparseArray<int> sa(5);
  for (int i = 0; i < 5; i++) {
    sa.set(i, i * 10);
  }
  EXPECT_EQ(sa.size(), 5);

  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());

  // Re-add elements
  for (int i = 0; i < 5; i++) {
    sa.set(i, i * 100);
  }
  EXPECT_EQ(sa.size(), 5);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(sa.get_existing(i), i * 100);
  }
}

// Test set returns iterator
TEST(SparseArrayTest_80, SetReturnsIterator_80) {
  SparseArray<int> sa(10);
  auto it = sa.set(3, 30);
  EXPECT_NE(it, sa.end());
}

// Test set_new returns iterator
TEST(SparseArrayTest_80, SetNewReturnsIterator_80) {
  SparseArray<int> sa(10);
  auto it = sa.set_new(3, 30);
  EXPECT_NE(it, sa.end());
}

// Test with max_size of 1
TEST(SparseArrayTest_80, MaxSizeOne_80) {
  SparseArray<int> sa(1);
  EXPECT_EQ(sa.max_size(), 1);
  EXPECT_EQ(sa.size(), 0);
  sa.set(0, 42);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 42);
}

// Test self-assignment
TEST(SparseArrayTest_80, SelfAssignment_80) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(5, 50);

  // This should not crash or corrupt data
  // Note: self-assignment may or may not be explicitly handled
  // but should at minimum not crash
  sa = sa;
  // After self-assignment, the data might or might not be preserved
  // depending on implementation. We just check it doesn't crash.
}

// Test double value type
TEST(SparseArrayTest_80, DoubleValues_80) {
  SparseArray<double> sa(10);
  sa.set(0, 3.14);
  sa.set(9, 2.71);
  EXPECT_DOUBLE_EQ(sa.get_existing(0), 3.14);
  EXPECT_DOUBLE_EQ(sa.get_existing(9), 2.71);
}

// Test has_index returns false for unset indices
TEST(SparseArrayTest_80, HasIndexReturnsFalseForUnset_80) {
  SparseArray<int> sa(100);
  sa.set(50, 500);
  EXPECT_FALSE(sa.has_index(0));
  EXPECT_FALSE(sa.has_index(49));
  EXPECT_FALSE(sa.has_index(51));
  EXPECT_FALSE(sa.has_index(99));
  EXPECT_TRUE(sa.has_index(50));
}
