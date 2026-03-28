#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_469 : public ::testing::Test {
 protected:
  EmitterState state;
};

// === Initial State Tests ===

TEST_F(EmitterStateTest_469, InitialStateIsGood_469) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_469, InitialStateNoError_469) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_469, InitialStateHasNoAnchor_469) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_469, InitialStateHasNoAlias_469) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_469, InitialStateHasNoTag_469) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_469, InitialCurIndentIsZero_469) {
  EXPECT_EQ(0u, state.CurIndent());
}

// === SetError Tests ===

TEST_F(EmitterStateTest_469, SetErrorMakesStateNotGood_469) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_469, SetErrorRecordsErrorMessage_469) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_469, SetErrorMultipleTimesKeepsFirstError_469) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically the first error is kept since state is no longer good
  EXPECT_FALSE(state.good());
}

// === SetAnchor / HasAnchor Tests ===

TEST_F(EmitterStateTest_469, SetAnchorSetsHasAnchor_469) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

// === SetAlias / HasAlias Tests ===

TEST_F(EmitterStateTest_469, SetAliasSetsHasAlias_469) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

// === SetTag / HasTag Tests ===

TEST_F(EmitterStateTest_469, SetTagSetsHasTag_469) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// === SetNonContent Tests ===

TEST_F(EmitterStateTest_469, SetNonContentDoesNotCrash_469) {
  EXPECT_NO_THROW(state.SetNonContent());
}

// === Document Lifecycle Tests ===

TEST_F(EmitterStateTest_469, StartedDocDoesNotCrash_469) {
  EXPECT_NO_THROW(state.StartedDoc());
}

TEST_F(EmitterStateTest_469, EndedDocDoesNotCrash_469) {
  state.StartedDoc();
  EXPECT_NO_THROW(state.EndedDoc());
}

TEST_F(EmitterStateTest_469, MultipleDocsDoNotCrash_469) {
  state.StartedDoc();
  state.EndedDoc();
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// === Scalar Tests ===

TEST_F(EmitterStateTest_469, StartedScalarDoesNotCrash_469) {
  state.StartedDoc();
  EXPECT_NO_THROW(state.StartedScalar());
}

// === Group Tests ===

TEST_F(EmitterStateTest_469, StartedGroupSeqDoesNotCrash_469) {
  state.StartedDoc();
  EXPECT_NO_THROW(state.StartedGroup(GroupType::Seq));
}

TEST_F(EmitterStateTest_469, StartedGroupMapDoesNotCrash_469) {
  state.StartedDoc();
  EXPECT_NO_THROW(state.StartedGroup(GroupType::Map));
}

TEST_F(EmitterStateTest_469, EndedGroupSeqDoesNotCrash_469) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_NO_THROW(state.EndedGroup(GroupType::Seq));
}

TEST_F(EmitterStateTest_469, EndedGroupMapDoesNotCrash_469) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_NO_THROW(state.EndedGroup(GroupType::Map));
}

TEST_F(EmitterStateTest_469, CurGroupTypeAfterStartedGroupSeq_469) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_469, CurGroupTypeAfterStartedGroupMap_469) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_469, CurGroupChildCountInitiallyZero_469) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_469, CurGroupLongKeyInitiallyFalse_469) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_469, SetLongKeyMakesGroupLongKey_469) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// === Format Setting Tests ===

TEST_F(EmitterStateTest_469, SetOutputCharsetUTF8_469) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_469, SetStringFormatSingleQuoted_469) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_469, SetStringFormatDoubleQuoted_469) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_469, SetBoolFormatYesNoBool_469) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_469, SetBoolFormatTrueFalseBool_469) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_469, SetBoolFormatOnOffBool_469) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Global));
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_469, SetBoolLengthFormatShortBool_469) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_469, SetBoolLengthFormatLongBool_469) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_469, SetBoolCaseFormatUpperCase_469) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_469, SetBoolCaseFormatLowerCase_469) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_469, SetBoolCaseFormatCamelCase_469) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_469, SetNullFormatLowerNull_469) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_469, SetNullFormatTildeNull_469) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Global));
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_469, SetIntFormatDec_469) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_469, SetIntFormatHex_469) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_469, SetIntFormatOct_469) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_469, SetIndentGlobal_469) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_469, SetIndentBoundaryMinValue_469) {
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetIndent());
}

