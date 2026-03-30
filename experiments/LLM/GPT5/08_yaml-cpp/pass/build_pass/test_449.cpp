// TEST_ID: 449
#include <gtest/gtest.h>

#include "emitterstate.h"

namespace {

class EmitterStateHasAliasTest_449 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateHasAliasTest_449, HasAliasIsStableAcrossConsecutiveCalls_449) {
  // HasAlias() is const; repeated calls should be consistent.
  const bool first = state.HasAlias();
  const bool second = state.HasAlias();
  const bool third = state.HasAlias();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(EmitterStateHasAliasTest_449, SetAliasMakesHasAliasTrue_449) {
  // Observable behavior: setting alias should make HasAlias() report true.
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateHasAliasTest_449, SetAliasIsIdempotent_449) {
  // Calling SetAlias multiple times should be safe and keep HasAlias() true.
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());

  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());

  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateHasAliasTest_449, SetAliasDoesNotFlipBackToFalse_449) {
  // Once an alias is set, HasAlias() should not unexpectedly revert.
  state.SetAlias();
  const bool after_first_set = state.HasAlias();

  // Probe behavior over more calls without additional operations.
  const bool after_second_check = state.HasAlias();
  const bool after_third_check = state.HasAlias();

  EXPECT_TRUE(after_first_set);
  EXPECT_EQ(after_first_set, after_second_check);
  EXPECT_EQ(after_second_check, after_third_check);
}

}  // namespace