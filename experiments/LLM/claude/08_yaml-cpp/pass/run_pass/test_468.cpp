#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {
namespace {

class EmitterStateTest_468 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_468, InitialState_IsGood_468) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_468, InitialState_NoError_468) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_468, InitialState_HasNoAnchor_468) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_468, InitialState_HasNoAlias_468) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_468, InitialState_HasNoTag_468) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_468, InitialState_HasNotBegunNode_468) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_468, InitialState_HasNotBegunContent_468) {
  EXPECT_FALSE(state.HasBegunContent());
}

TEST_F(EmitterStateTest_468, InitialState_CurIndentIsZero_468) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_468, SetError_MakesNotGood_468) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_468, SetError_StoresErrorMessage_468) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_468, SetError_FirstErrorSticks_468) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically first error is preserved
  EXPECT_FALSE(state.good());
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== SetAnchor Tests ====================

TEST_F(EmitterStateTest_468, SetAnchor_SetsHasAnchor_468) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

// ==================== SetAlias Tests ====================

TEST_F(EmitterStateTest_468, SetAlias_SetsHasAlias_468) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

// ==================== SetTag Tests ====================

TEST_F(EmitterStateTest_468, SetTag_SetsHasTag_468) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_468, SetNonContent_AffectsHasBegunContent_468) {
  state.SetNonContent();
  // After SetNonContent, HasBegunNode should be true but HasBegunContent false
  EXPECT_TRUE(state.HasBegunNode());
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== StartedDoc / EndedDoc Tests ====================

TEST_F(EmitterStateTest_468, StartedDoc_468) {
  state.StartedDoc();
  // Should not cause error
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_468, EndedDoc_468) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== StartedScalar Tests ====================

TEST_F(EmitterStateTest_468, StartedScalar_WithinGroup_468) {
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_468, StartedGroup_Seq_468) {
  state.StartedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_468, StartedGroup_Map_468) {
  state.StartedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_468, EndedGroup_Seq_468) {
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_468, EndedGroup_Map_468) {
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_468, CurGroupChildCount_InitiallyZero_468) {
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_468, CurGroupChildCount_IncreasesAfterScalar_468) {
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_468, CurGroupLongKey_DefaultFalse_468) {
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_468, SetLongKey_MakesCurGroupLongKeyTrue_468) {
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_468, CurGroupIndent_468) {
  state.StartedGroup(GroupType::Seq);
  std::size_t indent = state.CurGroupIndent();
  // Just verify it's accessible and doesn't crash
  (void)indent;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_468, CurGroupFlowType_468) {
  state.StartedGroup(GroupType::Seq);
  FlowType::value ft = state.CurGroupFlowType();
  (void)ft;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_468, CurGroupNodeType_468) {
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nt = state.CurGroupNodeType();
  (void)nt;
  EXPECT_TRUE(state.good());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_468, NextGroupType_Seq_468) {
  EmitterNodeType::value ngt = state.NextGroupType(GroupType::Seq);
  (void)ngt;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_468, NextGroupType_Map_468) {
  EmitterNodeType::value ngt = state.NextGroupType(GroupType::Map);
  (void)ngt;
  EXPECT_TRUE(state.good());
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_468, LastIndent_InitiallyZero_468) {
  EXPECT_EQ(0u, state.LastIndent());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_468, ForceFlow_InGroup_468) {
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== Setting Format Tests ====================

TEST_F(EmitterStateTest_468, SetOutputCharset_ValidValue_468) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_468, SetOutputCharset_UTF8_468) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_468, GetOutputCharset_Default_468) {
  EMITTER_MANIP charset = state.GetOutputCharset();
  (void)charset;
  // Just ensure it returns without error
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_468, SetStringFormat_SingleQuoted_468) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_468, SetStringFormat_DoubleQuoted_468) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_468, SetStringFormat_Literal_468) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Global));
  EXPECT_EQ(Literal, state.GetStringFormat());
}

