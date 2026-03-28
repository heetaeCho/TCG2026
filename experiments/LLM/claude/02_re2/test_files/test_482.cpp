#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>

namespace re2 {

// Test fixture for ParseState and FinishRegexp tests
class FinishRegexpTest_482 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that FinishRegexp returns NULL when given NULL
TEST_F(FinishRegexpTest_482, NullInput_482) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::PerlX, "test", &status);
  Regexp* result = ps.FinishRegexp(NULL);
  EXPECT_EQ(result, nullptr);
}

// Test FinishRegexp with a literal regexp (non-charclass)
TEST_F(FinishRegexpTest_482, LiteralRegexp_482) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::PerlX, "a", &status);
  Regexp* re = Regexp::NewLiteral('a', Regexp::PerlX);
  ASSERT_NE(re, nullptr);
  Regexp* result = ps.FinishRegexp(re);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->op(), kRegexpLiteral);
  result->Decref();
}

// Test that Parse works for a simple literal
TEST_F(FinishRegexpTest_482, ParseSimpleLiteral_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test that Parse works for a character class
TEST_F(FinishRegexpTest_482, ParseCharClass_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  // After FinishRegexp, cc_ should be valid (ccb_ converted to cc_)
  EXPECT_NE(re->cc(), nullptr);
  re->Decref();
}

// Test that Parse works for concatenation
TEST_F(FinishRegexpTest_482, ParseConcatenation_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  re->Decref();
}

// Test that Parse works for alternation
TEST_F(FinishRegexpTest_482, ParseAlternation_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test that Parse works for star repetition
TEST_F(FinishRegexpTest_482, ParseStar_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test that Parse works for plus repetition
TEST_F(FinishRegexpTest_482, ParsePlus_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test that Parse works for quest (optional)
TEST_F(FinishRegexpTest_482, ParseQuest_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test that Parse works for capture group
TEST_F(FinishRegexpTest_482, ParseCapture_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test that Parse works for dot (any char)
TEST_F(FinishRegexpTest_482, ParseDot_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAnyChar);
  re->Decref();
}

// Test that Parse works for begin-of-line
TEST_F(FinishRegexpTest_482, ParseCaret_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  // With PerlX, ^ is begin text by default
  re->Decref();
}

// Test that Parse works for end-of-line
TEST_F(FinishRegexpTest_482, ParseDollar_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("$", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Parse with empty string
TEST_F(FinishRegexpTest_482, ParseEmpty_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Parse with complex character class [a-z]
TEST_F(FinishRegexpTest_482, ParseCharClassRange_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  EXPECT_NE(re->cc(), nullptr);
  re->Decref();
}

// Test Parse with negated character class [^a-z]
TEST_F(FinishRegexpTest_482, ParseNegatedCharClass_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[^a-z]", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  EXPECT_NE(re->cc(), nullptr);
  re->Decref();
}

// Test Parse with word boundary
TEST_F(FinishRegexpTest_482, ParseWordBoundary_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\b", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpWordBoundary);
  re->Decref();
}

// Test Parse with non-word boundary
TEST_F(FinishRegexpTest_482, ParseNonWordBoundary_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\B", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoWordBoundary);
  re->Decref();
}

// Test Parse with repetition {2,5}
TEST_F(FinishRegexpTest_482, ParseRepetition_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test Parse with exact repetition {3}
TEST_F(FinishRegexpTest_482, ParseExactRepetition_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

// Test Parse with invalid regexp returns NULL and sets status
TEST_F(FinishRegexpTest_482, ParseInvalidRegexp_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::PerlX, &status);
  EXPECT_EQ(re, nullptr);
}

// Test Parse with another invalid regexp - unmatched )
TEST_F(FinishRegexpTest_482, ParseInvalidRightParen_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(")", Regexp::PerlX, &status);
  EXPECT_EQ(re, nullptr);
}

// Test NumCaptures
TEST_F(FinishRegexpTest_482, NumCaptures_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with nested groups
TEST_F(FinishRegexpTest_482, NumCapturesNested_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with zero captures
TEST_F(FinishRegexpTest_482, NumCapturesZero_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test ParseState DoLeftParen/DoRightParen sequence
TEST_F(FinishRegexpTest_482, ParseStateParens_482) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::PerlX, "(a)", &status);
  EXPECT_TRUE(ps.DoLeftParen(""));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

// Test ParseState DoLeftParenNoCapture
TEST_F(FinishRegexpTest_482, ParseStateNoCaptureParens_482) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::PerlX, "(?:a)", &status);
  EXPECT_TRUE(ps.DoLeftParenNoCapture());
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test ParseState PushLiteral
TEST_F(FinishRegexpTest_482, ParseStatePushLiteral_482) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::PerlX, "a", &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test ParseState PushDot
TEST_F(FinishRegexpTest_482, ParseStatePushDot_482) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::PerlX, ".", &status);
  EXPECT_TRUE(ps.PushDot());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAnyChar);
  re->Decref();
}

// Test ParseState DoVerticalBar for alternation
TEST_F(FinishRegexpTest_482, ParseStateAlternation_482) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::PerlX, "a|b", &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('b'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  // a|b may be optimized to a char class
  re->Decref();
}

// Test ParseState with multiple literals forms concatenation
TEST_F(FinishRegexpTest_482, ParseStateConcatenation_482) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::PerlX, "ab", &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushLiteral('b'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test ParseState PushCaret
TEST_F(FinishRegexpTest_482, ParseStatePushCaret_482) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::PerlX, "^", &status);
  EXPECT_TRUE(ps.PushCaret());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test ParseState PushDollar
TEST_F(FinishRegexpTest_482, ParseStatePushDollar_482) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::PerlX, "$", &status);
  EXPECT_TRUE(ps.PushDollar());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test ParseState PushWordBoundary
TEST_F(FinishRegexpTest_482, ParseStatePushWordBoundary_482) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::PerlX, "\\b", &status);
  EXPECT_TRUE(ps.PushWordBoundary(true));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpWordBoundary);
  re->Decref();
}

// Test ParseState PushWordBoundary false (non-word boundary)
TEST_F(FinishRegexpTest_482, ParseStatePushNonWordBoundary_482) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::PerlX, "\\B", &status);
  EXPECT_TRUE(ps.PushWordBoundary(false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoWordBoundary);
  re->Decref();
}

// Test Regexp::ToString round-trip
TEST_F(FinishRegexpTest_482, ToStringRoundTrip_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b*", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test Regexp::Dump
TEST_F(FinishRegexpTest_482, DumpNotEmpty_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// Test SimplifyRegexp
TEST_F(FinishRegexpTest_482, SimplifyRegexp_482) {
  RegexpStatus status;
  std::string dst;
  bool ok = Regexp::SimplifyRegexp("a{2,3}", Regexp::PerlX, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test Simplify
TEST_F(FinishRegexpTest_482, Simplify_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,3}", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test NamedCaptures with named groups
TEST_F(FinishRegexpTest_482, NamedCaptures_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>a)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 1u);
  EXPECT_EQ((*named)["name"], 1);
  delete named;
  re->Decref();
}

// Test CaptureNames
TEST_F(FinishRegexpTest_482, CaptureNames_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>a)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 1u);
  EXPECT_EQ((*names)[1], "name");
  delete names;
  re->Decref();
}

// Test NamedCaptures returns NULL when no named captures
TEST_F(FinishRegexpTest_482, NamedCapturesNull_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  re->Decref();
}

// Test HaveMatch
TEST_F(FinishRegexpTest_482, HaveMatch_482) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::PerlX);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test NewLiteral
TEST_F(FinishRegexpTest_482, NewLiteral_482) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::PerlX);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'z');
  re->Decref();
}

