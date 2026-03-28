// File: patchlist_mk_test.cc
#include <gtest/gtest.h>
#include <cstdint>

// Include the production declaration so we don't re-implement anything.
// If there's a header for PatchList in your tree, include that instead.
// The prompt shows the declaration lives in compile.cc; assuming it's reachable.
#include "re2/compile.h"  // <-- If unavailable, include the appropriate header that declares re2::PatchList.

using re2::PatchList;

class PatchListTest_285 : public ::testing::Test {};

// Normal operation: Mk should set head and tail to the same provided value.
TEST_F(PatchListTest_285, MkSetsHeadAndTail_285) {
  const uint32_t p = 12345u;
  PatchList pl = PatchList::Mk(p);

  EXPECT_EQ(pl.head, p);
  EXPECT_EQ(pl.tail, p);
}

// Boundary: zero value should be accepted and reflected in both head and tail.
TEST_F(PatchListTest_285, MkZero_285) {
  const uint32_t p = 0u;
  PatchList pl = PatchList::Mk(p);

  EXPECT_EQ(pl.head, p);
  EXPECT_EQ(pl.tail, p);
}

// Boundary: maximum 32-bit value should be accepted and reflected.
TEST_F(PatchListTest_285, MkMaxUint32_285) {
  const uint32_t p = 0xFFFFFFFFu;
  PatchList pl = PatchList::Mk(p);

  EXPECT_EQ(pl.head, p);
  EXPECT_EQ(pl.tail, p);
}

// Sanity: multiple independent calls produce independent PatchLists with their own values.
TEST_F(PatchListTest_285, MkMultipleIndependent_285) {
  const uint32_t p1 = 1u;
  const uint32_t p2 = 42u;

  PatchList a = PatchList::Mk(p1);
  PatchList b = PatchList::Mk(p2);

  EXPECT_EQ(a.head, p1);
  EXPECT_EQ(a.tail, p1);
  EXPECT_EQ(b.head, p2);
  EXPECT_EQ(b.tail, p2);

  // Ensure no accidental aliasing/mutation coupling (observable via public fields).
  a.head = 7u;  // mutate a
  EXPECT_EQ(a.head, 7u);
  EXPECT_EQ(a.tail, p1);
  EXPECT_EQ(b.head, p2);
  EXPECT_EQ(b.tail, p2);
}
