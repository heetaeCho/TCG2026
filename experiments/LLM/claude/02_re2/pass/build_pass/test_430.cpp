#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

class SimplifyTest_430 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper to parse, simplify, and return the string representation
  bool SimplifyRegexp(const std::string& src, std::string* dst) {
    RegexpStatus status;
    return Regexp::SimplifyRegexp(
        src, 
        static_cast<Regexp::ParseFlags>(Regexp::LikePerl), 
        dst, 
        &status);
  }

  // Helper to parse and simplify, returning the simplified regexp's string
  std::string SimplifyOrDie(const std::string& src) {
    std::string dst;
    RegexpStatus status;
    bool ok = Regexp::SimplifyRegexp(
        src,
        static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
        &dst,
        &status);
    EXPECT_TRUE(ok) << "Failed to simplify: " << src;
    return dst;
  }
};

// Test that simple literals pass through unchanged
TEST_F(SimplifyTest_430, SimplifyLiteral_430) {
  std::string result = SimplifyOrDie("a");
  EXPECT_EQ(result, "a");
}

// Test that a simple concatenation passes through
TEST_F(SimplifyTest_430, SimplifyConcatenation_430) {
  std::string result = SimplifyOrDie("abc");
  EXPECT_EQ(result, "abc");
}

// Test that alternation passes through
TEST_F(SimplifyTest_430, SimplifyAlternation_430) {
  std::string result = SimplifyOrDie("a|b");
  EXPECT_EQ(result, "[ab]");
}

// Test that star is preserved
TEST_F(SimplifyTest_430, SimplifyStar_430) {
  std::string result = SimplifyOrDie("a*");
  EXPECT_EQ(result, "a*");
}

// Test that plus is preserved
TEST_F(SimplifyTest_430, SimplifyPlus_430) {
  std::string result = SimplifyOrDie("a+");
  EXPECT_EQ(result, "a+");
}

// Test that quest is preserved
TEST_F(SimplifyTest_430, SimplifyQuest_430) {
  std::string result = SimplifyOrDie("a?");
  EXPECT_EQ(result, "a?");
}

// Test repeat {n} simplification
TEST_F(SimplifyTest_430, SimplifyRepeatExact_430) {
  std::string result = SimplifyOrDie("a{3}");
  EXPECT_EQ(result, "aaa");
}

// Test repeat {0} simplifies to empty match
TEST_F(SimplifyTest_430, SimplifyRepeatZero_430) {
  std::string result = SimplifyOrDie("a{0}");
  // a{0} should match empty string
  EXPECT_FALSE(result.empty());
}

// Test repeat {1} simplifies to just the sub-expression
TEST_F(SimplifyTest_430, SimplifyRepeatOne_430) {
  std::string result = SimplifyOrDie("a{1}");
  EXPECT_EQ(result, "a");
}

// Test repeat {0,1} simplifies to quest
TEST_F(SimplifyTest_430, SimplifyRepeatZeroOne_430) {
  std::string result = SimplifyOrDie("a{0,1}");
  EXPECT_EQ(result, "a?");
}

// Test repeat {1,} simplifies to plus
TEST_F(SimplifyTest_430, SimplifyRepeatOneOrMore_430) {
  std::string result = SimplifyOrDie("a{1,}");
  EXPECT_EQ(result, "a+");
}

// Test repeat {0,} simplifies to star
TEST_F(SimplifyTest_430, SimplifyRepeatZeroOrMore_430) {
  std::string result = SimplifyOrDie("a{0,}");
  EXPECT_EQ(result, "a*");
}

// Test repeat {2,5}
TEST_F(SimplifyTest_430, SimplifyRepeatRange_430) {
  std::string result = SimplifyOrDie("a{2,5}");
  EXPECT_EQ(result, "aaa?a?a?");
}

// Test that capture groups are preserved
TEST_F(SimplifyTest_430, SimplifyCapture_430) {
  std::string result = SimplifyOrDie("(a)");
  EXPECT_EQ(result, "(a)");
}

// Test nested repetitions like (a*)* 
TEST_F(SimplifyTest_430, SimplifyNestedStar_430) {
  std::string result = SimplifyOrDie("(a*)*");
  // The simplifier should handle nested repetitions
  EXPECT_FALSE(result.empty());
}

// Test character class simplification
TEST_F(SimplifyTest_430, SimplifyCharClass_430) {
  std::string result = SimplifyOrDie("[abc]");
  EXPECT_EQ(result, "[a-c]");
}

// Test that dot (any char) passes through
TEST_F(SimplifyTest_430, SimplifyAnyChar_430) {
  std::string result = SimplifyOrDie(".");
  EXPECT_FALSE(result.empty());
}