// Test Star
TEST_F(FinishRegexpTest_482, Star_482) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::PerlX);
  Regexp* re = Regexp::Star(sub, Regexp::PerlX);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Plus
TEST_F(FinishRegexpTest_482, Plus_482) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::PerlX);
  Regexp* re = Regexp::Plus(sub, Regexp::PerlX);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Quest
TEST_F(FinishRegexpTest_482, Quest_482) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::PerlX);
  Regexp* re = Regexp::Quest(sub, Regexp::PerlX);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Capture
TEST_F(FinishRegexpTest_482, Capture_482) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::PerlX);
  Regexp* re = Regexp::Capture(sub, Regexp::PerlX, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test Repeat
TEST_F(FinishRegexpTest_482, Repeat_482) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::PerlX);
  Regexp* re = Regexp::Repeat(sub, Regexp::PerlX, 2, 4);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 4);
  re->Decref();
}

// Test Incref and Ref
TEST_F(FinishRegexpTest_482, IncrefAndRef_482) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::PerlX);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->Ref(), 1);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  EXPECT_EQ(re->Ref(), 2);
  re->Decref();
  re->Decref();
}

// Test LiteralString
TEST_F(FinishRegexpTest_482, LiteralString_482) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::PerlX);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test Parse with Perl character class \d
TEST_F(FinishRegexpTest_482, ParsePerlCharClass_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\d+", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Parse with non-greedy
TEST_F(FinishRegexpTest_482, ParseNonGreedy_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+?", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test that DoFinish on empty ParseState returns EmptyMatch
TEST_F(FinishRegexpTest_482, DoFinishEmpty_482) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::PerlX, "", &status);
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test PushRepeatOp
TEST_F(FinishRegexpTest_482, PushRepeatOp_482) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::PerlX, "a*", &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, "a*", false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test PushRepetition
TEST_F(FinishRegexpTest_482, PushRepetition_482) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::PerlX, "a{2,4}", &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(2, 4, "a{2,4}", false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  re->Decref();
}

// Test flags accessor
TEST_F(FinishRegexpTest_482, ParseStateFlags_482) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::PerlX, "test", &status);
  EXPECT_EQ(ps.flags(), Regexp::PerlX);
}

// Test complex pattern
TEST_F(FinishRegexpTest_482, ParseComplexPattern_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:foo|bar)+[0-9]{2,}", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test RequiredPrefix
TEST_F(FinishRegexpTest_482, RequiredPrefix_482) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello.*", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    if (suffix) suffix->Decref();
  }
  re->Decref();
}

}  // namespace re2
