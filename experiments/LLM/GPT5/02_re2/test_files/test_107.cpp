// File: prog_inst_hint_test_107.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

using re2::Prog;
using re2::InstOp;

class InstHintTest_107 : public ::testing::Test {
protected:
  // Helper: create a ByteRange Inst with given params.
  static Prog::Inst MakeByteRange(int lo, int hi, int foldcase, uint32_t out) {
    Prog::Inst inst;
    inst.InitByteRange(lo, hi, foldcase, out);
    return inst;
  }
};

// ----------------------------------------------------------------------------
// Normal operation: hint() is callable for ByteRange and returns a stable int.
// ----------------------------------------------------------------------------

TEST_F(InstHintTest_107, ByteRangeHintIsCallableAndStable_107) {
  auto inst = InstHintTest_107::MakeByteRange(/*lo=*/'a', /*hi=*/'z',
                                              /*foldcase=*/0, /*out=*/0);
  // Sanity: opcode is ByteRange per interface behavior of InitByteRange.
  EXPECT_EQ(inst.opcode(), re2::kInstByteRange);

  // Calling hint() should be well-defined and stable (idempotent).
  const int h1 = inst.hint();
  const int h2 = inst.hint();
  EXPECT_EQ(h1, h2);
}

// ----------------------------------------------------------------------------
// Interface-driven check from provided hint() code:
// hint() shifts out the foldcase bit, so changing foldcase should NOT change
// the observed hint value for the same lo/hi/out (observable via interface).
// ----------------------------------------------------------------------------

TEST_F(InstHintTest_107, FoldcaseDoesNotAffectHint_107) {
  auto a = InstHintTest_107::MakeByteRange('a', 'z', /*foldcase=*/0, /*out=*/0);
  auto b = InstHintTest_107::MakeByteRange('a', 'z', /*foldcase=*/1, /*out=*/0);

  ASSERT_EQ(a.opcode(), re2::kInstByteRange);
  ASSERT_EQ(b.opcode(), re2::kInstByteRange);

  EXPECT_EQ(a.hint(), b.hint());
}

// ----------------------------------------------------------------------------
// Boundary conditions: extremes of the byte range, and degenerate range lo==hi.
// We only assert behaviors observable via the interface:
// - hint() is callable
// - hint() is stable
// - hint() is independent of foldcase for the same lo/hi/out
// ----------------------------------------------------------------------------

TEST_F(InstHintTest_107, HintWithFullByteRangeExtremes_107) {
  auto r0 = InstHintTest_107::MakeByteRange(0, 255, /*foldcase=*/0, /*out=*/0);
  auto r1 = InstHintTest_107::MakeByteRange(0, 255, /*foldcase=*/1, /*out=*/0);

  ASSERT_EQ(r0.opcode(), re2::kInstByteRange);
  ASSERT_EQ(r1.opcode(), re2::kInstByteRange);

  // Stable per instance
  EXPECT_EQ(r0.hint(), r0.hint());
  EXPECT_EQ(r1.hint(), r1.hint());

  // Independent from foldcase for identical lo/hi/out
  EXPECT_EQ(r0.hint(), r1.hint());
}

TEST_F(InstHintTest_107, HintWithSingleValueRangeBoundary_107) {
  auto x0 = InstHintTest_107::MakeByteRange('A', 'A', /*foldcase=*/0, /*out=*/0);
  auto x1 = InstHintTest_107::MakeByteRange('A', 'A', /*foldcase=*/1, /*out=*/0);

  ASSERT_EQ(x0.opcode(), re2::kInstByteRange);
  ASSERT_EQ(x1.opcode(), re2::kInstByteRange);

  EXPECT_EQ(x0.hint(), x0.hint());
  EXPECT_EQ(x1.hint(), x1.hint());
  EXPECT_EQ(x0.hint(), x1.hint());
}

// ----------------------------------------------------------------------------
// Copy/assignment semantics visible via the public API: copying an instruction
// should preserve observable behavior (including hint()).
// ----------------------------------------------------------------------------

TEST_F(InstHintTest_107, CopyPreservesHint_107) {
  auto original = InstHintTest_107::MakeByteRange('a', 'f', /*foldcase=*/0, /*out=*/123);
  ASSERT_EQ(original.opcode(), re2::kInstByteRange);

  Prog::Inst copy(original);               // copy ctor
  Prog::Inst assigned; assigned = original; // copy assignment

  EXPECT_EQ(original.hint(), copy.hint());
  EXPECT_EQ(original.hint(), assigned.hint());
}

// ----------------------------------------------------------------------------
// Exceptional / error behavior (observable): The provided implementation for
// hint() has a debug-check requiring opcode()==kInstByteRange. When DCHECKs are
// enabled, calling hint() on a non-ByteRange should crash. We guard the death
// test so it only runs under non-NDEBUG (debug) builds.
// ----------------------------------------------------------------------------

#ifndef NDEBUG
TEST_F(InstHintTest_107, DeathWhenNotByteRange_107) {
  Prog::Inst inst;
  inst.InitNop(/*out=*/0);
  ASSERT_EQ(inst.opcode(), re2::kInstNop);

  // ABSL_DCHECK_EQ in hint() should fire in debug when opcode != kInstByteRange.
  EXPECT_DEATH({ (void)inst.hint(); }, "");
}
#endif  // NDEBUG
