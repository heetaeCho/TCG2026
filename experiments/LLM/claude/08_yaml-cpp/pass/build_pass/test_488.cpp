#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_488 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_488, InitialStateIsGood_488) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_488, InitialLastErrorIsEmpty_488) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_488, InitialHasNoAnchor_488) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_488, InitialHasNoAlias_488) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_488, InitialHasNoTag_488) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_488, InitialCurIndentIsZero_488) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== Error Handling Tests ====================

TEST_F(EmitterStateTest_488, SetErrorMakesStateNotGood_488) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_488, SetErrorStoresLastError_488) {
  state.SetError("some error message");
  EXPECT_EQ("some error message", state.GetLastError());
}

TEST_F(EmitterStateTest_488, SetErrorOnlyKeepsFirstError_488) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically first error is kept
  EXPECT_FALSE(state.good());
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_488, SetAnchorSetsHasAnchor_488) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_488, SetAliasSetsHasAlias_488) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_488, SetTagSetsHasTag_488) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Format Setting Tests with Global Scope ====================

TEST_F(EmitterStateTest_488, SetOutputCharsetGlobalScope_488) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_488, SetStringFormatGlobalScope_488) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_488, SetBoolFormatGlobalScope_488) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_488, SetBoolLengthFormatGlobalScope_488) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_488, SetBoolCaseFormatGlobalScope_488) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_488, SetNullFormatGlobalScope_488) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_488, SetIntFormatGlobalScope_488) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_488, SetIndentGlobalScope_488) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_488, SetPreCommentIndentGlobalScope_488) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_488, SetPostCommentIndentGlobalScope_488) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_488, SetMapKeyFormatGlobalScope_488) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_488, SetFloatPrecisionGlobalScope_488) {
  EXPECT_TRUE(state.SetFloatPrecision(5, FmtScope::Global));
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_488, SetDoublePrecisionGlobalScope_488) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Global));
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== Flow Type Tests ====================

TEST_F(EmitterStateTest_488, SetFlowTypeSeqGlobalScope_488) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_488, SetFlowTypeMapGlobalScope_488) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== Local Scope Setting Tests ====================

TEST_F(EmitterStateTest_488, SetStringFormatLocalScope_488) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_488, SetIntFormatLocalScope_488) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Local));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_488, ClearModifiedSettingsRestoresLocalSettings_488) {
  // Set a local value then clear
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
  state.ClearModifiedSettings();
  // After clearing, should revert to default
  EXPECT_NE(DoubleQuoted, state.GetStringFormat());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_488, RestoreGlobalModifiedSettingsRestoresGlobal_488) {
  // Get original default
  EMITTER_MANIP original = state.GetStringFormat();
  // Set global
  state.SetStringFormat(SingleQuoted, FmtScope::Global);
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
  // Restore global modified settings
  state.RestoreGlobalModifiedSettings();
  // After restore, should go back to original default
  EXPECT_EQ(original, state.GetStringFormat());
}

TEST_F(EmitterStateTest_488, RestoreGlobalModifiedSettingsOnFreshState_488) {
  // Calling restore on a fresh state should not crash
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_488, RestoreGlobalModifiedSettingsMultipleTimes_488) {
  state.SetIntFormat(Hex, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== Document State Tests ====================

TEST_F(EmitterStateTest_488, StartedDocAndEndedDoc_488) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_488, MultipleDocuments_488) {
  state.StartedDoc();
  state.EndedDoc();
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_488, StartedGroupSeq_488) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_488, StartedGroupMap_488) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_488, EndedGroupSeq_488) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_488, EndedGroupMap_488) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_488, CurGroupChildCountInitiallyZero_488) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_488, CurGroupLongKeyInitiallyFalse_488) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_488, SetLocalValueFlow_488) {
  state.SetLocalValue(Flow);
  // Should not crash and state should remain good
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_488, SetLocalValueBlock_488) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// ==================== Scalar Tests ====================

TEST_F(EmitterStateTest_488, StartedScalarClearsFlags_488) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAnchor();
  state.SetTag();
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_488, NextGroupTypeSeq_488) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // The result should be a valid EmitterNodeType
  EXPECT_TRUE(nodeType == EmitterNodeType::NoType ||
              nodeType == EmitterNodeType::Property ||
              nodeType == EmitterNodeType::Scalar ||
              nodeType == EmitterNodeType::FlowSeq ||
              nodeType == EmitterNodeType::BlockSeq ||
              nodeType == EmitterNodeType::FlowMap ||
              nodeType == EmitterNodeType::BlockMap);
}

