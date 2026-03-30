// TEST_ID: 467
#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/emitterstate.h"

// If your build exposes these via a different header (e.g., yaml-cpp/emittermanip.h),
// adjust includes accordingly.
#include "TestProjects/yaml-cpp/include/yaml-cpp/emittermanip.h"

namespace {

using YAML::EmitterState;
using YAML::EMITTER_MANIP;

static void ApplyLocalValueManually(EmitterState& st, EMITTER_MANIP value) {
  // Mirrors the provided implementation of EmitterState::SetLocalValue(value)
  // without inferring any internal logic beyond the explicit call sequence.
  st.SetOutputCharset(value, YAML::FmtScope::Local);
  st.SetStringFormat(value, YAML::FmtScope::Local);
  st.SetBoolFormat(value, YAML::FmtScope::Local);
  st.SetBoolCaseFormat(value, YAML::FmtScope::Local);
  st.SetBoolLengthFormat(value, YAML::FmtScope::Local);
  st.SetNullFormat(value, YAML::FmtScope::Local);
  st.SetIntFormat(value, YAML::FmtScope::Local);
  st.SetFlowType(YAML::GroupType::Seq, value, YAML::FmtScope::Local);
  st.SetFlowType(YAML::GroupType::Map, value, YAML::FmtScope::Local);
  st.SetMapKeyFormat(value, YAML::FmtScope::Local);
}

static void ExpectCoreSettingsEqual(const EmitterState& a, const EmitterState& b) {
  EXPECT_EQ(a.good(), b.good());
  EXPECT_EQ(a.GetLastError(), b.GetLastError());

  EXPECT_EQ(a.GetOutputCharset(), b.GetOutputCharset());
  EXPECT_EQ(a.GetStringFormat(), b.GetStringFormat());
  EXPECT_EQ(a.GetBoolFormat(), b.GetBoolFormat());
  EXPECT_EQ(a.GetBoolCaseFormat(), b.GetBoolCaseFormat());
  EXPECT_EQ(a.GetBoolLengthFormat(), b.GetBoolLengthFormat());
  EXPECT_EQ(a.GetNullFormat(), b.GetNullFormat());
  EXPECT_EQ(a.GetIntFormat(), b.GetIntFormat());

  EXPECT_EQ(a.GetFlowType(YAML::GroupType::Seq), b.GetFlowType(YAML::GroupType::Seq));
  EXPECT_EQ(a.GetFlowType(YAML::GroupType::Map), b.GetFlowType(YAML::GroupType::Map));

  EXPECT_EQ(a.GetMapKeyFormat(), b.GetMapKeyFormat());

  // These are "unrelated" to SetLocalValue per the provided code, but comparing them
  // helps ensure SetLocalValue doesn't have unexpected observable side-effects.
  EXPECT_EQ(a.GetIndent(), b.GetIndent());
  EXPECT_EQ(a.GetPreCommentIndent(), b.GetPreCommentIndent());
  EXPECT_EQ(a.GetPostCommentIndent(), b.GetPostCommentIndent());
  EXPECT_EQ(a.GetFloatPrecision(), b.GetFloatPrecision());
  EXPECT_EQ(a.GetDoublePrecision(), b.GetDoublePrecision());

  EXPECT_EQ(a.CurIndent(), b.CurIndent());
  EXPECT_EQ(a.HasAnchor(), b.HasAnchor());
  EXPECT_EQ(a.HasAlias(), b.HasAlias());
  EXPECT_EQ(a.HasTag(), b.HasTag());
  EXPECT_EQ(a.HasBegunNode(), b.HasBegunNode());
  EXPECT_EQ(a.HasBegunContent(), b.HasBegunContent());
}

}  // namespace

class EmitterStateTest_467 : public ::testing::Test {};

TEST_F(EmitterStateTest_467, SetLocalValueMatchesManualApplication_Auto_467) {
  EmitterState via_api;
  EmitterState via_manual;

  // Use a commonly-supported manipulator that typically represents "default/auto".
  const EMITTER_MANIP value = YAML::Auto;

  EXPECT_NO_THROW(via_api.SetLocalValue(value));
  EXPECT_NO_THROW(ApplyLocalValueManually(via_manual, value));

  ExpectCoreSettingsEqual(via_api, via_manual);
}

TEST_F(EmitterStateTest_467, SetLocalValueMatchesManualApplication_Flow_467) {
  EmitterState via_api;
  EmitterState via_manual;

  // Even if a value is only meaningful for some settings, SetLocalValue should behave
  // identically to invoking the same setters with the same arguments in the same order.
  const EMITTER_MANIP value = YAML::Flow;

  EXPECT_NO_THROW(via_api.SetLocalValue(value));
  EXPECT_NO_THROW(ApplyLocalValueManually(via_manual, value));

  ExpectCoreSettingsEqual(via_api, via_manual);
}

TEST_F(EmitterStateTest_467, SetLocalValueMatchesManualApplication_Block_467) {
  EmitterState via_api;
  EmitterState via_manual;

  const EMITTER_MANIP value = YAML::Block;

  EXPECT_NO_THROW(via_api.SetLocalValue(value));
  EXPECT_NO_THROW(ApplyLocalValueManually(via_manual, value));

  ExpectCoreSettingsEqual(via_api, via_manual);
}

TEST_F(EmitterStateTest_467, RepeatedSetLocalValueMatchesRepeatedManualApplication_467) {
  EmitterState via_api;
  EmitterState via_manual;

  const EMITTER_MANIP first = YAML::Auto;
  const EMITTER_MANIP second = YAML::Block;

  EXPECT_NO_THROW(via_api.SetLocalValue(first));
  EXPECT_NO_THROW(via_api.SetLocalValue(second));

  EXPECT_NO_THROW(ApplyLocalValueManually(via_manual, first));
  EXPECT_NO_THROW(ApplyLocalValueManually(via_manual, second));

  ExpectCoreSettingsEqual(via_api, via_manual);
}

TEST_F(EmitterStateTest_467, SetLocalValueWithOutOfRangeValueMatchesManualApplication_467) {
  EmitterState via_api;
  EmitterState via_manual;

  // Boundary / exceptional-style input: an out-of-range enum value.
  // We do not assume whether it is accepted or rejected; we only require that
  // SetLocalValue's observable outcome matches the manual application of the same calls.
  const EMITTER_MANIP invalid = static_cast<EMITTER_MANIP>(-1);

  EXPECT_NO_THROW(via_api.SetLocalValue(invalid));
  EXPECT_NO_THROW(ApplyLocalValueManually(via_manual, invalid));

  ExpectCoreSettingsEqual(via_api, via_manual);
}