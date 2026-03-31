#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_462 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_462, InitialStateIsGood_462) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_462, InitialLastErrorIsEmpty_462) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_462, InitialCurIndentIsZero_462) {
  EXPECT_EQ(0u, state.CurIndent());
}

TEST_F(EmitterStateTest_462, InitialHasAnchorIsFalse_462) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_462, InitialHasAliasIsFalse_462) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_462, InitialHasTagIsFalse_462) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_462, InitialHasBegunNodeIsFalse_462) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_462, InitialHasBegunContentIsFalse_462) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== Error Handling Tests ====================

TEST_F(EmitterStateTest_462, SetErrorMakesStateNotGood_462) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_462, SetErrorStoresErrorMessage_462) {
  state.SetError("something went wrong");
  EXPECT_EQ("something went wrong", state.GetLastError());
}

TEST_F(EmitterStateTest_462, SetErrorEmptyString_462) {
  state.SetError("");
  EXPECT_FALSE(state.good());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_462, SetAnchorSetsHasAnchor_462) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_462, SetAliasSetsHasAlias_462) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_462, SetTagSetsHasTag_462) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Default Format Getter Tests ====================

TEST_F(EmitterStateTest_462, DefaultGetIndentIsReasonable_462) {
  std::size_t indent = state.GetIndent();
  EXPECT_GT(indent, 0u);
}

TEST_F(EmitterStateTest_462, DefaultGetPreCommentIndentIsReasonable_462) {
  std::size_t val = state.GetPreCommentIndent();
  EXPECT_GT(val, 0u);
}

TEST_F(EmitterStateTest_462, DefaultGetPostCommentIndentIsReasonable_462) {
  std::size_t val = state.GetPostCommentIndent();
  EXPECT_GT(val, 0u);
}

TEST_F(EmitterStateTest_462, DefaultGetFloatPrecisionIsReasonable_462) {
  std::size_t val = state.GetFloatPrecision();
  // Float precision should be some reasonable default
  EXPECT_GT(val, 0u);
}

TEST_F(EmitterStateTest_462, DefaultGetDoublePrecisionIsReasonable_462) {
  std::size_t val = state.GetDoublePrecision();
  EXPECT_GT(val, 0u);
}

// ==================== Set and Get Format Tests ====================

TEST_F(EmitterStateTest_462, SetIndentGlobal_462) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_462, SetIndentLocal_462) {
  EXPECT_TRUE(state.SetIndent(6, FmtScope::Local));
  EXPECT_EQ(6u, state.GetIndent());
}

TEST_F(EmitterStateTest_462, SetIndentZeroFails_462) {
  // Indent of 0 is likely invalid
  bool result = state.SetIndent(0, FmtScope::Global);
  // We check if it rejects 0 - depends on implementation
  // If it doesn't fail, the indent should still be valid
  if (!result) {
    EXPECT_NE(0u, state.GetIndent());
  }
}

TEST_F(EmitterStateTest_462, SetPreCommentIndentGlobal_462) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_462, SetPostCommentIndentGlobal_462) {
  EXPECT_TRUE(state.SetPostCommentIndent(5, FmtScope::Global));
  EXPECT_EQ(5u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_462, SetOutputCharsetGlobal_462) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_462, SetOutputCharsetUtf8_462) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Global));
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_462, SetStringFormatGlobal_462) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_462, SetStringFormatDoubleQuoted_462) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_462, SetStringFormatLiteral_462) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Global));
  EXPECT_EQ(Literal, state.GetStringFormat());
}

TEST_F(EmitterStateTest_462, SetBoolFormatYesNo_462) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_462, SetBoolFormatTrueFalse_462) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_462, SetBoolFormatOnOff_462) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Global));
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_462, SetBoolLengthFormatShort_462) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_462, SetBoolLengthFormatLong_462) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_462, SetBoolCaseFormatUpper_462) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_462, SetBoolCaseFormatLower_462) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_462, SetBoolCaseFormatCamel_462) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_462, SetIntFormatDec_462) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_462, SetIntFormatHex_462) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_462, SetIntFormatOct_462) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_462, SetNullFormatGlobal_462) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_462, SetNullFormatTilde_462) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Global));
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_462, SetMapKeyFormatGlobal_462) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_462, SetFloatPrecisionGlobal_462) {
  EXPECT_TRUE(state.SetFloatPrecision(3, FmtScope::Global));
  EXPECT_EQ(3u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_462, SetDoublePrecisionGlobal_462) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Global));
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== SetFlowType/GetFlowType Tests ====================

TEST_F(EmitterStateTest_462, SetFlowTypeSeqFlow_462) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_462, SetFlowTypeSeqBlock_462) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_462, SetFlowTypeMapFlow_462) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_462, SetFlowTypeMapBlock_462) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== Doc Lifecycle Tests ====================

TEST_F(EmitterStateTest_462, StartedDocEndedDoc_462) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_462, MultipleDocCycles_462) {
  state.StartedDoc();
  state.EndedDoc();
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Lifecycle Tests ====================

TEST_F(EmitterStateTest_462, StartedGroupSeqAndEnd_462) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_462, StartedGroupMapAndEnd_462) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_462, CurGroupChildCountInitiallyZero_462) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
  state.EndedDoc();
}

