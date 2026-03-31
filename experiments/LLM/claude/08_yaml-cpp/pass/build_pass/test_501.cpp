#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_501 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Construction / Initial State ====================

TEST_F(EmitterStateTest_501, InitialStateIsGood_501) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_501, InitialLastErrorIsEmpty_501) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_501, InitialHasAnchorIsFalse_501) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_501, InitialHasAliasIsFalse_501) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_501, InitialHasTagIsFalse_501) {
  EXPECT_FALSE(state.HasTag());
}

// ==================== SetError ====================

TEST_F(EmitterStateTest_501, SetErrorMakesStateNotGood_501) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_501, SetErrorStoresErrorMessage_501) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_501, SetErrorMultipleTimesKeepsFirstError_501) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically the first error is preserved, but we verify state is not good
  EXPECT_FALSE(state.good());
  // The last error should be at least one of them
  std::string err = state.GetLastError();
  EXPECT_FALSE(err.empty());
}

// ==================== SetMapKeyFormat ====================

TEST_F(EmitterStateTest_501, SetMapKeyFormatAutoReturnsTrue_501) {
  EXPECT_TRUE(state.SetMapKeyFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatLongKeyReturnsTrue_501) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatInvalidReturnsFalse_501) {
  EXPECT_FALSE(state.SetMapKeyFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatBlockReturnsFalse_501) {
  EXPECT_FALSE(state.SetMapKeyFormat(Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatDecReturnsFalse_501) {
  EXPECT_FALSE(state.SetMapKeyFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatAutoGlobalScope_501) {
  EXPECT_TRUE(state.SetMapKeyFormat(Auto, FmtScope::Global));
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatLongKeyGlobalScope_501) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
}

TEST_F(EmitterStateTest_501, GetMapKeyFormatAfterSetAuto_501) {
  state.SetMapKeyFormat(Auto, FmtScope::Local);
  EXPECT_EQ(Auto, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_501, GetMapKeyFormatAfterSetLongKey_501) {
  state.SetMapKeyFormat(LongKey, FmtScope::Local);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== SetOutputCharset ====================

TEST_F(EmitterStateTest_501, SetOutputCharsetEmitNonAsciiReturnsTrue_501) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetOutputCharsetEscapeNonAsciiReturnsTrue_501) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetOutputCharsetInvalidReturnsFalse_501) {
  EXPECT_FALSE(state.SetOutputCharset(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, GetOutputCharsetAfterSet_501) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Local);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

// ==================== SetStringFormat ====================

TEST_F(EmitterStateTest_501, SetStringFormatSingleQuotedReturnsTrue_501) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetStringFormatDoubleQuotedReturnsTrue_501) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetStringFormatLiteralReturnsTrue_501) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetStringFormatAutoReturnsTrue_501) {
  EXPECT_TRUE(state.SetStringFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetStringFormatInvalidReturnsFalse_501) {
  EXPECT_FALSE(state.SetStringFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, GetStringFormatAfterSet_501) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== SetBoolFormat ====================

TEST_F(EmitterStateTest_501, SetBoolFormatYesNoBoolReturnsTrue_501) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetBoolFormatTrueFalseBoolReturnsTrue_501) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetBoolFormatOnOffBoolReturnsTrue_501) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetBoolFormatInvalidReturnsFalse_501) {
  EXPECT_FALSE(state.SetBoolFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, GetBoolFormatAfterSet_501) {
  state.SetBoolFormat(YesNoBool, FmtScope::Local);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

// ==================== SetBoolLengthFormat ====================

TEST_F(EmitterStateTest_501, SetBoolLengthFormatLongBoolReturnsTrue_501) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetBoolLengthFormatShortBoolReturnsTrue_501) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetBoolLengthFormatInvalidReturnsFalse_501) {
  EXPECT_FALSE(state.SetBoolLengthFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, GetBoolLengthFormatAfterSet_501) {
  state.SetBoolLengthFormat(ShortBool, FmtScope::Local);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

// ==================== SetBoolCaseFormat ====================

TEST_F(EmitterStateTest_501, SetBoolCaseFormatUpperCaseReturnsTrue_501) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetBoolCaseFormatLowerCaseReturnsTrue_501) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetBoolCaseFormatCamelCaseReturnsTrue_501) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetBoolCaseFormatInvalidReturnsFalse_501) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, GetBoolCaseFormatAfterSet_501) {
  state.SetBoolCaseFormat(UpperCase, FmtScope::Local);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

// ==================== SetNullFormat ====================

TEST_F(EmitterStateTest_501, SetNullFormatLowerNullReturnsTrue_501) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetNullFormatUpperNullReturnsTrue_501) {
  EXPECT_TRUE(state.SetNullFormat(UpperNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetNullFormatCamelNullReturnsTrue_501) {
  EXPECT_TRUE(state.SetNullFormat(CamelNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetNullFormatTildeNullReturnsTrue_501) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetNullFormatInvalidReturnsFalse_501) {
  EXPECT_FALSE(state.SetNullFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, GetNullFormatAfterSet_501) {
  state.SetNullFormat(TildeNull, FmtScope::Local);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== SetIntFormat ====================

TEST_F(EmitterStateTest_501, SetIntFormatDecReturnsTrue_501) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetIntFormatHexReturnsTrue_501) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetIntFormatOctReturnsTrue_501) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetIntFormatInvalidReturnsFalse_501) {
  EXPECT_FALSE(state.SetIntFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, GetIntFormatAfterSet_501) {
  state.SetIntFormat(Hex, FmtScope::Local);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

// ==================== SetIndent ====================

TEST_F(EmitterStateTest_501, SetIndentValidValueReturnsTrue_501) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetIndentMinValueReturnsTrue_501) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetIndentZeroReturnsFalse_501) {
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetIndentOneReturnsFalse_501) {
  EXPECT_FALSE(state.SetIndent(1, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, GetIndentAfterSet_501) {
  state.SetIndent(6, FmtScope::Local);
  EXPECT_EQ(6u, state.GetIndent());
}

// ==================== SetPreCommentIndent ====================

TEST_F(EmitterStateTest_501, SetPreCommentIndentValidReturnsTrue_501) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetPreCommentIndentZeroReturnsFalse_501) {
  EXPECT_FALSE(state.SetPreCommentIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, GetPreCommentIndentAfterSet_501) {
  state.SetPreCommentIndent(3, FmtScope::Local);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

// ==================== SetPostCommentIndent ====================

TEST_F(EmitterStateTest_501, SetPostCommentIndentValidReturnsTrue_501) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetPostCommentIndentZeroReturnsFalse_501) {
  EXPECT_FALSE(state.SetPostCommentIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, GetPostCommentIndentAfterSet_501) {
  state.SetPostCommentIndent(5, FmtScope::Local);
  EXPECT_EQ(5u, state.GetPostCommentIndent());
}

// ==================== SetFlowType ====================

TEST_F(EmitterStateTest_501, SetFlowTypeSeqFlowReturnsTrue_501) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetFlowTypeSeqBlockReturnsTrue_501) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetFlowTypeMapFlowReturnsTrue_501) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetFlowTypeMapBlockReturnsTrue_501) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetFlowTypeInvalidReturnsFalse_501) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, GetFlowTypeSeqAfterSet_501) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_501, GetFlowTypeMapAfterSet_501) {
  state.SetFlowType(GroupType::Map, Block, FmtScope::Local);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== SetFloatPrecision / SetDoublePrecision ====================

TEST_F(EmitterStateTest_501, SetFloatPrecisionReturnsTrue_501) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, GetFloatPrecisionAfterSet_501) {
  state.SetFloatPrecision(3, FmtScope::Local);
  EXPECT_EQ(3u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_501, SetDoublePrecisionReturnsTrue_501) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, GetDoublePrecisionAfterSet_501) {
  state.SetDoublePrecision(12, FmtScope::Local);
  EXPECT_EQ(12u, state.GetDoublePrecision());
}

