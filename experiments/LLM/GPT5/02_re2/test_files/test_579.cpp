// File: ./TestProjects/re2/testing/prog_fanout_test.cc

#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/sparse_array.h"

using re2::Prog;
using re2::SparseArray;

namespace {

class ProgFanoutTest : public ::testing::Test {
 protected:
  // Helper to build a minimal program with at least `min_size` instructions.
  // We rely only on public APIs: inst(id) to access an instruction, and
  // set_start() to set the start state.
  static void EnsureInstExists(Prog* p, int id) {
    // Accessing inst(id) must be valid by interface; call it to ensure it's there.
    (void)p->inst(id);  // Do not infer internals; just request the slot.
  }
};

// -----------------------------------------------------------------------------
// Basic behavior: Fanout should initialize the fanout table with the start
// index and a starting count, and then accumulate counts for reachable
// ByteRange instructions.
// -----------------------------------------------------------------------------

TEST_F(ProgFanoutTest, CountsByteRangeFromStart_579) {
  Prog p;
  p.set_start(0);

  // Ensure at least instruction 0 exists and make it a ByteRange.
  Prog::Inst* i0 = p.inst(0);
  i0->InitByteRange('a', 'z', /*foldcase=*/0, /*out=*/0);  // self-loop

  // Fanout expects fanout->max_size() == p.size().
  SparseArray<int> fanout(p.size());
  p.Fanout(&fanout);

  // Start index should be present and its count should reflect one ByteRange.
  ASSERT_TRUE(fanout.has_index(0));
  EXPECT_EQ(fanout.get_existing(0), 1);
}

TEST_F(ProgFanoutTest, CountsMultipleReachableByteRanges_579) {
  Prog p;
  p.set_start(0);

  // Two consecutive ByteRange instructions reachable from the start.
  // 0: ByteRange -> 0 (self), and (since not last) 1 is reachable
  // 1: ByteRange -> 0
  EnsureInstExists(&p, 1);
  Prog::Inst* i0 = p.inst(0);
  Prog::Inst* i1 = p.inst(1);
  i0->InitByteRange('a', 'z', /*foldcase=*/0, /*out=*/0);
  i1->InitByteRange('A', 'Z', /*foldcase=*/0, /*out=*/0);

  SparseArray<int> fanout(p.size());
  p.Fanout(&fanout);

  ASSERT_TRUE(fanout.has_index(0));
  // Both 0 and 1 are ByteRange instructions reachable from the start
  // (via the per-entry reachability expansion). We only assert the
  // observable count on the start entry.
  EXPECT_EQ(fanout.get_existing(0), 2);
}

// -----------------------------------------------------------------------------
// Non-ByteRange reachable instructions should not increment the count.
// -----------------------------------------------------------------------------

TEST_F(ProgFanoutTest, NonByteRangeDoesNotIncreaseCount_579) {
  Prog p;
  p.set_start(0);

  // 0: Nop -> 0 (no ByteRange present)
  Prog::Inst* i0 = p.inst(0);
  i0->InitNop(/*out=*/0);

  SparseArray<int> fanout(p.size());
  p.Fanout(&fanout);

  ASSERT_TRUE(fanout.has_index(0));
  EXPECT_EQ(fanout.get_existing(0), 0);
}

// -----------------------------------------------------------------------------
// Fanout should clear the provided SparseArray and reinitialize the start entry.
// We verify by pre-populating a different value at the start index; after
// Fanout runs over a program that does NOT add ByteRange counts, the value
// should become 0.
// -----------------------------------------------------------------------------

TEST_F(ProgFanoutTest, ClearsAndInitializesFanoutStartEntry_579) {
  Prog p;
  p.set_start(0);

  // Program with no ByteRange from start so the count remains 0.
  Prog::Inst* i0 = p.inst(0);
  i0->InitNop(/*out=*/0);

  SparseArray<int> fanout(p.size());
  // Pre-populate the same start index with a non-zero value.
  fanout.set_new(0, 42);

  p.Fanout(&fanout);

  ASSERT_TRUE(fanout.has_index(0));
  EXPECT_EQ(fanout.get_existing(0), 0) << "Fanout should clear and reinit count";
}

// -----------------------------------------------------------------------------
// When a ByteRange is present but its out-target is already the start index,
// Fanout must still count it exactly once without relying on adding new
// fanout entries during iteration.
// -----------------------------------------------------------------------------

TEST_F(ProgFanoutTest, SelfLoopByteRangeCountsOnce_579) {
  Prog p;
  p.set_start(0);

  // 0: ByteRange -> 0 (self-loop)
  Prog::Inst* i0 = p.inst(0);
  i0->InitByteRange(0, 255, /*foldcase=*/0, /*out=*/0);

  SparseArray<int> fanout(p.size());
  p.Fanout(&fanout);

  ASSERT_TRUE(fanout.has_index(0));
  EXPECT_EQ(fanout.get_existing(0), 1);
}

}  // namespace
