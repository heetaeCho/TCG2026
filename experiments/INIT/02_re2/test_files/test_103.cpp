// File: prog_inst_cap_test_103.cc

#include <gtest/gtest.h>
#include <limits>
#include "re2/prog.h"  // adjust include path if your project layout differs

using re2::Prog;
using re2::InstOp;

class InstCapTest_103 : public ::testing::Test {};

// Normal operation: after InitCapture, opcode is kInstCapture and cap() returns the given value.
TEST_F(InstCapTest_103, InitCapture_SetsOpcodeAndCap_103) {
  Prog::Inst inst;
  const int kCap = 7;
  const uint32_t kOut = 123u;

  inst.InitCapture(kCap, kOut);

  EXPECT_EQ(inst.opcode(), InstOp::kInstCapture);
  EXPECT_EQ(inst.cap(), kCap);
}

// Boundary values: cap() returns exactly what was set via InitCapture for a range of values,
// including 0, positive/negative, and INT_MIN/INT_MAX. This does not infer internal logic—just
// validates observable outputs from the public API.
TEST_F(InstCapTest_103, Cap_ReturnsExactValues_ForVariousInputs_103) {
  const int values[] = {
      0,
      1,
      -1,
      std::numeric_limits<int>::max(),
      std::numeric_limits<int>::min()
  };

  for (int v : values) {
    Prog::Inst inst;
    inst.InitCapture(v, /*out=*/0u);
    ASSERT_EQ(inst.opcode(), InstOp::kInstCapture) << "Precondition for cap()";
    EXPECT_EQ(inst.cap(), v) << "cap() should return the same value passed to InitCapture";
  }
}

// Error/exceptional case (observable via debug checks):
// cap() has a precondition that opcode() == kInstCapture. In debug builds,
// ABSL_DCHECK should trigger death if called on a non-capture instruction.
// Guarded so release builds (where DCHECKs may be compiled out) don't fail.
#ifndef NDEBUG
TEST_F(InstCapTest_103, Cap_DeathIfOpcodeNotCapture_DebugOnly_103) {
  Prog::Inst inst;
  // Initialize to something that is not kInstCapture (e.g., NOP).
  inst.InitNop(/*out=*/0u);

  // Expect a debug-death due to the ABSL_DCHECK in cap().
  // The regex for EXPECT_DEATH can be empty to avoid coupling to log text.
  EXPECT_DEATH({ (void)inst.cap(); }, "");
}
#endif  // NDEBUG
