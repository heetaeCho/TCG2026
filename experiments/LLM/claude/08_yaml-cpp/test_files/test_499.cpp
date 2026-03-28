#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {
namespace {

class EmitterStateTest_499 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ===========================================================================
// Construction and initial state tests
// ===========================================================================

TEST_F(EmitterStateTest_499, InitialStateIsGood_499) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_499, InitialLastErrorIsEmpty_499) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_499, InitialCurIndentIsZero_499) {
  EXPECT_EQ(0u, state.CurIndent());
}

TEST_F(EmitterStateTest_499, InitialHasAnchorIsFalse_499) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_499, InitialHasAliasIsFalse_499) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_499, InitialHasTagIsFalse_499) {
  EXPECT_FALSE(state.HasTag());
}

// ===========================================================================
// SetError / good / GetLastError
// ===========================================================================

TEST_F(EmitterStateTest_499, SetErrorMakesStateNotGood_499) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_499, SetErrorStoresMessage_499) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_499, MultipleSetErrorKeepsFirstError_499) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically only the first error is retained
  EXPECT_FALSE(state.good());
  // The first error should be preserved
  EXPECT_EQ("first error", state.GetLastError());
}

// ===========================================================================
// SetFlowType / GetFlowType
// ===========================================================================

TEST_F(EmitterStateTest_499, SetFlowTypeBlockForSeqReturnsTrue_499) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetFlowTypeFlowForSeqReturnsTrue_499) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetFlowTypeBlockForMapReturnsTrue_499) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetFlowTypeFlowForMapReturnsTrue_499) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetFlowTypeInvalidValueReturnsFalse_499) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Auto, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetFlowTypeInvalidManipReturnsFalseForMap_499) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Map, Literal, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, GetFlowTypeReflectsSetForSeq_499) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_499, GetFlowTypeReflectsSetForMap_499) {
  state.SetFlowType(GroupType::Map, Flow, FmtScope::Global);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_499, SetFlowTypeBlockThenGetForSeq_499) {
  state.SetFlowType(GroupType::Seq, Block, FmtScope::Global);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_499, SetFlowTypeBlockThenGetForMap_499) {
  state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_499, SetFlowTypeLocalScopeForSeq_499) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_499, SetFlowTypeLocalScopeForMap_499) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
}

// ===========================================================================
// SetOutputCharset
// ===========================================================================

