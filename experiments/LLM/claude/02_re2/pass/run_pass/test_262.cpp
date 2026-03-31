#include "re2/re2.h"
#include "gtest/gtest.h"
#include "absl/strings/string_view.h"
#include <string>
#include <vector>

namespace re2 {
namespace {

// Test fixture for RE2::Match tests
class RE2MatchTest_262 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Normal Operation Tests ====================

TEST_F(RE2MatchTest_262, SimpleMatchUnanchored_262) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  absl::string_view text("say hello world");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "hello");
}

TEST_F(RE2MatchTest_262, SimpleMatchAnchorStart_262) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello world");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::ANCHOR_START, &submatch, 1));
  EXPECT_EQ(submatch, "hello");
}

TEST_F(RE2MatchTest_262, SimpleMatchAnchorBoth_262) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::ANCHOR_BOTH, &submatch, 1));
  EXPECT_EQ(submatch, "hello");
}

TEST_F(RE2MatchTest_262, AnchorBothNoMatch_262) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello world");
  absl::string_view submatch;
  EXPECT_FALSE(re.Match(text, 0, text.size(), RE2::ANCHOR_BOTH, &submatch, 1));
}

TEST_F(RE2MatchTest_262, AnchorStartNoMatch_262) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  absl::string_view text("say hello");
  absl::string_view submatch;
  EXPECT_FALSE(re.Match(text, 0, text.size(), RE2::ANCHOR_START, &submatch, 1));
}

TEST_F(RE2MatchTest_262, CapturingGroups_262) {
  RE2 re("(\\w+)@(\\w+)");
  ASSERT_TRUE(re.ok());
  absl::string_view text("user@host");
  absl::string_view submatch[3];
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, submatch, 3));
  EXPECT_EQ(submatch[0], "user@host");
  EXPECT_EQ(submatch[1], "user");
  EXPECT_EQ(submatch[2], "host");
}

TEST_F(RE2MatchTest_262, NoSubmatchRequested_262) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello world");
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, nullptr, 0));
}

TEST_F(RE2MatchTest_262, PartialTextRange_262) {
  RE2 re("world");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello world!");
  absl::string_view submatch;
  // Search in "hello world" (excluding '!')
  EXPECT_TRUE(re.Match(text, 0, text.size() - 1, RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "world");
}

TEST_F(RE2MatchTest_262, StartposNonZero_262) {
  RE2 re("world");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello world");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 6, text.size(), RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "world");
}

TEST_F(RE2MatchTest_262, StartposSkipsPastMatch_262) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello world");
  absl::string_view submatch;
  EXPECT_FALSE(re.Match(text, 6, text.size(), RE2::UNANCHORED, &submatch, 1));
}

TEST_F(RE2MatchTest_262, EmptyPattern_262) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "");
}

TEST_F(RE2MatchTest_262, EmptyText_262) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  absl::string_view text("");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, 0, RE2::UNANCHORED, &submatch, 1));
}

TEST_F(RE2MatchTest_262, EmptyTextNoMatch_262) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  absl::string_view text("");
  absl::string_view submatch;
  EXPECT_FALSE(re.Match(text, 0, 0, RE2::UNANCHORED, &submatch, 1));
}

// ==================== Boundary Conditions ====================

TEST_F(RE2MatchTest_262, StartposEqualsEndpos_262) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello");
  absl::string_view submatch;
  // startpos == endpos means empty substring
  EXPECT_TRUE(re.Match(text, 3, 3, RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "");
}

TEST_F(RE2MatchTest_262, FullTextRange_262) {
  RE2 re("hello world");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello world");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::ANCHOR_BOTH, &submatch, 1));
  EXPECT_EQ(submatch, "hello world");
}

TEST_F(RE2MatchTest_262, EndposAtTextSize_262) {
  RE2 re("world");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello world");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
}

TEST_F(RE2MatchTest_262, NsubmatchLessThanCaptures_262) {
  RE2 re("(a)(b)(c)");
  ASSERT_TRUE(re.ok());
  absl::string_view text("abc");
  absl::string_view submatch[2];
  // Only request 2 submatches out of 4 (full match + 3 groups)
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ(submatch[0], "abc");
  EXPECT_EQ(submatch[1], "a");
}

