#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"
#include <limits>
#include <string>

namespace YAML {

class EmitterStateTest_503 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Construction / Initial State ====================

TEST_F(EmitterStateTest_503, InitialStateIsGood_503) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_503, InitialLastErrorIsEmpty_503) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_503, InitialHasAnchorIsFalse_503) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_503, InitialHasAliasIsFalse_503) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_503, InitialHasTagIsFalse_503) {
  EXPECT_FALSE(state.HasTag());
}

// ==================== SetError ====================

TEST_F(EmitterStateTest_503, SetErrorMakesStateNotGood_503) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_503, SetErrorStoresErrorMessage_503) {
  state.SetError("some error message");
  EXPECT_EQ("some error message", state.GetLastError());
}

TEST_F(EmitterStateTest_503, SetErrorMultipleTimes_503) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically first error is preserved, but we check it's not good
  EXPECT_FALSE(state.good());
}

// ==================== SetDoublePrecision ====================

TEST_F(EmitterStateTest_503, SetDoublePrecisionValidValue_503) {
  EXPECT_TRUE(state.SetDoublePrecision(6, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetDoublePrecisionZero_503) {
  EXPECT_TRUE(state.SetDoublePrecision(0, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetDoublePrecisionMaxDigits10_503) {
  std::size_t maxDigits = std::numeric_limits<double>::max_digits10;
  EXPECT_TRUE(state.SetDoublePrecision(maxDigits, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetDoublePrecisionExceedsMaxDigits10_503) {
  std::size_t tooLarge = std::numeric_limits<double>::max_digits10 + 1;
  EXPECT_FALSE(state.SetDoublePrecision(tooLarge, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetDoublePrecisionVeryLargeValue_503) {
  EXPECT_FALSE(state.SetDoublePrecision(100, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetDoublePrecisionAndGet_503) {
  state.SetDoublePrecision(10, FmtScope::Global);
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

TEST_F(EmitterStateTest_503, SetDoublePrecisionLocalScope_503) {
  EXPECT_TRUE(state.SetDoublePrecision(8, FmtScope::Local));
}

// ==================== SetFloatPrecision ====================

TEST_F(EmitterStateTest_503, SetFloatPrecisionValidValue_503) {
  EXPECT_TRUE(state.SetFloatPrecision(5, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetFloatPrecisionExceedsMax_503) {
  std::size_t tooLarge = std::numeric_limits<float>::max_digits10 + 1;
  EXPECT_FALSE(state.SetFloatPrecision(tooLarge, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetFloatPrecisionMaxDigits10_503) {
  std::size_t maxDigits = std::numeric_limits<float>::max_digits10;
  EXPECT_TRUE(state.SetFloatPrecision(maxDigits, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetFloatPrecisionAndGet_503) {
  state.SetFloatPrecision(4, FmtScope::Global);
  EXPECT_EQ(4u, state.GetFloatPrecision());
}

// ==================== SetIndent ====================

TEST_F(EmitterStateTest_503, SetIndentValidValue_503) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetIndentAndGet_503) {
  state.SetIndent(4, FmtScope::Global);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_503, SetIndentZeroReturnsFalse_503) {
  // 0 indent is typically invalid
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetIndentOneReturnsFalse_503) {
  // 1 indent might be invalid (minimum is typically 2)
  EXPECT_FALSE(state.SetIndent(1, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetIndentTwo_503) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Global));
}

// ==================== SetPreCommentIndent / SetPostCommentIndent ====================

TEST_F(EmitterStateTest_503, SetPreCommentIndentValid_503) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetPreCommentIndentAndGet_503) {
  state.SetPreCommentIndent(3, FmtScope::Global);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_503, SetPostCommentIndentValid_503) {
  EXPECT_TRUE(state.SetPostCommentIndent(1, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetPostCommentIndentAndGet_503) {
  state.SetPostCommentIndent(2, FmtScope::Global);
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

// ==================== SetOutputCharset ====================

TEST_F(EmitterStateTest_503, SetOutputCharsetUTF8_503) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetOutputCharsetAndGet_503) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Global);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_503, SetOutputCharsetInvalidValue_503) {
  // A value that's not a charset manipulator
  EXPECT_FALSE(state.SetOutputCharset(Flow, FmtScope::Global));
}

// ==================== SetStringFormat ====================

TEST_F(EmitterStateTest_503, SetStringFormatValid_503) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetStringFormatDoubleQuoted_503) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetStringFormatAndGet_503) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_503, SetStringFormatInvalid_503) {
  EXPECT_FALSE(state.SetStringFormat(Flow, FmtScope::Global));
}

// ==================== SetBoolFormat ====================

TEST_F(EmitterStateTest_503, SetBoolFormatTrueFalse_503) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetBoolFormatYesNo_503) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetBoolFormatOnOff_503) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetBoolFormatAndGet_503) {
  state.SetBoolFormat(YesNoBool, FmtScope::Global);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_503, SetBoolFormatInvalid_503) {
  EXPECT_FALSE(state.SetBoolFormat(Flow, FmtScope::Global));
}

// ==================== SetBoolLengthFormat ====================

TEST_F(EmitterStateTest_503, SetBoolLengthFormatLong_503) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetBoolLengthFormatShort_503) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetBoolLengthFormatAndGet_503) {
  state.SetBoolLengthFormat(ShortBool, FmtScope::Global);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

// ==================== SetBoolCaseFormat ====================

TEST_F(EmitterStateTest_503, SetBoolCaseFormatUpper_503) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetBoolCaseFormatLower_503) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetBoolCaseFormatCamel_503) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetBoolCaseFormatAndGet_503) {
  state.SetBoolCaseFormat(UpperCase, FmtScope::Global);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

// ==================== SetIntFormat ====================

TEST_F(EmitterStateTest_503, SetIntFormatDec_503) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetIntFormatHex_503) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetIntFormatOct_503) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetIntFormatAndGet_503) {
  state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_503, SetIntFormatInvalid_503) {
  EXPECT_FALSE(state.SetIntFormat(Flow, FmtScope::Global));
}

// ==================== SetNullFormat ====================

TEST_F(EmitterStateTest_503, SetNullFormatAndGet_503) {
  state.SetNullFormat(LowerNull, FmtScope::Global);
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

// ==================== Anchor / Alias / Tag ====================

TEST_F(EmitterStateTest_503, SetAnchorSetsHasAnchor_503) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_503, SetAliasSetsHasAlias_503) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_503, SetTagSetsHasTag_503) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== SetFlowType / GetFlowType ====================

TEST_F(EmitterStateTest_503, SetFlowTypeSeqFlow_503) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetFlowTypeSeqBlock_503) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetFlowTypeMapFlow_503) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, GetFlowTypeSeqAfterSet_503) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_503, GetFlowTypeMapAfterSet_503) {
  state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_503, SetFlowTypeInvalidValue_503) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Dec, FmtScope::Global));
}

