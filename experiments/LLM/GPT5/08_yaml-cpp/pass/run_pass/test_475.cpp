// File: ./TestProjects/yaml-cpp/test/emitterstate_starteddoc_test.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/emitterstate.h"

namespace {

class EmitterStateStartedDocTest_475 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateStartedDocTest_475, StartedDocOnFreshStateClearsAnchorAndTag_475) {
  // Black-box expectation: StartedDoc() should result in no anchor/tag.
  state.StartedDoc();

  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateStartedDocTest_475, StartedDocResetsAnchorAfterSetAnchor_475) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor()) << "Precondition: SetAnchor() should be observable via HasAnchor().";

  state.StartedDoc();

  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateStartedDocTest_475, StartedDocResetsTagAfterSetTag_475) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag()) << "Precondition: SetTag() should be observable via HasTag().";

  state.StartedDoc();

  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateStartedDocTest_475, StartedDocResetsAnchorAndTagTogether_475) {
  state.SetAnchor();
  state.SetTag();

  ASSERT_TRUE(state.HasAnchor());
  ASSERT_TRUE(state.HasTag());

  state.StartedDoc();

  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateStartedDocTest_475, StartedDocIsIdempotentForAnchorAndTag_475) {
  state.SetAnchor();
  state.SetTag();
  ASSERT_TRUE(state.HasAnchor());
  ASSERT_TRUE(state.HasTag());

  state.StartedDoc();
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());

  // Calling StartedDoc again should keep the same observable state.
  state.StartedDoc();
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateStartedDocTest_475, StartedDocAfterNonContentSetStillClearsAnchorAndTag_475) {
  // We do not assume how "non-content" is represented beyond what is observable.
  state.SetNonContent();
  state.SetAnchor();
  state.SetTag();

  ASSERT_TRUE(state.HasAnchor());
  ASSERT_TRUE(state.HasTag());

  state.StartedDoc();

  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
}

}  // namespace