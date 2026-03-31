#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {
namespace {

class EmitterStateTest_490 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Construction / Initial State ====================

TEST_F(EmitterStateTest_490, InitialStateIsGood_490) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_490, InitialLastErrorIsEmpty_490) {
  EXPECT_EQ(state.GetLastError(), "");
}

TEST_F(EmitterStateTest_490, InitialHasNoAnchor_490) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_490, InitialHasNoAlias_490) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_490, InitialHasNoTag_490) {
  EXPECT_FALSE(state.HasTag());
}

// ==================== SetError ====================

TEST_F(EmitterStateTest_490, SetErrorMakesStateNotGood_490) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_490, SetErrorSetsLastError_490) {
  state.SetError("some error message");
  EXPECT_EQ(state.GetLastError(), "some error message");
}

TEST_F(EmitterStateTest_490, SetErrorEmptyString_490) {
  state.SetError("");
  EXPECT_FALSE(state.good());
}

// ==================== SetStringFormat ====================

TEST_F(EmitterStateTest_490, SetStringFormatAuto_490) {
  EXPECT_TRUE(state.SetStringFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetStringFormatSingleQuoted_490) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetStringFormatDoubleQuoted_490) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetStringFormatLiteral_490) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetStringFormatInvalidValue_490) {
  EXPECT_FALSE(state.SetStringFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetStringFormatInvalidBlock_490) {
  EXPECT_FALSE(state.SetStringFormat(Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetStringFormatInvalidDec_490) {
  EXPECT_FALSE(state.SetStringFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetStringFormatGlobalScope_490) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
}

TEST_F(EmitterStateTest_490, GetStringFormatAfterSet_490) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(state.GetStringFormat(), DoubleQuoted);
}

TEST_F(EmitterStateTest_490, GetStringFormatAfterSetSingleQuoted_490) {
  state.SetStringFormat(SingleQuoted, FmtScope::Local);
  EXPECT_EQ(state.GetStringFormat(), SingleQuoted);
}

TEST_F(EmitterStateTest_490, GetStringFormatAfterSetLiteral_490) {
  state.SetStringFormat(Literal, FmtScope::Local);
  EXPECT_EQ(state.GetStringFormat(), Literal);
}

// ==================== SetOutputCharset ====================

TEST_F(EmitterStateTest_490, SetOutputCharsetEmitNonAscii_490) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetOutputCharsetEscapeNonAscii_490) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetOutputCharsetEscapeAsJson_490) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeAsJson, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetOutputCharsetInvalid_490) {
  EXPECT_FALSE(state.SetOutputCharset(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, GetOutputCharsetAfterSet_490) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Local);
  EXPECT_EQ(state.GetOutputCharset(), EscapeNonAscii);
}

// ==================== SetBoolFormat ====================

TEST_F(EmitterStateTest_490, SetBoolFormatYesNo_490) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetBoolFormatTrueFalse_490) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetBoolFormatOnOff_490) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetBoolFormatInvalid_490) {
  EXPECT_FALSE(state.SetBoolFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, GetBoolFormatAfterSet_490) {
  state.SetBoolFormat(YesNoBool, FmtScope::Local);
  EXPECT_EQ(state.GetBoolFormat(), YesNoBool);
}

// ==================== SetBoolLengthFormat ====================

TEST_F(EmitterStateTest_490, SetBoolLengthFormatLong_490) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetBoolLengthFormatShort_490) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetBoolLengthFormatInvalid_490) {
  EXPECT_FALSE(state.SetBoolLengthFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, GetBoolLengthFormatAfterSet_490) {
  state.SetBoolLengthFormat(ShortBool, FmtScope::Local);
  EXPECT_EQ(state.GetBoolLengthFormat(), ShortBool);
}

// ==================== SetBoolCaseFormat ====================

TEST_F(EmitterStateTest_490, SetBoolCaseFormatUpperCase_490) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetBoolCaseFormatLowerCase_490) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetBoolCaseFormatCamelCase_490) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetBoolCaseFormatInvalid_490) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, GetBoolCaseFormatAfterSet_490) {
  state.SetBoolCaseFormat(UpperCase, FmtScope::Local);
  EXPECT_EQ(state.GetBoolCaseFormat(), UpperCase);
}

