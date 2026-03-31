#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_478 : public ::testing::Test {
 protected:
  EmitterState state;
};

// === Initial State Tests ===

TEST_F(EmitterStateTest_478, InitialStateIsGood_478) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_478, InitialCurIndentIsZero_478) {
  EXPECT_EQ(0u, state.CurIndent());
}

TEST_F(EmitterStateTest_478, InitialHasNoAnchor_478) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_478, InitialHasNoAlias_478) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_478, InitialHasNoTag_478) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_478, InitialGetLastErrorIsEmpty_478) {
  EXPECT_EQ("", state.GetLastError());
}

// === Error Handling Tests ===

TEST_F(EmitterStateTest_478, SetErrorMakesStateNotGood_478) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_478, SetErrorStoresErrorMessage_478) {
  state.SetError("some error message");
  EXPECT_EQ("some error message", state.GetLastError());
}

// === Anchor/Alias/Tag Tests ===

TEST_F(EmitterStateTest_478, SetAnchorSetsHasAnchor_478) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_478, SetAliasSetsHasAlias_478) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_478, SetTagSetsHasTag_478) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// === Document Tests ===

TEST_F(EmitterStateTest_478, StartedDocDoesNotBreakState_478) {
  state.StartedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_478, EndedDocDoesNotBreakState_478) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// === Group Tests (Sequences) ===

TEST_F(EmitterStateTest_478, StartedGroupSeqSetsGroupType_478) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_478, StartedGroupMapSetsGroupType_478) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_478, CurGroupChildCountInitiallyZero_478) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_478, CurGroupIndentMatchesGetIndent_478) {
  state.StartedDoc();
  std::size_t expectedIndent = state.GetIndent();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(expectedIndent, state.CurGroupIndent());
}

TEST_F(EmitterStateTest_478, EndedGroupReturnsToParentState_478) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_478, NestedGroupsTrackIndent_478) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  std::size_t indent1 = state.CurIndent();
  state.StartedScalar();  // Add a child to the seq
  state.StartedGroup(GroupType::Map);
  std::size_t indent2 = state.CurIndent();
  // Nested group should have greater or equal indentation
  EXPECT_GE(indent2, indent1);
}

// === Flow Type Tests ===

TEST_F(EmitterStateTest_478, SetFlowTypeForSeqReturnsTrue_478) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
}

TEST_F(EmitterStateTest_478, SetFlowTypeForMapReturnsTrue_478) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
}

TEST_F(EmitterStateTest_478, FlowGroupHasFlowFlowType_478) {
  state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local);
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

TEST_F(EmitterStateTest_478, BlockGroupHasBlockFlowType_478) {
  state.SetFlowType(GroupType::Seq, Block, FmtScope::Local);
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(FlowType::Block, state.CurGroupFlowType());
}

TEST_F(EmitterStateTest_478, ForceFlowAffectsNextGroup_478) {
  state.ForceFlow();
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// === LongKey Tests ===

TEST_F(EmitterStateTest_478, CurGroupLongKeyInitiallyFalse_478) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// === Setting Format Tests ===

TEST_F(EmitterStateTest_478, SetOutputCharsetReturnsTrue_478) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_478, SetStringFormatReturnsTrue_478) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_478, SetBoolFormatReturnsTrue_478) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_478, SetBoolLengthFormatReturnsTrue_478) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_478, SetBoolCaseFormatReturnsTrue_478) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_478, SetNullFormatReturnsTrue_478) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_478, SetIntFormatReturnsTrue_478) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Local));
}

TEST_F(EmitterStateTest_478, SetIndentReturnsTrue_478) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
}

TEST_F(EmitterStateTest_478, SetPreCommentIndentReturnsTrue_478) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_478, SetPostCommentIndentReturnsTrue_478) {
  EXPECT_TRUE(state.SetPostCommentIndent(1, FmtScope::Local));
}

TEST_F(EmitterStateTest_478, SetMapKeyFormatReturnsTrue_478) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Local));
}

TEST_F(EmitterStateTest_478, SetFloatPrecisionReturnsTrue_478) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Local));
}

TEST_F(EmitterStateTest_478, SetDoublePrecisionReturnsTrue_478) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Local));
}

// === Getter Tests ===

