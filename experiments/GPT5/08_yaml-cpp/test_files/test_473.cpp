// TEST_ID: 473
#include <gtest/gtest.h>

#include "emitterstate.h"

namespace {

class EmitterStateTest_473 : public ::testing::Test {
protected:
  static YAML::GroupType::value AnyGroupType() {
    // Use the first enumerator (commonly 0) without assuming specific enum names.
    return static_cast<YAML::GroupType::value>(0);
  }
};

TEST_F(EmitterStateTest_473, ForceFlowSetsCurrentGroupFlowTypeToFlow_473) {
  YAML::EmitterState state;

  const auto type = AnyGroupType();
  state.StartedGroup(type);

  state.ForceFlow();

  EXPECT_EQ(state.CurGroupFlowType(), YAML::FlowType::Flow);
}

TEST_F(EmitterStateTest_473, ForceFlowIsIdempotentOnCurrentGroup_473) {
  YAML::EmitterState state;

  const auto type = AnyGroupType();
  state.StartedGroup(type);

  state.ForceFlow();
  const auto after_first = state.CurGroupFlowType();

  state.ForceFlow();
  const auto after_second = state.CurGroupFlowType();

  EXPECT_EQ(after_first, YAML::FlowType::Flow);
  EXPECT_EQ(after_second, YAML::FlowType::Flow);
  EXPECT_EQ(after_second, after_first);
}

TEST_F(EmitterStateTest_473, ForceFlowAffectsOnlyInnermostGroup_473) {
  YAML::EmitterState state;

  const auto type = AnyGroupType();

  // Outer group
  state.StartedGroup(type);
  const auto outer_before = state.CurGroupFlowType();

  // Inner group
  state.StartedGroup(type);
  state.ForceFlow();
  EXPECT_EQ(state.CurGroupFlowType(), YAML::FlowType::Flow);

  // End inner group, verify outer group flow type was not altered by ForceFlow on inner.
  state.EndedGroup(type);
  EXPECT_EQ(state.CurGroupFlowType(), outer_before);
}

TEST_F(EmitterStateTest_473, ForceFlowWithNoActiveGroupDiesInDebugOtherwiseNoCrash_473) {
  YAML::EmitterState state;

#if !defined(NDEBUG) && GTEST_HAS_DEATH_TEST
  EXPECT_DEATH({ state.ForceFlow(); }, "");
#else
  // In release builds, asserts are typically compiled out. The implementation also guards
  // against empty groups, so this should be a no-op and not crash.
  state.ForceFlow();
  SUCCEED();
#endif
}

}  // namespace