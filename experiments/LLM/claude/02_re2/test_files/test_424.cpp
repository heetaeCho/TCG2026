#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

// Test fixture for Simplify-related tests
class SimplifyTest_424 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Helper: Parse a regexp, simplify it, and return the string representation
static std::string SimplifyRegexp(const char* pattern) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(pattern,
                                    Regexp::MatchNL | Regexp::PerlX | Regexp::PerlClasses | Regexp::UnicodeGroups,
                                    &dst, &status);
  if (!ok) {
    return "ERROR";
  }
  return dst;
}

// Test that SimplifyRegexp returns the simplified pattern for a basic literal
TEST_F(SimplifyTest_424, SimplifyLiteral_424) {
  std::string result = SimplifyRegexp("abc");
  EXPECT_EQ(result, "abc");
}

// Test simplification of character class
TEST_F(SimplifyTest_424, SimplifyCharClass_424) {
  std::string result = SimplifyRegexp("[a-z]");
  EXPECT_EQ(result, "[a-z]");
}

// Test simplification of a+ (plus)
TEST_F(SimplifyTest_424, SimplifyPlus_424) {
  std::string result = SimplifyRegexp("a+");
  EXPECT_EQ(result, "a+");
}

// Test simplification of a* (star)
TEST_F(SimplifyTest_424, SimplifyStar_424) {
  std::string result = SimplifyRegexp("a*");
  EXPECT_EQ(result, "a*");
}

// Test simplification of a? (quest)
TEST_F(SimplifyTest_424, SimplifyQuest_424) {
  std::string result = SimplifyRegexp("a?");
  EXPECT_EQ(result, "a?");
}

// Test simplification of bounded repeat a{3,5} -> aaa(?:a(?:a)?)?
TEST_F(SimplifyTest_424, SimplifyBoundedRepeat_424) {
  std::string result = SimplifyRegexp("a{3,5}");
  // Bounded repeats get expanded
  EXPECT_NE(result, "ERROR");
  EXPECT_FALSE(result.empty());
}

// Test simplification of exact repeat a{3} -> aaa
TEST_F(SimplifyTest_424, SimplifyExactRepeat_424) {
  std::string result = SimplifyRegexp("a{3}");
  EXPECT_EQ(result, "aaa");
}

// Test simplification of a{0} -> empty
TEST_F(SimplifyTest_424, SimplifyZeroRepeat_424) {
  std::string result = SimplifyRegexp("a{0}");
  EXPECT_NE(result, "ERROR");
}

// Test simplification of a{1} -> a
TEST_F(SimplifyTest_424, SimplifyOneRepeat_424) {
  std::string result = SimplifyRegexp("a{1}");
  EXPECT_EQ(result, "a");
}

// Test simplification of a{0,1} -> a?
TEST_F(SimplifyTest_424, SimplifyZeroOrOneRepeat_424) {
  std::string result = SimplifyRegexp("a{0,1}");
  EXPECT_EQ(result, "a?");
}

// Test simplification of a{1,} -> a+
TEST_F(SimplifyTest_424, SimplifyOneOrMoreRepeat_424) {
  std::string result = SimplifyRegexp("a{1,}");
  EXPECT_EQ(result, "a+");
}

// Test simplification of a{0,} -> a*
TEST_F(SimplifyTest_424, SimplifyZeroOrMoreRepeat_424) {
  std::string result = SimplifyRegexp("a{0,}");
  EXPECT_EQ(result, "a*");
}

// Test simplification of empty string
TEST_F(SimplifyTest_424, SimplifyEmpty_424) {
  std::string result = SimplifyRegexp("");
  EXPECT_NE(result, "ERROR");
}

// Test simplification of dot
TEST_F(SimplifyTest_424, SimplifyDot_424) {
  std::string result = SimplifyRegexp(".");
  EXPECT_NE(result, "ERROR");
}

// Test simplification of alternation
TEST_F(SimplifyTest_424, SimplifyAlternation_424) {
  std::string result = SimplifyRegexp("a|b");
  EXPECT_EQ(result, "[a-b]");
}

// Test simplification of nested groups
TEST_F(SimplifyTest_424, SimplifyNestedGroups_424) {
  std::string result = SimplifyRegexp("(a(b))");
  EXPECT_NE(result, "ERROR");
}

// Test simplification with non-greedy operators
TEST_F(SimplifyTest_424, SimplifyNonGreedyStar_424) {
  std::string result = SimplifyRegexp("a*?");
  EXPECT_EQ(result, "a*?");
}

TEST_F(SimplifyTest_424, SimplifyNonGreedyPlus_424) {
  std::string result = SimplifyRegexp("a+?");
  EXPECT_EQ(result, "a+?");
}

TEST_F(SimplifyTest_424, SimplifyNonGreedyQuest_424) {
  std::string result = SimplifyRegexp("a??");
  EXPECT_EQ(result, "a??");
}

