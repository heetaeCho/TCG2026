// TEST_ID: 500
#include <gtest/gtest.h>

#include "emitterstate.h"
#include "yaml-cpp/emittermanip.h"

namespace {

class EmitterStateGetFlowTypeTest_500 : public ::testing::Test {
 protected:
  YAML::EmitterState state;

  // We intentionally avoid assuming any specific enumerator names for FmtScope.
  // Using a value-cast keeps the test focused on observable behavior.
  static constexpr YAML::FmtScope::value kAnyScope =
      static_cast<YAML::FmtScope::value>(0);
};

TEST_F(EmitterStateGetFlowTypeTest_500, ReturnsConfiguredValueForSeqAndMap_500) {
  // Configure distinct values for Seq and Map so we can observe selection.
  ASSERT_TRUE(state.SetFlowType(YAML::GroupType::Seq, YAML::Flow, kAnyScope));
  ASSERT_TRUE(state.SetFlowType(YAML::GroupType::Map, YAML::Block, kAnyScope));

  const YAML::EMITTER_MANIP seq = state.GetFlowType(YAML::GroupType::Seq);
  const YAML::EMITTER_MANIP map = state.GetFlowType(YAML::GroupType::Map);

  EXPECT_EQ(seq, YAML::Flow);
  EXPECT_EQ(map, YAML::Block);
  EXPECT_NE(seq, map);
}

TEST_F(EmitterStateGetFlowTypeTest_500, ForceFlowOverridesGroupSpecificSetting_500) {
  // Even if configured to something else, forcing flow should be observable
  // through GetFlowType returning Flow.
  ASSERT_TRUE(state.SetFlowType(YAML::GroupType::Seq, YAML::Block, kAnyScope));
  ASSERT_TRUE(state.SetFlowType(YAML::GroupType::Map, YAML::Block, kAnyScope));

  state.ForceFlow();

  EXPECT_EQ(state.GetFlowType(YAML::GroupType::Seq), YAML::Flow);
  EXPECT_EQ(state.GetFlowType(YAML::GroupType::Map), YAML::Flow);
}

TEST_F(EmitterStateGetFlowTypeTest_500, UnknownGroupTypeMatchesMapResult_500) {
  // Boundary: passing a non-standard/unknown GroupType value should still be
  // handled through the public interface without relying on internal state.
  ASSERT_TRUE(state.SetFlowType(YAML::GroupType::Map, YAML::Flow, kAnyScope));
  ASSERT_TRUE(state.SetFlowType(YAML::GroupType::Seq, YAML::Block, kAnyScope));

  const auto map_val = state.GetFlowType(YAML::GroupType::Map);

  const auto unknown_group =
      static_cast<YAML::GroupType::value>(999);  // deliberately non-standard
  const auto unknown_val = state.GetFlowType(unknown_group);

  EXPECT_EQ(unknown_val, map_val);
}

TEST_F(EmitterStateGetFlowTypeTest_500, GetFlowTypeDoesNotThrow_500) {
  EXPECT_NO_THROW((void)state.GetFlowType(YAML::GroupType::Seq));
  EXPECT_NO_THROW((void)state.GetFlowType(YAML::GroupType::Map));
}

}  // namespace