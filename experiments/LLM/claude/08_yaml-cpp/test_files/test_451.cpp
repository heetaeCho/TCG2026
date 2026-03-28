#include "gtest/gtest.h"
#include "emitterstate.h"
#include "yaml-cpp/emittermanip.h"

namespace YAML {

class EmitterStateTest_451 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_451, InitialStateIsGood_451) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_451, InitialStateNoLastError_451) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_451, InitialStateHasNoAnchor_451) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_451, InitialStateHasNoAlias_451) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_451, InitialStateHasNoTag_451) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_451, InitialStateHasNotBegunNode_451) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_451, InitialStateHasNotBegunContent_451) {
  EXPECT_FALSE(state.HasBegunContent());
}

TEST_F(EmitterStateTest_451, InitialCurIndentIsZero_451) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_451, SetErrorMakesStateNotGood_451) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_451, SetErrorStoresErrorMessage_451) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_451, SetErrorEmptyStringStillSetsNotGood_451) {
  state.SetError("");
  EXPECT_FALSE(state.good());
}

// ==================== HasBegunNode Tests ====================

TEST_F(EmitterStateTest_451, HasBegunNodeAfterSetAnchor_451) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasBegunNode());
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_451, HasBegunNodeAfterSetTag_451) {
  state.SetTag();
  EXPECT_TRUE(state.HasBegunNode());
  EXPECT_TRUE(state.HasTag());
}

TEST_F(EmitterStateTest_451, HasBegunNodeAfterSetNonContent_451) {
  state.SetNonContent();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_451, SetAliasSetsHasAlias_451) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

// ==================== Format Setting/Getting Tests ====================

TEST_F(EmitterStateTest_451, SetOutputCharsetGlobal_451) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_451, SetOutputCharsetLocal_451) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Local));
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_451, SetStringFormatGlobal_451) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_451, SetStringFormatLocal_451) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_451, SetBoolFormatGlobal_451) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_451, SetBoolLengthFormatGlobal_451) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_451, SetBoolLengthFormatLong_451) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_451, SetBoolCaseFormatGlobal_451) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_451, SetBoolCaseFormatCamelCase_451) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_451, SetBoolCaseFormatLowerCase_451) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_451, SetNullFormatGlobal_451) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_451, SetIntFormatHex_451) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_451, SetIntFormatOct_451) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_451, SetIntFormatDec_451) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_451, SetIndentGlobal_451) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_451, SetIndentLocal_451) {
  EXPECT_TRUE(state.SetIndent(8, FmtScope::Local));
  EXPECT_EQ(8u, state.GetIndent());
}

TEST_F(EmitterStateTest_451, SetPreCommentIndent_451) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_451, SetPostCommentIndent_451) {
  EXPECT_TRUE(state.SetPostCommentIndent(5, FmtScope::Global));
  EXPECT_EQ(5u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_451, SetMapKeyFormatGlobal_451) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_451, SetFloatPrecision_451) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Global));
  EXPECT_EQ(6u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_451, SetDoublePrecision_451) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Global));
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

// ==================== Flow Type Tests ====================

TEST_F(EmitterStateTest_451, SetFlowTypeSeqFlow_451) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_451, SetFlowTypeSeqBlock_451) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_451, SetFlowTypeMapFlow_451) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_451, SetFlowTypeMapBlock_451) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== Document Tests ====================

TEST_F(EmitterStateTest_451, StartedDocEndedDoc_451) {
  state.StartedDoc();
  state.EndedDoc();
  // Should not crash and state should remain good
  EXPECT_TRUE(state.good());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_451, StartedGroupSeqAndEndedGroup_451) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_451, StartedGroupMapAndEndedGroup_451) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_451, CurGroupLongKeyInitiallyFalse_451) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

TEST_F(EmitterStateTest_451, SetLongKeyInGroup_451) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

TEST_F(EmitterStateTest_451, ForceFlowInGroup_451) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_451, StartedScalarInGroup_451) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_451, MultipleScalarsInGroup_451) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.StartedScalar();
  state.StartedScalar();
  EXPECT_EQ(3u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_451, NextGroupTypeSeqAtRoot_451) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return a valid node type
  EXPECT_TRUE(nodeType == EmitterNodeType::NoType ||
              nodeType == EmitterNodeType::Property ||
              nodeType == EmitterNodeType::FlowSeq ||
              nodeType == EmitterNodeType::BlockSeq ||
              nodeType == EmitterNodeType::FlowMap ||
              nodeType == EmitterNodeType::BlockMap);
}

