// File: ./TestProjects/yaml-cpp/test/emitterstate_startedgroup_test_478.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <limits>

#include "yaml-cpp/emittermanip.h"
#include "yaml-cpp/emitterstate.h"

namespace {

class EmitterStateStartedGroupTest_478 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateStartedGroupTest_478, StartedGroupSetsBegunNodeAndCurrentGroupMetadata_478) {
  // Arrange: choose a representative group type (sequence is commonly supported by yaml-cpp).
  const auto type = YAML::GroupType::Seq;

  // Make indent deterministic (if the implementation rejects it, the test still validates
  // that StartedGroup behaves consistently with the current GetIndent()).
  (void)state.SetIndent(2, YAML::FmtScope::Local);
  const std::size_t expectedIndent = state.GetIndent();

  const bool beganNodeBefore = state.HasBegunNode();
  const std::size_t curIndentBefore = state.CurIndent();
  const auto flowManipBefore = state.GetFlowType(type);

  // Act
  EXPECT_NO_THROW(state.StartedGroup(type));

  // Assert: StartedNode() is invoked (observable via HasBegunNode()).
  EXPECT_TRUE(state.HasBegunNode());
  // (Do not assume StartedNode() always flips from false->true; only require true after call.)
  (void)beganNodeBefore;

  // Current group type and indent should reflect the started group.
  EXPECT_EQ(state.CurGroupType(), type);
  EXPECT_EQ(state.CurGroupIndent(), expectedIndent);

  // Flow type should be consistent with GetFlowType(type) at the time of call.
  if (flowManipBefore == YAML::Block) {
    EXPECT_EQ(state.CurGroupFlowType(), YAML::FlowType::Block);
  } else {
    EXPECT_EQ(state.CurGroupFlowType(), YAML::FlowType::Flow);
  }

  // Basic sanity: CurIndent should be a well-defined value after the call.
  // (We only assert it didn't go "backwards" relative to the observable value beforehand.)
  EXPECT_GE(state.CurIndent(), curIndentBefore);
}

TEST_F(EmitterStateStartedGroupTest_478, NestedStartedGroupIncreasesCurIndentByParentGroupIndent_478) {
  // Arrange
  const auto outerType = YAML::GroupType::Seq;
  const auto innerType = YAML::GroupType::Map;

  // Force a known indent used by the group metadata.
  ASSERT_TRUE(state.SetIndent(3, YAML::FmtScope::Local));
  const std::size_t outerExpectedGroupIndent = state.GetIndent();

  state.StartedGroup(outerType);

  const std::size_t curIndentBeforeInner = state.CurIndent();
  const std::size_t outerGroupIndentObserved = state.CurGroupIndent();
  ASSERT_EQ(outerGroupIndentObserved, outerExpectedGroupIndent);

  // Act
  state.StartedGroup(innerType);

  // Assert: per provided implementation, CurIndent increases by the *previous* group's indent.
  EXPECT_EQ(state.CurIndent(), curIndentBeforeInner + outerGroupIndentObserved);

  // Also confirm the "current group" is now the inner group.
  EXPECT_EQ(state.CurGroupType(), innerType);
}

TEST_F(EmitterStateStartedGroupTest_478, StartedGroupCapturesIndentSettingAtTimeOfStart_478) {
  // Arrange
  const auto outerType = YAML::GroupType::Seq;
  const auto innerType = YAML::GroupType::Seq;

  ASSERT_TRUE(state.SetIndent(4, YAML::FmtScope::Local));
  const std::size_t indentOuter = state.GetIndent();

  // Act: start outer group
  state.StartedGroup(outerType);

  // Assert outer captured indent
  EXPECT_EQ(state.CurGroupIndent(), indentOuter);

  // Change indent, then start nested group
  ASSERT_TRUE(state.SetIndent(1, YAML::FmtScope::Local));
  const std::size_t indentInner = state.GetIndent();

  state.StartedGroup(innerType);

  // Assert inner captured the new indent
  EXPECT_EQ(state.CurGroupIndent(), indentInner);
}

TEST_F(EmitterStateStartedGroupTest_478, StartedGroupHandlesZeroIndentBoundary_478) {
  // Arrange
  const auto type = YAML::GroupType::Map;

  ASSERT_TRUE(state.SetIndent(0, YAML::FmtScope::Local));
  ASSERT_EQ(state.GetIndent(), static_cast<std::size_t>(0));

  // Act / Assert
  EXPECT_NO_THROW(state.StartedGroup(type));
  EXPECT_EQ(state.CurGroupIndent(), static_cast<std::size_t>(0));
  EXPECT_EQ(state.CurGroupType(), type);
}

TEST_F(EmitterStateStartedGroupTest_478, StartedGroupSupportsLargeIndentValueIfAcceptedBySetter_478) {
  // Arrange
  const auto type = YAML::GroupType::Seq;

  // Choose a "large" but reasonable value; also tolerate implementations that reject it.
  const std::size_t largeIndent = 1024;

  const bool setOk = state.SetIndent(largeIndent, YAML::FmtScope::Local);
  const std::size_t effectiveIndent = state.GetIndent();

  // Act
  EXPECT_NO_THROW(state.StartedGroup(type));

  // Assert: group indent matches whatever indent the state reports at start time.
  // If SetIndent rejected largeIndent, effectiveIndent will differ; we still validate capture behavior.
  EXPECT_EQ(state.CurGroupIndent(), effectiveIndent);

  // If the setter accepted the large value, ensure it is what was captured.
  if (setOk) {
    EXPECT_EQ(state.CurGroupIndent(), largeIndent);
  }
}

}  // namespace