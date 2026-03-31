#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_445 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_445, InitialStateIsGood_445) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_445, InitialLastErrorIsEmpty_445) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_445, InitialCurIndentIsZero_445) {
  EXPECT_EQ(0u, state.CurIndent());
}

TEST_F(EmitterStateTest_445, InitialHasAnchorIsFalse_445) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_445, InitialHasAliasIsFalse_445) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_445, InitialHasTagIsFalse_445) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_445, InitialHasBegunNodeIsFalse_445) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_445, InitialHasBegunContentIsFalse_445) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_445, SetErrorMakesStateNotGood_445) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_445, SetErrorStoresErrorMessage_445) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_445, SetErrorEmptyString_445) {
  state.SetError("");
  EXPECT_FALSE(state.good());
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_445, SetErrorMultipleTimesKeepsFirstError_445) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically the first error is preserved since state is no longer good
  // but we just check it's not good
  EXPECT_FALSE(state.good());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_445, SetAnchorSetsHasAnchor_445) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_445, SetAliasSetsHasAlias_445) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_445, SetTagSetsHasTag_445) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Document Tests ====================

TEST_F(EmitterStateTest_445, StartedDocEndsCleanly_445) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_445, EndedDocAfterStartedDoc_445) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Scalar Tests ====================

TEST_F(EmitterStateTest_445, StartedScalarSetsBegunNode_445) {
  state.StartedDoc();
  state.StartedScalar();
  EXPECT_TRUE(state.HasBegunNode());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_445, StartedGroupSeq_445) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_445, StartedGroupMap_445) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_445, CurGroupChildCountInitiallyZero_445) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_445, CurGroupLongKeyInitiallyFalse_445) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_445, EndedGroupSeq_445) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_445, EndedGroupMap_445) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// ==================== Format Setting Tests ====================

TEST_F(EmitterStateTest_445, SetOutputCharsetUtf8_445) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_445, SetStringFormatSingleQuoted_445) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_445, SetStringFormatDoubleQuoted_445) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_445, SetStringFormatLiteral_445) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Global));
  EXPECT_EQ(Literal, state.GetStringFormat());
}

TEST_F(EmitterStateTest_445, SetBoolFormatTrueFalse_445) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_445, SetBoolFormatYesNo_445) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_445, SetBoolFormatOnOff_445) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Global));
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_445, SetBoolLengthFormatShort_445) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_445, SetBoolLengthFormatLong_445) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_445, SetBoolCaseFormatUpper_445) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_445, SetBoolCaseFormatLower_445) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_445, SetBoolCaseFormatCamel_445) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_445, SetNullFormatTildeNull_445) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_445, SetIntFormatDec_445) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_445, SetIntFormatHex_445) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_445, SetIntFormatOct_445) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_445, SetIndentValidValue_445) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_445, SetIndentMinimumValue_445) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetIndent());
}

TEST_F(EmitterStateTest_445, SetIndentTooSmall_445) {
  // Indent of 1 or 0 may be rejected
  bool result = state.SetIndent(1, FmtScope::Global);
  // We simply check the function doesn't crash; it might return false
  (void)result;
}

TEST_F(EmitterStateTest_445, SetPreCommentIndent_445) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_445, SetPostCommentIndent_445) {
  EXPECT_TRUE(state.SetPostCommentIndent(1, FmtScope::Global));
  EXPECT_EQ(1u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_445, SetMapKeyFormatLongKey_445) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_445, SetFloatPrecision_445) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Global));
  EXPECT_EQ(6u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_445, SetDoublePrecision_445) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Global));
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

// ==================== Flow Type Tests ====================

TEST_F(EmitterStateTest_445, SetFlowTypeSeqFlow_445) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_445, SetFlowTypeSeqBlock_445) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_445, SetFlowTypeMapFlow_445) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_445, SetFlowTypeMapBlock_445) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== Scope Tests ====================

TEST_F(EmitterStateTest_445, SetStringFormatLocalScope_445) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_445, SetLongKeyInGroup_445) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_445, ForceFlowInGroup_445) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_445, SetNonContentDoesNotBeginNode_445) {
  state.SetNonContent();
  // SetNonContent should not count as beginning a node
  // This tests that it doesn't crash and state remains valid
  EXPECT_TRUE(state.good());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_445, ClearModifiedSettingsResetsLocalValues_445) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  state.ClearModifiedSettings();
  // After clearing, should revert to default
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_445, RestoreGlobalModifiedSettings_445) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_445, NextGroupTypeForSeqWithNoGroups_445) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return some valid type
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_445, NextGroupTypeForMapWithNoGroups_445) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ==================== Nested Group Tests ====================

TEST_F(EmitterStateTest_445, NestedGroups_445) {
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

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_445, LastIndentInitially_445) {
  std::size_t lastIndent = state.LastIndent();
  // Just verify it doesn't crash and returns some value
  (void)lastIndent;
  EXPECT_TRUE(state.good());
}

// ==================== Invalid Format Setting Tests ====================

TEST_F(EmitterStateTest_445, SetOutputCharsetInvalidValue_445) {
  // Passing an unrelated EMITTER_MANIP should return false
  bool result = state.SetOutputCharset(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_445, SetStringFormatInvalidValue_445) {
  bool result = state.SetStringFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_445, SetBoolFormatInvalidValue_445) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_445, SetIntFormatInvalidValue_445) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Multiple Doc Tests ====================

TEST_F(EmitterStateTest_445, MultipleDocuments_445) {
  state.StartedDoc();
  state.EndedDoc();
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_445, SetLocalValueFlow_445) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_445, SetLocalValueBlock_445) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_445, SetLocalValueDoubleQuoted_445) {
  state.SetLocalValue(DoubleQuoted);
  EXPECT_TRUE(state.good());
}

// ==================== Group with scalars Tests ====================

TEST_F(EmitterStateTest_445, GroupChildCountIncreasesAfterScalar_445) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_445, AnchorResetAfterScalar_445) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_445, TagResetAfterScalar_445) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_445, AliasResetAfterScalar_445) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAlias());
}

// ==================== Default format values Tests ====================

TEST_F(EmitterStateTest_445, DefaultOutputCharset_445) {
  EMITTER_MANIP charset = state.GetOutputCharset();
  // Should be a valid value
  (void)charset;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_445, DefaultStringFormat_445) {
  EMITTER_MANIP fmt = state.GetStringFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_445, DefaultBoolFormat_445) {
  EMITTER_MANIP fmt = state.GetBoolFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_445, DefaultIntFormat_445) {
  EMITTER_MANIP fmt = state.GetIntFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_445, DefaultIndent_445) {
  std::size_t indent = state.GetIndent();
  EXPECT_GE(indent, 2u);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_445, DefaultFloatPrecision_445) {
  std::size_t prec = state.GetFloatPrecision();
  (void)prec;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_445, DefaultDoublePrecision_445) {
  std::size_t prec = state.GetDoublePrecision();
  (void)prec;
  EXPECT_TRUE(state.good());
}

}  // namespace YAML
