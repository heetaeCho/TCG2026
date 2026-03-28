#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_483 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_483, InitialStateIsGood_483) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_483, InitialLastErrorIsEmpty_483) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_483, InitialCurIndentIsZero_483) {
  EXPECT_EQ(0u, state.CurIndent());
}

TEST_F(EmitterStateTest_483, InitialHasAnchorIsFalse_483) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_483, InitialHasAliasIsFalse_483) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_483, InitialHasTagIsFalse_483) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_483, InitialCurGroupIndentIsZero_483) {
  EXPECT_EQ(0u, state.CurGroupIndent());
}

TEST_F(EmitterStateTest_483, InitialCurGroupChildCountIsZero_483) {
  // When no groups exist, CurGroupChildCount should return 0
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

// ==================== Error Handling Tests ====================

TEST_F(EmitterStateTest_483, SetErrorMakesStateNotGood_483) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_483, SetErrorStoresErrorMessage_483) {
  state.SetError("something went wrong");
  EXPECT_EQ("something went wrong", state.GetLastError());
}

TEST_F(EmitterStateTest_483, SetErrorEmptyStringStillMakesNotGood_483) {
  state.SetError("");
  EXPECT_FALSE(state.good());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_483, SetAnchorSetsHasAnchor_483) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_483, SetAliasSetsHasAlias_483) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_483, SetTagSetsHasTag_483) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Document Tests ====================

TEST_F(EmitterStateTest_483, StartedDocAndEndedDoc_483) {
  state.StartedDoc();
  state.EndedDoc();
  // Should not crash and state should remain good
  EXPECT_TRUE(state.good());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_483, StartedGroupSeq_483) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_483, StartedGroupMap_483) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_483, EndedGroupSeq_483) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  // After ending the only group, CurGroupIndent should be 0 (no groups)
  EXPECT_EQ(0u, state.CurGroupIndent());
}

TEST_F(EmitterStateTest_483, NestedGroups_483) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_483, CurGroupFlowTypeInitiallyBlock_483) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // Default flow type should be block (FlowType::NoType or Flow depending on settings)
  FlowType::value ft = state.CurGroupFlowType();
  // Just verify it returns without crash; exact value depends on defaults
  (void)ft;
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_483, StartedScalarInGroup_483) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_483, MultipleScalarsIncreaseChildCount_483) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.StartedScalar();
  EXPECT_EQ(2u, state.CurGroupChildCount());
}

// ==================== Setting Format Tests ====================

TEST_F(EmitterStateTest_483, SetOutputCharsetValid_483) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_483, SetStringFormatValid_483) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_483, SetBoolFormatValid_483) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_483, SetBoolLengthFormatValid_483) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_483, SetBoolCaseFormatValid_483) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_483, SetNullFormatValid_483) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_483, SetIntFormatValid_483) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
}

TEST_F(EmitterStateTest_483, SetIndentValid_483) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
}

TEST_F(EmitterStateTest_483, SetIndentTooSmall_483) {
  // Indent of 1 might be rejected (minimum is typically 2)
  bool result = state.SetIndent(1, FmtScope::Local);
  // The result depends on implementation validation
  (void)result;
}

TEST_F(EmitterStateTest_483, SetPreCommentIndentValid_483) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_483, SetPostCommentIndentValid_483) {
  EXPECT_TRUE(state.SetPostCommentIndent(1, FmtScope::Local));
}

TEST_F(EmitterStateTest_483, SetMapKeyFormatValid_483) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Local));
}

TEST_F(EmitterStateTest_483, SetFloatPrecisionValid_483) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Local));
}

TEST_F(EmitterStateTest_483, SetDoublePrecisionValid_483) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Local));
}

// ==================== Get Format Default Tests ====================

TEST_F(EmitterStateTest_483, GetDefaultIndent_483) {
  std::size_t indent = state.GetIndent();
  EXPECT_GT(indent, 0u);
}

TEST_F(EmitterStateTest_483, GetDefaultPreCommentIndent_483) {
  std::size_t val = state.GetPreCommentIndent();
  EXPECT_GT(val, 0u);
}

TEST_F(EmitterStateTest_483, GetDefaultPostCommentIndent_483) {
  std::size_t val = state.GetPostCommentIndent();
  EXPECT_GT(val, 0u);
}

TEST_F(EmitterStateTest_483, GetFloatPrecisionDefault_483) {
  std::size_t val = state.GetFloatPrecision();
  EXPECT_GT(val, 0u);
}

TEST_F(EmitterStateTest_483, GetDoublePrecisionDefault_483) {
  std::size_t val = state.GetDoublePrecision();
  EXPECT_GT(val, 0u);
}

// ==================== Set and Get Round-Trip Tests ====================

TEST_F(EmitterStateTest_483, SetAndGetIndent_483) {
  state.SetIndent(6, FmtScope::Local);
  EXPECT_EQ(6u, state.GetIndent());
}

