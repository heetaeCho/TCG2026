#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {
namespace {

class EmitterStateTest_489 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_489, InitialStateIsGood_489) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_489, InitialLastErrorIsEmpty_489) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_489, InitialHasNoAnchor_489) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_489, InitialHasNoAlias_489) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_489, InitialHasNoTag_489) {
  EXPECT_FALSE(state.HasTag());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_489, SetErrorMakesStateNotGood_489) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_489, SetErrorStoresErrorMessage_489) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_489, SetErrorMultipleTimes_489) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically first error is preserved
  EXPECT_FALSE(state.good());
}

// ==================== SetOutputCharset Tests ====================

TEST_F(EmitterStateTest_489, SetOutputCharsetEmitNonAsciiReturnsTrue_489) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetOutputCharsetEscapeNonAsciiReturnsTrue_489) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetOutputCharsetEscapeAsJsonReturnsTrue_489) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeAsJson, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetOutputCharsetInvalidValueReturnsFalse_489) {
  EXPECT_FALSE(state.SetOutputCharset(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetOutputCharsetFlowReturnsFalse_489) {
  EXPECT_FALSE(state.SetOutputCharset(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetOutputCharsetBlockReturnsFalse_489) {
  EXPECT_FALSE(state.SetOutputCharset(Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetOutputCharsetWithGlobalScope_489) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_489, GetOutputCharsetAfterSet_489) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Local);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_489, GetOutputCharsetAfterSetEscapeAsJson_489) {
  state.SetOutputCharset(EscapeAsJson, FmtScope::Local);
  EXPECT_EQ(EscapeAsJson, state.GetOutputCharset());
}

// ==================== SetStringFormat Tests ====================

TEST_F(EmitterStateTest_489, SetStringFormatSingleQuotedReturnsTrue_489) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetStringFormatDoubleQuotedReturnsTrue_489) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetStringFormatLiteralReturnsTrue_489) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetStringFormatAutoReturnsTrue_489) {
  EXPECT_TRUE(state.SetStringFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetStringFormatInvalidReturnsFalse_489) {
  EXPECT_FALSE(state.SetStringFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, GetStringFormatAfterSet_489) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== SetBoolFormat Tests ====================

TEST_F(EmitterStateTest_489, SetBoolFormatYesNoReturnsTrue_489) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetBoolFormatTrueFalseReturnsTrue_489) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetBoolFormatOnOffReturnsTrue_489) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetBoolFormatInvalidReturnsFalse_489) {
  EXPECT_FALSE(state.SetBoolFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, GetBoolFormatAfterSet_489) {
  state.SetBoolFormat(OnOffBool, FmtScope::Local);
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

// ==================== SetBoolLengthFormat Tests ====================

TEST_F(EmitterStateTest_489, SetBoolLengthFormatLongReturnsTrue_489) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetBoolLengthFormatShortReturnsTrue_489) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetBoolLengthFormatInvalidReturnsFalse_489) {
  EXPECT_FALSE(state.SetBoolLengthFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, GetBoolLengthFormatAfterSet_489) {
  state.SetBoolLengthFormat(ShortBool, FmtScope::Local);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

// ==================== SetBoolCaseFormat Tests ====================

TEST_F(EmitterStateTest_489, SetBoolCaseFormatUpperCaseReturnsTrue_489) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetBoolCaseFormatLowerCaseReturnsTrue_489) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetBoolCaseFormatCamelCaseReturnsTrue_489) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetBoolCaseFormatInvalidReturnsFalse_489) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, GetBoolCaseFormatAfterSet_489) {
  state.SetBoolCaseFormat(UpperCase, FmtScope::Local);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

// ==================== SetNullFormat Tests ====================

TEST_F(EmitterStateTest_489, SetNullFormatLowerNullReturnsTrue_489) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetNullFormatUpperNullReturnsTrue_489) {
  EXPECT_TRUE(state.SetNullFormat(UpperNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetNullFormatCamelNullReturnsTrue_489) {
  EXPECT_TRUE(state.SetNullFormat(CamelNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetNullFormatTildeNullReturnsTrue_489) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetNullFormatInvalidReturnsFalse_489) {
  EXPECT_FALSE(state.SetNullFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, GetNullFormatAfterSet_489) {
  state.SetNullFormat(TildeNull, FmtScope::Local);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== SetIntFormat Tests ====================

TEST_F(EmitterStateTest_489, SetIntFormatDecReturnsTrue_489) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetIntFormatHexReturnsTrue_489) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetIntFormatOctReturnsTrue_489) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetIntFormatInvalidReturnsFalse_489) {
  EXPECT_FALSE(state.SetIntFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, GetIntFormatAfterSet_489) {
  state.SetIntFormat(Hex, FmtScope::Local);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

// ==================== SetIndent Tests ====================

TEST_F(EmitterStateTest_489, SetIndentValidValueReturnsTrue_489) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetIndentMinimumValueOf2_489) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetIndentZeroReturnsFalse_489) {
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetIndentOneReturnsFalse_489) {
  EXPECT_FALSE(state.SetIndent(1, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, GetIndentAfterSet_489) {
  state.SetIndent(6, FmtScope::Local);
  EXPECT_EQ(6u, state.GetIndent());
}

// ==================== SetPreCommentIndent Tests ====================

TEST_F(EmitterStateTest_489, SetPreCommentIndentValidValue_489) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetPreCommentIndentZeroReturnsFalse_489) {
  EXPECT_FALSE(state.SetPreCommentIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, GetPreCommentIndentAfterSet_489) {
  state.SetPreCommentIndent(3, FmtScope::Local);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

// ==================== SetPostCommentIndent Tests ====================

TEST_F(EmitterStateTest_489, SetPostCommentIndentValidValue_489) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetPostCommentIndentZeroReturnsFalse_489) {
  EXPECT_FALSE(state.SetPostCommentIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, GetPostCommentIndentAfterSet_489) {
  state.SetPostCommentIndent(4, FmtScope::Local);
  EXPECT_EQ(4u, state.GetPostCommentIndent());
}

// ==================== SetFlowType Tests ====================

TEST_F(EmitterStateTest_489, SetFlowTypeSeqFlowReturnsTrue_489) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetFlowTypeSeqBlockReturnsTrue_489) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetFlowTypeMapFlowReturnsTrue_489) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetFlowTypeMapBlockReturnsTrue_489) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetFlowTypeInvalidReturnsFalse_489) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Dec, FmtScope::Local));
}

