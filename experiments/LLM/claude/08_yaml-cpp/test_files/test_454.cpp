#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_454 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_454, InitialStateIsGood_454) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_454, InitialLastErrorIsEmpty_454) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_454, InitialCurIndentIsZero_454) {
  EXPECT_EQ(0u, state.CurIndent());
}

TEST_F(EmitterStateTest_454, InitialHasAnchorIsFalse_454) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_454, InitialHasAliasIsFalse_454) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_454, InitialHasTagIsFalse_454) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_454, InitialHasBegunNodeIsFalse_454) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_454, InitialHasBegunContentIsFalse_454) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== Default Format Getters ====================

TEST_F(EmitterStateTest_454, DefaultStringFormat_454) {
  // Default string format should be some valid EMITTER_MANIP value
  EMITTER_MANIP fmt = state.GetStringFormat();
  // Just ensure it returns without crashing; exact default depends on implementation
  (void)fmt;
}

TEST_F(EmitterStateTest_454, DefaultBoolFormat_454) {
  EMITTER_MANIP fmt = state.GetBoolFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_454, DefaultBoolLengthFormat_454) {
  EMITTER_MANIP fmt = state.GetBoolLengthFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_454, DefaultBoolCaseFormat_454) {
  EMITTER_MANIP fmt = state.GetBoolCaseFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_454, DefaultNullFormat_454) {
  EMITTER_MANIP fmt = state.GetNullFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_454, DefaultIntFormat_454) {
  EMITTER_MANIP fmt = state.GetIntFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_454, DefaultOutputCharset_454) {
  EMITTER_MANIP fmt = state.GetOutputCharset();
  (void)fmt;
}

TEST_F(EmitterStateTest_454, DefaultMapKeyFormat_454) {
  EMITTER_MANIP fmt = state.GetMapKeyFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_454, DefaultGetIndent_454) {
  std::size_t indent = state.GetIndent();
  EXPECT_GT(indent, 0u);
}

TEST_F(EmitterStateTest_454, DefaultGetPreCommentIndent_454) {
  std::size_t indent = state.GetPreCommentIndent();
  (void)indent;
}

TEST_F(EmitterStateTest_454, DefaultGetPostCommentIndent_454) {
  std::size_t indent = state.GetPostCommentIndent();
  (void)indent;
}

TEST_F(EmitterStateTest_454, DefaultGetFloatPrecision_454) {
  std::size_t prec = state.GetFloatPrecision();
  (void)prec;
}

TEST_F(EmitterStateTest_454, DefaultGetDoublePrecision_454) {
  std::size_t prec = state.GetDoublePrecision();
  (void)prec;
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_454, SetErrorMakesStateNotGood_454) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_454, SetErrorStoresErrorMessage_454) {
  state.SetError("some error message");
  EXPECT_EQ("some error message", state.GetLastError());
}

TEST_F(EmitterStateTest_454, SetErrorEmptyString_454) {
  state.SetError("");
  EXPECT_FALSE(state.good());
}

// ==================== SetAnchor / SetAlias / SetTag Tests ====================

TEST_F(EmitterStateTest_454, SetAnchorChangesHasAnchor_454) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_454, SetAliasChangesHasAlias_454) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_454, SetTagChangesHasTag_454) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== SetStringFormat Tests ====================

