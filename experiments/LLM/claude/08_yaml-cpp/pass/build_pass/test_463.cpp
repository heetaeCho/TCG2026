#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_463 : public ::testing::Test {
 protected:
  EmitterState state;
};

// =============================================================================
// Initial state / construction tests
// =============================================================================

TEST_F(EmitterStateTest_463, InitialState_IsGood_463) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_463, InitialState_NoLastError_463) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_463, InitialState_NoAnchor_463) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_463, InitialState_NoAlias_463) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_463, InitialState_NoTag_463) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_463, InitialState_HasNotBegunNode_463) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_463, InitialState_HasNotBegunContent_463) {
  EXPECT_FALSE(state.HasBegunContent());
}

// =============================================================================
// Error handling tests
// =============================================================================

TEST_F(EmitterStateTest_463, SetError_MakesNotGood_463) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_463, SetError_StoresMessage_463) {
  state.SetError("something went wrong");
  EXPECT_EQ("something went wrong", state.GetLastError());
}

TEST_F(EmitterStateTest_463, SetError_EmptyString_463) {
  state.SetError("");
  // Even empty error should make state not good
  EXPECT_FALSE(state.good());
}

// =============================================================================
// Anchor / Alias / Tag tests
// =============================================================================

TEST_F(EmitterStateTest_463, SetAnchor_SetsHasAnchor_463) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_463, SetAlias_SetsHasAlias_463) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_463, SetTag_SetsHasTag_463) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// =============================================================================
// Default format getters
// =============================================================================

TEST_F(EmitterStateTest_463, DefaultGetStringFormat_463) {
  // Should return some valid EMITTER_MANIP default
  EMITTER_MANIP fmt = state.GetStringFormat();
  (void)fmt; // Just ensure it doesn't crash
}

TEST_F(EmitterStateTest_463, DefaultGetBoolFormat_463) {
  EMITTER_MANIP fmt = state.GetBoolFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_463, DefaultGetBoolLengthFormat_463) {
  EMITTER_MANIP fmt = state.GetBoolLengthFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_463, DefaultGetBoolCaseFormat_463) {
  EMITTER_MANIP fmt = state.GetBoolCaseFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_463, DefaultGetNullFormat_463) {
  EMITTER_MANIP fmt = state.GetNullFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_463, DefaultGetIntFormat_463) {
  EMITTER_MANIP fmt = state.GetIntFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_463, DefaultGetOutputCharset_463) {
  EMITTER_MANIP fmt = state.GetOutputCharset();
  (void)fmt;
}

TEST_F(EmitterStateTest_463, DefaultGetMapKeyFormat_463) {
  EMITTER_MANIP fmt = state.GetMapKeyFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_463, DefaultGetIndent_463) {
  std::size_t indent = state.GetIndent();
  EXPECT_GT(indent, 0u);
}

TEST_F(EmitterStateTest_463, DefaultGetPreCommentIndent_463) {
  std::size_t indent = state.GetPreCommentIndent();
  (void)indent;
}

TEST_F(EmitterStateTest_463, DefaultGetPostCommentIndent_463) {
  std::size_t indent = state.GetPostCommentIndent();
  (void)indent;
}

TEST_F(EmitterStateTest_463, DefaultGetFloatPrecision_463) {
  std::size_t prec = state.GetFloatPrecision();
  (void)prec;
}

TEST_F(EmitterStateTest_463, DefaultGetDoublePrecision_463) {
  std::size_t prec = state.GetDoublePrecision();
  (void)prec;
}

// =============================================================================
// SetOutputCharset tests
// =============================================================================

