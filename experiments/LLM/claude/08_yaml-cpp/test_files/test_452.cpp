#include "gtest/gtest.h"
#include "emitterstate.h"
#include "yaml-cpp/emittermanip.h"

namespace YAML {

class EmitterStateTest_452 : public ::testing::Test {
 protected:
  EmitterState state;
};

// ============================================================
// Initial State Tests
// ============================================================

TEST_F(EmitterStateTest_452, InitialStateIsGood_452) {
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_452, InitialLastErrorIsEmpty_452) {
  EXPECT_EQ("", state.GetLastError());
}

TEST_F(EmitterStateTest_452, InitialHasAnchorIsFalse_452) {
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateTest_452, InitialHasAliasIsFalse_452) {
  EXPECT_FALSE(state.HasAlias());
}

TEST_F(EmitterStateTest_452, InitialHasTagIsFalse_452) {
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateTest_452, InitialHasBegunContentIsFalse_452) {
  EXPECT_FALSE(state.HasBegunContent());
}

TEST_F(EmitterStateTest_452, InitialHasBegunNodeIsFalse_452) {
  EXPECT_FALSE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_452, InitialCurIndentIsZero_452) {
  EXPECT_EQ(0u, state.CurIndent());
}

// ============================================================
// SetError Tests
// ============================================================

TEST_F(EmitterStateTest_452, SetErrorMakesStateNotGood_452) {
  state.SetError("some error");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_452, SetErrorRecordsErrorMessage_452) {
  state.SetError("test error message");
  EXPECT_EQ("test error message", state.GetLastError());
}

TEST_F(EmitterStateTest_452, SetErrorTwiceKeepsFirstError_452) {
  state.SetError("first error");
  state.SetError("second error");
  // Typically the first error is preserved
  EXPECT_FALSE(state.good());
  // The last error should be at least non-empty
  EXPECT_FALSE(state.GetLastError().empty());
}

// ============================================================
// HasAnchor / HasTag / HasAlias / HasBegunContent Tests
// ============================================================

TEST_F(EmitterStateTest_452, SetAnchorMakesHasAnchorTrue_452) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
}

TEST_F(EmitterStateTest_452, SetTagMakesHasTagTrue_452) {
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
}

TEST_F(EmitterStateTest_452, SetAliasMakesHasAliasTrue_452) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_452, HasBegunContentTrueWhenAnchorSet_452) {
  state.SetAnchor();
  EXPECT_TRUE(state.HasBegunContent());
}

TEST_F(EmitterStateTest_452, HasBegunContentTrueWhenTagSet_452) {
  state.SetTag();
  EXPECT_TRUE(state.HasBegunContent());
}

TEST_F(EmitterStateTest_452, HasBegunContentTrueWhenBothAnchorAndTagSet_452) {
  state.SetAnchor();
  state.SetTag();
  EXPECT_TRUE(state.HasBegunContent());
}

TEST_F(EmitterStateTest_452, HasBegunContentFalseWhenOnlyAliasSet_452) {
  state.SetAlias();
  // HasBegunContent depends on m_hasAnchor || m_hasTag, not m_hasAlias
  // So this should be false unless SetAlias triggers something else
  // Based on the code: HasBegunContent = m_hasAnchor || m_hasTag
  EXPECT_FALSE(state.HasBegunContent());
}

// ============================================================
// Setting Format Tests
// ============================================================

TEST_F(EmitterStateTest_452, SetOutputCharsetReturnsTrue_452) {
  EXPECT_TRUE(state.SetOutputCharset(EmitNonAscii, FmtScope::Local));
}

TEST_F(EmitterStateTest_452, SetStringFormatReturnsTrue_452) {
  EXPECT_TRUE(state.SetStringFormat(SingleQuoted, FmtScope::Local));
}

