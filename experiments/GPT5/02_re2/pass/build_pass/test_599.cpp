// File: compiler_constructor_allocinst_test_599.cc
#include <gtest/gtest.h>

// The production headers should expose re2::Compiler.
// If there isn't a dedicated header, include the umbrella header used in your build.
#include "re2/compile.cc"  // or the proper header that declares re2::Compiler

namespace {

using re2::Compiler;

// -----------------------------
// Construction basics
// -----------------------------

// Verifies that the Compiler can be constructed without throwing/crashing.
// (Covers the side-effects in the constructor, but only checks the observable outcome.)
TEST(CompilerConstructorTest_599, DefaultConstructible_599) {
  // Construction should not throw or crash.
  Compiler c;
  (void)c;  // silence unused variable warning
}

// -----------------------------
// AllocInst behavior (black-box)
// -----------------------------

// Sanity: allocating a single instruction returns a non-negative index.
TEST(CompilerAllocInstTest_599, SingleAllocationReturnsNonNegative_599) {
  Compiler c;
  int idx = c.AllocInst(1);
  EXPECT_GE(idx, 0);
}

// Two separate allocations of size 1 should (in normal operation) yield distinct blocks.
// We don't assume ordering—only that they are distinct indices.
TEST(CompilerAllocInstTest_599, MultipleSingleAllocationsYieldDistinctIndices_599) {
  Compiler c;
  int idx1 = c.AllocInst(1);
  int idx2 = c.AllocInst(1);
  // Observable expectation: different returned indices indicate separate allocations.
  EXPECT_NE(idx1, idx2);
}

// Boundary: requesting zero-length allocation should not crash. We place a minimal
// expectation on the return value being non-negative (observable, black-box safe).
TEST(CompilerAllocInstTest_599, ZeroLengthAllocationDoesNotCrash_599) {
  Compiler c;
  int idx = c.AllocInst(0);
  EXPECT_GE(idx, 0);
  // Follow with a normal allocation to ensure allocator still functions.
  int next = c.AllocInst(1);
  EXPECT_GE(next, 0);
}

// Stress-ish: a larger allocation should succeed and not interfere with subsequent allocations.
TEST(CompilerAllocInstTest_599, LargeThenSmallAllocation_SucceedsAndDistinct_599) {
  Compiler c;
  // Choose a moderate size to avoid excessive memory usage in CI while still exercising growth.
  const int kLarge = 1024;
  int big = c.AllocInst(kLarge);
  int small = c.AllocInst(1);
  EXPECT_GE(big, 0);
  EXPECT_GE(small, 0);
  EXPECT_NE(big, small);
}

// Repeated mixed-size allocations should all return non-negative indices and be pairwise distinct.
// This verifies allocator stability under varied request sizes without assuming internal layout.
TEST(CompilerAllocInstTest_599, MixedAllocationsAreDistinctAndNonNegative_599) {
  Compiler c;
  int a = c.AllocInst(1);
  int b = c.AllocInst(2);
  int d = c.AllocInst(4);
  int e = c.AllocInst(1);
  EXPECT_GE(a, 0);
  EXPECT_GE(b, 0);
  EXPECT_GE(d, 0);
  EXPECT_GE(e, 0);

  // Distinctness checks (minimal but meaningful observable behavior)
  EXPECT_NE(a, b);
  EXPECT_NE(a, d);
  EXPECT_NE(a, e);
  EXPECT_NE(b, d);
  EXPECT_NE(b, e);
  EXPECT_NE(d, e);
}

}  // namespace
