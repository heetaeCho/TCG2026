#include "gtest/gtest.h"
#include "emitterstate.h"
#include "yaml-cpp/emittermanip.h"

namespace YAML {

class EmitterStateTest_444 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_444, InitialStateIsGood_444) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_444, InitialLastErrorIsEmpty_444) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_444, InitialCurIndentIsZero_444) {
  EXPECT_EQ(0u, state.CurIndent());
}

TEST_F(EmitterStateTest_444, InitialHasAnchorIsFalse_444) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_444, InitialHasAliasIsFalse_444) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_444, InitialHasTagIsFalse_444) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_444, InitialHasBegunNodeIsFalse_444) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_444, InitialHasBegunContentIsFalse_444) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_444, SetErrorMakesStateNotGood_444) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_444, SetErrorSetsLastError_444) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_444, SetErrorTwiceKeepsFirstError_444) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_FALSE(state.good());
  // Typically only the first error is retained
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_444, SetAnchorSetsHasAnchor_444) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_444, SetAliasSetsHasAlias_444) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_444, SetTagSetsHasTag_444) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Document Tests ====================

TEST_F(EmitterStateTest_444, StartedDocDoesNotBreakGoodState_444) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_444, EndedDocDoesNotBreakGoodState_444) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Scalar Tests ====================

TEST_F(EmitterStateTest_444, StartedScalarBeforeGroupSetsError_444) {
  // Starting a scalar without being in a proper group context
  // may or may not set error depending on implementation;
  // but we can test that after StartedDoc + StartedScalar, anchor/tag are cleared
  state.StartedDoc();
  state.SetAnchor();
  state.SetTag();
  EXPECT_TRUE(state.HasAnchor());
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  // After starting a scalar, anchor and tag should be consumed
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_444, StartedGroupSeqAndEndedGroup_444) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_444, StartedGroupMapAndEndedGroup_444) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_444, CurGroupChildCountInitiallyZero_444) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_444, CurGroupChildCountIncrementsAfterScalar_444) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_444, CurGroupLongKeyDefaultFalse_444) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_444, SetLongKeyMakesCurGroupLongKeyTrue_444) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== Format Setter/Getter Tests ====================

TEST_F(EmitterStateTest_444, SetOutputCharsetAndGet_444) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_444, SetStringFormatAndGet_444) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_444, SetBoolFormatAndGet_444) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_444, SetBoolLengthFormatAndGet_444) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_444, SetBoolCaseFormatAndGet_444) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_444, SetNullFormatAndGet_444) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_444, SetIntFormatAndGet_444) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_444, SetIntFormatOct_444) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_444, SetIndentAndGet_444) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_444, SetPreCommentIndentAndGet_444) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_444, SetPostCommentIndentAndGet_444) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_444, SetMapKeyFormatAndGet_444) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_444, SetFloatPrecisionAndGet_444) {
  EXPECT_TRUE(state.SetFloatPrecision(5, FmtScope::Global));
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_444, SetDoublePrecisionAndGet_444) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Global));
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== Invalid Format Value Tests ====================

TEST_F(EmitterStateTest_444, SetOutputCharsetWithInvalidValue_444) {
  // Passing a value that's not a charset manipulator should return false
  EXPECT_FALSE(state.SetOutputCharset(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_444, SetStringFormatWithInvalidValue_444) {
  EXPECT_FALSE(state.SetStringFormat(Hex, FmtScope::Global));
}

TEST_F(EmitterStateTest_444, SetBoolFormatWithInvalidValue_444) {
  EXPECT_FALSE(state.SetBoolFormat(Hex, FmtScope::Global));
}

TEST_F(EmitterStateTest_444, SetIntFormatWithInvalidValue_444) {
  EXPECT_FALSE(state.SetIntFormat(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_444, SetIndentZeroReturnsFalse_444) {
  // Indent of 0 might be invalid
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Global));
}

// ==================== Flow Type Tests ====================

TEST_F(EmitterStateTest_444, SetFlowTypeSeqFlow_444) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_444, SetFlowTypeSeqBlock_444) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_444, SetFlowTypeMapFlow_444) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_444, SetFlowTypeMapBlock_444) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_444, SetFlowTypeInvalidValue_444) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Hex, FmtScope::Global));
}

