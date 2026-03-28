#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_472 : public ::testing::Test {
 protected:
  EmitterState state;
};

// =============================================================================
// Initial state tests
// =============================================================================

TEST_F(EmitterStateTest_472, InitialStateIsGood_472) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_472, InitialLastErrorIsEmpty_472) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_472, InitialHasAnchorIsFalse_472) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_472, InitialHasAliasIsFalse_472) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_472, InitialHasTagIsFalse_472) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_472, InitialCurIndentIsZero_472) {
  EXPECT_EQ(0u, state.CurIndent());
}

// =============================================================================
// SetError / good / GetLastError tests
// =============================================================================

TEST_F(EmitterStateTest_472, SetErrorMakesStateNotGood_472) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_472, SetErrorStoresErrorMessage_472) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_472, MultipleSetErrorKeepsFirstError_472) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically, once bad, the first error is kept
  EXPECT_FALSE(state.good());
  EXPECT_EQ("first error", state.GetLastError());
}

// =============================================================================
// SetAnchor / SetAlias / SetTag / SetNonContent tests
// =============================================================================

TEST_F(EmitterStateTest_472, SetAnchorSetsHasAnchor_472) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_472, SetAliasSetsHasAlias_472) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_472, SetTagSetsHasTag_472) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// =============================================================================
// Doc lifecycle tests
// =============================================================================

TEST_F(EmitterStateTest_472, StartedDocEndedDoc_472) {
  state.StartedDoc();
  state.EndedDoc();
  // Should remain in good state
  EXPECT_TRUE(state.good());
}

// =============================================================================
// Group lifecycle tests
// =============================================================================

TEST_F(EmitterStateTest_472, StartAndEndGroupSeq_472) {
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_472, StartAndEndGroupMap_472) {
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_472, CurGroupChildCountInitiallyZero_472) {
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_472, CurGroupLongKeyInitiallyFalse_472) {
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

TEST_F(EmitterStateTest_472, CurGroupIndentIsSet_472) {
  state.StartedGroup(GroupType::Seq);
  // Just check it returns a value without crashing
  std::size_t indent = state.CurGroupIndent();
  (void)indent;
  state.EndedGroup(GroupType::Seq);
}

// =============================================================================
// SetLongKey tests
// =============================================================================

TEST_F(EmitterStateTest_472, SetLongKeyOnMapGroup_472) {
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

TEST_F(EmitterStateTest_472, SetLongKeyWithNoGroupDoesNotCrash_472) {
  // No groups are started - SetLongKey should handle gracefully
  // The implementation has an assert check and returns early if empty
  // In release mode, this should not crash
  // We can't test this with assertions enabled; just verify it doesn't segfault
  // state.SetLongKey(); // Would assert in debug - skip in unit test
}

// =============================================================================
// ForceFlow tests
// =============================================================================

TEST_F(EmitterStateTest_472, ForceFlowOnGroup_472) {
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Seq);
}

// =============================================================================
// StartedScalar tests
// =============================================================================

TEST_F(EmitterStateTest_472, StartedScalarIncrementsChildCount_472) {
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_472, StartedScalarClearsAnchorAndTag_472) {
  state.StartedGroup(GroupType::Seq);
  state.SetAnchor();
  state.SetTag();
  EXPECT_TRUE(state.HasAnchor());
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
  state.EndedGroup(GroupType::Seq);
}

// =============================================================================
// Nested groups tests
// =============================================================================

TEST_F(EmitterStateTest_472, NestedGroupsWork_472) {
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());

  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());

  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());

  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// =============================================================================
// Setting format tests
// =============================================================================

TEST_F(EmitterStateTest_472, SetOutputCharsetGlobal_472) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_472, SetOutputCharsetLocal_472) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Local));
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_472, SetStringFormatGlobal_472) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_472, SetStringFormatLocal_472) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_472, SetBoolFormatGlobal_472) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_472, SetBoolLengthFormatGlobal_472) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_472, SetBoolLengthFormatLong_472) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_472, SetBoolCaseFormatGlobal_472) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_472, SetBoolCaseFormatLowerCase_472) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_472, SetBoolCaseFormatCamelCase_472) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_472, SetNullFormatGlobal_472) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_472, SetIntFormatHex_472) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_472, SetIntFormatOct_472) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_472, SetIntFormatDec_472) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_472, SetIndentGlobal_472) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_472, SetIndentBoundaryMinimum_472) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetIndent());
}

TEST_F(EmitterStateTest_472, SetPreCommentIndentGlobal_472) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_472, SetPostCommentIndentGlobal_472) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_472, SetMapKeyFormatGlobal_472) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_472, SetFloatPrecisionGlobal_472) {
  EXPECT_TRUE(state.SetFloatPrecision(5, FmtScope::Global));
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_472, SetDoublePrecisionGlobal_472) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Global));
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// =============================================================================
// SetFlowType / GetFlowType tests
// =============================================================================

