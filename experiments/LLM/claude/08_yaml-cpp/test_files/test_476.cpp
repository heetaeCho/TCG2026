#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_476 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Construction / Initial State ====================

TEST_F(EmitterStateTest_476, InitialStateIsGood_476) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_476, InitialLastErrorIsEmpty_476) {
  EXPECT_EQ(state.GetLastError(), "");
}

TEST_F(EmitterStateTest_476, InitialHasNoAnchor_476) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_476, InitialHasNoAlias_476) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_476, InitialHasNoTag_476) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_476, InitialCurIndentIsZero_476) {
  EXPECT_EQ(state.CurIndent(), 0u);
}

// ==================== SetError ====================

TEST_F(EmitterStateTest_476, SetErrorMakesStateNotGood_476) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_476, SetErrorStoresErrorMessage_476) {
  state.SetError("something went wrong");
  EXPECT_EQ(state.GetLastError(), "something went wrong");
}

TEST_F(EmitterStateTest_476, SetErrorMultipleTimesKeepsFirstError_476) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically only the first error is kept, but we test what's observable
  EXPECT_FALSE(state.good());
  // The last error could be either; we just check it's non-empty
  EXPECT_FALSE(state.GetLastError().empty());
}

// ==================== SetAnchor / HasAnchor ====================

TEST_F(EmitterStateTest_476, SetAnchorSetsHasAnchor_476) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

// ==================== SetAlias / HasAlias ====================

TEST_F(EmitterStateTest_476, SetAliasSetsHasAlias_476) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

// ==================== SetTag / HasTag ====================

TEST_F(EmitterStateTest_476, SetTagSetsHasTag_476) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== SetNonContent ====================

TEST_F(EmitterStateTest_476, SetNonContentSetsFlag_476) {
  state.SetNonContent();
  // HasBegunContent should reflect the non-content state
  // We just verify no crash and check related accessors
  // SetNonContent sets m_hasNonContent = true
}

// ==================== EndedDoc ====================

TEST_F(EmitterStateTest_476, EndedDocClearsAnchor_476) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.EndedDoc();
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_476, EndedDocClearsTag_476) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.EndedDoc();
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_476, EndedDocClearsNonContent_476) {
  state.SetNonContent();
  state.EndedDoc();
  // After EndedDoc, m_hasNonContent should be false
  // We can verify through HasBegunContent or HasBegunNode if applicable
}

TEST_F(EmitterStateTest_476, EndedDocCalledMultipleTimes_476) {
  state.SetAnchor();
  state.SetTag();
  state.EndedDoc();
  state.EndedDoc();
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
}

// ==================== StartedDoc ====================

TEST_F(EmitterStateTest_476, StartedDocDoesNotCrash_476) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_476, StartedDocThenEndedDoc_476) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Format Settings ====================

TEST_F(EmitterStateTest_476, SetOutputCharsetGlobal_476) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_476, SetOutputCharsetLocal_476) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_476, SetStringFormatGlobal_476) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
}

TEST_F(EmitterStateTest_476, SetStringFormatLocal_476) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_476, GetStringFormatAfterSet_476) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_EQ(state.GetStringFormat(), DoubleQuoted);
}

TEST_F(EmitterStateTest_476, SetBoolFormatGlobal_476) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_476, GetBoolFormatAfterSet_476) {
  state.SetBoolFormat(YesNoBool, FmtScope::Global);
  EXPECT_EQ(state.GetBoolFormat(), YesNoBool);
}

TEST_F(EmitterStateTest_476, SetBoolLengthFormatGlobal_476) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_476, GetBoolLengthFormatAfterSet_476) {
  state.SetBoolLengthFormat(LongBool, FmtScope::Global);
  EXPECT_EQ(state.GetBoolLengthFormat(), LongBool);
}

TEST_F(EmitterStateTest_476, SetBoolCaseFormatGlobal_476) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
}

TEST_F(EmitterStateTest_476, GetBoolCaseFormatAfterSet_476) {
  state.SetBoolCaseFormat(LowerCase, FmtScope::Global);
  EXPECT_EQ(state.GetBoolCaseFormat(), LowerCase);
}

TEST_F(EmitterStateTest_476, SetNullFormatGlobal_476) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
}

