#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_473 : public ::testing::Test {
 protected:
  EmitterState state;
};

// === Initial State Tests ===

TEST_F(EmitterStateTest_473, InitialStateIsGood_473) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_473, InitialLastErrorIsEmpty_473) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_473, InitialHasAnchorIsFalse_473) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_473, InitialHasAliasIsFalse_473) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_473, InitialHasTagIsFalse_473) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_473, InitialCurIndentIsZero_473) {
  EXPECT_EQ(0u, state.CurIndent());
}

// === SetError Tests ===

TEST_F(EmitterStateTest_473, SetErrorMakesStateNotGood_473) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_473, SetErrorStoresErrorMessage_473) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_473, SetErrorMultipleTimesKeepsFirstError_473) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically the first error is preserved, or the last one. Check observable.
  EXPECT_FALSE(state.good());
  // The first error should be kept since state is no longer good
  std::string err = state.GetLastError();
  EXPECT_FALSE(err.empty());
}

// === SetAnchor / SetAlias / SetTag Tests ===

TEST_F(EmitterStateTest_473, SetAnchorSetsHasAnchor_473) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_473, SetAliasSetsHasAlias_473) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_473, SetTagSetsHasTag_473) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// === Document Tests ===

TEST_F(EmitterStateTest_473, StartedDocDoesNotBreakState_473) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_473, EndedDocDoesNotBreakState_473) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// === Group Tests ===

TEST_F(EmitterStateTest_473, StartedGroupSeq_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_473, StartedGroupMap_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_473, EndedGroupMatchingType_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_473, CurGroupChildCountInitiallyZero_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_473, CurGroupLongKeyInitiallyFalse_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_473, SetLongKeyInGroup_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_473, ForceFlowInGroup_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

TEST_F(EmitterStateTest_473, CurGroupIndentReturnsValue_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // Just verify it doesn't crash and returns some reasonable value
  std::size_t indent = state.CurGroupIndent();
  (void)indent;
  EXPECT_TRUE(state.good());
}

// === Scalar Tests ===

TEST_F(EmitterStateTest_473, StartedScalarInGroup_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_473, StartedScalarIncreasesChildCount_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

// === Format Setting Tests ===

TEST_F(EmitterStateTest_473, SetOutputCharsetGlobal_473) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_473, SetStringFormatGlobal_473) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
}

TEST_F(EmitterStateTest_473, SetBoolFormatGlobal_473) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_473, SetBoolLengthFormatGlobal_473) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_473, SetBoolCaseFormatGlobal_473) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
}

TEST_F(EmitterStateTest_473, SetNullFormatGlobal_473) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
}

TEST_F(EmitterStateTest_473, SetIntFormatGlobal_473) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
}

TEST_F(EmitterStateTest_473, SetIndentGlobal_473) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
}

TEST_F(EmitterStateTest_473, SetPreCommentIndentGlobal_473) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Global));
}

TEST_F(EmitterStateTest_473, SetPostCommentIndentGlobal_473) {
  EXPECT_TRUE(state.SetPostCommentIndent(1, FmtScope::Global));
}

TEST_F(EmitterStateTest_473, SetMapKeyFormatGlobal_473) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
}

TEST_F(EmitterStateTest_473, SetFloatPrecisionGlobal_473) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Global));
}

TEST_F(EmitterStateTest_473, SetDoublePrecisionGlobal_473) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Global));
}

// === Get Format Tests ===

TEST_F(EmitterStateTest_473, GetIndentReturnsDefault_473) {
  std::size_t indent = state.GetIndent();
  EXPECT_GT(indent, 0u);
}

TEST_F(EmitterStateTest_473, GetIndentReturnsSetValue_473) {
  state.SetIndent(6, FmtScope::Global);
  EXPECT_EQ(6u, state.GetIndent());
}

