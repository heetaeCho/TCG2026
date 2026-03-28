// File: prog_reversed_test_117.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

namespace re2 {

class ProgReversedTest_117 : public ::testing::Test {
protected:
  Prog prog_;
};

// [Normal] Newly constructed Prog should report a defined default for reversed().
// Based on provided constructor snippet, default is false.
TEST_F(ProgReversedTest_117, DefaultReversedIsFalse_117) {
  EXPECT_FALSE(prog_.reversed());
}

// [Normal] Setting reversed to true reflects via getter.
TEST_F(ProgReversedTest_117, SetReversedTrue_117) {
  prog_.set_reversed(true);
  EXPECT_TRUE(prog_.reversed());
}

// [Normal] Toggling reversed true -> false is observable through getter.
TEST_F(ProgReversedTest_117, ToggleReversedTrueThenFalse_117) {
  prog_.set_reversed(true);
  ASSERT_TRUE(prog_.reversed());  // precondition for the toggle
  prog_.set_reversed(false);
  EXPECT_FALSE(prog_.reversed());
}

// [Boundary] Setting reversed to the same value twice remains consistent.
TEST_F(ProgReversedTest_117, IdempotentSetReversed_117) {
  prog_.set_reversed(false);
  EXPECT_FALSE(prog_.reversed());
  prog_.set_reversed(false);  // no-op logically; observable state should be unchanged
  EXPECT_FALSE(prog_.reversed());

  prog_.set_reversed(true);
  EXPECT_TRUE(prog_.reversed());
  prog_.set_reversed(true);  // again, setting the same value
  EXPECT_TRUE(prog_.reversed());
}

// [Interaction] reversed() is a const-observable query; ensure reads don't change state.
TEST_F(ProgReversedTest_117, GetterDoesNotMutateState_117) {
  prog_.set_reversed(true);
  (void)prog_.reversed();
  EXPECT_TRUE(prog_.reversed());   // still true after read

  prog_.set_reversed(false);
  (void)prog_.reversed();
  EXPECT_FALSE(prog_.reversed());  // still false after read
}

}  // namespace re2
