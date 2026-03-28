#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "re2/re2.h"
#include "re2/filtered_re2.h"
#include "re2/set.h"
#include "absl/strings/string_view.h"

// Forward declaration of the function under test
void TestOneInput(absl::string_view pattern, const RE2::Options& options,
                  RE2::Anchor anchor, absl::string_view text);

class Re2FuzzerTest_385 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default options
    options_ = RE2::Options();
    options_.set_log_errors(false);
  }

  RE2::Options options_;
};

// Test with a simple literal pattern and matching text
TEST_F(Re2FuzzerTest_385, SimpleLiteralPattern_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("hello", options_, RE2::UNANCHORED, "hello world"));
}

// Test with empty pattern
TEST_F(Re2FuzzerTest_385, EmptyPattern_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("", options_, RE2::UNANCHORED, "some text"));
}

// Test with empty text
TEST_F(Re2FuzzerTest_385, EmptyText_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("abc", options_, RE2::UNANCHORED, ""));
}

// Test with both empty pattern and text
TEST_F(Re2FuzzerTest_385, BothEmpty_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("", options_, RE2::UNANCHORED, ""));
}

// Test with invalid regex pattern
TEST_F(Re2FuzzerTest_385, InvalidPattern_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("[invalid", options_, RE2::UNANCHORED, "test"));
}

// Test with capturing groups
TEST_F(Re2FuzzerTest_385, CapturingGroup_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("(\\d+)", options_, RE2::UNANCHORED, "123"));
}

// Test with multiple capturing groups
TEST_F(Re2FuzzerTest_385, MultipleCapturingGroups_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("(a)(b)", options_, RE2::UNANCHORED, "ab"));
}

// Test with no capturing groups (simple pattern)
TEST_F(Re2FuzzerTest_385, NoCapturingGroups_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("abc", options_, RE2::UNANCHORED, "abcdef"));
}

// Test with anchored match
TEST_F(Re2FuzzerTest_385, AnchoredMatch_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("abc", options_, RE2::ANCHOR_BOTH, "abc"));
}

// Test with ANCHOR_START
TEST_F(Re2FuzzerTest_385, AnchorStart_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("abc", options_, RE2::ANCHOR_START, "abcdef"));
}

// Test char_class count exceeding limit (more than 9 dots)
TEST_F(Re2FuzzerTest_385, TooManyCharClasses_385) {
  // Pattern with more than 9 '.' characters should cause early return
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("..........", options_, RE2::UNANCHORED, "test"));
}

// Test backslash_p count exceeding limit
TEST_F(Re2FuzzerTest_385, TooManyBackslashP_385) {
  // Pattern with more than 1 \p should cause early return
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("\\p{L}\\p{N}", options_, RE2::UNANCHORED, "test"));
}

// Test with exactly 9 char classes (boundary)
TEST_F(Re2FuzzerTest_385, ExactlyNineCharClasses_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput(".........", options_, RE2::UNANCHORED, "abcdefghi"));
}

// Test with exactly 1 backslash_p (boundary - should be allowed)
TEST_F(Re2FuzzerTest_385, ExactlyOneBackslashP_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("\\p{L}", options_, RE2::UNANCHORED, "a"));
}

// Test with dot_nl option enabled
TEST_F(Re2FuzzerTest_385, DotNlOption_385) {
  options_.set_dot_nl(true);
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("a.b", options_, RE2::UNANCHORED, "a\nb"));
}

// Test with case insensitive option
TEST_F(Re2FuzzerTest_385, CaseInsensitive_385) {
  options_.set_case_sensitive(false);
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("abc", options_, RE2::UNANCHORED, "ABC"));
}

// Test with POSIX syntax
TEST_F(Re2FuzzerTest_385, PosixSyntax_385) {
  options_.set_posix_syntax(true);
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("abc", options_, RE2::UNANCHORED, "abc"));
}

// Test with literal mode
TEST_F(Re2FuzzerTest_385, LiteralMode_385) {
  options_.set_literal(true);
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("a.b", options_, RE2::UNANCHORED, "a.b"));
}

// Test with longest match
TEST_F(Re2FuzzerTest_385, LongestMatch_385) {
  options_.set_longest_match(true);
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("a+", options_, RE2::UNANCHORED, "aaa"));
}

// Test with never_nl option
TEST_F(Re2FuzzerTest_385, NeverNl_385) {
  options_.set_never_nl(true);
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput(".", options_, RE2::UNANCHORED, "\n"));
}

// Test with named capturing group
TEST_F(Re2FuzzerTest_385, NamedCapturingGroup_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("(?P<name>\\w+)", options_, RE2::UNANCHORED, "hello"));
}

