#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {
namespace {

class EmitterStateTest_495 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Construction / Initial State ====================

TEST_F(EmitterStateTest_495, InitialStateIsGood_495) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_495, InitialLastErrorIsEmpty_495) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_495, InitialHasAnchorIsFalse_495) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_495, InitialHasAliasIsFalse_495) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_495, InitialHasTagIsFalse_495) {
  EXPECT_FALSE(state.HasTag());
}

// ==================== SetError / good / GetLastError ====================

TEST_F(EmitterStateTest_495, SetErrorMakesStateNotGood_495) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_495, SetErrorStoresMessage_495) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_495, MultipleSetErrorKeepsFirstError_495) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically first error is kept since state is no longer good
  EXPECT_FALSE(state.good());
  // The first error should be preserved
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== SetIntFormat ====================

TEST_F(EmitterStateTest_495, SetIntFormatDecReturnsTrue_495) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetIntFormatHexReturnsTrue_495) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetIntFormatOctReturnsTrue_495) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetIntFormatInvalidReturnsFalse_495) {
  EXPECT_FALSE(state.SetIntFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetIntFormatFlowReturnsFalse_495) {
  EXPECT_FALSE(state.SetIntFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetIntFormatBlockReturnsFalse_495) {
  EXPECT_FALSE(state.SetIntFormat(Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetIntFormatTrueFalseBoolReturnsFalse_495) {
  EXPECT_FALSE(state.SetIntFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetIntFormatDecGlobalScope_495) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
}

TEST_F(EmitterStateTest_495, SetIntFormatHexGlobalScope_495) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
}

TEST_F(EmitterStateTest_495, SetIntFormatOctGlobalScope_495) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
}

TEST_F(EmitterStateTest_495, GetIntFormatAfterSetDec_495) {
  state.SetIntFormat(Dec, FmtScope::Global);
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_495, GetIntFormatAfterSetHex_495) {
  state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_495, GetIntFormatAfterSetOct_495) {
  state.SetIntFormat(Oct, FmtScope::Global);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

// ==================== SetOutputCharset ====================

TEST_F(EmitterStateTest_495, SetOutputCharsetEmitNonAsciiReturnsTrue_495) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetOutputCharsetEscapeNonAsciiReturnsTrue_495) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetOutputCharsetInvalidReturnsFalse_495) {
  EXPECT_FALSE(state.SetOutputCharset(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, GetOutputCharsetAfterSet_495) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Global);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

// ==================== SetStringFormat ====================

TEST_F(EmitterStateTest_495, SetStringFormatSingleQuotedReturnsTrue_495) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetStringFormatDoubleQuotedReturnsTrue_495) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetStringFormatLiteralReturnsTrue_495) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetStringFormatInvalidReturnsFalse_495) {
  EXPECT_FALSE(state.SetStringFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, GetStringFormatAfterSet_495) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== SetBoolFormat ====================

TEST_F(EmitterStateTest_495, SetBoolFormatYesNoBoolReturnsTrue_495) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetBoolFormatTrueFalseBoolReturnsTrue_495) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetBoolFormatOnOffBoolReturnsTrue_495) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetBoolFormatInvalidReturnsFalse_495) {
  EXPECT_FALSE(state.SetBoolFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, GetBoolFormatAfterSet_495) {
  state.SetBoolFormat(YesNoBool, FmtScope::Global);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

// ==================== SetBoolLengthFormat ====================

TEST_F(EmitterStateTest_495, SetBoolLengthFormatLongBoolReturnsTrue_495) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetBoolLengthFormatShortBoolReturnsTrue_495) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetBoolLengthFormatInvalidReturnsFalse_495) {
  EXPECT_FALSE(state.SetBoolLengthFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, GetBoolLengthFormatAfterSet_495) {
  state.SetBoolLengthFormat(ShortBool, FmtScope::Global);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

// ==================== SetBoolCaseFormat ====================

TEST_F(EmitterStateTest_495, SetBoolCaseFormatUpperCaseReturnsTrue_495) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetBoolCaseFormatLowerCaseReturnsTrue_495) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetBoolCaseFormatCamelCaseReturnsTrue_495) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetBoolCaseFormatInvalidReturnsFalse_495) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, GetBoolCaseFormatAfterSet_495) {
  state.SetBoolCaseFormat(UpperCase, FmtScope::Global);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

// ==================== SetNullFormat ====================

TEST_F(EmitterStateTest_495, SetNullFormatLowerNullReturnsTrue_495) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetNullFormatUpperNullReturnsTrue_495) {
  EXPECT_TRUE(state.SetNullFormat(UpperNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetNullFormatCamelNullReturnsTrue_495) {
  EXPECT_TRUE(state.SetNullFormat(CamelNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetNullFormatTildeNullReturnsTrue_495) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetNullFormatInvalidReturnsFalse_495) {
  EXPECT_FALSE(state.SetNullFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, GetNullFormatAfterSet_495) {
  state.SetNullFormat(TildeNull, FmtScope::Global);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== SetIndent ====================

TEST_F(EmitterStateTest_495, SetIndentValidValueReturnsTrue_495) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
}

TEST_F(EmitterStateTest_495, GetIndentAfterSet_495) {
  state.SetIndent(4, FmtScope::Global);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_495, SetIndentZeroReturnsFalse_495) {
  // Indent of 0 is likely invalid
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Global));
}

// ==================== SetPreCommentIndent ====================

TEST_F(EmitterStateTest_495, SetPreCommentIndentReturnsTrue_495) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Global));
}

