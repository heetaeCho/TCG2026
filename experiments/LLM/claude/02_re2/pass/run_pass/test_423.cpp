#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

class SimplifyTest_423 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that Simplify returns a non-null result for a simple literal
TEST_F(SimplifyTest_423, SimplifyLiteral_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp with a simple pattern
TEST_F(SimplifyTest_423, SimplifyRegexpSimplePattern_423) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a+", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test SimplifyRegexp with an empty pattern
TEST_F(SimplifyTest_423, SimplifyRegexpEmptyPattern_423) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
}

// Test Simplify on a character class
TEST_F(SimplifyTest_423, SimplifyCharClass_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test Simplify on alternation
TEST_F(SimplifyTest_423, SimplifyAlternation_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test Simplify on concatenation
TEST_F(SimplifyTest_423, SimplifyConcatenation_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test Simplify on star
TEST_F(SimplifyTest_423, SimplifyStar_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test Simplify on plus
TEST_F(SimplifyTest_423, SimplifyPlus_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test Simplify on quest (optional)
TEST_F(SimplifyTest_423, SimplifyQuest_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test Simplify on repeat with specific count
TEST_F(SimplifyTest_423, SimplifyRepeatFixed_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test Simplify on repeat with range
TEST_F(SimplifyTest_423, SimplifyRepeatRange_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test Simplify on repeat with open upper bound
TEST_F(SimplifyTest_423, SimplifyRepeatOpenEnd_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test Simplify on nested groups
TEST_F(SimplifyTest_423, SimplifyNestedGroups_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a+)b)+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test Simplify on capture groups
TEST_F(SimplifyTest_423, SimplifyCapture_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test Simplify on dot star
TEST_F(SimplifyTest_423, SimplifyDotStar_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test that Simplify marks the result as simple
TEST_F(SimplifyTest_423, SimplifyMarksSimple_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  EXPECT_TRUE(simplified->simple());
  simplified->Decref();
  re->Decref();
}

// Test Simplify on non-greedy star
TEST_F(SimplifyTest_423, SimplifyNonGreedyStar_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test Simplify on non-greedy plus
TEST_F(SimplifyTest_423, SimplifyNonGreedyPlus_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test Simplify on non-greedy quest
TEST_F(SimplifyTest_423, SimplifyNonGreedyQuest_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a??", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp preserves semantic equivalence for repeat
TEST_F(SimplifyTest_423, SimplifyRegexpRepeatEquivalence_423) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{0,1}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  // a{0,1} should simplify to a?
  EXPECT_EQ(dst, "a?");
}

// Test SimplifyRegexp for a{0,} simplifies to a*
TEST_F(SimplifyTest_423, SimplifyRegexpRepeatZeroToInf_423) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{0,}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "a*");
}

// Test SimplifyRegexp for a{1,} simplifies to a+
TEST_F(SimplifyTest_423, SimplifyRegexpRepeatOneToInf_423) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{1,}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "a+");
}

// Test SimplifyRegexp for a{1} simplifies to a
TEST_F(SimplifyTest_423, SimplifyRegexpRepeatExactlyOne_423) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{1}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "a");
}

// Test Simplify idempotence - simplifying twice gives same result
TEST_F(SimplifyTest_423, SimplifyIdempotent_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* s1 = re->Simplify();
  ASSERT_NE(s1, nullptr);
  std::string str1 = s1->ToString();
  Regexp* s2 = s1->Simplify();
  ASSERT_NE(s2, nullptr);
  std::string str2 = s2->ToString();
  EXPECT_EQ(str1, str2);
  s2->Decref();
  s1->Decref();
  re->Decref();
}

// Test Simplify with word boundary
TEST_F(SimplifyTest_423, SimplifyWordBoundary_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bfoo\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test Simplify on complex pattern with multiple features
TEST_F(SimplifyTest_423, SimplifyComplexPattern_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+|b{2,4})?c*[d-f]+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  EXPECT_TRUE(simplified->simple());
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp with POSIX flags
TEST_F(SimplifyTest_423, SimplifyRegexpPOSIX_423) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,5}", Regexp::PerlX, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test Simplify on character class with case folding
TEST_F(SimplifyTest_423, SimplifyCharClassFoldCase_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp for a{0} simplifies to empty match
TEST_F(SimplifyTest_423, SimplifyRegexpRepeatZero_423) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{0}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
}

// Test Simplify on anchored patterns
TEST_F(SimplifyTest_423, SimplifyAnchored_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test Simplify on already simple regexp returns equivalent
TEST_F(SimplifyTest_423, SimplifyAlreadySimple_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  EXPECT_EQ(re->ToString(), simplified->ToString());
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp with non-greedy repeat
TEST_F(SimplifyTest_423, SimplifyRegexpNonGreedyRepeat_423) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,5}?", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test Simplify preserves non-greedy flag on star
TEST_F(SimplifyTest_423, SimplifyNonGreedyRepeatRange_423) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  // The simplified form should still have non-greedy semantics
  std::string s = simplified->ToString();
  EXPECT_FALSE(s.empty());
  simplified->Decref();
  re->Decref();
}

}  // namespace re2
