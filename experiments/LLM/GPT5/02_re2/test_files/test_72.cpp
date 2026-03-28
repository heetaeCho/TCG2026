// File: sparse_array_begin_test_72.cc

#include <gtest/gtest.h>
#include <type_traits>
#include "re2/sparse_array.h"  // adjust include path if needed

namespace {

using ValueT = int;
using Arr = re2::SparseArray<ValueT>;

class SparseArrayTest_72 : public ::testing::Test {};

// [Behavior] On a freshly constructed (preallocated) array with no elements,
// begin() should equal end() (standard container semantics).
TEST_F(SparseArrayTest_72, BeginEqualsEndWhenEmpty_72) {
  Arr a(8);  // preallocate capacity so internal storage exists
  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());
  EXPECT_EQ(a.begin(), a.end());
}

// [Behavior] After inserting a single element, the iterator returned by set()
// should be the first valid element, which must coincide with begin()
// (since it is the only element).
TEST_F(SparseArrayTest_72, BeginPointsToSingleInserted_72) {
  Arr a(8);
  auto it = a.set(3, 42);
  ASSERT_NE(it, a.end());        // successfully inserted; iterator valid
  EXPECT_EQ(it, a.begin());      // with one element, it must be at begin()
  EXPECT_EQ(a.size(), 1);
  EXPECT_TRUE(a.has_index(3));
}

// [Behavior] With preallocated capacity, the underlying storage pointer for
// the dense segment should be stable across insertions; therefore begin()
// should not change just because we add more elements.
TEST_F(SparseArrayTest_72, BeginIsStableWithPreallocatedCapacity_72) {
  Arr a(10);
  auto begin_before = a.begin();     // dense_.data() before insertions
  EXPECT_EQ(begin_before, a.end());  // still empty

  auto it1 = a.set(1, 10);
  auto it2 = a.set(7, 20);
  (void)it1; (void)it2;              // not asserting order between them

  // After insertions, begin() should still reference the same underlying start.
  EXPECT_EQ(a.begin(), begin_before);
  EXPECT_NE(a.begin(), a.end());     // now non-empty
  EXPECT_EQ(a.size(), 2);
  EXPECT_TRUE(a.has_index(1));
  EXPECT_TRUE(a.has_index(7));
}

// [Behavior] After clearing all elements, container should be empty again and
// begin() should equal end().
TEST_F(SparseArrayTest_72, BeginEqualsEndAfterClear_72) {
  Arr a(8);
  a.set(2, 7);
  ASSERT_NE(a.begin(), a.end());  // sanity: became non-empty
  a.clear();
  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());
  EXPECT_EQ(a.begin(), a.end());
}

// [Interface] iterator type trait remains part of the public interface.
// We do not rely on internal details other than that iterator is a valid type.
TEST_F(SparseArrayTest_72, IteratorTypeIsPointerLike_72) {
  // The known interface typedefs iterator as a pointer type to an internal node.
  // Verifying pointer-ness is a compile-time assertion on the public alias.
  using Iter = decltype(std::declval<Arr&>().begin());
  static_assert(std::is_pointer<Iter>::value,
                "SparseArray::iterator should be a pointer type per interface");
  SUCCEED(); // keeps the test listed even though it's a compile-time check
}

}  // namespace
