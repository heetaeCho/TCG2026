#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {

class EmitterStateTest_459 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ==================== Initial State Tests ====================

TEST_F(EmitterStateTest_459, InitialStateIsGood_459) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_459, InitialLastErrorIsEmpty_459) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_459, InitialHasNoAnchor_459) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_459, InitialHasNoAlias_459) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_459, InitialHasNoTag_459) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_459, InitialHasNotBegunNode_459) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_459, InitialHasNotBegunContent_459) {
  EXPECT_FALSE(state.HasBegunContent());
}

// ==================== Default Format Getters ====================

TEST_F(EmitterStateTest_459, DefaultIntFormatIsDec_459) {
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_459, DefaultGetIndentReturnsNonZero_459) {
  EXPECT_GT(state.GetIndent(), 0u);
}

TEST_F(EmitterStateTest_459, DefaultGetPreCommentIndentReturnsValue_459) {
  EXPECT_GE(state.GetPreCommentIndent(), 0u);
}

TEST_F(EmitterStateTest_459, DefaultGetPostCommentIndentReturnsValue_459) {
  EXPECT_GE(state.GetPostCommentIndent(), 0u);
}

TEST_F(EmitterStateTest_459, DefaultGetStringFormatReturnsValue_459) {
  // Just ensure it returns without crashing
  EMITTER_MANIP fmt = state.GetStringFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_459, DefaultGetBoolFormatReturnsValue_459) {
  EMITTER_MANIP fmt = state.GetBoolFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_459, DefaultGetBoolLengthFormatReturnsValue_459) {
  EMITTER_MANIP fmt = state.GetBoolLengthFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_459, DefaultGetBoolCaseFormatReturnsValue_459) {
  EMITTER_MANIP fmt = state.GetBoolCaseFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_459, DefaultGetNullFormatReturnsValue_459) {
  EMITTER_MANIP fmt = state.GetNullFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_459, DefaultGetOutputCharsetReturnsValue_459) {
  EMITTER_MANIP fmt = state.GetOutputCharset();
  (void)fmt;
}

TEST_F(EmitterStateTest_459, DefaultGetMapKeyFormatReturnsValue_459) {
  EMITTER_MANIP fmt = state.GetMapKeyFormat();
  (void)fmt;
}

TEST_F(EmitterStateTest_459, DefaultGetFloatPrecisionReturnsValue_459) {
  std::size_t prec = state.GetFloatPrecision();
  (void)prec;
}

TEST_F(EmitterStateTest_459, DefaultGetDoublePrecisionReturnsValue_459) {
  std::size_t prec = state.GetDoublePrecision();
  (void)prec;
}

// ==================== SetError Tests ====================

TEST_F(EmitterStateTest_459, SetErrorMakesStateNotGood_459) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_459, SetErrorSetsLastError_459) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_459, SetErrorEmptyStringStillMakesNotGood_459) {
  state.SetError("");
  EXPECT_FALSE(state.good());
}

// ==================== SetAnchor / SetAlias / SetTag Tests ====================

TEST_F(EmitterStateTest_459, SetAnchorSetsHasAnchor_459) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_459, SetAliasSetsHasAlias_459) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_459, SetTagSetsHasTag_459) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

// ==================== SetIntFormat Tests ====================

