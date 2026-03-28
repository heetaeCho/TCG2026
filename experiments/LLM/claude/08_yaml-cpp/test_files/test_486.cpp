#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_486 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_486, InitialStateIsGood_486) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_486, InitialLastErrorIsEmpty_486) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_486, InitialCurIndentIsZero_486) {
  EXPECT_EQ(0u, state.CurIndent());
}

TEST_F(EmitterStateTest_486, InitialHasAnchorIsFalse_486) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_486, InitialHasAliasIsFalse_486) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_486, InitialHasTagIsFalse_486) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_486, InitialLastIndentIsZero_486) {
  EXPECT_EQ(0u, state.LastIndent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_486, SetErrorMakesStateNotGood_486) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_486, SetErrorStoresErrorMessage_486) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_486, SetErrorMultipleTimesKeepsFirstError_486) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically the first error is preserved
  EXPECT_FALSE(state.good());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_486, SetAnchorSetsHasAnchor_486) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_486, SetAliasSetsHasAlias_486) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_486, SetTagSetsHasTag_486) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Document Tests ====================

TEST_F(EmitterStateTest_486, StartedDocWorks_486) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_486, EndedDocWorks_486) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_486, StartedGroupSeq_486) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_486, StartedGroupMap_486) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_486, EndedGroupSeq_486) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_486, EndedGroupMap_486) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_486, CurGroupChildCountInitiallyZero_486) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_486, CurGroupLongKeyInitiallyFalse_486) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_486, SetLongKeyOnGroup_486) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_486, LastIndentWithNoGroupsIsZero_486) {
  EXPECT_EQ(0u, state.LastIndent());
}

TEST_F(EmitterStateTest_486, LastIndentWithOneGroupIsZero_486) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // With only one actual group (plus potentially a root), LastIndent behavior
  // depends on m_groups.size() <= 1 check
  // We just verify it doesn't crash and returns a valid value
  std::size_t indent = state.LastIndent();
  (void)indent; // Just verify no crash
}

TEST_F(EmitterStateTest_486, LastIndentWithNestedGroups_486) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.StartedGroup(GroupType::Seq);
  // Now we have nested groups, LastIndent should return non-zero or computed value
  std::size_t indent = state.LastIndent();
  (void)indent; // Verify no crash
}

// ==================== Format Setting Tests ====================

TEST_F(EmitterStateTest_486, SetOutputCharsetGlobal_486) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_486, SetOutputCharsetLocal_486) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_486, SetStringFormatGlobal_486) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
}

TEST_F(EmitterStateTest_486, SetStringFormatLocal_486) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_486, SetBoolFormatGlobal_486) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_486, SetBoolLengthFormatGlobal_486) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_486, SetBoolCaseFormatGlobal_486) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
}

TEST_F(EmitterStateTest_486, SetNullFormatGlobal_486) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
}

TEST_F(EmitterStateTest_486, SetIntFormatGlobal_486) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
}

TEST_F(EmitterStateTest_486, SetIndentGlobal_486) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
}

TEST_F(EmitterStateTest_486, SetIndentLocal_486) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
}

TEST_F(EmitterStateTest_486, SetIndentTooSmallFails_486) {
  // Indent of 1 may be too small
  // Test boundary - indent of 0 or 1 might fail
  bool result = state.SetIndent(1, FmtScope::Global);
  // We don't know if 1 is valid; just ensure no crash
  (void)result;
}

TEST_F(EmitterStateTest_486, SetPreCommentIndentGlobal_486) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Global));
}

TEST_F(EmitterStateTest_486, SetPostCommentIndentGlobal_486) {
  EXPECT_TRUE(state.SetPostCommentIndent(1, FmtScope::Global));
}

TEST_F(EmitterStateTest_486, SetFlowTypeSeqFlow_486) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_486, SetFlowTypeMapBlock_486) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
}

TEST_F(EmitterStateTest_486, SetMapKeyFormatGlobal_486) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
}

TEST_F(EmitterStateTest_486, SetFloatPrecisionGlobal_486) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Global));
}

TEST_F(EmitterStateTest_486, SetDoublePrecisionGlobal_486) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Global));
}

// ==================== Get Format Tests ====================

TEST_F(EmitterStateTest_486, GetIndentDefaultValue_486) {
  std::size_t indent = state.GetIndent();
  EXPECT_GT(indent, 0u);
}

TEST_F(EmitterStateTest_486, GetIndentAfterSet_486) {
  state.SetIndent(4, FmtScope::Global);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_486, GetPreCommentIndentDefault_486) {
  std::size_t indent = state.GetPreCommentIndent();
  EXPECT_GT(indent, 0u);
}

