// File: sparse_set_size_less_test_88.cc
#include <climits>
#include "gtest/gtest.h"
#include "./TestProjects/re2/re2/sparse_set.h"

namespace {

using namespace re2;

// A minimal fixture for naming consistency and potential future setup.
class SparseSetTest_88 : public ::testing::Test {};

// ---- Normal operation: size() should be callable on a default-constructed set
TEST_F(SparseSetTest_88, DefaultConstructedSizeIsNonNegative_88) {
  // Treat the implementation as a black box: just verify observable behavior.
  // We only rely on the public constructor and size() const.
  SparseSetT<int> s;  // using a concrete template argument as allowed by the interface
  EXPECT_GE(s.size(), 0);
}

// ---- Boundary condition: constructing with an explicit max size of 0
TEST_F(SparseSetTest_88, ExplicitZeroMaxSizeStillReportsNonNegativeSize_88) {
  // The interface shows an explicit ctor taking int max_size.
  // We don't infer internal logic; we only assert non-negative size is observable.
  SparseSetT<int> s0(0);
  EXPECT_GE(s0.size(), 0);
}

// ---- Normal operation: static comparator orders ascending
TEST_F(SparseSetTest_88, LessOrdersAscending_88) {
  // Verify comparator semantics via observable return values.
  EXPECT_TRUE (SparseSetT<int>::less(1, 2));
  EXPECT_FALSE(SparseSetT<int>::less(2, 1));
  EXPECT_FALSE(SparseSetT<int>::less(5, 5));  // equal elements: should not be "less"
}

// ---- Boundary conditions for comparator: extremes
TEST_F(SparseSetTest_88, LessWithIntegerExtremes_88) {
  EXPECT_TRUE (SparseSetT<int>::less(INT_MIN, INT_MAX));
  EXPECT_FALSE(SparseSetT<int>::less(INT_MAX, INT_MIN));
  EXPECT_FALSE(SparseSetT<int>::less(INT_MIN, INT_MIN));
  EXPECT_FALSE(SparseSetT<int>::less(INT_MAX, INT_MAX));
}

// ---- Sanity: size() const-ness (indirect check)
// We can't assert qualifiers directly, but we can ensure it’s callable on const objects.
TEST_F(SparseSetTest_88, SizeCallableOnConstObject_88) {
  const SparseSetT<int> s_const;  // const object
  // If size() is not const-qualified, this won't compile.
  const int reported = s_const.size();
  (void)reported;  // suppress unused warning
}

}  // namespace