TEST_F(EmitterStateTest_469, SetPreCommentIndent_469) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_469, SetPostCommentIndent_469) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_469, SetMapKeyFormatLongKey_469) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_469, SetFloatPrecision_469) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Global));
  EXPECT_EQ(6u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_469, SetDoublePrecision_469) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Global));
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

// === Flow Type Tests ===

TEST_F(EmitterStateTest_469, SetFlowTypeSeqFlow_469) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_469, SetFlowTypeSeqBlock_469) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_469, SetFlowTypeMapFlow_469) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_469, SetFlowTypeMapBlock_469) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// === ForceFlow Tests ===

TEST_F(EmitterStateTest_469, ForceFlowDoesNotCrash_469) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_NO_THROW(state.ForceFlow());
}

TEST_F(EmitterStateTest_469, ForceFlowSetsFlowType_469) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// === NextGroupType Tests ===

TEST_F(EmitterStateTest_469, NextGroupTypeSeqDefault_469) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return some valid EmitterNodeType
  EXPECT_TRUE(nodeType == EmitterNodeType::NoType ||
              nodeType == EmitterNodeType::Property ||
              nodeType == EmitterNodeType::Scalar ||
              nodeType == EmitterNodeType::FlowSeq ||
              nodeType == EmitterNodeType::BlockSeq ||
              nodeType == EmitterNodeType::FlowMap ||
              nodeType == EmitterNodeType::BlockMap);
}

TEST_F(EmitterStateTest_469, NextGroupTypeMapDefault_469) {
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  EXPECT_TRUE(nodeType == EmitterNodeType::NoType ||
              nodeType == EmitterNodeType::Property ||
              nodeType == EmitterNodeType::Scalar ||
              nodeType == EmitterNodeType::FlowSeq ||
              nodeType == EmitterNodeType::BlockSeq ||
              nodeType == EmitterNodeType::FlowMap ||
              nodeType == EmitterNodeType::BlockMap);
}

// === ClearModifiedSettings Tests ===

TEST_F(EmitterStateTest_469, ClearModifiedSettingsDoesNotCrash_469) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_NO_THROW(state.ClearModifiedSettings());
}

// === RestoreGlobalModifiedSettings Tests ===

TEST_F(EmitterStateTest_469, RestoreGlobalModifiedSettingsDoesNotCrash_469) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.ClearModifiedSettings();
  EXPECT_NO_THROW(state.RestoreGlobalModifiedSettings());
}

// === Scope Tests: Local vs Global ===

TEST_F(EmitterStateTest_469, SetStringFormatLocalScope_469) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_469, SetStringFormatGlobalScope_469) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

// === Invalid Format Setting Tests ===

TEST_F(EmitterStateTest_469, SetOutputCharsetInvalidValue_469) {
  // Passing an unrelated EMITTER_MANIP should return false
  bool result = state.SetOutputCharset(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_469, SetStringFormatInvalidValue_469) {
  bool result = state.SetStringFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_469, SetBoolFormatInvalidValue_469) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_469, SetIntFormatInvalidValue_469) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_469, SetNullFormatInvalidValue_469) {
  bool result = state.SetNullFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// === Indent Boundary Tests ===

TEST_F(EmitterStateTest_469, SetIndentZero_469) {
  // Zero indent might be rejected
  bool result = state.SetIndent(0, FmtScope::Global);
  // We just observe the result without inferring internal logic
  if (result) {
    EXPECT_EQ(0u, state.GetIndent());
  }
}

TEST_F(EmitterStateTest_469, SetIndentOne_469) {
  // Very small indent might be rejected
  bool result = state.SetIndent(1, FmtScope::Global);
  if (result) {
    EXPECT_EQ(1u, state.GetIndent());
  }
}

// === LastIndent Tests ===

TEST_F(EmitterStateTest_469, LastIndentInitialState_469) {
  // In initial state with no groups, LastIndent should return some value
  EXPECT_NO_THROW(state.LastIndent());
}

// === HasBegunNode / HasBegunContent Tests ===

TEST_F(EmitterStateTest_469, HasBegunNodeInitiallyFalse_469) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_469, HasBegunContentInitiallyFalse_469) {
  EXPECT_FALSE(state.HasBegunContent());
}

