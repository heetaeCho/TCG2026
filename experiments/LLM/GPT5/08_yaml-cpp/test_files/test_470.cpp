// File: ./TestProjects/yaml-cpp/test/emitterstate_settag_test_470.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/emitterstate.h"

namespace {

class EmitterStateTest_470 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateTest_470, SetTagMakesHasTagTrue_470) {
  // Black-box observable behavior: calling SetTag() should make HasTag() true.
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

TEST_F(EmitterStateTest_470, SetTagIsIdempotent_470) {
  // Boundary-ish: calling SetTag multiple times should remain safe and HasTag() stays true.
  state.SetTag();
  EXPECT_TRUE(state.HasTag());

  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

TEST_F(EmitterStateTest_470, SetTagDoesNotThrow_470) {
  // Exceptional/error case (as observable): API should not throw for a simple state toggle.
  EXPECT_NO_THROW(state.SetTag());
  EXPECT_TRUE(state.HasTag());
}

}  // namespace