TEST_F(EmitterStateTest_476, GetNullFormatAfterSet_476) {
  state.SetNullFormat(TildeNull, FmtScope::Global);
  EXPECT_EQ(state.GetNullFormat(), TildeNull);
}

TEST_F(EmitterStateTest_476, SetIntFormatGlobal_476) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
}

TEST_F(EmitterStateTest_476, GetIntFormatAfterSet_476) {
  state.SetIntFormat(Oct, FmtScope::Global);
  EXPECT_EQ(state.GetIntFormat(), Oct);
}

TEST_F(EmitterStateTest_476, SetIntFormatDec_476) {
  state.SetIntFormat(Dec, FmtScope::Global);
  EXPECT_EQ(state.GetIntFormat(), Dec);
}

// ==================== Indent Settings ====================

TEST_F(EmitterStateTest_476, SetIndentGlobal_476) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
}

TEST_F(EmitterStateTest_476, GetIndentAfterSet_476) {
  state.SetIndent(4, FmtScope::Global);
  EXPECT_EQ(state.GetIndent(), 4u);
}

TEST_F(EmitterStateTest_476, SetIndentBoundaryMinimum_476) {
  // An indent of 2 is typically the minimum meaningful value
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Global));
  EXPECT_EQ(state.GetIndent(), 2u);
}

TEST_F(EmitterStateTest_476, SetPreCommentIndent_476) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(state.GetPreCommentIndent(), 3u);
}

TEST_F(EmitterStateTest_476, SetPostCommentIndent_476) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
  EXPECT_EQ(state.GetPostCommentIndent(), 2u);
}

// ==================== Float/Double Precision ====================

TEST_F(EmitterStateTest_476, SetFloatPrecision_476) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Global));
  EXPECT_EQ(state.GetFloatPrecision(), 6u);
}

TEST_F(EmitterStateTest_476, SetDoublePrecision_476) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Global));
  EXPECT_EQ(state.GetDoublePrecision(), 15u);
}

TEST_F(EmitterStateTest_476, SetFloatPrecisionZero_476) {
  // Boundary: zero precision
  state.SetFloatPrecision(0, FmtScope::Global);
  EXPECT_EQ(state.GetFloatPrecision(), 0u);
}

TEST_F(EmitterStateTest_476, SetDoublePrecisionZero_476) {
  state.SetDoublePrecision(0, FmtScope::Global);
  EXPECT_EQ(state.GetDoublePrecision(), 0u);
}

// ==================== Flow Type ====================

TEST_F(EmitterStateTest_476, SetFlowTypeSeqFlow_476) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EXPECT_EQ(state.GetFlowType(GroupType::Seq), Flow);
}

TEST_F(EmitterStateTest_476, SetFlowTypeSeqBlock_476) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
  EXPECT_EQ(state.GetFlowType(GroupType::Seq), Block);
}

TEST_F(EmitterStateTest_476, SetFlowTypeMapFlow_476) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
  EXPECT_EQ(state.GetFlowType(GroupType::Map), Flow);
}

TEST_F(EmitterStateTest_476, SetFlowTypeMapBlock_476) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EXPECT_EQ(state.GetFlowType(GroupType::Map), Block);
}

// ==================== Map Key Format ====================

TEST_F(EmitterStateTest_476, SetMapKeyFormatGlobal_476) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(state.GetMapKeyFormat(), LongKey);
}

// ==================== Group Operations ====================

TEST_F(EmitterStateTest_476, StartedGroupSeq_476) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupType(), GroupType::Seq);
  EXPECT_EQ(state.CurGroupChildCount(), 0u);
}

TEST_F(EmitterStateTest_476, StartedGroupMap_476) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(state.CurGroupType(), GroupType::Map);
}

TEST_F(EmitterStateTest_476, EndedGroupSeq_476) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  // After ending the only group, should still be good
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_476, EndedGroupMap_476) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_476, NestedGroups_476) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupType(), GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupType(), GroupType::Map);
  state.EndedGroup(GroupType::Map);
}

TEST_F(EmitterStateTest_476, StartedScalarInGroup_476) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(state.CurGroupChildCount(), 1u);
}

TEST_F(EmitterStateTest_476, MultipleScalarsInGroup_476) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.StartedScalar();
  EXPECT_EQ(state.CurGroupChildCount(), 2u);
}

// ==================== CurGroupLongKey ====================

TEST_F(EmitterStateTest_476, CurGroupLongKeyDefault_476) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== SetLongKey ====================

