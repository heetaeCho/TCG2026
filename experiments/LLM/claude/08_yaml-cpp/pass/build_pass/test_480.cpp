#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_480 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_480, InitialStateIsGood_480) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_480, InitialLastErrorIsEmpty_480) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_480, InitialCurGroupNodeTypeIsNoType_480) {
  EXPECT_EQ(EmitterNodeType::NoType, state.CurGroupNodeType());
}

TEST_F(EmitterStateTest_480, InitialHasAnchorIsFalse_480) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_480, InitialHasAliasIsFalse_480) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_480, InitialHasTagIsFalse_480) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_480, InitialCurIndentIsZero_480) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_480, SetErrorMakesStateNotGood_480) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_480, SetErrorSetsLastError_480) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_480, SetErrorOnlyFirstErrorIsKept_480) {
  state.SetError("first error");
  state.SetError("second error");
  // Usually the first error is kept
  EXPECT_FALSE(state.good());
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_480, SetAnchorSetsHasAnchor_480) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_480, SetAliasSetsHasAlias_480) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_480, SetTagSetsHasTag_480) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Document Tests ====================

TEST_F(EmitterStateTest_480, StartedDocWorks_480) {
  state.StartedDoc();
  // Should not crash, state should still be good
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_480, EndedDocWorks_480) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_480, StartedGroupSeqCurGroupType_480) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_480, StartedGroupMapCurGroupType_480) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_480, CurGroupChildCountInitiallyZero_480) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_480, StartedGroupThenEndedGroup_480) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  // After ending the only group, CurGroupNodeType should be NoType
  EXPECT_EQ(EmitterNodeType::NoType, state.CurGroupNodeType());
}

TEST_F(EmitterStateTest_480, NestedGroups_480) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
}

TEST_F(EmitterStateTest_480, CurGroupLongKeyDefaultFalse_480) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_480, CurGroupNodeTypeAfterStartingGroup_480) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // The node type should reflect the group's state
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  // It should be a valid node type (not NoType since we have a group)
  EXPECT_NE(EmitterNodeType::NoType, nodeType);
}

// ==================== Scalar Tests ====================

TEST_F(EmitterStateTest_480, StartedScalarInGroup_480) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  // After starting a scalar, child count should increase
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_480, MultipleScalarsIncreasesChildCount_480) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.StartedScalar();
  EXPECT_EQ(2u, state.CurGroupChildCount());
}

// ==================== Format Setting Tests ====================

TEST_F(EmitterStateTest_480, SetOutputCharsetGlobal_480) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_480, SetOutputCharsetLocal_480) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_480, SetStringFormatGlobal_480) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
}

TEST_F(EmitterStateTest_480, SetStringFormatLocal_480) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_480, SetBoolFormatGlobal_480) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_480, SetBoolLengthFormatGlobal_480) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_480, SetBoolCaseFormatGlobal_480) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
}

TEST_F(EmitterStateTest_480, SetNullFormatGlobal_480) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
}

TEST_F(EmitterStateTest_480, SetIntFormatGlobal_480) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
}

TEST_F(EmitterStateTest_480, SetIndentGlobal_480) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
}

TEST_F(EmitterStateTest_480, SetIndentTooSmall_480) {
  // Indent of 1 might be rejected (minimum is usually 2)
  bool result = state.SetIndent(1, FmtScope::Global);
  // We check the result but the spec says minimum indent should be 2
  // This tests boundary behavior
  (void)result;
}

TEST_F(EmitterStateTest_480, SetPreCommentIndent_480) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Global));
}

TEST_F(EmitterStateTest_480, SetPostCommentIndent_480) {
  EXPECT_TRUE(state.SetPostCommentIndent(1, FmtScope::Global));
}

TEST_F(EmitterStateTest_480, SetMapKeyFormat_480) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
}

TEST_F(EmitterStateTest_480, SetFloatPrecision_480) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Global));
}

TEST_F(EmitterStateTest_480, SetDoublePrecision_480) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Global));
}

// ==================== Get Format Tests ====================

TEST_F(EmitterStateTest_480, GetOutputCharsetDefault_480) {
  EMITTER_MANIP charset = state.GetOutputCharset();
  // Default should be EmitNonAscii or a valid charset value
  (void)charset;  // Just verifying no crash
}

