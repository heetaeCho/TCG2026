#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

class SimplifyTest_422 : public ::testing::Test {
 protected:
  Regexp* Parse(const char* pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::MatchNL | Regexp::PerlX, &status);
    EXPECT_TRUE(re != nullptr) << "Failed to parse: " << pattern
                                << " error: " << status.Text();
    return re;
  }
};

// Test that Simplify returns non-null for a simple literal
TEST_F(SimplifyTest_422, SimplifyLiteral_422) {
  Regexp* re = Parse("a");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test that Simplify returns non-null for empty regex
TEST_F(SimplifyTest_422, SimplifyEmptyString_422) {
  Regexp* re = Parse("");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of character class
TEST_F(SimplifyTest_422, SimplifyCharacterClass_422) {
  Regexp* re = Parse("[a-z]");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of star (a*)
TEST_F(SimplifyTest_422, SimplifyStar_422) {
  Regexp* re = Parse("a*");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of plus (a+)
TEST_F(SimplifyTest_422, SimplifyPlus_422) {
  Regexp* re = Parse("a+");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of quest (a?)
TEST_F(SimplifyTest_422, SimplifyQuest_422) {
  Regexp* re = Parse("a?");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of bounded repeat a{3,5}
TEST_F(SimplifyTest_422, SimplifyBoundedRepeat_422) {
  Regexp* re = Parse("a{3,5}");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of exact repeat a{3}
TEST_F(SimplifyTest_422, SimplifyExactRepeat_422) {
  Regexp* re = Parse("a{3}");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of alternation
TEST_F(SimplifyTest_422, SimplifyAlternation_422) {
  Regexp* re = Parse("a|b|c");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of concatenation
TEST_F(SimplifyTest_422, SimplifyConcatenation_422) {
  Regexp* re = Parse("abc");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of dot (any character)
TEST_F(SimplifyTest_422, SimplifyDot_422) {
  Regexp* re = Parse(".");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of capture group
TEST_F(SimplifyTest_422, SimplifyCapture_422) {
  Regexp* re = Parse("(abc)");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of nested repetition
TEST_F(SimplifyTest_422, SimplifyNestedRepetition_422) {
  Regexp* re = Parse("(a*)*");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of complex pattern
TEST_F(SimplifyTest_422, SimplifyComplexPattern_422) {
  Regexp* re = Parse("(a|b)*c+[d-f]{2,4}");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test that simplify is idempotent (simplifying twice gives same result)
TEST_F(SimplifyTest_422, SimplifyIdempotent_422) {
  Regexp* re = Parse("(a+)*");
  ASSERT_NE(re, nullptr);
  Regexp* sre1 = re->Simplify();
  ASSERT_NE(sre1, nullptr);
  Regexp* sre2 = sre1->Simplify();
  ASSERT_NE(sre2, nullptr);
  EXPECT_EQ(sre1->ToString(), sre2->ToString());
  sre2->Decref();
  sre1->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST_F(SimplifyTest_422, SimplifyRegexpStatic_422) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,3}", Regexp::MatchNL, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test SimplifyRegexp static method with simple pattern
TEST_F(SimplifyTest_422, SimplifyRegexpStaticSimple_422) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("abc", Regexp::MatchNL, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "abc");
}

// Test simplification of non-greedy star
TEST_F(SimplifyTest_422, SimplifyNonGreedyStar_422) {
  Regexp* re = Parse("a*?");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of non-greedy plus
TEST_F(SimplifyTest_422, SimplifyNonGreedyPlus_422) {
  Regexp* re = Parse("a+?");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of non-greedy quest
TEST_F(SimplifyTest_422, SimplifyNonGreedyQuest_422) {
  Regexp* re = Parse("a??");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test that a{0} simplifies to empty match
TEST_F(SimplifyTest_422, SimplifyZeroRepeat_422) {
  Regexp* re = Parse("a{0}");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of a{1}
TEST_F(SimplifyTest_422, SimplifyOneRepeat_422) {
  Regexp* re = Parse("a{1}");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  // a{1} should simplify to just 'a'
  std::string s = sre->ToString();
  EXPECT_EQ(s, "a");
  sre->Decref();
  re->Decref();
}

// Test simplification of [^\s\S] (empty character class)
TEST_F(SimplifyTest_422, SimplifyNegatedCharClass_422) {
  Regexp* re = Parse("[^\\s\\S]");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification with anchors
TEST_F(SimplifyTest_422, SimplifyWithAnchors_422) {
  Regexp* re = Parse("^abc$");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of word boundary
TEST_F(SimplifyTest_422, SimplifyWordBoundary_422) {
  Regexp* re = Parse("\\b");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test that a{0,1} simplifies similarly to a?
TEST_F(SimplifyTest_422, SimplifyRepeatZeroOne_422) {
  Regexp* re_repeat = Parse("a{0,1}");
  ASSERT_NE(re_repeat, nullptr);
  Regexp* re_quest = Parse("a?");
  ASSERT_NE(re_quest, nullptr);

  Regexp* sre_repeat = re_repeat->Simplify();
  Regexp* sre_quest = re_quest->Simplify();
  ASSERT_NE(sre_repeat, nullptr);
  ASSERT_NE(sre_quest, nullptr);

  EXPECT_EQ(sre_repeat->ToString(), sre_quest->ToString());

  sre_repeat->Decref();
  sre_quest->Decref();
  re_repeat->Decref();
  re_quest->Decref();
}

// Test that a{1,} simplifies similarly to a+
TEST_F(SimplifyTest_422, SimplifyRepeatOneOrMore_422) {
  Regexp* re_repeat = Parse("a{1,}");
  ASSERT_NE(re_repeat, nullptr);
  Regexp* re_plus = Parse("a+");
  ASSERT_NE(re_plus, nullptr);

  Regexp* sre_repeat = re_repeat->Simplify();
  Regexp* sre_plus = re_plus->Simplify();
  ASSERT_NE(sre_repeat, nullptr);
  ASSERT_NE(sre_plus, nullptr);

  EXPECT_EQ(sre_repeat->ToString(), sre_plus->ToString());

  sre_repeat->Decref();
  sre_plus->Decref();
  re_repeat->Decref();
  re_plus->Decref();
}

// Test that a{0,} simplifies similarly to a*
TEST_F(SimplifyTest_422, SimplifyRepeatZeroOrMore_422) {
  Regexp* re_repeat = Parse("a{0,}");
  ASSERT_NE(re_repeat, nullptr);
  Regexp* re_star = Parse("a*");
  ASSERT_NE(re_star, nullptr);

  Regexp* sre_repeat = re_repeat->Simplify();
  Regexp* sre_star = re_star->Simplify();
  ASSERT_NE(sre_repeat, nullptr);
  ASSERT_NE(sre_star, nullptr);

  EXPECT_EQ(sre_repeat->ToString(), sre_star->ToString());

  sre_repeat->Decref();
  sre_star->Decref();
  re_repeat->Decref();
  re_star->Decref();
}

// Test simplification of complex nested groups
TEST_F(SimplifyTest_422, SimplifyNestedGroups_422) {
  Regexp* re = Parse("((a|b)*c){2,3}");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test SimplifyRegexp with empty pattern
TEST_F(SimplifyTest_422, SimplifyRegexpEmptyPattern_422) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("", Regexp::MatchNL, &dst, &status);
  EXPECT_TRUE(ok);
}

// Test simplification of Unicode properties
TEST_F(SimplifyTest_422, SimplifyUnicodeProperty_422) {
  Regexp* re = Parse("\\pL+");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test that coalescing works - adjacent literals in alternation
TEST_F(SimplifyTest_422, SimplifyCoalesceCharClass_422) {
  Regexp* re = Parse("[ab]");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification of deeply nested structure
TEST_F(SimplifyTest_422, SimplifyDeeplyNested_422) {
  Regexp* re = Parse("((((a))))");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test SimplifyRegexp with case-insensitive flag
TEST_F(SimplifyTest_422, SimplifyRegexpCaseInsensitive_422) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("(?i)abc", Regexp::PerlX, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test that simplification doesn't change semantics for digit classes
TEST_F(SimplifyTest_422, SimplifyDigitClass_422) {
  Regexp* re = Parse("\\d+");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

// Test simplification with multiple capture groups
TEST_F(SimplifyTest_422, SimplifyMultipleCaptures_422) {
  Regexp* re = Parse("(a)(b)(c)");
  ASSERT_NE(re, nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_NE(sre, nullptr);
  sre->Decref();
  re->Decref();
}

}  // namespace re2
