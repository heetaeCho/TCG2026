#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

// Helper to parse a regexp conveniently
static Regexp* ParseRegexp(const std::string& pattern, Regexp::ParseFlags flags = Regexp::LikePerl) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, flags, &status);
  EXPECT_TRUE(re != nullptr) << "Failed to parse: " << pattern << " error: " << status.Text();
  return re;
}

class RegexpEqualTest_349 : public ::testing::Test {
 protected:
  void TearDown() override {
    for (Regexp* re : to_decref_) {
      if (re) re->Decref();
    }
  }

  Regexp* Track(Regexp* re) {
    to_decref_.push_back(re);
    return re;
  }

  std::vector<Regexp*> to_decref_;
};

// Test that identical simple patterns are equal
TEST_F(RegexpEqualTest_349, IdenticalPatternsAreEqual_349) {
  Regexp* a = Track(ParseRegexp("abc"));
  Regexp* b = Track(ParseRegexp("abc"));
  ASSERT_TRUE(a != nullptr);
  ASSERT_TRUE(b != nullptr);
  // We test via ToString equality as Equal is private;
  // but we can use the public RegexpEqualTestingOnly if available
  EXPECT_EQ(a->ToString(), b->ToString());
}

// Test that different patterns produce different ToString
TEST_F(RegexpEqualTest_349, DifferentPatternsAreDifferent_349) {
  Regexp* a = Track(ParseRegexp("abc"));
  Regexp* b = Track(ParseRegexp("def"));
  ASSERT_TRUE(a != nullptr);
  ASSERT_TRUE(b != nullptr);
  EXPECT_NE(a->ToString(), b->ToString());
}

// Test NoMatch regexp
TEST_F(RegexpEqualTest_349, NoMatchRegexp_349) {
  Regexp* a = Track(ParseRegexp("[^\\s\\S]"));
  ASSERT_TRUE(a != nullptr);
  // Just verify it parses and has a valid op
  EXPECT_TRUE(a->op() >= kRegexpNoMatch && a->op() <= kMaxRegexpOp);
}

// Test EmptyMatch regexp
TEST_F(RegexpEqualTest_349, EmptyMatchRegexp_349) {
  Regexp* a = Track(ParseRegexp(""));
  // Empty pattern should parse
  // It may result in kRegexpEmptyMatch or similar
  ASSERT_TRUE(a != nullptr);
}

// Test Literal regexp
TEST_F(RegexpEqualTest_349, LiteralRegexp_349) {
  Regexp* a = Track(ParseRegexp("a", Regexp::Literal));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpLiteral, a->op());
  EXPECT_EQ('a', a->rune());
}

// Test Literal with FoldCase flag
TEST_F(RegexpEqualTest_349, LiteralFoldCase_349) {
  Regexp* a = Track(ParseRegexp("a", static_cast<Regexp::ParseFlags>(Regexp::Literal | Regexp::FoldCase)));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpLiteral, a->op());
}

// Test LiteralString regexp
TEST_F(RegexpEqualTest_349, LiteralStringRegexp_349) {
  Regexp* a = Track(ParseRegexp("hello", Regexp::Literal));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpLiteralString, a->op());
  EXPECT_EQ(5, a->nrunes());
}

// Test Star regexp
TEST_F(RegexpEqualTest_349, StarRegexp_349) {
  Regexp* a = Track(ParseRegexp("a*"));
  ASSERT_TRUE(a != nullptr);
  std::string s = a->ToString();
  EXPECT_NE(std::string::npos, s.find('*'));
}

// Test Plus regexp
TEST_F(RegexpEqualTest_349, PlusRegexp_349) {
  Regexp* a = Track(ParseRegexp("a+"));
  ASSERT_TRUE(a != nullptr);
  std::string s = a->ToString();
  EXPECT_NE(std::string::npos, s.find('+'));
}

// Test Quest regexp
TEST_F(RegexpEqualTest_349, QuestRegexp_349) {
  Regexp* a = Track(ParseRegexp("a?"));
  ASSERT_TRUE(a != nullptr);
  std::string s = a->ToString();
  EXPECT_NE(std::string::npos, s.find('?'));
}

