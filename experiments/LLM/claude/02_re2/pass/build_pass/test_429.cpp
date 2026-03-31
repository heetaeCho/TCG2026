#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

class SimplifyTest_429 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that SimplifyRegexp works on a simple literal string
TEST_F(SimplifyTest_429, SimplifyLiteral_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("abc", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("abc", dst);
}

// Test that SimplifyRegexp works on an empty pattern
TEST_F(SimplifyTest_429, SimplifyEmpty_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
}

// Test that Simplify on a parsed regexp returns a non-null result
TEST_F(SimplifyTest_429, SimplifyParsedRegexp_429) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test simplification of character class [a-z]
TEST_F(SimplifyTest_429, SimplifyCharClass_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("[a-z]", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("[a-z]", dst);
}

// Test simplification of a{0,1} which should become a?
TEST_F(SimplifyTest_429, SimplifyRepeatZeroOne_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{0,1}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a?", dst);
}

// Test simplification of a{1,} which should become a+
TEST_F(SimplifyTest_429, SimplifyRepeatOnePlus_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{1,}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a+", dst);
}

// Test simplification of a{0,} which should become a*
TEST_F(SimplifyTest_429, SimplifyRepeatZeroPlus_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{0,}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a*", dst);
}

// Test simplification of a{1,1} which should become a
TEST_F(SimplifyTest_429, SimplifyRepeatExactlyOne_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{1,1}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a", dst);
}

// Test simplification of a{2,3}
TEST_F(SimplifyTest_429, SimplifyRepeatTwoThree_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{2,3}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("aaa?", dst);
}

// Test simplification preserves alternation
TEST_F(SimplifyTest_429, SimplifyAlternation_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a|b", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("[ab]", dst);
}

// Test simplification of dot
TEST_F(SimplifyTest_429, SimplifyDot_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp(".", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
}

// Test simplification of a{0,0} which should become empty match
TEST_F(SimplifyTest_429, SimplifyRepeatZeroZero_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{0,0}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
}

// Test simplification of nested repetitions like (a+)+
TEST_F(SimplifyTest_429, SimplifyNestedRepeat_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("(a+)+", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
}

// Test simplification of non-greedy quantifiers
TEST_F(SimplifyTest_429, SimplifyNonGreedy_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a+?", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a+?", dst);
}

// Test that Simplify is idempotent
TEST_F(SimplifyTest_429, SimplifyIdempotent_429) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Regexp* simplified1 = re->Simplify();
  ASSERT_NE(simplified1, nullptr);
  std::string s1 = simplified1->ToString();
  
  Regexp* simplified2 = simplified1->Simplify();
  ASSERT_NE(simplified2, nullptr);
  std::string s2 = simplified2->ToString();
  
  EXPECT_EQ(s1, s2);
  
  simplified2->Decref();
  simplified1->Decref();
  re->Decref();
}

// Test simplification with capture groups
TEST_F(SimplifyTest_429, SimplifyWithCapture_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("(a)(b)", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
}

// Test simplification of complex pattern
TEST_F(SimplifyTest_429, SimplifyComplexPattern_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("(a{2,3}|b{1,2})+", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
}

// Test that simple() returns true after Simplify()
TEST_F(SimplifyTest_429, SimpleAfterSimplify_429) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  EXPECT_TRUE(simplified->simple());
  
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp with POSIX flags
TEST_F(SimplifyTest_429, SimplifyPOSIX_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{2,4}", Regexp::PerlX, &dst, &status);
  EXPECT_TRUE(result);
}

// Test simplification of a{3,3} which should become aaa
TEST_F(SimplifyTest_429, SimplifyRepeatExactlyThree_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{3,3}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("aaa", dst);
}

// Test simplification of star
TEST_F(SimplifyTest_429, SimplifyStar_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a*", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a*", dst);
}

// Test simplification of plus
TEST_F(SimplifyTest_429, SimplifyPlus_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a+", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a+", dst);
}

// Test simplification of question mark
TEST_F(SimplifyTest_429, SimplifyQuest_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a?", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a?", dst);
}

// Test simplification of concatenation
TEST_F(SimplifyTest_429, SimplifyConcat_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("abcdef", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("abcdef", dst);
}

// Test simplification of character class with single char
TEST_F(SimplifyTest_429, SimplifyCharClassSingleChar_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("[a]", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("a", dst);
}

// Test simplification with negated character class
TEST_F(SimplifyTest_429, SimplifyNegatedCharClass_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("[^a]", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
}

// Test simplification of a{5,10}
TEST_F(SimplifyTest_429, SimplifyRepeatFiveToTen_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{5,10}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("aaaaaa?a?a?a?a?", dst);
}

// Test Simplify returns valid regexp that can be converted to string
TEST_F(SimplifyTest_429, SimplifyToString_429) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b){2,4}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  
  std::string str = simplified->ToString();
  EXPECT_FALSE(str.empty());
  
  simplified->Decref();
  re->Decref();
}

// Test simplification of non-greedy repeat
TEST_F(SimplifyTest_429, SimplifyNonGreedyRepeat_429) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a{2,3}?", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ("aaa??", dst);
}

}  // namespace re2