// Test with alternation
TEST_F(Re2FuzzerTest_385, Alternation_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("a|b", options_, RE2::UNANCHORED, "b"));
}

// Test with repetition
TEST_F(Re2FuzzerTest_385, Repetition_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("a{2,3}", options_, RE2::UNANCHORED, "aaa"));
}

// Test with \\s character class
TEST_F(Re2FuzzerTest_385, BackslashS_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("\\s", options_, RE2::UNANCHORED, " "));
}

// Test with \\d character class
TEST_F(Re2FuzzerTest_385, BackslashD_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("\\d", options_, RE2::UNANCHORED, "5"));
}

// Test with \\w character class
TEST_F(Re2FuzzerTest_385, BackslashW_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("\\w+", options_, RE2::UNANCHORED, "hello"));
}

// Test with special characters in text
TEST_F(Re2FuzzerTest_385, SpecialCharsInText_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("test", options_, RE2::UNANCHORED, "te\0st"));
}

// Test QuoteMeta behavior via pattern with special chars
TEST_F(Re2FuzzerTest_385, PatternWithSpecialChars_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("a+b*c?", options_, RE2::UNANCHORED, "aabbc"));
}

// Test with never_capture option
TEST_F(Re2FuzzerTest_385, NeverCapture_385) {
  options_.set_never_capture(true);
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("(abc)", options_, RE2::UNANCHORED, "abc"));
}

// Test with 'k' and 'K' in pattern (char_class counter)
TEST_F(Re2FuzzerTest_385, CharClassCountK_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("kK", options_, RE2::UNANCHORED, "kK"));
}

// Test pattern with trailing backslash
TEST_F(Re2FuzzerTest_385, TrailingBackslash_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("abc\\", options_, RE2::UNANCHORED, "abc"));
}

// Test with pattern containing \\S and \\D (uppercase)
TEST_F(Re2FuzzerTest_385, BackslashUpperSD_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("\\S\\D", options_, RE2::UNANCHORED, "ab"));
}

// Test with \\P (uppercase)
TEST_F(Re2FuzzerTest_385, BackslashUpperP_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("\\P{L}", options_, RE2::UNANCHORED, "1"));
}

// Test with \\W
TEST_F(Re2FuzzerTest_385, BackslashUpperW_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("\\W", options_, RE2::UNANCHORED, " "));
}

// Test with long text
TEST_F(Re2FuzzerTest_385, LongText_385) {
  std::string long_text(1000, 'a');
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("a+", options_, RE2::UNANCHORED, long_text));
}

// Test with text that doesn't match the pattern
TEST_F(Re2FuzzerTest_385, NoMatch_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("xyz", options_, RE2::UNANCHORED, "abc"));
}

// Test with perl_classes option
TEST_F(Re2FuzzerTest_385, PerlClasses_385) {
  options_.set_perl_classes(true);
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("\\d+", options_, RE2::UNANCHORED, "123"));
}

// Test with word_boundary option
TEST_F(Re2FuzzerTest_385, WordBoundary_385) {
  options_.set_word_boundary(true);
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("abc", options_, RE2::UNANCHORED, "abc def"));
}

// Test with one_line option
TEST_F(Re2FuzzerTest_385, OneLine_385) {
  options_.set_one_line(true);
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("^abc$", options_, RE2::UNANCHORED, "abc"));
}

// Test with Latin1 encoding
TEST_F(Re2FuzzerTest_385, Latin1Encoding_385) {
  options_.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("abc", options_, RE2::UNANCHORED, "abc"));
}

// Test Replace and GlobalReplace functionality
TEST_F(Re2FuzzerTest_385, ReplaceOperations_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("a", options_, RE2::UNANCHORED, "aaa"));
}

// Test with Set Match (anchor = ANCHOR_BOTH)
TEST_F(Re2FuzzerTest_385, SetMatchAnchorBoth_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("abc", options_, RE2::ANCHOR_BOTH, "abc"));
}

// Test with limited max_mem
TEST_F(Re2FuzzerTest_385, LimitedMaxMem_385) {
  options_.set_max_mem(1024);
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("abc", options_, RE2::UNANCHORED, "abc"));
}

// Test with pattern that produces a larger program but within limits
TEST_F(Re2FuzzerTest_385, ModerateSizePattern_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("(a|b)(c|d)", options_, RE2::UNANCHORED, "ac"));
}

// Test with character class in brackets
TEST_F(Re2FuzzerTest_385, BracketCharClass_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("[a-z]+", options_, RE2::UNANCHORED, "hello"));
}

// Test with start and end anchors in pattern
TEST_F(Re2FuzzerTest_385, AnchoredPattern_385) {
  EXPECT_NO_FATAL_FAILURE(
      TestOneInput("^abc$", options_, RE2::UNANCHORED, "abc"));
}
