#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

// Helper to parse and manage lifetime
class RegexpHelper {
 public:
  static Regexp* Parse(const std::string& pattern, Regexp::ParseFlags flags) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, flags, &status);
    return re;
  }
};

// =============================================================================
// Tests for Regexp::Parse
// =============================================================================

TEST(RegexpParseTest_481, ParseSimpleLiteral_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParseEmptyString_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParseInvalidRegexp_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST(RegexpParseTest_481, ParseUnmatchedParen_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(")", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST(RegexpParseTest_481, ParseAlternation_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParseRepetition_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParsePlus_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParseQuestionMark_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParseCharClass_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParseDot_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParseCaret_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParseDollar_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParseNamedCapture_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParseNonCapturingGroup_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParseNestedGroups_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParseRepetitionWithBraces_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParseExactRepetition_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParseWordBoundary_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bword\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParseBadCharClass_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[z-a]", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST(RegexpParseTest_481, ParseEscapedSpecial_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\.", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// =============================================================================
// Tests for Regexp::ToString
// =============================================================================

TEST(RegexpToStringTest_481, SimpleStringRoundTrip_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

TEST(RegexpToStringTest_481, AlternationToString_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// =============================================================================
// Tests for Regexp::NumCaptures
// =============================================================================

TEST(RegexpNumCapturesTest_481, NoCaptures_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST(RegexpNumCapturesTest_481, OneCapture_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST(RegexpNumCapturesTest_481, MultipleCaptures_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST(RegexpNumCapturesTest_481, NestedCaptures_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST(RegexpNumCapturesTest_481, NonCapturingDoesNotCount_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc)(def)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

// =============================================================================
// Tests for Regexp::NamedCaptures
// =============================================================================

TEST(RegexpNamedCapturesTest_481, NoNamedCaptures_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

TEST(RegexpNamedCapturesTest_481, WithNamedCapture_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 1u);
  EXPECT_NE(named->find("name"), named->end());
  EXPECT_EQ((*named)["name"], 1);
  delete named;
  re->Decref();
}

TEST(RegexpNamedCapturesTest_481, MultipleNamedCaptures_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 2u);
  EXPECT_EQ((*named)["first"], 1);
  EXPECT_EQ((*named)["second"], 2);
  delete named;
  re->Decref();
}

// =============================================================================
// Tests for Regexp::CaptureNames
// =============================================================================

TEST(RegexpCaptureNamesTest_481, NoCaptureNames_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);
  delete names;
  re->Decref();
}

TEST(RegexpCaptureNamesTest_481, WithCaptureNames_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 1u);
  EXPECT_EQ((*names)[1], "name");
  delete names;
  re->Decref();
}

// =============================================================================
// Tests for Regexp::Simplify
// =============================================================================

TEST(RegexpSimplifyTest_481, SimplifyLiteral_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simple = re->Simplify();
  ASSERT_NE(simple, nullptr);
  simple->Decref();
  re->Decref();
}

TEST(RegexpSimplifyTest_481, SimplifyComplex_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,4}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simple = re->Simplify();
  ASSERT_NE(simple, nullptr);
  simple->Decref();
  re->Decref();
}

// =============================================================================
// Tests for Regexp::SimplifyRegexp (static)
// =============================================================================

TEST(RegexpSimplifyRegexpTest_481, SimplifyRegexpBasic_481) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a+", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

TEST(RegexpSimplifyRegexpTest_481, SimplifyRegexpInvalid_481) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("(", Regexp::LikePerl, &dst, &status);
  EXPECT_FALSE(ok);
}

// =============================================================================
// Tests for Regexp::Incref / Decref / Ref
// =============================================================================

TEST(RegexpRefTest_481, IncrefAndDecref_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* same = re->Incref();
  EXPECT_EQ(same, re);
  // Now refcount should be 2
  re->Decref();
  // Refcount back to 1
  same->Decref();
  // Refcount 0, destroyed
}

// =============================================================================
// Tests for Regexp static factory methods
// =============================================================================

TEST(RegexpFactoryTest_481, NewLiteral_481) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

TEST(RegexpFactoryTest_481, HaveMatch_481) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

TEST(RegexpFactoryTest_481, Star_481) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* star = Regexp::Star(lit, Regexp::LikePerl);
  ASSERT_NE(star, nullptr);
  EXPECT_EQ(star->op(), kRegexpStar);
  star->Decref();
}

TEST(RegexpFactoryTest_481, Plus_481) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* plus = Regexp::Plus(lit, Regexp::LikePerl);
  ASSERT_NE(plus, nullptr);
  EXPECT_EQ(plus->op(), kRegexpPlus);
  plus->Decref();
}

TEST(RegexpFactoryTest_481, Quest_481) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* quest = Regexp::Quest(lit, Regexp::LikePerl);
  ASSERT_NE(quest, nullptr);
  EXPECT_EQ(quest->op(), kRegexpQuest);
  quest->Decref();
}

TEST(RegexpFactoryTest_481, Capture_481) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* cap = Regexp::Capture(lit, Regexp::LikePerl, 1);
  ASSERT_NE(cap, nullptr);
  EXPECT_EQ(cap->op(), kRegexpCapture);
  EXPECT_EQ(cap->cap(), 1);
  cap->Decref();
}

TEST(RegexpFactoryTest_481, Repeat_481) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* rep = Regexp::Repeat(lit, Regexp::LikePerl, 2, 5);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->op(), kRegexpRepeat);
  EXPECT_EQ(rep->min(), 2);
  EXPECT_EQ(rep->max(), 5);
  rep->Decref();
}

