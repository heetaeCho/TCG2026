// File: ./TestProjects/yaml-cpp/test/emitterstate_getintformat_test.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/emitterstate.h"

// yaml-cpp typically exposes manipulators like YAML::Hex / YAML::Dec and scope enums.
// Including yaml.h is a common way to get those symbols in tests.
#include <yaml-cpp/yaml.h>

namespace {

class EmitterStateGetIntFormatTest_459 : public ::testing::Test {
 protected:
  YAML::EmitterState state_;
};

TEST_F(EmitterStateGetIntFormatTest_459, DefaultConstructed_ReturnsStableValueAcrossCalls_459) {
  const auto v1 = state_.GetIntFormat();
  const auto v2 = state_.GetIntFormat();
  EXPECT_EQ(v1, v2);
}

TEST_F(EmitterStateGetIntFormatTest_459, SetIntFormatToSameValue_DoesNotChangeObservedValue_459) {
  const auto before = state_.GetIntFormat();

  // Set to the currently observed value; regardless of internal behavior, the public getter
  // should still report the same value afterward if the call succeeds.
  const bool ok = state_.SetIntFormat(before, YAML::FmtScope::LOCAL);
  EXPECT_TRUE(ok);

  const auto after = state_.GetIntFormat();
  EXPECT_EQ(after, before);
}

TEST_F(EmitterStateGetIntFormatTest_459, SetIntFormatToDifferentValue_UpdatesGetterWhenCallSucceeds_459) {
  const auto original = state_.GetIntFormat();

  // Try to change the format to a commonly available alternative manipulator.
  // If it's already Hex, switch to Dec; otherwise switch to Hex.
  const auto target = (original == YAML::Hex) ? YAML::Dec : YAML::Hex;

  const bool ok = state_.SetIntFormat(target, YAML::FmtScope::LOCAL);
  EXPECT_TRUE(ok);

  EXPECT_EQ(state_.GetIntFormat(), target);

  // Restore to original to avoid leaking state between tests (even though this is a fresh fixture).
  const bool ok_restore = state_.SetIntFormat(original, YAML::FmtScope::LOCAL);
  EXPECT_TRUE(ok_restore);
  EXPECT_EQ(state_.GetIntFormat(), original);
}

}  // namespace