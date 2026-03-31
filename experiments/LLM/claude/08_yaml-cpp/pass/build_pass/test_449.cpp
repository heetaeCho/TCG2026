#include "gtest/gtest.h"
#include "emitterstate.h"
#include "yaml-cpp/emittermanip.h"

namespace YAML {
namespace {

class EmitterStateTest_449 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_449, InitialStateIsGood_449) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_449, InitialStateHasNoError_449) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_449, InitialStateHasNoAnchor_449) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_449, InitialStateHasNoAlias_449) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_449, InitialStateHasNoTag_449) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_449, InitialCurIndentIsZero_449) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_449, SetErrorMakesStateNotGood_449) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_449, SetErrorStoresErrorMessage_449) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_449, SetErrorMultipleTimes_449) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically first error is preserved, but we just check state is bad
  EXPECT_FALSE(state.good());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_449, SetAnchorSetsHasAnchor_449) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_449, SetAliasSetsHasAlias_449) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_449, SetTagSetsHasTag_449) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Document Lifecycle Tests ====================

TEST_F(EmitterStateTest_449, StartedDocDoesNotBreakState_449) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_449, EndedDocDoesNotBreakState_449) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== SetOutputCharset Tests ====================

TEST_F(EmitterStateTest_449, SetOutputCharsetWithValidValue_449) {
  bool result = state.SetOutputCharset(EmitNonAscii, FmtScope::Global);
  EXPECT_TRUE(result);
}

