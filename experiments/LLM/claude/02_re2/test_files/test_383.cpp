#include <gtest/gtest.h>
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/fuzzing/re2_fuzzer.cc"

namespace {

using re2::Regexp;
using re2::RegexpStatus;

class SubstringWalkerTest_383 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Helper to parse a regex and walk it
int WalkRegexp(const std::string& pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, re2::Regexp::LikePerl, &status);
  if (re == nullptr) return -2;  // parse error sentinel
  SubstringWalker walker;
  int result = walker.Walk(re, -1);
  re->Decref();
  return result;
}

// Test: A single literal character should return -1 (kRegexpLiteral, not LiteralString)
TEST_F(SubstringWalkerTest_383, SingleLiteralReturnsNegOne_383) {
  int result = WalkRegexp("a");
  EXPECT_EQ(result, -1);
}

// Test: A literal string (multiple chars concatenated) - the concat returns max of children
// Each child is a single literal which returns -1, so concat returns -1
TEST_F(SubstringWalkerTest_383, ConcatOfLiteralsReturnsNegOne_383) {
  int result = WalkRegexp("abc");
  // "abc" is parsed as Concat of literals, each literal returns -1, max of -1s is -1
  EXPECT_EQ(result, -1);
}

// Test: Empty match should return -1
TEST_F(SubstringWalkerTest_383, EmptyMatchReturnsNegOne_383) {
  int result = WalkRegexp("");
  EXPECT_EQ(result, -1);
}

// Test: Alternation of literals
TEST_F(SubstringWalkerTest_383, AlternateReturnsMaxOfChildren_383) {
  int result = WalkRegexp("a|b");
  // Alternate of two literals, each -1, max is -1
  EXPECT_EQ(result, -1);
}

// Test: Star of a literal
TEST_F(SubstringWalkerTest_383, StarOfLiteralReturnsNegOne_383) {
  int result = WalkRegexp("a*");
  EXPECT_EQ(result, -1);
}

// Test: Plus of a literal
TEST_F(SubstringWalkerTest_383, PlusOfLiteralReturnsNegOne_383) {
  int result = WalkRegexp("a+");
  EXPECT_EQ(result, -1);
}

// Test: Quest (optional) of a literal
TEST_F(SubstringWalkerTest_383, QuestOfLiteralReturnsNegOne_383) {
  int result = WalkRegexp("a?");
  EXPECT_EQ(result, -1);
}

// Test: Capture group with a literal
TEST_F(SubstringWalkerTest_383, CaptureReturnsMaxOfChild_383) {
  int result = WalkRegexp("(a)");
  EXPECT_EQ(result, -1);
}

// Test: Repeat {n,m} of a literal
TEST_F(SubstringWalkerTest_383, RepeatOfLiteralReturnsNegOne_383) {
  int result = WalkRegexp("a{2,5}");
  EXPECT_EQ(result, -1);
}

// Test: AnyChar (dot) returns -1
TEST_F(SubstringWalkerTest_383, AnyCharReturnsNegOne_383) {
  int result = WalkRegexp(".");
  EXPECT_EQ(result, -1);
}

// Test: BeginLine anchor returns -1
TEST_F(SubstringWalkerTest_383, BeginLineReturnsNegOne_383) {
  int result = WalkRegexp("^");
  EXPECT_EQ(result, -1);
}

// Test: EndLine anchor returns -1
TEST_F(SubstringWalkerTest_383, EndLineReturnsNegOne_383) {
  int result = WalkRegexp("$");
  EXPECT_EQ(result, -1);
}

// Test: Character class returns -1
TEST_F(SubstringWalkerTest_383, CharClassReturnsNegOne_383) {
  int result = WalkRegexp("[abc]");
  EXPECT_EQ(result, -1);
}

// Test: Word boundary returns -1
TEST_F(SubstringWalkerTest_383, WordBoundaryReturnsNegOne_383) {
  int result = WalkRegexp("\\b");
  EXPECT_EQ(result, -1);
}

// Test: Directly construct a LiteralString regexp and walk it
TEST_F(SubstringWalkerTest_383, LiteralStringReturnsNrunes_383) {
  re2::Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, re2::Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  SubstringWalker walker;
  int result = walker.Walk(re, -1);
  EXPECT_EQ(result, 5);
  re->Decref();
}