// Test Repeat regexp
TEST_F(RegexpEqualTest_349, RepeatRegexp_349) {
  Regexp* a = Track(ParseRegexp("a{3,5}"));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpRepeat, a->op());
  EXPECT_EQ(3, a->min());
  EXPECT_EQ(5, a->max());
}

// Test Repeat with same min and max
TEST_F(RegexpEqualTest_349, RepeatExactRegexp_349) {
  Regexp* a = Track(ParseRegexp("a{3}"));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpRepeat, a->op());
  EXPECT_EQ(3, a->min());
  EXPECT_EQ(3, a->max());
}

// Test Alternation regexp
TEST_F(RegexpEqualTest_349, AlternateRegexp_349) {
  Regexp* a = Track(ParseRegexp("a|b"));
  ASSERT_TRUE(a != nullptr);
  // Could be kRegexpAlternate or kRegexpCharClass after simplification
  EXPECT_TRUE(a->op() == kRegexpAlternate || a->op() == kRegexpCharClass);
}

// Test Concat regexp
TEST_F(RegexpEqualTest_349, ConcatRegexp_349) {
  Regexp* a = Track(ParseRegexp("ab"));
  ASSERT_TRUE(a != nullptr);
  // "ab" as a literal string or concat of literals
  EXPECT_TRUE(a->op() == kRegexpConcat || a->op() == kRegexpLiteralString);
}

// Test Capture regexp
TEST_F(RegexpEqualTest_349, CaptureRegexp_349) {
  Regexp* a = Track(ParseRegexp("(a)"));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpCapture, a->op());
  EXPECT_EQ(1, a->cap());
}

// Test Named Capture regexp
TEST_F(RegexpEqualTest_349, NamedCaptureRegexp_349) {
  Regexp* a = Track(ParseRegexp("(?P<name>a)"));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpCapture, a->op());
  EXPECT_TRUE(a->name() != nullptr);
  EXPECT_EQ("name", *a->name());
}

// Test AnyChar (dot) regexp
TEST_F(RegexpEqualTest_349, AnyCharRegexp_349) {
  Regexp* a = Track(ParseRegexp(".", static_cast<Regexp::ParseFlags>(Regexp::LikePerl | Regexp::DotNL)));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpAnyChar, a->op());
}

// Test BeginLine and EndLine
TEST_F(RegexpEqualTest_349, BeginEndLineRegexp_349) {
  Regexp* a = Track(ParseRegexp("^a$"));
  ASSERT_TRUE(a != nullptr);
  // The top-level may be a concat; just ensure it parses
  EXPECT_TRUE(a->op() >= kRegexpNoMatch && a->op() <= kMaxRegexpOp);
}

// Test BeginText and EndText
TEST_F(RegexpEqualTest_349, BeginEndTextRegexp_349) {
  Regexp* a = Track(ParseRegexp("\\Aa\\z"));
  ASSERT_TRUE(a != nullptr);
}

// Test WordBoundary
TEST_F(RegexpEqualTest_349, WordBoundaryRegexp_349) {
  Regexp* a = Track(ParseRegexp("\\ba\\b"));
  ASSERT_TRUE(a != nullptr);
}

// Test CharClass regexp
TEST_F(RegexpEqualTest_349, CharClassRegexp_349) {
  Regexp* a = Track(ParseRegexp("[abc]"));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpCharClass, a->op());
  CharClass* cc = a->cc();
  EXPECT_TRUE(cc != nullptr);
  EXPECT_EQ(3, cc->size());
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_TRUE(cc->Contains('b'));
  EXPECT_TRUE(cc->Contains('c'));
  EXPECT_FALSE(cc->Contains('d'));
}

// Test CharClass empty
TEST_F(RegexpEqualTest_349, CharClassEmpty_349) {
  Regexp* a = Track(ParseRegexp("[^\\s\\S]"));
  ASSERT_TRUE(a != nullptr);
  // This should be NoMatch
  EXPECT_EQ(kRegexpNoMatch, a->op());
}

