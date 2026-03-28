#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "util/utf.h"

namespace re2 {

class ParseStateTest_491 : public ::testing::Test {
 protected:
  void SetUp() override {
    status_ = new RegexpStatus;
  }

  void TearDown() override {
    delete status_;
  }

  RegexpStatus* status_;
};

// Test PushWordBoundary with word=true pushes kRegexpWordBoundary
TEST_F(ParseStateTest_491, PushWordBoundaryTrue_491) {
  absl::string_view pattern("\\b");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  bool result = state.PushWordBoundary(true);
  EXPECT_TRUE(result);
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpWordBoundary);
  re->Decref();
}

// Test PushWordBoundary with word=false pushes kRegexpNoWordBoundary
TEST_F(ParseStateTest_491, PushWordBoundaryFalse_491) {
  absl::string_view pattern("\\B");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  bool result = state.PushWordBoundary(false);
  EXPECT_TRUE(result);
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoWordBoundary);
  re->Decref();
}

// Test PushCaret pushes begin line/text marker
TEST_F(ParseStateTest_491, PushCaret_491) {
  absl::string_view pattern("^");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  bool result = state.PushCaret();
  EXPECT_TRUE(result);
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  // In PerlX mode, ^ matches beginning of line
  EXPECT_TRUE(re->op() == kRegexpBeginLine || re->op() == kRegexpBeginText);
  re->Decref();
}

// Test PushDollar pushes end line/text marker
TEST_F(ParseStateTest_491, PushDollar_491) {
  absl::string_view pattern("$");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  bool result = state.PushDollar();
  EXPECT_TRUE(result);
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->op() == kRegexpEndLine || re->op() == kRegexpEndText);
  re->Decref();
}

// Test PushDot pushes any char
TEST_F(ParseStateTest_491, PushDot_491) {
  absl::string_view pattern(".");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  bool result = state.PushDot();
  EXPECT_TRUE(result);
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  // Dot is either kRegexpAnyChar or kRegexpCharClass depending on flags
  EXPECT_TRUE(re->op() == kRegexpAnyChar || re->op() == kRegexpAnyByte || 
              re->op() == kRegexpCharClass);
  re->Decref();
}

