#include "gtest/gtest.h"
#include "re2/sparse_array.h"

namespace re2 {

// Test fixture for SparseArray tests
class SparseArrayTest_73 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(SparseArrayTest_73, DefaultConstructor_73) {
  SparseArray<int> sa;
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_73, ConstructorWithMaxSize_73) {
  SparseArray<int> sa(100);
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
  EXPECT_EQ(sa.max_size(), 100);
}

TEST_F(SparseArrayTest_73, CopyConstructor_73) {
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

TEST_F(SparseArrayTest_73, MoveConstructor_73) {
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

// ==================== Assignment Tests ====================

TEST_F(SparseArrayTest_73, CopyAssignment_73) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(5, 50);

  SparseArray<int> other(10);
  other = sa;
  EXPECT_EQ(other.size(), 2);
  EXPECT_TRUE(other.has_index(2));
  EXPECT_TRUE(other.has_index(5));
  EXPECT_EQ(other.get_existing(2), 20);
  EXPECT_EQ(other.get_existing(5), 50);
}

TEST_F(SparseArrayTest_73, MoveAssignment_73) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(5, 50);

  SparseArray<int> other(10);
  other = std::move(sa);
  EXPECT_EQ(other.size(), 2);
  EXPECT_TRUE(other.has_index(2));
  EXPECT_TRUE(other.has_index(5));
  EXPECT_EQ(other.get_existing(2), 20);
  EXPECT_EQ(other.get_existing(5), 50);
}

// ==================== Set / Get Tests ====================

TEST_F(SparseArrayTest_73, SetAndGetExisting_73) {
  SparseArray<int> sa(10);
  sa.set(0, 100);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 100);
}

TEST_F(SparseArrayTest_73, SetMultipleValues_73) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(3, 30);
  sa.set(5, 50);
  EXPECT_EQ(sa.size(), 3);
  EXPECT_EQ(sa.get_existing(1), 10);
  EXPECT_EQ(sa.get_existing(3), 30);
  EXPECT_EQ(sa.get_existing(5), 50);
}

TEST_F(SparseArrayTest_73, SetOverwritesExistingValue_73) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  EXPECT_EQ(sa.get_existing(3), 30);
  sa.set(3, 300);
  EXPECT_EQ(sa.get_existing(3), 300);
  EXPECT_EQ(sa.size(), 1);
}

TEST_F(SparseArrayTest_73, SetNew_73) {
  SparseArray<int> sa(10);
  sa.set_new(4, 40);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(4));
  EXPECT_EQ(sa.get_existing(4), 40);
}

TEST_F(SparseArrayTest_73, SetExisting_73) {
  SparseArray<int> sa(10);
  sa.set(4, 40);
  sa.set_existing(4, 400);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_EQ(sa.get_existing(4), 400);
}

// ==================== has_index Tests ====================

TEST_F(SparseArrayTest_73, HasIndexReturnsFalseForUnset_73) {
  SparseArray<int> sa(10);
  EXPECT_FALSE(sa.has_index(0));
  EXPECT_FALSE(sa.has_index(5));
  EXPECT_FALSE(sa.has_index(9));
}

TEST_F(SparseArrayTest_73, HasIndexReturnsTrueForSet_73) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_FALSE(sa.has_index(4));
}

// ==================== Size / Empty Tests ====================

TEST_F(SparseArrayTest_73, SizeIncreasesOnSet_73) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.size(), 0);
  sa.set(1, 10);
  EXPECT_EQ(sa.size(), 1);
  sa.set(2, 20);
  EXPECT_EQ(sa.size(), 2);
}

TEST_F(SparseArrayTest_73, SizeDoesNotIncreaseOnOverwrite_73) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(1, 100);
  EXPECT_EQ(sa.size(), 1);
}

