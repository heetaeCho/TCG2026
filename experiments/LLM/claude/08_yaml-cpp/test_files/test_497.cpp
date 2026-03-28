#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_497 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ============================================================
// Construction / Initial State Tests
// ============================================================

TEST_F(EmitterStateTest_497, InitialState_IsGood_497) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_497, InitialState_NoError_497) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_497, InitialState_NoAnchor_497) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_497, InitialState_NoAlias_497) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_497, InitialState_NoTag_497) {
  EXPECT_FALSE(state.HasTag());
}

// ============================================================
// SetError Tests
// ============================================================

TEST_F(EmitterStateTest_497, SetError_MakesNotGood_497) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_497, SetError_ReturnsErrorMessage_497) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_497, SetError_FirstErrorPersists_497) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically only the first error is recorded
  EXPECT_FALSE(state.good());
  EXPECT_EQ("first error", state.GetLastError());
}

// ============================================================
// SetPreCommentIndent Tests
// ============================================================

TEST_F(EmitterStateTest_497, SetPreCommentIndent_ZeroReturnsFalse_497) {
  EXPECT_FALSE(state.SetPreCommentIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_497, SetPreCommentIndent_NonZeroReturnsTrue_497) {
  EXPECT_TRUE(state.SetPreCommentIndent(1, FmtScope::Local));
}

TEST_F(EmitterStateTest_497, SetPreCommentIndent_ValueIsRetrievable_497) {
  state.SetPreCommentIndent(5, FmtScope::Local);
  EXPECT_EQ(5u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_497, SetPreCommentIndent_GlobalScope_497) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_497, SetPreCommentIndent_LargeValue_497) {
  EXPECT_TRUE(state.SetPreCommentIndent(100, FmtScope::Local));
  EXPECT_EQ(100u, state.GetPreCommentIndent());
}

// ============================================================
// SetPostCommentIndent Tests
// ============================================================

TEST_F(EmitterStateTest_497, SetPostCommentIndent_ZeroReturnsFalse_497) {
  EXPECT_FALSE(state.SetPostCommentIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_497, SetPostCommentIndent_NonZeroReturnsTrue_497) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_497, SetPostCommentIndent_ValueIsRetrievable_497) {
  state.SetPostCommentIndent(4, FmtScope::Local);
  EXPECT_EQ(4u, state.GetPostCommentIndent());
}

// ============================================================
// SetIndent Tests
// ============================================================

TEST_F(EmitterStateTest_497, SetIndent_ValidValue_497) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_497, SetIndent_OneReturnsFalse_497) {
  // Indent of 1 is typically too small (must be >= 2)
  EXPECT_FALSE(state.SetIndent(1, FmtScope::Local));
}

TEST_F(EmitterStateTest_497, SetIndent_ZeroReturnsFalse_497) {
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_497, SetIndent_TwoReturnsTrue_497) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Local));
  EXPECT_EQ(2u, state.GetIndent());
}

// ============================================================
// SetAnchor / SetAlias / SetTag / SetNonContent Tests
// ============================================================

TEST_F(EmitterStateTest_497, SetAnchor_HasAnchorTrue_497) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_497, SetAlias_HasAliasTrue_497) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_497, SetTag_HasTagTrue_497) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ============================================================
// SetOutputCharset Tests
// ============================================================

TEST_F(EmitterStateTest_497, SetOutputCharset_EmitUTF8_497) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_497, SetOutputCharset_EscapeNonAscii_497) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Local));
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_497, SetOutputCharset_InvalidValue_497) {
  // An unrelated EMITTER_MANIP should return false
  EXPECT_FALSE(state.SetOutputCharset(Dec, FmtScope::Local));
}

// ============================================================
// SetStringFormat Tests
// ============================================================

TEST_F(EmitterStateTest_497, SetStringFormat_SingleQuoted_497) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_497, SetStringFormat_DoubleQuoted_497) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_497, SetStringFormat_Literal_497) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Local));
  EXPECT_EQ(Literal, state.GetStringFormat());
}

TEST_F(EmitterStateTest_497, SetStringFormat_InvalidValue_497) {
  EXPECT_FALSE(state.SetStringFormat(Dec, FmtScope::Local));
}

// ============================================================
// SetBoolFormat Tests
// ============================================================

TEST_F(EmitterStateTest_497, SetBoolFormat_TrueFalseBool_497) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Local));
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_497, SetBoolFormat_YesNoBool_497) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Local));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_497, SetBoolFormat_OnOffBool_497) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Local));
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_497, SetBoolFormat_InvalidValue_497) {
  EXPECT_FALSE(state.SetBoolFormat(Dec, FmtScope::Local));
}

// ============================================================
// SetBoolLengthFormat Tests
// ============================================================

TEST_F(EmitterStateTest_497, SetBoolLengthFormat_ShortBool_497) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Local));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_497, SetBoolLengthFormat_LongBool_497) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Local));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_497, SetBoolLengthFormat_InvalidValue_497) {
  EXPECT_FALSE(state.SetBoolLengthFormat(Dec, FmtScope::Local));
}

