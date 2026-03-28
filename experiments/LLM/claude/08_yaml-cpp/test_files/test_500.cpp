#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_500 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Construction / Initial State ====================

TEST_F(EmitterStateTest_500, InitialStateIsGood_500) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_500, InitialLastErrorIsEmpty_500) {
  EXPECT_EQ(state.GetLastError(), "");
}

TEST_F(EmitterStateTest_500, InitialHasNoAnchor_500) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_500, InitialHasNoAlias_500) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_500, InitialHasNoTag_500) {
  EXPECT_FALSE(state.HasTag());
}

// ==================== SetError ====================

TEST_F(EmitterStateTest_500, SetErrorMakesStateNotGood_500) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_500, SetErrorSetsLastError_500) {
  state.SetError("test error message");
  EXPECT_EQ(state.GetLastError(), "test error message");
}

TEST_F(EmitterStateTest_500, SetErrorOnlyFirstErrorSticks_500) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically the first error is preserved
  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), "first error");
}

// ==================== Anchor / Alias / Tag ====================

TEST_F(EmitterStateTest_500, SetAnchorSetsHasAnchor_500) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_500, SetAliasSetsHasAlias_500) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_500, SetTagSetsHasTag_500) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Output Charset ====================

TEST_F(EmitterStateTest_500, SetOutputCharsetGlobal_500) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeNonAscii, FmtScope::Global));
  EXPECT_EQ(state.GetOutputCharset(), EscapeNonAscii);
}

TEST_F(EmitterStateTest_500, SetOutputCharsetLocal_500) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
  EXPECT_EQ(state.GetOutputCharset(), EmitNonAscii);
}

TEST_F(EmitterStateTest_500, SetOutputCharsetInvalidValue_500) {
  EXPECT_FALSE(state.SetOutputCharset(Flow, FmtScope::Global));
}

// ==================== String Format ====================

TEST_F(EmitterStateTest_500, SetStringFormatSingleQuoted_500) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(state.GetStringFormat(), SingleQuoted);
}

TEST_F(EmitterStateTest_500, SetStringFormatDoubleQuoted_500) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
  EXPECT_EQ(state.GetStringFormat(), DoubleQuoted);
}

TEST_F(EmitterStateTest_500, SetStringFormatLiteral_500) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Global));
  EXPECT_EQ(state.GetStringFormat(), Literal);
}

TEST_F(EmitterStateTest_500, SetStringFormatInvalid_500) {
  EXPECT_FALSE(state.SetStringFormat(Flow, FmtScope::Global));
}

// ==================== Bool Format ====================

TEST_F(EmitterStateTest_500, SetBoolFormatYesNo_500) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
  EXPECT_EQ(state.GetBoolFormat(), YesNoBool);
}

TEST_F(EmitterStateTest_500, SetBoolFormatTrueFalse_500) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
  EXPECT_EQ(state.GetBoolFormat(), TrueFalseBool);
}

TEST_F(EmitterStateTest_500, SetBoolFormatOnOff_500) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Global));
  EXPECT_EQ(state.GetBoolFormat(), OnOffBool);
}

TEST_F(EmitterStateTest_500, SetBoolFormatInvalid_500) {
  EXPECT_FALSE(state.SetBoolFormat(Flow, FmtScope::Global));
}

// ==================== Bool Length Format ====================

TEST_F(EmitterStateTest_500, SetBoolLengthFormatLong_500) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
  EXPECT_EQ(state.GetBoolLengthFormat(), LongBool);
}

TEST_F(EmitterStateTest_500, SetBoolLengthFormatShort_500) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(state.GetBoolLengthFormat(), ShortBool);
}

TEST_F(EmitterStateTest_500, SetBoolLengthFormatInvalid_500) {
  EXPECT_FALSE(state.SetBoolLengthFormat(Flow, FmtScope::Global));
}

// ==================== Bool Case Format ====================

TEST_F(EmitterStateTest_500, SetBoolCaseFormatUpper_500) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(state.GetBoolCaseFormat(), UpperCase);
}