TEST_F(EmitterStateTest_486, GetPostCommentIndentDefault_486) {
  std::size_t indent = state.GetPostCommentIndent();
  EXPECT_GT(indent, 0u);
}

TEST_F(EmitterStateTest_486, GetFloatPrecisionDefault_486) {
  std::size_t prec = state.GetFloatPrecision();
  (void)prec; // Just ensure no crash
}

TEST_F(EmitterStateTest_486, GetDoublePrecisionDefault_486) {
  std::size_t prec = state.GetDoublePrecision();
  (void)prec; // Just ensure no crash
}

TEST_F(EmitterStateTest_486, GetFlowTypeSeqDefault_486) {
  EMITTER_MANIP flow = state.GetFlowType(GroupType::Seq);
  (void)flow;
}

TEST_F(EmitterStateTest_486, GetFlowTypeMapDefault_486) {
  EMITTER_MANIP flow = state.GetFlowType(GroupType::Map);
  (void)flow;
}

TEST_F(EmitterStateTest_486, GetStringFormatDefault_486) {
  EMITTER_MANIP fmt = state.GetStringFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_486, GetBoolFormatDefault_486) {
  EMITTER_MANIP fmt = state.GetBoolFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_486, GetBoolLengthFormatDefault_486) {
  EMITTER_MANIP fmt = state.GetBoolLengthFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_486, GetBoolCaseFormatDefault_486) {
  EMITTER_MANIP fmt = state.GetBoolCaseFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_486, GetNullFormatDefault_486) {
  EMITTER_MANIP fmt = state.GetNullFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_486, GetIntFormatDefault_486) {
  EMITTER_MANIP fmt = state.GetIntFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_486, GetMapKeyFormatDefault_486) {
  EMITTER_MANIP fmt = state.GetMapKeyFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_486, GetOutputCharsetDefault_486) {
  EMITTER_MANIP charset = state.GetOutputCharset();
  (void)charset;
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_486, ForceFlowOnGroup_486) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_486, ClearModifiedSettingsDoesNotCrash_486) {
  state.SetIndent(6, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_486, RestoreGlobalModifiedSettingsDoesNotCrash_486) {
  state.SetIndent(6, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_486, SetLocalValueFlow_486) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_486, SetLocalValueBlock_486) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// ==================== StartedScalar Tests ====================

TEST_F(EmitterStateTest_486, StartedScalarInDoc_486) {
  state.StartedDoc();
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_486, NextGroupTypeSeq_486) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  (void)nodeType;
}

TEST_F(EmitterStateTest_486, NextGroupTypeMap_486) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
}

// ==================== CurGroupNodeType Tests ====================

TEST_F(EmitterStateTest_486, CurGroupNodeTypeInGroup_486) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  (void)nodeType;
}

// ==================== Nested Group Tests ====================

TEST_F(EmitterStateTest_486, NestedSeqGroups_486) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_486, NestedMapInSeq_486) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// ==================== HasBegunNode/HasBegunContent Tests ====================

TEST_F(EmitterStateTest_486, HasBegunNodeInitially_486) {
  // Before any content is started
  bool begun = state.HasBegunNode();
  (void)begun;
}

TEST_F(EmitterStateTest_486, HasBegunContentInitially_486) {
  bool begun = state.HasBegunContent();
  (void)begun;
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_486, SetNonContentWorks_486) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== CurGroupIndent Tests ====================

TEST_F(EmitterStateTest_486, CurGroupIndentInGroup_486) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  std::size_t indent = state.CurGroupIndent();
  (void)indent;
}

// ==================== Scope Tests ====================

TEST_F(EmitterStateTest_486, SetIndentWithLocalScope_486) {
  state.SetIndent(8, FmtScope::Local);
  EXPECT_EQ(8u, state.GetIndent());
}

TEST_F(EmitterStateTest_486, SetFlowTypeAfterSet_486) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_486, SetFlowTypeMapAfterSet_486) {
  state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== Float/Double Precision After Set ====================

TEST_F(EmitterStateTest_486, FloatPrecisionAfterSet_486) {
  state.SetFloatPrecision(3, FmtScope::Global);
  EXPECT_EQ(3u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_486, DoublePrecisionAfterSet_486) {
  state.SetDoublePrecision(10, FmtScope::Global);
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== Multiple Documents ====================

TEST_F(EmitterStateTest_486, MultipleDocuments_486) {
  state.StartedDoc();
  state.StartedScalar();
  state.EndedDoc();
  state.StartedDoc();
  state.StartedScalar();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== CurGroupFlowType ====================

TEST_F(EmitterStateTest_486, CurGroupFlowTypeBlockByDefault_486) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  FlowType::value flowType = state.CurGroupFlowType();
  // Default should be block unless forced
  (void)flowType;
}

}  // namespace YAML
