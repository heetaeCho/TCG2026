// File: ./TestProjects/re2/re2/tests/prog_set_anchor_start_test.cc

#include "gtest/gtest.h"
#include "re2/prog.h"

using re2::Prog;

// Test fixture for Prog-related tests
class ProgTest_125 : public ::testing::Test {
protected:
  Prog prog_;  // Fresh instance per test
};

// [Normal] Default state should be false (as observable via the public getter).
TEST_F(ProgTest_125, DefaultAnchorStartIsFalse_125) {
  // Observable behavior via public API:
  // Constructor initializes the object; verify the publicly exposed state.
  EXPECT_FALSE(prog_.anchor_start());
}

// [Normal] Setting anchor_start to true should be reflected by the getter.
TEST_F(ProgTest_125, SetAnchorStartTrue_125) {
  prog_.set_anchor_start(true);
  EXPECT_TRUE(prog_.anchor_start());
}

// [Boundary] Toggling from true to false should update the observable state.
TEST_F(ProgTest_125, ToggleAnchorStartTrueThenFalse_125) {
  prog_.set_anchor_start(true);
  ASSERT_TRUE(prog_.anchor_start());  // assert intermediate observable state

  prog_.set_anchor_start(false);
  EXPECT_FALSE(prog_.anchor_start());
}

// [Boundary] Setting the same value repeatedly should be idempotent (no side effects observable via getter).
TEST_F(ProgTest_125, IdempotentWhenSettingTrueTwice_125) {
  prog_.set_anchor_start(true);
  ASSERT_TRUE(prog_.anchor_start());

  prog_.set_anchor_start(true);  // same value again
  EXPECT_TRUE(prog_.anchor_start()); // remains true
}

// [Sanity] Changing anchor_start should not implicitly flip other, independent flags exposed via public getters.
TEST_F(ProgTest_125, DoesNotAffectAnchorEnd_125) {
  // Capture initial observable state of anchor_end via its public getter.
  const bool initial_anchor_end = prog_.anchor_end();

  // Change anchor_start and verify anchor_end remains unchanged (observable via its getter).
  prog_.set_anchor_start(true);
  EXPECT_EQ(initial_anchor_end, prog_.anchor_end());

  prog_.set_anchor_start(false);
  EXPECT_EQ(initial_anchor_end, prog_.anchor_end());
}
