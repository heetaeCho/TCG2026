// File: ./TestProjects/yaml-cpp/test/emitterstate_setprecommentindent_test.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <limits>

#include "yaml-cpp/emitterstate.h"

namespace {

class EmitterStateTest_497 : public ::testing::Test {
 protected:
  YAML::EmitterState state;

  // We intentionally avoid assuming specific enumerator names for FmtScope.
  // Using explicit casts keeps the tests focused on observable behavior.
  static constexpr YAML::FmtScope::value Scope0() {
    return static_cast<YAML::FmtScope::value>(0);
  }
  static constexpr YAML::FmtScope::value Scope1() {
    return static_cast<YAML::FmtScope::value>(1);
  }
};

TEST_F(EmitterStateTest_497, SetPreCommentIndentRejectsZeroAndDoesNotChangeValue_497) {
  const std::size_t before = state.GetPreCommentIndent();

  EXPECT_FALSE(state.SetPreCommentIndent(0u, Scope0()));
  EXPECT_EQ(state.GetPreCommentIndent(), before);

  // Also try a different scope value to ensure consistent observable behavior.
  EXPECT_FALSE(state.SetPreCommentIndent(0u, Scope1()));
  EXPECT_EQ(state.GetPreCommentIndent(), before);
}

TEST_F(EmitterStateTest_497, SetPreCommentIndentAcceptsNonZeroAndUpdatesGetter_497) {
  EXPECT_TRUE(state.SetPreCommentIndent(1u, Scope0()));
  EXPECT_EQ(state.GetPreCommentIndent(), 1u);

  EXPECT_TRUE(state.SetPreCommentIndent(4u, Scope0()));
  EXPECT_EQ(state.GetPreCommentIndent(), 4u);
}

TEST_F(EmitterStateTest_497, SetPreCommentIndentMultipleCallsLastWriteWins_497) {
  EXPECT_TRUE(state.SetPreCommentIndent(2u, Scope0()));
  EXPECT_EQ(state.GetPreCommentIndent(), 2u);

  EXPECT_TRUE(state.SetPreCommentIndent(3u, Scope0()));
  EXPECT_EQ(state.GetPreCommentIndent(), 3u);

  // Ensure a rejected update does not overwrite the last successful value.
  EXPECT_FALSE(state.SetPreCommentIndent(0u, Scope0()));
  EXPECT_EQ(state.GetPreCommentIndent(), 3u);
}

TEST_F(EmitterStateTest_497, SetPreCommentIndentAcceptsMaxSizeTValue_497) {
  const std::size_t maxv = (std::numeric_limits<std::size_t>::max)();

  EXPECT_TRUE(state.SetPreCommentIndent(maxv, Scope0()));
  EXPECT_EQ(state.GetPreCommentIndent(), maxv);
}

TEST_F(EmitterStateTest_497, SetPreCommentIndentWithDifferentScopesIsObservableAndNonFailing_497) {
  // This test does not assume what "scope" means internally; it only checks
  // that valid (non-zero) inputs are accepted and reflected by the public getter.
  EXPECT_TRUE(state.SetPreCommentIndent(5u, Scope0()));
  EXPECT_EQ(state.GetPreCommentIndent(), 5u);

  EXPECT_TRUE(state.SetPreCommentIndent(6u, Scope1()));
  EXPECT_EQ(state.GetPreCommentIndent(), 6u);
}

}  // namespace