// ==================== SetNullFormat ====================

TEST_F(EmitterStateTest_490, SetNullFormatLowerNull_490) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetNullFormatUpperNull_490) {
  EXPECT_TRUE(state.SetNullFormat(UpperNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetNullFormatCamelNull_490) {
  EXPECT_TRUE(state.SetNullFormat(CamelNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetNullFormatTildeNull_490) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetNullFormatInvalid_490) {
  EXPECT_FALSE(state.SetNullFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, GetNullFormatAfterSet_490) {
  state.SetNullFormat(TildeNull, FmtScope::Local);
  EXPECT_EQ(state.GetNullFormat(), TildeNull);
}

// ==================== SetIntFormat ====================

TEST_F(EmitterStateTest_490, SetIntFormatDec_490) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetIntFormatHex_490) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetIntFormatOct_490) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetIntFormatInvalid_490) {
  EXPECT_FALSE(state.SetIntFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, GetIntFormatAfterSet_490) {
  state.SetIntFormat(Hex, FmtScope::Local);
  EXPECT_EQ(state.GetIntFormat(), Hex);
}

// ==================== SetIndent ====================

TEST_F(EmitterStateTest_490, SetIndentValid_490) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetIndentMinimumBoundary_490) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetIndentTooSmall_490) {
  EXPECT_FALSE(state.SetIndent(1, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetIndentZero_490) {
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, GetIndentAfterSet_490) {
  state.SetIndent(6, FmtScope::Local);
  EXPECT_EQ(state.GetIndent(), 6u);
}

// ==================== SetPreCommentIndent ====================

TEST_F(EmitterStateTest_490, SetPreCommentIndentValid_490) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetPreCommentIndentZero_490) {
  EXPECT_FALSE(state.SetPreCommentIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, GetPreCommentIndentAfterSet_490) {
  state.SetPreCommentIndent(3, FmtScope::Local);
  EXPECT_EQ(state.GetPreCommentIndent(), 3u);
}

// ==================== SetPostCommentIndent ====================

TEST_F(EmitterStateTest_490, SetPostCommentIndentValid_490) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetPostCommentIndentZero_490) {
  EXPECT_FALSE(state.SetPostCommentIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, GetPostCommentIndentAfterSet_490) {
  state.SetPostCommentIndent(5, FmtScope::Local);
  EXPECT_EQ(state.GetPostCommentIndent(), 5u);
}

// ==================== SetFlowType ====================

TEST_F(EmitterStateTest_490, SetFlowTypeSeqFlow_490) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetFlowTypeSeqBlock_490) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetFlowTypeMapFlow_490) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetFlowTypeMapBlock_490) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetFlowTypeInvalid_490) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, GetFlowTypeSeqAfterSet_490) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local);
  EXPECT_EQ(state.GetFlowType(GroupType::Seq), Flow);
}

TEST_F(EmitterStateTest_490, GetFlowTypeMapAfterSet_490) {
  state.SetFlowType(GroupType::Map, Block, FmtScope::Local);
  EXPECT_EQ(state.GetFlowType(GroupType::Map), Block);
}

// ==================== SetMapKeyFormat ====================

TEST_F(EmitterStateTest_490, SetMapKeyFormatLongKey_490) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetMapKeyFormatAuto_490) {
  EXPECT_TRUE(state.SetMapKeyFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetMapKeyFormatInvalid_490) {
  EXPECT_FALSE(state.SetMapKeyFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, GetMapKeyFormatAfterSet_490) {
  state.SetMapKeyFormat(LongKey, FmtScope::Local);
  EXPECT_EQ(state.GetMapKeyFormat(), LongKey);
}

// ==================== SetFloatPrecision ====================

TEST_F(EmitterStateTest_490, SetFloatPrecisionValid_490) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, GetFloatPrecisionAfterSet_490) {
  state.SetFloatPrecision(3, FmtScope::Local);
  EXPECT_EQ(state.GetFloatPrecision(), 3u);
}

// ==================== SetDoublePrecision ====================

TEST_F(EmitterStateTest_490, SetDoublePrecisionValid_490) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, GetDoublePrecisionAfterSet_490) {
  state.SetDoublePrecision(8, FmtScope::Local);
  EXPECT_EQ(state.GetDoublePrecision(), 8u);
}

