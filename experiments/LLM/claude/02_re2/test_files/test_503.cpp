#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

// We test DoVerticalBar indirectly through the public Parse interface,
// since ParseState is a private nested class and DoVerticalBar is called
// during parsing of alternation patterns (the '|' operator).

class DoVerticalBarTest_503 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic alternation with two literals
TEST_F(DoVerticalBarTest_503, BasicAlternation_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(kRegexpAlternate, re->op());
  std::string s = re->Dump();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test alternation with multiple alternatives
TEST_F(DoVerticalBarTest_503, MultipleAlternation_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test alternation with dot (kRegexpAnyChar) on left side
TEST_F(DoVerticalBarTest_503, DotAlternationLeft_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".|a", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  // When one side is AnyChar (dot), the other literal/charclass can be absorbed
  std::string s = re->Dump();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test alternation with dot (kRegexpAnyChar) on right side
TEST_F(DoVerticalBarTest_503, DotAlternationRight_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|.", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test alternation of dot with dot
TEST_F(DoVerticalBarTest_503, DotAlternateDot_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".|.", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  // dot|dot should simplify to just dot
  std::string s = re->Dump();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test alternation with character class and dot
TEST_F(DoVerticalBarTest_503, CharClassAlternateDot_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]|.", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test dot alternate with character class
TEST_F(DoVerticalBarTest_503, DotAlternateCharClass_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".|[abc]", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test alternation with empty match
TEST_F(DoVerticalBarTest_503, EmptyAlternation_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("|a", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test alternation with concatenation on one side
TEST_F(DoVerticalBarTest_503, ConcatAlternation_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab|cd", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(kRegexpAlternate, re->op());
  re->Decref();
}

// Test alternation inside parentheses
TEST_F(DoVerticalBarTest_503, AlternationInParens_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(kRegexpCapture, re->op());
  re->Decref();
}

// Test nested alternation in groups
TEST_F(DoVerticalBarTest_503, NestedAlternation_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)|(c|d)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(kRegexpAlternate, re->op());
  re->Decref();
}

// Test single element (no vertical bar) - DoVerticalBar shouldn't be invoked
TEST_F(DoVerticalBarTest_503, NoAlternation_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_NE(kRegexpAlternate, re->op());
  re->Decref();
}

// Test multiple dots with alternation
TEST_F(DoVerticalBarTest_503, MultipleDotsAlternation_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".|.|.", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test alternation with quantifiers
TEST_F(DoVerticalBarTest_503, AlternationWithQuantifiers_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*|b+", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(kRegexpAlternate, re->op());
  re->Decref();
}

// Test alternation with dot and complex expression
TEST_F(DoVerticalBarTest_503, DotAlternateComplex_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".|abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test alternation with literal characters on both sides and dot
TEST_F(DoVerticalBarTest_503, LiteralDotLiteralAlternation_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|.|b", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test that ToString roundtrips for simple alternation
TEST_F(DoVerticalBarTest_503, RoundTripSimple_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string str = re->ToString();
  // Should be able to parse the result again
  Regexp* re2 = Regexp::Parse(str, Regexp::LikePerl, &status);
  ASSERT_TRUE(re2 != nullptr);
  re->Decref();
  re2->Decref();
}

// Test alternation with empty alternatives on both sides
TEST_F(DoVerticalBarTest_503, EmptyBothSides_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("|", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  re->Decref();
}

// Test alternation with DotNL flag
TEST_F(DoVerticalBarTest_503, DotNLAlternation_503) {
  RegexpStatus status;
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::DotNL);
  Regexp* re = Regexp::Parse(".|a", flags, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test many alternatives
TEST_F(DoVerticalBarTest_503, ManyAlternatives_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c|d|e|f|g|h|i|j", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(kRegexpAlternate, re->op());
  re->Decref();
}

// Test alternation with character classes
TEST_F(DoVerticalBarTest_503, CharClassAlternation_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]|[0-9]", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test alternation preserves grouping
TEST_F(DoVerticalBarTest_503, GroupingPreserved_503) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a|b)c", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(kRegexpConcat, re->op());
  re->Decref();
}

}  // namespace re2
