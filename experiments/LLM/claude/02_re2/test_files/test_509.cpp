#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "util/utf.h"

namespace re2 {

// Test fixture for Regexp::Parse and related functionality
class RegexpParseTest_509 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// ==================== Normal Operation Tests ====================

TEST_F(RegexpParseTest_509, ParseSimpleLiteral_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseAlternation_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseConcatenation_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  std::string s = re->Dump();
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseNestedGroups_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a(b)c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->NumCaptures(), 2);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseRepetitionStar_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseRepetitionPlus_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseRepetitionQuest_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseCharacterClass_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseCharacterClassRange_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseNegatedCharacterClass_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[^abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseDot_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseCaret_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseDollar_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseWordBoundary_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\babc\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseNonWordBoundary_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\Babc\\B", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseCountedRepetition_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseExactRepetition_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseNonGreedyRepetition_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseNonCapturingGroup_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseNamedCapture_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

// ==================== Collapse-related Tests via Parse ====================

TEST_F(RegexpParseTest_509, ParseNestedAlternation_509) {
  // This exercises DoCollapse with kRegexpAlternate
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c|d|e", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  // The alternation should be collapsed into a single node
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseNestedConcatenation_509) {
  // This exercises DoCollapse with kRegexpConcat
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abcdef", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseComplexAlternationWithGroups_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)|(c|d)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseAlternationWithConcat_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab|cd|ef", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

// ==================== Boundary Conditions ====================

TEST_F(RegexpParseTest_509, ParseEmptyString_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseSingleCharacter_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseEmptyAlternation_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("|", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseEmptyGroup_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("()", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseSingleAlternation_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseManyAlternations_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c|d|e|f|g|h|i|j", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseLongConcatenation_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abcdefghijklmnopqrstuvwxyz", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseRepetitionZeroToZero_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{0,0}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseRepetitionZeroToOne_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{0,1}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

// ==================== Error Cases ====================

TEST_F(RegexpParseTest_509, ParseUnmatchedLeftParen_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST_F(RegexpParseTest_509, ParseUnmatchedRightParen_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc)", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST_F(RegexpParseTest_509, ParseBadRepetition_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("*", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST_F(RegexpParseTest_509, ParseBadRepetitionPlus_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("+", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST_F(RegexpParseTest_509, ParseBadRepetitionQuest_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("?", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST_F(RegexpParseTest_509, ParseUnclosedCharClass_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST_F(RegexpParseTest_509, ParseBadEscape_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST_F(RegexpParseTest_509, ParseBadCountedRepetition_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{5,3}", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

// ==================== Regexp Static Factory Methods ====================

TEST_F(RegexpParseTest_509, NewLiteral_509) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ConcatFactory_509) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* b = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* subs[] = {a, b};
  Regexp* re = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_509, AlternateFactory_509) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* b = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* subs[] = {a, b};
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_509, StarFactory_509) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Star(a, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST_F(RegexpParseTest_509, PlusFactory_509) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Plus(a, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

TEST_F(RegexpParseTest_509, QuestFactory_509) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Quest(a, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

TEST_F(RegexpParseTest_509, CaptureFactory_509) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Capture(a, Regexp::LikePerl, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

TEST_F(RegexpParseTest_509, RepeatFactory_509) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(a, Regexp::LikePerl, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

TEST_F(RegexpParseTest_509, HaveMatchFactory_509) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// ==================== Incref/Decref Tests ====================

TEST_F(RegexpParseTest_509, IncrefDecref_509) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re2->Decref();
}

// ==================== ToString / Dump Tests ====================

TEST_F(RegexpParseTest_509, ToStringRoundTrip_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)d+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

TEST_F(RegexpParseTest_509, DumpNonEmpty_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// ==================== Simplify Tests ====================

TEST_F(RegexpParseTest_509, SimplifyRegexp_509) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,3}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

TEST_F(RegexpParseTest_509, SimplifyMethod_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simple = re->Simplify();
  ASSERT_NE(simple, nullptr);
  simple->Decref();
  re->Decref();
}

// ==================== NumCaptures Tests ====================

TEST_F(RegexpParseTest_509, NumCapturesNone_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpParseTest_509, NumCapturesMultiple_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// ==================== RequiredPrefix Tests ====================

TEST_F(RegexpParseTest_509, RequiredPrefixSimple_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    if (suffix != nullptr) {
      suffix->Decref();
    }
  }
  re->Decref();
}

// ==================== POSIX Mode Tests ====================

TEST_F(RegexpParseTest_509, ParsePOSIXMode_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

// ==================== Complex Patterns ====================

TEST_F(RegexpParseTest_509, ParseComplexPattern_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a+|b*)?c{2,4}[d-f]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseEscapedCharacters_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\d+\\.\\d+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ParseUnicodeClass_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

// ==================== Concat with single element ====================

TEST_F(RegexpParseTest_509, ConcatSingleElement_509) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* subs[] = {a};
  Regexp* re = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_509, AlternateSingleElement_509) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* subs[] = {a};
  Regexp* re = Regexp::Alternate(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_509, ConcatZeroElements_509) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_509, AlternateZeroElements_509) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// ==================== AlternateNoFactor Tests ====================

TEST_F(RegexpParseTest_509, AlternateNoFactorMultiple_509) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* b = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* c = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* subs[] = {a, b, c};
  Regexp* re = Regexp::AlternateNoFactor(subs, 3, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// ==================== LiteralString Tests ====================

TEST_F(RegexpParseTest_509, LiteralStringFactory_509) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  re->Decref();
}

// ==================== simple() accessor ====================

TEST_F(RegexpParseTest_509, SimpleAccessor_509) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // simple() should be a valid bool value
  bool s = re->simple();
  (void)s;  // Just checking it doesn't crash
  re->Decref();
}

// ==================== Deeply Nested Pattern ====================

TEST_F(RegexpParseTest_509, ParseDeeplyNestedGroups_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((((a))))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->NumCaptures(), 4);
  re->Decref();
}

// ==================== Mixed alternation and concatenation ====================

TEST_F(RegexpParseTest_509, ParseMixedAlternationConcat_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab|cd|ef|gh", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// ==================== Nested repetition ====================

TEST_F(RegexpParseTest_509, ParseNestedRepetition_509) {
  RegexpStatus status;
  // Nested repetition like (a+)* - should parse
  Regexp* re = Regexp::Parse("(a+)*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

// ==================== CaptureNames Tests ====================

TEST_F(RegexpParseTest_509, CaptureNamesWithNamedGroups_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  std::map<int, std::string>* names = re->CaptureNames();
  if (names != nullptr) {
    EXPECT_EQ(names->size(), 2u);
    delete names;
  }
  re->Decref();
}

TEST_F(RegexpParseTest_509, NamedCapturesMap_509) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  if (named != nullptr) {
    EXPECT_EQ(named->size(), 2u);
    EXPECT_NE(named->find("foo"), named->end());
    EXPECT_NE(named->find("bar"), named->end());
    delete named;
  }
  re->Decref();
}

// ==================== Flags accessor ====================

TEST_F(RegexpParseTest_509, ParseFlagsAccessor_509) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  Regexp::ParseFlags flags = re->parse_flags();
  // Just verify it doesn't crash and returns something
  (void)flags;
  re->Decref();
}

}  // namespace re2