TEST_F(SparseArrayTest_73, EmptyReturnsTrueWhenEmpty_73) {
  SparseArray<int> sa(10);
  EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_73, EmptyReturnsFalseWhenNotEmpty_73) {
  SparseArray<int> sa(10);
  sa.set(0, 0);
  EXPECT_FALSE(sa.empty());
}

// ==================== Clear Tests ====================

TEST_F(SparseArrayTest_73, ClearMakesArrayEmpty_73) {
  SparseArray<int> sa(10);
  sa.set(1, 10);
  sa.set(3, 30);
  sa.set(5, 50);
  EXPECT_EQ(sa.size(), 3);

  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_73, ClearRemovesIndices_73) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.clear();
  EXPECT_FALSE(sa.has_index(3));
}

TEST_F(SparseArrayTest_73, ClearOnAlreadyEmptyArray_73) {
  SparseArray<int> sa(10);
  sa.clear();
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
}

// ==================== Resize Tests ====================

TEST_F(SparseArrayTest_73, ResizeToLarger_73) {
  SparseArray<int> sa(5);
  sa.set(2, 20);
  sa.resize(20);
  EXPECT_EQ(sa.max_size(), 20);
  // Existing data should be preserved after resize
  EXPECT_TRUE(sa.has_index(2));
  EXPECT_EQ(sa.get_existing(2), 20);
}

TEST_F(SparseArrayTest_73, ResizeToSmaller_73) {
  SparseArray<int> sa(20);
  sa.set(2, 20);
  sa.resize(5);
  EXPECT_EQ(sa.max_size(), 5);
  EXPECT_TRUE(sa.has_index(2));
  EXPECT_EQ(sa.get_existing(2), 20);
}

TEST_F(SparseArrayTest_73, ResizeAfterClear_73) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  sa.clear();
  sa.resize(20);
  EXPECT_EQ(sa.max_size(), 20);
  EXPECT_EQ(sa.size(), 0);
}

// ==================== Iterator Tests ====================

TEST_F(SparseArrayTest_73, BeginEqualsEndWhenEmpty_73) {
  SparseArray<int> sa(10);
  EXPECT_EQ(sa.begin(), sa.end());
}

TEST_F(SparseArrayTest_73, IteratorRangeMatchesSize_73) {
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

TEST_F(SparseArrayTest_73, IteratorAccessesCorrectValues_73) {
  SparseArray<int> sa(10);
  sa.set(2, 200);
  sa.set(7, 700);

  // Collect all index-value pairs
  std::map<int, int> collected;
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    collected[it->index()] = it->value();
  }

  EXPECT_EQ(collected.size(), 2u);
  EXPECT_EQ(collected[2], 200);
  EXPECT_EQ(collected[7], 700);
}

// ==================== max_size Tests ====================

TEST_F(SparseArrayTest_73, MaxSizeReturnsConstructorValue_73) {
  SparseArray<int> sa(42);
  EXPECT_EQ(sa.max_size(), 42);
}

// ==================== less static function Tests ====================

TEST_F(SparseArrayTest_73, LessComparison_73) {
  SparseArray<int> sa(10);
  sa.set(2, 20);
  sa.set(5, 50);

  auto it1 = sa.begin();
  auto it2 = sa.begin() + 1;

  // The `less` function compares by index
  if (it1->index() < it2->index()) {
    EXPECT_TRUE(SparseArray<int>::less(*it1, *it2));
    EXPECT_FALSE(SparseArray<int>::less(*it2, *it1));
  } else {
    EXPECT_TRUE(SparseArray<int>::less(*it2, *it1));
    EXPECT_FALSE(SparseArray<int>::less(*it1, *it2));
  }
}

// ==================== Set returns iterator Tests ====================

TEST_F(SparseArrayTest_73, SetReturnsIterator_73) {
  SparseArray<int> sa(10);
  auto it = sa.set(3, 30);
  EXPECT_EQ(it->index(), 3);
  EXPECT_EQ(it->value(), 30);
}

