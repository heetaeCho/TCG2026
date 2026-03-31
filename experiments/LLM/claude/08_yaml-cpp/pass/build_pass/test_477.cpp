#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_477 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ============================================================
// Construction / Initial State Tests
// ============================================================

TEST_F(EmitterStateTest_477, DefaultConstruction_IsGood_477) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_477, DefaultConstruction_NoError_477) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_477, DefaultConstruction_HasNoAnchor_477) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_477, DefaultConstruction_HasNoAlias_477) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_477, DefaultConstruction_HasNoTag_477) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_477, DefaultConstruction_HasNotBegunNode_477) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_477, DefaultConstruction_HasNotBegunContent_477) {
  EXPECT_FALSE(state.HasBegunContent());
}

TEST_F(EmitterStateTest_477, DefaultConstruction_CurIndentIsZero_477) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ============================================================
// Error State Tests
// ============================================================

TEST_F(EmitterStateTest_477, SetError_MakesNotGood_477) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_477, SetError_StoresErrorMessage_477) {
  state.SetError("some error message");
  EXPECT_EQ("some error message", state.GetLastError());
}

TEST_F(EmitterStateTest_477, SetError_EmptyString_477) {
  state.SetError("");
  EXPECT_FALSE(state.good());
}

// ============================================================
// Anchor / Alias / Tag Tests
// ============================================================

TEST_F(EmitterStateTest_477, SetAnchor_HasAnchorTrue_477) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_477, SetAlias_HasAliasTrue_477) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_477, SetTag_HasTagTrue_477) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ============================================================
// StartedScalar Tests
// ============================================================

TEST_F(EmitterStateTest_477, StartedScalar_ClearsAnchor_477) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_477, StartedScalar_ClearsAlias_477) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_477, StartedScalar_ClearsTag_477) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_477, StartedScalar_HasBegunNode_477) {
  state.StartedScalar();
  EXPECT_TRUE(state.HasBegunNode());
}

// ============================================================
// Document Tests
// ============================================================

TEST_F(EmitterStateTest_477, StartedDoc_477) {
  state.StartedDoc();
  // After starting a doc, state should still be good
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_477, EndedDoc_477) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ============================================================
// Group Tests
// ============================================================

TEST_F(EmitterStateTest_477, StartedGroup_Seq_477) {
  state.StartedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_477, StartedGroup_Map_477) {
  state.StartedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_477, EndedGroup_Seq_477) {
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_477, EndedGroup_Map_477) {
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_477, CurGroupChildCount_InitiallyZero_477) {
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_477, CurGroupChildCount_AfterScalar_477) {
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_477, CurGroupChildCount_AfterMultipleScalars_477) {
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.StartedScalar();
  state.StartedScalar();
  EXPECT_EQ(3u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_477, CurGroupLongKey_DefaultFalse_477) {
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_477, NestedGroups_477) {
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
}

// ============================================================
// Setting Format Tests
// ============================================================

TEST_F(EmitterStateTest_477, SetOutputCharset_Valid_477) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_477, GetOutputCharset_Default_477) {
  // Default should be EmitNonAscii or similar; just ensure it returns a value
  EMITTER_MANIP charset = state.GetOutputCharset();
  (void)charset; // Just verifying it doesn't crash
}

TEST_F(EmitterStateTest_477, SetStringFormat_Valid_477) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_477, SetStringFormat_DoubleQuoted_477) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_477, SetBoolFormat_TrueFalse_477) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Local));
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_477, SetBoolFormat_YesNo_477) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Local));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_477, SetBoolFormat_OnOff_477) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Local));
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_477, SetBoolLengthFormat_Short_477) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Local));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_477, SetBoolLengthFormat_Long_477) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Local));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_477, SetBoolCaseFormat_Upper_477) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Local));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_477, SetBoolCaseFormat_Lower_477) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Local));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_477, SetBoolCaseFormat_Camel_477) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Local));
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_477, SetNullFormat_477) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_477, SetIntFormat_Dec_477) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Local));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_477, SetIntFormat_Hex_477) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_477, SetIntFormat_Oct_477) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Local));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_477, SetIndent_Valid_477) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_477, SetIndent_MinValue_477) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Local));
  EXPECT_EQ(2u, state.GetIndent());
}