// Test simplification of character class with repeated elements
TEST_F(SimplifyTest_424, SimplifyCharClassCoalesce_424) {
  std::string result = SimplifyRegexp("[aa]");
  EXPECT_NE(result, "ERROR");
}

// Test simplification of complex pattern
TEST_F(SimplifyTest_424, SimplifyComplex_424) {
  std::string result = SimplifyRegexp("(a{2,4}b{1,3})+");
  EXPECT_NE(result, "ERROR");
  EXPECT_FALSE(result.empty());
}

// Test using Regexp::Simplify directly
TEST_F(SimplifyTest_424, RegexpSimplifyDirect_424) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  std::string s = simplified->ToString();
  EXPECT_FALSE(s.empty());
  simplified->Decref();
  re->Decref();
}

// Test that Simplify on already simple regexp returns equivalent
TEST_F(SimplifyTest_424, RegexpSimplifyAlreadySimple_424) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  EXPECT_EQ(simplified->ToString(), "abc");
  simplified->Decref();
  re->Decref();
}

// Test simplification of capture groups
TEST_F(SimplifyTest_424, SimplifyCapture_424) {
  std::string result = SimplifyRegexp("(a)");
  EXPECT_NE(result, "ERROR");
}

// Test simplification of anchors
TEST_F(SimplifyTest_424, SimplifyAnchors_424) {
  std::string result = SimplifyRegexp("^abc$");
  EXPECT_NE(result, "ERROR");
}

// Test repeat with large bounds
TEST_F(SimplifyTest_424, SimplifyLargeRepeat_424) {
  std::string result = SimplifyRegexp("a{2,10}");
  EXPECT_NE(result, "ERROR");
  EXPECT_FALSE(result.empty());
}

// Test Incref/Decref via CoalesceWalker::Copy behavior (indirectly)
TEST_F(SimplifyTest_424, IncrefDecref_424) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->Ref(), 1);
  Regexp* ref = re->Incref();
  EXPECT_EQ(ref, re);
  EXPECT_EQ(re->Ref(), 2);
  re->Decref();
  EXPECT_EQ(ref->Ref(), 1);
  ref->Decref();
}

// Test simplification of concatenation with repeated chars (coalescing)
TEST_F(SimplifyTest_424, CoalesceConcat_424) {
  RegexpStatus status;
  // Parse "aab" - the parser may already coalesce, but simplify should handle it
  Regexp* re = Regexp::Parse("aab", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  std::string s = simplified->ToString();
  EXPECT_EQ(s, "aab");
  simplified->Decref();
  re->Decref();
}

// Test simplification of non-greedy bounded repeat
TEST_F(SimplifyTest_424, SimplifyNonGreedyBoundedRepeat_424) {
  std::string result = SimplifyRegexp("a{2,4}?");
  EXPECT_NE(result, "ERROR");
  EXPECT_FALSE(result.empty());
}

// Test simplification of a{2} -> aa
TEST_F(SimplifyTest_424, SimplifyExactRepeatTwo_424) {
  std::string result = SimplifyRegexp("a{2}");
  EXPECT_EQ(result, "aa");
}

// Test simplification preserves semantics
TEST_F(SimplifyTest_424, SimplifyPreservesSemantics_424) {
  // a{2,3} should match "aa" and "aaa"
  std::string simplified = SimplifyRegexp("a{2,3}");
  EXPECT_NE(simplified, "ERROR");
  // The simplified form should be a valid regex
  RegexpStatus status;
  Regexp* re = Regexp::Parse(simplified, Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test simplification of alternation of character classes
TEST_F(SimplifyTest_424, SimplifyAlternationCharClasses_424) {
  std::string result = SimplifyRegexp("[a-c]|[d-f]");
  EXPECT_NE(result, "ERROR");
}

// Test SimplifyRegexp with bad status returns false
TEST_F(SimplifyTest_424, SimplifyRegexpInvalidPattern_424) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("(abc", Regexp::PerlX, &dst, &status);
  EXPECT_FALSE(ok);
}

// Test simplification of word boundary
TEST_F(SimplifyTest_424, SimplifyWordBoundary_424) {
  std::string result = SimplifyRegexp("\\bfoo\\b");
  EXPECT_NE(result, "ERROR");
}

// Test simplification of digit class
TEST_F(SimplifyTest_424, SimplifyDigitClass_424) {
  std::string result = SimplifyRegexp("\\d+");
  EXPECT_NE(result, "ERROR");
}

// Test that Simplify on single char repeat is correct
TEST_F(SimplifyTest_424, SimplifyCharRepeat_424) {
  std::string result = SimplifyRegexp("a{1,1}");
  EXPECT_EQ(result, "a");
}

}  // namespace re2