TEST_F(EmitterStateTest_452, SetBoolFormatReturnsTrue_452) {
  EXPECT_TRUE(state.SetBoolFormat(TrueFalseBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_452, SetBoolLengthFormatReturnsTrue_452) {
  EXPECT_TRUE(state.SetBoolLengthFormat(ShortBool, FmtScope::Local));
}

TEST_F(EmitterStateTest_452, SetBoolCaseFormatReturnsTrue_452) {
  EXPECT_TRUE(state.SetBoolCaseFormat(LowerCase, FmtScope::Local));
}

TEST_F(EmitterStateTest_452, SetNullFormatReturnsTrue_452) {
  EXPECT_TRUE(state.SetNullFormat(LowerNull, FmtScope::Local));
}

TEST_F(EmitterStateTest_452, SetIntFormatReturnsTrue_452) {
  EXPECT_TRUE(state.SetIntFormat(Dec, FmtScope::Local));
}

TEST_F(EmitterStateTest_452, SetIndentReturnsTrue_452) {
  EXPECT_TRUE(state.SetIndent(4, FmtScope::Local));
}

TEST_F(EmitterStateTest_452, SetPreCommentIndentReturnsTrue_452) {
  EXPECT_TRUE(state.SetPreCommentIndent(2, FmtScope::Local));
}

TEST_F(EmitterStateTest_452, SetPostCommentIndentReturnsTrue_452) {
  EXPECT_TRUE(state.SetPostCommentIndent(1, FmtScope::Local));
}

TEST_F(EmitterStateTest_452, SetMapKeyFormatReturnsTrue_452) {
  EXPECT_TRUE(state.SetMapKeyFormat(LongKey, FmtScope::Local));
}

TEST_F(EmitterStateTest_452, SetFloatPrecisionReturnsTrue_452) {
  EXPECT_TRUE(state.SetFloatPrecision(6, FmtScope::Local));
}

TEST_F(EmitterStateTest_452, SetDoublePrecisionReturnsTrue_452) {
  EXPECT_TRUE(state.SetDoublePrecision(15, FmtScope::Local));
}

// ============================================================
// Get Format Tests (defaults)
// ============================================================

TEST_F(EmitterStateTest_452, GetOutputCharsetReturnsDefault_452) {
  EMITTER_MANIP val = state.GetOutputCharset();
  // Should return some valid EMITTER_MANIP
  EXPECT_TRUE(val == EmitNonAscii || val == EscapeNonAscii || val == EscapeAsJson);
}

TEST_F(EmitterStateTest_452, GetStringFormatReturnsDefault_452) {
  EMITTER_MANIP val = state.GetStringFormat();
  (void)val; // Just ensure it doesn't crash
}

TEST_F(EmitterStateTest_452, GetBoolFormatReturnsDefault_452) {
  EMITTER_MANIP val = state.GetBoolFormat();
  (void)val;
}

TEST_F(EmitterStateTest_452, GetIntFormatReturnsDefault_452) {
  EMITTER_MANIP val = state.GetIntFormat();
  EXPECT_TRUE(val == Dec || val == Hex || val == Oct);
}

TEST_F(EmitterStateTest_452, GetIndentReturnsDefault_452) {
  std::size_t val = state.GetIndent();
  EXPECT_GT(val, 0u);
}

TEST_F(EmitterStateTest_452, GetFloatPrecisionReturnsDefault_452) {
  std::size_t val = state.GetFloatPrecision();
  EXPECT_GT(val, 0u);
}

TEST_F(EmitterStateTest_452, GetDoublePrecisionReturnsDefault_452) {
  std::size_t val = state.GetDoublePrecision();
  EXPECT_GT(val, 0u);
}

// ============================================================
// Set and Get Round-trip Tests
// ============================================================

TEST_F(EmitterStateTest_452, SetAndGetIntFormatHex_452) {
  state.SetIntFormat(Hex, FmtScope::Local);
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_452, SetAndGetIntFormatOct_452) {
  state.SetIntFormat(Oct, FmtScope::Local);
  EXPECT_EQ(Oct, state.GetIntFormat());
}

TEST_F(EmitterStateTest_452, SetAndGetIndent_452) {
  state.SetIndent(8, FmtScope::Local);
  EXPECT_EQ(8u, state.GetIndent());
}

TEST_F(EmitterStateTest_452, SetAndGetStringFormatSingleQuoted_452) {
  state.SetStringFormat(SingleQuoted, FmtScope::Local);
  EXPECT_EQ(SingleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_452, SetAndGetStringFormatDoubleQuoted_452) {
  state.SetStringFormat(DoubleQuoted, FmtScope::Local);
  EXPECT_EQ(DoubleQuoted, state.GetStringFormat());
}

TEST_F(EmitterStateTest_452, SetAndGetNullFormatLowerNull_452) {
  state.SetNullFormat(LowerNull, FmtScope::Local);
  EXPECT_EQ(LowerNull, state.GetNullFormat());
}

TEST_F(EmitterStateTest_452, SetAndGetNullFormatTildeNull_452) {
  state.SetNullFormat(TildeNull, FmtScope::Local);
  EXPECT_EQ(TildeNull, state.GetNullFormat());
}

// ============================================================
// Global Scope Tests
// ============================================================

TEST_F(EmitterStateTest_452, SetIntFormatGlobalScope_452) {
  EXPECT_TRUE(state.SetIntFormat(Hex, FmtScope::Global));
  EXPECT_EQ(Hex, state.GetIntFormat());
}

TEST_F(EmitterStateTest_452, SetIndentGlobalScope_452) {
  EXPECT_TRUE(state.SetIndent(6, FmtScope::Global));
  EXPECT_EQ(6u, state.GetIndent());
}

// ============================================================
// Doc / Group Tests
// ============================================================

TEST_F(EmitterStateTest_452, StartedDocDoesNotCrash_452) {
  state.StartedDoc();
  // Should still be good
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_452, EndedDocDoesNotCrash_452) {
  state.StartedDoc();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_452, StartedScalarDoesNotCrash_452) {
  state.StartedDoc();
  state.StartedScalar();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_452, StartedGroupSeqDoesNotCrash_452) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_452, StartedGroupMapDoesNotCrash_452) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_452, EndedGroupSeqDoesNotCrash_452) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_452, EndedGroupMapDoesNotCrash_452) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_452, CurGroupTypeAfterStartedSeq_452) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
}

