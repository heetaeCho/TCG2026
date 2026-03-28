#include <gtest/gtest.h>
#include "emitterstate.h"
#include "yaml-cpp/emittermanip.h"

namespace YAML {

class EmitterStateTest_481 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_481, InitialStateIsGood_481) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_481, InitialLastErrorIsEmpty_481) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_481, InitialCurGroupTypeIsNoType_481) {
  EXPECT_EQ(GroupType::NoType, state.CurGroupType());
}

TEST_F(EmitterStateTest_481, InitialHasAnchorIsFalse_481) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_481, InitialHasAliasIsFalse_481) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_481, InitialHasTagIsFalse_481) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_481, InitialCurIndentIsZero_481) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_481, SetErrorMakesStateNotGood_481) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_481, SetErrorStoresMessage_481) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_481, SetErrorMultipleTimes_481) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_FALSE(state.good());
  // Typically the first error is kept
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== Anchor, Alias, Tag Tests ====================

TEST_F(EmitterStateTest_481, SetAnchorSetsHasAnchor_481) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_481, SetAliasSetsHasAlias_481) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_481, SetTagSetsHasTag_481) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Document Tests ====================

TEST_F(EmitterStateTest_481, StartedDocDoesNotBreakGoodState_481) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_481, EndedDocDoesNotBreakGoodState_481) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_481, StartedGroupSequenceSetsType_481) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_481, StartedGroupMapSetsType_481) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_481, EndedGroupRestoresPreviousType_481) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_481, EndedAllGroupsReturnsNoType_481) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::NoType, state.CurGroupType());
}

TEST_F(EmitterStateTest_481, CurGroupChildCountInitiallyZero_481) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_481, CurGroupLongKeyInitiallyFalse_481) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_481, NestedGroupsTrackCorrectly_481) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::NoType, state.CurGroupType());
}

// ==================== Scalar Tests ====================

TEST_F(EmitterStateTest_481, StartedScalarInGroup_481) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  // After starting a scalar, child count should increase
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

// ==================== Format Setting Tests ====================

TEST_F(EmitterStateTest_481, SetOutputCharsetReturnsTrue_481) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_481, SetStringFormatReturnsTrue_481) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_481, SetBoolFormatReturnsTrue_481) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_481, SetBoolLengthFormatReturnsTrue_481) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_481, SetBoolCaseFormatReturnsTrue_481) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_481, SetNullFormatReturnsTrue_481) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_481, SetIntFormatReturnsTrue_481) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_481, SetIntFormatHex_481) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_481, SetIntFormatOct_481) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Local));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_481, SetIndentReturnsTrue_481) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_481, SetIndentToMinimum_481) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Local));
  EXPECT_EQ(2u, state.GetIndent());
}

TEST_F(EmitterStateTest_481, SetPreCommentIndent_481) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Local));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_481, SetPostCommentIndent_481) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Local));
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_481, SetMapKeyFormatReturnsTrue_481) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Local));
}

TEST_F(EmitterStateTest_481, SetFloatPrecision_481) {
  EXPECT_TRUE(state.SetFloatPrecision(5, FmtScope::Local));
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_481, SetDoublePrecision_481) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Local));
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== FlowType Tests ====================

TEST_F(EmitterStateTest_481, SetFlowTypeForSeq_481) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_481, SetFlowTypeForMap_481) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== Global Scope Tests ====================

TEST_F(EmitterStateTest_481, SetIndentGlobalScope_481) {
  EXPECT_TRUE(state.SetIndent(6, FmtScope::Global));
  EXPECT_EQ(6u, state.GetIndent());
}

TEST_F(EmitterStateTest_481, SetStringFormatGlobalScope_481) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_481, ClearModifiedSettingsDoesNotCrash_481) {
  state.SetLocalValue(Flow);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_481, RestoreGlobalModifiedSettingsDoesNotCrash_481) {
  state.SetIndent(8, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_481, SetLongKeyInGroup_481) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_481, ForceFlowInGroup_481) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_481, NextGroupTypeSeqWhenNoGroup_481) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return some valid node type
  EXPECT_TRUE(nodeType == EmitterNodeType::NoType ||
              nodeType == EmitterNodeType::Property ||
              nodeType == EmitterNodeType::FlowSeq ||
              nodeType == EmitterNodeType::BlockSeq ||
              nodeType == EmitterNodeType::FlowMap ||
              nodeType == EmitterNodeType::BlockMap);
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_481, SetLocalValueFlow_481) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_481, SetLocalValueBlock_481) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// ==================== HasBegunNode / HasBegunContent Tests ====================

TEST_F(EmitterStateTest_481, InitialHasBegunNodeIsFalse_481) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_481, InitialHasBegunContentIsFalse_481) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_481, SetNonContentDoesNotCrash_481) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== Default format getters ====================

TEST_F(EmitterStateTest_481, DefaultGetOutputCharset_481) {
  EMITTER_MANIP charset = state.GetOutputCharset();
  // Should be some valid default
  (void)charset;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_481, DefaultGetStringFormat_481) {
  EMITTER_MANIP fmt = state.GetStringFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_481, DefaultGetBoolFormat_481) {
  EMITTER_MANIP fmt = state.GetBoolFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_481, DefaultGetBoolLengthFormat_481) {
  EMITTER_MANIP fmt = state.GetBoolLengthFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_481, DefaultGetBoolCaseFormat_481) {
  EMITTER_MANIP fmt = state.GetBoolCaseFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_481, DefaultGetNullFormat_481) {
  EMITTER_MANIP fmt = state.GetNullFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_481, DefaultGetIntFormat_481) {
  EMITTER_MANIP fmt = state.GetIntFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_481, DefaultGetMapKeyFormat_481) {
  EMITTER_MANIP fmt = state.GetMapKeyFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

// ==================== Invalid format setting tests ====================

TEST_F(EmitterStateTest_481, SetOutputCharsetWithInvalidValue_481) {
  // Passing a value that is not a charset value
  bool result = state.SetOutputCharset(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_481, SetStringFormatWithInvalidValue_481) {
  bool result = state.SetStringFormat(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_481, SetBoolFormatWithInvalidValue_481) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_481, SetIntFormatWithInvalidValue_481) {
  bool result = state.SetIntFormat(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== CurGroupIndent and LastIndent Tests ====================

TEST_F(EmitterStateTest_481, CurGroupIndentInGroup_481) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  std::size_t indent = state.CurGroupIndent();
  (void)indent;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_481, LastIndentInitially_481) {
  std::size_t indent = state.LastIndent();
  (void)indent;
  EXPECT_TRUE(state.good());
}

// ==================== CurGroupFlowType Tests ====================

TEST_F(EmitterStateTest_481, CurGroupFlowTypeInGroup_481) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  FlowType::value ft = state.CurGroupFlowType();
  (void)ft;
  EXPECT_TRUE(state.good());
}

// ==================== Multiple Scalars In Group ====================

TEST_F(EmitterStateTest_481, MultipleScalarsIncreaseChildCount_481) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.StartedScalar();
  state.StartedScalar();
  EXPECT_EQ(3u, state.CurGroupChildCount());
}

// ==================== CurGroupNodeType Tests ====================

TEST_F(EmitterStateTest_481, CurGroupNodeTypeInSeq_481) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

}  // namespace YAML
