#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_447 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_447, InitialStateIsGood_447) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_447, InitialLastErrorIsEmpty_447) {
  EXPECT_EQ(state.GetLastError(), "");
}

TEST_F(EmitterStateTest_447, InitialCurIndentIsZero_447) {
  EXPECT_EQ(state.CurIndent(), 0u);
}

TEST_F(EmitterStateTest_447, InitialHasAnchorIsFalse_447) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_447, InitialHasAliasIsFalse_447) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_447, InitialHasTagIsFalse_447) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_447, InitialHasBegunNodeIsFalse_447) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_447, InitialHasBegunContentIsFalse_447) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_447, SetErrorMakesStateNotGood_447) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_447, SetErrorSetsLastError_447) {
  state.SetError("test error message");
  EXPECT_EQ(state.GetLastError(), "test error message");
}

TEST_F(EmitterStateTest_447, SetErrorTwiceKeepsFirstError_447) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_FALSE(state.good());
  // Typically first error is preserved
  EXPECT_EQ(state.GetLastError(), "first error");
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_447, SetAnchorSetsHasAnchor_447) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_447, SetAliasSetsHasAlias_447) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_447, SetTagSetsHasTag_447) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Document Tests ====================

TEST_F(EmitterStateTest_447, StartedDocWorks_447) {
  state.StartedDoc();
  // After starting a doc, the state should still be good
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_447, EndedDocWorks_447) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Scalar Tests ====================

TEST_F(EmitterStateTest_447, StartedScalarClearsFlags_447) {
  state.SetAnchor();
  state.SetTag();
  state.StartedDoc();
  state.StartedScalar();
  // After starting a scalar, anchor and tag should be consumed
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_447, StartedGroupSeq_447) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupType(), GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_447, StartedGroupMap_447) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(state.CurGroupType(), GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_447, EndedGroupSeq_447) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_447, EndedGroupMap_447) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_447, CurGroupChildCountInitiallyZero_447) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupChildCount(), 0u);
}

TEST_F(EmitterStateTest_447, CurGroupLongKeyInitiallyFalse_447) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// ==================== Format Setting Tests ====================

TEST_F(EmitterStateTest_447, SetOutputCharsetGlobal_447) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
  EXPECT_EQ(state.GetOutputCharset(), EmitNonAscii);
}

TEST_F(EmitterStateTest_447, SetStringFormatGlobal_447) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(state.GetStringFormat(), SingleQuoted);
}

TEST_F(EmitterStateTest_447, SetStringFormatDoubleQuoted_447) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
  EXPECT_EQ(state.GetStringFormat(), DoubleQuoted);
}

TEST_F(EmitterStateTest_447, SetBoolFormatGlobal_447) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
  EXPECT_EQ(state.GetBoolFormat(), YesNoBool);
}

TEST_F(EmitterStateTest_447, SetBoolFormatTrueFalse_447) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
  EXPECT_EQ(state.GetBoolFormat(), TrueFalseBool);
}

TEST_F(EmitterStateTest_447, SetBoolFormatOnOff_447) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Global));
  EXPECT_EQ(state.GetBoolFormat(), OnOffBool);
}

TEST_F(EmitterStateTest_447, SetBoolLengthFormatGlobal_447) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(state.GetBoolLengthFormat(), ShortBool);
}

TEST_F(EmitterStateTest_447, SetBoolLengthFormatLong_447) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
  EXPECT_EQ(state.GetBoolLengthFormat(), LongBool);
}

TEST_F(EmitterStateTest_447, SetBoolCaseFormatGlobal_447) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(state.GetBoolCaseFormat(), UpperCase);
}

TEST_F(EmitterStateTest_447, SetBoolCaseFormatLowerCase_447) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
  EXPECT_EQ(state.GetBoolCaseFormat(), LowerCase);
}

TEST_F(EmitterStateTest_447, SetBoolCaseFormatCamelCase_447) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
  EXPECT_EQ(state.GetBoolCaseFormat(), CamelCase);
}

TEST_F(EmitterStateTest_447, SetNullFormatGlobal_447) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(state.GetNullFormat(), LowerNull);
}

TEST_F(EmitterStateTest_447, SetNullFormatTilde_447) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Global));
  EXPECT_EQ(state.GetNullFormat(), TildeNull);
}

TEST_F(EmitterStateTest_447, SetIntFormatDec_447) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
  EXPECT_EQ(state.GetIntFormat(), Dec);
}

TEST_F(EmitterStateTest_447, SetIntFormatHex_447) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(state.GetIntFormat(), Hex);
}

TEST_F(EmitterStateTest_447, SetIntFormatOct_447) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(state.GetIntFormat(), Oct);
}

// ==================== Indent Tests ====================

TEST_F(EmitterStateTest_447, SetIndentGlobal_447) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(state.GetIndent(), 4u);
}

TEST_F(EmitterStateTest_447, SetIndentBoundaryMin_447) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Global));
  EXPECT_EQ(state.GetIndent(), 2u);
}

TEST_F(EmitterStateTest_447, SetPreCommentIndentGlobal_447) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(state.GetPreCommentIndent(), 3u);
}

TEST_F(EmitterStateTest_447, SetPostCommentIndentGlobal_447) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
  EXPECT_EQ(state.GetPostCommentIndent(), 2u);
}

// ==================== Flow Type Tests ====================

TEST_F(EmitterStateTest_447, SetFlowTypeSeqBlock_447) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
  EXPECT_EQ(state.GetFlowType(GroupType::Seq), Block);
}

TEST_F(EmitterStateTest_447, SetFlowTypeSeqFlow_447) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EXPECT_EQ(state.GetFlowType(GroupType::Seq), Flow);
}

