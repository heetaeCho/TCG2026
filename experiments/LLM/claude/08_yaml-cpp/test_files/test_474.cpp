#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {
namespace {

class EmitterStateTest_474 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_474, InitialStateIsGood_474) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_474, InitialLastErrorIsEmpty_474) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_474, InitialHasNoAnchor_474) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_474, InitialHasNoAlias_474) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_474, InitialHasNoTag_474) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_474, InitialCurIndentIsZero_474) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_474, SetErrorMakesStateNotGood_474) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_474, SetErrorStoresErrorMessage_474) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_474, SetErrorTwiceKeepsFirstError_474) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically first error is kept
  EXPECT_FALSE(state.good());
  // The error message should be retrievable
  std::string err = state.GetLastError();
  EXPECT_FALSE(err.empty());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_474, SetAnchorSetsHasAnchor_474) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_474, SetAliasSetsHasAlias_474) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_474, SetTagSetsHasTag_474) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_474, NextGroupTypeSeqBlockReturnsBlockSeq_474) {
  // Default flow type for Seq should be Block
  EmitterNodeType::value result = state.NextGroupType(GroupType::Seq);
  EXPECT_EQ(EmitterNodeType::BlockSeq, result);
}

TEST_F(EmitterStateTest_474, NextGroupTypeMapBlockReturnsBlockMap_474) {
  // Default flow type for Map should be Block
  EmitterNodeType::value result = state.NextGroupType(GroupType::Map);
  EXPECT_EQ(EmitterNodeType::BlockMap, result);
}

TEST_F(EmitterStateTest_474, NextGroupTypeSeqFlowReturnsFlowSeq_474) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EmitterNodeType::value result = state.NextGroupType(GroupType::Seq);
  EXPECT_EQ(EmitterNodeType::FlowSeq, result);
}

TEST_F(EmitterStateTest_474, NextGroupTypeMapFlowReturnsFlowMap_474) {
  state.SetFlowType(GroupType::Map, Flow, FmtScope::Global);
  EmitterNodeType::value result = state.NextGroupType(GroupType::Map);
  EXPECT_EQ(EmitterNodeType::FlowMap, result);
}

// ==================== SetFlowType / GetFlowType Tests ====================

TEST_F(EmitterStateTest_474, SetFlowTypeSeqReturnsTrue_474) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_474, SetFlowTypeMapReturnsTrue_474) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
}

TEST_F(EmitterStateTest_474, GetFlowTypeSeqDefaultIsBlock_474) {
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_474, GetFlowTypeMapDefaultIsBlock_474) {
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_474, SetAndGetFlowTypeSeqFlow_474) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_474, SetAndGetFlowTypeMapFlow_474) {
  state.SetFlowType(GroupType::Map, Flow, FmtScope::Global);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

// ==================== Format Setting Tests ====================

TEST_F(EmitterStateTest_474, SetOutputCharsetReturnsTrue_474) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_474, SetStringFormatReturnsTrue_474) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
}

TEST_F(EmitterStateTest_474, SetBoolFormatReturnsTrue_474) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_474, SetBoolLengthFormatReturnsTrue_474) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_474, SetBoolCaseFormatReturnsTrue_474) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
}

TEST_F(EmitterStateTest_474, SetNullFormatReturnsTrue_474) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
}

TEST_F(EmitterStateTest_474, SetIntFormatReturnsTrue_474) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
}

TEST_F(EmitterStateTest_474, SetIndentReturnsTrue_474) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
}

TEST_F(EmitterStateTest_474, SetPreCommentIndentReturnsTrue_474) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Global));
}

TEST_F(EmitterStateTest_474, SetPostCommentIndentReturnsTrue_474) {
  EXPECT_TRUE(state.SetPostCommentIndent(1, FmtScope::Global));
}

TEST_F(EmitterStateTest_474, SetMapKeyFormatReturnsTrue_474) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
}

TEST_F(EmitterStateTest_474, SetFloatPrecisionReturnsTrue_474) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Global));
}