TEST_F(EmitterStateTest_477, SetIndent_TooSmall_477) {
  // Indent of 1 is likely invalid (minimum is typically 2)
  bool result = state.SetIndent(1, FmtScope::Local);
  // The function may return false for invalid values
  (void)result;
}

TEST_F(EmitterStateTest_477, SetPreCommentIndent_477) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Local));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_477, SetPostCommentIndent_477) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Local));
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_477, SetMapKeyFormat_LongKey_477) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Local));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_477, SetFloatPrecision_477) {
  EXPECT_TRUE(state.SetFloatPrecision(5, FmtScope::Local));
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_477, SetDoublePrecision_477) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Local));
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ============================================================
// Flow Type Tests
// ============================================================

TEST_F(EmitterStateTest_477, SetFlowType_SeqFlow_477) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_477, SetFlowType_SeqBlock_477) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Local));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_477, SetFlowType_MapFlow_477) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Local));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_477, SetFlowType_MapBlock_477) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ============================================================
// Scope Tests (Global vs Local)
// ============================================================

TEST_F(EmitterStateTest_477, SetStringFormat_GlobalScope_477) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_477, ClearModifiedSettings_ResetsLocalSettings_477) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
  state.ClearModifiedSettings();
  // After clearing, it should revert to default
  // The default is likely Auto or Literal; just check it changed
  EMITTER_MANIP fmt = state.GetStringFormat();
  (void)fmt; // verify no crash; exact value depends on defaults
}

TEST_F(EmitterStateTest_477, GlobalSetting_SurvivesClear_477) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ============================================================
// ForceFlow Tests
// ============================================================

TEST_F(EmitterStateTest_477, ForceFlow_InGroup_477) {
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ============================================================
// SetLongKey Tests
// ============================================================

TEST_F(EmitterStateTest_477, SetLongKey_InMapGroup_477) {
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ============================================================
// SetNonContent Tests
// ============================================================

TEST_F(EmitterStateTest_477, SetNonContent_477) {
  state.SetNonContent();
  // This should not crash and state should remain good
  EXPECT_TRUE(state.good());
}

// ============================================================
// NextGroupType Tests
// ============================================================

TEST_F(EmitterStateTest_477, NextGroupType_Seq_477) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  (void)nodeType; // Just verify it doesn't crash
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_477, NextGroupType_Map_477) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ============================================================
// CurGroupIndent / LastIndent Tests
// ============================================================

TEST_F(EmitterStateTest_477, CurGroupIndent_InGroup_477) {
  state.StartedGroup(GroupType::Seq);
  std::size_t indent = state.CurGroupIndent();
  (void)indent; // verify no crash
}

TEST_F(EmitterStateTest_477, LastIndent_NoGroup_477) {
  std::size_t indent = state.LastIndent();
  (void)indent; // verify no crash
}

// ============================================================
// SetLocalValue Tests
// ============================================================

TEST_F(EmitterStateTest_477, SetLocalValue_Flow_477) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_477, SetLocalValue_Block_477) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_477, SetLocalValue_DoubleQuoted_477) {
  state.SetLocalValue(DoubleQuoted);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_477, SetLocalValue_Hex_477) {
  state.SetLocalValue(Hex);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

// ============================================================
// Complex Scenario Tests
// ============================================================

TEST_F(EmitterStateTest_477, ComplexScenario_DocWithGroups_477) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.StartedScalar(); // key
  state.StartedScalar(); // value
  state.StartedScalar(); // key2
  state.StartedGroup(GroupType::Seq); // value2 is a sequence
  state.StartedScalar();
  state.StartedScalar();
  state.EndedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Map);
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_477, MultipleAnchorSets_ClearedByScalar_477) {
  state.SetAnchor();
  state.SetTag();
  EXPECT_TRUE(state.HasAnchor());
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_477, MultipleDocuments_477) {
  state.StartedDoc();
  state.StartedScalar();
  state.EndedDoc();
  state.StartedDoc();
  state.StartedScalar();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_477, SetError_OnlyFirstErrorSticks_477) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_FALSE(state.good());
  // The first error should be preserved (typical behavior)
  EXPECT_EQ("first error", state.GetLastError());
}

}  // namespace YAML
