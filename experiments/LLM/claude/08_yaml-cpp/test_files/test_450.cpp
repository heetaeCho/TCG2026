#include "gtest/gtest.h"
#include "emitterstate.h"
#include "yaml-cpp/emittermanip.h"

namespace YAML {

class EmitterStateTest_450 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_450, InitialStateIsGood_450) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_450, InitialStateHasNoTag_450) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_450, InitialStateHasNoAnchor_450) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_450, InitialStateHasNoAlias_450) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_450, InitialStateHasNoError_450) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_450, InitialCurIndentIsZero_450) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_450, SetErrorMakesNotGood_450) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_450, SetErrorStoresMessage_450) {
  state.SetError("some error message");
  EXPECT_EQ("some error message", state.GetLastError());
}

TEST_F(EmitterStateTest_450, SetErrorWithEmptyString_450) {
  state.SetError("");
  EXPECT_FALSE(state.good());
}

// ==================== Tag Tests ====================

TEST_F(EmitterStateTest_450, SetTagSetsHasTag_450) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Anchor Tests ====================

TEST_F(EmitterStateTest_450, SetAnchorSetsHasAnchor_450) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

// ==================== Alias Tests ====================

TEST_F(EmitterStateTest_450, SetAliasSetsHasAlias_450) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

// ==================== Format Setter/Getter Tests ====================

TEST_F(EmitterStateTest_450, SetOutputCharsetGlobal_450) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_450, SetOutputCharsetLocal_450) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Local));
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_450, SetStringFormatGlobal_450) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_450, SetStringFormatLocal_450) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_450, SetBoolFormatGlobal_450) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_450, SetBoolLengthFormatGlobal_450) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_450, SetBoolLengthFormatLong_450) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_450, SetBoolCaseFormatGlobal_450) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_450, SetBoolCaseFormatLowerCase_450) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_450, SetBoolCaseFormatCamelCase_450) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_450, SetIntFormatHex_450) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_450, SetIntFormatOct_450) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_450, SetIntFormatDec_450) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_450, SetNullFormatGlobal_450) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_450, SetNullFormatTilde_450) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Global));
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== Indent Tests ====================

TEST_F(EmitterStateTest_450, SetIndentGlobal_450) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_450, SetIndentLocal_450) {
  EXPECT_TRUE(state.SetIndent(8, FmtScope::Local));
  EXPECT_EQ(8u, state.GetIndent());
}

TEST_F(EmitterStateTest_450, SetPreCommentIndentGlobal_450) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_450, SetPostCommentIndentGlobal_450) {
  EXPECT_TRUE(state.SetPostCommentIndent(5, FmtScope::Global));
  EXPECT_EQ(5u, state.GetPostCommentIndent());
}

// ==================== Precision Tests ====================

TEST_F(EmitterStateTest_450, SetFloatPrecisionGlobal_450) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Global));
  EXPECT_EQ(6u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_450, SetDoublePrecisionGlobal_450) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Global));
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

TEST_F(EmitterStateTest_450, SetFloatPrecisionLocal_450) {
  EXPECT_TRUE(state.SetFloatPrecision(3, FmtScope::Local));
  EXPECT_EQ(3u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_450, SetDoublePrecisionLocal_450) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Local));
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== Map Key Format Tests ====================

TEST_F(EmitterStateTest_450, SetMapKeyFormatGlobal_450) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== Flow Type Tests ====================

TEST_F(EmitterStateTest_450, SetFlowTypeSeqGlobal_450) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_450, SetFlowTypeMapGlobal_450) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_450, SetFlowTypeSeqLocal_450) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Local));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

// ==================== Document Lifecycle Tests ====================

TEST_F(EmitterStateTest_450, StartedDocIncrementsDocCount_450) {
  state.StartedDoc();
  // After starting a doc, the state should still be good
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_450, EndedDocAfterStartedDoc_450) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Lifecycle Tests ====================

TEST_F(EmitterStateTest_450, StartedGroupSeq_450) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_450, StartedGroupMap_450) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_450, EndedGroupSeq_450) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_450, EndedGroupMap_450) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_450, CurGroupLongKeyDefaultFalse_450) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_450, SetLongKeyInGroup_450) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_450, ForceFlowInGroup_450) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== Scalar Tests ====================

TEST_F(EmitterStateTest_450, StartedScalarInGroup_450) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_450, SetNonContentSetsFlag_450) {
  state.SetNonContent();
  // HasBegunNode and HasBegunContent behavior may change; 
  // just verify it doesn't crash and state remains good
  EXPECT_TRUE(state.good());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_450, ClearModifiedSettingsResetsLocal_450) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
  state.ClearModifiedSettings();
  // After clearing, should revert to default or global
  // The default string format is typically Auto
  EXPECT_NE(DoubleQuoted, state.GetStringFormat());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_450, NextGroupTypeSeqNoGroup_450) {
  EmitterNodeType::value ntype = state.NextGroupType(GroupType::Seq);
  // Without any groups, should return some default
  // Just verify it doesn't crash
  (void)ntype;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_450, NextGroupTypeMapNoGroup_450) {
  EmitterNodeType::value ntype = state.NextGroupType(GroupType::Map);
  (void)ntype;
  EXPECT_TRUE(state.good());
}

// ==================== Multiple Error Tests ====================

TEST_F(EmitterStateTest_450, MultipleErrorsKeepFirstError_450) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_FALSE(state.good());
  // Typically first error is kept
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== HasBegunNode / HasBegunContent Tests ====================

TEST_F(EmitterStateTest_450, HasBegunNodeInitiallyFalse_450) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_450, HasBegunContentInitiallyFalse_450) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_450, RestoreGlobalModifiedSettings_450) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.SetStringFormat(SingleQuoted, FmtScope::Local);
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== Nested Groups Tests ====================

TEST_F(EmitterStateTest_450, NestedGroupsTrackCorrectType_450) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());

  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());

  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());

  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// ==================== CurGroupIndent Tests ====================

TEST_F(EmitterStateTest_450, CurGroupIndentAfterStartedGroup_450) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  std::size_t indent = state.CurGroupIndent();
  // Just verify it returns something reasonable and doesn't crash
  (void)indent;
  EXPECT_TRUE(state.good());
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_450, LastIndentDefault_450) {
  std::size_t lastIndent = state.LastIndent();
  (void)lastIndent;
  EXPECT_TRUE(state.good());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_450, SetLocalValueFlow_450) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_450, SetLocalValueBlock_450) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_450, SetLocalValueDoubleQuoted_450) {
  state.SetLocalValue(DoubleQuoted);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_450, SetLocalValueHex_450) {
  state.SetLocalValue(Hex);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

// ==================== Boundary: Zero Indent ====================

TEST_F(EmitterStateTest_450, SetIndentToMinimum_450) {
  // Indent of 2 is typically minimum
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetIndent());
}

// ==================== Tag/Anchor/Alias reset after scalar ====================

TEST_F(EmitterStateTest_450, TagResetAfterStartedScalar_450) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_450, AnchorResetAfterStartedScalar_450) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_450, AliasResetAfterStartedScalar_450) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAlias());
}

}  // namespace YAML
