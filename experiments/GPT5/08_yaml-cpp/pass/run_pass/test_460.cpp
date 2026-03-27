// File: ./TestProjects/yaml-cpp/test/emitterstate_getindent_test_460.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <limits>

#include "TestProjects/yaml-cpp/src/emitterstate.h"

namespace {

YAML::FmtScope::value Scope0() {
  // Avoid depending on specific enumerator names (treat as black box).
  return static_cast<YAML::FmtScope::value>(0);
}

YAML::FmtScope::value Scope1() {
  // Some builds may treat this as another valid scope (e.g., "Global").
  return static_cast<YAML::FmtScope::value>(1);
}

}  // namespace

class EmitterStateGetIndentTest_460 : public ::testing::Test {
 protected:
  YAML::EmitterState state_;
};

TEST_F(EmitterStateGetIndentTest_460, DefaultConstructed_GetIndentIsStable_460) {
  const std::size_t first = state_.GetIndent();
  const std::size_t second = state_.GetIndent();
  EXPECT_EQ(first, second);
}

TEST_F(EmitterStateGetIndentTest_460, SetIndent_ToZero_ReflectedInGetIndentWhenAccepted_460) {
  const std::size_t before = state_.GetIndent();

  const bool ok = state_.SetIndent(0u, Scope0());
  const std::size_t after = state_.GetIndent();

  if (ok) {
    EXPECT_EQ(after, 0u);
  } else {
    // If the implementation rejects the change (scope/value), observable state should remain unchanged.
    EXPECT_EQ(after, before);
  }
}

TEST_F(EmitterStateGetIndentTest_460, SetIndent_ToOne_ReflectedInGetIndentWhenAccepted_460) {
  const std::size_t before = state_.GetIndent();

  const bool ok = state_.SetIndent(1u, Scope0());
  const std::size_t after = state_.GetIndent();

  if (ok) {
    EXPECT_EQ(after, 1u);
  } else {
    EXPECT_EQ(after, before);
  }
}

TEST_F(EmitterStateGetIndentTest_460, SetIndent_ToMaxSizeT_ReflectedInGetIndentWhenAccepted_460) {
  const std::size_t before = state_.GetIndent();
  const std::size_t maxv = (std::numeric_limits<std::size_t>::max)();

  const bool ok = state_.SetIndent(maxv, Scope0());
  const std::size_t after = state_.GetIndent();

  if (ok) {
    EXPECT_EQ(after, maxv);
  } else {
    EXPECT_EQ(after, before);
  }
}

TEST_F(EmitterStateGetIndentTest_460, SetIndent_SameValueTwice_DoesNotChangeResult_460) {
  // First, attempt to set a known value. If rejected, we can still validate stability.
  const std::size_t target = 2u;
  const std::size_t before = state_.GetIndent();

  const bool ok1 = state_.SetIndent(target, Scope0());
  const std::size_t mid = state_.GetIndent();

  if (ok1) {
    EXPECT_EQ(mid, target);
  } else {
    EXPECT_EQ(mid, before);
  }

  const bool ok2 = state_.SetIndent(target, Scope0());
  const std::size_t after = state_.GetIndent();

  // Regardless of whether the second call reports success, observable indent should remain consistent.
  if (ok1) {
    EXPECT_EQ(after, target);
  } else {
    // If we never managed to set it, it should still be whatever it was.
    EXPECT_EQ(after, before);
  }

  (void)ok2;  // success/failure is implementation-defined; behavior is checked via GetIndent().
}

TEST_F(EmitterStateGetIndentTest_460, SetIndent_WithAlternateScope_EitherChangesOrIsRejectedWithoutSideEffects_460) {
  const std::size_t before = state_.GetIndent();
  const std::size_t target = 4u;

  const bool ok = state_.SetIndent(target, Scope1());
  const std::size_t after = state_.GetIndent();

  if (ok) {
    EXPECT_EQ(after, target);
  } else {
    EXPECT_EQ(after, before);
  }
}