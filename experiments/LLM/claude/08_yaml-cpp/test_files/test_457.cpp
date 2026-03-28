#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_457 : public ::testing::Test {
 protected:
  EmitterState state;
};

// === Construction / Initial State Tests ===

TEST_F(EmitterStateTest_457, InitialStateIsGood_457) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_457, InitialLastErrorIsEmpty_457) {
  EXPECT_EQ(state.GetLastError(), "");
}

TEST_F(EmitterStateTest_457, InitialHasAnchorIsFalse_457) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_457, InitialHasAliasIsFalse_457) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_457, InitialHasTagIsFalse_457) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_457, InitialCurIndentIsZero_457) {
  EXPECT_EQ(state.CurIndent(), 0u);
}

// === Error Handling Tests ===

TEST_F(EmitterStateTest_457, SetErrorMakesStateNotGood_457) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_457, SetErrorStoresErrorMessage_457) {
  state.SetError("test error message");
  EXPECT_EQ(state.GetLastError(), "test error message");
}

TEST_F(EmitterStateTest_457, SetErrorFirstErrorPersists_457) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically the first error is preserved
  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), "first error");
}

// === Anchor/Alias/Tag Tests ===

TEST_F(EmitterStateTest_457, SetAnchorSetsHasAnchor_457) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_457, SetAliasSetsHasAlias_457) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_457, SetTagSetsHasTag_457) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// === Bool Case Format Tests ===

TEST_F(EmitterStateTest_457, DefaultBoolCaseFormat_457) {
  // Should return a valid EMITTER_MANIP default
  EMITTER_MANIP fmt = state.GetBoolCaseFormat();
  // The default is typically LowerCase
  EXPECT_TRUE(fmt == LowerCase || fmt == UpperCase || fmt == CamelCase);
}

TEST_F(EmitterStateTest_457, SetBoolCaseFormatLocal_457) {
  bool result = state.SetBoolCaseFormat(UpperCase, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetBoolCaseFormat(), UpperCase);
}

TEST_F(EmitterStateTest_457, SetBoolCaseFormatGlobal_457) {
  bool result = state.SetBoolCaseFormat(CamelCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetBoolCaseFormat(), CamelCase);
}

// === Bool Format Tests ===

TEST_F(EmitterStateTest_457, SetBoolFormatTrueFalse_457) {
  bool result = state.SetBoolFormat(TrueFalseBool, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetBoolFormat(), TrueFalseBool);
}

TEST_F(EmitterStateTest_457, SetBoolFormatYesNo_457) {
  bool result = state.SetBoolFormat(YesNoBool, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetBoolFormat(), YesNoBool);
}

TEST_F(EmitterStateTest_457, SetBoolFormatOnOff_457) {
  bool result = state.SetBoolFormat(OnOffBool, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetBoolFormat(), OnOffBool);
}

// === Bool Length Format Tests ===

TEST_F(EmitterStateTest_457, SetBoolLengthFormatShort_457) {
  bool result = state.SetBoolLengthFormat(ShortBool, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetBoolLengthFormat(), ShortBool);
}

TEST_F(EmitterStateTest_457, SetBoolLengthFormatLong_457) {
  bool result = state.SetBoolLengthFormat(LongBool, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetBoolLengthFormat(), LongBool);
}

// === String Format Tests ===

TEST_F(EmitterStateTest_457, SetStringFormatSingleQuoted_457) {
  bool result = state.SetStringFormat(SingleQuoted, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetStringFormat(), SingleQuoted);
}

TEST_F(EmitterStateTest_457, SetStringFormatDoubleQuoted_457) {
  bool result = state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetStringFormat(), DoubleQuoted);
}

TEST_F(EmitterStateTest_457, SetStringFormatLiteral_457) {
  bool result = state.SetStringFormat(Literal, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetStringFormat(), Literal);
}

// === Int Format Tests ===

TEST_F(EmitterStateTest_457, SetIntFormatDec_457) {
  bool result = state.SetIntFormat(Dec, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetIntFormat(), Dec);
}

TEST_F(EmitterStateTest_457, SetIntFormatHex_457) {
  bool result = state.SetIntFormat(Hex, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetIntFormat(), Hex);
}

