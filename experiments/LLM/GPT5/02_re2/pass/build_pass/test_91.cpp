// File: sparse_set_clear_test_91.cc
#include <gtest/gtest.h>
#include "re2/sparse_set.h"

namespace re2 {

class SparseSetTTest_91 : public ::testing::Test {
protected:
  // Use a reasonable max size so we can test boundaries like max_size()-1.
  static constexpr int kMax = 16;

  // Helper to make a set with capacity kMax.
  template <typename T=int>
  SparseSetT<T> MakeSet() {
    return SparseSetT<T>(kMax);
  }

  // Inserts a few sample indices that are valid with respect to kMax.
  template <typename T=int>
  void InsertSample(SparseSetT<T>& s) {
    // Choose diverse positions: beginning, middle, end.
    s.insert(0);
    s.insert(3);
    s.insert(kMax - 1);
  }
};

// --- Tests ---

// 1) clear() on a fresh, empty set leaves it empty and size 0.
TEST_F(SparseSetTTest_91, ClearOnEmpty_91) {
  auto s = MakeSet<>();
  ASSERT_EQ(s.size(), 0);
  ASSERT_TRUE(s.empty());

  s.clear();

  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.begin(), s.end());  // no elements to iterate
}

// 2) clear() after inserts sets size to 0, empty() to true,
//    and iteration yields no elements anymore.
TEST_F(SparseSetTTest_91, ClearAfterInsert_91) {
  auto s = MakeSet<>();
  InsertSample(s);

  ASSERT_GT(s.size(), 0);
  ASSERT_FALSE(s.empty());

  s.clear();

  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.begin(), s.end());

  // Previously inserted elements should no longer be reported as present.
  EXPECT_FALSE(s.contains(0));
  EXPECT_FALSE(s.contains(3));
  EXPECT_FALSE(s.contains(kMax - 1));
}

// 3) clear() does not change capacity (max_size) and allows reuse (re-insert).
TEST_F(SparseSetTTest_91, ClearPreservesCapacityAndAllowsReuse_91) {
  auto s = MakeSet<>();
  const int before = s.max_size();

  InsertSample(s);
  s.clear();

  const int after = s.max_size();
  EXPECT_EQ(before, after) << "clear() should not change max_size()";

  // Reuse: can insert again and observe normal behavior.
  auto it = s.insert(5);
  // Using iterator equality to confirm insertion produced at least one element
  // (i.e., begin != end) without assuming iterator arithmetic.
  EXPECT_NE(s.begin(), s.end());
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(5));
  EXPECT_NE(it, s.end());
}

// 4) clear() is idempotent: calling it multiple times yields the same result.
TEST_F(SparseSetTTest_91, ClearIsIdempotent_91) {
  auto s = MakeSet<>();
  InsertSample(s);

  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());

  s.clear();  // second call should be a no-op in effect
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.begin(), s.end());
}

// 5) Boundary sanity: after clear(), contains() is false for any valid index range.
TEST_F(SparseSetTTest_91, ContainsFalseForAllAfterClear_91) {
  auto s = MakeSet<>();
  InsertSample(s);

  s.clear();

  // Probe a few boundary indices in range [0, max_size()).
  EXPECT_FALSE(s.contains(0));
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(kMax - 1));
}

}  // namespace re2
