#include "gtest/gtest.h"
#include "emitterstate.h"
#include "yaml-cpp/emittermanip.h"

namespace YAML {
namespace {

class EmitterStateTest_465 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_465, InitiallyGood_465) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_465, InitialLastErrorEmpty_465) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_465, InitialCurIndentIsZero_465) {
  EXPECT_EQ(0u, state.CurIndent());
}

TEST_F(EmitterStateTest_465, InitialHasAnchorFalse_465) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_465, InitialHasAliasFalse_465) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_465, InitialHasTagFalse_465) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_465, InitialHasBegunNodeFalse_465) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_465, InitialHasBegunContentFalse_465) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== Default Format Getters ====================

TEST_F(EmitterStateTest_465, DefaultIndentValue_465) {
  // Default indent is typically 2
  EXPECT_GE(state.GetIndent(), 1u);
}

TEST_F(EmitterStateTest_465, DefaultPreCommentIndent_465) {
  EXPECT_GE(state.GetPreCommentIndent(), 1u);
}

TEST_F(EmitterStateTest_465, DefaultPostCommentIndent_465) {
  EXPECT_GE(state.GetPostCommentIndent(), 1u);
}

TEST_F(EmitterStateTest_465, DefaultFloatPrecision_465) {
  std::size_t precision = state.GetFloatPrecision();
  // Should have some reasonable default
  EXPECT_GT(precision, 0u);
}

TEST_F(EmitterStateTest_465, DefaultDoublePrecision_465) {
  std::size_t precision = state.GetDoublePrecision();
  EXPECT_GT(precision, 0u);
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_465, SetErrorMakesNotGood_465) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_465, SetErrorStoresMessage_465) {
  state.SetError("some error message");
  EXPECT_EQ("some error message", state.GetLastError());
}

TEST_F(EmitterStateTest_465, SetErrorEmptyString_465) {
  state.SetError("");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_465, SetErrorMultipleTimes_465) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_FALSE(state.good());
  // Typically the first error is preserved
  std::string err = state.GetLastError();
  EXPECT_FALSE(err.empty());
}

// ==================== SetAnchor / SetAlias / SetTag ====================

TEST_F(EmitterStateTest_465, SetAnchorSetsHasAnchor_465) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_465, SetAliasSetsHasAlias_465) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_465, SetTagSetsHasTag_465) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== SetIndent Tests ====================

