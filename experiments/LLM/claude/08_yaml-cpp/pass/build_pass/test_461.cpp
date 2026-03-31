#include "gtest/gtest.h"
#include "emitterstate.h"
#include "yaml-cpp/emittermanip.h"

namespace YAML {

class EmitterStateTest_461 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_461, InitialState_IsGood_461) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_461, InitialState_NoLastError_461) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_461, InitialState_NoAnchor_461) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_461, InitialState_NoAlias_461) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_461, InitialState_NoTag_461) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_461, InitialState_CurIndentIsZero_461) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_461, SetError_MarksNotGood_461) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_461, SetError_StoresErrorMessage_461) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_461, SetError_OnlyFirstErrorKept_461) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_461, SetAnchor_HasAnchorTrue_461) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_461, SetAlias_HasAliasTrue_461) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_461, SetTag_HasTagTrue_461) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Default Getters Tests ====================

TEST_F(EmitterStateTest_461, DefaultGetIndent_461) {
  std::size_t indent = state.GetIndent();
  EXPECT_GT(indent, 0u);
}

TEST_F(EmitterStateTest_461, DefaultGetPreCommentIndent_461) {
  std::size_t preComment = state.GetPreCommentIndent();
  EXPECT_GT(preComment, 0u);
}

TEST_F(EmitterStateTest_461, DefaultGetPostCommentIndent_461) {
  std::size_t postComment = state.GetPostCommentIndent();
  EXPECT_GT(postComment, 0u);
}

TEST_F(EmitterStateTest_461, DefaultGetFloatPrecision_461) {
  std::size_t fp = state.GetFloatPrecision();
  // Should have some reasonable default
  EXPECT_GT(fp, 0u);
}

TEST_F(EmitterStateTest_461, DefaultGetDoublePrecision_461) {
  std::size_t dp = state.GetDoublePrecision();
  EXPECT_GT(dp, 0u);
}

// ==================== SetIndent Tests ====================