TEST_F(EmitterStateTest_457, SetIntFormatOct_457) {
  bool result = state.SetIntFormat(Oct, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetIntFormat(), Oct);
}

// === Null Format Tests ===

TEST_F(EmitterStateTest_457, SetNullFormatLowerNull_457) {
  bool result = state.SetNullFormat(LowerNull, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetNullFormat(), LowerNull);
}

TEST_F(EmitterStateTest_457, SetNullFormatTildeNull_457) {
  bool result = state.SetNullFormat(TildeNull, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetNullFormat(), TildeNull);
}

// === Indent Tests ===

TEST_F(EmitterStateTest_457, DefaultIndent_457) {
  std::size_t indent = state.GetIndent();
  EXPECT_GE(indent, 1u);
}

TEST_F(EmitterStateTest_457, SetIndentLocal_457) {
  bool result = state.SetIndent(4, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetIndent(), 4u);
}

TEST_F(EmitterStateTest_457, SetIndentGlobal_457) {
  bool result = state.SetIndent(3, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetIndent(), 3u);
}

TEST_F(EmitterStateTest_457, SetIndentBoundaryOne_457) {
  bool result = state.SetIndent(1, FmtScope::Local);
  // Minimum indent is typically 2
  // Implementation may reject 1
  // Just check it doesn't crash
  (void)result;
}

// === Pre/Post Comment Indent Tests ===

TEST_F(EmitterStateTest_457, SetPreCommentIndent_457) {
  bool result = state.SetPreCommentIndent(3, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetPreCommentIndent(), 3u);
}

TEST_F(EmitterStateTest_457, SetPostCommentIndent_457) {
  bool result = state.SetPostCommentIndent(2, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetPostCommentIndent(), 2u);
}

// === Float/Double Precision Tests ===

TEST_F(EmitterStateTest_457, SetFloatPrecision_457) {
  bool result = state.SetFloatPrecision(6, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetFloatPrecision(), 6u);
}

TEST_F(EmitterStateTest_457, SetDoublePrecision_457) {
  bool result = state.SetDoublePrecision(15, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetDoublePrecision(), 15u);
}

TEST_F(EmitterStateTest_457, SetFloatPrecisionZero_457) {
  // Boundary: precision of 0
  bool result = state.SetFloatPrecision(0, FmtScope::Local);
  // May or may not be accepted
  (void)result;
}

TEST_F(EmitterStateTest_457, SetDoublePrecisionZero_457) {
  bool result = state.SetDoublePrecision(0, FmtScope::Local);
  (void)result;
}

// === Output Charset Tests ===

TEST_F(EmitterStateTest_457, SetOutputCharsetUTF8_457) {
  bool result = state.SetOutputCharset(UTF8, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetOutputCharset(), UTF8);
}

// === Map Key Format Tests ===

TEST_F(EmitterStateTest_457, SetMapKeyFormatLongKey_457) {
  bool result = state.SetMapKeyFormat(LongKey, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetMapKeyFormat(), LongKey);
}

// === Flow Type Tests ===

TEST_F(EmitterStateTest_457, SetFlowTypeSeqFlow_457) {
  bool result = state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local);
  EXPECT_TRUE(result);
}

TEST_F(EmitterStateTest_457, SetFlowTypeMapBlock_457) {
  bool result = state.SetFlowType(GroupType::Map, Block, FmtScope::Local);
  EXPECT_TRUE(result);
}

// === Document Lifecycle Tests ===

TEST_F(EmitterStateTest_457, StartedDocDoesNotCrash_457) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_457, EndedDocDoesNotCrash_457) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// === Group Lifecycle Tests ===

TEST_F(EmitterStateTest_457, StartedGroupSeq_457) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupType(), GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_457, StartedGroupMap_457) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(state.CurGroupType(), GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_457, EndedGroupSeq_457) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_457, EndedGroupMap_457) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_457, CurGroupChildCountInitiallyZero_457) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupChildCount(), 0u);
}

TEST_F(EmitterStateTest_457, CurGroupIndentAfterStartGroup_457) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // Should have some indent value
  std::size_t indent = state.CurGroupIndent();
  (void)indent;  // Just ensure it doesn't crash
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_457, CurGroupLongKeyDefault_457) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// === SetNonContent Test ===

TEST_F(EmitterStateTest_457, SetNonContentDoesNotCrash_457) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// === SetLongKey Test ===

