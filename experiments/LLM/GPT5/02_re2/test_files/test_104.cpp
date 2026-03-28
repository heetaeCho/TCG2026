// File: prog_inst_lo_test_104.cc
#include <cstdint>
#include "gtest/gtest.h"
#include "re2/prog.h"

using re2::Prog;
using re2::kInstByteRange;

class ProgInstLoTest_104 : public ::testing::Test {
protected:
  // Helper to create a ByteRange instruction purely via the public interface.
  static Prog::Inst MakeByteRangeInst(int lo, int hi, int foldcase = 0, uint32_t out = 0) {
    Prog::Inst inst;
    inst.InitByteRange(lo, hi, foldcase, out);
    return inst;
  }
};

// Normal operation: Init via public API, then read via lo()
TEST_F(ProgInstLoTest_104, ReturnsAssignedValue_Normal_104) {
  auto inst = MakeByteRangeInst(/*lo=*/'a', /*hi=*/'z');
  EXPECT_EQ(inst.opcode(), kInstByteRange);  // observable via public method
  EXPECT_EQ(inst.lo(), 'a');                 // should reflect what was set
}

// Boundary: minimum possible byte value (0)
TEST_F(ProgInstLoTest_104, ReturnsMinBoundary_0_104) {
  auto inst = MakeByteRangeInst(/*lo=*/0, /*hi=*/0);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.lo(), 0);
}

// Boundary: maximum possible byte value (255)
TEST_F(ProgInstLoTest_104, ReturnsMaxBoundary_255_104) {
  auto inst = MakeByteRangeInst(/*lo=*/255, /*hi=*/255);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.lo(), 255);
}

// Exceptional/contract case: calling lo() when opcode != kInstByteRange
// The interface uses ABSL_DCHECK_EQ(opcode(), kInstByteRange) in lo().
// In debug builds, this should crash; in release it may be a no-op.
// Guard so the death test runs only when DCHECKs are enabled.
#if !defined(NDEBUG)
TEST_F(ProgInstLoTest_104, DCHECKsWhenNotByteRange_104) {
  Prog::Inst inst;
  inst.InitNop(/*out=*/0);  // any non-ByteRange opcode via public API
  ASSERT_NE(inst.opcode(), kInstByteRange);
  // Expect a debug check failure when calling lo() under wrong opcode.
  ASSERT_DEATH(
      {
        // Use a lambda body so ASSERT_DEATH captures just the call.
        (void)inst.lo();
      },
      "");  // accept any message
}
#endif
