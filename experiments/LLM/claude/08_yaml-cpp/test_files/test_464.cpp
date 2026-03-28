#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_464 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_464, InitialStateIsGood_464) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_464, InitialLastErrorIsEmpty_464) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_464, InitialHasNoAnchor_464) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_464, InitialHasNoAlias_464) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_464, InitialHasNoTag_464) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_464, InitialCurIndentIsZero_464) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== Error Handling Tests ====================

TEST_F(EmitterStateTest_464, SetErrorMakesStateNotGood_464) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_464, SetErrorStoresErrorMessage_464) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_464, SetErrorOnlyKeepsFirstError_464) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_464, SetAnchorSetsHasAnchor_464) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_464, SetAliasSetsHasAlias_464) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_464, SetTagSetsHasTag_464) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Default Format Getter Tests ====================

TEST_F(EmitterStateTest_464, DefaultOutputCharset_464) {
  EMITTER_MANIP charset = state.GetOutputCharset();
  // Default should be EmitNonAscii or UTF8 - just check it returns a valid value
  (void)charset;
}

TEST_F(EmitterStateTest_464, DefaultStringFormat_464) {
  EMITTER_MANIP fmt = state.GetStringFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_464, DefaultBoolFormat_464) {
  EMITTER_MANIP fmt = state.GetBoolFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_464, DefaultBoolLengthFormat_464) {
  EMITTER_MANIP fmt = state.GetBoolLengthFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_464, DefaultBoolCaseFormat_464) {
  EMITTER_MANIP fmt = state.GetBoolCaseFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_464, DefaultNullFormat_464) {
  EMITTER_MANIP fmt = state.GetNullFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_464, DefaultIntFormat_464) {
  EMITTER_MANIP fmt = state.GetIntFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_464, DefaultIndent_464) {
  std::size_t indent = state.GetIndent();
  EXPECT_GE(indent, 1u);
}

TEST_F(EmitterStateTest_464, DefaultPreCommentIndent_464) {
  std::size_t indent = state.GetPreCommentIndent();
  EXPECT_GE(indent, 1u);
}

TEST_F(EmitterStateTest_464, DefaultPostCommentIndent_464) {
  std::size_t indent = state.GetPostCommentIndent();
  EXPECT_GE(indent, 1u);
}

TEST_F(EmitterStateTest_464, DefaultFloatPrecision_464) {
  std::size_t precision = state.GetFloatPrecision();
  // Should have some reasonable default
  EXPECT_GT(precision, 0u);
}

TEST_F(EmitterStateTest_464, DefaultDoublePrecision_464) {
  std::size_t precision = state.GetDoublePrecision();
  EXPECT_GT(precision, 0u);
}

TEST_F(EmitterStateTest_464, DefaultMapKeyFormat_464) {
  EMITTER_MANIP fmt = state.GetMapKeyFormat();
  (void)fmt;
}

// ==================== Set Format Tests (Global Scope) ====================

TEST_F(EmitterStateTest_464, SetOutputCharsetGlobal_464) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_464, SetStringFormatGlobal_464) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
}

TEST_F(EmitterStateTest_464, SetBoolFormatGlobal_464) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_464, SetBoolLengthFormatGlobal_464) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_464, SetBoolCaseFormatGlobal_464) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
}

TEST_F(EmitterStateTest_464, SetNullFormatGlobal_464) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
}

TEST_F(EmitterStateTest_464, SetIntFormatGlobal_464) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
}

TEST_F(EmitterStateTest_464, SetIndentGlobal_464) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_464, SetPreCommentIndentGlobal_464) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_464, SetPostCommentIndentGlobal_464) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_464, SetFloatPrecisionGlobal_464) {
  EXPECT_TRUE(state.SetFloatPrecision(5, FmtScope::Global));
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_464, SetDoublePrecisionGlobal_464) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Global));
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

TEST_F(EmitterStateTest_464, SetMapKeyFormatGlobal_464) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
}

// ==================== Set Format Tests (Local Scope) ====================

TEST_F(EmitterStateTest_464, SetIndentLocal_464) {
  EXPECT_TRUE(state.SetIndent(6, FmtScope::Local));
  EXPECT_EQ(6u, state.GetIndent());
}

TEST_F(EmitterStateTest_464, SetFloatPrecisionLocal_464) {
  EXPECT_TRUE(state.SetFloatPrecision(3, FmtScope::Local));
  EXPECT_EQ(3u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_464, SetDoublePrecisionLocal_464) {
  EXPECT_TRUE(state.SetDoublePrecision(7, FmtScope::Local));
  EXPECT_EQ(7u, state.GetDoublePrecision());
}

// ==================== Invalid Set Format Tests ====================

TEST_F(EmitterStateTest_464, SetOutputCharsetInvalidValue_464) {
  // Passing an unrelated EMITTER_MANIP should return false
  EXPECT_FALSE(state.SetOutputCharset(Hex, FmtScope::Global));
}

TEST_F(EmitterStateTest_464, SetStringFormatInvalidValue_464) {
  EXPECT_FALSE(state.SetStringFormat(Dec, FmtScope::Global));
}

TEST_F(EmitterStateTest_464, SetBoolFormatInvalidValue_464) {
  EXPECT_FALSE(state.SetBoolFormat(Hex, FmtScope::Global));
}

TEST_F(EmitterStateTest_464, SetIntFormatInvalidValue_464) {
  EXPECT_FALSE(state.SetIntFormat(TrueFalseBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_464, SetIndentZeroReturnsFalse_464) {
  // Zero indent should likely be invalid
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Global));
}

// ==================== SetFlowType Tests ====================

TEST_F(EmitterStateTest_464, SetFlowTypeSeqGlobal_464) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_464, SetFlowTypeMapGlobal_464) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
}

