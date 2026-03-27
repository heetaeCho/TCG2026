// TEST_ID: 452
#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/emitterstate.h"

namespace {

class EmitterStateTest_452 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateTest_452, HasBegunContentMatchesHasAnchorOrHasTag_452) {
  // No assumptions about default state: only verify public-observable consistency.
  EXPECT_EQ(state.HasBegunContent(), state.HasAnchor() || state.HasTag());

  state.SetAnchor();
  EXPECT_EQ(state.HasBegunContent(), state.HasAnchor() || state.HasTag());

  state.SetTag();
  EXPECT_EQ(state.HasBegunContent(), state.HasAnchor() || state.HasTag());
}

TEST_F(EmitterStateTest_452, SetAnchorMakesBegunContentTrueWheneverHasAnchorIsTrue_452) {
  state.SetAnchor();

  // Only assert when the public predicate says anchor is present.
  if (state.HasAnchor()) {
    EXPECT_TRUE(state.HasBegunContent());
  }
  EXPECT_EQ(state.HasBegunContent(), state.HasAnchor() || state.HasTag());

  // Boundary/idempotence: calling again should keep consistency and not crash.
  state.SetAnchor();
  EXPECT_EQ(state.HasBegunContent(), state.HasAnchor() || state.HasTag());
  if (state.HasAnchor()) {
    EXPECT_TRUE(state.HasBegunContent());
  }
}

TEST_F(EmitterStateTest_452, SetTagMakesBegunContentTrueWheneverHasTagIsTrue_452) {
  state.SetTag();

  if (state.HasTag()) {
    EXPECT_TRUE(state.HasBegunContent());
  }
  EXPECT_EQ(state.HasBegunContent(), state.HasAnchor() || state.HasTag());

  // Boundary/idempotence: calling again should keep consistency and not crash.
  state.SetTag();
  EXPECT_EQ(state.HasBegunContent(), state.HasAnchor() || state.HasTag());
  if (state.HasTag()) {
    EXPECT_TRUE(state.HasBegunContent());
  }
}

TEST_F(EmitterStateTest_452, OrderIndependence_TagThenAnchorMaintainsConsistency_452) {
  state.SetTag();
  EXPECT_EQ(state.HasBegunContent(), state.HasAnchor() || state.HasTag());

  state.SetAnchor();
  EXPECT_EQ(state.HasBegunContent(), state.HasAnchor() || state.HasTag());

  // If either public predicate is true, begun-content must be true.
  if (state.HasAnchor() || state.HasTag()) {
    EXPECT_TRUE(state.HasBegunContent());
  }
}

TEST_F(EmitterStateTest_452, SetAliasDoesNotChangeAnchorOrTagFlags_452) {
  const bool before_anchor = state.HasAnchor();
  const bool before_tag = state.HasTag();

  state.SetAlias();

  // We don't assume what SetAlias does internally, only that it should not
  // affect HasAnchor/HasTag for HasBegunContent to remain consistent.
  EXPECT_EQ(state.HasAnchor(), before_anchor);
  EXPECT_EQ(state.HasTag(), before_tag);

  // Core observable contract for HasBegunContent:
  EXPECT_EQ(state.HasBegunContent(), state.HasAnchor() || state.HasTag());
}

}  // namespace