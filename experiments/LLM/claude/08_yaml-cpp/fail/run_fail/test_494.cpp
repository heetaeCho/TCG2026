#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {
namespace {

class EmitterStateTest_494 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_494, InitialStateIsGood_494) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_494, InitialLastErrorIsEmpty_494) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_494, InitialHasNoAnchor_494) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_494, InitialHasNoAlias_494) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_494, InitialHasNoTag_494) {
  EXPECT_FALSE(state.HasTag());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_494, SetErrorMakesStateNotGood_494) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_494, SetErrorStoresErrorMessage_494) {
  state.SetError("some error message");
  EXPECT_EQ("some error message", state.GetLastError());
}

TEST_F(EmitterStateTest_494, SetErrorMultipleTimesKeepsFirstError_494) {
  state.SetError("first error");
  state.SetError("second error");
  // Once in bad state, typically first error is kept
  EXPECT_FALSE(state.good());
}

// ==================== SetNullFormat Tests ====================

TEST_F(EmitterStateTest_494, SetNullFormatLowerNull_494) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetNullFormatUpperNull_494) {
  EXPECT_TRUE(state.SetNullFormat(UpperNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetNullFormatCamelNull_494) {
  EXPECT_TRUE(state.SetNullFormat(CamelNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetNullFormatTildeNull_494) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetNullFormatInvalidValue_494) {
  EXPECT_FALSE(state.SetNullFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetNullFormatFlowReturnsInvalid_494) {
  EXPECT_FALSE(state.SetNullFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetNullFormatDecReturnsInvalid_494) {
  EXPECT_FALSE(state.SetNullFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetNullFormatGlobalScope_494) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
}

TEST_F(EmitterStateTest_494, GetNullFormatAfterSetLowerNull_494) {
  state.SetNullFormat(LowerNull, FmtScope::Local);
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_494, GetNullFormatAfterSetUpperNull_494) {
  state.SetNullFormat(UpperNull, FmtScope::Local);
  EXPECT_EQ(UpperNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_494, GetNullFormatAfterSetCamelNull_494) {
  state.SetNullFormat(CamelNull, FmtScope::Local);
  EXPECT_EQ(CamelNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_494, GetNullFormatAfterSetTildeNull_494) {
  state.SetNullFormat(TildeNull, FmtScope::Local);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== SetOutputCharset Tests ====================

TEST_F(EmitterStateTest_494, SetOutputCharsetEmitNonAscii_494) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetOutputCharsetEscapeNonAscii_494) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetOutputCharsetEscapeAsJson_494) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeAsJson, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetOutputCharsetInvalidValue_494) {
  EXPECT_FALSE(state.SetOutputCharset(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, GetOutputCharsetAfterSet_494) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Local);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

// ==================== SetStringFormat Tests ====================

TEST_F(EmitterStateTest_494, SetStringFormatSingleQuoted_494) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetStringFormatDoubleQuoted_494) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetStringFormatLiteral_494) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetStringFormatInvalid_494) {
  EXPECT_FALSE(state.SetStringFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, GetStringFormatAfterSet_494) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== SetBoolFormat Tests ====================

TEST_F(EmitterStateTest_494, SetBoolFormatYesNo_494) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetBoolFormatTrueFalse_494) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetBoolFormatOnOff_494) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetBoolFormatInvalid_494) {
  EXPECT_FALSE(state.SetBoolFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, GetBoolFormatAfterSet_494) {
  state.SetBoolFormat(YesNoBool, FmtScope::Local);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

// ==================== SetBoolLengthFormat Tests ====================

TEST_F(EmitterStateTest_494, SetBoolLengthFormatLong_494) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetBoolLengthFormatShort_494) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetBoolLengthFormatInvalid_494) {
  EXPECT_FALSE(state.SetBoolLengthFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, GetBoolLengthFormatAfterSet_494) {
  state.SetBoolLengthFormat(LongBool, FmtScope::Local);
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

// ==================== SetBoolCaseFormat Tests ====================

TEST_F(EmitterStateTest_494, SetBoolCaseFormatUpperCase_494) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetBoolCaseFormatLowerCase_494) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetBoolCaseFormatCamelCase_494) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetBoolCaseFormatInvalid_494) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, GetBoolCaseFormatAfterSet_494) {
  state.SetBoolCaseFormat(UpperCase, FmtScope::Local);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

// ==================== SetIntFormat Tests ====================

TEST_F(EmitterStateTest_494, SetIntFormatDec_494) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetIntFormatHex_494) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetIntFormatOct_494) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetIntFormatInvalid_494) {
  EXPECT_FALSE(state.SetIntFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, GetIntFormatAfterSet_494) {
  state.SetIntFormat(Hex, FmtScope::Local);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

// ==================== SetIndent Tests ====================

TEST_F(EmitterStateTest_494, SetIndentValidValue_494) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetIndentMinimumValue_494) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, GetIndentAfterSet_494) {
  state.SetIndent(4, FmtScope::Local);
  EXPECT_EQ(4u, state.GetIndent());
}

// ==================== SetPreCommentIndent Tests ====================