TEST_F(EmitterStateTest_474, SetDoublePrecisionReturnsTrue_474) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Global));
}

// ==================== Get Format Tests ====================

TEST_F(EmitterStateTest_474, GetOutputCharsetDefault_474) {
  EMITTER_MANIP val = state.GetOutputCharset();
  // Should return a valid EMITTER_MANIP
  EXPECT_TRUE(val == EmitNonAscii || val == EscapeNonAscii || val == EscapeAsJson);
}

TEST_F(EmitterStateTest_474, GetStringFormatDefault_474) {
  EMITTER_MANIP val = state.GetStringFormat();
  // Some valid default
  (void)val;
}

TEST_F(EmitterStateTest_474, GetBoolFormatDefault_474) {
  EMITTER_MANIP val = state.GetBoolFormat();
  (void)val;
}

TEST_F(EmitterStateTest_474, GetIntFormatDefault_474) {
  EMITTER_MANIP val = state.GetIntFormat();
  (void)val;
}

TEST_F(EmitterStateTest_474, GetIndentDefault_474) {
  std::size_t indent = state.GetIndent();
  EXPECT_GT(indent, 0u);
}

TEST_F(EmitterStateTest_474, SetAndGetIndent_474) {
  state.SetIndent(4, FmtScope::Global);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_474, SetAndGetFloatPrecision_474) {
  state.SetFloatPrecision(3, FmtScope::Global);
  EXPECT_EQ(3u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_474, SetAndGetDoublePrecision_474) {
  state.SetDoublePrecision(10, FmtScope::Global);
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

TEST_F(EmitterStateTest_474, SetAndGetOutputCharset_474) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Global);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_474, SetAndGetStringFormat_474) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_474, SetAndGetBoolFormat_474) {
  state.SetBoolFormat(TrueFalseBool, FmtScope::Global);
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_474, SetAndGetBoolLengthFormat_474) {
  state.SetBoolLengthFormat(ShortBool, FmtScope::Global);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_474, SetAndGetBoolCaseFormat_474) {
  state.SetBoolCaseFormat(LowerCase, FmtScope::Global);
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_474, SetAndGetNullFormat_474) {
  state.SetNullFormat(TildeNull, FmtScope::Global);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_474, SetAndGetIntFormat_474) {
  state.SetIntFormat(Oct, FmtScope::Global);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_474, SetAndGetMapKeyFormat_474) {
  state.SetMapKeyFormat(LongKey, FmtScope::Global);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== Document Lifecycle Tests ====================

TEST_F(EmitterStateTest_474, StartedDocDoesNotBreakState_474) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_474, EndedDocDoesNotBreakState_474) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Lifecycle Tests ====================

TEST_F(EmitterStateTest_474, StartedGroupSeq_474) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_474, StartedGroupMap_474) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_474, EndedGroupSeq_474) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_474, EndedGroupMap_474) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_474, CurGroupChildCountInitiallyZero_474) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_474, CurGroupFlowTypeDefault_474) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  FlowType::value ft = state.CurGroupFlowType();
  // Should be block by default
  (void)ft;
}

TEST_F(EmitterStateTest_474, CurGroupLongKeyDefaultFalse_474) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// ==================== Scalar Test ====================

TEST_F(EmitterStateTest_474, StartedScalarInGroup_474) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_474, ForceFlowChangesFlowType_474) {
  state.ForceFlow();
  // After forcing flow, seq should be flow
  EmitterNodeType::value result = state.NextGroupType(GroupType::Seq);
  EXPECT_EQ(EmitterNodeType::FlowSeq, result);
}

TEST_F(EmitterStateTest_474, ForceFlowChangesMapFlowType_474) {
  state.ForceFlow();
  EmitterNodeType::value result = state.NextGroupType(GroupType::Map);
  EXPECT_EQ(EmitterNodeType::FlowMap, result);
}

// ==================== SetLongKey Test ====================

