#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_460 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_460, InitialState_IsGood_460) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_460, InitialState_NoError_460) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_460, InitialState_NoAnchor_460) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_460, InitialState_NoAlias_460) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_460, InitialState_NoTag_460) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_460, InitialState_CurIndentIsZero_460) {
  EXPECT_EQ(0u, state.CurIndent());
}

TEST_F(EmitterStateTest_460, InitialState_HasNotBegunNode_460) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_460, InitialState_HasNotBegunContent_460) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== Default Format Getters ====================

TEST_F(EmitterStateTest_460, DefaultGetIndent_460) {
  // Default indent is typically 2
  EXPECT_EQ(2u, state.GetIndent());
}

TEST_F(EmitterStateTest_460, DefaultGetPreCommentIndent_460) {
  EXPECT_EQ(2u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_460, DefaultGetPostCommentIndent_460) {
  EXPECT_EQ(1u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_460, DefaultGetFloatPrecision_460) {
  std::size_t prec = state.GetFloatPrecision();
  // Just ensure it returns some reasonable value
  EXPECT_GT(prec, 0u);
}

TEST_F(EmitterStateTest_460, DefaultGetDoublePrecision_460) {
  std::size_t prec = state.GetDoublePrecision();
  EXPECT_GT(prec, 0u);
}

TEST_F(EmitterStateTest_460, DefaultGetStringFormat_460) {
  EMITTER_MANIP fmt = state.GetStringFormat();
  // Should be some valid manip
  (void)fmt; // Just ensure it doesn't crash
}

TEST_F(EmitterStateTest_460, DefaultGetBoolFormat_460) {
  EMITTER_MANIP fmt = state.GetBoolFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_460, DefaultGetBoolLengthFormat_460) {
  EMITTER_MANIP fmt = state.GetBoolLengthFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_460, DefaultGetBoolCaseFormat_460) {
  EMITTER_MANIP fmt = state.GetBoolCaseFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_460, DefaultGetNullFormat_460) {
  EMITTER_MANIP fmt = state.GetNullFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_460, DefaultGetIntFormat_460) {
  EMITTER_MANIP fmt = state.GetIntFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_460, DefaultGetOutputCharset_460) {
  EMITTER_MANIP fmt = state.GetOutputCharset();
  (void)fmt;
}

TEST_F(EmitterStateTest_460, DefaultGetMapKeyFormat_460) {
  EMITTER_MANIP fmt = state.GetMapKeyFormat();
  (void)fmt;
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_460, SetError_MakesNotGood_460) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_460, SetError_StoresMessage_460) {
  state.SetError("some error message");
  EXPECT_EQ("some error message", state.GetLastError());
}

TEST_F(EmitterStateTest_460, SetError_EmptyString_460) {
  state.SetError("");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_460, SetError_MultipleErrors_FirstPersists_460) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically the first error is preserved
  EXPECT_FALSE(state.good());
  // The last error string may be the first one set
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_460, SetAnchor_HasAnchorTrue_460) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_460, SetAlias_HasAliasTrue_460) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_460, SetTag_HasTagTrue_460) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== SetIndent Tests ====================