// Test: LiteralString with 1 rune
TEST_F(SubstringWalkerTest_383, LiteralStringOneRuneReturnsOne_383) {
  re2::Rune runes[] = {'x'};
  Regexp* re = Regexp::LiteralString(runes, 1, re2::Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  SubstringWalker walker;
  int result = walker.Walk(re, -1);
  EXPECT_EQ(result, 1);
  re->Decref();
}

// Test: Capture wrapping a LiteralString should return the nrunes value
TEST_F(SubstringWalkerTest_383, CaptureOfLiteralStringReturnsNrunes_383) {
  re2::Rune runes[] = {'a', 'b', 'c'};
  Regexp* litstr = Regexp::LiteralString(runes, 3, re2::Regexp::NoParseFlags);
  ASSERT_NE(litstr, nullptr);
  Regexp* cap = Regexp::Capture(litstr, re2::Regexp::NoParseFlags, 1);
  ASSERT_NE(cap, nullptr);
  SubstringWalker walker;
  int result = walker.Walk(cap, -1);
  EXPECT_EQ(result, 3);
  cap->Decref();
}

// Test: Star wrapping a LiteralString
TEST_F(SubstringWalkerTest_383, StarOfLiteralStringReturnsNrunes_383) {
  re2::Rune runes[] = {'x', 'y'};
  Regexp* litstr = Regexp::LiteralString(runes, 2, re2::Regexp::NoParseFlags);
  ASSERT_NE(litstr, nullptr);
  Regexp* star = Regexp::Star(litstr, re2::Regexp::NoParseFlags);
  ASSERT_NE(star, nullptr);
  SubstringWalker walker;
  int result = walker.Walk(star, -1);
  EXPECT_EQ(result, 2);
  star->Decref();
}

// Test: Alternate of LiteralStrings returns the max nrunes
TEST_F(SubstringWalkerTest_383, AlternateOfLiteralStringsReturnsMax_383) {
  re2::Rune runes1[] = {'a', 'b'};
  re2::Rune runes2[] = {'c', 'd', 'e', 'f'};
  Regexp* lit1 = Regexp::LiteralString(runes1, 2, re2::Regexp::NoParseFlags);
  Regexp* lit2 = Regexp::LiteralString(runes2, 4, re2::Regexp::NoParseFlags);
  ASSERT_NE(lit1, nullptr);
  ASSERT_NE(lit2, nullptr);
  Regexp* subs[] = {lit1, lit2};
  Regexp* alt = Regexp::AlternateNoFactor(subs, 2, re2::Regexp::NoParseFlags);
  ASSERT_NE(alt, nullptr);
  SubstringWalker walker;
  int result = walker.Walk(alt, -1);
  EXPECT_EQ(result, 4);
  alt->Decref();
}

// Test: Concat of a literal and a LiteralString returns max (nrunes of LiteralString)
TEST_F(SubstringWalkerTest_383, ConcatOfLiteralAndLiteralStringReturnsMax_383) {
  Regexp* lit = Regexp::NewLiteral('z', re2::Regexp::NoParseFlags);
  re2::Rune runes[] = {'a', 'b', 'c'};
  Regexp* litstr = Regexp::LiteralString(runes, 3, re2::Regexp::NoParseFlags);
  ASSERT_NE(lit, nullptr);
  ASSERT_NE(litstr, nullptr);
  Regexp* subs[] = {lit, litstr};
  Regexp* concat = Regexp::Concat(subs, 2, re2::Regexp::NoParseFlags);
  ASSERT_NE(concat, nullptr);
  SubstringWalker walker;
  int result = walker.Walk(concat, -1);
  EXPECT_EQ(result, 3);
  concat->Decref();
}

// Test: Nested structure - Capture(Plus(LiteralString))
TEST_F(SubstringWalkerTest_383, NestedCapturePlusLiteralString_383) {
  re2::Rune runes[] = {'t', 'e', 's', 't'};
  Regexp* litstr = Regexp::LiteralString(runes, 4, re2::Regexp::NoParseFlags);
  ASSERT_NE(litstr, nullptr);
  Regexp* plus = Regexp::Plus(litstr, re2::Regexp::NoParseFlags);
  ASSERT_NE(plus, nullptr);
  Regexp* cap = Regexp::Capture(plus, re2::Regexp::NoParseFlags, 1);
  ASSERT_NE(cap, nullptr);
  SubstringWalker walker;
  int result = walker.Walk(cap, -1);
  EXPECT_EQ(result, 4);
  cap->Decref();
}

// Test: Quest of a NewLiteral returns -1
TEST_F(SubstringWalkerTest_383, QuestOfNewLiteralReturnsNegOne_383) {
  Regexp* lit = Regexp::NewLiteral('a', re2::Regexp::NoParseFlags);
  ASSERT_NE(lit, nullptr);
  Regexp* quest = Regexp::Quest(lit, re2::Regexp::NoParseFlags);
  ASSERT_NE(quest, nullptr);
  SubstringWalker walker;
  int result = walker.Walk(quest, -1);
  EXPECT_EQ(result, -1);
  quest->Decref();
}

// Test: HaveMatch returns -1
TEST_F(SubstringWalkerTest_383, HaveMatchReturnsNegOne_383) {
  Regexp* re = Regexp::HaveMatch(0, re2::Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  SubstringWalker walker;
  int result = walker.Walk(re, -1);
  EXPECT_EQ(result, -1);
  re->Decref();
}

// Test: Repeat of LiteralString returns nrunes
TEST_F(SubstringWalkerTest_383, RepeatOfLiteralStringReturnsNrunes_383) {
  re2::Rune runes[] = {'r', 'e'};
  Regexp* litstr = Regexp::LiteralString(runes, 2, re2::Regexp::NoParseFlags);
  ASSERT_NE(litstr, nullptr);
  Regexp* rep = Regexp::Repeat(litstr, re2::Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(rep, nullptr);
  SubstringWalker walker;
  int result = walker.Walk(rep, -1);
  EXPECT_EQ(result, 2);
  rep->Decref();
}

// Test: Large LiteralString
TEST_F(SubstringWalkerTest_383, LargeLiteralStringReturnsCorrectNrunes_383) {
  const int N = 100;
  re2::Rune runes[N];
  for (int i = 0; i < N; i++) runes[i] = 'a' + (i % 26);
  Regexp* litstr = Regexp::LiteralString(runes, N, re2::Regexp::NoParseFlags);
  ASSERT_NE(litstr, nullptr);
  SubstringWalker walker;
  int result = walker.Walk(litstr, -1);
  EXPECT_EQ(result, N);
  litstr->Decref();
}

}  // namespace
