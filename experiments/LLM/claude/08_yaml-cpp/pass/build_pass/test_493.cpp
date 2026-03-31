#include <gtest/gtest.h>
#include "yaml-cpp/emittermanip.h"
#include "emitterstate.h"

namespace YAML {
namespace {

class EmitterStateTest_493 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_493, InitialStateIsGood_493) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_493, InitialLastErrorIsEmpty_493) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_493, InitialHasNoAnchor_493) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_493, InitialHasNoAlias_493) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_493, InitialHasNoTag_493) {
  EXPECT_FALSE(state.HasTag());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_493, SetErrorMakesStateNotGood_493) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_493, SetErrorSetsLastError_493) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_493, SetErrorEmptyString_493) {
  state.SetError("");
  EXPECT_FALSE(state.good());
}

// ==================== SetBoolCaseFormat Tests ====================

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_UpperCase_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_LowerCase_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_CamelCase_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_InvalidValue_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_Auto_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_Dec_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_UpperCase_GetReturnsUpperCase_493) {
  state.SetBoolCaseFormat(UpperCase, FmtScope::Local);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_LowerCase_GetReturnsLowerCase_493) {
  state.SetBoolCaseFormat(LowerCase, FmtScope::Local);
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_CamelCase_GetReturnsCamelCase_493) {
  state.SetBoolCaseFormat(CamelCase, FmtScope::Local);
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_GlobalScope_493) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

// ==================== SetOutputCharset Tests ====================

TEST_F(EmitterStateTest_493, SetOutputCharset_EmitNonAscii_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetOutputCharset_EscapeNonAscii_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetOutputCharset_EscapeAsJson_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeAsJson, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetOutputCharset_Invalid_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetOutputCharset(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, GetOutputCharset_AfterSet_493) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Local);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

// ==================== SetStringFormat Tests ====================

TEST_F(EmitterStateTest_493, SetStringFormat_SingleQuoted_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetStringFormat_DoubleQuoted_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetStringFormat_Literal_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetStringFormat_Auto_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetStringFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetStringFormat_Invalid_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetStringFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, GetStringFormat_AfterSet_493) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== SetBoolFormat Tests ====================

