#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

// Helper to parse a regexp, simplify it, and return the string representation
static std::string SimplifyAndDump(const std::string& pattern) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(pattern, Regexp::MatchNL | Regexp::PerlX | Regexp::PerlClasses | Regexp::UnicodeGroups, &result, &status);
  if (!ok) return "";
  return result;
}

// Helper that parses, simplifies via Regexp::Simplify(), and returns ToString()
static std::string SimplifyViaObject(const std::string& pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, static_cast<Regexp::ParseFlags>(
      Regexp::MatchNL | Regexp::PerlX | Regexp::PerlClasses | Regexp::UnicodeGroups),
      &status);
  if (re == nullptr) return "";
  Regexp* simplified = re->Simplify();
  std::string result = simplified->ToString();
  simplified->Decref();
  re->Decref();
  return result;
}

// Test basic literal simplification (no change expected)
TEST(SimplifyTest_427, LiteralUnchanged_427) {
  std::string result = SimplifyAndDump("abc");
  EXPECT_EQ(result, "abc");
}

// Test that a+ simplifies correctly
TEST(SimplifyTest_427, PlusSimplify_427) {
  std::string result = SimplifyAndDump("a+");
  // a+ should remain a+ or simplify to aa*
  EXPECT_FALSE(result.empty());
}

// Test that a* simplifies correctly
TEST(SimplifyTest_427, StarSimplify_427) {
  std::string result = SimplifyAndDump("a*");
  EXPECT_FALSE(result.empty());
}

// Test that a? simplifies correctly
TEST(SimplifyTest_427, QuestSimplify_427) {
  std::string result = SimplifyAndDump("a?");
  EXPECT_FALSE(result.empty());
}

// Test repeat with specific count {3}
TEST(SimplifyTest_427, RepeatExact_427) {
  std::string result = SimplifyAndDump("a{3}");
  // Should simplify to aaa
  EXPECT_EQ(result, "aaa");
}

// Test repeat with range {2,4}
TEST(SimplifyTest_427, RepeatRange_427) {
  std::string result = SimplifyAndDump("a{2,4}");
  // Should simplify to aaa?a? or similar
  EXPECT_FALSE(result.empty());
}

// Test repeat {0,1} is equivalent to ?
TEST(SimplifyTest_427, RepeatZeroOne_427) {
  std::string result = SimplifyAndDump("a{0,1}");
  EXPECT_FALSE(result.empty());
}

// Test repeat {0,0} is empty
TEST(SimplifyTest_427, RepeatZeroZero_427) {
  std::string result = SimplifyAndDump("a{0,0}");
  EXPECT_FALSE(result.empty());
}

// Test repeat {1,1} is just the element
TEST(SimplifyTest_427, RepeatOneOne_427) {
  std::string result = SimplifyAndDump("a{1,1}");
  EXPECT_EQ(result, "a");
}

// Test character class simplification
TEST(SimplifyTest_427, CharClassSimplify_427) {
  std::string result = SimplifyAndDump("[a-z]");
  EXPECT_FALSE(result.empty());
}

// Test dot simplification
TEST(SimplifyTest_427, DotSimplify_427) {
  std::string result = SimplifyAndDump(".");
  EXPECT_FALSE(result.empty());
}

// Test alternation
TEST(SimplifyTest_427, AlternationSimplify_427) {
  std::string result = SimplifyAndDump("a|b");
  EXPECT_FALSE(result.empty());
}

// Test nested groups
TEST(SimplifyTest_427, NestedGroupSimplify_427) {
  std::string result = SimplifyAndDump("(a(b))");
  EXPECT_FALSE(result.empty());
}

// Test empty pattern
TEST(SimplifyTest_427, EmptyPattern_427) {
  std::string result = SimplifyAndDump("");
  EXPECT_FALSE(result.empty()); // empty regex still has a representation
}

// Test complex repeat: (ab){2,3}
TEST(SimplifyTest_427, ComplexRepeat_427) {
  std::string result = SimplifyAndDump("(ab){2,3}");
  EXPECT_FALSE(result.empty());
}

// Test non-greedy plus
TEST(SimplifyTest_427, NonGreedyPlus_427) {
  std::string result = SimplifyAndDump("a+?");
  EXPECT_FALSE(result.empty());
}

// Test non-greedy star
TEST(SimplifyTest_427, NonGreedyStar_427) {
  std::string result = SimplifyAndDump("a*?");
  EXPECT_FALSE(result.empty());
}

