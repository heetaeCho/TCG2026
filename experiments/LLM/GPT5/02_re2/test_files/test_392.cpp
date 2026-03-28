// File: prog_initcapture_test.cc

#include <gtest/gtest.h>
#include "re2/prog.h"

namespace {

using re2::Prog;
using re2::kInstCapture;

class ProgInstTest_392 : public ::testing::Test {
protected:
  Prog::Inst inst_;  // Fresh instance per test
};

// [Normal] InitCapture sets opcode, out, and cap as provided.
TEST_F(ProgInstTest_392, InitCapture_SetsOpcodeOutAndCap_392) {
  const int cap = 2;
  const uint32_t out = 42u;

  inst_.InitCapture(cap, out);

  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), cap);
  EXPECT_EQ(inst_.out(), static_cast<int>(out));  // out() is int in interface
}

// [Boundary] out = 0 should be accepted and observable via out().
TEST_F(ProgInstTest_392, InitCapture_AllowsZeroOut_392) {
  const int cap = 0;
  const uint32_t out = 0u;

  inst_.InitCapture(cap, out);

  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), cap);
  EXPECT_EQ(inst_.out(), 0);
}

// [Boundary] Negative cap should be stored as-is and observable via cap().
TEST_F(ProgInstTest_392, InitCapture_AllowsNegativeCap_392) {
  const int cap = -1;
  const uint32_t out = 7u;

  inst_.InitCapture(cap, out);

  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), cap);     // Expect exact preservation
  EXPECT_EQ(inst_.out(), 7);
}

// [Boundary] Large (but signed-int-range) out value should be preserved.
TEST_F(ProgInstTest_392, InitCapture_PreservesLargeOutWithinIntRange_392) {
  const int cap = 10;
  const uint32_t out = 0x7FFFFFFFu;  // fits in signed int

  inst_.InitCapture(cap, out);

  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), cap);
  EXPECT_EQ(inst_.out(), static_cast<int>(out));
}

}  // namespace
