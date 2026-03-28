// TEST_ID: 457
#include <gtest/gtest.h>

#include "emitterstate.h"

namespace {

TEST(EmitterStateTest_457, GetBoolCaseFormat_IsCallableOnConstObject_457) {
  const YAML::EmitterState state;
  (void)state.GetBoolCaseFormat();  // compile-time check: callable on const
}

TEST(EmitterStateTest_457, GetBoolCaseFormat_IsStableAcrossMultipleCalls_457) {
  YAML::EmitterState state;

  const auto v1 = state.GetBoolCaseFormat();
  const auto v2 = state.GetBoolCaseFormat();
  const auto v3 = state.GetBoolCaseFormat();

  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);
}

TEST(EmitterStateTest_457, GetBoolCaseFormat_DefaultConstructedEqualsValueInitialized_457) {
  YAML::EmitterState state;

  // Expect default-constructed state to expose the value-initialized EMITTER_MANIP.
  // This relies only on the observable return value and the public API.
  EXPECT_EQ(state.GetBoolCaseFormat(), EMITTER_MANIP());
}

TEST(EmitterStateTest_457, GetBoolCaseFormat_TwoDefaultInstancesMatch_457) {
  YAML::EmitterState a;
  YAML::EmitterState b;

  EXPECT_EQ(a.GetBoolCaseFormat(), b.GetBoolCaseFormat());
}

TEST(EmitterStateTest_457, GetBoolCaseFormat_CopyConstructionPreservesValue_457) {
  YAML::EmitterState original;
  const auto before = original.GetBoolCaseFormat();

  YAML::EmitterState copy(original);
  EXPECT_EQ(copy.GetBoolCaseFormat(), before);
  EXPECT_EQ(original.GetBoolCaseFormat(), before);
}

TEST(EmitterStateTest_457, GetBoolCaseFormat_CopyAssignmentPreservesValue_457) {
  YAML::EmitterState original;
  const auto before = original.GetBoolCaseFormat();

  YAML::EmitterState assigned;
  assigned = original;

  EXPECT_EQ(assigned.GetBoolCaseFormat(), before);
  EXPECT_EQ(original.GetBoolCaseFormat(), before);
}

TEST(EmitterStateTest_457, GetBoolCaseFormat_MoveConstructionPreservesValue_457) {
  YAML::EmitterState src;
  const auto before = src.GetBoolCaseFormat();

  YAML::EmitterState moved(std::move(src));
  EXPECT_EQ(moved.GetBoolCaseFormat(), before);
}

TEST(EmitterStateTest_457, GetBoolCaseFormat_MoveAssignmentPreservesValue_457) {
  YAML::EmitterState src;
  const auto before = src.GetBoolCaseFormat();

  YAML::EmitterState dst;
  dst = std::move(src);

  EXPECT_EQ(dst.GetBoolCaseFormat(), before);
}

}  // namespace