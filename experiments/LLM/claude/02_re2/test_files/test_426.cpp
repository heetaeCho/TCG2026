#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

class SimplifyTest_426 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that SimplifyRegexp works on a simple literal
TEST_F(SimplifyTest_426, SimplifyLiteral_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("abc", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("abc", dst);
}

// Test that SimplifyRegexp works on an empty pattern
TEST_F(SimplifyTest_426, SimplifyEmpty_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
}

// Test simplification of character class
TEST_F(SimplifyTest_426, SimplifyCharClass_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("[a-z]", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("[a-z]", dst);
}

// Test simplification of star
TEST_F(SimplifyTest_426, SimplifyStar_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a*", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a*", dst);
}

// Test simplification of plus
TEST_F(SimplifyTest_426, SimplifyPlus_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a+", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a+", dst);
}

// Test simplification of quest
TEST_F(SimplifyTest_426, SimplifyQuest_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a?", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a?", dst);
}

// Test simplification of repeat {n,m}
TEST_F(SimplifyTest_426, SimplifyRepeat_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{2,5}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  // a{2,5} should be simplified to aa(?:a(?:a(?:a)?)?)?
  EXPECT_FALSE(dst.empty());
}

// Test simplification of repeat {n}
TEST_F(SimplifyTest_426, SimplifyRepeatExact_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{3}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("aaa", dst);
}

// Test simplification of repeat {0,1} which is same as ?
TEST_F(SimplifyTest_426, SimplifyRepeatZeroOne_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{0,1}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a?", dst);
}

// Test simplification of alternation
TEST_F(SimplifyTest_426, SimplifyAlternate_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a|b", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("[a-b]", dst);
}

// Test simplification of concatenation
TEST_F(SimplifyTest_426, SimplifyConcat_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("ab", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("ab", dst);
}

// Test simplification of capture group
TEST_F(SimplifyTest_426, SimplifyCapture_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("(a)", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("(a)", dst);
}

// Test simplification of dot
TEST_F(SimplifyTest_426, SimplifyDot_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp(".", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
}

// Test simplification of anchors
TEST_F(SimplifyTest_426, SimplifyAnchors_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("^a$", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
}

// Test simplification of nested repeats - a** should simplify
TEST_F(SimplifyTest_426, SimplifyNestedStar_426) {
  std::string dst;
  RegexpStatus status;
  // POSIX doesn't allow **, but we parse in Perl mode
  // a{0,} is a*
  bool result = Regexp::SimplifyRegexp("(?:a*)*", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a*", dst);
}

// Test simplification of a+* -> a*
TEST_F(SimplifyTest_426, SimplifyPlusStar_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("(?:a+)*", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a*", dst);
}

// Test simplification of a?? -> a?
TEST_F(SimplifyTest_426, SimplifyQuestQuest_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("(?:a?)?", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a?", dst);
}

// Test Simplify on a parsed regexp directly
TEST_F(SimplifyTest_426, SimplifyParsedRegexp_426) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_TRUE(sre != nullptr);
  std::string s = sre->ToString();
  EXPECT_FALSE(s.empty());
  sre->Decref();
  re->Decref();
}

// Test simplification of repeat with {0,0}
TEST_F(SimplifyTest_426, SimplifyRepeatZeroZero_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{0}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
}

// Test simplification of repeat with {1,1}
TEST_F(SimplifyTest_426, SimplifyRepeatOneOne_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{1}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a", dst);
}

// Test simplification of non-greedy star
TEST_F(SimplifyTest_426, SimplifyNonGreedyStar_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a*?", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a*?", dst);
}

// Test simplification of non-greedy plus
TEST_F(SimplifyTest_426, SimplifyNonGreedyPlus_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a+?", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a+?", dst);
}

// Test that Simplify on a complex regex succeeds
TEST_F(SimplifyTest_426, SimplifyComplex_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("(a|b)*c+[d-f]{2,4}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_FALSE(dst.empty());
}

// Test coalescing of adjacent literals in concat
TEST_F(SimplifyTest_426, CoalesceAdjacentLiterals_426) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abcdef", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_TRUE(sre != nullptr);
  std::string s = sre->ToString();
  EXPECT_EQ("abcdef", s);
  sre->Decref();
  re->Decref();
}

// Test word boundary simplification
TEST_F(SimplifyTest_426, SimplifyWordBoundary_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("\\b", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
}

// Test simplification preserves semantics on complex alternation
TEST_F(SimplifyTest_426, SimplifyAlternationComplex_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a|b|c|d", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("[a-d]", dst);
}

// Test simplification of repeat {0,}
TEST_F(SimplifyTest_426, SimplifyRepeatZeroUnbounded_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{0,}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a*", dst);
}

// Test simplification of repeat {1,}
TEST_F(SimplifyTest_426, SimplifyRepeatOneUnbounded_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{1,}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a+", dst);
}

// Test that Simplify returns a valid Regexp that can be dumped
TEST_F(SimplifyTest_426, SimplifyDump_426) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a{2}b)+", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* sre = re->Simplify();
  ASSERT_TRUE(sre != nullptr);
  std::string dump = sre->Dump();
  EXPECT_FALSE(dump.empty());
  sre->Decref();
  re->Decref();
}

// Test simplification of character class with single character
TEST_F(SimplifyTest_426, SimplifySingleCharClass_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("[a]", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a", dst);
}

// Test simplification of negated character class
TEST_F(SimplifyTest_426, SimplifyNegatedCharClass_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("[^a]", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_FALSE(dst.empty());
}

// Test simplification with POSIX flags
TEST_F(SimplifyTest_426, SimplifyPOSIX_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a+", Regexp::PerlX, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a+", dst);
}

// Test simplification of repeat with large count
TEST_F(SimplifyTest_426, SimplifyLargeRepeat_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{10}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("aaaaaaaaaa", dst);
}

// Test that Simplify of a single character is identity
TEST_F(SimplifyTest_426, SimplifySingleChar_426) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a", dst);
}

}  // namespace re2
