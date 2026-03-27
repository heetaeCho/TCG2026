// TEST_ID: 450
#include <gtest/gtest.h>

#include "emitterstate.h"

namespace {

class EmitterStateTest_450 : public ::testing::Test {
 protected:
  YAML::EmitterState state_;
};

TEST_F(EmitterStateTest_450, HasTag_IsConstAndStableAcrossCalls_450) {
  const YAML::EmitterState& cref = state_;

  const bool first = cref.HasTag();
  const bool second = cref.HasTag();

  // We don't assume the default value; we only verify observable stability and const-correctness.
  EXPECT_EQ(first, second);
}

TEST_F(EmitterStateTest_450, SetTag_MakesHasTagTrue_450) {
  state_.SetTag();
  EXPECT_TRUE(state_.HasTag());
}

TEST_F(EmitterStateTest_450, SetTag_IsIdempotent_450) {
  state_.SetTag();
  state_.SetTag();  // should be safe to call repeatedly
  EXPECT_TRUE(state_.HasTag());
}

TEST_F(EmitterStateTest_450, HasTag_ReflectsStateThroughConstReference_450) {
  state_.SetTag();
  const YAML::EmitterState& cref = state_;
  EXPECT_TRUE(cref.HasTag());
}

}  // namespace