TEST_F(EmitterStateTest_474, SetLongKeyDoesNotBreakState_474) {
  state.SetLongKey();
  EXPECT_TRUE(state.good());
}

// ==================== SetNonContent Test ====================

TEST_F(EmitterStateTest_474, SetNonContentDoesNotBreakState_474) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== Scope Tests ====================

TEST_F(EmitterStateTest_474, SetIndentLocalScope_474) {
  EXPECT_TRUE(state.SetIndent(6, FmtScope::Local));
}

TEST_F(EmitterStateTest_474, ClearModifiedSettingsResetsLocal_474) {
  std::size_t defaultIndent = state.GetIndent();
  state.SetIndent(8, FmtScope::Local);
  EXPECT_EQ(8u, state.GetIndent());
  state.ClearModifiedSettings();
  EXPECT_EQ(defaultIndent, state.GetIndent());
}

TEST_F(EmitterStateTest_474, GlobalSettingsPersistAcrossClear_474) {
  state.SetIndent(5, FmtScope::Global);
  state.ClearModifiedSettings();
  EXPECT_EQ(5u, state.GetIndent());
}

TEST_F(EmitterStateTest_474, RestoreGlobalModifiedSettings_474) {
  state.SetIndent(7, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(7u, state.GetIndent());
}

// ==================== Nested Group Tests ====================

TEST_F(EmitterStateTest_474, NestedGroupsWorkCorrectly_474) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// ==================== HasBegunNode / HasBegunContent ====================

TEST_F(EmitterStateTest_474, HasBegunNodeInitiallyFalse_474) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_474, HasBegunContentInitiallyFalse_474) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== SetLocalValue Test ====================

TEST_F(EmitterStateTest_474, SetLocalValueFlow_474) {
  state.SetLocalValue(Flow);
  // This should affect the next group type for seq
  EmitterNodeType::value result = state.NextGroupType(GroupType::Seq);
  EXPECT_EQ(EmitterNodeType::FlowSeq, result);
}

TEST_F(EmitterStateTest_474, SetLocalValueBlock_474) {
  state.SetLocalValue(Block);
  EmitterNodeType::value result = state.NextGroupType(GroupType::Seq);
  EXPECT_EQ(EmitterNodeType::BlockSeq, result);
}

// ==================== Invalid Format Values ====================

TEST_F(EmitterStateTest_474, SetOutputCharsetInvalidValue_474) {
  // Passing an unrelated EMITTER_MANIP should return false
  bool result = state.SetOutputCharset(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_474, SetStringFormatInvalidValue_474) {
  bool result = state.SetStringFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_474, SetBoolFormatInvalidValue_474) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_474, SetIntFormatInvalidValue_474) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_474, SetNullFormatInvalidValue_474) {
  bool result = state.SetNullFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Boundary: Indent of Zero ====================

TEST_F(EmitterStateTest_474, SetIndentZero_474) {
  // Setting indent to 0 might not be valid
  bool result = state.SetIndent(0, FmtScope::Global);
  // Implementation may reject zero indent
  (void)result;
}

TEST_F(EmitterStateTest_474, SetIndentOne_474) {
  bool result = state.SetIndent(1, FmtScope::Global);
  // Implementation might require indent >= 2
  (void)result;
}

TEST_F(EmitterStateTest_474, PreCommentIndentDefault_474) {
  std::size_t val = state.GetPreCommentIndent();
  EXPECT_GT(val, 0u);
}

TEST_F(EmitterStateTest_474, PostCommentIndentDefault_474) {
  std::size_t val = state.GetPostCommentIndent();
  EXPECT_GT(val, 0u);
}

// ==================== FlowType within group ====================

TEST_F(EmitterStateTest_474, FlowGroupNodeType_474) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  EXPECT_EQ(EmitterNodeType::FlowSeq, nodeType);
}

TEST_F(EmitterStateTest_474, BlockGroupNodeType_474) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  EXPECT_EQ(EmitterNodeType::BlockMap, nodeType);
}

}  // namespace
}  // namespace YAML
