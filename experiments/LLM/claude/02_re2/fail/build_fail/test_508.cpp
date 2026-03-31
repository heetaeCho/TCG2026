#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"

namespace re2 {

// Test Round3 behavior through Regexp::Parse and Alternate, which invoke FactorAlternation internally.

class FactorAlternationRound3Test_508 : public ::testing::Test {
 protected:
  Regexp::ParseFlags flags_ = Regexp::LikePerl;
};

// Test that alternation of single character literals gets merged into a character class
TEST_F(FactorAlternationRound3Test_508, LiteralsMergedIntoCharClass_508) {
  RegexpStatus status;
  // [a|b|c] should be factored by Round3 into a character class
  Regexp* re = Regexp::Parse("[abc]", flags_, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  // A char class should be produced
  EXPECT_NE(s.find("cc"), std::string::npos);
  re->Decref();
}

// Test alternation of individual literals a|b|c gets merged
TEST_F(FactorAlternationRound3Test_508, AlternationOfLiteralsMerged_508) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", flags_, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  // Should be a character class, not an alternation of literals
  EXPECT_NE(s.find("cc"), std::string::npos);
  re->Decref();
}

// Test single literal remains as-is (no merging needed)
TEST_F(FactorAlternationRound3Test_508, SingleLiteralNoMerge_508) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", flags_, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test two literals get merged
TEST_F(FactorAlternationRound3Test_508, TwoLiteralsMerged_508) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", flags_, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  EXPECT_NE(s.find("cc"), std::string::npos);
  re->Decref();
}

// Test mixed literal and non-literal alternation
TEST_F(FactorAlternationRound3Test_508, MixedLiteralAndNonLiteral_508) {
  RegexpStatus status;
  // a|b|.* — a and b should merge, .* stays separate
  Regexp* re = Regexp::Parse("a|b|.*", flags_, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  // Should contain an alternation with a char class and a star
  EXPECT_NE(s.find("alt"), std::string::npos);
  re->Decref();
}

// Test alternation of char classes merges
TEST_F(FactorAlternationRound3Test_508, CharClassesMerged_508) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[ab]|[cd]", flags_, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  // Should be a single char class
  EXPECT_NE(s.find("cc"), std::string::npos);
  // Should not be an alternation
  EXPECT_EQ(s.find("alt"), std::string::npos);
  re->Decref();
}

// Test FoldCase handling for literals
TEST_F(FactorAlternationRound3Test_508, FoldCaseLiteralsMerged_508) {
  RegexpStatus status;
  Regexp::ParseFlags fc_flags = static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::FoldCase);
  Regexp* re = Regexp::Parse("a|b|c", fc_flags, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  EXPECT_NE(s.find("cc"), std::string::npos);
  re->Decref();
}

// Test that non-literal/non-charclass items break the consecutive grouping
TEST_F(FactorAlternationRound3Test_508, NonLiteralBreaksGroup_508) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|.*|c|d", flags_, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  // Should be an alternation
  EXPECT_NE(s.find("alt"), std::string::npos);
  re->Decref();
}

// Test empty alternation
TEST_F(FactorAlternationRound3Test_508, EmptyPattern_508) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", flags_, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test alternation with char class and literal
TEST_F(FactorAlternationRound3Test_508, CharClassAndLiteralMerge_508) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[ab]|c", flags_, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  // Should merge into single char class
  EXPECT_NE(s.find("cc"), std::string::npos);
  EXPECT_EQ(s.find("alt"), std::string::npos);
  re->Decref();
}

// Test many literals merge
TEST_F(FactorAlternationRound3Test_508, ManyLiteralsMerge_508) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c|d|e|f|g|h|i|j", flags_, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  EXPECT_NE(s.find("cc"), std::string::npos);
  EXPECT_EQ(s.find("alt"), std::string::npos);
  re->Decref();
}

// Test alternation where a complex expression separates two groups of literals
TEST_F(FactorAlternationRound3Test_508, TwoGroupsSeparatedByComplex_508) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|cd|e|f", flags_, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  // 'cd' is a concat, not a literal, so it breaks the group
  // a|b should merge, and e|f should merge
  EXPECT_NE(s.find("alt"), std::string::npos);
  re->Decref();
}

// Test that the result of merging is semantically correct via RE2 matching
TEST_F(FactorAlternationRound3Test_508, MergedCharClassMatchesCorrectly_508) {
  RE2 pattern("a|b|c");
  EXPECT_TRUE(RE2::FullMatch("a", pattern));
  EXPECT_TRUE(RE2::FullMatch("b", pattern));
  EXPECT_TRUE(RE2::FullMatch("c", pattern));
  EXPECT_FALSE(RE2::FullMatch("d", pattern));
  EXPECT_FALSE(RE2::FullMatch("ab", pattern));
}

// Test char class merge semantics
TEST_F(FactorAlternationRound3Test_508, MergedCharClassesMatchCorrectly_508) {
  RE2 pattern("[ab]|[cd]|e");
  EXPECT_TRUE(RE2::FullMatch("a", pattern));
  EXPECT_TRUE(RE2::FullMatch("b", pattern));
  EXPECT_TRUE(RE2::FullMatch("c", pattern));
  EXPECT_TRUE(RE2::FullMatch("d", pattern));
  EXPECT_TRUE(RE2::FullMatch("e", pattern));
  EXPECT_FALSE(RE2::FullMatch("f", pattern));
}

// Test FoldCase correctness
TEST_F(FactorAlternationRound3Test_508, FoldCaseMatchesCorrectly_508) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 pattern("a|b|c", opts);
  EXPECT_TRUE(RE2::FullMatch("A", pattern));
  EXPECT_TRUE(RE2::FullMatch("B", pattern));
  EXPECT_TRUE(RE2::FullMatch("C", pattern));
  EXPECT_FALSE(RE2::FullMatch("D", pattern));
}

}  // namespace re2