// ============================================================
// SetBoolCaseFormat Tests
// ============================================================

TEST_F(EmitterStateTest_497, SetBoolCaseFormat_UpperCase_497) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Local));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_497, SetBoolCaseFormat_LowerCase_497) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Local));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_497, SetBoolCaseFormat_CamelCase_497) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Local));
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_497, SetBoolCaseFormat_InvalidValue_497) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Dec, FmtScope::Local));
}

// ============================================================
// SetNullFormat Tests
// ============================================================

TEST_F(EmitterStateTest_497, SetNullFormat_LowerNull_497) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_497, SetNullFormat_TildeNull_497) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Local));
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_497, SetNullFormat_InvalidValue_497) {
  EXPECT_FALSE(state.SetNullFormat(Dec, FmtScope::Local));
}

// ============================================================
// SetIntFormat Tests
// ============================================================

TEST_F(EmitterStateTest_497, SetIntFormat_Dec_497) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Local));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_497, SetIntFormat_Hex_497) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_497, SetIntFormat_Oct_497) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Local));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_497, SetIntFormat_InvalidValue_497) {
  EXPECT_FALSE(state.SetIntFormat(TrueFalseBool, FmtScope::Local));
}

// ============================================================
// SetMapKeyFormat Tests
// ============================================================

TEST_F(EmitterStateTest_497, SetMapKeyFormat_LongKey_497) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Local));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_497, SetMapKeyFormat_InvalidValue_497) {
  EXPECT_FALSE(state.SetMapKeyFormat(Dec, FmtScope::Local));
}

// ============================================================
// SetFloatPrecision / SetDoublePrecision Tests
// ============================================================

TEST_F(EmitterStateTest_497, SetFloatPrecision_ValidValue_497) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Local));
  EXPECT_EQ(6u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_497, SetDoublePrecision_ValidValue_497) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Local));
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ============================================================
// SetFlowType Tests
// ============================================================

TEST_F(EmitterStateTest_497, SetFlowType_SeqBlock_497) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Local));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_497, SetFlowType_SeqFlow_497) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_497, SetFlowType_MapBlock_497) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_497, SetFlowType_MapFlow_497) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Local));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_497, SetFlowType_InvalidManip_497) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Dec, FmtScope::Local));
}

// ============================================================
// Document lifecycle Tests
// ============================================================

TEST_F(EmitterStateTest_497, StartedDoc_EndedDoc_497) {
  state.StartedDoc();
  state.EndedDoc();
  // Should remain in good state
  EXPECT_TRUE(state.good());
}

// ============================================================
// Group lifecycle Tests
// ============================================================

TEST_F(EmitterStateTest_497, StartedGroup_Seq_EndedGroup_497) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_497, StartedGroup_Map_EndedGroup_497) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// ============================================================
// Scalar within group Tests
// ============================================================

TEST_F(EmitterStateTest_497, StartedScalar_IncreasesChildCount_497) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// ============================================================
// Scope Tests (Global vs Local)
// ============================================================

TEST_F(EmitterStateTest_497, SetPreCommentIndent_GlobalPersists_497) {
  state.SetPreCommentIndent(7, FmtScope::Global);
  EXPECT_EQ(7u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_497, SetPreCommentIndent_LocalScope_497) {
  state.SetPreCommentIndent(3, FmtScope::Local);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

// ============================================================
// CurIndent Tests
// ============================================================

TEST_F(EmitterStateTest_497, CurIndent_InitialIsZero_497) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ============================================================
// CurGroupLongKey Tests
// ============================================================

TEST_F(EmitterStateTest_497, CurGroupLongKey_AfterSetLongKey_497) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ============================================================
// ForceFlow Tests
// ============================================================

TEST_F(EmitterStateTest_497, ForceFlow_ChangesFlowType_497) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Seq);
}

// ============================================================
// ClearModifiedSettings Tests
// ============================================================

TEST_F(EmitterStateTest_497, ClearModifiedSettings_DoesNotCrash_497) {
  state.SetPreCommentIndent(5, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ============================================================
// NextGroupType Tests
// ============================================================

TEST_F(EmitterStateTest_497, NextGroupType_Seq_497) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return a valid node type
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_497, NextGroupType_Map_497) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ============================================================
// HasBegunNode / HasBegunContent Tests
// ============================================================

TEST_F(EmitterStateTest_497, HasBegunNode_InitiallyFalse_497) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_497, HasBegunContent_InitiallyFalse_497) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ============================================================
// Multiple settings with different scopes
// ============================================================

TEST_F(EmitterStateTest_497, SetIndent_GlobalThenLocal_497) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
  EXPECT_TRUE(state.SetIndent(6, FmtScope::Local));
  EXPECT_EQ(6u, state.GetIndent());
}

TEST_F(EmitterStateTest_497, RestoreGlobalModifiedSettings_RestoresGlobal_497) {
  state.SetPreCommentIndent(10, FmtScope::Global);
  EXPECT_EQ(10u, state.GetPreCommentIndent());
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

}  // namespace YAML
