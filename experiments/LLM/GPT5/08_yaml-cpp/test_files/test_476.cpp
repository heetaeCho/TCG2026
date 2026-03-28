// File: ./TestProjects/yaml-cpp/test/emitterstate_endeddoc_test_476.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/src/emitterstate.h"

namespace {

class EmitterStateTest_476 : public ::testing::Test {
protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateTest_476, EndedDocClearsAnchorTagAndNonContent_476) {
  // Precondition: set observable flags via public API.
  state.SetAnchor();
  state.SetTag();
  state.SetNonContent();

  EXPECT_TRUE(state.HasAnchor());
  EXPECT_TRUE(state.HasTag());
  EXPECT_TRUE(state.HasBegunContent());

  // Action
  state.EndedDoc();

  // Postcondition: these flags are cleared.
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
  EXPECT_FALSE(state.HasBegunContent());
}

TEST_F(EmitterStateTest_476, EndedDocIsIdempotentWhenNothingWasSet_476) {
  // With a fresh instance, flags should be false.
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
  EXPECT_FALSE(state.HasBegunContent());

  // Calling EndedDoc() should not flip them to true or otherwise break.
  state.EndedDoc();

  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
  EXPECT_FALSE(state.HasBegunContent());
}

TEST_F(EmitterStateTest_476, EndedDocCanBeCalledRepeatedlyAfterStateChanges_476) {
  state.SetAnchor();
  state.SetTag();
  state.SetNonContent();

  ASSERT_TRUE(state.HasAnchor());
  ASSERT_TRUE(state.HasTag());
  ASSERT_TRUE(state.HasBegunContent());

  state.EndedDoc();
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
  EXPECT_FALSE(state.HasBegunContent());

  // Change state again, and ensure EndedDoc clears again.
  state.SetAnchor();
  state.SetTag();
  state.SetNonContent();

  ASSERT_TRUE(state.HasAnchor());
  ASSERT_TRUE(state.HasTag());
  ASSERT_TRUE(state.HasBegunContent());

  state.EndedDoc();
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
  EXPECT_FALSE(state.HasBegunContent());
}

TEST_F(EmitterStateTest_476, EndedDocDoesNotClearAliasFlag_476) {
  // Alias is independently settable and observable.
  state.SetAlias();
  ASSERT_TRUE(state.HasAlias());

  // EndedDoc is expected to clear anchor/tag/non-content, but not alias.
  state.EndedDoc();

  EXPECT_TRUE(state.HasAlias());
}

}  // namespace