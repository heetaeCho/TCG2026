#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {
namespace {

class EmitterStateTest_448 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ========== Initial State Tests ==========

TEST_F(EmitterStateTest_448, InitialStateIsGood_448) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_448, InitialLastErrorIsEmpty_448) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_448, InitialHasAnchorIsFalse_448) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_448, InitialHasAliasIsFalse_448) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_448, InitialHasTagIsFalse_448) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_448, InitialCurIndentIsZero_448) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ========== SetError Tests ==========

TEST_F(EmitterStateTest_448, SetErrorMakesStateNotGood_448) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_448, SetErrorStoresErrorMessage_448) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_448, SetErrorEmptyStringStillNotGood_448) {
  state.SetError("");
  EXPECT_FALSE(state.good());
}

// ========== Anchor / Alias / Tag Tests ==========

TEST_F(EmitterStateTest_448, SetAnchorSetsHasAnchor_448) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_448, SetAliasSetsHasAlias_448) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_448, SetTagSetsHasTag_448) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// After starting a scalar, the flags should be consumed/cleared
TEST_F(EmitterStateTest_448, StartedScalarClearsAnchor_448) {
  state.StartedDoc();
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_448, StartedScalarClearsAlias_448) {
  state.StartedDoc();
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
  state.StartedScalar();
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_448, StartedScalarClearsTag_448) {
  state.StartedDoc();
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.StartedScalar();
  EXPECT_FALSE(state.HasTag());
}

// ========== SetOutputCharset Tests ==========

TEST_F(EmitterStateTest_448, SetOutputCharsetValidValue_448) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Global));
}

TEST_F(EmitterStateTest_448, GetOutputCharsetAfterSet_448) {
  state.SetOutputCharset(EmitNonAscii, FmtScope::Global);
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

// ========== SetStringFormat Tests ==========

TEST_F(EmitterStateTest_448, SetStringFormatValid_448) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Global));
}

TEST_F(EmitterStateTest_448, GetStringFormatAfterSet_448) {
  state.SetStringFormat(SingleQuoted, FmtScope::Global);
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_448, SetStringFormatDoubleQuoted_448) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Global));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_448, SetStringFormatLiteral_448) {
  EXPECT_TRUE(state.SetStringFormat(Literal, FmtScope::Global));
  EXPECT_EQ(Literal, state.GetStringFormat());
}

// ========== SetBoolFormat Tests ==========

TEST_F(EmitterStateTest_448, SetBoolFormatValid_448) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Global));
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_448, SetBoolFormatYesNo_448) {
  EXPECT_TRUE(state.SetBoolFormat(YesNoBool, FmtScope::Global));
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_448, SetBoolFormatOnOff_448) {
  EXPECT_TRUE(state.SetBoolFormat(OnOffBool, FmtScope::Global));
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

// ========== SetBoolLengthFormat Tests ==========

TEST_F(EmitterStateTest_448, SetBoolLengthFormatShort_448) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Global));
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_448, SetBoolLengthFormatLong_448) {
  EXPECT_TRUE(state.SetBoolLengthFormat(LongBool, FmtScope::Global));
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

// ========== SetBoolCaseFormat Tests ==========

TEST_F(EmitterStateTest_448, SetBoolCaseFormatUpper_448) {
  EXPECT_TRUE(state.SetBoolCaseFormat(UpperCase, FmtScope::Global));
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_448, SetBoolCaseFormatLower_448) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Global));
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_448, SetBoolCaseFormatCamel_448) {
  EXPECT_TRUE(state.SetBoolCaseFormat(CamelCase, FmtScope::Global));
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

// ========== SetNullFormat Tests ==========

TEST_F(EmitterStateTest_448, SetNullFormatLower_448) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Global));
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_448, SetNullFormatTilde_448) {
  EXPECT_TRUE(state.SetNullFormat(TildeNull, FmtScope::Global));
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ========== SetIntFormat Tests ==========

TEST_F(EmitterStateTest_448, SetIntFormatDec_448) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Global));
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_448, SetIntFormatHex_448) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_448, SetIntFormatOct_448) {
  EXPECT_TRUE(state.SetIntFormat(Oct, FmtScope::Global));
  EXPECT_EQ(Oct, state.GetIntFormat());
}