TEST_F(EmitterStateTest_499, SetOutputCharsetEmitNonAsciiReturnsTrue_499) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetOutputCharsetEscapeNonAsciiReturnsTrue_499) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetOutputCharsetInvalidReturnsFalse_499) {
  EXPECT_FALSE(state.SetOutputCharset(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, GetOutputCharsetReflectsSet_499) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Global);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

// ===========================================================================
// SetStringFormat
// ===========================================================================

TEST_F(EmitterStateTest_499, SetStringFormatSingleQuotedReturnsTrue_499) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetStringFormatDoubleQuotedReturnsTrue_499) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetStringFormatLiteralReturnsTrue_499) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetStringFormatInvalidReturnsFalse_499) {
  EXPECT_FALSE(state.SetStringFormat(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, GetStringFormatReflectsSet_499) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ===========================================================================
// SetBoolFormat
// ===========================================================================

TEST_F(EmitterStateTest_499, SetBoolFormatYesNoReturnsTrue_499) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetBoolFormatTrueFalseReturnsTrue_499) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetBoolFormatOnOffReturnsTrue_499) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetBoolFormatInvalidReturnsFalse_499) {
  EXPECT_FALSE(state.SetBoolFormat(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, GetBoolFormatReflectsSet_499) {
  state.SetBoolFormat(OnOffBool, FmtScope::Global);
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

// ===========================================================================
// SetBoolLengthFormat
// ===========================================================================

TEST_F(EmitterStateTest_499, SetBoolLengthFormatLongReturnsTrue_499) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetBoolLengthFormatShortReturnsTrue_499) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetBoolLengthFormatInvalidReturnsFalse_499) {
  EXPECT_FALSE(state.SetBoolLengthFormat(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, GetBoolLengthFormatReflectsSet_499) {
  state.SetBoolLengthFormat(ShortBool, FmtScope::Global);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

// ===========================================================================
// SetBoolCaseFormat
// ===========================================================================

TEST_F(EmitterStateTest_499, SetBoolCaseFormatUpperReturnsTrue_499) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetBoolCaseFormatLowerReturnsTrue_499) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetBoolCaseFormatCamelReturnsTrue_499) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetBoolCaseFormatInvalidReturnsFalse_499) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, GetBoolCaseFormatReflectsSet_499) {
  state.SetBoolCaseFormat(LowerCase, FmtScope::Global);
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

// ===========================================================================
// SetNullFormat
// ===========================================================================

TEST_F(EmitterStateTest_499, SetNullFormatLowerNullReturnsTrue_499) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetNullFormatUpperNullReturnsTrue_499) {
  EXPECT_TRUE(state.SetNullFormat(UpperNull, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetNullFormatCamelNullReturnsTrue_499) {
  EXPECT_TRUE(state.SetNullFormat(CamelNull, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetNullFormatTildeNullReturnsTrue_499) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetNullFormatInvalidReturnsFalse_499) {
  EXPECT_FALSE(state.SetNullFormat(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, GetNullFormatReflectsSet_499) {
  state.SetNullFormat(TildeNull, FmtScope::Global);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ===========================================================================
// SetIntFormat
// ===========================================================================

TEST_F(EmitterStateTest_499, SetIntFormatDecReturnsTrue_499) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetIntFormatHexReturnsTrue_499) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetIntFormatOctReturnsTrue_499) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetIntFormatInvalidReturnsFalse_499) {
  EXPECT_FALSE(state.SetIntFormat(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, GetIntFormatReflectsSet_499) {
  state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

// ===========================================================================
// SetIndent
// ===========================================================================

TEST_F(EmitterStateTest_499, SetIndentValidValueReturnsTrue_499) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetIndentMinValueReturnsTrue_499) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetIndentTooSmallReturnsFalse_499) {
  // Indent of 0 or 1 is typically invalid
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, GetIndentReflectsSet_499) {
  state.SetIndent(6, FmtScope::Global);
  EXPECT_EQ(6u, state.GetIndent());
}

// ===========================================================================
// SetPreCommentIndent / SetPostCommentIndent
// ===========================================================================

TEST_F(EmitterStateTest_499, SetPreCommentIndentValidReturnsTrue_499) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetPostCommentIndentValidReturnsTrue_499) {
  EXPECT_TRUE(state.SetPostCommentIndent(1, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, GetPreCommentIndentReflectsSet_499) {
  state.SetPreCommentIndent(3, FmtScope::Global);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_499, GetPostCommentIndentReflectsSet_499) {
  state.SetPostCommentIndent(5, FmtScope::Global);
  EXPECT_EQ(5u, state.GetPostCommentIndent());
}

// ===========================================================================
// SetMapKeyFormat
// ===========================================================================

TEST_F(EmitterStateTest_499, SetMapKeyFormatLongKeyReturnsTrue_499) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetMapKeyFormatAutoReturnsTrue_499) {
  EXPECT_TRUE(state.SetMapKeyFormat(Auto, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetMapKeyFormatInvalidReturnsFalse_499) {
  EXPECT_FALSE(state.SetMapKeyFormat(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, GetMapKeyFormatReflectsSet_499) {
  state.SetMapKeyFormat(LongKey, FmtScope::Global);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ===========================================================================
// SetFloatPrecision / SetDoublePrecision
// ===========================================================================

TEST_F(EmitterStateTest_499, SetFloatPrecisionValidReturnsTrue_499) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetDoublePrecisionValidReturnsTrue_499) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, GetFloatPrecisionReflectsSet_499) {
  state.SetFloatPrecision(3, FmtScope::Global);
  EXPECT_EQ(3u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_499, GetDoublePrecisionReflectsSet_499) {
  state.SetDoublePrecision(10, FmtScope::Global);
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ===========================================================================
// SetAnchor / HasAnchor
// ===========================================================================

TEST_F(EmitterStateTest_499, SetAnchorSetsHasAnchor_499) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

// ===========================================================================
// SetAlias / HasAlias
// ===========================================================================

TEST_F(EmitterStateTest_499, SetAliasSetsHasAlias_499) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

// ===========================================================================
// SetTag / HasTag
// ===========================================================================

TEST_F(EmitterStateTest_499, SetTagSetsHasTag_499) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ===========================================================================
// Document operations
// ===========================================================================

TEST_F(EmitterStateTest_499, StartedDocAndEndedDocDoNotCrash_499) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ===========================================================================
// Group operations
// ===========================================================================

TEST_F(EmitterStateTest_499, StartedGroupAndEndedGroupSeq_499) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_499, StartedGroupAndEndedGroupMap_499) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_499, CurGroupChildCountInitiallyZero_499) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_499, CurGroupIndentAfterStartingGroup_499) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // The indent should be some value (dependent on the default indent setting)
  std::size_t indent = state.CurGroupIndent();
  (void)indent; // just ensure it doesn't crash
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_499, CurGroupLongKeyDefaultFalse_499) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ===========================================================================
// ForceFlow
// ===========================================================================

TEST_F(EmitterStateTest_499, ForceFlowOnGroupChangesFlowType_499) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Seq);
}

// ===========================================================================
// SetLongKey
// ===========================================================================

TEST_F(EmitterStateTest_499, SetLongKeyMakesLongKeyTrue_499) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ===========================================================================
// StartedScalar affects child count
// ===========================================================================

TEST_F(EmitterStateTest_499, StartedScalarIncreasesChildCount_499) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

// ===========================================================================
// ClearModifiedSettings / RestoreGlobalModifiedSettings
// ===========================================================================

TEST_F(EmitterStateTest_499, ClearModifiedSettingsDoesNotCrash_499) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_499, RestoreGlobalModifiedSettingsDoesNotCrash_499) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ===========================================================================
// SetNonContent / HasBegunNode / HasBegunContent
// ===========================================================================

TEST_F(EmitterStateTest_499, SetNonContentDoesNotCrash_499) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ===========================================================================
// Multiple flow type overrides (Seq independent of Map)
// ===========================================================================

TEST_F(EmitterStateTest_499, SeqAndMapFlowTypesAreIndependent_499) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ===========================================================================
// SetFlowType with various invalid EMITTER_MANIP values
// ===========================================================================

TEST_F(EmitterStateTest_499, SetFlowTypeDecReturnsFalse_499) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Dec, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetFlowTypeLongKeyReturnsFalse_499) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Map, LongKey, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, SetFlowTypeNewlineReturnsFalse_499) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Newline, FmtScope::Global));
}

// ===========================================================================
// NextGroupType
// ===========================================================================

TEST_F(EmitterStateTest_499, NextGroupTypeSeq_499) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return some valid node type without crashing
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_499, NextGroupTypeMap_499) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ===========================================================================
// LastIndent
// ===========================================================================

TEST_F(EmitterStateTest_499, LastIndentAfterNestedGroups_499) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Seq);
  std::size_t lastIndent = state.LastIndent();
  (void)lastIndent;
  state.EndedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// ===========================================================================
// EscapeAsJson charset
// ===========================================================================

TEST_F(EmitterStateTest_499, SetOutputCharsetEscapeAsJsonReturnsTrue_499) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeAsJson, FmtScope::Global));
}

TEST_F(EmitterStateTest_499, GetOutputCharsetEscapeAsJson_499) {
  state.SetOutputCharset(EscapeAsJson, FmtScope::Global);
  EXPECT_EQ(EscapeAsJson, state.GetOutputCharset());
}

}  // namespace
}  // namespace YAML
