#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_470 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ===== Initial State Tests =====

TEST_F(EmitterStateTest_470, InitialState_IsGood_470) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_470, InitialState_NoLastError_470) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_470, InitialState_HasNoAnchor_470) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_470, InitialState_HasNoAlias_470) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_470, InitialState_HasNoTag_470) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_470, InitialState_CurIndentIsZero_470) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ===== SetError Tests =====

TEST_F(EmitterStateTest_470, SetError_MakesNotGood_470) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_470, SetError_StoresErrorMessage_470) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_470, SetError_FirstErrorPersists_470) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically first error is preserved
  EXPECT_FALSE(state.good());
  // The last error should be the first one set (common pattern)
  EXPECT_EQ("first error", state.GetLastError());
}

// ===== SetAnchor / HasAnchor Tests =====

TEST_F(EmitterStateTest_470, SetAnchor_SetsHasAnchor_470) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

// ===== SetAlias / HasAlias Tests =====

TEST_F(EmitterStateTest_470, SetAlias_SetsHasAlias_470) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

// ===== SetTag / HasTag Tests =====

TEST_F(EmitterStateTest_470, SetTag_SetsHasTag_470) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ===== SetNonContent Tests =====

TEST_F(EmitterStateTest_470, SetNonContent_DoesNotBreakState_470) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ===== Doc State Tests =====

TEST_F(EmitterStateTest_470, StartedDoc_StateRemainsGood_470) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_470, EndedDoc_StateRemainsGood_470) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ===== Group Tests =====

TEST_F(EmitterStateTest_470, StartedGroup_Seq_StateRemainsGood_470) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_470, StartedGroup_Map_StateRemainsGood_470) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_470, EndedGroup_AfterStartedGroup_470) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_470, CurGroupType_AfterStartingSeq_470) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_470, CurGroupType_AfterStartingMap_470) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_470, CurGroupChildCount_InitiallyZero_470) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_470, CurGroupChildCount_IncreasesAfterScalar_470) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_470, CurGroupLongKey_InitiallyFalse_470) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_470, SetLongKey_MakesCurGroupLongKeyTrue_470) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ===== Scalar Tests =====

TEST_F(EmitterStateTest_470, StartedScalar_ClearsAnchorTagAlias_470) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetAnchor();
  state.SetTag();
  EXPECT_TRUE(state.HasAnchor());
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
  EXPECT_FALSE(state.HasTag());
}

// ===== Format Setting Tests =====

TEST_F(EmitterStateTest_470, SetOutputCharset_ValidValue_ReturnsTrue_470) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, GetOutputCharset_AfterSet_470) {
  state.SetOutputCharset(EmitNonAscii, FmtScope::Global);
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_470, SetStringFormat_ValidValue_ReturnsTrue_470) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, GetStringFormat_AfterSet_470) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_470, SetBoolFormat_ValidValue_ReturnsTrue_470) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, GetBoolFormat_AfterSet_470) {
  state.SetBoolFormat(TrueFalseBool, FmtScope::Global);
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_470, SetBoolLengthFormat_ValidValue_ReturnsTrue_470) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, GetBoolLengthFormat_AfterSet_470) {
  state.SetBoolLengthFormat(LongBool, FmtScope::Global);
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_470, SetBoolCaseFormat_ValidValue_ReturnsTrue_470) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, GetBoolCaseFormat_AfterSet_470) {
  state.SetBoolCaseFormat(LowerCase, FmtScope::Global);
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_470, SetIntFormat_ValidValue_ReturnsTrue_470) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, GetIntFormat_AfterSet_470) {
  state.SetIntFormat(Oct, FmtScope::Global);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_470, SetNullFormat_ValidValue_ReturnsTrue_470) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, GetNullFormat_AfterSet_470) {
  state.SetNullFormat(LowerNull, FmtScope::Global);
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

// ===== Indent Settings =====

TEST_F(EmitterStateTest_470, SetIndent_ValidValue_ReturnsTrue_470) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, GetIndent_AfterSet_470) {
  state.SetIndent(4, FmtScope::Global);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_470, SetIndent_ZeroValue_ReturnsFalse_470) {
  // Indent of 0 is likely invalid
  EXPECT_FALSE(state.SetIndent(0, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, SetPreCommentIndent_ValidValue_ReturnsTrue_470) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, GetPreCommentIndent_AfterSet_470) {
  state.SetPreCommentIndent(3, FmtScope::Global);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_470, SetPostCommentIndent_ValidValue_ReturnsTrue_470) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, GetPostCommentIndent_AfterSet_470) {
  state.SetPostCommentIndent(3, FmtScope::Global);
  EXPECT_EQ(3u, state.GetPostCommentIndent());
}

// ===== Precision Settings =====