TEST_F(EmitterStateTest_472, SetFlowTypeSeqFlow_472) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_472, SetFlowTypeSeqBlock_472) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_472, SetFlowTypeMapFlow_472) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_472, SetFlowTypeMapBlock_472) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// =============================================================================
// Invalid format values tests
// =============================================================================

TEST_F(EmitterStateTest_472, SetOutputCharsetInvalidValue_472) {
  // Passing a wrong manip that doesn't apply to charset
  EXPECT_FALSE(state.SetOutputCharset(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_472, SetStringFormatInvalidValue_472) {
  EXPECT_FALSE(state.SetStringFormat(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_472, SetBoolFormatInvalidValue_472) {
  EXPECT_FALSE(state.SetBoolFormat(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_472, SetIntFormatInvalidValue_472) {
  EXPECT_FALSE(state.SetIntFormat(Flow, FmtScope::Global));
}

// =============================================================================
// NextGroupType tests
// =============================================================================

TEST_F(EmitterStateTest_472, NextGroupTypeSeqWithNoGroups_472) {
  EmitterNodeType::value ntype = state.NextGroupType(GroupType::Seq);
  // Without any parent group, should return some default
  (void)ntype; // Just ensure no crash
}

TEST_F(EmitterStateTest_472, NextGroupTypeMapWithNoGroups_472) {
  EmitterNodeType::value ntype = state.NextGroupType(GroupType::Map);
  (void)ntype;
}

// =============================================================================
// CurGroupNodeType tests
// =============================================================================

TEST_F(EmitterStateTest_472, CurGroupNodeTypeAfterStartingSeq_472) {
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value ntype = state.CurGroupNodeType();
  (void)ntype;
  state.EndedGroup(GroupType::Seq);
}

// =============================================================================
// ClearModifiedSettings / RestoreGlobalModifiedSettings tests
// =============================================================================

TEST_F(EmitterStateTest_472, ClearModifiedSettingsDoesNotCrash_472) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_472, RestoreGlobalModifiedSettingsDoesNotCrash_472) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// =============================================================================
// SetLocalValue tests
// =============================================================================

TEST_F(EmitterStateTest_472, SetLocalValueFlow_472) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_472, SetLocalValueBlock_472) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_472, SetLocalValueLongKey_472) {
  state.SetLocalValue(LongKey);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_472, SetLocalValueDoubleQuoted_472) {
  state.SetLocalValue(DoubleQuoted);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// =============================================================================
// LastIndent tests
// =============================================================================

TEST_F(EmitterStateTest_472, LastIndentWithNoGroups_472) {
  std::size_t last = state.LastIndent();
  EXPECT_EQ(0u, last);
}

TEST_F(EmitterStateTest_472, LastIndentWithOneGroup_472) {
  state.StartedGroup(GroupType::Seq);
  std::size_t last = state.LastIndent();
  (void)last;
  state.EndedGroup(GroupType::Seq);
}

// =============================================================================
// HasBegunNode / HasBegunContent tests
// =============================================================================

TEST_F(EmitterStateTest_472, HasBegunNodeInitiallyFalse_472) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_472, HasBegunContentInitiallyFalse_472) {
  EXPECT_FALSE(state.HasBegunContent());
}

TEST_F(EmitterStateTest_472, HasBegunNodeAfterSetAnchor_472) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_472, HasBegunNodeAfterSetTag_472) {
  state.SetTag();
  EXPECT_TRUE(state.HasBegunNode());
}

// =============================================================================
// Complex lifecycle tests
// =============================================================================

TEST_F(EmitterStateTest_472, FullDocumentLifecycle_472) {
  state.StartedDoc();

  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());

  state.StartedScalar();  // key
  state.StartedScalar();  // value

  EXPECT_EQ(2u, state.CurGroupChildCount());

  state.EndedGroup(GroupType::Map);
  state.EndedDoc();

  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_472, MultipleScalarsInSeq_472) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);

  state.StartedScalar();
  state.StartedScalar();
  state.StartedScalar();

  EXPECT_EQ(3u, state.CurGroupChildCount());

  state.EndedGroup(GroupType::Seq);
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_472, SetLongKeyInMapAndVerify_472) {
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

TEST_F(EmitterStateTest_472, ForceFlowInNestedGroup_472) {
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Map);
  // Outer group should not be affected by inner ForceFlow
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// =============================================================================
// Scope tests (Local vs Global)
// =============================================================================

TEST_F(EmitterStateTest_472, LocalSettingClearedAfterClearModifiedSettings_472) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
  state.ClearModifiedSettings();
  // After clearing local modifications, should revert to default
  // Default string format is typically Auto
  EXPECT_NE(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_472, GlobalSettingPersistsAfterClearModifiedSettings_472) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
  state.ClearModifiedSettings();
  // Global settings should persist
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

}  // namespace YAML
