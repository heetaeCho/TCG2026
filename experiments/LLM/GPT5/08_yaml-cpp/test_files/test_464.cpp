// TEST_ID: 464
#include <gtest/gtest.h>

#include <cstddef>
#include <limits>

#include "emitterstate.h"

namespace {

class EmitterStateTest_464 : public ::testing::Test {
protected:
  YAML::EmitterState state_;
};

TEST_F(EmitterStateTest_464, GetFloatPrecision_IsStableAcrossCalls_464) {
  const std::size_t p1 = state_.GetFloatPrecision();
  const std::size_t p2 = state_.GetFloatPrecision();
  EXPECT_EQ(p1, p2);
}

TEST_F(EmitterStateTest_464, GetFloatPrecision_WorksOnConstObject_464) {
  const YAML::EmitterState& const_state = state_;
  (void)const_state.GetFloatPrecision();  // Should be callable and not crash.
}

TEST_F(EmitterStateTest_464, SetFloatPrecision_LocalScope_UpdatesGetterWhenAccepted_464) {
  const std::size_t before = state_.GetFloatPrecision();
  const std::size_t desired = before + 1;

  const bool ok = state_.SetFloatPrecision(desired, YAML::FmtScope::Local);

  if (ok) {
    EXPECT_EQ(desired, state_.GetFloatPrecision());
  } else {
    // If the implementation rejects the value/scope, precision should remain unchanged.
    EXPECT_EQ(before, state_.GetFloatPrecision());
  }
}

TEST_F(EmitterStateTest_464, SetFloatPrecision_ZeroValue_BehaviorObservableViaGetter_464) {
  const std::size_t before = state_.GetFloatPrecision();
  const std::size_t desired = 0;

  const bool ok = state_.SetFloatPrecision(desired, YAML::FmtScope::Local);

  if (ok) {
    EXPECT_EQ(desired, state_.GetFloatPrecision());
  } else {
    EXPECT_EQ(before, state_.GetFloatPrecision());
  }
}

TEST_F(EmitterStateTest_464, SetFloatPrecision_MaxSizeT_BehaviorObservableViaGetter_464) {
  const std::size_t before = state_.GetFloatPrecision();
  const std::size_t desired = (std::numeric_limits<std::size_t>::max)();

  const bool ok = state_.SetFloatPrecision(desired, YAML::FmtScope::Local);

  if (ok) {
    EXPECT_EQ(desired, state_.GetFloatPrecision());
  } else {
    EXPECT_EQ(before, state_.GetFloatPrecision());
  }
}

TEST_F(EmitterStateTest_464, SetFloatPrecision_RepeatedUpdates_LastAcceptedValueReflected_464) {
  const std::size_t before = state_.GetFloatPrecision();

  const std::size_t v1 = before + 2;
  const bool ok1 = state_.SetFloatPrecision(v1, YAML::FmtScope::Local);
  const std::size_t after1 = state_.GetFloatPrecision();
  if (ok1) EXPECT_EQ(v1, after1);
  else EXPECT_EQ(before, after1);

  const std::size_t v2 = before + 3;
  const bool ok2 = state_.SetFloatPrecision(v2, YAML::FmtScope::Local);
  const std::size_t after2 = state_.GetFloatPrecision();
  if (ok2) EXPECT_EQ(v2, after2);
  else EXPECT_EQ(after1, after2);
}

}  // namespace