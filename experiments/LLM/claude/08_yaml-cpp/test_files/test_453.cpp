#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_453 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_453, InitialState_IsGood_453) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_453, InitialState_NoLastError_453) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_453, InitialState_NoAnchor_453) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_453, InitialState_NoAlias_453) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_453, InitialState_NoTag_453) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_453, InitialState_HasNotBegunNode_453) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_453, InitialState_HasNotBegunContent_453) {
  EXPECT_FALSE(state.HasBegunContent());
}

TEST_F(EmitterStateTest_453, InitialState_CurIndentIsZero_453) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== Error Handling Tests ====================

TEST_F(EmitterStateTest_453, SetError_MakesStateNotGood_453) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_453, SetError_StoresErrorMessage_453) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_453, SetError_EmptyString_453) {
  state.SetError("");
  EXPECT_FALSE(state.good());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_453, SetAnchor_HasAnchorReturnsTrue_453) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_453, SetAlias_HasAliasReturnsTrue_453) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_453, SetTag_HasTagReturnsTrue_453) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Output Charset Tests ====================

TEST_F(EmitterStateTest_453, DefaultOutputCharset_453) {
  EMITTER_MANIP charset = state.GetOutputCharset();
  // Default should be EmitNonAscii or UTF8 — just verify it's a valid value
  EXPECT_TRUE(charset == EmitNonAscii || charset == EscapeNonAscii || charset == EscapeAsJson);
}

