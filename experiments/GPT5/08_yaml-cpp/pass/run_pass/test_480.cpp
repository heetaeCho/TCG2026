// TEST_ID: 480
#include <gtest/gtest.h>

#include "emitterstate.h"

namespace {

class EmitterStateTest_480 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateTest_480, CurGroupNodeType_EmptyGroupsReturnsNoType_480) {
  EXPECT_EQ(state.CurGroupNodeType(), YAML::EmitterNodeType::NoType);
}

TEST_F(EmitterStateTest_480, CurGroupNodeType_AfterStartedGroupMatchesNextGroupType_480) {
  const auto expected_seq = state.NextGroupType(YAML::GroupType::Seq);
  state.StartedGroup(YAML::GroupType::Seq);
  EXPECT_EQ(state.CurGroupNodeType(), expected_seq);

  state.EndedGroup(YAML::GroupType::Seq);
  EXPECT_EQ(state.CurGroupNodeType(), YAML::EmitterNodeType::NoType);
}

TEST_F(EmitterStateTest_480, CurGroupNodeType_NestedGroupsReflectsInnermostGroup_480) {
  state.StartedGroup(YAML::GroupType::Seq);
  const auto expected_map = state.NextGroupType(YAML::GroupType::Map);
  state.StartedGroup(YAML::GroupType::Map);

  EXPECT_EQ(state.CurGroupNodeType(), expected_map);

  state.EndedGroup(YAML::GroupType::Map);
  const auto expected_seq = state.NextGroupType(YAML::GroupType::Seq);
  EXPECT_EQ(state.CurGroupNodeType(), expected_seq);

  state.EndedGroup(YAML::GroupType::Seq);
  EXPECT_EQ(state.CurGroupNodeType(), YAML::EmitterNodeType::NoType);
}

TEST_F(EmitterStateTest_480, CurGroupNodeType_CalledRepeatedlyIsStableForSameState_480) {
  // Empty case: multiple calls should be consistent.
  EXPECT_EQ(state.CurGroupNodeType(), YAML::EmitterNodeType::NoType);
  EXPECT_EQ(state.CurGroupNodeType(), YAML::EmitterNodeType::NoType);

  // Non-empty case: multiple calls should be consistent as long as state doesn't change.
  state.StartedGroup(YAML::GroupType::Map);
  const auto first = state.CurGroupNodeType();
  const auto second = state.CurGroupNodeType();
  EXPECT_EQ(first, second);

  state.EndedGroup(YAML::GroupType::Map);
  EXPECT_EQ(state.CurGroupNodeType(), YAML::EmitterNodeType::NoType);
}

TEST_F(EmitterStateTest_480, CurGroupNodeType_AfterEndedGroupOnEmptyDoesNotThrowAndReturnsNoType_480) {
  // Error/exceptional behavior is only checked if observable. Here we just ensure it doesn't crash
  // and CurGroupNodeType remains well-defined.
  EXPECT_NO_THROW(state.EndedGroup(YAML::GroupType::Seq));
  EXPECT_EQ(state.CurGroupNodeType(), YAML::EmitterNodeType::NoType);
}

}  // namespace