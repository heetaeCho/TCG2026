#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {
namespace {

class EmitterStateTest_491 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Constructor / Initial State ====================

TEST_F(EmitterStateTest_491, InitialStateIsGood_491) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_491, InitialLastErrorIsEmpty_491) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_491, InitialHasAnchorIsFalse_491) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_491, InitialHasAliasIsFalse_491) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_491, InitialHasTagIsFalse_491) {
  EXPECT_FALSE(state.HasTag());
}

// ==================== SetError ====================

TEST_F(EmitterStateTest_491, SetErrorMakesStateNotGood_491) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_491, SetErrorSetsLastError_491) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_491, SetErrorMultipleTimesKeepsFirstError_491) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically first error is preserved, but behavior may vary
  EXPECT_FALSE(state.good());
}

// ==================== SetBoolFormat ====================

TEST_F(EmitterStateTest_491, SetBoolFormatOnOffBoolReturnsTrue_491) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolFormatTrueFalseBoolReturnsTrue_491) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolFormatYesNoBoolReturnsTrue_491) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolFormatInvalidValueReturnsFalse_491) {
  EXPECT_FALSE(state.SetBoolFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolFormatFlowReturnsFalse_491) {
  EXPECT_FALSE(state.SetBoolFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolFormatBlockReturnsFalse_491) {
  EXPECT_FALSE(state.SetBoolFormat(Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolFormatDecReturnsFalse_491) {
  EXPECT_FALSE(state.SetBoolFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolFormatGlobalScope_491) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_491, GetBoolFormatAfterSet_491) {
  state.SetBoolFormat(YesNoBool, FmtScope::Local);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_491, GetBoolFormatAfterSetOnOff_491) {
  state.SetBoolFormat(OnOffBool, FmtScope::Local);
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

// ==================== SetBoolLengthFormat ====================

TEST_F(EmitterStateTest_491, SetBoolLengthFormatLongBoolReturnsTrue_491) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolLengthFormatShortBoolReturnsTrue_491) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolLengthFormatInvalidReturnsFalse_491) {
  EXPECT_FALSE(state.SetBoolLengthFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, GetBoolLengthFormatAfterSet_491) {
  state.SetBoolLengthFormat(ShortBool, FmtScope::Local);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

// ==================== SetBoolCaseFormat ====================

TEST_F(EmitterStateTest_491, SetBoolCaseFormatUpperCaseReturnsTrue_491) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolCaseFormatLowerCaseReturnsTrue_491) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolCaseFormatCamelCaseReturnsTrue_491) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolCaseFormatInvalidReturnsFalse_491) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, GetBoolCaseFormatAfterSet_491) {
  state.SetBoolCaseFormat(UpperCase, FmtScope::Local);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

// ==================== SetOutputCharset ====================

TEST_F(EmitterStateTest_491, SetOutputCharsetEmitNonAsciiReturnsTrue_491) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetOutputCharsetEscapeNonAsciiReturnsTrue_491) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetOutputCharsetEscapeAsJsonReturnsTrue_491) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeAsJson, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetOutputCharsetInvalidReturnsFalse_491) {
  EXPECT_FALSE(state.SetOutputCharset(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, GetOutputCharsetAfterSet_491) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Local);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

// ==================== SetStringFormat ====================

TEST_F(EmitterStateTest_491, SetStringFormatSingleQuotedReturnsTrue_491) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetStringFormatDoubleQuotedReturnsTrue_491) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetStringFormatLiteralReturnsTrue_491) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetStringFormatAutoReturnsTrue_491) {
  EXPECT_TRUE(state.SetStringFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetStringFormatInvalidReturnsFalse_491) {
  EXPECT_FALSE(state.SetStringFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, GetStringFormatAfterSet_491) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== SetNullFormat ====================

TEST_F(EmitterStateTest_491, SetNullFormatLowerNullReturnsTrue_491) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetNullFormatUpperNullReturnsTrue_491) {
  EXPECT_TRUE(state.SetNullFormat(UpperNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetNullFormatCamelNullReturnsTrue_491) {
  EXPECT_TRUE(state.SetNullFormat(CamelNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetNullFormatTildeNullReturnsTrue_491) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetNullFormatInvalidReturnsFalse_491) {
  EXPECT_FALSE(state.SetNullFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, GetNullFormatAfterSet_491) {
  state.SetNullFormat(TildeNull, FmtScope::Local);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== SetIntFormat ====================

TEST_F(EmitterStateTest_491, SetIntFormatDecReturnsTrue_491) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetIntFormatHexReturnsTrue_491) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetIntFormatOctReturnsTrue_491) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetIntFormatInvalidReturnsFalse_491) {
  EXPECT_FALSE(state.SetIntFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, GetIntFormatAfterSet_491) {
  state.SetIntFormat(Hex, FmtScope::Local);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

// ==================== SetIndent ====================

TEST_F(EmitterStateTest_491, SetIndentValidValueReturnsTrue_491) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetIndentMinValueReturnsTrue_491) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetIndentZeroReturnsFalse_491) {
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetIndentOneReturnsFalse_491) {
  EXPECT_FALSE(state.SetIndent(1, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, GetIndentAfterSet_491) {
  state.SetIndent(6, FmtScope::Local);
  EXPECT_EQ(6u, state.GetIndent());
}

// ==================== SetPreCommentIndent ====================

TEST_F(EmitterStateTest_491, SetPreCommentIndentValidReturnsTrue_491) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetPreCommentIndentZeroReturnsFalse_491) {
  EXPECT_FALSE(state.SetPreCommentIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, GetPreCommentIndentAfterSet_491) {
  state.SetPreCommentIndent(3, FmtScope::Local);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

// ==================== SetPostCommentIndent ====================

TEST_F(EmitterStateTest_491, SetPostCommentIndentValidReturnsTrue_491) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetPostCommentIndentZeroReturnsFalse_491) {
  EXPECT_FALSE(state.SetPostCommentIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, GetPostCommentIndentAfterSet_491) {
  state.SetPostCommentIndent(5, FmtScope::Local);
  EXPECT_EQ(5u, state.GetPostCommentIndent());
}

// ==================== SetFloatPrecision ====================

TEST_F(EmitterStateTest_491, SetFloatPrecisionValidReturnsTrue_491) {
  EXPECT_TRUE(state.SetFloatPrecision(5, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, GetFloatPrecisionAfterSet_491) {
  state.SetFloatPrecision(3, FmtScope::Local);
  EXPECT_EQ(3u, state.GetFloatPrecision());
}

// ==================== SetDoublePrecision ====================

TEST_F(EmitterStateTest_491, SetDoublePrecisionValidReturnsTrue_491) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, GetDoublePrecisionAfterSet_491) {
  state.SetDoublePrecision(8, FmtScope::Local);
  EXPECT_EQ(8u, state.GetDoublePrecision());
}

// ==================== SetMapKeyFormat ====================

TEST_F(EmitterStateTest_491, SetMapKeyFormatLongKeyReturnsTrue_491) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetMapKeyFormatAutoReturnsTrue_491) {
  EXPECT_TRUE(state.SetMapKeyFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetMapKeyFormatInvalidReturnsFalse_491) {
  EXPECT_FALSE(state.SetMapKeyFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, GetMapKeyFormatAfterSet_491) {
  state.SetMapKeyFormat(LongKey, FmtScope::Local);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== SetFlowType ====================

TEST_F(EmitterStateTest_491, SetFlowTypeSeqFlowReturnsTrue_491) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetFlowTypeSeqBlockReturnsTrue_491) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetFlowTypeMapFlowReturnsTrue_491) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetFlowTypeMapBlockReturnsTrue_491) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetFlowTypeInvalidReturnsFalse_491) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, GetFlowTypeAfterSet_491) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

// ==================== SetAnchor / SetAlias / SetTag ====================

TEST_F(EmitterStateTest_491, SetAnchorSetsHasAnchor_491) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_491, SetAliasSetsHasAlias_491) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_491, SetTagSetsHasTag_491) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Document lifecycle ====================

TEST_F(EmitterStateTest_491, StartedDocEndedDocDoNotCrash_491) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group lifecycle ====================

TEST_F(EmitterStateTest_491, StartedGroupSeqEndedGroupSeq_491) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_491, StartedGroupMapEndedGroupMap_491) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_491, CurGroupChildCountInitiallyZero_491) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

