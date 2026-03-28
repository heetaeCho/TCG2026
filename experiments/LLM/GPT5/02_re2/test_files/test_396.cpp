// File: prog_initfail_test_396.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

namespace re2 {

class ProgInstInitFailTest_396 : public ::testing::Test {};

TEST_F(ProgInstInitFailTest_396, InitFailSetsOpcodeToFail_396) {
  Prog::Inst inst;
  inst.InitFail();

  // Observable behavior: opcode() reflects kInstFail after InitFail().
  EXPECT_EQ(inst.opcode(), kInstFail);
}

#ifndef NDEBUG
// In debug builds, ABSL_DCHECKs are active. Calling InitFail() when the
// instruction has already been initialized should violate the precondition
// (out_opcode_ must be zero) and trigger a death.
// We do NOT rely on private state; we simply initialize via a *public* init
// (InitNop) and then call InitFail().
TEST_F(ProgInstInitFailTest_396, InitFailAfterAnotherInitTriggersDCheck_396) {
  Prog::Inst inst;
  inst.InitNop(/*out=*/0);

  // Expect a debug-time check failure when calling InitFail() on a non-pristine inst.
  EXPECT_DEATH(inst.InitFail(), "");
}
#endif  // NDEBUG

// Optional smoke test: Dump should be callable after InitFail() without crashing.
// We don't assert specific contents to avoid inferring internal formatting.
TEST_F(ProgInstInitFailTest_396, DumpAfterInitFailIsCallable_396) {
  Prog::Inst inst;
  inst.InitFail();

  std::string dumped = inst.Dump();
  // Minimal observable check: Dump returns a string object (may be empty or not).
  // We avoid asserting on contents to not infer internal formatting.
  (void)dumped;  // Suppress unused warning while still validating callability.
  SUCCEED();
}

}  // namespace re2