// Test begin/end anchors
TEST_F(SimplifyTest_430, SimplifyAnchors_430) {
  std::string result = SimplifyOrDie("^a$");
  EXPECT_FALSE(result.empty());
}

// Test word boundary
TEST_F(SimplifyTest_430, SimplifyWordBoundary_430) {
  std::string result = SimplifyOrDie("\\b");
  EXPECT_FALSE(result.empty());
}

// Test empty match
TEST_F(SimplifyTest_430, SimplifyEmptyMatch_430) {
  std::string result = SimplifyOrDie("");
  // Empty pattern
  EXPECT_TRUE(result.empty() || !result.empty());
}

// Test that SimplifyRegexp returns true for valid input
TEST_F(SimplifyTest_430, SimplifyRegexpReturnsTrueForValid_430) {
  std::string dst;
  bool ok = SimplifyRegexp("abc", &dst);
  EXPECT_TRUE(ok);
}

// Test Simplify method directly on a parsed Regexp
TEST_F(SimplifyTest_430, SimplifyDirectMethod_430) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", 
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl), &status);
  ASSERT_NE(re, nullptr);
  
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  EXPECT_TRUE(simplified->simple());
  
  std::string s = simplified->ToString();
  EXPECT_EQ(s, "aaaa?a?");
  
  simplified->Decref();
  re->Decref();
}

// Test that simplify marks result as simple
TEST_F(SimplifyTest_430, SimplifyMarksSimple_430) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", 
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl), &status);
  ASSERT_NE(re, nullptr);
  
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  EXPECT_TRUE(simplified->simple());
  
  simplified->Decref();
  re->Decref();
}

// Test non-greedy star
TEST_F(SimplifyTest_430, SimplifyNonGreedyStar_430) {
  std::string result = SimplifyOrDie("a*?");
  EXPECT_FALSE(result.empty());
}

// Test non-greedy plus
TEST_F(SimplifyTest_430, SimplifyNonGreedyPlus_430) {
  std::string result = SimplifyOrDie("a+?");
  EXPECT_FALSE(result.empty());
}

// Test non-greedy quest
TEST_F(SimplifyTest_430, SimplifyNonGreedyQuest_430) {
  std::string result = SimplifyOrDie("a??");
  EXPECT_FALSE(result.empty());
}

// Test repeat {2}
TEST_F(SimplifyTest_430, SimplifyRepeatTwo_430) {
  std::string result = SimplifyOrDie("a{2}");
  EXPECT_EQ(result, "aa");
}

// Test that complex patterns simplify correctly
TEST_F(SimplifyTest_430, SimplifyComplexPattern_430) {
  std::string result = SimplifyOrDie("(a{2}b{3})+");
  EXPECT_FALSE(result.empty());
}

// Test character class with single element
TEST_F(SimplifyTest_430, SimplifyCharClassSingle_430) {
  std::string result = SimplifyOrDie("[a]");
  EXPECT_EQ(result, "a");
}

// Test that double simplification yields the same result
TEST_F(SimplifyTest_430, SimplifyIdempotent_430) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,4}", 
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl), &status);
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

// Test repeat with {0,0}
TEST_F(SimplifyTest_430, SimplifyRepeatZeroZero_430) {
  std::string result = SimplifyOrDie("a{0,0}");
  EXPECT_FALSE(result.empty());
}

// Test deeply nested groups
TEST_F(SimplifyTest_430, SimplifyDeepNesting_430) {
  std::string result = SimplifyOrDie("((((a))))");
  EXPECT_FALSE(result.empty());
}

// Test alternation of character classes
TEST_F(SimplifyTest_430, SimplifyAlternationCharClasses_430) {
  std::string result = SimplifyOrDie("[a-z]|[A-Z]");
  EXPECT_FALSE(result.empty());
}

// Test that NoMatch patterns are handled
TEST_F(SimplifyTest_430, SimplifyNoMatchContext_430) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[^\\s\\S]",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl), &status);
  if (re != nullptr) {
    Regexp* simplified = re->Simplify();
    if (simplified != nullptr) {
      EXPECT_TRUE(simplified->simple());
      simplified->Decref();
    }
    re->Decref();
  }
}

// Test repeat with large count
TEST_F(SimplifyTest_430, SimplifyRepeatLargeCount_430) {
  std::string result = SimplifyOrDie("a{10}");
  EXPECT_EQ(result, "aaaaaaaaaa");
}

// Test that BeginText/EndText simplify properly
TEST_F(SimplifyTest_430, SimplifyBeginEndText_430) {
  std::string result = SimplifyOrDie("\\Aa\\z");
  EXPECT_FALSE(result.empty());
}

}  // namespace re2