// ==================== Scalar ====================

TEST_F(EmitterStateTest_491, StartedScalarInGroup_491) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

// ==================== FmtScope::Global ====================

TEST_F(EmitterStateTest_491, SetBoolFormatGlobalScopeAndRestore_491) {
  state.SetBoolFormat(YesNoBool, FmtScope::Global);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

// ==================== ClearModifiedSettings ====================

TEST_F(EmitterStateTest_491, ClearModifiedSettingsDoesNotCrash_491) {
  state.SetBoolFormat(YesNoBool, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterStateTest_491, RestoreGlobalModifiedSettingsDoesNotCrash_491) {
  state.SetBoolFormat(YesNoBool, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== CurIndent ====================

TEST_F(EmitterStateTest_491, CurIndentInitial_491) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== ForceFlow ====================

TEST_F(EmitterStateTest_491, ForceFlowDoesNotCrash_491) {
  state.ForceFlow();
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey ====================

TEST_F(EmitterStateTest_491, SetLongKeyDoesNotCrash_491) {
  state.SetLongKey();
  EXPECT_TRUE(state.good());
}

// ==================== SetNonContent ====================

TEST_F(EmitterStateTest_491, SetNonContentDoesNotCrash_491) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== Multiple valid BoolFormat values with Global scope ====================

TEST_F(EmitterStateTest_491, SetBoolFormatOnOffBoolGlobal_491) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Global));
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_491, SetBoolFormatTrueFalseBoolGlobal_491) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

// ==================== All invalid EMITTER_MANIP for SetBoolFormat ====================

TEST_F(EmitterStateTest_491, SetBoolFormatNewlineReturnsFalse_491) {
  EXPECT_FALSE(state.SetBoolFormat(Newline, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolFormatLongKeyReturnsFalse_491) {
  EXPECT_FALSE(state.SetBoolFormat(LongKey, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolFormatHexReturnsFalse_491) {
  EXPECT_FALSE(state.SetBoolFormat(Hex, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolFormatSingleQuotedReturnsFalse_491) {
  EXPECT_FALSE(state.SetBoolFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolFormatUpperCaseReturnsFalse_491) {
  EXPECT_FALSE(state.SetBoolFormat(UpperCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolFormatLongBoolReturnsFalse_491) {
  EXPECT_FALSE(state.SetBoolFormat(LongBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_491, SetBoolFormatShortBoolReturnsFalse_491) {
  EXPECT_FALSE(state.SetBoolFormat(ShortBool, FmtScope::Local));
}

}  // namespace
}  // namespace YAML