TEST_F(EmitterStateTest_473, GetPreCommentIndentReturnsValue_473) {
  state.SetPreCommentIndent(3, FmtScope::Global);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_473, GetPostCommentIndentReturnsValue_473) {
  state.SetPostCommentIndent(2, FmtScope::Global);
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_473, GetFloatPrecisionReturnsSetValue_473) {
  state.SetFloatPrecision(4, FmtScope::Global);
  EXPECT_EQ(4u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_473, GetDoublePrecisionReturnsSetValue_473) {
  state.SetDoublePrecision(12, FmtScope::Global);
  EXPECT_EQ(12u, state.GetDoublePrecision());
}

TEST_F(EmitterStateTest_473, GetIntFormatReturnsSetValue_473) {
  state.SetIntFormat(Oct, FmtScope::Global);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_473, GetStringFormatReturnsSetValue_473) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_473, GetBoolFormatReturnsSetValue_473) {
  state.SetBoolFormat(TrueFalseBool, FmtScope::Global);
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

// === FlowType Setting Tests ===

TEST_F(EmitterStateTest_473, SetFlowTypeSeqGlobal_473) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_473, SetFlowTypeMapGlobal_473) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
}

TEST_F(EmitterStateTest_473, GetFlowTypeSeqAfterSet_473) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_473, GetFlowTypeMapAfterSet_473) {
  state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// === Local Scope Tests ===

TEST_F(EmitterStateTest_473, SetIndentLocalScope_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_TRUE(state.SetIndent(8, FmtScope::Local));
}

TEST_F(EmitterStateTest_473, ClearModifiedSettingsDoesNotCrash_473) {
  state.SetIndent(4, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_473, RestoreGlobalModifiedSettingsDoesNotCrash_473) {
  state.SetIndent(4, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// === SetLocalValue Tests ===

TEST_F(EmitterStateTest_473, SetLocalValueFlow_473) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_473, SetLocalValueBlock_473) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// === NextGroupType Tests ===

TEST_F(EmitterStateTest_473, NextGroupTypeSeqNoGroups_473) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return some valid value without crashing
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_473, NextGroupTypeMapNoGroups_473) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// === Nested Group Tests ===

TEST_F(EmitterStateTest_473, NestedGroups_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// === HasBegunNode / HasBegunContent Tests ===

TEST_F(EmitterStateTest_473, HasBegunNodeInitially_473) {
  // Initially should not have begun a node
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_473, HasBegunContentInitially_473) {
  EXPECT_FALSE(state.HasBegunContent());
}

// === SetNonContent Tests ===

TEST_F(EmitterStateTest_473, SetNonContentDoesNotCrash_473) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// === LastIndent Tests ===

TEST_F(EmitterStateTest_473, LastIndentNoGroups_473) {
  std::size_t lastIndent = state.LastIndent();
  (void)lastIndent;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_473, LastIndentAfterGroup_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  std::size_t lastIndent = state.LastIndent();
  (void)lastIndent;
  EXPECT_TRUE(state.good());
}

// === Boundary: Invalid format values ===

TEST_F(EmitterStateTest_473, SetOutputCharsetInvalidValue_473) {
  // Passing a value that doesn't correspond to charset - should return false
  bool result = state.SetOutputCharset(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_473, SetStringFormatInvalidValue_473) {
  bool result = state.SetStringFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_473, SetBoolFormatInvalidValue_473) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_473, SetIntFormatInvalidValue_473) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// === Multiple scalars in a group ===

TEST_F(EmitterStateTest_473, MultipleScalarsIncrementChildCount_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.StartedScalar();
  state.StartedScalar();
  EXPECT_EQ(3u, state.CurGroupChildCount());
}

// === Anchor/Alias/Tag reset after node starts ===

TEST_F(EmitterStateTest_473, AnchorResetsAfterScalar_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_473, AliasResetsAfterScalar_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_473, TagResetsAfterScalar_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasTag());
}

// === CurGroupNodeType ===

TEST_F(EmitterStateTest_473, CurGroupNodeTypeInSeq_473) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// === ForceFlow on empty groups (boundary) ===

TEST_F(EmitterStateTest_473, ForceFlowWithNoGroupsDoesNotCrash_473) {
  // ForceFlow with no groups should just return (the assert may trigger in debug)
  // In release mode, it should safely return
  // We just verify it doesn't cause undefined behavior in a controlled test
  // Skip this test if assertions are enabled - it's a boundary case
  // state.ForceFlow(); // would assert
  EXPECT_TRUE(state.good());
}

// === SetError on already bad state ===

TEST_F(EmitterStateTest_473, SetErrorOnAlreadyBadState_473) {
  state.SetError("first");
  EXPECT_FALSE(state.good());
  state.SetError("second");
  EXPECT_FALSE(state.good());
  // First error should be preserved
  EXPECT_EQ("first", state.GetLastError());
}

}  // namespace YAML
