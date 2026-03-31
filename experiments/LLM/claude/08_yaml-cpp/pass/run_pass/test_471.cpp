#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_471 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_471, InitialStateIsGood_471) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_471, InitialLastErrorIsEmpty_471) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_471, InitialHasAnchorIsFalse_471) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_471, InitialHasAliasIsFalse_471) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_471, InitialHasTagIsFalse_471) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_471, InitialCurIndentIsZero_471) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_471, SetErrorMakesStateNotGood_471) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_471, SetErrorSetsLastError_471) {
  state.SetError("some error message");
  EXPECT_EQ("some error message", state.GetLastError());
}

TEST_F(EmitterStateTest_471, SetErrorOnlyFirstErrorIsKept_471) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== SetAnchor / SetAlias / SetTag Tests ====================

TEST_F(EmitterStateTest_471, SetAnchorSetsHasAnchor_471) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_471, SetAliasSetsHasAlias_471) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_471, SetTagSetsHasTag_471) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_471, SetNonContentAffectsHasBegunContent_471) {
  // After SetNonContent, HasBegunContent should reflect non-content state
  state.SetNonContent();
  // HasBegunContent should be false if only non-content was set
  // This tests that SetNonContent is observable
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== Document Lifecycle Tests ====================

TEST_F(EmitterStateTest_471, StartedDocAndEndedDoc_471) {
  state.StartedDoc();
  state.EndedDoc();
  // Should not crash and state should still be good
  EXPECT_TRUE(state.good());
}

// ==================== Scalar Tests ====================

TEST_F(EmitterStateTest_471, StartedScalarResetsFlags_471) {
  state.StartedDoc();
  state.SetAnchor();
  state.SetTag();
  state.StartedScalar();
  // After starting a scalar, anchor and tag should be consumed
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
}

// ==================== Group Lifecycle Tests ====================

TEST_F(EmitterStateTest_471, StartedGroupAndEndedGroup_Seq_471) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_471, StartedGroupAndEndedGroup_Map_471) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_471, CurGroupChildCountInitiallyZero_471) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_471, CurGroupChildCountIncreasesAfterScalar_471) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_471, CurGroupLongKeyInitiallyFalse_471) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_471, SetLongKeyAffectsCurGroupLongKey_471) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_471, ForceFlowChangesFlowType_471) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Seq);
}

// ==================== Setting Format Tests ====================

TEST_F(EmitterStateTest_471, SetOutputCharsetValid_471) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetStringFormatValid_471) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetStringFormatDoubleQuoted_471) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetStringFormatLiteral_471) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetBoolFormatValid_471) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetBoolFormatTrueFalse_471) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetBoolFormatOnOff_471) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetBoolLengthFormatValid_471) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetBoolLengthFormatLong_471) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetBoolCaseFormatValid_471) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetBoolCaseFormatLower_471) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetBoolCaseFormatCamel_471) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetNullFormatValid_471) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetNullFormatTilde_471) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetIntFormatDec_471) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetIntFormatHex_471) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetIntFormatOct_471) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetIndentValid_471) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetIndentMinBoundary_471) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetIndentTooSmall_471) {
  // Indent of 0 or 1 may be rejected
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetIndentOne_471) {
  // Indent of 1 may be rejected depending on implementation
  // We test observability
  bool result = state.SetIndent(1, FmtScope::Local);
  // Either true or false is acceptable; we just ensure no crash
  (void)result;
}

TEST_F(EmitterStateTest_471, SetPreCommentIndentValid_471) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetPostCommentIndentValid_471) {
  EXPECT_TRUE(state.SetPostCommentIndent(1, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetPreCommentIndentZero_471) {
  // Zero may or may not be acceptable
  bool result = state.SetPreCommentIndent(0, FmtScope::Local);
  (void)result;
}

TEST_F(EmitterStateTest_471, SetPostCommentIndentZero_471) {
  bool result = state.SetPostCommentIndent(0, FmtScope::Local);
  (void)result;
}

// ==================== Get Format Tests ====================

TEST_F(EmitterStateTest_471, GetStringFormatAfterSet_471) {
  state.SetStringFormat(SingleQuoted, FmtScope::Local);
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_471, GetBoolFormatAfterSet_471) {
  state.SetBoolFormat(YesNoBool, FmtScope::Local);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_471, GetBoolLengthFormatAfterSet_471) {
  state.SetBoolLengthFormat(LongBool, FmtScope::Local);
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_471, GetBoolCaseFormatAfterSet_471) {
  state.SetBoolCaseFormat(UpperCase, FmtScope::Local);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_471, GetNullFormatAfterSet_471) {
  state.SetNullFormat(TildeNull, FmtScope::Local);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_471, GetIntFormatAfterSet_471) {
  state.SetIntFormat(Hex, FmtScope::Local);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_471, GetIndentAfterSet_471) {
  state.SetIndent(4, FmtScope::Local);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_471, GetPreCommentIndentAfterSet_471) {
  state.SetPreCommentIndent(3, FmtScope::Local);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_471, GetPostCommentIndentAfterSet_471) {
  state.SetPostCommentIndent(2, FmtScope::Local);
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_471, GetOutputCharsetAfterSet_471) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Local);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_471, GetMapKeyFormatAfterSet_471) {
  state.SetMapKeyFormat(LongKey, FmtScope::Local);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== Flow Type Tests ====================

TEST_F(EmitterStateTest_471, SetFlowTypeSeqBlock_471) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetFlowTypeSeqFlow_471) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetFlowTypeMapBlock_471) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, SetFlowTypeMapFlow_471) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, GetFlowTypeSeqAfterSet_471) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_471, GetFlowTypeMapAfterSet_471) {
  state.SetFlowType(GroupType::Map, Flow, FmtScope::Local);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

// ==================== Precision Tests ====================

TEST_F(EmitterStateTest_471, SetFloatPrecisionValid_471) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, GetFloatPrecisionAfterSet_471) {
  state.SetFloatPrecision(3, FmtScope::Local);
  EXPECT_EQ(3u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_471, SetDoublePrecisionValid_471) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Local));
}