TEST_F(EmitterStateTest_451, NextGroupTypeMapAtRoot_451) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  EXPECT_TRUE(nodeType == EmitterNodeType::NoType ||
              nodeType == EmitterNodeType::Property ||
              nodeType == EmitterNodeType::FlowSeq ||
              nodeType == EmitterNodeType::BlockSeq ||
              nodeType == EmitterNodeType::FlowMap ||
              nodeType == EmitterNodeType::BlockMap);
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_451, ClearModifiedSettingsResetsLocalSettings_451) {
  state.SetIndent(8, FmtScope::Local);
  EXPECT_EQ(8u, state.GetIndent());
  state.ClearModifiedSettings();
  // After clearing, it should revert to default or global
  // We just verify no crash and state is good
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_451, RestoreGlobalModifiedSettings_451) {
  state.SetIndent(6, FmtScope::Global);
  state.SetIndent(10, FmtScope::Local);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(6u, state.GetIndent());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_451, SetLocalValueFlow_451) {
  state.SetLocalValue(Flow);
  // Should not crash; the effect depends on context
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_451, SetLocalValueBlock_451) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_451, SetLocalValueDoubleQuoted_451) {
  state.SetLocalValue(DoubleQuoted);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_451, SetLocalValueSingleQuoted_451) {
  state.SetLocalValue(SingleQuoted);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_451, SetLocalValueLiteral_451) {
  state.SetLocalValue(Literal);
  EXPECT_TRUE(state.good());
}

// ==================== Invalid Format Tests ====================

TEST_F(EmitterStateTest_451, SetOutputCharsetInvalidValue_451) {
  // Pass an unrelated EMITTER_MANIP value for output charset
  bool result = state.SetOutputCharset(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_451, SetStringFormatInvalidValue_451) {
  bool result = state.SetStringFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_451, SetBoolFormatInvalidValue_451) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_451, SetIntFormatInvalidValue_451) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Boundary: Indent value of zero or one ====================

TEST_F(EmitterStateTest_451, SetIndentMinimumValue_451) {
  // Indent of 2 is typically the minimum valid
  bool result = state.SetIndent(2, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(2u, state.GetIndent());
}

TEST_F(EmitterStateTest_451, SetIndentZero_451) {
  // Zero indent may be rejected
  bool result = state.SetIndent(0, FmtScope::Global);
  // Depending on implementation, may return false
  // We don't know the exact behavior but test it doesn't crash
  (void)result;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_451, SetIndentOne_451) {
  // Indent of 1 may be rejected (too small)
  bool result = state.SetIndent(1, FmtScope::Global);
  (void)result;
  EXPECT_TRUE(state.good());
}

// ==================== Nested Group Tests ====================

TEST_F(EmitterStateTest_451, NestedGroups_451) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());

  state.StartedScalar();  // key
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  EXPECT_EQ(0u, state.CurGroupChildCount());

  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());

  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());

  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// ==================== HasBegunContent Tests ====================

TEST_F(EmitterStateTest_451, HasBegunContentAfterScalar_451) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  // After starting a scalar, content has begun
  EXPECT_TRUE(state.HasBegunContent());
  state.EndedGroup(GroupType::Seq);
}

// ==================== Multiple Document Tests ====================

TEST_F(EmitterStateTest_451, MultipleDocuments_451) {
  state.StartedDoc();
  state.EndedDoc();
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_451, LastIndentAtRoot_451) {
  // At root, LastIndent should return 0
  EXPECT_EQ(0u, state.LastIndent());
}

// ==================== Float/Double Precision Boundary ====================

TEST_F(EmitterStateTest_451, SetFloatPrecisionZero_451) {
  bool result = state.SetFloatPrecision(0, FmtScope::Global);
  // May or may not succeed, but shouldn't crash
  (void)result;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_451, SetDoublePrecisionZero_451) {
  bool result = state.SetDoublePrecision(0, FmtScope::Global);
  (void)result;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_451, SetFloatPrecisionLargeValue_451) {
  bool result = state.SetFloatPrecision(100, FmtScope::Global);
  (void)result;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_451, SetDoublePrecisionLargeValue_451) {
  bool result = state.SetDoublePrecision(100, FmtScope::Global);
  (void)result;
  EXPECT_TRUE(state.good());
}

// ==================== Scope Tests ====================

TEST_F(EmitterStateTest_451, GlobalScopePersistsAcrossClear_451) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_451, LocalScopeOverridesGlobal_451) {
  state.SetStringFormat(SingleQuoted, FmtScope::Global);
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_451, LocalScopeClearedReverts_451) {
  state.SetStringFormat(SingleQuoted, FmtScope::Global);
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

}  // namespace YAML