TEST_F(EmitterStateTest_447, SetFlowTypeMapBlock_447) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EXPECT_EQ(state.GetFlowType(GroupType::Map), Block);
}

TEST_F(EmitterStateTest_447, SetFlowTypeMapFlow_447) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
  EXPECT_EQ(state.GetFlowType(GroupType::Map), Flow);
}

// ==================== Map Key Format Tests ====================

TEST_F(EmitterStateTest_447, SetMapKeyFormatLongKey_447) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(state.GetMapKeyFormat(), LongKey);
}

// ==================== Precision Tests ====================

TEST_F(EmitterStateTest_447, SetFloatPrecisionGlobal_447) {
  EXPECT_TRUE(state.SetFloatPrecision(5, FmtScope::Global));
  EXPECT_EQ(state.GetFloatPrecision(), 5u);
}

TEST_F(EmitterStateTest_447, SetDoublePrecisionGlobal_447) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Global));
  EXPECT_EQ(state.GetDoublePrecision(), 10u);
}

TEST_F(EmitterStateTest_447, SetFloatPrecisionZero_447) {
  EXPECT_TRUE(state.SetFloatPrecision(0, FmtScope::Global));
  EXPECT_EQ(state.GetFloatPrecision(), 0u);
}

TEST_F(EmitterStateTest_447, SetDoublePrecisionZero_447) {
  EXPECT_TRUE(state.SetDoublePrecision(0, FmtScope::Global));
  EXPECT_EQ(state.GetDoublePrecision(), 0u);
}

// ==================== Local Scope Tests ====================

TEST_F(EmitterStateTest_447, SetIndentLocalScope_447) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_TRUE(state.SetIndent(6, FmtScope::Local));
  EXPECT_EQ(state.GetIndent(), 6u);
}

TEST_F(EmitterStateTest_447, ClearModifiedSettingsRestoresGlobal_447) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_TRUE(state.SetIndent(8, FmtScope::Local));
  EXPECT_EQ(state.GetIndent(), 8u);
  state.ClearModifiedSettings();
  EXPECT_EQ(state.GetIndent(), 4u);
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_447, SetNonContentWorks_447) {
  state.SetNonContent();
  // After setting non-content, HasBegunNode should reflect appropriately
  // This mainly tests that the call doesn't crash
  EXPECT_TRUE(state.good());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_447, ForceFlowWorks_447) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(state.CurGroupFlowType(), FlowType::Flow);
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_447, SetLongKeyWorks_447) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== Nested Groups Tests ====================

TEST_F(EmitterStateTest_447, NestedGroupsWork_447) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(state.CurGroupType(), GroupType::Map);

  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupType(), GroupType::Seq);

  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupType(), GroupType::Map);

  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_447, NextGroupTypeForSeq_447) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return some valid node type
  EXPECT_TRUE(state.good());
  (void)nodeType;  // Just verify it doesn't crash
}

TEST_F(EmitterStateTest_447, NextGroupTypeForMap_447) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  EXPECT_TRUE(state.good());
  (void)nodeType;
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_447, LastIndentWithNoGroups_447) {
  // Before any groups, LastIndent should return 0
  EXPECT_EQ(state.LastIndent(), 0u);
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_447, RestoreGlobalModifiedSettings_447) {
  EXPECT_TRUE(state.SetIndent(6, FmtScope::Global));
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(state.GetIndent(), 6u);
}

// ==================== Multiple Doc Tests ====================

TEST_F(EmitterStateTest_447, MultipleDocs_447) {
  state.StartedDoc();
  state.StartedScalar();
  state.EndedDoc();
  
  state.StartedDoc();
  state.StartedScalar();
  state.EndedDoc();
  
  EXPECT_TRUE(state.good());
}

// ==================== Invalid Format Tests ====================

TEST_F(EmitterStateTest_447, SetOutputCharsetInvalidValue_447) {
  // Passing a non-charset manip should return false
  bool result = state.SetOutputCharset(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_447, SetStringFormatInvalidValue_447) {
  bool result = state.SetStringFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_447, SetBoolFormatInvalidValue_447) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_447, SetIntFormatInvalidValue_447) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== HasBegunNode after setting properties ====================

TEST_F(EmitterStateTest_447, HasBegunNodeAfterAnchor_447) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_447, HasBegunNodeAfterTag_447) {
  state.SetTag();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_447, HasBegunNodeAfterAlias_447) {
  state.SetAlias();
  EXPECT_TRUE(state.HasBegunNode());
}

// ==================== Default Get Value Tests ====================

TEST_F(EmitterStateTest_447, DefaultOutputCharset_447) {
  // Default should be a valid EMITTER_MANIP
  EMITTER_MANIP charset = state.GetOutputCharset();
  (void)charset;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_447, DefaultStringFormat_447) {
  EMITTER_MANIP fmt = state.GetStringFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_447, DefaultBoolFormat_447) {
  EMITTER_MANIP fmt = state.GetBoolFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_447, DefaultIntFormat_447) {
  EMITTER_MANIP fmt = state.GetIntFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_447, DefaultIndent_447) {
  std::size_t indent = state.GetIndent();
  EXPECT_GT(indent, 0u);
}

TEST_F(EmitterStateTest_447, DefaultFloatPrecision_447) {
  std::size_t prec = state.GetFloatPrecision();
  (void)prec;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_447, DefaultDoublePrecision_447) {
  std::size_t prec = state.GetDoublePrecision();
  (void)prec;
  EXPECT_TRUE(state.good());
}

}  // namespace YAML