TEST_F(EmitterStateTest_500, SetBoolCaseFormatLower_500) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
  EXPECT_EQ(state.GetBoolCaseFormat(), LowerCase);
}

TEST_F(EmitterStateTest_500, SetBoolCaseFormatCamel_500) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
  EXPECT_EQ(state.GetBoolCaseFormat(), CamelCase);
}

TEST_F(EmitterStateTest_500, SetBoolCaseFormatInvalid_500) {
  EXPECT_FALSE(state.SetBoolCaseFormat(Flow, FmtScope::Global));
}

// ==================== Null Format ====================

TEST_F(EmitterStateTest_500, SetNullFormatLower_500) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(state.GetNullFormat(), LowerNull);
}

TEST_F(EmitterStateTest_500, SetNullFormatUpper_500) {
  EXPECT_TRUE(state.SetNullFormat(UpperNull, FmtScope::Global));
  EXPECT_EQ(state.GetNullFormat(), UpperNull);
}

TEST_F(EmitterStateTest_500, SetNullFormatCamel_500) {
  EXPECT_TRUE(state.SetNullFormat(CamelNull, FmtScope::Global));
  EXPECT_EQ(state.GetNullFormat(), CamelNull);
}

TEST_F(EmitterStateTest_500, SetNullFormatTilde_500) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Global));
  EXPECT_EQ(state.GetNullFormat(), TildeNull);
}

TEST_F(EmitterStateTest_500, SetNullFormatInvalid_500) {
  EXPECT_FALSE(state.SetNullFormat(Flow, FmtScope::Global));
}

// ==================== Int Format ====================

TEST_F(EmitterStateTest_500, SetIntFormatDec_500) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
  EXPECT_EQ(state.GetIntFormat(), Dec);
}

TEST_F(EmitterStateTest_500, SetIntFormatHex_500) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(state.GetIntFormat(), Hex);
}

TEST_F(EmitterStateTest_500, SetIntFormatOct_500) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(state.GetIntFormat(), Oct);
}

TEST_F(EmitterStateTest_500, SetIntFormatInvalid_500) {
  EXPECT_FALSE(state.SetIntFormat(Flow, FmtScope::Global));
}

// ==================== Indent ====================

TEST_F(EmitterStateTest_500, SetIndentGlobal_500) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(state.GetIndent(), 4u);
}

TEST_F(EmitterStateTest_500, SetIndentLocal_500) {
  EXPECT_TRUE(state.SetIndent(6, FmtScope::Local));
  EXPECT_EQ(state.GetIndent(), 6u);
}

TEST_F(EmitterStateTest_500, SetIndentBoundaryMinimum_500) {
  // Indent of 1 should be minimum reasonable value
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Global));
  EXPECT_EQ(state.GetIndent(), 2u);
}

// ==================== Pre/Post Comment Indent ====================

TEST_F(EmitterStateTest_500, SetPreCommentIndent_500) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(state.GetPreCommentIndent(), 3u);
}

TEST_F(EmitterStateTest_500, SetPostCommentIndent_500) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
  EXPECT_EQ(state.GetPostCommentIndent(), 2u);
}

// ==================== Flow Type (GetFlowType focus) ====================

TEST_F(EmitterStateTest_500, GetFlowTypeSeqDefaultIsBlock_500) {
  // By default, without any group, seq format should return default
  EMITTER_MANIP flowType = state.GetFlowType(GroupType::Seq);
  // Default seq format should be Block
  EXPECT_EQ(flowType, Block);
}

TEST_F(EmitterStateTest_500, GetFlowTypeMapDefaultIsBlock_500) {
  EMITTER_MANIP flowType = state.GetFlowType(GroupType::Map);
  EXPECT_EQ(flowType, Block);
}

TEST_F(EmitterStateTest_500, SetFlowTypeSeqToFlow_500) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EMITTER_MANIP flowType = state.GetFlowType(GroupType::Seq);
  EXPECT_EQ(flowType, Flow);
}

