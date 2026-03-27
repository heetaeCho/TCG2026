// File: prog_set_anchor_end_test.cc

#include "re2/prog.h"
#include <gtest/gtest.h>

using re2::Prog;

class ProgTest_127 : public ::testing::Test {};

// Verifies the default observable state of anchor_end via the getter.
TEST_F(ProgTest_127, DefaultAnchorEndIsFalse_127) {
  Prog p;
  // Observable behavior only: check the public getter.
  EXPECT_FALSE(p.anchor_end());
}

// Setting anchor_end to true should be observable via the getter.
TEST_F(ProgTest_127, SetAnchorEndTrue_127) {
  Prog p;
  p.set_anchor_end(true);
  EXPECT_TRUE(p.anchor_end());
}

// Toggling from true back to false should be reflected via the getter.
TEST_F(ProgTest_127, ToggleAnchorEndTrueThenFalse_127) {
  Prog p;
  p.set_anchor_end(true);
  ASSERT_TRUE(p.anchor_end());

  p.set_anchor_end(false);
  EXPECT_FALSE(p.anchor_end());
}

// Idempotency: setting the same value repeatedly should keep the same observable state.
TEST_F(ProgTest_127, IdempotentWhenSettingSameValue_127) {
  Prog p;

  p.set_anchor_end(true);
  ASSERT_TRUE(p.anchor_end());
  p.set_anchor_end(true);
  EXPECT_TRUE(p.anchor_end());

  p.set_anchor_end(false);
  ASSERT_FALSE(p.anchor_end());
  p.set_anchor_end(false);
  EXPECT_FALSE(p.anchor_end());
}

// Independence across instances: changing one instance should not affect another.
TEST_F(ProgTest_127, InstanceIndependence_127) {
  Prog a;
  Prog b;

  a.set_anchor_end(true);
  EXPECT_TRUE(a.anchor_end());
  EXPECT_FALSE(b.anchor_end());  // b should remain at its default-observed state
}