// Test PushLiteral pushes a literal character
TEST_F(ParseStateTest_491, PushLiteral_491) {
  absl::string_view pattern("a");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  bool result = state.PushLiteral('a');
  EXPECT_TRUE(result);
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test multiple literals create a concatenation or literal string
TEST_F(ParseStateTest_491, PushMultipleLiterals_491) {
  absl::string_view pattern("ab");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_TRUE(state.PushLiteral('a'));
  EXPECT_TRUE(state.PushLiteral('b'));
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  // Two literals can be concatenated or become a literal string
  EXPECT_TRUE(re->op() == kRegexpConcat || re->op() == kRegexpLiteralString);
  re->Decref();
}

// Test DoLeftParen and DoRightParen for grouping
TEST_F(ParseStateTest_491, ParenGrouping_491) {
  absl::string_view pattern("(a)");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_TRUE(state.DoLeftParen(absl::string_view()));
  EXPECT_TRUE(state.PushLiteral('a'));
  EXPECT_TRUE(state.DoRightParen());
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

// Test DoLeftParenNoCapture for non-capturing group
TEST_F(ParseStateTest_491, NonCapturingGroup_491) {
  absl::string_view pattern("(?:a)");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_TRUE(state.DoLeftParenNoCapture());
  EXPECT_TRUE(state.PushLiteral('a'));
  EXPECT_TRUE(state.DoRightParen());
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  // Non-capturing group should just return the inner expression
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test alternation with DoVerticalBar
TEST_F(ParseStateTest_491, Alternation_491) {
  absl::string_view pattern("a|b");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_TRUE(state.PushLiteral('a'));
  EXPECT_TRUE(state.DoVerticalBar());
  EXPECT_TRUE(state.PushLiteral('b'));
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test PushRepeatOp with star
TEST_F(ParseStateTest_491, PushRepeatOpStar_491) {
  absl::string_view pattern("a*");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_TRUE(state.PushLiteral('a'));
  EXPECT_TRUE(state.PushRepeatOp(kRegexpStar, pattern, false));
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test PushRepeatOp with plus
TEST_F(ParseStateTest_491, PushRepeatOpPlus_491) {
  absl::string_view pattern("a+");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_TRUE(state.PushLiteral('a'));
  EXPECT_TRUE(state.PushRepeatOp(kRegexpPlus, pattern, false));
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test PushRepeatOp with quest (optional)
TEST_F(ParseStateTest_491, PushRepeatOpQuest_491) {
  absl::string_view pattern("a?");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_TRUE(state.PushLiteral('a'));
  EXPECT_TRUE(state.PushRepeatOp(kRegexpQuest, pattern, false));
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test nongreedy repeat
TEST_F(ParseStateTest_491, PushRepeatOpNonGreedy_491) {
  absl::string_view pattern("a*?");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_TRUE(state.PushLiteral('a'));
  EXPECT_TRUE(state.PushRepeatOp(kRegexpStar, pattern, true));
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test PushRepetition with specific min/max
TEST_F(ParseStateTest_491, PushRepetition_491) {
  absl::string_view pattern("a{2,5}");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_TRUE(state.PushLiteral('a'));
  EXPECT_TRUE(state.PushRepetition(2, 5, pattern, false));
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  re->Decref();
}

// Test PushRepetition with exact count
TEST_F(ParseStateTest_491, PushRepetitionExact_491) {
  absl::string_view pattern("a{3}");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_TRUE(state.PushLiteral('a'));
  EXPECT_TRUE(state.PushRepetition(3, 3, pattern, false));
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  re->Decref();
}

// Test empty pattern produces EmptyMatch
TEST_F(ParseStateTest_491, EmptyPatternFinish_491) {
  absl::string_view pattern("");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test flags accessor
TEST_F(ParseStateTest_491, FlagsAccessor_491) {
  absl::string_view pattern("test");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_EQ(state.flags(), Regexp::PerlX);
}

// Test word boundary followed by literal
TEST_F(ParseStateTest_491, WordBoundaryWithLiteral_491) {
  absl::string_view pattern("\\ba");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_TRUE(state.PushWordBoundary(true));
  EXPECT_TRUE(state.PushLiteral('a'));
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  re->Decref();
}

// Test no-word boundary followed by literal
TEST_F(ParseStateTest_491, NoWordBoundaryWithLiteral_491) {
  absl::string_view pattern("\\Ba");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_TRUE(state.PushWordBoundary(false));
  EXPECT_TRUE(state.PushLiteral('a'));
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  re->Decref();
}

// Test PushSimpleOp directly with various ops
TEST_F(ParseStateTest_491, PushSimpleOpEmptyMatch_491) {
  absl::string_view pattern("");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  bool result = state.PushSimpleOp(kRegexpEmptyMatch);
  EXPECT_TRUE(result);
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test complex expression: (a|b)*
TEST_F(ParseStateTest_491, ComplexExpression_491) {
  absl::string_view pattern("(a|b)*");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_TRUE(state.DoLeftParen(absl::string_view()));
  EXPECT_TRUE(state.PushLiteral('a'));
  EXPECT_TRUE(state.DoVerticalBar());
  EXPECT_TRUE(state.PushLiteral('b'));
  EXPECT_TRUE(state.DoRightParen());
  EXPECT_TRUE(state.PushRepeatOp(kRegexpStar, pattern, false));
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test named capture group
TEST_F(ParseStateTest_491, NamedCaptureGroup_491) {
  absl::string_view pattern("(?P<name>a)");
  absl::string_view name("name");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_TRUE(state.DoLeftParen(name));
  EXPECT_TRUE(state.PushLiteral('a'));
  EXPECT_TRUE(state.DoRightParen());
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

// Test PushRepetition with min=0, max=-1 (unbounded)
TEST_F(ParseStateTest_491, PushRepetitionUnbounded_491) {
  absl::string_view pattern("a{0,}");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_TRUE(state.PushLiteral('a'));
  EXPECT_TRUE(state.PushRepetition(0, -1, pattern, false));
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  // {0,} is equivalent to *
  EXPECT_TRUE(re->op() == kRegexpStar || re->op() == kRegexpRepeat);
  re->Decref();
}

// Test multiple alternations
TEST_F(ParseStateTest_491, MultipleAlternations_491) {
  absl::string_view pattern("a|b|c");
  Regexp::ParseState state(Regexp::PerlX, pattern, status_);
  
  EXPECT_TRUE(state.PushLiteral('a'));
  EXPECT_TRUE(state.DoVerticalBar());
  EXPECT_TRUE(state.PushLiteral('b'));
  EXPECT_TRUE(state.DoVerticalBar());
  EXPECT_TRUE(state.PushLiteral('c'));
  
  Regexp* re = state.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

}  // namespace re2