TEST_F(EmitterStateTest_500, SetFlowTypeSeqToBlock_500) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
  EMITTER_MANIP flowType = state.GetFlowType(GroupType::Seq);
  EXPECT_EQ(flowType, Block);
}

TEST_F(EmitterStateTest_500, SetFlowTypeMapToFlow_500) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
  EMITTER_MANIP flowType = state.GetFlowType(GroupType::Map);
  EXPECT_EQ(flowType, Flow);
}

TEST_F(EmitterStateTest_500, SetFlowTypeMapToBlock_500) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EMITTER_MANIP flowType = state.GetFlowType(GroupType::Map);
  EXPECT_EQ(flowType, Block);
}

TEST_F(EmitterStateTest_500, SetFlowTypeInvalidValue_500) {
  EXPECT_FALSE(state.SetFlowType(GroupType::Seq, Dec, FmtScope::Global));
}

TEST_F(EmitterStateTest_500, SetFlowTypeLocal_500) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
  EXPECT_EQ(state.GetFlowType(GroupType::Seq), Flow);
}

// Test GetFlowType inside a Flow group - it should return Flow regardless of settings
TEST_F(EmitterStateTest_500, GetFlowTypeInFlowGroupReturnsFlow_500) {
  state.SetFlowType(GroupType::Seq, Block, FmtScope::Global);
  state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  // Start a flow group
  state.ForceFlow();
  state.StartedGroup(GroupType::Seq);
  // Inside a flow group, GetFlowType should return Flow
  EXPECT_EQ(state.GetFlowType(GroupType::Seq), Flow);
  EXPECT_EQ(state.GetFlowType(GroupType::Map), Flow);
  state.EndedGroup(GroupType::Seq);
}

// ==================== Map Key Format ====================

TEST_F(EmitterStateTest_500, SetMapKeyFormatLongKey_500) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(state.GetMapKeyFormat(), LongKey);
}

TEST_F(EmitterStateTest_500, SetMapKeyFormatAuto_500) {
  EXPECT_TRUE(state.SetMapKeyFormat(Auto, FmtScope::Global));
  EXPECT_EQ(state.GetMapKeyFormat(), Auto);
}

TEST_F(EmitterStateTest_500, SetMapKeyFormatInvalid_500) {
  EXPECT_FALSE(state.SetMapKeyFormat(Flow, FmtScope::Global));
}

// ==================== Float/Double Precision ====================

TEST_F(EmitterStateTest_500, SetFloatPrecision_500) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Global));
  EXPECT_EQ(state.GetFloatPrecision(), 6u);
}

TEST_F(EmitterStateTest_500, SetDoublePrecision_500) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Global));
  EXPECT_EQ(state.GetDoublePrecision(), 15u);
}

// ==================== Doc lifecycle ====================

TEST_F(EmitterStateTest_500, StartedDocEndedDoc_500) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group lifecycle ====================

TEST_F(EmitterStateTest_500, StartAndEndSeqGroup_500) {
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupType(), GroupType::Seq);
  EXPECT_EQ(state.CurGroupChildCount(), 0u);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_500, StartAndEndMapGroup_500) {
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(state.CurGroupType(), GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_500, NestedGroups_500) {
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(state.CurGroupType(), GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(state.CurGroupType(), GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// ==================== CurGroupFlowType ====================

TEST_F(EmitterStateTest_500, CurGroupFlowTypeBlockByDefault_500) {
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupFlowType(), FlowType::Block);
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_500, CurGroupFlowTypeFlowWhenForced_500) {
  state.ForceFlow();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupFlowType(), FlowType::Flow);
  state.EndedGroup(GroupType::Seq);
}

// ==================== SetLocalValue ====================

TEST_F(EmitterStateTest_500, SetLocalValueFlow_500) {
  state.SetLocalValue(Flow);
  // This should affect the next group's flow type
  state.StartedGroup(GroupType::Seq);
  // The seq format should be flow
  EXPECT_EQ(state.CurGroupFlowType(), FlowType::Flow);
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_500, SetLocalValueBlock_500) {
  state.SetLocalValue(Block);
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurGroupFlowType(), FlowType::Block);
  state.EndedGroup(GroupType::Seq);
}

// ==================== ClearModifiedSettings ====================

TEST_F(EmitterStateTest_500, ClearModifiedSettingsRestoresLocal_500) {
  EMITTER_MANIP original = state.GetStringFormat();
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(state.GetStringFormat(), DoubleQuoted);
  state.ClearModifiedSettings();
  EXPECT_EQ(state.GetStringFormat(), original);
}

// ==================== HasBegunNode / HasBegunContent ====================

TEST_F(EmitterStateTest_500, InitialHasNotBegunNode_500) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_500, InitialHasNotBegunContent_500) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== SetNonContent ====================