TEST_F(EmitterStateTest_495, GetPreCommentIndentAfterSet_495) {
  state.SetPreCommentIndent(3, FmtScope::Global);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

// ==================== SetPostCommentIndent ====================

TEST_F(EmitterStateTest_495, SetPostCommentIndentReturnsTrue_495) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
}

TEST_F(EmitterStateTest_495, GetPostCommentIndentAfterSet_495) {
  state.SetPostCommentIndent(5, FmtScope::Global);
  EXPECT_EQ(5u, state.GetPostCommentIndent());
}

// ==================== SetFlowType ====================

TEST_F(EmitterStateTest_495, SetFlowTypeSeqFlowReturnsTrue_495) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetFlowTypeSeqBlockReturnsTrue_495) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetFlowTypeMapFlowReturnsTrue_495) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetFlowTypeMapBlockReturnsTrue_495) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetFlowTypeInvalidReturnsFalse_495) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, GetFlowTypeAfterSetSeq_495) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_495, GetFlowTypeAfterSetMap_495) {
  state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== SetMapKeyFormat ====================

TEST_F(EmitterStateTest_495, SetMapKeyFormatLongKeyReturnsTrue_495) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetMapKeyFormatAutoReturnsTrue_495) {
  EXPECT_TRUE(state.SetMapKeyFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetMapKeyFormatInvalidReturnsFalse_495) {
  EXPECT_FALSE(state.SetMapKeyFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, GetMapKeyFormatAfterSet_495) {
  state.SetMapKeyFormat(LongKey, FmtScope::Global);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== SetFloatPrecision ====================

TEST_F(EmitterStateTest_495, SetFloatPrecisionReturnsTrue_495) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Global));
}

TEST_F(EmitterStateTest_495, GetFloatPrecisionAfterSet_495) {
  state.SetFloatPrecision(3, FmtScope::Global);
  EXPECT_EQ(3u, state.GetFloatPrecision());
}

// ==================== SetDoublePrecision ====================

TEST_F(EmitterStateTest_495, SetDoublePrecisionReturnsTrue_495) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Global));
}

TEST_F(EmitterStateTest_495, GetDoublePrecisionAfterSet_495) {
  state.SetDoublePrecision(15, FmtScope::Global);
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

// ==================== SetAnchor / HasAnchor ====================

TEST_F(EmitterStateTest_495, SetAnchorMakesHasAnchorTrue_495) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

// ==================== SetAlias / HasAlias ====================

TEST_F(EmitterStateTest_495, SetAliasMakesHasAliasTrue_495) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

// ==================== SetTag / HasTag ====================

TEST_F(EmitterStateTest_495, SetTagMakesHasTagTrue_495) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== StartedDoc / EndedDoc ====================

TEST_F(EmitterStateTest_495, StartedDocDoesNotBreakState_495) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_495, EndedDocDoesNotBreakState_495) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group operations ====================

