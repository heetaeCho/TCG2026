// File: ./TestProjects/yaml-cpp/test/emitterstate_setpostcommentindent_test.cpp

#include <gtest/gtest.h>

#include <limits>

#include "yaml-cpp/src/emitterstate.h"

namespace {

class EmitterStateTest_498 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateTest_498, SetPostCommentIndentNonZeroReturnsTrueAndIsObservableViaGetter_498) {
  struct Case {
    YAML::FmtScope::value scope;
    std::size_t value;
  };

  const Case kCases[] = {
      {YAML::FmtScope::Local, 1u},
      {YAML::FmtScope::Local, 4u},
      {YAML::FmtScope::Global, 2u},
      {YAML::FmtScope::Global, 8u},
  };

  for (const auto& tc : kCases) {
    SCOPED_TRACE(tc.value);
    SCOPED_TRACE(static_cast<int>(tc.scope));

    EXPECT_TRUE(state.SetPostCommentIndent(tc.value, tc.scope));
    EXPECT_EQ(state.GetPostCommentIndent(), tc.value);
  }
}

TEST_F(EmitterStateTest_498, SetPostCommentIndentZeroReturnsFalseAndDoesNotChangeExistingValue_498) {
  ASSERT_TRUE(state.SetPostCommentIndent(3u, YAML::FmtScope::Local));
  ASSERT_EQ(state.GetPostCommentIndent(), 3u);

  EXPECT_FALSE(state.SetPostCommentIndent(0u, YAML::FmtScope::Local));
  EXPECT_EQ(state.GetPostCommentIndent(), 3u);

  // Also verify with another scope to ensure the failure behavior is consistent.
  ASSERT_TRUE(state.SetPostCommentIndent(5u, YAML::FmtScope::Global));
  ASSERT_EQ(state.GetPostCommentIndent(), 5u);

  EXPECT_FALSE(state.SetPostCommentIndent(0u, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetPostCommentIndent(), 5u);
}

TEST_F(EmitterStateTest_498, SetPostCommentIndentAcceptsMaxSizeT_498) {
  const std::size_t kMax = (std::numeric_limits<std::size_t>::max)();

  EXPECT_TRUE(state.SetPostCommentIndent(kMax, YAML::FmtScope::Local));
  EXPECT_EQ(state.GetPostCommentIndent(), kMax);
}

}  // namespace