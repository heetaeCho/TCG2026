#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_446 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ============================================================
// Initial state tests
// ============================================================

TEST_F(EmitterStateTest_446, InitialStateIsGood_446) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_446, InitialLastErrorIsEmpty_446) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_446, InitialCurIndentIsZero_446) {
  EXPECT_EQ(0u, state.CurIndent());
}

TEST_F(EmitterStateTest_446, InitialHasAnchorIsFalse_446) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_446, InitialHasAliasIsFalse_446) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_446, InitialHasTagIsFalse_446) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_446, InitialHasBegunNodeIsFalse_446) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_446, InitialHasBegunContentIsFalse_446) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ============================================================
// SetError tests
// ============================================================

TEST_F(EmitterStateTest_446, SetErrorMakesStateNotGood_446) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_446, SetErrorStoresErrorMessage_446) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_446, SetErrorWithEmptyString_446) {
  state.SetError("");
  EXPECT_FALSE(state.good());
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_446, SetErrorTwiceKeepsLastError_446) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_FALSE(state.good());
  EXPECT_EQ("second error", state.GetLastError());
}

// ============================================================
// Anchor / Alias / Tag tests
// ============================================================

TEST_F(EmitterStateTest_446, SetAnchorSetsHasAnchor_446) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_446, SetAliasSetsHasAlias_446) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_446, SetTagSetsHasTag_446) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ============================================================
// Document lifecycle tests
// ============================================================

TEST_F(EmitterStateTest_446, StartedDocAndEndedDoc_446) {
  state.StartedDoc();
  state.EndedDoc();
  // Should not crash; state should still be good
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_446, MultipleDocuments_446) {
  state.StartedDoc();
  state.EndedDoc();
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ============================================================
// Group lifecycle tests
// ============================================================

TEST_F(EmitterStateTest_446, StartAndEndSequenceGroup_446) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_446, StartAndEndMapGroup_446) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_446, CurGroupChildCountInitiallyZero_446) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_446, CurGroupChildCountIncrementsAfterScalar_446) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_446, CurGroupLongKeyInitiallyFalse_446) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

TEST_F(EmitterStateTest_446, SetLongKeyMakesCurGroupLongKeyTrue_446) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

TEST_F(EmitterStateTest_446, CurGroupIndentReturnsValue_446) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // Just verify it returns without crashing
  std::size_t indent = state.CurGroupIndent();
  (void)indent;
  state.EndedGroup(GroupType::Seq);
}

// ============================================================
// Scalar tests
// ============================================================

TEST_F(EmitterStateTest_446, StartedScalarClearsAnchorAndTag_446) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAnchor();
  state.SetTag();
  EXPECT_TRUE(state.HasAnchor());
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
  state.EndedGroup(GroupType::Seq);
}

// ============================================================
// Setting format tests - OutputCharset
// ============================================================

TEST_F(EmitterStateTest_446, SetOutputCharsetGlobal_446) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_446, SetOutputCharsetLocal_446) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Local));
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

// ============================================================
// Setting format tests - StringFormat
// ============================================================

TEST_F(EmitterStateTest_446, SetStringFormatGlobal_446) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_446, SetStringFormatLocal_446) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_446, SetStringFormatLiteral_446) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Global));
  EXPECT_EQ(Literal, state.GetStringFormat());
}

// ============================================================
// Setting format tests - BoolFormat
// ============================================================

TEST_F(EmitterStateTest_446, SetBoolFormatGlobal_446) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_446, SetBoolFormatTrueFalse_446) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_446, SetBoolFormatOnOff_446) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Global));
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

// ============================================================
// Setting format tests - BoolLengthFormat
// ============================================================

TEST_F(EmitterStateTest_446, SetBoolLengthFormatShort_446) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_446, SetBoolLengthFormatLong_446) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

// ============================================================
// Setting format tests - BoolCaseFormat
// ============================================================

TEST_F(EmitterStateTest_446, SetBoolCaseFormatUpper_446) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_446, SetBoolCaseFormatLower_446) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_446, SetBoolCaseFormatCamel_446) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

// ============================================================
// Setting format tests - IntFormat
// ============================================================

TEST_F(EmitterStateTest_446, SetIntFormatDec_446) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_446, SetIntFormatHex_446) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_446, SetIntFormatOct_446) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

// ============================================================
// Setting format tests - NullFormat
// ============================================================

TEST_F(EmitterStateTest_446, SetNullFormatTildeNull_446) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

// ============================================================
// Setting format tests - Indent
// ============================================================

TEST_F(EmitterStateTest_446, SetIndentGlobal_446) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_446, SetIndentLocal_446) {
  EXPECT_TRUE(state.SetIndent(6, FmtScope::Local));
  EXPECT_EQ(6u, state.GetIndent());
}

TEST_F(EmitterStateTest_446, SetIndentBoundaryMinimum_446) {
  // Indent of 2 is typically the minimum meaningful indent
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetIndent());
}

// ============================================================
// Setting format tests - PreCommentIndent / PostCommentIndent
// ============================================================

TEST_F(EmitterStateTest_446, SetPreCommentIndent_446) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_446, SetPostCommentIndent_446) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

// ============================================================
// Setting format tests - FlowType
// ============================================================

TEST_F(EmitterStateTest_446, SetFlowTypeSeqFlow_446) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_446, SetFlowTypeSeqBlock_446) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_446, SetFlowTypeMapFlow_446) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_446, SetFlowTypeMapBlock_446) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ============================================================
// Setting format tests - MapKeyFormat
// ============================================================