TEST_F(EmitterStateTest_449, GetOutputCharsetReturnsSetValue_449) {
  state.SetOutputCharset(EmitNonAscii, FmtScope::Global);
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

// ==================== SetStringFormat Tests ====================

TEST_F(EmitterStateTest_449, SetStringFormatWithValidValue_449) {
  bool result = state.SetStringFormat(SingleQuoted, FmtScope::Global);
  EXPECT_TRUE(result);
}

TEST_F(EmitterStateTest_449, GetStringFormatReturnsSetValue_449) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== SetBoolFormat Tests ====================

TEST_F(EmitterStateTest_449, SetBoolFormatWithValidValue_449) {
  bool result = state.SetBoolFormat(TrueFalseBool, FmtScope::Global);
  EXPECT_TRUE(result);
}

TEST_F(EmitterStateTest_449, GetBoolFormatReturnsSetValue_449) {
  state.SetBoolFormat(YesNoBool, FmtScope::Global);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

// ==================== SetBoolLengthFormat Tests ====================

TEST_F(EmitterStateTest_449, SetBoolLengthFormatWithValidValue_449) {
  bool result = state.SetBoolLengthFormat(ShortBool, FmtScope::Global);
  EXPECT_TRUE(result);
}

TEST_F(EmitterStateTest_449, GetBoolLengthFormatReturnsSetValue_449) {
  state.SetBoolLengthFormat(LongBool, FmtScope::Global);
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

// ==================== SetBoolCaseFormat Tests ====================

TEST_F(EmitterStateTest_449, SetBoolCaseFormatWithValidValue_449) {
  bool result = state.SetBoolCaseFormat(UpperCase, FmtScope::Global);
  EXPECT_TRUE(result);
}

TEST_F(EmitterStateTest_449, GetBoolCaseFormatReturnsSetValue_449) {
  state.SetBoolCaseFormat(LowerCase, FmtScope::Global);
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

// ==================== SetNullFormat Tests ====================

TEST_F(EmitterStateTest_449, SetNullFormatWithValidValue_449) {
  bool result = state.SetNullFormat(LowerNull, FmtScope::Global);
  EXPECT_TRUE(result);
}

TEST_F(EmitterStateTest_449, GetNullFormatReturnsSetValue_449) {
  state.SetNullFormat(TildeNull, FmtScope::Global);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== SetIntFormat Tests ====================

TEST_F(EmitterStateTest_449, SetIntFormatDecimal_449) {
  bool result = state.SetIntFormat(Dec, FmtScope::Global);
  EXPECT_TRUE(result);
}

TEST_F(EmitterStateTest_449, SetIntFormatHex_449) {
  bool result = state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_449, SetIntFormatOct_449) {
  bool result = state.SetIntFormat(Oct, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

// ==================== SetIndent Tests ====================

TEST_F(EmitterStateTest_449, SetIndentWithValidValue_449) {
  bool result = state.SetIndent(4, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_449, SetIndentWithMinValue_449) {
  bool result = state.SetIndent(2, FmtScope::Global);
  EXPECT_TRUE(result);
}

TEST_F(EmitterStateTest_449, SetIndentWithZero_449) {
  // Zero indent might be invalid
  bool result = state.SetIndent(0, FmtScope::Global);
  // We just observe the return
  (void)result;
}

TEST_F(EmitterStateTest_449, SetIndentWithOne_449) {
  // 1 might be invalid (minimum typically 2)
  bool result = state.SetIndent(1, FmtScope::Global);
  (void)result;
}

// ==================== SetPreCommentIndent Tests ====================

TEST_F(EmitterStateTest_449, SetPreCommentIndentValid_449) {
  bool result = state.SetPreCommentIndent(2, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(2u, state.GetPreCommentIndent());
}

// ==================== SetPostCommentIndent Tests ====================

TEST_F(EmitterStateTest_449, SetPostCommentIndentValid_449) {
  bool result = state.SetPostCommentIndent(1, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(1u, state.GetPostCommentIndent());
}

// ==================== SetFlowType Tests ====================

TEST_F(EmitterStateTest_449, SetFlowTypeForSeq_449) {
  bool result = state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_449, SetFlowTypeForMap_449) {
  bool result = state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== SetMapKeyFormat Tests ====================

TEST_F(EmitterStateTest_449, SetMapKeyFormatValid_449) {
  bool result = state.SetMapKeyFormat(LongKey, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== SetFloatPrecision Tests ====================

TEST_F(EmitterStateTest_449, SetFloatPrecisionValid_449) {
  bool result = state.SetFloatPrecision(6, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(6u, state.GetFloatPrecision());
}

// ==================== SetDoublePrecision Tests ====================

TEST_F(EmitterStateTest_449, SetDoublePrecisionValid_449) {
  bool result = state.SetDoublePrecision(15, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

// ==================== Group Operations Tests ====================

TEST_F(EmitterStateTest_449, StartedGroupSeq_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_449, StartedGroupMap_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_449, EndedGroupSeq_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_449, EndedGroupMap_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_449, CurGroupChildCountInitiallyZero_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_449, CurGroupIndentAfterStart_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // Just check it doesn't crash and returns a reasonable value
  std::size_t indent = state.CurGroupIndent();
  (void)indent;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_449, CurGroupLongKeyDefault_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_449, SetNonContentDoesNotBreakState_449) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_449, SetLongKeyInGroup_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_449, ForceFlowInGroup_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== StartedScalar Tests ====================

TEST_F(EmitterStateTest_449, StartedScalarInGroup_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_449, StartedScalarIncreasesChildCount_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

// ==================== AnchorClearedAfterNode Tests ====================

TEST_F(EmitterStateTest_449, AnchorClearedAfterStartedScalar_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_449, AliasClearedAfterStartedScalar_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_449, TagClearedAfterStartedScalar_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasTag());
}

// ==================== FmtScope::Local Tests ====================

TEST_F(EmitterStateTest_449, SetIndentLocalScope_449) {
  bool result = state.SetIndent(4, FmtScope::Local);
  EXPECT_TRUE(result);
}

TEST_F(EmitterStateTest_449, SetStringFormatLocalScope_449) {
  bool result = state.SetStringFormat(Literal, FmtScope::Local);
  EXPECT_TRUE(result);
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_449, ClearModifiedSettingsDoesNotBreak_449) {
  state.SetIndent(6, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_449, RestoreGlobalModifiedSettingsDoesNotBreak_449) {
  state.SetIndent(6, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_449, NextGroupTypeForSeq_449) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Just verify it returns a valid value without crashing
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_449, NextGroupTypeForMap_449) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_449, LastIndentInitially_449) {
  std::size_t indent = state.LastIndent();
  (void)indent;
  EXPECT_TRUE(state.good());
}

// ==================== Multiple Group Nesting Tests ====================

TEST_F(EmitterStateTest_449, NestedGroups_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_449, SetLocalValueFlow_449) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_449, SetLocalValueBlock_449) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_449, SetLocalValueHex_449) {
  state.SetLocalValue(Hex);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_449, SetLocalValueDoubleQuoted_449) {
  state.SetLocalValue(DoubleQuoted);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== Invalid SetBoolFormat Tests ====================

TEST_F(EmitterStateTest_449, SetBoolFormatWithInvalidValue_449) {
  // Passing a non-bool-format value should return false
  bool result = state.SetBoolFormat(Hex, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_449, SetIntFormatWithInvalidValue_449) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_449, SetOutputCharsetWithInvalidValue_449) {
  bool result = state.SetOutputCharset(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_449, SetStringFormatWithInvalidValue_449) {
  bool result = state.SetStringFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== HasBegunNode / HasBegunContent Tests ====================

TEST_F(EmitterStateTest_449, HasBegunNodeInitiallyFalse_449) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_449, HasBegunContentInitiallyFalse_449) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== CurGroupFlowType Tests ====================

TEST_F(EmitterStateTest_449, CurGroupFlowTypeDefaultBlock_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(FlowType::NoType, state.CurGroupFlowType());
}

// ==================== Multiple Scalars In Group ====================

TEST_F(EmitterStateTest_449, MultipleScalarsIncreasesChildCount_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.StartedScalar();
  state.StartedScalar();
  EXPECT_EQ(3u, state.CurGroupChildCount());
}

// ==================== CurGroupNodeType Tests ====================

TEST_F(EmitterStateTest_449, CurGroupNodeTypeInSeq_449) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

}  // namespace
}  // namespace YAML
