#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_456 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_456, InitialStateIsGood_456) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_456, InitialLastErrorIsEmpty_456) {
  EXPECT_EQ(state.GetLastError(), "");
}

TEST_F(EmitterStateTest_456, InitialHasAnchorIsFalse_456) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_456, InitialHasAliasIsFalse_456) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_456, InitialHasTagIsFalse_456) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_456, InitialCurIndentIsZero_456) {
  EXPECT_EQ(state.CurIndent(), 0u);
}

// ==================== Error Handling Tests ====================

TEST_F(EmitterStateTest_456, SetErrorMakesStateNotGood_456) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_456, SetErrorStoresMessage_456) {
  state.SetError("some error message");
  EXPECT_EQ(state.GetLastError(), "some error message");
}

TEST_F(EmitterStateTest_456, SetErrorFirstErrorPersists_456) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically the first error is kept
  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), "first error");
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_456, SetAnchorSetsHasAnchor_456) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_456, SetAliasSetsHasAlias_456) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_456, SetTagSetsHasTag_456) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Default Format Getter Tests ====================

TEST_F(EmitterStateTest_456, DefaultBoolLengthFormatIsLongBool_456) {
  // Default bool length format is typically TrueFalseBool (long form)
  EMITTER_MANIP fmt = state.GetBoolLengthFormat();
  EXPECT_EQ(fmt, LongBool);
}

TEST_F(EmitterStateTest_456, DefaultBoolFormatIsYesNoBool_456) {
  EMITTER_MANIP fmt = state.GetBoolFormat();
  EXPECT_EQ(fmt, TrueFalseBool);
}

TEST_F(EmitterStateTest_456, DefaultBoolCaseFormat_456) {
  EMITTER_MANIP fmt = state.GetBoolCaseFormat();
  EXPECT_EQ(fmt, LowerCase);
}

TEST_F(EmitterStateTest_456, DefaultStringFormat_456) {
  EMITTER_MANIP fmt = state.GetStringFormat();
  // Default is typically Auto
  EXPECT_EQ(fmt, Auto);
}

TEST_F(EmitterStateTest_456, DefaultIntFormat_456) {
  EMITTER_MANIP fmt = state.GetIntFormat();
  EXPECT_EQ(fmt, Dec);
}

TEST_F(EmitterStateTest_456, DefaultOutputCharset_456) {
  EMITTER_MANIP charset = state.GetOutputCharset();
  EXPECT_EQ(charset, EmitNonAscii);
}

TEST_F(EmitterStateTest_456, DefaultNullFormat_456) {
  EMITTER_MANIP fmt = state.GetNullFormat();
  EXPECT_EQ(fmt, LowerNull);
}

TEST_F(EmitterStateTest_456, DefaultMapKeyFormat_456) {
  EMITTER_MANIP fmt = state.GetMapKeyFormat();
  EXPECT_EQ(fmt, Auto);
}

TEST_F(EmitterStateTest_456, DefaultIndent_456) {
  std::size_t indent = state.GetIndent();
  EXPECT_EQ(indent, 2u);
}

TEST_F(EmitterStateTest_456, DefaultPreCommentIndent_456) {
  std::size_t indent = state.GetPreCommentIndent();
  EXPECT_EQ(indent, 2u);
}

TEST_F(EmitterStateTest_456, DefaultPostCommentIndent_456) {
  std::size_t indent = state.GetPostCommentIndent();
  EXPECT_EQ(indent, 1u);
}

TEST_F(EmitterStateTest_456, DefaultFloatPrecision_456) {
  std::size_t prec = state.GetFloatPrecision();
  EXPECT_GT(prec, 0u);
}

TEST_F(EmitterStateTest_456, DefaultDoublePrecision_456) {
  std::size_t prec = state.GetDoublePrecision();
  EXPECT_GT(prec, 0u);
}

// ==================== SetBoolLengthFormat Tests ====================

TEST_F(EmitterStateTest_456, SetBoolLengthFormatLocalScope_456) {
  bool result = state.SetBoolLengthFormat(ShortBool, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetBoolLengthFormat(), ShortBool);
}

TEST_F(EmitterStateTest_456, SetBoolLengthFormatGlobalScope_456) {
  bool result = state.SetBoolLengthFormat(ShortBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetBoolLengthFormat(), ShortBool);
}