TEST_F(EmitterStateTest_461, SetIndent_GlobalScope_461) {
  bool result = state.SetIndent(4, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_461, SetIndent_LocalScope_461) {
  bool result = state.SetIndent(6, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(6u, state.GetIndent());
}

TEST_F(EmitterStateTest_461, SetIndent_ZeroIsInvalid_461) {
  bool result = state.SetIndent(0, FmtScope::Global);
  // 0 indent may not be valid
  // We just check return value; if false, good may become false
  if (!result) {
    EXPECT_FALSE(state.good());
  }
}

// ==================== SetPreCommentIndent Tests ====================

TEST_F(EmitterStateTest_461, SetPreCommentIndent_GlobalScope_461) {
  bool result = state.SetPreCommentIndent(3, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_461, SetPreCommentIndent_LocalScope_461) {
  bool result = state.SetPreCommentIndent(5, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(5u, state.GetPreCommentIndent());
}

// ==================== SetPostCommentIndent Tests ====================

TEST_F(EmitterStateTest_461, SetPostCommentIndent_GlobalScope_461) {
  bool result = state.SetPostCommentIndent(2, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_461, SetPostCommentIndent_LocalScope_461) {
  bool result = state.SetPostCommentIndent(4, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(4u, state.GetPostCommentIndent());
}

// ==================== SetOutputCharset Tests ====================

TEST_F(EmitterStateTest_461, SetOutputCharset_UTF8_461) {
  bool result = state.SetOutputCharset(EmitNonAscii, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_461, SetOutputCharset_EscapeNonAscii_461) {
  bool result = state.SetOutputCharset(EscapeNonAscii, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_461, SetOutputCharset_InvalidValue_461) {
  // Passing an unrelated EMITTER_MANIP should fail
  bool result = state.SetOutputCharset(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetStringFormat Tests ====================

TEST_F(EmitterStateTest_461, SetStringFormat_SingleQuoted_461) {
  bool result = state.SetStringFormat(SingleQuoted, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_461, SetStringFormat_DoubleQuoted_461) {
  bool result = state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_461, SetStringFormat_Literal_461) {
  bool result = state.SetStringFormat(Literal, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Literal, state.GetStringFormat());
}

TEST_F(EmitterStateTest_461, SetStringFormat_InvalidValue_461) {
  bool result = state.SetStringFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetBoolFormat Tests ====================

TEST_F(EmitterStateTest_461, SetBoolFormat_TrueFalseBool_461) {
  bool result = state.SetBoolFormat(TrueFalseBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_461, SetBoolFormat_YesNoBool_461) {
  bool result = state.SetBoolFormat(YesNoBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_461, SetBoolFormat_OnOffBool_461) {
  bool result = state.SetBoolFormat(OnOffBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_461, SetBoolFormat_InvalidValue_461) {
  bool result = state.SetBoolFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetBoolLengthFormat Tests ====================

TEST_F(EmitterStateTest_461, SetBoolLengthFormat_ShortBool_461) {
  bool result = state.SetBoolLengthFormat(ShortBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_461, SetBoolLengthFormat_LongBool_461) {
  bool result = state.SetBoolLengthFormat(LongBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_461, SetBoolLengthFormat_InvalidValue_461) {
  bool result = state.SetBoolLengthFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetBoolCaseFormat Tests ====================

TEST_F(EmitterStateTest_461, SetBoolCaseFormat_UpperCase_461) {
  bool result = state.SetBoolCaseFormat(UpperCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_461, SetBoolCaseFormat_LowerCase_461) {
  bool result = state.SetBoolCaseFormat(LowerCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_461, SetBoolCaseFormat_CamelCase_461) {
  bool result = state.SetBoolCaseFormat(CamelCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_461, SetBoolCaseFormat_InvalidValue_461) {
  bool result = state.SetBoolCaseFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetNullFormat Tests ====================

TEST_F(EmitterStateTest_461, SetNullFormat_LowerNull_461) {
  bool result = state.SetNullFormat(LowerNull, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_461, SetNullFormat_TildeNull_461) {
  bool result = state.SetNullFormat(TildeNull, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_461, SetNullFormat_InvalidValue_461) {
  bool result = state.SetNullFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetIntFormat Tests ====================

TEST_F(EmitterStateTest_461, SetIntFormat_Dec_461) {
  bool result = state.SetIntFormat(Dec, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_461, SetIntFormat_Hex_461) {
  bool result = state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_461, SetIntFormat_Oct_461) {
  bool result = state.SetIntFormat(Oct, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_461, SetIntFormat_InvalidValue_461) {
  bool result = state.SetIntFormat(TrueFalseBool, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetFloatPrecision Tests ====================

TEST_F(EmitterStateTest_461, SetFloatPrecision_ValidValue_461) {
  bool result = state.SetFloatPrecision(5, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_461, SetDoublePrecision_ValidValue_461) {
  bool result = state.SetDoublePrecision(10, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== SetMapKeyFormat Tests ====================

TEST_F(EmitterStateTest_461, SetMapKeyFormat_LongKey_461) {
  bool result = state.SetMapKeyFormat(LongKey, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_461, SetMapKeyFormat_InvalidValue_461) {
  bool result = state.SetMapKeyFormat(Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetFlowType Tests ====================

TEST_F(EmitterStateTest_461, SetFlowType_SeqFlow_461) {
  bool result = state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_461, SetFlowType_MapBlock_461) {
  bool result = state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_461, SetFlowType_InvalidValue_461) {
  bool result = state.SetFlowType(GroupType::Seq, Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Doc Lifecycle Tests ====================

TEST_F(EmitterStateTest_461, StartedDoc_EndedDoc_Lifecycle_461) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Lifecycle Tests ====================

TEST_F(EmitterStateTest_461, StartedGroup_Seq_EndedGroup_461) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_461, StartedGroup_Map_EndedGroup_461) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_461, CurGroupChildCount_InitiallyZero_461) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_461, CurGroupLongKey_InitiallyFalse_461) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== Scalar Tests ====================

TEST_F(EmitterStateTest_461, StartedScalar_ClearsFlags_461) {
  state.SetAnchor();
  state.SetTag();
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
  state.EndedGroup(GroupType::Seq);
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_461, SetNonContent_HasBegunNode_461) {
  state.SetNonContent();
  // SetNonContent sets m_hasNonContent; HasBegunNode checks m_hasNonContent
  // The exact relationship is implementation detail, but we can check
  // that after setting non-content, HasBegunNode returns true
  EXPECT_TRUE(state.HasBegunNode());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_461, ClearModifiedSettings_RestoresLocalSettings_461) {
  std::size_t defaultIndent = state.GetIndent();
  state.SetIndent(8, FmtScope::Local);
  EXPECT_EQ(8u, state.GetIndent());
  state.ClearModifiedSettings();
  EXPECT_EQ(defaultIndent, state.GetIndent());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_461, RestoreGlobalModifiedSettings_461) {
  std::size_t defaultIndent = state.GetIndent();
  state.SetIndent(8, FmtScope::Global);
  EXPECT_EQ(8u, state.GetIndent());
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(defaultIndent, state.GetIndent());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_461, SetLocalValue_Flow_461) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetLocalValue(Flow);
  EXPECT_EQ(Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Seq);
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_461, ForceFlow_ChangesFlowType_461) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Seq);
}

// ==================== NestedGroups Tests ====================

TEST_F(EmitterStateTest_461, NestedGroups_InnerGroupType_461) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
}

// ==================== Multiple Scopes for Same Setting ====================

TEST_F(EmitterStateTest_461, GlobalThenLocal_LocalOverrides_461) {
  state.SetIndent(3, FmtScope::Global);
  EXPECT_EQ(3u, state.GetIndent());
  state.SetIndent(7, FmtScope::Local);
  EXPECT_EQ(7u, state.GetIndent());
  state.ClearModifiedSettings();
  EXPECT_EQ(3u, state.GetIndent());
}

// ==================== Boundary: Large Indent ====================

TEST_F(EmitterStateTest_461, SetIndent_LargeValue_461) {
  bool result = state.SetIndent(100, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(100u, state.GetIndent());
}

// ==================== Boundary: Indent of 1 ====================

TEST_F(EmitterStateTest_461, SetIndent_MinimumValid_461) {
  bool result = state.SetIndent(1, FmtScope::Global);
  // 1 might be valid minimum
  if (result) {
    EXPECT_EQ(1u, state.GetIndent());
  }
}

// ==================== Multiple Docs ====================

TEST_F(EmitterStateTest_461, MultipleDocs_461) {
  state.StartedDoc();
  state.EndedDoc();
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== HasBegunContent Tests ====================

TEST_F(EmitterStateTest_461, HasBegunContent_InitiallyFalse_461) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_461, SetLongKey_InGroup_461) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_461, LastIndent_WithNestedGroups_461) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  std::size_t outerIndent = state.CurGroupIndent();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(outerIndent, state.LastIndent());
  state.EndedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
}

}  // namespace YAML
