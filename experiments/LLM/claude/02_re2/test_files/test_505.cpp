#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

// Test fixture for ParseState/DoFinish tests via the public Regexp::Parse interface
class DoFinishTest_505 : public ::testing::Test {
 protected:
  RegexpStatus status_;
};

// Test: Parsing a simple literal should succeed (DoFinish returns valid Regexp)
TEST_F(DoFinishTest_505, SimpleLiteral_505) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Empty string should parse successfully
TEST_F(DoFinishTest_505, EmptyString_505) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Unmatched left paren should trigger kRegexpMissingParen
TEST_F(DoFinishTest_505, UnmatchedLeftParen_505) {
  Regexp* re = Regexp::Parse("(abc", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpMissingParen);
}

// Test: Unmatched right paren should trigger kRegexpUnexpectedParen
TEST_F(DoFinishTest_505, UnmatchedRightParen_505) {
  Regexp* re = Regexp::Parse("abc)", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpUnexpectedParen);
}

// Test: Properly matched parentheses should succeed
TEST_F(DoFinishTest_505, MatchedParens_505) {
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Nested parentheses should succeed
TEST_F(DoFinishTest_505, NestedParens_505) {
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Alternation should succeed
TEST_F(DoFinishTest_505, SimpleAlternation_505) {
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Complex alternation with groups should succeed
TEST_F(DoFinishTest_505, AlternationWithGroups_505) {
  Regexp* re = Regexp::Parse("(a|b)|(c|d)", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Multiple unmatched left parens
TEST_F(DoFinishTest_505, MultipleUnmatchedLeftParens_505) {
  Regexp* re = Regexp::Parse("((abc", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpMissingParen);
}

// Test: Repetition operators should work properly after DoFinish
TEST_F(DoFinishTest_505, RepetitionOperator_505) {
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Star operator
TEST_F(DoFinishTest_505, StarOperator_505) {
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Question mark operator
TEST_F(DoFinishTest_505, QuestionOperator_505) {
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class should parse correctly
TEST_F(DoFinishTest_505, CharacterClass_505) {
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Unclosed character class should fail
TEST_F(DoFinishTest_505, UnclosedCharacterClass_505) {
  Regexp* re = Regexp::Parse("[abc", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpMissingBracket);
}

// Test: Dot metacharacter
TEST_F(DoFinishTest_505, DotMetacharacter_505) {
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Caret and dollar anchors
TEST_F(DoFinishTest_505, Anchors_505) {
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Non-capturing group should succeed
TEST_F(DoFinishTest_505, NonCapturingGroup_505) {
  Regexp* re = Regexp::Parse("(?:abc)", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Named capturing group should succeed
TEST_F(DoFinishTest_505, NamedCapturingGroup_505) {
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Complex pattern with multiple features
TEST_F(DoFinishTest_505, ComplexPattern_505) {
  Regexp* re = Regexp::Parse("^(a+|b*)?[c-f]\\d{2,5}$", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Single character parses correctly
TEST_F(DoFinishTest_505, SingleCharacter_505) {
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Alternation at top level results in correct structure
TEST_F(DoFinishTest_505, TopLevelAlternation_505) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test: Concatenation at top level
TEST_F(DoFinishTest_505, TopLevelConcatenation_505) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  // "abc" should be a concatenation or literal string
  re->Decref();
}

// Test: Verify error_arg is set on missing paren
TEST_F(DoFinishTest_505, ErrorArgOnMissingParen_505) {
  std::string pattern = "(abc";
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpMissingParen);
  // error_arg should reference the whole regexp
  EXPECT_FALSE(status_.error_arg().empty());
}

// Test: Repetition with bounds
TEST_F(DoFinishTest_505, BoundedRepetition_505) {
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Word boundary
TEST_F(DoFinishTest_505, WordBoundary_505) {
  Regexp* re = Regexp::Parse("\\babc\\b", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Bad escape should fail
TEST_F(DoFinishTest_505, BadEscape_505) {
  // In POSIX mode, backslash before certain characters may be an error
  Regexp* re = Regexp::Parse("\\", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpTrailingBackslash);
}

// Test: Repeat with no argument should fail
TEST_F(DoFinishTest_505, RepeatNoArgument_505) {
  Regexp* re = Regexp::Parse("*", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpRepeatArgument);
}

// Test: Double repeat operator should fail
TEST_F(DoFinishTest_505, DoubleRepeatOp_505) {
  Regexp* re = Regexp::Parse("a**", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpRepeatOp);
}

// Test: Parse with POSIX flags
TEST_F(DoFinishTest_505, PosixFlags_505) {
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Empty alternation branches
TEST_F(DoFinishTest_505, EmptyAlternationBranches_505) {
  Regexp* re = Regexp::Parse("|", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Deeply nested groups
TEST_F(DoFinishTest_505, DeeplyNestedGroups_505) {
  Regexp* re = Regexp::Parse("((((a))))", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

}  // namespace re2
