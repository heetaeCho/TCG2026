#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

// Test that Simplify works on basic regexps
TEST(CoalesceWalkerTest_425, SimplifyBasicLiteral_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  simplified->Decref();
  re->Decref();
}

TEST(CoalesceWalkerTest_425, SimplifyAlternation_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  simplified->Decref();
  re->Decref();
}

TEST(CoalesceWalkerTest_425, SimplifyCharacterClass_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  simplified->Decref();
  re->Decref();
}

TEST(CoalesceWalkerTest_425, SimplifyRepetition_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  simplified->Decref();
  re->Decref();
}

TEST(CoalesceWalkerTest_425, SimplifyStarPlus_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*b+c?", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  simplified->Decref();
  re->Decref();
}

TEST(CoalesceWalkerTest_425, SimplifyNestedGroups_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a(b(c)))", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  simplified->Decref();
  re->Decref();
}

TEST(CoalesceWalkerTest_425, SimplifyDot_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  simplified->Decref();
  re->Decref();
}

TEST(CoalesceWalkerTest_425, SimplifyEmptyRegexp_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST(CoalesceWalkerTest_425, SimplifyRegexpStatic_425) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,3}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

TEST(CoalesceWalkerTest_425, SimplifyRegexpStaticSimple_425) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("abc", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "abc");
}

TEST(CoalesceWalkerTest_425, SimplifyRegexpStaticCharClass_425) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("[a-zA-Z]", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test coalescing of consecutive character classes in alternation
TEST(CoalesceWalkerTest_425, SimplifyCoalesceAlternation_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-c]|[d-f]", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  std::string s = simplified->ToString();
  EXPECT_FALSE(s.empty());
  simplified->Decref();
  re->Decref();
}

// Test simplification of repeated patterns that might coalesce
TEST(CoalesceWalkerTest_425, SimplifyRepeatedConcat_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("aaa", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  simplified->Decref();
  re->Decref();
}

// Test that simplification is idempotent
TEST(CoalesceWalkerTest_425, SimplifyIdempotent_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* s1 = re->Simplify();
  ASSERT_TRUE(s1 != nullptr);
  Regexp* s2 = s1->Simplify();
  ASSERT_TRUE(s2 != nullptr);
  std::string str1 = s1->ToString();
  std::string str2 = s2->ToString();
  EXPECT_EQ(str1, str2);
  s2->Decref();
  s1->Decref();
  re->Decref();
}

// Test simplification with non-greedy quantifiers
TEST(CoalesceWalkerTest_425, SimplifyNonGreedy_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*?b+?c??", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  simplified->Decref();
  re->Decref();
}

// Test simplification with complex patterns
TEST(CoalesceWalkerTest_425, SimplifyComplexPattern_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c{1,3}[d-f]+", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  simplified->Decref();
  re->Decref();
}

// Test simplification with anchors
TEST(CoalesceWalkerTest_425, SimplifyAnchors_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  simplified->Decref();
  re->Decref();
}

// Test simplification of counted repetition
TEST(CoalesceWalkerTest_425, SimplifyCountedRepetition_425) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{0,1}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  // a{0,1} should simplify to a?
  EXPECT_EQ(dst, "a?");
}

TEST(CoalesceWalkerTest_425, SimplifyCountedRepetitionExact_425) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{3}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "aaa");
}

TEST(CoalesceWalkerTest_425, SimplifyCountedRepetitionRange_425) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,4}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "aaa?a?");
}

// Test simplification preserves matching semantics
TEST(CoalesceWalkerTest_425, SimplifyPreservesSemantics_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a|b){2,3}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  // Just verify it produces valid output
  std::string s = simplified->ToString();
  EXPECT_FALSE(s.empty());
  simplified->Decref();
  re->Decref();
}

// Test with POSIX flags
TEST(CoalesceWalkerTest_425, SimplifyPOSIX_425) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,3}", Regexp::PerlX, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test ShortVisit indirectly through deeply nested regexps
TEST(CoalesceWalkerTest_425, SimplifyDeeplyNested_425) {
  // Build a deeply nested pattern that might trigger ShortVisit
  std::string pattern;
  for (int i = 0; i < 100; i++) {
    pattern += "(";
  }
  pattern += "a";
  for (int i = 0; i < 100; i++) {
    pattern += ")";
  }
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  simplified->Decref();
  re->Decref();
}

// Test that Incref/Decref work correctly in simplification context
TEST(CoalesceWalkerTest_425, SimplifyRefCounting_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  // Both should be independently decref-able
  simplified->Decref();
  re->Decref();
}

// Test simplification with Unicode character classes
TEST(CoalesceWalkerTest_425, SimplifyUnicodeClass_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  simplified->Decref();
  re->Decref();
}

// Test simplification with word boundary
TEST(CoalesceWalkerTest_425, SimplifyWordBoundary_425) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bfoo\\b", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  simplified->Decref();
  re->Decref();
}

// Test a{0} simplification
TEST(CoalesceWalkerTest_425, SimplifyZeroRepetition_425) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{0}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
}

// Test a{1} simplification
TEST(CoalesceWalkerTest_425, SimplifyOneRepetition_425) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{1}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "a");
}

}  // namespace re2
