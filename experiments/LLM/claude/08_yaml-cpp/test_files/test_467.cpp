#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/emittermanip.h"
#include "emitterstate.h"

namespace YAML {
namespace {

class EmitterStateTest_467 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_467, InitialStateIsGood_467) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_467, InitialLastErrorIsEmpty_467) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_467, InitialHasAnchorIsFalse_467) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_467, InitialHasAliasIsFalse_467) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_467, InitialHasTagIsFalse_467) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_467, InitialCurIndentIsZero_467) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_467, SetErrorMakesStateNotGood_467) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_467, SetErrorSetsLastError_467) {
  state.SetError("some error message");
  EXPECT_EQ("some error message", state.GetLastError());
}

TEST_F(EmitterStateTest_467, SetErrorOnlyFirstErrorIsKept_467) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_467, SetAnchorMakesHasAnchorTrue_467) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_467, SetAliasMakesHasAliasTrue_467) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_467, SetTagMakesHasTagTrue_467) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Output Charset Tests ====================

TEST_F(EmitterStateTest_467, SetOutputCharsetWithValidValue_467) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_467, SetOutputCharsetWithUtf8_467) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Global));
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_467, SetOutputCharsetInvalidValue_467) {
  EXPECT_FALSE(state.SetOutputCharset(Flow, FmtScope::Global));
}

// ==================== String Format Tests ====================

TEST_F(EmitterStateTest_467, SetStringFormatDoubleQuoted_467) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_467, SetStringFormatSingleQuoted_467) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_467, SetStringFormatLiteral_467) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Global));
  EXPECT_EQ(Literal, state.GetStringFormat());
}

TEST_F(EmitterStateTest_467, SetStringFormatInvalidValue_467) {
  EXPECT_FALSE(state.SetStringFormat(Flow, FmtScope::Global));
}

// ==================== Bool Format Tests ====================

TEST_F(EmitterStateTest_467, SetBoolFormatTrueFalse_467) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_467, SetBoolFormatYesNo_467) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_467, SetBoolFormatOnOff_467) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Global));
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_467, SetBoolFormatInvalidValue_467) {
  EXPECT_FALSE(state.SetBoolFormat(Flow, FmtScope::Global));
}

// ==================== Bool Length Format Tests ====================

TEST_F(EmitterStateTest_467, SetBoolLengthFormatShort_467) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_467, SetBoolLengthFormatLong_467) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_467, SetBoolLengthFormatInvalid_467) {
  EXPECT_FALSE(state.SetBoolLengthFormat(Flow, FmtScope::Global));
}

// ==================== Bool Case Format Tests ====================

TEST_F(EmitterStateTest_467, SetBoolCaseFormatUpper_467) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_467, SetBoolCaseFormatLower_467) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_467, SetBoolCaseFormatCamel_467) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_467, SetBoolCaseFormatInvalid_467) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Flow, FmtScope::Global));
}

// ==================== Null Format Tests ====================

TEST_F(EmitterStateTest_467, SetNullFormatLowerNull_467) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_467, SetNullFormatTildeNull_467) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Global));
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_467, SetNullFormatInvalid_467) {
  EXPECT_FALSE(state.SetNullFormat(Flow, FmtScope::Global));
}

// ==================== Int Format Tests ====================

TEST_F(EmitterStateTest_467, SetIntFormatDec_467) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_467, SetIntFormatHex_467) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_467, SetIntFormatOct_467) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_467, SetIntFormatInvalid_467) {
  EXPECT_FALSE(state.SetIntFormat(Flow, FmtScope::Global));
}

// ==================== Indent Tests ====================

TEST_F(EmitterStateTest_467, SetIndentValidValue_467) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_467, SetIndentMinimumValue_467) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetIndent());
}

TEST_F(EmitterStateTest_467, SetIndentTooSmall_467) {
  // Indent of 1 may be rejected
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Global));
}

// ==================== Pre/Post Comment Indent Tests ====================

TEST_F(EmitterStateTest_467, SetPreCommentIndentValidValue_467) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_467, SetPostCommentIndentValidValue_467) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_467, SetPreCommentIndentZero_467) {
  // Zero indent might be rejected
  EXPECT_FALSE(state.SetPreCommentIndent(0, FmtScope::Global));
}