// ==================== SetMapKeyFormat Tests ====================

TEST_F(EmitterStateTest_489, SetMapKeyFormatLongKeyReturnsTrue_489) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetMapKeyFormatAutoReturnsTrue_489) {
  EXPECT_TRUE(state.SetMapKeyFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetMapKeyFormatInvalidReturnsFalse_489) {
  EXPECT_FALSE(state.SetMapKeyFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, GetMapKeyFormatAfterSet_489) {
  state.SetMapKeyFormat(LongKey, FmtScope::Local);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== SetFloatPrecision Tests ====================

TEST_F(EmitterStateTest_489, SetFloatPrecisionValidValue_489) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, GetFloatPrecisionAfterSet_489) {
  state.SetFloatPrecision(3, FmtScope::Local);
  EXPECT_EQ(3u, state.GetFloatPrecision());
}

// ==================== SetDoublePrecision Tests ====================

TEST_F(EmitterStateTest_489, SetDoublePrecisionValidValue_489) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, GetDoublePrecisionAfterSet_489) {
  state.SetDoublePrecision(10, FmtScope::Local);
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== Anchor / Alias / Tag Tests ====================

TEST_F(EmitterStateTest_489, SetAnchorSetsHasAnchor_489) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_489, SetAliasSetsHasAlias_489) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_489, SetTagSetsHasTag_489) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Doc Lifecycle Tests ====================

TEST_F(EmitterStateTest_489, StartedDocDoesNotBreak_489) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_489, EndedDocDoesNotBreak_489) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Lifecycle Tests ====================

TEST_F(EmitterStateTest_489, StartedGroupSeq_489) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_489, StartedGroupMap_489) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_489, CurGroupChildCountInitiallyZero_489) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_489, EndedGroupAfterStartedGroup_489) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// ==================== Scope Tests (Global vs Local) ====================

TEST_F(EmitterStateTest_489, SetOutputCharsetGlobalScope_489) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Global));
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_489, SetOutputCharsetLocalScope_489) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeAsJson, FmtScope::Local));
  EXPECT_EQ(EscapeAsJson, state.GetOutputCharset());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_489, ForceFlowDoesNotBreakState_489) {
  state.ForceFlow();
  EXPECT_TRUE(state.good());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_489, SetNonContentDoesNotBreak_489) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_489, SetLongKeyDoesNotBreak_489) {
  state.SetLongKey();
  EXPECT_TRUE(state.good());
}

// ==================== CurIndent Tests ====================

TEST_F(EmitterStateTest_489, InitialCurIndentIsZero_489) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== Multiple Invalid EMITTER_MANIP for SetOutputCharset ====================

TEST_F(EmitterStateTest_489, SetOutputCharsetDecReturnsFalse_489) {
  EXPECT_FALSE(state.SetOutputCharset(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetOutputCharsetHexReturnsFalse_489) {
  EXPECT_FALSE(state.SetOutputCharset(Hex, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetOutputCharsetSingleQuotedReturnsFalse_489) {
  EXPECT_FALSE(state.SetOutputCharset(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetOutputCharsetLongKeyReturnsFalse_489) {
  EXPECT_FALSE(state.SetOutputCharset(LongKey, FmtScope::Local));
}

TEST_F(EmitterStateTest_489, SetOutputCharsetNewlineReturnsFalse_489) {
  EXPECT_FALSE(state.SetOutputCharset(Newline, FmtScope::Local));
}

// ==================== Default Getter Values ====================

TEST_F(EmitterStateTest_489, DefaultOutputCharsetIsEmitNonAscii_489) {
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

// ==================== HasBegunNode / HasBegunContent ====================

TEST_F(EmitterStateTest_489, InitialHasNotBegunNode_489) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_489, InitialHasNotBegunContent_489) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== StartedScalar Tests ====================

TEST_F(EmitterStateTest_489, StartedScalarInGroupIncrementsChildCount_489) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_489, ClearModifiedSettingsDoesNotBreak_489) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_489, RestoreGlobalModifiedSettingsDoesNotBreak_489) {
  state.SetOutputCharset(EscapeAsJson, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_489, SetLocalValueDoesNotBreak_489) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

}  // namespace
}  // namespace YAML
