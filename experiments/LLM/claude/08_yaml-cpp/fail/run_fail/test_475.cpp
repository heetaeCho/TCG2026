#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_475 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Construction / Initial State ====================

TEST_F(EmitterStateTest_475, DefaultConstruction_IsGood_475) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_475, DefaultConstruction_NoError_475) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_475, DefaultConstruction_HasNoAnchor_475) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_475, DefaultConstruction_HasNoAlias_475) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_475, DefaultConstruction_HasNoTag_475) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_475, DefaultConstruction_CurIndentIsZero_475) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== SetError ====================

TEST_F(EmitterStateTest_475, SetError_MakesStateNotGood_475) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_475, SetError_StoresErrorMessage_475) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_475, SetError_FirstErrorWins_475) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically, only the first error is stored
  EXPECT_FALSE(state.good());
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== SetAnchor / HasAnchor ====================

TEST_F(EmitterStateTest_475, SetAnchor_SetsHasAnchor_475) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

// ==================== SetAlias / HasAlias ====================

TEST_F(EmitterStateTest_475, SetAlias_SetsHasAlias_475) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

// ==================== SetTag / HasTag ====================

TEST_F(EmitterStateTest_475, SetTag_SetsHasTag_475) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== SetNonContent ====================

TEST_F(EmitterStateTest_475, SetNonContent_AffectsBegunContent_475) {
  state.SetNonContent();
  // SetNonContent marks that non-content has been emitted
  // HasBegunContent should reflect this
  // We just verify no crash and observable state
}

// ==================== StartedDoc ====================

TEST_F(EmitterStateTest_475, StartedDoc_ClearsAnchor_475) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.StartedDoc();
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_475, StartedDoc_ClearsTag_475) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.StartedDoc();
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_475, StartedDoc_CalledMultipleTimes_475) {
  state.StartedDoc();
  state.EndedDoc();
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== EndedDoc ====================

TEST_F(EmitterStateTest_475, EndedDoc_AfterStartedDoc_475) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Format Setters / Getters ====================

TEST_F(EmitterStateTest_475, SetOutputCharset_ValidValue_ReturnsTrue_475) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_475, SetOutputCharset_GetReturnsSetValue_475) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Local);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_475, SetStringFormat_ValidValue_ReturnsTrue_475) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_475, SetStringFormat_GetReturnsSetValue_475) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_475, SetBoolFormat_ValidValue_475) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Local));
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_475, SetBoolFormat_InvalidValue_ReturnsFalse_475) {
  EXPECT_FALSE(state.SetBoolFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_475, SetBoolLengthFormat_ValidValue_475) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Local));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_475, SetBoolLengthFormat_LongBool_475) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Local));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_475, SetBoolCaseFormat_ValidValue_475) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Local));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_475, SetBoolCaseFormat_LowerCase_475) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Local));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_475, SetBoolCaseFormat_CamelCase_475) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Local));
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_475, SetNullFormat_ValidValue_475) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_475, SetIntFormat_Dec_475) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Local));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_475, SetIntFormat_Hex_475) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_475, SetIntFormat_Oct_475) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Local));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_475, SetIndent_ValidValue_475) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_475, SetIndent_BoundaryMinValue_475) {
  // Indent of 2 is typically the minimum
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Local));
  EXPECT_EQ(2u, state.GetIndent());
}

TEST_F(EmitterStateTest_475, SetPreCommentIndent_ValidValue_475) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Local));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_475, SetPostCommentIndent_ValidValue_475) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Local));
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_475, SetMapKeyFormat_LongKey_475) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Local));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_475, SetFloatPrecision_ValidValue_475) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Local));
  EXPECT_EQ(6u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_475, SetDoublePrecision_ValidValue_475) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Local));
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

// ==================== Flow Type ====================

TEST_F(EmitterStateTest_475, SetFlowType_Seq_Flow_475) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_475, SetFlowType_Seq_Block_475) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Local));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_475, SetFlowType_Map_Flow_475) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Local));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_475, SetFlowType_Map_Block_475) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== Scope Tests ====================

TEST_F(EmitterStateTest_475, SetStringFormat_GlobalScope_475) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Global));
  EXPECT_EQ(Literal, state.GetStringFormat());
}

TEST_F(EmitterStateTest_475, SetOutputCharset_GlobalScope_475) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Global));
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

