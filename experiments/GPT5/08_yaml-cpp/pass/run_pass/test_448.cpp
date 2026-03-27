// File: emitterstate_hasanchor_test.cpp
#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/emitterstate.h"

namespace {

class EmitterStateHasAnchorTest_448 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateHasAnchorTest_448, HasAnchorIsConsistentAcrossRepeatedCalls_448) {
  const bool first = state.HasAnchor();
  const bool second = state.HasAnchor();
  EXPECT_EQ(first, second);
}

TEST_F(EmitterStateHasAnchorTest_448, SetAnchorMakesHasAnchorTrue_448) {
  // Regardless of the initial state, after SetAnchor() the observable state
  // should indicate an anchor is present.
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateHasAnchorTest_448, SetAnchorIsIdempotent_448) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());

  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

}  // namespace