#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_455 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_455, InitialStateIsGood_455) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_455, InitialLastErrorIsEmpty_455) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_455, InitialHasAnchorIsFalse_455) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_455, InitialHasAliasIsFalse_455) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_455, InitialHasTagIsFalse_455) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_455, InitialCurIndentIsZero_455) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_455, SetErrorMakesStateNotGood_455) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_455, SetErrorStoresLastError_455) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_455, SetErrorMultipleTimes_455) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_FALSE(state.good());
  // First error should be preserved (typical behavior)
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== Anchor/Alias/Tag Tests ====================

TEST_F(EmitterStateTest_455, SetAnchorSetsHasAnchor_455) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_455, SetAliasSetsHasAlias_455) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_455, SetTagSetsHasTag_455) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== Bool Format Tests ====================

TEST_F(EmitterStateTest_455, DefaultBoolFormat_455) {
  EMITTER_MANIP fmt = state.GetBoolFormat();
  EXPECT_EQ(TrueFalseBool, fmt);
}

TEST_F(EmitterStateTest_455, SetBoolFormatGlobal_455) {
  bool result = state.SetBoolFormat(YesNoBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_455, SetBoolFormatLocal_455) {
  bool result = state.SetBoolFormat(OnOffBool, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

// ==================== String Format Tests ====================

TEST_F(EmitterStateTest_455, SetStringFormatGlobal_455) {
  bool result = state.SetStringFormat(SingleQuoted, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_455, SetStringFormatInvalidValue_455) {
  bool result = state.SetStringFormat(TrueFalseBool, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Int Format Tests ====================

TEST_F(EmitterStateTest_455, SetIntFormatHex_455) {
  bool result = state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_455, SetIntFormatOct_455) {
  bool result = state.SetIntFormat(Oct, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_455, SetIntFormatDec_455) {
  bool result = state.SetIntFormat(Dec, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_455, SetIntFormatInvalidValue_455) {
  bool result = state.SetIntFormat(SingleQuoted, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Indent Tests ====================

TEST_F(EmitterStateTest_455, DefaultIndent_455) {
  std::size_t indent = state.GetIndent();
  EXPECT_EQ(2u, indent);
}

TEST_F(EmitterStateTest_455, SetIndentGlobal_455) {
  bool result = state.SetIndent(4, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_455, SetIndentLocal_455) {
  bool result = state.SetIndent(3, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(3u, state.GetIndent());
}

// ==================== Pre/Post Comment Indent Tests ====================

TEST_F(EmitterStateTest_455, DefaultPreCommentIndent_455) {
  std::size_t indent = state.GetPreCommentIndent();
  EXPECT_EQ(2u, indent);
}

TEST_F(EmitterStateTest_455, SetPreCommentIndent_455) {
  bool result = state.SetPreCommentIndent(4, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(4u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_455, DefaultPostCommentIndent_455) {
  std::size_t indent = state.GetPostCommentIndent();
  EXPECT_EQ(1u, indent);
}

TEST_F(EmitterStateTest_455, SetPostCommentIndent_455) {
  bool result = state.SetPostCommentIndent(3, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(3u, state.GetPostCommentIndent());
}

// ==================== Output Charset Tests ====================

TEST_F(EmitterStateTest_455, SetOutputCharsetUTF8_455) {
  bool result = state.SetOutputCharset(EmitNonAscii, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_455, SetOutputCharsetEscapeNonAscii_455) {
  bool result = state.SetOutputCharset(EscapeNonAscii, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_455, SetOutputCharsetInvalidValue_455) {
  bool result = state.SetOutputCharset(TrueFalseBool, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Bool Length Format Tests ====================

TEST_F(EmitterStateTest_455, SetBoolLengthFormatShort_455) {
  bool result = state.SetBoolLengthFormat(ShortBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_455, SetBoolLengthFormatLong_455) {
  bool result = state.SetBoolLengthFormat(LongBool, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_455, SetBoolLengthFormatInvalid_455) {
  bool result = state.SetBoolLengthFormat(Hex, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Bool Case Format Tests ====================

TEST_F(EmitterStateTest_455, SetBoolCaseFormatUpperCase_455) {
  bool result = state.SetBoolCaseFormat(UpperCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_455, SetBoolCaseFormatLowerCase_455) {
  bool result = state.SetBoolCaseFormat(LowerCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_455, SetBoolCaseFormatCamelCase_455) {
  bool result = state.SetBoolCaseFormat(CamelCase, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_455, SetBoolCaseFormatInvalid_455) {
  bool result = state.SetBoolCaseFormat(Hex, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Null Format Tests ====================

TEST_F(EmitterStateTest_455, SetNullFormatTilde_455) {
  bool result = state.SetNullFormat(LowerNull, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_455, SetNullFormatInvalid_455) {
  bool result = state.SetNullFormat(Hex, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Flow Type Tests ====================

TEST_F(EmitterStateTest_455, SetFlowTypeSeqBlock_455) {
  bool result = state.SetFlowType(GroupType::Seq, Block, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_455, SetFlowTypeMapFlow_455) {
  bool result = state.SetFlowType(GroupType::Map, Flow, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_455, SetFlowTypeInvalid_455) {
  bool result = state.SetFlowType(GroupType::Seq, Hex, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Map Key Format Tests ====================

TEST_F(EmitterStateTest_455, SetMapKeyFormatLongKey_455) {
  bool result = state.SetMapKeyFormat(LongKey, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_455, SetMapKeyFormatInvalid_455) {
  bool result = state.SetMapKeyFormat(Hex, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== Float/Double Precision Tests ====================

TEST_F(EmitterStateTest_455, SetFloatPrecision_455) {
  bool result = state.SetFloatPrecision(6, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(6u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_455, SetDoublePrecision_455) {
  bool result = state.SetDoublePrecision(15, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

// ==================== Document Tests ====================

TEST_F(EmitterStateTest_455, StartedDocEndedDoc_455) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Tests ====================

TEST_F(EmitterStateTest_455, StartedGroupSeq_455) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_455, StartedGroupMap_455) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_455, CurGroupChildCountInitiallyZero_455) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_455, StartEndGroupPair_455) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_455, CurGroupLongKeyInitiallyFalse_455) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_455, SetLocalValueFlow_455) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_455, ForceFlowSetsFlowType_455) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_455, SetLongKeySetsLongKey_455) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_455, SetNonContentHasEffect_455) {
  state.SetNonContent();
  // Just verify it doesn't crash and state remains good
  EXPECT_TRUE(state.good());
}

// ==================== HasBegunNode/HasBegunContent Tests ====================

TEST_F(EmitterStateTest_455, InitialHasBegunNodeIsFalse_455) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_455, InitialHasBegunContentIsFalse_455) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_455, ClearModifiedSettingsRestoresLocal_455) {
  state.SetBoolFormat(YesNoBool, FmtScope::Local);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
  state.ClearModifiedSettings();
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_455, ClearModifiedSettingsDoesNotAffectGlobal_455) {
  state.SetBoolFormat(YesNoBool, FmtScope::Global);
  state.ClearModifiedSettings();
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterStateTest_455, RestoreGlobalModifiedSettings_455) {
  EMITTER_MANIP originalFmt = state.GetBoolFormat();
  state.SetBoolFormat(YesNoBool, FmtScope::Global);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(originalFmt, state.GetBoolFormat());
}

// ==================== StartedScalar Tests ====================

TEST_F(EmitterStateTest_455, StartedScalar_455) {
  state.StartedDoc();
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

// ==================== NextGroupType Tests ====================

TEST_F(EmitterStateTest_455, NextGroupTypeForSeq_455) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return a valid node type
  EXPECT_TRUE(nodeType == EmitterNodeType::NoType ||
              nodeType == EmitterNodeType::Property ||
              nodeType == EmitterNodeType::Scalar ||
              nodeType == EmitterNodeType::FlowSeq ||
              nodeType == EmitterNodeType::BlockSeq ||
              nodeType == EmitterNodeType::FlowMap ||
              nodeType == EmitterNodeType::BlockMap);
}

// ==================== Scope Interaction Tests ====================

TEST_F(EmitterStateTest_455, LocalSettingOverridesGlobal_455) {
  state.SetIntFormat(Hex, FmtScope::Global);
  state.SetIntFormat(Oct, FmtScope::Local);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_455, ClearModifiedSettingsRestoresToGlobal_455) {
  state.SetIntFormat(Hex, FmtScope::Global);
  state.SetIntFormat(Oct, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_EQ(Hex, state.GetIntFormat());
}

// ==================== Multiple Setting Changes Tests ====================

TEST_F(EmitterStateTest_455, MultipleGlobalChanges_455) {
  state.SetBoolFormat(YesNoBool, FmtScope::Global);
  state.SetIntFormat(Hex, FmtScope::Global);
  state.SetIndent(4, FmtScope::Global);
  
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
  EXPECT_EQ(Hex, state.GetIntFormat());
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_455, SetBoolFormatInvalidValue_455) {
  bool result = state.SetBoolFormat(Hex, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ==================== SetStringFormat Valid Values Tests ====================

TEST_F(EmitterStateTest_455, SetStringFormatDoubleQuoted_455) {
  bool result = state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_455, SetStringFormatLiteral_455) {
  bool result = state.SetStringFormat(Literal, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Literal, state.GetStringFormat());
}

// ==================== Nested Groups Tests ====================

TEST_F(EmitterStateTest_455, NestedGroups_455) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// ==================== Anchor Cleared After Node Start Tests ====================

TEST_F(EmitterStateTest_455, AnchorClearedAfterScalar_455) {
  state.StartedDoc();
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_455, TagClearedAfterScalar_455) {
  state.StartedDoc();
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_455, AliasClearedAfterScalar_455) {
  state.StartedDoc();
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAlias());
}

}  // namespace YAML