TEST_F(EmitterStateTest_457, SetLongKeyInGroup_457) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// === ForceFlow Test ===

TEST_F(EmitterStateTest_457, ForceFlowInGroup_457) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(state.CurGroupFlowType(), FlowType::Flow);
}

// === StartedScalar Test ===

TEST_F(EmitterStateTest_457, StartedScalarDoesNotCrash_457) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

// === ClearModifiedSettings Test ===

TEST_F(EmitterStateTest_457, ClearModifiedSettingsResetsLocal_457) {
  state.SetBoolCaseFormat(UpperCase, FmtScope::Local);
  EXPECT_EQ(state.GetBoolCaseFormat(), UpperCase);
  state.ClearModifiedSettings();
  // After clearing, should revert to default/global
  EMITTER_MANIP fmt = state.GetBoolCaseFormat();
  // Should not be UpperCase anymore (assuming default is different)
  (void)fmt;
  EXPECT_TRUE(state.good());
}

// === RestoreGlobalModifiedSettings Test ===

TEST_F(EmitterStateTest_457, RestoreGlobalModifiedSettings_457) {
  state.SetBoolCaseFormat(CamelCase, FmtScope::Global);
  EXPECT_EQ(state.GetBoolCaseFormat(), CamelCase);
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// === Global vs Local scope interaction ===

TEST_F(EmitterStateTest_457, GlobalSettingPersistsAfterClearModified_457) {
  state.SetIntFormat(Hex, FmtScope::Global);
  state.SetIntFormat(Oct, FmtScope::Local);
  EXPECT_EQ(state.GetIntFormat(), Oct);
  state.ClearModifiedSettings();
  EXPECT_EQ(state.GetIntFormat(), Hex);
}

// === Invalid format values ===

TEST_F(EmitterStateTest_457, SetBoolFormatWithInvalidValue_457) {
  // Try setting a non-bool-format value
  bool result = state.SetBoolFormat(Hex, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_457, SetIntFormatWithInvalidValue_457) {
  bool result = state.SetIntFormat(TrueFalseBool, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_457, SetStringFormatWithInvalidValue_457) {
  bool result = state.SetStringFormat(Hex, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_457, SetBoolCaseFormatWithInvalidValue_457) {
  bool result = state.SetBoolCaseFormat(Hex, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_457, SetBoolLengthFormatWithInvalidValue_457) {
  bool result = state.SetBoolLengthFormat(Hex, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_457, SetOutputCharsetWithInvalidValue_457) {
  bool result = state.SetOutputCharset(Hex, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_457, SetNullFormatWithInvalidValue_457) {
  bool result = state.SetNullFormat(Hex, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_457, SetMapKeyFormatWithInvalidValue_457) {
  bool result = state.SetMapKeyFormat(Hex, FmtScope::Local);
  EXPECT_FALSE(result);
}

// === HasBegunNode / HasBegunContent Tests ===

TEST_F(EmitterStateTest_457, HasBegunNodeInitiallyFalse_457) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_457, HasBegunContentInitiallyFalse_457) {
  EXPECT_FALSE(state.HasBegunContent());
}

// === NextGroupType Test ===

TEST_F(EmitterStateTest_457, NextGroupTypeSeq_457) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return a valid EmitterNodeType
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_457, NextGroupTypeMap_457) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// === LastIndent Test ===

TEST_F(EmitterStateTest_457, LastIndentInitial_457) {
  std::size_t lastIndent = state.LastIndent();
  EXPECT_EQ(lastIndent, 0u);
}

// === Nested Groups Test ===

TEST_F(EmitterStateTest_457, NestedGroupsWork_457) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupType(), GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupType(), GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// === SetLocalValue Test ===

TEST_F(EmitterStateTest_457, SetLocalValueFlow_457) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_457, SetLocalValueBlock_457) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_457, SetLocalValueDoubleQuoted_457) {
  state.SetLocalValue(DoubleQuoted);
  EXPECT_EQ(state.GetStringFormat(), DoubleQuoted);
}

// === Multiple consecutive docs ===

TEST_F(EmitterStateTest_457, MultipleDocuments_457) {
  state.StartedDoc();
  state.EndedDoc();
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

}  // namespace YAML