TEST_F(EmitterStateTest_456, SetBoolLengthFormatInvalidValue_456) {
  // Passing an unrelated EMITTER_MANIP should fail
  bool result = state.SetBoolLengthFormat(Dec, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetBoolFormat Tests ====================

TEST_F(EmitterStateTest_456, SetBoolFormatLocal_456) {
  bool result = state.SetBoolFormat(YesNoBool, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetBoolFormat(), YesNoBool);
}

TEST_F(EmitterStateTest_456, SetBoolFormatInvalid_456) {
  bool result = state.SetBoolFormat(Dec, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetBoolCaseFormat Tests ====================

TEST_F(EmitterStateTest_456, SetBoolCaseFormatLocal_456) {
  bool result = state.SetBoolCaseFormat(UpperCase, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetBoolCaseFormat(), UpperCase);
}

TEST_F(EmitterStateTest_456, SetBoolCaseFormatCamelCase_456) {
  bool result = state.SetBoolCaseFormat(CamelCase, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetBoolCaseFormat(), CamelCase);
}

TEST_F(EmitterStateTest_456, SetBoolCaseFormatInvalid_456) {
  bool result = state.SetBoolCaseFormat(Dec, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetStringFormat Tests ====================

TEST_F(EmitterStateTest_456, SetStringFormatSingleQuoted_456) {
  bool result = state.SetStringFormat(SingleQuoted, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetStringFormat(), SingleQuoted);
}

TEST_F(EmitterStateTest_456, SetStringFormatDoubleQuoted_456) {
  bool result = state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetStringFormat(), DoubleQuoted);
}

TEST_F(EmitterStateTest_456, SetStringFormatLiteral_456) {
  bool result = state.SetStringFormat(Literal, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetStringFormat(), Literal);
}

TEST_F(EmitterStateTest_456, SetStringFormatInvalid_456) {
  bool result = state.SetStringFormat(Dec, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetIntFormat Tests ====================

TEST_F(EmitterStateTest_456, SetIntFormatHex_456) {
  bool result = state.SetIntFormat(Hex, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetIntFormat(), Hex);
}

TEST_F(EmitterStateTest_456, SetIntFormatOct_456) {
  bool result = state.SetIntFormat(Oct, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetIntFormat(), Oct);
}

TEST_F(EmitterStateTest_456, SetIntFormatInvalid_456) {
  bool result = state.SetIntFormat(TrueFalseBool, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetOutputCharset Tests ====================

TEST_F(EmitterStateTest_456, SetOutputCharsetEscapeNonAscii_456) {
  bool result = state.SetOutputCharset(EscapeNonAscii, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetOutputCharset(), EscapeNonAscii);
}

TEST_F(EmitterStateTest_456, SetOutputCharsetInvalid_456) {
  bool result = state.SetOutputCharset(Dec, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetNullFormat Tests ====================

TEST_F(EmitterStateTest_456, SetNullFormatTildeNull_456) {
  bool result = state.SetNullFormat(TildeNull, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetNullFormat(), TildeNull);
}

TEST_F(EmitterStateTest_456, SetNullFormatUpperNull_456) {
  bool result = state.SetNullFormat(UpperNull, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetNullFormat(), UpperNull);
}

TEST_F(EmitterStateTest_456, SetNullFormatCamelNull_456) {
  bool result = state.SetNullFormat(CamelNull, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetNullFormat(), CamelNull);
}

TEST_F(EmitterStateTest_456, SetNullFormatInvalid_456) {
  bool result = state.SetNullFormat(Dec, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetIndent Tests ====================

TEST_F(EmitterStateTest_456, SetIndentValidValue_456) {
  bool result = state.SetIndent(4, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetIndent(), 4u);
}

TEST_F(EmitterStateTest_456, SetIndentZero_456) {
  // Zero indent should be rejected (minimum is typically 2)
  bool result = state.SetIndent(0, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_456, SetIndentOne_456) {
  // Indent of 1 might be rejected
  bool result = state.SetIndent(1, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_456, SetIndentGlobal_456) {
  bool result = state.SetIndent(3, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetIndent(), 3u);
}

// ==================== SetPreCommentIndent Tests ====================

TEST_F(EmitterStateTest_456, SetPreCommentIndentValid_456) {
  bool result = state.SetPreCommentIndent(3, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetPreCommentIndent(), 3u);
}

TEST_F(EmitterStateTest_456, SetPreCommentIndentZero_456) {
  bool result = state.SetPreCommentIndent(0, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetPostCommentIndent Tests ====================

TEST_F(EmitterStateTest_456, SetPostCommentIndentValid_456) {
  bool result = state.SetPostCommentIndent(3, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetPostCommentIndent(), 3u);
}

TEST_F(EmitterStateTest_456, SetPostCommentIndentZero_456) {
  bool result = state.SetPostCommentIndent(0, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetMapKeyFormat Tests ====================

TEST_F(EmitterStateTest_456, SetMapKeyFormatLongKey_456) {
  bool result = state.SetMapKeyFormat(LongKey, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetMapKeyFormat(), LongKey);
}

TEST_F(EmitterStateTest_456, SetMapKeyFormatInvalid_456) {
  bool result = state.SetMapKeyFormat(Dec, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetFloatPrecision Tests ====================

TEST_F(EmitterStateTest_456, SetFloatPrecisionValid_456) {
  bool result = state.SetFloatPrecision(5, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetFloatPrecision(), 5u);
}

// ==================== SetDoublePrecision Tests ====================

TEST_F(EmitterStateTest_456, SetDoublePrecisionValid_456) {
  bool result = state.SetDoublePrecision(10, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(state.GetDoublePrecision(), 10u);
}

// ==================== Flow Type Tests ====================

TEST_F(EmitterStateTest_456, SetFlowTypeSeqFlow_456) {
  bool result = state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local);
  EXPECT_TRUE(result);
}

TEST_F(EmitterStateTest_456, SetFlowTypeMapBlock_456) {
  bool result = state.SetFlowType(GroupType::Map, Block, FmtScope::Local);
  EXPECT_TRUE(result);
}

TEST_F(EmitterStateTest_456, SetFlowTypeInvalid_456) {
  bool result = state.SetFlowType(GroupType::Seq, Dec, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== Document Lifecycle Tests ====================

TEST_F(EmitterStateTest_456, StartedDocInitially_456) {
  state.StartedDoc();
  // After starting a doc, state should still be good
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_456, EndedDocAfterStarted_456) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Lifecycle Tests ====================

TEST_F(EmitterStateTest_456, StartedGroupSeq_456) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
  EXPECT_EQ(state.CurGroupType(), GroupType::Seq);
}

TEST_F(EmitterStateTest_456, StartedGroupMap_456) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
  EXPECT_EQ(state.CurGroupType(), GroupType::Map);
}

TEST_F(EmitterStateTest_456, EndedGroupMatchesStarted_456) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_456, CurGroupChildCountInitiallyZero_456) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupChildCount(), 0u);
}

TEST_F(EmitterStateTest_456, CurGroupIndentReturnsValue_456) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // Should return some valid indent value
  std::size_t indent = state.CurGroupIndent();
  (void)indent;  // Just check it doesn't crash
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_456, CurGroupLongKeyDefault_456) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_456, CurGroupFlowType_456) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  FlowType::value flow = state.CurGroupFlowType();
  (void)flow;
  EXPECT_TRUE(state.good());
}

// ==================== Scalar Tests ====================

TEST_F(EmitterStateTest_456, StartedScalarInGroup_456) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_456, StartedScalarIncrementsChildCount_456) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupChildCount(), 0u);
  state.StartedScalar();
  EXPECT_EQ(state.CurGroupChildCount(), 1u);
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_456, SetNonContentDoesNotAffectGoodState_456) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_456, SetLongKeyInGroup_456) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_456, ForceFlowInGroup_456) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(state.CurGroupFlowType(), FlowType::Flow);
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_456, ClearModifiedSettingsRestoresLocal_456) {
  state.SetBoolLengthFormat(ShortBool, FmtScope::Local);
  EXPECT_EQ(state.GetBoolLengthFormat(), ShortBool);
  state.ClearModifiedSettings();
  EXPECT_EQ(state.GetBoolLengthFormat(), LongBool);
}

TEST_F(EmitterStateTest_456, ClearModifiedSettingsDoesNotAffectGlobal_456) {
  state.SetBoolLengthFormat(ShortBool, FmtScope::Global);
  EXPECT_EQ(state.GetBoolLengthFormat(), ShortBool);
  state.ClearModifiedSettings();
  // Global settings should persist
  EXPECT_EQ(state.GetBoolLengthFormat(), ShortBool);
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_456, RestoreGlobalModifiedSettingsResetsToDefault_456) {
  state.SetBoolLengthFormat(ShortBool, FmtScope::Global);
  EXPECT_EQ(state.GetBoolLengthFormat(), ShortBool);
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(state.GetBoolLengthFormat(), LongBool);
}

// ==================== HasBegunNode / HasBegunContent Tests ====================

TEST_F(EmitterStateTest_456, HasBegunNodeInitiallyFalse_456) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_456, HasBegunContentInitiallyFalse_456) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_456, NextGroupTypeForSeqNoGroups_456) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  EXPECT_EQ(nodeType, EmitterNodeType::NoNode);
}

TEST_F(EmitterStateTest_456, NextGroupTypeForMapNoGroups_456) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  EXPECT_EQ(nodeType, EmitterNodeType::NoNode);
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_456, LastIndentInitially_456) {
  std::size_t lastIndent = state.LastIndent();
  EXPECT_EQ(lastIndent, 0u);
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_456, SetLocalValueFlow_456) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_456, SetLocalValueBlock_456) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_456, SetLocalValueDoubleQuoted_456) {
  state.SetLocalValue(DoubleQuoted);
  EXPECT_TRUE(state.good());
  EXPECT_EQ(state.GetStringFormat(), DoubleQuoted);
}

TEST_F(EmitterStateTest_456, SetLocalValueHex_456) {
  state.SetLocalValue(Hex);
  EXPECT_TRUE(state.good());
  EXPECT_EQ(state.GetIntFormat(), Hex);
}

// ==================== Multiple Group Nesting Tests ====================

TEST_F(EmitterStateTest_456, NestedGroupsWork_456) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.StartedScalar();  // key
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupType(), GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupType(), GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// ==================== Anchor/Alias/Tag Reset After Node Tests ====================

TEST_F(EmitterStateTest_456, AnchorResetAfterScalar_456) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_456, TagResetAfterScalar_456) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_456, AliasResetAfterScalar_456) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAlias());
}

}  // namespace YAML