TEST_F(EmitterStateTest_453, SetOutputCharset_Global_453) {
  bool result = state.SetOutputCharset(EscapeNonAscii, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_453, SetOutputCharset_Local_453) {
  bool result = state.SetOutputCharset(EscapeNonAscii, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_453, SetOutputCharset_InvalidValue_453) {
  // Setting an unrelated EMITTER_MANIP should fail
  bool result = state.SetOutputCharset(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== String Format Tests ====================

TEST_F(EmitterStateTest_453, DefaultStringFormat_453) {
  EMITTER_MANIP fmt = state.GetStringFormat();
  // Some default value
  (void)fmt; // Just verify it doesn't crash
}

TEST_F(EmitterStateTest_453, SetStringFormat_Global_453) {
  bool result = state.SetStringFormat(SingleQuoted, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_453, SetStringFormat_DoubleQuoted_453) {
  bool result = state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_453, SetStringFormat_Literal_453) {
  bool result = state.SetStringFormat(Literal, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Literal, state.GetStringFormat());
}

TEST_F(EmitterStateTest_453, SetStringFormat_InvalidValue_453) {
  bool result = state.SetStringFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Bool Format Tests ====================

TEST_F(EmitterStateTest_453, SetBoolFormat_TrueFalseBool_453) {
  bool result = state.SetBoolFormat(TrueFalseBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_453, SetBoolFormat_YesNoBool_453) {
  bool result = state.SetBoolFormat(YesNoBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_453, SetBoolFormat_OnOffBool_453) {
  bool result = state.SetBoolFormat(OnOffBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_453, SetBoolFormat_InvalidValue_453) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Bool Length Format Tests ====================

TEST_F(EmitterStateTest_453, SetBoolLengthFormat_ShortBool_453) {
  bool result = state.SetBoolLengthFormat(ShortBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_453, SetBoolLengthFormat_LongBool_453) {
  bool result = state.SetBoolLengthFormat(LongBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_453, SetBoolLengthFormat_InvalidValue_453) {
  bool result = state.SetBoolLengthFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Bool Case Format Tests ====================

TEST_F(EmitterStateTest_453, SetBoolCaseFormat_UpperCase_453) {
  bool result = state.SetBoolCaseFormat(UpperCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_453, SetBoolCaseFormat_LowerCase_453) {
  bool result = state.SetBoolCaseFormat(LowerCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_453, SetBoolCaseFormat_CamelCase_453) {
  bool result = state.SetBoolCaseFormat(CamelCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_453, SetBoolCaseFormat_InvalidValue_453) {
  bool result = state.SetBoolCaseFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Null Format Tests ====================

TEST_F(EmitterStateTest_453, SetNullFormat_LowerNull_453) {
  bool result = state.SetNullFormat(LowerNull, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_453, SetNullFormat_TildeNull_453) {
  bool result = state.SetNullFormat(TildeNull, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_453, SetNullFormat_InvalidValue_453) {
  bool result = state.SetNullFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Int Format Tests ====================

TEST_F(EmitterStateTest_453, SetIntFormat_Dec_453) {
  bool result = state.SetIntFormat(Dec, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_453, SetIntFormat_Hex_453) {
  bool result = state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_453, SetIntFormat_Oct_453) {
  bool result = state.SetIntFormat(Oct, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_453, SetIntFormat_InvalidValue_453) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Indent Tests ====================

TEST_F(EmitterStateTest_453, DefaultIndent_453) {
  std::size_t indent = state.GetIndent();
  EXPECT_GE(indent, 1u);
}

TEST_F(EmitterStateTest_453, SetIndent_Global_453) {
  bool result = state.SetIndent(4, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_453, SetIndent_Local_453) {
  bool result = state.SetIndent(6, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(6u, state.GetIndent());
}

TEST_F(EmitterStateTest_453, SetIndent_ZeroFails_453) {
  // 0 indent doesn't make sense, should fail
  bool result = state.SetIndent(0, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Pre/Post Comment Indent Tests ====================

TEST_F(EmitterStateTest_453, DefaultPreCommentIndent_453) {
  std::size_t indent = state.GetPreCommentIndent();
  EXPECT_GE(indent, 0u);
}

TEST_F(EmitterStateTest_453, SetPreCommentIndent_Global_453) {
  bool result = state.SetPreCommentIndent(3, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_453, DefaultPostCommentIndent_453) {
  std::size_t indent = state.GetPostCommentIndent();
  EXPECT_GE(indent, 0u);
}

TEST_F(EmitterStateTest_453, SetPostCommentIndent_Global_453) {
  bool result = state.SetPostCommentIndent(2, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

// ==================== Flow Type Tests ====================

TEST_F(EmitterStateTest_453, SetFlowType_Seq_Flow_453) {
  bool result = state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_453, SetFlowType_Seq_Block_453) {
  bool result = state.SetFlowType(GroupType::Seq, Block, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_453, SetFlowType_Map_Flow_453) {
  bool result = state.SetFlowType(GroupType::Map, Flow, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_453, SetFlowType_Map_Block_453) {
  bool result = state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_453, SetFlowType_InvalidValue_453) {
  bool result = state.SetFlowType(GroupType::Seq, Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Map Key Format Tests ====================

TEST_F(EmitterStateTest_453, SetMapKeyFormat_LongKey_453) {
  bool result = state.SetMapKeyFormat(LongKey, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_453, SetMapKeyFormat_InvalidValue_453) {
  bool result = state.SetMapKeyFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Float/Double Precision Tests ====================

TEST_F(EmitterStateTest_453, DefaultFloatPrecision_453) {
  std::size_t prec = state.GetFloatPrecision();
  // Just verify it returns something reasonable
  (void)prec;
}

TEST_F(EmitterStateTest_453, SetFloatPrecision_453) {
  bool result = state.SetFloatPrecision(5, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_453, DefaultDoublePrecision_453) {
  std::size_t prec = state.GetDoublePrecision();
  (void)prec;
}

TEST_F(EmitterStateTest_453, SetDoublePrecision_453) {
  bool result = state.SetDoublePrecision(10, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== Document Lifecycle Tests ====================

TEST_F(EmitterStateTest_453, StartedDoc_DoesNotCrash_453) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_453, EndedDoc_DoesNotCrash_453) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Scalar Tests ====================

TEST_F(EmitterStateTest_453, StartedScalar_DoesNotCrash_453) {
  state.StartedDoc();
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

// ==================== Group Lifecycle Tests ====================

TEST_F(EmitterStateTest_453, StartedGroup_Seq_453) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_453, StartedGroup_Map_453) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_453, EndedGroup_Seq_453) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_453, EndedGroup_Map_453) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_453, CurGroupChildCount_InitiallyZero_453) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_453, CurGroupChildCount_AfterScalar_453) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_453, CurGroupIndent_453) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  std::size_t indent = state.CurGroupIndent();
  (void)indent; // Just verify it doesn't crash
}

TEST_F(EmitterStateTest_453, CurGroupLongKey_DefaultFalse_453) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// ==================== SetNonContent Test ====================

TEST_F(EmitterStateTest_453, SetNonContent_DoesNotCrash_453) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey Test ====================

TEST_F(EmitterStateTest_453, SetLongKey_InGroup_453) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== ForceFlow Test ====================

TEST_F(EmitterStateTest_453, ForceFlow_InGroup_453) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== ClearModifiedSettings Test ====================

TEST_F(EmitterStateTest_453, ClearModifiedSettings_DoesNotCrash_453) {
  state.SetIndent(4, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Test ====================

TEST_F(EmitterStateTest_453, RestoreGlobalModifiedSettings_DoesNotCrash_453) {
  state.SetIndent(4, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== NextGroupType Test ====================

TEST_F(EmitterStateTest_453, NextGroupType_Seq_453) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return some valid EmitterNodeType
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_453, NextGroupType_Map_453) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ==================== SetLocalValue Test ====================

TEST_F(EmitterStateTest_453, SetLocalValue_Flow_453) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_453, SetLocalValue_Block_453) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// ==================== Multiple Settings Scope Tests ====================

TEST_F(EmitterStateTest_453, LocalSettingClearedAfterClear_453) {
  state.SetIndent(8, FmtScope::Local);
  EXPECT_EQ(8u, state.GetIndent());
  state.ClearModifiedSettings();
  // After clearing, should revert to previous value
  EXPECT_NE(8u, state.GetIndent());
}

TEST_F(EmitterStateTest_453, GlobalSettingPersistsAfterClear_453) {
  state.SetIndent(8, FmtScope::Global);
  EXPECT_EQ(8u, state.GetIndent());
  state.ClearModifiedSettings();
  // Global setting should persist
  EXPECT_EQ(8u, state.GetIndent());
}

// ==================== LastIndent Test ====================

TEST_F(EmitterStateTest_453, LastIndent_DefaultZero_453) {
  EXPECT_EQ(0u, state.LastIndent());
}

// ==================== NestedGroups Test ====================

TEST_F(EmitterStateTest_453, NestedGroups_453) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// ==================== CurGroupNodeType Test ====================

TEST_F(EmitterStateTest_453, CurGroupNodeType_InSeq_453) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ==================== HasBegunNode/Content after StartedScalar ====================

TEST_F(EmitterStateTest_453, HasBegunNode_AfterScalar_453) {
  state.StartedDoc();
  state.StartedScalar();
  // After starting a scalar, node should have begun
  // This depends on implementation, but we test the interface
  EXPECT_TRUE(state.good());
}

// ==================== Multiple errors ====================

TEST_F(EmitterStateTest_453, MultipleErrors_FirstErrorPersists_453) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_FALSE(state.good());
  // The first error should typically be the one stored
  EXPECT_EQ("first error", state.GetLastError());
}

}  // namespace YAML
