// File: walker_stopped_early_test_210.cc
#include <gtest/gtest.h>

// Header under test
#include "re2/walker-inl.h"

// Keep tests minimal and interface-driven.

namespace {

// Basic fixture, reserved for future shared setup if needed.
class WalkerTest_210 : public ::testing::Test {};

}  // namespace

// [210] Verifies that stopped_early() returns a boolean and is callable.
// This confirms basic accessibility of the public API.
TEST_F(WalkerTest_210, StoppedEarly_IsCallableAndBoolean_210) {
  re2::Regexp::Walker w;
  // We don't assert a specific initial value here beyond checking that it’s a bool-returning call.
  // Still, a boolean EXPECT_* requires a value; we allow either true/false logically,
  // but we check that repeated calls are consistent (see next tests).
  bool value = w.stopped_early();
  (void)value;  // Explicitly ignore to emphasize API call success.
  SUCCEED();    // If we reached here, the API is callable.
}

// [210] Calling stopped_early() multiple times should not, by itself, change the value.
// Getter should be idempotent with no visible side effects.
TEST_F(WalkerTest_210, StoppedEarly_IdempotentGetter_210) {
  re2::Regexp::Walker w;

  bool first = w.stopped_early();
  bool second = w.stopped_early();
  bool third = w.stopped_early();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

// [210] The value observed from stopped_early() remains stable across many calls,
// ensuring repeated reads don’t mutate state.
TEST_F(WalkerTest_210, StoppedEarly_NoSideEffectsFromReads_210) {
  re2::Regexp::Walker w;

  bool initial = w.stopped_early();
  for (int i = 0; i < 100; ++i) {
    EXPECT_EQ(initial, w.stopped_early()) << "stopped_early() value changed on read at iteration " << i;
  }
}