TEST_F(EmitterStateTest_468, SetBoolFormat_YesNoBool_468) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_468, SetBoolFormat_TrueFalseBool_468) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_468, SetBoolFormat_OnOffBool_468) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Global));
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_468, SetBoolLengthFormat_ShortBool_468) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_468, SetBoolLengthFormat_LongBool_468) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_468, SetBoolCaseFormat_UpperCase_468) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_468, SetBoolCaseFormat_LowerCase_468) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_468, SetBoolCaseFormat_CamelCase_468) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_468, SetNullFormat_LowerNull_468) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_468, SetNullFormat_TildeNull_468) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Global));
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_468, SetIntFormat_Dec_468) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_468, SetIntFormat_Hex_468) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_468, SetIntFormat_Oct_468) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_468, SetIndent_ValidValue_468) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_468, SetIndent_MinValue_468) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetIndent());
}

TEST_F(EmitterStateTest_468, SetIndent_InvalidValueTooSmall_468) {
  // Indent of 1 or 0 might be rejected
  bool result = state.SetIndent(0, FmtScope::Global);
  // If it fails, the state should still be good but return false
  (void)result;
}

TEST_F(EmitterStateTest_468, SetPreCommentIndent_468) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_468, SetPostCommentIndent_468) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_468, SetMapKeyFormat_LongKey_468) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_468, SetFloatPrecision_468) {
  EXPECT_TRUE(state.SetFloatPrecision(5, FmtScope::Global));
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_468, SetDoublePrecision_468) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Global));
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== FlowType Setting Tests ====================

TEST_F(EmitterStateTest_468, SetFlowType_SeqFlow_468) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_468, SetFlowType_SeqBlock_468) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_468, SetFlowType_MapFlow_468) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_468, SetFlowType_MapBlock_468) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== Scope Tests ====================

TEST_F(EmitterStateTest_468, SetStringFormat_LocalScope_468) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_468, ClearModifiedSettings_468) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  state.ClearModifiedSettings();
  // After clearing local modifications, should revert to default
  // The default string format might not be DoubleQuoted
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_468, RestoreGlobalModifiedSettings_468) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_468, SetLocalValue_Flow_468) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_468, SetLocalValue_Block_468) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// ==================== Anchor/Alias/Tag Reset After StartedScalar ====================

TEST_F(EmitterStateTest_468, AnchorResetAfterStartedScalar_468) {
  state.StartedGroup(GroupType::Seq);
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_468, AliasResetAfterStartedScalar_468) {
  state.StartedGroup(GroupType::Seq);
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_468, TagResetAfterStartedScalar_468) {
  state.StartedGroup(GroupType::Seq);
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasTag());
}

// ==================== Nested Groups ====================

TEST_F(EmitterStateTest_468, NestedGroups_468) {
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_468, NestedGroups_ChildCount_468) {
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
  state.StartedScalar();
  EXPECT_EQ(2u, state.CurGroupChildCount());
}

// ==================== Invalid Format Tests ====================

TEST_F(EmitterStateTest_468, SetOutputCharset_InvalidValue_468) {
  // Passing an unrelated EMITTER_MANIP should return false
  bool result = state.SetOutputCharset(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_468, SetStringFormat_InvalidValue_468) {
  bool result = state.SetStringFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_468, SetBoolFormat_InvalidValue_468) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_468, SetIntFormat_InvalidValue_468) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_468, SetNullFormat_InvalidValue_468) {
  bool result = state.SetNullFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Multiple Doc Tests ====================

TEST_F(EmitterStateTest_468, MultipleDocs_468) {
  state.StartedDoc();
  state.EndedDoc();
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== HasBegunNode After SetAnchor ====================

TEST_F(EmitterStateTest_468, HasBegunNode_AfterSetAnchor_468) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_468, HasBegunNode_AfterSetTag_468) {
  state.SetTag();
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_468, HasBegunNode_AfterSetAlias_468) {
  state.SetAlias();
  EXPECT_TRUE(state.HasBegunNode());
}

// ==================== HasBegunContent Tests ====================

TEST_F(EmitterStateTest_468, HasBegunContent_AfterStartedScalar_468) {
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_TRUE(state.HasBegunContent());
}

TEST_F(EmitterStateTest_468, HasBegunContent_AfterSetAnchorOnly_468) {
  state.SetAnchor();
  // Anchor alone is non-content
  EXPECT_FALSE(state.HasBegunContent());
}

}  // namespace
}  // namespace YAML
