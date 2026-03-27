// File: prog_inst_greedy_test_110.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

using re2::Prog;
using re2::kInstAltMatch;
using re2::kInstNop;

class InstGreedyTest_110 : public ::testing::Test {};

// This test verifies the only externally observable behavior we can exercise
// from the interface: greedy() DCHECKs unless opcode() == kInstAltMatch.
// We must guard it so it only runs in debug builds where ABSL_DCHECK is active.
#if !defined(NDEBUG)
TEST_F(InstGreedyTest_110, DCheckWhenOpcodeIsNotAltMatch_110) {
  Prog::Inst inst;
  // Set an opcode that's *not* kInstAltMatch. Nop is a simple option.
  inst.InitNop(/*out=*/0);

  // Calling greedy() should trigger the ABSL_DCHECK_EQ on opcode().
  // We pass a null Prog*; the DCHECK occurs before dereferencing 'p'.
  ASSERT_DEATH(
      {
        // Intentionally invoke the precondition failure.
        (void)inst.greedy(/*p=*/nullptr);
      },
      "");  // Don't over-specify the regex for portability.
}
#else
TEST_F(InstGreedyTest_110, DCheckWhenOpcodeIsNotAltMatch_SkippedInRelease_110) {
  GTEST_SKIP() << "ABSL_DCHECKs are disabled in release builds.";
}
#endif

// Note:
// Additional normal/boundary cases (i.e., greedy() returning true/false based
// on successors reached via Prog::inst()) cannot be constructed using only the
// provided public interface without relying on private state or simulating the
// class internals—both forbidden by the constraints. If a black-box builder or
// factory for Prog/Inst graphs becomes available, we can add tests like:
//  - GreedyReturnsTrueWhenOutIsByteRange_110
//  - GreedyReturnsTrueWhenOutIsNopThenByteRange_110
//  - GreedyReturnsFalseForOtherSuccessors_110
// each configured strictly via public APIs.