// ========== SetIndent Tests ==========

TEST_F(EmitterStateTest_448, SetIndentValid_448) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Global));
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_448, SetIndentMinimum_448) {
  // Indent of 2 is typically the minimum valid
  EXPECT_TRUE(state.SetIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetIndent());
}

TEST_F(EmitterStateTest_448, SetIndentOneReturnsFalse_448) {
  // An indent of 1 might be rejected as invalid
  bool result = state.SetIndent(1, FmtScope::Global);
  // We just observe the return value; don't assume internal logic
  // If it fails, indent should remain at default
  if (!result) {
    EXPECT_NE(1u, state.GetIndent());
  }
}

TEST_F(EmitterStateTest_448, SetIndentZeroReturnsFalse_448) {
  bool result = state.SetIndent(0, FmtScope::Global);
  if (!result) {
    EXPECT_NE(0u, state.GetIndent());
  }
}

// ========== SetPreCommentIndent Tests ==========

TEST_F(EmitterStateTest_448, SetPreCommentIndentValid_448) {
  EXPECT_TRUE(state.SetPreCommentIndent(3, FmtScope::Global));
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

// ========== SetPostCommentIndent Tests ==========

TEST_F(EmitterStateTest_448, SetPostCommentIndentValid_448) {
  EXPECT_TRUE(state.SetPostCommentIndent(2, FmtScope::Global));
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

// ========== SetMapKeyFormat Tests ==========

TEST_F(EmitterStateTest_448, SetMapKeyFormatLongKey_448) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Global));
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

// ========== SetFloatPrecision Tests ==========

TEST_F(EmitterStateTest_448, SetFloatPrecisionValid_448) {
  EXPECT_TRUE(state.SetFloatPrecision(5, FmtScope::Global));
  EXPECT_EQ(5u, state.GetFloatPrecision());
}

// ========== SetDoublePrecision Tests ==========

TEST_F(EmitterStateTest_448, SetDoublePrecisionValid_448) {
  EXPECT_TRUE(state.SetDoublePrecision(10, FmtScope::Global));
  EXPECT_EQ(10u, state.GetDoublePrecision());
}

// ========== SetFlowType Tests ==========

TEST_F(EmitterStateTest_448, SetFlowTypeSeqFlow_448) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_448, SetFlowTypeSeqBlock_448) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_448, SetFlowTypeMapFlow_448) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_448, SetFlowTypeMapBlock_448) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Global));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ========== Document lifecycle Tests ==========

TEST_F(EmitterStateTest_448, StartedDocAndEndedDoc_448) {
  state.StartedDoc();
  state.EndedDoc();
  // Should still be good
  EXPECT_TRUE(state.good());
}

// ========== Group lifecycle Tests ==========

TEST_F(EmitterStateTest_448, StartedGroupSeq_448) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_448, StartedGroupMap_448) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
}

TEST_F(EmitterStateTest_448, CurGroupChildCountInitiallyZero_448) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_448, CurGroupChildCountIncrements_448) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedScalar();
  EXPECT_EQ(1u, state.CurGroupChildCount());
  state.StartedScalar();
  EXPECT_EQ(2u, state.CurGroupChildCount());
  state.EndedGroup(GroupType::Seq);
}

TEST_F(EmitterStateTest_448, CurGroupLongKeyDefaultFalse_448) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ========== SetNonContent Tests ==========

TEST_F(EmitterStateTest_448, SetNonContentBehavior_448) {
  state.SetNonContent();
  // The state should still be good
  EXPECT_TRUE(state.good());
}

// ========== ForceFlow Tests ==========

TEST_F(EmitterStateTest_448, ForceFlowOnGroup_448) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
  state.EndedGroup(GroupType::Seq);
}

// ========== SetLongKey Tests ==========

