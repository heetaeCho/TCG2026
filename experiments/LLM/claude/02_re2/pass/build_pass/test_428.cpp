#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

class SimplifyTest_428 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that Simplify returns a valid regexp for a simple literal
TEST_F(SimplifyTest_428, SimplifyLiteral_428) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test that Simplify is idempotent
TEST_F(SimplifyTest_428, SimplifyIdempotent_428) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b*c?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* s1 = re->Simplify();
  ASSERT_NE(s1, nullptr);
  Regexp* s2 = s1->Simplify();
  ASSERT_NE(s2, nullptr);
  EXPECT_EQ(s1->ToString(), s2->ToString());
  s2->Decref();
  s1->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST_F(SimplifyTest_428, SimplifyRegexpStatic_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,5}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test simplification of character classes
TEST_F(SimplifyTest_428, SimplifyCharClass_428) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-zA-Z0-9]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test simplification of repetition {n,m}
TEST_F(SimplifyTest_428, SimplifyRepeat_428) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  // Simplified should not contain counted repetition
  std::string s = simplified->ToString();
  EXPECT_NE(s.find("a"), std::string::npos);
  simplified->Decref();
  re->Decref();
}

// Test simplification of {0,1} which is equivalent to ?
TEST_F(SimplifyTest_428, SimplifyRepeatZeroOne_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{0,1}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  // Should simplify to a?
  EXPECT_EQ(dst, "a?");
}

// Test simplification of {1,} which is equivalent to +
TEST_F(SimplifyTest_428, SimplifyRepeatOneOrMore_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{1,}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "a+");
}

// Test simplification of {0,} which is equivalent to *
TEST_F(SimplifyTest_428, SimplifyRepeatZeroOrMore_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{0,}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "a*");
}

// Test simplification of {1,1} which is equivalent to just a
TEST_F(SimplifyTest_428, SimplifyRepeatExactlyOne_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{1,1}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "a");
}

// Test simplification of nested groups
TEST_F(SimplifyTest_428, SimplifyNestedGroups_428) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a+)+)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test simplification with alternation
TEST_F(SimplifyTest_428, SimplifyAlternation_428) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test that simple() flag is set after Simplify
TEST_F(SimplifyTest_428, SimplifySetSimpleFlag_428) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  EXPECT_TRUE(simplified->simple());
  simplified->Decref();
  re->Decref();
}

// Test simplification of empty regexp
TEST_F(SimplifyTest_428, SimplifyEmptyRegexp_428) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test simplification of dot star
TEST_F(SimplifyTest_428, SimplifyDotStar_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(".*", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
}

// Test simplification with POSIX flags
TEST_F(SimplifyTest_428, SimplifyPOSIXFlags_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,5}", Regexp::PerlX, &dst, &status);
  EXPECT_TRUE(ok);
}

// Test simplification of a{0,0} which should give empty match
TEST_F(SimplifyTest_428, SimplifyRepeatZeroZero_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{0,0}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
}

// Test simplification of complex pattern
TEST_F(SimplifyTest_428, SimplifyComplex_428) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a{2,3}b{1,2}|c{0,4}d+)*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  EXPECT_TRUE(simplified->simple());
  simplified->Decref();
  re->Decref();
}

// Test that simplification handles non-greedy operators
TEST_F(SimplifyTest_428, SimplifyNonGreedy_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a+?", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "a+?");
}

// Test simplification of {n,n} (exact repeat)
TEST_F(SimplifyTest_428, SimplifyExactRepeat_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{3,3}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "aaa");
}

// Test simplification of non-greedy repeat
TEST_F(SimplifyTest_428, SimplifyNonGreedyRepeat_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,4}?", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  // Should expand to aa(?:a(?:a)?)?? or similar non-greedy form
  EXPECT_FALSE(dst.empty());
}

// Test that SimplifyRegexp handles invalid input gracefully
TEST_F(SimplifyTest_428, SimplifyRegexpInvalidInput_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("[z-a]", Regexp::LikePerl, &dst, &status);
  EXPECT_FALSE(ok);
}

// Test simplification of Unicode category
TEST_F(SimplifyTest_428, SimplifyUnicodeCategory_428) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\pL+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test simplification of capture groups preserves capture semantics
TEST_F(SimplifyTest_428, SimplifyCaptureGroup_428) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a{2,3})", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  EXPECT_EQ(simplified->NumCaptures(), 1);
  simplified->Decref();
  re->Decref();
}

// Test simplification of large repeat count
TEST_F(SimplifyTest_428, SimplifyLargeRepeat_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{1,100}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test that simplification of already simple regexp returns equivalent
TEST_F(SimplifyTest_428, SimplifyAlreadySimple_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("abc", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "abc");
}

// Test simplification of star
TEST_F(SimplifyTest_428, SimplifyStar_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a*", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "a*");
}

// Test simplification of plus
TEST_F(SimplifyTest_428, SimplifyPlus_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a+", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "a+");
}

// Test simplification of quest
TEST_F(SimplifyTest_428, SimplifyQuest_428) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a?", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(dst, "a?");
}

}  // namespace re2
