// TEST_ID: 482
#include <gtest/gtest.h>

#include <yaml-cpp/emitterstate.h>

namespace {

class EmitterStateTest_482 : public ::testing::Test {
 protected:
  YAML::EmitterState state_;
};

TEST_F(EmitterStateTest_482, CurGroupFlowType_WhenNoGroups_ReturnsNoType_482) {
  EXPECT_EQ(state_.CurGroupFlowType(), YAML::FlowType::NoType);
}

TEST_F(EmitterStateTest_482, CurGroupFlowType_AfterStartedAndEndedGroup_ReturnsNoType_482) {
  EXPECT_NO_THROW(state_.StartedGroup(YAML::GroupType::Seq));
  (void)state_.CurGroupFlowType();  // Should be callable in a non-empty state.

  EXPECT_NO_THROW(state_.EndedGroup(YAML::GroupType::Seq));
  EXPECT_EQ(state_.CurGroupFlowType(), YAML::FlowType::NoType);
}

TEST_F(EmitterStateTest_482, CurGroupFlowType_NestedGroups_PopRestoresPreviousTop_482) {
  ASSERT_NO_THROW(state_.StartedGroup(YAML::GroupType::Seq));
  const YAML::FlowType::value outer_flow = state_.CurGroupFlowType();

  ASSERT_NO_THROW(state_.StartedGroup(YAML::GroupType::Map));
  const YAML::FlowType::value inner_flow = state_.CurGroupFlowType();

  // Not asserting outer_flow != inner_flow (implementation-defined),
  // only that the "top of stack" changes and is restored on pop.
  ASSERT_NO_THROW(state_.EndedGroup(YAML::GroupType::Map));
  EXPECT_EQ(state_.CurGroupFlowType(), outer_flow);

  ASSERT_NO_THROW(state_.EndedGroup(YAML::GroupType::Seq));
  EXPECT_EQ(state_.CurGroupFlowType(), YAML::FlowType::NoType);

  (void)inner_flow;  // Silence unused warnings if compiled with -Wextra.
}

TEST_F(EmitterStateTest_482, CurGroupFlowType_EndGroupWithoutStart_DoesNotThrowAndRemainsNoType_482) {
  EXPECT_EQ(state_.CurGroupFlowType(), YAML::FlowType::NoType);

  EXPECT_NO_THROW(state_.EndedGroup(YAML::GroupType::Seq));
  EXPECT_EQ(state_.CurGroupFlowType(), YAML::FlowType::NoType);

  // Repeating the error case should still not crash and should remain stable.
  EXPECT_NO_THROW(state_.EndedGroup(YAML::GroupType::Map));
  EXPECT_EQ(state_.CurGroupFlowType(), YAML::FlowType::NoType);
}

}  // namespace