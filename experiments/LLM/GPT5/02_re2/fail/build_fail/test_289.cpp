// File: compiler_allocinst_test_289.cc
#include <gtest/gtest.h>
#include <limits>

// Prefer the proper header if available in your build.
// If your project exposes a different internal header, include that instead.
#include "re2/compile.h"  // Assumes Compiler is declared here.

using re2::Compiler;

class CompilerAllocInstTest_289 : public ::testing::Test {
protected:
  Compiler c_;  // Default-constructible in the real codebase.
};

// [Normal] First allocation returns 0 for a single instruction.
TEST_F(CompilerAllocInstTest_289, FirstSingleAllocStartsAtZero_289) {
  int id = c_.AllocInst(1);
  EXPECT_GE(id, 0);           // Must be non-negative on success.
  // For a fresh compiler, the first allocated id should be 0.
  EXPECT_EQ(id, 0);
}

// [Normal] Sequential allocations return cumulative starting offsets.
TEST_F(CompilerAllocInstTest_289, SequentialAllocationsReturnRunningOffset_289) {
  int id0 = c_.AllocInst(3);   // [0,1,2]
  ASSERT_GE(id0, 0);
  int id1 = c_.AllocInst(2);   // [3,4]
  ASSERT_GE(id1, 0);
  int id2 = c_.AllocInst(5);   // [5,6,7,8,9]
  ASSERT_GE(id2, 0);

  EXPECT_EQ(id0, 0);
  EXPECT_EQ(id1, id0 + 3);
  EXPECT_EQ(id2, id1 + 2);
}

// [Boundary] Zero-sized allocation should not advance the offset.
TEST_F(CompilerAllocInstTest_289, ZeroSizedAllocationDoesNotAdvance_289) {
  // Fresh compiler: current offset is 0.
  int id0 = c_.AllocInst(0);
  ASSERT_GE(id0, 0);
  EXPECT_EQ(id0, 0);

  // Next real allocation should still start at 0.
  int id1 = c_.AllocInst(1);
  ASSERT_GE(id1, 0);
  EXPECT_EQ(id1, 0);

  // Another zero-sized alloc now should return current offset (which is 1).
  int id2 = c_.AllocInst(0);
  ASSERT_GE(id2, 0);
  EXPECT_EQ(id2, 1);

  // And a subsequent allocation should start at 1.
  int id3 = c_.AllocInst(2);
  ASSERT_GE(id3, 0);
  EXPECT_EQ(id3, 1);
}

// [Normal + Growth] Many small allocations should produce monotonically increasing start ids.
TEST_F(CompilerAllocInstTest_289, ManySmallAllocationsIncreaseMonotonically_289) {
  // Allocate repeatedly to (likely) trigger internal growth without depending on private state.
  const int kRounds = 1024;
  for (int i = 0; i < kRounds; ++i) {
    int id = c_.AllocInst(1);
    // Each successful id should match the running offset i starting from 0.
    // If the implementation enforces a global cap and fails earlier, the assertion will reveal it.
    ASSERT_GE(id, 0) << "Allocation failed unexpectedly at i=" << i;
    EXPECT_EQ(id, i);
  }
}