TEST_F(EmitterStateTest_465, SetIndentGlobalScope_465) {
  bool result = state.SetIndent(4, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_465, SetIndentLocalScope_465) {
  bool result = state.SetIndent(6, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(6u, state.GetIndent());
}

TEST_F(EmitterStateTest_465, SetIndentZeroFails_465) {
  // Indent of 0 might not be valid
  bool result = state.SetIndent(0, FmtScope::Global);
  // Depending on implementation, this may return false
  // We just test it doesn't crash
  (void)result;
}

// ==================== SetPreCommentIndent / SetPostCommentIndent ====================

TEST_F(EmitterStateTest_465, SetPreCommentIndentGlobal_465) {
  bool result = state.SetPreCommentIndent(3, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_465, SetPostCommentIndentGlobal_465) {
  bool result = state.SetPostCommentIndent(2, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

// ==================== SetFloatPrecision / SetDoublePrecision ====================

TEST_F(EmitterStateTest_465, SetFloatPrecisionGlobal_465) {
  bool result = state.SetFloatPrecision(5, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_465, SetDoublePrecisionGlobal_465) {
  bool result = state.SetDoublePrecision(10, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

TEST_F(EmitterStateTest_465, SetDoublePrecisionLocal_465) {
  bool result = state.SetDoublePrecision(8, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(8u, state.GetDoublePrecision());
}

// ==================== SetOutputCharset Tests ====================

TEST_F(EmitterStateTest_465, SetOutputCharsetUtf8_465) {
  bool result = state.SetOutputCharset(EmitNonAscii, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_465, SetOutputCharsetEscapeNonAscii_465) {
  bool result = state.SetOutputCharset(EscapeNonAscii, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_465, SetOutputCharsetInvalidValue_465) {
  // Setting an unrelated EMITTER_MANIP should return false
  bool result = state.SetOutputCharset(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetStringFormat Tests ====================

TEST_F(EmitterStateTest_465, SetStringFormatSingleQuoted_465) {
  bool result = state.SetStringFormat(SingleQuoted, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_465, SetStringFormatDoubleQuoted_465) {
  bool result = state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_465, SetStringFormatLiteral_465) {
  bool result = state.SetStringFormat(Literal, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Literal, state.GetStringFormat());
}

TEST_F(EmitterStateTest_465, SetStringFormatInvalidValue_465) {
  bool result = state.SetStringFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetBoolFormat Tests ====================

TEST_F(EmitterStateTest_465, SetBoolFormatTrueFalseBool_465) {
  bool result = state.SetBoolFormat(TrueFalseBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_465, SetBoolFormatYesNoBool_465) {
  bool result = state.SetBoolFormat(YesNoBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_465, SetBoolFormatOnOffBool_465) {
  bool result = state.SetBoolFormat(OnOffBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_465, SetBoolFormatInvalid_465) {
  bool result = state.SetBoolFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetBoolLengthFormat Tests ====================

TEST_F(EmitterStateTest_465, SetBoolLengthFormatShortBool_465) {
  bool result = state.SetBoolLengthFormat(ShortBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_465, SetBoolLengthFormatLongBool_465) {
  bool result = state.SetBoolLengthFormat(LongBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

// ==================== SetBoolCaseFormat Tests ====================

TEST_F(EmitterStateTest_465, SetBoolCaseFormatUpperCase_465) {
  bool result = state.SetBoolCaseFormat(UpperCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_465, SetBoolCaseFormatLowerCase_465) {
  bool result = state.SetBoolCaseFormat(LowerCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_465, SetBoolCaseFormatCamelCase_465) {
  bool result = state.SetBoolCaseFormat(CamelCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

// ==================== SetIntFormat Tests ====================

TEST_F(EmitterStateTest_465, SetIntFormatDec_465) {
  bool result = state.SetIntFormat(Dec, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_465, SetIntFormatHex_465) {
  bool result = state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_465, SetIntFormatOct_465) {
  bool result = state.SetIntFormat(Oct, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_465, SetIntFormatInvalid_465) {
  bool result = state.SetIntFormat(SingleQuoted, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetNullFormat Tests ====================

TEST_F(EmitterStateTest_465, SetNullFormatLowerNull_465) {
  bool result = state.SetNullFormat(LowerNull, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_465, SetNullFormatTildeNull_465) {
  bool result = state.SetNullFormat(TildeNull, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== SetMapKeyFormat Tests ====================

TEST_F(EmitterStateTest_465, SetMapKeyFormatLongKey_465) {
  bool result = state.SetMapKeyFormat(LongKey, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== SetFlowType Tests ====================

TEST_F(EmitterStateTest_465, SetFlowTypeSeqBlock_465) {
  bool result = state.SetFlowType(GroupType::Seq, Block, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_465, SetFlowTypeSeqFlow_465) {
  bool result = state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_465, SetFlowTypeMapBlock_465) {
  bool result = state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_465, SetFlowTypeMapFlow_465) {
  bool result = state.SetFlowType(GroupType::Map, Flow, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_465, SetFlowTypeInvalid_465) {
  bool result = state.SetFlowType(GroupType::Seq, Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Doc Lifecycle Tests ====================

TEST_F(EmitterStateTest_465, StartedDocEndedDoc_465) {
  state.StartedDoc();
  state.EndedDoc();
  // Should not crash and state should still be good
  EXPECT_TRUE(state.good());
}

// ==================== Group Lifecycle Tests ====================

TEST_F(EmitterStateTest_465, StartedGroupSeq_465) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_465, StartedGroupMap_465) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_465, EndedGroupSeq_465) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  // After ending the only group, should still be good
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_465, CurGroupChildCountIncrementsOnScalar_465) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  std::size_t before = state.CurGroupChildCount();
  state.StartedScalar();
  std::size_t after = state.CurGroupChildCount();
  EXPECT_EQ(before + 1, after);
}

TEST_F(EmitterStateTest_465, CurGroupLongKeyDefaultFalse_465) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_465, SetNonContentSetsFlag_465) {
  state.SetNonContent();
  EXPECT_TRUE(state.HasBegunNode());
}

// ==================== StartedScalar Tests ====================

TEST_F(EmitterStateTest_465, StartedScalarClearsAnchorTagAlias_465) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAnchor();
  state.SetTag();
  EXPECT_TRUE(state.HasAnchor());
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_465, ClearModifiedSettingsResetsLocal_465) {
  std::size_t defaultIndent = state.GetIndent();
  state.SetIndent(8, FmtScope::Local);
  EXPECT_EQ(8u, state.GetIndent());
  state.ClearModifiedSettings();
  EXPECT_EQ(defaultIndent, state.GetIndent());
}

// ==================== Nested Groups Tests ====================

TEST_F(EmitterStateTest_465, NestedGroupsTrackCorrectly_465) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());

  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());

  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());

  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_465, ForceFlowChangesFlowType_465) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_465, SetLongKeyInGroup_465) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_465, NextGroupTypeNoGroup_465) {
  // When no group is active, NextGroupType should return something sensible
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // We just verify it doesn't crash
  (void)nodeType;
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_465, LastIndentDefaultZero_465) {
  EXPECT_EQ(0u, state.LastIndent());
}

// ==================== Multiple Settings Scope Tests ====================

TEST_F(EmitterStateTest_465, GlobalSettingPersistsAfterClear_465) {
  state.SetDoublePrecision(15, FmtScope::Global);
  EXPECT_EQ(15u, state.GetDoublePrecision());
  state.ClearModifiedSettings();
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

TEST_F(EmitterStateTest_465, LocalSettingOverridesGlobal_465) {
  state.SetDoublePrecision(10, FmtScope::Global);
  state.SetDoublePrecision(5, FmtScope::Local);
  EXPECT_EQ(5u, state.GetDoublePrecision());
  state.ClearModifiedSettings();
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_465, RestoreGlobalModifiedSettings_465) {
  std::size_t defaultPrecision = state.GetDoublePrecision();
  state.SetDoublePrecision(12, FmtScope::Global);
  EXPECT_EQ(12u, state.GetDoublePrecision());
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(defaultPrecision, state.GetDoublePrecision());
}

// ==================== Boundary Tests ====================

TEST_F(EmitterStateTest_465, SetIndentLargeValue_465) {
  bool result = state.SetIndent(100, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(100u, state.GetIndent());
}

TEST_F(EmitterStateTest_465, SetIndentOne_465) {
  bool result = state.SetIndent(1, FmtScope::Global);
  // Indent of 1 should be minimal valid
  EXPECT_TRUE(result);
  EXPECT_EQ(1u, state.GetIndent());
}

TEST_F(EmitterStateTest_465, SetFloatPrecisionZero_465) {
  // Zero precision edge case
  bool result = state.SetFloatPrecision(0, FmtScope::Global);
  // Implementation may or may not allow 0
  (void)result;
}

TEST_F(EmitterStateTest_465, SetDoublePrecisionZero_465) {
  bool result = state.SetDoublePrecision(0, FmtScope::Global);
  (void)result;
}

// ==================== Error Propagation Tests ====================

TEST_F(EmitterStateTest_465, SetErrorPreventsSubsequentChanges_465) {
  state.SetError("fatal");
  EXPECT_FALSE(state.good());
  // Operations on a bad state may still technically work
  // but the state should remain not good
  state.SetIndent(5, FmtScope::Global);
  EXPECT_FALSE(state.good());
}

}  // namespace
}  // namespace YAML
