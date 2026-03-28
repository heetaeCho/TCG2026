// TEST_ID: 501
#include <gtest/gtest.h>

#include "yaml-cpp/emitterstate.h"
#include "yaml-cpp/emittermanip.h"

namespace {

class EmitterStateTest_501 : public ::testing::Test {
 protected:
  YAML::EmitterState state;

  static YAML::FmtScope::value Scope0() {
    return static_cast<YAML::FmtScope::value>(0);
  }
  static YAML::FmtScope::value Scope1() {
    return static_cast<YAML::FmtScope::value>(1);
  }
};

TEST_F(EmitterStateTest_501, SetMapKeyFormatAcceptsAutoAndUpdatesGetter_501) {
  const auto before = state.GetMapKeyFormat();

  EXPECT_TRUE(state.SetMapKeyFormat(YAML::Auto, Scope0()));
  EXPECT_EQ(state.GetMapKeyFormat(), YAML::Auto);

  // Sanity: it actually changed if the default wasn't already Auto.
  // (If it was already Auto, this still verifies the observable getter value.)
  (void)before;
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatAcceptsLongKeyAndUpdatesGetter_501) {
  EXPECT_TRUE(state.SetMapKeyFormat(YAML::LongKey, Scope0()));
  EXPECT_EQ(state.GetMapKeyFormat(), YAML::LongKey);
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatRejectsUnsupportedManipAndDoesNotChangeValue_501) {
  // Put the state into a known value first.
  ASSERT_TRUE(state.SetMapKeyFormat(YAML::Auto, Scope0()));
  const auto before = state.GetMapKeyFormat();
  ASSERT_EQ(before, YAML::Auto);

  // Choose a manip that is not Auto/LongKey (per switch default => false).
  EXPECT_FALSE(state.SetMapKeyFormat(YAML::Key, Scope0()));
  EXPECT_EQ(state.GetMapKeyFormat(), before);

  EXPECT_FALSE(state.SetMapKeyFormat(YAML::Flow, Scope0()));
  EXPECT_EQ(state.GetMapKeyFormat(), before);

  EXPECT_FALSE(state.SetMapKeyFormat(YAML::BeginMap, Scope0()));
  EXPECT_EQ(state.GetMapKeyFormat(), before);
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatCanBeChangedMultipleTimes_501) {
  EXPECT_TRUE(state.SetMapKeyFormat(YAML::Auto, Scope0()));
  EXPECT_EQ(state.GetMapKeyFormat(), YAML::Auto);

  EXPECT_TRUE(state.SetMapKeyFormat(YAML::LongKey, Scope0()));
  EXPECT_EQ(state.GetMapKeyFormat(), YAML::LongKey);

  EXPECT_TRUE(state.SetMapKeyFormat(YAML::Auto, Scope0()));
  EXPECT_EQ(state.GetMapKeyFormat(), YAML::Auto);
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatBehaviorIsConsistentAcrossDifferentScopes_501) {
  // This test does NOT assume specific meanings of scope values; it just verifies
  // the observable contract for at least two distinct scope inputs.
  EXPECT_TRUE(state.SetMapKeyFormat(YAML::Auto, Scope0()));
  EXPECT_EQ(state.GetMapKeyFormat(), YAML::Auto);

  EXPECT_TRUE(state.SetMapKeyFormat(YAML::LongKey, Scope1()));
  EXPECT_EQ(state.GetMapKeyFormat(), YAML::LongKey);

  // Unsupported values should still be rejected regardless of scope.
  const auto before = state.GetMapKeyFormat();
  EXPECT_FALSE(state.SetMapKeyFormat(YAML::Value, Scope1()));
  EXPECT_EQ(state.GetMapKeyFormat(), before);
}

}  // n