TEST_F(EmitterStateTest_480, GetStringFormatDefault_480) {
  EMITTER_MANIP fmt = state.GetStringFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_480, GetBoolFormatDefault_480) {
  EMITTER_MANIP fmt = state.GetBoolFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_480, GetBoolLengthFormatDefault_480) {
  EMITTER_MANIP fmt = state.GetBoolLengthFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_480, GetBoolCaseFormatDefault_480) {
  EMITTER_MANIP fmt = state.GetBoolCaseFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_480, GetNullFormatDefault_480) {
  EMITTER_MANIP fmt = state.GetNullFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_480, GetIntFormatDefault_480) {
  EMITTER_MANIP fmt = state.GetIntFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_480, GetIndentDefault_480) {
  std::size_t indent = state.GetIndent();
  EXPECT_GT(indent, 0u);
}

TEST_F(EmitterStateTest_480, GetPreCommentIndentDefault_480) {
  std::size_t indent = state.GetPreCommentIndent();
  EXPECT_GT(indent, 0u);
}

TEST_F(EmitterStateTest_480, GetPostCommentIndentDefault_480) {
  std::size_t indent = state.GetPostCommentIndent();
  EXPECT_GT(indent, 0u);
}

TEST_F(EmitterStateTest_480, GetMapKeyFormatDefault_480) {
  EMITTER_MANIP fmt = state.GetMapKeyFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_480, GetFloatPrecisionDefault_480) {
  std::size_t prec = state.GetFloatPrecision();
  (void)prec;
}

TEST_F(EmitterStateTest_480, GetDoublePrecisionDefault_480) {
  std::size_t prec = state.GetDoublePrecision();
  (void)prec;
}

// ==================== SetThenGet Tests ====================

TEST_F(EmitterStateTest_480, SetThenGetIndent_480) {
  state.SetIndent(4, FmtScope::Global);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_480, SetThenGetStringFormat_480) {
  state.SetStringFormat(SingleQuoted, FmtScope::Global);
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_480, SetThenGetIntFormat_480) {
  state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_480, SetThenGetBoolFormat_480) {
  state.SetBoolFormat(YesNoBool, FmtScope::Global);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_480, SetThenGetNullFormat_480) {
  state.SetNullFormat(LowerNull, FmtScope::Global);
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

// ==================== Flow Type Tests ====================

TEST_F(EmitterStateTest_480, SetFlowTypeSeq_480) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_480, SetFlowTypeMap_480) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
}

TEST_F(EmitterStateTest_480, GetFlowTypeSeq_480) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_480, GetFlowTypeMap_480) {
  state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_480, NextGroupTypeSeq_480) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  (void)nodeType;  // Just verifying no crash
}

TEST_F(EmitterStateTest_480, NextGroupTypeMap_480) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_480, ForceFlowWorks_480) {
  state.ForceFlow();
  // Should not crash
  EXPECT_TRUE(state.good());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_480, SetLocalValueFlow_480) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_480, SetLocalValueBlock_480) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_480, ClearModifiedSettingsWorks_480) {
  state.SetStringFormat(SingleQuoted, FmtScope::Local);
  state.ClearModifiedSettings();
  // Settings should revert to defaults (or global)
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_480, RestoreGlobalModifiedSettingsWorks_480) {
  state.SetStringFormat(SingleQuoted, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

// ==================== HasBegunNode / HasBegunContent Tests ====================

TEST_F(EmitterStateTest_480, HasBegunNodeInitiallyFalse_480) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_480, HasBegunContentInitiallyFalse_480) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_480, SetNonContentWorks_480) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_480, SetLongKeyInGroup_480) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== CurGroupFlowType Tests ====================

TEST_F(EmitterStateTest_480, CurGroupFlowTypeAfterStartGroup_480) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  FlowType::value flowType = state.CurGroupFlowType();
  (void)flowType;  // Just verify no crash
}

// ==================== CurGroupIndent Tests ====================

TEST_F(EmitterStateTest_480, CurGroupIndentAfterStartGroup_480) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  std::size_t indent = state.CurGroupIndent();
  (void)indent;  // Verify no crash
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_480, LastIndentInitial_480) {
  std::size_t lastIndent = state.LastIndent();
  (void)lastIndent;  // Verify no crash
}

// ==================== AnchorResetAfterScalar Tests ====================

TEST_F(EmitterStateTest_480, AnchorResetAfterStartedScalar_480) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_480, AliasResetAfterStartedScalar_480) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_480, TagResetAfterStartedScalar_480) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasTag());
}

// ==================== Invalid Format Values Tests ====================

TEST_F(EmitterStateTest_480, SetOutputCharsetInvalidValue_480) {
  // Passing an unrelated EMITTER_MANIP
  bool result = state.SetOutputCharset(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_480, SetStringFormatInvalidValue_480) {
  bool result = state.SetStringFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_480, SetBoolFormatInvalidValue_480) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_480, SetIntFormatInvalidValue_480) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_480, SetNullFormatInvalidValue_480) {
  bool result = state.SetNullFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

}  // namespace YAML