TEST_F(SparseArrayTest_73, SetNewReturnsIterator_73) {
  SparseArray<int> sa(10);
  auto it = sa.set_new(5, 50);
  EXPECT_EQ(it->index(), 5);
  EXPECT_EQ(it->value(), 50);
}

TEST_F(SparseArrayTest_73, SetExistingReturnsIterator_73) {
  SparseArray<int> sa(10);
  sa.set(5, 50);
  auto it = sa.set_existing(5, 500);
  EXPECT_EQ(it->index(), 5);
  EXPECT_EQ(it->value(), 500);
}

// ==================== Boundary Conditions ====================

TEST_F(SparseArrayTest_73, SetAtIndexZero_73) {
  SparseArray<int> sa(10);
  sa.set(0, 0);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 0);
}

TEST_F(SparseArrayTest_73, SetAtMaxIndex_73) {
  SparseArray<int> sa(10);
  sa.set(9, 90);
  EXPECT_TRUE(sa.has_index(9));
  EXPECT_EQ(sa.get_existing(9), 90);
}

TEST_F(SparseArrayTest_73, FillAllIndices_73) {
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

TEST_F(SparseArrayTest_73, ClearThenReuse_73) {
  SparseArray<int> sa(10);
  sa.set(3, 30);
  sa.set(7, 70);
  sa.clear();

  sa.set(1, 100);
  sa.set(9, 900);
  EXPECT_EQ(sa.size(), 2);
  EXPECT_TRUE(sa.has_index(1));
  EXPECT_TRUE(sa.has_index(9));
  EXPECT_FALSE(sa.has_index(3));
  EXPECT_FALSE(sa.has_index(7));
  EXPECT_EQ(sa.get_existing(1), 100);
  EXPECT_EQ(sa.get_existing(9), 900);
}

// ==================== Different Value Types ====================

TEST_F(SparseArrayTest_73, StringValueType_73) {
  SparseArray<std::string> sa(10);
  sa.set(3, "hello");
  sa.set(7, "world");
  EXPECT_EQ(sa.size(), 2);
  EXPECT_EQ(sa.get_existing(3), "hello");
  EXPECT_EQ(sa.get_existing(7), "world");
}

TEST_F(SparseArrayTest_73, DoubleValueType_73) {
  SparseArray<double> sa(10);
  sa.set(0, 3.14);
  sa.set(9, 2.718);
  EXPECT_EQ(sa.size(), 2);
  EXPECT_DOUBLE_EQ(sa.get_existing(0), 3.14);
  EXPECT_DOUBLE_EQ(sa.get_existing(9), 2.718);
}

// ==================== MaxSize 1 Edge Case ====================

TEST_F(SparseArrayTest_73, MaxSizeOne_73) {
  SparseArray<int> sa(1);
  EXPECT_EQ(sa.max_size(), 1);
  EXPECT_TRUE(sa.empty());

  sa.set(0, 42);
  EXPECT_EQ(sa.size(), 1);
  EXPECT_TRUE(sa.has_index(0));
  EXPECT_EQ(sa.get_existing(0), 42);

  sa.clear();
  EXPECT_TRUE(sa.empty());
  EXPECT_FALSE(sa.has_index(0));
}

// ==================== Copy Preserves Independence ====================

TEST_F(SparseArrayTest_73, CopyIsIndependent_73) {
  SparseArray<int> sa(10);
  sa.set(3, 30);

  SparseArray<int> copy(sa);
  copy.set(3, 300);

  EXPECT_EQ(sa.get_existing(3), 30);
  EXPECT_EQ(copy.get_existing(3), 300);
}

TEST_F(SparseArrayTest_73, CopyAssignmentIsIndependent_73) {
  SparseArray<int> sa(10);
  sa.set(3, 30);

  SparseArray<int> other(10);
  other = sa;
  other.set(3, 300);

  EXPECT_EQ(sa.get_existing(3), 30);
  EXPECT_EQ(other.get_existing(3), 300);
}

}  // namespace re2