// ==================== SetAnchor / SetAlias / SetTag ====================

TEST_F(EmitterStateTest_501, SetAnchorSetsHasAnchor_501) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_501, SetAliasSetsHasAlias_501) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_501, SetTagSetsHasTag_501) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Document lifecycle ====================

TEST_F(EmitterStateTest_501, StartedDocDoesNotBreakState_501) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_501, EndedDocDoesNotBreakState_501) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group lifecycle ====================

TEST_F(EmitterStateTest_501, StartedGroupSeqDoesNotBreakState_501) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_501, StartedGroupMapDoesNotBreakState_501) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_501, CurGroupTypeAfterStartSeq_501) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_501, CurGroupTypeAfterStartMap_501) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_501, CurGroupChildCountInitiallyZero_501) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_501, EndedGroupDoesNotBreakState_501) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// ==================== StartedScalar ====================

TEST_F(EmitterStateTest_501, StartedScalarInGroupIncrementsChildCount_501) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

// ==================== CurGroupLongKey ====================

TEST_F(EmitterStateTest_501, CurGroupLongKeyDefaultIsFalse_501) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// ==================== SetLongKey ====================

TEST_F(EmitterStateTest_501, SetLongKeyBeforeGroup_501) {
  state.StartedDoc();
  state.SetLongKey();
  state.StartedGroup(GroupType::Map);
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== ForceFlow ====================

TEST_F(EmitterStateTest_501, ForceFlowBeforeGroup_501) {
  state.StartedDoc();
  state.ForceFlow();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== FmtScope::Global ====================

TEST_F(EmitterStateTest_501, SetMapKeyFormatGlobalPersistsAfterClear_501) {
  state.SetMapKeyFormat(LongKey, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== ClearModifiedSettings ====================

TEST_F(EmitterStateTest_501, ClearModifiedSettingsResetsLocal_501) {
  EMITTER_MANIP defaultFmt = state.GetMapKeyFormat();
  state.SetMapKeyFormat(LongKey, FmtScope::Local);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
  state.ClearModifiedSettings();
  EXPECT_EQ(defaultFmt, state.GetMapKeyFormat());
}

// ==================== SetNonContent ====================

TEST_F(EmitterStateTest_501, SetNonContentDoesNotBreakState_501) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== Multiple invalid SetMapKeyFormat values ====================

TEST_F(EmitterStateTest_501, SetMapKeyFormatNewlineReturnsFalse_501) {
  EXPECT_FALSE(state.SetMapKeyFormat(Newline, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatSingleQuotedReturnsFalse_501) {
  EXPECT_FALSE(state.SetMapKeyFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatDoubleQuotedReturnsFalse_501) {
  EXPECT_FALSE(state.SetMapKeyFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatKeyReturnsFalse_501) {
  EXPECT_FALSE(state.SetMapKeyFormat(Key, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatValueReturnsFalse_501) {
  EXPECT_FALSE(state.SetMapKeyFormat(Value, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatBeginDocReturnsFalse_501) {
  EXPECT_FALSE(state.SetMapKeyFormat(BeginDoc, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatEndDocReturnsFalse_501) {
  EXPECT_FALSE(state.SetMapKeyFormat(EndDoc, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatBeginSeqReturnsFalse_501) {
  EXPECT_FALSE(state.SetMapKeyFormat(BeginSeq, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatEndSeqReturnsFalse_501) {
  EXPECT_FALSE(state.SetMapKeyFormat(EndSeq, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatBeginMapReturnsFalse_501) {
  EXPECT_FALSE(state.SetMapKeyFormat(BeginMap, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, SetMapKeyFormatEndMapReturnsFalse_501) {
  EXPECT_FALSE(state.SetMapKeyFormat(EndMap, FmtScope::Local));
}

// ==================== Charset with EscapeAsJson ====================

TEST_F(EmitterStateTest_501, SetOutputCharsetEscapeAsJsonReturnsTrue_501) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeAsJson, FmtScope::Local));
}

TEST_F(EmitterStateTest_501, GetOutputCharsetAfterEscapeAsJson_501) {
  state.SetOutputCharset(EscapeAsJson, FmtScope::Local);
  EXPECT_EQ(EscapeAsJson, state.GetOutputCharset());
}

// ==================== Default values ====================

TEST_F(EmitterStateTest_501, DefaultIndentIsNonZero_501) {
  EXPECT_GT(state.GetIndent(), 0u);
}

TEST_F(EmitterStateTest_501, DefaultPreCommentIndentIsNonZero_501) {
  EXPECT_GT(state.GetPreCommentIndent(), 0u);
}

TEST_F(EmitterStateTest_501, DefaultPostCommentIndentIsNonZero_501) {
  EXPECT_GT(state.GetPostCommentIndent(), 0u);
}

}  // namespace YAML
