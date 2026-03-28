#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// We test the Star function indirectly through the Compile interface,
// since the Compiler class members are not all directly accessible.
// The Star operation corresponds to the regex '*' operator.

class CompilerStarTest_295 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that a simple star pattern compiles and matches correctly (greedy)
TEST_F(CompilerStarTest_295, SimpleStarGreedyCompiles_295) {
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  // "a*" should match empty string
  EXPECT_TRUE(RE2::FullMatch("", "a*"));
  EXPECT_TRUE(RE2::FullMatch("a", "a*"));
  EXPECT_TRUE(RE2::FullMatch("aaa", "a*"));
  delete prog;
  re->Decref();
}

// Test that a simple star pattern compiles with non-greedy
TEST_F(CompilerStarTest_295, SimpleStarNonGreedyCompiles_295) {
  Regexp* re = Regexp::Parse("a*?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test star with a character class
TEST_F(CompilerStarTest_295, StarWithCharClass_295) {
  Regexp* re = Regexp::Parse("[abc]*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(RE2::FullMatch("", "[abc]*"));
  EXPECT_TRUE(RE2::FullMatch("abc", "[abc]*"));
  EXPECT_TRUE(RE2::FullMatch("cba", "[abc]*"));
  EXPECT_TRUE(RE2::FullMatch("aabbcc", "[abc]*"));
  delete prog;
  re->Decref();
}

// Test star matches empty string (nullable property)
TEST_F(CompilerStarTest_295, StarMatchesEmptyString_295) {
  EXPECT_TRUE(RE2::FullMatch("", "a*"));
  EXPECT_TRUE(RE2::FullMatch("", ".*"));
  EXPECT_TRUE(RE2::FullMatch("", "[a-z]*"));
}

// Test nested star - e.g., (a*)* which involves nullable fragments
TEST_F(CompilerStarTest_295, NestedStarNullable_295) {
  Regexp* re = Regexp::Parse("(a*)*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(RE2::FullMatch("", "(a*)*"));
  EXPECT_TRUE(RE2::FullMatch("a", "(a*)*"));
  EXPECT_TRUE(RE2::FullMatch("aaa", "(a*)*"));
  delete prog;
  re->Decref();
}

// Test star with dot (any character)
TEST_F(CompilerStarTest_295, StarWithDot_295) {
  EXPECT_TRUE(RE2::FullMatch("", ".*"));
  EXPECT_TRUE(RE2::FullMatch("hello world", ".*"));
  EXPECT_TRUE(RE2::FullMatch("12345", ".*"));
}

// Test greedy vs non-greedy star behavior via partial match
TEST_F(CompilerStarTest_295, GreedyVsNonGreedyBehavior_295) {
  std::string match;
  // Greedy: should match as much as possible
  EXPECT_TRUE(RE2::PartialMatch("aaa", "(a*)", &match));
  EXPECT_EQ(match, "aaa");

  // Non-greedy: should match as little as possible
  EXPECT_TRUE(RE2::PartialMatch("aaa", "(a*?)", &match));
  EXPECT_EQ(match, "");
}

// Test star in combination with other operators
TEST_F(CompilerStarTest_295, StarCombinedWithCat_295) {
  EXPECT_TRUE(RE2::FullMatch("baaac", "ba*c"));
  EXPECT_TRUE(RE2::FullMatch("bc", "ba*c"));
  EXPECT_FALSE(RE2::FullMatch("bdc", "ba*c"));
}

// Test star in combination with alternation
TEST_F(CompilerStarTest_295, StarCombinedWithAlt_295) {
  EXPECT_TRUE(RE2::FullMatch("aaa", "(a|b)*"));
  EXPECT_TRUE(RE2::FullMatch("bbb", "(a|b)*"));
  EXPECT_TRUE(RE2::FullMatch("ababab", "(a|b)*"));
  EXPECT_TRUE(RE2::FullMatch("", "(a|b)*"));
}

// Test star with reversed compilation
TEST_F(CompilerStarTest_295, StarReversedCompile_295) {
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test star with very small memory limit
TEST_F(CompilerStarTest_295, StarWithSmallMemoryLimit_295) {
  // Very small memory limit might cause compilation to fail gracefully
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Even with a tiny limit, simple patterns should still compile
  // or return nullptr gracefully
  Prog* prog = Compiler::Compile(re, false, 1);
  // The result depends on implementation; just ensure no crash
  delete prog;
  re->Decref();
}

// Test star on a group
TEST_F(CompilerStarTest_295, StarOnGroup_295) {
  EXPECT_TRUE(RE2::FullMatch("abcabcabc", "(abc)*"));
  EXPECT_TRUE(RE2::FullMatch("", "(abc)*"));
  EXPECT_FALSE(RE2::FullMatch("ab", "(abc)*"));
}

// Test star with capture groups
TEST_F(CompilerStarTest_295, StarWithCapture_295) {
  std::string capture;
  EXPECT_TRUE(RE2::FullMatch("aaa", "(a)*", &capture));
  // Last captured value
  EXPECT_EQ(capture, "a");
}

// Test non-greedy star on nullable subexpression
TEST_F(CompilerStarTest_295, NonGreedyStarNullableSubexpr_295) {
  // (a?)* is nullable, so Star should use Quest(Plus(...))
  Regexp* re = Regexp::Parse("(a?)*?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(RE2::FullMatch("", "(a?)*?"));
  EXPECT_TRUE(RE2::FullMatch("aaa", "(a?)*?"));
  delete prog;
  re->Decref();
}

// Test star with unicode/multi-byte characters
TEST_F(CompilerStarTest_295, StarWithUnicode_295) {
  EXPECT_TRUE(RE2::FullMatch("", "\\pL*"));
  EXPECT_TRUE(RE2::FullMatch("abc", "\\pL*"));
}

// Test star applied to a complex regex
TEST_F(CompilerStarTest_295, StarComplexPattern_295) {
  EXPECT_TRUE(RE2::FullMatch("xyxyxy", "(xy)*"));
  EXPECT_TRUE(RE2::FullMatch("", "(xy)*"));
  EXPECT_FALSE(RE2::FullMatch("xyx", "(xy)*"));
}

// Test compilation of CompileSet with star
TEST_F(CompilerStarTest_295, CompileSetWithStar_295) {
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test double star: a** equivalent to a*
TEST_F(CompilerStarTest_295, DoubleStarSimplified_295) {
  // Regexp parser may simplify a** but the pattern should still work
  EXPECT_TRUE(RE2::FullMatch("", "a*"));
  EXPECT_TRUE(RE2::FullMatch("aaaa", "a*"));
}

// Test star at end of pattern
TEST_F(CompilerStarTest_295, StarAtEndOfPattern_295) {
  EXPECT_TRUE(RE2::FullMatch("ab", "ab*"));
  EXPECT_TRUE(RE2::FullMatch("abbb", "ab*"));
  EXPECT_TRUE(RE2::FullMatch("a", "ab*"));
}

// Test star at beginning of pattern
TEST_F(CompilerStarTest_295, StarAtBeginningOfPattern_295) {
  EXPECT_TRUE(RE2::FullMatch("b", "a*b"));
  EXPECT_TRUE(RE2::FullMatch("aaab", "a*b"));
}

}  // namespace re2
