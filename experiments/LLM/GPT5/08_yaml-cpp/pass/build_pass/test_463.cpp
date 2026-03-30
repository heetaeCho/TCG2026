// TEST_ID: 463
// File: ./TestProjects/yaml-cpp/test/emitterstate_getmapkeyformat_test.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/src/emitterstate.h"

namespace YAML {
namespace {

class EmitterStateGetMapKeyFormatTest_463 : public ::testing::Test {
 protected:
  EmitterState state_;
};

TEST_F(EmitterStateGetMapKeyFormatTest_463, DefaultValueIsStableAcrossRepeatedCalls_463) {
  const auto v1 = state_.GetMapKeyFormat();
  const auto v2 = state_.GetMapKeyFormat();
  const auto v3 = state_.GetMapKeyFormat();

  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);
}

TEST_F(EmitterStateGetMapKeyFormatTest_463, DefaultValueMatchesAcrossFreshInstances_463) {
  EmitterState a;
  EmitterState b;

  EXPECT_EQ(a.GetMapKeyFormat(), b.GetMapKeyFormat());
}

TEST_F(EmitterStateGetMapKeyFormatTest_463, CallableOnConstInstance_463) {
  const EmitterState& cref = state_;
  // Just verifying the method is callable and returns a value consistently on const objects.
  const auto v1 = cref.GetMapKeyFormat();
  const auto v2 = cref.GetMapKeyFormat();
  EXPECT_EQ(v1, v2);
}

TEST_F(EmitterStateGetMapKeyFormatTest_463, SettingAnErrorDoesNotChangeMapKeyFormat_463) {
  const auto before = state_.GetMapKeyFormat();

  state_.SetError("some error");

  const auto after = state_.GetMapKeyFormat();
  EXPECT_EQ(before, after);
}

TEST_F(EmitterStateGetMapKeyFormatTest_463, ClearingModifiedSettingsDoesNotChangeMapKeyFormat_463) {
  const auto before = state_.GetMapKeyFormat();

  state_.ClearModifiedSettings();

  const auto after = state_.GetMapKeyFormat();
  EXPECT_EQ(before, after);
}

}  // namespace
}  // namespace YAML