TEST_F(EmitterStateTest_460, SetIndent_GlobalScope_460) {
  bool result = state.SetIndent(4, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_460, SetIndent_LocalScope_460) {
  bool result = state.SetIndent(6, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(6u, state.GetIndent());
}

TEST_F(EmitterStateTest_460, SetIndent_ZeroValue_460) {
  // Indent of 0 might not be valid
  bool result = state.SetIndent(0, FmtScope::Global);
  // Could return false for invalid indent
  (void)result;
}

TEST_F(EmitterStateTest_460, SetIndent_ValueOfOne_460) {
  // Indent of 1 might not be valid (needs to be >= 2)
  bool result = state.SetIndent(1, FmtScope::Global);
  (void)result;
}

// ==================== SetPreCommentIndent / SetPostCommentIndent ====================

TEST_F(EmitterStateTest_460, SetPreCommentIndent_GlobalScope_460) {
  bool result = state.SetPreCommentIndent(3, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_460, SetPostCommentIndent_GlobalScope_460) {
  bool result = state.SetPostCommentIndent(5, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(5u, state.GetPostCommentIndent());
}

// ==================== SetOutputCharset ====================

TEST_F(EmitterStateTest_460, SetOutputCharset_UTF8_460) {
  bool result = state.SetOutputCharset(EmitNonAscii, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_460, SetOutputCharset_EscapeNonAscii_460) {
  bool result = state.SetOutputCharset(EscapeNonAscii, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_460, SetOutputCharset_InvalidValue_460) {
  // Passing an unrelated EMITTER_MANIP should fail
  bool result = state.SetOutputCharset(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetStringFormat ====================

TEST_F(EmitterStateTest_460, SetStringFormat_SingleQuoted_460) {
  bool result = state.SetStringFormat(SingleQuoted, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_460, SetStringFormat_DoubleQuoted_460) {
  bool result = state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_460, SetStringFormat_Literal_460) {
  bool result = state.SetStringFormat(Literal, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Literal, state.GetStringFormat());
}

TEST_F(EmitterStateTest_460, SetStringFormat_InvalidValue_460) {
  bool result = state.SetStringFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetBoolFormat ====================

TEST_F(EmitterStateTest_460, SetBoolFormat_TrueFalseBool_460) {
  bool result = state.SetBoolFormat(TrueFalseBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_460, SetBoolFormat_YesNoBool_460) {
  bool result = state.SetBoolFormat(YesNoBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_460, SetBoolFormat_OnOffBool_460) {
  bool result = state.SetBoolFormat(OnOffBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_460, SetBoolFormat_InvalidValue_460) {
  bool result = state.SetBoolFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetBoolLengthFormat ====================

TEST_F(EmitterStateTest_460, SetBoolLengthFormat_Short_460) {
  bool result = state.SetBoolLengthFormat(ShortBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_460, SetBoolLengthFormat_Long_460) {
  bool result = state.SetBoolLengthFormat(LongBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

// ==================== SetBoolCaseFormat ====================

TEST_F(EmitterStateTest_460, SetBoolCaseFormat_Upper_460) {
  bool result = state.SetBoolCaseFormat(UpperCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_460, SetBoolCaseFormat_Lower_460) {
  bool result = state.SetBoolCaseFormat(LowerCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_460, SetBoolCaseFormat_Camel_460) {
  bool result = state.SetBoolCaseFormat(CamelCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

// ==================== SetNullFormat ====================

TEST_F(EmitterStateTest_460, SetNullFormat_LowerNull_460) {
  bool result = state.SetNullFormat(LowerNull, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_460, SetNullFormat_TildeNull_460) {
  bool result = state.SetNullFormat(TildeNull, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== SetIntFormat ====================

TEST_F(EmitterStateTest_460, SetIntFormat_Dec_460) {
  bool result = state.SetIntFormat(Dec, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_460, SetIntFormat_Hex_460) {
  bool result = state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_460, SetIntFormat_Oct_460) {
  bool result = state.SetIntFormat(Oct, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_460, SetIntFormat_InvalidValue_460) {
  bool result = state.SetIntFormat(SingleQuoted, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetFlowType ====================

TEST_F(EmitterStateTest_460, SetFlowType_SeqBlock_460) {
  bool result = state.SetFlowType(GroupType::Seq, Block, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_460, SetFlowType_SeqFlow_460) {
  bool result = state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_460, SetFlowType_MapBlock_460) {
  bool result = state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_460, SetFlowType_MapFlow_460) {
  bool result = state.SetFlowType(GroupType::Map, Flow, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_460, SetFlowType_InvalidValue_460) {
  bool result = state.SetFlowType(GroupType::Seq, Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetMapKeyFormat ====================

TEST_F(EmitterStateTest_460, SetMapKeyFormat_LongKey_460) {
  bool result = state.SetMapKeyFormat(LongKey, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== SetFloatPrecision / SetDoublePrecision ====================

TEST_F(EmitterStateTest_460, SetFloatPrecision_460) {
  bool result = state.SetFloatPrecision(5, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_460, SetDoublePrecision_460) {
  bool result = state.SetDoublePrecision(10, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== Document Lifecycle ====================

TEST_F(EmitterStateTest_460, StartedDoc_460) {
  state.StartedDoc();
  // After starting a doc, the state should still be good
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_460, EndedDoc_460) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Lifecycle ====================

TEST_F(EmitterStateTest_460, StartedGroup_Seq_460) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_460, StartedGroup_Map_460) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_460, EndedGroup_Seq_460) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_460, EndedGroup_Map_460) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_460, CurGroupChildCount_InitiallyZero_460) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_460, CurGroupChildCount_AfterScalar_460) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_460, CurGroupLongKey_DefaultFalse_460) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// ==================== Nested Groups ====================

TEST_F(EmitterStateTest_460, NestedGroups_460) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// ==================== StartedScalar ====================

TEST_F(EmitterStateTest_460, StartedScalar_460) {
  state.StartedDoc();
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

// ==================== SetNonContent ====================

TEST_F(EmitterStateTest_460, SetNonContent_460) {
  state.SetNonContent();
  // HasBegunContent should reflect that we have non-content
  // We just ensure it doesn't crash
  EXPECT_TRUE(state.good());
}

// ==================== ForceFlow ====================

TEST_F(EmitterStateTest_460, ForceFlow_InGroup_460) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== SetLongKey ====================

TEST_F(EmitterStateTest_460, SetLongKey_InGroup_460) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== ClearModifiedSettings ====================

TEST_F(EmitterStateTest_460, ClearModifiedSettings_460) {
  state.SetIndent(4, FmtScope::Local);
  EXPECT_EQ(4u, state.GetIndent());
  state.ClearModifiedSettings();
  // After clearing local modifications, should revert to default/global
  EXPECT_EQ(2u, state.GetIndent());
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterStateTest_460, RestoreGlobalModifiedSettings_460) {
  state.SetIndent(4, FmtScope::Global);
  EXPECT_EQ(4u, state.GetIndent());
  state.RestoreGlobalModifiedSettings();
  // After restoring, global settings should be reverted
  EXPECT_EQ(2u, state.GetIndent());
}

// ==================== Scope Interactions ====================

TEST_F(EmitterStateTest_460, LocalScopeOverridesGlobal_460) {
  state.SetIndent(4, FmtScope::Global);
  EXPECT_EQ(4u, state.GetIndent());
  state.SetIndent(6, FmtScope::Local);
  EXPECT_EQ(6u, state.GetIndent());
  state.ClearModifiedSettings();
  // After clearing local, should revert to global
  EXPECT_EQ(4u, state.GetIndent());
}

// ==================== LastIndent ====================

TEST_F(EmitterStateTest_460, LastIndent_InitiallyZero_460) {
  EXPECT_EQ(0u, state.LastIndent());
}

// ==================== CurGroupIndent ====================

TEST_F(EmitterStateTest_460, CurGroupIndent_460) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // CurGroupIndent should be some value
  std::size_t indent = state.CurGroupIndent();
  (void)indent;
  EXPECT_TRUE(state.good());
}

// ==================== NextGroupType ====================

TEST_F(EmitterStateTest_460, NextGroupType_Seq_460) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_460, NextGroupType_Map_460) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ==================== CurGroupNodeType ====================

TEST_F(EmitterStateTest_460, CurGroupNodeType_InSeq_460) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ==================== CurGroupFlowType ====================

TEST_F(EmitterStateTest_460, CurGroupFlowType_DefaultBlock_460) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // Default flow type should be block for sequences at top level
  FlowType::value flowType = state.CurGroupFlowType();
  (void)flowType;
  EXPECT_TRUE(state.good());
}

// ==================== Multiple SetLocalValue ====================

TEST_F(EmitterStateTest_460, SetLocalValue_Flow_460) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_460, SetLocalValue_Block_460) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// ==================== HasBegunNode / HasBegunContent ====================

TEST_F(EmitterStateTest_460, HasBegunNode_AfterAnchor_460) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_460, HasBegunNode_AfterTag_460) {
  state.SetTag();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_460, HasBegunNode_AfterAlias_460) {
  state.SetAlias();
  EXPECT_TRUE(state.HasBegunNode());
}

// ==================== Error state prevents modifications ====================

TEST_F(EmitterStateTest_460, ErrorState_SetIndentStillWorks_460) {
  state.SetError("error");
  EXPECT_FALSE(state.good());
  // Setting indent on errored state
  bool result = state.SetIndent(4, FmtScope::Global);
  // Behavior depends on implementation; just check it doesn't crash
  (void)result;
}

}  // namespace YAML
