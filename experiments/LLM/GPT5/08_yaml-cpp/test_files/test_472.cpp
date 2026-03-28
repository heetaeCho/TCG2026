// TEST_ID: 472
#include <gtest/gtest.h>

#include "emitterstate.h"  // ./TestProjects/yaml-cpp/src/emitterstate.h

namespace {

class EmitterStateTest_472 : public ::testing::Test {
 protected:
  YAML::EmitterState state_;
};

TEST_F(EmitterStateTest_472, SetLongKeyOnMapGroupSetsLongKeyFlag_472) {
  // Arrange: enter a map group
  state_.StartedGroup(YAML::GroupType::Map);

  // Precondition (observable via public API): longKey starts false for a new group.
  EXPECT_FALSE(state_.CurGroupLongKey());

  // Act
  state_.SetLongKey();

  // Assert
  EXPECT_TRUE(state_.CurGroupLongKey());
}

TEST_F(EmitterStateTest_472, SetLongKeyIsIdempotentOnMapGroup_472) {
  state_.StartedGroup(YAML::GroupType::Map);

  state_.SetLongKey();
  EXPECT_TRUE(state_.CurGroupLongKey());

  // Calling again should keep it true (no additional observable effect expected).
  state_.SetLongKey();
  EXPECT_TRUE(state_.CurGroupLongKey());
}

#ifndef NDEBUG
TEST_F(EmitterStateTest_472, SetLongKeyWithNoActiveGroupDiesInDebug_472) {
  // With no started group, SetLongKey() has debug-time assertions.
  EXPECT_DEATH(state_.SetLongKey(), "");
}

TEST_F(EmitterStateTest_472, SetLongKeyWithNonMapTopGroupDiesInDebug_472) {
  // Arrange: top group is not a map.
  state_.StartedGroup(YAML::GroupType::Seq);

  // SetLongKey() asserts the current group type is Map in debug builds.
  EXPECT_DEATH(state_.SetLongKey(), "");
}
#else
TEST_F(EmitterStateTest_472, SetLongKeyWithNoActiveGroupDoesNotCrashInRelease_472) {
  // In release builds (asserts disabled), behavior should be non-fatal.
  // We only verify it does not crash/throw via observable behavior.
  EXPECT_NO_THROW(state_.SetLongKey());
}
#endif

}  // namespace