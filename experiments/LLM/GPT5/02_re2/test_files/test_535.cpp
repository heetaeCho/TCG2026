// File: re2_parse_tests_535.cc
#include <gtest/gtest.h>
#include <string>
#include "re2/regexp.h"

using re2::Regexp;
using re2::RegexpStatus;
using re2::RegexpStatusCode;

// Convenience to safely decref when non-null (no assumptions about internals).
static void DecrefIfNotNull(Regexp* re) {
  if (re != nullptr) {
    re->Decref();
  }
}

// ---------- Success paths (observable: returns non-null, status.ok()) ----------

TEST(RegexpParseTest_535, LiteralTreatsMetacharsAsLiterals_535) {
  // In Literal mode, metacharacters are treated as ordinary characters.
  RegexpStatus status;
  const std::string pattern = R"(a.*[b]\c\Q\E)";  // contains many meta-ish chars
  Regexp* re = Regexp::Parse(pattern, Regexp::Literal, &status);

  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  DecrefIfNotNull(re);
}

TEST(RegexpParseTest_535, PerlQRegionWithoutClosingE_Succeeds_535) {
  // \Q ... (without \E) should consume until end as literals.
  RegexpStatus status;
  const std::string pattern = "\\Q*+?{2}";  // no closing \E
  Regexp* re = Regexp::Parse(pattern, Regexp::PerlX, &status);

  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  DecrefIfNotNull(re);
}

TEST(RegexpParseTest_535, PerlB_WordBoundaryTokens_Succeed_535) {
  // With PerlB flag, \b and \B should be accepted.
  RegexpStatus status;
  const std::string pattern = "\\b\\B";
  Regexp* re = Regexp::Parse(pattern, Regexp::PerlB, &status);

  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  DecrefIfNotNull(re);
}

TEST(RegexpParseTest_535, Latin1InputIsAcceptedAndConverted_535) {
  // With Latin1 flag, bytes > 0x7F are converted; parsing should succeed.
  RegexpStatus status;
  // 0xE9 = 'é' in Latin-1. Also set Literal so it's just a literal character.
  const std::string pattern = std::string(1, static_cast<char>(0xE9));
  Regexp* re = Regexp::Parse(pattern, static_cast<Regexp::ParseFlags>(Regexp::Latin1 | Regexp::Literal), &status);

  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  DecrefIfNotNull(re);
}

TEST(RegexpParseTest_535, SimpleDotParses_535) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::NoParseFlags, &status);

  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  DecrefIfNotNull(re);
}

// ---------- Error paths (observable: returns null & status fields) ----------

TEST(RegexpParseTest_535, RepeatOperatorAtStart_Star_WithPerlX_IsError_535) {
  // A unary repeat operator with no previous atom should be an error under PerlX.
  RegexpStatus status;
  Regexp* re = Regexp::Parse("*", Regexp::PerlX, &status);

  ASSERT_EQ(re, nullptr);
  EXPECT_EQ(status.code(), re2::kRegexpRepeatOp);
  // Error arg should reflect the offending operator.
  EXPECT_EQ(std::string(status.error_arg()), "*");
}

TEST(RegexpParseTest_535, RepeatOperatorAtStart_StarNonGreedy_WithPerlX_IsError_535) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("*?", Regexp::PerlX, &status);

  ASSERT_EQ(re, nullptr);
  EXPECT_EQ(status.code(), re2::kRegexpRepeatOp);
  EXPECT_EQ(std::string(status.error_arg()), "*?");
}

TEST(RegexpParseTest_535, CountedRepetitionAtStart_WithPerlX_IsError_535) {
  // A counted repetition like {2,3} without a preceding atom should error with PerlX.
  RegexpStatus status;
  Regexp* re = Regexp::Parse("{2,3}", Regexp::PerlX, &status);

  ASSERT_EQ(re, nullptr);
  EXPECT_EQ(status.code(), re2::kRegexpRepeatOp);
  EXPECT_EQ(std::string(status.error_arg()), "{2,3}");
}

TEST(RegexpParseTest_535, TrailingBackslashIsError_535) {
  // A trailing backslash should be flagged as a bad escape (trailing backslash).
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\", Regexp::NoParseFlags, &status);

  ASSERT_EQ(re, nullptr);
  EXPECT_EQ(status.code(), re2::kRegexpTrailingBackslash);
  // error_arg may vary by implementation; we only assert the code.
}
