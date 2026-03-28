#include "re2/re2.h"
#include <string>
#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

namespace re2 {
namespace {

// =============================================================================
// Tests for CheckRewriteString
// =============================================================================

class CheckRewriteStringTest_263 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Normal operation: simple literal rewrite with no backreferences
TEST_F(CheckRewriteStringTest_263, LiteralRewriteReturnsTrue_263) {
  RE2 re("(hello)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("world", &error));
  EXPECT_TRUE(error.empty());
}

// Normal operation: valid backreference \0 (entire match)
TEST_F(CheckRewriteStringTest_263, BackrefZeroWithNoGroups_263) {
  RE2 re("hello");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\0", &error));
}

// Normal operation: valid backreference \1 with one capturing group
TEST_F(CheckRewriteStringTest_263, BackrefOneWithOneGroup_263) {
  RE2 re("(hello)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
  EXPECT_TRUE(error.empty());
}

// Normal operation: escaped backslash in rewrite
TEST_F(CheckRewriteStringTest_263, EscapedBackslashReturnsTrue_263) {
  RE2 re("hello");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\\\", &error));
  EXPECT_TRUE(error.empty());
}

// Normal operation: mixed literal text and valid backreferences
TEST_F(CheckRewriteStringTest_263, MixedLiteralAndBackref_263) {
  RE2 re("(a)(b)(c)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("prefix\\1-\\2-\\3suffix", &error));
  EXPECT_TRUE(error.empty());
}

// Error case: backslash at end of rewrite string
TEST_F(CheckRewriteStringTest_263, BackslashAtEndReturnsFalse_263) {
  RE2 re("hello");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("trailing\\", &error));
  EXPECT_EQ(error, "Rewrite schema error: '\\' not allowed at end.");
}

// Error case: backslash followed by non-digit, non-backslash character
TEST_F(CheckRewriteStringTest_263, BackslashFollowedByNonDigit_263) {
  RE2 re("hello");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\a", &error));
  EXPECT_EQ(error,
            "Rewrite schema error: "
            "'\\' must be followed by a digit or '\\'.");
}

// Error case: backreference exceeds number of capturing groups
TEST_F(CheckRewriteStringTest_263, BackrefExceedsCapturingGroups_263) {
  RE2 re("hello");  // 0 capturing groups
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\1", &error));
  EXPECT_NE(error.find("Rewrite schema requests"), std::string::npos);
}

// Error case: backreference \9 with only 2 groups
TEST_F(CheckRewriteStringTest_263, BackrefNineExceedsTwoGroups_263) {
  RE2 re("(a)(b)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\9", &error));
  EXPECT_NE(error.find("Rewrite schema requests"), std::string::npos);
}

// Boundary: empty rewrite string
TEST_F(CheckRewriteStringTest_263, EmptyRewriteReturnsTrue_263) {
  RE2 re("hello");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("", &error));
}

// Boundary: rewrite string with only escaped backslashes
TEST_F(CheckRewriteStringTest_263, OnlyEscapedBackslashes_263) {
  RE2 re("hello");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\\\\\\\", &error));
}

// Boundary: multiple valid backreferences up to max group
TEST_F(CheckRewriteStringTest_263, MultipleValidBackrefs_263) {
  RE2 re("(a)(b)(c)(d)(e)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1\\2\\3\\4\\5", &error));
  EXPECT_TRUE(error.empty());
}

// Boundary: backreference equal to number of capturing groups
TEST_F(CheckRewriteStringTest_263, BackrefEqualToGroupCount_263) {
  RE2 re("(a)(b)(c)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\3", &error));
  EXPECT_TRUE(error.empty());
}

// Boundary: backreference one more than number of capturing groups
TEST_F(CheckRewriteStringTest_263, BackrefOneMoreThanGroupCount_263) {
  RE2 re("(a)(b)(c)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\4", &error));
}

// Error case: backslash followed by a letter
TEST_F(CheckRewriteStringTest_263, BackslashFollowedByLetter_263) {
  RE2 re("(hello)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\n", &error));
  EXPECT_EQ(error,
            "Rewrite schema error: "
            "'\\' must be followed by a digit or '\\'.");
}

// Normal: \0 backreference with groups present
TEST_F(CheckRewriteStringTest_263, BackrefZeroAlwaysValid_263) {
  RE2 re("(a)(b)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\0", &error));
  EXPECT_TRUE(error.empty());
}