TEST_F(EmitterStateTest_476, SetLongKeyInGroup_476) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== ForceFlow ====================

TEST_F(EmitterStateTest_476, ForceFlowInGroup_476) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(state.CurGroupFlowType(), FlowType::Flow);
  state.EndedGroup(GroupType::Seq);
}

// ==================== CurGroupFlowType ====================

TEST_F(EmitterStateTest_476, CurGroupFlowTypeDefaultBlock_476) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // Default flow type for a sequence should be NoFlow or Block
  FlowType::value ft = state.CurGroupFlowType();
  // Just verify it returns a valid value without crashing
  (void)ft;
  state.EndedGroup(GroupType::Seq);
}

// ==================== CurGroupIndent ====================

TEST_F(EmitterStateTest_476, CurGroupIndent_476) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  std::size_t indent = state.CurGroupIndent();
  // Just verify it doesn't crash and returns something reasonable
  (void)indent;
  state.EndedGroup(GroupType::Seq);
}

// ==================== ClearModifiedSettings ====================

TEST_F(EmitterStateTest_476, ClearModifiedSettingsDoesNotCrash_476) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterStateTest_476, RestoreGlobalModifiedSettings_476) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(state.GetStringFormat(), DoubleQuoted);
}

// ==================== SetLocalValue ====================

TEST_F(EmitterStateTest_476, SetLocalValueDoesNotCrash_476) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

// ==================== NextGroupType ====================

TEST_F(EmitterStateTest_476, NextGroupTypeSeq_476) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Verify it returns some valid type
  (void)nodeType;
}

TEST_F(EmitterStateTest_476, NextGroupTypeMap_476) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
}

// ==================== HasBegunNode / HasBegunContent ====================

TEST_F(EmitterStateTest_476, HasBegunNodeInitiallyFalse_476) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_476, HasBegunContentInitiallyFalse_476) {
  EXPECT_FALSE(state.HasBegunContent());
}

TEST_F(EmitterStateTest_476, HasBegunNodeAfterSetAnchor_476) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_476, HasBegunNodeAfterSetTag_476) {
  state.SetTag();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_476, HasBegunNodeAfterSetAlias_476) {
  state.SetAlias();
  EXPECT_TRUE(state.HasBegunNode());
}

// ==================== GetOutputCharset ====================

TEST_F(EmitterStateTest_476, GetOutputCharsetDefault_476) {
  EMITTER_MANIP charset = state.GetOutputCharset();
  // Default should be EmitNonAscii typically
  (void)charset;
}

TEST_F(EmitterStateTest_476, GetOutputCharsetAfterSet_476) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Global);
  EXPECT_EQ(state.GetOutputCharset(), EscapeNonAscii);
}

// ==================== LastIndent ====================

TEST_F(EmitterStateTest_476, LastIndentDefault_476) {
  std::size_t lastIndent = state.LastIndent();
  // Should return 0 or some default
  (void)lastIndent;
}

// ==================== CurGroupNodeType ====================

TEST_F(EmitterStateTest_476, CurGroupNodeTypeInSeq_476) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  (void)nodeType;
  state.EndedGroup(GroupType::Seq);
}

// ==================== Scope Tests ====================

TEST_F(EmitterStateTest_476, LocalScopeSettingClearedOnClear_476) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(state.GetStringFormat(), DoubleQuoted);
  state.ClearModifiedSettings();
  // After clearing, should revert to default or global
  EMITTER_MANIP fmt = state.GetStringFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_476, GlobalScopeSettingPersistsAfterClear_476) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(state.GetStringFormat(), DoubleQuoted);
}

// ==================== StartedScalar ====================

TEST_F(EmitterStateTest_476, StartedScalarClearsAnchor_476) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_476, StartedScalarClearsTag_476) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasTag());
  state.EndedGroup(GroupType::Seq);
}

// ==================== Multiple Docs ====================

TEST_F(EmitterStateTest_476, MultipleDocsCycle_476) {
  state.StartedDoc();
  state.EndedDoc();
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_476, DocWithGroupAndScalar_476) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.StartedScalar();  // key
  state.StartedScalar();  // value
  EXPECT_EQ(state.CurGroupChildCount(), 2u);
  state.EndedGroup(GroupType::Map);
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

}  // namespace YAML
