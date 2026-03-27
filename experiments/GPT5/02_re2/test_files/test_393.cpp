// File: prog_init_empty_width_test.cc

#include <limits>
#include <cstdint>
#include "gtest/gtest.h"
#include "re2/prog.h"

namespace re2 {

class ProgInstTest_393 : public ::testing::Test {};

// Normal operation: verifies opcode, out edge (typical), and empty payload pass-through.
TEST_F(ProgInstTest_393, InitEmptyWidth_SetsOpcodeOutAndEmpty_393) {
  Prog::Inst inst;
  const uint32_t kOut = 42;
  // Use a non-zero bit-pattern to ensure pass-through (treating as black box)
  EmptyOp eo = static_cast<EmptyOp>(0x25);

  inst.InitEmptyWidth(eo, kOut);

  EXPECT_EQ(inst.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst.out(), static_cast<int>(kOut));
  EXPECT_EQ(inst.empty(), eo);
}

// Boundary: out == 0 should be stored and reported as-is.
TEST_F(ProgInstTest_393, InitEmptyWidth_BoundaryOutZero_393) {
  Prog::Inst inst;
  const uint32_t kOut = 0u;
  EmptyOp eo = static_cast<EmptyOp>(0);  // allow zero mask

  inst.InitEmptyWidth(eo, kOut);

  EXPECT_EQ(inst.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst.out(), static_cast<int>(kOut));
  EXPECT_EQ(inst.empty(), eo);
}

// Boundary: large out value within signed-int range (avoids relying on internal width).
TEST_F(ProgInstTest_393, InitEmptyWidth_BoundaryOutLarge_393) {
  Prog::Inst inst;
  // Choose a large value that is still safely representable by int to avoid
  // making assumptions about internal representation of out().
  const uint32_t kOut = static_cast<uint32_t>(std::numeric_limits<int>::max());
  // Use a dense bitmask to ensure no accidental normalization.
  EmptyOp eo = static_cast<EmptyOp>(0x7FFF);

  inst.InitEmptyWidth(eo, kOut);

  EXPECT_EQ(inst.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst.out(), static_cast<int>(kOut));
  EXPECT_EQ(inst.empty(), eo);
}

}  // namespace re2