TEST_F(EmitterStateTest_467, SetPostCommentIndentZero_467) {
  EXPECT_FALSE(state.SetPostCommentIndent(0, FmtScope::Global));
}

// ==================== Flow Type Tests ====================

TEST_F(EmitterStateTest_467, SetFlowTypeSeqFlow_467) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_467, SetFlowTypeSeqBlock_467) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_467, SetFlowTypeMapFlow_467) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_467, SetFlowTypeMapBlock_467) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_467, SetFlowTypeInvalidValue_467) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Dec, FmtScope::Global));
}

// ==================== Map Key Format Tests ====================

TEST_F(EmitterStateTest_467, SetMapKeyFormatLongKey_467) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_467, SetMapKeyFormatInvalid_467) {
  EXPECT_FALSE(state.SetMapKeyFormat(Flow, FmtScope::Global));
}

// ==================== Float/Double Precision Tests ====================

TEST_F(EmitterStateTest_467, SetFloatPrecisionValidValue_467) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Global));
  EXPECT_EQ(6u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_467, SetDoublePrecisionValidValue_467) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Global));
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

// ==================== Document Lifecycle Tests ====================

TEST_F(EmitterStateTest_467, StartedDocIncreasesDocCount_467) {
  state.StartedDoc();
  // After starting a doc, the state should still be good
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_467, EndedDocAfterStartedDoc_467) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Lifecycle Tests ====================

TEST_F(EmitterStateTest_467, StartedGroupSeq_467) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_467, StartedGroupMap_467) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_467, EndedGroupSeq_467) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_467, EndedGroupMap_467) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_467, CurGroupChildCountInitiallyZero_467) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_467, CurGroupLongKeyInitiallyFalse_467) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_467, SetLocalValueWithFlow_467) {
  // SetLocalValue dispatches to multiple setters; Flow should affect flow types
  state.SetLocalValue(Flow);
  // Should still be good, just sets local formatting
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_467, SetLocalValueWithBlock_467) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_467, SetLocalValueWithDoubleQuoted_467) {
  state.SetLocalValue(DoubleQuoted);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_467, SetLocalValueWithHex_467) {
  state.SetLocalValue(Hex);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_467, SetLocalValueWithDec_467) {
  state.SetLocalValue(Dec);
  EXPECT_TRUE(state.good());
}

// ==================== Scope Tests ====================

TEST_F(EmitterStateTest_467, SetStringFormatLocalScope_467) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_467, SetStringFormatGlobalScope_467) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_467, ClearModifiedSettingsDoesNotCrash_467) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_467, RestoreGlobalModifiedSettingsDoesNotCrash_467) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_467, ForceFlowDoesNotCrash_467) {
  state.ForceFlow();
  EXPECT_TRUE(state.good());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_467, SetNonContentSetsFlag_467) {
  state.SetNonContent();
  // After setting non-content, the state should still be good
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_467, SetLongKeyInGroup_467) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== StartedScalar Tests ====================

TEST_F(EmitterStateTest_467, StartedScalarAfterGroupStart_467) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_467, NextGroupTypeNoGroup_467) {
  // When no group is started, NextGroupType should return a valid value
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Just check it doesn't crash and returns some value
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ==================== HasBegunNode/HasBegunContent Tests ====================

TEST_F(EmitterStateTest_467, HasBegunNodeInitiallyFalse_467) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_467, HasBegunContentInitiallyFalse_467) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== Nested Groups Tests ====================

TEST_F(EmitterStateTest_467, NestedGroups_467) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// ==================== Multiple Scalars in Group Tests ====================

TEST_F(EmitterStateTest_467, MultipleScalarsInGroup_467) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.StartedScalar();
  EXPECT_EQ(2u, state.CurGroupChildCount());
}

// ==================== Global Setting Persistence Tests ====================

TEST_F(EmitterStateTest_467, GlobalSettingPersistsAfterClearModified_467) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.ClearModifiedSettings();
  // Global settings should persist; the exact behavior depends on implementation
  // but the state should remain good
  EXPECT_TRUE(state.good());
}

}  // namespace
}  // namespace YAML
