// File: emitterstate_getnullformat_test_458.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/emitterstate.h"

namespace {

class EmitterStateGetNullFormatTest_458 : public ::testing::Test {
 protected:
  YAML::EmitterState state_;
};

TEST_F(EmitterStateGetNullFormatTest_458, ReturnsSameValueAcrossRepeatedCalls_458) {
  const auto first = state_.GetNullFormat();
  const auto second = state_.GetNullFormat();

  // Observable behavior: repeated calls should be stable (no mutation visible via return value).
  EXPECT_EQ(first, second);
}

TEST_F(EmitterStateGetNullFormatTest_458, CallableOnConstObject_458) {
  const YAML::EmitterState& const_state = state_;

  const auto v1 = const_state.GetNullFormat();
  const auto v2 = const_state.GetNullFormat();

  EXPECT_EQ(v1, v2);
}

TEST_F(EmitterStateGetNullFormatTest_458, DoesNotChangeOtherObservableState_458) {
  // We do not assume any specific default values; we only assert "no change" across the call.
  const bool good_before = state_.good();
  const std::string err_before = state_.GetLastError();

  (void)state_.GetNullFormat();

  EXPECT_EQ(state_.good(), good_before);
  EXPECT_EQ(state_.GetLastError(), err_before);
}

TEST_F(EmitterStateGetNullFormatTest_458, DoesNotChangeNullFormatAfterOtherQueries_458) {
  // Ensure other (read-only) queries don't affect the returned null format.
  const auto before = state_.GetNullFormat();

  (void)state_.good();
  (void)state_.GetLastError();
  (void)state_.CurIndent();
  (void)state_.HasAnchor();
  (void)state_.HasAlias();
  (void)state_.HasTag();
  (void)state_.HasBegunNode();
  (void)state_.HasBegunContent();

  const auto after = state_.GetNullFormat();
  EXPECT_EQ(before, after);
}

}  // namespace