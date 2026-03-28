// File: onepass_isonepass_test_569.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

using namespace re2;

class ProgOnePassTest_569 : public ::testing::Test {
protected:
  Prog p_;
};

// [569] If start() == 0, IsOnePass() must report false (early no-match case).
TEST_F(ProgOnePassTest_569, StartZeroReturnsFalse_569) {
  p_.set_start(0);                 // Explicit: no-match start
  p_.set_dfa_mem(1LL << 30);       // Plenty of memory, so failure is due to start==0
  EXPECT_FALSE(p_.IsOnePass());
}

// [569] With nonzero start but effectively no memory budget, IsOnePass() reports false.
TEST_F(ProgOnePassTest_569, InsufficientMemoryReturnsFalse_569) {
  p_.set_start(1);                 // Non-zero start to avoid the early-return path above
  p_.set_dfa_mem(0);               // No memory available
  EXPECT_FALSE(p_.IsOnePass());
}

// [569] Once IsOnePass() has been evaluated, the result is cached.
// If the first call returns false, subsequent calls keep returning false
// even if external conditions change.
TEST_F(ProgOnePassTest_569, CachesFirstEvaluationResult_569) {
  // First call arranged to be false via start()==0.
  p_.set_start(0);
  p_.set_dfa_mem(0);
  EXPECT_FALSE(p_.IsOnePass());

  // Change conditions to something that *might* allow a different outcome
  // if recomputed, but the cached result should remain in effect.
  p_.set_start(1);
  p_.set_dfa_mem(1LL << 30);

  // Expect the same (cached) result.
  EXPECT_FALSE(p_.IsOnePass());
}

// [569] When IsOnePass() returns false, it should not consume the DFA memory budget.
// (Observable via the public getters/setters.)
TEST_F(ProgOnePassTest_569, DoesNotConsumeDfaMemOnFailure_569) {
  const int64_t initial_mem = 1234567;
  p_.set_dfa_mem(initial_mem);

  // Force an early false: start()==0 path.
  p_.set_start(0);
  EXPECT_FALSE(p_.IsOnePass());

  // Memory must remain unchanged after a failed IsOnePass().
  EXPECT_EQ(p_.dfa_mem(), initial_mem);
}
