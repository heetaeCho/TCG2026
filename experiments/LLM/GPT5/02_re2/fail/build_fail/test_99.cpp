// File: prog_inst_opcode_tests_99.cc

#include <gtest/gtest.h>
#include <cstdint>

// Include the real header from your tree:
#include "re2/prog.h"

using re2::Prog;

class ProgInstTest_99 : public ::testing::Test {};

// Verifies that different Init* calls result in distinguishable opcodes.
// (We don't assert *which* enum value each maps to — only that they differ.)
TEST_F(ProgInstTest_99, DistinctOpcodesForDifferentInits_99) {
  Prog::Inst inst;

  inst.InitAlt(/*out=*/1u, /*out1=*/2u);
  auto op_alt = inst.opcode();

  inst.InitByteRange(/*lo=*/'a', /*hi=*/'z', /*foldcase=*/0, /*out=*/3u);
  auto op_byte = inst.opcode();

  inst.InitCapture(/*cap=*/0, /*out=*/4u);
  auto op_cap = inst.opcode();

  // EmptyOp type exists but exact values are not assumed; use a benign zero cast.
  inst.InitEmptyWidth(static_cast<EmptyOp>(0), /*out=*/5u);
  auto op_empty = inst.opcode();

  inst.InitMatch(/*id=*/123);
  auto op_match = inst.opcode();

  inst.InitNop(/*out=*/6u);
  auto op_nop = inst.opcode();

  inst.InitFail();
  auto op_fail = inst.opcode();

  // Only observable behavior: opcodes from different initializers should differ.
  // We don't require all pairwise differences; at minimum, each should differ from the first.
  EXPECT_NE(op_byte,  op_alt);
  EXPECT_NE(op_cap,   op_alt);
  EXPECT_NE(op_empty, op_alt);
  EXPECT_NE(op_match, op_alt);
  EXPECT_NE(op_nop,   op_alt);
  EXPECT_NE(op_fail,  op_alt);

  // And a couple of additional cross-checks:
  EXPECT_NE(op_fail,  op_nop);
  EXPECT_NE(op_match, op_byte);
}

// Re-initializing an instruction with a different initializer should change the opcode.
TEST_F(ProgInstTest_99, ReinitChangesOpcode_99) {
  Prog::Inst inst;

  inst.InitNop(/*out=*/1u);
  auto op1 = inst.opcode();

  inst.InitFail();
  auto op2 = inst.opcode();

  EXPECT_NE(op2, op1);
}

// Copy-constructing should preserve the observable opcode.
TEST_F(ProgInstTest_99, CopyConstructorPreservesOpcode_99) {
  Prog::Inst original;
  original.InitMatch(/*id=*/42);
  auto op_before = original.opcode();

  Prog::Inst copy = original;
  EXPECT_EQ(copy.opcode(), op_before);
  EXPECT_EQ(original.opcode(), op_before);  // original unchanged
}

// Copy-assignment should preserve the observable opcode.
TEST_F(ProgInstTest_99, AssignmentPreservesOpcode_99) {
  Prog::Inst src;
  src.InitByteRange(/*lo=*/0, /*hi=*/255, /*foldcase=*/0, /*out=*/7u);
  auto op_src = src.opcode();

  Prog::Inst dst;
  dst.InitFail();  // start different
  EXPECT_NE(dst.opcode(), op_src);

  dst = src;  // assign
  EXPECT_EQ(dst.opcode(), op_src);
}

// Two independently initialized instances with the same initializer should report the same opcode.
TEST_F(ProgInstTest_99, SameInitYieldsSameOpcodeAcrossInstances_99) {
  Prog::Inst a, b;

  a.InitAlt(/*out=*/10u, /*out1=*/20u);
  b.InitAlt(/*out=*/30u, /*out1=*/40u);

  // We only check opcode equivalence; we don't assume or inspect any internal state or outputs.
  EXPECT_EQ(a.opcode(), b.opcode());
}

// Sanity: calling opcode() after a valid init should be safe and stable across repeated calls.
TEST_F(ProgInstTest_99, OpcodeStableAfterInit_99) {
  Prog::Inst inst;
  inst.InitNop(/*out=*/123u);

  auto op1 = inst.opcode();
  auto op2 = inst.opcode();
  EXPECT_EQ(op1, op2);
}
