// TEST_ID: 465
#include <gtest/gtest.h>

#include <cstddef>
#include <limits>

#include "emitterstate.h"

namespace {

class EmitterStateDoublePrecisionTest_465 : public ::testing::Test {
protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateDoublePrecisionTest_465, GetDoublePrecision_DefaultIsStableAcrossCalls_465) {
  const std::size_t first = state.GetDoublePrecision();
  const std::size_t second = state.GetDoublePrecision();
  EXPECT_EQ(first, second);
}

TEST_F(EmitterStateDoublePrecisionTest_465, GetDoublePrecision_AfterSetIfSetterSucceedsReflectsNewValue_465) {
  const std::size_t before = state.GetDoublePrecision();

  const std::size_t desired = before + 1u;  // any different value (wrap not expected for size_t+1)
  const auto scope0 = static_cast<YAML::FmtScope::value>(0);

  const bool ok = state.SetDoublePrecision(desired, scope0);

  if (ok) {
    EXPECT_EQ(state.GetDoublePrecision(), desired);
  } else {
    // Black-box friendly: if the setter rejects the input/scope, the getter should remain unchanged.
    EXPECT_EQ(state.GetDoublePrecision(), before);
  }
}

TEST_F(EmitterStateDoublePrecisionTest_465, SetDoublePrecision_BoundaryValues_ZeroOneMax_465) {
  const auto scope0 = static_cast<YAML::FmtScope::value>(0);

  std::size_t expected = state.GetDoublePrecision();

  const std::size_t candidates[] = {
      static_cast<std::size_t>(0),
      static_cast<std::size_t>(1),
      std::numeric_limits<std::size_t>::max(),
  };

  for (const std::size_t v : candidates) {
    const bool ok = state.SetDoublePrecision(v, scope0);
    if (ok) expected = v;

    EXPECT_EQ(state.GetDoublePrecision(), expected)
        << "Getter should reflect the last demonstrated successful SetDoublePrecision() call";
  }
}

TEST_F(EmitterStateDoublePrecisionTest_465, SetDoublePrecision_DifferentScopesDoNotBreakGetterConsistency_465) {
  const std::size_t before = state.GetDoublePrecision();

  // We intentionally avoid assuming specific enum constants exist (e.g., LOCAL/GLOBAL).
  const auto scope0 = static_cast<YAML::FmtScope::value>(0);
  const auto scope1 = static_cast<YAML::FmtScope::value>(1);

  const std::size_t v0 = before + 2u;
  const std::size_t v1 = before + 3u;

  const bool ok0 = state.SetDoublePrecision(v0, scope0);
  const std::size_t after0 = state.GetDoublePrecision();

  if (ok0) {
    EXPECT_EQ(after0, v0);
  } else {
    EXPECT_EQ(after0, before);
  }

  const bool ok1 = state.SetDoublePrecision(v1, scope1);
  const std::size_t after1 = state.GetDoublePrecision();

  if (ok1) {
    EXPECT_EQ(after1, v1);
  } else {
    // If the second call fails, we should still observe the previously observable state.
    EXPECT_EQ(after1, after0);
  }

  // Sanity: repeated reads should match (no hidden side effects from the getter).
  EXPECT_EQ(state.GetDoublePrecision(), after1);
}

}  // namespace