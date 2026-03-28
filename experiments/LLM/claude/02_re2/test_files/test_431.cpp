#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

// Test fixture for Simplify tests
class SimplifyTest_431 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper to parse, simplify, and return the string representation
  std::string SimplifyRegexp(const std::string& pattern) {
    std::string result;
    RegexpStatus status;
    bool ok = Regexp::SimplifyRegexp(
        pattern,
        static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
        &result, &status);
    if (!ok) return "";
    return result;
  }

  // Helper to parse a regexp and check if Simplify produces expected output
  void TestSimplify(const std::string& input, const std::string& expected) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(input, static_cast<Regexp::ParseFlags>(Regexp::LikePerl), &status);
    ASSERT_TRUE(re != nullptr) << "Failed to parse: " << input;
    Regexp* simplified = re->Simplify();
    ASSERT_TRUE(simplified != nullptr) << "Simplify returned null for: " << input;
    std::string result = simplified->ToString();
    EXPECT_EQ(expected, result) << "Input: " << input;
    simplified->Decref();
    re->Decref();
  }
};

// Test that SimplifyRegexp works for a simple literal
TEST_F(SimplifyTest_431, SimpleLiteral_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "abc",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ("abc", result);
}

// Test that SimplifyRegexp handles empty pattern
TEST_F(SimplifyTest_431, EmptyPattern_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
}

// Test simplification of character class
TEST_F(SimplifyTest_431, CharacterClass_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "[a-z]",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ("[a-z]", result);
}

// Test simplification of star quantifier
TEST_F(SimplifyTest_431, StarQuantifier_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "a*",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ("a*", result);
}

// Test simplification of plus quantifier
TEST_F(SimplifyTest_431, PlusQuantifier_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "a+",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ("a+", result);
}

// Test simplification of quest quantifier
TEST_F(SimplifyTest_431, QuestQuantifier_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "a?",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ("a?", result);
}

// Test simplification of repeat {n,m}
TEST_F(SimplifyTest_431, RepeatNM_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "a{2,4}",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  // a{2,4} simplifies to aaa?a? 
  EXPECT_FALSE(result.empty());
}

// Test simplification of repeat {n}
TEST_F(SimplifyTest_431, RepeatExact_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "a{3}",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

// Test simplification of repeat {0,1} is same as ?
TEST_F(SimplifyTest_431, RepeatZeroOne_431) {
  std::string r1 = SimplifyRegexp("a{0,1}");
  std::string r2 = SimplifyRegexp("a?");
  EXPECT_EQ(r1, r2);
}

// Test simplification of repeat {0,} is same as *
TEST_F(SimplifyTest_431, RepeatZeroMore_431) {
  std::string r1 = SimplifyRegexp("a{0,}");
  std::string r2 = SimplifyRegexp("a*");
  EXPECT_EQ(r1, r2);
}

// Test simplification of repeat {1,} is same as +
TEST_F(SimplifyTest_431, RepeatOneMore_431) {
  std::string r1 = SimplifyRegexp("a{1,}");
  std::string r2 = SimplifyRegexp("a+");
  EXPECT_EQ(r1, r2);
}

// Test simplification of alternation
TEST_F(SimplifyTest_431, Alternation_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "a|b",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ("[a-b]", result);
}

// Test simplification of concatenation
TEST_F(SimplifyTest_431, Concatenation_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "ab",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ("ab", result);
}

// Test simplification of dot
TEST_F(SimplifyTest_431, Dot_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      ".",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

// Test simplification of anchors - begin line
TEST_F(SimplifyTest_431, BeginLine_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "^a",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

// Test simplification of anchors - end line
TEST_F(SimplifyTest_431, EndLine_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "a$",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

// Test simplification of word boundary
TEST_F(SimplifyTest_431, WordBoundary_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "\\b",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

// Test simplification of no word boundary
TEST_F(SimplifyTest_431, NoWordBoundary_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "\\B",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

// Test simplification of begin text
TEST_F(SimplifyTest_431, BeginText_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "\\A",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

// Test simplification of end text
TEST_F(SimplifyTest_431, EndText_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "\\z",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

// Test simplification of capture group
TEST_F(SimplifyTest_431, CaptureGroup_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "(abc)",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

// Test simplification of nested quantifiers
TEST_F(SimplifyTest_431, NestedQuantifiers_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "(a+)*",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

// Test Simplify on a parsed Regexp object directly
TEST_F(SimplifyTest_431, SimplifyDirectCall_431) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl), &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  // After simplification, the regexp should be marked simple
  EXPECT_TRUE(simplified->simple());
  simplified->Decref();
  re->Decref();
}

// Test that calling Simplify twice gives same result
TEST_F(SimplifyTest_431, SimplifyIdempotent_431) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,7}",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl), &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* s1 = re->Simplify();
  ASSERT_TRUE(s1 != nullptr);
  std::string str1 = s1->ToString();
  Regexp* s2 = s1->Simplify();
  ASSERT_TRUE(s2 != nullptr);
  std::string str2 = s2->ToString();
  EXPECT_EQ(str1, str2);
  s2->Decref();
  s1->Decref();
  re->Decref();
}

// Test simplification of non-greedy quantifiers
TEST_F(SimplifyTest_431, NonGreedyStar_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "a*?",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

TEST_F(SimplifyTest_431, NonGreedyPlus_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "a+?",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

TEST_F(SimplifyTest_431, NonGreedyQuest_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "a??",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

// Test simplification of complex pattern
TEST_F(SimplifyTest_431, ComplexPattern_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "^(foo|bar){2,3}\\b[a-z]+$",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

// Test simplification of repeat {0}
TEST_F(SimplifyTest_431, RepeatZero_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "a{0}",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
}

// Test simplification of repeat {1}
TEST_F(SimplifyTest_431, RepeatOne_431) {
  std::string r1 = SimplifyRegexp("a{1}");
  std::string r2 = SimplifyRegexp("a");
  EXPECT_EQ(r1, r2);
}

// Test simplification with POSIX flags
TEST_F(SimplifyTest_431, PosixFlags_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "a{2,4}",
      static_cast<Regexp::ParseFlags>(Regexp::PerlX),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

// Test that empty ops (anchors, boundaries) simplify correctly
// These are related to IsEmptyOp in simplify.cc
TEST_F(SimplifyTest_431, EmptyOpStar_431) {
  // ^* should simplify since ^ is an "empty" op
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "(?:^)*",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
}

TEST_F(SimplifyTest_431, EmptyOpPlus_431) {
  // ^+ should simplify since ^ is an "empty" op
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "(?:^)+",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
}

TEST_F(SimplifyTest_431, EmptyOpQuest_431) {
  // ^? should simplify since ^ is an "empty" op
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "(?:^)?",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
}

// Test simplification with character class negation
TEST_F(SimplifyTest_431, NegatedCharClass_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "[^a-z]",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

// Test simplification of \\d
TEST_F(SimplifyTest_431, DigitClass_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "\\d+",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

// Test simplification of a large repeat
TEST_F(SimplifyTest_431, LargeRepeat_431) {
  std::string result;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(
      "a{1,10}",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl),
      &result, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(result.empty());
}

// Test that simplified regexp's simple() flag is true
TEST_F(SimplifyTest_431, SimpleFlag_431) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,3}",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl), &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  EXPECT_TRUE(simplified->simple());
  simplified->Decref();
  re->Decref();
}

// Test already-simple regexp
TEST_F(SimplifyTest_431, AlreadySimple_431) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl), &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  EXPECT_EQ("abc", simplified->ToString());
  simplified->Decref();
  re->Decref();
}

}  // namespace re2