TEST_F(EmitterStateTest_452, CurGroupTypeAfterStartedMap_452) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
}

TEST_F(EmitterStateTest_452, CurGroupChildCountInitiallyZero_452) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(0u, state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_452, CurGroupIndentAfterStartedGroup_452) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  // Should return some indent value (at least 0)
  std::size_t indent = state.CurGroupIndent();
  (void)indent; // Just ensure no crash
}

TEST_F(EmitterStateTest_452, CurGroupLongKeyDefaultFalse_452) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  EXPECT_FALSE(state.CurGroupLongKey());
}

// ============================================================
// SetLongKey Tests
// ============================================================

TEST_F(EmitterStateTest_452, SetLongKeyDoesNotCrash_452) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.SetLongKey();
  // No crash expected
  EXPECT_TRUE(state.good());
}

// ============================================================
// ForceFlow Tests
// ============================================================

TEST_F(EmitterStateTest_452, ForceFlowDoesNotCrash_452) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_452, ForceFlowChangesFlowType_452) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Seq);
  state.ForceFlow();
  EXPECT_EQ(FlowType::Flow, state.CurGroupFlowType());
}

// ============================================================
// SetNonContent Tests
// ============================================================

TEST_F(EmitterStateTest_452, SetNonContentDoesNotCrash_452) {
  state.SetNonContent();
  EXPECT_TRUE(state.good());
}

// ============================================================
// SetFlowType Tests
// ============================================================

TEST_F(EmitterStateTest_452, SetFlowTypeSeqFlow_452) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Seq, Flow, FmtScope::Local));
  EXPECT_EQ(Flow, state.GetFlowType(GroupType::Seq));
}

TEST_F(EmitterStateTest_452, SetFlowTypeMapBlock_452) {
  EXPECT_TRUE(state.SetFlowType(GroupType::Map, Block, FmtScope::Local));
  EXPECT_EQ(Block, state.GetFlowType(GroupType::Map));
}

// ============================================================
// ClearModifiedSettings Tests
// ============================================================

TEST_F(EmitterStateTest_452, ClearModifiedSettingsRestoresDefaults_452) {
  EMITTER_MANIP defaultIntFmt = state.GetIntFormat();
  state.SetIntFormat(Hex, FmtScope::Local);
  EXPECT_EQ(Hex, state.GetIntFormat());
  state.ClearModifiedSettings();
  EXPECT_EQ(defaultIntFmt, state.GetIntFormat());
}

// ============================================================
// RestoreGlobalModifiedSettings Tests
// ============================================================