TEST_F(EmitterStateTest_446, SetMapKeyFormatLongKey_446) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ============================================================
// Setting format tests - FloatPrecision / DoublePrecision
// ============================================================

TEST_F(EmitterStateTest_446, SetFloatPrecision_446) {
  EXPECT_TRUE(state.SetFloatPrecision(5, FmtScope::Global));
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_446, SetDoublePrecision_446) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Global));
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

TEST_F(EmitterStateTest_446, SetFloatPrecisionLocal_446) {
  EXPECT_TRUE(state.SetFloatPrecision(3, FmtScope::Local));
  EXPECT_EQ(3u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_446, SetDoublePrecisionLocal_446) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Local));
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

// ============================================================
// ForceFlow tests
// ============================================================

TEST_F(EmitterStateTest_446, ForceFlowOnGroup_446) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Seq);
}

// ============================================================
// NextGroupType tests
// ============================================================

TEST_F(EmitterStateTest_446, NextGroupTypeForSeq_446) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return a valid node type
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_446, NextGroupTypeForMap_446) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ============================================================
// ClearModifiedSettings tests
// ============================================================

TEST_F(EmitterStateTest_446, ClearModifiedSettingsResetsLocal_446) {
  state.SetIndent(8, FmtScope::Local);
  EXPECT_EQ(8u, state.GetIndent());
  state.ClearModifiedSettings();
  // After clearing, should revert to default or global
  // We just check it doesn't crash and the state is still good
  EXPECT_TRUE(state.good());
}

// ============================================================
// RestoreGlobalModifiedSettings tests
// ============================================================

TEST_F(EmitterStateTest_446, RestoreGlobalModifiedSettings_446) {
  state.SetIndent(6, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(6u, state.GetIndent());
}

// ============================================================
// Nested group tests
// ============================================================

TEST_F(EmitterStateTest_446, NestedGroups_446) {
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

// ============================================================
// SetNonContent test
// ============================================================

TEST_F(EmitterStateTest_446, SetNonContent_446) {
  state.SetNonContent();
  // Verify it doesn't crash and state is still good
  EXPECT_TRUE(state.good());
}

// ============================================================
// LastIndent test
// ============================================================

TEST_F(EmitterStateTest_446, LastIndentReturnsValue_446) {
  std::size_t lastIndent = state.LastIndent();
  (void)lastIndent;
  EXPECT_TRUE(state.good());
}

// ============================================================
// Invalid format values tests (error cases)
// ============================================================

TEST_F(EmitterStateTest_446, SetOutputCharsetWithInvalidValue_446) {
  // Passing a value that is not a charset manipulator
  bool result = state.SetOutputCharset(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_446, SetStringFormatWithInvalidValue_446) {
  bool result = state.SetStringFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_446, SetBoolFormatWithInvalidValue_446) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_446, SetIntFormatWithInvalidValue_446) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_446, SetBoolLengthFormatWithInvalidValue_446) {
  bool result = state.SetBoolLengthFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_446, SetBoolCaseFormatWithInvalidValue_446) {
  bool result = state.SetBoolCaseFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_446, SetNullFormatWithInvalidValue_446) {
  bool result = state.SetNullFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_446, SetMapKeyFormatWithInvalidValue_446) {
  bool result = state.SetMapKeyFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ============================================================
// SetLocalValue test
// ============================================================

TEST_F(EmitterStateTest_446, SetLocalValueFlow_446) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_446, SetLocalValueBlock_446) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_446, SetLocalValueDoubleQuoted_446) {
  state.SetLocalValue(DoubleQuoted);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_446, SetLocalValueHex_446) {
  state.SetLocalValue(Hex);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

// ============================================================
// Default getter values tests
// ============================================================

TEST_F(EmitterStateTest_446, DefaultOutputCharset_446) {
  EMITTER_MANIP charset = state.GetOutputCharset();
  // Just verify it returns a value without crashing
  (void)charset;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_446, DefaultStringFormat_446) {
  EMITTER_MANIP fmt = state.GetStringFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_446, DefaultBoolFormat_446) {
  EMITTER_MANIP fmt = state.GetBoolFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_446, DefaultIntFormat_446) {
  EMITTER_MANIP fmt = state.GetIntFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_446, DefaultIndent_446) {
  std::size_t indent = state.GetIndent();
  EXPECT_GT(indent, 0u);
}

TEST_F(EmitterStateTest_446, DefaultPreCommentIndent_446) {
  std::size_t indent = state.GetPreCommentIndent();
  (void)indent;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_446, DefaultPostCommentIndent_446) {
  std::size_t indent = state.GetPostCommentIndent();
  (void)indent;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_446, DefaultFloatPrecision_446) {
  std::size_t prec = state.GetFloatPrecision();
  (void)prec;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_446, DefaultDoublePrecision_446) {
  std::size_t prec = state.GetDoublePrecision();
  (void)prec;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_446, DefaultMapKeyFormat_446) {
  EMITTER_MANIP fmt = state.GetMapKeyFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

// ============================================================
// Multiple scalars in a sequence
// ============================================================

TEST_F(EmitterStateTest_446, MultipleScalarsInSequence_446) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.StartedScalar();
  state.StartedScalar();
  EXPECT_EQ(3u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

// ============================================================
// CurGroupNodeType test
// ============================================================

TEST_F(EmitterStateTest_446, CurGroupNodeTypeInSeq_446) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  (void)nodeType;
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_446, CurGroupNodeTypeInMap_446) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  (void)nodeType;
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Map);
}

}  // namespace YAML
