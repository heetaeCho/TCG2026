// File: prog_inst_count_test_120.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

using re2::Prog;

// A small fixture in case future tests need shared setup.
class ProgInstCountTest_120 : public ::testing::Test {};

// [Type Contract] The member function type must be: int (Prog::*)(InstOp).
// This does not execute any code; it only verifies the public signature.
TEST_F(ProgInstCountTest_120, InstCount_HasExpectedSignature_120) {
  // If this static_assert fails, the public interface changed.
  using MemberFn = int (Prog::*)(InstOp);
  static_assert(std::is_same<decltype(&Prog::inst_count), MemberFn>::value,
                "Prog::inst_count must have signature int(InstOp)");
  SUCCEED();  // Make the test body non-empty for some compilers/tools.
}

// [Default Construction] For a freshly constructed Prog, the count for each
// defined opcode should be 0. We avoid inferring internal ranges by relying
// on the commonly used 8-way opcode space (0..7) as exposed in the API type.
// If your InstOp has a different range, adjust indices accordingly in your env.
TEST_F(ProgInstCountTest_120, InstCount_DefaultIsZeroForCommonOps_120) {
  Prog p;

  // The header shows an internal array of size 8 for counts; exercise 0..7.
  for (int i = 0; i < 8; ++i) {
    auto op = static_cast<InstOp>(i);
    int count = p.inst_count(op);
    EXPECT_EQ(count, 0) << "Expected default inst_count for op " << i << " to be 0";
  }
}

// [Idempotence] Calling inst_count repeatedly with the same op should not
// change its result (a pure observer).
TEST_F(ProgInstCountTest_120, InstCount_IsStableAcrossRepeatedCalls_120) {
  Prog p;
  auto op = static_cast<InstOp>(0);  // use a valid, well-defined opcode index

  int first = p.inst_count(op);
  int second = p.inst_count(op);
  int third = p.inst_count(op);

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

// [Object Independence] Two default-constructed objects should report the same
// count for the same opcode (no shared mutable state exposed through this API).
TEST_F(ProgInstCountTest_120, InstCount_IndependentAcrossInstances_120) {
  Prog p1;
  Prog p2;

  for (int i = 0; i < 8; ++i) {
    auto op = static_cast<InstOp>(i);
    EXPECT_EQ(p1.inst_count(op), p2.inst_count(op))
        << "inst_count differs between two default-constructed Prog objects for op " << i;
  }
}

// [No Side Effects] Calling inst_count for one opcode should not alter the
// observed count for another opcode.
TEST_F(ProgInstCountTest_120, InstCount_NoCrossOpcodeSideEffects_120) {
  Prog p;

  auto op0 = static_cast<InstOp>(0);
  auto op1 = static_cast<InstOp>(1);

  int before0 = p.inst_count(op0);
  int before1 = p.inst_count(op1);

  // Invoke multiple times on op0.
  (void)p.inst_count(op0);
  (void)p.inst_count(op0);
  (void)p.inst_count(op0);

  int after0 = p.inst_count(op0);
  int after1 = p.inst_count(op1);

  EXPECT_EQ(before0, after0) << "inst_count(op0) changed after repeated reads";
  EXPECT_EQ(before1, after1) << "inst_count(op1) changed after reads of a different opcode";
}