TEST_F(RE2MatchTest_262, NsubmatchMoreThanCaptures_262) {
  RE2 re("(a)b");
  ASSERT_TRUE(re.ok());
  absl::string_view text("ab");
  absl::string_view submatch[5];
  // Request 5 submatches but only 2 are meaningful (full match + 1 group)
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, submatch, 5));
  EXPECT_EQ(submatch[0], "ab");
  EXPECT_EQ(submatch[1], "a");
  // Extra submatches should be empty
  EXPECT_EQ(submatch[2], "");
  EXPECT_EQ(submatch[3], "");
  EXPECT_EQ(submatch[4], "");
}

TEST_F(RE2MatchTest_262, NsubmatchOne_262) {
  RE2 re("(\\d+)-(\\d+)");
  ASSERT_TRUE(re.ok());
  absl::string_view text("123-456");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "123-456");
}

// ==================== Error / Exceptional Cases ====================

TEST_F(RE2MatchTest_262, InvalidRegex_262) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("(unclosed", opts);
  EXPECT_FALSE(re.ok());
  absl::string_view text("test");
  absl::string_view submatch;
  EXPECT_FALSE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
}

TEST_F(RE2MatchTest_262, StartposGreaterThanEndpos_262) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("hello", opts);
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello world");
  absl::string_view submatch;
  EXPECT_FALSE(re.Match(text, 5, 3, RE2::UNANCHORED, &submatch, 1));
}

TEST_F(RE2MatchTest_262, EndposGreaterThanTextSize_262) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("hello", opts);
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello");
  absl::string_view submatch;
  EXPECT_FALSE(re.Match(text, 0, text.size() + 10, RE2::UNANCHORED, &submatch, 1));
}

TEST_F(RE2MatchTest_262, StartposEqualsTextSizeEndposGreater_262) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("hello", opts);
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello");
  absl::string_view submatch;
  EXPECT_FALSE(re.Match(text, text.size(), text.size() + 1, RE2::UNANCHORED, &submatch, 1));
}

// ==================== Regex Feature Tests ====================

TEST_F(RE2MatchTest_262, DotStarMatch_262) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  absl::string_view text("anything goes here");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::ANCHOR_BOTH, &submatch, 1));
  EXPECT_EQ(submatch, text);
}

TEST_F(RE2MatchTest_262, AnchoredPatternStart_262) {
  RE2 re("^hello");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello world");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "hello");
}

TEST_F(RE2MatchTest_262, AnchoredPatternEnd_262) {
  RE2 re("world$");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello world");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "world");
}

TEST_F(RE2MatchTest_262, CaseInsensitiveMatch_262) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  absl::string_view text("HELLO world");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "HELLO");
}

TEST_F(RE2MatchTest_262, LongestMatchOption_262) {
  RE2::Options opts;
  opts.set_longest_match(true);
  RE2 re("a+", opts);
  ASSERT_TRUE(re.ok());
  absl::string_view text("aaa");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "aaa");
}

TEST_F(RE2MatchTest_262, LiteralMatch_262) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);  // Should match literal "a.b", not regex
  ASSERT_TRUE(re.ok());
  absl::string_view text("a.b");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "a.b");
}

TEST_F(RE2MatchTest_262, LiteralNoRegexMatch_262) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  ASSERT_TRUE(re.ok());
  absl::string_view text("axb");
  absl::string_view submatch;
  EXPECT_FALSE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
}

TEST_F(RE2MatchTest_262, NumberOfCapturingGroups_262) {
  RE2 re("(a)(b)(c)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(RE2MatchTest_262, NoCapturingGroups_262) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(RE2MatchTest_262, MatchWithinSubrange_262) {
  RE2 re("bc");
  ASSERT_TRUE(re.ok());
  absl::string_view text("abcde");
  absl::string_view submatch;
  // Search within "bcd" (positions 1..4)
  EXPECT_TRUE(re.Match(text, 1, 4, RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "bc");
}

TEST_F(RE2MatchTest_262, MatchNotInSubrange_262) {
  RE2 re("ab");
  ASSERT_TRUE(re.ok());
  absl::string_view text("abcde");
  absl::string_view submatch;
  // Search within "cde" (positions 2..5), "ab" is not there
  EXPECT_FALSE(re.Match(text, 2, 5, RE2::UNANCHORED, &submatch, 1));
}

TEST_F(RE2MatchTest_262, AnchorBothWithSubrange_262) {
  RE2 re("bcd");
  ASSERT_TRUE(re.ok());
  absl::string_view text("abcde");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 1, 4, RE2::ANCHOR_BOTH, &submatch, 1));
  EXPECT_EQ(submatch, "bcd");
}