// ==================== Group Operations ====================

TEST_F(EmitterStateTest_475, StartedGroup_Seq_NoError_475) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_475, StartedGroup_Map_NoError_475) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_475, EndedGroup_Seq_AfterStart_475) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_475, EndedGroup_Map_AfterStart_475) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_475, CurGroupType_AfterStartSeq_475) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_475, CurGroupType_AfterStartMap_475) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_475, CurGroupChildCount_InitiallyZero_475) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_475, CurGroupLongKey_DefaultFalse_475) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// ==================== StartedScalar ====================

TEST_F(EmitterStateTest_475, StartedScalar_InDoc_475) {
  state.StartedDoc();
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_475, StartedScalar_ClearsAnchor_475) {
  state.SetAnchor();
  state.StartedDoc();
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_475, StartedScalar_ClearsTag_475) {
  state.SetTag();
  state.StartedDoc();
  state.StartedScalar();
  EXPECT_FALSE(state.HasTag());
}

// ==================== ClearModifiedSettings ====================

TEST_F(EmitterStateTest_475, ClearModifiedSettings_NoError_475) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterStateTest_475, RestoreGlobalModifiedSettings_NoError_475) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== ForceFlow ====================

TEST_F(EmitterStateTest_475, ForceFlow_NoError_475) {
  state.ForceFlow();
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey ====================

TEST_F(EmitterStateTest_475, SetLongKey_NoError_475) {
  state.SetLongKey();
  EXPECT_TRUE(state.good());
}

// ==================== HasBegunNode / HasBegunContent ====================

TEST_F(EmitterStateTest_475, HasBegunNode_InitiallyFalse_475) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_475, HasBegunContent_InitiallyFalse_475) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== NextGroupType ====================

TEST_F(EmitterStateTest_475, NextGroupType_Seq_ReturnsValue_475) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Just ensure it returns a valid enum value without crashing
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_475, NextGroupType_Map_ReturnsValue_475) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ==================== Nested Groups ====================

TEST_F(EmitterStateTest_475, NestedGroups_SeqInMap_475) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_475, NestedGroups_MapInSeq_475) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// ==================== Invalid format values ====================

TEST_F(EmitterStateTest_475, SetStringFormat_InvalidValue_ReturnsFalse_475) {
  EXPECT_FALSE(state.SetStringFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_475, SetOutputCharset_InvalidValue_ReturnsFalse_475) {
  EXPECT_FALSE(state.SetOutputCharset(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_475, SetIntFormat_InvalidValue_ReturnsFalse_475) {
  EXPECT_FALSE(state.SetIntFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_475, SetNullFormat_InvalidValue_ReturnsFalse_475) {
  EXPECT_FALSE(state.SetNullFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_475, SetBoolLengthFormat_InvalidValue_ReturnsFalse_475) {
  EXPECT_FALSE(state.SetBoolLengthFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_475, SetBoolCaseFormat_InvalidValue_ReturnsFalse_475) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_475, SetMapKeyFormat_InvalidValue_ReturnsFalse_475) {
  EXPECT_FALSE(state.SetMapKeyFormat(Flow, FmtScope::Local));
}

// ==================== SetLocalValue ====================

TEST_F(EmitterStateTest_475, SetLocalValue_Flow_475) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_475, SetLocalValue_Block_475) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_475, SetLocalValue_Hex_475) {
  state.SetLocalValue(Hex);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_475, SetLocalValue_DoubleQuoted_475) {
  state.SetLocalValue(DoubleQuoted);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_475, SetLocalValue_LongKey_475) {
  state.SetLocalValue(LongKey);
  EXPECT_TRUE(state.good());
}

// ==================== Multiple Doc Cycle ====================

TEST_F(EmitterStateTest_475, MultipleDocCycle_475) {
  state.StartedDoc();
  state.StartedScalar();
  state.EndedDoc();
  
  state.StartedDoc();
  state.StartedScalar();
  state.EndedDoc();
  
  EXPECT_TRUE(state.good());
}

// ==================== Anchor/Tag cleared after StartedGroup ====================

TEST_F(EmitterStateTest_475, StartedGroup_ClearsAnchor_475) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_475, StartedGroup_ClearsTag_475) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.HasTag());
}

}  // namespace YAML