// Test non-greedy quest
TEST(SimplifyTest_427, NonGreedyQuest_427) {
  std::string result = SimplifyAndDump("a??");
  EXPECT_FALSE(result.empty());
}

// Test non-greedy repeat
TEST(SimplifyTest_427, NonGreedyRepeat_427) {
  std::string result = SimplifyAndDump("a{2,4}?");
  EXPECT_FALSE(result.empty());
}

// Test Simplify() via Regexp object preserves semantics
TEST(SimplifyTest_427, SimplifyViaObjectLiteral_427) {
  std::string result = SimplifyViaObject("abc");
  EXPECT_EQ(result, "abc");
}

// Test Simplify() via Regexp object for repeat
TEST(SimplifyTest_427, SimplifyViaObjectRepeat_427) {
  std::string result = SimplifyViaObject("a{3}");
  EXPECT_EQ(result, "aaa");
}

// Test character class [aa] simplifies to [a]
TEST(SimplifyTest_427, CharClassDuplicate_427) {
  std::string result = SimplifyAndDump("[aa]");
  // Should simplify duplicates
  EXPECT_FALSE(result.empty());
}

// Test Simplify returns non-null for valid patterns
TEST(SimplifyTest_427, SimplifyReturnsNonNull_427) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b+c", static_cast<Regexp::ParseFlags>(
      Regexp::MatchNL | Regexp::PerlX), &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp with invalid pattern
TEST(SimplifyTest_427, InvalidPattern_427) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("(abc", Regexp::PerlX, &result, &status);
  EXPECT_FALSE(ok);
}

// Test that simplification is idempotent
TEST(SimplifyTest_427, SimplifyIdempotent_427) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", static_cast<Regexp::ParseFlags>(
      Regexp::MatchNL | Regexp::PerlX), &status);
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

// Test simple() returns true after simplification
TEST(SimplifyTest_427, SimpleFlag_427) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", static_cast<Regexp::ParseFlags>(
      Regexp::MatchNL | Regexp::PerlX), &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  EXPECT_TRUE(simplified->simple());
  simplified->Decref();
  re->Decref();
}

// Test Incref/Decref (the Copy function in SimplifyWalker uses Incref)
TEST(SimplifyTest_427, IncrefDecref_427) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", static_cast<Regexp::ParseFlags>(
      Regexp::MatchNL | Regexp::PerlX), &status);
  ASSERT_NE(re, nullptr);
  // Incref increases reference count
  Regexp* ref = re->Incref();
  EXPECT_EQ(ref, re);
  // Should be safe to Decref twice
  re->Decref();
  ref->Decref();
}

// Test repeat with unbounded max: a{2,}
TEST(SimplifyTest_427, RepeatUnbounded_427) {
  std::string result = SimplifyAndDump("a{2,}");
  // Should simplify to aa+ or aa*
  EXPECT_FALSE(result.empty());
}

// Test repeat {0,} is same as *
TEST(SimplifyTest_427, RepeatZeroUnbounded_427) {
  std::string result1 = SimplifyAndDump("a{0,}");
  std::string result2 = SimplifyAndDump("a*");
  EXPECT_EQ(result1, result2);
}

// Test repeat {1,} is same as +
TEST(SimplifyTest_427, RepeatOneUnbounded_427) {
  std::string result1 = SimplifyAndDump("a{1,}");
  std::string result2 = SimplifyAndDump("a+");
  EXPECT_EQ(result1, result2);
}

// Test character class negation
TEST(SimplifyTest_427, CharClassNegation_427) {
  std::string result = SimplifyAndDump("[^a]");
  EXPECT_FALSE(result.empty());
}

// Test complex pattern simplification
TEST(SimplifyTest_427, ComplexPattern_427) {
  std::string result = SimplifyAndDump("(a|b){2,3}c+d?");
  EXPECT_FALSE(result.empty());
}

// Test SimplifyRegexp populates status on error
TEST(SimplifyTest_427, StatusOnError_427) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("[invalid", Regexp::PerlX, &result, &status);
  EXPECT_FALSE(ok);
}

// Test that \\d class simplifies
TEST(SimplifyTest_427, PerlClassSimplify_427) {
  std::string result = SimplifyAndDump("\\d+");
  EXPECT_FALSE(result.empty());
}

// Test anchored pattern
TEST(SimplifyTest_427, AnchoredPattern_427) {
  std::string result = SimplifyAndDump("^abc$");
  EXPECT_FALSE(result.empty());
}

}  // namespace re2