TEST_F(EmitterStateTest_493, SetBoolFormat_YesNoBool_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetBoolFormat_TrueFalseBool_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetBoolFormat_OnOffBool_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetBoolFormat_Invalid_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetBoolFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, GetBoolFormat_AfterSet_493) {
  state.SetBoolFormat(YesNoBool, FmtScope::Local);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

// ==================== SetBoolLengthFormat Tests ====================

TEST_F(EmitterStateTest_493, SetBoolLengthFormat_LongBool_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetBoolLengthFormat_ShortBool_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetBoolLengthFormat_Invalid_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetBoolLengthFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, GetBoolLengthFormat_AfterSet_493) {
  state.SetBoolLengthFormat(ShortBool, FmtScope::Local);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

// ==================== SetNullFormat Tests ====================

TEST_F(EmitterStateTest_493, SetNullFormat_LowerNull_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetNullFormat_UpperNull_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetNullFormat(UpperNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetNullFormat_CamelNull_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetNullFormat(CamelNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetNullFormat_TildeNull_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetNullFormat_Invalid_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetNullFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, GetNullFormat_AfterSet_493) {
  state.SetNullFormat(TildeNull, FmtScope::Local);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== SetIntFormat Tests ====================

TEST_F(EmitterStateTest_493, SetIntFormat_Dec_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetIntFormat_Hex_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetIntFormat_Oct_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetIntFormat_Invalid_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetIntFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, GetIntFormat_AfterSet_493) {
  state.SetIntFormat(Hex, FmtScope::Local);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

// ==================== SetIndent Tests ====================

TEST_F(EmitterStateTest_493, SetIndent_ValidValue_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetIndent_Two_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, GetIndent_AfterSet_493) {
  state.SetIndent(4, FmtScope::Local);
  EXPECT_EQ(4u, state.GetIndent());
}

// ==================== SetPreCommentIndent Tests ====================

TEST_F(EmitterStateTest_493, SetPreCommentIndent_ValidValue_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, GetPreCommentIndent_AfterSet_493) {
  state.SetPreCommentIndent(3, FmtScope::Local);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

// ==================== SetPostCommentIndent Tests ====================

TEST_F(EmitterStateTest_493, SetPostCommentIndent_ValidValue_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetPostCommentIndent(1, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, GetPostCommentIndent_AfterSet_493) {
  state.SetPostCommentIndent(5, FmtScope::Local);
  EXPECT_EQ(5u, state.GetPostCommentIndent());
}

// ==================== SetFlowType Tests ====================

TEST_F(EmitterStateTest_493, SetFlowType_Seq_Flow_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetFlowType_Seq_Block_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetFlowType_Map_Flow_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetFlowType_Map_Block_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetFlowType_Invalid_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, GetFlowType_Seq_AfterSet_493) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_493, GetFlowType_Map_AfterSet_493) {
  state.SetFlowType(GroupType::Map, Block, FmtScope::Local);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ==================== SetMapKeyFormat Tests ====================

TEST_F(EmitterStateTest_493, SetMapKeyFormat_LongKey_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetMapKeyFormat_Auto_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetMapKeyFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetMapKeyFormat_Invalid_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetMapKeyFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, GetMapKeyFormat_AfterSet_493) {
  state.SetMapKeyFormat(LongKey, FmtScope::Local);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== SetFloatPrecision Tests ====================

TEST_F(EmitterStateTest_493, SetFloatPrecision_ValidValue_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, GetFloatPrecision_AfterSet_493) {
  state.SetFloatPrecision(8, FmtScope::Local);
  EXPECT_EQ(8u, state.GetFloatPrecision());
}

// ==================== SetDoublePrecision Tests ====================

TEST_F(EmitterStateTest_493, SetDoublePrecision_ValidValue_ReturnsTrue_493) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, GetDoublePrecision_AfterSet_493) {
  state.SetDoublePrecision(10, FmtScope::Local);
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_493, SetAnchor_HasAnchorReturnsTrue_493) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_493, SetAlias_HasAliasReturnsTrue_493) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_493, SetTag_HasTagReturnsTrue_493) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Doc Tests ====================

TEST_F(EmitterStateTest_493, StartedDoc_EndedDoc_NoError_493) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_493, StartedGroup_Seq_EndedGroup_493) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_493, StartedGroup_Map_EndedGroup_493) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
}

TEST_F(EmitterStateTest_493, CurGroupChildCount_InitiallyZeroAfterGroupStart_493) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_493, CurGroupLongKey_DefaultFalse_493) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== FmtScope::Global persistence Tests ====================

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_GlobalScope_Persists_493) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

// ==================== Multiple invalid EMITTER_MANIP for SetBoolCaseFormat ====================

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_Newline_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Newline, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_Block_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_TrueFalseBool_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetBoolCaseFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_LongBool_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetBoolCaseFormat(LongBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_ShortBool_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetBoolCaseFormat(ShortBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormat_LongKey_ReturnsFalse_493) {
  EXPECT_FALSE(state.SetBoolCaseFormat(LongKey, FmtScope::Local));
}

// ==================== Scalar in Group Tests ====================

TEST_F(EmitterStateTest_493, StartedScalar_InGroup_IncreasesChildCount_493) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_493, ClearModifiedSettings_DoesNotCrash_493) {
  state.SetBoolCaseFormat(UpperCase, FmtScope::Local);
  state.ClearModifiedSettings();
  // Should not crash and state should still be good
  EXPECT_TRUE(state.good());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_493, RestoreGlobalModifiedSettings_DoesNotCrash_493) {
  state.SetBoolCaseFormat(LowerCase, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_493, SetNonContent_NoExceptionThrown_493) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_493, ForceFlow_NoExceptionThrown_493) {
  state.ForceFlow();
  EXPECT_TRUE(state.good());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_493, SetLocalValue_Flow_493) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_493, SetLocalValue_UpperCase_493) {
  state.SetLocalValue(UpperCase);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_493, SetLocalValue_Hex_493) {
  state.SetLocalValue(Hex);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

}  // namespace
}  // namespace YAML
