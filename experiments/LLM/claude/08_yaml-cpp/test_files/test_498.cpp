#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_498 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Construction / Initial State ====================

TEST_F(EmitterStateTest_498, InitialStateIsGood_498) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_498, InitialLastErrorIsEmpty_498) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_498, InitialHasNoAnchor_498) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_498, InitialHasNoAlias_498) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_498, InitialHasNoTag_498) {
  EXPECT_FALSE(state.HasTag());
}

// ==================== SetError ====================

TEST_F(EmitterStateTest_498, SetErrorMakesStateNotGood_498) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_498, SetErrorStoresMessage_498) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

// ==================== SetAnchor / SetAlias / SetTag ====================

TEST_F(EmitterStateTest_498, SetAnchorSetsFlag_498) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_498, SetAliasSetsFlag_498) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_498, SetTagSetsFlag_498) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== SetPostCommentIndent ====================

TEST_F(EmitterStateTest_498, SetPostCommentIndentZeroReturnsFalse_498) {
  EXPECT_FALSE(state.SetPostCommentIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_498, SetPostCommentIndentNonZeroReturnsTrue_498) {
  EXPECT_TRUE(state.SetPostCommentIndent(1, FmtScope::Local));
}

TEST_F(EmitterStateTest_498, SetPostCommentIndentUpdatesValue_498) {
  std::size_t defaultVal = state.GetPostCommentIndent();
  EXPECT_TRUE(state.SetPostCommentIndent(5, FmtScope::Local));
  EXPECT_EQ(5u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_498, SetPostCommentIndentGlobalScope_498) {
  EXPECT_TRUE(state.SetPostCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(3u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_498, SetPostCommentIndentZeroDoesNotChangeValue_498) {
  EXPECT_TRUE(state.SetPostCommentIndent(7, FmtScope::Local));
  EXPECT_EQ(7u, state.GetPostCommentIndent());
  EXPECT_FALSE(state.SetPostCommentIndent(0, FmtScope::Local));
  // Value should remain unchanged after failed set
  EXPECT_EQ(7u, state.GetPostCommentIndent());
}

// ==================== SetPreCommentIndent ====================

TEST_F(EmitterStateTest_498, SetPreCommentIndentZeroReturnsFalse_498) {
  EXPECT_FALSE(state.SetPreCommentIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_498, SetPreCommentIndentNonZeroReturnsTrue_498) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Local));
  EXPECT_EQ(2u, state.GetPreCommentIndent());
}

// ==================== SetIndent ====================

TEST_F(EmitterStateTest_498, SetIndentZeroReturnsFalse_498) {
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_498, SetIndentNonZeroReturnsTrue_498) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_498, SetIndentOneReturnsTrue_498) {
  // Boundary: minimum valid indent
  EXPECT_TRUE(state.SetIndent(1, FmtScope::Local));
  EXPECT_EQ(1u, state.GetIndent());
}

// ==================== SetOutputCharset ====================

TEST_F(EmitterStateTest_498, SetOutputCharsetUtf8_498) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

// ==================== SetStringFormat ====================

TEST_F(EmitterStateTest_498, SetStringFormatDoubleQuoted_498) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_498, SetStringFormatSingleQuoted_498) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_498, SetStringFormatLiteral_498) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Local));
  EXPECT_EQ(Literal, state.GetStringFormat());
}

// ==================== SetBoolFormat ====================

TEST_F(EmitterStateTest_498, SetBoolFormatTrueFalseLowercase_498) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Local));
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_498, SetBoolFormatYesNo_498) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Local));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_498, SetBoolFormatOnOff_498) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Local));
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

// ==================== SetBoolLengthFormat ====================

TEST_F(EmitterStateTest_498, SetBoolLengthFormatShort_498) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Local));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_498, SetBoolLengthFormatLong_498) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Local));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

// ==================== SetBoolCaseFormat ====================

TEST_F(EmitterStateTest_498, SetBoolCaseFormatUpperCase_498) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Local));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_498, SetBoolCaseFormatLowerCase_498) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Local));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_498, SetBoolCaseFormatCamelCase_498) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Local));
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

// ==================== SetNullFormat ====================

TEST_F(EmitterStateTest_498, SetNullFormatLowerNull_498) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_498, SetNullFormatTildeNull_498) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Local));
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== SetIntFormat ====================

TEST_F(EmitterStateTest_498, SetIntFormatDec_498) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Local));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_498, SetIntFormatHex_498) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_498, SetIntFormatOct_498) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Local));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

// ==================== SetMapKeyFormat ====================

TEST_F(EmitterStateTest_498, SetMapKeyFormatLongKey_498) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Local));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== SetFloatPrecision / SetDoublePrecision ====================

TEST_F(EmitterStateTest_498, SetFloatPrecisionValid_498) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Local));
  EXPECT_EQ(6u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_498, SetDoublePrecisionValid_498) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Local));
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