// Single backslash as the entire rewrite
TEST_F(CheckRewriteStringTest_263, SingleBackslashOnly_263) {
  RE2 re("hello");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\", &error));
  EXPECT_EQ(error, "Rewrite schema error: '\\' not allowed at end.");
}

// Backslash followed by special character (not digit, not backslash)
TEST_F(CheckRewriteStringTest_263, BackslashFollowedBySpecialChar_263) {
  RE2 re("hello");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\!", &error));
  EXPECT_EQ(error,
            "Rewrite schema error: "
            "'\\' must be followed by a digit or '\\'.");
}

// Valid: escaped backslash followed by a digit (not a backreference)
TEST_F(CheckRewriteStringTest_263, EscapedBackslashThenDigit_263) {
  RE2 re("hello");  // 0 groups
  std::string error;
  // "\\\\1" should be interpreted as literal \1, not backreference
  EXPECT_TRUE(re.CheckRewriteString("\\\\1", &error));
}

// Multiple errors: first error encountered should be returned
TEST_F(CheckRewriteStringTest_263, FirstErrorReturnedForBackslashAtEnd_263) {
  RE2 re("(a)");
  std::string error;
  // "\\a" - backslash followed by non-digit
  EXPECT_FALSE(re.CheckRewriteString("\\a", &error));
  EXPECT_EQ(error,
            "Rewrite schema error: "
            "'\\' must be followed by a digit or '\\'.");
}

// =============================================================================
// Tests for MaxSubmatch (static method)
// =============================================================================

class MaxSubmatchTest_263 : public ::testing::Test {};

TEST_F(MaxSubmatchTest_263, NoBackreferences_263) {
  EXPECT_EQ(RE2::MaxSubmatch("hello"), 0);
}

TEST_F(MaxSubmatchTest_263, SingleBackref_263) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1"), 1);
}

TEST_F(MaxSubmatchTest_263, MultipleBackrefs_263) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1\\3\\2"), 3);
}

TEST_F(MaxSubmatchTest_263, EmptyString_263) {
  EXPECT_EQ(RE2::MaxSubmatch(""), 0);
}

TEST_F(MaxSubmatchTest_263, EscapedBackslash_263) {
  EXPECT_EQ(RE2::MaxSubmatch("\\\\"), 0);
}

// =============================================================================
// Tests for Replace
// =============================================================================

class ReplaceTest_263 : public ::testing::Test {};

TEST_F(ReplaceTest_263, SimpleReplace_263) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, RE2("world"), "there"));
  EXPECT_EQ(s, "hello there");
}

TEST_F(ReplaceTest_263, NoMatch_263) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, RE2("xyz"), "there"));
  EXPECT_EQ(s, "hello world");
}

TEST_F(ReplaceTest_263, ReplaceWithBackref_263) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, RE2("(\\w+)\\s(\\w+)"), "\\2 \\1"));
  EXPECT_EQ(s, "world hello");
}

// =============================================================================
// Tests for GlobalReplace
// =============================================================================

class GlobalReplaceTest_263 : public ::testing::Test {};

TEST_F(GlobalReplaceTest_263, ReplaceAll_263) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, RE2("a"), "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "bbb");
}

TEST_F(GlobalReplaceTest_263, NoMatch_263) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, RE2("x"), "y");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello");
}

// =============================================================================
// Tests for Extract
// =============================================================================

class ExtractTest_263 : public ::testing::Test {};

TEST_F(ExtractTest_263, SimpleExtract_263) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", RE2("(.*)@([^.]*)"), "\\2!\\1", &out));
  EXPECT_EQ(out, "kremlin!boris");
}

TEST_F(ExtractTest_263, NoMatch_263) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("boris", RE2("(.*)@(.*)"), "\\2!\\1", &out));
}

// =============================================================================
// Tests for FullMatch / PartialMatch
// =============================================================================

class MatchTest_263 : public ::testing::Test {};

TEST_F(MatchTest_263, FullMatchSuccess_263) {
  EXPECT_TRUE(RE2::FullMatch("hello", RE2("hello")));
}

TEST_F(MatchTest_263, FullMatchFailure_263) {
  EXPECT_FALSE(RE2::FullMatch("hello world", RE2("hello")));
}

TEST_F(MatchTest_263, PartialMatchSuccess_263) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", RE2("hello")));
}