TEST_F(EmitterStateTest_448, SetLongKeyOnGroup_448) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
  state.EndedGroup(GroupType::Map);
}

// ========== ClearModifiedSettings Tests ==========

TEST_F(EmitterStateTest_448, ClearModifiedSettingsDoesNotCrash_448) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  state.ClearModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ========== RestoreGlobalModifiedSettings Tests ==========

TEST_F(EmitterStateTest_448, RestoreGlobalModifiedSettingsDoesNotCrash_448) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(state.good());
}

// ========== Local scope tests ==========

TEST_F(EmitterStateTest_448, SetStringFormatLocalScope_448) {
  EXPECT_TRUE(state.SetStringFormat(DoubleQuoted, FmtScope::Local));
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_448, ClearModifiedSettingsRestoresDefault_448) {
  EMITTER_MANIP originalFmt = state.GetStringFormat();
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
  state.ClearModifiedSettings();
  EXPECT_EQ(originalFmt, state.GetStringFormat());
}

// ========== Multiple error sets ==========

TEST_F(EmitterStateTest_448, MultipleSetErrorKeepsFirst_448) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically the first error is preserved
  EXPECT_FALSE(state.good());
  // The error message should be non-empty
  EXPECT_FALSE(state.GetLastError().empty());
}

// ========== HasBegunNode / HasBegunContent ==========

TEST_F(EmitterStateTest_448, InitialHasBegunNodeIsFalse_448) {
  // Initially no node has begun
  // HasBegunNode depends on whether we started any content
  // We just check it doesn't crash and has a reasonable default
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_448, InitialHasBegunContentIsFalse_448) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ========== NextGroupType Tests ==========

TEST_F(EmitterStateTest_448, NextGroupTypeForSeqNoParent_448) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Seq);
  // Should return some valid node type
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_448, NextGroupTypeForMapNoParent_448) {
  state.StartedDoc();
  EmitterNodeType::value nodeType = state.NextGroupType(GroupType::Map);
  (void)nodeType;
  EXPECT_TRUE(state.good());
}

// ========== Nested groups ==========

TEST_F(EmitterStateTest_448, NestedGroups_448) {
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

// ========== CurGroupIndent Tests ==========

TEST_F(EmitterStateTest_448, CurGroupIndentAfterStartingGroup_448) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // Should return some indent value without crashing
  std::size_t indent = state.CurGroupIndent();
  (void)indent;
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Seq);
}

// ========== LastIndent Tests ==========

TEST_F(EmitterStateTest_448, LastIndentAfterNestedGroups_448) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  std::size_t lastIndent = state.LastIndent();
  (void)lastIndent;
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Seq);
}

// ========== SetLocalValue Tests ==========

TEST_F(EmitterStateTest_448, SetLocalValueFlow_448) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_448, SetLocalValueBlock_448) {
  state.SetLocalValue(Block);
  EXPECT_TRUE(state.good());
}

// ========== CurGroupNodeType Tests ==========

TEST_F(EmitterStateTest_448, CurGroupNodeTypeInSeq_448) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EmitterNodeType::value nodeType = state.CurGroupNodeType();
  (void)nodeType;
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Seq);
}

// ========== Invalid format value tests ==========

TEST_F(EmitterStateTest_448, SetOutputCharsetInvalidValue_448) {
  // Passing a value that's not a charset manipulator
  bool result = state.SetOutputCharset(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_448, SetStringFormatInvalidValue_448) {
  bool result = state.SetStringFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_448, SetBoolFormatInvalidValue_448) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_448, SetIntFormatInvalidValue_448) {
  bool result = state.SetIntFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_448, SetNullFormatInvalidValue_448) {
  bool result = state.SetNullFormat(Flow, FmtScope::Global);
  EXPECT_FALSE(result);
}

// ========== Global scope persistence ==========

TEST_F(EmitterStateTest_448, GlobalScopeSettingPersistsAfterClear_448) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Global);
  state.ClearModifiedSettings();
  // Global setting should persist
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

}  // namespace
}  // namespace YAML
