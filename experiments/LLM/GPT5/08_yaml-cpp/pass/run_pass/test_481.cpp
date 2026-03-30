// TEST_ID: 481
#include <gtest/gtest.h>

#include "emitterstate.h"

namespace {

class EmitterStateTest_481 : public ::testing::Test {
protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateTest_481, CurGroupType_DefaultIsNoType_481) {
  EXPECT_EQ(state.CurGroupType(), YAML::GroupType::NoType);
}

TEST_F(EmitterStateTest_481, CurGroupType_AfterStartedGroupReflectsThatGroup_481) {
  state.StartedGroup(YAML::GroupType::Seq);
  EXPECT_EQ(state.CurGroupType(), YAML::GroupType::Seq);
}

TEST_F(EmitterStateTest_481, CurGroupType_NestedGroupsReturnsInnermost_481) {
  state.StartedGroup(YAML::GroupType::Map);
  EXPECT_EQ(state.CurGroupType(), YAML::GroupType::Map);

  state.StartedGroup(YAML::GroupType::Seq);
  EXPECT_EQ(state.CurGroupType(), YAML::GroupType::Seq);
}

TEST_F(EmitterStateTest_481, CurGroupType_EndingInnerGroupRevealsOuterGroup_481) {
  state.StartedGroup(YAML::GroupType::Map);
  state.StartedGroup(YAML::GroupType::Seq);

  state.EndedGroup(YAML::GroupType::Seq);
  EXPECT_EQ(state.CurGroupType(), YAML::GroupType::Map);
}

TEST_F(EmitterStateTest_481, CurGroupType_EndingAllGroupsReturnsToNoType_481) {
  state.StartedGroup(YAML::GroupType::Map);
  state.StartedGroup(YAML::GroupType::Seq);

  state.EndedGroup(YAML::GroupType::Seq);
  state.EndedGroup(YAML::GroupType::Map);

  EXPECT_EQ(state.CurGroupType(), YAML::GroupType::NoType);
}

}  // namespace