// Test NonGreedy flag on Star
TEST_F(RegexpEqualTest_349, NonGreedyStar_349) {
  Regexp* a = Track(ParseRegexp("a*?"));
  ASSERT_TRUE(a != nullptr);
  std::string s = a->ToString();
  // Non-greedy star should have *? in its string representation
  EXPECT_NE(std::string::npos, s.find("*?"));
}

// Test NonGreedy flag on Plus
TEST_F(RegexpEqualTest_349, NonGreedyPlus_349) {
  Regexp* a = Track(ParseRegexp("a+?"));
  ASSERT_TRUE(a != nullptr);
  std::string s = a->ToString();
  EXPECT_NE(std::string::npos, s.find("+?"));
}

// Test NonGreedy flag on Quest
TEST_F(RegexpEqualTest_349, NonGreedyQuest_349) {
  Regexp* a = Track(ParseRegexp("a??"));
  ASSERT_TRUE(a != nullptr);
  std::string s = a->ToString();
  EXPECT_NE(std::string::npos, s.find("??"));
}

// Test HaveMatch via factory
TEST_F(RegexpEqualTest_349, HaveMatchRegexp_349) {
  Regexp* a = Track(Regexp::HaveMatch(42, Regexp::NoParseFlags));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpHaveMatch, a->op());
  EXPECT_EQ(42, a->match_id());
}

// Test NumCaptures
TEST_F(RegexpEqualTest_349, NumCaptures_349) {
  Regexp* a = Track(ParseRegexp("(a)(b)(c)"));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(3, a->NumCaptures());
}

// Test NumCaptures with nested
TEST_F(RegexpEqualTest_349, NumCapturesNested_349) {
  Regexp* a = Track(ParseRegexp("((a)(b))"));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(3, a->NumCaptures());
}

// Test NumCaptures zero
TEST_F(RegexpEqualTest_349, NumCapturesZero_349) {
  Regexp* a = Track(ParseRegexp("abc"));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(0, a->NumCaptures());
}

// Test NamedCaptures
TEST_F(RegexpEqualTest_349, NamedCaptures_349) {
  Regexp* a = Track(ParseRegexp("(?P<foo>a)(?P<bar>b)"));
  ASSERT_TRUE(a != nullptr);
  auto* named = a->NamedCaptures();
  ASSERT_TRUE(named != nullptr);
  EXPECT_EQ(2u, named->size());
  EXPECT_EQ(1, (*named)["foo"]);
  EXPECT_EQ(2, (*named)["bar"]);
  delete named;
}

// Test CaptureNames
TEST_F(RegexpEqualTest_349, CaptureNames_349) {
  Regexp* a = Track(ParseRegexp("(?P<foo>a)(?P<bar>b)"));
  ASSERT_TRUE(a != nullptr);
  auto* names = a->CaptureNames();
  ASSERT_TRUE(names != nullptr);
  EXPECT_EQ("foo", (*names)[1]);
  EXPECT_EQ("bar", (*names)[2]);
  delete names;
}

// Test Incref and Decref
TEST_F(RegexpEqualTest_349, IncrefDecref_349) {
  Regexp* a = ParseRegexp("a");
  ASSERT_TRUE(a != nullptr);
  Regexp* b = a->Incref();
  EXPECT_EQ(a, b);
  // Decref once (from Incref)
  a->Decref();
  // Decref again (original)
  a->Decref();
  // No track needed since we manually decref'd
}

// Test ToString round-trip for various patterns
TEST_F(RegexpEqualTest_349, ToStringRoundTrip_349) {
  std::vector<std::string> patterns = {
    "a",
    "abc",
    "a*",
    "a+",
    "a?",
    "a{2,5}",
    "[a-z]",
    ".",
    "^",
    "$",
    "\\b",
    "\\B",
  };
  for (const auto& p : patterns) {
    Regexp* a = Track(ParseRegexp(p));
    ASSERT_TRUE(a != nullptr) << "Pattern: " << p;
    std::string s = a->ToString();
    // Parse the result again to ensure it's valid
    Regexp* b = Track(ParseRegexp(s));
    ASSERT_TRUE(b != nullptr) << "Re-parsed pattern: " << s << " (original: " << p << ")";
  }
}

