#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_484 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_484, InitiallyGood_484) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_484, InitialLastErrorEmpty_484) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_484, InitialCurGroupChildCountIsZero_484) {
  // No groups, no docs started => m_docCount should be 0
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_484, InitialHasAnchorFalse_484) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_484, InitialHasAliasFalse_484) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_484, InitialHasTagFalse_484) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_484, InitialHasBegunNodeFalse_484) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_484, InitialHasBegunContentFalse_484) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== Error Handling Tests ====================

TEST_F(EmitterStateTest_484, SetErrorMakesNotGood_484) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_484, SetErrorSetsLastError_484) {
  state.SetError("test error");
  EXPECT_EQ("test error", state.GetLastError());
}

TEST_F(EmitterStateTest_484, SetErrorOnlyFirstErrorStored_484) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== Anchor / Alias / Tag Tests ====================

TEST_F(EmitterStateTest_484, SetAnchorSetsHasAnchor_484) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_484, SetAliasSetsHasAlias_484) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_484, SetTagSetsHasTag_484) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Document Tests ====================

TEST_F(EmitterStateTest_484, StartedDocIncreasesChildCount_484) {
  state.StartedDoc();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_484, MultipleStartedDocsIncreaseCount_484) {
  state.StartedDoc();
  state.EndedDoc();
  state.StartedDoc();
  EXPECT_EQ(2u, state.CurGroupChildCount());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_484, StartedGroupSeqCreatesGroup_484) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_484, StartedGroupMapCreatesGroup_484) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_484, CurGroupChildCountInGroupIsZero_484) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_484, ScalarInGroupIncreasesChildCount_484) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_484, EndedGroupRestoresParent_484) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.EndedGroup(GroupType::Seq);
  // Back to doc-level child count: 1 doc was started
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_484, NestedGroupsWorkCorrectly_484) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

// ==================== Indent Tests ====================

TEST_F(EmitterStateTest_484, DefaultIndentValue_484) {
  std::size_t indent = state.GetIndent();
  EXPECT_GE(indent, 1u);
}

TEST_F(EmitterStateTest_484, SetIndentLocalScope_484) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
}

TEST_F(EmitterStateTest_484, SetIndentGlobalScope_484) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_484, SetIndentZeroFails_484) {
  // Indent of 0 is likely invalid
  // Implementation may reject it
  bool result = state.SetIndent(0, FmtScope::Global);
  // If it returns false, it was rejected; either way we test observable behavior
  if (!result) {
    EXPECT_NE(0u, state.GetIndent());
  }
}

// ==================== Format Setting Tests ====================

TEST_F(EmitterStateTest_484, SetOutputCharsetUtf8_484) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_484, SetStringFormatSingleQuoted_484) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_484, SetStringFormatDoubleQuoted_484) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_484, SetBoolFormatYesNoBool_484) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_484, SetBoolFormatTrueFalseBool_484) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_484, SetBoolFormatOnOffBool_484) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Global));
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_484, SetBoolLengthFormatShortBool_484) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_484, SetBoolLengthFormatLongBool_484) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_484, SetBoolCaseFormatUpperCase_484) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_484, SetBoolCaseFormatLowerCase_484) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_484, SetBoolCaseFormatCamelCase_484) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_484, SetIntFormatDec_484) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_484, SetIntFormatHex_484) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_484, SetIntFormatOct_484) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_484, SetNullFormat_484) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

// ==================== Flow Type Tests ====================

TEST_F(EmitterStateTest_484, SetFlowTypeSeqFlow_484) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_484, SetFlowTypeSeqBlock_484) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_484, SetFlowTypeMapFlow_484) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_484, SetFlowTypeMapBlock_484) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== Map Key Format Tests ====================

TEST_F(EmitterStateTest_484, SetMapKeyFormatLongKey_484) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== Precision Tests ====================

TEST_F(EmitterStateTest_484, SetFloatPrecision_484) {
  EXPECT_TRUE(state.SetFloatPrecision(5, FmtScope::Global));
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_484, SetDoublePrecision_484) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Global));
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== Comment Indent Tests ====================

TEST_F(EmitterStateTest_484, SetPreCommentIndent_484) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_484, SetPostCommentIndent_484) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

// ==================== CurGroupFlowType Tests ====================

TEST_F(EmitterStateTest_484, CurGroupFlowTypeInFlowGroup_484) {
  state.StartedDoc();
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local);
  state.ForceFlow();
  state.StartedGroup(GroupType::Seq);
  FlowType::value ft = state.CurGroupFlowType();
  EXPECT_EQ(FlowType::Flow, ft);
  state.EndedGroup(GroupType::Seq);
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_484, SetNonContentAffectsState_484) {
  state.SetNonContent();
  // NonContent set; HasBegunContent should reflect appropriately
  // Just checking no crash and state remains good
  EXPECT_TRUE(state.good());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_484, ClearModifiedSettingsDoesNotCrash_484) {
  state.SetIndent(6, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_484, RestoreGlobalModifiedSettingsDoesNotCrash_484) {
  state.SetIndent(6, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_484, NextGroupTypeForSeq_484) {
  state.StartedDoc();
  EmitterNodeType::value nt = state.NextGroupType(GroupType::Seq);
  // Should return some valid node type
  (void)nt; // Just confirm no crash
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_484, NextGroupTypeForMap_484) {
  state.StartedDoc();
  EmitterNodeType::value nt = state.NextGroupType(GroupType::Map);
  (void)nt;
  EXPECT_TRUE(state.good());
}

// ==================== CurGroupLongKey Tests ====================

TEST_F(EmitterStateTest_484, CurGroupLongKeyDefault_484) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

TEST_F(EmitterStateTest_484, SetLongKeyInGroup_484) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== CurGroupIndent Tests ====================

TEST_F(EmitterStateTest_484, CurGroupIndentInGroup_484) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  std::size_t indent = state.CurGroupIndent();
  // Should be some reasonable value
  (void)indent;
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Seq);
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_484, LastIndentInitial_484) {
  std::size_t lastIndent = state.LastIndent();
  // Without any groups, should return some default
  (void)lastIndent;
  EXPECT_TRUE(state.good());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_484, SetLocalValueDoesNotCrash_484) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_484, SetLocalValueBlock_484) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// ==================== Multiple Scalars in Group ====================

TEST_F(EmitterStateTest_484, MultipleScalarsIncreasesChildCount_484) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.StartedScalar();
  state.StartedScalar();
  EXPECT_EQ(3u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_484, ForceFlowDoesNotCrash_484) {
  state.ForceFlow();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_484, ForceFlowInGroupSetsFlow_484) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  // The group should now be flow type
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Seq);
}

// ==================== Invalid format setting tests ====================

TEST_F(EmitterStateTest_484, SetStringFormatWithInvalidValue_484) {
  // Passing an invalid EMITTER_MANIP for string format
  bool result = state.SetStringFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_484, SetBoolFormatWithInvalidValue_484) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_484, SetIntFormatWithInvalidValue_484) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_484, SetOutputCharsetInvalidValue_484) {
  bool result = state.SetOutputCharset(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Scope Tests ====================

TEST_F(EmitterStateTest_484, SetIndentLocalScopeIsTemporary_484) {
  std::size_t originalIndent = state.GetIndent();
  state.SetIndent(8, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_EQ(originalIndent, state.GetIndent());
}

TEST_F(EmitterStateTest_484, SetIndentGlobalScopePersists_484) {
  state.SetIndent(8, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(8u, state.GetIndent());
}

}  // namespace YAML