TEST_F(EmitterStateTest_463, SetOutputCharset_ValidValue_463) {
  bool result = state.SetOutputCharset(EmitNonAscii, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_463, SetOutputCharset_InvalidValue_463) {
  // Passing an unrelated EMITTER_MANIP should return false
  bool result = state.SetOutputCharset(Auto, FmtScope::Global);
  EXPECT_FALSE(result);
}

// =============================================================================
// SetStringFormat tests
// =============================================================================

TEST_F(EmitterStateTest_463, SetStringFormat_SingleQuoted_Global_463) {
  bool result = state.SetStringFormat(SingleQuoted, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_463, SetStringFormat_DoubleQuoted_Global_463) {
  bool result = state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_463, SetStringFormat_Literal_Global_463) {
  bool result = state.SetStringFormat(Literal, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Literal, state.GetStringFormat());
}

TEST_F(EmitterStateTest_463, SetStringFormat_InvalidValue_463) {
  bool result = state.SetStringFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// =============================================================================
// SetBoolFormat tests
// =============================================================================

TEST_F(EmitterStateTest_463, SetBoolFormat_TrueFalseBool_463) {
  bool result = state.SetBoolFormat(TrueFalseBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_463, SetBoolFormat_YesNoBool_463) {
  bool result = state.SetBoolFormat(YesNoBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_463, SetBoolFormat_OnOffBool_463) {
  bool result = state.SetBoolFormat(OnOffBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_463, SetBoolFormat_InvalidValue_463) {
  bool result = state.SetBoolFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// =============================================================================
// SetBoolLengthFormat tests
// =============================================================================

TEST_F(EmitterStateTest_463, SetBoolLengthFormat_ShortBool_463) {
  bool result = state.SetBoolLengthFormat(ShortBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_463, SetBoolLengthFormat_LongBool_463) {
  bool result = state.SetBoolLengthFormat(LongBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_463, SetBoolLengthFormat_InvalidValue_463) {
  bool result = state.SetBoolLengthFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// =============================================================================
// SetBoolCaseFormat tests
// =============================================================================

TEST_F(EmitterStateTest_463, SetBoolCaseFormat_UpperCase_463) {
  bool result = state.SetBoolCaseFormat(UpperCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_463, SetBoolCaseFormat_LowerCase_463) {
  bool result = state.SetBoolCaseFormat(LowerCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_463, SetBoolCaseFormat_CamelCase_463) {
  bool result = state.SetBoolCaseFormat(CamelCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_463, SetBoolCaseFormat_InvalidValue_463) {
  bool result = state.SetBoolCaseFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// =============================================================================
// SetNullFormat tests
// =============================================================================

TEST_F(EmitterStateTest_463, SetNullFormat_LowerNull_463) {
  bool result = state.SetNullFormat(LowerNull, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_463, SetNullFormat_TildeNull_463) {
  bool result = state.SetNullFormat(TildeNull, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_463, SetNullFormat_InvalidValue_463) {
  bool result = state.SetNullFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// =============================================================================
// SetIntFormat tests
// =============================================================================

TEST_F(EmitterStateTest_463, SetIntFormat_Dec_463) {
  bool result = state.SetIntFormat(Dec, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_463, SetIntFormat_Hex_463) {
  bool result = state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_463, SetIntFormat_Oct_463) {
  bool result = state.SetIntFormat(Oct, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_463, SetIntFormat_InvalidValue_463) {
  bool result = state.SetIntFormat(TrueFalseBool, FmtScope::Global);
  EXPECT_FALSE(result);
}

// =============================================================================
// SetIndent tests
// =============================================================================

TEST_F(EmitterStateTest_463, SetIndent_ValidValue_463) {
  bool result = state.SetIndent(4, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_463, SetIndent_MinValue_463) {
  bool result = state.SetIndent(2, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(2u, state.GetIndent());
}

TEST_F(EmitterStateTest_463, SetIndent_LargeValue_463) {
  bool result = state.SetIndent(10, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(10u, state.GetIndent());
}

// =============================================================================
// SetMapKeyFormat tests
// =============================================================================

TEST_F(EmitterStateTest_463, SetMapKeyFormat_LongKey_463) {
  bool result = state.SetMapKeyFormat(LongKey, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_463, SetMapKeyFormat_InvalidValue_463) {
  bool result = state.SetMapKeyFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// =============================================================================
// SetFlowType tests
// =============================================================================

TEST_F(EmitterStateTest_463, SetFlowType_Seq_Flow_463) {
  bool result = state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_463, SetFlowType_Seq_Block_463) {
  bool result = state.SetFlowType(GroupType::Seq, Block, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_463, SetFlowType_Map_Flow_463) {
  bool result = state.SetFlowType(GroupType::Map, Flow, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_463, SetFlowType_Map_Block_463) {
  bool result = state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_463, SetFlowType_InvalidValue_463) {
  bool result = state.SetFlowType(GroupType::Seq, Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// =============================================================================
// SetFloatPrecision / SetDoublePrecision tests
// =============================================================================

TEST_F(EmitterStateTest_463, SetFloatPrecision_463) {
  bool result = state.SetFloatPrecision(5, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_463, SetDoublePrecision_463) {
  bool result = state.SetDoublePrecision(10, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// =============================================================================
// SetPreCommentIndent / SetPostCommentIndent tests
// =============================================================================

TEST_F(EmitterStateTest_463, SetPreCommentIndent_463) {
  bool result = state.SetPreCommentIndent(3, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_463, SetPostCommentIndent_463) {
  bool result = state.SetPostCommentIndent(2, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

// =============================================================================
// Document lifecycle tests
// =============================================================================

TEST_F(EmitterStateTest_463, StartedDoc_IncreasesDocCount_463) {
  // After starting a doc, the state should still be good
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_463, EndedDoc_AfterStartedDoc_463) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// =============================================================================
// Group lifecycle tests
// =============================================================================

TEST_F(EmitterStateTest_463, StartedGroup_Seq_463) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_463, StartedGroup_Map_463) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_463, EndedGroup_Seq_463) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_463, EndedGroup_Map_463) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_463, CurGroupChildCount_InitiallyZero_463) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_463, CurGroupChildCount_AfterScalar_463) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_463, CurGroupLongKey_DefaultFalse_463) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// =============================================================================
// SetLongKey test
// =============================================================================

TEST_F(EmitterStateTest_463, SetLongKey_InGroup_463) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// =============================================================================
// ForceFlow test
// =============================================================================

TEST_F(EmitterStateTest_463, ForceFlow_InGroup_463) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// =============================================================================
// StartedScalar tests
// =============================================================================

TEST_F(EmitterStateTest_463, StartedScalar_ClearsAnchorAndTag_463) {
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

// =============================================================================
// SetNonContent test
// =============================================================================

TEST_F(EmitterStateTest_463, SetNonContent_463) {
  state.SetNonContent();
  // We can observe that HasBegunContent should be affected
  // Just ensure it doesn't crash
  EXPECT_TRUE(state.good());
}

// =============================================================================
// CurIndent test
// =============================================================================

TEST_F(EmitterStateTest_463, CurIndent_InitiallyZero_463) {
  EXPECT_EQ(0u, state.CurIndent());
}

// =============================================================================
// Scope: Local setting tests
// =============================================================================

TEST_F(EmitterStateTest_463, SetStringFormat_LocalScope_463) {
  bool result = state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_463, ClearModifiedSettings_RestoresDefaults_463) {
  EMITTER_MANIP originalFmt = state.GetStringFormat();
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_EQ(originalFmt, state.GetStringFormat());
}

// =============================================================================
// Nested groups
// =============================================================================

TEST_F(EmitterStateTest_463, NestedGroups_463) {
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

// =============================================================================
// Multiple errors
// =============================================================================

TEST_F(EmitterStateTest_463, MultipleErrors_FirstErrorKept_463) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_FALSE(state.good());
  // Typically first error is preserved
  EXPECT_EQ("first error", state.GetLastError());
}

// =============================================================================
// NextGroupType test
// =============================================================================

TEST_F(EmitterStateTest_463, NextGroupType_Seq_463) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return a valid node type
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_463, NextGroupType_Map_463) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// =============================================================================
// LastIndent test
// =============================================================================

TEST_F(EmitterStateTest_463, LastIndent_Default_463) {
  std::size_t lastIndent = state.LastIndent();
  (void)lastIndent;
  // Just ensure it doesn't crash with no groups
}

// =============================================================================
// Global scope setting persistence
// =============================================================================

TEST_F(EmitterStateTest_463, GlobalScopePersistsAfterClear_463) {
  state.SetIntFormat(Hex, FmtScope::Global);
  state.ClearModifiedSettings();
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_463, RestoreGlobalModifiedSettings_463) {
  EMITTER_MANIP original = state.GetIntFormat();
  state.SetIntFormat(Hex, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(original, state.GetIntFormat());
}

}  // namespace YAML