TEST_F(EmitterStateTest_488, NextGroupTypeMap_488) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  EXPECT_TRUE(nodeType == EmitterNodeType::NoType ||
              nodeType == EmitterNodeType::Property ||
              nodeType == EmitterNodeType::Scalar ||
              nodeType == EmitterNodeType::FlowSeq ||
              nodeType == EmitterNodeType::BlockSeq ||
              nodeType == EmitterNodeType::FlowMap ||
              nodeType == EmitterNodeType::BlockMap);
}

// ==================== Boundary Conditions ====================

TEST_F(EmitterStateTest_488, SetIndentBoundaryMinimum_488) {
  // Setting indent to minimum (e.g., 1)
  EXPECT_TRUE(state.SetIndent(1, FmtScope::Global));
}

TEST_F(EmitterStateTest_488, SetIndentBoundaryZero_488) {
  // Zero indent may or may not be valid
  bool result = state.SetIndent(0, FmtScope::Global);
  // Just verify it doesn't crash; result depends on implementation
  (void)result;
}

TEST_F(EmitterStateTest_488, SetFloatPrecisionZero_488) {
  bool result = state.SetFloatPrecision(0, FmtScope::Global);
  (void)result;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_488, SetDoublePrecisionZero_488) {
  bool result = state.SetDoublePrecision(0, FmtScope::Global);
  (void)result;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_488, SetFloatPrecisionLargeValue_488) {
  bool result = state.SetFloatPrecision(100, FmtScope::Global);
  (void)result;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_488, SetDoublePrecisionLargeValue_488) {
  bool result = state.SetDoublePrecision(100, FmtScope::Global);
  (void)result;
  EXPECT_TRUE(state.good());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_488, SetNonContent_488) {
  state.SetNonContent();
  // The effect should be observable through HasBegunNode/HasBegunContent
  EXPECT_TRUE(state.good());
}

// ==================== HasBegunNode / HasBegunContent Tests ====================

TEST_F(EmitterStateTest_488, HasBegunNodeInitially_488) {
  // Fresh state should have specific behavior
  bool result = state.HasBegunNode();
  (void)result; // Just ensure it doesn't crash
}

TEST_F(EmitterStateTest_488, HasBegunContentInitially_488) {
  bool result = state.HasBegunContent();
  (void)result;
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_488, ForceFlowSetsFlowMode_488) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_488, SetLongKeyInGroup_488) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_488, LastIndentOnFreshState_488) {
  std::size_t lastIndent = state.LastIndent();
  EXPECT_EQ(0u, lastIndent);
}

// ==================== Default Format Values ====================

TEST_F(EmitterStateTest_488, DefaultOutputCharset_488) {
  EMITTER_MANIP charset = state.GetOutputCharset();
  // Should have a valid default
  (void)charset;
}

TEST_F(EmitterStateTest_488, DefaultStringFormat_488) {
  EMITTER_MANIP fmt = state.GetStringFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_488, DefaultBoolFormat_488) {
  EMITTER_MANIP fmt = state.GetBoolFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_488, DefaultIntFormat_488) {
  EMITTER_MANIP fmt = state.GetIntFormat();
  EXPECT_EQ(Dec, fmt);
}

TEST_F(EmitterStateTest_488, DefaultIndent_488) {
  std::size_t indent = state.GetIndent();
  EXPECT_EQ(2u, indent);
}

// ==================== Complex Scenario Tests ====================

TEST_F(EmitterStateTest_488, GlobalSettingPersistsAcrossDocuments_488) {
  state.SetIntFormat(Hex, FmtScope::Global);
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_488, LocalSettingClearedOnClear_488) {
  state.SetIntFormat(Hex, FmtScope::Local);
  EXPECT_EQ(Hex, state.GetIntFormat());
  state.ClearModifiedSettings();
  // Should revert to default (Dec)
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_488, GlobalSettingNotAffectedByClearModified_488) {
  state.SetIntFormat(Hex, FmtScope::Global);
  state.ClearModifiedSettings();
  // Global should still be Hex
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_488, NestedGroupsWorkCorrectly_488) {
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

TEST_F(EmitterStateTest_488, SetOutputCharsetInvalidValue_488) {
  // Try setting with an unrelated EMITTER_MANIP value
  bool result = state.SetOutputCharset(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_488, SetBoolFormatInvalidValue_488) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_488, SetIntFormatInvalidValue_488) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_488, SetStringFormatInvalidValue_488) {
  bool result = state.SetStringFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_488, DestructorDoesNotCrash_488) {
  // Create a state, do various operations, let it be destroyed
  {
    EmitterState tempState;
    tempState.SetIntFormat(Hex, FmtScope::Global);
    tempState.StartedDoc();
    tempState.StartedGroup(GroupType::Seq);
    tempState.SetAnchor();
    tempState.SetTag();
  }
  // If we reach here, destructor didn't crash
  EXPECT_TRUE(true);
}

}  // namespace YAML
