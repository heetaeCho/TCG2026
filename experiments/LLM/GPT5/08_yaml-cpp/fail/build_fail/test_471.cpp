// TEST_ID: 471
// File: emitterstate_setnoncontent_test_471.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/emitterstate.h"  // adjust include path if your build uses <yaml-cpp/emitterstate.h>

namespace {

class EmitterStateTest_471 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateTest_471, SetNonContent_DoesNotThrowOnFreshState_471) {
  EXPECT_NO_THROW(state.SetNonContent());
}

TEST_F(EmitterStateTest_471, SetNonContent_IsIdempotent_NoThrowOnRepeatedCalls_471) {
  EXPECT_NO_THROW(state.SetNonContent());
  EXPECT_NO_THROW(state.SetNonContent());
  EXPECT_NO_THROW(state.SetNonContent());
}

TEST_F(EmitterStateTest_471, SetNonContent_DoesNotPreventBasicQueryMethods_471) {
  ASSERT_NO_THROW(state.SetNonContent());

  // We intentionally do NOT assert specific return values (black-box).
  EXPECT_NO_THROW((void)state.good());
  EXPECT_NO_THROW((void)state.GetLastError());
  EXPECT_NO_THROW((void)state.CurIndent());

  EXPECT_NO_THROW((void)state.HasAnchor());
  EXPECT_NO_THROW((void)state.HasAlias());
  EXPECT_NO_THROW((void)state.HasTag());
  EXPECT_NO_THROW((void)state.HasBegunNode());
  EXPECT_NO_THROW((void)state.HasBegunContent());

  EXPECT_NO_THROW((void)state.GetOutputCharset());
  EXPECT_NO_THROW((void)state.GetStringFormat());
  EXPECT_NO_THROW((void)state.GetBoolFormat());
  EXPECT_NO_THROW((void)state.GetBoolLengthFormat());
  EXPECT_NO_THROW((void)state.GetBoolCaseFormat());
  EXPECT_NO_THROW((void)state.GetNullFormat());
  EXPECT_NO_THROW((void)state.GetIntFormat());
  EXPECT_NO_THROW((void)state.GetIndent());
  EXPECT_NO_THROW((void)state.GetPreCommentIndent());
  EXPECT_NO_THROW((void)state.GetPostCommentIndent());
  EXPECT_NO_THROW((void)state.GetMapKeyFormat());
  EXPECT_NO_THROW((void)state.GetFloatPrecision());
  EXPECT_NO_THROW((void)state.GetDoublePrecision());
}

TEST_F(EmitterStateTest_471, SetNonContent_NoThrowAcrossDocumentLifecycleCalls_471) {
  EXPECT_NO_THROW(state.StartedDoc());
  EXPECT_NO_THROW(state.SetNonContent());
  EXPECT_NO_THROW(state.StartedScalar());
  EXPECT_NO_THROW(state.SetNonContent());
  EXPECT_NO_THROW(state.EndedDoc());
}

TEST_F(EmitterStateTest_471, SetNonContent_NoThrowAfterErrorIsSet_471) {
  EXPECT_NO_THROW(state.SetError("synthetic error for testing"));
  EXPECT_NO_THROW(state.SetNonContent());

  // Only verify that observable queries remain callable.
  EXPECT_NO_THROW((void)state.good());
  EXPECT_NO_THROW((void)state.GetLastError());
}

}  // namespace