// File: sparse_array_less_test_87.cc
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

// Adjust include path as needed for your project layout.
#include "re2/sparse_array.h"

namespace {

using re2::SparseArray;

class SparseArrayLessTest_87 : public ::testing::Test {
protected:
  using SA = SparseArray<int>;
  // Convenience: find the first IndexValue with matching index() via public iterators.
  static const typename SA::IndexValue* FindByIndex(const SA& sa, int idx) {
    for (auto it = sa.begin(); it != sa.end(); ++it) {
      if (it->index() == idx) return &*it;
    }
    return nullptr;
  }

  // Non-const overload for convenience in setup paths.
  static typename SA::IndexValue* FindByIndex(SA& sa, int idx) {
    for (auto it = sa.begin(); it != sa.end(); ++it) {
      if (it->index() == idx) return &*it;
    }
    return nullptr;
  }
};

// Normal behavior: less returns true iff a.index() < b.index().
TEST_F(SparseArrayLessTest_87, ReturnsTrueWhenFirstHasSmallerIndex_87) {
  SA sa(10);
  sa.set(1, 100);
  sa.set(5, 500);

  const auto* a = FindByIndex(sa, 1);
  const auto* b = FindByIndex(sa, 5);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  EXPECT_TRUE(SA::less(*a, *b));
  EXPECT_FALSE(SA::less(*b, *a));
}

// Boundary: comparing the same element should be false (not strictly less).
TEST_F(SparseArrayLessTest_87, ReturnsFalseWhenIndicesAreEqual_87) {
  SA sa(10);
  sa.set(3, 300);

  const auto* x = FindByIndex(sa, 3);
  ASSERT_NE(x, nullptr);

  EXPECT_FALSE(SA::less(*x, *x));
}

// Robustness: ordering depends only on index(), not on stored value.
TEST_F(SparseArrayLessTest_87, IgnoresValueOrdersByIndexOnly_87) {
  SA sa(10);
  // Intentionally store a larger value at a smaller index, and a smaller value at a larger index.
  sa.set(2, 1000);  // smaller index, larger value
  sa.set(7, 10);    // larger index, smaller value

  const auto* lowIdxHighVal = FindByIndex(sa, 2);
  const auto* highIdxLowVal = FindByIndex(sa, 7);
  ASSERT_NE(lowIdxHighVal, nullptr);
  ASSERT_NE(highIdxLowVal, nullptr);

  EXPECT_TRUE(SA::less(*lowIdxHighVal, *highIdxLowVal));
  EXPECT_FALSE(SA::less(*highIdxLowVal, *lowIdxHighVal));
}

// Integration-style: usable as a comparator for sorting by index.
TEST_F(SparseArrayLessTest_87, WorksAsComparatorForSortingByIndex_87) {
  SA sa(20);
  sa.set(7, 70);
  sa.set(2, 20);
  sa.set(15, 150);
  sa.set(9, 90);
  // Collect pointers to existing IndexValue entries using public iteration.
  std::vector<const SA::IndexValue*> items;
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    items.push_back(&*it);
  }

  // Sort by index via SparseArray::less
  std::sort(items.begin(), items.end(),
            [](const SA::IndexValue* lhs, const SA::IndexValue* rhs) {
              return SA::less(*lhs, *rhs);
            });

  // Verify ascending by index() only.
  ASSERT_GE(items.size(), 4u);
  EXPECT_LT(items[0]->index(), items[1]->index());
  EXPECT_LT(items[1]->index(), items[2]->index());
  EXPECT_LT(items[2]->index(), items[3]->index());
}

// Edge indices within capacity: smallest and largest valid indices compare correctly.
TEST_F(SparseArrayLessTest_87, HandlesMinAndMaxIndicesWithinCapacity_87) {
  const int kCap = 16;
  SA sa(kCap);
  sa.set(0, 1);
  sa.set(kCap - 1, 2);

  const auto* first = FindByIndex(sa, 0);
  const auto* last  = FindByIndex(sa, kCap - 1);
  ASSERT_NE(first, nullptr);
  ASSERT_NE(last, nullptr);

  EXPECT_TRUE(SA::less(*first, *last));
  EXPECT_FALSE(SA::less(*last, *first));
}

}  // namespace