// ==================== SetAnchor / HasAnchor ====================

TEST_F(EmitterStateTest_490, SetAnchorSetsHasAnchor_490) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

// ==================== SetAlias / HasAlias ====================

TEST_F(EmitterStateTest_490, SetAliasSetsHasAlias_490) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

// ==================== SetTag / HasTag ====================

TEST_F(EmitterStateTest_490, SetTagSetsHasTag_490) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Doc Management ====================

TEST_F(EmitterStateTest_490, StartedDocDoesNotBreak_490) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_490, EndedDocDoesNotBreak_490) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Management ====================

TEST_F(EmitterStateTest_490, StartedGroupSeq_490) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_490, StartedGroupMap_490) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_490, CurGroupTypeAfterStartSeq_490) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupType(), GroupType::Seq);
}

TEST_F(EmitterStateTest_490, CurGroupTypeAfterStartMap_490) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(state.CurGroupType(), GroupType::Map);
}

TEST_F(EmitterStateTest_490, CurGroupChildCountInitiallyZero_490) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupChildCount(), 0u);
}

TEST_F(EmitterStateTest_490, EndedGroupSeq_490) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_490, EndedGroupMap_490) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// ==================== Scalar ====================

TEST_F(EmitterStateTest_490, StartedScalarInGroup_490) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_490, ChildCountIncreasesAfterScalar_490) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(state.CurGroupChildCount(), 1u);
}

// ==================== ClearModifiedSettings ====================

TEST_F(EmitterStateTest_490, ClearModifiedSettingsDoesNotBreak_490) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== Global Scope Settings ====================

TEST_F(EmitterStateTest_490, SetStringFormatGlobalPersists_490) {
  state.SetStringFormat(Literal, FmtScope::Global);
  EXPECT_EQ(state.GetStringFormat(), Literal);
}

TEST_F(EmitterStateTest_490, RestoreGlobalModifiedSettingsDoesNotBreak_490) {
  state.SetStringFormat(Literal, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== Multiple invalid SetStringFormat values ====================

TEST_F(EmitterStateTest_490, SetStringFormatNewline_490) {
  EXPECT_FALSE(state.SetStringFormat(Newline, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetStringFormatTrueFalseBool_490) {
  EXPECT_FALSE(state.SetStringFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetStringFormatHex_490) {
  EXPECT_FALSE(state.SetStringFormat(Hex, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetStringFormatBeginDoc_490) {
  EXPECT_FALSE(state.SetStringFormat(BeginDoc, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetStringFormatKey_490) {
  EXPECT_FALSE(state.SetStringFormat(Key, FmtScope::Local));
}

TEST_F(EmitterStateTest_490, SetStringFormatLongKey_490) {
  EXPECT_FALSE(state.SetStringFormat(LongKey, FmtScope::Local));
}

// ==================== ForceFlow ====================

TEST_F(EmitterStateTest_490, ForceFlowDoesNotBreakState_490) {
  state.ForceFlow();
  EXPECT_TRUE(state.good());
}

// ==================== SetNonContent ====================

TEST_F(EmitterStateTest_490, SetNonContentDoesNotBreak_490) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey ====================

TEST_F(EmitterStateTest_490, SetLongKeyDoesNotBreak_490) {
  state.SetLongKey();
  EXPECT_TRUE(state.good());
}

// ==================== Nested groups ====================

TEST_F(EmitterStateTest_490, NestedGroups_490) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(state.CurGroupType(), GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(state.CurGroupType(), GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// ==================== Multiple errors ====================

TEST_F(EmitterStateTest_490, MultipleErrorsFirstWins_490) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_FALSE(state.good());
  // The first error should be preserved
  EXPECT_EQ(state.GetLastError(), "first error");
}

}  // namespace
}  // namespace YAML
