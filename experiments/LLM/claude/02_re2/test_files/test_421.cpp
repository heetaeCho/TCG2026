#include "gtest/gtest.h"
#include "re2/regexp.h"
#include <string>

namespace re2 {

// Helper to get common parse flags
static const Regexp::ParseFlags kTestFlags = Regexp::LikePerl;

class SimplifyRegexpTest_421 : public ::testing::Test {
 protected:
  std::string dst_;
  RegexpStatus status_;
};

// Test that a simple literal string simplifies correctly
TEST_F(SimplifyRegexpTest_421, SimpleLiteral_421) {
  bool result = Regexp::SimplifyRegexp("abc", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
  EXPECT_FALSE(dst_.empty());
}

// Test that an empty regex simplifies correctly
TEST_F(SimplifyRegexpTest_421, EmptyRegex_421) {
  bool result = Regexp::SimplifyRegexp("", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of a dot (any character)
TEST_F(SimplifyRegexpTest_421, DotSimplify_421) {
  bool result = Regexp::SimplifyRegexp(".", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of alternation
TEST_F(SimplifyRegexpTest_421, Alternation_421) {
  bool result = Regexp::SimplifyRegexp("a|b|c", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of character class
TEST_F(SimplifyRegexpTest_421, CharClass_421) {
  bool result = Regexp::SimplifyRegexp("[abc]", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of negated character class
TEST_F(SimplifyRegexpTest_421, NegatedCharClass_421) {
  bool result = Regexp::SimplifyRegexp("[^abc]", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of star quantifier
TEST_F(SimplifyRegexpTest_421, StarQuantifier_421) {
  bool result = Regexp::SimplifyRegexp("a*", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of plus quantifier
TEST_F(SimplifyRegexpTest_421, PlusQuantifier_421) {
  bool result = Regexp::SimplifyRegexp("a+", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of question mark quantifier
TEST_F(SimplifyRegexpTest_421, QuestionQuantifier_421) {
  bool result = Regexp::SimplifyRegexp("a?", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of counted repetition
TEST_F(SimplifyRegexpTest_421, CountedRepetition_421) {
  bool result = Regexp::SimplifyRegexp("a{3,5}", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of exact repetition
TEST_F(SimplifyRegexpTest_421, ExactRepetition_421) {
  bool result = Regexp::SimplifyRegexp("a{3}", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of bounded repetition with min only
TEST_F(SimplifyRegexpTest_421, MinRepetition_421) {
  bool result = Regexp::SimplifyRegexp("a{3,}", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of zero repetition
TEST_F(SimplifyRegexpTest_421, ZeroRepetition_421) {
  bool result = Regexp::SimplifyRegexp("a{0}", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of zero-or-more repetition (equivalent to star)
TEST_F(SimplifyRegexpTest_421, ZeroOrMoreRepetition_421) {
  bool result = Regexp::SimplifyRegexp("a{0,}", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of one-or-more repetition (equivalent to plus)
TEST_F(SimplifyRegexpTest_421, OneOrMoreRepetition_421) {
  bool result = Regexp::SimplifyRegexp("a{1,}", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of zero-or-one repetition (equivalent to question)
TEST_F(SimplifyRegexpTest_421, ZeroOrOneRepetition_421) {
  bool result = Regexp::SimplifyRegexp("a{0,1}", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test invalid regex returns false
TEST_F(SimplifyRegexpTest_421, InvalidRegex_421) {
  bool result = Regexp::SimplifyRegexp("(", kTestFlags, &dst_, &status_);
  EXPECT_FALSE(result);
  EXPECT_FALSE(status_.ok());
}

// Test invalid regex - missing closing bracket
TEST_F(SimplifyRegexpTest_421, MissingBracket_421) {
  bool result = Regexp::SimplifyRegexp("[abc", kTestFlags, &dst_, &status_);
  EXPECT_FALSE(result);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpMissingBracket);
}

// Test invalid regex - unexpected closing paren
TEST_F(SimplifyRegexpTest_421, UnexpectedParen_421) {
  bool result = Regexp::SimplifyRegexp(")", kTestFlags, &dst_, &status_);
  EXPECT_FALSE(result);
  EXPECT_FALSE(status_.ok());
}

// Test simplification of capture group
TEST_F(SimplifyRegexpTest_421, CaptureGroup_421) {
  bool result = Regexp::SimplifyRegexp("(abc)", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of nested groups
TEST_F(SimplifyRegexpTest_421, NestedGroups_421) {
  bool result = Regexp::SimplifyRegexp("((a)(b))", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of non-greedy star
TEST_F(SimplifyRegexpTest_421, NonGreedyStar_421) {
  bool result = Regexp::SimplifyRegexp("a*?", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of non-greedy plus
TEST_F(SimplifyRegexpTest_421, NonGreedyPlus_421) {
  bool result = Regexp::SimplifyRegexp("a+?", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of non-greedy question mark
TEST_F(SimplifyRegexpTest_421, NonGreedyQuestion_421) {
  bool result = Regexp::SimplifyRegexp("a??", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of non-greedy counted repetition
TEST_F(SimplifyRegexpTest_421, NonGreedyCountedRepetition_421) {
  bool result = Regexp::SimplifyRegexp("a{3,5}?", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of character class range
TEST_F(SimplifyRegexpTest_421, CharClassRange_421) {
  bool result = Regexp::SimplifyRegexp("[a-z]", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of word boundary
TEST_F(SimplifyRegexpTest_421, WordBoundary_421) {
  bool result = Regexp::SimplifyRegexp("\\b", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of anchors
TEST_F(SimplifyRegexpTest_421, Anchors_421) {
  bool result = Regexp::SimplifyRegexp("^abc$", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of complex regex
TEST_F(SimplifyRegexpTest_421, ComplexRegex_421) {
  bool result = Regexp::SimplifyRegexp("(a|b)*c+[d-f]{2,4}?", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification with POSIX flags
TEST_F(SimplifyRegexpTest_421, PosixFlags_421) {
  bool result = Regexp::SimplifyRegexp("abc", Regexp::PerlX, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of single character
TEST_F(SimplifyRegexpTest_421, SingleChar_421) {
  bool result = Regexp::SimplifyRegexp("a", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(dst_, "a");
}

// Test with null status pointer (should still work if regex is valid)
TEST_F(SimplifyRegexpTest_421, NullStatus_421) {
  bool result = Regexp::SimplifyRegexp("abc", kTestFlags, &dst_, nullptr);
  EXPECT_TRUE(result);
}

// Test invalid regex with null status pointer
TEST_F(SimplifyRegexpTest_421, NullStatusInvalidRegex_421) {
  bool result = Regexp::SimplifyRegexp("(", kTestFlags, &dst_, nullptr);
  EXPECT_FALSE(result);
}

// Test simplification of escape sequences
TEST_F(SimplifyRegexpTest_421, EscapeSequences_421) {
  bool result = Regexp::SimplifyRegexp("\\d+", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of \\w
TEST_F(SimplifyRegexpTest_421, WordCharClass_421) {
  bool result = Regexp::SimplifyRegexp("\\w+", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of \\s
TEST_F(SimplifyRegexpTest_421, SpaceCharClass_421) {
  bool result = Regexp::SimplifyRegexp("\\s+", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test that {1,1} simplifies appropriately
TEST_F(SimplifyRegexpTest_421, RepeatOneOne_421) {
  bool result = Regexp::SimplifyRegexp("a{1,1}", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification preserves semantics for a{0,0}
TEST_F(SimplifyRegexpTest_421, RepeatZeroZero_421) {
  bool result = Regexp::SimplifyRegexp("a{0,0}", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test trailing backslash is an error
TEST_F(SimplifyRegexpTest_421, TrailingBackslash_421) {
  bool result = Regexp::SimplifyRegexp("\\", kTestFlags, &dst_, &status_);
  EXPECT_FALSE(result);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpTrailingBackslash);
}

// Test bad character range
TEST_F(SimplifyRegexpTest_421, BadCharRange_421) {
  bool result = Regexp::SimplifyRegexp("[z-a]", kTestFlags, &dst_, &status_);
  EXPECT_FALSE(result);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpBadCharRange);
}

// Test repeat of nothing (nothing to repeat)
TEST_F(SimplifyRegexpTest_421, RepeatOfNothing_421) {
  bool result = Regexp::SimplifyRegexp("*", kTestFlags, &dst_, &status_);
  EXPECT_FALSE(result);
  EXPECT_FALSE(status_.ok());
}

// Test missing paren
TEST_F(SimplifyRegexpTest_421, MissingParen_421) {
  bool result = Regexp::SimplifyRegexp("(abc", kTestFlags, &dst_, &status_);
  EXPECT_FALSE(result);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpMissingParen);
}

// Test simplification of concat with repetitions
TEST_F(SimplifyRegexpTest_421, ConcatWithRepetitions_421) {
  bool result = Regexp::SimplifyRegexp("a{2}b{3}c{4}", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of named capture group
TEST_F(SimplifyRegexpTest_421, NamedCaptureGroup_421) {
  bool result = Regexp::SimplifyRegexp("(?P<name>abc)", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test simplification of non-capturing group
TEST_F(SimplifyRegexpTest_421, NonCapturingGroup_421) {
  bool result = Regexp::SimplifyRegexp("(?:abc)", kTestFlags, &dst_, &status_);
  EXPECT_TRUE(result);
  EXPECT_TRUE(status_.ok());
}

// Test that status error_arg is set on parse failure
TEST_F(SimplifyRegexpTest_421, StatusErrorArgOnFailure_421) {
  absl::string_view src = "(unclosed";
  bool result = Regexp::SimplifyRegexp(src, kTestFlags, &dst_, &status_);
  EXPECT_FALSE(result);
  EXPECT_FALSE(status_.ok());
  // error_arg should be set to something meaningful
  EXPECT_FALSE(status_.error_arg().empty());
}

// Test RegexpStatus default state
TEST(RegexpStatusTest_421, DefaultState_421) {
  RegexpStatus status;
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

// Test RegexpStatus set_code and code
TEST(RegexpStatusTest_421, SetAndGetCode_421) {
  RegexpStatus status;
  status.set_code(kRegexpInternalError);
  EXPECT_EQ(status.code(), kRegexpInternalError);
  EXPECT_FALSE(status.ok());
}

// Test RegexpStatus set_error_arg and error_arg
TEST(RegexpStatusTest_421, SetAndGetErrorArg_421) {
  RegexpStatus status;
  status.set_error_arg("test error");
  EXPECT_EQ(status.error_arg(), "test error");
}

// Test RegexpStatus CodeText
TEST(RegexpStatusTest_421, CodeText_421) {
  std::string text = RegexpStatus::CodeText(kRegexpSuccess);
  EXPECT_FALSE(text.empty());
}

// Test RegexpStatus Text method
TEST(RegexpStatusTest_421, TextMethod_421) {
  RegexpStatus status;
  status.set_code(kRegexpBadEscape);
  status.set_error_arg("\\x");
  std::string text = status.Text();
  EXPECT_FALSE(text.empty());
}

// Test RegexpStatus Copy
TEST(RegexpStatusTest_421, CopyStatus_421) {
  RegexpStatus status1;
  status1.set_code(kRegexpBadCharClass);
  status1.set_error_arg("[invalid");
  
  RegexpStatus status2;
  status2.Copy(status1);
  EXPECT_EQ(status2.code(), kRegexpBadCharClass);
}

}  // namespace re2
