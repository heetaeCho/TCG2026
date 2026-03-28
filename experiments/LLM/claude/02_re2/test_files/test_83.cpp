#include "gtest/gtest.h"
#include "re2/sparse_array.h"

#include <string>
#include <vector>
#include <algorithm>

namespace re2 {
namespace {

// Test basic construction and empty state
TEST(SparseArrayTest_83, DefaultConstructedIsEmpty_83) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.size(), 0);
}

TEST(SparseArrayTest_83, DefaultConstructedBeginEqualsEnd_83) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.begin(), sa.end());
}

// Test set and get operations
TEST(SparseArrayTest_83, SetAndGet_83) {
  SparseArray<int> sa(100);
  sa.set(5, 42);
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_EQ(sa.get(5, -1), 42);
}

TEST(SparseArrayTest_83, SetOverwritesExisting_83) {
  SparseArray<int> sa(100);
  sa.set(5, 42);
  sa.set(5, 99);
  EXPECT_EQ(sa.get(5, -1), 99);
  EXPECT_EQ(sa.size(), 1);
}

TEST(SparseArrayTest_83, GetDefaultWhenNotSet_83) {
  SparseArray<int> sa(100);
  EXPECT_EQ(sa.get(5, -1), -1);
}

TEST(SparseArrayTest_83, HasIndexReturnsFalseWhenNotSet_83) {
  SparseArray<int> sa(100);
  EXPECT_FALSE(sa.has_index(0));
  EXPECT_FALSE(sa.has_index(50));
  EXPECT_FALSE(sa.has_index(99));
}

TEST(SparseArrayTest_83, HasIndexReturnsTrueWhenSet_83) {
  SparseArray<int> sa(100);
  sa.set(50, 123);
  EXPECT_TRUE(sa.has_index(50));
}

// Test size tracking
TEST(SparseArrayTest_83, SizeIncreasesWithNewEntries_83) {
  SparseArray<int> sa(100);
  EXPECT_EQ(sa.size(), 0);
  sa.set(1, 10);
  EXPECT_EQ(sa.size(), 1);
  sa.set(2, 20);
  EXPECT_EQ(sa.size(), 2);
  sa.set(3, 30);
  EXPECT_EQ(sa.size(), 3);
}

TEST(SparseArrayTest_83, SizeDoesNotIncreaseOnOverwrite_83) {
  SparseArray<int> sa(100);
  sa.set(1, 10);
  sa.set(1, 20);
  EXPECT_EQ(sa.size(), 1);
}

// Test clear
TEST(SparseArrayTest_83, ClearResetsSize_83) {
  SparseArray<int> sa(100);
  sa.set(1, 10);
  sa.set(2, 20);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);
}

TEST(SparseArrayTest_83, ClearRemovesAllIndices_83) {
  SparseArray<int> sa(100);
  sa.set(1, 10);
  sa.set(2, 20);
  sa.clear();
  EXPECT_FALSE(sa.has_index(1));
  EXPECT_FALSE(sa.has_index(2));
}

// Test iteration
TEST(SparseArrayTest_83, IterationOverAllElements_83) {
  SparseArray<int> sa(100);
  sa.set(10, 100);
  sa.set(20, 200);
  sa.set(30, 300);

  std::vector<std::pair<int, int>> entries;
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    entries.push_back({it->index(), it->value()});
  }
  EXPECT_EQ(entries.size(), 3);
}

TEST(SparseArrayTest_83, IterationEmptyArray_83) {
  SparseArray<int> sa(100);
  int count = 0;
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 0);
}

// Test IndexValue access
TEST(SparseArrayTest_83, IndexValueIndex_83) {
  SparseArray<int> sa(100);
  sa.set(42, 999);
  auto it = sa.begin();
  EXPECT_EQ(it->index(), 42);
}

