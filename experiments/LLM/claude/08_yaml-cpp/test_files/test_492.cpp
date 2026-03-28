#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {
namespace {

class EmitterStateTest_492 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ============================================================
// Constructor / Initial State Tests
// ============================================================

TEST_F(EmitterStateTest_492, InitialState_IsGood_492) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_492, InitialState_NoError_492) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_492, InitialState_HasNoAnchor_492) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_492, InitialState_HasNoAlias_492) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_492, InitialState_HasNoTag_492) {
  EXPECT_FALSE(state.HasTag());
}

// ============================================================
// SetError Tests
// ============================================================

TEST_F(EmitterStateTest_492, SetError_MakesNotGood_492) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_492, SetError_ReturnsErrorMessage_492) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_492, SetError_EmptyString_492) {
  state.SetError("");
  EXPECT_FALSE(state.good());
}

// ============================================================
// SetBoolLengthFormat Tests
// ============================================================

TEST_F(EmitterStateTest_492, SetBoolLengthFormat_LongBool_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetBoolLengthFormat_ShortBool_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetBoolLengthFormat_InvalidValue_ReturnsFalse_492) {
  EXPECT_FALSE(state.SetBoolLengthFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetBoolLengthFormat_Flow_ReturnsFalse_492) {
  EXPECT_FALSE(state.SetBoolLengthFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetBoolLengthFormat_Dec_ReturnsFalse_492) {
  EXPECT_FALSE(state.SetBoolLengthFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetBoolLengthFormat_TrueFalseBool_ReturnsFalse_492) {
  EXPECT_FALSE(state.SetBoolLengthFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetBoolLengthFormat_LongBool_GetReturnsLongBool_492) {
  state.SetBoolLengthFormat(LongBool, FmtScope::Local);
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_492, SetBoolLengthFormat_ShortBool_GetReturnsShortBool_492) {
  state.SetBoolLengthFormat(ShortBool, FmtScope::Local);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_492, SetBoolLengthFormat_GlobalScope_492) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

// ============================================================
// SetBoolFormat Tests
// ============================================================

TEST_F(EmitterStateTest_492, SetBoolFormat_YesNoBool_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetBoolFormat_TrueFalseBool_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetBoolFormat_OnOffBool_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetBoolFormat_Invalid_ReturnsFalse_492) {
  EXPECT_FALSE(state.SetBoolFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetBoolFormat_GetReturnsSet_492) {
  state.SetBoolFormat(YesNoBool, FmtScope::Local);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

// ============================================================
// SetBoolCaseFormat Tests
// ============================================================

TEST_F(EmitterStateTest_492, SetBoolCaseFormat_UpperCase_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetBoolCaseFormat_LowerCase_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetBoolCaseFormat_CamelCase_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetBoolCaseFormat_Invalid_ReturnsFalse_492) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetBoolCaseFormat_GetReturnsSet_492) {
  state.SetBoolCaseFormat(UpperCase, FmtScope::Local);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

// ============================================================
// SetOutputCharset Tests
// ============================================================

TEST_F(EmitterStateTest_492, SetOutputCharset_EmitNonAscii_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetOutputCharset_EscapeNonAscii_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetOutputCharset_EscapeAsJson_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeAsJson, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetOutputCharset_Invalid_ReturnsFalse_492) {
  EXPECT_FALSE(state.SetOutputCharset(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetOutputCharset_GetReturnsSet_492) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Local);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

// ============================================================
// SetStringFormat Tests
// ============================================================

TEST_F(EmitterStateTest_492, SetStringFormat_SingleQuoted_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetStringFormat_DoubleQuoted_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetStringFormat_Literal_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetStringFormat_Invalid_ReturnsFalse_492) {
  EXPECT_FALSE(state.SetStringFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetStringFormat_GetReturnsSet_492) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ============================================================
// SetNullFormat Tests
// ============================================================

TEST_F(EmitterStateTest_492, SetNullFormat_LowerNull_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetNullFormat_UpperNull_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetNullFormat(UpperNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetNullFormat_CamelNull_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetNullFormat(CamelNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetNullFormat_TildeNull_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetNullFormat_Invalid_ReturnsFalse_492) {
  EXPECT_FALSE(state.SetNullFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetNullFormat_GetReturnsSet_492) {
  state.SetNullFormat(TildeNull, FmtScope::Local);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ============================================================
// SetIntFormat Tests
// ============================================================

TEST_F(EmitterStateTest_492, SetIntFormat_Dec_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetIntFormat_Hex_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetIntFormat_Oct_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetIntFormat_Invalid_ReturnsFalse_492) {
  EXPECT_FALSE(state.SetIntFormat(Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetIntFormat_GetReturnsSet_492) {
  state.SetIntFormat(Hex, FmtScope::Local);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

// ============================================================
// SetIndent Tests
// ============================================================

TEST_F(EmitterStateTest_492, SetIndent_ValidValue_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetIndent_MinValue_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetIndent_TooSmall_ReturnsFalse_492) {
  EXPECT_FALSE(state.SetIndent(1, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetIndent_Zero_ReturnsFalse_492) {
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetIndent_GetReturnsSet_492) {
  state.SetIndent(4, FmtScope::Local);
  EXPECT_EQ(4u, state.GetIndent());
}

// ============================================================
// SetPreCommentIndent Tests
// ============================================================

TEST_F(EmitterStateTest_492, SetPreCommentIndent_ValidValue_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetPreCommentIndent_Zero_ReturnsFalse_492) {
  EXPECT_FALSE(state.SetPreCommentIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetPreCommentIndent_GetReturnsSet_492) {
  state.SetPreCommentIndent(3, FmtScope::Local);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

// ============================================================
// SetPostCommentIndent Tests
// ============================================================

TEST_F(EmitterStateTest_492, SetPostCommentIndent_ValidValue_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetPostCommentIndent_Zero_ReturnsFalse_492) {
  EXPECT_FALSE(state.SetPostCommentIndent(0, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetPostCommentIndent_GetReturnsSet_492) {
  state.SetPostCommentIndent(5, FmtScope::Local);
  EXPECT_EQ(5u, state.GetPostCommentIndent());
}

// ============================================================
// SetFlowType Tests
// ============================================================

TEST_F(EmitterStateTest_492, SetFlowType_Seq_Flow_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetFlowType_Seq_Block_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetFlowType_Map_Flow_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetFlowType_Map_Block_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetFlowType_Invalid_ReturnsFalse_492) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Dec, FmtScope::Local));
}

// ============================================================
// SetMapKeyFormat Tests
// ============================================================

TEST_F(EmitterStateTest_492, SetMapKeyFormat_LongKey_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetMapKeyFormat_Auto_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetMapKeyFormat(Auto, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetMapKeyFormat_Invalid_ReturnsFalse_492) {
  EXPECT_FALSE(state.SetMapKeyFormat(Flow, FmtScope::Local));
}

// ============================================================
// SetFloatPrecision / SetDoublePrecision Tests
// ============================================================

TEST_F(EmitterStateTest_492, SetFloatPrecision_ValidValue_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetFloatPrecision_GetReturnsSet_492) {
  state.SetFloatPrecision(4, FmtScope::Local);
  EXPECT_EQ(4u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_492, SetDoublePrecision_ValidValue_ReturnsTrue_492) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Local));
}

TEST_F(EmitterStateTest_492, SetDoublePrecision_GetReturnsSet_492) {
  state.SetDoublePrecision(8, FmtScope::Local);
  EXPECT_EQ(8u, state.GetDoublePrecision());
}

// ============================================================
// Anchor / Alias / Tag State Tests
// ============================================================

TEST_F(EmitterStateTest_492, SetAnchor_HasAnchorReturnsTrue_492) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_492, SetAlias_HasAliasReturnsTrue_492) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_492, SetTag_HasTagReturnsTrue_492) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ============================================================
// Document lifecycle Tests
// ============================================================

TEST_F(EmitterStateTest_492, StartedDoc_EndedDoc_NoError_492) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ============================================================
// Group lifecycle Tests
// ============================================================

TEST_F(EmitterStateTest_492, StartedGroup_EndedGroup_Seq_492) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_492, StartedGroup_EndedGroup_Map_492) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_492, CurGroupChildCount_InitiallyZero_492) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_492, CurGroupLongKey_DefaultFalse_492) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// ============================================================
// SetLocalValue boundary Tests
// ============================================================

TEST_F(EmitterStateTest_492, SetLocalValue_Flow_492) {
  // SetLocalValue should not crash; it sets local formatting
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_492, SetLocalValue_Block_492) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// ============================================================
// ClearModifiedSettings / RestoreGlobalModifiedSettings Tests
// ============================================================

TEST_F(EmitterStateTest_492, ClearModifiedSettings_NoError_492) {
  state.SetBoolLengthFormat(LongBool, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_492, RestoreGlobalModifiedSettings_NoError_492) {
  state.SetBoolLengthFormat(LongBool, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ============================================================
// Multiple scope interactions for SetBoolLengthFormat
// ============================================================

TEST_F(EmitterStateTest_492, SetBoolLengthFormat_LocalThenGlobal_492) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Local));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_492, SetBoolLengthFormat_AllInvalidManips_492) {
  // Test several invalid EMITTER_MANIP values
  EXPECT_FALSE(state.SetBoolLengthFormat(Newline, FmtScope::Local));
  EXPECT_FALSE(state.SetBoolLengthFormat(BeginDoc, FmtScope::Local));
  EXPECT_FALSE(state.SetBoolLengthFormat(EndDoc, FmtScope::Local));
  EXPECT_FALSE(state.SetBoolLengthFormat(BeginSeq, FmtScope::Local));
  EXPECT_FALSE(state.SetBoolLengthFormat(EndSeq, FmtScope::Local));
  EXPECT_FALSE(state.SetBoolLengthFormat(BeginMap, FmtScope::Local));
  EXPECT_FALSE(state.SetBoolLengthFormat(EndMap, FmtScope::Local));
  EXPECT_FALSE(state.SetBoolLengthFormat(Key, FmtScope::Local));
  EXPECT_FALSE(state.SetBoolLengthFormat(Value, FmtScope::Local));
  EXPECT_FALSE(state.SetBoolLengthFormat(LongKey, FmtScope::Local));
  EXPECT_FALSE(state.SetBoolLengthFormat(YesNoBool, FmtScope::Local));
  EXPECT_FALSE(state.SetBoolLengthFormat(TrueFalseBool, FmtScope::Local));
  EXPECT_FALSE(state.SetBoolLengthFormat(OnOffBool, FmtScope::Local));
  EXPECT_FALSE(state.SetBoolLengthFormat(UpperCase, FmtScope::Local));
  EXPECT_FALSE(state.SetBoolLengthFormat(LowerCase, FmtScope::Local));
  EXPECT_FALSE(state.SetBoolLengthFormat(CamelCase, FmtScope::Local));
}

// ============================================================
// ForceFlow Test
// ============================================================

TEST_F(EmitterStateTest_492, ForceFlow_NoError_492) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ============================================================
// SetLongKey Test
// ============================================================

TEST_F(EmitterStateTest_492, SetLongKey_InGroup_492) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

}  // namespace
}  // namespace YAML