TEST_F(EmitterStateTest_459, SetIntFormatToHex_459) {
  bool result = state.SetIntFormat(Hex, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_459, SetIntFormatToOct_459) {
  bool result = state.SetIntFormat(Oct, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_459, SetIntFormatToDec_459) {
  state.SetIntFormat(Hex, FmtScope::Local);
  bool result = state.SetIntFormat(Dec, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(Dec, state.GetIntFormat());
}

TEST_F(EmitterStateTest_459, SetIntFormatInvalidValueReturnsFalse_459) {
  // Passing a value that's not a valid int format
  bool result = state.SetIntFormat(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_459, SetIntFormatGlobalScope_459) {
  bool result = state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_TRUE(result);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

// ==================== SetBoolFormat Tests ====================

TEST_F(EmitterStateTest_459, SetBoolFormatTrueFalse_459) {
  bool result = state.SetBoolFormat(TrueFalseBool, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(TrueFalseBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_459, SetBoolFormatYesNo_459) {
  bool result = state.SetBoolFormat(YesNoBool, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(YesNoBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_459, SetBoolFormatOnOff_459) {
  bool result = state.SetBoolFormat(OnOffBool, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(OnOffBool, state.GetBoolFormat());
}

TEST_F(EmitterStateTest_459, SetBoolFormatInvalid_459) {
  bool result = state.SetBoolFormat(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetBoolLengthFormat Tests ====================

TEST_F(EmitterStateTest_459, SetBoolLengthFormatShort_459) {
  bool result = state.SetBoolLengthFormat(ShortBool, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(ShortBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_459, SetBoolLengthFormatLong_459) {
  bool result = state.SetBoolLengthFormat(LongBool, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongBool, state.GetBoolLengthFormat());
}

TEST_F(EmitterStateTest_459, SetBoolLengthFormatInvalid_459) {
  bool result = state.SetBoolLengthFormat(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetBoolCaseFormat Tests ====================

TEST_F(EmitterStateTest_459, SetBoolCaseFormatUpper_459) {
  bool result = state.SetBoolCaseFormat(UpperCase, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(UpperCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_459, SetBoolCaseFormatLower_459) {
  bool result = state.SetBoolCaseFormat(LowerCase, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_459, SetBoolCaseFormatCamel_459) {
  bool result = state.SetBoolCaseFormat(CamelCase, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(CamelCase, state.GetBoolCaseFormat());
}

TEST_F(EmitterStateTest_459, SetBoolCaseFormatInvalid_459) {
  bool result = state.SetBoolCaseFormat(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetStringFormat Tests ====================

TEST_F(EmitterStateTest_459, SetStringFormatSingleQuoted_459) {
  bool result = state.SetStringFormat(SingleQuoted, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_459, SetStringFormatDoubleQuoted_459) {
  bool result = state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_459, SetStringFormatLiteral_459) {
  bool result = state.SetStringFormat(Literal, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(Literal, state.GetStringFormat());
}

TEST_F(EmitterStateTest_459, SetStringFormatInvalid_459) {
  bool result = state.SetStringFormat(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetNullFormat Tests ====================

TEST_F(EmitterStateTest_459, SetNullFormatValid_459) {
  bool result = state.SetNullFormat(LowerNull, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_459, SetNullFormatTilde_459) {
  bool result = state.SetNullFormat(TildeNull, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_459, SetNullFormatInvalid_459) {
  bool result = state.SetNullFormat(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetOutputCharset Tests ====================

TEST_F(EmitterStateTest_459, SetOutputCharsetUtf8_459) {
  bool result = state.SetOutputCharset(EmitNonAscii, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(EmitNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_459, SetOutputCharsetEscape_459) {
  bool result = state.SetOutputCharset(EscapeNonAscii, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(EscapeNonAscii, state.GetOutputCharset());
}

TEST_F(EmitterStateTest_459, SetOutputCharsetInvalid_459) {
  bool result = state.SetOutputCharset(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetIndent Tests ====================

TEST_F(EmitterStateTest_459, SetIndentValid_459) {
  bool result = state.SetIndent(4, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(4u, state.GetIndent());
}

TEST_F(EmitterStateTest_459, SetIndentMinimum_459) {
  bool result = state.SetIndent(2, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(2u, state.GetIndent());
}

TEST_F(EmitterStateTest_459, SetIndentZeroReturnsFalse_459) {
  // 0 indent is likely invalid
  bool result = state.SetIndent(0, FmtScope::Local);
  EXPECT_FALSE(result);
}

TEST_F(EmitterStateTest_459, SetIndentOneReturnsFalse_459) {
  // 1 indent is likely invalid (minimum is usually 2)
  bool result = state.SetIndent(1, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetPreCommentIndent / SetPostCommentIndent Tests ====================

TEST_F(EmitterStateTest_459, SetPreCommentIndentValid_459) {
  bool result = state.SetPreCommentIndent(3, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(3u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_459, SetPostCommentIndentValid_459) {
  bool result = state.SetPostCommentIndent(2, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(2u, state.GetPostCommentIndent());
}

// ==================== SetMapKeyFormat Tests ====================

TEST_F(EmitterStateTest_459, SetMapKeyFormatLongKey_459) {
  bool result = state.SetMapKeyFormat(LongKey, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

TEST_F(EmitterStateTest_459, SetMapKeyFormatInvalid_459) {
  bool result = state.SetMapKeyFormat(Flow, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== SetFloatPrecision / SetDoublePrecision Tests ====================

TEST_F(EmitterStateTest_459, SetFloatPrecisionValid_459) {
  bool result = state.SetFloatPrecision(6, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(6u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_459, SetDoublePrecisionValid_459) {
  bool result = state.SetDoublePrecision(15, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(15u, state.GetDoublePrecision());
}

// ==================== SetFlowType Tests ====================

TEST_F(EmitterStateTest_459, SetFlowTypeSeqFlow_459) {
  bool result = state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_459, SetFlowTypeSeqBlock_459) {
  bool result = state.SetFlowType(GroupType::Seq, Block, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_459, SetFlowTypeMapFlow_459) {
  bool result = state.SetFlowType(GroupType::Map, Flow, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_459, SetFlowTypeMapBlock_459) {
  bool result = state.SetFlowType(GroupType::Map, Block, FmtScope::Local);
  EXPECT_TRUE(result);
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

TEST_F(EmitterStateTest_459, SetFlowTypeInvalid_459) {
  bool result = state.SetFlowType(GroupType::Seq, Dec, FmtScope::Local);
  EXPECT_FALSE(result);
}

// ==================== Document Lifecycle Tests ====================

TEST_F(EmitterStateTest_459, StartedDocIncrementsDocState_459) {
  state.StartedDoc();
  // State should still be good after starting a doc
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_459, EndedDocAfterStarted_459) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

// ==================== Group Lifecycle Tests ====================

TEST_F(EmitterStateTest_459, StartedGroupSeq_459) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_459, StartedGroupMap_459) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_459, EndedGroupRestoresPrevious_459) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_459, CurGroupChildCountInitiallyZero_459) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_459, CurGroupLongKeyInitiallyFalse_459) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// ==================== Scalar Tests ====================

TEST_F(EmitterStateTest_459, StartedScalarAfterDoc_459) {
  state.StartedDoc();
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

// ==================== ForceFlow Tests ====================

TEST_F(EmitterStateTest_459, ForceFlowOnGroup_459) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ==================== SetLongKey Tests ====================

TEST_F(EmitterStateTest_459, SetLongKeyOnMapGroup_459) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  EXPECT_TRUE(state.CurGroupLongKey());
}

// ==================== SetNonContent Tests ====================

TEST_F(EmitterStateTest_459, SetNonContentSetsFlag_459) {
  state.SetNonContent();
  // HasBegunNode should remain false since non-content is set
  // The exact behavior depends on implementation, but we can check state stays good
  EXPECT_TRUE(state.good());
}

// ==================== ClearModifiedSettings Tests ====================

TEST_F(EmitterStateTest_459, ClearModifiedSettingsResetsLocalSettings_459) {
  state.SetIntFormat(Hex, FmtScope::Local);
  EXPECT_EQ(Hex, state.GetIntFormat());
  state.ClearModifiedSettings();
  EXPECT_EQ(Dec, state.GetIntFormat());
}

// ==================== Global Scope Tests ====================

TEST_F(EmitterStateTest_459, GlobalSettingPersistsAfterClearModified_459) {
  state.SetIntFormat(Hex, FmtScope::Global);
  EXPECT_EQ(Hex, state.GetIntFormat());
  state.ClearModifiedSettings();
  // Global settings should persist
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_459, RestoreGlobalModifiedSettings_459) {
  state.SetIntFormat(Hex, FmtScope::Global);
  state.RestoreGlobalModifiedSettings();
  // After restoring, should revert to default
  EXPECT_EQ(Dec, state.GetIntFormat());
}

// ==================== CurIndent Tests ====================

TEST_F(EmitterStateTest_459, CurIndentInitiallyZero_459) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ==================== Multiple SetError Calls ====================

TEST_F(EmitterStateTest_459, MultipleSetErrorKeepsFirstError_459) {
  state.SetError("first error");
  state.SetError("second error");
  EXPECT_FALSE(state.good());
  // Typically the first error is kept
  EXPECT_EQ("first error", state.GetLastError());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterStateTest_459, SetLocalValueFlow_459) {
  state.SetLocalValue(Flow);
  // This should affect some local state; just ensure no crash
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_459, SetLocalValueHex_459) {
  state.SetLocalValue(Hex);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_459, SetLocalValueDoubleQuoted_459) {
  state.SetLocalValue(DoubleQuoted);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

// ==================== Nested Groups Tests ====================

TEST_F(EmitterStateTest_459, NestedGroupsPreserveTypes_459) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
}

// ==================== LastIndent Tests ====================

TEST_F(EmitterStateTest_459, LastIndentInitially_459) {
  // Before any groups, LastIndent should return some value
  std::size_t indent = state.LastIndent();
  (void)indent;
  EXPECT_TRUE(state.good());
}

}  // namespace YAML
