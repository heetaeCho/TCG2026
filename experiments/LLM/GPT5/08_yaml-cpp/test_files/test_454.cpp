// TEST_ID: 454
#include <gtest/gtest.h>

#include <type_traits>

#include "TestProjects/yaml-cpp/src/emitterstate.h"

namespace {

template <typename Manip>
Manip MakeDifferentManip(Manip base) {
  if constexpr (std::is_enum_v<Manip>) {
    using U = std::underlying_type_t<Manip>;
    U u = static_cast<U>(base);
    return static_cast<Manip>(u + static_cast<U>(1));
  } else if constexpr (std::is_integral_v<Manip>) {
    return static_cast<Manip>(base + 1);
  } else {
    // If EMITTER_MANIP is not enum/integral, we can't reliably synthesize
    // a different value without assuming internal details.
    return base;
  }
}

}  // namespace

namespace YAML {

class EmitterStateTest_454 : public ::testing::Test {};

TEST_F(EmitterStateTest_454, GetStringFormat_IsStableAcrossCalls_454) {
  EmitterState state;

  const auto v1 = state.GetStringFormat();
  const auto v2 = state.GetStringFormat();

  EXPECT_EQ(v1, v2);
}

TEST_F(EmitterStateTest_454, GetStringFormat_CanBeCalledOnConstObject_454) {
  EmitterState state;
  const EmitterState& cstate = state;

  const auto v1 = cstate.GetStringFormat();
  const auto v2 = cstate.GetStringFormat();

  EXPECT_EQ(v1, v2);
}

TEST_F(EmitterStateTest_454, GetStringFormat_ReflectsSuccessfulSetStringFormatIfSetterExists_454) {
  EmitterState state;

  const auto before = state.GetStringFormat();
  const auto candidate = MakeDifferentManip(before);

  // If we couldn't create a different candidate (non-enum/non-integral),
  // we can still validate "setting to same value does not change it" behavior.
  const auto desired = candidate;

  // NOTE: We do not assume which scope values exist beyond what the header provides.
  // yaml-cpp typically exposes FmtScope::LOCAL / FmtScope::GLOBAL. If your project
  // uses different enumerators, adjust accordingly.
  const bool ok = state.SetStringFormat(desired, FmtScope::LOCAL);

  const auto after = state.GetStringFormat();
  if (ok) {
    EXPECT_EQ(after, desired);
  } else {
    // If the setter rejects the value, the observable expectation is that the
    // getter remains unchanged.
    EXPECT_EQ(after, before);
  }
}

TEST_F(EmitterStateTest_454, GetStringFormat_SetStringFormatWithClearlyInvalidValueDoesNotCorruptState_454) {
  EmitterState state;

  const auto before = state.GetStringFormat();

  using Manip = decltype(before);
  Manip invalid = before;
  if constexpr (std::is_enum_v<Manip>) {
    using U = std::underlying_type_t<Manip>;
    invalid = static_cast<Manip>(static_cast<U>(before) - static_cast<U>(1));
  } else if constexpr (std::is_integral_v<Manip>) {
    invalid = static_cast<Manip>(before - 1);
  } else {
    // Can't manufacture "invalid" without assumptions; keep same value.
    invalid = before;
  }

  const bool ok = state.SetStringFormat(invalid, FmtScope::LOCAL);
  const auto after = state.GetStringFormat();

  if (ok) {
    // If it accepts it, the getter should reflect it.
    EXPECT_EQ(after, invalid);
  } else {
    // If it rejects it, the getter should stay stable.
    EXPECT_EQ(after, before);
  }
}

}  // namespace YAML