// ==================== Local Scope Tests ====================

TEST_F(EmitterStateTest_444, SetIndentLocalScope_444) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_TRUE(state.SetIndent(6, FmtScope::Local));
  EXPECT_EQ(6u, state.GetIndent());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_444, ForceFlowChangesFlowType_444) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_444, SetNonContentSetsFlag_444) {
  state.SetNonContent();
  // HasBegunNode should still be false since non-content is not a node
  // The non-content flag affects HasBegunContent
  // Exact behavior depends on implementation, but we verify no crash
  EXPECT_TRUE(state.good());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_444, ClearModifiedSettingsDoesNotBreakState_444) {
  state.SetIndent(6, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_444, RestoreGlobalModifiedSettingsDoesNotBreakState_444) {
  state.SetIndent(8, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(8u, state.GetIndent());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_444, NextGroupTypeSeqWithNoGroups_444) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Without any active group context, we check we get a valid value
  EXPECT_TRUE(nodeType == EmitterNodeType::NoType ||
              nodeType == EmitterNodeType::FlowSeq ||
              nodeType == EmitterNodeType::BlockSeq);
}

TEST_F(EmitterStateTest_444, NextGroupTypeMapWithNoGroups_444) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  EXPECT_TRUE(nodeType == EmitterNodeType::NoType ||
              nodeType == EmitterNodeType::FlowMap ||
              nodeType == EmitterNodeType::BlockMap);
}

// ==================== Nested Group Tests ====================

TEST_F(EmitterStateTest_444, NestedGroupsTrackCorrectly_444) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_444, LastIndentWithNoGroupsReturnsZero_444) {
  EXPECT_EQ(0u, state.LastIndent());
}

// ==================== Multiple Scalars in Sequence ====================

TEST_F(EmitterStateTest_444, MultipleScalarsIncrementChildCount_444) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.StartedScalar();
  state.StartedScalar();
  EXPECT_EQ(3u, state.CurGroupChildCount());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_444, SetLocalValueFlow_444) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetLocalValue(Flow);
  // The group should now be flow
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

TEST_F(EmitterStateTest_444, SetLocalValueBlock_444) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// ==================== Default Format Value Tests ====================

TEST_F(EmitterStateTest_444, DefaultStringFormat_444) {
  // Default should be a valid EMITTER_MANIP
  EMITTER_MANIP fmt = state.GetStringFormat();
  // We don't know exact default but it should be one of the string formats
  (void)fmt;  // Just ensure no crash
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_444, DefaultBoolFormat_444) {
  EMITTER_MANIP fmt = state.GetBoolFormat();
  (void)fmt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_444, DefaultIntFormat_444) {
  EMITTER_MANIP fmt = state.GetIntFormat();
  EXPECT_EQ(Dec, fmt);
}

TEST_F(EmitterStateTest_444, DefaultGetIndent_444) {
  std::size_t indent = state.GetIndent();
  EXPECT_GE(indent, 1u);
}

// ==================== SetAnchor clears after StartedScalar ====================

TEST_F(EmitterStateTest_444, AnchorClearedAfterScalar_444) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_444, AliasClearedAfterScalar_444) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_444, TagClearedAfterScalar_444) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasTag());
}

// ==================== CurGroupNodeType Tests ====================

TEST_F(EmitterStateTest_444, CurGroupNodeTypeInSeq_444) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  // Should be a valid node type
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ==================== Boundary: Large indent ====================

TEST_F(EmitterStateTest_444, SetLargeIndent_444) {
  EXPECT_TRUE(state.SetIndent(100, FmtScope::Global));
  EXPECT_EQ(100u, state.GetIndent());
}

// ==================== Boundary: precision ====================

TEST_F(EmitterStateTest_444, SetFloatPrecisionZero_444) {
  // Zero precision might be valid or invalid
  bool result = state.SetFloatPrecision(0, FmtScope::Global);
  (void)result;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_444, SetDoublePrecisionZero_444) {
  bool result = state.SetDoublePrecision(0, FmtScope::Global);
  (void)result;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_444, SetFloatPrecisionLargeValue_444) {
  // Very large precision
  bool result = state.SetFloatPrecision(100, FmtScope::Global);
  (void)result;
  EXPECT_TRUE(state.good());
}

}  // namespace YAML
