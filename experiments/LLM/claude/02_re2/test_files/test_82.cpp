#include "gtest/gtest.h"
#include "re2/sparse_array.h"

namespace re2 {

// Test basic construction and initial state
TEST(SparseArrayTest_82, DefaultConstructEmpty_82) {
  SparseArray<int> sa;
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

TEST(SparseArrayTest_82, ConstructWithMaxSize_82) {
  SparseArray<int> sa(100);
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

TEST(SparseArrayTest_82, SetAndGet_82) {
  SparseArray<int> sa(10);
  sa.set(3, 42);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get(3, -1), 42);
}

TEST(SparseArrayTest_82, GetDefaultWhenNotSet_82) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.get(3, -1), -1);
}

TEST(SparseArrayTest_82, HasIndexReturnsFalseWhenNotSet_82) {
  SparseArray<int> sa(10);
  EXPECT_FALSE(sa.has_index(0));
  EXPECT_FALSE(sa.has_index(5));
  EXPECT_FALSE(sa.has_index(9));
}

TEST(SparseArrayTest_82, HasIndexReturnsTrueWhenSet_82) {
  SparseArray<int> sa(10);
  sa.set(5, 100);
  EXPECT_TRUE(sa.has_index(5));
}

TEST(SparseArrayTest_82, SetMultipleValues_82) {
  SparseArray<int> sa(10);
  sa.set(0, 10);
  sa.set(5, 50);
  sa.set(9, 90);
  EXPECT_EQ(sa.size(), 3);
  EXPECT_EQ(sa.get(0, -1), 10);
  EXPECT_EQ(sa.get(5, -1), 50);
  EXPECT_EQ(sa.get(9, -1), 90);
}

TEST(SparseArrayTest_82, SetOverwritesExistingValue_82) {
  SparseArray<int> sa(10);
  sa.set(3, 42);
  EXPECT_EQ(sa.get(3, -1), 42);
  sa.set(3, 99);
  EXPECT_EQ(sa.get(3, -1), 99);
  EXPECT_EQ(sa.size(), 1);
}

TEST(SparseArrayTest_82, ClearRemovesAllEntries_82) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(3, 30);
  sa.set(7, 70);
  EXPECT_EQ(sa.size(), 3);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
  EXPECT_FALSE(sa.has_index(1));
  EXPECT_FALSE(sa.has_index(3));
  EXPECT_FALSE(sa.has_index(7));
}

TEST(SparseArrayTest_82, SizeReflectsNumberOfEntries_82) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.size(), 0);
  sa.set(0, 1);
  EXPECT_EQ(sa.size(), 1);
  sa.set(1, 2);
  EXPECT_EQ(sa.size(), 2);
  sa.set(0, 3);  // overwrite
  EXPECT_EQ(sa.size(), 2);
}

TEST(SparseArrayTest_82, IterationOverEntries_82) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(5, 50);
  sa.set(8, 80);

  int count = 0;
  int sum_indices = 0;
  int sum_values = 0;
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    sum_indices += it->index();
    sum_values += it->value();
    count++;
  }
  EXPECT_EQ(count, 3);
  EXPECT_EQ(sum_indices, 2 + 5 + 8);
  EXPECT_EQ(sum_values, 20 + 50 + 80);
}

TEST(SparseArrayTest_82, EmptyIteration_82) {
  SparseArray<int> sa(10);
  int count = 0;
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 0);
}

TEST(SparseArrayTest_82, IndexValueIndex_82) {
  SparseArray<int> sa(10);
  sa.set(7, 777);
  auto it = sa.begin();
  EXPECT_EQ(it->index(), 7);
  EXPECT_EQ(it->value(), 777);
}

TEST(SparseArrayTest_82, SetNewAddsEntry_82) {
  SparseArray<int> sa(10);
  sa.set_new(3, 42);
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get(3, -1), 42);
  EXPECT_EQ(sa.size(), 1);
}

TEST(SparseArrayTest_82, Erase_82) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(5, 50);
  sa.set(7, 70);
  EXPECT_EQ(sa.size(), 3);

  // Erase the first element
  sa.erase(3);
  EXPECT_FALSE(sa.has_index(3));
  EXPECT_EQ(sa.size(), 2);
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_TRUE(sa.has_index(7));
}

TEST(SparseArrayTest_82, BoundaryIndexZero_82) {
  SparseArray<int> sa(1);
  sa.set(0, 999);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get(0, -1), 999);
  EXPECT_EQ(sa.size(), 1);
}

TEST(SparseArrayTest_82, BoundaryMaxIndex_82) {
  SparseArray<int> sa(100);
  sa.set(99, 123);
  EXPECT_TRUE(sa.has_index(99));
  EXPECT_EQ(sa.get(99, -1), 123);
}

TEST(SparseArrayTest_82, ResizeIncreasesCapacity_82) {
  SparseArray<int> sa(5);
  sa.set(2, 20);
  sa.resize(10);
  // Existing entries should still be valid
  EXPECT_TRUE(sa.has_index(2));
  EXPECT_EQ(sa.get(2, -1), 20);
  // Can now set at higher indices
  sa.set(8, 80);
  EXPECT_TRUE(sa.has_index(8));
  EXPECT_EQ(sa.get(8, -1), 80);
}

TEST(SparseArrayTest_82, ClearThenReuse_82) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(2, 20);
  sa.clear();
  sa.set(1, 100);
  EXPECT_TRUE(sa.has_index(1));
  EXPECT_EQ(sa.get(1, -1), 100);
  EXPECT_FALSE(sa.has_index(2));
  EXPECT_EQ(sa.size(), 1);
}

TEST(SparseArrayTest_82, StringValueType_82) {
  SparseArray<std::string> sa(10);
  sa.set(3, "hello");
  sa.set(7, "world");
  EXPECT_EQ(sa.get(3, ""), "hello");
  EXPECT_EQ(sa.get(7, ""), "world");
  EXPECT_EQ(sa.get(0, "default"), "default");
}

TEST(SparseArrayTest_82, LargeArray_82) {
  const int N = 1000;
  SparseArray<int> sa(N);
  for (int i = 0; i < N; i += 2) {
    sa.set(i, i * 10);
  }
  EXPECT_EQ(sa.size(), N / 2);
  for (int i = 0; i < N; i += 2) {
    EXPECT_TRUE(sa.has_index(i));
    EXPECT_EQ(sa.get(i, -1), i * 10);
  }
  for (int i = 1; i < N; i += 2) {
    EXPECT_FALSE(sa.has_index(i));
  }
}

TEST(SparseArrayTest_82, SetNewMultiple_82) {
  SparseArray<int> sa(10);
  sa.set_new(0, 0);
  sa.set_new(1, 10);
  sa.set_new(2, 20);
  EXPECT_EQ(sa.size(), 3);
  EXPECT_EQ(sa.get(0, -1), 0);
  EXPECT_EQ(sa.get(1, -1), 10);
  EXPECT_EQ(sa.get(2, -1), 20);
}

TEST(SparseArrayTest_82, MutableValueAccess_82) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  // Access through iterator and modify
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    if (it->index() == 5) {
      it->value() = 500;
    }
  }
  EXPECT_EQ(sa.get(5, -1), 500);
}

}  // namespace re2