TEST_F(EmitterStateTest_500, SetNonContentDoesNotCrash_500) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ==================== SetLongKey ====================

TEST_F(EmitterStateTest_500, SetLongKeyDoesNotCrash_500) {
  state.SetLongKey();
  EXPECT_TRUE(state.good());
}

// ==================== StartedScalar ====================

TEST_F(EmitterStateTest_500, StartedScalarInGroup_500) {
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(state.CurGroupChildCount(), 1u);
  state.EndedGroup(GroupType::Seq);
}

// ==================== NextGroupType ====================

TEST_F(EmitterStateTest_500, NextGroupTypeSeq_500) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Without any parent group, should return something meaningful
  EXPECT_TRUE(nodeType == EmitterNodeType::NoNode ||
               nodeType == EmitterNodeType::FlowSeq ||
               nodeType == EmitterNodeType::BlockSeq);
}

TEST_F(EmitterStateTest_500, NextGroupTypeMap_500) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  EXPECT_TRUE(nodeType == EmitterNodeType::NoNode ||
               nodeType == EmitterNodeType::FlowMap ||
               nodeType == EmitterNodeType::BlockMap);
}

// ==================== CurGroupLongKey ====================

TEST_F(EmitterStateTest_500, CurGroupLongKeyDefault_500) {
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterStateTest_500, RestoreGlobalModifiedSettingsWorks_500) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_EQ(state.GetStringFormat(), DoubleQuoted);
  state.RestoreGlobalModifiedSettings();
  // After restore, should be back to default
  EXPECT_NE(state.GetStringFormat(), DoubleQuoted);
}

// ==================== Scope interaction ====================

TEST_F(EmitterStateTest_500, LocalScopeOverridesGlobal_500) {
  state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_EQ(state.GetIntFormat(), Hex);
  state.SetIntFormat(Oct, FmtScope::Local);
  EXPECT_EQ(state.GetIntFormat(), Oct);
  state.ClearModifiedSettings();
  EXPECT_EQ(state.GetIntFormat(), Hex);
}

// ==================== Multiple scalars increment child count ====================

TEST_F(EmitterStateTest_500, MultipleScalarsIncrementChildCount_500) {
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.StartedScalar();
  state.StartedScalar();
  EXPECT_EQ(state.CurGroupChildCount(), 3u);
  state.EndedGroup(GroupType::Seq);
}

// ==================== EscapeAsJson charset ====================

TEST_F(EmitterStateTest_500, SetOutputCharsetEscapeAsJson_500) {
  EXPECT_TRUE(state.SetOutputCharset(EscapeAsJson, FmtScope::Global));
  EXPECT_EQ(state.GetOutputCharset(), EscapeAsJson);
}

// ==================== CurIndent ====================

TEST_F(EmitterStateTest_500, CurIndentInitial_500) {
  EXPECT_EQ(state.CurIndent(), 0u);
}

// ==================== SeqFmt and MapFmt independence ====================

TEST_F(EmitterStateTest_500, SeqAndMapFlowTypeIndependent_500) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);
  state.SetFlowType(GroupType::Map, Block, FmtScope::Global);
  EXPECT_EQ(state.GetFlowType(GroupType::Seq), Flow);
  EXPECT_EQ(state.GetFlowType(GroupType::Map), Block);
}

}  // namespace YAML