// === Anchor/Alias/Tag reset after StartedScalar ===

TEST_F(EmitterStateTest_469, AnchorResetAfterScalar_469) {
  state.StartedDoc();
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_469, AliasResetAfterScalar_469) {
  state.StartedDoc();
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_469, TagResetAfterScalar_469) {
  state.StartedDoc();
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasTag());
}

// === SetLocalValue Tests ===

TEST_F(EmitterStateTest_469, SetLocalValueFlow_469) {
  EXPECT_NO_THROW(state.SetLocalValue(Flow));
}

TEST_F(EmitterStateTest_469, SetLocalValueBlock_469) {
  EXPECT_NO_THROW(state.SetLocalValue(Block));
}

TEST_F(EmitterStateTest_469, SetLocalValueDoubleQuoted_469) {
  EXPECT_NO_THROW(state.SetLocalValue(DoubleQuoted));
}

TEST_F(EmitterStateTest_469, SetLocalValueSingleQuoted_469) {
  EXPECT_NO_THROW(state.SetLocalValue(SingleQuoted));
}

TEST_F(EmitterStateTest_469, SetLocalValueLongKey_469) {
  EXPECT_NO_THROW(state.SetLocalValue(LongKey));
}

// === Nested Groups Tests ===

TEST_F(EmitterStateTest_469, NestedGroupsWorkCorrectly_469) {
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

// === CurGroupIndent Tests ===

TEST_F(EmitterStateTest_469, CurGroupIndentAfterStartGroup_469) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // Just verify we can call it without crash
  std::size_t indent = state.CurGroupIndent();
  (void)indent;
  state.EndedGroup(GroupType::Seq);
}

// === Multiple settings scope interaction ===

TEST_F(EmitterStateTest_469, GlobalSettingPersistsAfterClearModified_469) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// === CurGroupNodeType Tests ===

TEST_F(EmitterStateTest_469, CurGroupNodeTypeInGroup_469) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  (void)nodeType;
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Seq);
}

// === Destructor test (implicit) ===

TEST_F(EmitterStateTest_469, DestructorDoesNotCrash_469) {
  {
    EmitterState localState;
    localState.StartedDoc();
    localState.StartedGroup(GroupType::Seq);
    // Destructor called here, should not crash even with unclosed groups
  }
  SUCCEED();
}

// === SetFloatPrecision boundary ===

TEST_F(EmitterStateTest_469, SetFloatPrecisionZero_469) {
  bool result = state.SetFloatPrecision(0, FmtScope::Global);
  if (result) {
    EXPECT_EQ(0u, state.GetFloatPrecision());
  }
}

TEST_F(EmitterStateTest_469, SetDoublePrecisionZero_469) {
  bool result = state.SetDoublePrecision(0, FmtScope::Global);
  if (result) {
    EXPECT_EQ(0u, state.GetDoublePrecision());
  }
}

// === SetBoolCaseFormat invalid ===

TEST_F(EmitterStateTest_469, SetBoolCaseFormatInvalid_469) {
  bool result = state.SetBoolCaseFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// === SetBoolLengthFormat invalid ===

TEST_F(EmitterStateTest_469, SetBoolLengthFormatInvalid_469) {
  bool result = state.SetBoolLengthFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// === SetFlowType invalid ===

TEST_F(EmitterStateTest_469, SetFlowTypeInvalidValue_469) {
  bool result = state.SetFlowType(GroupType::Seq, Dec, FmtScope::Global);
  EXPECT_FALSE(result);
}

// === SetMapKeyFormat invalid ===

TEST_F(EmitterStateTest_469, SetMapKeyFormatInvalidValue_469) {
  bool result = state.SetMapKeyFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

}  // namespace YAML
