// TEST_ID: 462
#include <gtest/gtest.h>

#include <cstddef>
#include <limits>

#include "emitterstate.h"

namespace {

class EmitterStateTest_462 : public ::testing::Test {
 protected:
  YAML::EmitterState state;

  // Finds a scope value that the implementation accepts (returns true).
  // This avoids hard-coding enum constants that may differ across versions.
  static YAML::FmtScope::value FindAnyValidScopeOrFail(YAML::EmitterState& s,
                                                      std::size_t probeValue) {
    for (int i = 0; i <= 10; ++i) {
      auto scope = static_cast<YAML::FmtScope::value>(i);
      if (s.SetPostCommentIndent(probeValue, scope)) {
        return scope;
      }
    }
    ADD_FAILURE() << "Could not find any valid YAML::FmtScope::value for SetPostCommentIndent";
    return static_cast<YAML::FmtScope::value>(0);
  }
};

}  // namespace

TEST_F(EmitterStateTest_462, GetPostCommentIndent_IsStableAcrossCalls_462) {
  const std::size_t first = state.GetPostCommentIndent();
  const std::size_t second = state.GetPostCommentIndent();
  const std::size_t third = state.GetPostCommentIndent();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(EmitterStateTest_462, SetPostCommentIndent_WhenAccepted_UpdatesGetter_462) {
  // Pick a scope the implementation accepts.
  const std::size_t v1 = 0;
  const auto validScope = FindAnyValidScopeOrFail(state, v1);
  ASSERT_EQ(state.GetPostCommentIndent(), v1);

  // Update to a non-zero value.
  const std::size_t v2 = 7;
  ASSERT_TRUE(state.SetPostCommentIndent(v2, validScope));
  EXPECT_EQ(state.GetPostCommentIndent(), v2);

  // Boundary-ish value.
  const std::size_t v3 = std::numeric_limits<std::size_t>::max();
  ASSERT_TRUE(state.SetPostCommentIndent(v3, validScope));
  EXPECT_EQ(state.GetPostCommentIndent(), v3);
}

TEST_F(EmitterStateTest_462, SetPostCommentIndent_InvalidScope_DoesNotChangeValue_462) {
  // Establish a known value using any accepted scope.
  const std::size_t known = 3;
  const auto validScope = FindAnyValidScopeOrFail(state, known);
  ASSERT_EQ(state.GetPostCommentIndent(), known);

  // Try an obviously out-of-range scope.
  const auto invalidScope = static_cast<YAML::FmtScope::value>(999);
  const bool ok = state.SetPostCommentIndent(11, invalidScope);

  // Observable error case: if rejected, it should not change the getter.
  if (!ok) {
    EXPECT_EQ(state.GetPostCommentIndent(), known);
  } else {
    // If the implementation happens to accept this value, at least verify the update is observable.
    EXPECT_EQ(state.GetPostCommentIndent(), 11u);
  }

  // Confirm that valid scope still works afterward.
  ASSERT_TRUE(state.SetPostCommentIndent(5, validScope));
  EXPECT_EQ(state.GetPostCommentIndent(), 5u);
}