TEST_F(EmitterStateTest_471, GetDoublePrecisionAfterSet_471) {
  state.SetDoublePrecision(10, FmtScope::Local);
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== Scope Tests ====================

TEST_F(EmitterStateTest_471, SetIndentGlobalScope_471) {
  EXPECT_TRUE(state.SetIndent(5, FmtScope::Global));
  EXPECT_EQ(5u, state.GetIndent());
}

TEST_F(EmitterStateTest_471, SetStringFormatGlobalScope_471) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_471, ClearModifiedSettingsResetsLocalSettings_471) {
  state.SetStringFormat(SingleQuoted, FmtScope::Local);
  state.ClearModifiedSettings();
  // After clearing, local settings should be reverted
  // The default string format should be restored
  EMITTER_MANIP fmt = state.GetStringFormat();
  // We don't know the default but it should not crash
  (void)fmt;
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_471, RestoreGlobalModifiedSettingsWorks_471) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_471, NextGroupTypeSeqNoGroup_471) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return some valid node type
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_471, NextGroupTypeMapNoGroup_471) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ==================== HasBegunNode / HasBegunContent Tests ====================

TEST_F(EmitterStateTest_471, HasBegunNodeInitiallyFalse_471) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_471, HasBegunContentInitiallyFalse_471) {
  EXPECT_FALSE(state.HasBegunContent());
}

TEST_F(EmitterStateTest_471, HasBegunNodeAfterAnchor_471) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_471, HasBegunNodeAfterTag_471) {
  state.SetTag();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_471, HasBegunNodeAfterAlias_471) {
  state.SetAlias();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_471, HasBegunContentAfterSetNonContent_471) {
  state.SetNonContent();
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== Nested Group Tests ====================

TEST_F(EmitterStateTest_471, NestedGroups_471) {
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

TEST_F(EmitterStateTest_471, LastIndentInitial_471) {
  std::size_t indent = state.LastIndent();
  // Should return some default value, just ensure no crash
  (void)indent;
}

// ==================== CurGroupIndent Tests ====================

TEST_F(EmitterStateTest_471, CurGroupIndentInGroup_471) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  std::size_t indent = state.CurGroupIndent();
  (void)indent;
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Seq);
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_471, SetLocalValueFlow_471) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_471, SetLocalValueBlock_471) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_471, SetLocalValueLongKey_471) {
  state.SetLocalValue(LongKey);
  EXPECT_TRUE(state.good());
}

// ==================== Multiple Doc Tests ====================

TEST_F(EmitterStateTest_471, MultipleDocuments_471) {
  state.StartedDoc();
  state.StartedScalar();
  state.EndedDoc();

  state.StartedDoc();
  state.StartedScalar();
  state.EndedDoc();

  EXPECT_TRUE(state.good());
}

// ==================== CurGroupNodeType Tests ====================

TEST_F(EmitterStateTest_471, CurGroupNodeTypeInSeq_471) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  (void)nodeType;
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_471, CurGroupNodeTypeInMap_471) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  (void)nodeType;
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Map);
}

// ==================== Invalid Format Tests ====================

TEST_F(EmitterStateTest_471, SetOutputCharsetInvalidValue_471) {
  // Passing a value that is not a charset should return false
  bool result = state.SetOutputCharset(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_471, SetStringFormatInvalidValue_471) {
  bool result = state.SetStringFormat(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_471, SetBoolFormatInvalidValue_471) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_471, SetIntFormatInvalidValue_471) {
  bool result = state.SetIntFormat(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_471, SetNullFormatInvalidValue_471) {
  bool result = state.SetNullFormat(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_471, SetMapKeyFormatInvalidValue_471) {
  bool result = state.SetMapKeyFormat(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_471, SetFlowTypeInvalidValue_471) {
  bool result = state.SetFlowType(GroupType::Seq, Dec, FmtScope::Local);
  EXPECT_FALSE(result);
}

}  // namespace YAML