TEST_F(EmitterStateTest_495, StartedGroupSeqAndEndedGroup_495) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_495, StartedGroupMapAndEndedGroup_495) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_495, CurGroupChildCountInitiallyZero_495) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_495, CurGroupChildCountAfterScalar_495) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_495, CurGroupLongKeyDefaultFalse_495) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== ForceFlow ====================

TEST_F(EmitterStateTest_495, ForceFlowChangesFlowType_495) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Seq);
}

// ==================== SetLongKey ====================

TEST_F(EmitterStateTest_495, SetLongKeyMakesCurGroupLongKeyTrue_495) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== Scope tests for SetIntFormat ====================

TEST_F(EmitterStateTest_495, SetIntFormatLocalScope_495) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_495, SetIntFormatGlobalScope_495) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

// ==================== ClearModifiedSettings ====================

TEST_F(EmitterStateTest_495, ClearModifiedSettingsResetsLocalSettings_495) {
  state.SetIntFormat(Hex, FmtScope::Local);
  state.ClearModifiedSettings();
  // After clearing, should revert to default (Dec)
  EXPECT_EQ(Dec, state.GetIntFormat());
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterStateTest_495, RestoreGlobalModifiedSettingsRestoresGlobal_495) {
  state.SetIntFormat(Oct, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(Oct, state.GetIntFormat());
}

// ==================== All invalid EMITTER_MANIP values for SetIntFormat ====================

TEST_F(EmitterStateTest_495, SetIntFormatNewlineReturnsFalse_495) {
  EXPECT_FALSE(state.SetIntFormat(Newline, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetIntFormatSingleQuotedReturnsFalse_495) {
  EXPECT_FALSE(state.SetIntFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetIntFormatDoubleQuotedReturnsFalse_495) {
  EXPECT_FALSE(state.SetIntFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetIntFormatLiteralReturnsFalse_495) {
  EXPECT_FALSE(state.SetIntFormat(Literal, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetIntFormatLongKeyReturnsFalse_495) {
  EXPECT_FALSE(state.SetIntFormat(LongKey, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetIntFormatBeginDocReturnsFalse_495) {
  EXPECT_FALSE(state.SetIntFormat(BeginDoc, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetIntFormatKeyReturnsFalse_495) {
  EXPECT_FALSE(state.SetIntFormat(Key, FmtScope::Local));
}

TEST_F(EmitterStateTest_495, SetIntFormatValueReturnsFalse_495) {
  EXPECT_FALSE(state.SetIntFormat(Value, FmtScope::Local));
}

// ==================== Default GetIntFormat ====================

TEST_F(EmitterStateTest_495, DefaultIntFormatIsDec_495) {
  EXPECT_EQ(Dec, state.GetIntFormat());
}

// ==================== Multiple format overrides ====================

TEST_F(EmitterStateTest_495, SetIntFormatOverridesPrevious_495) {
  state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_EQ(Hex, state.GetIntFormat());
  state.SetIntFormat(Oct, FmtScope::Global);
  EXPECT_EQ(Oct, state.GetIntFormat());
  state.SetIntFormat(Dec, FmtScope::Global);
  EXPECT_EQ(Dec, state.GetIntFormat());
}

// ==================== SetNonContent ====================

TEST_F(EmitterStateTest_495, SetNonContentDoesNotBreakState_495) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== HasBegunNode / HasBegunContent ====================

TEST_F(EmitterStateTest_495, HasBegunNodeInitiallyFalse_495) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_495, HasBegunContentInitiallyFalse_495) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== CurIndent ====================

TEST_F(EmitterStateTest_495, CurIndentInitialValue_495) {
  EXPECT_EQ(0u, state.CurIndent());
}

}  // namespace
}  // namespace YAML