TEST_F(MatchTest_263, PartialMatchFailure_263) {
  EXPECT_FALSE(RE2::PartialMatch("hello world", RE2("xyz")));
}

// =============================================================================
// Tests for NumberOfCapturingGroups
// =============================================================================

class CapturingGroupsTest_263 : public ::testing::Test {};

TEST_F(CapturingGroupsTest_263, NoGroups_263) {
  RE2 re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(CapturingGroupsTest_263, OneGroup_263) {
  RE2 re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST_F(CapturingGroupsTest_263, MultipleGroups_263) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(CapturingGroupsTest_263, NestedGroups_263) {
  RE2 re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

// =============================================================================
// Tests for QuoteMeta
// =============================================================================

class QuoteMetaTest_263 : public ::testing::Test {};

TEST_F(QuoteMetaTest_263, NoSpecialChars_263) {
  EXPECT_EQ(RE2::QuoteMeta("hello"), "hello");
}

TEST_F(QuoteMetaTest_263, SpecialCharsEscaped_263) {
  std::string quoted = RE2::QuoteMeta("a.b*c+d");
  // The quoted string should match literally
  RE2 re(quoted);
  EXPECT_TRUE(RE2::FullMatch("a.b*c+d", re));
}

TEST_F(QuoteMetaTest_263, EmptyString_263) {
  EXPECT_EQ(RE2::QuoteMeta(""), "");
}

// =============================================================================
// Tests for Rewrite
// =============================================================================

class RewriteTest_263 : public ::testing::Test {};

TEST_F(RewriteTest_263, SimpleRewrite_263) {
  RE2 re("(\\w+)");
  std::string out;
  absl::string_view vec[] = {"full", "first"};
  EXPECT_TRUE(re.Rewrite(&out, "\\1", vec, 2));
  EXPECT_EQ(out, "first");
}

TEST_F(RewriteTest_263, RewriteWithLiterals_263) {
  RE2 re("(\\w+)");
  std::string out;
  absl::string_view vec[] = {"full", "group1"};
  EXPECT_TRUE(re.Rewrite(&out, "prefix-\\1-suffix", vec, 2));
  EXPECT_EQ(out, "prefix-group1-suffix");
}

// =============================================================================
// Tests for ok() and pattern()
// =============================================================================

class RE2BasicTest_263 : public ::testing::Test {};

TEST_F(RE2BasicTest_263, ValidPatternIsOk_263) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
}

TEST_F(RE2BasicTest_263, InvalidPatternNotOk_263) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
}

TEST_F(RE2BasicTest_263, PatternReturnsOriginal_263) {
  RE2 re("hello.*world");
  EXPECT_EQ(re.pattern(), "hello.*world");
}

TEST_F(RE2BasicTest_263, ErrorNonEmptyForBadPattern_263) {
  RE2 re("(bad");
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(re.error().empty());
}

// =============================================================================
// Tests for Consume and FindAndConsume
// =============================================================================

class ConsumeTest_263 : public ::testing::Test {};

TEST_F(ConsumeTest_263, ConsumeAdvancesInput_263) {
  absl::string_view input("hello world");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, RE2("(\\w+)"), &word));
  EXPECT_EQ(word, "hello");
}

TEST_F(ConsumeTest_263, FindAndConsumeSkips_263) {
  absl::string_view input("   hello world");
  std::string word;
  EXPECT_TRUE(RE2::FindAndConsume(&input, RE2("(\\w+)"), &word));
  EXPECT_EQ(word, "hello");
}

// =============================================================================
// Additional CheckRewriteString edge cases
// =============================================================================

TEST_F(CheckRewriteStringTest_263, BackslashFollowedBySpace_263) {
  RE2 re("(a)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\ ", &error));
  EXPECT_EQ(error,
            "Rewrite schema error: "
            "'\\' must be followed by a digit or '\\'.");
}

TEST_F(CheckRewriteStringTest_263, AllDigitBackrefs0Through9_263) {
  // Pattern with 9 capturing groups
  RE2 re("(a)(b)(c)(d)(e)(f)(g)(h)(i)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 9);
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\0\\1\\2\\3\\4\\5\\6\\7\\8\\9", &error));
  EXPECT_TRUE(error.empty());
}

TEST_F(CheckRewriteStringTest_263, OnlyLiteralText_263) {
  RE2 re("(a)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("just plain text", &error));
  EXPECT_TRUE(error.empty());
}

}  // namespace
}  // namespace re2