TEST_F(EmitterStateTest_470, SetFloatPrecision_ValidValue_ReturnsTrue_470) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, GetFloatPrecision_AfterSet_470) {
  state.SetFloatPrecision(5, FmtScope::Global);
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_470, SetDoublePrecision_ValidValue_ReturnsTrue_470) {
  EXPECT_TRUE(state.SetDoublePrecision(12, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, GetDoublePrecision_AfterSet_470) {
  state.SetDoublePrecision(10, FmtScope::Global);
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ===== Flow Type Tests =====

TEST_F(EmitterStateTest_470, SetFlowType_Seq_Block_ReturnsTrue_470) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, SetFlowType_Seq_Flow_ReturnsTrue_470) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, GetFlowType_Seq_AfterSet_470) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_470, SetFlowType_Map_Block_ReturnsTrue_470) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, GetFlowType_Map_AfterSet_470) {
  state.SetFlowType(GroupType::Map, Flow, FmtScope::Global);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

// ===== Map Key Format Tests =====

TEST_F(EmitterStateTest_470, SetMapKeyFormat_ValidValue_ReturnsTrue_470) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, GetMapKeyFormat_AfterSet_470) {
  state.SetMapKeyFormat(LongKey, FmtScope::Global);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ===== ForceFlow Tests =====

TEST_F(EmitterStateTest_470, ForceFlow_StateRemainsGood_470) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_470, ForceFlow_ChangesFlowTypeToFlow_470) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ===== Local Scope Tests =====

TEST_F(EmitterStateTest_470, SetLocalValue_Flow_470) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_470, SetLocalValue_Block_470) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// ===== ClearModifiedSettings Tests =====

TEST_F(EmitterStateTest_470, ClearModifiedSettings_DoesNotBreak_470) {
  state.SetIndent(6, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ===== RestoreGlobalModifiedSettings Tests =====

TEST_F(EmitterStateTest_470, RestoreGlobalModifiedSettings_DoesNotBreak_470) {
  state.SetIndent(6, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ===== NextGroupType Tests =====

TEST_F(EmitterStateTest_470, NextGroupType_WithNoGroup_470) {
  // With no group started, NextGroupType should return a valid type
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should be some valid enum value - just checking it doesn't crash
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ===== Nested Groups =====

TEST_F(EmitterStateTest_470, NestedGroups_TypeIsCorrect_470) {
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

TEST_F(EmitterStateTest_470, NestedGroups_IndentIncreases_470) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  std::size_t indent1 = state.CurGroupIndent();
  state.StartedGroup(GroupType::Seq);
  std::size_t indent2 = state.CurGroupIndent();
  // Inner group indent should be >= outer
  EXPECT_GE(indent2, indent1);
}

// ===== HasBegunNode / HasBegunContent Tests =====

TEST_F(EmitterStateTest_470, HasBegunNode_InitiallyFalse_470) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_470, HasBegunContent_InitiallyFalse_470) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ===== LastIndent Tests =====

TEST_F(EmitterStateTest_470, LastIndent_InitialValue_470) {
  // Before any group, LastIndent should return some default
  std::size_t last = state.LastIndent();
  (void)last;
  EXPECT_TRUE(state.good());
}

// ===== Invalid Format Values =====

TEST_F(EmitterStateTest_470, SetOutputCharset_InvalidValue_ReturnsFalse_470) {
  // Passing a value that is not a charset manipulator
  EXPECT_FALSE(state.SetOutputCharset(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, SetStringFormat_InvalidValue_ReturnsFalse_470) {
  EXPECT_FALSE(state.SetStringFormat(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, SetBoolFormat_InvalidValue_ReturnsFalse_470) {
  EXPECT_FALSE(state.SetBoolFormat(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, SetIntFormat_InvalidValue_ReturnsFalse_470) {
  EXPECT_FALSE(state.SetIntFormat(Flow, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, SetFlowType_InvalidValue_ReturnsFalse_470) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Hex, FmtScope::Global));
}

TEST_F(EmitterStateTest_470, SetMapKeyFormat_InvalidValue_ReturnsFalse_470) {
  EXPECT_FALSE(state.SetMapKeyFormat(Flow, FmtScope::Global));
}

// ===== Multiple Scalars in Sequence =====

TEST_F(EmitterStateTest_470, MultipleScalarsInSequence_ChildCountIncreases_470) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
  state.StartedScalar();
  EXPECT_EQ(2u, state.CurGroupChildCount());
  state.StartedScalar();
  EXPECT_EQ(3u, state.CurGroupChildCount());
}

// ===== Setting with Local Scope =====

TEST_F(EmitterStateTest_470, SetIndent_LocalScope_470) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_470, ClearModifiedSettings_RestoresDefaults_470) {
  std::size_t defaultIndent = state.GetIndent();
  state.SetIndent(8, FmtScope::Local);
  EXPECT_EQ(8u, state.GetIndent());
  state.ClearModifiedSettings();
  EXPECT_EQ(defaultIndent, state.GetIndent());
}

// ===== Doc Count / Multiple Docs =====

TEST_F(EmitterStateTest_470, MultipleDocuments_StateRemainsGood_470) {
  state.StartedDoc();
  state.EndedDoc();
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

}  // namespace YAML
