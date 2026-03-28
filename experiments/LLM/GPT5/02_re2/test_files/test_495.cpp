// File: push_repeat_op_test_495.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"
// NOTE: ParseState is declared/defined in parse.cc in this project layout.
#include "re2/parse.cc"

using namespace re2;

class PushRepeatOpTest_495 : public ::testing::Test {
protected:
  RegexpStatus status_;
  using PF = Regexp::ParseFlags;

  Regexp::ParseState MakeState(PF flags = Regexp::NoParseFlags,
                               absl::string_view whole = "") {
    return Regexp::ParseState(flags, whole, &status_);
  }
};

// Error case: no previous operand (stack empty) -> kRegexpRepeatArgument and false.
TEST_F(PushRepeatOpTest_495, NoPrevOperandSetsError_495) {
  auto ps = MakeState();
  const absl::string_view where = "*";
  bool ok = ps.PushRepeatOp(kRegexpStar, where, /*nongreedy=*/false);

  EXPECT_FALSE(ok);
  EXPECT_EQ(status_.code(), kRegexpRepeatArgument);
  EXPECT_EQ(std::string(status_.error_arg()), std::string(where));
}

// Normal: apply '*' to a literal operand.
TEST_F(PushRepeatOpTest_495, AppliesStarToLiteral_495) {
  auto ps = MakeState();
  ASSERT_TRUE(ps.PushLiteral('a'));
  ASSERT_TRUE(ps.PushRepeatOp(kRegexpStar, "*", /*nongreedy=*/false));
  Regexp* re = ps.DoFinish();

  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  EXPECT_TRUE(status_.ok());
  // Greedy by default (NonGreedy bit not set).
  EXPECT_EQ(re->parse_flags() & Regexp::NonGreedy, 0);
  re->Decref();
}

// Normal: nongreedy flag is applied when requested.
TEST_F(PushRepeatOpTest_495, NongreedyFlagIsToggledOn_495) {
  auto ps = MakeState();
  ASSERT_TRUE(ps.PushLiteral('a'));
  ASSERT_TRUE(ps.PushRepeatOp(kRegexpStar, "*", /*nongreedy=*/true));
  Regexp* re = ps.DoFinish();

  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  EXPECT_NE(re->parse_flags() & Regexp::NonGreedy, 0);  // bit set
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Idempotent path: pushing the same repeat op with matching flags succeeds without changing op.
TEST_F(PushRepeatOpTest_495, SameOpAndFlagsIsNoop_495) {
  auto ps = MakeState();
  ASSERT_TRUE(ps.PushLiteral('a'));
  ASSERT_TRUE(ps.PushRepeatOp(kRegexpPlus, "+", /*nongreedy=*/false));

  // Same op and same flags -> true; resulting top op remains Plus.
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpPlus, "+", /*nongreedy=*/false));

  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Normalization: if top is Star/Plus/Quest and flags match, any further repeat normalizes to Star.
TEST_F(PushRepeatOpTest_495, NormalizesNestedRepeatToStar_495) {
  auto ps = MakeState();
  ASSERT_TRUE(ps.PushLiteral('a'));
  ASSERT_TRUE(ps.PushRepeatOp(kRegexpPlus, "+", /*nongreedy=*/false));

  // Different incoming repeat op but same flags -> top becomes Star per observable behavior.
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpQuest, "?", /*nongreedy=*/false));

  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Flags mismatch prevents normalization; a new node reflecting requested flags should be observable at the top.
TEST_F(PushRepeatOpTest_495, FlagsMismatchPreventsNormalization_495) {
  auto ps = MakeState();
  ASSERT_TRUE(ps.PushLiteral('a'));
  ASSERT_TRUE(ps.PushRepeatOp(kRegexpPlus, "+", /*nongreedy=*/false));

  // Toggle NonGreedy, so flags differ from the existing repeat node.
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, "*", /*nongreedy=*/true));

  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  // Top reflects the last requested op (Star), with NonGreedy set due to the toggle.
  EXPECT_EQ(re->op(), kRegexpStar);
  EXPECT_NE(re->parse_flags() & Regexp::NonGreedy, 0);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}
