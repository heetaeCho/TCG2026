#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_458 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_458, InitialStateIsGood_458) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_458, InitialLastErrorIsEmpty_458) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_458, InitialHasAnchorIsFalse_458) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_458, InitialHasAliasIsFalse_458) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_458, InitialHasTagIsFalse_458) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_458, InitialCurIndentIsZero_458) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_458, SetErrorMakesStateNotGood_458) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_458, SetErrorSetsLastError_458) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_458, SetErrorOnlyFirstErrorKept_458) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_458, SetAnchorMakesHasAnchorTrue_458) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_458, SetAliasMakesHasAliasTrue_458) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_458, SetTagMakesHasTagTrue_458) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Null Format Tests ====================

TEST_F(EmitterStateTest_458, DefaultNullFormat_458) {
  EMITTER_MANIP fmt = state.GetNullFormat();
  // Default null format should be a valid EMITTER_MANIP value
  // Typically it's TildeNull or LowerNull
  (void)fmt;  // Just ensure it doesn't crash
}

TEST_F(EmitterStateTest_458, SetNullFormatGlobal_458) {
  bool result = state.SetNullFormat(TildeNull, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_458, SetNullFormatLocal_458) {
  bool result = state.SetNullFormat(LowerNull, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_458, SetNullFormatCamelNull_458) {
  bool result = state.SetNullFormat(CamelNull, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(CamelNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_458, SetNullFormatUpperNull_458) {
  bool result = state.SetNullFormat(UpperNull, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(UpperNull, state.GetNullFormat());
}

// ==================== String Format Tests ====================

TEST_F(EmitterStateTest_458, SetStringFormatGlobal_458) {
  bool result = state.SetStringFormat(SingleQuoted, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_458, SetStringFormatDoubleQuoted_458) {
  bool result = state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_458, SetStringFormatLiteral_458) {
  bool result = state.SetStringFormat(Literal, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Literal, state.GetStringFormat());
}

// ==================== Bool Format Tests ====================

TEST_F(EmitterStateTest_458, SetBoolFormatGlobal_458) {
  bool result = state.SetBoolFormat(YesNoBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_458, SetBoolFormatTrueFalse_458) {
  bool result = state.SetBoolFormat(TrueFalseBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_458, SetBoolFormatOnOff_458) {
  bool result = state.SetBoolFormat(OnOffBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

// ==================== Bool Length Format Tests ====================

TEST_F(EmitterStateTest_458, SetBoolLengthFormatLong_458) {
  bool result = state.SetBoolLengthFormat(LongBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_458, SetBoolLengthFormatShort_458) {
  bool result = state.SetBoolLengthFormat(ShortBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

// ==================== Bool Case Format Tests ====================

TEST_F(EmitterStateTest_458, SetBoolCaseFormatUpper_458) {
  bool result = state.SetBoolCaseFormat(UpperCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_458, SetBoolCaseFormatLower_458) {
  bool result = state.SetBoolCaseFormat(LowerCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_458, SetBoolCaseFormatCamel_458) {
  bool result = state.SetBoolCaseFormat(CamelCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

// ==================== Int Format Tests ====================

TEST_F(EmitterStateTest_458, SetIntFormatDec_458) {
  bool result = state.SetIntFormat(Dec, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_458, SetIntFormatHex_458) {
  bool result = state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_458, SetIntFormatOct_458) {
  bool result = state.SetIntFormat(Oct, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

// ==================== Output Charset Tests ====================

TEST_F(EmitterStateTest_458, SetOutputCharsetUTF8_458) {
  bool result = state.SetOutputCharset(EscapeNonAscii, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

// ==================== Indent Tests ====================

TEST_F(EmitterStateTest_458, DefaultIndentIsReasonable_458) {
  std::size_t indent = state.GetIndent();
  EXPECT_GT(indent, 0u);
}

TEST_F(EmitterStateTest_458, SetIndentGlobal_458) {
  bool result = state.SetIndent(4, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_458, SetIndentLocal_458) {
  bool result = state.SetIndent(8, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(8u, state.GetIndent());
}

TEST_F(EmitterStateTest_458, SetIndentBoundaryOne_458) {
  // Indent of 1 might be a minimum boundary
  state.SetIndent(1, FmtScope::Global);
  // Just check it doesn't crash; behavior depends on implementation
}

// ==================== Pre/Post Comment Indent Tests ====================

TEST_F(EmitterStateTest_458, SetPreCommentIndent_458) {
  bool result = state.SetPreCommentIndent(3, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_458, SetPostCommentIndent_458) {
  bool result = state.SetPostCommentIndent(2, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

// ==================== Float/Double Precision Tests ====================

TEST_F(EmitterStateTest_458, SetFloatPrecisionGlobal_458) {
  bool result = state.SetFloatPrecision(5, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_458, SetDoublePrecisionGlobal_458) {
  bool result = state.SetDoublePrecision(10, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== Map Key Format Tests ====================

TEST_F(EmitterStateTest_458, SetMapKeyFormatLongKey_458) {
  bool result = state.SetMapKeyFormat(LongKey, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== Flow Type Tests ====================

TEST_F(EmitterStateTest_458, SetFlowTypeSeqFlow_458) {
  bool result = state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_458, SetFlowTypeMapFlow_458) {
  bool result = state.SetFlowType(GroupType::Map, Flow, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_458, SetFlowTypeSeqBlock_458) {
  bool result = state.SetFlowType(GroupType::Seq, Block, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_458, SetFlowTypeMapBlock_458) {
  bool result = state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== Doc State Tests ====================

TEST_F(EmitterStateTest_458, StartedDocAndEndedDoc_458) {
  state.StartedDoc();
  state.EndedDoc();
  // Should not crash; verify state is still good
  EXPECT_TRUE(state.good());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_458, StartAndEndSeqGroup_458) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_458, StartAndEndMapGroup_458) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_458, CurGroupChildCountInitiallyZero_458) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_458, CurGroupLongKeyInitiallyFalse_458) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== Scalar Tests ====================

TEST_F(EmitterStateTest_458, StartedScalarInGroup_458) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Seq);
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_458, SetNonContentDoesNotCrash_458) {
  state.SetNonContent();
  // Just verifying it doesn't crash
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_458, SetLongKeyInMapGroup_458) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_458, ForceFlowInGroup_458) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Seq);
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_458, ClearModifiedSettingsRestoresLocalChanges_458) {
  EMITTER_MANIP originalNullFmt = state.GetNullFormat();
  state.SetNullFormat(TildeNull, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_EQ(originalNullFmt, state.GetNullFormat());
}

// ==================== Invalid Format Tests ====================

TEST_F(EmitterStateTest_458, SetNullFormatWithInvalidValueReturnsFalse_458) {
  // Trying to set a format that's not valid for null format
  bool result = state.SetNullFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_458, SetBoolFormatWithInvalidValueReturnsFalse_458) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_458, SetIntFormatWithInvalidValueReturnsFalse_458) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_458, SetStringFormatWithInvalidValueReturnsFalse_458) {
  bool result = state.SetStringFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_458, NextGroupTypeForSeq_458) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return a valid EmitterNodeType
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_458, NextGroupTypeForMap_458) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ==================== Multiple Group Nesting Tests ====================

TEST_F(EmitterStateTest_458, NestedGroups_458) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_458, RestoreGlobalModifiedSettings_458) {
  state.SetNullFormat(TildeNull, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  // After restoring, the global modified settings should be cleared
  // The format should revert to default
  EXPECT_TRUE(state.good());
}

// ==================== HasBegunNode / HasBegunContent Tests ====================

TEST_F(EmitterStateTest_458, InitialHasBegunNodeIsFalse_458) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_458, InitialHasBegunContentIsFalse_458) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_458, LastIndentInitially_458) {
  std::size_t lastIndent = state.LastIndent();
  // Should not crash; value depends on implementation
  (void)lastIndent;
}

// ==================== CurGroupIndent Tests ====================

TEST_F(EmitterStateTest_458, CurGroupIndentInGroup_458) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  std::size_t indent = state.CurGroupIndent();
  (void)indent;
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Seq);
}

// ==================== Multiple Documents Tests ====================

TEST_F(EmitterStateTest_458, MultipleDocuments_458) {
  state.StartedDoc();
  state.EndedDoc();
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_458, SetLocalValueFlow_458) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_458, SetLocalValueBlock_458) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Map);
}

// ==================== Scope Tests ====================

TEST_F(EmitterStateTest_458, GlobalScopeNullFormatPersistsAfterClear_458) {
  state.SetNullFormat(TildeNull, FmtScope::Global);
  state.ClearModifiedSettings();
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_458, LocalScopeNullFormatClearedAfterClear_458) {
  EMITTER_MANIP original = state.GetNullFormat();
  state.SetNullFormat(TildeNull, FmtScope::Local);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
  state.ClearModifiedSettings();
  EXPECT_EQ(original, state.GetNullFormat());
}

// ==================== CurGroupNodeType Tests ====================

TEST_F(EmitterStateTest_458, CurGroupNodeTypeInSeq_458) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  (void)nodeType;
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_458, CurGroupNodeTypeInMap_458) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  (void)nodeType;
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Map);
}

}  // namespace YAML