TEST(SparseArrayTest_83, IndexValueValue_83) {
  SparseArray<int> sa(100);
  sa.set(42, 999);
  auto it = sa.begin();
  EXPECT_EQ(it->value(), 999);
}

TEST(SparseArrayTest_83, IndexValueMutableValue_83) {
  SparseArray<int> sa(100);
  sa.set(42, 999);
  auto it = sa.begin();
  it->value() = 1234;
  EXPECT_EQ(sa.get(42, -1), 1234);
}

// Test set_new (if available through the interface)
TEST(SparseArrayTest_83, SetNewAddsEntry_83) {
  SparseArray<int> sa(100);
  sa.set_new(5, 42);
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_EQ(sa.get(5, -1), 42);
  EXPECT_EQ(sa.size(), 1);
}

// Test boundary indices
TEST(SparseArrayTest_83, SetAtIndexZero_83) {
  SparseArray<int> sa(10);
  sa.set(0, 100);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get(0, -1), 100);
}

TEST(SparseArrayTest_83, SetAtMaxIndex_83) {
  SparseArray<int> sa(10);
  sa.set(9, 100);
  EXPECT_TRUE(sa.has_index(9));
  EXPECT_EQ(sa.get(9, -1), 100);
}

// Test with different value types
TEST(SparseArrayTest_83, StringValues_83) {
  SparseArray<std::string> sa(50);
  sa.set(10, "hello");
  sa.set(20, "world");
  EXPECT_EQ(sa.get(10, ""), "hello");
  EXPECT_EQ(sa.get(20, ""), "world");
  EXPECT_EQ(sa.get(30, "default"), "default");
}

// Test with size 1
TEST(SparseArrayTest_83, SingleElementArray_83) {
  SparseArray<int> sa(1);
  EXPECT_EQ(sa.size(), 0);
  sa.set(0, 42);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get(0, -1), 42);
}

// Test multiple sets and clears
TEST(SparseArrayTest_83, MultipleSetClearCycles_83) {
  SparseArray<int> sa(100);
  for (int cycle = 0; cycle < 5; cycle++) {
    for (int i = 0; i < 10; i++) {
      sa.set(i, i * cycle);
    }
    EXPECT_EQ(sa.size(), 10);
    sa.clear();
    EXPECT_EQ(sa.size(), 0);
  }
}

// Test that after clear, we can re-add
TEST(SparseArrayTest_83, ReAddAfterClear_83) {
  SparseArray<int> sa(100);
  sa.set(5, 50);
  sa.clear();
  sa.set(5, 60);
  EXPECT_EQ(sa.get(5, -1), 60);
  EXPECT_EQ(sa.size(), 1);
}

// Test many elements
TEST(SparseArrayTest_83, ManyElements_83) {
  const int N = 1000;
  SparseArray<int> sa(N);
  for (int i = 0; i < N; i++) {
    sa.set(i, i * 2);
  }
  EXPECT_EQ(sa.size(), N);
  for (int i = 0; i < N; i++) {
    EXPECT_TRUE(sa.has_index(i));
    EXPECT_EQ(sa.get(i, -1), i * 2);
  }
}

// Test sparse usage (few elements in large array)
TEST(SparseArrayTest_83, SparseUsage_83) {
  SparseArray<int> sa(10000);
  sa.set(0, 1);
  sa.set(5000, 2);
  sa.set(9999, 3);
  EXPECT_EQ(sa.size(), 3);
  EXPECT_EQ(sa.get(0, -1), 1);
  EXPECT_EQ(sa.get(5000, -1), 2);
  EXPECT_EQ(sa.get(9999, -1), 3);
  EXPECT_FALSE(sa.has_index(1));
  EXPECT_FALSE(sa.has_index(4999));
}

// Test empty() if available
TEST(SparseArrayTest_83, EmptyCheck_83) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.size(), 0);
  sa.set(0, 1);
  EXPECT_NE(sa.size(), 0);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);
}

}  // namespace
}  // namespace re2
