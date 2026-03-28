// File: prog_anchor_end_test_126.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

namespace re2 {

class ProgAnchorEndTest_126 : public ::testing::Test {
protected:
  Prog prog_;  // Construct fresh instance for each test
};

// Verifies the default observable state immediately after construction.
TEST_F(ProgAnchorEndTest_126, DefaultIsFalse_126) {
  // Expect: freshly constructed Prog reports anchor_end() == false.
  // (Observable behavior via public getter.)
  EXPECT_FALSE(prog_.anchor_end());
}

// Verifies that setting the flag to true is observable via the getter.
TEST_F(ProgAnchorEndTest_126, SetTrueReflectsInGetter_126) {
  prog_.set_anchor_end(true);
  EXPECT_TRUE(prog_.anchor_end());
}

// Verifies toggling the flag back to false is observable via the getter,
// and that repeated sets are consistent.
TEST_F(ProgAnchorEndTest_126, ToggleTrueThenFalseIsConsistent_126) {
  prog_.set_anchor_end(true);
  EXPECT_TRUE(prog_.anchor_end());

  prog_.set_anchor_end(false);
  EXPECT_FALSE(prog_.anchor_end());

  // Idempotence check: setting the same value again keeps it unchanged.
  prog_.set_anchor_end(false);
  EXPECT_FALSE(prog_.anchor_end());
}

}  // namespace re2