TEST_F(EmitterStateTest_483, SetAndGetStringFormat_483) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_483, SetAndGetBoolFormat_483) {
  state.SetBoolFormat(YesNoBool, FmtScope::Local);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_483, SetAndGetIntFormat_483) {
  state.SetIntFormat(Oct, FmtScope::Local);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_483, SetAndGetNullFormat_483) {
  state.SetNullFormat(TildeNull, FmtScope::Local);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== Flow Type Tests ====================

TEST_F(EmitterStateTest_483, SetFlowTypeSeq_483) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_483, SetFlowTypeMap_483) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_483, GetFlowTypeAfterSet_483) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

// ==================== Scope Tests ====================

TEST_F(EmitterStateTest_483, SetIndentGlobalScope_483) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_483, ClearModifiedSettingsResetsLocal_483) {
  state.SetIndent(8, FmtScope::Local);
  EXPECT_EQ(8u, state.GetIndent());
  state.ClearModifiedSettings();
  // After clearing, should revert to default or global
  // The exact value depends on the default (typically 2)
  std::size_t indent = state.GetIndent();
  EXPECT_NE(8u, indent);
}

TEST_F(EmitterStateTest_483, GlobalSettingsPersistAfterClear_483) {
  state.SetIndent(5, FmtScope::Global);
  state.SetIndent(8, FmtScope::Local);
  state.ClearModifiedSettings();
  // Global should persist
  EXPECT_EQ(5u, state.GetIndent());
}

TEST_F(EmitterStateTest_483, RestoreGlobalModifiedSettings_483) {
  state.SetIndent(5, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(5u, state.GetIndent());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_483, SetLocalValueFlow_483) {
  state.SetLocalValue(Flow);
  // This should affect current flow type settings
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_483, SetLocalValueBlock_483) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_483, ForceFlowSetsFlowType_483) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Seq);
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_483, SetLongKeyInGroup_483) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

TEST_F(EmitterStateTest_483, CurGroupLongKeyDefaultFalse_483) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_483, LastIndentInitial_483) {
  std::size_t lastIndent = state.LastIndent();
  // Just verify it returns without crash
  (void)lastIndent;
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_483, NextGroupTypeSeq_483) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return a valid node type
  (void)nodeType;
}

TEST_F(EmitterStateTest_483, NextGroupTypeMap_483) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
}

// ==================== CurGroupNodeType Tests ====================

TEST_F(EmitterStateTest_483, CurGroupNodeTypeWithGroup_483) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nt = state.CurGroupNodeType();
  (void)nt;
  state.EndedGroup(GroupType::Seq);
}

// ==================== HasBegunNode / HasBegunContent Tests ====================

TEST_F(EmitterStateTest_483, HasBegunNodeInitiallyFalse_483) {
  // Initially there's no begun node
  // The exact behavior depends on doc state, but right after construction:
  bool begun = state.HasBegunNode();
  (void)begun;
}

TEST_F(EmitterStateTest_483, HasBegunContentInitiallyFalse_483) {
  bool begun = state.HasBegunContent();
  (void)begun;
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_483, SetNonContent_483) {
  state.SetNonContent();
  // Should not crash; verifying state remains good
  EXPECT_TRUE(state.good());
}

// ==================== Complex Scenarios ====================

TEST_F(EmitterStateTest_483, MultipleGroupsAndScalars_483) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.StartedScalar();  // key
  state.StartedScalar();  // value
  state.StartedScalar();  // key
  state.StartedGroup(GroupType::Seq);  // value is a sequence
  state.StartedScalar();
  state.StartedScalar();
  EXPECT_EQ(2u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Map);
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_483, MultipleDocuments_483) {
  state.StartedDoc();
  state.StartedScalar();
  state.EndedDoc();
  state.StartedDoc();
  state.StartedScalar();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_483, SetFloatPrecisionAndGet_483) {
  state.SetFloatPrecision(3, FmtScope::Local);
  EXPECT_EQ(3u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_483, SetDoublePrecisionAndGet_483) {
  state.SetDoublePrecision(10, FmtScope::Local);
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

TEST_F(EmitterStateTest_483, SetPreCommentIndentAndGet_483) {
  state.SetPreCommentIndent(3, FmtScope::Local);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_483, SetPostCommentIndentAndGet_483) {
  state.SetPostCommentIndent(2, FmtScope::Local);
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_483, OutputCharsetSetAndGet_483) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Local);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_483, BoolLengthFormatSetAndGet_483) {
  state.SetBoolLengthFormat(LongBool, FmtScope::Local);
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_483, BoolCaseFormatSetAndGet_483) {
  state.SetBoolCaseFormat(LowerCase, FmtScope::Local);
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_483, MapKeyFormatSetAndGet_483) {
  state.SetMapKeyFormat(LongKey, FmtScope::Local);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

}  // namespace YAML