TEST_F(EmitterStateTest_464, GetFlowTypeSeqAfterSet_464) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_464, GetFlowTypeMapAfterSet_464) {
  state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_464, SetFlowTypeInvalidValue_464) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Hex, FmtScope::Global));
}

// ==================== Document Lifecycle Tests ====================

TEST_F(EmitterStateTest_464, StartedDocDoesNotBreakState_464) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_464, EndedDocDoesNotBreakState_464) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Lifecycle Tests ====================

TEST_F(EmitterStateTest_464, StartAndEndSeqGroup_464) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_464, StartAndEndMapGroup_464) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_464, CurGroupChildCountInitiallyZero_464) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_464, CurGroupChildCountAfterScalar_464) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_464, CurGroupLongKeyDefaultFalse_464) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

TEST_F(EmitterStateTest_464, CurGroupFlowTypeDefault_464) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  FlowType::value ft = state.CurGroupFlowType();
  (void)ft;
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_464, CurGroupIndent_464) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  std::size_t indent = state.CurGroupIndent();
  (void)indent;
  state.EndedGroup(GroupType::Seq);
}

// ==================== Nested Group Tests ====================

TEST_F(EmitterStateTest_464, NestedGroups_464) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_464, SetLocalValueFlow_464) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_464, SetLocalValueBlock_464) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_464, ClearModifiedSettingsRestoresLocalValues_464) {
  std::size_t defaultIndent = state.GetIndent();
  state.SetIndent(8, FmtScope::Local);
  EXPECT_EQ(8u, state.GetIndent());
  state.ClearModifiedSettings();
  EXPECT_EQ(defaultIndent, state.GetIndent());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_464, RestoreGlobalModifiedSettings_464) {
  std::size_t defaultIndent = state.GetIndent();
  state.SetIndent(8, FmtScope::Global);
  EXPECT_EQ(8u, state.GetIndent());
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(defaultIndent, state.GetIndent());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_464, SetNonContent_464) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_464, ForceFlowDoesNotBreakState_464) {
  state.ForceFlow();
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_464, SetLongKey_464) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_464, NextGroupTypeSeq_464) {
  state.StartedDoc();
  EmitterNodeType::value type = state.NextGroupType(GroupType::Seq);
  (void)type;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_464, NextGroupTypeMap_464) {
  state.StartedDoc();
  EmitterNodeType::value type = state.NextGroupType(GroupType::Map);
  (void)type;
  EXPECT_TRUE(state.good());
}

// ==================== Precision Boundary Tests ====================

TEST_F(EmitterStateTest_464, FloatPrecisionMaxReasonable_464) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Global));
  EXPECT_EQ(6u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_464, DoublePrecisionMaxReasonable_464) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Global));
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

// ==================== Multiple Scalar Emissions ====================

TEST_F(EmitterStateTest_464, StartedScalarClearsAnchorAndTag_464) {
  state.SetAnchor();
  state.SetTag();
  EXPECT_TRUE(state.HasAnchor());
  EXPECT_TRUE(state.HasTag());
  state.StartedDoc();
  state.StartedScalar();
  // After starting a scalar, anchor and tag should be consumed
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
}

// ==================== HasBegunNode / HasBegunContent ====================

TEST_F(EmitterStateTest_464, HasBegunNodeInitiallyFalse_464) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_464, HasBegunContentInitiallyFalse_464) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== Int Format Round Trip ====================

TEST_F(EmitterStateTest_464, SetAndGetIntFormatDec_464) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_464, SetAndGetIntFormatHex_464) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_464, SetAndGetIntFormatOct_464) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

// ==================== Bool Format Round Trip ====================

TEST_F(EmitterStateTest_464, SetAndGetBoolFormatTrueFalse_464) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_464, SetAndGetBoolFormatYesNo_464) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_464, SetAndGetBoolFormatOnOff_464) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Global));
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

// ==================== String Format Round Trip ====================

TEST_F(EmitterStateTest_464, SetAndGetStringFormatSingleQuoted_464) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_464, SetAndGetStringFormatDoubleQuoted_464) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_464, SetAndGetStringFormatLiteral_464) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Global));
  EXPECT_EQ(Literal, state.GetStringFormat());
}

// ==================== Output Charset Round Trip ====================

TEST_F(EmitterStateTest_464, SetAndGetOutputCharsetEmitNonAscii_464) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_464, SetAndGetOutputCharsetEscapeNonAscii_464) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Global));
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

// ==================== Null Format Round Trip ====================

TEST_F(EmitterStateTest_464, SetAndGetNullFormatLowerNull_464) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_464, SetAndGetNullFormatTildeNull_464) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Global));
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_464, LastIndentDefault_464) {
  std::size_t lastIndent = state.LastIndent();
  (void)lastIndent;
  EXPECT_TRUE(state.good());
}

// ==================== Multiple Document Tests ====================

TEST_F(EmitterStateTest_464, MultipleDocuments_464) {
  state.StartedDoc();
  state.EndedDoc();
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== CurGroupNodeType Tests ====================

TEST_F(EmitterStateTest_464, CurGroupNodeTypeInGroup_464) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nt = state.CurGroupNodeType();
  (void)nt;
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

}  // namespace YAML