TEST(RegexpFactoryTest_481, Concat_481) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* b = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* subs[] = {a, b};
  Regexp* concat = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(concat, nullptr);
  concat->Decref();
}

TEST(RegexpFactoryTest_481, Alternate_481) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* b = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* subs[] = {a, b};
  Regexp* alt = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  alt->Decref();
}

TEST(RegexpFactoryTest_481, AlternateNoFactor_481) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* b = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* subs[] = {a, b};
  Regexp* alt = Regexp::AlternateNoFactor(subs, 2, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  alt->Decref();
}

TEST(RegexpFactoryTest_481, LiteralString_481) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// =============================================================================
// Tests for Regexp::RequiredPrefix
// =============================================================================

TEST(RegexpRequiredPrefixTest_481, HasPrefix_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    ASSERT_NE(suffix, nullptr);
    suffix->Decref();
  }
  re->Decref();
}

TEST(RegexpRequiredPrefixTest_481, NoPrefix_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

// =============================================================================
// Tests for Regexp::Dump
// =============================================================================

TEST(RegexpDumpTest_481, DumpLiteral_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

TEST(RegexpDumpTest_481, DumpComplex_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+|b*)?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// =============================================================================
// Tests for Parse with POSIX flags
// =============================================================================

TEST(RegexpParsePOSIXTest_481, ParsePOSIXBasic_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// =============================================================================
// Tests for complex patterns
// =============================================================================

TEST(RegexpParseComplexTest_481, ParseEscapeSequences_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\d+\\.\\d+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseComplexTest_481, ParseUnicodeClass_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseComplexTest_481, ParseNonGreedy_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+?b*?c??", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseComplexTest_481, ParseBadRepetition_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("*", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST(RegexpParseComplexTest_481, ParseBadRepetitionPlus_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("+", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST(RegexpParseComplexTest_481, ParseBadRepetitionQuestion_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("?", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// =============================================================================
// Tests for Regexp::CompileToProg
// =============================================================================

TEST(RegexpCompileTest_481, CompileToProg_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST(RegexpCompileTest_481, CompileToReverseProg_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// =============================================================================
// Tests for Regexp op accessor
// =============================================================================

TEST(RegexpOpTest_481, LiteralOp_481) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// =============================================================================
// Tests for Concat/Alternate with zero and one sub
// =============================================================================

TEST(RegexpFactoryEdgeCaseTest_481, ConcatZeroSubs_481) {
  Regexp* concat = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(concat, nullptr);
  concat->Decref();
}

TEST(RegexpFactoryEdgeCaseTest_481, ConcatOneSub_481) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* subs[] = {a};
  Regexp* concat = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(concat, nullptr);
  concat->Decref();
}

TEST(RegexpFactoryEdgeCaseTest_481, AlternateZeroSubs_481) {
  Regexp* alt = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  alt->Decref();
}

TEST(RegexpFactoryEdgeCaseTest_481, AlternateOneSub_481) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* subs[] = {a};
  Regexp* alt = Regexp::Alternate(subs, 1, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  alt->Decref();
}

// =============================================================================
// Tests for Regexp::NullWalk
// =============================================================================

TEST(RegexpNullWalkTest_481, NullWalkDoesNotCrash_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_NO_FATAL_FAILURE(re->NullWalk());
  re->Decref();
}

// =============================================================================
// Tests for parse_flags accessor
// =============================================================================

TEST(RegexpFlagsTest_481, ParseFlagsAccessor_481) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // parse_flags should contain the flags passed in
  EXPECT_NE(re->parse_flags() & Regexp::LikePerl, 0);
  re->Decref();
}

// =============================================================================
// Tests for Repeat with unbounded max (-1)
// =============================================================================

TEST(RegexpRepeatTest_481, RepeatUnbounded_481) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* rep = Regexp::Repeat(lit, Regexp::LikePerl, 2, -1);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->min(), 2);
  EXPECT_EQ(rep->max(), -1);
  rep->Decref();
}

// =============================================================================
// Tests for Regexp::MimicsPCRE
// =============================================================================

TEST(RegexpMimicsPCRETest_481, SimpleLiteralMimicsPCRE_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Just verify it doesn't crash and returns a boolean
  bool result = re->MimicsPCRE();
  (void)result;
  re->Decref();
}

// =============================================================================
// Tests for nested parse patterns 
// =============================================================================

TEST(RegexpParseTest_481, DeeplyNestedGroups_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((((a))))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 4);
  re->Decref();
}

TEST(RegexpParseTest_481, ParseFlagsInsidePattern_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_481, ParseComplexAlternation_481) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(foo|bar|baz)+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

}  // namespace re2