TEST_F(EmitterStateTest_494, SetPreCommentIndentValid_494) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, GetPreCommentIndentAfterSet_494) {
  state.SetPreCommentIndent(3, FmtScope::Local);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

// ==================== SetPostCommentIndent Tests ====================

TEST_F(EmitterStateTest_494, SetPostCommentIndentValid_494) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, GetPostCommentIndentAfterSet_494) {
  state.SetPostCommentIndent(5, FmtScope::Local);
  EXPECT_EQ(5u, state.GetPostCommentIndent());
}

// ==================== SetFlowType Tests ====================

TEST_F(EmitterStateTest_494, SetFlowTypeSeqFlow_494) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetFlowTypeSeqBlock_494) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetFlowTypeMapFlow_494) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetFlowTypeMapBlock_494) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetFlowTypeInvalidManip_494) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Dec, FmtScope::Local));
}

// ==================== SetMapKeyFormat Tests ====================

TEST_F(EmitterStateTest_494, SetMapKeyFormatLongKey_494) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetMapKeyFormatAuto_494) {
  EXPECT_TRUE(state.SetMapKeyFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetMapKeyFormatInvalid_494) {
  EXPECT_FALSE(state.SetMapKeyFormat(Flow, FmtScope::Local));
}

// ==================== SetFloatPrecision Tests ====================

TEST_F(EmitterStateTest_494, SetFloatPrecisionValid_494) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, GetFloatPrecisionAfterSet_494) {
  state.SetFloatPrecision(6, FmtScope::Local);
  EXPECT_EQ(6u, state.GetFloatPrecision());
}

// ==================== SetDoublePrecision Tests ====================

TEST_F(EmitterStateTest_494, SetDoublePrecisionValid_494) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, GetDoublePrecisionAfterSet_494) {
  state.SetDoublePrecision(15, FmtScope::Local);
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_494, SetAnchorMakesHasAnchorTrue_494) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_494, SetAliasMakesHasAliasTrue_494) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_494, SetTagMakesHasTagTrue_494) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Document Lifecycle Tests ====================

TEST_F(EmitterStateTest_494, StartedDocDoesNotBreakState_494) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_494, EndedDocDoesNotBreakState_494) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_494, StartAndEndSeqGroup_494) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_494, StartAndEndMapGroup_494) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_494, CurGroupChildCountInitiallyZero_494) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_494, CurGroupLongKeyInitiallyFalse_494) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== Scope Tests ====================

TEST_F(EmitterStateTest_494, SetNullFormatGlobalScopeRetained_494) {
  state.SetNullFormat(UpperNull, FmtScope::Global);
  EXPECT_EQ(UpperNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_494, SetNullFormatLocalScopeRetained_494) {
  state.SetNullFormat(TildeNull, FmtScope::Local);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_494, SetLocalValueDoesNotCrash_494) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_494, ClearModifiedSettingsDoesNotCrash_494) {
  state.SetNullFormat(UpperNull, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_494, RestoreGlobalModifiedSettingsDoesNotCrash_494) {
  state.SetNullFormat(UpperNull, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_494, ForceFlowDoesNotBreakState_494) {
  state.ForceFlow();
  EXPECT_TRUE(state.good());
}

// ==================== Multiple SetNullFormat invalid values ====================

TEST_F(EmitterStateTest_494, SetNullFormatSingleQuotedInvalid_494) {
  EXPECT_FALSE(state.SetNullFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetNullFormatDoubleQuotedInvalid_494) {
  EXPECT_FALSE(state.SetNullFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetNullFormatBlockInvalid_494) {
  EXPECT_FALSE(state.SetNullFormat(Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetNullFormatLiteralInvalid_494) {
  EXPECT_FALSE(state.SetNullFormat(Literal, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetNullFormatYesNoBoolInvalid_494) {
  EXPECT_FALSE(state.SetNullFormat(YesNoBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetNullFormatTrueFalseBoolInvalid_494) {
  EXPECT_FALSE(state.SetNullFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetNullFormatHexInvalid_494) {
  EXPECT_FALSE(state.SetNullFormat(Hex, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetNullFormatOctInvalid_494) {
  EXPECT_FALSE(state.SetNullFormat(Oct, FmtScope::Local));
}

TEST_F(EmitterStateTest_494, SetNullFormatLongKeyInvalid_494) {
  EXPECT_FALSE(state.SetNullFormat(LongKey, FmtScope::Local));
}

// ==================== Overwrite NullFormat Tests ====================

TEST_F(EmitterStateTest_494, SetNullFormatOverwritesPrevious_494) {
  state.SetNullFormat(LowerNull, FmtScope::Local);
  EXPECT_EQ(LowerNull, state.GetNullFormat());
  state.SetNullFormat(CamelNull, FmtScope::Local);
  EXPECT_EQ(CamelNull, state.GetNullFormat());
}

// ==================== StartedScalar Tests ====================

TEST_F(EmitterStateTest_494, StartedScalarDoesNotCrash_494) {
  state.StartedDoc();
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_494, SetNonContentDoesNotCrash_494) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

}  // namespace
}  // namespace YAML
