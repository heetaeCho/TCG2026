// TEST_ID: 483
#include <gtest/gtest.h>

#include "emitterstate.h"

namespace {

class EmitterStateTest_483 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateTest_483, CurGroupIndent_DefaultIsZero_483) {
  EXPECT_EQ(state.CurGroupIndent(), 0u);

  const YAML::EmitterState& cstate = state;
  EXPECT_EQ(cstate.CurGroupIndent(), 0u);
}

TEST_F(EmitterStateTest_483, CurGroupIndent_EndedGroupWithoutStartedGroup_DoesNotChangeFromZero_483) {
  // Error/exceptional-ish case: end a group when none has been started.
  // Observable requirement: should not crash; indent stays at the "no group" value.
  state.EndedGroup(static_cast<YAML::GroupType::value>(0));
  EXPECT_EQ(state.CurGroupIndent(), 0u);

  // Repeat to cover boundary-like repeated calls.
  state.EndedGroup(static_cast<YAML::GroupType::value>(0));
  EXPECT_EQ(state.CurGroupIndent(), 0u);
}

TEST_F(EmitterStateTest_483, CurGroupIndent_GroupStackRestoresPreviousIndent_483) {
  // Start an outer group and record its indent.
  state.StartedGroup(static_cast<YAML::GroupType::value>(0));
  const std::size_t outerIndent = state.CurGroupIndent();

  // Start an inner group; record its indent.
  state.StartedGroup(static_cast<YAML::GroupType::value>(1));
  const std::size_t innerIndent = state.CurGroupIndent();

  // The key observable behavior we can assert without inferring indent computation:
  // ending the inner group restores the previous group's indent.
  state.EndedGroup(static_cast<YAML::GroupType::value>(1));
  EXPECT_EQ(state.CurGroupIndent(), outerIndent);

  // Ending the outer group returns to the "no group" indent.
  state.EndedGroup(static_cast<YAML::GroupType::value>(0));
  EXPECT_EQ(state.CurGroupIndent(), 0u);

  // Sanity: we did observe an inner indent value (even if it equals outerIndent in some impls).
  (void)innerIndent;
}

TEST_F(EmitterStateTest_483, CurGroupIndent_MultipleNestedGroups_UnwindsToZero_483) {
  state.StartedGroup(static_cast<YAML::GroupType::value>(0));
  const std::size_t indent1 = state.CurGroupIndent();

  state.StartedGroup(static_cast<YAML::GroupType::value>(1));
  const std::size_t indent2 = state.CurGroupIndent();

  state.StartedGroup(static_cast<YAML::GroupType::value>(2));
  const std::size_t indent3 = state.CurGroupIndent();

  state.EndedGroup(static_cast<YAML::GroupType::value>(2));
  EXPECT_EQ(state.CurGroupIndent(), indent2);

  state.EndedGroup(static_cast<YAML::GroupType::value>(1));
  EXPECT_EQ(state.CurGroupIndent(), indent1);

  state.EndedGroup(static_cast<YAML::GroupType::value>(0));
  EXPECT_EQ(state.CurGroupIndent(), 0u);

  (void)indent3;
}

}  // namespace