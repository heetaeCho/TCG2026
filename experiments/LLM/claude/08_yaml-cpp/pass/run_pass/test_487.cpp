#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_487 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_487, InitialState_IsGood_487) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_487, InitialState_NoError_487) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_487, InitialState_NoAnchor_487) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_487, InitialState_NoAlias_487) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_487, InitialState_NoTag_487) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_487, InitialState_CurIndent_487) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_487, SetError_MarksNotGood_487) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_487, SetError_StoresMessage_487) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_487, SetError_FirstErrorSticks_487) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically first error is kept
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_487, SetAnchor_HasAnchor_487) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_487, SetAlias_HasAlias_487) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_487, SetTag_HasTag_487) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Output Charset Tests ====================

TEST_F(EmitterStateTest_487, SetOutputCharset_UTF8_Global_487) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_487, SetOutputCharset_Local_487) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

// ==================== String Format Tests ====================

TEST_F(EmitterStateTest_487, SetStringFormat_SingleQuoted_Global_487) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_487, SetStringFormat_DoubleQuoted_Global_487) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_487, SetStringFormat_Literal_Global_487) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Global));
  EXPECT_EQ(Literal, state.GetStringFormat());
}

// ==================== Bool Format Tests ====================

TEST_F(EmitterStateTest_487, SetBoolFormat_TrueFalseBool_Global_487) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_487, SetBoolFormat_YesNoBool_Global_487) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_487, SetBoolFormat_OnOffBool_Global_487) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Global));
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

// ==================== Bool Length Format Tests ====================

TEST_F(EmitterStateTest_487, SetBoolLengthFormat_ShortBool_Global_487) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_487, SetBoolLengthFormat_LongBool_Global_487) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

// ==================== Bool Case Format Tests ====================

TEST_F(EmitterStateTest_487, SetBoolCaseFormat_UpperCase_Global_487) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_487, SetBoolCaseFormat_LowerCase_Global_487) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_487, SetBoolCaseFormat_CamelCase_Global_487) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

// ==================== Null Format Tests ====================

TEST_F(EmitterStateTest_487, SetNullFormat_LowerNull_Global_487) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_487, SetNullFormat_TildeNull_Global_487) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Global));
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== Int Format Tests ====================

TEST_F(EmitterStateTest_487, SetIntFormat_Dec_Global_487) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_487, SetIntFormat_Hex_Global_487) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_487, SetIntFormat_Oct_Global_487) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

// ==================== Indent Tests ====================

TEST_F(EmitterStateTest_487, SetIndent_ValidValue_Global_487) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_487, SetIndent_MinValue_Global_487) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetIndent());
}

TEST_F(EmitterStateTest_487, SetIndent_ZeroValue_Invalid_487) {
  // Setting indent to 0 should fail (indent must be >= 2)
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Global));
}

TEST_F(EmitterStateTest_487, SetIndent_OneValue_Invalid_487) {
  EXPECT_FALSE(state.SetIndent(1, FmtScope::Global));
}

// ==================== Pre/Post Comment Indent Tests ====================

TEST_F(EmitterStateTest_487, SetPreCommentIndent_ValidValue_487) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_487, SetPostCommentIndent_ValidValue_487) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

// ==================== Flow Type Tests ====================

TEST_F(EmitterStateTest_487, SetFlowType_Seq_Flow_Global_487) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_487, SetFlowType_Seq_Block_Global_487) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_487, SetFlowType_Map_Flow_Global_487) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_487, SetFlowType_Map_Block_Global_487) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== Map Key Format Tests ====================

TEST_F(EmitterStateTest_487, SetMapKeyFormat_LongKey_Global_487) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== Float/Double Precision Tests ====================

TEST_F(EmitterStateTest_487, SetFloatPrecision_ValidValue_487) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Global));
  EXPECT_EQ(6u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_487, SetDoublePrecision_ValidValue_487) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Global));
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

TEST_F(EmitterStateTest_487, SetFloatPrecision_Zero_487) {
  // Setting precision to 0 should still work or return false
  state.SetFloatPrecision(0, FmtScope::Global);
  // Just verifying it doesn't crash
}

