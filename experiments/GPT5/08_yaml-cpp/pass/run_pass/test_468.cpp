// TEST_ID: 468
#include <gtest/gtest.h>

#include "emitterstate.h"  // Adjust include path if your project uses <yaml-cpp/emitterstate.h>

namespace {

class EmitterStateTest_468 : public ::testing::Test {
 protected:
  YAML::EmitterState state_;
};

TEST_F(EmitterStateTest_468, SetAnchorDoesNotThrow_468) {
  EXPECT_NO_THROW(state_.SetAnchor());
}

TEST_F(EmitterStateTest_468, SetAnchorMakesHasAnchorTrue_468) {
  // Black-box: regardless of initial state, after SetAnchor() we must observe HasAnchor()==true.
  state_.SetAnchor();
  EXPECT_TRUE(state_.HasAnchor());
}

TEST_F(EmitterStateTest_468, SetAnchorIsIdempotent_468) {
  state_.SetAnchor();
  ASSERT_TRUE(state_.HasAnchor());

  // Calling again should keep HasAnchor() true (at minimum it must not revert).
  state_.SetAnchor();
  EXPECT_TRUE(state_.HasAnchor());
}

}  // namespace