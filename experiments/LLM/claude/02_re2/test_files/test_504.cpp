#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

// Test fixture for DoRightParen tests via the public Regexp::Parse interface
class DoRightParenTest_504 : public ::testing::Test {
 protected:
  RegexpStatus status_;
};

// Test: Unmatched right paren should fail with kRegexpUnexpectedParen
TEST_F(DoRightParenTest_504, UnmatchedRightParen_504) {
  Regexp* re = Regexp::Parse(")", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpUnexpectedParen);
}

// Test: Matched parentheses with empty content should succeed
TEST_F(DoRightParenTest_504, EmptyParentheses_504) {
  Regexp* re = Regexp::Parse("()", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Simple capture group with a literal
TEST_F(DoRightParenTest_504, SimpleCaptureGroup_504) {
  Regexp* re = Regexp::Parse("(a)", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  // The top-level should be a capture
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test: Nested parentheses
TEST_F(DoRightParenTest_504, NestedParentheses_504) {
  Regexp* re = Regexp::Parse("((a))", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  // Inner should also be a capture
  ASSERT_EQ(re->nsub(), 1);
  Regexp* inner = re->sub()[0];
  EXPECT_EQ(inner->op(), kRegexpCapture);
  EXPECT_EQ(inner->cap(), 2);
  re->Decref();
}

// Test: Multiple right parens without matching left parens
TEST_F(DoRightParenTest_504, ExtraRightParen_504) {
  Regexp* re = Regexp::Parse("(a))", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpUnexpectedParen);
}

// Test: Non-capturing group followed by right paren
TEST_F(DoRightParenTest_504, NonCapturingGroup_504) {
  Regexp* re = Regexp::Parse("(?:a)", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  // Non-capturing group should not produce a capture node at top level
  // It should just be the literal 'a'
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test: Non-capturing group with alternation inside
TEST_F(DoRightParenTest_504, NonCapturingGroupWithAlternation_504) {
  Regexp* re = Regexp::Parse("(?:a|b)", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test: Capturing group with alternation inside
TEST_F(DoRightParenTest_504, CapturingGroupWithAlternation_504) {
  Regexp* re = Regexp::Parse("(a|b)", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpCapture);
  ASSERT_EQ(re->nsub(), 1);
  EXPECT_EQ(re->sub()[0]->op(), kRegexpAlternate);
  re->Decref();
}

// Test: Right paren at start of string
TEST_F(DoRightParenTest_504, RightParenAtStart_504) {
  Regexp* re = Regexp::Parse(")", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpUnexpectedParen);
}

// Test: Multiple capture groups
TEST_F(DoRightParenTest_504, MultipleCaptureGroups_504) {
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  // Should be a concatenation of two capture groups
  EXPECT_EQ(re->op(), kRegexpConcat);
  ASSERT_EQ(re->nsub(), 2);
  EXPECT_EQ(re->sub()[0]->op(), kRegexpCapture);
  EXPECT_EQ(re->sub()[0]->cap(), 1);
  EXPECT_EQ(re->sub()[1]->op(), kRegexpCapture);
  EXPECT_EQ(re->sub()[1]->cap(), 2);
  re->Decref();
}

// Test: Named capture group
TEST_F(DoRightParenTest_504, NamedCaptureGroup_504) {
  Regexp* re = Regexp::Parse("(?P<name>a)", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  ASSERT_NE(re->name(), nullptr);
  EXPECT_EQ(*re->name(), "name");
  re->Decref();
}

// Test: Missing right paren should fail with kRegexpMissingParen
TEST_F(DoRightParenTest_504, MissingRightParen_504) {
  Regexp* re = Regexp::Parse("(a", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpMissingParen);
}

// Test: Complex expression with repetition inside parens
TEST_F(DoRightParenTest_504, RepetitionInsideParens_504) {
  Regexp* re = Regexp::Parse("(a+)", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpCapture);
  ASSERT_EQ(re->nsub(), 1);
  EXPECT_EQ(re->sub()[0]->op(), kRegexpPlus);
  re->Decref();
}

// Test: Deeply nested parentheses
TEST_F(DoRightParenTest_504, DeeplyNestedParentheses_504) {
  Regexp* re = Regexp::Parse("(((a)))", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test: Flags change inside non-capturing group (e.g., (?i:a))
TEST_F(DoRightParenTest_504, FlagGroupRestoresFlags_504) {
  Regexp* re = Regexp::Parse("(?i:a)b", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Empty non-capturing group
TEST_F(DoRightParenTest_504, EmptyNonCapturingGroup_504) {
  Regexp* re = Regexp::Parse("(?:)", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test: Capture group number correctness with multiple groups
TEST_F(DoRightParenTest_504, CaptureGroupNumbering_504) {
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpConcat);
  ASSERT_EQ(re->nsub(), 3);
  EXPECT_EQ(re->sub()[0]->cap(), 1);
  EXPECT_EQ(re->sub()[1]->cap(), 2);
  EXPECT_EQ(re->sub()[2]->cap(), 3);
  re->Decref();
}

// Test: Verify NumCaptures after parsing with captures
TEST_F(DoRightParenTest_504, NumCapturesAfterParse_504) {
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->NumCaptures(), 2);
  re->Decref();
}

// Test: Right paren after vertical bar in non-capturing group
TEST_F(DoRightParenTest_504, VerticalBarInNonCapturingGroup_504) {
  Regexp* re = Regexp::Parse("(?:a|)", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: POSIX mode - unmatched right paren
TEST_F(DoRightParenTest_504, PosixUnmatchedRightParen_504) {
  Regexp* re = Regexp::Parse(")", Regexp::PerlX, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpUnexpectedParen);
}

}  // namespace re2