// Test Simplify
TEST_F(RegexpEqualTest_349, Simplify_349) {
  Regexp* a = Track(ParseRegexp("a{1}"));
  ASSERT_TRUE(a != nullptr);
  Regexp* s = Track(a->Simplify());
  ASSERT_TRUE(s != nullptr);
  // a{1} simplifies to just 'a'
  EXPECT_EQ("a", s->ToString());
}

// Test SimplifyRegexp static method
TEST_F(RegexpEqualTest_349, SimplifyRegexpStatic_349) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{1,1}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ("a", dst);
}

// Test Dump
TEST_F(RegexpEqualTest_349, Dump_349) {
  Regexp* a = Track(ParseRegexp("a*"));
  ASSERT_TRUE(a != nullptr);
  std::string d = a->Dump();
  EXPECT_FALSE(d.empty());
}

// Test parsing error case
TEST_F(RegexpEqualTest_349, ParseError_349) {
  RegexpStatus status;
  Regexp* a = Regexp::Parse("[invalid", Regexp::LikePerl, &status);
  EXPECT_TRUE(a == nullptr);
}

// Test Parse with another error
TEST_F(RegexpEqualTest_349, ParseErrorUnbalancedParen_349) {
  RegexpStatus status;
  Regexp* a = Regexp::Parse("(abc", Regexp::LikePerl, &status);
  EXPECT_TRUE(a == nullptr);
}

// Test NewLiteral factory
TEST_F(RegexpEqualTest_349, NewLiteralFactory_349) {
  Regexp* a = Track(Regexp::NewLiteral('x', Regexp::NoParseFlags));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpLiteral, a->op());
  EXPECT_EQ('x', a->rune());
}

// Test LiteralString factory
TEST_F(RegexpEqualTest_349, LiteralStringFactory_349) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* a = Track(Regexp::LiteralString(runes, 5, Regexp::NoParseFlags));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpLiteralString, a->op());
  EXPECT_EQ(5, a->nrunes());
}

// Test Star factory
TEST_F(RegexpEqualTest_349, StarFactory_349) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* a = Track(Regexp::Star(sub, Regexp::NoParseFlags));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpStar, a->op());
}

// Test Plus factory
TEST_F(RegexpEqualTest_349, PlusFactory_349) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* a = Track(Regexp::Plus(sub, Regexp::NoParseFlags));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpPlus, a->op());
}

// Test Quest factory
TEST_F(RegexpEqualTest_349, QuestFactory_349) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* a = Track(Regexp::Quest(sub, Regexp::NoParseFlags));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpQuest, a->op());
}

// Test Capture factory
TEST_F(RegexpEqualTest_349, CaptureFactory_349) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* a = Track(Regexp::Capture(sub, Regexp::NoParseFlags, 5));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpCapture, a->op());
  EXPECT_EQ(5, a->cap());
}

// Test Repeat factory
TEST_F(RegexpEqualTest_349, RepeatFactory_349) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* a = Track(Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 7));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpRepeat, a->op());
  EXPECT_EQ(2, a->min());
  EXPECT_EQ(7, a->max());
}

// Test Concat factory
TEST_F(RegexpEqualTest_349, ConcatFactory_349) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* a = Track(Regexp::Concat(subs, 2, Regexp::NoParseFlags));
  ASSERT_TRUE(a != nullptr);
  // Could be LiteralString or Concat
  EXPECT_TRUE(a->op() == kRegexpConcat || a->op() == kRegexpLiteralString);
}

// Test Alternate factory
TEST_F(RegexpEqualTest_349, AlternateFactory_349) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* a = Track(Regexp::Alternate(subs, 2, Regexp::NoParseFlags));
  ASSERT_TRUE(a != nullptr);
  EXPECT_TRUE(a->op() == kRegexpAlternate || a->op() == kRegexpCharClass);
}

// Test CharClass Contains boundary
TEST_F(RegexpEqualTest_349, CharClassContainsBoundary_349) {
  Regexp* a = Track(ParseRegexp("[a-z]"));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpCharClass, a->op());
  CharClass* cc = a->cc();
  ASSERT_TRUE(cc != nullptr);
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_TRUE(cc->Contains('z'));
  EXPECT_TRUE(cc->Contains('m'));
  EXPECT_FALSE(cc->Contains('A'));
  EXPECT_FALSE(cc->Contains('0'));
}