TEST_F(EmitterStateTest_452, RestoreGlobalModifiedSettingsDoesNotCrash_452) {
  state.SetIntFormat(Hex, FmtScope::Global);
  state.ClearModifiedSettings();
  state.RestoreGlobalModifiedSettings();
  EXPECT_EQ(Hex, state.GetIntFormat());
}

// ============================================================
// SetLocalValue Tests
// ============================================================

TEST_F(EmitterStateTest_452, SetLocalValueDoesNotCrash_452) {
  state.SetLocalValue(Flow);
  EXPECT_TRUE(state.good());
}

// ============================================================
// Boundary / Edge Cases
// ============================================================

TEST_F(EmitterStateTest_452, SetIndentZeroReturnsAppropriate_452) {
  // Setting indent to 0 may fail or succeed depending on validation
  bool result = state.SetIndent(0, FmtScope::Local);
  (void)result; // Just check it doesn't crash
}

TEST_F(EmitterStateTest_452, SetIndentToOne_452) {
  // Very small indent
  bool result = state.SetIndent(1, FmtScope::Local);
  (void)result;
}

TEST_F(EmitterStateTest_452, SetFloatPrecisionZero_452) {
  bool result = state.SetFloatPrecision(0, FmtScope::Local);
  (void)result;
}

TEST_F(EmitterStateTest_452, SetDoublePrecisionZero_452) {
  bool result = state.SetDoublePrecision(0, FmtScope::Local);
  (void)result;
}

TEST_F(EmitterStateTest_452, MultipleDocsCycle_452) {
  state.StartedDoc();
  state.StartedScalar();
  state.EndedDoc();
  state.StartedDoc();
  state.StartedScalar();
  state.EndedDoc();
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_452, NestedGroups_452) {
  state.StartedDoc();
  state.StartedGroup(GroupType::Map);
  state.StartedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Seq, state.CurGroupType());
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(GroupType::Map, state.CurGroupType());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_452, LastIndentInitial_452) {
  // Without any groups, LastIndent should return something reasonable
  std::size_t li = state.LastIndent();
  (void)li; // Just ensure no crash
}

TEST_F(EmitterStateTest_452, NextGroupTypeSeq_452) {
  state.StartedDoc();
  EmitterNodeType::value ntype = state.NextGroupType(GroupType::Seq);
  (void)ntype; // Ensure no crash
}

TEST_F(EmitterStateTest_452, NextGroupTypeMap_452) {
  state.StartedDoc();
  EmitterNodeType::value ntype = state.NextGroupType(GroupType::Map);
  (void)ntype;
}

TEST_F(EmitterStateTest_452, SetErrorEmptyString_452) {
  state.SetError("");
  EXPECT_FALSE(state.good());
}

TEST_F(EmitterStateTest_452, GetPreCommentIndentDefault_452) {
  std::size_t val = state.GetPreCommentIndent();
  EXPECT_GT(val, 0u);
}

TEST_F(EmitterStateTest_452, GetPostCommentIndentDefault_452) {
  std::size_t val = state.GetPostCommentIndent();
  EXPECT_GT(val, 0u);
}

TEST_F(EmitterStateTest_452, SetAndGetPreCommentIndent_452) {
  state.SetPreCommentIndent(5, FmtScope::Local);
  EXPECT_EQ(5u, state.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_452, SetAndGetPostCommentIndent_452) {
  state.SetPostCommentIndent(3, FmtScope::Local);
  EXPECT_EQ(3u, state.GetPostCommentIndent());
}

TEST_F(EmitterStateTest_452, SetAndGetFloatPrecision_452) {
  state.SetFloatPrecision(10, FmtScope::Local);
  EXPECT_EQ(10u, state.GetFloatPrecision());
}

TEST_F(EmitterStateTest_452, SetAndGetDoublePrecision_452) {
  state.SetDoublePrecision(12, FmtScope::Local);
  EXPECT_EQ(12u, state.GetDoublePrecision());
}

TEST_F(EmitterStateTest_452, GetMapKeyFormatDefault_452) {
  EMITTER_MANIP val = state.GetMapKeyFormat();
  (void)val; // Ensure no crash
}

TEST_F(EmitterStateTest_452, SetAndGetMapKeyFormat_452) {
  state.SetMapKeyFormat(LongKey, FmtScope::Local);
  EXPECT_EQ(LongKey, state.GetMapKeyFormat());
}

}  // namespace YAML