TEST_F(RE2MatchTest_262, AnchorBothWithSubrangeFail_262) {
  RE2 re("bc");
  ASSERT_TRUE(re.ok());
  absl::string_view text("abcde");
  absl::string_view submatch;
  // "bc" doesn't cover the entire range [1,4) = "bcd"
  EXPECT_FALSE(re.Match(text, 1, 4, RE2::ANCHOR_BOTH, &submatch, 1));
}

TEST_F(RE2MatchTest_262, OptionalCapturingGroup_262) {
  RE2 re("(a)(b)?(c)");
  ASSERT_TRUE(re.ok());
  absl::string_view text("ac");
  absl::string_view submatch[4];
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, submatch, 4));
  EXPECT_EQ(submatch[0], "ac");
  EXPECT_EQ(submatch[1], "a");
  EXPECT_EQ(submatch[2], "");  // optional group not matched
  EXPECT_EQ(submatch[3], "c");
}

TEST_F(RE2MatchTest_262, MultipleMatchesReturnFirst_262) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  absl::string_view text("abc 123 def 456");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "123");
}

TEST_F(RE2MatchTest_262, ZeroLengthStartposEndpos_262) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, 0, RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "");
}

TEST_F(RE2MatchTest_262, ComplexPattern_262) {
  RE2 re("(\\d{4})-(\\d{2})-(\\d{2})");
  ASSERT_TRUE(re.ok());
  absl::string_view text("Date: 2023-12-25 is Christmas");
  absl::string_view submatch[4];
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, submatch, 4));
  EXPECT_EQ(submatch[0], "2023-12-25");
  EXPECT_EQ(submatch[1], "2023");
  EXPECT_EQ(submatch[2], "12");
  EXPECT_EQ(submatch[3], "25");
}

TEST_F(RE2MatchTest_262, PatternWithAlternation_262) {
  RE2 re("cat|dog");
  ASSERT_TRUE(re.ok());
  absl::string_view text("I have a dog");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "dog");
}

TEST_F(RE2MatchTest_262, PatternNoMatchInText_262) {
  RE2 re("xyz");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello world");
  absl::string_view submatch;
  EXPECT_FALSE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
}

TEST_F(RE2MatchTest_262, MatchStartPosAtEnd_262) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello");
  absl::string_view submatch;
  // startpos == endpos == text.size()
  EXPECT_TRUE(re.Match(text, text.size(), text.size(), RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "");
}

TEST_F(RE2MatchTest_262, CaseSensitiveOptionDefault_262) {
  RE2 re("Hello");
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello");
  absl::string_view submatch;
  EXPECT_FALSE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
}

TEST_F(RE2MatchTest_262, CaseInsensitiveOption_262) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("Hello", opts);
  ASSERT_TRUE(re.ok());
  absl::string_view text("hello");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
}

TEST_F(RE2MatchTest_262, SubmatchPointerDataWithinOriginalText_262) {
  RE2 re("world");
  ASSERT_TRUE(re.ok());
  std::string text_str = "hello world";
  absl::string_view text(text_str);
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
  // Submatch should point into the original text
  EXPECT_GE(submatch.data(), text.data());
  EXPECT_LE(submatch.data() + submatch.size(), text.data() + text.size());
}

TEST_F(RE2MatchTest_262, AnchorStartWithStartpos_262) {
  // Pattern anchored to start with ^ but startpos > 0
  RE2 re("^hello");
  ASSERT_TRUE(re.ok());
  absl::string_view text("say hello");
  absl::string_view submatch;
  // With anchor_start and startpos != 0, should return false
  EXPECT_FALSE(re.Match(text, 4, text.size(), RE2::UNANCHORED, &submatch, 1));
}

TEST_F(RE2MatchTest_262, QuietOptionInvalidRegex_262) {
  RE2 re("(invalid", RE2::Quiet);
  EXPECT_FALSE(re.ok());
  absl::string_view text("test");
  EXPECT_FALSE(re.Match(text, 0, text.size(), RE2::UNANCHORED, nullptr, 0));
}

}  // namespace
}  // namespace re2
