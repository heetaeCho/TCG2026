// File: ./TestProjects/ninja/tests/subprocess_is_interrupted_test_93.cc

#include "subprocess.h"

#include <gtest/gtest.h>
#include <signal.h>

// Basic fixture for SubprocessSet-related tests.
// We don't access or assume anything about internal state.
class SubprocessSetTest_93 : public ::testing::Test {};

// Verify that after calling SetInterruptedFlag with a valid signal,
// IsInterrupted() reports an interrupted state.
TEST_F(SubprocessSetTest_93, IsInterruptedSetBySetInterruptedFlag_93) {
  // Act: simulate that an interrupt-like signal was received.
  SubprocessSet::SetInterruptedFlag(SIGINT);

  // Assert: the observable state via the public API should show interruption.
  EXPECT_TRUE(SubprocessSet::IsInterrupted());
}

// Verify that multiple calls to SetInterruptedFlag keep IsInterrupted() true.
// This checks that once interruption is signaled, the observable state
// remains interrupted even if SetInterruptedFlag is called again.
TEST_F(SubprocessSetTest_93, IsInterruptedStaysTrueAfterMultipleSetInterruptedFlagCalls_93) {
  // First "interrupt" with one signal.
  SubprocessSet::SetInterruptedFlag(SIGINT);
  EXPECT_TRUE(SubprocessSet::IsInterrupted());

  // Call again with a different signal; observable state should remain interrupted.
  SubprocessSet::SetInterruptedFlag(SIGTERM);
  EXPECT_TRUE(SubprocessSet::IsInterrupted());
}
