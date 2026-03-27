// File: prog_inst_out_test_101.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

using re2::Prog;

// Test fixture kept minimal; we only rely on the public Inst interface.
class InstOutTest_101 : public ::testing::Test {};

// Normal operation: InitNop sets a single out target that out() should return.
TEST_F(InstOutTest_101, InitNop_SetsOut_101) {
  Prog::Inst inst;
  inst.InitNop(/*out=*/7);
  EXPECT_EQ(inst.out(), 7);
}

// Normal operation: InitByteRange carries an out value that out() should return.
TEST_F(InstOutTest_101, InitByteRange_SetsOut_101) {
  Prog::Inst inst;
  inst.InitByteRange(/*lo=*/'a', /*hi=*/'z', /*foldcase=*/0, /*out=*/123);
  EXPECT_EQ(inst.out(), 123);
}

// Normal operation: InitCapture carries an out value that out() should return.
TEST_F(InstOutTest_101, InitCapture_SetsOut_101) {
  Prog::Inst inst;
  inst.InitCapture(/*cap=*/2, /*out=*/77);
  EXPECT_EQ(inst.out(), 77);
}

// Normal operation: InitEmptyWidth carries an out value that out() should return.
TEST_F(InstOutTest_101, InitEmptyWidth_SetsOut_101) {
  Prog::Inst inst;
  // EmptyOp is opaque here; pass 0 which is a common “no-flags” value in many enums.
  inst.InitEmptyWidth(/*empty=*/static_cast<EmptyOp>(0), /*out=*/88);
  EXPECT_EQ(inst.out(), 88);
}

// Normal operation with two-way branch: InitAlt has two outs; out() must return the primary one.
TEST_F(InstOutTest_101, InitAlt_PrimaryOutReturned_101) {
  Prog::Inst inst;
  inst.InitAlt(/*out=*/5, /*out1=*/9);
  EXPECT_EQ(inst.out(), 5);
}

// Boundary conditions: verify representative edge-y out values are preserved.
TEST_F(InstOutTest_101, Out_PreservesRepresentativeBoundaryValues_101) {
  Prog::Inst inst;

  // 0 should be preserved.
  inst.InitNop(/*out=*/0);
  EXPECT_EQ(inst.out(), 0);

  // Low nibble values (exercise potential packing of opcode in low bits).
  inst.InitNop(/*out=*/1);
  EXPECT_EQ(inst.out(), 1);
  inst.InitNop(/*out=*/15);
  EXPECT_EQ(inst.out(), 15);
  inst.InitNop(/*out=*/16);
  EXPECT_EQ(inst.out(), 16);
  inst.InitNop(/*out=*/31);
  EXPECT_EQ(inst.out(), 31);

  // Large value within common 28-bit “out” packing (if any). We don't depend on internals,
  // but this checks that a large, valid out is surfaced consistently via out().
  const uint32_t kLargeRepresentableOut = (1u << 28) - 1u; // 268,435,455
  inst.InitNop(/*out=*/kLargeRepresentableOut);
  EXPECT_EQ(static_cast<uint32_t>(inst.out()), kLargeRepresentableOut);
}

// State change: re-initialization should update the observable out() accordingly.
TEST_F(InstOutTest_101, Reinit_UpdatesOut_101) {
  Prog::Inst inst;
  inst.InitNop(/*out=*/1);
  EXPECT_EQ(inst.out(), 1);

  // Re-initialize with a different instruction and out value.
  inst.InitByteRange(/*lo=*/0, /*hi=*/255, /*foldcase=*/0, /*out=*/42);
  EXPECT_EQ(inst.out(), 42);

  // Re-initialize again to a different out.
  inst.InitCapture(/*cap=*/0, /*out=*/99);
  EXPECT_EQ(inst.out(), 99);
}

// Exceptional / special forms: instructions that conceptually have no outgoing edge.
// We verify observable behavior without assuming internal representation.
TEST_F(InstOutTest_101, InitMatch_NoExplicitOut_ObservableIsStable_101) {
  Prog::Inst inst;

  // Set a known out first, then switch to a form that conceptually has no out.
  inst.InitNop(/*out=*/17);
  EXPECT_EQ(inst.out(), 17);

  inst.InitMatch(/*id=*/3);
  // The interface doesn't document a specific out() for a terminal instruction.
  // We only assert that calling out() is well-defined (no crash) and returns
  // a non-negative integer. Avoid over-specifying exact value.
  int observed = inst.out();
  EXPECT_GE(observed, 0);
}

TEST_F(InstOutTest_101, InitFail_NoExplicitOut_ObservableIsStable_101) {
  Prog::Inst inst;

  inst.InitNop(/*out=*/25);
  EXPECT_EQ(inst.out(), 25);

  inst.InitFail();
  int observed = inst.out();
  EXPECT_GE(observed, 0);
}
