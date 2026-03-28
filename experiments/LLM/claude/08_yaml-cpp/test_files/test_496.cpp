#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_496 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Construction / Initial State ====================

TEST_F(EmitterStateTest_496, InitialState_IsGood_496) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_496, InitialState_NoError_496) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_496, InitialState_HasNoAnchor_496) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_496, InitialState_HasNoAlias_496) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_496, InitialState_HasNoTag_496) {
  EXPECT_FALSE(state.HasTag());
}

// ==================== SetError ====================

TEST_F(EmitterStateTest_496, SetError_MakesNotGood_496) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_496, SetError_ReturnsErrorMessage_496) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_496, SetError_OnlyFirstErrorStored_496) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== SetIndent ====================

TEST_F(EmitterStateTest_496, SetIndent_Zero_ReturnsFalse_496) {
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetIndent_One_ReturnsFalse_496) {
  EXPECT_FALSE(state.SetIndent(1, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetIndent_Two_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetIndent_Large_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetIndent(10, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetIndent_Two_GetReturnsTwo_496) {
  state.SetIndent(2, FmtScope::Global);
  EXPECT_EQ(2u, state.GetIndent());
}

TEST_F(EmitterStateTest_496, SetIndent_Five_GetReturnsFive_496) {
  state.SetIndent(5, FmtScope::Global);
  EXPECT_EQ(5u, state.GetIndent());
}

TEST_F(EmitterStateTest_496, SetIndent_LocalScope_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
}

TEST_F(EmitterStateTest_496, SetIndent_BoundaryValueOne_ReturnsFalse_496) {
  EXPECT_FALSE(state.SetIndent(1, FmtScope::Local));
}

// ==================== SetPreCommentIndent ====================

TEST_F(EmitterStateTest_496, SetPreCommentIndent_Zero_ReturnsFalse_496) {
  EXPECT_FALSE(state.SetPreCommentIndent(0, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetPreCommentIndent_One_ReturnsFalse_496) {
  EXPECT_FALSE(state.SetPreCommentIndent(1, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetPreCommentIndent_Two_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetPreCommentIndent_GetReturnsSetValue_496) {
  state.SetPreCommentIndent(3, FmtScope::Global);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

// ==================== SetPostCommentIndent ====================

TEST_F(EmitterStateTest_496, SetPostCommentIndent_Zero_ReturnsFalse_496) {
  EXPECT_FALSE(state.SetPostCommentIndent(0, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetPostCommentIndent_One_ReturnsFalse_496) {
  EXPECT_FALSE(state.SetPostCommentIndent(1, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetPostCommentIndent_Two_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetPostCommentIndent_GetReturnsSetValue_496) {
  state.SetPostCommentIndent(4, FmtScope::Global);
  EXPECT_EQ(4u, state.GetPostCommentIndent());
}

// ==================== SetAnchor / SetAlias / SetTag ====================

TEST_F(EmitterStateTest_496, SetAnchor_HasAnchorReturnsTrue_496) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_496, SetAlias_HasAliasReturnsTrue_496) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_496, SetTag_HasTagReturnsTrue_496) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== SetOutputCharset ====================

TEST_F(EmitterStateTest_496, SetOutputCharset_EmitNonAscii_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetOutputCharset_EscapeNonAscii_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetOutputCharset_InvalidValue_ReturnsFalse_496) {
  // Passing a non-charset EMITTER_MANIP should return false
  EXPECT_FALSE(state.SetOutputCharset(Auto, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetOutputCharset_GetReturnsSetValue_496) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Global);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

// ==================== SetStringFormat ====================

TEST_F(EmitterStateTest_496, SetStringFormat_SingleQuoted_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetStringFormat_DoubleQuoted_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetStringFormat_Literal_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetStringFormat_GetReturnsSetValue_496) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== SetBoolFormat ====================

TEST_F(EmitterStateTest_496, SetBoolFormat_TrueFalseBool_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetBoolFormat_YesNoBool_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetBoolFormat_OnOffBool_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetBoolFormat_GetReturnsSetValue_496) {
  state.SetBoolFormat(YesNoBool, FmtScope::Global);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

// ==================== SetBoolLengthFormat ====================

TEST_F(EmitterStateTest_496, SetBoolLengthFormat_ShortBool_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetBoolLengthFormat_LongBool_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetBoolLengthFormat_GetReturnsSetValue_496) {
  state.SetBoolLengthFormat(LongBool, FmtScope::Global);
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

// ==================== SetBoolCaseFormat ====================

TEST_F(EmitterStateTest_496, SetBoolCaseFormat_UpperCase_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetBoolCaseFormat_LowerCase_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetBoolCaseFormat_CamelCase_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetBoolCaseFormat_GetReturnsSetValue_496) {
  state.SetBoolCaseFormat(UpperCase, FmtScope::Global);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

// ==================== SetIntFormat ====================

TEST_F(EmitterStateTest_496, SetIntFormat_Dec_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetIntFormat_Hex_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetIntFormat_Oct_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetIntFormat_GetReturnsSetValue_496) {
  state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

// ==================== SetNullFormat ====================

TEST_F(EmitterStateTest_496, SetNullFormat_LowerNull_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetNullFormat_TildeNull_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetNullFormat_GetReturnsSetValue_496) {
  state.SetNullFormat(TildeNull, FmtScope::Global);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ==================== SetMapKeyFormat ====================

TEST_F(EmitterStateTest_496, SetMapKeyFormat_LongKey_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetMapKeyFormat_GetReturnsSetValue_496) {
  state.SetMapKeyFormat(LongKey, FmtScope::Global);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ==================== SetFloatPrecision / SetDoublePrecision ====================

TEST_F(EmitterStateTest_496, SetFloatPrecision_ValidValue_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetFloatPrecision(3, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetFloatPrecision_GetReturnsSetValue_496) {
  state.SetFloatPrecision(5, FmtScope::Global);
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_496, SetDoublePrecision_ValidValue_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetDoublePrecision(6, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetDoublePrecision_GetReturnsSetValue_496) {
  state.SetDoublePrecision(10, FmtScope::Global);
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ==================== SetFlowType ====================

TEST_F(EmitterStateTest_496, SetFlowType_Seq_Block_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetFlowType_Seq_Flow_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetFlowType_Map_Block_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, SetFlowType_Map_Flow_ReturnsTrue_496) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_496, GetFlowType_Seq_ReturnsSetValue_496) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_496, GetFlowType_Map_ReturnsSetValue_496) {
  state.SetFlowType(GroupType::Map, Flow, FmtScope::Global);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

// ==================== Doc lifecycle ====================

TEST_F(EmitterStateTest_496, StartedDoc_DoesNotBreakGoodState_496) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_496, EndedDoc_DoesNotBreakGoodState_496) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group lifecycle ====================

TEST_F(EmitterStateTest_496, StartedGroup_Seq_DoesNotBreakGoodState_496) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_496, StartedGroup_Map_DoesNotBreakGoodState_496) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_496, EndedGroup_Seq_AfterStart_496) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_496, CurGroupType_AfterStartSeq_496) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_496, CurGroupType_AfterStartMap_496) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_496, CurGroupChildCount_InitiallyZero_496) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

// ==================== StartedScalar ====================

TEST_F(EmitterStateTest_496, StartedScalar_DoesNotBreakGoodState_496) {
  state.StartedDoc();
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

// ==================== ForceFlow ====================

TEST_F(EmitterStateTest_496, ForceFlow_OnGroup_496) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== SetNonContent ====================

TEST_F(EmitterStateTest_496, SetNonContent_DoesNotBreakGoodState_496) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== CurIndent ====================

TEST_F(EmitterStateTest_496, CurIndent_InitialValue_496) {
  // Initially cur indent should be 0
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== ClearModifiedSettings ====================

TEST_F(EmitterStateTest_496, ClearModifiedSettings_DoesNotBreakGoodState_496) {
  state.SetIndent(4, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey ====================

TEST_F(EmitterStateTest_496, SetLongKey_InGroup_496) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

}  // namespace YAML
