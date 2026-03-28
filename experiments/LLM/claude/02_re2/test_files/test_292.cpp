#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include <string>
#include <memory>

namespace re2 {

class CompilerCatTest_292 : public ::testing::Test {
 protected:
  Prog* CompileRegexp(const char* pattern, bool reversed = false, int64_t max_mem = 8 << 20) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re == nullptr) return nullptr;
    Prog* prog = Compiler::Compile(re, reversed, max_mem);
    re->Decref();
    return prog;
  }
};

// Test basic concatenation via compiling "ab" which uses Cat internally
TEST_F(CompilerCatTest_292, BasicConcatenation_292) {
  Prog* prog = CompileRegexp("ab");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test that single character compiles successfully (no Cat needed)
TEST_F(CompilerCatTest_292, SingleCharNoConcat_292) {
  Prog* prog = CompileRegexp("a");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test longer concatenation "abcdef"
TEST_F(CompilerCatTest_292, LongerConcatenation_292) {
  Prog* prog = CompileRegexp("abcdef");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test concatenation with alternation inside "a(b|c)d"
TEST_F(CompilerCatTest_292, ConcatWithAlternation_292) {
  Prog* prog = CompileRegexp("a(b|c)d");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test concatenation with quantifiers "ab*c"
TEST_F(CompilerCatTest_292, ConcatWithStar_292) {
  Prog* prog = CompileRegexp("ab*c");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test concatenation with plus "ab+c"
TEST_F(CompilerCatTest_292, ConcatWithPlus_292) {
  Prog* prog = CompileRegexp("ab+c");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test concatenation with optional "ab?c"
TEST_F(CompilerCatTest_292, ConcatWithQuest_292) {
  Prog* prog = CompileRegexp("ab?c");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test empty pattern
TEST_F(CompilerCatTest_292, EmptyPattern_292) {
  Prog* prog = CompileRegexp("");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test reversed compilation with concatenation
TEST_F(CompilerCatTest_292, ReversedConcatenation_292) {
  Prog* prog = CompileRegexp("abc", true);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test reversed compilation with longer pattern
TEST_F(CompilerCatTest_292, ReversedLongerConcat_292) {
  Prog* prog = CompileRegexp("abcdef", true);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test concatenation with captures "(a)(b)"
TEST_F(CompilerCatTest_292, ConcatWithCaptures_292) {
  Prog* prog = CompileRegexp("(a)(b)");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test that Cat results in correct matching behavior
TEST_F(CompilerCatTest_292, ConcatMatchBehavior_292) {
  RE2 re("abc");
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_FALSE(RE2::FullMatch("ab", re));
  EXPECT_FALSE(RE2::FullMatch("abcd", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
}

// Test concatenation with empty width assertions
TEST_F(CompilerCatTest_292, ConcatWithEmptyWidth_292) {
  Prog* prog = CompileRegexp("^abc$");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test concatenation with character classes
TEST_F(CompilerCatTest_292, ConcatWithCharClass_292) {
  Prog* prog = CompileRegexp("[a-z][0-9]");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test very small max_mem causes failure (tests NoMatch path in Cat)
TEST_F(CompilerCatTest_292, SmallMaxMemFailure_292) {
  Prog* prog = CompileRegexp("abcdefghijklmnopqrstuvwxyz", false, 1);
  // With very small memory, compilation may fail
  // The result is either nullptr or a valid program
  delete prog;  // safe even if nullptr
}

// Test concatenation of dot patterns
TEST_F(CompilerCatTest_292, ConcatDots_292) {
  Prog* prog = CompileRegexp("..");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test nested concatenation with groups
TEST_F(CompilerCatTest_292, NestedGroupConcat_292) {
  Prog* prog = CompileRegexp("(ab)(cd)(ef)");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test matching behavior for concatenation with alternation
TEST_F(CompilerCatTest_292, ConcatAltMatchBehavior_292) {
  RE2 re("a(b|c)d");
  EXPECT_TRUE(RE2::FullMatch("abd", re));
  EXPECT_TRUE(RE2::FullMatch("acd", re));
  EXPECT_FALSE(RE2::FullMatch("ad", re));
  EXPECT_FALSE(RE2::FullMatch("aed", re));
}

// Test concatenation with Unicode
TEST_F(CompilerCatTest_292, ConcatUnicode_292) {
  Prog* prog = CompileRegexp("αβγ");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test CompileSet with concatenation
TEST_F(CompilerCatTest_292, CompileSetConcat_292) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 8 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test reversed concatenation matching
TEST_F(CompilerCatTest_292, ReversedConcatMatchBehavior_292) {
  RE2 re("abc");
  EXPECT_TRUE(RE2::PartialMatch("xabcy", re));
  EXPECT_FALSE(RE2::PartialMatch("xaby", re));
}

// Test concatenation with repetition
TEST_F(CompilerCatTest_292, ConcatWithRepetition_292) {
  Prog* prog = CompileRegexp("a{3}b{2}");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test concatenation nullable fragments
TEST_F(CompilerCatTest_292, ConcatNullableFragments_292) {
  RE2 re("a?b?");
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("b", re));
  EXPECT_TRUE(RE2::FullMatch("ab", re));
}

}  // namespace re2
