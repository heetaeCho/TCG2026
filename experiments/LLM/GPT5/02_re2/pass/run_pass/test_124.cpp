// File: prog_anchor_start_test_124.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

namespace {

using re2::Prog;

class ProgAnchorStartTest_124 : public ::testing::Test {
protected:
  Prog p_;
};

// [Normal] Default should be false per observable constructor behavior.
TEST_F(ProgAnchorStartTest_124, DefaultIsFalse_124) {
  EXPECT_FALSE(p_.anchor_start());
}

// [Normal] After setting to true, getter reflects the change.
TEST_F(ProgAnchorStartTest_124, SetTrueThenGetTrue_124) {
  p_.set_anchor_start(true);
  EXPECT_TRUE(p_.anchor_start());
}

// [Boundary] Toggling true -> false should be reflected.
TEST_F(ProgAnchorStartTest_124, ToggleTrueThenFalse_124) {
  p_.set_anchor_start(true);
  ASSERT_TRUE(p_.anchor_start());  // sanity check
  p_.set_anchor_start(false);
  EXPECT_FALSE(p_.anchor_start());
}

// [Boundary] Setting the same value repeatedly is idempotent (observable).
TEST_F(ProgAnchorStartTest_124, IdempotentWhenSettingTrueTwice_124) {
  p_.set_anchor_start(true);
  EXPECT_TRUE(p_.anchor_start());
  p_.set_anchor_start(true);
  EXPECT_TRUE(p_.anchor_start());
}

// [Interaction] Changes to other public flags must not alter anchor_start()
// (verifies independence via observable interface).
TEST_F(ProgAnchorStartTest_124, UnaffectedByOtherFlags_124) {
  // Start with a known state.
  p_.set_anchor_start(false);
  // These are other public setters in the interface; we call them and
  // verify anchor_start() stays the same.
  p_.set_anchor_end(true);
  EXPECT_FALSE(p_.anchor_start());

  p_.set_reversed(true);
  EXPECT_FALSE(p_.anchor_start());

  // Flip anchor_start and verify still unaffected by further changes.
  p_.set_anchor_start(true);
  EXPECT_TRUE(p_.anchor_start());

  p_.set_anchor_end(false);
  EXPECT_TRUE(p_.anchor_start());

  p_.set_reversed(false);
  EXPECT_TRUE(p_.anchor_start());
}

}  // namespace
