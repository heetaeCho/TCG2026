// File: prog_inst_empty_test_109.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

namespace {

using re2::Prog;
using re2::InstOp;

// Test fixture kept minimal — we don't assume any internal state.
class ProgInstEmptyTest_109 : public ::testing::Test {};

TEST_F(ProgInstEmptyTest_109, InitEmptyWidthThenEmptyReturnsSame_109) {
  Prog::Inst inst;

  // Use distinct, arbitrary values without assuming EmptyOp's definition.
  auto v = static_cast<re2::EmptyOp>(0x1234);

  inst.InitEmptyWidth(v, /*out=*/0);
  EXPECT_EQ(inst.opcode(), InstOp::kInstEmptyWidth);
  EXPECT_EQ(inst.empty(), v);
}

TEST_F(ProgInstEmptyTest_109, EmptyWidthZeroFlag_109) {
  Prog::Inst inst;

  auto zero = static_cast<re2::EmptyOp>(0);
  inst.InitEmptyWidth(zero, /*out=*/0);
  EXPECT_EQ(inst.opcode(), InstOp::kInstEmptyWidth);
  EXPECT_EQ(inst.empty(), zero);
}

TEST_F(ProgInstEmptyTest_109, ReinitEmptyWidthOverwritesPrevious_109) {
  Prog::Inst inst;

  auto first  = static_cast<re2::EmptyOp>(0x1);
  auto second = static_cast<re2::EmptyOp>(0xABCD);

  inst.InitEmptyWidth(first, /*out=*/0);
  ASSERT_EQ(inst.opcode(), InstOp::kInstEmptyWidth);
  ASSERT_EQ(inst.empty(), first);

  // Re-initialize via the public API; observable result must reflect the latest init.
  inst.InitEmptyWidth(second, /*out=*/0);
  EXPECT_EQ(inst.opcode(), InstOp::kInstEmptyWidth);
  EXPECT_EQ(inst.empty(), second);
}

TEST_F(ProgInstEmptyTest_109, OpcodeNotEmptyWidthForOtherInits_109) {
  Prog::Inst inst;

  // Verify that initializing with other constructors results in a non-kInstEmptyWidth opcode.
  // We do NOT call empty() here to avoid depending on debug assertions.
  inst.InitNop(/*out=*/0);
  EXPECT_NE(inst.opcode(), InstOp::kInstEmptyWidth);

  inst.InitFail();
  EXPECT_NE(inst.opcode(), InstOp::kInstEmptyWidth);

  inst.InitMatch(/*id=*/7);
  EXPECT_NE(inst.opcode(), InstOp::kInstEmptyWidth);

  inst.InitCapture(/*cap=*/2, /*out=*/0);
  EXPECT_NE(inst.opcode(), InstOp::kInstEmptyWidth);

  inst.InitAlt(/*out=*/0, /*out1=*/0);
  EXPECT_NE(inst.opcode(), InstOp::kInstEmptyWidth);

  inst.InitByteRange(/*lo=*/'a', /*hi=*/'z', /*foldcase=*/0, /*out=*/0);
  EXPECT_NE(inst.opcode(), InstOp::kInstEmptyWidth);
}

TEST_F(ProgInstEmptyTest_109, IdempotentEmptyCallDoesNotChangeOpcode_109) {
  Prog::Inst inst;
  auto v = static_cast<re2::EmptyOp>(0x42);

  inst.InitEmptyWidth(v, /*out=*/0);
  ASSERT_EQ(inst.opcode(), InstOp::kInstEmptyWidth);

  // Calling empty() should be a pure observer: it shouldn't change opcode.
  (void)inst.empty();
  EXPECT_EQ(inst.opcode(), InstOp::kInstEmptyWidth);

  // And value remains stable.
  EXPECT_EQ(inst.empty(), v);
}

}  // namespace
