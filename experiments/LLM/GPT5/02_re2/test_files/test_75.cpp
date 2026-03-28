// File: sparse_array_clear_test_75.cc
#include <gtest/gtest.h>
#include "re2/sparse_array.h"

using re2::SparseArray;

class SparseArrayClearTest_75 : public ::testing::Test {
protected:
  // Use a simple value type for clarity.
  using SA = SparseArray<int>;
};

TEST_F(SparseArrayClearTest_75, ClearOnEmpty_NoChangeAndSafe_75) {
  SA sa(/*max_size*/16);
  // Pre-condition: newly constructed should be empty if the interface provides it
  // (we don't assert that here to avoid assuming behavior not stated).
  sa.clear();

  // Observable post-conditions we can rely on via the interface.
  // If size()/empty() exist per interface, they should reflect cleared state.
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());

  // begin() == end() is a common empty-range contract.
  EXPECT_EQ(sa.begin(), sa.end());
}

TEST_F(SparseArrayClearTest_75, ClearOnNonEmpty_ResetsSizeAndEmpties_75) {
  SA sa(32);

  // Make it non-empty using the public setter(s).
  // We don't assert anything about internal storage—only observable behavior.
  sa.set(3, 30);
  sa.set(7, 70);
  sa.set(12, 120);

  // Sanity: after inserts, size() should be > 0 (observable).
  ASSERT_GT(sa.size(), 0);
  ASSERT_FALSE(sa.empty());

  // Act
  sa.clear();

  // Assert: cleared state is observable via size/empty/iterators.
  EXPECT_EQ(sa.size(), 0);
  EXPECT_TRUE(sa.empty());
  EXPECT_EQ(sa.begin(), sa.end());
}

TEST_F(SparseArrayClearTest_75, ClearRemovesPreviouslySetIndices_75) {
  SA sa(16);
  sa.set(1, 10);
  sa.set(5, 50);

  ASSERT_TRUE(sa.has_index(1));
  ASSERT_TRUE(sa.has_index(5));

  sa.clear();

  // After clear, previously present indices should no longer be reported present.
  EXPECT_FALSE(sa.has_index(1));
  EXPECT_FALSE(sa.has_index(5));
}

TEST_F(SparseArrayClearTest_75, ClearIsIdempotent_75) {
  SA sa(8);
  sa.set(2, 20);
  ASSERT_FALSE(sa.empty());

  sa.clear();
  EXPECT_TRUE(sa.empty());
  EXPECT_EQ(sa.size(), 0);

  // Calling clear() again should keep it empty and safe.
  sa.clear();
  EXPECT_TRUE(sa.empty());
  EXPECT_EQ(sa.size(), 0);
  EXPECT_EQ(sa.begin(), sa.end());
}

TEST_F(SparseArrayClearTest_75, CanReuseAfterClear_75) {
  SA sa(16);
  sa.set(4, 40);
  sa.set(9, 90);
  ASSERT_GT(sa.size(), 0);

  sa.clear();
  ASSERT_TRUE(sa.empty());

  // After clearing, setting new values should still work via the public API.
  auto it = sa.set(2, 200);
  // We only check observable effects; we don't dereference iterator unless allowed.
  EXPECT_TRUE(sa.has_index(2));
  EXPECT_EQ(sa.size(), 1);
  EXPECT_FALSE(sa.empty());
  (void)it; // suppress unused warning in case iterator isn't inspected further
}

TEST_F(SparseArrayClearTest_75, BeginEndRemainValidAfterClear_75) {
  SA sa(10);
  sa.set(0, 1);
  sa.set(9, 2);
  ASSERT_NE(sa.begin(), sa.end());

  sa.clear();

  // After clear(), iterators should represent an empty range and be comparable.
  auto b = sa.begin();
  auto e = sa.end();
  EXPECT_EQ(b, e);
}