TEST_F(EmitterStateTest_478, GetOutputCharsetReturnsValue_478) {
  state.SetOutputCharset(EscapeNonAscii, FmtScope::Local);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_478, GetStringFormatReturnsValue_478) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_478, GetBoolFormatReturnsValue_478) {
  state.SetBoolFormat(TrueFalseBool, FmtScope::Local);
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_478, GetBoolLengthFormatReturnsValue_478) {
  state.SetBoolLengthFormat(ShortBool, FmtScope::Local);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_478, GetBoolCaseFormatReturnsValue_478) {
  state.SetBoolCaseFormat(LowerCase, FmtScope::Local);
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_478, GetNullFormatReturnsValue_478) {
  state.SetNullFormat(UpperNull, FmtScope::Local);
  EXPECT_EQ(UpperNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_478, GetIntFormatReturnsValue_478) {
  state.SetIntFormat(Oct, FmtScope::Local);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_478, GetIndentReturnsSetValue_478) {
  state.SetIndent(4, FmtScope::Local);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_478, GetPreCommentIndentReturnsValue_478) {
  state.SetPreCommentIndent(3, FmtScope::Local);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_478, GetPostCommentIndentReturnsValue_478) {
  state.SetPostCommentIndent(5, FmtScope::Local);
  EXPECT_EQ(5u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_478, GetMapKeyFormatReturnsValue_478) {
  state.SetMapKeyFormat(LongKey, FmtScope::Local);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_478, GetFloatPrecisionReturnsValue_478) {
  state.SetFloatPrecision(7, FmtScope::Local);
  EXPECT_EQ(7u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_478, GetDoublePrecisionReturnsValue_478) {
  state.SetDoublePrecision(12, FmtScope::Local);
  EXPECT_EQ(12u, state.GetDoublePrecision());
}

// === Scope Tests ===

TEST_F(EmitterStateTest_478, GlobalScopeSettingPersists_478) {
  state.SetIndent(6, FmtScope::Global);
  EXPECT_EQ(6u, state.GetIndent());
}

// === NextGroupType Tests ===

TEST_F(EmitterStateTest_478, NextGroupTypeForSeqWithoutGroup_478) {
  state.StartedDoc();
  auto nodeType = state.NextGroupType(GroupType::Seq);
  // Should return some valid EmitterNodeType value
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_478, NextGroupTypeForMapWithoutGroup_478) {
  state.StartedDoc();
  auto nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// === StartedScalar Tests ===

TEST_F(EmitterStateTest_478, StartedScalarKeepsStateGood_478) {
  state.StartedDoc();
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

// === Multiple Groups Tests ===

TEST_F(EmitterStateTest_478, MultipleNestedGroupsCanBeCreatedAndEnded_478) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  state.StartedGroup(GroupType::Map);
  state.StartedScalar();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// === LastIndent Tests ===

TEST_F(EmitterStateTest_478, LastIndentWithNoGroupsReturnsZero_478) {
  EXPECT_EQ(0u, state.LastIndent());
}

TEST_F(EmitterStateTest_478, LastIndentAfterGroupStarted_478) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // LastIndent should be defined - just check it doesn't crash
  std::size_t lastIndent = state.LastIndent();
  (void)lastIndent;
  EXPECT_TRUE(state.good());
}

// === ClearModifiedSettings Tests ===

TEST_F(EmitterStateTest_478, ClearModifiedSettingsDoesNotBreakState_478) {
  state.SetIndent(4, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// === SetNonContent Tests ===

TEST_F(EmitterStateTest_478, SetNonContentDoesNotBreakState_478) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// === HasBegunNode / HasBegunContent Tests ===

TEST_F(EmitterStateTest_478, HasBegunNodeInitiallyFalse_478) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_478, HasBegunContentInitiallyFalse_478) {
  EXPECT_FALSE(state.HasBegunContent());
}

// === SetIndent Boundary Tests ===

TEST_F(EmitterStateTest_478, SetIndentZero_478) {
  // Indent of 0 may or may not be valid
  bool result = state.SetIndent(0, FmtScope::Local);
  (void)result;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_478, SetIndentOne_478) {
  bool result = state.SetIndent(1, FmtScope::Local);
  (void)result;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_478, SetIndentLargeValue_478) {
  bool result = state.SetIndent(100, FmtScope::Local);
  (void)result;
  EXPECT_TRUE(state.good());
}

// === SetLongKey Tests ===

TEST_F(EmitterStateTest_478, SetLongKeyDoesNotBreakState_478) {
  state.SetLongKey();
  EXPECT_TRUE(state.good());
}

// === RestoreGlobalModifiedSettings Tests ===

TEST_F(EmitterStateTest_478, RestoreGlobalModifiedSettingsDoesNotBreak_478) {
  state.SetIndent(8, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// === Interaction: SetFlowType invalid value ===

TEST_F(EmitterStateTest_478, SetFlowTypeInvalidManipReturnsFalse_478) {
  // Using a EMITTER_MANIP that is not Flow or Block
  bool result = state.SetFlowType(GroupType::Seq, Dec, FmtScope::Local);
  EXPECT_FALSE(result);
}

// === Interaction: SetOutputCharset with invalid value ===

TEST_F(EmitterStateTest_478, SetOutputCharsetInvalidValueReturnsFalse_478) {
  bool result = state.SetOutputCharset(Dec, FmtScope::Local);
  EXPECT_FALSE(result);
}

// === Interaction: SetStringFormat invalid ===

TEST_F(EmitterStateTest_478, SetStringFormatInvalidReturnsFalse_478) {
  bool result = state.SetStringFormat(Dec, FmtScope::Local);
  EXPECT_FALSE(result);
}

// === Interaction: SetBoolFormat invalid ===

TEST_F(EmitterStateTest_478, SetBoolFormatInvalidReturnsFalse_478) {
  bool result = state.SetBoolFormat(Dec, FmtScope::Local);
  EXPECT_FALSE(result);
}

// === Interaction: SetIntFormat invalid ===

TEST_F(EmitterStateTest_478, SetIntFormatInvalidReturnsFalse_478) {
  bool result = state.SetIntFormat(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

// === CurGroupNodeType without group ===

TEST_F(EmitterStateTest_478, CurGroupNodeTypeNoGroup_478) {
  auto nodeType = state.CurGroupNodeType();
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

}  // namespace YAML