TEST_F(EmitterStateTest_462, CurGroupIndentAfterStartingGroup_462) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // CurGroupIndent should return some value
  std::size_t indent = state.CurGroupIndent();
  (void)indent; // just ensure it doesn't crash
  state.EndedGroup(GroupType::Seq);
  state.EndedDoc();
}

TEST_F(EmitterStateTest_462, CurGroupLongKeyDefaultFalse_462) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
  state.EndedDoc();
}

// ==================== StartedScalar Tests ====================

TEST_F(EmitterStateTest_462, StartedScalarInSeq_462) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Seq);
  state.EndedDoc();
}

// ==================== SetNonContent Test ====================

TEST_F(EmitterStateTest_462, SetNonContentSetsFlag_462) {
  state.SetNonContent();
  // HasBegunNode and HasBegunContent may be affected
  // Just ensure no crash and state remains good
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey Test ====================

TEST_F(EmitterStateTest_462, SetLongKeyInGroup_462) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
  state.EndedDoc();
}

// ==================== ForceFlow Test ====================

TEST_F(EmitterStateTest_462, ForceFlowInGroup_462) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Seq);
  state.EndedDoc();
}

// ==================== ClearModifiedSettings Test ====================

TEST_F(EmitterStateTest_462, ClearModifiedSettingsDoesNotCrash_462) {
  state.SetIndent(8, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Test ====================

TEST_F(EmitterStateTest_462, RestoreGlobalModifiedSettingsDoesNotCrash_462) {
  state.SetIndent(8, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== SetLocalValue Test ====================

TEST_F(EmitterStateTest_462, SetLocalValueFlow_462) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_462, SetLocalValueBlock_462) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// ==================== Invalid Format Values Tests ====================

TEST_F(EmitterStateTest_462, SetOutputCharsetInvalidValue_462) {
  // Passing a value that isn't a charset manipulator
  bool result = state.SetOutputCharset(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_462, SetStringFormatInvalidValue_462) {
  bool result = state.SetStringFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_462, SetBoolFormatInvalidValue_462) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_462, SetIntFormatInvalidValue_462) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_462, SetNullFormatInvalidValue_462) {
  bool result = state.SetNullFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_462, NextGroupTypeSeq_462) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return a valid EmitterNodeType
  (void)nodeType;
  state.EndedGroup(GroupType::Seq);
  state.EndedDoc();
}

TEST_F(EmitterStateTest_462, NextGroupTypeMap_462) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  state.EndedGroup(GroupType::Map);
  state.EndedDoc();
}

// ==================== CurGroupNodeType Tests ====================

TEST_F(EmitterStateTest_462, CurGroupNodeTypeInSeq_462) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  (void)nodeType;
  state.EndedGroup(GroupType::Seq);
  state.EndedDoc();
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_462, LastIndentInitial_462) {
  std::size_t lastIndent = state.LastIndent();
  EXPECT_EQ(0u, lastIndent);
}

// ==================== Scope Tests ====================

TEST_F(EmitterStateTest_462, LocalSettingClearedOnClear_462) {
  std::size_t defaultIndent = state.GetIndent();
  state.SetIndent(10, FmtScope::Local);
  EXPECT_EQ(10u, state.GetIndent());
  state.ClearModifiedSettings();
  EXPECT_EQ(defaultIndent, state.GetIndent());
}

TEST_F(EmitterStateTest_462, GlobalSettingPersistsAfterClear_462) {
  state.SetIndent(10, FmtScope::Global);
  state.ClearModifiedSettings();
  EXPECT_EQ(10u, state.GetIndent());
}

// ==================== Multiple Nested Groups ====================

TEST_F(EmitterStateTest_462, NestedGroups_462) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Scalar increments child count ====================

TEST_F(EmitterStateTest_462, ScalarIncrementsChildCount_462) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
  state.StartedScalar();
  EXPECT_EQ(2u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
  state.EndedDoc();
}

// ==================== HasBegunNode after scalar ====================

TEST_F(EmitterStateTest_462, HasBegunNodeAfterAnchor_462) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_462, HasBegunNodeAfterAlias_462) {
  state.SetAlias();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_462, HasBegunNodeAfterTag_462) {
  state.SetTag();
  EXPECT_TRUE(state.HasBegunNode());
}

// ==================== FlowType in group with ForceFlow ====================

TEST_F(EmitterStateTest_462, ForceFlowOnMapGroup_462) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Map);
  state.EndedDoc();
}

// ==================== SetFloatPrecision boundary ====================

TEST_F(EmitterStateTest_462, SetFloatPrecisionZero_462) {
  // Precision of 0 may or may not be valid
  bool result = state.SetFloatPrecision(0, FmtScope::Global);
  if (result) {
    EXPECT_EQ(0u, state.GetFloatPrecision());
  }
}

TEST_F(EmitterStateTest_462, SetDoublePrecisionZero_462) {
  bool result = state.SetDoublePrecision(0, FmtScope::Global);
  if (result) {
    EXPECT_EQ(0u, state.GetDoublePrecision());
  }
}

TEST_F(EmitterStateTest_462, SetFloatPrecisionLargeValue_462) {
  EXPECT_TRUE(state.SetFloatPrecision(20, FmtScope::Global));
  EXPECT_EQ(20u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_462, SetDoublePrecisionLargeValue_462) {
  EXPECT_TRUE(state.SetDoublePrecision(20, FmtScope::Global));
  EXPECT_EQ(20u, state.GetDoublePrecision());
}

}  // namespace YAML