// Test CharClass size for range
TEST_F(RegexpEqualTest_349, CharClassSize_349) {
  Regexp* a = Track(ParseRegexp("[a-z]"));
  ASSERT_TRUE(a != nullptr);
  CharClass* cc = a->cc();
  ASSERT_TRUE(cc != nullptr);
  EXPECT_EQ(26, cc->size());
  EXPECT_FALSE(cc->empty());
}

// Test RequiredPrefix
TEST_F(RegexpEqualTest_349, RequiredPrefix_349) {
  Regexp* a = Track(ParseRegexp("^abc.*"));
  ASSERT_TRUE(a != nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = a->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    if (suffix) Track(suffix);
  }
}

// Test EndText with WasDollar
TEST_F(RegexpEqualTest_349, EndTextWasDollar_349) {
  // $ in multiline mode is EndLine, in single-line it's EndText with WasDollar
  Regexp* a = Track(ParseRegexp("a$", static_cast<Regexp::ParseFlags>(Regexp::LikePerl | Regexp::OneLine)));
  ASSERT_TRUE(a != nullptr);
}

// Test op() accessor
TEST_F(RegexpEqualTest_349, OpAccessor_349) {
  Regexp* a = Track(ParseRegexp("a"));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpLiteral, a->op());
}

// Test parse_flags() accessor
TEST_F(RegexpEqualTest_349, ParseFlagsAccessor_349) {
  Regexp* a = Track(ParseRegexp("a", Regexp::FoldCase));
  ASSERT_TRUE(a != nullptr);
  EXPECT_TRUE((a->parse_flags() & Regexp::FoldCase) != 0);
}

// Test NeverCapture flag
TEST_F(RegexpEqualTest_349, NeverCaptureFlag_349) {
  Regexp* a = Track(ParseRegexp("(a)(b)", static_cast<Regexp::ParseFlags>(Regexp::LikePerl | Regexp::NeverCapture)));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(0, a->NumCaptures());
}

// Test complex pattern parsing
TEST_F(RegexpEqualTest_349, ComplexPattern_349) {
  Regexp* a = Track(ParseRegexp("(?:a|b)*c+[d-f]{2,4}"));
  ASSERT_TRUE(a != nullptr);
  std::string s = a->ToString();
  EXPECT_FALSE(s.empty());
}

// Test HaveMatch with different IDs
TEST_F(RegexpEqualTest_349, HaveMatchDifferentIds_349) {
  Regexp* a = Track(Regexp::HaveMatch(1, Regexp::NoParseFlags));
  Regexp* b = Track(Regexp::HaveMatch(2, Regexp::NoParseFlags));
  EXPECT_EQ(1, a->match_id());
  EXPECT_EQ(2, b->match_id());
}

// Test Repeat with unbounded max
TEST_F(RegexpEqualTest_349, RepeatUnboundedMax_349) {
  Regexp* a = Track(ParseRegexp("a{3,}"));
  ASSERT_TRUE(a != nullptr);
  EXPECT_EQ(kRegexpRepeat, a->op());
  EXPECT_EQ(3, a->min());
  EXPECT_EQ(-1, a->max());
}

// Test nsub for alternation
TEST_F(RegexpEqualTest_349, NsubAlternation_349) {
  Regexp* a = Track(ParseRegexp("a|b|c|d"));
  ASSERT_TRUE(a != nullptr);
  // After factoring, may become char class
  if (a->op() == kRegexpAlternate) {
    EXPECT_GE(a->nsub(), 2);
  }
}

// Test single character char class
TEST_F(RegexpEqualTest_349, SingleCharClass_349) {
  Regexp* a = Track(ParseRegexp("[a]"));
  ASSERT_TRUE(a != nullptr);
  // May optimize to literal
  EXPECT_TRUE(a->op() == kRegexpLiteral || a->op() == kRegexpCharClass);
}

}  // namespace re2