TEST_F(EmitterStateTest_487, SetDoublePrecision_Zero_487) {
  state.SetDoublePrecision(0, FmtScope::Global);
  // Just verifying it doesn't crash
}

// ==================== Document Lifecycle Tests ====================

TEST_F(EmitterStateTest_487, StartedDoc_EndedDoc_487) {
  state.StartedDoc();
  state.EndedDoc();
  // Should remain in good state
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_487, StartedDoc_Multiple_487) {
  state.StartedDoc();
  state.EndedDoc();
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_487, StartedGroup_Seq_487) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_487, StartedGroup_Map_487) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_487, EndedGroup_Seq_487) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_487, EndedGroup_Map_487) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_487, NestedGroups_487) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_487, ClearModifiedSettings_NoChange_487) {
  // Should be safe to call on fresh state
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_487, ClearModifiedSettings_AfterLocalSetting_487) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  state.ClearModifiedSettings();
  // After clearing, local modifications should be reverted
  // The default string format should be restored
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_487, RestoreGlobalModifiedSettings_NoChange_487) {
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_487, SetLocalValue_Flow_487) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_487, SetLocalValue_Block_487) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// ==================== Scalar Tests ====================

TEST_F(EmitterStateTest_487, StartedScalar_487) {
  state.StartedDoc();
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

// ==================== HasBegunNode / HasBegunContent Tests ====================

TEST_F(EmitterStateTest_487, InitialState_HasBegunNode_487) {
  // Before any node has started
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_487, InitialState_HasBegunContent_487) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_487, SetNonContent_487) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_487, ForceFlow_487) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_487, SetLongKey_487) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== Scope Tests (Local vs Global) ====================

TEST_F(EmitterStateTest_487, SetStringFormat_Local_RestoresAfterClear_487) {
  EMITTER_MANIP original = state.GetStringFormat();
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
  state.ClearModifiedSettings();
  EXPECT_EQ(original, state.GetStringFormat());
}

TEST_F(EmitterStateTest_487, SetIntFormat_Local_RestoresAfterClear_487) {
  EMITTER_MANIP original = state.GetIntFormat();
  state.SetIntFormat(Hex, FmtScope::Local);
  EXPECT_EQ(Hex, state.GetIntFormat());
  state.ClearModifiedSettings();
  EXPECT_EQ(original, state.GetIntFormat());
}

TEST_F(EmitterStateTest_487, SetIndent_Global_PersistsAfterClear_487) {
  state.SetIndent(4, FmtScope::Global);
  state.ClearModifiedSettings();
  EXPECT_EQ(4u, state.GetIndent());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_487, NextGroupType_Seq_487) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return a valid node type
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_487, NextGroupType_Map_487) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ==================== Invalid Setting Values ====================

TEST_F(EmitterStateTest_487, SetOutputCharset_InvalidValue_487) {
  // Passing an invalid/unrelated EMITTER_MANIP value
  bool result = state.SetOutputCharset(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_487, SetStringFormat_InvalidValue_487) {
  bool result = state.SetStringFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_487, SetBoolFormat_InvalidValue_487) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_487, SetIntFormat_InvalidValue_487) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_487, LastIndent_Initial_487) {
  // Before any group, LastIndent should have some default
  std::size_t lastIndent = state.LastIndent();
  (void)lastIndent;
  EXPECT_TRUE(state.good());
}

// ==================== Multiple Clear Calls ====================

TEST_F(EmitterStateTest_487, ClearModifiedSettings_MultipleCalls_487) {
  state.ClearModifiedSettings();
  state.ClearModifiedSettings();
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== Combined Operations ====================

TEST_F(EmitterStateTest_487, ComplexWorkflow_DocWithNestedGroups_487) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetIndent(4, FmtScope::Local);
  state.StartedScalar();
  state.StartedScalar();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.EndedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Map);
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_487, SetAnchorThenStartScalar_ClearsAnchor_487) {
  state.StartedDoc();
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.StartedScalar();
  // After starting a scalar, anchor flag should be consumed
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_487, SetTagThenStartScalar_ClearsTag_487) {
  state.StartedDoc();
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_487, SetAliasThenStartScalar_ClearsAlias_487) {
  state.StartedDoc();
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAlias());
}

}  // namespace YAML
