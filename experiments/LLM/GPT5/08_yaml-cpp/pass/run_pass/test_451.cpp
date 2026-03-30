#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/emitterstate.h"

namespace {

class EmitterStateTest_451 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateTest_451, InitiallyFalse_451) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_451, SetAnchorMakesTrue_451) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_451, SetTagMakesTrue_451) {
  state.SetTag();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_451, SetNonContentMakesTrue_451) {
  state.SetNonContent();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_451, SetAliasAloneDoesNotMakeTrue_451) {
  state.SetAlias();
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_451, AliasThenAnchorMakesTrue_451) {
  state.SetAlias();
  EXPECT_FALSE(state.HasBegunNode());

  state.SetAnchor();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_451, AliasThenTagMakesTrue_451) {
  state.SetAlias();
  EXPECT_FALSE(state.HasBegunNode());

  state.SetTag();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_451, AliasThenNonContentMakesTrue_451) {
  state.SetAlias();
  EXPECT_FALSE(state.HasBegunNode());

  state.SetNonContent();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_451, MultipleBegunFlagsRemainTrue_451) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasBegunNode());

  state.SetTag();
  EXPECT_TRUE(state.HasBegunNode());

  state.SetNonContent();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_451, RepeatedSetOperationsAreSafeAndStillTrue_451) {
  state.SetAnchor();
  state.SetAnchor();
  EXPECT_TRUE(state.HasBegunNode());

  state.SetTag();
  state.SetTag();
  EXPECT_TRUE(state.HasBegunNode());

  state.SetNonContent();
  state.SetNonContent();
  EXPECT_TRUE(state.HasBegunNode());
}

}  // namespace