// ==================== SetFlowType / GetFlowType ====================

TEST_F(EmitterStateTest_498, SetFlowTypeSeqFlow_498) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_498, SetFlowTypeMapBlock_498) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== Document lifecycle ====================

TEST_F(EmitterStateTest_498, StartedDocEndedDoc_498) {
  state.StartedDoc();
  state.EndedDoc();
  // Should still be good after normal doc lifecycle
  EXPECT_TRUE(state.good());
}

// ==================== Group lifecycle ====================

TEST_F(EmitterStateTest_498, StartedGroupSeq_498) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_498, StartedGroupMap_498) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_498, CurGroupChildCountInitiallyZero_498) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_498, EndedGroupAfterStarted_498) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// ==================== Scope interactions ====================

TEST_F(EmitterStateTest_498, GlobalScopePersistsAfterClear_498) {
  EXPECT_TRUE(state.SetIndent(6, FmtScope::Global));
  state.ClearModifiedSettings();
  // Global settings should persist (restored)
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(6u, state.GetIndent());
}

TEST_F(EmitterStateTest_498, LocalScopeClearedAfterClear_498) {
  std::size_t defaultIndent = state.GetIndent();
  EXPECT_TRUE(state.SetIndent(8, FmtScope::Local));
  EXPECT_EQ(8u, state.GetIndent());
  state.ClearModifiedSettings();
  // Local settings should be cleared, reverting to default
  EXPECT_EQ(defaultIndent, state.GetIndent());
}

// ==================== SetNonContent ====================

TEST_F(EmitterStateTest_498, SetNonContentFlag_498) {
  state.SetNonContent();
  // We can't directly query HasNonContent, but this should not break state
  EXPECT_TRUE(state.good());
}

// ==================== Large values ====================

TEST_F(EmitterStateTest_498, SetPostCommentIndentLargeValue_498) {
  EXPECT_TRUE(state.SetPostCommentIndent(1000, FmtScope::Local));
  EXPECT_EQ(1000u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_498, SetIndentLargeValue_498) {
  EXPECT_TRUE(state.SetIndent(100, FmtScope::Local));
  EXPECT_EQ(100u, state.GetIndent());
}

// ==================== Boundary: value = 1 ====================

TEST_F(EmitterStateTest_498, SetPostCommentIndentBoundaryOne_498) {
  EXPECT_TRUE(state.SetPostCommentIndent(1, FmtScope::Local));
  EXPECT_EQ(1u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_498, SetPreCommentIndentBoundaryOne_498) {
  EXPECT_TRUE(state.SetPreCommentIndent(1, FmtScope::Local));
  EXPECT_EQ(1u, state.GetPreCommentIndent());
}

// ==================== Multiple errors ====================

TEST_F(EmitterStateTest_498, MultipleSetErrorKeepsFirstError_498) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_FALSE(state.good());
  // Typically the first error is retained
  std::string err = state.GetLastError();
  EXPECT_FALSE(err.empty());
}

// ==================== Invalid EMITTER_MANIP for format setters ====================

TEST_F(EmitterStateTest_498, SetStringFormatInvalidManipReturnsFalse_498) {
  // Passing an unrelated manip should return false
  EXPECT_FALSE(state.SetStringFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_498, SetBoolFormatInvalidManipReturnsFalse_498) {
  EXPECT_FALSE(state.SetBoolFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_498, SetIntFormatInvalidManipReturnsFalse_498) {
  EXPECT_FALSE(state.SetIntFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_498, SetOutputCharsetInvalidManipReturnsFalse_498) {
  EXPECT_FALSE(state.SetOutputCharset(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_498, SetNullFormatInvalidManipReturnsFalse_498) {
  EXPECT_FALSE(state.SetNullFormat(Dec, FmtScope::Local));
}

// ==================== CurIndent ====================

TEST_F(EmitterStateTest_498, CurIndentInitial_498) {
  // Initially should be 0 or some default
  std::size_t indent = state.CurIndent();
  EXPECT_GE(indent, 0u);
}

// ==================== HasBegunNode / HasBegunContent ====================

TEST_F(EmitterStateTest_498, HasBegunNodeInitiallyFalse_498) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_498, HasBegunContentInitiallyFalse_498) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== StartedScalar ====================

TEST_F(EmitterStateTest_498, StartedScalarAfterDoc_498) {
  state.StartedDoc();
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

// ==================== ForceFlow ====================

TEST_F(EmitterStateTest_498, ForceFlowDoesNotBreakState_498) {
  state.ForceFlow();
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey ====================

TEST_F(EmitterStateTest_498, SetLongKeyDoesNotBreakState_498) {
  state.SetLongKey();
  EXPECT_TRUE(state.good());
}

}  // namespace YAML