// ==================== SetMapKeyFormat ====================

TEST_F(EmitterStateTest_503, SetMapKeyFormatLongKey_503) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
}

TEST_F(EmitterStateTest_503, SetMapKeyFormatAndGet_503) {
  state.SetMapKeyFormat(LongKey, FmtScope::Global);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== Doc operations ====================

TEST_F(EmitterStateTest_503, StartedDocAndEndedDoc_503) {
  state.StartedDoc();
  state.EndedDoc();
  // Should not crash; state should remain good
  EXPECT_TRUE(state.good());
}

// ==================== Group operations ====================

TEST_F(EmitterStateTest_503, StartedGroupSeq_503) {
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_503, StartedGroupMap_503) {
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_503, CurGroupChildCountInitiallyZero_503) {
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_503, EndedGroupAfterStarted_503) {
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  // After ending the only group, state should still be good
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_503, NestedGroups_503) {
  state.StartedGroup(GroupType::Map);
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
}

// ==================== CurGroupLongKey ====================

TEST_F(EmitterStateTest_503, CurGroupLongKeyDefaultFalse_503) {
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// ==================== ForceFlow ====================

TEST_F(EmitterStateTest_503, ForceFlowOnGroup_503) {
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== Scope tests for DoublePrecision ====================

TEST_F(EmitterStateTest_503, SetDoublePrecisionGlobalScope_503) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Global));
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

TEST_F(EmitterStateTest_503, SetDoublePrecisionLocalScope_503) {
  EXPECT_TRUE(state.SetDoublePrecision(8, FmtScope::Local));
  EXPECT_EQ(8u, state.GetDoublePrecision());
}

// ==================== ClearModifiedSettings ====================

TEST_F(EmitterStateTest_503, ClearModifiedSettingsDoesNotCrash_503) {
  state.SetDoublePrecision(10, FmtScope::Local);
  state.ClearModifiedSettings();
  // Should not crash
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterStateTest_503, RestoreGlobalModifiedSettingsDoesNotCrash_503) {
  state.SetDoublePrecision(10, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== StartedScalar ====================

TEST_F(EmitterStateTest_503, StartedScalarInGroup_503) {
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_503, MultipleScalarsInGroup_503) {
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.StartedScalar();
  EXPECT_EQ(2u, state.CurGroupChildCount());
}

// ==================== HasBegunNode / HasBegunContent ====================

TEST_F(EmitterStateTest_503, HasBegunNodeInitially_503) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_503, HasBegunContentInitially_503) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== SetNonContent ====================

TEST_F(EmitterStateTest_503, SetNonContentSetsFlag_503) {
  state.SetNonContent();
  // SetNonContent sets m_hasNonContent, observable through HasBegunNode potentially
  // We just verify it doesn't crash
  EXPECT_TRUE(state.good());
}

// ==================== CurIndent ====================

TEST_F(EmitterStateTest_503, CurIndentInitialValue_503) {
  // Initially cur indent should be 0
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== LastIndent ====================

TEST_F(EmitterStateTest_503, LastIndentInitial_503) {
  // Without any groups, calling LastIndent should return 0
  EXPECT_EQ(0u, state.LastIndent());
}

// ==================== NextGroupType ====================

TEST_F(EmitterStateTest_503, NextGroupTypeSeqWithNoGroup_503) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Without any current group context, it should still return a valid type
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ==================== SetLocalValue ====================

TEST_F(EmitterStateTest_503, SetLocalValueFlow_503) {
  state.SetLocalValue(Flow);
  // Should not crash and state remains good
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_503, SetLocalValueBlock_503) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

}  // namespace YAML