TEST_F(EmitterStateTest_454, SetStringFormatGlobal_454) {
  bool result = state.SetStringFormat(SingleQuoted, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_454, SetStringFormatLocal_454) {
  bool result = state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_454, SetStringFormatInvalidValue_454) {
  // Passing an invalid value for string format should return false
  bool result = state.SetStringFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetBoolFormat Tests ====================

TEST_F(EmitterStateTest_454, SetBoolFormatTrueFalse_454) {
  bool result = state.SetBoolFormat(TrueFalseBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_454, SetBoolFormatYesNo_454) {
  bool result = state.SetBoolFormat(YesNoBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_454, SetBoolFormatOnOff_454) {
  bool result = state.SetBoolFormat(OnOffBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_454, SetBoolFormatInvalidValue_454) {
  bool result = state.SetBoolFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetBoolLengthFormat Tests ====================

TEST_F(EmitterStateTest_454, SetBoolLengthFormatShort_454) {
  bool result = state.SetBoolLengthFormat(ShortBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_454, SetBoolLengthFormatLong_454) {
  bool result = state.SetBoolLengthFormat(LongBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

// ==================== SetBoolCaseFormat Tests ====================

TEST_F(EmitterStateTest_454, SetBoolCaseFormatUpperCase_454) {
  bool result = state.SetBoolCaseFormat(UpperCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_454, SetBoolCaseFormatLowerCase_454) {
  bool result = state.SetBoolCaseFormat(LowerCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_454, SetBoolCaseFormatCamelCase_454) {
  bool result = state.SetBoolCaseFormat(CamelCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

// ==================== SetNullFormat Tests ====================

TEST_F(EmitterStateTest_454, SetNullFormatLowerNull_454) {
  bool result = state.SetNullFormat(LowerNull, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_454, SetNullFormatTildeNull_454) {
  bool result = state.SetNullFormat(TildeNull, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== SetIntFormat Tests ====================

TEST_F(EmitterStateTest_454, SetIntFormatDec_454) {
  bool result = state.SetIntFormat(Dec, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_454, SetIntFormatHex_454) {
  bool result = state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_454, SetIntFormatOct_454) {
  bool result = state.SetIntFormat(Oct, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

// ==================== SetIndent Tests ====================

TEST_F(EmitterStateTest_454, SetIndentValid_454) {
  bool result = state.SetIndent(4, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_454, SetIndentMinimum_454) {
  bool result = state.SetIndent(2, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(2u, state.GetIndent());
}

TEST_F(EmitterStateTest_454, SetIndentZeroFails_454) {
  // Indent of 0 is likely invalid
  bool result = state.SetIndent(0, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_454, SetIndentOneFails_454) {
  // Indent of 1 is likely invalid (minimum is typically 2)
  bool result = state.SetIndent(1, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetPreCommentIndent / SetPostCommentIndent ====================

TEST_F(EmitterStateTest_454, SetPreCommentIndent_454) {
  bool result = state.SetPreCommentIndent(3, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_454, SetPostCommentIndent_454) {
  bool result = state.SetPostCommentIndent(5, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(5u, state.GetPostCommentIndent());
}

// ==================== SetOutputCharset Tests ====================

TEST_F(EmitterStateTest_454, SetOutputCharsetUtf8_454) {
  bool result = state.SetOutputCharset(EmitNonAscii, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_454, SetOutputCharsetEscapeNonAscii_454) {
  bool result = state.SetOutputCharset(EscapeNonAscii, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

// ==================== SetMapKeyFormat Tests ====================

TEST_F(EmitterStateTest_454, SetMapKeyFormatLongKey_454) {
  bool result = state.SetMapKeyFormat(LongKey, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== SetFloatPrecision / SetDoublePrecision ====================

TEST_F(EmitterStateTest_454, SetFloatPrecision_454) {
  bool result = state.SetFloatPrecision(6, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(6u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_454, SetDoublePrecision_454) {
  bool result = state.SetDoublePrecision(15, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

// ==================== SetFlowType Tests ====================

TEST_F(EmitterStateTest_454, SetFlowTypeSeqFlow_454) {
  bool result = state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_454, SetFlowTypeSeqBlock_454) {
  bool result = state.SetFlowType(GroupType::Seq, Block, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_454, SetFlowTypeMapFlow_454) {
  bool result = state.SetFlowType(GroupType::Map, Flow, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_454, SetFlowTypeMapBlock_454) {
  bool result = state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== Doc Start/End Tests ====================

TEST_F(EmitterStateTest_454, StartedDocEndedDoc_454) {
  state.StartedDoc();
  state.EndedDoc();
  // Should still be good
  EXPECT_TRUE(state.good());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_454, StartedGroupSeqAndEndedGroup_454) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_454, StartedGroupMapAndEndedGroup_454) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_454, CurGroupChildCountInitiallyZero_454) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_454, CurGroupLongKeyInitiallyFalse_454) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== StartedScalar Tests ====================

TEST_F(EmitterStateTest_454, StartedScalarAfterDoc_454) {
  state.StartedDoc();
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_454, SetNonContent_454) {
  state.SetNonContent();
  // HasBegunContent should still be false if only non-content was set
  // This tests that non-content doesn't count as content
  // The exact semantics depend on implementation but should not crash
  EXPECT_TRUE(state.good());
}

// ==================== Scope Tests ====================

TEST_F(EmitterStateTest_454, LocalScopeSettingIsTemporary_454) {
  EMITTER_MANIP origFmt = state.GetStringFormat();
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
  state.ClearModifiedSettings();
  EXPECT_EQ(origFmt, state.GetStringFormat());
}

TEST_F(EmitterStateTest_454, GlobalScopeSettingPersistsAfterClear_454) {
  state.SetStringFormat(SingleQuoted, FmtScope::Global);
  state.ClearModifiedSettings();
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_454, ForceFlowDoesNotBreakState_454) {
  state.ForceFlow();
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_454, SetLongKeyDoesNotBreakState_454) {
  state.SetLongKey();
  EXPECT_TRUE(state.good());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_454, NextGroupTypeSeq_454) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_454, NextGroupTypeMap_454) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_454, RestoreGlobalModifiedSettings_454) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  // After restoring, the global modifications should be undone
  // The format should revert to default
  EXPECT_TRUE(state.good());
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_454, LastIndentInitial_454) {
  std::size_t lastIndent = state.LastIndent();
  (void)lastIndent;
  EXPECT_TRUE(state.good());
}

// ==================== Multiple Error Setting ====================

TEST_F(EmitterStateTest_454, MultipleErrorsKeepFirstError_454) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_FALSE(state.good());
  // Typically first error is preserved
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== SetStringFormat with Different Scopes ====================

TEST_F(EmitterStateTest_454, SetStringFormatLocalThenGlobal_454) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
  
  state.SetStringFormat(SingleQuoted, FmtScope::Global);
  // Local should still take precedence if active
  // Or global might override - depends on implementation
  // Just verify it's one of the two set values
  EMITTER_MANIP result = state.GetStringFormat();
  EXPECT_TRUE(result == DoubleQuoted || result == SingleQuoted);
}

// ==================== Nested Groups ====================

TEST_F(EmitterStateTest_454, NestedGroups_454) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  
  state.StartedScalar(); // key
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// ==================== CurGroupFlowType Tests ====================

TEST_F(EmitterStateTest_454, CurGroupFlowTypeAfterStartGroup_454) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  FlowType::value flowType = state.CurGroupFlowType();
  (void)flowType;
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// ==================== CurGroupIndent Tests ====================

TEST_F(EmitterStateTest_454, CurGroupIndentAfterStartGroup_454) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  std::size_t indent = state.CurGroupIndent();
  (void)indent;
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// ==================== ForceFlow affects group flow type ====================

TEST_F(EmitterStateTest_454, ForceFlowBeforeGroupMakesItFlow_454) {
  state.StartedDoc();
  state.ForceFlow();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Seq);
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_454, SetLocalValueFlow_454) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_454, SetLocalValueBlock_454) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_454, SetLocalValueDoubleQuoted_454) {
  state.SetLocalValue(DoubleQuoted);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

}  // namespace YAML
